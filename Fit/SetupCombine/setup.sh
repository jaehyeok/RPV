#!/bin/sh

# combine twiki
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit

# Get CMSSW and combine tool
cmsrel CMSSW_7_4_7_patch1
CURRENT=$PWD
cd CMSSW_7_4_7_patch1/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git checkout 74x-root6
cd ../../ 

# Do some customization for RPV
cp $CURRENT/SetupCombine/FitterAlgoBase.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MaxLikelihoodFit.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MultiDimFit.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MultiDimFit.h HiggsAnalysis/CombinedLimit/interface/ 
cp $CURRENT/SetupCombine/RPVModel.py HiggsAnalysis/CombinedLimit/python

# Build the beast
scramv1 b -j 10
