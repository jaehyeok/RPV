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

using namespace std;

void set_piechart(TPie *p_opt){
	p_opt->GetSlice(0)->SetTitle("QCD");
	p_opt->GetSlice(1)->SetTitle("t#bar{t}");
	p_opt->GetSlice(2)->SetTitle("W+jets");
	p_opt->GetSlice(3)->SetTitle("Other");
	//p_opt->GetSlice(4)->SetTitle("m_{g} = 1600GeV");
	p_opt->SetRadius(.25);
	p_opt->SetLabelsOffset(.01);
	p_opt->SetLabelFormat("#splitline{%val (%perc)}{%txt}");
	//p_opt->GetSlice(0)->SetTextSize(0.07);
}

int main()
{
	TString inputdir, outputdir;
	outputdir = "/cms/scratch/yjeong/CMSSW_10_5_0/src/RPV/rpv_macros/plots/";
	inputdir = "/cms/scratch/yjeong/CMSSW_10_5_0/src/RPV/rpv_macros/variations/";

	TFile* infile  = TFile::Open(inputdir+"output_nominal_newnt.root", "READ");

	float qcd[34][3], ttbar[34][3], wjets[34][3], other[34][3], sig1600[34][3];

	for(int ibin=0; ibin<34; ibin++){
		for(int inb=0; inb<3; inb++){
			qcd[ibin][inb] = 0;
			ttbar[ibin][inb] = 0;
			wjets[ibin][inb] = 0;
			other[ibin][inb] = 0;
			sig1600[ibin][inb] = 0;
		}
	}

	for(int ibin=22; ibin<34; ibin++){
		for(int inb=0; inb<3; inb++){
			qcd[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)))->GetBinContent(inb+1);
			ttbar[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)))->GetBinContent(inb+1);
			wjets[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)))->GetBinContent(inb+1);
			wjets[ibin][inb]=1.53*wjets[ibin][inb];
			other[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin)))->GetBinContent(inb+1);
			sig1600[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1600", ibin)))->GetBinContent(inb+1);
		}
	}

	TCanvas *cpie[12][3];
	TPie *pie4[12][3];
	//Float_t vals[] = {201.4,447.3,526.5,174.1,0.5};
	for(int ibin=22; ibin<34; ibin++){
		for (int inb=0; inb<3; inb++){
			Float_t vals[] = {qcd[ibin][inb],ttbar[ibin][inb],wjets[ibin][inb],other[ibin][inb]};
			Int_t colors[] = {kYellow-7,kAzure+7,kGreen+2,kGray+1};
			Int_t nvals = sizeof(vals)/sizeof(vals[0]);
			cpie[ibin][inb] = new TCanvas(Form("cpie_%i_%i",ibin,inb),Form("TPie test_%i_%i",ibin,inb),700,700);
			pie4[ibin][inb] = new TPie(Form("pie4_%i_%i", ibin,inb),Form("MC_piechart_%i_bin_%i_Mj",ibin,inb),nvals,vals,colors);
			set_piechart(pie4[ibin][inb]);
			if(!(ibin==31 && inb==2)){
			pie4[ibin][inb]->Draw("nol <");
			cpie[ibin][inb]->SaveAs(outputdir+Form("test_piechart_%i_%i.png",ibin,inb));
			}
		}
	}
}
