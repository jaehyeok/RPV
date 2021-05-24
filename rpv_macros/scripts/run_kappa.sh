for mode in {jec,btag_bc,btag_udsg,mur,muf,murf,isr,gs,jer,lep_eff};
do echo ${mode}
./run/plot_kappa.exe nominal X 500 1400 $1 &
./run/plot_kappa.exe ${mode} Up 500 1400 $1 &
./run/plot_kappa.exe ${mode} Down 500 1400 $1 &
done
