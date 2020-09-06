#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include <iostream>

void signalCrossSection(int glu_mass, double &xsec, double &xsec_unc);
TGraphErrors * theoryGraph();

void setStyle()
{
  gStyle->SetCanvasDefW(600);
  gStyle->SetCanvasDefH(600);
  gStyle->SetTitleOffset(1.2,"x"); 
  gStyle->SetTitleOffset(1.7,"z"); 
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadTopMargin(0.08);
  
  gStyle->SetLabelFont(42);
  gStyle->SetLabelSize(0.05);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.07);
}

void drawHeader()
{
  TLatex *lat = new TLatex;
  lat->SetTextSize(0.038);
  lat->DrawLatexNDC(0.12, 0.93, "CMS #font[52]{Preliminary}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.66, 0.93, "137 fb^{-1} (13 TeV)");
}

void pulls()
{
  std::vector<float> gluinoMasses = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  std::vector<float> mean;
  std::vector<float> meanError;
  std::vector<float> dummy;

  for(unsigned int i=0; i<gluinoMasses.size(); i++) {
    TFile *f = TFile::Open(Form("mlfitM%d_nopdf_100toys.root", static_cast<int>(gluinoMasses.at(i))));
    TTree *tree = static_cast<TTree*>(f->Get("tree_fit_sb"));
    TString name(Form("h%d", static_cast<int>(gluinoMasses.at(i))));
    TH1F *h = new TH1F(name, name, 1000, 0, 10);
    tree->Project(name, "mu", "");
    std::cout << h->GetMean() << " +/- " << h->GetMeanError() << std::endl;
    double xSec, xSecErr;
    signalCrossSection(static_cast<int>(gluinoMasses.at(i)), xSec, xSecErr);
    mean.push_back(h->GetMean());
    meanError.push_back(h->GetMeanError());
    dummy.push_back(0);
  }

  setStyle();
  TCanvas *c = new TCanvas;
  TGraphErrors *gr = new TGraphErrors(mean.size(), &gluinoMasses.at(0), &mean.at(0), &dummy.at(0), &meanError.at(0));
  gr->SetTitle(";Gluino mass (GeV);Fitted signal strength");
  gr->SetMarkerStyle(kFullCircle);
  gr->SetMinimum(0.8);
  gr->SetMaximum(1.2);
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetNdivisions(505);
  gr->Draw("AP");
  
  drawHeader();

  c->Print("injection.pdf");
  

}

void limits_new()
{
  std::vector<float> gluinoMasses = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
  std::vector<float> minus2Sigma, minus1Sigma, mean, plus1Sigma, plus2Sigma;
  std::vector<float> observed;
  std::vector<float> dummy;

  for(unsigned int i=0; i<gluinoMasses.size(); i++) {
    TString filename(Form("../rpv_macros/datacards/nopdfoutput_2016/higgsCombineM%d.AsymptoticLimits.mH120.root", static_cast<int>(gluinoMasses.at(i))));
    TFile *f = TFile::Open(filename);
    if(!f->IsOpen()) {
      std::cout << "Could not open file " << filename << std::endl;
      exit(1);
    }
    TTree *tree = static_cast<TTree*>(f->Get("limit"));
    if(tree == nullptr) { 
      std::cout << "Could not get limit tree " << filename << std::endl;
      exit(1);
    }
    
    double limit;
    double minus2SigmaExpected, minus1SigmaExpected, meanExpected, plus1SigmaExpected, plus2SigmaExpected;
    double obs;
    tree->SetBranchAddress("limit", &limit);
    tree->GetEntry(0);
    minus2SigmaExpected=limit;
    tree->GetEntry(1);
    minus1SigmaExpected=limit;
    tree->GetEntry(2);
    meanExpected=limit;
    tree->GetEntry(3);
    plus1SigmaExpected=limit;
    tree->GetEntry(4);
    plus2SigmaExpected=limit;
    tree->GetEntry(5);
    obs=limit;

    double xSec, xSecErr;
    const double pbToFb=1000.;
    signalCrossSection(static_cast<int>(gluinoMasses.at(i)), xSec, xSecErr);
    minus2Sigma.push_back(abs(minus2SigmaExpected-meanExpected)*xSec*pbToFb);
    minus1Sigma.push_back(abs(minus1SigmaExpected-meanExpected)*xSec*pbToFb);
    mean.push_back(meanExpected*xSec*pbToFb);
    plus1Sigma.push_back(abs(plus1SigmaExpected-meanExpected)*xSec*pbToFb);
    plus2Sigma.push_back(abs(plus2SigmaExpected-meanExpected)*xSec*pbToFb);
    observed.push_back(obs*xSec*pbToFb);
    dummy.push_back(0);
  }

  setStyle();
  TCanvas *c = new TCanvas;
  c->SetLogy();

  TGraph *gr = new TGraph(mean.size(), &gluinoMasses.at(0), &mean.at(0));
  gr->SetTitle(";m_{#tilde{g}} [GeV];#sigma(pp #rightarrow #tilde{g}#tilde{g}) (fb)");
  gr->SetMarkerStyle(kFullCircle);
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetNdivisions(505);
  gr->SetLineWidth(3);
  gr->SetLineStyle(2);
  gr->SetMinimum(1);
  gr->SetMaximum(10000);

  // expected limit +/- 1 sigma
  TGraphAsymmErrors *grMean = new TGraphAsymmErrors(mean.size(), &gluinoMasses.at(0), &mean.at(0), 
						    &dummy.at(0), &dummy.at(0),
						    &minus1Sigma.at(0), &plus1Sigma.at(0));
  grMean->SetLineColor(kBlack);
  grMean->SetLineWidth(2);
  grMean->SetFillColor(kGreen+1);

  // expected limit +/- 2 sigma
  TGraphAsymmErrors *grMean2Sigma = new TGraphAsymmErrors(mean.size(), &gluinoMasses.at(0), &mean.at(0), 
							  &dummy.at(0), &dummy.at(0),
							  &minus2Sigma.at(0), &plus2Sigma.at(0));
  grMean2Sigma->SetFillColor(kYellow);

  TGraph *grObserved = new TGraph(observed.size(), &gluinoMasses.at(0), &observed.at(0));
  grObserved->SetMarkerColor(kBlack);
  grObserved->SetLineWidth(2);
  grObserved->SetLineColor(kBlack);
  grObserved->SetMarkerStyle(kFullDotLarge);
  grObserved->SetMarkerSize(1.0);

  TGraphErrors *grTheory = theoryGraph();

  // draw all limits
  gr->Draw("AL");
  grMean2Sigma->Draw("L3");
  grMean->Draw("L3");
  grMean->Draw("LX,same");
  grTheory->Draw(/*"LX"*/"L3");
  grTheory->Draw("LX,same");
  grObserved->Draw("LP");

  
  TLegend *leg = new TLegend(0.45, 0.6, 0.85, 0.9);
  leg->AddEntry(grObserved, "Observed 95% CL limit", "LP");
  leg->AddEntry(grMean, "Expected 95% CL limit", "L");
  leg->AddEntry(grMean, "Expected #pm 1#sigma", "F");
  leg->AddEntry(grMean2Sigma, "Expected #pm 2#sigma", "F");
  leg->AddEntry(grTheory, "#sigma^{NLO+NLL} (pp #rightarrow #tilde{g}#tilde{g})", "LF");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

  drawHeader();
  c->Print("limits.pdf");
  c->Print("limits.png");
}

TGraphErrors * theoryGraph()
{
  std::vector<float> mass;
  std::vector<float> xsec;
  std::vector<float> xsecError;
  std::vector<float> dummy;

  int glu_mass = 595;
  double xsecTemp=0.0;
  double xsecErrTemp=0.0;
  do {
    mass.push_back(static_cast<int>(glu_mass));
    signalCrossSection(glu_mass, xsecTemp, xsecErrTemp);
    // convert cross section from pb to fb
    xsecTemp*=1000.;
    xsec.push_back(xsecTemp);
    xsecError.push_back(xsecTemp*xsecErrTemp);
    dummy.push_back(0.);
    glu_mass+=5;
  } while(glu_mass < 2000);

  TGraphErrors *grTheory = new TGraphErrors(mass.size(), &mass.at(0), &xsec.at(0), &dummy.at(0), &xsecError.at(0)); 
  grTheory->SetMarkerStyle(kFullSquare);
  grTheory->SetLineColor(kMagenta);
  grTheory->SetLineWidth(2);
  grTheory->SetFillColor(kMagenta);
  grTheory->SetFillStyle(3002);

  return grTheory;
}

  void signalCrossSection(int glu_mass, double &xsec, double &xsec_unc){
    if (glu_mass == 595) { xsec = 	0; xsec_unc =  0; return; }
      else if (glu_mass == 600) { xsec = 	0.113E+02; xsec_unc =  8.62E-02; return; }
      else if (glu_mass == 605) { xsec = 	0.108E+02; xsec_unc =  8.66E-02; return; }
      else if (glu_mass == 610) { xsec = 	0.102E+02; xsec_unc =  8.7E-02; return; }
      else if (glu_mass == 615) { xsec = 	0.974E+01; xsec_unc =  8.74E-02; return; }
      else if (glu_mass == 620) { xsec = 	0.926E+01; xsec_unc =  8.78E-02; return; }
      else if (glu_mass == 625) { xsec = 	0.881E+01; xsec_unc =  8.82E-02; return; }
      else if (glu_mass == 630) { xsec = 	0.839E+01; xsec_unc =  8.86E-02; return; }
      else if (glu_mass == 635) { xsec = 	0.799E+01; xsec_unc =  8.9E-02; return; }
      else if (glu_mass == 640) { xsec = 	0.761E+01; xsec_unc =  8.94E-02; return; }
      else if (glu_mass == 645) { xsec = 	0.725E+01; xsec_unc =  8.98E-02; return; }
      else if (glu_mass == 650) { xsec = 	0.690E+01; xsec_unc =  9.02E-02; return; }
      else if (glu_mass == 655) { xsec = 	0.658E+01; xsec_unc =  9.06E-02; return; }
      else if (glu_mass == 660) { xsec = 	0.627E+01; xsec_unc =  9.1E-02; return; }
      else if (glu_mass == 665) { xsec = 	0.598E+01; xsec_unc =  9.15E-02; return; }
      else if (glu_mass == 670) { xsec = 	0.571E+01; xsec_unc =  9.19E-02; return; }
      else if (glu_mass == 675) { xsec = 	0.544E+01; xsec_unc =  9.23E-02; return; }
      else if (glu_mass == 680) { xsec = 	0.520E+01; xsec_unc =  9.27E-02; return; }
      else if (glu_mass == 685) { xsec = 	0.496E+01; xsec_unc =  9.31E-02; return; }
      else if (glu_mass == 690) { xsec = 	0.474E+01; xsec_unc =  9.35E-02; return; }
      else if (glu_mass == 695) { xsec = 	0.452E+01; xsec_unc =  9.39E-02; return; }
      else if (glu_mass == 700) { xsec = 	0.432E+01; xsec_unc =  9.43E-02; return; }
      else if (glu_mass == 705) { xsec = 	0.413E+01; xsec_unc =  9.46E-02; return; }
      else if (glu_mass == 710) { xsec = 	0.395E+01; xsec_unc =  9.5E-02; return; }
      else if (glu_mass == 715) { xsec = 	0.377E+01; xsec_unc =  9.54E-02; return; }
      else if (glu_mass == 720) { xsec = 	0.361E+01; xsec_unc =  9.58E-02; return; }
      else if (glu_mass == 725) { xsec = 	0.345E+01; xsec_unc =  9.61E-02; return; }
      else if (glu_mass == 730) { xsec = 	0.330E+01; xsec_unc =  9.65E-02; return; }
      else if (glu_mass == 735) { xsec = 	0.316E+01; xsec_unc =  9.69E-02; return; }
      else if (glu_mass == 740) { xsec = 	0.302E+01; xsec_unc =  9.72E-02; return; }
      else if (glu_mass == 745) { xsec = 	0.289E+01; xsec_unc =  9.76E-02; return; }
      else if (glu_mass == 750) { xsec = 	0.277E+01; xsec_unc =  9.8E-02; return; }
      else if (glu_mass == 755) { xsec = 	0.265E+01; xsec_unc =  9.83E-02; return; }
      else if (glu_mass == 760) { xsec = 	0.254E+01; xsec_unc =  9.87E-02; return; }
      else if (glu_mass == 765) { xsec = 	0.243E+01; xsec_unc =  9.91E-02; return; }
      else if (glu_mass == 770) { xsec = 	0.233E+01; xsec_unc =  9.94E-02; return; }
      else if (glu_mass == 775) { xsec = 	0.223E+01; xsec_unc =  9.98E-02; return; }
      else if (glu_mass == 780) { xsec = 	0.214E+01; xsec_unc =  10.01E-02; return; }
      else if (glu_mass == 785) { xsec = 	0.205E+01; xsec_unc =  10.05E-02; return; }
      else if (glu_mass == 790) { xsec = 	0.197E+01; xsec_unc =  10.09E-02; return; }
      else if (glu_mass == 795) { xsec = 	0.188E+01; xsec_unc =  10.12E-02; return; }
      else if (glu_mass == 800) { xsec = 	0.181E+01; xsec_unc =  10.16E-02; return; }
      else if (glu_mass == 805) { xsec = 	0.173E+01; xsec_unc =  10.2E-02; return; }
      else if (glu_mass == 810) { xsec = 	0.166E+01; xsec_unc =  10.23E-02; return; }
      else if (glu_mass == 815) { xsec = 	0.160E+01; xsec_unc =  10.27E-02; return; }
      else if (glu_mass == 820) { xsec = 	0.153E+01; xsec_unc =  10.31E-02; return; }
      else if (glu_mass == 825) { xsec = 	0.147E+01; xsec_unc =  10.34E-02; return; }
      else if (glu_mass == 830) { xsec = 	0.141E+01; xsec_unc =  10.38E-02; return; }
      else if (glu_mass == 835) { xsec = 	0.136E+01; xsec_unc =  10.42E-02; return; }
      else if (glu_mass == 840) { xsec = 	0.130E+01; xsec_unc =  10.45E-02; return; }
      else if (glu_mass == 845) { xsec = 	0.125E+01; xsec_unc =  10.49E-02; return; }
      else if (glu_mass == 850) { xsec = 	0.120E+01; xsec_unc =  10.53E-02; return; }
      else if (glu_mass == 855) { xsec = 	0.115E+01; xsec_unc =  10.57E-02; return; }
      else if (glu_mass == 860) { xsec = 	0.111E+01; xsec_unc =  10.6E-02; return; }
      else if (glu_mass == 865) { xsec = 	0.107E+01; xsec_unc =  10.64E-02; return; }
      else if (glu_mass == 870) { xsec = 	0.103E+01; xsec_unc =  10.68E-02; return; }
      else if (glu_mass == 875) { xsec = 	0.986E+00; xsec_unc =  10.71E-02; return; }
      else if (glu_mass == 880) { xsec = 	0.948E+00; xsec_unc =  10.75E-02; return; }
      else if (glu_mass == 885) { xsec = 	0.912E+00; xsec_unc =  10.79E-02; return; }
      else if (glu_mass == 890) { xsec = 	0.877E+00; xsec_unc =  10.82E-02; return; }
      else if (glu_mass == 895) { xsec = 	0.844E+00; xsec_unc =  10.86E-02; return; }
      else if (glu_mass == 900) { xsec = 	0.812E+00; xsec_unc =  10.89E-02; return; }
      else if (glu_mass == 905) { xsec = 	0.781E+00; xsec_unc =  10.93E-02; return; }
      else if (glu_mass == 910) { xsec = 	0.752E+00; xsec_unc =  10.97E-02; return; }
      else if (glu_mass == 915) { xsec = 	0.723E+00; xsec_unc =  11.0E-02; return; }
      else if (glu_mass == 920) { xsec = 	0.696E+00; xsec_unc =  11.04E-02; return; }
      else if (glu_mass == 925) { xsec = 	0.670E+00; xsec_unc =  11.07E-02; return; }
      else if (glu_mass == 930) { xsec = 	0.646E+00; xsec_unc =  11.11E-02; return; }
      else if (glu_mass == 935) { xsec = 	0.622E+00; xsec_unc =  11.14E-02; return; }
      else if (glu_mass == 940) { xsec = 	0.599E+00; xsec_unc =  11.18E-02; return; }
      else if (glu_mass == 945) { xsec = 	0.577E+00; xsec_unc =  11.21E-02; return; }
      else if (glu_mass == 950) { xsec = 	0.556E+00; xsec_unc =  11.25E-02; return; }
      else if (glu_mass == 955) { xsec = 	0.535E+00; xsec_unc =  11.28E-02; return; }
      else if (glu_mass == 960) { xsec = 	0.516E+00; xsec_unc =  11.32E-02; return; }
      else if (glu_mass == 965) { xsec = 	0.497E+00; xsec_unc =  11.35E-02; return; }
      else if (glu_mass == 970) { xsec = 	0.479E+00; xsec_unc =  11.39E-02; return; }
      else if (glu_mass == 975) { xsec = 	0.462E+00; xsec_unc =  11.42E-02; return; }
      else if (glu_mass == 980) { xsec = 	0.445E+00; xsec_unc =  11.46E-02; return; }
      else if (glu_mass == 985) { xsec = 	0.430E+00; xsec_unc =  11.49E-02; return; }
      else if (glu_mass == 990) { xsec = 	0.414E+00; xsec_unc =  11.53E-02; return; }
      else if (glu_mass == 995) { xsec = 	0.399E+00; xsec_unc =  11.56E-02; return; }
      else if (glu_mass == 1000) { xsec = 	0.385E+00; xsec_unc =  11.6E-02; return; }
      else if (glu_mass == 1005) { xsec = 	0.372E+00; xsec_unc =  11.63E-02; return; }
      else if (glu_mass == 1010) { xsec = 	0.359E+00; xsec_unc =  11.67E-02; return; }
      else if (glu_mass == 1015) { xsec = 	0.346E+00; xsec_unc =  11.7E-02; return; }
      else if (glu_mass == 1020) { xsec = 	0.334E+00; xsec_unc =  11.74E-02; return; }
      else if (glu_mass == 1025) { xsec = 	0.322E+00; xsec_unc =  11.78E-02; return; }
      else if (glu_mass == 1030) { xsec = 	0.311E+00; xsec_unc =  11.81E-02; return; }
      else if (glu_mass == 1035) { xsec = 	0.300E+00; xsec_unc =  11.85E-02; return; }
      else if (glu_mass == 1040) { xsec = 	0.290E+00; xsec_unc =  11.88E-02; return; }
      else if (glu_mass == 1045) { xsec = 	0.280E+00; xsec_unc =  11.92E-02; return; }
      else if (glu_mass == 1050) { xsec = 	0.270E+00; xsec_unc =  11.95E-02; return; }
      else if (glu_mass == 1055) { xsec = 	0.261E+00; xsec_unc =  11.99E-02; return; }
      else if (glu_mass == 1060) { xsec = 	0.252E+00; xsec_unc =  12.02E-02; return; }
      else if (glu_mass == 1065) { xsec = 	0.243E+00; xsec_unc =  12.06E-02; return; }
      else if (glu_mass == 1070) { xsec = 	0.235E+00; xsec_unc =  12.09E-02; return; }
      else if (glu_mass == 1075) { xsec = 	0.227E+00; xsec_unc =  12.13E-02; return; }
      else if (glu_mass == 1080) { xsec = 	0.219E+00; xsec_unc =  12.17E-02; return; }
      else if (glu_mass == 1085) { xsec = 	0.212E+00; xsec_unc =  12.2E-02; return; }
      else if (glu_mass == 1090) { xsec = 	0.205E+00; xsec_unc =  12.24E-02; return; }
      else if (glu_mass == 1095) { xsec = 	0.198E+00; xsec_unc =  12.27E-02; return; }
      else if (glu_mass == 1100) { xsec = 	0.191E+00; xsec_unc =  12.31E-02; return; }
      else if (glu_mass == 1105) { xsec = 	0.185E+00; xsec_unc =  12.34E-02; return; }
      else if (glu_mass == 1110) { xsec = 	0.179E+00; xsec_unc =  12.38E-02; return; }
      else if (glu_mass == 1115) { xsec = 	0.173E+00; xsec_unc =  12.42E-02; return; }
      else if (glu_mass == 1120) { xsec = 	0.167E+00; xsec_unc =  12.45E-02; return; }
      else if (glu_mass == 1125) { xsec = 	0.162E+00; xsec_unc =  12.49E-02; return; }
      else if (glu_mass == 1130) { xsec = 	0.156E+00; xsec_unc =  12.53E-02; return; }
      else if (glu_mass == 1135) { xsec = 	0.151E+00; xsec_unc =  12.56E-02; return; }
      else if (glu_mass == 1140) { xsec = 	0.146E+00; xsec_unc =  12.6E-02; return; }
      else if (glu_mass == 1145) { xsec = 	0.141E+00; xsec_unc =  12.64E-02; return; }
      else if (glu_mass == 1150) { xsec = 	0.137E+00; xsec_unc =  12.67E-02; return; }
      else if (glu_mass == 1155) { xsec = 	0.132E+00; xsec_unc =  12.71E-02; return; }
      else if (glu_mass == 1160) { xsec = 	0.128E+00; xsec_unc =  12.74E-02; return; }
      else if (glu_mass == 1165) { xsec = 	0.124E+00; xsec_unc =  12.78E-02; return; }
      else if (glu_mass == 1170) { xsec = 	0.120E+00; xsec_unc =  12.82E-02; return; }
      else if (glu_mass == 1175) { xsec = 	0.116E+00; xsec_unc =  12.85E-02; return; }
      else if (glu_mass == 1180) { xsec = 	0.112E+00; xsec_unc =  12.89E-02; return; }
      else if (glu_mass == 1185) { xsec = 	0.109E+00; xsec_unc =  12.92E-02; return; }
      else if (glu_mass == 1190) { xsec = 	0.105E+00; xsec_unc =  12.96E-02; return; }
      else if (glu_mass == 1195) { xsec = 	0.102E+00; xsec_unc =  13.0E-02; return; }
      else if (glu_mass == 1200) { xsec = 	0.985E-01; xsec_unc =  13.03E-02; return; }
      else if (glu_mass == 1205) { xsec = 	0.953E-01; xsec_unc =  13.07E-02; return; }
      else if (glu_mass == 1210) { xsec = 	0.923E-01; xsec_unc =  13.1E-02; return; }
      else if (glu_mass == 1215) { xsec = 	0.894E-01; xsec_unc =  13.14E-02; return; }
      else if (glu_mass == 1220) { xsec = 	0.866E-01; xsec_unc =  13.17E-02; return; }
      else if (glu_mass == 1225) { xsec = 	0.838E-01; xsec_unc =  13.21E-02; return; }
      else if (glu_mass == 1230) { xsec = 	0.812E-01; xsec_unc =  13.24E-02; return; }
      else if (glu_mass == 1235) { xsec = 	0.786E-01; xsec_unc =  13.27E-02; return; }
      else if (glu_mass == 1240) { xsec = 	0.762E-01; xsec_unc =  13.31E-02; return; }
      else if (glu_mass == 1245) { xsec = 	0.738E-01; xsec_unc =  13.34E-02; return; }
      else if (glu_mass == 1250) { xsec = 	0.715E-01; xsec_unc =  13.38E-02; return; }
      else if (glu_mass == 1255) { xsec = 	0.692E-01; xsec_unc =  13.41E-02; return; }
      else if (glu_mass == 1260) { xsec = 	0.671E-01; xsec_unc =  13.45E-02; return; }
      else if (glu_mass == 1265) { xsec = 	0.650E-01; xsec_unc =  13.48E-02; return; }
      else if (glu_mass == 1270) { xsec = 	0.630E-01; xsec_unc =  13.51E-02; return; }
      else if (glu_mass == 1275) { xsec = 	0.610E-01; xsec_unc =  13.55E-02; return; }
      else if (glu_mass == 1280) { xsec = 	0.591E-01; xsec_unc =  13.58E-02; return; }
      else if (glu_mass == 1285) { xsec = 	0.573E-01; xsec_unc =  13.62E-02; return; }
      else if (glu_mass == 1290) { xsec = 	0.556E-01; xsec_unc =  13.65E-02; return; }
      else if (glu_mass == 1295) { xsec = 	0.539E-01; xsec_unc =  13.69E-02; return; }
      else if (glu_mass == 1300) { xsec = 	0.522E-01; xsec_unc =  13.72E-02; return; }
      else if (glu_mass == 1305) { xsec = 	0.506E-01; xsec_unc =  13.76E-02; return; }
      else if (glu_mass == 1310) { xsec = 	0.491E-01; xsec_unc =  13.79E-02; return; }
      else if (glu_mass == 1315) { xsec = 	0.476E-01; xsec_unc =  13.83E-02; return; }
      else if (glu_mass == 1320) { xsec = 	0.461E-01; xsec_unc =  13.86E-02; return; }
      else if (glu_mass == 1325) { xsec = 	0.447E-01; xsec_unc =  13.9E-02; return; }
      else if (glu_mass == 1330) { xsec = 	0.434E-01; xsec_unc =  13.94E-02; return; }
      else if (glu_mass == 1335) { xsec = 	0.421E-01; xsec_unc =  13.97E-02; return; }
      else if (glu_mass == 1340) { xsec = 	0.408E-01; xsec_unc =  14.01E-02; return; }
      else if (glu_mass == 1345) { xsec = 	0.396E-01; xsec_unc =  14.04E-02; return; }
      else if (glu_mass == 1350) { xsec = 	0.384E-01; xsec_unc =  14.08E-02; return; }
      else if (glu_mass == 1355) { xsec = 	0.372E-01; xsec_unc =  14.11E-02; return; }
      else if (glu_mass == 1360) { xsec = 	0.361E-01; xsec_unc =  14.15E-02; return; }
      else if (glu_mass == 1365) { xsec = 	0.350E-01; xsec_unc =  14.19E-02; return; }
      else if (glu_mass == 1370) { xsec = 	0.340E-01; xsec_unc =  14.22E-02; return; }
      else if (glu_mass == 1375) { xsec = 	0.330E-01; xsec_unc =  14.26E-02; return; }
      else if (glu_mass == 1380) { xsec = 	0.320E-01; xsec_unc =  14.3E-02; return; }
      else if (glu_mass == 1385) { xsec = 	0.310E-01; xsec_unc =  14.33E-02; return; }
      else if (glu_mass == 1390) { xsec = 	0.301E-01; xsec_unc =  14.37E-02; return; }
      else if (glu_mass == 1395) { xsec = 	0.292E-01; xsec_unc =  14.4E-02; return; }
      else if (glu_mass == 1400) { xsec = 	0.284E-01; xsec_unc =  14.44E-02; return; }
      else if (glu_mass == 1405) { xsec = 	0.275E-01; xsec_unc =  14.48E-02; return; }
      else if (glu_mass == 1410) { xsec = 	0.267E-01; xsec_unc =  14.51E-02; return; }
      else if (glu_mass == 1415) { xsec = 	0.259E-01; xsec_unc =  14.55E-02; return; }
      else if (glu_mass == 1420) { xsec = 	0.252E-01; xsec_unc =  14.59E-02; return; }
      else if (glu_mass == 1425) { xsec = 	0.244E-01; xsec_unc =  14.63E-02; return; }
      else if (glu_mass == 1430) { xsec = 	0.237E-01; xsec_unc =  14.66E-02; return; }
      else if (glu_mass == 1435) { xsec = 	0.230E-01; xsec_unc =  14.7E-02; return; }
      else if (glu_mass == 1440) { xsec = 	0.224E-01; xsec_unc =  14.74E-02; return; }
      else if (glu_mass == 1445) { xsec = 	0.217E-01; xsec_unc =  14.77E-02; return; }
      else if (glu_mass == 1450) { xsec = 	0.211E-01; xsec_unc =  14.81E-02; return; }
      else if (glu_mass == 1455) { xsec = 	0.205E-01; xsec_unc =  14.85E-02; return; }
      else if (glu_mass == 1460) { xsec = 	0.199E-01; xsec_unc =  14.88E-02; return; }
      else if (glu_mass == 1465) { xsec = 	0.193E-01; xsec_unc =  14.92E-02; return; }
      else if (glu_mass == 1470) { xsec = 	0.187E-01; xsec_unc =  14.96E-02; return; }
      else if (glu_mass == 1475) { xsec = 	0.182E-01; xsec_unc =  15.0E-02; return; }
      else if (glu_mass == 1480) { xsec = 	0.177E-01; xsec_unc =  15.03E-02; return; }
      else if (glu_mass == 1485) { xsec = 	0.172E-01; xsec_unc =  15.07E-02; return; }
      else if (glu_mass == 1490) { xsec = 	0.167E-01; xsec_unc =  15.11E-02; return; }
      else if (glu_mass == 1495) { xsec = 	0.162E-01; xsec_unc =  15.15E-02; return; }
      else if (glu_mass == 1500) { xsec = 	0.157E-01; xsec_unc =  15.18E-02; return; }
      else if (glu_mass == 1505) { xsec = 	0.153E-01; xsec_unc =  15.22E-02; return; }
      else if (glu_mass == 1510) { xsec = 	0.148E-01; xsec_unc =  15.26E-02; return; }
      else if (glu_mass == 1515) { xsec = 	0.144E-01; xsec_unc =  15.3E-02; return; }
      else if (glu_mass == 1520) { xsec = 	0.140E-01; xsec_unc =  15.33E-02; return; }
      else if (glu_mass == 1525) { xsec = 	0.136E-01; xsec_unc =  15.37E-02; return; }
      else if (glu_mass == 1530) { xsec = 	0.132E-01; xsec_unc =  15.41E-02; return; }
      else if (glu_mass == 1535) { xsec = 	0.128E-01; xsec_unc =  15.45E-02; return; }
      else if (glu_mass == 1540) { xsec = 	0.125E-01; xsec_unc =  15.48E-02; return; }
      else if (glu_mass == 1545) { xsec = 	0.121E-01; xsec_unc =  15.52E-02; return; }
      else if (glu_mass == 1550) { xsec = 	0.118E-01; xsec_unc =  15.56E-02; return; }
      else if (glu_mass == 1555) { xsec = 	0.115E-01; xsec_unc =  15.6E-02; return; }
      else if (glu_mass == 1560) { xsec = 	0.111E-01; xsec_unc =  15.64E-02; return; }
      else if (glu_mass == 1565) { xsec = 	0.108E-01; xsec_unc =  15.67E-02; return; }
      else if (glu_mass == 1570) { xsec = 	0.105E-01; xsec_unc =  15.71E-02; return; }
      else if (glu_mass == 1575) { xsec = 	0.102E-01; xsec_unc =  15.75E-02; return; }
      else if (glu_mass == 1580) { xsec = 	0.993E-02; xsec_unc =  15.79E-02; return; }
      else if (glu_mass == 1585) { xsec = 	0.966E-02; xsec_unc =  15.83E-02; return; }
      else if (glu_mass == 1590) { xsec = 	0.939E-02; xsec_unc =  15.87E-02; return; }
      else if (glu_mass == 1595) { xsec = 	0.912E-02; xsec_unc =  15.9E-02; return; }
      else if (glu_mass == 1600) { xsec = 	0.887E-02; xsec_unc =  15.94E-02; return; }
      else if (glu_mass == 1605) { xsec = 	0.862E-02; xsec_unc =  15.98E-02; return; }
      else if (glu_mass == 1610) { xsec = 	0.838E-02; xsec_unc =  16.02E-02; return; }
      else if (glu_mass == 1615) { xsec = 	0.815E-02; xsec_unc =  16.06E-02; return; }
      else if (glu_mass == 1620) { xsec = 	0.792E-02; xsec_unc =  16.1E-02; return; }
      else if (glu_mass == 1625) { xsec = 	0.770E-02; xsec_unc =  16.13E-02; return; }
      else if (glu_mass == 1630) { xsec = 	0.749E-02; xsec_unc =  16.17E-02; return; }
      else if (glu_mass == 1635) { xsec = 	0.728E-02; xsec_unc =  16.21E-02; return; }
      else if (glu_mass == 1640) { xsec = 	0.708E-02; xsec_unc =  16.25E-02; return; }
      else if (glu_mass == 1645) { xsec = 	0.689E-02; xsec_unc =  16.29E-02; return; }
      else if (glu_mass == 1650) { xsec = 	0.670E-02; xsec_unc =  16.33E-02; return; }
      else if (glu_mass == 1655) { xsec = 	0.651E-02; xsec_unc =  16.37E-02; return; }
      else if (glu_mass == 1660) { xsec = 	0.633E-02; xsec_unc =  16.41E-02; return; }
      else if (glu_mass == 1665) { xsec = 	0.616E-02; xsec_unc =  16.45E-02; return; }
      else if (glu_mass == 1670) { xsec = 	0.599E-02; xsec_unc =  16.49E-02; return; }
      else if (glu_mass == 1675) { xsec = 	0.583E-02; xsec_unc =  16.53E-02; return; }
      else if (glu_mass == 1680) { xsec = 	0.567E-02; xsec_unc =  16.56E-02; return; }
      else if (glu_mass == 1685) { xsec = 	0.551E-02; xsec_unc =  16.6E-02; return; }
      else if (glu_mass == 1690) { xsec = 	0.536E-02; xsec_unc =  16.64E-02; return; }
      else if (glu_mass == 1695) { xsec = 	0.521E-02; xsec_unc =  16.68E-02; return; }
      else if (glu_mass == 1700) { xsec = 	0.507E-02; xsec_unc =  16.72E-02; return; }
      else if (glu_mass == 1705) { xsec = 	0.493E-02; xsec_unc =  16.76E-02; return; }
      else if (glu_mass == 1710) { xsec = 	0.480E-02; xsec_unc =  16.81E-02; return; }
      else if (glu_mass == 1715) { xsec = 	0.467E-02; xsec_unc =  16.85E-02; return; }
      else if (glu_mass == 1720) { xsec = 	0.454E-02; xsec_unc =  16.89E-02; return; }
      else if (glu_mass == 1725) { xsec = 	0.442E-02; xsec_unc =  16.93E-02; return; }
      else if (glu_mass == 1730) { xsec = 	0.430E-02; xsec_unc =  16.97E-02; return; }
      else if (glu_mass == 1735) { xsec = 	0.418E-02; xsec_unc =  17.01E-02; return; }
      else if (glu_mass == 1740) { xsec = 	0.407E-02; xsec_unc =  17.05E-02; return; }
      else if (glu_mass == 1745) { xsec = 	0.396E-02; xsec_unc =  17.09E-02; return; }
      else if (glu_mass == 1750) { xsec = 	0.385E-02; xsec_unc =  17.13E-02; return; }
      else if (glu_mass == 1755) { xsec = 	0.375E-02; xsec_unc =  17.18E-02; return; }
      else if (glu_mass == 1760) { xsec = 	0.365E-02; xsec_unc =  17.22E-02; return; }
      else if (glu_mass == 1765) { xsec = 	0.355E-02; xsec_unc =  17.26E-02; return; }
      else if (glu_mass == 1770) { xsec = 	0.345E-02; xsec_unc =  17.3E-02; return; }
      else if (glu_mass == 1775) { xsec = 	0.336E-02; xsec_unc =  17.34E-02; return; }
      else if (glu_mass == 1780) { xsec = 	0.327E-02; xsec_unc =  17.39E-02; return; }
      else if (glu_mass == 1785) { xsec = 	0.318E-02; xsec_unc =  17.43E-02; return; }
      else if (glu_mass == 1790) { xsec = 	0.310E-02; xsec_unc =  17.47E-02; return; }
      else if (glu_mass == 1795) { xsec = 	0.301E-02; xsec_unc =  17.51E-02; return; }
      else if (glu_mass == 1800) { xsec = 	0.293E-02; xsec_unc =  17.56E-02; return; }
      else if (glu_mass == 1805) { xsec = 	0.286E-02; xsec_unc =  17.6E-02; return; }
      else if (glu_mass == 1810) { xsec = 	0.278E-02; xsec_unc =  17.64E-02; return; }
      else if (glu_mass == 1815) { xsec = 	0.271E-02; xsec_unc =  17.69E-02; return; }
      else if (glu_mass == 1820) { xsec = 	0.263E-02; xsec_unc =  17.73E-02; return; }
      else if (glu_mass == 1825) { xsec = 	0.256E-02; xsec_unc =  17.77E-02; return; }
      else if (glu_mass == 1830) { xsec = 	0.249E-02; xsec_unc =  17.82E-02; return; }
      else if (glu_mass == 1835) { xsec = 	0.243E-02; xsec_unc =  17.86E-02; return; }
      else if (glu_mass == 1840) { xsec = 	0.236E-02; xsec_unc =  17.9E-02; return; }
      else if (glu_mass == 1845) { xsec = 	0.230E-02; xsec_unc =  17.95E-02; return; }
      else if (glu_mass == 1850) { xsec = 	0.224E-02; xsec_unc =  17.99E-02; return; }
      else if (glu_mass == 1855) { xsec = 	0.218E-02; xsec_unc =  18.04E-02; return; }
      else if (glu_mass == 1860) { xsec = 	0.212E-02; xsec_unc =  18.08E-02; return; }
      else if (glu_mass == 1865) { xsec = 	0.207E-02; xsec_unc =  18.13E-02; return; }
      else if (glu_mass == 1870) { xsec = 	0.201E-02; xsec_unc =  18.17E-02; return; }
      else if (glu_mass == 1875) { xsec = 	0.196E-02; xsec_unc =  18.22E-02; return; }
      else if (glu_mass == 1880) { xsec = 	0.191E-02; xsec_unc =  18.26E-02; return; }
      else if (glu_mass == 1885) { xsec = 	0.186E-02; xsec_unc =  18.31E-02; return; }
      else if (glu_mass == 1890) { xsec = 	0.181E-02; xsec_unc =  18.35E-02; return; }
      else if (glu_mass == 1895) { xsec = 	0.176E-02; xsec_unc =  18.4E-02; return; }
      else if (glu_mass == 1900) { xsec = 	0.171E-02; xsec_unc =  18.45E-02; return; }
      else if (glu_mass == 1905) { xsec = 	0.167E-02; xsec_unc =  18.49E-02; return; }
      else if (glu_mass == 1910) { xsec = 	0.163E-02; xsec_unc =  18.54E-02; return; }
      else if (glu_mass == 1915) { xsec = 	0.158E-02; xsec_unc =  18.59E-02; return; }
      else if (glu_mass == 1920) { xsec = 	0.154E-02; xsec_unc =  18.63E-02; return; }
      else if (glu_mass == 1925) { xsec = 	0.150E-02; xsec_unc =  18.68E-02; return; }
      else if (glu_mass == 1930) { xsec = 	0.146E-02; xsec_unc =  18.73E-02; return; }
      else if (glu_mass == 1935) { xsec = 	0.142E-02; xsec_unc =  18.78E-02; return; }
      else if (glu_mass == 1940) { xsec = 	0.139E-02; xsec_unc =  18.82E-02; return; }
      else if (glu_mass == 1945) { xsec = 	0.135E-02; xsec_unc =  18.87E-02; return; }
      else if (glu_mass == 1950) { xsec = 	0.131E-02; xsec_unc =  18.92E-02; return; }
      else if (glu_mass == 1955) { xsec = 	0.128E-02; xsec_unc =  18.97E-02; return; }
      else if (glu_mass == 1960) { xsec = 	0.125E-02; xsec_unc =  19.02E-02; return; }
      else if (glu_mass == 1965) { xsec = 	0.121E-02; xsec_unc =  19.07E-02; return; }
      else if (glu_mass == 1970) { xsec = 	0.118E-02; xsec_unc =  19.12E-02; return; }
      else if (glu_mass == 1975) { xsec = 	0.115E-02; xsec_unc =  19.17E-02; return; }
      else if (glu_mass == 1980) { xsec = 	0.112E-02; xsec_unc =  19.22E-02; return; }
      else if (glu_mass == 1985) { xsec = 	0.109E-02; xsec_unc =  19.27E-02; return; }
      else if (glu_mass == 1990) { xsec = 	0.106E-02; xsec_unc =  19.32E-02; return; }
      else if (glu_mass == 1995) { xsec = 	0.104E-02; xsec_unc =  19.37E-02; return; }
      else if (glu_mass == 2000) { xsec = 	0.101E-02; xsec_unc =  19.42E-02; return; }
      else if (glu_mass == 2005) { xsec = 	0.983E-03; xsec_unc =  19.48E-02; return; }
      else if (glu_mass == 2010) { xsec = 	0.957E-03; xsec_unc =  19.53E-02; return; }
      else if (glu_mass == 2015) { xsec = 	0.933E-03; xsec_unc =  19.58E-02; return; }
      else if (glu_mass == 2020) { xsec = 	0.908E-03; xsec_unc =  19.64E-02; return; }
      else if (glu_mass == 2025) { xsec = 	0.885E-03; xsec_unc =  19.69E-02; return; }
      else if (glu_mass == 2030) { xsec = 	0.862E-03; xsec_unc =  19.74E-02; return; }
      else if (glu_mass == 2035) { xsec = 	0.840E-03; xsec_unc =  19.8E-02; return; }
      else if (glu_mass == 2040) { xsec = 	0.818E-03; xsec_unc =  19.85E-02; return; }
      else if (glu_mass == 2045) { xsec = 	0.797E-03; xsec_unc =  19.91E-02; return; }
      else if (glu_mass == 2050) { xsec = 	0.776E-03; xsec_unc =  19.96E-02; return; }
      else if (glu_mass == 2055) { xsec = 	0.756E-03; xsec_unc =  20.02E-02; return; }
      else if (glu_mass == 2060) { xsec = 	0.737E-03; xsec_unc =  20.07E-02; return; }
      else if (glu_mass == 2065) { xsec = 	0.718E-03; xsec_unc =  20.13E-02; return; }
      else if (glu_mass == 2070) { xsec = 	0.699E-03; xsec_unc =  20.19E-02; return; }
      else if (glu_mass == 2075) { xsec = 	0.681E-03; xsec_unc =  20.25E-02; return; }
      else if (glu_mass == 2080) { xsec = 	0.664E-03; xsec_unc =  20.3E-02; return; }
      else if (glu_mass == 2085) { xsec = 	0.647E-03; xsec_unc =  20.36E-02; return; }
      else if (glu_mass == 2090) { xsec = 	0.630E-03; xsec_unc =  20.42E-02; return; }
      else if (glu_mass == 2095) { xsec = 	0.614E-03; xsec_unc =  20.48E-02; return; }
      else if (glu_mass == 2100) { xsec = 	0.598E-03; xsec_unc =  20.54E-02; return; }
      else if (glu_mass == 2105) { xsec = 	0.583E-03; xsec_unc =  20.6E-02; return; }
      else if (glu_mass == 2110) { xsec = 	0.568E-03; xsec_unc =  20.66E-02; return; }
      else if (glu_mass == 2115) { xsec = 	0.553E-03; xsec_unc =  20.72E-02; return; }
      else if (glu_mass == 2120) { xsec = 	0.539E-03; xsec_unc =  20.78E-02; return; }
      else if (glu_mass == 2125) { xsec = 	0.525E-03; xsec_unc =  20.84E-02; return; }
      else if (glu_mass == 2130) { xsec = 	0.512E-03; xsec_unc =  20.9E-02; return; }
      else if (glu_mass == 2135) { xsec = 	0.499E-03; xsec_unc =  20.97E-02; return; }
      else if (glu_mass == 2140) { xsec = 	0.486E-03; xsec_unc =  21.03E-02; return; }
      else if (glu_mass == 2145) { xsec = 	0.473E-03; xsec_unc =  21.09E-02; return; }
      else if (glu_mass == 2150) { xsec = 	0.461E-03; xsec_unc =  21.16E-02; return; }
      else if (glu_mass == 2155) { xsec = 	0.449E-03; xsec_unc =  21.22E-02; return; }
      else if (glu_mass == 2160) { xsec = 	0.438E-03; xsec_unc =  21.29E-02; return; }
      else if (glu_mass == 2165) { xsec = 	0.427E-03; xsec_unc =  21.35E-02; return; }
      else if (glu_mass == 2170) { xsec = 	0.416E-03; xsec_unc =  21.42E-02; return; }
      else if (glu_mass == 2175) { xsec = 	0.405E-03; xsec_unc =  21.48E-02; return; }
      else if (glu_mass == 2180) { xsec = 	0.395E-03; xsec_unc =  21.55E-02; return; }
      else if (glu_mass == 2185) { xsec = 	0.385E-03; xsec_unc =  21.62E-02; return; }
      else if (glu_mass == 2190) { xsec = 	0.375E-03; xsec_unc =  21.69E-02; return; }
      else if (glu_mass == 2195) { xsec = 	0.365E-03; xsec_unc =  21.76E-02; return; }
      else if (glu_mass == 2200) { xsec = 	0.356E-03; xsec_unc =  21.83E-02; return; }// */
      else {xsec = 0.; xsec_unc = 0.;} 
  }
