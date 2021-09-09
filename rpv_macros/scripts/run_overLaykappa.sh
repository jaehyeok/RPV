for mode in {jer,jec,btag_bc,btag_udsg,mur,muf,murf,isr,gs,lep_eff,pileup};
do echo ${mode}
./run/plot_overLayOneKappa.exe ${mode} $1 &
done
