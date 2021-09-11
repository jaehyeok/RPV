#!/usr/bin/sh

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}; do
	combine -M FitDiagnostics datacards/datacard_M${mass}_mconly_nopdfoutput_SpB_M${mass}.dat > sinjection_M${mass}.txt &
done
