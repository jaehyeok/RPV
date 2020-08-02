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
#include "TSystem.h"
using namespace std;

void set_histo_style(TH1F *h){
	h->GetXaxis()->SetTitle("HT");
	h->SetLineWidth(1.2);
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
	float ht, lhe_ht;
	float w_isr_tr, w_lumi, weight;
	const int nfiles = 5;
	TString inputdir, outputdir;
	outputdir = "plots/ht/";
	gSystem->mkdir(outputdir);
	//inputdir = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_rpvfitnbge0/";
	inputdir = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/processed/";

	TString filename[nfiles] = {
		"A73A4F60-87D6-0B44-A377-1B29B24DF617_fatjetbaby_TTJets_HT-2500toInf_TuneCUETP8M1.root",
		"CEFBBD30-07B3-EB43-8325-D4E887570D33_fatjetbaby_TTJets_HT-1200to2500_TuneCUETP8M1.root",
		"CCF461B3-DC23-2549-968C-6F28A8A72D77_fatjetbaby_TTJets_HT-800to1200_TuneCUETP8M1.root",
		"8C973745-0EDF-484F-A51D-950BA631194E_fatjetbaby_TTJets_HT-600to800_TuneCUETP8M1.root",
		"5A0AAF6E-5F59-344C-86B2-ABD8DF613D0E_fatjetbaby_TTJets_TuneCUETP8M1.root"
	};
	//---------------TTJets_HT_All-------------------
	TString alltt;
	alltt = "8F42BDAD-0FF8-6849-9BF0-D55E5D02CD6D_fatjetbaby_TTJets_TuneCUETP8M1.root";
	TFile *f1;
	TTree *t1;
	TLegend *l;
	l = new TLegend(0.65,0.54,0.75,0.8);
	set_legend_style(l);
	TH1F *h2;
	TCanvas *c1;
	c1 = new TCanvas;
	c1->SetLogy();
	f1 = new TFile(inputdir+alltt);
	t1 = (TTree*)f1->Get("tree");
	h2 = new TH1F("h2","TTJets_HT",25,0,5000);
	for(int i = 0; i<t1->GetEntries(); i++){
		t1->GetEntry(i);
		t1->SetBranchAddress("ht",&ht);
		t1->SetBranchAddress("w_isr_tr",&w_isr_tr);
		t1->SetBranchAddress("w_lumi",&w_lumi);
		t1->SetBranchAddress("weight",&weight);
		t1->SetBranchAddress("lhe_ht",&lhe_ht);
		h2->Fill(ht,weight);
	}
	h2->SetLineColor(kBlack);
	l->AddEntry(h2,"Inclusive");
	h2->Draw("hist");
	c1->SaveAs(outputdir+"TTJets_Inclusive_Ht.png");
	//------------------------------------------------

	TFile *tfile[nfiles];
	TTree *tree[nfiles];
	TH1F *h1[nfiles];
	TCanvas *c2;
	c2 = new TCanvas;
	c2->SetLogy();
	TCanvas *c3;
	c3 = new TCanvas;
	c3->SetLogy();
	THStack *hs;
	float ymax = 0;
	hs = new THStack("hs","TTJets_HT");
	for(int i = 0; i < nfiles; i++){
		tfile[i] = new TFile(inputdir+filename[i]);
		tree[i] = (TTree*)tfile[i]->Get("tree");
		tree[i]->SetBranchAddress("ht",&ht);
		tree[i]->SetBranchAddress("w_isr_tr",&w_isr_tr);
		tree[i]->SetBranchAddress("w_lumi",&w_lumi);
		tree[i]->SetBranchAddress("weight",&weight);
		tree[i]->SetBranchAddress("lhe_ht",&lhe_ht);

		h1[i] = new TH1F(Form("h1_%d",i),Form("TTJets_HT"),25,0,5000);
		set_histo_style(h1[i]);
		for(int j=0; j<tree[i]->GetEntries();j++){
			tree[i]->GetEntry(j);
			if(!(filename[i].Contains("TTJets_Tune")))h1[i]->Fill(ht,weight);
			else if(filename[i].Contains("TTJets_Tune") && lhe_ht < 600)h1[i]->Fill(ht,weight);
		}

		cout<<"weight: "<<weight<<", w_isr: "<<w_isr_tr<<", w_lumi: "<<w_lumi<<endl;
		if(i==0){
			h1[i]->SetLineColor(kRed);
			l->AddEntry(h1[i],"600to800");
		}
		else if(i==1){
			h1[i]->SetLineColor(kBlue);
			l->AddEntry(h1[i],"800to1200");
		}
		else if(i==2){
			h1[i]->SetLineColor(kGreen);
			l->AddEntry(h1[i],"1200to2500");
		}
		else if(i==3){
			h1[i]->SetLineColor(kOrange+1);
			l->AddEntry(h1[i],"2500toInf");
		}
		else if(i==4){
                        h1[i]->SetLineColor(kOrange-1);
                        l->AddEntry(h1[i],"0to600");
                }
		hs->Add(h1[i]);
		if(i==0)ymax = h1[i]->GetMaximum();
		c2->cd();
		if(i==0){
			h1[i]->SetMaximum(ymax*1000000);
			h1[i]->Draw("hist");
		}
		else if(i>0)h1[i]->Draw("histsame");

	}
	l->Draw();
	c2->SaveAs(outputdir+"TTJets_Ht.png");
	c3->cd();
	hs->SetMaximum(ymax*1000000);
	hs->Draw("hist");
	h2->Draw("histsame");
	l->Draw();
	c3->SaveAs(outputdir+"TTJets_Ht_stack.png");
}
