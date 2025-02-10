#!/usr/bin/sh

if [ $1 = "UL2016" ]
	then
	years=("UL2016_preVFP" "UL2016_postVFP")
elif [ $1 = "UL20178" ]
	then
	years=("UL2017" "UL2018")
else
	years=($1)
fi
mconly=$2

for year in ${years[@]}
	do
	if [ $1 = "UL2016" ]
		then
		./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year} UL2016
		./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year} UL2016
		rm variations/output_syst_${year}_UL2016.root
		#for syst in {kappa,jer,jec,btag_bc,btag_udsg,mur,murf,muf,gs,lep_eff,pileup}; do
    			#hadd -a -f variations/output_syst_${year}_UL2016.root variations/output_${syst}_newnt_${year}_UL2016.root
  		#done
    		hadd -f variations/output_syst_${year}_UL2016.root variations/output_kappa_newnt_${year}_UL2016.root variations/output_jer_newnt_${year}_UL2016.root variations/output_jec_newnt_${year}_UL2016.root variations/output_btag_bc_uncor_newnt_${year}_UL2016.root variations/output_btag_bc_cor_newnt_${year}_UL2016.root variations/output_btag_udsg_uncor_newnt_${year}_UL2016.root variations/output_btag_udsg_cor_newnt_${year}_UL2016.root variations/output_mur_newnt_${year}_UL2016.root variations/output_murf_newnt_${year}_UL2016.root variations/output_muf_newnt_${year}_UL2016.root variations/output_gs_newnt_${year}_UL2016.root variations/output_lep_eff_newnt_${year}_UL2016.root variations/output_pileup_newnt_${year}_UL2016.root
	elif [ $1 = "UL20178" ]
		then
		./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year} UL20178
		./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year} UL20178
		rm variations/output_syst_${year}_UL20178.root
		#for syst in {kappa,jer,jec,btag_bc,btag_udsg,mur,murf,muf,gs,lep_eff,pileup}; do
    			#hadd -a -f variations/output_syst_${year}_UL20178.root variations/output_${syst}_newnt_${year}_UL20178.root
  		#done
    		hadd -f variations/output_syst_${year}_UL20178.root variations/output_kappa_newnt_${year}_UL20178.root variations/output_jer_newnt_${year}_UL20178.root variations/output_jec_newnt_${year}_UL20178.root variations/output_btag_bc_uncor_newnt_${year}_UL20178.root variations/output_btag_bc_cor_newnt_${year}_UL20178.root variations/output_btag_udsg_uncor_newnt_${year}_UL20178.root variations/output_btag_udsg_cor_newnt_${year}_UL20178.root variations/output_mur_newnt_${year}_UL20178.root variations/output_murf_newnt_${year}_UL20178.root variations/output_muf_newnt_${year}_UL20178.root variations/output_gs_newnt_${year}_UL20178.root variations/output_lep_eff_newnt_${year}_UL20178.root variations/output_pileup_newnt_${year}_UL20178.root
	else
		./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year}
		./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year}
		rm variations/output_syst_${year}.root
		#for syst in {kappa,mur,murf,muf,lep_eff,btag_udsg,btag_bc,jec,jer,gs,pileup}; do
          	#      hadd -f -a variations/output_syst_${year}.root variations/output_${syst}_newnt_${year}.root
  	        #done
    		hadd -f variations/output_syst_${year}.root variations/output_kappa_newnt_${year}.root variations/output_jer_newnt_${year}.root variations/output_jec_newnt_${year}.root variations/output_btag_bc_uncor_newnt_${year}.root variations/output_btag_bc_cor_newnt_${year}.root variations/output_btag_udsg_uncor_newnt_${year}.root variations/output_btag_udsg_cor_newnt_${year}.root variations/output_mur_newnt_${year}.root variations/output_murf_newnt_${year}.root variations/output_muf_newnt_${year}.root variations/output_gs_newnt_${year}.root variations/output_lep_eff_newnt_${year}.root variations/output_pileup_newnt_${year}.root
	fi
	if [ ${mconly} = "on" ]
		then
		echo "MConly mode on"
		if [ $1 = "UL2016" ]
			then
			echo "./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_UL2016.root"
			./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_UL2016.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_UL2016_mconly.root variations/output_kappa_newnt_${year}_UL2016.root
		elif [ $1 = "UL20178" ]
			then
			echo "./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_UL20178.root"
			./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}_UL20178.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_UL20178_mconly.root variations/output_kappa_newnt_${year}_UL20178.root
		else
			./run/rescale_variations_kappa.exe mconly variations/output_nominal_newnt_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_mconly.root variations/output_kappa_newnt_${year}.root
		fi
	else
		echo "Using Real Data"
		if [ $1 = "UL2016" ]
			then
			rm variations/output_CRFit_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_UL2016.root variations/output_syst_${year}_UL2016.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root variations/output_${year}_unc_dy.root
			./run/make_jer_symm.exe ${year} variations/output_CRFit_${year}.root
		elif [ $1 = "UL20178" ]
			then
			rm variations/output_CRFit_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}_UL20178.root variations/output_syst_${year}_UL20178.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root variations/output_${year}_unc_dy.root
			./run/make_jer_symm.exe ${year} variations/output_CRFit_${year}.root
		else
			rm variations/output_CRFit_${year}.root
			hadd -f variations/output_CRFit_${year}.root variations/output_nominal_newnt_${year}.root variations/output_syst_${year}.root variations/output_${year}_mckappa.root variations/output_${year}_mjsyst.root variations/output_${year}_unc_dy.root
			./run/make_jer_symm.exe ${year} variations/output_CRFit_${year}.root
		fi
	fi
	cp variations/output_CRFit_${year}.root datacards/variations/output_CRFit_${year}.root
	if [ $1 = "UL2016" ]
		then
		./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} UL2016 on
		combineCards.py datacards/datacard_M1800_mconly_cr_nb0_*_CRFit_${year}.dat datacards/datacard_M1800_mconly_cr_nb1_*_CRFit_${year}.dat > datacards/datacard_M1800_CRFit_${year}.dat
	elif [ $1 = "UL20178" ]
		then
		./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} UL20178 on
		combineCards.py datacards/datacard_M1800_mconly_cr_nb0_*_CRFit_${year}.dat datacards/datacard_M1800_mconly_cr_nb1_*_CRFit_${year}.dat > datacards/datacard_M1800_CRFit_${year}.dat
	else
		./run/make_rpv_datacard_newbins_CRfit.exe 1800 mconly output_CRFit_${year}.root ${year} off on
		combineCards.py datacards/datacard_M1800_mconly_cr_nb0_*_CRFit_${year}.dat datacards/datacard_M1800_mconly_cr_nb1_*_CRFit_${year}.dat > datacards/datacard_M1800_CRFit_${year}.dat
		combine -M FitDiagnostics datacards/datacard_M1800_CRFit_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
		root -l -q repack.C\(\"CRFit_${year}\"\)
	fi
done
if [ $1 = "UL2016" ]
	then
	cd datacards
	combineCards.py datacard_M1800_CRFit_UL2016_preVFP.dat datacard_M1800_CRFit_UL2016_postVFP.dat > datacard_M1800_CRFit_UL2016.dat
	cd - 
	combine -M FitDiagnostics datacards/datacard_M1800_CRFit_UL2016.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
	root -l -q repack.C\(\"CRFit_UL2016\"\)
elif [ $1 = "UL20178" ]
	then
	cd datacards
	combineCards.py datacard_M1800_CRFit_UL2017.dat datacard_M1800_CRFit_UL2018.dat > datacard_M1800_CRFit_UL20178.dat
	cd - 
	combine -M FitDiagnostics datacards/datacard_M1800_CRFit_UL20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
	root -l -q repack.C\(\"CRFit_UL20178\"\)
fi
