[English](README.md) [中文](README.zh.md)
# AmberMDrun 
Easy to use, easy to expand, high-performance Amber simulation package
## install
~~~bash
git clone https://github.com/9527567/AmberMD --recursive
python3 setup.py install --user
~~~
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

