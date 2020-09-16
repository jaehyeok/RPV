for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
#for mass in {300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400}
do echo ${mass}
./run/make_rpv_datacard_newbins.exe ${mass} mconly output_$1.root
done

mkdir -p datacards/nopdfoutput_$1/

cp datacards/*mconly_nopdfoutput_$1.dat datacards/nopdfoutput_$1/.

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
#for mass in {300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400}
do echo ${mass}
mv datacards/nopdfoutput_$1/datacard_M${mass}_mconly_nopdfoutput_$1.dat datacards/nopdfoutput_$1/datacard_M${mass}.dat
done

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
#for mass in {300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1050,1100,1150,1200,1250,1300,1350,1400}
do echo ${mass}
combine -M AsymptoticLimits datacards/nopdfoutput_$1/datacard_M${mass}.dat -n M${mass}
done

mv higgsCombineM*.AsymptoticLimits.mH120.root datacards/nopdfoutput_$1/.
#cp ../Fit/limits.cc datacards/nopdfoutput_$1/.
