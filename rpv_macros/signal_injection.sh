#!/usr/bin/sh

function run_combine(){
  card=`echo datacards/datacard_M${2}_mconly_nopdfoutput_SpB_M${2}_201678.dat`
  combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s ${1} --saveToys -n _M${2}_${1} --expectSignal=1 --toysFrequentist --cminDefaultMinimizerType Minuit
  #combine -M FitDiagnostics $card --saveNorm --saveShapes -t 1 -s ${1} --saveToys -n _M${2}_${1} --expectSignal=1 --toysFrequentist --cminDefaultMinimizerType Minuit --cminDefaultMinimizerStrategy 0
  fitdiag=`echo fitDiagnostics_M${2}_${1}.root`
  fitdiag_aft=`echo fitDiagnostics_M${2}_${1}.root`
  higcomb=`echo  higgsCombine_M${2}_${1}.FitDiagnostics.mH120.${1}.root`
  mv $fitdiag out_injection_201678_231225/$fitdiag_aft
  mv $higcomb out_injection_201678_231225
}

th="15"

#./run/make_kappa_CRfit.exe on 500 1400 2016
#./run/make_variations_loop_newntuple.exe nominal off 500 1400 2016
#./run/make_variations_loop_newntuple.exe kappa off 500 1400 2016

for mass in {1500,1600,1700,1800,1900,2000,2100,2200}; do
echo ${mass}
#for mass in 1500; do
: << "END"
year=$1
  if [ ${year} -eq 2016 ]; then
	  echo ${year}
	  ./run/rescale_variations.exe mconlySplusB variations/output_nominal_newnt_${year}.root ${year} ${mass}
#	  hadd -f variations/output_SpB_M${mass}_${year}.root variations/output_nominal_newnt_${year}_mconlySplusB.root variations/output_syst_${year}.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root
	  hadd -f variations/output_SpB_M${mass}_${year}.root variations/output_nominal_newnt_${year}_mconlySplusB.root variations/output_syst_${year}.root variations/output_${year}_mckappa.root
#  hadd -f variations/output_SpB_M${mass}.root variations/output_nominal_newnt_2016_mconlySplusB.root variations/output_kappa_newnt_2016.root
  	  cp variations/output_SpB_M${mass}_${year}.root datacards/variations/
  	  ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_SpB_M${mass}_${year}.root ${year} off on
  fi

  if [ ${year} -eq 2017 -o ${year} -eq 2018 ]; then
	  echo ${year}
	  ./run/rescale_variations.exe mconlySplusB variations/output_nominal_newnt_${year}_20178.root ${year} ${mass}
#	  hadd -f variations/output_SpB_M${mass}_${year}.root variations/output_nominal_newnt_${year}_20178_mconlySplusB.root variations/output_syst_${year}_20178.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root
	  hadd -f variations/output_SpB_M${mass}_${year}.root variations/output_nominal_newnt_${year}_20178_mconlySplusB.root variations/output_syst_${year}_20178.root variations/output_${year}_mckappa.root
  	  cp variations/output_SpB_M${mass}_${year}.root datacards/variations/
  	  ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_SpB_M${mass}_${year}.root ${year} on on
  fi
END
#: << "END"
  for x in {1..1000}; do
#  for x in {1..100}; do
    j_count=`jobs -l|wc|awk '{print $1}'`
    if [[ $j_count -ge $th ]];then
      until [[ $j_count -lt $th ]] 
        do j_count=`jobs -l|wc|awk '{print $1}'`
	sleep 0.1
        done
    fi
    run_combine ${x} ${mass} & 	
  done
#END
done
