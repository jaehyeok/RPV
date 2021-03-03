mkdir -p datacards/nopdfoutput_tot

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
#for mass in {1700,1800}
do echo "${mass} GeV..."

cp datacards/datacard_M${mass}_mconly_nopdfoutput_*.dat .

combineCards.py datacard_M${mass}_mconly_nopdfoutput_*.dat > total_M${mass}.dat

rm datacard_M${mass}_mconly_nopdfoutput_*.dat

combine -M AsymptoticLimits total_M${mass}.dat -n M${mass}

done

mv total_*.dat datacards/nopdfoutput_tot/.
mv higgsCombineM*.AsymptoticLimits.mH120.root datacards/nopdfoutput_tot/.
