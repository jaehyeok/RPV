#! /usr/bin/env python
import argparse
import os

parser = argparse.ArgumentParser(description="Sends toys")
parser.add_argument("workspace", help="Path to workspace/datacard")
parser.add_argument("seed", help="Seed to use")
parser.add_argument("sig", help="Expected signal")
parser.add_argument("toys", help="Number of toys")
parser.add_argument("-n","--note", help="Note to add to filename")
parser.add_argument("-o","--out", help="Directory to save mlfit file")
parser.add_argument("-f","--fit", help="Fit after generating toy", action="store_true")
args = parser.parse_args()

tag = "_sig"+args.sig+"_seed"+args.seed
if args.note: tag += "_"+args.note

os.chdir("/net/top/homes/rohan/RPV/Fit/CMSSW_7_4_7_patch1/src/HiggsAnalysis/CombinedLimit/")
os.system(". /net/cms2/cms2r0/babymaker/cmsset_default.sh")

freezeNuisances = '--freezeNuisances normqcd_vlownjets,normqcd_lownjets,normqcd_mednjets,normqcd_highnjets,normtt_lownjets,normtt_mednjets,normtt_highnjets,normqcd_bin0_bin3,normqcd_bin1_2_bin4_5,normqcd_bin16_11_bin17_14,normqcd_bin17_14_bin18_20,normqcd_bin10_12_bin13_15,normqcd_bin13_15_bin19_21,normtt_bin0_1_2_bin3_4_5,normtt_bin16_11_bin17_14,normtt_bin17_14_bin18_20,normtt_bin10_12_bin13_15,normtt_bin13_15_bin19_21,normwjets,normwjets_mednjets,normwjets_highnjets'

os.system("eval `scramv1 runtime -sh`; combine -M GenerateOnly --saveToys -t "+args.toys+" -s "+args.seed+" --expectSignal="+args.sig+" -n "+tag+" "+freezeNuisances+" "+args.workspace)

if args.fit:
    os.system("eval `scramv1 runtime -sh`; combine -M MaxLikelihoodFit --minimizerTolerance 0.9999999 --saveNorm -t "+args.toys+" --toysFile higgsCombine"+tag+".GenerateOnly.mH120."+args.seed+".root "+args.workspace+" --out "+args.out+" -n "+tag)

os.system("mv *"+tag+"* "+args.out)
