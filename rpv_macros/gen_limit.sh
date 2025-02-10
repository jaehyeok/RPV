#!/usr/bin/sh
#: << "END"

# do rescale
echo "...do rescale"
./run/rescale_variations.exe mconly variations/output_nominal_newnt_UL2016_preVFP_UL2016.root UL2016_preVFP 1800
./run/rescale_variations.exe mconly variations/output_nominal_newnt_UL2016_postVFP_UL2016.root UL2016_postVFP 1800
./run/rescale_variations.exe mconly variations/output_nominal_newnt_UL2017_UL20178.root UL2017 1800
./run/rescale_variations.exe mconly variations/output_nominal_newnt_UL2018_UL20178.root UL2018 1800

# remove previous impact output files
echo "...remove previous impact output files"
rm variations/output_impact_UL2016_preVFP_UL2016_rescale.root
rm variations/output_impact_UL2016_postVFP_UL2016_rescale.root
rm variations/output_impact_UL2017_UL20178_rescale.root
rm variations/output_impact_UL2018_UL20178_rescale.root

# get impact output files
echo "...get impact output files"
hadd -f variations/output_impact_UL2016_preVFP_UL2016_rescale.root variations/output_nominal_newnt_UL2016_preVFP_UL2016_mconly.root variations/output_syst_UL2016_preVFP_UL2016.root variations/output_UL2016_preVFP_mckappa.root variations/output_UL2016_preVFP_mjsyst.root variations/output_UL2016_preVFP_unc_dy.root
hadd -f variations/output_impact_UL2016_postVFP_UL2016_rescale.root variations/output_nominal_newnt_UL2016_postVFP_UL2016_mconly.root variations/output_syst_UL2016_postVFP_UL2016.root variations/output_UL2016_postVFP_mckappa.root variations/output_UL2016_postVFP_mjsyst.root variations/output_UL2016_postVFP_unc_dy.root
hadd -f variations/output_impact_UL2017_UL20178_rescale.root variations/output_nominal_newnt_UL2017_UL20178_mconly.root variations/output_syst_UL2017_UL20178.root variations/output_UL2017_mckappa.root variations/output_UL2017_mjsyst.root variations/output_UL2017_unc_dy.root
hadd -f variations/output_impact_UL2018_UL20178_rescale.root variations/output_nominal_newnt_UL2018_UL20178_mconly.root variations/output_syst_UL2018_UL20178.root variations/output_UL2018_mckappa.root variations/output_UL2018_mjsyst.root variations/output_UL2018_unc_dy.root

# make jer symmetric for other and signal processes
echo "...make jer symmetric for other and signal processes"
./run/make_jer_symm.exe UL2016_preVFP variations/output_impact_UL2016_preVFP_UL2016_rescale.root
./run/make_jer_symm.exe UL2016_postVFP variations/output_impact_UL2016_postVFP_UL2016_rescale.root
./run/make_jer_symm.exe UL2017 variations/output_impact_UL2017_UL20178_rescale.root
./run/make_jer_symm.exe UL2018 variations/output_impact_UL2018_UL20178_rescale.root

# copy output files to datacards/variations folder
echo "...copy output files to datacards/variations folder"
cp variations/output_impact_UL2016_preVFP_UL2016_rescale.root datacards/variations
cp variations/output_impact_UL2016_postVFP_UL2016_rescale.root datacards/variations
cp variations/output_impact_UL2017_UL20178_rescale.root datacards/variations
cp variations/output_impact_UL2018_UL20178_rescale.root datacards/variations

# make datacards
echo "...make datacards"
for year in UL2016_preVFP; do
echo "......UL2016_preVFP"
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_UL2016_rescale.root ${year} UL2016 on
    done
done
echo "......UL2016_postVFP"
for year in UL2016_postVFP; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_UL2016_rescale.root ${year} UL2016 on
    done
done
echo "......UL2017"
for year in UL2017; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_UL20178_rescale.root ${year} UL20178 on
    done
done
echo "......UL2018"
for year in UL2018; do
    for mass in {1000..2200..100}; do
        echo ${year} ${mass}
        ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_UL20178_rescale.root ${year} UL20178 on
    done
done
#END
# do combineCards
echo "...do combineCards"
for mass in {1000..2200..100}; do
   combineCards.py datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL2016_preVFP_UL2016_rescale.dat datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL2016_postVFP_UL2016_rescale.dat datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL2017_UL20178_rescale.dat datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL2018_UL20178_rescale.dat > datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL201678_rescale.dat
done

# do combine
echo "...do combine"
for mass in {1000..2200..100}; do
    echo ${mass}
    combine -M AsymptoticLimits datacards/datacard_M${mass}_mconly_nopdfoutput_impact_UL201678_rescale.dat
    mv higgsCombineTest.AsymptoticLimits.mH120.root newbin_250122/higgsCombine_M${mass}.AsymptoticLimits.mH120.root
done

# Then run limits_new.cc
