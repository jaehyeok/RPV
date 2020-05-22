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

void make_fit(TFile *fhist, TFile *kappa, int ibin);
float SF_kap(TFile *kappa, int ikap, int ibin); 

int main(int argc, char* argv[]){

  TFile *kappa = new TFile("plots/kappa_summary_nominalX.root","READ");
  TFile *fhist = new TFile("variations/output_newnt.root","READ");

  make_fit(fhist,kappa,28); 
  make_fit(fhist,kappa,29); 
  make_fit(fhist,kappa,30); 

  kappa->Close();
  fhist->Close();
}

void make_fit( TFile *fhist, TFile *kappa, int ibin){

  TH1F *data   = static_cast<TH1F*>(fhist->Get(Form("bin%i/data_obs", ibin)));
  TH1F *qcd    = static_cast<TH1F*>(fhist->Get(Form("bin%i/qcd"     , ibin)));
  TH1F *ttbar  = static_cast<TH1F*>(fhist->Get(Form("bin%i/ttbar"   , ibin)));
  TH1F *wjets  = static_cast<TH1F*>(fhist->Get(Form("bin%i/wjets"   , ibin)));
  TH1F *other  = static_cast<TH1F*>(fhist->Get(Form("bin%i/other"   , ibin))); 
  TH1F *mc_tot = (TH1F *)qcd;

  float mjmin  = (float) data->GetMinimum();
  float mjmax  = (float) data->GetMaximum();

  TH1F *h_mc_proc1   = new TH1F("h_mc_proc1","h_mc_proc1",3,500,1400); 
  TH1F *h_mc         = new TH1F("h_mc","h_mc",3,500,1400); 

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

  h_mc_proc1->SetBinContent(1, mjbin_mc[0]*SF);
  h_mc_proc1->SetBinContent(2, mjbin_mc[1]*SF);
  h_mc_proc1->SetBinContent(3, mjbin_mc[2]*SF);
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

  h_mc_proc1->SetStats(0);
  h_mc_proc1->SetLineColor(kBlue);
  h_mc_proc1->SetLineWidth(2);
  h_mc_proc1->GetXaxis()->SetTitle("M_{J}");
  mc_tot->SetStats(0);
  mc_tot->SetLineColor(kBlue);
  mc_tot->SetLineWidth(2);
  mc_tot->GetXaxis()->SetTitle("M_{J}");
  mc_tot->Print("all");

  vector<double> lines = {1.};

  TCanvas *c = new TCanvas("c","c",1000,1000);
  TRatioPlot *comp = new TRatioPlot(h_mc,data);
  comp->SetGridlines(lines);
  comp->Draw();
  comp->GetUpperPad()->SetLogy();
  comp->GetUpperRefYaxis()->SetTitle("Events");
  comp->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetRangeUser(0.5,1.5);
  comp->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  c->Print(Form("plots/kappa_syst_uncert_%d.pdf",ibin));

  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->cd();
  TRatioPlot *comp1 = new TRatioPlot(h_mc_proc1,data);
  comp1->SetGridlines(lines);
  comp1->Draw();
  comp1->GetUpperPad()->SetLogy();
  comp1->GetUpperRefYaxis()->SetTitle("Events");
  comp1->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp1->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp1->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp1->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp1->GetLowerRefYaxis()->SetRangeUser(0.5,1.5);
  comp1->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  c1->Print(Form("plots/kappa_syst_uncert_%d_proc1.pdf",ibin));

  TCanvas *c2 = new TCanvas("c","c",1000,1000);
  c2->cd();
  TRatioPlot *comp2 = new TRatioPlot(mc_tot,data);
  comp2->SetGridlines(lines);
  comp2->Draw();
  comp2->GetUpperPad()->SetLogy();
  comp2->GetUpperRefYaxis()->SetTitle("Events");
  comp2->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp2->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp2->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp2->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp2->GetLowerRefYaxis()->SetRangeUser(0.5,1.5);
  comp2->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  c2->Print(Form("plots/kappa_syst_uncert_%d_nocor.pdf",ibin));
}

float SF_kap(TFile *kappa, int ikap, int ibin){
  TH1F *h = static_cast<TH1F*> (kappa->Get(Form("h1_1l_summary%d",ikap)));

  int njets_region=1;
  if(ibin%3==2)njets_region=2;
  if(ibin%3==0)njets_region=3;
  int bin_index= (njets_region-1)*25 + 8;

  float kappa_0, kappa_1, kappa_2, kappa_ave;
  kappa_0 = (float)h->GetBinContent(bin_index); 
  kappa_1 = (float)h->GetBinContent(bin_index+2); 
  kappa_2 = (float)h->GetBinContent(bin_index+4); 
  kappa_ave = (kappa_1+kappa_2)/2;
  cout<<"kappa average for njets "<<njets_region<<" : "<<kappa_ave<<endl;
  return kappa_ave;
}