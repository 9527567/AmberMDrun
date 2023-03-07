import os
import pathlib
from setuptools import setup
from setuptools import Extension
from setuptools.command.build_ext import build_ext
from distutils.sysconfig import get_python_lib
from distutils import spawn
import sys

class CMakeExtension(Extension):

    def __init__(self, name):
        super().__init__(name, sources=[])


class BuildExt(build_ext):
    def run(self):
        for ext in self.extensions:
            if isinstance(ext, CMakeExtension):
                self.build_cmake(ext)
        super().run()

    def build_cmake(self, ext):
        cwd = pathlib.Path().absolute()

        build_temp = f"{pathlib.Path(self.build_temp)}/{ext.name}"
        os.makedirs(build_temp, exist_ok=True)
        extdir = pathlib.Path(self.get_ext_fullpath(ext.name))
        extdir.mkdir(parents=True, exist_ok=True)

        config = "Debug" if self.debug else "Release"
        _source_dir = os.path.split(__file__)[0]
        _build_dir = os.path.join(_source_dir, 'build_setup_py')
        _prefix = get_python_lib()
        try:
            cmake_configure_command = [
                'cmake',
                '-H{0}'.format(_source_dir),
                '-B{0}'.format(_build_dir),
                '-DCMAKE_INSTALL_PREFIX={0}'.format(_prefix)
            ]
            _generator = os.getenv('CMAKE_GENERATOR')
            if _generator is not None:
              cmake_configure_command.append('-G{0}'.format(_generator))
            spawn.spawn(cmake_configure_command)
            build_args = [
                "--config", config,
                "-j8",
                "--target","install"
            ]
            os.chdir(build_temp)
            if not self.dry_run:
                self.spawn(["cmake", "--build", _build_dir] + build_args)
            os.chdir(str(cwd))
        except spawn.DistutilsExecError:
            sys.stderr.write("Error while building with CMake\n")
            sys.exit(-1)
            _build.build.run(self)

pyamber = CMakeExtension(".")

setup(name="AmberMDrun",
      version="0.1",
      description="This is a demo package",
      packages=["."],
      ext_modules=[pyamber],  
      cmdclass={"build_ext": BuildExt},  
      entry_points={'console_scripts': ['amberMDrun = main:main', "mmpbsa = mmpbsa:main"]}
      )