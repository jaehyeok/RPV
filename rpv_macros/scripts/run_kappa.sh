for mode in {jec,jer,btag_bc,btag_udsg,mur,muf,murf,isr,gs,lep_eff,pileup};
do echo ${mode}
./run/plot_kappa.exe nominal X $1 variations/output_$1.root 
./run/plot_kappa.exe ${mode} Up $1 variations/output_$1.root 
./run/plot_kappa.exe ${mode} Down $1 variations/output_$1.root
done
