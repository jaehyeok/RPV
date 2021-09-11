#!/bin/sh
mjadd=900

trap 'rm -rf comb_comp.C;exit' SIGINT

for mass in 1600 1700 1800 1900 2000
do
	rm -rf results_${mass}_16
	mkdir results_${mass}_16
done
for mjmin in 500 550 600 650 700 750 800 850 900 950 1000
	do 
		echo ${mjmin}
		mjmax=`expr ${mjmin} + ${mjadd}`
		./run/make_variations_loop_newntuple.exe nominal off ${mjmin} ${mjmax} 2016 137
		./run/rescale_variations.exe mconly variations/output_nominal_newnt_2016_137.root
    ./run/make_kappa.exe on ${mjmin} ${mjmax} 2016 137 
		./run/make_variations_loop_newntuple.exe kappa off ${mjmin} ${mjmax} 2016 137
		hadd -f variations/output_newnt_2016_${mjmin}.root variations/output_nominal_newnt_2016_137_mconly.root variations/output_kappa_newnt_2016_137.root
		for mass in 1600 1700 1800 1900 2000
		do
			./run/make_rpv_datacard_newbins.exe ${mass} mconly output_newnt_2016_${mjmin}.root 2016
			python datacards/combine.py ${mass} output_newnt_2016_${mjmin}
			python make_combine_plot.py ${mass} ${mjmin}
			mv result.pdf results_${mass}_16/result_${mjmin}.pdf
			mv result.root results_${mass}_16/result_${mjmin}.root
		done
    mkdir datacards/datacard_legacy_${mjmin}
    mv datacards/datacard_*.dat datacards/datacard_legacy_${mjmin}/
	done

root -l comb_comp.C
