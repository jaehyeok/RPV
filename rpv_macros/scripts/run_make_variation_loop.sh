for mode in {nominal,JES,btag_bc,btag_udsg,mur,muf,murf,ISR,GS};
do echo ${mode}
./run/make_variations_loop_newntuple.exe ${mode} off 500 1400 $1 137 > log_make_variation_${mode}.txt &
done
