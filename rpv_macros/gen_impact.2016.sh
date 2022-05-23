#!/usr/bin/sh
for year in 2016 
  do
##	rm variations/output_syst_2016.root
##	rm -r impacts_${year}
##	mkdir impacts_${year}
##	./run/make_kappa_CRfit.exe off 500 1400 ${year}
#	./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year}
##	for syst in {kappa,mur,murf,muf,lep_eff,btag_udsg,btag_bc,isr,jec,jer,gs,pileup}; do
##		./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 ${year} > log.txt &  
##	done
##	./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year}
##	for syst in {kappa,mur,murf,muf,lep_eff,btag_udsg,btag_bc,isr,jec,jer,gs,pileup}; do
##		hadd -f -a variations/output_syst_${year}.root variations/output_${syst}_newnt_${year}.root
##	done
##	hadd -f variations/output_impact_${year}.root variations/output_nominal_newnt_${year}.root variations/output_syst_${year}.root 
##	python python/outputfix.py ${year}
#3	hadd -f variations/output_impact_${year}.root variations/output_nominal_newnt_${year}.root variations/output_syst_${year}.root variations/output_${year}_mckappa.root
	#hadd -f -a variations/output_impact_${year}.root variations/output_${year}_mckappa.root
##	cp variations/output_impact_${year}.root datacards/variations/output_impact_${year}.root



	for mass in 1500
		do
	      	./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}.root ${year} off on 
	      	combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb3_*_nopdfoutput_impact_${year}.dat > datacards/datacard_M${mass}_vr2_impact_${year}.dat
#	      	text2workspace.py datacards/datacard_M${mass}_vr2_impact_${year}.dat -m 125
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3   
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3  --parallel 60
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3 
#	      	plotImpacts.py -i impacts.json --per-page 140 -o impacts
#	      	mv impacts.pdf impacts_${year}/impacts_realdata_vr2_M${mass}.pdf
	      	combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*_nopdfoutput_impact_${year}.dat > datacards/datacard_M${mass}_vr_impact_${year}.dat
#	      combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*lownjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*mednjets*_impact_${year}.dat > datacards/datacard_M${mass}_vr_impact_${year}.dat
#	      	text2workspace.py datacards/datacard_M${mass}_vr_impact_${year}.dat -m 125
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3  
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3 --parallel 60
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3 
#	      	plotImpacts.py -i impacts.json --per-page 120 -o impacts
#	      	mv impacts.pdf impacts_${year}/impacts_realdata_vr_M${mass}.pdf
	      	combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*lownjets_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb1_*mednjets_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*lownjets_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*mednjets_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*lownjets_nopdfoutput_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*mednjets_nopdfoutput_impact_${year}.dat> datacards/datacard_M${mass}_cr_impact_${year}.dat
#	      	text2workspace.py datacards/datacard_M${mass}_cr_impact_${year}.dat -m 125 
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3 
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3 --parallel 60
#	      	combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3
#	      	plotImpacts.py -i impacts.json --per-page 60 -o impacts
#	      	mv impacts.pdf impacts_${year}/impacts_realdata_cr_M${mass}.pdf
  done
  mass=1500
  echo 'combining step 1 ::....'
  combine -M FitDiagnostics datacards/datacard_M${mass}_cr_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit 
  mv fitDiagnosticsTest.root fitDiagnostics_cr_${year}.root
  echo 'combining step 2 ::....'
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
  mv fitDiagnosticsTest.root fitDiagnostics_vr_${year}.root
  echo 'combining step 3 ::....'
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr2_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit
#  combine -M FitDiagnostics datacards/datacard_M${mass}_vr2_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --cminDefaultMinimizerStrategy 0
  mv fitDiagnosticsTest.root fitDiagnostics_vr2_${year}.root
  
done
