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

void signalCrossSection(int mStop_mass, double &xsec, double &xsec_unc);
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
  std::vector<float> StopMasses = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400};
  std::vector<float> mean;
  std::vector<float> meanError;
  std::vector<float> dummy;

  for(unsigned int i=0; i<StopMasses.size(); i++) {
    TFile *f = TFile::Open(Form("mlfitM%d_nopdf_100toys.root", static_cast<int>(StopMasses.at(i))));
    TTree *tree = static_cast<TTree*>(f->Get("tree_fit_sb"));
    TString name(Form("h%d", static_cast<int>(StopMasses.at(i))));
    TH1F *h = new TH1F(name, name, 1000, 0, 10);
    tree->Project(name, "mu", "");
    std::cout << h->GetMean() << " +/- " << h->GetMeanError() << std::endl;
    double xSec, xSecErr;
    signalCrossSection(static_cast<int>(StopMasses.at(i)), xSec, xSecErr);
    mean.push_back(h->GetMean());
    meanError.push_back(h->GetMeanError());
    dummy.push_back(0);
  }

  setStyle();
  TCanvas *c = new TCanvas;
  TGraphErrors *gr = new TGraphErrors(mean.size(), &StopMasses.at(0), &mean.at(0), &dummy.at(0), &meanError.at(0));
  gr->SetTitle(";Stop mass (GeV);Fitted signal strength");
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

void limits_Stealth()
{
  std::vector<float> StopMasses = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1350, 1400};
  std::vector<float> minus2Sigma, minus1Sigma, mean, plus1Sigma, plus2Sigma;
  std::vector<float> observed;
  std::vector<float> dummy;

  for(unsigned int i=0; i<StopMasses.size(); i++) {
    TString filename(Form("higgsCombineM%d.AsymptoticLimits.mH120.root", static_cast<int>(StopMasses.at(i))));
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
    signalCrossSection(static_cast<int>(StopMasses.at(i)), xSec, xSecErr);
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

  TGraph *gr = new TGraph(mean.size(), &StopMasses.at(0), &mean.at(0));
  gr->SetTitle(";m_{#tilde{t}} [GeV];#sigma(pp #rightarrow #tilde{t}#tilde{t}) (fb)");
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
  TGraphAsymmErrors *grMean = new TGraphAsymmErrors(mean.size(), &StopMasses.at(0), &mean.at(0), 
						    &dummy.at(0), &dummy.at(0),
						    &minus1Sigma.at(0), &plus1Sigma.at(0));
  grMean->SetLineColor(kBlack);
  grMean->SetLineWidth(2);
  grMean->SetFillColor(kGreen+1);

  // expected limit +/- 2 sigma
  TGraphAsymmErrors *grMean2Sigma = new TGraphAsymmErrors(mean.size(), &StopMasses.at(0), &mean.at(0), 
							  &dummy.at(0), &dummy.at(0),
							  &minus2Sigma.at(0), &plus2Sigma.at(0));
  grMean2Sigma->SetFillColor(kYellow);

  TGraph *grObserved = new TGraph(observed.size(), &StopMasses.at(0), &observed.at(0));
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
  leg->AddEntry(grTheory, "#sigma^{NLO+NLL} (pp #rightarrow #tilde{t}#tilde{t})", "LF");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

  drawHeader();
  c->Print("limits_Stealth.pdf");
  c->Print("limits_Stealth.png");
}

TGraphErrors * theoryGraph()
{
  std::vector<float> mass;
  std::vector<float> xsec;
  std::vector<float> xsecError;
  std::vector<float> dummy;

  int mStop_mass = 100;
  double xsecTemp=0.0;
  double xsecErrTemp=0.0;
  do {
    mass.push_back(static_cast<int>(mStop_mass));
    signalCrossSection(mStop_mass, xsecTemp, xsecErrTemp);
    // convert cross section from pb to fb
    xsecTemp*=300.;
    xsec.push_back(xsecTemp);
    xsecError.push_back(xsecTemp*xsecErrTemp);
    dummy.push_back(0.);
    mStop_mass+=5;
  } while(mStop_mass < 1400);

  TGraphErrors *grTheory = new TGraphErrors(mass.size(), &mass.at(0), &xsec.at(0), &dummy.at(0), &xsecError.at(0)); 
  grTheory->SetMarkerStyle(kFullSquare);
  grTheory->SetLineColor(kMagenta);
  grTheory->SetLineWidth(2);
  grTheory->SetFillColor(kMagenta);
  grTheory->SetFillStyle(3002);

  return grTheory;
}

  void signalCrossSection(int mStop_mass, double &xsec, double &xsec_unc){
    if (mStop_mass == 100) {xsec = 	0.177E+04 ; xsec_unc = 6.77E-02; return; }
      else if (mStop_mass == 105) {xsec = 	0.145E+04 ; xsec_unc = 6.74E-02; return; }
      else if (mStop_mass == 110) {xsec = 	0.120E+04 ; xsec_unc = 6.71E-02; return; }
      else if (mStop_mass == 115) {xsec = 	0.998E+03 ; xsec_unc = 6.69E-02; return; }
      else if (mStop_mass == 120) {xsec = 	0.832E+03 ; xsec_unc = 6.67E-02; return; }
      else if (mStop_mass == 125) {xsec = 	0.697E+03 ; xsec_unc = 6.65E-02; return; }
      else if (mStop_mass == 130) {xsec = 	0.586E+03 ; xsec_unc = 6.63E-02; return; }
      else if (mStop_mass == 135) {xsec = 	0.495E+03 ; xsec_unc = 6.61E-02; return; }
      else if (mStop_mass == 140) {xsec = 	0.419E+03 ; xsec_unc = 6.59E-02; return; }
      else if (mStop_mass == 145) {xsec = 	0.357E+03 ; xsec_unc = 6.58E-02; return; }
      else if (mStop_mass == 150) {xsec = 	0.304E+03 ; xsec_unc = 6.57E-02; return; }
      else if (mStop_mass == 155) {xsec = 	0.261E+03 ; xsec_unc = 6.55E-02; return; }
      else if (mStop_mass == 160) {xsec = 	0.224E+03 ; xsec_unc = 6.54E-02; return; }
      else if (mStop_mass == 165) {xsec = 	0.194E+03 ; xsec_unc = 6.53E-02; return; }
      else if (mStop_mass == 170) {xsec = 	0.168E+03 ; xsec_unc = 6.52E-02; return; }
      else if (mStop_mass == 175) {xsec = 	0.146E+03 ; xsec_unc = 6.52E-02; return; }
      else if (mStop_mass == 180) {xsec = 	0.127E+03 ; xsec_unc = 6.51E-02; return; }
      else if (mStop_mass == 185) {xsec = 	0.111E+03 ; xsec_unc = 6.51E-02; return; }
      else if (mStop_mass == 190) {xsec = 	0.973E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 195) {xsec = 	0.856E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 200) {xsec = 	0.755E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 205) {xsec = 	0.668E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 210) {xsec = 	0.593E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 215) {xsec = 	0.527E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 220) {xsec = 	0.470E+02 ; xsec_unc = 6.5E-02; return; }
      else if (mStop_mass == 225) {xsec = 	0.420E+02 ; xsec_unc = 6.51E-02; return; }
      else if (mStop_mass == 230) {xsec = 	0.377E+02 ; xsec_unc = 6.51E-02; return; }
      else if (mStop_mass == 235) {xsec = 	0.338E+02 ; xsec_unc = 6.52E-02; return; }
      else if (mStop_mass == 240) {xsec = 	0.305E+02 ; xsec_unc = 6.52E-02; return; }
      else if (mStop_mass == 245) {xsec = 	0.275E+02 ; xsec_unc = 6.53E-02; return; }
      else if (mStop_mass == 250) {xsec = 	0.248E+02 ; xsec_unc = 6.54E-02; return; }
      else if (mStop_mass == 255) {xsec = 	0.225E+02 ; xsec_unc = 6.54E-02; return; }
      else if (mStop_mass == 260) {xsec = 	0.204E+02 ; xsec_unc = 6.55E-02; return; }
      else if (mStop_mass == 265) {xsec = 	0.186E+02 ; xsec_unc = 6.56E-02; return; }
      else if (mStop_mass == 270) {xsec = 	0.169E+02 ; xsec_unc = 6.57E-02; return; }
      else if (mStop_mass == 275) {xsec = 	0.155E+02 ; xsec_unc = 6.58E-02; return; }
      else if (mStop_mass == 280) {xsec = 	0.141E+02 ; xsec_unc = 6.6E-02; return; }
      else if (mStop_mass == 285) {xsec = 	0.129E+02 ; xsec_unc = 6.61E-02; return; }
      else if (mStop_mass == 290) {xsec = 	0.119E+02 ; xsec_unc = 6.62E-02; return; }
      else if (mStop_mass == 295) {xsec = 	0.109E+02 ; xsec_unc = 6.63E-02; return; }
      else if (mStop_mass == 300) {xsec = 	0.100E+02 ; xsec_unc = 6.65E-02; return; }
      else if (mStop_mass == 305) {xsec = 	0.918E+01 ; xsec_unc = 6.66E-02; return; }
      else if (mStop_mass == 310) {xsec = 	0.843E+01 ; xsec_unc = 6.67E-02; return; }
      else if (mStop_mass == 315) {xsec = 	0.775E+01 ; xsec_unc = 6.69E-02; return; }
      else if (mStop_mass == 320) {xsec = 	0.713E+01 ; xsec_unc = 6.7E-02; return; }
      else if (mStop_mass == 325) {xsec = 	0.657E+01 ; xsec_unc = 6.71E-02; return; }
      else if (mStop_mass == 330) {xsec = 	0.606E+01 ; xsec_unc = 6.73E-02; return; }
      else if (mStop_mass == 335) {xsec = 	0.559E+01 ; xsec_unc = 6.74E-02; return; }
      else if (mStop_mass == 340) {xsec = 	0.517E+01 ; xsec_unc = 6.76E-02; return; }
      else if (mStop_mass == 345) {xsec = 	0.478E+01 ; xsec_unc = 6.78E-02; return; }
      else if (mStop_mass == 350) {xsec = 	0.443E+01 ; xsec_unc = 6.79E-02; return; }
      else if (mStop_mass == 355) {xsec = 	0.410E+01 ; xsec_unc = 6.81E-02; return; }
      else if (mStop_mass == 360) {xsec = 	0.381E+01 ; xsec_unc = 6.83E-02; return; }
      else if (mStop_mass == 365) {xsec = 	0.354E+01 ; xsec_unc = 6.85E-02; return; }
      else if (mStop_mass == 370) {xsec = 	0.329E+01 ; xsec_unc = 6.87E-02; return; }
      else if (mStop_mass == 375) {xsec = 	0.306E+01 ; xsec_unc = 6.89E-02; return; }
      else if (mStop_mass == 380) {xsec = 	0.285E+01 ; xsec_unc = 6.91E-02; return; }
      else if (mStop_mass == 385) {xsec = 	0.265E+01 ; xsec_unc = 6.93E-02; return; }
      else if (mStop_mass == 390) {xsec = 	0.247E+01 ; xsec_unc = 6.95E-02; return; }
      else if (mStop_mass == 395) {xsec = 	0.231E+01 ; xsec_unc = 6.97E-02; return; }
      else if (mStop_mass == 400) {xsec = 	0.215E+01 ; xsec_unc = 6.99E-02; return; }
      else if (mStop_mass == 405) {xsec = 	0.201E+01 ; xsec_unc = 7.01E-02; return; }
      else if (mStop_mass == 410) {xsec = 	0.188E+01 ; xsec_unc = 7.04E-02; return; }
      else if (mStop_mass == 415) {xsec = 	0.176E+01 ; xsec_unc = 7.06E-02; return; }
      else if (mStop_mass == 420) {xsec = 	0.164E+01 ; xsec_unc = 7.09E-02; return; }
      else if (mStop_mass == 425) {xsec = 	0.154E+01 ; xsec_unc = 7.11E-02; return; }
      else if (mStop_mass == 430) {xsec = 	0.144E+01 ; xsec_unc = 7.14E-02; return; }
      else if (mStop_mass == 435) {xsec = 	0.135E+01 ; xsec_unc = 7.16E-02; return; }
      else if (mStop_mass == 440) {xsec = 	0.126E+01 ; xsec_unc = 7.19E-02; return; }
      else if (mStop_mass == 445) {xsec = 	0.119E+01 ; xsec_unc = 7.22E-02; return; }
      else if (mStop_mass == 450) {xsec = 	0.111E+01 ; xsec_unc = 7.25E-02; return; }
      else if (mStop_mass == 455) {xsec = 	0.105E+01 ; xsec_unc = 7.27E-02; return; }
      else if (mStop_mass == 460) {xsec = 	0.983E+00 ; xsec_unc = 7.3E-02; return; }
      else if (mStop_mass == 465) {xsec = 	0.925E+00 ; xsec_unc = 7.33E-02; return; }
      else if (mStop_mass == 470) {xsec = 	0.870E+00 ; xsec_unc = 7.36E-02; return; }
      else if (mStop_mass == 475) {xsec = 	0.819E+00 ; xsec_unc = 7.38E-02; return; }
      else if (mStop_mass == 480) {xsec = 	0.771E+00 ; xsec_unc = 7.41E-02; return; }
      else if (mStop_mass == 485) {xsec = 	0.727E+00 ; xsec_unc = 7.44E-02; return; }
      else if (mStop_mass == 490) {xsec = 	0.685E+00 ; xsec_unc = 7.47E-02; return; }
      else if (mStop_mass == 495) {xsec = 	0.646E+00 ; xsec_unc = 7.5E-02; return; }
      else if (mStop_mass == 500) {xsec = 	0.609E+00 ; xsec_unc = 7.53E-02; return; }
      else if (mStop_mass == 505) {xsec = 	0.575E+00 ; xsec_unc = 7.56E-02; return; }
      else if (mStop_mass == 510) {xsec = 	0.543E+00 ; xsec_unc = 7.58E-02; return; }
      else if (mStop_mass == 515) {xsec = 	0.513E+00 ; xsec_unc = 7.61E-02; return; }
      else if (mStop_mass == 520) {xsec = 	0.484E+00 ; xsec_unc = 7.64E-02; return; }
      else if (mStop_mass == 525) {xsec = 	0.458E+00 ; xsec_unc = 7.67E-02; return; }
      else if (mStop_mass == 530) {xsec = 	0.433E+00 ; xsec_unc = 7.7E-02; return; }
      else if (mStop_mass == 535) {xsec = 	0.409E+00 ; xsec_unc = 7.73E-02; return; }
      else if (mStop_mass == 540) {xsec = 	0.387E+00 ; xsec_unc = 7.75E-02; return; }
      else if (mStop_mass == 545) {xsec = 	0.367E+00 ; xsec_unc = 7.78E-02; return; }
      else if (mStop_mass == 550) {xsec = 	0.347E+00 ; xsec_unc = 7.81E-02; return; }
      else if (mStop_mass == 555) {xsec = 	0.329E+00 ; xsec_unc = 7.84E-02; return; }
      else if (mStop_mass == 560) {xsec = 	0.312E+00 ; xsec_unc = 7.87E-02; return; }
      else if (mStop_mass == 565) {xsec = 	0.296E+00 ; xsec_unc = 7.9E-02; return; }
      else if (mStop_mass == 570) {xsec = 	0.280E+00 ; xsec_unc = 7.93E-02; return; }
      else if (mStop_mass == 575) {xsec = 	0.266E+00 ; xsec_unc = 7.96E-02; return; }
      else if (mStop_mass == 580) {xsec = 	0.252E+00 ; xsec_unc = 7.99E-02; return; }
      else if (mStop_mass == 585) {xsec = 	0.240E+00 ; xsec_unc = 8.02E-02; return; }
      else if (mStop_mass == 590) {xsec = 	0.228E+00 ; xsec_unc = 8.05E-02; return; }
      else if (mStop_mass == 595) {xsec = 	0.216E+00 ; xsec_unc = 8.08E-02; return; }
      else if (mStop_mass == 600) {xsec = 	0.205E+00 ; xsec_unc = 8.12E-02; return; }
      else if (mStop_mass == 605) {xsec = 	0.195E+00 ; xsec_unc = 8.15E-02; return; }
      else if (mStop_mass == 610) {xsec = 	0.186E+00 ; xsec_unc = 8.18E-02; return; }
      else if (mStop_mass == 615) {xsec = 	0.177E+00 ; xsec_unc = 8.21E-02; return; }
      else if (mStop_mass == 620) {xsec = 	0.168E+00 ; xsec_unc = 8.25E-02; return; }
      else if (mStop_mass == 625) {xsec = 	0.160E+00 ; xsec_unc = 8.28E-02; return; }
      else if (mStop_mass == 630) {xsec = 	0.152E+00 ; xsec_unc = 8.31E-02; return; }
      else if (mStop_mass == 635) {xsec = 	0.145E+00 ; xsec_unc = 8.35E-02; return; }
      else if (mStop_mass == 640) {xsec = 	0.138E+00 ; xsec_unc = 8.38E-02; return; }
      else if (mStop_mass == 645) {xsec = 	0.131E+00 ; xsec_unc = 8.42E-02; return; }
      else if (mStop_mass == 650) {xsec = 	0.125E+00 ; xsec_unc = 8.45E-02; return; }
      else if (mStop_mass == 655) {xsec = 	0.119E+00 ; xsec_unc = 8.49E-02; return; }
      else if (mStop_mass == 660) {xsec = 	0.114E+00 ; xsec_unc = 8.52E-02; return; }
      else if (mStop_mass == 665) {xsec = 	0.108E+00 ; xsec_unc = 8.56E-02; return; }
      else if (mStop_mass == 670) {xsec = 	0.103E+00 ; xsec_unc = 8.59E-02; return; }
      else if (mStop_mass == 675) {xsec = 	0.987E-01 ; xsec_unc = 8.63E-02; return; }
      else if (mStop_mass == 680) {xsec = 	0.942E-01 ; xsec_unc = 8.66E-02; return; }
      else if (mStop_mass == 685) {xsec = 	0.899E-01 ; xsec_unc = 8.7E-02; return; }
      else if (mStop_mass == 690) {xsec = 	0.858E-01 ; xsec_unc = 8.73E-02; return; }
      else if (mStop_mass == 695) {xsec = 	0.820E-01 ; xsec_unc = 8.77E-02; return; }
      else if (mStop_mass == 700) {xsec = 	0.783E-01 ; xsec_unc = 8.8E-02; return; }
      else if (mStop_mass == 705) {xsec = 	0.748E-01 ; xsec_unc = 8.84E-02; return; }
      else if (mStop_mass == 710) {xsec = 	0.715E-01 ; xsec_unc = 8.88E-02; return; }
      else if (mStop_mass == 715) {xsec = 	0.683E-01 ; xsec_unc = 8.91E-02; return; }
      else if (mStop_mass == 720) {xsec = 	0.653E-01 ; xsec_unc = 8.95E-02; return; }
      else if (mStop_mass == 725) {xsec = 	0.624E-01 ; xsec_unc = 8.98E-02; return; }
      else if (mStop_mass == 730) {xsec = 	0.597E-01 ; xsec_unc = 9.02E-02; return; }
      else if (mStop_mass == 735) {xsec = 	0.571E-01 ; xsec_unc = 9.05E-02; return; }
      else if (mStop_mass == 740) {xsec = 	0.546E-01 ; xsec_unc = 9.09E-02; return; }
      else if (mStop_mass == 745) {xsec = 	0.523E-01 ; xsec_unc = 9.13E-02; return; }
      else if (mStop_mass == 750) {xsec = 	0.500E-01 ; xsec_unc = 9.16E-02; return; }
      else if (mStop_mass == 755) {xsec = 	0.479E-01 ; xsec_unc = 9.2E-02; return; }
      else if (mStop_mass == 760) {xsec = 	0.459E-01 ; xsec_unc = 9.24E-02; return; }
      else if (mStop_mass == 765) {xsec = 	0.439E-01 ; xsec_unc = 9.27E-02; return; }
      else if (mStop_mass == 770) {xsec = 	0.421E-01 ; xsec_unc = 9.31E-02; return; }
      else if (mStop_mass == 775) {xsec = 	0.403E-01 ; xsec_unc = 9.35E-02; return; }
      else if (mStop_mass == 780) {xsec = 	0.386E-01 ; xsec_unc = 9.38E-02; return; }
      else if (mStop_mass == 785) {xsec = 	0.370E-01 ; xsec_unc = 9.42E-02; return; }
      else if (mStop_mass == 790) {xsec = 	0.355E-01 ; xsec_unc = 9.46E-02; return; }
      else if (mStop_mass == 795) {xsec = 	0.340E-01 ; xsec_unc = 9.5E-02; return; }
      else if (mStop_mass == 800) {xsec = 	0.326E-01 ; xsec_unc = 9.53E-02; return; }
      else if (mStop_mass == 805) {xsec = 	0.313E-01 ; xsec_unc = 9.57E-02; return; }
      else if (mStop_mass == 810) {xsec = 	0.300E-01 ; xsec_unc = 9.61E-02; return; }
      else if (mStop_mass == 815) {xsec = 	0.288E-01 ; xsec_unc = 9.65E-02; return; }
      else if (mStop_mass == 820) {xsec = 	0.276E-01 ; xsec_unc = 9.69E-02; return; }
      else if (mStop_mass == 825) {xsec = 	0.265E-01 ; xsec_unc = 9.73E-02; return; }
      else if (mStop_mass == 830) {xsec = 	0.254E-01 ; xsec_unc = 9.77E-02; return; }
      else if (mStop_mass == 835) {xsec = 	0.244E-01 ; xsec_unc = 9.81E-02; return; }
      else if (mStop_mass == 840) {xsec = 	0.234E-01 ; xsec_unc = 9.85E-02; return; }
      else if (mStop_mass == 845) {xsec = 	0.225E-01 ; xsec_unc = 9.89E-02; return; }
      else if (mStop_mass == 850) {xsec = 	0.216E-01 ; xsec_unc = 9.93E-02; return; }
      else if (mStop_mass == 855) {xsec = 	0.208E-01 ; xsec_unc = 9.97E-02; return; }
      else if (mStop_mass == 860) {xsec = 	0.199E-01 ; xsec_unc = 10.01E-02; return; }
      else if (mStop_mass == 865) {xsec = 	0.192E-01 ; xsec_unc = 10.05E-02; return; }
      else if (mStop_mass == 870) {xsec = 	0.184E-01 ; xsec_unc = 10.09E-02; return; }
      else if (mStop_mass == 875) {xsec = 	0.177E-01 ; xsec_unc = 10.13E-02; return; }
      else if (mStop_mass == 880) {xsec = 	0.170E-01 ; xsec_unc = 10.17E-02; return; }
      else if (mStop_mass == 885) {xsec = 	0.164E-01 ; xsec_unc = 10.21E-02; return; }
      else if (mStop_mass == 890) {xsec = 	0.157E-01 ; xsec_unc = 10.25E-02; return; }
      else if (mStop_mass == 895) {xsec = 	0.151E-01 ; xsec_unc = 10.29E-02; return; }
      else if (mStop_mass == 900) {xsec = 	0.145E-01 ; xsec_unc = 10.33E-02; return; }
      else if (mStop_mass == 905) {xsec = 	0.140E-01 ; xsec_unc = 10.38E-02; return; }
      else if (mStop_mass == 910) {xsec = 	0.135E-01 ; xsec_unc = 10.42E-02; return; }
      else if (mStop_mass == 915) {xsec = 	0.129E-01 ; xsec_unc = 10.46E-02; return; }
      else if (mStop_mass == 920) {xsec = 	0.125E-01 ; xsec_unc = 10.5E-02; return; }
      else if (mStop_mass == 925) {xsec = 	0.120E-01 ; xsec_unc = 10.54E-02; return; }
      else if (mStop_mass == 930) {xsec = 	0.115E-01 ; xsec_unc = 10.59E-02; return; }
      else if (mStop_mass == 935) {xsec = 	0.111E-01 ; xsec_unc = 10.63E-02; return; }
      else if (mStop_mass == 940) {xsec = 	0.107E-01 ; xsec_unc = 10.67E-02; return; }
      else if (mStop_mass == 945) {xsec = 	0.103E-01 ; xsec_unc = 10.71E-02; return; }
      else if (mStop_mass == 950) {xsec = 	0.991E-02 ; xsec_unc = 10.76E-02; return; }
      else if (mStop_mass == 955) {xsec = 	0.954E-02 ; xsec_unc = 10.8E-02; return; }
      else if (mStop_mass == 960) {xsec = 	0.919E-02 ; xsec_unc = 10.84E-02; return; }
      else if (mStop_mass == 965) {xsec = 	0.885E-02 ; xsec_unc = 10.89E-02; return; }
      else if (mStop_mass == 970) {xsec = 	0.853E-02 ; xsec_unc = 10.93E-02; return; }
      else if (mStop_mass == 975) {xsec = 	0.822E-02 ; xsec_unc = 10.97E-02; return; }
      else if (mStop_mass == 980) {xsec = 	0.792E-02 ; xsec_unc = 11.02E-02; return; }
      else if (mStop_mass == 985) {xsec = 	0.763E-02 ; xsec_unc = 11.06E-02; return; }
      else if (mStop_mass == 990) {xsec = 	0.735E-02 ; xsec_unc = 11.11E-02; return; }
      else if (mStop_mass == 995) {xsec = 	0.709E-02 ; xsec_unc = 11.15E-02; return; }
      else if (mStop_mass == 1000) {xsec = 	0.683E-02 ; xsec_unc = 11.2E-02; return; }
      else if (mStop_mass == 1005) {xsec = 	0.659E-02 ; xsec_unc = 11.24E-02; return; }
      else if (mStop_mass == 1010) {xsec = 	0.635E-02 ; xsec_unc = 11.29E-02; return; }
      else if (mStop_mass == 1015) {xsec = 	0.613E-02 ; xsec_unc = 11.33E-02; return; }
      else if (mStop_mass == 1020) {xsec = 	0.591E-02 ; xsec_unc = 11.38E-02; return; }
      else if (mStop_mass == 1025) {xsec = 	0.570E-02 ; xsec_unc = 11.42E-02; return; }
      else if (mStop_mass == 1030) {xsec = 	0.550E-02 ; xsec_unc = 11.47E-02; return; }
      else if (mStop_mass == 1035) {xsec = 	0.530E-02 ; xsec_unc = 11.51E-02; return; }
      else if (mStop_mass == 1040) {xsec = 	0.511E-02 ; xsec_unc = 11.56E-02; return; }
      else if (mStop_mass == 1045) {xsec = 	0.493E-02 ; xsec_unc = 11.6E-02; return; }
      else if (mStop_mass == 1050) {xsec = 	0.476E-02 ; xsec_unc = 11.65E-02; return; }
      else if (mStop_mass == 1055) {xsec = 	0.460E-02 ; xsec_unc = 11.7E-02; return; }
      else if (mStop_mass == 1060) {xsec = 	0.444E-02 ; xsec_unc = 11.74E-02; return; }
      else if (mStop_mass == 1065) {xsec = 	0.428E-02 ; xsec_unc = 11.79E-02; return; }
      else if (mStop_mass == 1070) {xsec = 	0.413E-02 ; xsec_unc = 11.84E-02; return; }
      else if (mStop_mass == 1075) {xsec = 	0.399E-02 ; xsec_unc = 11.88E-02; return; }
      else if (mStop_mass == 1080) {xsec = 	0.385E-02 ; xsec_unc = 11.93E-02; return; }
      else if (mStop_mass == 1085) {xsec = 	0.372E-02 ; xsec_unc = 11.98E-02; return; }
      else if (mStop_mass == 1090) {xsec = 	0.359E-02 ; xsec_unc = 12.03E-02; return; }
      else if (mStop_mass == 1095) {xsec = 	0.347E-02 ; xsec_unc = 12.07E-02; return; }
      else if (mStop_mass == 1100) {xsec = 	0.335E-02 ; xsec_unc = 12.12E-02; return; }
      else if (mStop_mass == 1105) {xsec = 	0.324E-02 ; xsec_unc = 12.17E-02; return; }
      else if (mStop_mass == 1110) {xsec = 	0.313E-02 ; xsec_unc = 12.22E-02; return; }
      else if (mStop_mass == 1115) {xsec = 	0.302E-02 ; xsec_unc = 12.27E-02; return; }
      else if (mStop_mass == 1120) {xsec = 	0.292E-02 ; xsec_unc = 12.32E-02; return; }
      else if (mStop_mass == 1125) {xsec = 	0.282E-02 ; xsec_unc = 12.37E-02; return; }
      else if (mStop_mass == 1130) {xsec = 	0.272E-02 ; xsec_unc = 12.42E-02; return; }
      else if (mStop_mass == 1135) {xsec = 	0.263E-02 ; xsec_unc = 12.47E-02; return; }
      else if (mStop_mass == 1140) {xsec = 	0.254E-02 ; xsec_unc = 12.52E-02; return; }
      else if (mStop_mass == 1145) {xsec = 	0.246E-02 ; xsec_unc = 12.57E-02; return; }
      else if (mStop_mass == 1150) {xsec = 	0.238E-02 ; xsec_unc = 12.62E-02; return; }
      else if (mStop_mass == 1155) {xsec = 	0.230E-02 ; xsec_unc = 12.67E-02; return; }
      else if (mStop_mass == 1160) {xsec = 	0.222E-02 ; xsec_unc = 12.72E-02; return; }
      else if (mStop_mass == 1165) {xsec = 	0.215E-02 ; xsec_unc = 12.77E-02; return; }
      else if (mStop_mass == 1170) {xsec = 	0.208E-02 ; xsec_unc = 12.82E-02; return; }
      else if (mStop_mass == 1175) {xsec = 	0.201E-02 ; xsec_unc = 12.87E-02; return; }
      else if (mStop_mass == 1180) {xsec = 	0.194E-02 ; xsec_unc = 12.93E-02; return; }
      else if (mStop_mass == 1185) {xsec = 	0.188E-02 ; xsec_unc = 12.98E-02; return; }
      else if (mStop_mass == 1190) {xsec = 	0.182E-02 ; xsec_unc = 13.03E-02; return; }
      else if (mStop_mass == 1195) {xsec = 	0.176E-02 ; xsec_unc = 13.08E-02; return; }
      else if (mStop_mass == 1200) {xsec = 	0.170E-02 ; xsec_unc = 13.13E-02; return; }
      else if (mStop_mass == 1205) {xsec = 	0.164E-02 ; xsec_unc = 13.19E-02; return; }
      else if (mStop_mass == 1210) {xsec = 	0.159E-02 ; xsec_unc = 13.24E-02; return; }
      else if (mStop_mass == 1215) {xsec = 	0.154E-02 ; xsec_unc = 13.29E-02; return; }
      else if (mStop_mass == 1220) {xsec = 	0.149E-02 ; xsec_unc = 13.34E-02; return; }
      else if (mStop_mass == 1225) {xsec = 	0.144E-02 ; xsec_unc = 13.4E-02; return; }
      else if (mStop_mass == 1230) {xsec = 	0.139E-02 ; xsec_unc = 13.45E-02; return; }
      else if (mStop_mass == 1235) {xsec = 	0.135E-02 ; xsec_unc = 13.5E-02; return; }
      else if (mStop_mass == 1240) {xsec = 	0.131E-02 ; xsec_unc = 13.55E-02; return; }
      else if (mStop_mass == 1245) {xsec = 	0.126E-02 ; xsec_unc = 13.61E-02; return; }
      else if (mStop_mass == 1250) {xsec = 	0.122E-02 ; xsec_unc = 13.66E-02; return; }
      else if (mStop_mass == 1255) {xsec = 	0.118E-02 ; xsec_unc = 13.72E-02; return; }
      else if (mStop_mass == 1260) {xsec = 	0.115E-02 ; xsec_unc = 13.77E-02; return; }
      else if (mStop_mass == 1265) {xsec = 	0.111E-02 ; xsec_unc = 13.82E-02; return; }
      else if (mStop_mass == 1270) {xsec = 	0.107E-02 ; xsec_unc = 13.88E-02; return; }
      else if (mStop_mass == 1275) {xsec = 	0.104E-02 ; xsec_unc = 13.93E-02; return; }
      else if (mStop_mass == 1280) {xsec = 	0.101E-02 ; xsec_unc = 13.99E-02; return; }
      else if (mStop_mass == 1285) {xsec = 	0.976E-03 ; xsec_unc = 14.04E-02; return; }
      else if (mStop_mass == 1290) {xsec = 	0.945E-03 ; xsec_unc = 14.1E-02; return; }
      else if (mStop_mass == 1295) {xsec = 	0.915E-03 ; xsec_unc = 14.15E-02; return; }
      else if (mStop_mass == 1300) {xsec = 	0.887E-03 ; xsec_unc = 14.21E-02; return; }
      else if (mStop_mass == 1305) {xsec = 	0.859E-03 ; xsec_unc = 14.26E-02; return; }
      else if (mStop_mass == 1310) {xsec = 	0.832E-03 ; xsec_unc = 14.32E-02; return; }
      else if (mStop_mass == 1315) {xsec = 	0.806E-03 ; xsec_unc = 14.38E-02; return; }
      else if (mStop_mass == 1320) {xsec = 	0.781E-03 ; xsec_unc = 14.43E-02; return; }
      else if (mStop_mass == 1325) {xsec = 	0.756E-03 ; xsec_unc = 14.49E-02; return; }
      else if (mStop_mass == 1330) {xsec = 	0.733E-03 ; xsec_unc = 14.55E-02; return; }
      else if (mStop_mass == 1335) {xsec = 	0.710E-03 ; xsec_unc = 14.61E-02; return; }
      else if (mStop_mass == 1340) {xsec = 	0.688E-03 ; xsec_unc = 14.66E-02; return; }
      else if (mStop_mass == 1345) {xsec = 	0.667E-03 ; xsec_unc = 14.72E-02; return; }
      else if (mStop_mass == 1350) {xsec = 	0.646E-03 ; xsec_unc = 14.78E-02; return; }
      else if (mStop_mass == 1355) {xsec = 	0.626E-03 ; xsec_unc = 14.84E-02; return; }
      else if (mStop_mass == 1360) {xsec = 	0.607E-03 ; xsec_unc = 14.9E-02; return; }
      else if (mStop_mass == 1365) {xsec = 	0.588E-03 ; xsec_unc = 14.95E-02; return; }
      else if (mStop_mass == 1370) {xsec = 	0.570E-03 ; xsec_unc = 15.01E-02; return; }
      else if (mStop_mass == 1375) {xsec = 	0.553E-03 ; xsec_unc = 15.07E-02; return; }
      else if (mStop_mass == 1380) {xsec = 	0.536E-03 ; xsec_unc = 15.13E-02; return; }
      else if (mStop_mass == 1385) {xsec = 	0.519E-03 ; xsec_unc = 15.19E-02; return; }
      else if (mStop_mass == 1390) {xsec = 	0.503E-03 ; xsec_unc = 15.25E-02; return; }
      else if (mStop_mass == 1395) {xsec = 	0.488E-03 ; xsec_unc = 15.31E-02; return; }
      else if (mStop_mass == 1400) {xsec = 	0.473E-03 ; xsec_unc = 15.37E-02; return; }
      else if (mStop_mass == 1400) {xsec = 	0.473E-03 ; xsec_unc = 15.37E-02; return; }
      else {xsec = 0.; xsec_unc = 0.;}
  }
