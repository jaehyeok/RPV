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
		for(int inb=0; inb<3; inb++){
			qcd[ibin][inb] = 0;
			ttbar[ibin][inb] = 0;
			wjets[ibin][inb] = 0;
			other[ibin][inb] = 0;
		}
	}

	for(int ibin=22; ibin<34; ibin++){
		for(int inb=0; inb<3; inb++){
			qcd[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)))->GetBinContent(inb+1);
			ttbar[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)))->GetBinContent(inb+1);
			wjets[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)))->GetBinContent(inb+1);
			wjets[ibin][inb]=1.53*wjets[ibin][inb];
			other[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin)))->GetBinContent(inb+1);
		}
	}

	TCanvas *cpie[12][3];
	TPie *pie4[12][3];
	TLatex lt1;
	/*TString GeV[3]={"500#leqM_{J}#leq800GeV ",
	  "800#leqM_{J}#leq1100GeV ",
	  "1100GeV#leqM_{J} "};*/

	/*TString histo_Title[3][12]={
	  {"500\leqM_{J}\leq800GeV ",
	  "800\leqM_{J}\leq1100GeV ",
	  "1100GeV\leqM_{J} "},
	  {"N_{leps}=1, H_{T}>1200 GeV, 4\legN_{jets}\leg5, N_{b}=1",
	  "N_{leps}=1, H_{T}>1200 GeV, 6\legN_{jets}\leg7, N_{b}=1",
	  "N_{leps}=1, H_{T}>1200 GeV, 8\legN_{jets}, N_{b}=1",
	  "N_{leps}=1, H_{T}>1200 GeV, 4\legN_{jets}\leg5, N_{b}=2",
	  "N_{leps}=1, H_{T}>1200 GeV, 6\legN_{jets}\leg7, N_{b}=2",
	  "N_{leps}=1, H_{T}>1200 GeV, 8\legN_{jets}, N_{b}=2",
	  "N_{leps}=1, H_{T}>1200 GeV, 4\legN_{jets}\leg5, N_{b}=3",
	  "N_{leps}=1, H_{T}>1200 GeV, 6\legN_{jets}\leg7, N_{b}=3",
	  "N_{leps}=1, H_{T}>1200 GeV, 8\legN_{jets}, N_{b}=3",
	  "N_{leps}=1, H_{T}>1200 GeV, 4\legN_{jets}\leg5, N_{b}=4",
	  "N_{leps}=1, H_{T}>1200 GeV, 6\legN_{jets}\leg7, N_{b}=4",
	  "N_{leps}=1, H_{T}>1200 GeV, 8\legN_{jets}, N_{b}=4"}
	  };*/
	for(int ibin=22; ibin<34; ibin++){
		for (int inb=0; inb<3; inb++){
			Float_t vals[] = {qcd[ibin][inb],ttbar[ibin][inb],wjets[ibin][inb],other[ibin][inb]};
			Int_t colors[] = {kYellow-7,kAzure+7,kGreen+2,kGray+1};
			Int_t nvals = sizeof(vals)/sizeof(vals[0]);
			cpie[ibin][inb] = new TCanvas(Form("cpie_%i_%i",ibin,inb),Form("TPie test_%i_%i",ibin,inb),700,700);
			pie4[ibin][inb] = new TPie(Form("pie4_%i_%i", ibin,inb),Form(""),nvals,vals,colors);
			set_piechart(pie4[ibin][inb]);
			set_latex(lt1);
			lt1.DrawLatex(0.12,0.12+0.095,"test-------------------------");
			if(!(ibin==31 && inb==2)){
				pie4[ibin][inb]->Draw("nol <");
				cpie[ibin][inb]->SaveAs(outputdir+Form("piechart_ibin_%i_Mj_%i.pdf",ibin,inb));
			}
		}
	}
}
