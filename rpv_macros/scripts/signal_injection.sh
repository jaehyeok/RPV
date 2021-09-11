#!/usr/bin/sh

function run_combine(){
  card=`echo datacards/datacard_M${2}_mconly_nopdfoutput_SpB_M${2}.dat`
  #combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s ${1} --saveToys -n _M${2} --expectSignal=1 --toysFrequentist 
  combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s ${1} --saveToys -n _M${2}_${1} --expectSignal=1 --toysFrequentist 
  fitdiag=`echo fitDiagnostics_M${2}_${1}.root`
  fitdiag_aft=`echo fitDiagnostics_M${2}_s${1}.root`
  higcomb=`echo  higgsCombine_M${2}_${1}.FitDiagnostics.mH120.${1}.root`
  mv $fitdiag out_injection/$fitdiag_aft
  mv $higcomb out_injection  
}

th="30"

#./run/make_kappa_CRfit.exe on 500 1400 2016 137 
#./run/make_variations_loop_newntuple.exe nominal off 500 1400 2016 137
#./run/make_variations_loop_newntuple.exe kappa off 500 1400 2016 137
for mass in {1500,1600,1700,1800,1900,2000,2100,2200}; do
  ./run/rescale_variations.exe mconlySplusB variations/output_nominal_newnt_2016_137.root 2016 ${mass}
  hadd -f variations/output_SpB_M${mass}.root variations/output_nominal_newnt_2016_137_mconlySplusB.root variations/output_kappa_newnt_2016_137.root
  ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_SpB_M${mass}.root 2016 
  for x in {1..1000}; do
    j_count=`jobs -l|wc|awk '{print $1}'`
    if [[ $j_count -ge $th ]];then
      until [[ $j_count -lt $th ]] 
        do j_count=`jobs -l|wc|awk '{print $1}'`
	sleep 0.1
      done
    fi
    run_combine ${x} ${mass} & 	
  done
done
