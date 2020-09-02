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
    if (mStop_mass == 100 ) { xsec = 	1521.11 ; xsec_unc =  0.154038; return; }
      else if (mStop_mass == 105 ) { xsec = 	1233.18 ; xsec_unc =  0.154059; return; }
      else if (mStop_mass == 110 ) { xsec = 	1013.76 ; xsec_unc =  0.154088; return; }
      else if (mStop_mass == 115 ) { xsec = 	832.656 ; xsec_unc =  0.151503; return; }
      else if (mStop_mass == 120 ) { xsec = 	689.799 ; xsec_unc =  0.15044 ; return; }
      else if (mStop_mass == 125 ) { xsec = 	574.981 ; xsec_unc =  0.149895; return; }
      else if (mStop_mass == 130 ) { xsec = 	481.397 ; xsec_unc =  0.148906; return; }
      else if (mStop_mass == 135 ) { xsec = 	405.159 ; xsec_unc =  0.148952; return; }
      else if (mStop_mass == 140 ) { xsec = 	342.865 ; xsec_unc =  0.149119; return; }
      else if (mStop_mass == 145 ) { xsec = 	291.752 ; xsec_unc =  0.148022; return; }
      else if (mStop_mass == 150 ) { xsec = 	249.409 ; xsec_unc =  0.147477; return; }
      else if (mStop_mass == 155 ) { xsec = 	214.221 ; xsec_unc =  0.145928; return; }
      else if (mStop_mass == 160 ) { xsec = 	184.623 ; xsec_unc =  0.145821; return; }
      else if (mStop_mass == 165 ) { xsec = 	159.614 ; xsec_unc =  0.147859; return; }
      else if (mStop_mass == 170 ) { xsec = 	139.252 ; xsec_unc =  0.14547 ; return; }
      else if (mStop_mass == 175 ) { xsec = 	121.416 ; xsec_unc =  0.146341; return; }
      else if (mStop_mass == 180 ) { xsec = 	106.194 ; xsec_unc =  0.142033; return; }
      else if (mStop_mass == 185 ) { xsec = 	93.3347 ; xsec_unc =  0.144893; return; }
      else if (mStop_mass == 190 ) { xsec = 	82.2541 ; xsec_unc =  0.144677; return; }
      else if (mStop_mass == 195 ) { xsec = 	72.7397 ; xsec_unc =  0.144452; return; }
      else if (mStop_mass == 200 ) { xsec = 	64.5085 ; xsec_unc =  0.144098; return; }
      else if (mStop_mass == 205 ) { xsec = 	57.2279 ; xsec_unc =  0.144191; return; }
      else if (mStop_mass == 210 ) { xsec = 	50.9226 ; xsec_unc =  0.142457; return; }
      else if (mStop_mass == 215 ) { xsec = 	45.3761 ; xsec_unc =  0.14344 ; return; }
      else if (mStop_mass == 220 ) { xsec = 	40.5941 ; xsec_unc =  0.142634; return; }
      else if (mStop_mass == 225 ) { xsec = 	36.3818 ; xsec_unc =  0.142189; return; }
      else if (mStop_mass == 230 ) { xsec = 	32.6679 ; xsec_unc =  0.141592; return; }
      else if (mStop_mass == 235 ) { xsec = 	29.3155 ; xsec_unc =  0.142233; return; }
      else if (mStop_mass == 240 ) { xsec = 	26.4761 ; xsec_unc =  0.141723; return; }
      else if (mStop_mass == 245 ) { xsec = 	23.8853 ; xsec_unc =  0.139482; return; }
      else if (mStop_mass == 250 ) { xsec = 	21.5949 ; xsec_unc =  0.140595; return; }
      else if (mStop_mass == 255 ) { xsec = 	19.5614 ; xsec_unc =  0.138755; return; }
      else if (mStop_mass == 260 ) { xsec = 	17.6836 ; xsec_unc =  0.139505; return; }
      else if (mStop_mass == 265 ) { xsec = 	16.112  ; xsec_unc =  0.139531; return; }
      else if (mStop_mass == 270 ) { xsec = 	14.6459 ; xsec_unc = 0.139278; return; }
      else if (mStop_mass == 275 ) { xsec = 	13.3231 ; xsec_unc =  0.142549; return; }
      else if (mStop_mass == 280 ) { xsec = 	12.1575 ; xsec_unc =  0.141584; return; }
      else if (mStop_mass == 285 ) { xsec = 	11.0925 ; xsec_unc =  0.140904; return; }
      else if (mStop_mass == 290 ) { xsec = 	10.1363 ; xsec_unc =  0.138967; return; }
      else if (mStop_mass == 295 ) { xsec = 	9.29002 ; xsec_unc =  0.139107; return; } 
      else if (mStop_mass == 300 ) { xsec =  	8.51615 ; xsec_unc =  0.139223; return; }
      else if (mStop_mass == 305 ) { xsec =  	7.81428 ; xsec_unc =  0.138996; return; }
      else if (mStop_mass == 310 ) { xsec =  	7.17876 ; xsec_unc =  0.139357; return; }
      else if (mStop_mass == 315 ) { xsec =  	6.60266 ; xsec_unc =  0.139256; return; }
      else if (mStop_mass == 320 ) { xsec =  	6.08444 ; xsec_unc =  0.137957; return; }
      else if (mStop_mass == 325 ) { xsec =  	5.60471 ; xsec_unc =  0.138144; return; }
      else if (mStop_mass == 330 ) { xsec =  	5.17188 ; xsec_unc =  0.136954; return; }
      else if (mStop_mass == 335 ) { xsec =  	4.77871 ; xsec_unc =  0.137554; return; }
      else if (mStop_mass == 340 ) { xsec =  	4.41629 ; xsec_unc =  0.137945; return; }
      else if (mStop_mass == 345 ) { xsec =  	4.08881 ; xsec_unc =  0.137075; return; }
      else if (mStop_mass == 350 ) { xsec =  	3.78661 ; xsec_unc =  0.136877; return; }
      else if (mStop_mass == 355 ) { xsec =  	3.50911 ; xsec_unc =  0.138089; return; }
      else if (mStop_mass == 360 ) { xsec =  	3.25619 ; xsec_unc =  0.138002; return; }
      else if (mStop_mass == 365 ) { xsec =  	3.02472 ; xsec_unc =  0.137093; return; }
      else if (mStop_mass == 370 ) { xsec =  	2.8077 ; xsec_unc =  0.138064; return; }
      else if (mStop_mass == 375 ) { xsec =  	2.61162 ; xsec_unc =  0.138477; return; }
      else if (mStop_mass == 380 ) { xsec =  	2.43031 ; xsec_unc =  0.136999; return; }
      else if (mStop_mass == 385 ) { xsec =  	2.26365 ; xsec_unc =  0.13728; return; }
      else if (mStop_mass == 390 ) { xsec =  	2.10786 ; xsec_unc =  0.13732; return; }
      else if (mStop_mass == 395 ) { xsec =  	1.9665 ; xsec_unc =  0.134737; return; }
      else if (mStop_mass == 400 ) { xsec =  	1.83537 ; xsec_unc =  0.136985; return; }
      else if (mStop_mass == 405 ) { xsec =  	1.70927 ; xsec_unc =  0.137114; return; }
      else if (mStop_mass == 410 ) { xsec =  	1.60378 ; xsec_unc =  0.135468; return; }
      else if (mStop_mass == 415 ) { xsec =  	1.49798 ; xsec_unc =  0.134453; return; }
      else if (mStop_mass == 420 ) { xsec =  	1.39688 ; xsec_unc =  0.136719; return; }
      else if (mStop_mass == 425 ) { xsec =  	1.31169 ; xsec_unc =  0.135013; return; }
      else if (mStop_mass == 430 ) { xsec =  	1.22589 ; xsec_unc =  0.133237; return; }
      else if (mStop_mass == 435 ) { xsec =  	1.14553 ; xsec_unc =  0.135478; return; }
      else if (mStop_mass == 440 ) { xsec =  	1.07484 ; xsec_unc =  0.137238; return; }
      else if (mStop_mass == 445 ) { xsec =  	1.01019 ; xsec_unc =  0.134187; return; }
      else if (mStop_mass == 450 ) { xsec =  	0.948333 ; xsec_unc =  0.134559; return; }
      else if (mStop_mass == 455 ) { xsec =  	0.890847 ; xsec_unc =  0.134587; return; }
      else if (mStop_mass == 460 ) { xsec =  	0.836762 ; xsec_unc =  0.134468; return; }
      else if (mStop_mass == 465 ) { xsec =  	0.787221 ; xsec_unc =  0.134149; return; }
      else if (mStop_mass == 470 ) { xsec =  	0.740549 ; xsec_unc =  0.134127; return; }
      else if (mStop_mass == 475 ) { xsec =  	0.697075 ; xsec_unc =  0.133926; return; }
      else if (mStop_mass == 480 ) { xsec =  	0.655954 ; xsec_unc =  0.134392; return; }
      else if (mStop_mass == 485 ) { xsec =  	0.618562 ; xsec_unc =  0.133705; return; }
      else if (mStop_mass == 490 ) { xsec =  	0.582467 ; xsec_unc =  0.133914; return; }
      else if (mStop_mass == 495 ) { xsec =  	0.549524 ; xsec_unc =  0.133691; return; }
      else if (mStop_mass == 500 ) { xsec =  	0.51848 ; xsec_unc =  0.133797; return; }
      else if (mStop_mass == 505 ) { xsec =  	0.489324 ; xsec_unc =  0.133608; return; }
      else if (mStop_mass == 510 ) { xsec =  	0.462439 ; xsec_unc =  0.133046; return; }
      else if (mStop_mass == 515 ) { xsec =  	0.436832 ; xsec_unc =  0.133703; return; }
      else if (mStop_mass == 520 ) { xsec =  	0.412828 ; xsec_unc =  0.13272; return; }
      else if (mStop_mass == 525 ) { xsec =  	0.390303 ; xsec_unc =  0.133443; return; }
      else if (mStop_mass == 530 ) { xsec =  	0.368755 ; xsec_unc =  0.133769; return; }
      else if (mStop_mass == 535 ) { xsec =  	0.348705 ; xsec_unc =  0.132706; return; }
      else if (mStop_mass == 540 ) { xsec =  	0.330157 ; xsec_unc =  0.132981; return; }
      else if (mStop_mass == 545 ) { xsec =  	0.312672 ; xsec_unc =  0.13277; return; }
      else if (mStop_mass == 550 ) { xsec =  	0.296128 ; xsec_unc =  0.132687; return; }
      else if (mStop_mass == 555 ) { xsec =  	0.280734 ; xsec_unc =  0.132363; return; }
      else if (mStop_mass == 560 ) { xsec =  	0.266138 ; xsec_unc =  0.13193; return; }
      else if (mStop_mass == 565 ) { xsec =  	0.251557 ; xsec_unc =  0.131731; return; }
      else if (mStop_mass == 570 ) { xsec =  	0.238537 ; xsec_unc =  0.133409; return; }
      else if (mStop_mass == 575 ) { xsec =  	0.226118 ; xsec_unc =  0.132741; return; }
      else if (mStop_mass == 580 ) { xsec =  	0.214557 ; xsec_unc =  0.131697; return; }
      else if (mStop_mass == 585 ) { xsec =  	0.203566 ; xsec_unc =  0.133257; return; }
      else if (mStop_mass == 590 ) { xsec =  	0.193079 ; xsec_unc =  0.132037; return; }
      else if (mStop_mass == 595 ) { xsec =  	0.183604 ; xsec_unc =  0.130973; return; }
      else if (mStop_mass == 600 ) { xsec =  	0.174599 ; xsec_unc =  0.132074; return; }
      else if (mStop_mass == 605 ) { xsec =  	0.166131 ; xsec_unc =  0.130154; return; }
      else if (mStop_mass == 610 ) { xsec =  	0.158242 ; xsec_unc =  0.13142; return; }
      else if (mStop_mass == 615 ) { xsec =  	0.150275 ; xsec_unc =  0.13285; return; }
      else if (mStop_mass == 620 ) { xsec =  	0.142787 ; xsec_unc =  0.130642; return; }
      else if (mStop_mass == 625 ) { xsec =  	0.136372 ; xsec_unc =  0.127962; return; }
      else if (mStop_mass == 630 ) { xsec =  	0.129886 ; xsec_unc =  0.132957; return; }
      else if (mStop_mass == 635 ) { xsec =  	0.123402 ; xsec_unc =  0.13016; return; }
      else if (mStop_mass == 640 ) { xsec =  	0.11795 ; xsec_unc =  0.127132; return; }
      else if (mStop_mass == 645 ) { xsec =  	0.112008 ; xsec_unc =  0.12808; return; }
      else if (mStop_mass == 650 ) { xsec =  	0.107045 ; xsec_unc =  0.129232; return; }
      else if (mStop_mass == 655 ) { xsec =  	0.102081 ; xsec_unc =  0.130012; return; }
      else if (mStop_mass == 660 ) { xsec =  	0.09725 ; xsec_unc =  0.129038; return; }
      else if (mStop_mass == 665 ) { xsec =  	0.0927515 ; xsec_unc =  0.129548; return; }
      else if (mStop_mass == 670 ) { xsec =  	0.0885084 ; xsec_unc =  0.130218; return; }
      else if (mStop_mass == 675 ) { xsec =  	0.0844877 ; xsec_unc =  0.130703; return; }
      else if (mStop_mass == 680 ) { xsec =  	0.0806192 ; xsec_unc =  0.131131; return; }
      else if (mStop_mass == 685 ) { xsec =  	0.0769099 ; xsec_unc =  0.131517; return; }
      else if (mStop_mass == 690 ) { xsec =  	0.0734901 ; xsec_unc =  0.132344; return; }
      else if (mStop_mass == 695 ) { xsec =  	0.0701805 ; xsec_unc =  0.132716; return; }
      else if (mStop_mass == 700 ) { xsec =  	0.0670476 ; xsec_unc =  0.133429; return; }
      else if (mStop_mass == 705 ) { xsec =  	0.0641426 ; xsec_unc =  0.13363; return; }
      else if (mStop_mass == 710 ) { xsec =  	0.0612942 ; xsec_unc =  0.133941; return; }
      else if (mStop_mass == 715 ) { xsec =  	0.0585678 ; xsec_unc =  0.134663; return; }
      else if (mStop_mass == 720 ) { xsec =  	0.0560753 ; xsec_unc =  0.134984; return; }
      else if (mStop_mass == 725 ) { xsec =  	0.0536438 ; xsec_unc =  0.135804; return; }
      else if (mStop_mass == 730 ) { xsec =  	0.0513219 ; xsec_unc =  0.135682; return; }
      else if (mStop_mass == 735 ) { xsec =  	0.0491001 ; xsec_unc =  0.136268; return; }
      else if (mStop_mass == 740 ) { xsec =  	0.0470801 ; xsec_unc =  0.136895; return; }
      else if (mStop_mass == 745 ) { xsec =  	0.045061 ; xsec_unc =  0.136816; return; }
      else if (mStop_mass == 750 ) { xsec =  	0.0431418 ; xsec_unc =  0.137455; return; }
      else if (mStop_mass == 755 ) { xsec =  	0.0413447 ; xsec_unc =  0.137833; return; }
      else if (mStop_mass == 760 ) { xsec =  	0.0396264 ; xsec_unc =  0.138518; return; }
      else if (mStop_mass == 765 ) { xsec =  	0.0379036 ; xsec_unc =  0.138537; return; }
      else if (mStop_mass == 770 ) { xsec =  	0.0363856 ; xsec_unc =  0.139334; return; }
      else if (mStop_mass == 775 ) { xsec =  	0.0348796 ; xsec_unc =  0.139597; return; }
      else if (mStop_mass == 780 ) { xsec =  	0.0334669 ; xsec_unc =  0.140267; return; }
      else if (mStop_mass == 785 ) { xsec =  	0.0320548 ; xsec_unc =  0.140406; return; }
      else if (mStop_mass == 790 ) { xsec =  	0.0307373 ; xsec_unc =  0.14115; return; }
      else if (mStop_mass == 795 ) { xsec =  	0.0295348 ; xsec_unc =  0.141397; return; }
      else if (mStop_mass == 800 ) { xsec =  	0.0283338 ; xsec_unc =  0.14171; return; }
      else if (mStop_mass == 805 ) { xsec =  	0.0272206 ; xsec_unc =  0.14241; return; }
      else if (mStop_mass == 810 ) { xsec =  	0.0261233 ; xsec_unc =  0.142891; return; }
      else if (mStop_mass == 815 ) { xsec =  	0.0251107 ; xsec_unc =  0.143632; return; }
      else if (mStop_mass == 820 ) { xsec =  	0.0241099 ; xsec_unc =  0.143805; return; }
      else if (mStop_mass == 825 ) { xsec =  	0.0230866 ; xsec_unc =  0.144428; return; }
      else if (mStop_mass == 830 ) { xsec =  	0.0221834 ; xsec_unc =  0.144791; return; }
      else if (mStop_mass == 835 ) { xsec =  	0.0213766 ; xsec_unc =  0.145511; return; }
      else if (mStop_mass == 840 ) { xsec =  	0.0204715 ; xsec_unc =  0.146131; return; }
      else if (mStop_mass == 845 ) { xsec =  	0.0197653 ; xsec_unc =  0.146602; return; }
      else if (mStop_mass == 850 ) { xsec =  	0.0189612 ; xsec_unc =  0.14702; return; }
      else if (mStop_mass == 855 ) { xsec =  	0.0182516 ; xsec_unc =  0.147648; return; }
      else if (mStop_mass == 860 ) { xsec =  	0.0175509 ; xsec_unc =  0.147944; return; }
      else if (mStop_mass == 865 ) { xsec =  	0.0168336 ; xsec_unc =  0.148528; return; }
      else if (mStop_mass == 870 ) { xsec =  	0.0162314 ; xsec_unc =  0.148772; return; }
      else if (mStop_mass == 875 ) { xsec =  	0.015625 ; xsec_unc =  0.149567; return; }
      else if (mStop_mass == 880 ) { xsec =  	0.0150143 ; xsec_unc =  0.150389; return; }
      else if (mStop_mass == 885 ) { xsec =  	0.0144112 ; xsec_unc =  0.150614; return; }
      else if (mStop_mass == 890 ) { xsec =  	0.0138979 ; xsec_unc =  0.151; return; }
      else if (mStop_mass == 895 ) { xsec =  	0.0133962 ; xsec_unc =  0.151325; return; }
      else if (mStop_mass == 900 ) { xsec =  	0.0128895 ; xsec_unc =  0.152026; return; }
      else if (mStop_mass == 905 ) { xsec =  	0.0123843 ; xsec_unc =  0.152968; return; }
      else if (mStop_mass == 910 ) { xsec =  	0.0119837 ; xsec_unc =  0.153089; return; }
      else if (mStop_mass == 915 ) { xsec =  	0.0114713 ; xsec_unc =  0.153678; return; }
      else if (mStop_mass == 920 ) { xsec =  	0.0110688 ; xsec_unc =  0.154082; return; }
      else if (mStop_mass == 925 ) { xsec =  	0.0106631 ; xsec_unc =  0.154806; return; }
      else if (mStop_mass == 930 ) { xsec =  	0.0102629 ; xsec_unc =  0.155313; return; }
      else if (mStop_mass == 935 ) { xsec =  	0.0098874 ; xsec_unc =  0.156066; return; }
      else if (mStop_mass == 940 ) { xsec =  	0.00952142 ; xsec_unc =  0.156055; return; }
      else if (mStop_mass == 945 ) { xsec =  	0.00916636 ; xsec_unc =  0.156849; return; }
      else if (mStop_mass == 950 ) { xsec =  	0.00883465 ; xsec_unc =  0.157177; return; }
      else if (mStop_mass == 955 ) { xsec =  	0.00851073 ; xsec_unc =  0.158094; return; }
      else if (mStop_mass == 960 ) { xsec =  	0.00820884 ; xsec_unc =  0.15844; return; }
      else if (mStop_mass == 965 ) { xsec =  	0.00791403 ; xsec_unc =  0.159216; return; }
      else if (mStop_mass == 970 ) { xsec =  	0.00763112 ; xsec_unc =  0.159742; return; }
      else if (mStop_mass == 975 ) { xsec =  	0.00735655 ; xsec_unc =  0.160548; return; }
      else if (mStop_mass == 980 ) { xsec =  	0.00710317 ; xsec_unc =  0.160626; return; }
      else if (mStop_mass == 985 ) { xsec =  	0.00684867 ; xsec_unc =  0.16144; return; }
      else if (mStop_mass == 990 ) { xsec =  	0.00660695 ; xsec_unc =  0.161813; return; }
      else if (mStop_mass == 995 ) { xsec =  	0.00637546 ; xsec_unc =  0.162158; return; }
      else if (mStop_mass == 1000 ) { xsec =  	0.00615134 ; xsec_unc =  0.162953; return; }
      else if (mStop_mass == 1005 ) { xsec =  	0.00593765 ; xsec_unc =  0.163716; return; }
      else if (mStop_mass == 1010 ) { xsec =  	0.00572452 ; xsec_unc =  0.163857; return; }
      else if (mStop_mass == 1015 ) { xsec =  	0.00553094 ; xsec_unc =  0.164628; return; }
      else if (mStop_mass == 1020 ) { xsec =  	0.00533968 ; xsec_unc =  0.164963; return; }
      else if (mStop_mass == 1025 ) { xsec =  	0.00514619 ; xsec_unc =  0.165762; return; }
      else if (mStop_mass == 1030 ) { xsec =  	0.00497235 ; xsec_unc =  0.165838; return; }
      else if (mStop_mass == 1035 ) { xsec =  	0.00479906 ; xsec_unc =  0.166646; return; }
      else if (mStop_mass == 1040 ) { xsec =  	0.00463806 ; xsec_unc =  0.166947; return; }
      else if (mStop_mass == 1045 ) { xsec =  	0.00447537 ; xsec_unc =  0.167071; return; }
      else if (mStop_mass == 1050 ) { xsec =  	0.00432261 ; xsec_unc =  0.167859; return; }
      else if (mStop_mass == 1055 ) { xsec =  	0.00417983 ; xsec_unc =  0.168637; return; }
      else if (mStop_mass == 1060 ) { xsec =  	0.00403886 ; xsec_unc =  0.168981; return; }
      else if (mStop_mass == 1065 ) { xsec =  	0.0038962 ; xsec_unc =  0.169794; return; }
      else if (mStop_mass == 1070 ) { xsec =  	0.00376343 ; xsec_unc =  0.169764; return; }
      else if (mStop_mass == 1075 ) { xsec =  	0.00364174 ; xsec_unc =  0.170634; return; }
      else if (mStop_mass == 1080 ) { xsec =  	0.00352093 ; xsec_unc =  0.170908; return; }
      else if (mStop_mass == 1085 ) { xsec =  	0.00339813 ; xsec_unc =  0.171929; return; }
      else if (mStop_mass == 1090 ) { xsec =  	0.00328695 ; xsec_unc =  0.172274; return; }
      else if (mStop_mass == 1095 ) { xsec =  	0.00317628 ; xsec_unc =  0.172617; return; }
      else if (mStop_mass == 1100 ) { xsec =  	0.00307413 ; xsec_unc =  0.173377; return; }
      else if (mStop_mass == 1105 ) { xsec =  	0.00297377 ; xsec_unc =  0.173822; return; }
      else if (mStop_mass == 1110 ) { xsec =  	0.00287148 ; xsec_unc =  0.174725; return; }
      else if (mStop_mass == 1115 ) { xsec =  	0.00278078 ; xsec_unc =  0.175091; return; }
      else if (mStop_mass == 1120 ) { xsec =  	0.00268873 ; xsec_unc =  0.175883; return; }
      else if (mStop_mass == 1125 ) { xsec =  	0.00260821 ; xsec_unc =  0.176126; return; }
      else if (mStop_mass == 1130 ) { xsec =  	0.00251529 ; xsec_unc =  0.176836; return; }
      else if (mStop_mass == 1135 ) { xsec =  	0.00243484 ; xsec_unc =  0.177128; return; }
      else if (mStop_mass == 1140 ) { xsec =  	0.00236295 ; xsec_unc =  0.177977; return; }
      else if (mStop_mass == 1145 ) { xsec =  	0.00228192 ; xsec_unc =  0.178507; return; }
      else if (mStop_mass == 1150 ) { xsec =  	0.00221047 ; xsec_unc =  0.179259; return; }
      else if (mStop_mass == 1155 ) { xsec =  	0.00213907 ; xsec_unc =  0.180255; return; }
      else if (mStop_mass == 1160 ) { xsec =  	0.00206845 ; xsec_unc =  0.180518; return; }
      else if (mStop_mass == 1165 ) { xsec =  	0.0020063 ; xsec_unc =  0.180954; return; }
      else if (mStop_mass == 1170 ) { xsec =  	0.00194569 ; xsec_unc =  0.181194; return; }
      else if (mStop_mass == 1175 ) { xsec =  	0.0018741 ; xsec_unc =  0.182145; return; }
      else if (mStop_mass == 1180 ) { xsec =  	0.00182266 ; xsec_unc =  0.183074; return; }
      else if (mStop_mass == 1185 ) { xsec =  	0.00176211 ; xsec_unc =  0.183375; return; }
      else if (mStop_mass == 1190 ) { xsec =  	0.00170006 ; xsec_unc =  0.184075; return; }
      else if (mStop_mass == 1195 ) { xsec =  	0.00164968 ; xsec_unc =  0.184438; return; }
      else if (mStop_mass == 1200 ) { xsec =  	0.00159844 ; xsec_unc =  0.185209; return; }
      else if (mStop_mass == 1205 ) { xsec =  	0.0015472 ; xsec_unc =  0.185977; return; }
      else if (mStop_mass == 1210 ) { xsec =  	0.00149657 ; xsec_unc =  0.186485; return; }
      else if (mStop_mass == 1215 ) { xsec =  	0.00145544 ; xsec_unc =  0.187347; return; }
      else if (mStop_mass == 1220 ) { xsec =  	0.00140288 ; xsec_unc =  0.188774; return; }
      else if (mStop_mass == 1225 ) { xsec =  	0.00136155 ; xsec_unc =  0.18989; return; }
      else if (mStop_mass == 1230 ) { xsec =  	0.00131271 ; xsec_unc =  0.188763; return; }
      else if (mStop_mass == 1235 ) { xsec =  	0.0012717 ; xsec_unc =  0.189588; return; }
      else if (mStop_mass == 1240 ) { xsec =  	0.00123066 ; xsec_unc =  0.19049; return; }
      else if (mStop_mass == 1245 ) { xsec =  	0.00119994 ; xsec_unc =  0.191442; return; }
      else if (mStop_mass == 1250 ) { xsec =  	0.0011583 ; xsec_unc =  0.193006; return; }
      else if (mStop_mass == 1255 ) { xsec =  	0.00112694 ; xsec_unc =  0.194441; return; }
      else if (mStop_mass == 1260 ) { xsec =  	0.00108716 ; xsec_unc =  0.194141; return; }
      else if (mStop_mass == 1265 ) { xsec =  	0.00105517 ; xsec_unc =  0.196361; return; }
      else if (mStop_mass == 1270 ) { xsec =  	0.00102241 ; xsec_unc =  0.196297; return; }
      else if (mStop_mass == 1275 ) { xsec =  	0.000991293 ; xsec_unc =  0.19762; return; }
      else if (mStop_mass == 1280 ) { xsec =  	0.000961012 ; xsec_unc =  0.197926; return; }
      else if (mStop_mass == 1285 ) { xsec =  	0.000932394 ; xsec_unc =  0.198682; return; }
      else if (mStop_mass == 1290 ) { xsec =  	0.000903404 ; xsec_unc =  0.199924; return; }
      else if (mStop_mass == 1295 ) { xsec =  	0.000876957 ; xsec_unc =  0.200777; return; }
      else if (mStop_mass == 1300 ) { xsec =  	0.000850345 ; xsec_unc =  0.201604; return; }
      else if (mStop_mass == 1305 ) { xsec =  	0.00082443 ; xsec_unc =  0.202883; return; }
      else if (mStop_mass == 1310 ) { xsec =  	0.00079983 ; xsec_unc =  0.20373; return; }
      else if (mStop_mass == 1315 ) { xsec =  	0.000775222 ; xsec_unc =  0.204622; return; }
      else if (mStop_mass == 1320 ) { xsec =  	0.000751372 ; xsec_unc =  0.205919; return; }
      else if (mStop_mass == 1325 ) { xsec =  	0.000728912 ; xsec_unc =  0.206884; return; }
      else if (mStop_mass == 1330 ) { xsec =  	0.000706867 ; xsec_unc =  0.207763; return; }
      else if (mStop_mass == 1335 ) { xsec =  	0.000685372 ; xsec_unc =  0.208587; return; }
      else if (mStop_mass == 1340 ) { xsec =  	0.000664649 ; xsec_unc =  0.209879; return; }
      else if (mStop_mass == 1345 ) { xsec =  	0.000644804 ; xsec_unc =  0.211487; return; }
      else if (mStop_mass == 1350 ) { xsec =  	0.000625155 ; xsec_unc =  0.212761; return; }
      else if (mStop_mass == 1355 ) { xsec =  	0.000606802 ; xsec_unc =  0.213529; return; }
      else if (mStop_mass == 1360 ) { xsec =  	0.000588512 ; xsec_unc =  0.214428; return; }
      else if (mStop_mass == 1365 ) { xsec =  	0.000570506 ; xsec_unc =  0.216584; return; }
      else if (mStop_mass == 1370 ) { xsec =  	0.000553379 ; xsec_unc =  0.216036; return; }
      else if (mStop_mass == 1375 ) { xsec =  	0.000536646 ; xsec_unc =  0.21775; return; }
      else if (mStop_mass == 1380 ) { xsec =  	0.000521404 ; xsec_unc =  0.218383; return; }
      else if (mStop_mass == 1385 ) { xsec =  	0.000505008 ; xsec_unc =  0.219675; return; }
      else if (mStop_mass == 1390 ) { xsec =  	0.000490353 ; xsec_unc =  0.221444; return; }
      else if (mStop_mass == 1395 ) { xsec =  	0.000476164 ; xsec_unc =  0.222016; return; }
      else if (mStop_mass == 1400 ) { xsec =  	0.000461944 ; xsec_unc =  0.222704; return; }
      else {xsec = 0.; xsec_unc = 0.;}
  }
