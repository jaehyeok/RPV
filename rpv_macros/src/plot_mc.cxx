// plot_note: Macro that plots variables both lumi weighted and normalized to the same area.

#include <iostream>
#include <vector>
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"
#include "TColor.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
  }

using namespace std;

enum linecolor{
    c_nb0=kAzure+7,
    c_nb1=kYellow-7,
    c_nb2=kGreen+2,
    c_nb3=kGray+2,
    c_nb4=kMagenta+1
};

int main(int argc, char *argv[]){

  TString year = argv[1];
  if(argc<1){
    cout<<"./run/plot_mc.exe [year] !!!!"<<endl;
  }
  string lumi;
  if(year=="UL2016_preVFP") lumi="19.5";
  else if(year=="UL2016_postVFP") lumi="16.8";
  else if(year=="UL2017") lumi="41.5";
  else if(year=="UL2018") lumi="59.8";

  // ntuple folders
  TString folder_bkg = "/mnt/data3/babies/250110/"+year+"/merged_rpvfitnbge0_mc/";

  // Get file lists
  vector<TString> s_qcd_njet45   = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_ttbar_njet45 = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets_njet45 = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other_njet45 = getRPVProcess(folder_bkg,"other_public");
  vector<TString> s_qcd   = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");

  // Reading ntuples
  vector<sfeats> Samples_qcd_njet45, Samples_ttbar_njet45, Samples_wjets_njet45;
  vector<sfeats> Samples_qcd, Samples_ttbar, Samples_wjets;
  string extraweight = "1";

  // qcd
      // njet45
  Samples_qcd_njet45.push_back(sfeats(s_qcd_njet45, "qcd N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_qcd_njet45.push_back(sfeats(s_qcd_njet45, "qcd N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_qcd_njet45.push_back(sfeats(s_qcd_njet45, "qcd N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_qcd_njet45.push_back(sfeats(s_qcd_njet45, "qcd N_{b}#geq3",	linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
      // njet67, 8-
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}#geq3",	linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
  // ttbar
      // njet45
  Samples_ttbar_njet45.push_back(sfeats(s_ttbar_njet45, "t#bar{t} N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_ttbar_njet45.push_back(sfeats(s_ttbar_njet45, "t#bar{t} N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_ttbar_njet45.push_back(sfeats(s_ttbar_njet45, "t#bar{t} N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_ttbar_njet45.push_back(sfeats(s_ttbar_njet45, "t#bar{t} N_{b}#geq3", linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
      // njet67, 8-
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}#geq3", linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
  // wjets 
      // njet45
  Samples_wjets_njet45.push_back(sfeats(s_wjets_njet45, "wjets N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_wjets_njet45.push_back(sfeats(s_wjets_njet45, "wjets N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_wjets_njet45.push_back(sfeats(s_wjets_njet45, "wjets N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_wjets_njet45.push_back(sfeats(s_wjets_njet45, "wjets N_{b}#geq3",	linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
      // njet67, 8-
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=0",	linecolor::c_nb0,   1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=1",	linecolor::c_nb1,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=2",	linecolor::c_nb2,   1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}#geq3",	linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));

  // Loop over samples
      // njet45
  vector<int> rpv_sam_qcd_njet45, rpv_sam_ttbar_njet45, rpv_sam_wjets_njet45;
  for(unsigned sam(0); sam < Samples_qcd_njet45.size(); sam++) rpv_sam_qcd_njet45.push_back(sam);
  for(unsigned sam(0); sam < Samples_ttbar_njet45.size(); sam++) rpv_sam_ttbar_njet45.push_back(sam);
  for(unsigned sam(0); sam < Samples_wjets_njet45.size(); sam++) rpv_sam_wjets_njet45.push_back(sam);
      // njet67, 8-
  vector<int> rpv_sam_qcd, rpv_sam_ttbar, rpv_sam_wjets;
  for(unsigned sam(0); sam < Samples_qcd.size(); sam++) rpv_sam_qcd.push_back(sam);
  for(unsigned sam(0); sam < Samples_ttbar.size(); sam++) rpv_sam_ttbar.push_back(sam);
  for(unsigned sam(0); sam < Samples_wjets.size(); sam++) rpv_sam_wjets.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists_qcd_njet45, hists_ttbar_njet45, hists_wjets_njet45;
  vector<hfeats> hists_qcd, hists_ttbar, hists_wjets;

  ////////////
  // njet45 //
  ////////////
  // Set cuts
  TString basecut = "mj12>=500&&nleps==1&&ht>1200";
  // Loop over cuts to make histograms
  TString cut = "";
  cut = basecut + "&&" + "njets>=4&&njets<=5";
  // Define histograms
  hists_qcd_njet45.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_qcd_njet45, "M_{J}", cut));
  hists_ttbar_njet45.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_ttbar_njet45, "M_{J}", cut));
  hists_wjets_njet45.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_wjets_njet45, "M_{J}", cut));
  // Make plots
  plot_distributions(Samples_qcd_njet45, hists_qcd_njet45, lumi, plot_type, plot_style, "rpv_base_qcd", false, true);  
  plot_distributions(Samples_ttbar_njet45, hists_ttbar_njet45, lumi, plot_type, plot_style, "rpv_base_ttbar", false, true);  
  plot_distributions(Samples_wjets_njet45, hists_wjets_njet45, lumi, plot_type, plot_style, "rpv_base_wjets", false, true);  

  ////////////////
  // njet67, 8- //
  ////////////////
  vector<TString> njetcuts = {"njets>=6&&njets<=7", "njets>=8"};
  for(auto injet : njetcuts) {
    if(injet=="njets>=6&&njets<=7") {
      Samples_qcd.pop_back();
      Samples_ttbar.pop_back();
      Samples_wjets.pop_back();
      Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=3",		linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm==3)",extraweight)));
      Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}#geq4",		linecolor::c_nb4,   1, cutandweight("stitch_ht*pass*(nbm>=4)",extraweight)));
      Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=3",	linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm==3)",extraweight)));
      Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}#geq4",	linecolor::c_nb4,   1, cutandweight("stitch_ht*pass*(nbm>=4)",extraweight)));
      Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=3",		linecolor::c_nb3,   1, cutandweight("stitch_ht*pass*(nbm==3)",extraweight)));
      Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}#geq4",	linecolor::c_nb4,   1, cutandweight("stitch_ht*pass*(nbm>=4)",extraweight)));
      rpv_sam_qcd.push_back(4);
      rpv_sam_ttbar.push_back(4);
      rpv_sam_wjets.push_back(4);
    }
    cut = basecut + "&&" + injet;
    // Define histograms
    hists_qcd.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_qcd, "M_{J}", cut));
    hists_ttbar.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_ttbar, "M_{J}", cut));
    hists_wjets.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam_wjets, "M_{J}", cut));
  }

  // Make plots
  plot_distributions(Samples_qcd, hists_qcd, lumi, plot_type, plot_style, "rpv_base_qcd", false, true);  
  plot_distributions(Samples_ttbar, hists_ttbar, lumi, plot_type, plot_style, "rpv_base_ttbar", false, true);  
  plot_distributions(Samples_wjets, hists_wjets, lumi, plot_type, plot_style, "rpv_base_wjets", false, true);  
}
