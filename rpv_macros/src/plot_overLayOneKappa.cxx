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

using namespace std;

void set_legend_style(TLegend *l){
	l->SetFillColor(0);
	l->SetLineColor(0);
	l->SetLineStyle(kSolid);
	l->SetLineWidth(1);
	l->SetFillStyle(1001);
	l->SetTextFont(42);
	l->SetTextSize(0.07);
}

void drawHeader(TString year){
  TLatex *lat = new TLatex;
  lat->SetTextSize(0.053);
  lat->DrawLatexNDC(0.12, 0.83, "CMS #scale[0.8]{#font[52]{Work In Progress}}");
  lat->SetTextFont(42);
  if(year=="2016") lat->DrawLatexNDC(0.76, 0.83, "36.3 fb^{-1} (13 TeV)");//FIXME
  else if(year=="2017") lat->DrawLatexNDC(0.76, 0.83, "41.5 fb^{-1} (13 TeV)");//FIXME
  else if(year=="2018") lat->DrawLatexNDC(0.76, 0.83, "59.8 fb^{-1} (13 TeV)");//FIXME
  else if(year=="20178") lat->DrawLatexNDC(0.76, 0.83, "101.3 fb^{-1} (13 TeV)");//FIXME
}

int main(int argc, char *argv[]){
	
	gStyle->SetOptStat(0);

	TString Systematic, year;

	Systematic = argv[1];
	year = argv[2];

	if(argc<2){
		cout << "[Error] Not Enough Arguments! argument \"--help\" may help you" << endl;
		return 1;
	}

	if(Systematic == "--help" || argc<3){
		cout << "" <<endl;
		cout << "./run/plot_overLayKappa.exe [Systematic] [year]" << endl;
		cout << "" <<endl;
		cout << "Systematic: jec,btag_bc,btag_udsg,mur,muf,murf,isr,leps_eff" << endl;
		cout << "year: 2016, 2017, 2018" << endl;
		cout << "" << endl;
		return 1;
	}

	TFile *f1, *f2 ,*f3;
	TH1D *h1, *h2, *h3, *h4;
	TH1D *hn1, *hn2;
	TLegend *l1, *l2;

//	l1 = new TLegend(0.65,0.54,0.75,0.8);
//	l2 = new TLegend(0.65,0.54,0.75,0.8);
	l1 = new TLegend(0.55,0.65,0.65,0.85);
	l2 = new TLegend(0.55,0.65,0.65,0.85);

	set_legend_style(l1);
	set_legend_style(l2);

	TCanvas *c;
	c = new TCanvas;
	c->Divide(1,2);

	f1 = new TFile("plots/kappa/"+year+"/kappa_summary_"+Systematic+"Up_"+year+".root");
	f2 = new TFile("plots/kappa/"+year+"/kappa_summary_"+Systematic+"Down_"+year+".root");
	f3 = new TFile("plots/kappa/"+year+"/kappa_summary_nominalX_"+year+".root");
	h1 = (TH1D*)f1->Get("h1_1l_summary1");
	h2 = (TH1D*)f2->Get("h1_1l_summary1");
	h3 = (TH1D*)f1->Get("h1_1l_summary2");
	h4 = (TH1D*)f2->Get("h1_1l_summary2");
	hn1 = (TH1D*)f3->Get("h1_1l_summary1");
	hn2 = (TH1D*)f3->Get("h1_1l_summary2");

	h1->SetMarkerStyle(22);
	h2->SetMarkerStyle(32);
	h3->SetMarkerStyle(22);
	h4->SetMarkerStyle(32);
	h1->SetMarkerColor(kRed-4);
	h2->SetMarkerColor(kAzure+1);
	h3->SetMarkerColor(kRed-4);
	h4->SetMarkerColor(kAzure+1);
	h1->SetMarkerSize(0.5);
	h2->SetMarkerSize(0.5);
	h3->SetMarkerSize(0.5);
	h4->SetMarkerSize(0.5);
	h1->SetLineColor(kRed+1);
	h2->SetLineColor(kAzure-1);
	h3->SetLineColor(kRed+1);
	h4->SetLineColor(kAzure-1);

	l1->AddEntry(h1,Systematic+" 1#sigma up","p");
	l1->AddEntry(h2,Systematic+" 1#sigma down", "p");
	l2->AddEntry(h3,Systematic+" 1#sigma up","p");
	l2->AddEntry(h4,Systematic+" 1#sigma down","p");


  // set bin label
  hn1->GetXaxis()->SetLabelSize(0.05);
  hn1->GetXaxis()->SetBinLabel(8,  "N_{b}=0");
  hn1->GetXaxis()->SetBinLabel(33, "N_{b}=0");
  hn1->GetXaxis()->SetBinLabel(58, "N_{b}=0");
  hn1->GetXaxis()->SetBinLabel(10, "N_{b}=1");
  hn1->GetXaxis()->SetBinLabel(35, "N_{b}=1");
  hn1->GetXaxis()->SetBinLabel(60, "N_{b}=1");
  hn1->GetXaxis()->SetBinLabel(12, "N_{b}=2");
  hn1->GetXaxis()->SetBinLabel(37, "N_{b}=2");
  hn1->GetXaxis()->SetBinLabel(62, "N_{b}=2");
  hn1->GetXaxis()->SetBinLabel(14, "N_{b}#geq 3");
  hn1->GetXaxis()->SetBinLabel(39, "N_{b}=3");
  hn1->GetXaxis()->SetBinLabel(64, "N_{b}=3");
  hn1->GetXaxis()->SetBinLabel(41, "N_{b}#geq 4");
  hn1->GetXaxis()->SetBinLabel(66, "N_{b}#geq 4");
 
  hn2->GetXaxis()->SetLabelSize(0.05);
  hn2->GetXaxis()->SetBinLabel(8,  "N_{b}=0");
  hn2->GetXaxis()->SetBinLabel(33, "N_{b}=0");
  hn2->GetXaxis()->SetBinLabel(58, "N_{b}=0");
  hn2->GetXaxis()->SetBinLabel(10, "N_{b}=1");
  hn2->GetXaxis()->SetBinLabel(35, "N_{b}=1");
  hn2->GetXaxis()->SetBinLabel(60, "N_{b}=1");
  hn2->GetXaxis()->SetBinLabel(12, "N_{b}=2");
  hn2->GetXaxis()->SetBinLabel(37, "N_{b}=2");
  hn2->GetXaxis()->SetBinLabel(62, "N_{b}=2");
  hn2->GetXaxis()->SetBinLabel(14, "N_{b}#geq 3");
  hn2->GetXaxis()->SetBinLabel(39, "N_{b}=3");
  hn2->GetXaxis()->SetBinLabel(64, "N_{b}=3");
  hn2->GetXaxis()->SetBinLabel(41, "N_{b}#geq 4");
  hn2->GetXaxis()->SetBinLabel(66, "N_{b}#geq 4");

  //  
  hn1->SetTitle("N_{jets}=4-5                                          N_{jets}=6-7                                          N_{jets}#geq 8        ");
  hn2->SetTitle("N_{jets}=4-5                                          N_{jets}=6-7                                          N_{jets}#geq 8        ");

  // 
  hn1->GetYaxis()->SetTitle("#kappa_{1}");
  hn1->GetYaxis()->SetTitleSize(0.05);
  hn2->GetYaxis()->SetTitle("#kappa_{2}");
  hn2->GetYaxis()->SetTitleSize(0.05);

  hn1->SetFillColor(kGray);
  hn1->SetFillStyle(1001);
  hn2->SetFillColor(kGray);
  hn2->SetFillStyle(1001);
  
  hn1->SetMaximum(1.5);
  hn1->SetMinimum(0.5);
  hn2->SetMaximum(1.5);
  hn2->SetMinimum(0.5);

 
	c->cd(1);
//	hn1->Draw();
	hn1->Draw("e2");
	h1->Draw("same hist p");
	h2->Draw("same hist p");
	drawHeader(year);
	l1->Draw();

	c->cd(2);
//	hn2->Draw();
	hn2->Draw("e2");
	h3->Draw("same hist p");
	h4->Draw("same hist p");
	drawHeader(year);
	l2->Draw();

	c->SaveAs("plots/kappa/"+year+"/overlay_one_kappa"+Systematic+"_"+year+".pdf");
	c->SaveAs("plots/kappa/"+year+"/overlay_one_kappa"+Systematic+"_"+year+".png");
}
