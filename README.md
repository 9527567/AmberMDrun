# AmberMD
方便使用易于扩展，高性能的amber模拟程序包
## 安装
~~~bash
git clone https://github.com/9527567/AmberMD --recursive
python3 setup.py install --user
~~~
## 使用
~~~bash
ambermd -h
usage: ambermd [-h] --parm7 PARM7 --rst7 RST7 [--temp TEMP] [--ns NS] [--addmask ADDMASK] [--gamd GAMD]

Demo of AmberMD

optional arguments:
  -h, --help            show this help message and exit
  --parm7 PARM7, -p PARM7
                        amber top file
  --rst7 RST7, -c RST7  amber rst file
  --temp TEMP, -t TEMP  Temperature
  --ns NS, -n NS        time for MD(ns)
  --addmask ADDMASK     add restarint mask
  --gamd GAMD           if run gamd
~~~
## 定制自己的类
待续
