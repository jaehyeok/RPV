#include <iostream> 
#include <vector> 
#include <iomanip> 

#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TMath.h"
#include "TLegend.h"

using namespace std;

bool formatLatex=false;

//
// main
//
int main(int argc, char *argv[])
{


    TString syst("nominal"), updo("X");
   // TString reweight("other");
    TString arg(argv[1]);
//    TString year, filename;
    if(argc<=3 && arg == "--help"){
      cout << "./run/plot_multiKappa.exe [Systematics] [Up/Down]" << endl;
      return 1;
    }
    if(argc>=3){

      syst = argv[1];
      updo = argv[2];
//      year = argv[2];
      //filename = argv[4];
    }
    else {cout << "ERROR: Invalid arguments. Use ./run/plot_multiKappa.exe [Systematics] [Up/Down] " << endl;
		return 1;
	}
    cout << "Systematics : " << syst <<endl;
    cout << "Up/Down : " << updo <<endl;
//    cout << "Reweight Process   : " << proc <<endl;
//    cout << "Year : " << year << endl;
    
    TFile *fqcd = new TFile("/homes/schmitz/RPV/rpv_macros/plots/kappa_qcd/kappa_summary_"+syst+updo+".root");
    TFile *fttbar = new TFile("/homes/schmitz/RPV/rpv_macros/plots/kappa_ttbar/kappa_summary_"+syst+updo+".root");
    TFile *fwjets = new TFile("/homes/schmitz/RPV/rpv_macros/plots/kappa_wjets/kappa_summary_"+syst+updo+".root");
    TFile *fother = new TFile("/homes/schmitz/RPV/rpv_macros/plots/kappa_other/kappa_summary_"+syst+updo+".root");
 
    TH1F *hqcd11 = (TH1F*)fqcd->Get("h1_1l_summary1");
    TH1F *hqcd12 = (TH1F*)fqcd->Get("h1_1l_summary2");
    TH1F *hqcd01 = (TH1F*)fqcd->Get("h1_0l_summary1");
    TH1F *hqcd02 = (TH1F*)fqcd->Get("h1_0l_summary2");
    
    TH1F *httbar11 = (TH1F*)fttbar->Get("h1_1l_summary1");
    TH1F *httbar12 = (TH1F*)fttbar->Get("h1_1l_summary2");
    TH1F *httbar01 = (TH1F*)fttbar->Get("h1_0l_summary1");
    TH1F *httbar02 = (TH1F*)fttbar->Get("h1_0l_summary2");

    TH1F *hwjets11 = (TH1F*)fwjets->Get("h1_1l_summary1");
    TH1F *hwjets12 = (TH1F*)fwjets->Get("h1_1l_summary2");
    TH1F *hwjets01 = (TH1F*)fwjets->Get("h1_0l_summary1");
    TH1F *hwjets02 = (TH1F*)fwjets->Get("h1_0l_summary2");

    TH1F *hother11 = (TH1F*)fother->Get("h1_1l_summary1");
    TH1F *hother12 = (TH1F*)fother->Get("h1_1l_summary2");
    TH1F *hother01 = (TH1F*)fother->Get("h1_0l_summary1");
    TH1F *hother02 = (TH1F*)fother->Get("h1_0l_summary2");

    Double_t shift = 0.25*hqcd11->GetBinWidth(1);
    Double_t xmin  = hqcd11->GetXaxis()->GetXmin();
    Double_t xmax  = hqcd11->GetXaxis()->GetXmax();
    
    TF1 *fqcd11 = new TF1("qcdfit11","pol 0");
    hqcd11->Fit("qcdfit11");
    TF1 *fttbar11 = new TF1("ttbarfit11","pol 0");
    httbar11->Fit("ttbarfit11");
    TF1 *fwjets11 = new TF1("wjetsfit11","pol 0");
    hwjets11->Fit("wjetsfit11");
    TF1 *fother11 = new TF1("otherfit11","pol 0");
    hother11->Fit("otherfit11");
    TF1 *fqcd12 = new TF1("qcdfit12","pol 0");
    hqcd12->Fit("qcdfit12");
    TF1 *fttbar12 = new TF1("ttbarfit12","pol 0");
    httbar12->Fit("ttbarfit12");
    TF1 *fwjets12 = new TF1("wjetsfit12","pol 0");
    hwjets12->Fit("wjetsfit12");
    TF1 *fother12 = new TF1("otherfit12","pol 0");
    hother12->Fit("otherfit12");
    TF1 *fqcd01 = new TF1("qcdfit01","pol 0");
    hqcd01->Fit("qcdfit01");
    TF1 *fttbar01 = new TF1("ttbarfit01","pol 0");
    httbar01->Fit("ttbarfit01");
    TF1 *fwjets01 = new TF1("wjetsfit01","pol 0");
    hwjets01->Fit("wjetsfit01");
    TF1 *fother01 = new TF1("otherfit01","pol 0");
    hother01->Fit("otherfit01");
    TF1 *fqcd02 = new TF1("qcdfit02","pol 0");
    hqcd02->Fit("qcdfit02");
    TF1 *fttbar02 = new TF1("ttbarfit02","pol 0");
    httbar02->Fit("ttbarfit02");
    TF1 *fwjets02 = new TF1("wjetsfit02","pol 0");
    hwjets02->Fit("wjetsfit02");
    TF1 *fother02 = new TF1("otherfit02","pol 0");
    hother02->Fit("otherfit02");
    //fqcd11->SetLineColor(kRed);
    Double_t totalChi11 = fqcd11->GetChisquare() + fttbar11->GetChisquare()
				+fwjets11->GetChisquare() + fother11->GetChisquare();
    Double_t totalChi12 = fqcd12->GetChisquare() + fttbar12->GetChisquare()
				+fwjets12->GetChisquare() + fother12->GetChisquare();
    Double_t totalChi01 = fqcd01->GetChisquare() + fttbar01->GetChisquare()
				+fwjets01->GetChisquare() + fother01->GetChisquare();
    Double_t totalChi02 = fqcd02->GetChisquare() + fttbar02->GetChisquare()
				+fwjets02->GetChisquare() + fother02->GetChisquare();

    cout << "total chi11: " << totalChi11 << endl;
    cout << "total chi12: " << totalChi12 << endl;
    cout << "total chi01: " << totalChi01 << endl;
    cout << "total chi02: " << totalChi02 << endl;
    cout << "for syst: " << syst << ", updo: " << updo << ", reduced chi overall: " << (totalChi11+totalChi12+totalChi01+totalChi02)/33.0 << endl;

    httbar11->GetXaxis()->SetLimits(xmin+shift,xmax+shift);
    hwjets11->GetXaxis()->SetLimits(xmin+2*shift,xmax+2*shift);
    hother11->GetXaxis()->SetLimits(xmin+3*shift,xmax+3*shift);
    httbar12->GetXaxis()->SetLimits(xmin+shift,xmax+shift);
    hwjets12->GetXaxis()->SetLimits(xmin+2*shift,xmax+2*shift);
    hother12->GetXaxis()->SetLimits(xmin+3*shift,xmax+3*shift);
    httbar01->GetXaxis()->SetLimits(xmin+shift,xmax+shift);
    hwjets01->GetXaxis()->SetLimits(xmin+2*shift,xmax+2*shift);
    hother01->GetXaxis()->SetLimits(xmin+3*shift,xmax+3*shift);
    httbar02->GetXaxis()->SetLimits(xmin+shift,xmax+shift);
    hwjets02->GetXaxis()->SetLimits(xmin+2*shift,xmax+2*shift);
    hother02->GetXaxis()->SetLimits(xmin+3*shift,xmax+3*shift);

    TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
    leg->AddEntry(hqcd11,"QCD reweight","ep");
    leg->AddEntry(httbar11,"W+jets reweight","ep");
    leg->AddEntry(hwjets11,"ttbar reweight","ep");
    leg->AddEntry(hother11,"other reweight","ep");
    
    TCanvas *c = new TCanvas("c", "c", 1200, 1400);
    c->Divide(1,4);
    c->cd(1);
    hqcd11->SetLineColor(kBlack);
    hqcd11->SetMarkerColor(kBlack);
    httbar11->SetLineColor(kBlue);
    httbar11->SetMarkerColor(kBlue);
    hwjets11->SetLineColor(kRed);
    hwjets11->SetMarkerColor(kRed);
    hother11->SetLineColor(kGreen);
    hother11->SetMarkerColor(kGreen);
    hother11->Draw("ep");
    hwjets11->Draw("ep same");
    httbar11->Draw("ep same");
    hqcd11->Draw("ep same");
    //fqcd11->Draw("same");
    leg->Draw();
    c->cd(2);
    hqcd12->SetLineColor(kBlack);
    hqcd12->SetMarkerColor(kBlack);
    httbar12->SetLineColor(kBlue);
    httbar12->SetMarkerColor(kBlue);
    hwjets12->SetLineColor(kRed);
    hwjets12->SetMarkerColor(kRed);
    hother12->SetLineColor(kGreen);
    hother12->SetMarkerColor(kGreen);
    hother12->Draw("ep");
    hwjets12->Draw("ep same");
    httbar12->Draw("ep same");
    hqcd12->Draw("ep same");
    c->cd(3);
    hqcd01->SetLineColor(kBlack);
    hqcd01->SetMarkerColor(kBlack);
    httbar01->SetLineColor(kBlue);
    httbar01->SetMarkerColor(kBlue);
    hwjets01->SetLineColor(kRed);
    hwjets01->SetMarkerColor(kRed);
    hother01->SetLineColor(kGreen);
    hother01->SetMarkerColor(kGreen);
    hother01->Draw("ep");
    hwjets01->Draw("ep same");
    httbar01->Draw("ep same");
    hqcd01->Draw("ep same");
    c->cd(4);
    hqcd02->SetLineColor(kBlack);
    hqcd02->SetMarkerColor(kBlack);
    httbar02->SetLineColor(kBlue);
    httbar02->SetMarkerColor(kBlue);
    hwjets02->SetLineColor(kRed);
    hwjets02->SetMarkerColor(kRed);
    hother02->SetLineColor(kGreen);
    hother02->SetMarkerColor(kGreen);
    hother02->Draw("ep");
    hwjets02->Draw("ep same");
    httbar02->Draw("ep same");
    hqcd02->Draw("ep same");


    c->Print("plots/kappa_reweight/kappa_summary_"+syst+updo+".pdf");
    c->Print("plots/kappa_reweight/kappa_summary_"+syst+updo+".png");
    fqcd->Close();  
    fttbar->Close();  
    fwjets->Close();  
    fother->Close();  

    return 0;
}


