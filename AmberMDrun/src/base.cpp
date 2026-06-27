//
// Created by jack on 2022/9/19.
//
#include "base.hpp"
#include "fmt/core.h"
#include "fmt/os.h"
#include <utility>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

Base *Base::runningInstance_ = nullptr;
#define f fmt::format
void Base::sigintHandler(int)
{
    if (runningInstance_) {
        if (runningInstance_->childPid_ > 0)
            kill(-runningInstance_->childPid_, SIGKILL);
        runningInstance_->done_ = true;
    }
    const char msg[] = "\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(130);
}

Base::Base(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest,
           const std::string &restranintmask, float restraint_wt, float cut)
{
    name_ = name;
    systemInfo_ = std::move(systemInfo);
    rst7_ = rst7;
    iRest_ = irest;
    restraintMask_ = restranintmask;
    restraint_wt_ = restraint_wt;
    cut_ = cut;
}

void Base::writeInput()
{
    fmt::ostream out = fmt::output_file(name_ + ".in");
    out.print("Minimization:{}\n", name_);
    out.print("&cntrl\n");
}

void Base::Run()
{
    if (this->done_) this->done_ = false;
    runningInstance_ = this;
    auto *prev = std::signal(SIGINT, sigintHandler);
    writeInput();
    charmmWater();
    restraint();
    writeEnd();
    {
        std::exception_ptr ep;
        std::thread th1([this, &ep] {
            try { progress(); }
            catch (...) { ep = std::current_exception(); done_ = true; }
        });
        std::thread th2([this, &ep] {
            try { runMd(); }
            catch (...) { ep = std::current_exception(); done_ = true; }
        });
        th1.join();
        th2.join();
        if (ep) std::rethrow_exception(ep);
    }
    std::signal(SIGINT, prev);
    runningInstance_ = nullptr;
}

void Base::charmmWater()
{
    if (systemInfo_.getHasCharmmWater())
    {
        hasCharmmWater_ = true;
    }
    if (hasCharmmWater_)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("   WATNAM = 'TIP3', OWTNM = 'OH2',");
    }
}

void Base::writeEnd()
{
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("&end\n");
}

void Base::restraint()
{
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    if (restraintMask_.empty())
    {
        out.print("ntr=0");
        out.print("\n");
    } else
    {
        out.print("ntr=1,");
        out.print("restraintmask={},", restraintMask_);
        out.print("restraint_wt={},", restraint_wt_);
        out.print("\n");
    }
}

// 最简单的版本
Base *Base::setRestraintMask(std::string restraintMask)
{
    restraintMask_ = std::move(restraintMask);
    return this;
}

[[maybe_unused]] Base *Base::setCut(float cut)
{
    cut_ = cut;
    return this;
}

Base *Base::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}

Base *Base::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}

Base *Base::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}

void Base::runMd()
{
    run_.release();
    std::string run = "sander";
    if (iMin_ == 1)
        run = systemInfo_.getRunMin();
    else
        run = systemInfo_.getRunMd();

    std::string execCommand = fmt::format(
            "{} -O -i {}.in -p {} -c {} -ref {} -o {}.out -r {}.rst7 -x {}.nc -inf {}.mdinfo -AllowSmallBox", run,
            name_, systemInfo_.getParm7File(), rst7_, refc_, name_, name_, name_, name_);

    int stdout_fds[2];
    if (pipe(stdout_fds) == -1)
        throw std::runtime_error("pipe() failed");

    childPid_ = fork();
    if (childPid_ == -1)
    {
        close(stdout_fds[0]);
        close(stdout_fds[1]);
        throw std::runtime_error("fork() failed");
    }

    if (childPid_ == 0)
    {
        close(stdout_fds[0]);
        dup2(stdout_fds[1], 1);
        dup2(stdout_fds[1], 2);
        close(stdout_fds[1]);
        setpgid(0, 0);
        execl("/bin/sh", "sh", "-c", execCommand.c_str(), nullptr);
        _exit(127);
    }

    close(stdout_fds[1]);

    int flags = fcntl(stdout_fds[0], F_GETFL, 0);
    fcntl(stdout_fds[0], F_SETFL, flags | O_NONBLOCK);

    std::string out;
    char buffer[4096];
    ssize_t r;
    while (!this->done_) {
        r = read(stdout_fds[0], buffer, sizeof(buffer));
        if (r > 0) {
            out.append(buffer, r);
        } else if (r == 0) {
            break;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } else if (errno == EINTR) {
            continue;
        } else {
            break;
        }
    }
    close(stdout_fds[0]);

    int status;
    pid_t ret;
    if (this->done_ && childPid_ > 0) {
        kill(-childPid_, SIGKILL);
    }
    do {
        ret = waitpid(childPid_, &status, 0);
    } while (ret == -1 && errno == EINTR);

    childPid_ = -1;

    if (ret > 0 && WIFSIGNALED(status))
        throw std::runtime_error(fmt::format("{} was terminated by signal {} (Ctrl+C)", execCommand, WTERMSIG(status)));
    if (ret > 0 && WIFEXITED(status) && WEXITSTATUS(status) != 0)
        throw std::runtime_error(fmt::format("{} run failed!\n", execCommand));

    fmt::print("{}", out);

    this->done_ = true;
}

Base *Base::setRestraint_wt(float restraint_wt)
{
    restraint_wt_ = restraint_wt;
    return this;
}
void Base::progress()
{
    run_.acquire();

    int index = 0;
    tqdm bar;
    fswatcher_t watcher = fswatcher_create(FSWATCHER_CREATE_DEFAULT, FSWATCHER_EVENT_ALL, ".", nullptr);

    while (!this->done_)
    {
        fswatcher_event_handler handler = {[&](fswatcher_event_handler *handler, fswatcher_event_type evtype, const char *src, const char *dst) -> bool {
            if (src =="./" + this->name_ + ".out")
            {
                (void) handler;
                (void) dst;

                switch (evtype)
                {
                    case FSWATCHER_EVENT_CREATE:
                        index += 10;
                        bar.progress(index, 100);
                        break;
                    case FSWATCHER_EVENT_MODIFY:
                        index += 10;
                        bar.progress(index, 100);
                        break;
                    default:
                        printf("unhandled event!\n");
                }
            }
            return true;
        }};
        fswatcher_poll(watcher, &handler, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    bar.finish();
    fswatcher_destroy(watcher);
}
