#!/usr/bin/sh

if [ $1 = "20178" ]
	then
	years=("2017" "2018")
else
	years=($1)
fi
mconly=$2

for year in ${years[@]}
	do
	if [ $1 = "20178" ]
		then
		./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year} 20178
		./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year} 20178
		rm variations/output_syst_${year}_20178.root
		for syst in {kappa,jer,jec,btag_bc,btag_udsg,mur,murf,muf,gs,lep_eff,pileup}; do
    			hadd -a -f variations/output_syst_${year}_20178.root variations/output_${syst}_newnt_${year}_20178.root
  		done
	else
		./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year}
		./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year}
		rm variations/output_syst_${year}.root
		for syst in {kappa,mur,murf,muf,lep_eff,btag_udsg,btag_bc,jec,jer,gs,pileup}; do
          	      hadd -f -a variations/output_syst_${year}.root variations/output_${syst}_newnt_${year}.root
  	        done
	fi
	if [ ${mconly} = "on" ]
		then
		echo "MConly mode on"
		if [ $1 = "20178" ]
			then
			echo "./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_20178.root"
			./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_20178.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_20178_mconly.root variations/output_kappa_newnt_${year}_20178.root
		else
			./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_mconly.root variations/output_kappa_newnt_${year}.root
		fi
	else
		echo "Using Real Data"
		if [ $1 = "20178" ]
			then
			#hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_20178.root variations/output_kappa_newnt_${year}_20178.root
			rm variations/output_CRFit_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_20178.root variations/output_syst_${year}_20178.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root variations/output_${year}_unc_dy.root
			./run/make_jer_symm.exe ${year} variations/output_CRFit_${year}.root
		else
			#hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}.root variations/output_kappa_newnt_${year}.root
			rm variations/output_CRFit_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}.root variations/output_syst_${year}.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root variations/output_${year}_unc_dy.root
			./run/make_jer_symm.exe ${year} variations/output_CRFit_${year}.root
		fi
	fi
	cp variations/output_CRFit_${year}.root datacards/variations/output_CRFit_${year}.root
	if [ $1 = "20178" ]
		then
		#./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} on off
		./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} on on
		combineCards.py datacards/datacard_M1800_mconly_cr_nb0_*_CRFit_${year}.dat datacards/datacard_M1800_mconly_cr_nb1_*_CRFit_${year}.dat > datacards/datacard_M1800_CRFit_${year}.dat
	else
		#./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} off off 
		./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} off on
		combineCards.py datacards/datacard_M1800_mconly_cr_nb0_*_CRFit_${year}.dat datacards/datacard_M1800_mconly_cr_nb1_*_CRFit_${year}.dat > datacards/datacard_M1800_CRFit_${year}.dat
		combine -M FitDiagnostics datacards/datacard_M1800_CRFit_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
		root -l -q repack.C\(\"CRFit_${year}\"\)
	fi
done
if [ $1 = "20178" ]
	then
	cd datacards
	combineCards.py datacard_M1800_CRFit_2017.dat datacard_M1800_CRFit_2018.dat > datacard_M1800_CRFit_20178.dat
	cd - 
	combine -M FitDiagnostics datacards/datacard_M1800_CRFit_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
	root -l -q repack.C\(\"CRFit_20178\"\)
fi
