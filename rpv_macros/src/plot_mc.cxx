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

int main(int argc, char *argv[]){

  TString year = argv[1];
  if(argc<1){
    cout<<"./run/plot_mc.exe [year] !!!!"<<endl;
  }
  string lumi;
  if(year=="2016") lumi="36.3";
  else if(year=="2017") lumi="41.5";
  else if(year=="2018") lumi="59.7";

  // ntuple folders
  TString folder_bkg = "/data4/babies/210910/"+year+"/merged_norm_JER_0903/";

  // Get file lists
  vector<TString> s_qcd   = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");

  // Reading ntuples
  vector<sfeats> Samples_qcd, Samples_ttbar, Samples_wjets; 
  string extraweight = "1";

  // qcd
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=0", rpv::c_tt,    1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=1", rpv::c_qcd,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}=2", rpv::c_wjets, 1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_qcd.push_back(sfeats(s_qcd, "qcd N_{b}#geq3", rpv::c_other, 1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
  // ttbar
//  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=0", rpv::c_tt,    1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=1", rpv::c_qcd,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=2", rpv::c_wjets, 1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_ttbar.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}#geq3", rpv::c_other, 1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));
  // wjets 
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=0", rpv::c_tt,    1, cutandweight("stitch_ht*pass*(nbm==0)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=1", rpv::c_qcd,   1, cutandweight("stitch_ht*pass*(nbm==1)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}=2", rpv::c_wjets, 1, cutandweight("stitch_ht*pass*(nbm==2)",extraweight)));
  Samples_wjets.push_back(sfeats(s_wjets, "wjets N_{b}#geq3", rpv::c_other, 1, cutandweight("stitch_ht*pass*(nbm>=3)",extraweight)));

  // Loop over samples
  vector<int> rpv_sam_qcd, rpv_sam_ttbar, rpv_sam_wjets;
  for(unsigned sam(0); sam < Samples_qcd.size(); sam++) rpv_sam_qcd.push_back(sam);
  for(unsigned sam(0); sam < Samples_ttbar.size(); sam++) rpv_sam_ttbar.push_back(sam);
  for(unsigned sam(0); sam < Samples_wjets.size(); sam++) rpv_sam_wjets.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists_qcd, hists_ttbar, hists_wjets;

  // Set cuts
  TString basecut = "mj12>=500&&nleps==1&&ht>1200";
  vector<TString> njetcuts = {"njets>=4&&njets<=5", "njets>=6&&njets<=7", "njets>=8"};

  // Loop over cuts to make histograms
  TString cut = "";
  for(auto injet : njetcuts) {
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
