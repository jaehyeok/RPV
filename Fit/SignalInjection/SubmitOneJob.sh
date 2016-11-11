#!/bin/sh

# mkdir two directories 
# log: print out of fit result
# mlfit: mlfit.root files

echo " --------------------------------------------------- " 
echo "[RPV toys] Currect directory : " 
pwd 

echo " --------------------------------------------------- " 
echo "[RPV toys] Set env and move back to the batch node : "  
# change working directory
cd /afs/cern.ch/user/j/jaehyeok/work/RPV/CMSSW_7_4_7_patch1/src 
eval `scramv1 runtime -sh`
cd -
echo " --------------------------------------------------- " 
echo "[RPV toys] Current directory : " 
pwd 

WORKINGDIR=$CMSSW_BASE/src
MASS=$1
SEED=$2

echo " --------------------------------------------------- " 
echo "[RPV toys] SEED:$SEED, M=$MASS"

echo " --------------------------------------------------- " 
echo "[RPV toys] Run combine "

# Change the following as you wish 
# - expected signal by "expectSignal=xx"
# - path and name of datacards 
$CMSSW_BASE/bin/slc6_amd64_gcc491/combine -M MaxLikelihoodFit  --expectSignal=1 -t 1 --saveNormalizations --saveShapes -s $SEED -n M${MASS}_seed${SEED} $WORKINGDIR/datacards/nov7/datacard_M${MASS}_mconly_nopdf.dat > RPVtoys_M${MASS}_seed${SEED}.txt

echo " --------------------------------------------------- " 
echo "[RPV toys] Error code: $?"

echo " --------------------------------------------------- " 
echo "[RPV toys] Check if combine output has been generated and copy them to the appropriate directories " 
ls -lrt *M${MASS}*seed${SEED}* 

mv RPVtoys_M${MASS}_seed${SEED}.txt $WORKINGDIR/log 
mv mlfitM${MASS}_seed${SEED}.root $WORKINGDIR/mlfit
mv higgsCombineM${MASS}_seed${SEED}${TAG}.MaxLikelihoodFit.mH120.${SEED}.root $WORKINGDIR/mlfit
