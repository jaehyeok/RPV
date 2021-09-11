#!/usr/bin/sh

#./run/make_kappa_CRfit.exe on 500 1400 2016
#./run/make_kappa_CRfit.exe on 500 1400 20178
#for syst in {kappa,gs,isr,lep_eff,btag_udsg,btag_bc,mur,murf,muf,jec,jer}
#do
#        ./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 2016 > log_var.log &
#        ./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 2017 20178  > log_var.log &
#        ./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 2018 20178  > log_var.log &
#done
#./run/make_variations_loop_newntuple.exe nominal off 500 1400 2016
#./run/make_variations_loop_newntuple.exe nominal off 500 1400 2017 20178
#./run/make_variations_loop_newntuple.exe nominal off 500 1400 2018 20178
#./run/rescale_variations.exe mconly variations/output_nominal_newnt_2016.root 2016
#./run/rescale_variations.exe mconly variations/output_nominal_newnt_2017_20178.root 2017
#./run/rescale_variations.exe mconly variations/output_nominal_newnt_2017_20178.root 2018
hadd -f variations/output_limit_2016.root variations/output_nominal_newnt_2016_mconly.root variations/output_kappa_newnt_2016.root variations/output_isr_newnt_2016.root variations/output_gs_newnt_2016.root variations/output_lep_eff_newnt_2016.root variations/output_btag_udsg_newnt_2016.root variations/output_btag_bc_newnt_2016.root variations/output_mur_newnt_2016.root variations/output_murf_newnt_2016.root variations/output_muf_newnt_2016.root variations/output_jec_newnt_2016.root variations/output_jer_newnt_2016.root
hadd -f variations/output_limit_2017.root variations/output_nominal_newnt_2017_20178_mconly.root variations/output_kappa_newnt_2017_20178.root variations/output_isr_newnt_2017_20178.root variations/output_gs_newnt_2017_20178.root variations/output_lep_eff_newnt_2017_20178.root variations/output_btag_udsg_newnt_2017_20178.root variations/output_btag_bc_newnt_2017_20178.root variations/output_mur_newnt_2017_20178.root variations/output_murf_newnt_2017_20178.root variations/output_muf_newnt_2017_20178.root variations/output_jec_newnt_2017_20178.root variations/output_jer_newnt_2017_20178.root
hadd -f variations/output_limit_2018.root variations/output_nominal_newnt_2018_20178_mconly.root variations/output_kappa_newnt_2018_20178.root variations/output_isr_newnt_2018_20178.root variations/output_gs_newnt_2018_20178.root variations/output_lep_eff_newnt_2018_20178.root variations/output_btag_udsg_newnt_2018_20178.root variations/output_btag_bc_newnt_2018_20178.root variations/output_mur_newnt_2018_20178.root variations/output_murf_newnt_2018_20178.root variations/output_muf_newnt_2018_20178.root variations/output_jec_newnt_2018_20178.root variations/output_jer_newnt_2018_20178.root
mkdir newbin
for mass in 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200; do
	for year in 2016 2017 2018;do
		echo ${year}
		if [ ${year} -eq 2016 ];
		then
        		./run/make_rpv_datacard_newbins.exe ${mass} mconly output_limit_${year}.root ${year} off off
		else
        		./run/make_rpv_datacard_newbins.exe ${mass} mconly output_limit_${year}.root ${year} on off
		fi

	done
	cd datacards
	combineCards.py datacard_M${mass}_mconly_nopdfoutput_limit_2016.dat datacard_M${mass}_mconly_nopdfoutput_limit_2017.dat datacard_M${mass}_mconly_nopdfoutput_limit_2018.dat > datacard_M${mass}_nopdfoutput_limit.dat
	cd -
	combine -M AsymptoticLimits datacards/datacard_M${mass}_nopdfoutput_limit.dat -n _M${mass}
        cp higgsCombine_M${mass}.AsymptoticLimits.mH120.root newbin/higgsCombine_M${mass}.AsymptoticLimits.mH120.root
done
root -q -b limits_new.cc
mv limits_tot_0225.pdf limits_mconly_new.pdf
