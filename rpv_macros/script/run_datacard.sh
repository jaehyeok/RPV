cd ..

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
do echo ${mass}
./run/make_rpv_datacard_newbins.exe ${mass} mconly output_newnt.root
done

mkdir -p datacards/nopdfoutput_newnt/

cp datacards/*mconly_nopdfoutput_newnt.dat datacards/nopdfoutput_newnt/.

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
do echo ${mass}
mv datacards/nopdfoutput_newnt/datacard_M${mass}_mconly_nopdfoutput_newnt.dat datacards/nopdfoutput_newnt/datacard_M${mass}.dat
done

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
do echo ${mass}
combine -M AsymptoticLimits datacards/nopdfoutput_newnt/datacard_M${mass}.dat -n M${mass}
done

mv higgsCombineM*.AsymptoticLimits.mH120.root datacards/nopdfoutput_newnt/.
