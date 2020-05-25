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
  TString lumi = "35.9";
  
  bool showData = true; // Draw with/wihout data
  bool unblindSRs = false; // Draw data in (unblind) SRs
  TString json = "1";
  TString trigger = "( trig_ht900 || trig_jet450)"; // PFHT800 OR PFHT900 OR PFJet450

  bool makeNm1 = false; // Make only N=1 plots. Does not draw data
  
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;

int main(){

  // ntuple folders
  //TString folder_dat = "/net/cms29/cms29r0/babymaker/babies/2017_01_27/data/merged_rpvdata_st1000/";
  //TString folder_bkg = "/net/cms29/cms29r0/babymaker/babies/2017_01_27/mc/merged_rpvmc_rpvregion/";
  //TString folder_sig = "/net/cms2/cms2r0/jaehyeokyoo/babies/2017_01_10/mc/T1tbs/";
  TString folder_dat = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_rpvfitnbge0_sys_v1-1/";
  TString folder_bkg = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_rpvfitnbge0_sys_v1-1/";
  TString folder_sig = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_rpvfitnbge0_sys_v1-1/";

  // Get file lists
  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1500 = getRPVProcess(folder_sig,"rpv_m1500");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

  //vector<TString> s_tt1l = getRPVProcess(folder_bkg,"ttbar_1l");
  //vector<TString> s_tt2l = getRPVProcess(folder_bkg,"ttbar_2l");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  //vector<TString> s_singlet = getRPVProcess(folder_bkg,"singlet");
  //vector<TString> s_zjets = getRPVProcess(folder_bkg,"zjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  
  // Reading ntuples
  vector<sfeats> Samples; 
  // Plot with data if showData == true
  if(showData) {
    if(unblindSRs){
      Samples.push_back(sfeats(s_data, "Data",kBlack,1,trigger+" && "+json+" && pass"));
      Samples.back().isData = true;
    }
    else{
      // Only use events with njets<=7 (for 0-lepton) and njets<=5 (for 1-lepton)
      Samples.push_back(sfeats(s_data, "Data",kBlack,1,trigger+" && "+json+" && pass && ((nbm==0)||(nbm==1)||(nbm>=2 && njets>=4 && njets<=5))"));
      Samples.back().isData = true;
    }
  }

  string extraweight = "1";
  Samples.push_back(sfeats(s_qcd, "QCD", rpv::c_qcd, 1, cutandweight("1&&pass",extraweight)));
  Samples.push_back(sfeats(s_wjets, "W+ jets", rpv::c_wjets, 1, cutandweight("1&&pass",extraweight)));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt, 1, cutandweight("1&&pass",extraweight)));
  Samples.push_back(sfeats(s_other, "Others", rpv::c_other, 1, cutandweight("1&&pass",extraweight)));
  /*
  Samples.push_back(sfeats(s_wjets, "W+jets, 0 l", ra4::c_wjets, 1, cutandweight("1&&pass&&nleps==0",extraweight)));
  Samples.push_back(sfeats(s_zjets, "Z+jets, 0 l", kBlack, 1, cutandweight("1&&pass",extraweight)));
  Samples.push_back(sfeats(s_tt1l, "t#bar{t}, 1 l", ra4::c_tt_1l, 1, cutandweight("1&&pass&&nleps==1",extraweight)));
  Samples.push_back(sfeats(s_tt2l, "t#bar{t}, 2 l", ra4::c_tt_2l, 1, cutandweight("1&&pass&&nleps==2",extraweight)));
  Samples.push_back(sfeats(s_tthad, "t#bar{t}, 0 l", kTeal, 1, cutandweight("1&&pass&&nleps==0",extraweight)));
  Samples.push_back(sfeats(s_wjets, "W+jets, 1 l", ra4::c_wjets, 1, cutandweight("1&&pass&&nleps==1",extraweight)));
  Samples.push_back(sfeats(s_singlet, "Single t", ra4::c_singlet, 1, cutandweight("1&&pass",extraweight)));
  Samples.push_back(sfeats(s_other, "Other", ra4::c_other, 1, cutandweight("1&&pass",extraweight)));
  */
  // Loop over samples
  vector<int> rpv_sam;
  for(unsigned sam(0); sam < Samples.size(); sam++) rpv_sam.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists;

  // Make analysis regions plots
  if(!makeNm1){
    // Set cuts
    TString basecut = "mj12>=500";
    //vector<TString> lepcuts = {"nleps==0&&ht>1500", "nleps==1&&ht>1200"};
    TString lepcuts = "nleps==1&&ht>1200";
    vector<TString> nbcuts = {"nbm==0","nbm==1"};
    vector<TString> njetcuts = {"njets>=4&&njets<=5", "njets>=6&&njets<=7", "njets>=8"};

    // Loop over cuts to make histograms
    TString cut = "";
      for(auto inb : nbcuts) {
	for(auto injet : njetcuts){
	  /*
	  // Handle different MJ binning at low njets (CR)
	  if(ilep == "nleps==0&&ht>1500"){
	    if(injet == "njets>=4&&njets<=5" || injet=="njets>=6&&njets<=7"){
	      if(inb == "mj12>800&&mj12<=1000") inb.ReplaceAll("mj12>800&&mj12<=1000","mj12>800");
	      else if(inb == "mj12>1000") continue;
	    }
	  }
	  else if(ilep == "nleps==1&&ht>1200"){
	    if(injet == "njets>=4&&njets<=5"){
	      if(inb == "mj12>800&&mj12<=1000") inb.ReplaceAll("mj12>800&&mj12<=1000","mj12>800");
	      else if(inb == "mj12>1000") continue;
	    }
	  }
	  
	    // Handle different njet binning in 1 lep selection
	  if(ilep == "nleps==1&&ht>1200"){
	    if(injet == "njets>=8&&njets<=9") injet.ReplaceAll("njets>=8&&njets<=9","njets>=8");
	    else if(injet == "njets>=10") continue;
	  }
	  */
	  // Set cuts
	  cut = lepcuts + "&&" + inb + "&&" + injet + "&&" + basecut;
	  
	  // Define histograms
	  hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cut));
	  if(showData) hists.back().normalize = true;	
	}
      }
    
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", showData, true);  
  }
  
  /*////////////
    N-1 PLOTS
  /////////// */

  else{
    // Set baseline cuts
    TString lepcutsNm1 = "nleps==1";
    TString htcutsNm1 =  "ht>1200";
    TString mjcutNm1 = "mj12>500";
    TString njetcutNm1 = "njets>=4";
    TString nbcutNm1 = "nbm>=1";

    TString cutNm1 = "";
      // Choose what ht cut to use based on nleps
      cutNm1 = lepcutsNm1 + "&&" + mjcutNm1 + "&&" + njetcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("ht", 40, 0, 4000, rpv_sam, "H_{T}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + njetcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + mjcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("njets", 12, 0, 12, rpv_sam, "N_{jets}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + mjcutNm1 + "&&" + njetcutNm1;
      hists.push_back(hfeats("nbm", 5, 0, 5, rpv_sam, "N_{b}", cutNm1));
    
    
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "nminus1", true, true); 
  }
}
