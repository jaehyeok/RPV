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
#include "TLorentzVector.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  TString lumi = "59.8";
  TString plot_type=".pdf";
  TString plot_style="CMSPaper";//"CMSPaper_Preliminary";
}

using namespace std;
using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
    // don't want to include RA4 trigger efficiency
    //std::string extraWeight("w_btag_bf/w_btag");
    std::string extraWeight("1");
    TString trigger = "(trig_ht900 || trig_jet450)";
    //TString trigger = "trig_ht1050";//2017 and 2018

    TString year = argv[1];

    // Reading ntuples
    vector<sfeats> Samples; 
    
    //TString folder_bkg_dy = "/net/cms2/cms2r0/babymaker/babies/2017_01_27/mc/skim_st1000/";
    //TString folder_data_dy = "/net/cms27/cms27r0/babymaker/babies/2017_02_14_ra4_rpv_keep/data/unskimmed/";

    TString folder_bkg = folder_year(year,false).at(0);
    TString folder_dat = folder_year(year,false).at(1);

    vector<TString> s_data_dy    = getRPVProcess(folder_dat, "data");
    vector<TString> s_zjets_dy;    
    s_zjets_dy.push_back(folder_bkg+"*DYJetsToLL_M-50_*.root");
    vector<TString> s_ttlep_dy   = getRPVProcess(folder_bkg,  "ttbar");
    vector<TString> s_wjets_dy   = getRPVProcess(folder_bkg,  "wjets");
    vector<TString> s_vv_dy; 
    s_vv_dy.push_back(folder_bkg+"*_WW_*.root");
    s_vv_dy.push_back(folder_bkg+"*_WZ_*.root");
    s_vv_dy.push_back(folder_bkg+"*_ZZ_*.root");
    vector<TString> s_other_dy;
    s_other_dy.push_back(folder_bkg+"*_ST_*");
    s_other_dy.push_back(folder_bkg+"*_TTTT_*");
    s_other_dy.push_back(folder_bkg+"*_TTWJetsToLNu_*");
    s_other_dy.push_back(folder_bkg+"*_TTWJetsToQQ_*");
    s_other_dy.push_back(folder_bkg+"*_TTZToQQ_*");
    s_other_dy.push_back(folder_bkg+"*_TTZToLLNuNu_*");

    //Samples.push_back(sfeats(s_data_dy, "Data",kBlack,1,"(trig[19] || trig[20] || trig[40] || trig[21] || trig[24] || trig[41]) && json12p9 && pass"));
    //Samples.push_back(sfeats(s_data_dy, "Data",kBlack,1,"(trig[19] || trig[20] || trig[40] || trig[21] || trig[24] || trig[41]) && pass && run<278820"));//(run>=278820&&run<=284044)"));
    Samples.push_back(sfeats(s_data_dy, " Data",kBlack,1,trigger+" && pass"));
    Samples.back().isData = true;
    Samples.back().doStack = false;
    Samples.push_back(sfeats(s_zjets_dy,   " Z+jets",    rpv::c_qcd,   1, cutandweight("pass",extraWeight)));
    Samples.push_back(sfeats(s_ttlep_dy,   " t#bar{t}",  rpv::c_tt,    1, cutandweight("pass&&nleps>=1", extraWeight)));
    Samples.push_back(sfeats(s_wjets_dy,   " W+jets",    rpv::c_wjets, 1, cutandweight("pass&&nleps>=1",extraWeight)));
    Samples.push_back(sfeats(s_vv_dy,      " WW/WZ/ZZ",  ra4::c_ttv,   1, cutandweight("pass",extraWeight)));
    Samples.push_back(sfeats(s_other_dy,   " Other",     rpv::c_other, 1, cutandweight("pass",extraWeight))); 

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
    
    //string mll="(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))";
    string mll="(leps_m*(leps_m>0&&leps_pt[0]>30) && leps_m*(leps_m>0&&leps_pt[1]>30))";
    //string mllcut="(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))>80&&(mumu_m*(mumu_m>0&&mumu_pt1>30)+elel_m*(elel_m>0&&elel_pt1>30))<100";
    string mllcut="(leps_m*(leps_m>0&&leps_pt[0]>30)>80&&(leps_m*(leps_m>0&&leps_pt[0]>30)<100) && leps_m*(leps_m>0&&leps_pt[1]>30)>80&&(leps_m*(leps_m>0&&leps_pt[1]>30)<100))";
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
    vars.push_back(hfeats("njets", 3, 4, 10, dy_sam, "", mllcut+"&&mj12>500&&ht>1200&&njets>=4&&nbm>=1"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
cout<<"4"<<endl;
/*
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4&&nbm==0"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("nbm", 5, -0.5, 4.5, dy_sam, "N_{b}", mllcut+"&&mj12>500&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>500&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>600&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>700&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
    vars.push_back(hfeats("njets", 3, 3.5, 9.5, dy_sam, "N_{jets}", mllcut+"&&mj12>800&&ht>1200&&njets>=4"));
    vars.back().normalize = true; vars.back().whichPlots = "12";
*/
    plot_distributions(Samples, vars, lumi, plot_type, plot_style, "dy", true, false); // last argument determines whether or not a ratio is drawn, and whether or not to show cuts

}
