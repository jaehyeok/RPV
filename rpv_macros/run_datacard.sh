for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000}
do echo ${mass}
./run/make_rpv_datacard_newbins.exe ${mass} mconly output_newnt.root
done
