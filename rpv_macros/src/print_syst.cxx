
#include <iomanip>
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
#include "TLatex.h" 
#include "TFile.h"
#include "TMath.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"


using namespace std;

void qcd_fake_ratio(TString year) {

  TH1::SetDefaultSumw2();

  TString lumi, trigger;

  if(year=="UL2016_preVFP") {
    lumi = "19.5";
    trigger = "(trig_jet450 || trig_ht900)";
  }
  else if(year=="UL2016_postVFP") {
    lumi = "16.8";
    trigger = "(trig_jet450 || trig_ht900)";
  }
  else if(year=="UL2017") {
    lumi = "41.5";
    trigger = "trig_ht1050";
  }
  else if(year=="UL2018") {
    lumi = "59.8";
    trigger = "trig_ht1050";
  }
  else {
    cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018" << endl;
  }



  TString folder_dat = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_data/";
  TString folder_bkg = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_mc/";
  TString folder_sig = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_sig/";

  TChain* ch_dat = new TChain("tree");
  TChain* ch_sig = new TChain("tree");
  TChain* ch_qcd = new TChain("tree");
  TChain* ch_bkg = new TChain("tree");

  ch_dat->Add(folder_dat+"*Run*.root");
  ch_sig->Add(folder_sig+"SMS-T1tbs_RPV_mGluino1800_*.root");
  ch_qcd->Add(folder_bkg+"QCD_*.root");
  ch_bkg->Add(folder_bkg+"DYJetsToLL_*.root");
  ch_bkg->Add(folder_bkg+"ST_*.root");
  ch_bkg->Add(folder_bkg+"ttHJetTobb_*.root");
  ch_bkg->Add(folder_bkg+"TTJets_*.root");
  ch_bkg->Add(folder_bkg+"TTTT_*.root");
  ch_bkg->Add(folder_bkg+"TTWJetsToLNu_*.root");
  ch_bkg->Add(folder_bkg+"TTWJetsToQQ_*.root");
  ch_bkg->Add(folder_bkg+"TTZToLLNuNu_*.root");
  ch_bkg->Add(folder_bkg+"TTZToQQ_*.root");
  ch_bkg->Add(folder_bkg+"WJetsToLNu_*.root");
  ch_bkg->Add(folder_bkg+"WW_*.root");
  ch_bkg->Add(folder_bkg+"WWW_*.root");
  ch_bkg->Add(folder_bkg+"WWZ_*.root");
  ch_bkg->Add(folder_bkg+"WZ_*.root");
  ch_bkg->Add(folder_bkg+"WZZ_*.root");
  ch_bkg->Add(folder_bkg+"ZZ_*.root");
  ch_bkg->Add(folder_bkg+"ZZZ_*.root");



  vector<TString> njetcuts = {"(njets>=4&&njets<=5)", "(njets>=6&&njets<=7)", "(njets>=8)"};

  // Cuts for real electrons
  TString cut_real_ele = "(mj12<500 && ht>1200 && (nbm==0) && els_pt>20 && abs(els_eta)<2.5 && (els_miniso<0.1 && els_sigid==1) && met<50)";
  // Cuts for fake electrons
  TString cut_fake_ele = "(mj12<500 && ht>1200 && (nbm==0) && els_pt>20 && abs(els_eta)<2.5 && (els_miniso>=0.1 || els_sigid==0) && met<50)";
  // Cuts for real muons
  TString cut_real_muon = "(mj12<500 && ht>1200 && (nbm==0) && mus_pt>20 && abs(mus_eta)<2.4 && (mus_miniso<0.2 && mus_sigid==1) && met<50)";
  // Cuts for fake muons
  TString cut_fake_muon = "(mj12<500 && ht>1200 && (nbm==0) && mus_pt>20 && abs(mus_eta)<2.4 && (mus_miniso>=0.2 || mus_sigid==0) && met<50)";
   

  for(auto injet : njetcuts) {

    cout << "njetcuts: " << injet << endl;

    TH1D* h_dat_real_ele = new TH1D("h_dat_real_ele","h_dat_real_ele",1,0,1500);
    TH1D* h_sig_real_ele = new TH1D("h_sig_real_ele","h_sig_real_ele",1,0,1500);
    TH1D* h_qcd_real_ele = new TH1D("h_qcd_real_ele","h_qcd_real_ele",1,0,1500);
    TH1D* h_bkg_real_ele = new TH1D("h_bkg_real_ele","h_bkg_real_ele",1,0,1500);

    TH1D* h_dat_fake_ele = new TH1D("h_dat_fake_ele","h_dat_fake_ele",1,0,1500);
    TH1D* h_sig_fake_ele = new TH1D("h_sig_fake_ele","h_sig_fake_ele",1,0,1500);
    TH1D* h_qcd_fake_ele = new TH1D("h_qcd_fake_ele","h_qcd_fake_ele",1,0,1500);
    TH1D* h_bkg_fake_ele = new TH1D("h_bkg_fake_ele","h_bkg_fake_ele",1,0,1500);

    TH1D* h_dat_real_muon = new TH1D("h_dat_real_muon","h_dat_real_muon",1,0,1500);
    TH1D* h_sig_real_muon = new TH1D("h_sig_real_muon","h_sig_real_muon",1,0,1500);
    TH1D* h_qcd_real_muon = new TH1D("h_qcd_real_muon","h_qcd_real_muon",1,0,1500);
    TH1D* h_bkg_real_muon = new TH1D("h_bkg_real_muon","h_bkg_real_muon",1,0,1500);

    TH1D* h_dat_fake_muon = new TH1D("h_dat_fake_muon","h_dat_fake_muon",1,0,1500);
    TH1D* h_sig_fake_muon = new TH1D("h_sig_fake_muon","h_sig_fake_muon",1,0,1500);
    TH1D* h_qcd_fake_muon = new TH1D("h_qcd_fake_muon","h_qcd_fake_muon",1,0,1500);
    TH1D* h_bkg_fake_muon = new TH1D("h_bkg_fake_muon","h_bkg_fake_muon",1,0,1500);

    h_dat_real_ele->Sumw2(); h_sig_real_ele->Sumw2(); h_qcd_real_ele->Sumw2(); h_bkg_real_ele->Sumw2();
    h_dat_fake_ele->Sumw2(); h_sig_fake_ele->Sumw2(); h_qcd_fake_ele->Sumw2(); h_bkg_fake_ele->Sumw2();
    h_dat_real_muon->Sumw2(); h_sig_real_muon->Sumw2(); h_qcd_real_muon->Sumw2(); h_bkg_real_muon->Sumw2();
    h_dat_fake_muon->Sumw2(); h_sig_fake_muon->Sumw2(); h_qcd_fake_muon->Sumw2(); h_bkg_fake_muon->Sumw2();


    // real electron
    ch_dat->Draw("min(ht,1499.99)>>h_dat_real_ele", "pass*("+trigger+"&&"+injet+"&&"+cut_real_ele+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_real_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_ele+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_real_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_ele+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_real_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_ele+")", "goff");

    // fake electron
    ch_dat->Draw("min(ht,1499.99)>>h_dat_fake_ele", "pass*("+trigger+"&&"+injet+"&&"+cut_fake_ele+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_fake_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_ele+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_fake_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_ele+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_fake_ele", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_ele+")", "goff");

    // real muon
    ch_dat->Draw("min(ht,1499.99)>>h_dat_real_muon", "pass*("+trigger+"&&"+injet+"&&"+cut_real_muon+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_real_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_muon+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_real_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_muon+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_real_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_real_muon+")", "goff");

    // fake muon
    ch_dat->Draw("min(ht,1499.99)>>h_dat_fake_muon", "pass*("+trigger+"&&"+injet+"&&"+cut_fake_muon+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_fake_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_muon+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_fake_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_muon+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_fake_muon", lumi+"*weight*pass*stitch_ht*("+injet+"&&"+cut_fake_muon+")", "goff");

    /*
    ch_dat->Draw("min(ht,1499.99)>>h_dat_real_ele", "pass*("+trigger+"&&"+injet+"&&"+cut_real_ele+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_real_ele", lumi+"*weight*pass*("+injet+"&&"+cut_real_ele+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_real_ele", lumi+"*weight*pass*("+injet+"&&"+cut_real_ele+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_real_ele", lumi+"*weight*pass*("+injet+"&&"+cut_real_ele+")", "goff");

    ch_dat->Draw("min(ht,1499.99)>>h_dat_fake_ele", "pass*("+trigger+"&&"+injet+"&&"+cut_fake_ele+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_fake_ele", lumi+"*weight*pass*("+injet+"&&"+cut_fake_ele+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_fake_ele", lumi+"*weight*pass*("+injet+"&&"+cut_fake_ele+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_fake_ele", lumi+"*weight*pass*("+injet+"&&"+cut_fake_ele+")", "goff");

    ch_dat->Draw("min(ht,1499.99)>>h_dat_real_muon", "pass*("+trigger+"&&"+injet+"&&"+cut_real_muon+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_real_muon", lumi+"*weight*pass*("+injet+"&&"+cut_real_muon+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_real_muon", lumi+"*weight*pass*("+injet+"&&"+cut_real_muon+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_real_muon", lumi+"*weight*pass*("+injet+"&&"+cut_real_muon+")", "goff");

    ch_dat->Draw("min(ht,1499.99)>>h_dat_fake_muon", "pass*("+trigger+"&&"+injet+"&&"+cut_fake_muon+")", "goff");
    ch_sig->Draw("min(ht,1499.99)>>h_sig_fake_muon", lumi+"*weight*pass*("+injet+"&&"+cut_fake_muon+")", "goff");
    ch_qcd->Draw("min(ht,1499.99)>>h_qcd_fake_muon", lumi+"*weight*pass*("+injet+"&&"+cut_fake_muon+")", "goff");
    ch_bkg->Draw("min(ht,1499.99)>>h_bkg_fake_muon", lumi+"*weight*pass*("+injet+"&&"+cut_fake_muon+")", "goff");
    */

    cout << "qcd_real_ele: "  << h_qcd_real_ele->GetBinContent(1)  << "#pm" << h_qcd_real_ele->GetBinError(1)  << endl;
    cout << "qcd_real_muon: " << h_qcd_real_muon->GetBinContent(1) << "#pm" << h_qcd_real_muon->GetBinError(1) << endl;
    cout << "qcd_fake_ele: "  << h_qcd_fake_ele->GetBinContent(1)  << "#pm" << h_qcd_fake_ele->GetBinError(1)  << endl;
    cout << "qcd_fake_muon: " << h_qcd_fake_muon->GetBinContent(1) << "#pm" << h_qcd_fake_muon->GetBinError(1) << endl;
    cout << "dat_real_ele: "  << h_dat_real_ele->GetBinContent(1)  << "#pm" << h_dat_real_ele->GetBinError(1)  << endl;
    cout << "dat_real_muon: " << h_dat_real_muon->GetBinContent(1) << "#pm" << h_dat_real_muon->GetBinError(1) << endl;
    cout << "dat_fake_ele: "  << h_dat_fake_ele->GetBinContent(1)  << "#pm" << h_dat_fake_ele->GetBinError(1)  << endl;
    cout << "dat_fake_muon: " << h_dat_fake_muon->GetBinContent(1) << "#pm" << h_dat_fake_muon->GetBinError(1) << endl;
    cout << "bkg_real_ele: "  << h_bkg_real_ele->GetBinContent(1)  << "#pm" << h_bkg_real_ele->GetBinError(1)  << endl;
    cout << "bkg_real_muon: " << h_bkg_real_muon->GetBinContent(1) << "#pm" << h_bkg_real_muon->GetBinError(1) << endl;
    cout << "bkg_fake_ele: "  << h_bkg_fake_ele->GetBinContent(1)  << "#pm" << h_bkg_fake_ele->GetBinError(1)  << endl;
    cout << "bkg_fake_muon: " << h_bkg_fake_muon->GetBinContent(1) << "#pm" << h_bkg_fake_muon->GetBinError(1) << endl;

    // 
    TH1D* h_qcd_real_lep 		= new TH1D("h_qcd_real_lep","h_qcd_real_lep",1,0,1500);
    TH1D* h_qcd_fake_lep 		= new TH1D("h_qcd_fake_lep","h_qcd_fake_lep",1,0,1500);
    TH1D* h_dat_minus_others_real_lep   = new TH1D("h_dat_minus_others_real_lep","h_dat_minus_others_real_lep",1,0,1500);
    TH1D* h_dat_minus_others_fake_lep   = new TH1D("h_dat_minus_others_fake_lep","h_dat_minus_others_fake_lep",1,0,1500);
    h_qcd_real_lep->Sumw2(); h_qcd_fake_lep->Sumw2(); h_dat_minus_others_real_lep->Sumw2(); h_dat_minus_others_fake_lep->Sumw2();

    h_qcd_real_lep = static_cast<TH1D*>(h_qcd_real_ele->Clone("h_qcd_real_lep"));
    h_qcd_real_lep->Add(h_qcd_real_muon);
    h_qcd_fake_lep = static_cast<TH1D*>(h_qcd_fake_ele->Clone("h_qcd_fake_lep"));
    h_qcd_fake_lep->Add(h_qcd_fake_muon);

    h_dat_minus_others_real_lep = static_cast<TH1D*>(h_dat_real_ele->Clone("h_dat_minus_others_real_lep"));
    h_dat_minus_others_real_lep->Add(h_dat_real_muon, 1.);
    h_dat_minus_others_real_lep->Add(h_bkg_real_ele, -1.);
    h_dat_minus_others_real_lep->Add(h_bkg_real_muon, -1.);
    h_dat_minus_others_fake_lep = static_cast<TH1D*>(h_dat_fake_ele->Clone("h_dat_minus_others_fake_lep"));
    h_dat_minus_others_fake_lep->Add(h_dat_fake_muon, 1.);
    h_dat_minus_others_fake_lep->Add(h_bkg_fake_ele, -1.);
    h_dat_minus_others_fake_lep->Add(h_bkg_fake_muon, -1.);

    TH1D* h_qcd_ratio 		      = new TH1D("h_qcd_ratio", "h_qcd_ratio", 1, 0, 1500);
    TH1D* h_dat_minus_others_ratio    = new TH1D("h_dat_minus_others_ratio", "h_dat_minus_others_ratio", 1, 0, 1500);
    TH1D* h_dat_minus_others_qcd_ratio = new TH1D("h_dat_minus_others_qcd_ratio", "h_dat_minus_others_qcd_ratio", 1, 0, 1500);
    h_qcd_ratio->Sumw2(); h_dat_minus_others_ratio->Sumw2(), h_dat_minus_others_qcd_ratio->Sumw2();

    h_qcd_ratio = static_cast<TH1D*>(h_qcd_real_lep->Clone("h_qcd_ratio"));
    h_qcd_ratio->Divide(h_qcd_fake_lep);
    h_dat_minus_others_ratio = static_cast<TH1D*>(h_dat_minus_others_real_lep->Clone("h_dat_minus_others_ratio"));
    h_dat_minus_others_ratio->Divide(h_dat_minus_others_fake_lep);
    h_dat_minus_others_qcd_ratio = static_cast<TH1D*>(h_dat_minus_others_ratio->Clone("h_dat_minus_others_qcd_ratio"));
    h_dat_minus_others_qcd_ratio->Divide(h_qcd_ratio);


    //cout.width(10);
    cout.precision(10);
    cout << " " << endl;
    cout << "||" << std::right << setw(25) << "Process" << setw(20) << "||" << setw(29) << "Real Leptons" << setw(20) << "||" << setw(29) << "Fake Leptons" << setw(20) << "||" << setw(23) << "ratio" << setw(20) << "||" << setw(30) << "(Data-all other)/QCD" << endl;
    cout << "||" << std::right << setw(22) << "QCD" << setw(23) << "||" << setw(22) << h_qcd_real_lep->GetBinContent(1) << " #pm " << std::left << setw(20) << h_qcd_real_lep->GetBinError(1) << "||" << std::right << setw(22) << h_qcd_fake_lep->GetBinContent(1) << " #pm " << std::left << setw(20) << h_qcd_fake_lep->GetBinError(1) << "||" << std::right << setw(19) << h_qcd_ratio->GetBinContent(1) << " #pm " << std::left << setw(17) << h_qcd_ratio->GetBinError(1) << "||" << endl;
    cout << "||" << std::right << setw(25) << "" << setw(20) << "||" << setw(29) << "" << setw(20) << "||" << setw(29) << "" << setw(20) << "||" << setw(23) << "" << setw(20) << "||" << setw(18) << h_dat_minus_others_qcd_ratio->GetBinContent(1) << " #pm " << std::left << setw(21) << h_dat_minus_others_qcd_ratio->GetBinError(1) << setw(8) << Form("%.2f", TMath::Sqrt((1-h_dat_minus_others_qcd_ratio->GetBinContent(1))*(1-h_dat_minus_others_qcd_ratio->GetBinContent(1)) + h_dat_minus_others_qcd_ratio->GetBinError(1)*h_dat_minus_others_qcd_ratio->GetBinError(1))) << endl;
    cout << "||" << std::right << setw(29) << "Data-all others" << setw(16) << "||" << setw(22) << h_dat_minus_others_real_lep->GetBinContent(1) << " #pm " << std::left << setw(20) << h_dat_minus_others_real_lep->GetBinError(1) << "|| " << std::right << setw(21) << h_dat_minus_others_fake_lep->GetBinContent(1) << " #pm " << std::left << setw(20) << h_dat_minus_others_fake_lep->GetBinError(1) << "||" << std::right << setw(19) << h_dat_minus_others_ratio->GetBinContent(1) << " #pm " << std::left << setw(17) << h_dat_minus_others_ratio->GetBinError(1) << "||" << endl;
    cout << " " << endl;


    

    delete h_dat_real_ele; delete h_sig_real_ele; delete h_qcd_real_ele; delete h_bkg_real_ele;
    delete h_dat_fake_ele; delete h_sig_fake_ele; delete h_qcd_fake_ele; delete h_bkg_fake_ele;
    delete h_dat_real_muon; delete h_sig_real_muon; delete h_qcd_real_muon; delete h_bkg_real_muon;
    delete h_dat_fake_muon; delete h_sig_fake_muon; delete h_qcd_fake_muon; delete h_bkg_fake_muon;
    delete h_qcd_real_lep; delete h_qcd_fake_lep;
    delete h_dat_minus_others_real_lep; delete h_dat_minus_others_fake_lep;
    delete h_qcd_ratio; delete h_dat_minus_others_ratio; delete h_dat_minus_others_qcd_ratio;
  }

}

void ttbar_purity(TString year) {

  TString inputfile;

  if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
    inputfile = "variations/output_nominal_newnt_"+year+"_UL2016.root";
  }
  else if(year=="UL2017" || year=="UL2018") {
    inputfile = "variations/output_nominal_newnt_"+year+"_UL20178.root";
  }
  else if(year=="UL2016" || year=="UL20178") {
    inputfile = "variations/output_nominal_newnt_"+year+".root";
  }

  TFile* f_in = new TFile(inputfile, "READ");
  
  TH1D *qcd, *ttbar, *wjets, *other;
  // mj0: 1st MJ bin, mj1: 2nd MJ bin, mj2: 3rd MJ bin
  float mj0[6], mj1[6], mj2[6];

  for(int ibin=22; ibin<28; ibin++) {
    qcd   = (TH1D*)f_in->Get(Form("bin%i/qcd"  , ibin));
    ttbar = (TH1D*)f_in->Get(Form("bin%i/ttbar", ibin));
    wjets = (TH1D*)f_in->Get(Form("bin%i/wjets", ibin));
    other = (TH1D*)f_in->Get(Form("bin%i/other", ibin));

    mj0[ibin-22] = 100*ttbar->GetBinContent(1) / (qcd->GetBinContent(1)+ttbar->GetBinContent(1)+wjets->GetBinContent(1)+other->GetBinContent(1));
    mj1[ibin-22] = 100*ttbar->GetBinContent(2) / (qcd->GetBinContent(2)+ttbar->GetBinContent(2)+wjets->GetBinContent(2)+other->GetBinContent(2));
    mj2[ibin-22] = 100*ttbar->GetBinContent(3) / (qcd->GetBinContent(3)+ttbar->GetBinContent(3)+wjets->GetBinContent(3)+other->GetBinContent(3));

  }
  cout.precision(3);
  cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| 4 <= Njet <= 5  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
  cout << "||" << setw(19) << "||" << setw(27) << "500 < MJ < 800" << setw(13) << "||" << setw(27) << "800 < MJ < 1100" << setw(13) << "||" << setw(27) << "1100 < MJ" << setw(13) << "||" << endl;
  cout << "||" << setw(10) << "Nb=0" << setw(9) << "||" << setw(25) << to_string(mj0[0])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[0])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[0])+" %" << setw(15) << "||" << endl;
  cout << "||" << setw(10) << "Nb=1" << setw(9) << "||" << setw(25) << to_string(mj0[3])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[3])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[3])+" %" << setw(15) << "||" << endl;
  cout << "=============================================================================================================================================" << endl;
  cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| 6 <= Njet <= 7  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
  cout << "||" << setw(19) << "||" << setw(27) << "500 < MJ < 800" << setw(13) << "||" << setw(27) << "800 < MJ < 1100" << setw(13) << "||" << setw(27) << "1100 < MJ" << setw(13) << "||" << endl;
  cout << "||" << setw(10) << "Nb=0" << setw(9) << "||" << setw(25) << to_string(mj0[1])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[1])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[1])+" %" << setw(15) << "||" << endl;
  cout << "||" << setw(10) << "Nb=1" << setw(9) << "||" << setw(25) << to_string(mj0[4])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[4])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[4])+" %" << setw(15) << "||" << endl;
  cout << "=============================================================================================================================================" << endl;
  cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| 8 <= Njet  ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
  cout << "||" << setw(19) << "||" << setw(27) << "500 < MJ < 800" << setw(13) << "||" << setw(27) << "800 < MJ < 1100" << setw(13) << "||" << setw(27) << "1100 < MJ" << setw(13) << "||" << endl;
  cout << "||" << setw(10) << "Nb=0" << setw(9) << "||" << setw(25) << to_string(mj0[2])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[2])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[2])+" %" << setw(15) << "||" << endl;
  cout << "||" << setw(10) << "Nb=1" << setw(9) << "||" << setw(25) << to_string(mj0[5])+" %" << setw(15) << "||" << setw(25) << to_string(mj1[5])+" %" << setw(15) << "||" << setw(25) << to_string(mj2[5])+" %" << setw(15) << "||" << endl;
  cout << "=============================================================================================================================================" << endl;
    




}

int main(int argc, char *argv[]) {


  int nthreads = 16;
  ROOT::EnableImplicitMT(nthreads);

  TString year, type;

  TString arg(argv[1]);

  if(argc<2 || arg=="--help") {
    cout << "./run/print_syst.exe [year] [type]" << endl;
    cout << "[year]: UL2016_preVFP, UL2016_postVFP, UL2017, or UL2018" << endl;
    cout << "[type]: qcd or ttbar or wjets" << endl;
    cout << "FYI - qcd  : qcd fake ratio" << endl;
    cout << "FYI - ttbar: ttbar purity" << endl;
    return 0;
  }
  else if(argc>2) {
    year = argv[1];
    type = argv[2];
  }



  if(type == "qcd") qcd_fake_ratio(year);
  else if(type == "ttbar") ttbar_purity(year);
  

  return 0;
}




















