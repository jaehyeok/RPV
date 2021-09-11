#!/usr/bin/sh
#./run/make_kappa_CRfit.exe off 500 1400 20178
#rm -rf impacts_20178
mkdir impacts_20178
for year in 2018 2017;do
#  for syst in {kappa,jer,jec,btag_bc,btag_udsg,mur,murf,muf,gs,isr,lep_eff}; do
#    echo ${syst}
#    ./run/make_variations_loop_newntuple.exe ${syst} off 500 1400 ${year} 20178 > log/log_${syst}_var.txt &
#  done
#  ./run/make_variations_loop_newntuple.exe nominal off 500 1400 ${year} 20178
#  rm variations/output_syst_${year}_20178.root
#  sleep 5m
#  for syst in {kappa,jer,jec,btag_bc,btag_udsg,mur,murf,muf,gs,isr,lep_eff}; do
#    echo ${syst}
#    hadd -a -f variations/output_syst_${year}_20178.root variations/output_${syst}_newnt_${year}_20178.root
#  done
#  hadd -f variations/output_impact_${year}_20178.root variations/output_nominal_newnt_${year}_20178.root variations/output_syst_${year}_20178.root
  for mass in 1500 
    do
    ./run/make_rpv_datacard_newbins.exe ${mass} mconly output_impact_${year}_20178.root ${year} on off
    cd datacards
    combineCards.py datacard_M${mass}_mconly_*_nb1_*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb2_*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb0_*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb3_*lownjets*_impact_${year}_20178.dat > datacard_M${mass}_vr2_impact_${year}_20178.dat
    combineCards.py datacard_M${mass}_mconly_*_nb1_*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb2_*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb0_*_impact_${year}_20178.dat > datacard_M${mass}_vr_impact_${year}_20178.dat
    combineCards.py datacard_M${mass}_mconly_cr_nb1_*lownjets*_impact_${year}_20178.dat datacard_M${mass}_mconly_cr_nb1_*mednjets*_impact_${year}_20178.dat datacard_M${mass}_mconly_cr_nb0_*lownjets*_impact_${year}_20178.dat datacard_M${mass}_mconly_cr_nb0_*mednjets*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb2_*lownjets*_impact_${year}_20178.dat datacard_M${mass}_mconly_*_nb2_*mednjets*_impact_${year}_20178.dat > datacard_M${mass}_cr_impact_${year}_20178.dat
    cd -
    done
  #combine -M FitDiagnostics datacards/datacard_M${mass}_vr_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3 
  #mv fitDiagnosticsTest.root fitDiagnostics_vr_${year}_20178.root
  #combine -M FitDiagnostics datacards/datacard_M${mass}_cr_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3
  #mv fitDiagnosticsTest.root fitDiagnostics_cr_${year}_20178.root
  #combine -M FitDiagnostics datacards/datacard_M${mass}_vr2_impact_${year}_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit --rMin -3 
  #mv fitDiagnosticsTest.root fitDiagnostics_vr2_${year}_20178.root
done

crvr=$1
for mass in 1500; do
  cd datacards
  combineCards.py datacard_M${mass}_${crvr}_impact_2017_20178.dat datacard_M${mass}_${crvr}_impact_2018_20178.dat > datacard_M${mass}_${crvr}_impact_20178.dat
  cd -

  combine -M FitDiagnostics datacards/datacard_M${mass}_${crvr}_impact_20178.dat --saveNorm --saveShape --cminDefaultMinimizerType Minuit 
#  text2workspace.py datacards/datacard_M${mass}_${crvr}_impact_20178.dat -m 125 
#  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root --doInitialFit --robustFit 1 -m 125 --cminDefaultMinimizerType Minuit --rMin -3
#  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root  -m 125 --robustFit 1 --doFits --parallel 60 --cminDefaultMinimizerType Minuit --rMin -3
#  combineTool.py -M Impacts -d datacards/datacard_M${mass}_${crvr}_impact_20178.dat.root -m 125 -o impacts.json --cminDefaultMinimizerType Minuit --rMin -3
#  plotImpacts.py -i impacts.json --per-page 60 -o impacts
#  mv impacts.pdf impacts_20178/impacts_realdata_${crvr}_M${mass}.pdf
  mv fitDiagnosticsTest.root fitDiagnostics_${crvr}_20178.root
done
