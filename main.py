import argparse as arg
import pyamber as pya
import os
if __name__ == '__main__':
    s = pya.SystemInfo("com.parm7","com.rst7")
    min1 = pya.Min("step1",systemInfo=s,ref="com.rst7",restraint_wt=5.0)
    min1.Run()
    md = pya.Md(name="step2",systemInfo=s,ref="step1.rst7",restraint_wt=2.0,dt=0.001)
    md.Run()
