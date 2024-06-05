#include <iostream>
#include <vector>

#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"
#include "TColor.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLatex.h"

#include "small_tree_rpv.hpp"
#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

void compare_shape_wjets_dy(TString year)
{
  TH1::SetDefaultSumw2();

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  styles style("CMSPaper");
  style.LabelSize    *= 1.1;
  style.LegendSize   *= 1.0;
  style.TitleSize    *= 1.1;
  style.yTitleOffset /= 1.3;
  style.xTitleOffset /= 1.08;

  double lumi;
  TString lumi_title;
  if(year=="UL2016" || year=="2016") {
    lumi = 36.3;
    lumi_title = "36p3";
    year = "2016";
  }
  else if(year=="UL2017" || year=="2017") {
    lumi = 41.5;
    lumi_title = "41p5";
    year = "2017";
  }
  else if(year=="UL2018" || year=="2018") {
    lumi = 59.8;
    lumi_title = "59p8";
    year = "2018";
  }
  else if(year=="UL20178" || year=="20178") {
    lumi = 101.3;
    lumi_title = "101p3";
    year = "20178";
  }
  else {
    cout << "Please input the year as 2016/2017/2018/20178 or UL2016/UL2017/UL2018/UL20178" << endl;
  }

  TString folder_wjets = folder_year(year, false).at(0);
  TString folder_dy    = folder_year(year, false).at(3);

  vector<TString> s_wjets = getRPVProcess(folder_wjets, "wjets");
  vector<TString> s_dy    = getRPVProcess(folder_dy,    "DY");

  // make small tree
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_dy((static_cast<std::string>(s_dy.at(0))));

  // define histogram
  TH1D* h_wjets_njets45 = new TH1D("h_wjets_njets45", "h_wjets_njets45", 3, 500, 1400);
  TH1D* h_wjets_njets67 = new TH1D("h_wjets_njets67", "h_wjets_njets67", 3, 500, 1400);
  TH1D* h_wjets_njets8 	= new TH1D("h_wjets_njets8",  "h_wjets_njets8",  3, 500, 1400);
  TH1D* h_dy_njets34 	= new TH1D("h_dy_njets34",    "h_dy_njets34",    3, 500, 1400);
  TH1D* h_dy_njets56 	= new TH1D("h_dy_njets56",    "h_dy_njets56",    3, 500, 1400);
  TH1D* h_dy_njets7 	= new TH1D("h_dy_njets7",     "h_dy_njets7",     3, 500, 1400);

  // event loop for DY
  for(unsigned int ievt=0; ievt<tree_dy.GetEntries(); ievt++) {

    tree_dy.GetEntry(ievt);
    float mll=0;
    float mass=0;
    TLorentzVector mom1, mom2;

    // baseline cut
    if(tree_dy.nleps()!=2) continue;
    if(tree_dy.nbm()>2) continue;
    if(tree_dy.njets()<3) continue;
    if(tree_dy.ht()<1200) continue;
    if(tree_dy.mj12()<500) continue;
    if(tree_dy.pass()!=1) continue;
    if(tree_dy.mj12()>=1400) tree_dy.mj12()=1399.99; // to consider overflow

    // cut for OSSF and mll
    if(tree_dy.leps_pdgid().at(0)*tree_dy.leps_pdgid().at(1)==-121) mass = 0.510*0.001;
    else if(tree_dy.leps_pdgid().at(0)*tree_dy.leps_pdgid().at(1)==-169) mass = 105.66*0.001;
    else continue;

    mom1.SetPtEtaPhiM(tree_dy.leps_pt().at(0), tree_dy.leps_eta().at(0), tree_dy.leps_phi().at(0), mass);
    mom2.SetPtEtaPhiM(tree_dy.leps_pt().at(1), tree_dy.leps_eta().at(1), tree_dy.leps_phi().at(1), mass);
    TLorentzVector momtot = mom1+mom2;
    mll = momtot.M();
    if(mll<81 || mll>101) continue;

    // Fill histogram
    if(year=="20178") {
      if(tree_dy.njets()>=3 && tree_dy.njets()<=4) h_dy_njets34->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
      if(tree_dy.njets()>=5 && tree_dy.njets()<=6) h_dy_njets56->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
      if(tree_dy.njets()>=7) h_dy_njets7->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
    }
    else {
      if(tree_dy.njets()>=3 && tree_dy.njets()<=4) h_dy_njets34->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
      if(tree_dy.njets()>=5 && tree_dy.njets()<=6) h_dy_njets56->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
      if(tree_dy.njets()>=7) h_dy_njets7->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
    }
  }

  // event loop for wjets
  for(unsigned int ievt=0; ievt<tree_wjets.GetEntries(); ievt++) {

    tree_wjets.GetEntry(ievt);

    // baseline cut
    if(tree_wjets.nleps()!=1) continue;
    if(tree_wjets.nbm()>2) continue;
    if(tree_wjets.njets()<4) continue;
    if(tree_wjets.ht()<1200) continue;
    if(tree_wjets.mj12()<500) continue;
    if(tree_wjets.pass()!=1) continue;
    if(tree_wjets.mj12()>=1400) tree_wjets.mj12()=1399.99; // to consider overflow

    // Fill histogram
    if(year=="20178") {
      if(tree_wjets.njets()>=4 && tree_wjets.njets()<=5) h_wjets_njets45->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
      if(tree_wjets.njets()>=6 && tree_wjets.njets()<=7) h_wjets_njets67->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
      if(tree_wjets.njets()>=8) h_wjets_njets8->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
    }
    else {
      if(tree_wjets.njets()>=4 && tree_wjets.njets()<=5) h_wjets_njets45->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
      if(tree_wjets.njets()>=6 && tree_wjets.njets()<=7) h_wjets_njets67->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
      if(tree_wjets.njets()>=8) h_wjets_njets8->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
    }
  }

  /*
  cout << "njets34: " << h_dy_njets34->GetBinContent(1) << " " << h_dy_njets34->GetBinContent(2) << " " << h_dy_njets34->GetBinContent(3) << endl;
  cout << "njets34: " << h_dy_njets34->GetBinError(1) << " " << h_dy_njets34->GetBinError(2) << " " << h_dy_njets34->GetBinError(3) << endl;
  cout << "njets56: " << h_dy_njets56->GetBinContent(1) << " " << h_dy_njets56->GetBinContent(2) << " " << h_dy_njets56->GetBinContent(3) << endl;
  cout << "njets56: " << h_dy_njets56->GetBinError(1) << " " << h_dy_njets56->GetBinError(2) << " " << h_dy_njets56->GetBinError(3) << endl;
  cout << "njets7: " << h_dy_njets7->GetBinContent(1) << " " << h_dy_njets7->GetBinContent(2) << " " << h_dy_njets7->GetBinContent(3) << endl;
  cout << "njets7: " << h_dy_njets7->GetBinError(1) << " " << h_dy_njets7->GetBinError(2) << " " << h_dy_njets7->GetBinError(3) << endl;
  cout << "njets45: " << h_wjets_njets45->GetBinContent(1) << " " << h_wjets_njets45->GetBinContent(2) << " " << h_wjets_njets45->GetBinContent(3) << endl;
  cout << "njets45: " << h_wjets_njets45->GetBinError(1) << " " << h_wjets_njets45->GetBinError(2) << " " << h_wjets_njets45->GetBinError(3) << endl;
  cout << "njets67: " << h_wjets_njets67->GetBinContent(1) << " " << h_wjets_njets67->GetBinContent(2) << " " << h_wjets_njets67->GetBinContent(3) << endl;
  cout << "njets67: " << h_wjets_njets67->GetBinError(1) << " " << h_wjets_njets67->GetBinError(2) << " " << h_wjets_njets67->GetBinError(3) << endl;
  cout << "njets8: " << h_wjets_njets8->GetBinContent(1) << " " << h_wjets_njets8->GetBinContent(2) << " " << h_wjets_njets8->GetBinContent(3) << endl;
  cout << "njets8: " << h_wjets_njets8->GetBinError(1) << " " << h_wjets_njets8->GetBinError(2) << " " << h_wjets_njets8->GetBinError(3) << endl;
  */

  cout << endl;
  cout << "unc_dy" << endl;
  cout << "[low njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets45->GetBinContent(2)/h_wjets_njets45->GetBinContent(1))/(h_dy_njets34->GetBinContent(2)/h_dy_njets34->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets45->GetBinContent(3)/h_wjets_njets45->GetBinContent(1))/(h_dy_njets34->GetBinContent(3)/h_dy_njets34->GetBinContent(1)) << endl;
  cout << "[mid njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets67->GetBinContent(2)/h_wjets_njets67->GetBinContent(1))/(h_dy_njets56->GetBinContent(2)/h_dy_njets56->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets67->GetBinContent(3)/h_wjets_njets67->GetBinContent(1))/(h_dy_njets56->GetBinContent(3)/h_dy_njets56->GetBinContent(1)) << endl;
  cout << "[high njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets8->GetBinContent(2)/h_wjets_njets8->GetBinContent(1))/(h_dy_njets7->GetBinContent(2)/h_dy_njets7->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets8->GetBinContent(3)/h_wjets_njets8->GetBinContent(1))/(h_dy_njets7->GetBinContent(3)/h_dy_njets7->GetBinContent(1)) << endl;


  // Draw plots

    // make clone
  TH1D* h_dy_njets34_clone = (TH1D*)h_dy_njets34->Clone("h_dy_njets34_clone");
  TH1D* h_dy_njets56_clone = (TH1D*)h_dy_njets56->Clone("h_dy_njets56_clone");
  TH1D* h_dy_njets7_clone  = (TH1D*)h_dy_njets7->Clone("h_dy_njets7_clone");
  TH1D* h_wjets_njets45_clone = (TH1D*)h_wjets_njets45->Clone("h_wjets_njets45_clone");
  TH1D* h_wjets_njets67_clone = (TH1D*)h_wjets_njets67->Clone("h_wjets_njets67_clone");
  TH1D* h_wjets_njets8_clone  = (TH1D*)h_wjets_njets8->Clone("h_wjets_njets8_clone");

    // cosmetics
      // tpad
        // njets 4-5
  h_wjets_njets45->SetTitle("");
  h_wjets_njets45->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets45->GetYaxis()->SetLabelSize(0.06); h_wjets_njets45->GetYaxis()->SetTitle("Events"); h_wjets_njets45->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets45->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets45->SetMinimum(0.31); h_wjets_njets45->SetMaximum(h_wjets_njets45->GetBinContent(1)*100); h_wjets_njets45->SetLineColor(kGreen+2); h_dy_njets34->SetLineColor(kViolet-9);
  h_wjets_njets45->SetLineWidth(3); h_dy_njets34->SetLineWidth(3);
        // njets 6-7
  h_wjets_njets67->SetTitle("");
  h_wjets_njets67->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets67->GetYaxis()->SetLabelSize(0.06); h_wjets_njets67->GetYaxis()->SetTitle("Events"); h_wjets_njets67->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets67->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets67->SetMinimum(0.31); h_wjets_njets67->SetMaximum(h_wjets_njets67->GetBinContent(1)*100); h_wjets_njets67->SetLineColor(kGreen+2); h_dy_njets56->SetLineColor(kViolet-9);
  h_wjets_njets67->SetLineWidth(3); h_dy_njets56->SetLineWidth(3);
        // njets 8-
  h_wjets_njets8->SetTitle("");
  h_wjets_njets8->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets8->GetYaxis()->SetLabelSize(0.06); h_wjets_njets8->GetYaxis()->SetTitle("Events"); h_wjets_njets8->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets8->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets8->SetMinimum(0.31); h_wjets_njets8->SetMaximum(h_wjets_njets8->GetBinContent(1)*100); h_wjets_njets8->SetLineColor(kGreen+2); h_dy_njets7->SetLineColor(kViolet-9);
  h_wjets_njets8->SetLineWidth(3); h_dy_njets7->SetLineWidth(3);
      // bpad
        // njets 4-5
  h_wjets_njets45_clone->SetTitle("");
  h_wjets_njets45_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets45_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets45_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets45_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets45_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets45_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets45_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets45_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets45_clone->GetYaxis()->SetTitle("W+jets / DY"); h_wjets_njets45_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets45_clone->GetYaxis()->SetTitleOffset(0.4);
        // njets 6-7
  h_wjets_njets67_clone->SetTitle("");
  h_wjets_njets67_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets67_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets67_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets67_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets67_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets67_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets67_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets67_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets67_clone->GetYaxis()->SetTitle("W+jets / DY"); h_wjets_njets67_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets67_clone->GetYaxis()->SetTitleOffset(0.4);
        // njets 8
  h_wjets_njets8_clone->SetTitle("");
  h_wjets_njets8_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets8_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets8_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets8_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets8_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets8_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets8_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets8_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets8_clone->GetYaxis()->SetTitle("W+jets / DY"); h_wjets_njets8_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets8_clone->GetYaxis()->SetTitleOffset(0.4);

    // Make TLatex
  double err_wjets_njets45=0, err_wjets_njets67=0, err_wjets_njets8=0;
  double err_dy_njets34=0,    err_dy_njets56=0,    err_dy_njets7=0;

  float num_wjets_njets45 = h_wjets_njets45_clone->IntegralAndError(1, h_wjets_njets45->GetNbinsX(), err_wjets_njets45);
  float num_wjets_njets67 = h_wjets_njets67_clone->IntegralAndError(1, h_wjets_njets67->GetNbinsX(), err_wjets_njets67);
  float num_wjets_njets8  = h_wjets_njets8_clone->IntegralAndError(1, h_wjets_njets8->GetNbinsX(), err_wjets_njets8);
  float num_dy_njets34    = h_dy_njets34_clone->IntegralAndError(1, h_dy_njets34->GetNbinsX(), err_dy_njets34);
  float num_dy_njets56    = h_dy_njets56_clone->IntegralAndError(1, h_dy_njets56->GetNbinsX(), err_dy_njets56);
  float num_dy_njets7     = h_dy_njets7_clone->IntegralAndError(1, h_dy_njets7->GetNbinsX(), err_dy_njets7);

  double err_tot_34       = (num_wjets_njets45/num_dy_njets34)*TMath::Sqrt(TMath::Power(err_dy_njets34/num_dy_njets34, 2) + TMath::Power(err_wjets_njets45/num_wjets_njets45, 2));
  double err_tot_56       = (num_wjets_njets67/num_dy_njets56)*TMath::Sqrt(TMath::Power(err_dy_njets56/num_dy_njets56, 2) + TMath::Power(err_wjets_njets67/num_wjets_njets67, 2));
  double err_tot_7        = (num_wjets_njets8/num_dy_njets7)*TMath::Sqrt(TMath::Power(err_dy_njets7/num_dy_njets7, 2) + TMath::Power(err_wjets_njets8/num_wjets_njets8, 2));

  TLatex* tex_njets34 = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets45/num_dy_njets34)*100, err_tot_34*100));
  tex_njets34->SetNDC();
  tex_njets34->SetTextSize(0.045);
  TLatex* tex_njets56 = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets67/num_dy_njets56)*100, err_tot_56*100));
  tex_njets56->SetNDC();
  tex_njets56->SetTextSize(0.045);
  TLatex* tex_njets7  = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets8/num_dy_njets7)*100, err_tot_7*100));
  tex_njets7->SetNDC();
  tex_njets7->SetTextSize(0.045);

  // Make TLegend
    // njets 4-5
  TLegend* l_njets34 = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets34->SetBorderSize(0);
  l_njets34->AddEntry(h_wjets_njets45, Form("%s W+jets [N=%.0f]", year.Data(), h_wjets_njets45_clone->Integral()));
  l_njets34->AddEntry(h_dy_njets34, Form("%s DY [N=%.0f]", year.Data(), h_wjets_njets45_clone->Integral()));
  l_njets34->SetTextSize(0.05);
    // njets 6-7
  TLegend* l_njets56  = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets56->SetBorderSize(0);
  l_njets56->AddEntry(h_wjets_njets67, Form("%s W+jets [N=%.0f]", year.Data(), h_wjets_njets67_clone->Integral()));
  l_njets56->AddEntry(h_dy_njets56, Form("%s DY [N=%.0f]", year.Data(), h_wjets_njets67_clone->Integral()));
  l_njets56->SetTextSize(0.05);
    // njets 8-
  TLegend* l_njets7 = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets7->SetBorderSize(0);
  l_njets7->AddEntry(h_wjets_njets8, Form("%s W+jets [N=%.0f]", year.Data(), h_wjets_njets8_clone->Integral()));
  l_njets7->AddEntry(h_dy_njets7, Form("%s DY [N=%.0f]", year.Data(), h_wjets_njets8_clone->Integral()));
  l_njets7->SetTextSize(0.05);

  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);
    // njets 4-5
  TPad *tpad_njets45(NULL), *bpad_njets45(NULL);
      // tpad
  TCanvas* c_njets34 = new TCanvas("c_njets34", "c_njets34", 800, 800);
  c_njets34->cd();
  tpad_njets45 = new TPad("tpad_njets45","tpad_njets45",0.,0.3,1.,1.);
  tpad_njets45->SetLeftMargin(0.12); tpad_njets45->SetBottomMargin(0.02); tpad_njets45->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets45->Draw();
  tpad_njets45->cd();
  gPad->SetLogy();
  h_wjets_njets45->Draw("hist");
  h_dy_njets34->Scale(1.*h_wjets_njets45_clone->Integral()/h_dy_njets34_clone->Integral());
  h_dy_njets34->Draw("same PL");
  l_njets34->Draw();
  tex_njets34->Draw();
      // bpad
  c_njets34->cd();
  bpad_njets45 = new TPad("bpad_njets45","bpad_njets45",0.,0.,1.,0.305);
  bpad_njets45->SetLeftMargin(0.12);
  bpad_njets45->SetTopMargin(0.); bpad_njets45->SetBottomMargin(0.4); bpad_njets45->SetFillStyle(4000);
  bpad_njets45->Draw(); bpad_njets45->cd();
  h_wjets_njets45_clone->Scale(1.*h_dy_njets34_clone->Integral()/h_wjets_njets45_clone->Integral());
  h_wjets_njets45_clone->Divide(h_dy_njets34_clone);
  //h_wjets_njets45_clone->SetMarkerStyle(20);
  h_wjets_njets45_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets45_clone->SetLineColor(kBlack);
  h_wjets_njets45_clone->SetLineWidth(2);
  h_wjets_njets45_clone->Draw("B e");
  line->SetLineColor(1); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets34->Print(Form("plots/comp_dy_wjets/log_shapes_dy_wjets_njets45_lumi%s.pdf", lumi_title.Data()));

    // njets 6-7
  TPad *tpad_njets67(NULL), *bpad_njets67(NULL);
      // tpad
  TCanvas* c_njets56 = new TCanvas("c_njets56", "c_njets56", 800, 800);
  c_njets56->cd();
  tpad_njets67 = new TPad("tpad_njets67","tpad_njets67",0.,0.3,1.,1.);
  tpad_njets67->SetLeftMargin(0.12); tpad_njets67->SetBottomMargin(0.02); tpad_njets67->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets67->Draw();
  tpad_njets67->cd();
  gPad->SetLogy();
  h_wjets_njets67->Draw("hist");
  h_dy_njets56->Scale(1.*h_wjets_njets67_clone->Integral()/h_dy_njets56_clone->Integral());
  h_dy_njets56->Draw("same PL");
  l_njets56->Draw();
  tex_njets56->Draw();
      // bpad
  c_njets56->cd();
  bpad_njets67 = new TPad("bpad_njets67","bpad_njets67",0.,0.,1.,0.305);
  bpad_njets67->SetLeftMargin(0.12);
  bpad_njets67->SetTopMargin(0.); bpad_njets67->SetBottomMargin(0.4); bpad_njets67->SetFillStyle(4000);
  bpad_njets67->Draw(); bpad_njets67->cd();
  h_wjets_njets67_clone->Scale(1.*h_dy_njets56_clone->Integral()/h_wjets_njets67_clone->Integral());
  h_wjets_njets67_clone->Divide(h_dy_njets56_clone);
  //h_wjets_njets67_clone->SetMarkerStyle(20);
  h_wjets_njets67_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets67_clone->SetLineColor(kBlack);
  h_wjets_njets67_clone->SetLineWidth(2);
  h_wjets_njets67_clone->Draw("B e");
  line->SetLineColor(1); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets56->Print(Form("plots/comp_dy_wjets/log_shapes_dy_wjets_njets67_lumi%s.pdf", lumi_title.Data()));

    // njets 8-
  TPad *tpad_njets8(NULL), *bpad_njets8(NULL);
      // tpad
  TCanvas* c_njets7 = new TCanvas("c_njets7", "c_njets7", 800, 800);
  c_njets7->cd();
  tpad_njets8 = new TPad("tpad_njets8","tpad_njets8",0.,0.3,1.,1.);
  tpad_njets8->SetLeftMargin(0.12); tpad_njets8->SetBottomMargin(0.02); tpad_njets8->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets8->Draw();
  tpad_njets8->cd();
  gPad->SetLogy();
  h_wjets_njets8->Draw("hist");
  h_dy_njets7->Scale(1.*h_wjets_njets8_clone->Integral()/h_dy_njets7_clone->Integral());
  h_dy_njets7->Draw("same PL");
  l_njets7->Draw();
  tex_njets7->Draw();
      // bpad
  c_njets7->cd();
  bpad_njets8 = new TPad("bpad_njets8","bpad_njets8",0.,0.,1.,0.305);
  bpad_njets8->SetLeftMargin(0.12);
  bpad_njets8->SetTopMargin(0.); bpad_njets8->SetBottomMargin(0.4); bpad_njets8->SetFillStyle(4000);
  bpad_njets8->Draw(); bpad_njets8->cd();
  h_wjets_njets8_clone->Scale(1.*h_dy_njets7_clone->Integral()/h_wjets_njets8_clone->Integral());
  h_wjets_njets8_clone->Divide(h_dy_njets7_clone);
  //h_wjets_njets8_clone->SetMarkerStyle(20);
  h_wjets_njets8_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets8_clone->SetLineColor(kBlack);
  h_wjets_njets8_clone->SetLineWidth(2);
  h_wjets_njets8_clone->Draw("B e");
  line->SetLineColor(1); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets7->Print(Form("plots/comp_dy_wjets/log_shapes_dy_wjets_njets8_lumi%s.pdf", lumi_title.Data()));




}


int main(int argc, char **argv)
{
  TString year;
  year = argv[1];

  compare_shape_wjets_dy(year);



  return 0;
}
