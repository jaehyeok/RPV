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
  TString lumi = "35.9"; //FIXME
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;

int main(int argc, char *argv[]){

  TString year = argv[1];
  if(argc<1){
    cout<<"./run/plot_mc.exe [year] !!!!"<<endl;
  }

  // ntuple folders
  TString folder_bkg = "/data4/babies/210910/"+year+"/merged_norm_JER_0903/";

  // Get file lists
  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd   = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");

  // Reading ntuples
  vector<sfeats> Samples; 
  string extraweight = "1";
  Samples.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=0", rpv::c_tt,    1, cutandweight("pass*(nbm==0)",extraweight)));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=1", rpv::c_qcd,   1, cutandweight("pass*(nbm==1)",extraweight)));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}=2", rpv::c_wjets, 1, cutandweight("pass*(nbm==2)",extraweight)));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t} N_{b}#ge3", rpv::c_wjets, 1, cutandweight("pass*(nbm>=3)",extraweight)));

  // Loop over samples
  vector<int> rpv_sam;
  for(unsigned sam(0); sam < Samples.size(); sam++) rpv_sam.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists;

  // Set cuts
  TString basecut = "mj12>=500&&nleps==1&&ht>1200";
  vector<TString> njetcuts = {"njets>=4&&njets<=5", "njets>=6&&njets<=7", "njets>=8"};

  // Loop over cuts to make histograms
  TString cut = "";
  for(auto injet : njetcuts){
    // Set cuts
    cut = basecut + "&&" + injet;
    // Define histograms
    hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cut));
  }

  plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", false, true);  
}
