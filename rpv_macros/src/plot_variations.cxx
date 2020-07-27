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
#include "TLatex.h"

using namespace std;

void loadColorPalette();
void h1cosmetic(TH1F* &h1, const char* title="", int linecolor=kRed, int linewidth=1, int fillcolor=0, TString var="");
void drawUpDown(int bin, vector<TString> variations);
TString getBinName(int bin);

int main() 
{

/*    vector<TString> variations={
        "btag_bc","btag_udsg",
        "gs45", "gs67", "gs89", "gs10Inf",
        "jes", "jer",
        "lep_eff", 
        //"ttbar_pt", //"pileup"*
        //"isr",
        "qcd_flavor",
        "qcd_mur", "qcd_muf", "qcd_murf",
        "ttbar_mur", "ttbar_muf", "ttbar_murf",
        "wjets_mur", "wjets_muf", "wjets_murf",
        "other_mur", "other_muf", "other_murf"};
// */
  
    vector<TString> variations={
        "btag_bc"
    };
//    vector<int> bins={0,1,2,3,4,5, // CR
//                      10,11,12,13,14,15,16,17,18,19,20,21}; // SR
  
    vector<int> bins = {22, 23, 24, 25, 26, 27, 28, 31, 34, 
			29, 30, 32, 33, 35, 36};
    //for(int i=0; i<100; i++) variations.push_back(Form("w_pdf%i",i)); 
    
    for(auto ibin : bins){ 
        //if(bins.at(ibin)!=0) continue; 
        drawUpDown(ibin, variations); 
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

//    TFile* infile = TFile::Open("variations/11jan2017/12p9/sum_rescaled_control.root");

    TFile* infile = TFile::Open("variations/output_2016.root");

    for(unsigned int iprocess=0; iprocess<5; iprocess++) 
    {
        TString hname = "ttbar";
        if(iprocess==1) hname = "qcd";
        if(iprocess==2) hname = "wjets";
        if(iprocess==3) hname = "other";
        if(iprocess==4) hname = "signal_M1500";

        for(unsigned int ivariation=0; ivariation<variations.size(); ivariation++) 
        { 
            if(iprocess==4 && variations.at(ivariation).Contains("mu")) continue;
            if(iprocess==4 && variations.at(ivariation).Contains("pdf")) continue;

            const char* haltername = variations.at(ivariation).Data();
            cout << "Drawing " << haltername << " for " << hname << endl;  
            TH1F *h1_central  = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", bin, hname.Data())));
            TH1F *h1_up       = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%sUp", bin, hname.Data(), haltername))); 
            TH1F *h1_down     = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%sDown", bin, hname.Data(), haltername))); 

            float stat_cent   = h1_central->Integral();
            float stat_up     = h1_up->Integral();
            float stat_down   = h1_down->Integral();

            float SF_up       = stat_cent/stat_up;
            float SF_down     = stat_cent/stat_down;

            h1_up->Scale(SF_up);
            h1_down->Scale(SF_down);

            h1cosmetic(h1_central,   "", kBlack, 1, 0, "N_{b}");
            h1cosmetic(h1_up,        "", kRed,   1, 0, "N_{b}");
            h1cosmetic(h1_down,      "", kBlue,  1, 0, "N_{b}");

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
    
            // CMS and lumi labels
            float textSize = 0.05;
            TLatex *TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%.1f fb^{-1} (13 TeV)}", 12.9));
            TexEnergyLumi->SetNDC();
            TexEnergyLumi->SetTextSize(textSize);
            TexEnergyLumi->SetTextAlign (31);
            TexEnergyLumi->SetLineWidth(2);

            TLatex *TexCMS = new TLatex(0.2,0.92,"CMS #font[52]{Preliminary}");
            TexCMS->SetNDC();
            TexCMS->SetTextSize(textSize);
            TexCMS->SetLineWidth(2);
            TexEnergyLumi->Draw("same");
            TexCMS->Draw("same");

            // display cuts
            textSize=textSize-0.01;
            TLatex *TexNlep=0;
            TLatex *TexNjets=0;
            TLatex *TexNb=0;
            TLatex *TexSyst=0;
            TString binname_tstr = getBinName(bin); 
            if(binname_tstr.Contains("nlep1"))   TexNlep = new TLatex(0.6,0.75,"N_{lep} = 1,");
            if(binname_tstr.Contains("nlep0"))   TexNlep = new TLatex(0.6,0.75,"N_{lep} = 0,");
            TexNlep->SetNDC();
            TexNlep->SetTextFont(42);
            TexNlep->SetTextSize(textSize);
            //TexNlep->SetLineWidth(2);
            if(binname_tstr.Contains("nj45_"))   TexNjets = new TLatex(0.7,0.75,"4 #leq N_{jet} #leq 5");
            if(binname_tstr.Contains("nj67_"))   TexNjets = new TLatex(0.7,0.75,"6 #leq N_{jet} #leq 7");
            if(binname_tstr.Contains("nj89_"))   TexNjets = new TLatex(0.7,0.75,"8 #leq N_{jet} #leq 9");
            if(binname_tstr.Contains("nj8_"))    TexNjets = new TLatex(0.7,0.75,"N_{jet} #geq 8");
            if(binname_tstr.Contains("nj10_"))   TexNjets = new TLatex(0.7,0.75,"N_{jet} #geq 10");
            TexNjets->SetNDC();
            TexNjets->SetTextFont(42);
            TexNjets->SetTextSize(textSize);
            //TexNjets->SetLineWidth(2);
            //if(binname_tstr.Contains("lowmj"))    TexMJ = new TLatex(0.6,0.70,"500 < M_{J} < 800 GeV");
            //if(binname_tstr.Contains("highmj"))   TexMJ = new TLatex(0.6,0.70,"M_{J} > 800 GeV");
            if(binname_tstr.Contains("nb0"))   TexNb = new TLatex(0.6,0.70,"N_{b} = 0");
            if(binname_tstr.Contains("nb1"))   TexNb = new TLatex(0.6,0.70,"N_{b} = 1");
            if(binname_tstr.Contains("nb2"))   TexNb = new TLatex(0.6,0.70,"N_{b} = 2");
            if(binname_tstr.Contains("nb3"))   TexNb = new TLatex(0.6,0.70,"N_{b} = 3");
            if(binname_tstr.Contains("nb4"))   TexNb = new TLatex(0.6,0.70,"N_{b} #geq 4");
            TexNb->SetNDC();
            TexNb->SetTextFont(42);
            TexNb->SetTextSize(textSize);
            //TexMJ->SetLineWidth(2);
            TexSyst = new TLatex(0.6,0.65, Form("Bin %i: %s %s", bin, hname.Data(), haltername));
            TexSyst->SetNDC();
            TexSyst->SetTextFont(42);
            TexSyst->SetTextSize(textSize);
            

            TexNlep->Draw("same");
            TexNjets->Draw("same");
            TexNb->Draw("same");
            TexSyst->Draw("same");

            c->cd();
            pad_ratio = new TPad(Form("p_pull_%i",bin), Form("p_pull_%i",bin), 0.0, 0.0, 1.0, 0.3);
            pad_ratio->SetLeftMargin(0.2);
            pad_ratio->Draw();
            pad_ratio->cd();
            pad_ratio->SetTopMargin(0.04);
            pad_ratio->SetRightMargin(0.1);
            pad_ratio->SetBottomMargin(0.4);
    
            TH1F *h1_cent_rat   =static_cast<TH1F*>(h1_central->Clone("h1_cent_rat"));
            TH1F *h1_up_ratio   =static_cast<TH1F*>(h1_up->Clone("h1_up_ratio")); 
            TH1F *h1_down_ratio =static_cast<TH1F*>(h1_down->Clone("h1_down_ratio")); 

            TH1F *h1_cent_rat_deno = static_cast<TH1F*>(h1_central->Clone("h1_cent_rat_deno"));

            for(int hbin = 1 ; hbin < 4 ; hbin ++) h1_cent_rat_deno->SetBinError(hbin,0);

	    h1_cent_rat->Divide(h1_cent_rat_deno);
            h1_up_ratio->Divide(h1_central);
            h1_down_ratio->Divide(h1_central);
            

            h1cosmetic(h1_up_ratio,   "", kRed, 1, 0, "M_{J}");
            h1cosmetic(h1_down_ratio,   "", kBlue, 1, 0, "M_{J}");

            h1_up_ratio->SetLabelSize(0.15,"XY");
            h1_up_ratio->GetXaxis()->SetLabelSize(0.10);
            h1_up_ratio->GetYaxis()->SetLabelSize(0.10);
            h1_up_ratio->SetTitleSize(0.14,"XY");
            h1_up_ratio->SetTitleOffset(1.0);
            h1_up_ratio->GetYaxis()->SetNdivisions(/*3,false*/706);
            h1_up_ratio->GetXaxis()->SetNdivisions(5,true);
            h1_up_ratio->SetMinimum(0.7);
            h1_up_ratio->SetMaximum(1.3);
            h1_up_ratio->GetYaxis()->SetTitle("#frac{up/down}{central}");
            h1_up_ratio->GetYaxis()->SetTitleOffset(0.5);
            h1_cent_rat->SetMarkerSize(0);
            h1_cent_rat->SetFillColor(kBlack);
            h1_cent_rat->SetLineColor(kBlack);
            h1_cent_rat->SetFillStyle(3354);
            h1_up_ratio->Draw("hist");
            h1_down_ratio->Draw("hist same");
            h1_cent_rat->Draw("same e2"); 
           
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

            gSystem->mkdir(Form("plots/variations/bin%i",bin), kTRUE); 
            c->Print(Form("plots/variations/bin%i/bin%i_%s_%s_mconly.pdf", bin, bin, hname.Data(), haltername));

            delete h1_central; 
            delete h1_up; 
            delete h1_down; 
            delete c; 
        } 
    }
}

TString getBinName(int bin)
{
    // bin name 
    vector<TString> binname;
    vector<int> binnumber;
/*    binname = {"nlep0_nj45_lowmj", "nlep0_nj67_lowmj", "nlep1_nj45_lowmj",
  			  "nlep0_nj45_highmj", "nlep0_nj67_highmj", "nlep1_nj45_highmj",
  			  "nlep0_nj10_lowmj", "nlep1_nj67_lowmj", "nlep1_nj8_lowmj", "nlep0_nj10_highmj",
  			  "nlep1_nj67_highmj", "nlep1_nj8_highmj", "nlep0_nj89_lowmj", "nlep0_nj89_highmj",
  			  "nlep0_nj89_vhighmj", "nlep0_nj10_vhighmj", "nlep1_nj67_vhighmj", "nlep1_nj8_vhighmj"}; 
    binnumber = {0,1,2,
                 3,4,5,
                 10,11,12,13,
                 14,15,16,17,
                 18,19,20,21}; 
// */
//
    binname = {"nlep1_nj45_nb0", "nlep1_nj67_nb0", "nlep1_nj8_nb0",
               "nlep1_nj45_nb1", "nlep1_nj67_nb1", "nlep1_nj8_nb1",
               "nlep1_nj45_nb2", "nlep1_nj67_nb2", "nlep1_nj8_nb2",
               "nlep1_nj45_nb3", "nlep1_nj67_nb3", "nlep1_nj8_nb3",
               "nlep1_nj45_nb4", "nlep1_nj67_nb4", "nlep1_nj8_nb4"};

    binnumber = {22, 23, 24,
                 25, 26, 27,
                 28, 29, 30,
                 31, 32, 33,
                 34, 35, 36};

    for(unsigned int i=0; i<binname.size(); i++)  
    { 
        if(binnumber.at(i)==bin) return binname.at(i); 
    } 

    return "Wrong bin";

}
