#!/bin/sh
mjadd=900
for mjmin in 500 550 600 650 700 750 800 850 900 950 1000
	do 
		echo ${mjmin}
		mjmax=`expr ${mjmin} + ${mjadd}`
		./run/make_variations_loop_newntuple.exe nominal off ${mjmin} ${mjmax}
		./run/rescale_variations.exe mconly 
		./run/make_rpv_datacard_newbins.exe $1 mconly output_nominal_mconly.root
		python datacards/combine.py $1 
		mv results_$1/result.pdf results_$1/result_${mjmin}.pdf
	done
