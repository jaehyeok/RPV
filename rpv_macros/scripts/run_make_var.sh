#!/bin/sh
year=$1
for syst in {mur,murf,muf,nominal};do
	echo ${syst}
	./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 $1 20178 > log/log_${syst}_$1.txt &
done
