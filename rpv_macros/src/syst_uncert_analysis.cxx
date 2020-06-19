#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TRatioPlot.h"
#include "TStyle.h"
#include "TMath.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

void make_fit(TFile *fhist, TFile *kappa, TFile *f_out, int ibin);
void make_fit(TFile *fhist, TFile *kappa, int ibin);
float SF_kap(TFile *kappa, int ikap, int ibin); 
float SF_kap_err(TFile *kappa, int ikap, int ibin);

int main(int argc, char* argv[]){
  TString n_input = "variations/output_newnt_nl0shape_2016.root";
  TString n_kappa = "plots/kappa_summary_nominalX.root";
  if(argc==2){
    n_kappa = argv[1];
  }
  else if(argc==3){
    n_kappa = argv[1];
    n_input = argv[2];
  }
  TString temp = n_input;
  TString n_out = temp.ReplaceAll("output_","output_kappa");
  temp = n_input;
  TFile *kappa = new TFile(n_kappa,"READ");
  TFile *fhist = new TFile(n_input,"READ");
  if(n_kappa.Contains("mconly")){
    if(n_input.Contains("nominal")) n_out = temp.ReplaceAll("nominal","kappa");
    n_out = n_out.ReplaceAll("_mconly","");
    TFile *f_out = new TFile(n_out,"recreate");
    for(int rg=22;rg<52;rg++){make_fit(fhist,kappa,f_out,rg);}
    f_out->Close();
  }
  else{
    make_fit(fhist,kappa,28); 
    make_fit(fhist,kappa,29); 
    make_fit(fhist,kappa,30); 
  }
  kappa->Close();
  fhist->Close();
}

void make_fit( TFile *fhist, TFile *kappa, TFile *f_out, int ibin){

  TH1F *data   = static_cast<TH1F*>(fhist->Get(Form("bin%i/data_obs", ibin)));
  TH1F *qcd    = static_cast<TH1F*>(fhist->Get(Form("bin%i/qcd"     , ibin)));
  TH1F *ttbar  = static_cast<TH1F*>(fhist->Get(Form("bin%i/ttbar"   , ibin)));
  TH1F *wjets  = static_cast<TH1F*>(fhist->Get(Form("bin%i/wjets"   , ibin)));
  TH1F *other  = static_cast<TH1F*>(fhist->Get(Form("bin%i/other"   , ibin))); 
  TH1F *mc_tot = (TH1F *)qcd;

  float mjmin  = (float) data->GetXaxis()->GetBinLowEdge(1);
  float mjmax  = (float) data->GetXaxis()->GetBinUpEdge(3);

  mc_tot->Add(ttbar);
  mc_tot->Add(wjets);
  mc_tot->Add(other);

  float mjbin_data[3];
  float mjbin_mc[3];
 
  for(int i=0; i<3; i++){
    mjbin_data[i] = (float) data->GetBinContent(i+1);
    mjbin_mc[i]   = (float) mc_tot->GetBinContent(i+1); 
  }


  float SF     = mjbin_data[0]/mjbin_mc[0];
  float binsz  = (mjmax-mjmin)/3;

  vector<TString> proc = {"qcd","ttbar","wjets","other",
                          "signal_M1100","signal_M1200","signal_M1300","signal_M1400","signal_M1500","signal_M1600","signal_M1700","signal_M1800","signal_M1900","signal_M2000"};
  vector<TString> updo = {"Up","Down"};
  
  f_out->cd();
  gDirectory->cd("/");
  TString directory(Form("bin%d",ibin));
  if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
  gDirectory->cd(directory);

  for(auto updown : updo){
    for(auto process : proc){
      TH1F *h_process  = static_cast<TH1F*>(fhist->Get(Form("bin%i/%s"   , ibin,process.Data())));
      for(int i=0; i<3; i++){
        mjbin_mc[i]   = (float) h_process->GetBinContent(i+1); 
      }

      TString h_name  = process+"_kappa"+updown;
      TH1F *h_kappa = new TH1F(h_name.Data(),h_name.Data(),3,mjmin,mjmax); 
      float uncert1, uncert2;
      if(updown=="Up"){
        uncert1 = SF_kap_err(kappa,1,ibin);
        uncert2 = SF_kap_err(kappa,2,ibin);
      }
      else if(updown=="Down"){
        uncert1 = -SF_kap_err(kappa,1,ibin);
        uncert2 = -SF_kap_err(kappa,2,ibin);
      }
      h_kappa->SetBinContent(1, mjbin_mc[0]*SF);
      h_kappa->SetBinContent(2, mjbin_mc[1]*SF*(SF_kap(kappa,1,ibin)+uncert1));
      h_kappa->SetBinContent(3, mjbin_mc[2]*SF*(SF_kap(kappa,2,ibin)+uncert2));
      h_kappa->Write();
    }
  }
}

void make_fit( TFile *fhist, TFile *kappa,int ibin){

  TH1F *data   = static_cast<TH1F*>(fhist->Get(Form("bin%i/data_obs", ibin)));
  TH1F *qcd    = static_cast<TH1F*>(fhist->Get(Form("bin%i/qcd"     , ibin)));
  TH1F *ttbar  = static_cast<TH1F*>(fhist->Get(Form("bin%i/ttbar"   , ibin)));
  TH1F *wjets  = static_cast<TH1F*>(fhist->Get(Form("bin%i/wjets"   , ibin)));
  TH1F *other  = static_cast<TH1F*>(fhist->Get(Form("bin%i/other"   , ibin))); 
  TH1F *mc_tot = (TH1F *)qcd;

  float mjmin  = (float) data->GetXaxis()->GetBinLowEdge(1);
  float mjmax  = (float) data->GetXaxis()->GetBinUpEdge(3);

  TH1F *h_mc_proc1   = new TH1F("h_mc_proc1","h_mc_proc1",3,mjmin,mjmax); 
  TH1F *h_mc         = new TH1F("h_mc","h_mc",3,mjmin,mjmax); 

  float binsz  = (mjmax-mjmin)/3;

  mc_tot->Add(ttbar);
  mc_tot->Add(wjets);
  mc_tot->Add(other);

  
  float mjbin_data[3];
  float mjbin_mc[3];
 
  for(int i=0; i<3; i++){
    mjbin_data[i] = (float) data->GetBinContent(i+1);
    mjbin_mc[i]   = (float) mc_tot->GetBinContent(i+1); 
  }
 
  float SF          = mjbin_data[0]/mjbin_mc[0];

  h_mc->SetBinContent(1, mjbin_mc[0]*SF);
  h_mc->SetBinContent(2, mjbin_mc[1]*SF*SF_kap(kappa,1,ibin));
  h_mc->SetBinContent(3, mjbin_mc[2]*SF*SF_kap(kappa,2,ibin));

  float ymax;

  data->SetStats(0);
  data->SetLineColor(kBlack);
  data->SetMarkerStyle(20);
  data->SetLineWidth(2);
  data->GetXaxis()->SetTitle("M_{J}");
  ymax = data->GetMaximum();
  h_mc->SetStats(0);
  h_mc->SetLineColor(kBlue);
  h_mc->SetLineWidth(2);
  h_mc->GetXaxis()->SetTitle("M_{J}");

  mc_tot->SetStats(0);
  mc_tot->SetLineColor(kRed);
  mc_tot->SetLineWidth(2);
  mc_tot->GetXaxis()->SetTitle("M_{J}");

  vector<double> lines = {1.};

  TCanvas *c = new TCanvas("c","c",1000,1000);
  TRatioPlot *comp = new TRatioPlot(h_mc,data);
  comp->SetGridlines(lines);
  comp->Draw();
  comp->GetUpperPad()->SetLogy();
  comp->GetUpperRefYaxis()->SetTitle("Events");
  comp->GetLowerRefYaxis()->SetTitle("MC/Data");
  comp->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetRangeUser(0.5,1.5);
  comp->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  comp->GetUpperPad()->cd();
  mc_tot->Draw("hist same");
  c->Print(Form("plots/kappa_syst_uncert_%d.pdf",ibin));

}



float SF_kap(TFile *kappa, int ikap, int ibin){
  TH1F *h = static_cast<TH1F*> (kappa->Get(Form("h1_1l_summary%d",ikap)));

  int njets_region=1;
  if(ibin%3==2)njets_region=2;
  if(ibin%3==0)njets_region=3;
  int bin_index= (njets_region-1)*25 + 8;

  float kappa_0, kappa_1, kappa_2, kappa_ave;
  kappa_0 = (float)h->GetBinContent(bin_index-2); 
  kappa_1 = (float)h->GetBinContent(bin_index); 
  kappa_2 = (float)h->GetBinContent(bin_index+2); 
  kappa_ave = (kappa_1+kappa_2)/2;
  cout<<kappa_ave<<endl;
  return kappa_ave;
}

float SF_kap_err(TFile *kappa, int ikap, int ibin){
  TH1F *h = static_cast<TH1F*> (kappa->Get(Form("h1_1l_summary%d",ikap)));

  int njets_region=1;
  if(ibin%3==2)njets_region=2;
  if(ibin%3==0)njets_region=3;
  int bin_index= (njets_region-1)*25 + 8;

  float err_kappa_0, err_kappa_1, err_kappa_2, err_kappa_ave;
  err_kappa_0 = (float)h->GetBinError(bin_index-2); 
  err_kappa_1 = (float)h->GetBinError(bin_index); 
  err_kappa_2 = (float)h->GetBinError(bin_index+2); 
  err_kappa_ave = TMath::Sqrt((err_kappa_1*err_kappa_1+err_kappa_2*err_kappa_2)/2);
  return err_kappa_ave;
}
