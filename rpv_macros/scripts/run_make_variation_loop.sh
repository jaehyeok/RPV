for mode in {nominal,jes,btag_bc,btag_udsg,mur,muf,murf,isr};
do echo ${mode}
./run/make_variations_loop_newntuple.exe ${mode} 500 1400 > log_make_variation_${mode}.txt &
done
