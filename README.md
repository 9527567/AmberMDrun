# AmberMD
方便使用的，高性能的amber脚本
## 安装
~~~bash
cd AmberMD
mkdir build
cd build
cmake ..
make
cp pyamber.so {your python package path}
~~~
## 使用
~~~python
import pyamber as pya
if __name__ == '__main__':
    # 读取拓扑坐标中的信息
    s = pya.SystemInfo("com.parm7","com.rst7")
    # 创建能量最小化的类
    min1 = pya.Min("step1",systemInfo=s,ref="com.rst7",restraint_wt=5.0)
    # 运行能量最小化
    min1.Run()
    # 创建MD类，nvt平衡
    nvt = pya.Md(name="step2",systemInfo=s,ref="step1.rst7",restraint_wt=2.0,dt=0.001,ntb=1)
    nvt.Run()
    # npt平衡
    npt = pya.Md(name="step2",systemInfo=s,ref="step1.rst7",restraint_wt=1.0,dt=0.001,ntb=2)
    npt.Run()
    # 运行MD
    md = pya.Md(name="step2",systemInfo=s,ref="step1.rst7",restraint_wt=1.0,dt=0.001,ntb=2)
    md.Run()
~~~