#!/bin/sh

CURRENT=$PWD

# Get combine 
cmsrel CMSSW_7_4_7_patch1
cd CMSSW_7_4_7_patch1/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git checkout 74x-root6
cd ../../ 

#Do some customization 
cp $CURRENT/SetupCombine/FitterAlgoBase.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MaxLikelihoodFit.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MultiDimFit.cc HiggsAnalysis/CombinedLimit/src/ 
cp $CURRENT/SetupCombine/MultiDimFit.h HiggsAnalysis/CombinedLimit/interface/ 
cp $CURRENT/SetupCombine/RPVModel.py HiggsAnalysis/CombinedLimit/python
scramv1 b -j 10
