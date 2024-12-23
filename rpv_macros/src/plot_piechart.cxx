#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TPie.h"
#include "TLegend.h"
#include "TPieSlice.h"
#include "TDirectory.h"
#include "TString.h"
#include "TLatex.h"
#include "TSystem.h"

using namespace std;

void set_piechart(TPie *p_opt){
	p_opt->GetSlice(0)->SetTitle("QCD");
	p_opt->GetSlice(1)->SetTitle("t#bar{t}");
	p_opt->GetSlice(2)->SetTitle("W+jets");
	p_opt->GetSlice(3)->SetTitle("Other");
	p_opt->GetSlice(4)->SetTitle("m_{gluino} = 1800 GeV");
	p_opt->SetTextSize(0.038);
	p_opt->SetRadius(.40);
	p_opt->SetLabelsOffset(-.26);
	p_opt->SetLabelFormat("#splitline{%val (%perc)}{%txt}");
}

int main(int argc, char *argv[])
{
	TString inputdir, outputdir, year, infile;
	year = argv[1];
	TString test = argv[1];
	infile = argv[2];

	inputdir = "variations/";
	outputdir = "plots/pie_"+year+"/";
	gSystem->mkdir(outputdir);

	if(test == "--help" || argc<1){
		cout<<"./run/plot_piechart.exe [year] [infile]"<<endl;
	}

	TFile* f = TFile::Open(infile.Data(), "READ"); // for QCD kappa factor region

	const int nbins = 52;

	float qcd[nbins][3], ttbar[nbins][3], wjets[nbins][3], other[nbins][3], sig1800[nbins][3];
	for(int ibin=0; ibin<nbins; ibin++){
		for(int iMj=0; iMj<3; iMj++){
			qcd[ibin][iMj] = 0;
			ttbar[ibin][iMj] = 0;
			wjets[ibin][iMj] = 0;
			other[ibin][iMj] = 0;
			sig1800[ibin][iMj] = 0;
		}
	}

	for(int ibin=22; ibin<nbins; ibin++){
		for(int iMj=0; iMj<3; iMj++){
			qcd[ibin][iMj]= static_cast<TH1F*>(f->Get(Form("bin%i/qcd", ibin)))->GetBinContent(iMj+1);
			ttbar[ibin][iMj]= static_cast<TH1F*>(f->Get(Form("bin%i/ttbar", ibin)))->GetBinContent(iMj+1);
			wjets[ibin][iMj]= static_cast<TH1F*>(f->Get(Form("bin%i/wjets", ibin)))->GetBinContent(iMj+1);
			other[ibin][iMj]= static_cast<TH1F*>(f->Get(Form("bin%i/other", ibin)))->GetBinContent(iMj+1);
			sig1800[ibin][iMj]= static_cast<TH1F*>(f->Get(Form("bin%i/signal_M1800", ibin)))->GetBinContent(iMj+1);
		}
	}

	TCanvas *cpie[12][3];
	TPie *pie4[12][3];

	TString title_1[nbins] = {
		"",//0
		"",
		"",
		"",
		"",
		"",//5
		"",
		"",
		"",
		"",
		"",//10
		"",
		"",
		"",
		"",
		"",//15
		"",
		"",
		"",
		"",
		"",//20
		"",
		// Njets-Nb basis
		"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=0", // 22
		"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=0",
		"1-lepton,HT>1200,N_{jets}#geq8,N_{b}=0",
		"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=1", // 25
		"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=1",
		"1-lepton,HT>1200,N_{jets}#geq8,N_{b}=1",
		"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=2",
		"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=2",
		"1-lepton,HT>1200,N_{jets}#geq8,N_{b}=2", // 30
		"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}#geq3",
		"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=3",
		"1-lepton,HT>1200,N_{jets}#geq8,N_{b}=3",
		"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}#geq4",
		"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq4", // 35
		"1-lepton,HT>1200,N_{jets}#geq8,N_{b}#geq4",
		"0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=0",
		"0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=0",
		"0-lepton,HT>1200,N_{jets}#geq10,N_{b}=0",
		"0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=1", // 40
		"0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=1",
		"0-lepton,HT>1200,N_{jets}#geq10,N_{b}=1",
		"0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=2",
		"0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=2",
		"0-lepton,HT>1200,N_{jets}#geq10,N_{b}=2", // 45
		"0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq3",
		"0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=3",
		"0-lepton,HT>1200,N_{jets}#geq10,N_{b}=3",
		"0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq4",
		"0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}#geq4", // 50
		"0-lepton,HT>1200,N_{jets}#geq10,N_{b}#geq4"
	};

	TString Mj_txt[3]={", 500<M_{J}<800",", 800<M_{J}<1100",", 1100<M_{J}"};

	for(int ibin=22; ibin<nbins; ibin++){
		if(ibin == 34 or ibin==49) continue;
		for (int iMj=0; iMj<3; iMj++){
			Float_t vals[] = {qcd[ibin][iMj],ttbar[ibin][iMj],wjets[ibin][iMj],other[ibin][iMj],sig1800[ibin][iMj]};
			Int_t colors[] = {kYellow-7,kAzure+7,kGreen+2,kGray+1,kRed+1};
			Int_t nvals = sizeof(vals)/sizeof(vals[0]);
			cpie[ibin][iMj] = new TCanvas(Form("cpie_%i_%i",ibin,iMj),Form("TPie test_%i_%i",ibin,iMj),700,700);
			pie4[ibin][iMj] = new TPie(Form("pie4_%i_%i", ibin,iMj),Form(title_1[ibin]+Mj_txt[iMj]),nvals,vals,colors);
			set_piechart(pie4[ibin][iMj]);
			pie4[ibin][iMj]->Draw("nol <");
			cpie[ibin][iMj]->SaveAs(outputdir+Form("piechart_%i_%i.png",ibin,iMj));
			cpie[ibin][iMj]->SaveAs(outputdir+Form("piechart_%i_%i.pdf",ibin,iMj));
		}
	}
}
