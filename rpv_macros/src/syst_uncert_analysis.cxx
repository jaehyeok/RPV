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

  TH1F *h_mc   = new TH1F("h_mc","h_mc",3,500,1400); 

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
  
  TCanvas *c = new TCanvas("c","c",1000,1000);
  c->cd();
  data->SetStats(0);
  data->SetLineColor(kBlack);
  data->SetMarkerStyle(20);
  data->SetLineWidth(2);
  data->Draw("e");
  h_mc->SetLineColor(kBlue);
  h_mc->SetLineWidth(2);
  h_mc->Draw("same hist");
  c->Print(Form("plots/kappa_syst_uncert_%d.pdf",ibin));
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
  return kappa_ave/kappa_2;
}
