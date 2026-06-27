import os
import subprocess
import sys
from pathlib import Path

from setuptools import Command, Extension, setup
from setuptools.command.build_ext import build_ext

import re

def get_version():
    with open("AmberMDrun/version.py") as f:
        return re.search(r'__version__\s*=\s*[\'"]([^\'"]+)[\'"]', f.read()).group(1)

__version__ = get_version()

PLAT_TO_CMAKE = {
    "Linux": "x86",
    "Linux-amd64": "x64",
    "Linux-arm32": "ARM",
    "Linux-arm64": "ARM64",
}


class CMakeExtension(Extension):
    def __init__(self, name: str, sourcedir: str = "") -> None:
        super().__init__(name, sources=[])
        self.sourcedir = os.fspath(Path(sourcedir).resolve())


class CMakeBuild(build_ext):
    def build_extension(self, ext: CMakeExtension) -> None:
        ext_fullpath = Path.cwd() / self.get_ext_fullpath(ext.name)
        extdir = ext_fullpath.parent.resolve()

        debug = int(os.environ.get("DEBUG", 0)) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"

        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}{os.sep}/AmberMDrun",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-DCMAKE_BUILD_TYPE={cfg}",
        ]
        build_args = []
        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

        if self.compiler.compiler_type != "msvc":
            if not cmake_generator or cmake_generator == "Ninja":
                try:
                    import ninja
                    ninja_executable_path = Path(ninja.BIN_DIR) / "ninja"
                    cmake_args += [
                        "-GNinja",
                        f"-DCMAKE_MAKE_PROGRAM:FILEPATH={ninja_executable_path}",
                    ]
                except ImportError:
                    pass
        else:
            single_config = any(x in cmake_generator for x in {"NMake", "Ninja"})
            contains_arch = any(x in cmake_generator for x in {"ARM", "Win64"})
            if not single_config and not contains_arch:
                cmake_args += ["-A", PLAT_TO_CMAKE[self.plat_name]]
            if not single_config:
                cmake_args += [f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{cfg.upper()}={extdir}"]
                build_args += ["--config", cfg]

        if sys.platform.startswith("darwin"):
            raise RuntimeError("Mac OS X is not supported")

        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            if hasattr(self, "parallel") and self.parallel:
                build_args += [f"-j{self.parallel}"]

        build_temp = Path(self.build_temp) / ext.name
        if not build_temp.exists():
            build_temp.mkdir(parents=True)

        subprocess.run(
            ["cmake", ext.sourcedir, *cmake_args], cwd=build_temp, check=True
        )
        subprocess.run(
            ["cmake", "--build", ".", *build_args], cwd=build_temp, check=True
        )


class BuildDocs(Command):
    description = "Generate Doxygen HTML documentation"
    user_options = []

    def initialize_options(self) -> None:
        pass

    def finalize_options(self) -> None:
        pass

    def run(self) -> None:
        build_dir = Path("build") / "docs"
        subprocess.run(
            ["cmake", "-S", "AmberMDrun", "-B", str(build_dir)], check=True
        )
        subprocess.run(
            ["cmake", "--build", str(build_dir), "--target", "docs"], check=True
        )
        docs_html = build_dir / "html"
        if docs_html.exists():
            print(f"Documentation generated in {docs_html}")


with open("README.md", encoding="utf-8") as f:
    long_description = f.read()

setup(
    name="AmberMDrun",
    version=__version__,
    author="ZhiWei Zhang",
    author_email="z9527567@gmail.com",
    description="A scripting tool for running Amber MD in an easy way",
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=["AmberMDrun"],
    install_requires=['pandas'],
    ext_modules=[CMakeExtension("AmberMDrun")],
    cmdclass={"build_ext": CMakeBuild, "build_docs": BuildDocs},
    entry_points={'console_scripts': ['amberMDrun = AmberMDrun:main', "mmpbsa = AmberMDrun:mmpbsa"]},
    zip_safe=False,
    python_requires=">=3.9,<3.15",
    project_urls={
        "Source": "https://github.com/9527567/AmberMDrun",
        "Bug Tracker": "https://github.com/9527567/AmberMDrun/issues",
    },
)
