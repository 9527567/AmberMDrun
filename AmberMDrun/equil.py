from . import pyamber
import os
import pandas as pd
from pathlib import Path


def density():
    path = Path.cwd()
    final_file = []
    for out_file in path.glob('final_*.out'):
        final_file.append(out_file)
    input = (f"for FILE in {' '.join([item.name for item in final_file])} \n"
             "readdata \$FILE name MD \n"
             "done \n"
             "evalplateau *[Density] name EQ out Eval.agr resultsout Eval.results\n"
             "go\n"
             "quit"
             )

    with open("cpptraj.in", "w") as f:
        f.write(input)
    os.system(f'cpptraj -i cpptraj.in')
    result = pd.read_csv("Eval.results", sep="\s+")
    if result["EQ[result]"][0] == "yes":
        return 0
    elif result["EQ[result]"][0] == "no":
        return 1
    else:
        raise RuntimeError("Equil failed!")


def prep(rst7, s, temp, heavymask, backbonemask, loop=20):
    min1 = pyamber.Min("step1", systemInfo=s, ref=rst7,
                       refc=rst7, restraintmask=heavymask, restraint_wt=5.0)
    min1.Run()
    nvt1 = pyamber.NVT("step2", systemInfo=s, ref="step1.rst7", refc="step1.rst7", temp=temp,
                       restraintmask=heavymask, restraint_wt=5.0, nstlim=15000, tautp=0.5)
    nvt1.Run()
    min2 = pyamber.Min('step3', systemInfo=s, ref='step2.rst7',
                       refc='step2.rst7', restraintmask=heavymask, restraint_wt=2.0)
    min2.Run()
    min3 = pyamber.Min('step4', systemInfo=s, ref='step3.rst7',
                       refc='step3.rst7', restraintmask=backbonemask, restraint_wt=0.1)
    min3.Run()
    min4 = pyamber.Min('step5', systemInfo=s,
                       ref='step4.rst7', refc='step4.rst7')
    min4.Run()
    npt1 = pyamber.NPT("step6", systemInfo=s, ref="step5.rst7", temp=temp,
                       refc="step5.rst7", restraintmask=heavymask, restraint_wt=1.0)
    npt1.Run()
    npt2 = pyamber.NPT("step7", systemInfo=s, ref="step6.rst7", refc="step5.rst7", temp=temp,
                       irest=True, restraintmask=heavymask, restraint_wt=0.5)
    npt2.Run()
    npt3 = pyamber.NPT("step8", systemInfo=s, ref="step7.rst7", refc="step5.rst7", temp=temp,
                       irest=True, restraintmask=backbonemask, restraint_wt=0.5, nstlim=10000)
    npt3.Run()
    npt4 = pyamber.NPT("step9", systemInfo=s, ref="step8.rst7", temp=temp,
                       refc="step5.rst7", irest=True, dt=0.002, nscm=1000)
    npt4.Run()

    ref = "step9.rst7"
    for i in range(loop):
        final = pyamber.NPT(f"final_{i}", systemInfo=s, ref=ref, temp=temp,
                            refc="step5.rst7", irest=True, dt=0.002, nscm=1000, nstlim=500000, ntwx=5000)
        final.Run()
        result = density()
        if result == 0:
            return f'final_{i}.rst7'
        ref = f'final_{i}.rst7'
    raise RuntimeError(
        "More than 20 iterations of final density equil required. Bailing out.")

