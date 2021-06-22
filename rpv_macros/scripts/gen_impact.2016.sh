#!/usr/bin/sh
for year in 2016 
  do
#	  rm -r impacts_${year}
#	  mkdir impacts_${year}
#	  ./run/make_kappa_CRfit.exe off 500 1400 ${year}
#	  ./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year}
	  ./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year}
	  hadd -f variations/output_impact_${year}.root variations/output_nominal_newnt_${year}.root variations/output_kappa_newnt_${year}.root
	  cp variations/output_impact_${year}.root datacards/variations/output_impact_${year}.root
	  for mass in 1500
	    do
	      ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}.root ${year}
	      combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb3_*_impact_${year}.dat > datacards/datacard_M${mass}_vr2_impact_${year}.dat
	      text2workspace.py datacards/datacard_M${mass}_vr2_impact_${year}.dat -m 125
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3   
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3  --parallel 60
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr2_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3 
	      plotImpacts.py -i impacts.json --per-page 140 -o impacts
	      mv impacts.pdf impacts_${year}/impacts_realdata_vr2_M${mass}.pdf
	      combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*_impact_${year}.dat > datacards/datacard_M${mass}_vr_impact_${year}.dat
#	      combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*lownjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*mednjets*_impact_${year}.dat > datacards/datacard_M${mass}_vr_impact_${year}.dat
	      text2workspace.py datacards/datacard_M${mass}_vr_impact_${year}.dat -m 125
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3  
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3 --parallel 60
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_vr_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3 
	      plotImpacts.py -i impacts.json --per-page 120 -o impacts
	      mv impacts.pdf impacts_${year}/impacts_realdata_vr_M${mass}.pdf
	      combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*lownjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb1_*mednjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*lownjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_cr_nb0_*mednjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*lownjets*_impact_${year}.dat datacards/datacard_M${mass}_mconly_*_nb2_*mednjets*_impact_${year}.dat> datacards/datacard_M${mass}_cr_impact_${year}.dat
	      text2workspace.py datacards/datacard_M${mass}_cr_impact_${year}.dat -m 125 
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root --doInitialFit --robustFit 1 -m 125 --rMin -3 
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root  -m 125 --robustFit 1 --doFits --rMin -3 --parallel 60
	      combineTool.py -M Impacts -d datacards/datacard_M${mass}_cr_impact_${year}.dat.root -m 125 -o impacts.json --rMin -3
	      plotImpacts.py -i impacts.json --per-page 60 -o impacts
	      mv impacts.pdf impacts_${year}/impacts_realdata_cr_M${mass}.pdf
  done
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr2_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit2
  mv fitDiagnosticsTest.root fitDiagnostics_vr2_${year}.root
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit2
  mv fitDiagnosticsTest.root fitDiagnostics_vr_${year}.root
  combine -M FitDiagnostics datacards/datacard_M${mass}_cr_impact_${year}.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit2 
  mv fitDiagnosticsTest.root fitDiagnostics_cr_${year}.root
done
