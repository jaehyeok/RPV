#include <iostream>
#include <fstream>
#include <vector>

#include "TDirectory.h"
#include "TFile.h"

#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  const int nBins=20;
  const float xMin=0.8484;
  const float xMax=1.0;

  TString fittype = "nominal";

  TString lumi = "36.8";
  TString tag = "";
  bool makeDatacard = true;
  bool doWithSFs = true;
}

using namespace std;

TString getBasecut(TString fittype);
TString getProcessCut(TString process, TString cut);
vector<vector<TH1D*> > makeMCStatVariations(TString process, TH1D* hist);
vector<vector<TH1D*> > makeSFVariations(TString process, TString cut, TChain& chain, double nom_norm);
TH1D* makeShapeHist(TString process, TString cut, TChain& chain);

// Usage: ./run/make_csvfit_templates.exe [fittype] [doWithSFs]
int main(int argc, char* argv[]){ 
  if(argc>1) fittype = argv[1];
  if(argc>2) doWithSFs = stoi(argv[2]);

  TH1::SetDefaultSumw2(true);

  cout<<"Making csvfit templates for fittype: "<<fittype<<endl;

  TString folder_dat = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/data/merged_rpvdata_rpvregion/";  
  TString folder_bkg = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/mc/merged_rpvmc_rpvfit/";
  TString folder_sig = "/net/cms2/cms2r0/jaehyeokyoo/babies/2017_01_10/mc/T1tbs/";

  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  // The CSV reweighting only affects QCD; the flavor composition of other samples are well defined and does not need correction
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  // Add ttbar and wjets to other
  s_other.insert(s_other.end(),s_tt.begin(),s_tt.end());
  s_other.insert(s_other.end(),s_wjets.begin(),s_wjets.end());

  //Make chains
  TChain data("tree"), rpv("tree"), qcd("tree"), other("tree");
  for(unsigned int ifile=0; ifile<s_data.size(); ifile++)      data.Add(s_data[ifile]);
  for(unsigned int ifile=0; ifile<s_rpv_m1700.size(); ifile++) rpv.Add(s_rpv_m1700[ifile]);
  for(unsigned int ifile=0; ifile<s_qcd.size(); ifile++)       qcd.Add(s_qcd[ifile]);
  for(unsigned int ifile=0; ifile<s_other.size(); ifile++)     other.Add(s_other[ifile]);
  
  TString basecut = getBasecut(fittype);

  //Make shape hists
  TH1D* h_data =   makeShapeHist("data_obs", basecut, data);
  TH1D* h_rpv =    makeShapeHist("rpv", basecut, rpv);
  TH1D* h_qcdb =   makeShapeHist("qcdb", basecut, qcd);
  TH1D* h_qcdc =   makeShapeHist("qcdc", basecut, qcd);
  TH1D* h_qcdl =   makeShapeHist("qcdl", basecut, qcd);
  TH1D* h_other =  makeShapeHist("other", basecut, other);

  cout<<"Normalizing QCD yields to data"<<endl;
  double scaling = (h_data->Integral() - h_other->Integral())/(h_qcdb->Integral() + h_qcdc->Integral() + h_qcdl->Integral());
  cout<<"Scaling factor is "<<scaling<<endl;

  h_qcdb->Scale(scaling);
  h_qcdc->Scale(scaling);
  h_qcdl->Scale(scaling);

  vector<vector<TH1D*> > h_qcdb_sf, h_qcdc_sf, h_qcdl_sf, h_other_sf;
  if(doWithSFs){
    cout<<"Making SF variations"<<endl;
    h_qcdb_sf =  makeSFVariations("qcdb", basecut, qcd, h_qcdb->Integral());
    h_qcdc_sf =  makeSFVariations("qcdc", basecut, qcd, h_qcdc->Integral());
    h_qcdl_sf =  makeSFVariations("qcdl", basecut, qcd, h_qcdl->Integral());
    h_other_sf = makeSFVariations("other", basecut, other, h_other->Integral());
  }

  cout<<"Making MC stat variations"<<endl;
  vector<vector<TH1D*> > h_qcdb_mcstat =  makeMCStatVariations("qcdb", h_qcdb);
  vector<vector<TH1D*> > h_qcdc_mcstat =  makeMCStatVariations("qcdc", h_qcdc);
  vector<vector<TH1D*> > h_qcdl_mcstat =  makeMCStatVariations("qcdl", h_qcdl);
  vector<vector<TH1D*> > h_other_mcstat = makeMCStatVariations("other", h_other);

  //Make file and write histograms to it
  TString filename = "csvfit/csvfit_shapes.root";
  if(fittype!="nominal") filename.ReplaceAll(".root","_"+fittype+".root");
  if(!doWithSFs) filename.ReplaceAll(".root","_noSFs.root");
  if(tag!="") filename.ReplaceAll(".root","_"+tag+".root");
  TFile *out = new TFile(filename, "recreate");
  TDirectory *bin = out->mkdir("bin1");
  bin->cd();
  
  // Write out nominal shapes
  h_data->Write();
  h_rpv->Write();
  h_qcdb->Write();
  h_qcdc->Write();
  h_qcdl->Write();
  h_other->Write();

  // Write out SF shapes
  if(doWithSFs){
    for(unsigned int isys=0; isys<2; isys++){
      for(unsigned int idir=0; idir<2; idir++){
	h_qcdb_sf[isys][idir]->Write();
	h_qcdc_sf[isys][idir]->Write();
	h_qcdl_sf[isys][idir]->Write();
	h_other_sf[isys][idir]->Write();
      }
    }
  }

  // Write out mc stat. shapes
  for(unsigned int isys=0; isys<2; isys++){
    for(unsigned int ibin=0; ibin<nBins; ibin++){
      h_qcdb_mcstat[isys][ibin]->Write();
      h_qcdc_mcstat[isys][ibin]->Write();
      h_qcdl_mcstat[isys][ibin]->Write();
      h_other_mcstat[isys][ibin]->Write();
    }
  }

  out->Write();
  out->Close();

  cout<<"Wrote out shapes file: "<<filename<<endl;

  // Make datacard
  if(makeDatacard){
    double ndata = h_data->Integral();
    double nrpv = h_rpv->Integral();    
    double nqcdb = h_qcdb->Integral();
    double nqcdc = h_qcdc->Integral();
    double nqcdl =  h_qcdl->Integral();
    double nother = h_other->Integral();

    ofstream card;
    TString cardname = "csvfit/datacard_csvfit.dat";
    if(fittype!="nominal") cardname.ReplaceAll(".dat","_"+fittype+".dat");
    if(!doWithSFs) cardname.ReplaceAll(".dat","_noSFs.dat");
    if(tag!="") cardname.ReplaceAll(".dat","_"+tag+".dat");
    card.open(cardname);
    card << "# Datacard for csv flavor fit \n";
    card << "imax 1  number of channels \n";
    card << "jmax 4  number of backgrounds \n";
    card << "kmax *  number of nuisances \n";    
    card << "------------------------------------------------------------------------- \n";
    card << "shapes * bin1 "<<basename(filename)<<" bin1/$PROCESS bin1/$PROCESS_$SYSTEMATIC \n";
    card << "------------------------------------------------------------------------- \n";
    card << "bin         bin1 \n";
    card << "observation "<<ndata<<" \n";
    card << "--------------------------------------------------------- \n";
    card << "bin         bin1      bin1     bin1     bin1     bin1 \n";
    card << "process     rpv       qcdb     qcdc     qcdl     other \n";
    card << "process     0         1        2        3        4 \n";
    card << "rate        "<<nrpv<<"   "<<nqcdb<<"  "<<nqcdc<<"  "<<nqcdl<<"  "<<nother<<" \n";
    card << "--------------------------------------------------------- \n";
    card << "norm_qcdb     lnU - 5 - - - \n";
    card << "norm_qcdc     lnU - - 5 - - \n\n";

    if(doWithSFs){
      card << "btag_bc  " << "  shape - 1 1 1 1 \n";
      card << "btag_udsg" << "  shape - 1 1 1 1 \n\n";
    }
    
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcdb_bin"+to_string(ibin+1)  << "  shape - 1 - - - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcdc_bin"+to_string(ibin+1)  << "  shape - - 1 - - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcdl_bin"+to_string(ibin+1)  << "  shape - - - 1 - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_other_bin"+to_string(ibin+1) << "  shape - - - - 1 \n";

    cout<<"Made datacard: "<<cardname<<endl;
  }  
}

vector<vector<TH1D*> > makeMCStatVariations(TString process, TH1D* hist){

  if(process != "qcdb" && process != "qcdc" && process != "qcdl" && process != "other"){
    cout<<"ERROR: Incorrect process name"<<endl;
    exit(1);
  }

  vector<vector<TH1D*> > h_variations(2, vector<TH1D*>(nBins));

  double norm = hist->Integral();

  for(unsigned int ibin=0; ibin<nBins; ibin++){
    for(unsigned int isys=0; isys<2; isys++){

      TString title = process+"_mcstat_"+process+"_bin"+to_string(ibin+1);
      title += isys==0 ? "Up" : "Down";

      h_variations[isys][ibin] = static_cast<TH1D*>(hist->Clone(title));
      double nomContent = h_variations[isys][ibin]->GetBinContent(ibin+1);
      double error = h_variations[isys][ibin]->GetBinError(ibin+1);
      double varContent = isys==0 ? nomContent+error : nomContent-error;

      h_variations[isys][ibin]->SetBinContent(ibin+1, varContent);

      // Renormalize variations
      h_variations[isys][ibin]->Scale(norm/h_variations[isys][ibin]->Integral());
    }
  }
  return h_variations;
}

vector<vector<TH1D*> > makeSFVariations(TString process, TString cut, TChain& chain, double nom_norm){

  cut = getProcessCut(process, cut);

  // [Heavy/Light SF][Up/Down]
  vector<vector<TH1D*> > h_variations(2, vector<TH1D*>(2));
  vector<vector<TString> > sfNames = {{"btag_bcUp", "btag_bcDown"}, {"btag_udsgUp", "btag_udsgDown"}};
  vector<vector<TString> > sfWeights = {{"sys_bctag[0]/w_btag", "sys_bctag[1]/w_btag"}, {"sys_udsgtag[0]/w_btag", "sys_udsgtag[1]/w_btag"}};

  for(int isys=0; isys<2; isys++){
    for(int idir=0; idir<2; idir++){
        h_variations[isys][idir] = new TH1D(process+"_"+sfNames[isys][idir], process+"_"+sfNames[isys][idir], nBins, xMin, xMax);
	chain.Project(process+"_"+sfNames[isys][idir],"jets_csv",cut+"*"+sfWeights[isys][idir]);

	// Renormalize variations
	h_variations[isys][idir]->Scale(nom_norm/h_variations[isys][idir]->Integral());
    }
  }
  return h_variations;
}

TH1D* makeShapeHist(TString process, TString cut, TChain& chain){

  cout<<"Making "+process+" histogram"<<endl;
  cut = getProcessCut(process, cut);

  TH1D* h_temp = new TH1D(process, process, nBins, xMin, xMax);
  chain.Project(process,"jets_csv",cut);

  return h_temp;
}

TString getBasecut(TString fittype){

  TString cut = "";
  if(fittype == "nominal")     cut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>500&&nbm>=2&&pass";
  else if(fittype == "vlowmj") cut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>300&&mj12<=500&&nbm>=2&&pass";
  else if(fittype == "lowmj")  cut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>500&&mj12<=800&&nbm>=2&&pass";
  else if(fittype == "highmj") cut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>800&&nbm>=2&&pass";
  else if(fittype == "45jets") cut = "nleps==0&&ht>1500&&njets>=4&&njets<=5&&mj12>500&&nbm>=2&&pass";
  else if(fittype == "67jets") cut = "nleps==0&&ht>1500&&njets>=6&&njets<=7&&mj12>500&&nbm>=2&&pass";
  else if(fittype == "89jets") cut = "nleps==0&&ht>1500&&njets>=8&&njets<=9&&mj12>500&&nbm>=2&&pass";
  else if(fittype == "10jets") cut = "nleps==0&&ht>1500&&njets>10&&mj12>500&&nbm>=2&&pass";
  else{
    cout<<"ERROR: Incorrect fittype"<<endl;
    exit(1);
  }
  return cut;
}

TString getProcessCut(TString process, TString cut){

  if(process=="data_obs")   cut = cut;
  else if(process=="rpv")   cut = lumi+"*weight*("+cut+")";     
  else if(process=="qcdb")  cut = lumi+"*weight*("+cut+"&&Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)>=1)";
  else if(process=="qcdc")  cut = lumi+"*weight*("+cut+"&&Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)==0&&Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==4)>=1)";
  else if(process=="qcdl")  cut = lumi+"*weight*("+cut+"&&Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)==0&&Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==4)==0)";
  else if(process=="other") cut = lumi+"*weight*("+cut+"&&stitch_ht)";     
  else{
    cout<<"ERROR: Incorrect process name"<<endl;
    exit(1);
  }
  return cut;
}
