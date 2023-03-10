
 [English](README.md) | [中文](README.zh.md) 

# AmberMDrun 
Easy to use, easy to expand, high-performance Amber simulation package
## Install
This software only supports **Linux** because some Linux system functions are called.**Mac OS X** and **Windows** are not supported.
### Necessary
Ambertools, python3, and python3-dev are required. Amber acceleration package is optional, but we strongly recommend installing high-performance pmemd module. [Amber](https://ambermd.org/)

You can refer to the [Amber installation tutorial](https://ambermd.org/Installation.php) to install Amber.

Then, you can choose several installation methods.

1. Anaconda(**recommend**)

![anaconda](https://anaconda.org/zjack/ambermdrun/badges/version.svg)
![update](https://anaconda.org/zjack/ambermdrun/badges/latest_release_date.svg)
![download](https://anaconda.org/zjack/ambermdrun/badges/downloads.svg)
![MIT](https://anaconda.org/zjack/ambermdrun/badges/license.svg)
![platform](https://anaconda.org/zjack/ambermdrun/badges/platforms.svg)
~~~bash
conda install ambermdrun -c zjack
~~~
<br>

2. PYPI
PYPI installation requires a c++compiler that supports the c++17 standard.
GCC-8 does not fully support the file system in the c++17 standard, so GCC-9 or higher is required. Therefore, different systems have different processing methods, and we recommend using conda for installation.

Ubuntu >= 20
~~~bash
apt install g++ libpython3-dev
pip install AmberMDrun
~~~
 centos7
 We recommend [Red Hat Developer Toolset](https://access.redhat.com/documentation/en-us/red_hat_developer_toolset/9) for higher version of gcc.
~~~bash
yum update
yum install epel-release
yum install centos-release-scl-rh
yum install devtoolset-9
source /opt/rh/devtoolset-9/enable # enable gcc-9
yum install python3-devel
pip install AmberMDrun
~~~
3. You can also choose to build from source code.
~~~bash
git clone https://github.com/9527567/AmberMD --recursive
python setup.py install --user
~~~
### Optional
If you want to use AmberMDrun to calculate MMPB (GB) SA, then additional programs are necessary.

- [ACPYPE](https://github.com/alanwilter/acpype)
- [gmx_MMPBSA](https://github.com/Valdes-Tresanco-MS/gmx_MMPBSA)
## How to use parm7 and rst7 for dynamic simulation
~~~bash
amberMDrun -h
usage: amberMDrun [-h] --parm7 PARM7 --rst7 RST7 [--temp TEMP] [--ns NS] [--addmask ADDMASK] [--gamd GAMD]

Demo of AmberMD

options:
  -h, --help            show this help message and exit
  --parm7 PARM7, -p PARM7
                        amber top file
  --rst7 RST7, -c RST7  amber rst file
  --temp TEMP, -t TEMP  Temperature
  --ns NS, -n NS        time for MD(ns)
  --addmask ADDMASK     add restarint mask
  --gamd GAMD           if run gamd
~~~
## How to calculate MM-PB (GB) SA between small molecules and proteins of a single drug

~~~bash
mmpbsa -h
usage: mmpbsa [-h] --protein PROTEIN --mol2 MOL2 [--temp TEMP] [--ns NS] [--mmpbsa MMPBSA]

Demo of MMPBSA

options:
  -h, --help            show this help message and exit
  --protein PROTEIN, -p PROTEIN
                        pdb file for protein
  --mol2 MOL2, -m MOL2  mol2 file for mol
  --temp TEMP, -t TEMP  Temperature
  --ns NS, -n NS        time for MD(ns)
  --mmpbsa MMPBSA       if run mmpbsa
~~~
## How to extend code through inheritance classes
Will be described in the near future

