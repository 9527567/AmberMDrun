# # AmberMDrun 

## 如何安装
~~~bash
git clone https://github.com/9527567/AmberMD --recursive
python3 setup.py install --user
~~~
## 使用构建好的parm7和rst7文件运行模拟
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
## 计算蛋白和单个配体的MM-PB(GB)SA
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
## 如何编写自己的类？
Will be described in the near future
