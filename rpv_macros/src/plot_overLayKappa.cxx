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

int main(int argc, char *argv[]){

	TString Systematic1, Systematic2, Scale, year;

	Systematic1 = argv[1];
	Systematic2 = argv[2];
	Scale = argv[3];
	year = argv[4];

	if(Systematic1 == "--help" || argc<3){
		cout << "" <<endl;
		cout << "./run/plot_overLayKappa.exe [Systematic1] [Systematic2] [Up/Down] [year]" << endl;
		cout << "" <<endl;
		cout << "Systematic1: JES,btag_bc,btag_udsg,mur,muf,murf,ISR" << endl;
		cout << "Systematic2: JES,btag_bc,btag_udsg,mur,muf,murf,ISR" << endl;
		cout << "Up/Down: Up or Down" << endl;
		cout << "year: 2016, 2017, 2018" << endl;
		cout << "" << endl;
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

	f1 = new TFile("plots/kappa/kappa_summary_"+Systematic1+Scale+year+".root");
	f2 = new TFile("plots/kappa/kappa_summary_"+Systematic2+Scale+year+".root");
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

	l1->AddEntry(h1,Systematic1+" 1#sigma "+Scale,"p");
	l1->AddEntry(h2,Systematic2+" 1#sigma "+Scale,"p");
	l2->AddEntry(h3,Systematic1+" 1#sigma "+Scale,"p");
	l2->AddEntry(h4,Systematic2+" 1#sigma "+Scale,"p");

	c->cd(1);
	h1->Draw();
	h2->Draw("same");
	l1->Draw();

	c->cd(2);
	h3->Draw();
	h4->Draw("same");
	l2->Draw();
	c->SaveAs("plots/kappa/overlay_kappa"+Systematic1+"vs"+Systematic2+Scale+year+".png");
}
