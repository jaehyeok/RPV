#! /usr/bin/env python
import argparse
import os

parser = argparse.ArgumentParser(description="Sends toys")
parser.add_argument("workspace", help="Path to workspace (also accepts datacards)")
parser.add_argument("seed", help="Seed to start with. Seed is incremented by 1 for every toy after.")
parser.add_argument("mjcut", help="The high MJ threshold")
parser.add_argument("lumi", help="Luminosity")
parser.add_argument("sig", help="Expected signal")
parser.add_argument("toys", help="Number of toys")
parser.add_argument("-n","--note", help="Note to add to filename")
parser.add_argument("-o","--out", help="Directory to save mlfit file")
args = parser.parse_args()

for i in range(int(args.seed),int(args.seed)+int(args.toys)):
    command = "JobSubmit.csh ./wrapper.sh ./sendToyExp.py "+args.workspace+" "+str(i)+" "+args.mjcut+" "+args.lumi+" "+args.sig+" 1"

    if args.note: command += " --note "+args.note
    if args.out: command += " --out "+args.out

    #print(command)
    os.system(command)

