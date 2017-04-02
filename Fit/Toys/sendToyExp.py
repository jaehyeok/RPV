#! /usr/bin/env python
import argparse
import os

parser = argparse.ArgumentParser(description="Sends toys")
parser.add_argument("workspace", help="Path to workspace (also accepts datacards)")
parser.add_argument("seed", help="Seed to use")
parser.add_argument("mjcut", help="The high MJ threshold")
parser.add_argument("lumi", help="Luminosity")
parser.add_argument("sig", help="Expected signal")
parser.add_argument("toys", help="Number of toys")
parser.add_argument("-n","--note", help="Note to add to filename")
parser.add_argument("-o","--out", help="Directory to save mlfit file")
args = parser.parse_args()

tag = "_toys_lumi"+args.lumi+"_mj"+args.mjcut+"_sig"+args.sig+"_seed"+args.seed
if args.note: tag += "_"+args.note

os.system("cd ~/RPV/Fit/CMSSW_7_4_7_patch1/src/HiggsAnalysis/CombinedLimit/")
os.system(". /net/cms2/cms2r0/babymaker/cmsset_default.sh")

if args.out:
    os.system("eval `scramv1 runtime -sh`; combine -M MaxLikelihoodFit --expectSignal="+args.sig+" -t "+args.toys+" -s "+args.seed+" -n "+tag+" --minimizerTolerance 0.9999999 --toysNoSystematics --saveNorm --out "+args.out+" "+args.workspace)
else:
    os.system("eval `scramv1 runtime -sh`; combine -M MaxLikelihoodFit --expectSignal="+args.sig+" -t "+args.toys+" -s "+args.seed+" -n "+tag+" --minimizerTolerance 0.9999999 --toysNoSystematics --saveNorm "+args.workspace)
