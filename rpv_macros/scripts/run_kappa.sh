for mode in {JES,btag_bc,btag_udsg,mur,muf,murf,ISR};
do echo ${mode}
./run/plot_kappa.exe ${mode} Up 500 1400 $1 variations/output_newnt_nl0shape_$1.root &
./run/plot_kappa.exe ${mode} Down 500 1400 $1 variations/output_newnt_nl0shape_$1.root &
done
