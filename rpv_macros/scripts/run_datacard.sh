for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
do echo ${mass}
./run/make_rpv_datacard_newbins.exe ${mass} mconly output_$1.root $1
done

mkdir -p datacards/nopdfoutput_$1/

cp datacards/*mconly_nopdfoutput_$1.dat datacards/nopdfoutput_$1/.

for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
do echo ${mass}
combine -M AsymptoticLimits datacards/nopdfoutput_$1/datacard_M${mass}_mconly_nopdfoutput_$1.dat -n M${mass}
done

mv higgsCombineM*.AsymptoticLimits.mH120.root datacards/nopdfoutput_$1/.
