for mode in {jes,btag_bc,btag_udsg,mur,muf,murf,isr};
do echo ${mode}
./run/plot_multiKappa.exe ${mode} Up &
./run/plot_multiKappa.exe ${mode} Down &
done
