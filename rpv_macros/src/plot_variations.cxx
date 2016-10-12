// plot_variations.cxx : plot variations in 1D plot per variation per bin per process

#include <iostream>
#include <vector>

#include "TSystem.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include "TPad.h"
#include "TLine.h"

using namespace std;

void loadColorPalette();
void h1cosmetic(TH1F* &h1, const char* title="", int linecolor=kRed, int linewidth=1, int fillcolor=0, TString var="");
void drawUpDown(int bin, vector<TString> variations);

int main() 
{
/*
    vector<TString> variations={"btag_bc","btag_udsg",
        "gs45", "gs67", "gs89", "gs10Inf",
        "jes", "jer",
        "lep_eff", "ttbar_pt", //"pileup"*
        "isr",
        "qcd_flavor45", "qcd_flavor67",
        "qcd_flavor89", "qcd_flavor10Inf",
        "qcd_mur", "qcd_muf", "qcd_murf",
        "ttbar_mur", "ttbar_muf", "ttbar_murf",
        "wjets_mur", "wjets_muf", //"wjets_murf",
        "other_mur", "other_muf", "other_murf"};
 */   
    vector<TString> variations={"btag_bc","btag_udsg",
                                "gs45", "gs67", "gs89", "gs10Inf"};
    vector<int> bins={13,15}; 
    
    //for(int i=0; i<100; i++) variations.push_back(Form("w_pdf%i",i)); 
    
    for(unsigned int ivar=0; ivar<variations.size(); ivar++) 
    { 
        for(unsigned int ibin=0; ibin<bins.size(); ibin++) 
        { 
            drawUpDown(bins.at(ibin), variations); 
        } 
    } 
    return 0;
}

//
// Cosmetics for projected histograms
//
void h1cosmetic(TH1F* &h1, const char* title, int linecolor, int linewidth, int fillcolor, TString var){

    h1->SetMarkerColor(linecolor);
    h1->SetMarkerSize(0);
    h1->SetMarkerStyle(20);

    h1->SetLineColor(linecolor);
    h1->SetLineWidth(linewidth);
    h1->SetFillColor(fillcolor);
    h1->SetTitle(title);
    //h1->SetTitleSize(0.05);
    h1->SetTitleOffset(1.2);
    h1->SetXTitle(var);
    h1->SetStats(0);
    //h1->SetMinimum(0.0);

}

//
void drawUpDown(int bin, vector<TString> variations)
{

	// style
	gStyle->SetPaintTextFormat(".1f");
	gStyle->SetMarkerSize(2.5);

    //TFile* infile = TFile::Open("variations/sum_rescaled_before.root");
    TFile* infile = TFile::Open("variations/sum_rescaled_beforerescale_withoutwjets_murf.root");

    for(unsigned int iprocess=0; iprocess<4; iprocess++) 
    {
        TString hname = "ttbar";
        if(iprocess==1) hname = "qcd";
        if(iprocess==2) hname = "wjets";
        if(iprocess==3) hname = "other";
        if(iprocess==4) hname = "signal_M1200";

        for(unsigned int ivariation=0; ivariation<variations.size(); ivariation++) 
        { 
            if(iprocess==4 && variations.at(ivariation).Contains("mu")) continue;
            if(iprocess==4 && variations.at(ivariation).Contains("pdf")) continue;

            const char* haltername = variations.at(ivariation).Data();
            cout << "Drawing " << haltername << " for " << hname << endl;  
            TH1F *h1_central  = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", bin, hname.Data())));
            TH1F *h1_up       = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%sUp", bin, hname.Data(), haltername))); 
            TH1F *h1_down     = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%sDown", bin, hname.Data(), haltername))); 

            h1cosmetic(h1_central,   Form("Bin %i: %s %s", bin, hname.Data(), haltername), kBlack, 1, 0, "N_{b}");
            h1cosmetic(h1_up,        Form("Bin %i: %s %s", bin, hname.Data(), haltername), kRed,   1, 0, "N_{b}");
            h1cosmetic(h1_down,      Form("Bin %i: %s %s", bin, hname.Data(), haltername), kBlue,  1, 0, "N_{b}");

            TLegend* l1 = new TLegend (0.3,0.8,0.8,0.9);
            l1->SetNColumns(3);
            l1->SetBorderSize(1);
            l1->SetFillColor(0);
            l1->SetFillStyle(1);
            l1->SetTextSize(0.05);
            l1->SetTextFont(42);
            l1->AddEntry(h1_central,    "Central",         "l");
            l1->AddEntry(h1_up,         "Up",              "l");
            l1->AddEntry(h1_down,       "Down",            "l");

            TCanvas *c = new TCanvas("c", "", 400, 400);
            TPad *pad_overlaid;
            TPad *pad_ratio;
            c->cd(); 

            pad_overlaid = new TPad(Form("p_main_%i",bin), Form("p_main_%i",bin), 0.0, 0.28, 1.0, 1.0);
            pad_overlaid->SetTopMargin(0.1);
            pad_overlaid->SetBottomMargin(0.04);
            pad_overlaid->SetRightMargin(0.1);
            pad_overlaid->SetLeftMargin(0.2);
            pad_overlaid->Draw();
            pad_overlaid->cd();
            pad_overlaid->cd()->SetLogy(1);
    
            //h1_central->SetMaximum(h1_central->GetMaximum()*1.5);
            h1_central->SetMaximum(h1_central->GetMaximum()*10);
            h1_central->Draw("histo e");
            h1_up->Draw("histo same");
            h1_down->Draw("histo same");
            l1->Draw("same");
    
            c->cd();
            pad_ratio = new TPad(Form("p_pull_%i",bin), Form("p_pull_%i",bin), 0.0, 0.0, 1.0, 0.3);
            pad_ratio->SetLeftMargin(0.2);
            pad_ratio->Draw();
            pad_ratio->cd();
            pad_ratio->SetTopMargin(0.04);
            pad_ratio->SetRightMargin(0.1);
            pad_ratio->SetBottomMargin(0.4);
    
            TH1F *h1_up_ratio   =static_cast<TH1F*>(h1_up->Clone("h1_up_ratio")); 
            TH1F *h1_down_ratio =static_cast<TH1F*>(h1_down->Clone("h1_down_ratio")); 
            h1_up_ratio->Divide(h1_central);
            h1_down_ratio->Divide(h1_central);
            
            h1cosmetic(h1_up_ratio,   "", kRed, 1, 0, "N_{b}");
            h1cosmetic(h1_down_ratio,   "", kBlue, 1, 0, "N_{b}");

            h1_up_ratio->SetLabelSize(0.15,"XY");
            h1_up_ratio->GetXaxis()->SetLabelSize(0.10);
            h1_up_ratio->SetTitleSize(0.14,"XY");
            h1_up_ratio->SetTitleOffset(1.0);
            h1_up_ratio->GetYaxis()->SetNdivisions(/*3,false*/706);
            h1_up_ratio->GetXaxis()->SetNdivisions(5,true);
            h1_up_ratio->SetMinimum(0.7);
            h1_up_ratio->SetMaximum(1.3);
            h1_up_ratio->GetYaxis()->SetTitle("#frac{up/down}{central}");
            h1_up_ratio->GetYaxis()->SetTitleOffset(0.5);
            h1_up_ratio->Draw("hist");
            h1_down_ratio->Draw("hist same");
            
            TLine *l = new TLine(0,1,5,1);
            l->SetLineStyle(2);
            l->Draw("same");
            TLine *l1p1 = new TLine(0,1.1,5,1.1);
            l1p1->SetLineStyle(2);
            l1p1->SetLineColor(kGray);
            l1p1->Draw("same");
            TLine *l0p9 = new TLine(0,0.9,5,0.9);
            l0p9->SetLineStyle(2);
            l0p9->SetLineColor(kGray);
            l0p9->Draw("same");
            //cout << hname  << h1_central->GetBinError(5) << " " <<  h1_central->GetBinContent(5) << " = " <<  h1_central->GetBinError(5) / h1_central->GetBinContent(5)<< endl; 

            gSystem->mkdir("plots/variations", kTRUE); 
            c->Print(Form("plots/variations/bin%i_%s_%s.pdf", bin, hname.Data(), haltername));

            delete h1_central; 
            delete h1_up; 
            delete h1_down; 
            delete c; 
        } 
    }
}
