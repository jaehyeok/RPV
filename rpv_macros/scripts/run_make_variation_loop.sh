mkdir -p log/
for mode in {nominal,JES,btag_bc,btag_udsg,mur,muf,murf,ISR,lep_eff};
do echo ${mode}
	if [ $1 = "2016" ]; then
		./run/make_variations_loop_newntuple.exe ${mode} off 500 1400 $1 > log/log_make_variation_${mode}.txt & #2016 or 20178
	else
		./run/make_variations_loop_newntuple.exe ${mode} off 500 1400 $1 20178 > log/log_make_variation_${mode}.txt & #2016 or 20178
	fi
done
