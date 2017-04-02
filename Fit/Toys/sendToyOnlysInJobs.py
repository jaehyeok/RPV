#! /usr/bin/env python
import argparse
import os

parser = argparse.ArgumentParser(description="Sends toys")
parser.add_argument("workspace", help="Path to workspace (also accepts datacards)")
parser.add_argument("seed", help="Seed to start with. Seed is incremented by 1 for every toy after.")
parser.add_argument("sig",choices=['0','1','2'], help="Expected signal. If '2', run both sig0 and sig1")
parser.add_argument("toys", help="Number of toys")
parser.add_argument("-n","--note", help="Note to add to filename")
parser.add_argument("-o","--out", help="Directory to save mlfit file")
parser.add_argument("-f","--fit", help="Fit the toys", action="store_true")
args = parser.parse_args()

sig = ["0","1"] if args.sig == "2" else [args.sig]

for isig in sig:
    for ijob in range(int(args.seed),int(args.seed)+int(args.toys)):
        command = "JobSubmit.csh ./Toys/wrapper.sh ./Toys/sendToyOnlyExp.py "+args.workspace+" "+str(ijob)+" "+isig+" 1"

        if args.note: command += " --note "+args.note
        if args.out: command += " --out "+args.out
        if args.fit: command += " -f"

#        print(command)
        os.system(command)

