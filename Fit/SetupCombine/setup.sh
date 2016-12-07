#!/bin/sh

# combine twiki
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit

# Get CMSSW and combine tool
export SCRAM_ARCH=slc6_amd64_gcc491
cmsrel CMSSW_7_4_7
CURRENT=$PWD
cd CMSSW_7_4_7/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v6.3.0
cd ../../ 

# Do some customization for RPV (Note: These files are for the 2015 Fit Model)
#cp $CURRENT/SetupCombine/FitterAlgoBase.cc HiggsAnalysis/CombinedLimit/src/
#cp $CURRENT/SetupCombine/MaxLikelihoodFit.cc HiggsAnalysis/CombinedLimit/src/
#cp $CURRENT/SetupCombine/MultiDimFit.cc HiggsAnalysis/CombinedLimit/src/
#cp $CURRENT/SetupCombine/MultiDimFit.h HiggsAnalysis/CombinedLimit/interface/
#cp $CURRENT/SetupCombine/RPVModel.py HiggsAnalysis/CombinedLimit/python/

# Build the beast
scramv1 b clean
scramv1 b -j 10
