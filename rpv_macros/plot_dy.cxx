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
  TString lumi = /*"12.9";*/"36.4";
  TString plot_type=".root";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;
using std::cout;
using std::endl;


int main(){
    
    // don't want to include RA4 trigger efficiency
    std::string extraWeight("1");

    // Reading ntuples
    vector<sfeats> Samples; 
    
    TString folder_bkg_dy   = "/xrootd_user/jaehyeok/xrootd/ucsb_babies/2017_01_27/mc/merged_rpvmc_rpvfit/";
    TString folder_data_dy  = "/xrootd_user/jaehyeok/xrootd/ucsb_babies/2017_02_14/data/merged_rpvdata_st1000/";
    
    vector<TString> s_data_dy    = getRPVProcess(folder_data_dy, "data");
    vector<TString> s_zjets_dy;    
    s_zjets_dy.push_back(folder_bkg_dy+"*DYJetsToLL_M-50_*.root");
    vector<TString> s_ttlep_dy   = getRPVProcess(folder_bkg_dy,  "ttbar");
    vector<TString> s_wjets_dy   = getRPVProcess(folder_bkg_dy,  "wjets");
    vector<TString> s_vv_dy; 
    s_vv_dy.push_back(folder_bkg_dy+"*_WWTo2L2Nu_13TeV_*.root");
    s_vv_dy.push_back(folder_bkg_dy+"*_WZTo3LNu_TuneCUETP8M1_13TeV_*.root");
    s_vv_dy.push_back(folder_bkg_dy+"*_WZTo2L2Q_13TeV_*.root");
    s_vv_dy.push_back(folder_bkg_dy+"*_ZZTo2L2Q_13TeV_*.root");
    vector<TString> s_other_dy;
    s_other_dy.push_back(folder_bkg_dy+"*_ST_*");
    s_other_dy.push_back(folder_bkg_dy+"*_ttHJetTobb_*");
    s_other_dy.push_back(folder_bkg_dy+"*_TTTT_*");
    s_other_dy.push_back(folder_bkg_dy+"*_TTWJetsToLNu_*");
    s_other_dy.push_back(folder_bkg_dy+"*_TTWJetsToQQ_*");
    s_other_dy.push_back(folder_bkg_dy+"*_TTZToQQ_*");
    s_other_dy.push_back(folder_bkg_dy+"*_TTZToLLNuNu_*");


    Samples.push_back(sfeats(s_data_dy, "Data",kBlack,1,"(trig[19] || trig[20] || trig[40] || trig[21] || trig[24] || trig[41]) && json12p9 && pass"));
    //Samples.push_back(sfeats(s_data_dy, "Data",kBlack,1,"(trig[19] || trig[20] || trig[40] || trig[21] || trig[24] || trig[41]) && pass"));
    Samples.back().isData = true;
    Samples.back().doStack = false;
    Samples.push_back(sfeats(s_zjets_dy,   "Z+jets",    rpv::c_qcd,   1, cutandweight("1",extraWeight)));
    Samples.push_back(sfeats(s_ttlep_dy,   "t#bar{t}",  rpv::c_tt,    1, cutandweight("1", extraWeight)));
    Samples.push_back(sfeats(s_wjets_dy,   "W+jets",    rpv::c_wjets, 1, cutandweight("1",extraWeight)));
    Samples.push_back(sfeats(s_vv_dy,      "WW/WZ/ZZ",  ra4::c_ttv,   1, cutandweight("1",extraWeight)));
    Samples.push_back(sfeats(s_other_dy,   "Other",     rpv::c_other, 1, cutandweight("1",extraWeight))); 

    vector<int> dy_sam;
    unsigned nsam_dy(Samples.size());
    for(unsigned sam(0); sam < nsam_dy; sam++){
        dy_sam.push_back(sam);
        vector<TString> sam_files = Samples[sam].file;
        Samples.push_back(sfeats(sam_files, Samples[sam].label, Samples[sam].color, Samples[sam].style,
                    Samples[sam].cut));
    }  

    //
    //
    // 

    vector<hfeats> vars;
   
    string mll="(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))";
    string mllcut="(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))>80&&(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))<100";
/*    
    vars.push_back(hfeats(mll, 40, 80, 100, dy_sam, "m_{ll} [GeV]", mllcut)); 
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats(mll, 40, 80, 100, dy_sam, "m_{ee} [GeV]", mllcut+"&&nels==2&&nmus==0")); 
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats(mll, 40, 80, 100, dy_sam, "m_{#mu#mu} [GeV]", mllcut+"&&nels==0&&nmus==2")); 
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats(mll, 40, 80, 100, dy_sam, "m_{ll} [GeV]", mllcut+"&&ht>500"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>500"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>700"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>900"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1100"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1100&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 15, -0.5, 14.5, dy_sam, "N_{jets}", mllcut+"&&mj12>800&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
*/
    vars.push_back(hfeats("nbm", 5, -0.5, 4.5, dy_sam, "N_{b}", mllcut+"&&mj12>500&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4&&nbm>=1"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4&&nbm==0"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
/*
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>600&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>700&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>800&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
*/
    plot_distributions(Samples, vars, lumi, plot_type, plot_style, "dy", true, true); // last argument determines whether or not a ratio is drawn, and whether or not to show cuts

}
