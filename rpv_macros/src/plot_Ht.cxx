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
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TString.h"
#include "TTree.h"

using namespace std;

void set_histo_style(TH1F *h1){
	h1->GetXaxis()->SetTitle("HT");
	h1->SetLineWidth(1.2);
}

void set_legend_style(TLegend *l1){
	l1->SetFillColor(0);
	l1->SetLineColor(0);
	l1->SetLineStyle(kSolid);
	l1->SetLineWidth(1);
	l1->SetFillStyle(1001);
	l1->SetTextFont(42);
	l1->SetTextSize(0.04);
}

int main(){
	const int nfiles = 4;
	TString inputdir, outputdir;
	outputdir = "/cms/scratch/yjeong/CMSSW_10_2_13/src/RPV/rpv_macros/plots_ht/";
	inputdir = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_rpvfitnbge0/";

	TString filename[nfiles] = {
		"600to800_TuneCUETP8M1_18",
		"800to1200_TuneCUETP8M1_14",
		"1200to2500_TuneCUETP8M1_7",
		"2500toInf_TuneCUETP8M1_4"
	};

	TFile *tfile[nfiles];
	TTree *tree[nfiles];
	TH1F *ht[nfiles];
	TCanvas *c;
	c = new TCanvas;
	TLegend *l;
	l = new TLegend(0.65,0.54,0.75,0.8);
	set_legend_style(l);
	//float xmax[nfiles] = {0.}, xmin[nfiles] = {0.};
	for(int i = 0; i < nfiles; i++){
		tfile[i] = new TFile(inputdir+"TTJets_HT-"+filename[i]+".root");
		tree[i] = (TTree*)tfile[i]->Get("tree");

		//xmax[i] = tree[i]->GetMaximum("tree/ht");
		//xmin[i] = tree[i]->GetMinimum("tree/ht");

		ht[i] = new TH1F(Form("ht_%d",i),Form("TTJets_HT"),100,1100,7000);
		tree[i]->Project(Form("ht_%d",i),"ht");

		set_histo_style(ht[i]);

		if(i==0)ht[i]->SetLineColor(kRed);
		else if(i==1)ht[i]->SetLineColor(kBlue);
		else if(i==2)ht[i]->SetLineColor(kGreen);
		else if(i==3)ht[i]->SetLineColor(kOrange+1);

		if(i==0)l->AddEntry(ht[i],"600to800");
		else if(i==1)l->AddEntry(ht[i],"800to1200");
		else if(i==2)l->AddEntry(ht[i],"1200to2500");
		else if(i==3)l->AddEntry(ht[i],"2500toInf");

		float ymax = 0;
		ymax = ht[i]->GetMaximum();

		if(i==0){
			ht[i]->SetMaximum(ymax*1.5);
			ht[i]->Draw();
		}
		else if(i>0)ht[i]->Draw("histsame");
		l->Draw();
	}
	c->SaveAs(outputdir+"TTJets_ht.png");
}
