#!/bin/sh


#for mass in {1500,1600,1700,1800,1900,2000,2100,2200}; do
#for x in {1..10}; do
#for mass in {1500,1600}; do
  mass=1500
  for x in {1..100}; do
    card=`echo datacards/datacard_M${mass}_cr_impact_2016.dat`
    combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s $x --saveToys -n _M${mass} --expectSignal=0 --toysFrequentist
    fitdiag=`echo fitDiagnostics_M${mass}.root`
    higcomb=`echo  higgsCombine_M${mass}.FitDiagnostics.mH120.${x}.root`
    mv $fitdiag out_injection_step1/fitDiagnostics_M${mass}_16_${x}.root
    rm $higcomb
  done

#  for x in {1..100}; do
#    card=`echo datacards/datacard_M${mass}_vr_impact_20178.dat`
#    combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s $x --saveToys -n _M${mass} --expectSignal=0 --toysFrequentist
#    fitdiag=`echo fitDiagnostics_M${mass}.root`
#    higcomb=`echo  higgsCombine_M${mass}.FitDiagnostics.mH120.${x}.root`
#    mv $fitdiag out_injection_step2/fitDiagnostics_M${mass}_78_${x}.root
#    rm $higcomb
#  done

#done



