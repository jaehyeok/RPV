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

void drawHeader(){
  TLatex *lat = new TLatex;
  lat->SetTextSize(0.053);
  lat->DrawLatexNDC(0.12, 0.93, "CMS #scale[0.8]{#font[52]{Work In Progress}}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.78, 0.93, "36.3 fb^{-1} (13 TeV)");//FIXME
//  lat->DrawLatexNDC(0.78, 0.93, "101.3 fb^{-1} (13 TeV)");//FIXME
}

int main(int argc, char *argv[]){

	TString Systematic, year, outdir;

	Systematic = argv[1];
	year = argv[2];

	if(argc<2){
		cout << "[Error] Not Enough Arguments! argument \"--help\" may help you" << endl;
		return 1;
	}

	if(Systematic == "--help" || argc<2){
		cout << "" <<endl;
		cout << "./run/plot_overLayKappa.exe [Systematic] [year]" << endl;
		cout << "" <<endl;
		cout << "Systematic: jec,btag_bc,btag_udsg,mur,muf,murf,isr,gs,jer" << endl;
		cout << "year: 2016, 2017, 2018" << endl;
		cout << "" << endl;
		return 1;
	}

	TFile *f1, *f2, *f3, *f4;
	TH1D *h1, *h2, *h3, *h4;
	TLegend *l1, *l2;

	l1 = new TLegend(0.65,0.54,0.75,0.8);
	l2 = new TLegend(0.65,0.54,0.75,0.8);

	set_legend_style(l1);
	set_legend_style(l2);

	TCanvas *c;
	c = new TCanvas;
	c->Divide(1,2);

	f1 = new TFile("plots/kappa/"+year+"/kappa_summary_"+Systematic+"Up_"+year+".root");
	f2 = new TFile("plots/kappa/"+year+"/kappa_summary_"+Systematic+"Down_"+year+".root");
	h1 = (TH1D*)f1->Get("h1_1l_summary1");
	h2 = (TH1D*)f2->Get("h1_1l_summary1");
	h3 = (TH1D*)f1->Get("h1_1l_summary2");
	h4 = (TH1D*)f2->Get("h1_1l_summary2");

	h1->SetMarkerStyle(kFullTriangleDown);
	h2->SetMarkerStyle(kOpenCircle);
	h3->SetMarkerStyle(kFullTriangleDown);
	h4->SetMarkerStyle(kOpenCircle);
	h1->SetMarkerColor(kRed);
	h2->SetMarkerColor(kBlue);
	h3->SetMarkerColor(kRed);
	h4->SetMarkerColor(kBlue);

	l1->AddEntry(h1,Systematic+" 1#sigma Up","p");
	l1->AddEntry(h2,Systematic+" 1#sigma Down","p");
	l2->AddEntry(h3,Systematic+" 1#sigma Up","p");
	l2->AddEntry(h4,Systematic+" 1#sigma Down","p");

	c->cd(1);
	h1->Draw();
	h2->Draw("same");
	drawHeader();
	l1->Draw();

	c->cd(2);
	h3->Draw();
	h4->Draw("same");
	drawHeader();
	l2->Draw();
	c->SaveAs("plots/kappa/"+year+"/overlay_kappa"+Systematic+"_"+year+".png");
	c->SaveAs("plots/kappa/"+year+"/overlay_kappa"+Systematic+"_"+year+".pdf");
}
