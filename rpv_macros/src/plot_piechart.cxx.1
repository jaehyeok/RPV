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

using namespace std;

void set_piechart(TPie *p_opt){
	p_opt->GetSlice(0)->SetTitle("QCD");
	p_opt->GetSlice(1)->SetTitle("t#bar{t}");
	p_opt->GetSlice(2)->SetTitle("W+jets");
	p_opt->GetSlice(3)->SetTitle("Other");
	p_opt->SetTextSize(0.028);
	p_opt->SetRadius(.40);
	p_opt->SetLabelsOffset(-.22);
	p_opt->SetLabelFormat("#splitline{%val (%perc)}{%txt}");
}

void set_latex(TLatex lt){
	lt.SetTextAlign(12);
	lt.SetNDC();
	lt.SetTextFont(132);
	lt.SetTextAngle(0);
	lt.SetTextSize(0.165);
}

int main()
{
	TString inputdir, outputdir;
	outputdir = "/cms/scratch/yjeong/CMSSW_10_5_0/src/RPV/rpv_macros/plots/";
	inputdir = "/cms/scratch/yjeong/CMSSW_10_5_0/src/RPV/rpv_macros/variations/";

	TFile* infile  = TFile::Open(inputdir+"output_nominal_newnt.root", "READ");

	float qcd[34][3], ttbar[34][3], wjets[34][3], other[34][3];//, sig1600[34][3];

	for(int ibin=0; ibin<34; ibin++){
		for(int iMj=0; iMj<3; iMj++){
			qcd[ibin][iMj] = 0;
			ttbar[ibin][iMj] = 0;
			wjets[ibin][iMj] = 0;
			other[ibin][iMj] = 0;
		}
	}

	for(int ibin=22; ibin<34; ibin++){
		for(int iMj=0; iMj<3; iMj++){
			qcd[ibin][iMj]= static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)))->GetBinContent(iMj+1);
			ttbar[ibin][iMj]= static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)))->GetBinContent(iMj+1);
			wjets[ibin][iMj]= static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)))->GetBinContent(iMj+1);
			wjets[ibin][iMj]=1.53*wjets[ibin][iMj];
			other[ibin][iMj]= static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin)))->GetBinContent(iMj+1);
		}
	}

	TCanvas *cpie[12][3];
	TPie *pie4[12][3];

	TString title_1[36] = {
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
		"1-lepton, HT>1200 GeV, 4#leq N_{jets}#leq5",//22
		"1-lepton, HT>1200 GeV, 6#leq N_{jets}#leq7",
		"1-lepton, HT>1200 GeV, N_{jets}#leq8", 
		"1-lepton, HT>1200 GeV, 4#leq N_{jets}#leq5",
		"1-lepton, HT>1200 GeV, 6#leq N_{jets}#leq7",
		"1-lepton, HT>1200 GeV, N_{jets}#leq8",
		"1-lepton, HT>1200 GeV, 4#leq N_{jets}#leq5",
		"1-lepton, HT>1200 GeV, 6#leq N_{jets}#leq7",//29
		"1-lepton, HT>1200 GeV, N_{jets}#leq8",
		"1-lepton, HT>1200 GeV, 4#leq N_{jets}#leq5",
		"1-lepton, HT>1200 GeV, 6#leq N_{jets}#leq7",       
		"1-lepton, HT>1200 GeV, N_{jets}#leq8"//33
	};

	TString Mj_txt[3]={", 500<M_{j}<800",", 800<M_{j}<1100",", 1100<M_{j}"};

	for(int ibin=22; ibin<34; ibin++){
		for (int iMj=0; iMj<3; iMj++){
			Float_t vals[] = {qcd[ibin][iMj],ttbar[ibin][iMj],wjets[ibin][iMj],other[ibin][iMj]};
			Int_t colors[] = {kYellow-7,kAzure+7,kGreen+2,kGray+1};
			Int_t nvals = sizeof(vals)/sizeof(vals[0]);
			cpie[ibin][iMj] = new TCanvas(Form("cpie_%i_%i",ibin,iMj),Form("TPie test_%i_%i",ibin,iMj),700,700);
			pie4[ibin][iMj] = new TPie(Form("pie4_%i_%i", ibin,iMj),Form(title_1[ibin]+Mj_txt[iMj]),nvals,vals,colors);
			set_piechart(pie4[ibin][iMj]);
			if(!(ibin==31 && iMj==2)){
				pie4[ibin][iMj]->Draw("nol <");
				cpie[ibin][iMj]->SaveAs(outputdir+Form("piechart_ibin_%i_Mj_%i.pdf",ibin,iMj));
			}
		}
	}
}
