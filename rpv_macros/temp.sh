#!/bin/sh
mjadd=900
for mjmin in 500 550 600 650 700 750 800 850 900 950 1000
	do 
		echo ${mjmin}
		mjmax=`expr ${mjmin} + ${mjadd}`
		./run/make_variations_loop_newntuple.exe nominal off ${mjmin} ${mjmax} 
		./run/make_rpv_datacard_newbins.exe 1600 mconly output_nominal_newnt.root
		python datacards/combine.py 1600 
		mv result.pdf result_${mjmin}.pdf
	done
