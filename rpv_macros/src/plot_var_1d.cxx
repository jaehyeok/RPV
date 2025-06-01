#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooFit.h"
#include "RooSimultaneous.h"
#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooPlot.h"

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
#include "THStack.h"
#include "TGaxis.h"
#include "TFile.h"

#include "small_tree_rpv.hpp"
#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;


void appendTree(vector<TString> s_process, small_tree &tree_in);
void pass_selection(small_tree_rpv &tree, TH1D* h, TString var, TString year);
std::tuple<std::vector<TH1D*>, std::vector<TH1D*>, std::vector<TH1D*>> make_hist_var(TString var);


void appendTree(vector<TString> s_process, small_tree &tree_in)
{
  cout << "flist of s_process: " << s_process.at(0) << endl;
  if(s_process.size()>1) {
    for(int i=1; i<s_process.size(); i++) {
      tree_in.Add((static_cast<std::string>(s_process.at(i))));
      cout << "       " << s_process.at(i) << " is appended" << endl;
    }
  }
  cout << endl;
}

void pass_selection(small_tree_rpv &tree, TH1D* h, TString var, TString year)
{
  gErrorIgnoreLevel = kError+1;

  double lumi;
  TString lumi_title;
  if(year=="UL2016_preVFP") 	  lumi=19.5;
  else if(year=="UL2016_postVFP") lumi=16.8;
  else if(year=="UL2017")         lumi=41.5;
  else if(year=="UL2018")  	  lumi=59.8;
  else if(year=="UL2016_comb") 	  lumi=36.3;
  else if(year=="UL20178_comb")	  lumi=101.3;
  else {cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018/UL2016_comb/UL20178_comb" << endl;}

  for(unsigned int ievt=0; ievt<tree.GetEntries(); ievt++) {
    tree.GetEntry(ievt);

    // baseline selection
    
    if(tree.stitch_ht()==0) continue;
    if(tree.nleps()!=0)     continue;
    if(tree.njets()<4)      continue;
    if(tree.ht()<1200)      continue;
    if(tree.mj12()<500)     continue;
    if(tree.pass()!=1)      continue;
    if(tree.mj12()>=2000) tree.mj12()=1999.99; // to consider overflow
    if(tree.njets()>15)   tree.njets()=15; // to consider overflow
    if(tree.nbm()>5)      tree.nbm()=5; // to consider overflow

    if(var=="njet")    h->Fill(tree.njets(), lumi*tree.weight());
    else if(var=="nb") h->Fill(tree.nbm(),    lumi*tree.weight());
    else if(var=="mj") h->Fill(tree.mj12(),    lumi*tree.weight());

  } // end event loop
}


std::tuple<std::vector<TH1D*>, std::vector<TH1D*>, std::vector<TH1D*>> make_hist_var(TString var)
{
  gErrorIgnoreLevel = kError+1;
  TH1::SetDefaultSumw2();


  double lumi;
  TString lumi_title = "138";

      // ttbar
  TString folder_bkg_UL2016_preVFP    = folder_year("UL2016_preVFP",  false).at(0);
  TString folder_bkg_UL2016_postVFP   = folder_year("UL2016_postVFP", false).at(0);
  TString folder_bkg_UL2017           = folder_year("UL2017", 	      false).at(0);
  TString folder_bkg_UL2018           = folder_year("UL2018", 	      false).at(0);
      // sig
  TString folder_sig_UL2016_preVFP    = folder_year("UL2016_preVFP",  false).at(2);
  TString folder_sig_UL2016_postVFP   = folder_year("UL2016_postVFP", false).at(2);
  TString folder_sig_UL2017           = folder_year("UL2017", 	      false).at(2);
  TString folder_sig_UL2018           = folder_year("UL2018", 	      false).at(2);

      // ttbar
  vector<TString> s_ttbar_UL2016_preVFP  = getRPVProcess(folder_bkg_UL2016_preVFP , "ttbar");
  vector<TString> s_ttbar_UL2016_postVFP = getRPVProcess(folder_bkg_UL2016_postVFP, "ttbar");
  vector<TString> s_ttbar_UL2017         = getRPVProcess(folder_bkg_UL2017        , "ttbar");
  vector<TString> s_ttbar_UL2018         = getRPVProcess(folder_bkg_UL2018        , "ttbar");
      // sig 1800
  vector<TString> s_sig1800_UL2016_preVFP  = getRPVProcess(folder_sig_UL2016_preVFP , "rpv_m1800");
  vector<TString> s_sig1800_UL2016_postVFP = getRPVProcess(folder_sig_UL2016_postVFP, "rpv_m1800");
  vector<TString> s_sig1800_UL2017         = getRPVProcess(folder_sig_UL2017        , "rpv_m1800");
  vector<TString> s_sig1800_UL2018         = getRPVProcess(folder_sig_UL2018        , "rpv_m1800");
      // sig 1000
  vector<TString> s_sig1000_UL2016_preVFP  = getRPVProcess(folder_sig_UL2016_preVFP , "rpv_m1000");
  vector<TString> s_sig1000_UL2016_postVFP = getRPVProcess(folder_sig_UL2016_postVFP, "rpv_m1000");
  vector<TString> s_sig1000_UL2017         = getRPVProcess(folder_sig_UL2017        , "rpv_m1000");
  vector<TString> s_sig1000_UL2018         = getRPVProcess(folder_sig_UL2018        , "rpv_m1000");

  // make small tree
      // ttbar
  small_tree_rpv tree_ttbar_UL2016_preVFP((static_cast<std::string>(s_ttbar_UL2016_preVFP.at(0))));
  small_tree_rpv tree_ttbar_UL2016_postVFP((static_cast<std::string>(s_ttbar_UL2016_postVFP.at(0))));
  small_tree_rpv tree_ttbar_UL2017((static_cast<std::string>(s_ttbar_UL2017.at(0))));
  small_tree_rpv tree_ttbar_UL2018((static_cast<std::string>(s_ttbar_UL2018.at(0))));
      // sig 1800
  small_tree_rpv tree_signal_1800_UL2016_preVFP((static_cast<std::string>(s_sig1800_UL2016_preVFP.at(0))));
  small_tree_rpv tree_signal_1800_UL2016_postVFP((static_cast<std::string>(s_sig1800_UL2016_postVFP.at(0))));
  small_tree_rpv tree_signal_1800_UL2017((static_cast<std::string>(s_sig1800_UL2017.at(0))));
  small_tree_rpv tree_signal_1800_UL2018((static_cast<std::string>(s_sig1800_UL2018.at(0))));
      // sig 1000
  small_tree_rpv tree_signal_1000_UL2016_preVFP((static_cast<std::string>(s_sig1000_UL2016_preVFP.at(0))));
  small_tree_rpv tree_signal_1000_UL2016_postVFP((static_cast<std::string>(s_sig1000_UL2016_postVFP.at(0))));
  small_tree_rpv tree_signal_1000_UL2017((static_cast<std::string>(s_sig1000_UL2017.at(0))));
  small_tree_rpv tree_signal_1000_UL2018((static_cast<std::string>(s_sig1000_UL2018.at(0))));

  // append small tree
      // ttbar
  appendTree(s_ttbar_UL2016_preVFP,  tree_ttbar_UL2016_preVFP);
  appendTree(s_ttbar_UL2016_postVFP, tree_ttbar_UL2016_postVFP);
  appendTree(s_ttbar_UL2017,         tree_ttbar_UL2017);
  appendTree(s_ttbar_UL2018,         tree_ttbar_UL2018);
      // sig 1800
  appendTree(s_sig1800_UL2016_preVFP,  tree_signal_1800_UL2016_preVFP);
  appendTree(s_sig1800_UL2016_postVFP, tree_signal_1800_UL2016_postVFP);
  appendTree(s_sig1800_UL2017,         tree_signal_1800_UL2017);
  appendTree(s_sig1800_UL2018,         tree_signal_1800_UL2018);
      // sig 1000
  appendTree(s_sig1000_UL2016_preVFP,  tree_signal_1000_UL2016_preVFP);
  appendTree(s_sig1000_UL2016_postVFP, tree_signal_1000_UL2016_postVFP);
  appendTree(s_sig1000_UL2017,         tree_signal_1000_UL2017);
  appendTree(s_sig1000_UL2018,         tree_signal_1000_UL2018);


  // define histogram
  int nbin, bin_i, bin_f;
  if(var=="njet")    {nbin=11; bin_i=4;   bin_f=15;}
  else if(var=="nb") {nbin=5;  bin_i=0;   bin_f=5;}
  else if(var=="mj") {nbin=10; bin_i=500; bin_f=2000;}
      // ttbar
  TH1D* h_ttbar_UL2016_preVFP  = new TH1D("h_ttbar_UL2016_preVFP",  "h_ttbar_UL2016_preVFP",   nbin, bin_i, bin_f);
  TH1D* h_ttbar_UL2016_postVFP = new TH1D("h_ttbar_UL2016_postVFP", "h_ttbar_UL2016_postVFP",  nbin, bin_i, bin_f);
  TH1D* h_ttbar_UL2017         = new TH1D("h_ttbar_UL2017",         "h_ttbar_UL2017",  	       nbin, bin_i, bin_f);
  TH1D* h_ttbar_UL2018         = new TH1D("h_ttbar_UL2018",         "h_ttbar_UL2018",          nbin, bin_i, bin_f);
      // sig 1800
  TH1D* h_sig1800_UL2016_preVFP  = new TH1D("h_sig1800_UL2016_preVFP",  "h_sig1800_UL2016_preVFP",   nbin, bin_i, bin_f);
  TH1D* h_sig1800_UL2016_postVFP = new TH1D("h_sig1800_UL2016_postVFP", "h_sig1800_UL2016_postVFP",  nbin, bin_i, bin_f);
  TH1D* h_sig1800_UL2017         = new TH1D("h_sig1800_UL2017",         "h_sig1800_UL2017",  	 nbin, bin_i, bin_f);
  TH1D* h_sig1800_UL2018         = new TH1D("h_sig1800_UL2018",         "h_sig1800_UL2018",  	 nbin, bin_i, bin_f);
      // sig 1000
  TH1D* h_sig1000_UL2016_preVFP  = new TH1D("h_sig1000_UL2016_preVFP",  "h_sig1000_UL2016_preVFP",   nbin, bin_i, bin_f);
  TH1D* h_sig1000_UL2016_postVFP = new TH1D("h_sig1000_UL2016_postVFP", "h_sig1000_UL2016_postVFP",  nbin, bin_i, bin_f);
  TH1D* h_sig1000_UL2017         = new TH1D("h_sig1000_UL2017",         "h_sig1000_UL2017",  	 nbin, bin_i, bin_f);
  TH1D* h_sig1000_UL2018         = new TH1D("h_sig1000_UL2018",         "h_sig1000_UL2018",  	 nbin, bin_i, bin_f);

  // selection w.r.t. variable
      // ttbar
  pass_selection(tree_ttbar_UL2016_preVFP,  h_ttbar_UL2016_preVFP,  var, "UL2016_preVFP");
  pass_selection(tree_ttbar_UL2016_postVFP, h_ttbar_UL2016_postVFP, var, "UL2016_postVFP");
  pass_selection(tree_ttbar_UL2017, 	    h_ttbar_UL2017, 	    var, "UL2017");
  pass_selection(tree_ttbar_UL2018, 	    h_ttbar_UL2018, 	    var, "UL2018");
      // sig 1800
  pass_selection(tree_signal_1800_UL2016_preVFP,    h_sig1800_UL2016_preVFP,    var, "UL2016_preVFP");
  pass_selection(tree_signal_1800_UL2016_postVFP,   h_sig1800_UL2016_postVFP,   var, "UL2016_postVFP");
  pass_selection(tree_signal_1800_UL2017, 	    h_sig1800_UL2017, 	    	 var, "UL2017");
  pass_selection(tree_signal_1800_UL2018, 	    h_sig1800_UL2018, 	    	 var, "UL2018");
      // sig 1000
  pass_selection(tree_signal_1000_UL2016_preVFP,    h_sig1000_UL2016_preVFP,    var, "UL2016_preVFP");
  pass_selection(tree_signal_1000_UL2016_postVFP,   h_sig1000_UL2016_postVFP,   var, "UL2016_postVFP");
  pass_selection(tree_signal_1000_UL2017, 	    h_sig1000_UL2017, 	    	 var, "UL2017");
  pass_selection(tree_signal_1000_UL2018, 	    h_sig1000_UL2018, 	    	 var, "UL2018");

      // ttbar
  std::vector<TH1D*> h_ttbar, h_sig1800, h_sig1000;
  h_ttbar.push_back(h_ttbar_UL2016_preVFP);
  h_ttbar.push_back(h_ttbar_UL2016_postVFP);
  h_ttbar.push_back(h_ttbar_UL2017);
  h_ttbar.push_back(h_ttbar_UL2018);
      // sig 1800
  h_sig1800.push_back(h_sig1800_UL2016_preVFP);
  h_sig1800.push_back(h_sig1800_UL2016_postVFP);
  h_sig1800.push_back(h_sig1800_UL2017);
  h_sig1800.push_back(h_sig1800_UL2018);
      // sig 1000
  h_sig1000.push_back(h_sig1000_UL2016_preVFP);
  h_sig1000.push_back(h_sig1000_UL2016_postVFP);
  h_sig1000.push_back(h_sig1000_UL2017);
  h_sig1000.push_back(h_sig1000_UL2018);

  cout << "[Validation]" << endl;
  cout << var << endl;
  cout << h_ttbar_UL2016_preVFP->GetBinContent(1) << " : " << h_ttbar_UL2016_preVFP->GetBinContent(2) << " : " << h_ttbar_UL2016_preVFP->GetBinContent(3) << endl;
  cout << h_sig1800_UL2016_preVFP->GetBinContent(1) << " : " << h_sig1800_UL2016_preVFP->GetBinContent(2) << " : " << h_sig1800_UL2016_preVFP->GetBinContent(3) << endl;
  cout << h_sig1000_UL2016_preVFP->GetBinContent(1) << " : " << h_sig1000_UL2016_preVFP->GetBinContent(2) << " : " << h_sig1000_UL2016_preVFP->GetBinContent(3) << endl;
  cout << endl;


  return std::make_tuple(h_ttbar, h_sig1800, h_sig1000);
}

void plot_1d_var()
{
  gErrorIgnoreLevel = kError+1;
  TH1::SetDefaultSumw2();

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  styles style("CMSPaper");
  //style.LabelSize    *= 1.1;
  //style.LegendSize   *= 1.0;
  //style.TitleSize    *= 1.1;
  //style.yTitleOffset /= 1.3;
  //style.xTitleOffset /= 1.08;

  auto [vec_ttbar_njet, vec_sig1800_njet, vec_sig1000_njet] = make_hist_var("njet");
  auto [vec_ttbar_nb,   vec_sig1800_nb,   vec_sig1000_nb]   = make_hist_var("nb");
  auto [vec_ttbar_mj,   vec_sig1800_mj,   vec_sig1000_mj]   = make_hist_var("mj");

      // ttbar
  TH1D* h_ttbar_njet = new TH1D("h_ttbar_njet", "h_ttbar_njet", 11, 4, 15);
  TH1D* h_ttbar_nb   = new TH1D("h_ttbar_nb",   "h_ttbar_nb",   5, 0, 5);
  TH1D* h_ttbar_mj   = new TH1D("h_ttbar_mj",   "h_ttbar_mj",   10, 500, 2000);
      // sig 1800
  TH1D* h_sig1800_njet = new TH1D("h_sig1800_njet", "h_sig1800_njet", 11, 4, 15);
  TH1D* h_sig1800_nb   = new TH1D("h_sig1800_nb",   "h_sig1800_nb",   5, 0, 5);
  TH1D* h_sig1800_mj   = new TH1D("h_sig1800_mj",   "h_sig1800_mj",   10, 500, 2000);
      // sig 1000
  TH1D* h_sig1000_njet = new TH1D("h_sig1000_njet", "h_sig1000_njet", 11, 4, 15);
  TH1D* h_sig1000_nb   = new TH1D("h_sig1000_nb",   "h_sig1000_nb",   5, 0, 5);
  TH1D* h_sig1000_mj   = new TH1D("h_sig1000_mj",   "h_sig1000_mj",   10, 500, 2000);

      // ttbar
  for(int i=0; i<vec_ttbar_njet.size(); i++) {
    h_ttbar_njet->Add(vec_ttbar_njet.at(i));
    h_ttbar_nb->Add(vec_ttbar_nb.at(i));
    h_ttbar_mj->Add(vec_ttbar_mj.at(i));
  }
      // sig 1800
  for(int i=0; i<vec_sig1800_njet.size(); i++) {
    h_sig1800_njet->Add(vec_sig1800_njet.at(i));
    h_sig1800_nb->Add(vec_sig1800_nb.at(i));
    h_sig1800_mj->Add(vec_sig1800_mj.at(i));
  }
      // sig 1000
  for(int i=0; i<vec_sig1000_njet.size(); i++) {
    h_sig1000_njet->Add(vec_sig1000_njet.at(i));
    h_sig1000_nb->Add(vec_sig1000_nb.at(i));
    h_sig1000_mj->Add(vec_sig1000_mj.at(i));
  }

  // Normalization
      // ttbar
  h_ttbar_njet->Scale(100./h_ttbar_njet->Integral(0,-1));
  h_ttbar_nb->Scale(100./h_ttbar_nb->Integral(0,-1));
  h_ttbar_mj->Scale(100./h_ttbar_mj->Integral(0,-1));
      // sig 1800
  h_sig1800_njet->Scale(100./h_sig1800_njet->Integral(0,-1));
  h_sig1800_nb->Scale(100./h_sig1800_nb->Integral(0,-1));
  h_sig1800_mj->Scale(100./h_sig1800_mj->Integral(0,-1));
      // sig 1000
  h_sig1000_njet->Scale(100./h_sig1000_njet->Integral(0,-1));
  h_sig1000_nb->Scale(100./h_sig1000_nb->Integral(0,-1));
  h_sig1000_mj->Scale(100./h_sig1000_mj->Integral(0,-1));


  // Cosmetics
  h_ttbar_njet->SetLineColor(TColor::GetColor("#3f90da")); h_ttbar_nb->SetLineColor(TColor::GetColor("#3f90da")); h_ttbar_mj->SetLineColor(TColor::GetColor("#3f90da"));
  h_sig1800_njet->SetLineColor(TColor::GetColor("#bd1f01")); h_sig1800_nb->SetLineColor(TColor::GetColor("#bd1f01")); h_sig1800_mj->SetLineColor(TColor::GetColor("#bd1f01"));
  h_sig1000_njet->SetLineColor(TColor::GetColor("#bd1f01")); h_sig1000_nb->SetLineColor(TColor::GetColor("#bd1f01")); h_sig1000_mj->SetLineColor(TColor::GetColor("#bd1f01"));
  h_ttbar_njet->SetLineWidth(4); h_ttbar_nb->SetLineWidth(4); h_ttbar_mj->SetLineWidth(4);
  h_sig1800_njet->SetLineWidth(4); h_sig1800_nb->SetLineWidth(4); h_sig1800_mj->SetLineWidth(4);
  h_sig1000_njet->SetLineWidth(4); h_sig1000_nb->SetLineWidth(4); h_sig1000_mj->SetLineWidth(4);
  h_sig1000_njet->SetLineStyle(2); h_sig1000_nb->SetLineStyle(2); h_sig1000_mj->SetLineStyle(2);
  h_ttbar_njet->GetXaxis()->SetTitle("N_{jet}"); h_ttbar_nb->GetXaxis()->SetTitle("N_{b}"); h_ttbar_mj->GetXaxis()->SetTitle("M_{J} (GeV)");
  h_ttbar_njet->GetYaxis()->SetTitle("% events"); h_ttbar_nb->GetYaxis()->SetTitle("% events"); h_ttbar_mj->GetYaxis()->SetTitle("% events / (150 GeV)");
  h_ttbar_njet->GetXaxis()->SetTitleSize(0.055); h_ttbar_nb->GetXaxis()->SetTitleSize(0.055); h_ttbar_mj->GetXaxis()->SetTitleSize(0.055);
  h_ttbar_njet->GetYaxis()->SetTitleSize(0.055); h_ttbar_nb->GetYaxis()->SetTitleSize(0.055); h_ttbar_mj->GetYaxis()->SetTitleSize(0.055);
  h_ttbar_njet->GetXaxis()->SetLabelSize(0.05); h_ttbar_nb->GetXaxis()->SetLabelSize(0.05); h_ttbar_mj->GetXaxis()->SetLabelSize(0.05);
  h_ttbar_njet->GetYaxis()->SetLabelSize(0.05); h_ttbar_nb->GetYaxis()->SetLabelSize(0.05); h_ttbar_mj->GetYaxis()->SetLabelSize(0.05);
  h_ttbar_njet->GetYaxis()->SetRangeUser(0.008, 750); h_ttbar_nb->GetYaxis()->SetRangeUser(0.05, 750); h_ttbar_mj->GetYaxis()->SetRangeUser(0.008, 750);

  h_ttbar_njet->GetYaxis()->SetTitleOffset(1.2); h_ttbar_nb->GetYaxis()->SetTitleOffset(1.2); h_ttbar_mj->GetYaxis()->SetTitleOffset(1.2);
  h_ttbar_njet->GetXaxis()->SetTitleOffset(1.2); h_ttbar_nb->GetXaxis()->SetTitleOffset(1.2); h_ttbar_mj->GetXaxis()->SetTitleOffset(1.2);

  h_ttbar_njet->GetXaxis()->SetNdivisions(-11);
  h_ttbar_nb->GetXaxis()->SetNdivisions(6);
  h_ttbar_mj->GetXaxis()->SetNdivisions(-10); // '-': compulsorily

  h_ttbar_njet->GetXaxis()->SetLabelOffset(1);
  h_ttbar_nb->GetXaxis()->SetLabelOffset(0.01);
  h_ttbar_mj->GetXaxis()->SetLabelOffset(1);


  TLatex* tex_njet4  = new TLatex(0.15, 0.11,  "4");
  TLatex* tex_njet6  = new TLatex(0.28, 0.11,  "6");
  TLatex* tex_njet8  = new TLatex(0.42, 0.11,  "8");
  TLatex* tex_njet10  = new TLatex(0.54, 0.11, "10");
  TLatex* tex_njet12  = new TLatex(0.67, 0.11, "12");
  TLatex* tex_njet14  = new TLatex(0.81, 0.11, "14");

  tex_njet4->SetNDC(); tex_njet6->SetNDC(); tex_njet8->SetNDC(); tex_njet10->SetNDC(); tex_njet12->SetNDC(); tex_njet14->SetNDC();
  tex_njet4->SetTextSize(0.05); tex_njet6->SetTextSize(0.05); tex_njet8->SetTextSize(0.05); tex_njet10->SetTextSize(0.05); tex_njet12->SetTextSize(0.05); tex_njet14->SetTextSize(0.05);
  tex_njet4->SetTextFont(42); tex_njet6->SetTextFont(42); tex_njet8->SetTextFont(42); tex_njet10->SetTextFont(42); tex_njet12->SetTextFont(42); tex_njet14->SetTextFont(42);

  TLatex* tex_mj500  = new TLatex(0.12, 0.11, "500");
  TLatex* tex_mj800  = new TLatex(0.27, 0.11, "800");
  TLatex* tex_mj1100 = new TLatex(0.40, 0.11, "1100");
  TLatex* tex_mj1400 = new TLatex(0.55, 0.11, "1400");
  TLatex* tex_mj1700 = new TLatex(0.70, 0.11, "1700");
  TLatex* tex_mj2000 = new TLatex(0.85, 0.11, "2000");

  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC(); tex_mj1700->SetNDC(); tex_mj2000->SetNDC();
  tex_mj500->SetTextSize(0.05); tex_mj800->SetTextSize(0.05); tex_mj1100->SetTextSize(0.05); tex_mj1400->SetTextSize(0.05); tex_mj1700->SetTextSize(0.05); tex_mj2000->SetTextSize(0.05);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42); tex_mj1700->SetTextFont(42); tex_mj2000->SetTextFont(42);







  h_ttbar_njet->SetTitle(""); h_ttbar_nb->SetTitle(""); h_ttbar_mj->SetTitle("");
  //h_ttbar_njet->GetXaxis()->SetLabelOffset(1); h_ttbar_nb->GetXaxis()->SetLabelOffset(1); h_ttbar_mj->GetXaxis()->SetLabelOffset(1);
  //h_ttbar_njet->GetYaxis()->SetLabelSize(0.07); h_ttbar_nb->GetYaxis()->SetLabelSize(0.07); h_ttbar_mj->GetYaxis()->SetLabelSize(0.07);



  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.89, 0.93, Form("138 fb^{-1} (13 TeV)"));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.045);
  TLatex *TexCMS = new TLatex(0.16,0.92,"CMS #font[52]{Preliminary}");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.045);
  TexCMS->SetLineWidth(2);

  // Make TLegend
      // njet
  TLegend* l_njet_left = new TLegend(0.22, 0.80, 0.66, 0.85);
  l_njet_left->SetTextSize(0.045);
  l_njet_left->SetBorderSize(0);
  l_njet_left->SetFillStyle(0);
  l_njet_left->AddEntry(h_ttbar_njet,    "t#bar{t}", "l");
  TLegend* l_njet_right = new TLegend(0.48, 0.70, 0.92, 0.87);
  l_njet_right->SetTextSize(0.045);
  l_njet_right->SetBorderSize(0);
  l_njet_right->SetFillStyle(0);
  l_njet_right->AddEntry(h_sig1000_njet, "m_{#tilde{g}}=1000 GeV", "l");
  l_njet_right->AddEntry(h_sig1800_njet, "m_{#tilde{g}}=1800 GeV", "l");
      // nb
  TLegend* l_nb_left = new TLegend(0.22, 0.80, 0.66, 0.85);
  l_nb_left->SetTextSize(0.045);
  l_nb_left->SetBorderSize(0);
  l_nb_left->SetFillStyle(0);
  l_nb_left->AddEntry(h_ttbar_nb,    "t#bar{t}", "l");
  TLegend* l_nb_right = new TLegend(0.48, 0.70, 0.92, 0.87);
  l_nb_right->SetTextSize(0.045);
  l_nb_right->SetBorderSize(0);
  l_nb_right->SetFillStyle(0);
  l_nb_right->AddEntry(h_sig1000_nb, "m_{#tilde{g}}=1000 GeV", "l");
  l_nb_right->AddEntry(h_sig1800_nb, "m_{#tilde{g}}=1800 GeV", "l");
      // mj
  TLegend* l_mj_left = new TLegend(0.22, 0.80, 0.66, 0.85);
  l_mj_left->SetTextSize(0.045);
  l_mj_left->SetBorderSize(0);
  l_mj_left->SetFillStyle(0);
  l_mj_left->AddEntry(h_ttbar_mj,    "t#bar{t}", "l");
  TLegend* l_mj_right = new TLegend(0.48, 0.70, 0.92, 0.87);
  l_mj_right->SetTextSize(0.045);
  l_mj_right->SetBorderSize(0);
  l_mj_right->SetFillStyle(0);
  l_mj_right->AddEntry(h_sig1000_mj, "m_{#tilde{g}}=1000 GeV", "l");
  l_mj_right->AddEntry(h_sig1800_mj, "m_{#tilde{g}}=1800 GeV", "l");

  // Draw plots
      // njet
  TCanvas* c_njet = new TCanvas("c_njet", "c_njet", 800, 800);
  c_njet->cd();
  c_njet->SetLeftMargin(0.16); c_njet->SetBottomMargin(0.16);
  gPad->SetLogy();
  h_ttbar_njet->Draw("hist");
  h_sig1000_njet->Draw("same hist");
  h_sig1800_njet->Draw("same hist");
  l_njet_left->Draw();
  l_njet_right->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_njet4->Draw();
  tex_njet6->Draw();
  tex_njet8->Draw();
  tex_njet10->Draw();
  tex_njet12->Draw();
  tex_njet14->Draw();
  c_njet->Print("plots/plot_ttbar_vs_sig_njet.pdf");
      // nb
  TCanvas* c_nb = new TCanvas("c_nb", "c_nb", 800, 800);
  c_nb->cd();
  c_nb->SetLeftMargin(0.16); c_nb->SetBottomMargin(0.16);
  gPad->SetLogy();
  h_ttbar_nb->Draw("hist");
  h_sig1000_nb->Draw("same hist");
  h_sig1800_nb->Draw("same hist");
  l_nb_left->Draw();
  l_nb_right->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  c_nb->Print("plots/plot_ttbar_vs_sig_nb.pdf");
      // mj
  TCanvas* c_mj = new TCanvas("c_mj", "c_mj", 800, 800);
  c_mj->cd();
  c_mj->SetLeftMargin(0.16); c_mj->SetBottomMargin(0.16);
  gPad->SetLogy();
  h_ttbar_mj->Draw("hist");
  h_sig1000_mj->Draw("same hist");
  h_sig1800_mj->Draw("same hist");
  l_mj_left->Draw();
  l_mj_right->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_mj500->Draw();
  tex_mj800->Draw();
  tex_mj1100->Draw();
  tex_mj1400->Draw();
  tex_mj1700->Draw();
  tex_mj2000->Draw();
  c_mj->Print("plots/plot_ttbar_vs_sig_mj.pdf");



}


int main(int argc, char **argv)
{

  plot_1d_var();
 
  return 0;
}
