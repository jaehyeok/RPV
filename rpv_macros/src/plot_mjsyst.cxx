// command: ./run/plot_mjsyst.exe variations/output_nominal_newnt_2016.root
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TString.h"
#include "TTree.h"
#include "THStack.h"
#include "TLatex.h"
#include "TF1.h"
#include "TLine.h"

using namespace std;

float GetShapeError(TH1F *h1, int ibin);
float GetShapeError_ttbar(TH1F *h1, int ibin);
float GetShapeError_wjets(TH1F *h1, int ibin);
double fitf(double *x, double *par)
{
  double fitval;
  return fitval = par[0]*x[0] + par[1];
}
float return_y(float x, float slope, float y_intercept)
{
  return slope*x + y_intercept;
}

int main(int argc, char *argv[])
{
  gStyle->SetOptStat(0);
  TString filename;
  filename = argv[1];
  TString year;
  if(filename.Contains("2016")) year="2016";
  else if(filename.Contains("2017_20178.root")) year="2017";
  else if(filename.Contains("2018_20178.root")) year="2018";
  else if(filename.Contains("2017.root")) year="2017";
  else if(filename.Contains("2018.root")) year="2018";
  else cout << "input file doesn't contain year" << endl;
  cout << "year: " << year << endl;

  TFile *infile;
  infile = TFile::Open(filename,"READ");

  TH1F *h1_qcd[37], *h1_ttbar[37], *h1_wjets[37];
  TH1F *h1_qcd_clone[37], *h1_ttbar_clone[37], *h1_wjets_clone[37];

  for(int ibin=22; ibin<37; ibin++) {
    //define histogram
    h1_qcd[ibin] = new TH1F(Form("h1_qcd_bin%i", ibin), Form("h1_qcd_bin%i", ibin), 3, 500, 1400);
    h1_ttbar[ibin] = new TH1F(Form("h1_ttbar_bin%i", ibin), Form("h1_ttbar_bin%i", ibin), 3, 500, 1400);
    h1_wjets[ibin] = new TH1F(Form("h1_wjets_bin%i", ibin), Form("h1_wjets_bin%i", ibin), 3, 500, 1400);
    h1_qcd_clone[ibin] = new TH1F(Form("h1_qcd_clone_bin%i", ibin), Form("h1_qcd_clone_bin%i", ibin), 3, 500, 1400);
    h1_ttbar_clone[ibin] = new TH1F(Form("h1_ttbar_clone_bin%i", ibin), Form("h1_ttbar_clone_bin%i", ibin), 3, 500, 1400);
    h1_wjets_clone[ibin] = new TH1F(Form("h1_wjets_clone_bin%i", ibin), Form("h1_wjets_clone_bin%i", ibin), 3, 500, 1400);

    h1_qcd[ibin]->Sumw2();
    h1_ttbar[ibin]->Sumw2();
    h1_wjets[ibin]->Sumw2();
    h1_qcd_clone[ibin]->Sumw2();
    h1_ttbar_clone[ibin]->Sumw2();
    h1_wjets_clone[ibin]->Sumw2();

    //get and clone histogram
    h1_qcd[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)));
    h1_ttbar[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)));
    h1_wjets[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)));
    h1_qcd_clone[ibin] = static_cast<TH1F*>(h1_qcd[ibin]->Clone(Form("qcd_bin%d", ibin)));
    h1_ttbar_clone[ibin] = static_cast<TH1F*>(h1_ttbar[ibin]->Clone(Form("ttbar_bin%d", ibin)));
    h1_wjets_clone[ibin] = static_cast<TH1F*>(h1_wjets[ibin]->Clone(Form("wjets_bin%d", ibin)));
  }

  TH1F *h1_qcd_shape[37], *h1_ttbar_shape[37], *h1_wjets_shape[37];
  for(int ibin=22; ibin<37; ibin++) {
    //define shape histogram
    h1_qcd_shape[ibin] = new TH1F(Form("h1_qcd_shape_bin%i", ibin), Form("h1_qcd_shape_bin%i", ibin), 3, 500, 1400);
    h1_ttbar_shape[ibin] = new TH1F(Form("h1_ttbar_shape_bin%i", ibin), Form("h1_ttbar_shape_bin%i", ibin), 3, 500, 1400);
    h1_wjets_shape[ibin] = new TH1F(Form("h1_wjets_shape_bin%i", ibin), Form("h1_wjets_shape_bin%i", ibin), 3, 500, 1400);
    if(ibin==34) continue;
    //set values and errors
      //qcd
    for(int jbin=1; jbin<4; jbin++) {
      if(h1_qcd_clone[ibin]->GetBinContent(1)==0) continue;
      else if(h1_qcd_clone[ibin]->GetBinContent(jbin)==0) {
	h1_qcd_shape[ibin]->SetBinContent(jbin, 0);
	h1_qcd_shape[ibin]->SetBinError(jbin, 0);
      }
      else {
	h1_qcd_shape[ibin]->SetBinContent(jbin, h1_qcd_clone[ibin]->GetBinContent(jbin)/h1_qcd_clone[ibin]->GetBinContent(1));
      }
    }
      //ttbar
    for(int jbin=1; jbin<4; jbin++) {
      if(h1_ttbar_clone[ibin]->GetBinContent(1)==0) continue;
      else if(h1_ttbar_clone[ibin]->GetBinContent(jbin)==0) {
	h1_ttbar_shape[ibin]->SetBinContent(jbin, 0);
	h1_ttbar_shape[ibin]->SetBinError(jbin, 0);
      }
      else {
	if(ibin==32) h1_ttbar_shape[ibin]->SetBinContent(jbin, (h1_ttbar_clone[32]->GetBinContent(jbin)+h1_ttbar_clone[35]->GetBinContent(jbin))/(h1_ttbar_clone[32]->GetBinContent(1)+h1_ttbar_clone[35]->GetBinContent(1)));
	else if(ibin==33) h1_ttbar_shape[ibin]->SetBinContent(jbin, (h1_ttbar_clone[33]->GetBinContent(jbin)+h1_ttbar_clone[36]->GetBinContent(jbin))/(h1_ttbar_clone[33]->GetBinContent(1)+h1_ttbar_clone[36]->GetBinContent(1)));
	else h1_ttbar_shape[ibin]->SetBinContent(jbin, h1_ttbar_clone[ibin]->GetBinContent(jbin)/h1_ttbar_clone[ibin]->GetBinContent(1));
	//h1_ttbar_shape[ibin]->SetBinContent(jbin, h1_ttbar_clone[ibin]->GetBinContent(jbin)/h1_ttbar_clone[ibin]->GetBinContent(1));
      }
    }
      //wjets
    for(int jbin=1; jbin<4; jbin++) {
      if(h1_wjets_clone[ibin]->GetBinContent(1)==0) continue;
      else if(h1_wjets_clone[ibin]->GetBinContent(jbin)==0) {
	h1_wjets_shape[ibin]->SetBinContent(jbin, 0);
	h1_wjets_shape[ibin]->SetBinError(jbin, 0);
      }
      else {
	if(ibin==32) h1_wjets_shape[ibin]->SetBinContent(jbin, (h1_wjets_clone[32]->GetBinContent(jbin)+h1_wjets_clone[35]->GetBinContent(jbin))/(h1_wjets_clone[32]->GetBinContent(1)+h1_wjets_clone[35]->GetBinContent(1)));
	else if(ibin==33) h1_wjets_shape[ibin]->SetBinContent(jbin, (h1_wjets_clone[33]->GetBinContent(jbin)+h1_wjets_clone[36]->GetBinContent(jbin))/(h1_wjets_clone[33]->GetBinContent(1)+h1_wjets_clone[36]->GetBinContent(1)));
	else h1_wjets_shape[ibin]->SetBinContent(jbin, h1_wjets_clone[ibin]->GetBinContent(jbin)/h1_wjets_clone[ibin]->GetBinContent(1));
	//h1_wjets_shape[ibin]->SetBinContent(jbin, h1_wjets_clone[ibin]->GetBinContent(jbin)/h1_wjets_clone[ibin]->GetBinContent(1));
      }
    }

/*
    h1_ttbar_shape[ibin]->SetBinContent(1, 1);
    h1_ttbar_shape[ibin]->SetBinContent(2, h1_ttbar_clone[ibin]->GetBinContent(2)/h1_ttbar_clone[ibin]->GetBinContent(1));
    h1_ttbar_shape[ibin]->SetBinContent(3, h1_ttbar_clone[ibin]->GetBinContent(3)/h1_ttbar_clone[ibin]->GetBinContent(1));
    h1_ttbar_shape[ibin]->SetBinError(1, h1_ttbar_clone[ibin]->GetBinError(1)/h1_ttbar_clone[ibin]->GetBinContent(1));
    h1_ttbar_shape[ibin]->SetBinError(2, GetShapeError(h1_ttbar_clone[ibin], 2));
    h1_ttbar_shape[ibin]->SetBinError(3, GetShapeError(h1_ttbar_clone[ibin], 3));

    h1_wjets_shape[ibin]->SetBinContent(1, 1);
    h1_wjets_shape[ibin]->SetBinContent(2, h1_wjets_clone[ibin]->GetBinContent(2)/h1_wjets_clone[ibin]->GetBinContent(1));
    h1_wjets_shape[ibin]->SetBinContent(3, h1_wjets_clone[ibin]->GetBinContent(3)/h1_wjets_clone[ibin]->GetBinContent(1));
    h1_wjets_shape[ibin]->SetBinError(1, h1_wjets_clone[ibin]->GetBinError(1)/h1_wjets_clone[ibin]->GetBinContent(1));
    h1_wjets_shape[ibin]->SetBinError(2, GetShapeError(h1_wjets_clone[ibin], 2));
    h1_wjets_shape[ibin]->SetBinError(3, GetShapeError(h1_wjets_clone[ibin], 3));
    */
  }

  //define r1 and r2 histogram
  TH1F *h1_qcd_njet45_r1, *h1_ttbar_njet45_r1, *h1_wjets_njet45_r1; //r1: mjbin[2]/mjbin[1]
  TH1F *h1_qcd_njet67_r1, *h1_ttbar_njet67_r1, *h1_wjets_njet67_r1;
  TH1F *h1_qcd_njet8_r1,  *h1_ttbar_njet8_r1,  *h1_wjets_njet8_r1;
  TH1F *h1_qcd_njet45_r2, *h1_ttbar_njet45_r2, *h1_wjets_njet45_r2; //r2: mjbin[3]/mjbin[1]
  TH1F *h1_qcd_njet67_r2, *h1_ttbar_njet67_r2, *h1_wjets_njet67_r2;
  TH1F *h1_qcd_njet8_r2,  *h1_ttbar_njet8_r2,  *h1_wjets_njet8_r2;
    //r1
  h1_qcd_njet45_r1 = new TH1F("h1_qcd_njet45_r1", "h1_qcd_njet45_r1", 5, -0.5, 4.5);
  h1_ttbar_njet45_r1 = new TH1F("h1_ttbar_njet45_r1", "h1_ttbar_njet45_r1", 5, -0.5, 4.5);
  h1_wjets_njet45_r1 = new TH1F("h1_wjets_njet45_r1", "h1_wjets_njet45_r1", 5, -0.5, 4.5);
  h1_qcd_njet67_r1 = new TH1F("h1_qcd_njet67_r1", "h1_qcd_njet67_r1", 5, -0.5, 4.5);
  h1_ttbar_njet67_r1 = new TH1F("h1_ttbar_njet67_r1", "h1_ttbar_njet67_r1", 5, -0.5, 4.5);
  h1_wjets_njet67_r1 = new TH1F("h1_wjets_njet67_r1", "h1_wjets_njet67_r1", 5, -0.5, 4.5);
  h1_qcd_njet8_r1 = new TH1F("h1_qcd_njet8_r1", "h1_qcd_njet8_r1", 5, -0.5, 4.5);
  h1_ttbar_njet8_r1 = new TH1F("h1_ttbar_njet8_r1", "h1_ttbar_njet8_r1", 5, -0.5, 4.5);
  h1_wjets_njet8_r1 = new TH1F("h1_wjets_njet8_r1", "h1_wjets_njet8_r1", 5, -0.5, 4.5);
    //r2
  h1_qcd_njet45_r2 = new TH1F("h1_qcd_njet45_r2", "h1_qcd_njet45_r2", 5, -0.5, 4.5);
  h1_ttbar_njet45_r2 = new TH1F("h1_ttbar_njet45_r2", "h1_ttbar_njet45_r2", 5, -0.5, 4.5);
  h1_wjets_njet45_r2 = new TH1F("h1_wjets_njet45_r2", "h1_wjets_njet45_r2", 5, -0.5, 4.5);
  h1_qcd_njet67_r2 = new TH1F("h1_qcd_njet67_r2", "h1_qcd_njet67_r2", 5, -0.5, 4.5);
  h1_ttbar_njet67_r2 = new TH1F("h1_ttbar_njet67_r2", "h1_ttbar_njet67_r2", 5, -0.5, 4.5);
  h1_wjets_njet67_r2 = new TH1F("h1_wjets_njet67_r2", "h1_wjets_njet67_r2", 5, -0.5, 4.5);
  h1_qcd_njet8_r2 = new TH1F("h1_qcd_njet8_r2", "h1_qcd_njet8_r2", 5, -0.5, 4.5);
  h1_ttbar_njet8_r2 = new TH1F("h1_ttbar_njet8_r2", "h1_ttbar_njet8_r2", 5, -0.5, 4.5);
  h1_wjets_njet8_r2 = new TH1F("h1_wjets_njet8_r2", "h1_wjets_njet8_r2", 5, -0.5, 4.5);
  //set values and errors
    //r1
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet45_r1->SetBinContent(ibin, h1_qcd_shape[22+3*(ibin-1)]->GetBinContent(2));
    h1_ttbar_njet45_r1->SetBinContent(ibin, h1_ttbar_shape[22+3*(ibin-1)]->GetBinContent(2));
    h1_wjets_njet45_r1->SetBinContent(ibin, h1_wjets_shape[22+3*(ibin-1)]->GetBinContent(2));
    if(ibin==5) {  // bin31 and bin34 have the same value
      h1_qcd_njet45_r1->SetBinContent(ibin, h1_qcd_shape[22+3*(ibin-2)]->GetBinContent(2));
      h1_ttbar_njet45_r1->SetBinContent(ibin, h1_ttbar_shape[22+3*(ibin-2)]->GetBinContent(2));
      h1_wjets_njet45_r1->SetBinContent(ibin, h1_wjets_shape[22+3*(ibin-2)]->GetBinContent(2));
    }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet67_r1->SetBinContent(ibin, h1_qcd_shape[23+3*(ibin-1)]->GetBinContent(2));
    h1_ttbar_njet67_r1->SetBinContent(ibin, h1_ttbar_shape[23+3*(ibin-1)]->GetBinContent(2));
    h1_wjets_njet67_r1->SetBinContent(ibin, h1_wjets_shape[23+3*(ibin-1)]->GetBinContent(2));
    if(ibin==5) {  // bin32 and bin35 have the same value
      h1_qcd_njet67_r1->SetBinContent(ibin, h1_qcd_shape[23+3*(ibin-2)]->GetBinContent(2));
      h1_ttbar_njet67_r1->SetBinContent(ibin, h1_ttbar_shape[23+3*(ibin-2)]->GetBinContent(2));
      h1_wjets_njet67_r1->SetBinContent(ibin, h1_wjets_shape[23+3*(ibin-2)]->GetBinContent(2));
    }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet8_r1->SetBinContent(ibin, h1_qcd_shape[24+3*(ibin-1)]->GetBinContent(2));
    h1_ttbar_njet8_r1->SetBinContent(ibin, h1_ttbar_shape[24+3*(ibin-1)]->GetBinContent(2));
    h1_wjets_njet8_r1->SetBinContent(ibin, h1_wjets_shape[24+3*(ibin-1)]->GetBinContent(2));
    if(ibin==5) {  // bin33 and bin36 have the same value
      h1_qcd_njet8_r1->SetBinContent(ibin, h1_qcd_shape[24+3*(ibin-2)]->GetBinContent(2));
      h1_ttbar_njet8_r1->SetBinContent(ibin, h1_ttbar_shape[24+3*(ibin-2)]->GetBinContent(2));
      h1_wjets_njet8_r1->SetBinContent(ibin, h1_wjets_shape[24+3*(ibin-2)]->GetBinContent(2));
    }
  }
    //r2
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet45_r2->SetBinContent(ibin, h1_qcd_shape[22+3*(ibin-1)]->GetBinContent(3));
    h1_ttbar_njet45_r2->SetBinContent(ibin, h1_ttbar_shape[22+3*(ibin-1)]->GetBinContent(3));
    h1_wjets_njet45_r2->SetBinContent(ibin, h1_wjets_shape[22+3*(ibin-1)]->GetBinContent(3));
    if(ibin==5) {  // bin31 and bin34 have the same value
      h1_qcd_njet45_r2->SetBinContent(ibin, h1_qcd_shape[22+3*(ibin-2)]->GetBinContent(3));
      h1_ttbar_njet45_r2->SetBinContent(ibin, h1_ttbar_shape[22+3*(ibin-2)]->GetBinContent(3));
      h1_wjets_njet45_r2->SetBinContent(ibin, h1_wjets_shape[22+3*(ibin-2)]->GetBinContent(3));
    }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet67_r2->SetBinContent(ibin, h1_qcd_shape[23+3*(ibin-1)]->GetBinContent(3));
    h1_ttbar_njet67_r2->SetBinContent(ibin, h1_ttbar_shape[23+3*(ibin-1)]->GetBinContent(3));
    h1_wjets_njet67_r2->SetBinContent(ibin, h1_wjets_shape[23+3*(ibin-1)]->GetBinContent(3));
    if(ibin==5) {  // bin32 and bin35 have the same value
      h1_qcd_njet67_r2->SetBinContent(ibin, h1_qcd_shape[23+3*(ibin-2)]->GetBinContent(3));
      h1_ttbar_njet67_r2->SetBinContent(ibin, h1_ttbar_shape[23+3*(ibin-2)]->GetBinContent(3));
      h1_wjets_njet67_r2->SetBinContent(ibin, h1_wjets_shape[23+3*(ibin-2)]->GetBinContent(3));
    }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    h1_qcd_njet8_r2->SetBinContent(ibin, h1_qcd_shape[24+3*(ibin-1)]->GetBinContent(3));
    h1_ttbar_njet8_r2->SetBinContent(ibin, h1_ttbar_shape[24+3*(ibin-1)]->GetBinContent(3));
    h1_wjets_njet8_r2->SetBinContent(ibin, h1_wjets_shape[24+3*(ibin-1)]->GetBinContent(3));
    if(ibin==5) {  // bin33 and bin36 have the same value
      h1_qcd_njet8_r2->SetBinContent(ibin, h1_qcd_shape[24+3*(ibin-2)]->GetBinContent(3));
      h1_ttbar_njet8_r2->SetBinContent(ibin, h1_ttbar_shape[24+3*(ibin-2)]->GetBinContent(3));
      h1_wjets_njet8_r2->SetBinContent(ibin, h1_wjets_shape[24+3*(ibin-2)]->GetBinContent(3));
    }
  }

  //define normalized r1 and r2 histogram
  TH1F *h1_qcd_njet45_norm_r1, *h1_ttbar_njet45_norm_r1, *h1_wjets_njet45_norm_r1; //r1: mjbin[2]/mjbin[1]
  TH1F *h1_qcd_njet67_norm_r1, *h1_ttbar_njet67_norm_r1, *h1_wjets_njet67_norm_r1;
  TH1F *h1_qcd_njet8_norm_r1,  *h1_ttbar_njet8_norm_r1,  *h1_wjets_njet8_norm_r1;
  TH1F *h1_qcd_njet45_norm_r2, *h1_ttbar_njet45_norm_r2, *h1_wjets_njet45_norm_r2; //r2: mjbin[3]/mjbin[1]
  TH1F *h1_qcd_njet67_norm_r2, *h1_ttbar_njet67_norm_r2, *h1_wjets_njet67_norm_r2;
  TH1F *h1_qcd_njet8_norm_r2,  *h1_ttbar_njet8_norm_r2,  *h1_wjets_njet8_norm_r2;
    //r1
  h1_qcd_njet45_norm_r1 = new TH1F("h1_qcd_njet45_norm_r1", "h1_qcd_njet45_norm_r1", 5, -0.5, 4.5);
  h1_ttbar_njet45_norm_r1 = new TH1F("h1_ttbar_njet45_norm_r1", "h1_ttbar_njet45_norm_r1", 5, -0.5, 4.5);
  h1_wjets_njet45_norm_r1 = new TH1F("h1_wjets_njet45_norm_r1", "h1_wjets_njet45_norm_r1", 5, -0.5, 4.5);
  h1_qcd_njet67_norm_r1 = new TH1F("h1_qcd_njet67_norm_r1", "h1_qcd_njet67_norm_r1", 5, -0.5, 4.5);
  h1_ttbar_njet67_norm_r1 = new TH1F("h1_ttbar_njet67_norm_r1", "h1_ttbar_njet67_norm_r1", 5, -0.5, 4.5);
  h1_wjets_njet67_norm_r1 = new TH1F("h1_wjets_njet67_norm_r1", "h1_wjets_njet67_norm_r1", 5, -0.5, 4.5);
  h1_qcd_njet8_norm_r1 = new TH1F("h1_qcd_njet8_norm_r1", "h1_qcd_njet8_norm_r1", 5, -0.5, 4.5);
  h1_ttbar_njet8_norm_r1 = new TH1F("h1_ttbar_njet8_norm_r1", "h1_ttbar_njet8_norm_r1", 5, -0.5, 4.5);
  h1_wjets_njet8_norm_r1 = new TH1F("h1_wjets_njet8_norm_r1", "h1_wjets_njet8_norm_r1", 5, -0.5, 4.5);
    //r2
  h1_qcd_njet45_norm_r2 = new TH1F("h1_qcd_njet45_norm_r2", "h1_qcd_njet45_norm_r2", 5, -0.5, 4.5);
  h1_ttbar_njet45_norm_r2 = new TH1F("h1_ttbar_njet45_norm_r2", "h1_ttbar_njet45_norm_r2", 5, -0.5, 4.5);
  h1_wjets_njet45_norm_r2 = new TH1F("h1_wjets_njet45_norm_r2", "h1_wjets_njet45_norm_r2", 5, -0.5, 4.5);
  h1_qcd_njet67_norm_r2 = new TH1F("h1_qcd_njet67_norm_r2", "h1_qcd_njet67_norm_r2", 5, -0.5, 4.5);
  h1_ttbar_njet67_norm_r2 = new TH1F("h1_ttbar_njet67_norm_r2", "h1_ttbar_njet67_norm_r2", 5, -0.5, 4.5);
  h1_wjets_njet67_norm_r2 = new TH1F("h1_wjets_njet67_norm_r2", "h1_wjets_njet67_norm_r2", 5, -0.5, 4.5);
  h1_qcd_njet8_norm_r2 = new TH1F("h1_qcd_njet8_norm_r2", "h1_qcd_njet8_norm_r2", 5, -0.5, 4.5);
  h1_ttbar_njet8_norm_r2 = new TH1F("h1_ttbar_njet8_norm_r2", "h1_ttbar_njet8_norm_r2", 5, -0.5, 4.5);
  h1_wjets_njet8_norm_r2 = new TH1F("h1_wjets_njet8_norm_r2", "h1_wjets_njet8_norm_r2", 5, -0.5, 4.5);

    //r1
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet45_r1->GetBinContent(ibin)==0) {
      h1_ttbar_njet45_norm_r1->SetBinContent(ibin, 0);
      h1_ttbar_njet45_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet45_norm_r1->SetBinContent(ibin, h1_ttbar_njet45_r1->GetBinContent(2)/h1_ttbar_njet45_r1->GetBinContent(ibin));  // denominator is ratio of 1 and 2 or 1 and 3 MJ bin of Nb==0(Nb==1) for W+jets(ttbar), and numerator is other Nb bins, because it will be multiplied by yields of 2nd and 3rd MJ bin later (python/outputfix_mjsyst.py)
      h1_ttbar_njet45_norm_r1->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet45_r1, ibin)); }
  }
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet45_r1->GetBinContent(ibin)==0) {
      h1_wjets_njet45_norm_r1->SetBinContent(ibin, 0);
      h1_wjets_njet45_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet45_norm_r1->SetBinContent(ibin, h1_wjets_njet45_r1->GetBinContent(1)/h1_wjets_njet45_r1->GetBinContent(ibin));
      h1_wjets_njet45_norm_r1->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet45_r1, ibin)); }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet67_r1->GetBinContent(ibin)==0) {
      h1_ttbar_njet67_norm_r1->SetBinContent(ibin, 0);
      h1_ttbar_njet67_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet67_norm_r1->SetBinContent(ibin, h1_ttbar_njet67_r1->GetBinContent(2)/h1_ttbar_njet67_r1->GetBinContent(ibin));
      h1_ttbar_njet67_norm_r1->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet67_r1, ibin)); }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet67_r1->GetBinContent(ibin)==0) {
      h1_wjets_njet67_norm_r1->SetBinContent(ibin, 0);
      h1_wjets_njet67_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet67_norm_r1->SetBinContent(ibin, h1_wjets_njet67_r1->GetBinContent(1)/h1_wjets_njet67_r1->GetBinContent(ibin));
      h1_wjets_njet67_norm_r1->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet67_r1, ibin)); }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet8_r1->GetBinContent(ibin)==0) {
      h1_ttbar_njet8_norm_r1->SetBinContent(ibin, 0);
      h1_ttbar_njet8_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet8_norm_r1->SetBinContent(ibin, h1_ttbar_njet8_r1->GetBinContent(2)/h1_ttbar_njet8_r1->GetBinContent(ibin));
      h1_ttbar_njet8_norm_r1->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet8_r1, ibin)); }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet8_r1->GetBinContent(ibin)==0) {
      h1_wjets_njet8_norm_r1->SetBinContent(ibin, 0);
      h1_wjets_njet8_norm_r1->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet8_norm_r1->SetBinContent(ibin, h1_wjets_njet8_r1->GetBinContent(1)/h1_wjets_njet8_r1->GetBinContent(ibin));
      h1_wjets_njet8_norm_r1->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet8_r1, ibin)); }
  }

    //r2
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet45_r2->GetBinContent(ibin)==0) {
      h1_ttbar_njet45_norm_r2->SetBinContent(ibin, 0);
      h1_ttbar_njet45_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet45_norm_r2->SetBinContent(ibin, h1_ttbar_njet45_r2->GetBinContent(2)/h1_ttbar_njet45_r2->GetBinContent(ibin));
      h1_ttbar_njet45_norm_r2->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet45_r2, ibin)); }
  }
      //njet45
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet45_r2->GetBinContent(ibin)==0) {
      h1_wjets_njet45_norm_r2->SetBinContent(ibin, 0);
      h1_wjets_njet45_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet45_norm_r2->SetBinContent(ibin, h1_wjets_njet45_r2->GetBinContent(1)/h1_wjets_njet45_r2->GetBinContent(ibin));
      h1_wjets_njet45_norm_r2->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet45_r2, ibin)); }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet67_r2->GetBinContent(ibin)==0) {
      h1_ttbar_njet67_norm_r2->SetBinContent(ibin, 0);
      h1_ttbar_njet67_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet67_norm_r2->SetBinContent(ibin, h1_ttbar_njet67_r2->GetBinContent(2)/h1_ttbar_njet67_r2->GetBinContent(ibin));
      h1_ttbar_njet67_norm_r2->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet67_r2, ibin)); }
  }
      //njet67
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet67_r2->GetBinContent(ibin)==0) {
      h1_wjets_njet67_norm_r2->SetBinContent(ibin, 0);
      h1_wjets_njet67_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet67_norm_r2->SetBinContent(ibin, h1_wjets_njet67_r2->GetBinContent(1)/h1_wjets_njet67_r2->GetBinContent(ibin));
      h1_wjets_njet67_norm_r2->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet67_r2, ibin)); }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_ttbar_njet8_r2->GetBinContent(ibin)==0) {
      h1_ttbar_njet8_norm_r2->SetBinContent(ibin, 0);
      h1_ttbar_njet8_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_ttbar_njet8_norm_r2->SetBinContent(ibin, h1_ttbar_njet8_r2->GetBinContent(2)/h1_ttbar_njet8_r2->GetBinContent(ibin));
      h1_ttbar_njet8_norm_r2->SetBinError(ibin, GetShapeError_ttbar(h1_ttbar_njet8_r2, ibin)); }
  }
      //njet8
  for(int ibin=1; ibin<6; ibin++) {
    if(h1_wjets_njet8_r2->GetBinContent(ibin)==0) {
      h1_wjets_njet8_norm_r2->SetBinContent(ibin, 0);
      h1_wjets_njet8_norm_r2->SetBinError(ibin, 0);   }
    else {
      h1_wjets_njet8_norm_r2->SetBinContent(ibin, h1_wjets_njet8_r2->GetBinContent(1)/h1_wjets_njet8_r2->GetBinContent(ibin));
      h1_wjets_njet8_norm_r2->SetBinError(ibin, GetShapeError_wjets(h1_wjets_njet8_r2, ibin)); }
  }

//----------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

  TFile *mjsyst_ttbar = new TFile("plots/mjsyst/"+year+"/mjsyst_ttbar_"+year+".root", "recreate");
  TFile *mjsyst_wjets = new TFile("plots/mjsyst/"+year+"/mjsyst_wjets_"+year+".root", "recreate");
  mjsyst_ttbar->cd();
  h1_ttbar_njet45_norm_r1->Write();
  h1_ttbar_njet67_norm_r1->Write();
  h1_ttbar_njet8_norm_r1->Write();
  h1_ttbar_njet45_norm_r2->Write();
  h1_ttbar_njet67_norm_r2->Write();
  h1_ttbar_njet8_norm_r2->Write();
  mjsyst_ttbar->Close();
  mjsyst_wjets->cd();
  h1_wjets_njet45_norm_r1->Write();
  h1_wjets_njet67_norm_r1->Write();
  h1_wjets_njet8_norm_r1->Write();
  h1_wjets_njet45_norm_r2->Write();
  h1_wjets_njet67_norm_r2->Write();
  h1_wjets_njet8_norm_r2->Write();
  mjsyst_wjets->Close();


  //visualization
  TH1F *h1_ttbar_summary_r1 = new TH1F("h1_ttbar_summary_r1", "h1_ttbar_summary_r1", 75, 0, 75);
  TH1F *h1_wjets_summary_r1 = new TH1F("h1_wjets_summary_r1", "h1_wjets_summary_r1", 75, 0, 75);
  TH1F *h1_ttbar_summary_r2 = new TH1F("h1_ttbar_summary_r2", "h1_ttbar_summary_r2", 75, 0, 75);
  TH1F *h1_wjets_summary_r2 = new TH1F("h1_wjets_summary_r2", "h1_wjets_summary_r2", 75, 0, 75);

  for(int ibin=1; ibin<6; ibin++) {
    //r1
    h1_ttbar_summary_r1->SetBinContent(8+2*(ibin-1), h1_ttbar_njet45_norm_r1->GetBinContent(ibin));
    h1_ttbar_summary_r1->SetBinContent(33+2*(ibin-1), h1_ttbar_njet67_norm_r1->GetBinContent(ibin));
    h1_ttbar_summary_r1->SetBinContent(58+2*(ibin-1), h1_ttbar_njet8_norm_r1->GetBinContent(ibin));
    h1_wjets_summary_r1->SetBinContent(8+2*(ibin-1), h1_wjets_njet45_norm_r1->GetBinContent(ibin));
    h1_wjets_summary_r1->SetBinContent(33+2*(ibin-1), h1_wjets_njet67_norm_r1->GetBinContent(ibin));
    h1_wjets_summary_r1->SetBinContent(58+2*(ibin-1), h1_wjets_njet8_norm_r1->GetBinContent(ibin));
    h1_ttbar_summary_r1->SetBinError(8+2*(ibin-1), h1_ttbar_njet45_norm_r1->GetBinError(ibin));
    h1_ttbar_summary_r1->SetBinError(33+2*(ibin-1), h1_ttbar_njet67_norm_r1->GetBinError(ibin));
    h1_ttbar_summary_r1->SetBinError(58+2*(ibin-1), h1_ttbar_njet8_norm_r1->GetBinError(ibin));
    h1_wjets_summary_r1->SetBinError(8+2*(ibin-1), h1_wjets_njet45_norm_r1->GetBinError(ibin));
    h1_wjets_summary_r1->SetBinError(33+2*(ibin-1), h1_wjets_njet67_norm_r1->GetBinError(ibin));
    h1_wjets_summary_r1->SetBinError(58+2*(ibin-1), h1_wjets_njet8_norm_r1->GetBinError(ibin));
    //r2
    h1_ttbar_summary_r2->SetBinContent(8+2*(ibin-1), h1_ttbar_njet45_norm_r2->GetBinContent(ibin));
    h1_ttbar_summary_r2->SetBinContent(33+2*(ibin-1), h1_ttbar_njet67_norm_r2->GetBinContent(ibin));
    h1_ttbar_summary_r2->SetBinContent(58+2*(ibin-1), h1_ttbar_njet8_norm_r2->GetBinContent(ibin));
    h1_wjets_summary_r2->SetBinContent(8+2*(ibin-1), h1_wjets_njet45_norm_r2->GetBinContent(ibin));
    h1_wjets_summary_r2->SetBinContent(33+2*(ibin-1), h1_wjets_njet67_norm_r2->GetBinContent(ibin));
    h1_wjets_summary_r2->SetBinContent(58+2*(ibin-1), h1_wjets_njet8_norm_r2->GetBinContent(ibin));
    h1_ttbar_summary_r2->SetBinError(8+2*(ibin-1), h1_ttbar_njet45_norm_r2->GetBinError(ibin));
    h1_ttbar_summary_r2->SetBinError(33+2*(ibin-1), h1_ttbar_njet67_norm_r2->GetBinError(ibin));
    h1_ttbar_summary_r2->SetBinError(58+2*(ibin-1), h1_ttbar_njet8_norm_r2->GetBinError(ibin));
    h1_wjets_summary_r2->SetBinError(8+2*(ibin-1), h1_wjets_njet45_norm_r2->GetBinError(ibin));
    h1_wjets_summary_r2->SetBinError(33+2*(ibin-1), h1_wjets_njet67_norm_r2->GetBinError(ibin));
    h1_wjets_summary_r2->SetBinError(58+2*(ibin-1), h1_wjets_njet8_norm_r2->GetBinError(ibin));
  }

  //save plot and root file
  TString plotpath = "plots/mjsyst/"+year+"/";
  TFile *ttbar_summary = new TFile(plotpath+"mjsyst_ttbar_summary_"+year+".root", "recreate");
  TFile *wjets_summary = new TFile(plotpath+"mjsyst_wjets_summary_"+year+".root", "recreate");
  ttbar_summary->cd(); h1_ttbar_summary_r1->Write(); h1_ttbar_summary_r2->Write();
  wjets_summary->cd(); h1_wjets_summary_r1->Write(); h1_wjets_summary_r2->Write();

  infile->Close();

}
float GetShapeError(TH1F *h1, int ibin)
{
  float err=0;
  if(h1->GetBinContent(ibin)==0) err=0;
  else err = (h1->GetBinContent(ibin)/h1->GetBinContent(1))*TMath::Sqrt(TMath::Power(h1->GetBinError(1)/h1->GetBinContent(1),2)+TMath::Power(h1->GetBinError(ibin)/h1->GetBinContent(ibin),2));
  return err;
}

float GetShapeError_ttbar(TH1F *h1, int ibin)
{
  float err=0;
  if(h1->GetBinContent(ibin)==0) err=0;
  else err = (h1->GetBinContent(2)/h1->GetBinContent(ibin))*TMath::Sqrt(TMath::Power(h1->GetBinError(1)/h1->GetBinContent(1),2)+TMath::Power(h1->GetBinError(ibin)/h1->GetBinContent(ibin),2)); // nb=1 is a reference nb region for ttbar
  return err;
}

float GetShapeError_wjets(TH1F *h1, int ibin)
{
  float err=0;
  if(h1->GetBinContent(ibin)==0) err=0;
  else err = (h1->GetBinContent(1)/h1->GetBinContent(ibin))*TMath::Sqrt(TMath::Power(h1->GetBinError(1)/h1->GetBinContent(1),2)+TMath::Power(h1->GetBinError(ibin)/h1->GetBinContent(ibin),2)); // nb=0 is a reference nb region for wjets
  return err;
}
