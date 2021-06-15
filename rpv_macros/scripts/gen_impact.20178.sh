#!/usr/bin/sh
./run/make_kappa_CRfit.exe off 500 1400 20178
#rm -rf impacts_20178
#mkdir impacts_20178
for year in 2018 2017 
  do
  ./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year} 20178
  ./run/make_variations_loop_newntuple.exe kappa off 500 1400 ${year} 20178
  hadd -f variations/output_impact_${year}_20178.root variations/output_nominal_newnt_${year}_20178.root variations/output_kappa_newnt_${year}_20178.root
  cp variations/output_impact_${year}_20178.root datacards/variations/output_impact_${year}_20178.root
  for mass in 1500
    do
    ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_20178.root ${year} on off
    combineCards.py datacards/datacard_M${mass}_mconly_*_nb1_*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb2_*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb0_*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb3_*lownjets*_impact_${year}_20178.dat > datacards/datacard_M${mass}_vr2_impact_${year}_20178.dat
    combineCards.py datacards/datacard_M${mass}_mconly_*_nb1_*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb2_*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb0_*_impact_${year}_20178.dat > datacards/datacard_M${mass}_vr_impact_${year}_20178.dat
    combineCards.py datacards/datacard_M${mass}_mconly_cr_nb1_*lownjets*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_cr_nb1_*mednjets*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_cr_nb0_*lownjets*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_cr_nb0_*mednjets*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb2_*lownjets*_impact_${year}_20178.dat datacards/datacard_M${mass}_mconly_*_nb2_*mednjets*_impact_${year}_20178.dat > datacards/datacard_M${mass}_cr_impact_${year}_20178.dat
    done
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3 
  mv fitDiagnosticsTest.root fitDiagnostics_vr_${year}_20178.root
  combine -M FitDiagnostics datacards/datacard_M${mass}_cr_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3
  mv fitDiagnosticsTest.root fitDiagnostics_cr_${year}_20178.root
  combine -M FitDiagnostics datacards/datacard_M${mass}_vr2_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3 
  mv fitDiagnosticsTest.root fitDiagnostics_vr2_${year}_20178.root
done

crvr=$1
for mass in 1500; do
  cd datacards
  combineCards.py datacard_M${mass}_${crvr}_impact_2017_20178.dat datacard_M${mass}_${crvr}_impact_2018_20178.dat > datacard_M${mass}_${crvr}_impact_20178.dat
  cd -

  combine -M FitDiagnostics datacards/datacard_M${mass}_${crvr}_impact_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3
  text2workspace.py datacards/datacard_M${mass}_${crvr}_impact_20178.dat -m 125 
  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root --doInitialFit --robustFit 1 -m 125 --cminDefaultMinimizerType Minuit --rMin -3
  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root  -m 125 --robustFit 1 --doFits --parallel 60 --cminDefaultMinimizerType Minuit --rMin -3
  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root -m 125 -o impacts.json --cminDefaultMinimizerType Minuit --rMin -3
  plotImpacts.py -i impacts.json --per-page 60 -o impacts
  mv impacts.pdf impacts_20178/impacts_realdata_${crvr}_M${mass}.pdf
  mv fitDiagnosticsTest.root fitDiagnostics_${crvr}_20178.root
done
