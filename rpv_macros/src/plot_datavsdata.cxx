// plot_dps: Macro that plots variables both for comissioning DPS

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
  //TString luminosity="35.9";
  TString luminosity="41.5";
  //TString luminosity="59.7";
  //TString luminosity="1.";// when drawing data
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;
using std::cout;
using std::endl;

int main(){ 

  TString bfolder("");
  string hostname = execute("echo $HOSTNAME");
  if(Contains(hostname, "cms") || Contains(hostname, "compute-"))  
    bfolder = "/net/cms2"; // In laptops, you can't create a /net folder



   //data
   TString folder_dat_16 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_norm/";
   vector<TString> s_data_2016 = getRPVProcess(folder_dat_16,"data");

   TString folder_dat_17 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2017/merged_norm/";
   vector<TString> s_data_2017 = getRPVProcess(folder_dat_17,"data");

   TString folder_dat_18 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2018/merged_norm/";//FIXME
   //TString folder_dat_18 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2018/processed_0925/";//FIXME
   vector<TString> s_data_2018 = getRPVProcess(folder_dat_18,"data");// */

   //MC
   TString folder_bkg_16 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_norm/";
   vector<TString> s_wjets_2016 = getRPVProcess(folder_bkg_16,"wjets");
   vector<TString> s_ttbar_2016 = getRPVProcess(folder_bkg_16,"ttbar");
   vector<TString> s_qcd_2016 = getRPVProcess(folder_bkg_16,"qcd");
   vector<TString> s_other_2016 = getRPVProcess(folder_bkg_16,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_2016 = getRPVProcess(folder_bkg_16,"all_bg");

   TString folder_bkg_17 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2017/merged_norm/";
   vector<TString> s_wjets_2017 = getRPVProcess(folder_bkg_17,"wjets");
   vector<TString> s_ttbar_2017 = getRPVProcess(folder_bkg_17,"ttbar");
   vector<TString> s_qcd_2017 = getRPVProcess(folder_bkg_17,"qcd");
   vector<TString> s_other_2017 = getRPVProcess(folder_bkg_17,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_2017 = getRPVProcess(folder_bkg_17,"all_bg");

   TString folder_bkg_18 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2018/merged_norm/";
   vector<TString> s_wjets_2018 = getRPVProcess(folder_bkg_18,"wjets");
   vector<TString> s_ttbar_2018 = getRPVProcess(folder_bkg_18,"ttbar");
   vector<TString> s_qcd_2018 = getRPVProcess(folder_bkg_18,"qcd");
   vector<TString> s_other_2018 = getRPVProcess(folder_bkg_18,"other_public"); //This doesn't include W+jets */  
   vector<TString> s_all_bg_2018 = getRPVProcess(folder_bkg_18,"all_bg");

   /*
     if(rpv2017){
    extraWeight = "w_pu_rpv/eff_trig";
    cutandweight("pass",extraWeight)
    csvm = "0.890";
  }
   */


   //2017 MC weight
  std::string extraWeight = "L1Prefiring_Nom";
  //std::string extraWeight = "L1Prefiring_Dn";
  //std::string extraWeight = "L1Prefiring_Up";

  vector<sfeats> Samples;

  Samples.push_back(sfeats(s_data_2018, "2018 data HEM without 15/16 (1 fb^{-1})", kRed,1,"pass && trig_ht1050 && run>=319077 && Sum$((jets_eta>-3.0 && jets_eta<-1.3  && jets_phi>-1.57 && jets_phi <-0.87) && jets_pt>30 && abs(jets_eta)<2.4)==0")); Samples.back().isData=true;
  Samples.push_back(sfeats(s_data_2018, "2018 data HEM (1 fb^{-1})", kBlue,1,"pass && trig_ht1050 && run<319077")); //Samples.back().isData=true;
  //Samples.push_back(sfeats(s_data_2016, "2016 data (1 fb^{-1})", kBlue,1,"trig_ht900 && trig_jet450 && pass")); //Samples.back().isData=true; 
  Samples.back().doBand = true;
  vector<int> data;
  data.push_back(0);
  data.push_back(1);
  
  Samples.push_back(sfeats(s_qcd_2017, "2017 QCD_prefired", kRed,1,cutandweight("pass",extraWeight))); Samples.back().mcerr=true; Samples.back().isSig=true;
  Samples.push_back(sfeats(s_qcd_2017, "2017 QCD", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> qcd;
  qcd.push_back(2);
  qcd.push_back(3);// */

  Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar_prefired", kRed,1,cutandweight("pass",extraWeight))); Samples.back().mcerr=true; Samples.back().isSig=true;
  Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> ttbar;
  ttbar.push_back(4);
  ttbar.push_back(5);
  
  Samples.push_back(sfeats(s_other_2017, "2017 other_prefired", kRed,1,cutandweight("pass",extraWeight))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_other_2017, "2017 other", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> other;
  other.push_back(6);
  other.push_back(7);
  
  Samples.push_back(sfeats(s_wjets_2017, "2017 W+jets_prefired", kRed,1,cutandweight("pass",extraWeight))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_wjets_2017, "2017 W+jets", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> wjets;
  wjets.push_back(8);
  wjets.push_back(9);

  Samples.push_back(sfeats(s_all_bg_2017, "2017 All_Bkg_prefired", kRed,1,cutandweight("pass",extraWeight))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_all_bg_2017, "2017 All_Bkg", kBlue,1,cutandweight("pass","1.")));
  Samples.back().doBand = true;
  vector<int> all_bg;
  all_bg.push_back(10);
  all_bg.push_back(11);// */

  /*
   Samples.push_back(sfeats(s_2016, "Dilepton events", kBlack,1,"nonblind&&((nleps==2&&nbm>=0&&nbm<=2&&njets>=5)||(nleps==1&&nveto==1&&nbm>=1&&nbm<=2&&njets>=6&&mt>140))&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass")); Samples.back().isData=true;
   Samples.push_back(sfeats(s_2016, "Single lepton events, m_{T} < 140", kBlue,1,"nonblind&&nleps==1&&nveto==0&&nbm>=1&&njets>=6&&mt<=140&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass"));   Samples.back().doBand = true;*/
  
  vector<hfeats> vars;
  std::vector<TString> cuts = {"nbm==0&&mj12>500&&nleps==0&&ht>1200&&fabs(jets_eta)>2.2&&fabs(jets_eta)<2.4"};// */
  /*std::vector<TString> cuts = {"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&8<=njets",

	};// */

  for(auto icut : cuts){
    //vars.push_back(hfeats("nbm", 6, 0, 6, data, "N_{b}", icut,-1,"data"));
    //vars.push_back(hfeats("njets", 6, 0, 12, data, "NJets", icut,-1,"data"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, data, "mj12", icut,-1,"data"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, data, "H_{t}", icut,-1,"data"));//
    vars.back().normalize = true; // */
    //vars.push_back(hfeats("nbm", 6, 0, 6, ttbar, "N_{b}", icut,-1,"ttbar"));
    //vars.push_back(hfeats("njets", 10, 0, 20, ttbar, "NJets", icut,-1,"ttbar"));
    //vars.push_back(hfeats("mj12", 3, 500, 1400, ttbar, "mj12", icut,-1,"ttbar"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, ttbar, "H_{t}", icut,-1,"ttbar"));//
    /*vars.push_back(hfeats("jets_pt", 20, 30, 1200, ttbar, "P_{t}", icut,-1,"ttbar"));//
    //vars.push_back(hfeats("jets_eta", 10, -2.4, 2.4, ttbar, "{eta}", icut,-1,"ttbar"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, qcd, "N_{b}", icut,-1,"qcd"));
    //vars.push_back(hfeats("njets", 6, 0, 12, qcd, "NJets", icut,-1,"qcd"));
    //vars.push_back(hfeats("mj12", 3, 500, 1400, qcd, "mj12", icut,-1,"qcd"));
    vars.push_back(hfeats("jets_pt", 20, 30, 1300, qcd, "P_{t}", icut,-1,"qcd"));//
    //vars.push_back(hfeats("ht", 20, 1200, 2600, qcd, "H_{t}", icut,-1,"qcd"));// 
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, other, "N_{b}", icut,-1,"other"));
    //vars.push_back(hfeats("njets", 6, 0, 12, other, "NJets", icut,-1,"other"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, other, "mj12", icut,-1,"other"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, other, "H_{t}", icut,-1,"other"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, wjets, "N_{b}", icut,-1,"wjets"));
    //vars.push_back(hfeats("njets", 6, 0, 12, wjets, "NJets", icut,-1,"wjets"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, wjets, "mj12", icut,-1,"wjets"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, wjets, "H_{t}", icut,-1,"wjets"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, all_bg, "N_{b}", icut,-1,"all_bg"));
    //vars.push_back(hfeats("njets", 9, 0, 18, all_bg, "Njets", icut,-1,"all_bg"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, all_bg, "mj12", icut,-1,"all_bg"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, all_bg, "H_{t}", icut,-1,"all_bg"));
    vars.back().normalize = true;// */
  }


  //  plot_style="CMSPaperNoRatio";
  /*vars.push_back(hfeats("mj14",10,25,775, mj_sam, "M_{J} [GeV]",
			"nleps==1&&ht>500&&met>200&&njets>=6&&nbm>=1&&mt<140",400,"results"));

  vars.push_back(hfeats("mj14",10,25,775, dilep_comp, "M_{J} [GeV]",
			"ht>500&&met>200&&met<500",400,"results"));
  vars.back().normalize=true;
  */
  plot_distributions(Samples, vars, luminosity, plot_type, plot_style, "datavsdata", true, true);
  
}
