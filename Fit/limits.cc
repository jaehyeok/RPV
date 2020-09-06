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

void limits()
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
    if (glu_mass == 595) { xsec = 0.; xsec_unc = 0.; return; } // we shouldn't have these points
    else if (glu_mass == 600) { xsec = 9.20353; xsec_unc = 0.137185; return; }
    else if (glu_mass == 605) { xsec = 8.74315; xsec_unc = 0.137502; return; }
    else if (glu_mass == 610) { xsec = 8.30988; xsec_unc = 0.136818; return; }
    else if (glu_mass == 615) { xsec = 7.9012; xsec_unc = 0.137122; return; }
    else if (glu_mass == 620) { xsec = 7.51811; xsec_unc = 0.136123; return; }
    else if (glu_mass == 625) { xsec = 7.15194; xsec_unc = 0.136874; return; }
    else if (glu_mass == 630) { xsec = 6.80558; xsec_unc = 0.136655; return; }
    else if (glu_mass == 635) { xsec = 6.47541; xsec_unc = 0.136459; return; }
    else if (glu_mass == 640) { xsec = 6.17196; xsec_unc = 0.136449; return; }
    else if (glu_mass == 645) { xsec = 5.87366; xsec_unc = 0.136392; return; }
    else if (glu_mass == 650) { xsec = 5.60048; xsec_unc = 0.136262; return; }
    else if (glu_mass == 655) { xsec = 5.33799; xsec_unc = 0.137031; return; }
    else if (glu_mass == 660) { xsec = 5.09822; xsec_unc = 0.137329; return; }
    else if (glu_mass == 665) { xsec = 4.86409; xsec_unc = 0.137702; return; }
    else if (glu_mass == 670) { xsec = 4.64349; xsec_unc = 0.138022; return; }
    else if (glu_mass == 675) { xsec = 4.43132; xsec_unc = 0.138749; return; }
    else if (glu_mass == 680) { xsec = 4.23046; xsec_unc = 0.139166; return; }
    else if (glu_mass == 685) { xsec = 4.03841; xsec_unc = 0.139934; return; }
    else if (glu_mass == 690) { xsec = 3.85666; xsec_unc = 0.139917; return; }
    else if (glu_mass == 695) { xsec = 3.68567; xsec_unc = 0.140759; return; }
    else if (glu_mass == 700) { xsec = 3.5251; xsec_unc = 0.141034; return; }
    else if (glu_mass == 705) { xsec = 3.3737; xsec_unc = 0.141609; return; }
    else if (glu_mass == 710) { xsec = 3.22336; xsec_unc = 0.141972; return; }
    else if (glu_mass == 715) { xsec = 3.0811; xsec_unc = 0.142311; return; }
    else if (glu_mass == 720) { xsec = 2.9509; xsec_unc = 0.142518; return; }
    else if (glu_mass == 725) { xsec = 2.81957; xsec_unc = 0.143333; return; }
    else if (glu_mass == 730) { xsec = 2.7; xsec_unc = 0.143772; return; }
    else if (glu_mass == 735) { xsec = 2.57737; xsec_unc = 0.144452; return; }
    else if (glu_mass == 740) { xsec = 2.47729; xsec_unc = 0.144485; return; }
    else if (glu_mass == 745) { xsec = 2.3661; xsec_unc = 0.145381; return; }
    else if (glu_mass == 750) { xsec = 2.26585; xsec_unc = 0.145653; return; }
    else if (glu_mass == 755) { xsec = 2.17436; xsec_unc = 0.145861; return; }
    else if (glu_mass == 760) { xsec = 2.08446; xsec_unc = 0.146279; return; }
    else if (glu_mass == 765) { xsec = 1.99341; xsec_unc = 0.147278; return; }
    else if (glu_mass == 770) { xsec = 1.91352; xsec_unc = 0.147424; return; }
    else if (glu_mass == 775) { xsec = 1.83188; xsec_unc = 0.147835; return; }
    else if (glu_mass == 780) { xsec = 1.76145; xsec_unc = 0.148078; return; }
    else if (glu_mass == 785) { xsec = 1.68078; xsec_unc = 0.148956; return; }
    else if (glu_mass == 790) { xsec = 1.62071; xsec_unc = 0.149017; return; }
    else if (glu_mass == 795) { xsec = 1.54896; xsec_unc = 0.149976; return; }
    else if (glu_mass == 800) { xsec = 1.4891; xsec_unc = 0.150167; return; }
    else if (glu_mass == 805) { xsec = 1.42888; xsec_unc = 0.150599; return; }
    else if (glu_mass == 810) { xsec = 1.36759; xsec_unc = 0.151122; return; }
    else if (glu_mass == 815) { xsec = 1.31749; xsec_unc = 0.151184; return; }
    else if (glu_mass == 820) { xsec = 1.26659; xsec_unc = 0.151928; return; }
    else if (glu_mass == 825) { xsec = 1.2167; xsec_unc = 0.152141; return; }
    else if (glu_mass == 830) { xsec = 1.16617; xsec_unc = 0.152437; return; }
    else if (glu_mass == 835) { xsec = 1.12555; xsec_unc = 0.153009; return; }
    else if (glu_mass == 840) { xsec = 1.07523; xsec_unc = 0.15367; return; }
    else if (glu_mass == 845) { xsec = 1.03426; xsec_unc = 0.154018; return; }
    else if (glu_mass == 850) { xsec = 0.996137; xsec_unc = 0.154252; return; }
    else if (glu_mass == 855) { xsec = 0.957975; xsec_unc = 0.154597; return; }
    else if (glu_mass == 860) { xsec = 0.921447; xsec_unc = 0.155362; return; }
    else if (glu_mass == 865) { xsec = 0.885917; xsec_unc = 0.155643; return; }
    else if (glu_mass == 870) { xsec = 0.852433; xsec_unc = 0.156368; return; }
    else if (glu_mass == 875) { xsec = 0.820259; xsec_unc = 0.156742; return; }
    else if (glu_mass == 880) { xsec = 0.788789; xsec_unc = 0.156746; return; }
    else if (glu_mass == 885) { xsec = 0.759346; xsec_unc = 0.157507; return; }
    else if (glu_mass == 890) { xsec = 0.731213; xsec_unc = 0.157879; return; }
    else if (glu_mass == 895) { xsec = 0.703532; xsec_unc = 0.158276; return; }
    else if (glu_mass == 900) { xsec = 0.677478; xsec_unc = 0.158762; return; }
    else if (glu_mass == 905) { xsec = 0.652317; xsec_unc = 0.15914; return; }
    else if (glu_mass == 910) { xsec = 0.627695; xsec_unc = 0.159569; return; }
    else if (glu_mass == 915) { xsec = 0.605596; xsec_unc = 0.159838; return; }
    else if (glu_mass == 920) { xsec = 0.58302; xsec_unc = 0.16029; return; }
    else if (glu_mass == 925) { xsec = 0.561889; xsec_unc = 0.160626; return; }
    else if (glu_mass == 930) { xsec = 0.540533; xsec_unc = 0.161499; return; }
    else if (glu_mass == 935) { xsec = 0.521159; xsec_unc = 0.161607; return; }
    else if (glu_mass == 940) { xsec = 0.501865; xsec_unc = 0.16245; return; }
    else if (glu_mass == 945) { xsec = 0.483546; xsec_unc = 0.162492; return; }
    else if (glu_mass == 950) { xsec = 0.466352; xsec_unc = 0.163378; return; }
    else if (glu_mass == 955) { xsec = 0.45012; xsec_unc = 0.163303; return; }
    else if (glu_mass == 960) { xsec = 0.433842; xsec_unc = 0.164161; return; }
    else if (glu_mass == 965) { xsec = 0.418744; xsec_unc = 0.164473; return; }
    else if (glu_mass == 970) { xsec = 0.403514; xsec_unc = 0.164538; return; }
    else if (glu_mass == 975) { xsec = 0.389266; xsec_unc = 0.165308; return; }
    else if (glu_mass == 980) { xsec = 0.375053; xsec_unc = 0.165398; return; }
    else if (glu_mass == 985) { xsec = 0.36182; xsec_unc = 0.16619; return; }
    else if (glu_mass == 990) { xsec = 0.349764; xsec_unc = 0.166462; return; }
    else if (glu_mass == 995) { xsec = 0.337454; xsec_unc = 0.166888; return; }
    else if (glu_mass == 1000) { xsec = 0.325388; xsec_unc = 0.16758; return; }
    else if (glu_mass == 1005) { xsec = 0.314329; xsec_unc = 0.167865; return; }
    else if (glu_mass == 1010) { xsec = 0.30314; xsec_unc = 0.168766; return; }
    else if (glu_mass == 1015) { xsec = 0.292987; xsec_unc = 0.168793; return; }
    else if (glu_mass == 1020) { xsec = 0.282927; xsec_unc = 0.169098; return; }
    else if (glu_mass == 1025) { xsec = 0.272778; xsec_unc = 0.169917; return; }
    else if (glu_mass == 1030) { xsec = 0.263724; xsec_unc = 0.170244; return; }
    else if (glu_mass == 1035) { xsec = 0.254721; xsec_unc = 0.170758; return; }
    else if (glu_mass == 1040) { xsec = 0.245426; xsec_unc = 0.171325; return; }
    else if (glu_mass == 1045) { xsec = 0.237403; xsec_unc = 0.171542; return; }
    else if (glu_mass == 1050) { xsec = 0.229367; xsec_unc = 0.171975; return; }
    else if (glu_mass == 1055) { xsec = 0.221273; xsec_unc = 0.172482; return; }
    else if (glu_mass == 1060) { xsec = 0.214167; xsec_unc = 0.173167; return; }
    else if (glu_mass == 1065) { xsec = 0.207025; xsec_unc = 0.173211; return; }
    else if (glu_mass == 1070) { xsec = 0.199967; xsec_unc = 0.173603; return; }
    else if (glu_mass == 1075) { xsec = 0.193881; xsec_unc = 0.174329; return; }
    else if (glu_mass == 1080) { xsec = 0.186836; xsec_unc = 0.174816; return; }
    else if (glu_mass == 1085) { xsec = 0.180783; xsec_unc = 0.175245; return; }
    else if (glu_mass == 1090) { xsec = 0.174652; xsec_unc = 0.175336; return; }
    else if (glu_mass == 1095) { xsec = 0.168526; xsec_unc = 0.176231; return; }
    else if (glu_mass == 1100) { xsec = 0.163491; xsec_unc = 0.176402; return; }
    else if (glu_mass == 1105) { xsec = 0.158451; xsec_unc = 0.176564; return; }
    else if (glu_mass == 1110) { xsec = 0.153298; xsec_unc = 0.177266; return; }
    else if (glu_mass == 1115) { xsec = 0.148246; xsec_unc = 0.177755; return; }
    else if (glu_mass == 1120) { xsec = 0.143169; xsec_unc = 0.17813; return; }
    else if (glu_mass == 1125) { xsec = 0.139009; xsec_unc = 0.178569; return; }
    else if (glu_mass == 1130) { xsec = 0.133972; xsec_unc = 0.179205; return; }
    else if (glu_mass == 1135) { xsec = 0.129938; xsec_unc = 0.17938; return; }
    else if (glu_mass == 1140) { xsec = 0.125799; xsec_unc = 0.179658; return; }
    else if (glu_mass == 1145) { xsec = 0.121755; xsec_unc = 0.180222; return; }
    else if (glu_mass == 1150) { xsec = 0.117687; xsec_unc = 0.180655; return; }
    else if (glu_mass == 1155) { xsec = 0.11358; xsec_unc = 0.181327; return; }
    else if (glu_mass == 1160) { xsec = 0.110557; xsec_unc = 0.181465; return; }
    else if (glu_mass == 1165) { xsec = 0.107532; xsec_unc = 0.181655; return; }
    else if (glu_mass == 1170) { xsec = 0.10339; xsec_unc = 0.182421; return; }
    else if (glu_mass == 1175) { xsec = 0.10036; xsec_unc = 0.182686; return; }
    else if (glu_mass == 1180) { xsec = 0.0971485; xsec_unc = 0.183142; return; }
    else if (glu_mass == 1185) { xsec = 0.0942072; xsec_unc = 0.183623; return; }
    else if (glu_mass == 1190) { xsec = 0.0912756; xsec_unc = 0.183957; return; }
    else if (glu_mass == 1195) { xsec = 0.0883712; xsec_unc = 0.184467; return; }
    else if (glu_mass == 1200) { xsec = 0.0856418; xsec_unc = 0.184814; return; }
    else if (glu_mass == 1205) { xsec = 0.0830236; xsec_unc = 0.185276; return; }
    else if (glu_mass == 1210) { xsec = 0.0804313; xsec_unc = 0.185714; return; }
    else if (glu_mass == 1215) { xsec = 0.0779039; xsec_unc = 0.186096; return; }
    else if (glu_mass == 1220) { xsec = 0.0755801; xsec_unc = 0.186429; return; }
    else if (glu_mass == 1225) { xsec = 0.0732255; xsec_unc = 0.187227; return; }
    else if (glu_mass == 1230) { xsec = 0.0709683; xsec_unc = 0.187266; return; }
    else if (glu_mass == 1235) { xsec = 0.0688462; xsec_unc = 0.187544; return; }
    else if (glu_mass == 1240) { xsec = 0.0666928; xsec_unc = 0.188404; return; }
    else if (glu_mass == 1245) { xsec = 0.0646423; xsec_unc = 0.188414; return; }
    else if (glu_mass == 1250) { xsec = 0.0627027; xsec_unc = 0.189328; return; }
    else if (glu_mass == 1255) { xsec = 0.0607803; xsec_unc = 0.189693; return; }
    else if (glu_mass == 1260) { xsec = 0.0589319; xsec_unc = 0.189695; return; }
    else if (glu_mass == 1265) { xsec = 0.0571859; xsec_unc = 0.190561; return; }
    else if (glu_mass == 1270) { xsec = 0.0554225; xsec_unc = 0.191806; return; }
    else if (glu_mass == 1275) { xsec = 0.0536906; xsec_unc = 0.192452; return; }
    else if (glu_mass == 1280) { xsec = 0.052051; xsec_unc = 0.192396; return; }
    else if (glu_mass == 1285) { xsec = 0.0504982; xsec_unc = 0.193577; return; }
    else if (glu_mass == 1290) { xsec = 0.0489404; xsec_unc = 0.194903; return; }
    else if (glu_mass == 1295) { xsec = 0.047474; xsec_unc = 0.195871; return; }
    else if (glu_mass == 1300) { xsec = 0.0460525; xsec_unc = 0.1964; return; }
    else if (glu_mass == 1305) { xsec = 0.0447038; xsec_unc = 0.197627; return; }
    else if (glu_mass == 1310) { xsec = 0.0433373; xsec_unc = 0.198601; return; }
    else if (glu_mass == 1315) { xsec = 0.0420362; xsec_unc = 0.198634; return; }
    else if (glu_mass == 1320) { xsec = 0.0407723; xsec_unc = 0.199586; return; }
    else if (glu_mass == 1325) { xsec = 0.0395728; xsec_unc = 0.19951; return; }
    else if (glu_mass == 1330) { xsec = 0.0383587; xsec_unc = 0.19993; return; }
    else if (glu_mass == 1335) { xsec = 0.0372043; xsec_unc = 0.201012; return; }
    else if (glu_mass == 1340) { xsec = 0.0361694; xsec_unc = 0.202191; return; }
    else if (glu_mass == 1345) { xsec = 0.0350586; xsec_unc = 0.201714; return; }
    else if (glu_mass == 1350) { xsec = 0.0340187; xsec_unc = 0.203088; return; }
    else if (glu_mass == 1355) { xsec = 0.0330251; xsec_unc = 0.202807; return; }
    else if (glu_mass == 1360) { xsec = 0.0320787; xsec_unc = 0.203682; return; }
    else if (glu_mass == 1365) { xsec = 0.0311325; xsec_unc = 0.205466; return; }
    else if (glu_mass == 1370) { xsec = 0.0302294; xsec_unc = 0.204724; return; }
    else if (glu_mass == 1375) { xsec = 0.0292919; xsec_unc = 0.206217; return; }
    else if (glu_mass == 1380) { xsec = 0.0284627; xsec_unc = 0.207773; return; }
    else if (glu_mass == 1385) { xsec = 0.0276679; xsec_unc = 0.206729; return; }
    else if (glu_mass == 1390) { xsec = 0.0268339; xsec_unc = 0.208251; return; }
    else if (glu_mass == 1395) { xsec = 0.0260313; xsec_unc = 0.207488; return; }
    else if (glu_mass == 1400) { xsec = 0.0252977; xsec_unc = 0.209163; return; }
    else if (glu_mass == 1405) { xsec = 0.0245679; xsec_unc = 0.210704; return; }
    else if (glu_mass == 1410) { xsec = 0.0238741; xsec_unc = 0.209586; return; }
    else if (glu_mass == 1415) { xsec = 0.0231433; xsec_unc = 0.211204; return; }
    else if (glu_mass == 1420) { xsec = 0.0225194; xsec_unc = 0.212481; return; }
    else if (glu_mass == 1425) { xsec = 0.0218959; xsec_unc = 0.214183; return; }
    else if (glu_mass == 1430) { xsec = 0.0211928; xsec_unc = 0.21365; return; }
    else if (glu_mass == 1435) { xsec = 0.0206244; xsec_unc = 0.217574; return; }
    else if (glu_mass == 1440) { xsec = 0.0200458; xsec_unc = 0.216629; return; }
    else if (glu_mass == 1445) { xsec = 0.0194648; xsec_unc = 0.215531; return; }
    else if (glu_mass == 1450) { xsec = 0.0188887; xsec_unc = 0.219548; return; }
    else if (glu_mass == 1455) { xsec = 0.018364; xsec_unc = 0.221266; return; }
    else if (glu_mass == 1460) { xsec = 0.0178858; xsec_unc = 0.220054; return; }
    else if (glu_mass == 1465) { xsec = 0.0173622; xsec_unc = 0.221916; return; }
    else if (glu_mass == 1470) { xsec = 0.0168403; xsec_unc = 0.223972; return; }
    else if (glu_mass == 1475) { xsec = 0.0163556; xsec_unc = 0.222173; return; }
    else if (glu_mass == 1480) { xsec = 0.0159386; xsec_unc = 0.223581; return; }
    else if (glu_mass == 1485) { xsec = 0.0154568; xsec_unc = 0.222281; return; }
    else if (glu_mass == 1490) { xsec = 0.0150345; xsec_unc = 0.224111; return; }
    else if (glu_mass == 1495) { xsec = 0.0146102; xsec_unc = 0.225293; return; }
    else if (glu_mass == 1500) { xsec = 0.0141903; xsec_unc = 0.227296; return; }
    else if (glu_mass == 1505) { xsec = 0.01377; xsec_unc = 0.229402; return; }
    else if (glu_mass == 1510) { xsec = 0.0133923; xsec_unc = 0.226528; return; }
    else if (glu_mass == 1515) { xsec = 0.0130286; xsec_unc = 0.232697; return; }
    else if (glu_mass == 1520) { xsec = 0.012649; xsec_unc = 0.230194; return; }
    else if (glu_mass == 1525) { xsec = 0.0123374; xsec_unc = 0.231801; return; }
    else if (glu_mass == 1530) { xsec = 0.0119628; xsec_unc = 0.229449; return; }
    else if (glu_mass == 1535) { xsec = 0.0116378; xsec_unc = 0.231293; return; }
    else if (glu_mass == 1540) { xsec = 0.0113183; xsec_unc = 0.233535; return; }
    else if (glu_mass == 1545) { xsec = 0.0110039; xsec_unc = 0.23456; return; }
    else if (glu_mass == 1550) { xsec = 0.0107027; xsec_unc = 0.234971; return; }
    else if (glu_mass == 1555) { xsec = 0.0103967; xsec_unc = 0.23505; return; }
    else if (glu_mass == 1560) { xsec = 0.0101149; xsec_unc = 0.236723; return; }
    else if (glu_mass == 1565) { xsec = 0.00984079; xsec_unc = 0.237486; return; }
    else if (glu_mass == 1570) { xsec = 0.00956216; xsec_unc = 0.238011; return; }
    else if (glu_mass == 1575) { xsec = 0.00930893; xsec_unc = 0.238712; return; }
    else if (glu_mass == 1580) { xsec = 0.00905112; xsec_unc = 0.239145; return; }
    else if (glu_mass == 1585) { xsec = 0.00880102; xsec_unc = 0.24088; return; }
    else if (glu_mass == 1590) { xsec = 0.00856388; xsec_unc = 0.241033; return; }
    else if (glu_mass == 1595) { xsec = 0.00832287; xsec_unc = 0.242052; return; }
    else if (glu_mass == 1600) { xsec = 0.00810078; xsec_unc = 0.242679; return; }
    else if (glu_mass == 1605) { xsec = 0.0078785; xsec_unc = 0.243322; return; }
    else if (glu_mass == 1610) { xsec = 0.00767087; xsec_unc = 0.244839; return; }
    else if (glu_mass == 1615) { xsec = 0.00745579; xsec_unc = 0.245137; return; }
    else if (glu_mass == 1620) { xsec = 0.00725443; xsec_unc = 0.24569; return; }
    else if (glu_mass == 1625) { xsec = 0.00705942; xsec_unc = 0.246853; return; }
    else if (glu_mass == 1630) { xsec = 0.00687457; xsec_unc = 0.24804; return; }
    else if (glu_mass == 1635) { xsec = 0.00668418; xsec_unc = 0.248672; return; }
    else if (glu_mass == 1640) { xsec = 0.00651001; xsec_unc = 0.249776; return; }
    else if (glu_mass == 1645) { xsec = 0.00633268; xsec_unc = 0.250679; return; }
    else if (glu_mass == 1650) { xsec = 0.00616072; xsec_unc = 0.25138; return; }
    else if (glu_mass == 1655) { xsec = 0.00599673; xsec_unc = 0.252591; return; }
    else if (glu_mass == 1660) { xsec = 0.00583243; xsec_unc = 0.253829; return; }
    else if (glu_mass == 1665) { xsec = 0.00567868; xsec_unc = 0.255006; return; }
    else if (glu_mass == 1670) { xsec = 0.00553066; xsec_unc = 0.255203; return; }
    else if (glu_mass == 1675) { xsec = 0.00538094; xsec_unc = 0.255439; return; }
    else if (glu_mass == 1680) { xsec = 0.00523764; xsec_unc = 0.256602; return; }
    else if (glu_mass == 1685) { xsec = 0.00509647; xsec_unc = 0.258745; return; }
    else if (glu_mass == 1690) { xsec = 0.0049577; xsec_unc = 0.258847; return; }
    else if (glu_mass == 1695) { xsec = 0.00483094; xsec_unc = 0.260944; return; }
    else if (glu_mass == 1700) { xsec = 0.00470323; xsec_unc = 0.261021; return; }
    else if (glu_mass == 1705) { xsec = 0.0045807; xsec_unc = 0.262095; return; }
    else if (glu_mass == 1710) { xsec = 0.00445824; xsec_unc = 0.263238; return; }
    else if (glu_mass == 1715) { xsec = 0.0043369; xsec_unc = 0.263092; return; }
    else if (glu_mass == 1720) { xsec = 0.00422488; xsec_unc = 0.264093; return; }
    else if (glu_mass == 1725) { xsec = 0.00411276; xsec_unc = 0.26513; return; }
    else if (glu_mass == 1730) { xsec = 0.00400698; xsec_unc = 0.267386; return; }
    else if (glu_mass == 1735) { xsec = 0.00389655; xsec_unc = 0.267109; return; }
    else if (glu_mass == 1740) { xsec = 0.00379497; xsec_unc = 0.268072; return; }
    else if (glu_mass == 1745) { xsec = 0.00370003; xsec_unc = 0.2704; return; }
    else if (glu_mass == 1750) { xsec = 0.00359842; xsec_unc = 0.271502; return; }
    else if (glu_mass == 1755) { xsec = 0.00350486; xsec_unc = 0.27229; return; }
    else if (glu_mass == 1760) { xsec = 0.00341375; xsec_unc = 0.273209; return; }
    else if (glu_mass == 1765) { xsec = 0.00332255; xsec_unc = 0.27416; return; }
    else if (glu_mass == 1770) { xsec = 0.00323809; xsec_unc = 0.276458; return; }
    else if (glu_mass == 1775) { xsec = 0.00314866; xsec_unc = 0.275834; return; }
    else if (glu_mass == 1780) { xsec = 0.00306841; xsec_unc = 0.276481; return; }
    else if (glu_mass == 1785) { xsec = 0.00298808; xsec_unc = 0.277145; return; }
    else if (glu_mass == 1790) { xsec = 0.00291365; xsec_unc = 0.279548; return; }
    else if (glu_mass == 1795) { xsec = 0.0028312; xsec_unc = 0.280642; return; }
    else if (glu_mass == 1800) { xsec = 0.00276133; xsec_unc = 0.28108; return; }
    else if (glu_mass == 1805) { xsec = 0.00269156; xsec_unc = 0.281566; return; }
    else if (glu_mass == 1810) { xsec = 0.00262156; xsec_unc = 0.282017; return; }
    else if (glu_mass == 1815) { xsec = 0.00254938; xsec_unc = 0.282755; return; }
    else if (glu_mass == 1820) { xsec = 0.00248581; xsec_unc = 0.285102; return; }
    else if (glu_mass == 1825) { xsec = 0.00241549; xsec_unc = 0.285869; return; }
    else if (glu_mass == 1830) { xsec = 0.00235625; xsec_unc = 0.286103; return; }
    else if (glu_mass == 1835) { xsec = 0.00229576; xsec_unc = 0.28596; return; }
    else if (glu_mass == 1840) { xsec = 0.00223603; xsec_unc = 0.286654; return; }
    else if (glu_mass == 1845) { xsec = 0.00218302; xsec_unc = 0.288949; return; }
    else if (glu_mass == 1850) { xsec = 0.00212345; xsec_unc = 0.289167; return; }
    else if (glu_mass == 1855) { xsec = 0.00207; xsec_unc = 0.291835; return; }
    else if (glu_mass == 1860) { xsec = 0.00200972; xsec_unc = 0.291901; return; }
    else if (glu_mass == 1865) { xsec = 0.00196025; xsec_unc = 0.292103; return; }
    else if (glu_mass == 1870) { xsec = 0.00191132; xsec_unc = 0.291893; return; }
    else if (glu_mass == 1875) { xsec = 0.00185789; xsec_unc = 0.294928; return; }
    else if (glu_mass == 1880) { xsec = 0.00181527; xsec_unc = 0.29723; return; }
    else if (glu_mass == 1885) { xsec = 0.00176658; xsec_unc = 0.297236; return; }
    else if (glu_mass == 1890) { xsec = 0.00172274; xsec_unc = 0.299813; return; }
    else if (glu_mass == 1895) { xsec = 0.00167806; xsec_unc = 0.296455; return; }
    else if (glu_mass == 1900) { xsec = 0.00163547; xsec_unc = 0.299045; return; }
    else if (glu_mass == 1905) { xsec = 0.0015925; xsec_unc = 0.302039; return; }
    else if (glu_mass == 1910) { xsec = 0.00155445; xsec_unc = 0.301015; return; }
    else if (glu_mass == 1915) { xsec = 0.00151503; xsec_unc = 0.300356; return; }
    else if (glu_mass == 1920) { xsec = 0.00147199; xsec_unc = 0.303575; return; }
    else if (glu_mass == 1925) { xsec = 0.0014401; xsec_unc = 0.305951; return; }
    else if (glu_mass == 1930) { xsec = 0.0014016; xsec_unc = 0.305171; return; }
    else if (glu_mass == 1935) { xsec = 0.00136297; xsec_unc = 0.304873; return; }
    else if (glu_mass == 1940) { xsec = 0.001331; xsec_unc = 0.307414; return; }
    else if (glu_mass == 1945) { xsec = 0.001299; xsec_unc = 0.310066; return; }
    else if (glu_mass == 1950) { xsec = 0.0012642; xsec_unc = 0.304581; return; }
    else if (glu_mass == 1955) { xsec = 0.00123087; xsec_unc = 0.308644; return; }
    else if (glu_mass == 1960) { xsec = 0.00120048; xsec_unc = 0.309669; return; }
    else if (glu_mass == 1965) { xsec = 0.00117053; xsec_unc = 0.310216; return; }
    else if (glu_mass == 1970) { xsec = 0.00114051; xsec_unc = 0.310814; return; }
    else if (glu_mass == 1975) { xsec = 0.00111722; xsec_unc = 0.315357; return; }
    else if (glu_mass == 1980) { xsec = 0.00108758; xsec_unc = 0.315568; return; }
    else if (glu_mass == 1985) { xsec = 0.00105813; xsec_unc = 0.315103; return; }
    else if (glu_mass == 1990) { xsec = 0.00102936; xsec_unc = 0.314167; return; }
    else if (glu_mass == 1995) { xsec = 0.00100614; xsec_unc = 0.317628; return; }
    else if (glu_mass == 2000) { xsec = 0.000981077; xsec_unc = 0.318422; return; }
    else {xsec = 0.; xsec_unc = 0.;} 
  }
