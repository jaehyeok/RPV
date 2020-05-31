for mode in {jes,btag_bc,btag_udsg,mur,muf,murf,isr};
do echo ${mode}
./run/plot_kappa.exe ${mode} Up 500 1400 &
./run/plot_kappa.exe ${mode} Down 500 1400 &
done
