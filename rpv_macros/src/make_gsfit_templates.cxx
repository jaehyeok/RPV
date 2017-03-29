#include <iostream>
#include <fstream>
#include <vector>

#include "TDirectory.h"
#include "TFile.h"

#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  const int nBins=4;
  const float xMin=0;
  const float xMax=4.8;

  TString lumi = "16.2";
  TString tag = "";

  bool makeDatacard = true;
}

using namespace std;

TString getProcessCut(TString process, TString cut);
TH1D* makeShapeHist(TString process, TString cut, TChain& chain);
vector<vector<TH1D*> > makeMCStatVariations(TString process, TH1D* hist);

// Usage: ./run/make_gsfit_templates.exe
int main(){ 
  TH1::SetDefaultSumw2(true);

  cout<<"Making gsfit templates"<<endl;

  TString folder_dat = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/data/skim_st1000/";  
  TString folder_bkg = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/mc/skim_rpv0lep/";
  TString folder_sig = "/net/cms2/cms2r0/jaehyeokyoo/babies/2017_01_10/mc/T1tbs/";

  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  // Non-QCD is fixed
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
  
  TString basecut = "nleps==0&&ht>1500&&njets>=4&&mj12>500&&nbm==2&&pass";

  //Make shape hists
  TH1D* h_data = makeShapeHist("data_obs", basecut, data);
  TH1D* h_rpv = makeShapeHist("rpv", basecut, rpv);
  TH1D* h_qcd_GSbb = makeShapeHist("qcd_GSbb", basecut, qcd);
  TH1D* h_qcd_GSb  = makeShapeHist("qcd_GSb", basecut, qcd);
  TH1D* h_qcd_noGS = makeShapeHist("qcd_noGS", basecut, qcd);
  TH1D* h_other = makeShapeHist("other", basecut, other);

  cout<<"Normalizing QCD yields to data"<<endl;
  double scaling = (h_data->Integral() - h_other->Integral())/(h_qcd_GSbb->Integral() + h_qcd_GSb->Integral() + h_qcd_noGS->Integral());
  cout<<"Scaling factor is "<<scaling<<endl;

  h_qcd_GSbb->Scale(scaling);
  h_qcd_GSb->Scale(scaling);
  h_qcd_noGS->Scale(scaling);

  cout<<"Making MC stat variations"<<endl;
  vector<vector<TH1D*> > h_qcd_GSbb_mcstat   =  makeMCStatVariations("qcd_GSbb", h_qcd_GSbb);
  vector<vector<TH1D*> > h_qcd_GSb_mcstat   =  makeMCStatVariations("qcd_GSb", h_qcd_GSb);
  vector<vector<TH1D*> > h_qcd_noGS_mcstat =  makeMCStatVariations("qcd_noGS", h_qcd_noGS);
  vector<vector<TH1D*> > h_other_mcstat    = makeMCStatVariations("other", h_other);

  //Make file and write histograms to it
  TString filename = "gsfit/gsfit_shapes.root";
  if(tag!="") filename.ReplaceAll(".root","_"+tag+".root");
  TFile *out = new TFile(filename, "recreate");
  TDirectory *bin = out->mkdir("bin1");
  bin->cd();
  
  // Write out nominal shapes
  h_data->Write();
  h_rpv->Write();
  h_qcd_GSbb->Write();
  h_qcd_GSb->Write();
  h_qcd_noGS->Write();
  h_other->Write();

  // Write out mc stat. shapes
  for(unsigned int isys=0; isys<2; isys++){
    for(unsigned int ibin=0; ibin<nBins; ibin++){
      h_qcd_GSbb_mcstat[isys][ibin]->Write();
      h_qcd_GSb_mcstat[isys][ibin]->Write();
      h_qcd_noGS_mcstat[isys][ibin]->Write();
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
    double nqcd_GSbb = h_qcd_GSbb->Integral();
    double nqcd_GSb = h_qcd_GSb->Integral();
    double nqcd_noGS = h_qcd_noGS->Integral();
    double nother = h_other->Integral();

    ofstream card;
    TString cardname = "gsfit/datacard_gsfit.dat";
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
    card << "-------------------------------------------------------------- \n";
    card << "bin         bin1      bin1       bin1      bin1       bin1  \n";
    card << "process     rpv       qcd_GSbb   qcd_GSb   qcd_noGS   other \n";
    card << "process     0         1          2         3          4\n";
    card << "rate        "<<nrpv<<"   "<<nqcd_GSbb<<"    "<<nqcd_GSb<<"   "<<nqcd_noGS<<"    "<<nother<<" \n";
    card << "-------------------------------------------------------------- \n";
    card << "norm_qcd_GSbb   lnU - 5 - - - \n";
    card << "norm_qcd_GSb    lnU - - 5 - - \n";
    card << "norm_qcd_noGS   lnU - - - 5 - \n\n";

    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcd_GSbb_bin"+to_string(ibin+1) << "  shape - 1 - - - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcd_GSb_bin"+to_string(ibin+1)  << "   shape - - 1 - - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_qcd_noGS_bin"+to_string(ibin+1) << "  shape - - - 1 - \n";
    for(unsigned int ibin=0; ibin<nBins; ibin++) card << "mcstat_other_bin"+to_string(ibin+1)    << "     shape - - - - 1 \n";

    cout<<"Made datacard: "<<cardname<<endl;
  }  
}

TH1D* makeShapeHist(TString process, TString cut, TChain& chain){

  cout<<"Making "+process+" histogram"<<endl;
  cut = getProcessCut(process, cut);

  TH1D* h_temp = new TH1D(process, process, nBins, xMin, xMax);
  chain.Project(process,"dr_bb",cut);

  return h_temp;
}

vector<vector<TH1D*> > makeMCStatVariations(TString process, TH1D* hist){

  if(process != "qcd_GSbb" && process != "qcd_GSb" && process != "qcd_noGS" && process != "other"){
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

      h_variations[isys][ibin]->Scale(norm/h_variations[isys][ibin]->Integral());
      
    }
  }
  return h_variations;
}

TString getProcessCut(TString process, TString cut){

  if(process=="data_obs")      cut = cut+" && run>=278820&&run<=284044";
  else if(process=="rpv")      cut = lumi+"*weight*("+cut+")";     
  else if(process=="qcd_GSbb") cut = lumi+"*weight/w_btag*w_btag_gh*("+cut+" && (Sum$(mc_gs&&mc_id==21&&mc_pt>30)>0&&Sum$(mc_gs&&abs(mc_id)==5)>=2) && abs(bb_gs_flavor)>=5)";
  else if(process=="qcd_GSb")  cut = lumi+"*weight/w_btag*w_btag_gh*("+cut+" && (Sum$(mc_gs&&mc_id==21&&mc_pt>30)>0&&Sum$(mc_gs&&abs(mc_id)==5)>=2) && abs(bb_gs_flavor)<5)";
  else if(process=="qcd_noGS") cut = lumi+"*weight/w_btag*w_btag_gh*("+cut+" && !(Sum$(mc_gs&&mc_id==21&&mc_pt>30)>0&&Sum$(mc_gs&&abs(mc_id)==5)>=2))";
  else if(process=="other")    cut = lumi+"*weight/w_btag*w_btag_gh*("+cut+"&&stitch_ht)";     
  else{
    cout<<"ERROR: Incorrect process name"<<endl;
    exit(1);
  }
  return cut;
}
