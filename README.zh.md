# AmberMDrun 
易于使用、易于扩展、高性能的Amber模拟软件包。
## 版本更新
v0.0.5 添加了多配体的支持。
## 安装
此软件仅支持**Linux**，因为某些Linux系统功能被调用。**Mac OS X**和**Windows**不受支持。
### 必要的依赖
Ambertools、python3和python3dev是必需的。Amber加速包是可选的，但我们强烈建议安装高性能的pmemd模块。[Amber](https://ambermd.org/)



您可以参考[Amber安装教程](https://ambermd.org/Installation.php)以安装琥珀色。

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
PYPI安装需要一个支持c++17标准的c++编译器。
GCC-8并不完全支持c++17标准中的文件系统，因此需要GCC-9或更高版本。因此，不同的系统有不同的处理方法，我们建议使用conda进行安装。

![pypi](https://img.shields.io/pypi/dm/ambermdrun?style=flat-square)

Ubuntu >= 20
~~~bash
apt install g++ libpython3-dev
pip install AmberMDrun
~~~
 centos7
我们推荐[Red Hat开发工具集](https://access.redhat.com/documentation/en-us/red_hat_developer_toolset/9)用于更高版本的gcc。
~~~bash
yum update
yum install epel-release
yum install centos-release-scl-rh
yum install devtoolset-9
source /opt/rh/devtoolset-9/enable # enable gcc-9
yum install python3-devel
pip install AmberMDrun
~~~
3. 您也可以选择从源代码构建。
~~~bash
git clone https://github.com/9527567/AmberMD --recursive
python setup.py install --user
~~~
### Optional
如果要使用AmberMDrun计算MMPB（GB）SA，则需要其他程序。

- [ACPYPE](https://github.com/alanwilter/acpype)
- [gmx_MMPBSA](https://github.com/Valdes-Tresanco-MS/gmx_MMPBSA)
## 如何使用parm7和rst7进行分子动力学模拟
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
## 如何计算单个小分子和蛋白质之间的MM-PB（GB）SA
~~~bash
usage: mmpbsa [-h] --protein PROTEIN [--mol2 MOL2 [MOL2 ...]] [--temp TEMP] [--ns NS] [-g] [-uc] [-c CHARGE [CHARGE ...]] [--multiplicity MULTIPLICITY [MULTIPLICITY ...]]
              [--MIN MIN] [--MD MD]

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
  -uc, --user_charge    user charge
  -c CHARGE [CHARGE ...], --charge CHARGE [CHARGE ...]
                        charge of mol
  --multiplicity MULTIPLICITY [MULTIPLICITY ...]
                        multiplicity of mol
  --MIN MIN             Engine for MIN
  --MD MD               Engine for MD
~~~
通常，分子对接后的复合物结构用于执行MMPBSA计算。因此，我们提供了一个简短的代码来处理复合物的pdb格式。因此，当您的络合物结构对接并且配体处于所需的初始位置时，您可以直接提供络合物的pdb格式文件。以下是一个示例。**需要注意的是，我们不会主动协助您处理配体的氢原子。我们需要你确保配体的氢是正确的**。
~~~bash
mmpbsa -p complex.pdb
~~~

## V0.0.5 添加了多配体的支持
只需要在-m 后跟多个配体的文件即可，添加了一个选项`-g`用于猜测小分子的静电荷，或者手动指定静电荷，例如：
~~~bash
mmpbsa -p pro.pdb -m lig1.mol2 lig2.mol2 -g -n 100
~~~
## V0.0.6 添加自定义电荷选项
添加了一个选项`-uc`用于使用自定义小分子的静电荷，只能用mol2文件，例如：
~~~bash
mmpbsa -p pro.pdb -m lig1.mol2 lig2.mol2 -uc -n 100
~~~
## 如何通过继承扩展代码
我们将在不久的将来进行描述。

## 如何引用
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
## 如果您感兴趣的话，也可以引用这篇文章
bibtex:
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