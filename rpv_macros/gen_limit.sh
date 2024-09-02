#!/usr/bin/sh

# do rescale
./run/rescale_variations.exe mconly variations/output_nominal_newnt_2016.root 2016 1800
./run/rescale_variations.exe mconly variations/output_nominal_newnt_2017_20178.root 2017 1800
./run/rescale_variations.exe mconly variations/output_nominal_newnt_2018_20178.root 2018 1800

# get impact output files
hadd -f variations/output_impact_2016_rescale.root variations/output_nominal_newnt_2016_mconly.root variations/output_syst_2016.root variations/output_2016_mckappa.root variations/output_2016_mjsyst.root variations/output_2016_unc_dy.root
hadd -f variations/output_impact_2017_20178_rescale.root variations/output_nominal_newnt_2017_20178_mconly.root variations/output_syst_2017_20178.root variations/output_2017_mckappa.root variations/output_2017_mjsyst.root variations/output_2017_unc_dy.root
hadd -f variations/output_impact_2018_20178_rescale.root variations/output_nominal_newnt_2018_20178_mconly.root variations/output_syst_2018_20178.root variations/output_2018_mckappa.root variations/output_2018_mjsyst.root variations/output_2018_unc_dy.root

# make jer symmetry for other and signal processes
./run/make_jer_symm.exe 2016 variations/output_impact_2016_rescale.root
./run/make_jer_symm.exe 2017 variations/output_impact_2017_20178_rescale.root
./run/make_jer_symm.exe 2018 variations/output_impact_2018_20178_rescale.root

# copy output files to datacards/variations folder
cp variations/output_impact_2016_rescale.root datacards/variations
cp variations/output_impact_2017_20178_rescale.root datacards/variations
cp variations/output_impact_2018_20178_rescale.root datacards/variations

# make datacards
for year in 2016; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_rescale.root ${year} off on
    done
done
for year in 2017; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_20178_rescale.root ${year} on on
    done
done
for year in 2018; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_20178_rescale.root ${year} on on
    done
done

# do combineCards
for mass in {1000..2200..100}; do
   combineCards.py datacards/datacard_M${mass}_mconly_nopdfoutput_impact_2016_rescale.dat datacards/datacard_M${mass}_mconly_nopdfoutput_impact_2017_20178_rescale.dat datacards/datacard_M${mass}_mconly_nopdfoutput_impact_2018_20178_rescale.dat > datacards/datacard_M${mass}_mconly_nopdfoutput_impact_201678_rescale.dat
done

# do combine
for mass in {1000..2200..100}; do
    echo ${mass}
    combine -M AsymptoticLimits datacards/datacard_M${mass}_mconly_nopdfoutput_impact_201678_rescale.dat
    mv higgsCombineTest.AsymptoticLimits.mH120.root newbin_240606/higgsCombine_M${mass}.AsymptoticLimits.mH120.root
done

# Then run limits_new.cc
