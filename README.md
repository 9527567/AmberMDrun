
 [English](README.md) | [中文](README.zh.md) 

# AmberMDrun 
Easy to use, easy to expand, high-performance Amber simulation package
## Update 
v0.0.5 Added support for multiple ligands.
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

![pypi](https://img.shields.io/pypi/dm/ambermdrun?style=flat-square)

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
usage: amberMDrun [-h] --parm7 PARM7 --rst7 RST7 [--temp TEMP] [--ns NS] [--addmask ADDMASK] [--gamd GAMD] [--MIN MIN] [--MD MD]

Tools for automated operation of AMBER MD

options:
  -h, --help            show this help message and exit
  --parm7 PARM7, -p PARM7
                        amber top file
  --rst7 RST7, -c RST7  amber rst file
  --temp TEMP, -t TEMP  Temperature
  --ns NS, -n NS        time for MD(ns)
  --addmask ADDMASK     add restarint mask
  --gamd GAMD           if run gamd
  --MIN MIN             Engine for MIN
  --MD MD               Engine for MD
~~~
## How to calculate MM-PB (GB) SA between small molecules and proteins of a single drug

~~~bash
usage: mmpbsa [-h] --protein PROTEIN [--mol2 MOL2 [MOL2 ...]] [--temp TEMP] [--ns NS] [-g] [-c CHARGE [CHARGE ...]] [--multiplicity MULTIPLICITY [MULTIPLICITY ...]] [--MIN MIN] [--MD MD]

Tools for automating the operation of MMPBSA

options:
  -h, --help            show this help message and exit
  --protein PROTEIN, -p PROTEIN
                        pdb file for protein
  --mol2 MOL2 [MOL2 ...], -m MOL2 [MOL2 ...]
                        mol2 file for mol
  --temp TEMP, -t TEMP  Temperature
  --ns NS, -n NS        time for MD(ns)
  -g, --guess_charge    guess charge
  -c CHARGE [CHARGE ...], --charge CHARGE [CHARGE ...]
                        charge of mol
  --multiplicity MULTIPLICITY [MULTIPLICITY ...]
                        multiplicity of mol
  --MIN MIN             Engine for MIN
  --MD MD               Engine for MD
~~~
Typically, the complex structure after molecular docking is used to perform MMPBSA calculations.Therefore, we have provided a short code to handle the pdb format of the complex. Therefore, when your complex structure is docked and the ligand is in the desired initial position, you can directly provide the pdb format file of the complex.The following is an example.**It should be noted that we will not actively assist you in handling the hydrogen atom of the ligand. We need you to ensure that the hydrogen of the ligand is correct.**
~~~bash
mmpbsa -p complex.pdb
~~~
## V0.0.5 added support for multiple ligands
Just follow the files of multiple ligands after -m, and add an option `-g` to guess the static charge of small molecules, or manually specify the static charge, for example:
~~~bash
mmpbsa -p pro.pdb -m lig1.mol2 lig2.mol2 -g -n 100
~~~
## How to extend code through inheritance classes
Will be described in the near future

## How to cite
bibtex:
~~~tex
@Article{biom13040635,
AUTHOR = {Zhang, Zhi-Wei and Lu, Wen-Cai},
TITLE = {AmberMDrun: A Scripting Tool for Running Amber MD in an Easy Way},
JOURNAL = {Biomolecules},
VOLUME = {13},
YEAR = {2023},
NUMBER = {4},
ARTICLE-NUMBER = {635},
URL = {https://www.mdpi.com/2218-273X/13/4/635},
ISSN = {2218-273X},
DOI = {10.3390/biom13040635}
}
~~~
## If you are interested, you can also cite this article
~~~tex
@article{CUI2023134812,
title = {A TastePeptides-Meta system including an umami/bitter classification model Umami_YYDS, a TastePeptidesDB database and an open-source package Auto_Taste_ML},
journal = {Food Chemistry},
volume = {405},
pages = {134812},
year = {2023},
issn = {0308-8146},
doi = {https://doi.org/10.1016/j.foodchem.2022.134812},
url = {https://www.sciencedirect.com/science/article/pii/S0308814622027741},
author = {Zhiyong Cui and Zhiwei Zhang and Tianxing Zhou and Xueke Zhou and Yin Zhang and Hengli Meng and Wenli Wang and Yuan Liu},
keywords = {Peptides, Umami prediction, TastePeptidesDB, Machine learning},
abstract = {Taste peptides with umami/bitterness play a role in food attributes. However, the taste mechanisms of peptides are not fully understood, and the identification of these peptides is time-consuming. Here, we created a taste peptide database by collecting the reported taste peptide information. Eight key molecular descriptors from di/tri-peptides were selected and obtained by modeling screening. A gradient boosting decision tree model named Umami_YYDS (89.6\% accuracy) was established by data enhancement, comparison algorithm and model optimization. Our model showed a great prediction performance compared to other models, and its outstanding ability was verified by sensory experiments. To provide a convenient approach, we deployed a prediction website based on Umami_YYDS and uploaded the Auto_Taste_ML machine learning package. In summary, we established the system TastePeptides-Meta, containing a taste peptide database TastePeptidesDB an umami/bitter taste prediction model Umami_YYDS and an open-source machine learning package Auto_Taste_ML, which were helpful for rapid screening of umami peptides.}
}
~~~