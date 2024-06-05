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
  //TString luminosity="138";
  //TString luminosity="36.3";
  //TString luminosity="41.5";
  //TString luminosity="59.8";
  TString luminosity="101.3";
  //TString luminosity="1.";// when drawing data
  TString plot_type=".pdf";
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
   TString folder_dat_16 = "/mnt/data3/babies/231001/2016/JetHTRun_rpvfitnbge0_step3/";
   vector<TString> s_data_2016 = getRPVProcess(folder_dat_16,"data");

   TString folder_dat_17 = "/mnt/data3/babies/231001/2017/JetHTRun_rpvfitnbge0_step3/";
   vector<TString> s_data_2017 = getRPVProcess(folder_dat_17,"data");

   TString folder_dat_18 = "/mnt/data3/babies/231001/2018/JetHTRun_rpvfitnbge0_step3/";//FIXME
   vector<TString> s_data_2018 = getRPVProcess(folder_dat_18,"data");

   //MC
   TString folder_DY_16 = "/mnt/data3/babies/231001/2016/merged_norm_njets3nleps2/";
   vector<TString> s_DY_2016 = getRPVProcess(folder_DY_16,"DY");

   TString folder_DY_17 = "/mnt/data3/babies/231001/2017/merged_norm_njets3nleps2/";
   vector<TString> s_DY_2017 = getRPVProcess(folder_DY_17,"DY");

   TString folder_DY_18 = "/mnt/data3/babies/231001/2018/merged_norm_njets3nleps2/";
   vector<TString> s_DY_2018 = getRPVProcess(folder_DY_18,"DY");

   TString folder_DY_1718 = "/mnt/data3/babies/231001/20178/merged_norm_njets3nleps2/";
   vector<TString> s_DY_20178 = getRPVProcess(folder_DY_1718,"DY");

   TString folder_bkg_16 = "/mnt/data3/babies/231001/2016/merged_norm_JER_0903/";
   vector<TString> s_qcd_2016 = getRPVProcess(folder_bkg_16,"qcd");
   vector<TString> s_wjets_2016 = getRPVProcess(folder_bkg_16,"wjets");
   vector<TString> s_ttbar_2016 = getRPVProcess(folder_bkg_16,"ttbar");
   vector<TString> s_other_2016 = getRPVProcess(folder_bkg_16,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_2016 = getRPVProcess(folder_bkg_16,"all_bg");

   TString folder_bkg_17 = "/mnt/data3/babies/231001/2017/merged_norm_JER_0903/";
   vector<TString> s_qcd_2017 = getRPVProcess(folder_bkg_17,"qcd");
   vector<TString> s_wjets_2017 = getRPVProcess(folder_bkg_17,"wjets");
   vector<TString> s_ttbar_2017 = getRPVProcess(folder_bkg_17,"ttbar");
   vector<TString> s_other_2017 = getRPVProcess(folder_bkg_17,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_2017 = getRPVProcess(folder_bkg_17,"all_bg");

   TString folder_bkg_18 = "/mnt/data3/babies/231001/2018/merged_norm_JER_0903/";
   vector<TString> s_qcd_2018 = getRPVProcess(folder_bkg_18,"qcd");
   vector<TString> s_wjets_2018 = getRPVProcess(folder_bkg_18,"wjets");
   vector<TString> s_ttbar_2018 = getRPVProcess(folder_bkg_18,"ttbar");
   vector<TString> s_other_2018 = getRPVProcess(folder_bkg_18,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_2018 = getRPVProcess(folder_bkg_18,"all_bg");

   TString folder_bkg_1718 = "/mnt/data3/babies/231001/20178/merged_norm_JER_0903/";
   vector<TString> s_qcd_20178 = getRPVProcess(folder_bkg_1718,"qcd");
   vector<TString> s_wjets_20178 = getRPVProcess(folder_bkg_1718,"wjets");
   vector<TString> s_ttbar_20178 = getRPVProcess(folder_bkg_1718,"ttbar");
   vector<TString> s_other_20178 = getRPVProcess(folder_bkg_1718,"other_public"); //This doesn't include W+jets
   vector<TString> s_all_bg_20178 = getRPVProcess(folder_bkg_1718,"all_bg");

   TString folder_sig_16_1600 = "/mnt/data3/babies/231001/2016/merged_norm_sig_pu/";
   vector<TString> s_rpv_2016_1600 = getRPVProcess(folder_sig_16_1600,"rpv_m1600");
   TString folder_sig_16_1800 = "/mnt/data3/babies/231001/2016/merged_norm_sig_pu/";
   vector<TString> s_rpv_2016_1800 = getRPVProcess(folder_sig_16_1800,"rpv_m1800");
   TString folder_sig_16_2000 = "/mnt/data3/babies/231001/2016/merged_norm_sig_pu/";
   vector<TString> s_rpv_2016_2000 = getRPVProcess(folder_sig_16_2000,"rpv_m2000");

   TString folder_sig_17_1600 = "/mnt/data3/babies/231001/2017/merged_norm_sig_pu/";
   vector<TString> s_rpv_2017_1600 = getRPVProcess(folder_sig_17_1600,"rpv_m1600");
   TString folder_sig_17_1800 = "/mnt/data3/babies/231001/2017/merged_norm_sig_pu/";
   vector<TString> s_rpv_2017_1800 = getRPVProcess(folder_sig_17_1800,"rpv_m1800");
   TString folder_sig_17_2000 = "/mnt/data3/babies/231001/2017/merged_norm_sig_pu/";
   vector<TString> s_rpv_2017_2000 = getRPVProcess(folder_sig_17_2000,"rpv_m2000");

   TString folder_sig_18_1600 = "/mnt/data3/babies/231001/2018/merged_norm_sig_pu/";
   vector<TString> s_rpv_2018_1600 = getRPVProcess(folder_sig_18_1600,"rpv_m1600");
   TString folder_sig_18_1800 = "/mnt/data3/babies/231001/2018/merged_norm_sig_pu/";
   vector<TString> s_rpv_2018_1800 = getRPVProcess(folder_sig_18_1800,"rpv_m1800");
   TString folder_sig_18_2000 = "/mnt/data3/babies/231001/2018/merged_norm_sig_pu/";
   vector<TString> s_rpv_2018_2000 = getRPVProcess(folder_sig_18_2000,"rpv_m2000");

   /*
     if(rpv2017){
    extraWeight = "w_pu_rpv/eff_trig";
    cutandweight("pass",extraWeight)
    csvm = "0.890";
  }
   */


   //2017 MC weight
  std::string extraWeight = "1";

  vector<sfeats> Samples;

  Samples.push_back(sfeats(s_data_2018, "2018 dataAB HEM (1 fb^{-1})", kRed,1,"pass && trig_ht1050 && run<319077 && Sum$((jets_eta>-3.0 && jets_eta<-1.3 && jets_phi>-1.57 && jets_phi <-0.87) && jets_pt>30 && abs(jets_eta)<2.4)==0")); Samples.back().isData=true;
  Samples.push_back(sfeats(s_data_2018, "2018 dataAB (1 fb^{-1})", kBlue,1,"pass && trig_ht1050 && run<319077")); //Samples.back().isData=true;
 // Samples.push_back(sfeats(s_data_2016, "2016 data (1 fb^{-1})", kBlue,1,"trig_ht900 && trig_jet450 && pass")); //Samples.back().isData=true; 
  Samples.back().doBand = true;
  vector<int> data;
  data.push_back(0);
  data.push_back(1);
  
  Samples.push_back(sfeats(s_qcd_2016, "2016 qcd", kRed,1,cutandweight("pass","1."))); Samples.back().mcerr=true; Samples.back().isSig=true;
  Samples.push_back(sfeats(s_qcd_2016, "2016 qcd", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> qcd;
  qcd.push_back(2);
  qcd.push_back(3);

  Samples.push_back(sfeats(s_ttbar_2016, "2016 ttbar", kRed,1,cutandweight("pass","1."))); Samples.back().mcerr=true; Samples.back().isSig=true;
  Samples.push_back(sfeats(s_ttbar_2016, "2016 ttbar", kBlue,1,cutandweight("pass",extraWeight))); 
  //Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar", kBlue,1,cutandweight("pass",extraWeight))); 
  Samples.back().doBand = true;
  vector<int> ttbar;
  ttbar.push_back(4);
  ttbar.push_back(5);
  
  Samples.push_back(sfeats(s_other_2016, "2016 other", kRed,1,cutandweight("pass","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_other_2016, "2016 other", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  vector<int> other;
  other.push_back(6);
  other.push_back(7);
  
  Samples.push_back(sfeats(s_wjets_2016, "2016 W+jets", kRed,1,cutandweight("pass","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_wjets_2016, "2016 W+jets", kBlue,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;
  /*Samples.push_back(sfeats(s_wjets_2018, "2018 W+jets", kNeon,1,cutandweight("pass","1."))); 
  Samples.back().doBand = true;*/
  vector<int> wjets;
  wjets.push_back(8);
  wjets.push_back(9);

  Samples.push_back(sfeats(s_all_bg_2016, "2016 All_Bkg", kRed,1,cutandweight("pass","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_all_bg_2016, "2016 All_Bkg", kBlue,1,cutandweight("pass","1.")));
  Samples.back().doBand = true;
  vector<int> all_bg;
  all_bg.push_back(10);
  all_bg.push_back(11);// */

  Samples.push_back(sfeats(s_rpv_2016_1600, "2016 RPV 1600 pu>30", kRed,1,cutandweight("pass && ntrupv>30","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_rpv_2016_1600, "2016 RPV 1600 pu<20", kBlue,1,cutandweight("pass && ntrupv<20","1.")));
  Samples.back().doBand = true;
  vector<int> sig_1600;
  sig_1600.push_back(12);
  sig_1600.push_back(13);

  Samples.push_back(sfeats(s_rpv_2016_1800, "2016 RPV 1800 pu>30", kRed,1,cutandweight("pass && ntrupv>30","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_rpv_2016_1800, "2016 RPV 1800 pu<20", kBlue,1,cutandweight("pass && ntrupv<20","1.")));
  Samples.back().doBand = true;
  vector<int> sig_1800;
  sig_1800.push_back(14);
  sig_1800.push_back(15);

  Samples.push_back(sfeats(s_rpv_2016_2000, "2016 RPV 2000 pu>30", kRed,1,cutandweight("pass && ntrupv>30","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_rpv_2016_2000, "2016 RPV 2000 pu<20", kBlue,1,cutandweight("pass && ntrupv<20","1.")));
  Samples.back().doBand = true;
  vector<int> sig_2000;
  sig_2000.push_back(16);
  sig_2000.push_back(17);

  //2016
  //Samples.push_back(sfeats(s_wjets_2016, "2016 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=4&&njets<=5)","frac16"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2016, "2016 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=3&&njets<=4)","frac16")));
  //20178
  Samples.push_back(sfeats(s_wjets_20178, "2017+18 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=4&&njets<=5)","frac1718"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_DY_20178, "2017+18 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=3&&njets<=4)","frac1718")));
  //2017
  //Samples.push_back(sfeats(s_wjets_2017, "2017 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=4&&njets<=5)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2017, "2017 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=3&&njets<=4)","1.")));
  //2018
  //Samples.push_back(sfeats(s_wjets_2018, "2018 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=4&&njets<=5)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2018, "2018 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=3&&njets<=4)","1.")));
  Samples.back().doBand = true;
  vector<int> dy_njet_45;
  dy_njet_45.push_back(18);
  dy_njet_45.push_back(19);

  //2016
  //Samples.push_back(sfeats(s_wjets_2016, "2016 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=6&&njets<=7)","frac16"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2016, "2016 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=5&&njets<=6)","frac16")));
  //20178
  Samples.push_back(sfeats(s_wjets_20178, "2017+18 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=6&&njets<=7)","frac1718"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_DY_20178, "2017+18 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=5&&njets<=6)","frac1718")));
  //2017
  //Samples.push_back(sfeats(s_wjets_2017, "2017 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=6&&njets<=7)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2017, "2017 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=5&&njets<=6)","1.")));
  //2018
  //Samples.push_back(sfeats(s_wjets_2018, "2018 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=6&&njets<=7)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2018, "2018 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=5&&njets<=6)","1.")));
  Samples.back().doBand = true;
  vector<int> dy_njet_67;
  dy_njet_67.push_back(20);
  dy_njet_67.push_back(21);

  //2016
  //Samples.push_back(sfeats(s_wjets_2016, "2016 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=8)","frac16"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2016, "2016 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=7)","frac16")));
  //20178
  Samples.push_back(sfeats(s_wjets_20178, "2017+18 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=8)","frac1718"))); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_DY_20178, "2017+18 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=7)","frac1718")));
  //2017
  //Samples.push_back(sfeats(s_wjets_2017, "2017 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=8)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2017, "2017 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=7)","1.")));
  //2018
  //Samples.push_back(sfeats(s_wjets_2018, "2018 W+jets", kGreen+2,1,cutandweight("pass*(nleps==1&&njets>=8)","1."))); Samples.back().mcerr=true;Samples.back().isSig=true;
  //Samples.push_back(sfeats(s_DY_2018, "2018 DYjets", kGray+2,1,cutandweight("pass*(nleps==2&&njets>=7)","1.")));
  Samples.back().doBand = true;
  vector<int> dy_njet_8;
  dy_njet_8.push_back(22);
  dy_njet_8.push_back(23);

  /*
   Samples.push_back(sfeats(s_2016, "Dilepton events", kBlack,1,"nonblind&&((nleps==2&&nbm>=0&&nbm<=2&&njets>=5)||(nleps==1&&nveto==1&&nbm>=1&&nbm<=2&&njets>=6&&mt>140))&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass")); Samples.back().isData=true;
   Samples.push_back(sfeats(s_2016, "Single lepton events, m_{T} < 140", kBlue,1,"nonblind&&nleps==1&&nveto==0&&nbm>=1&&njets>=6&&mt<=140&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass"));   Samples.back().doBand = true;*/
  
  vector<hfeats> vars;
  std::vector<TString> cuts = {"mj12>=500&&ht>1200&&nbm<=2"};
  /*std::vector<TString> cuts = {"mj12>500&&ht>1200&&njets>=4&&njets<=5&&nleps==1",
				"mj12>500&&ht>1200&&njets>=6&&njets<=7&&nleps==1",
				"mj12>500&&ht>1200&&njets>=8&&nleps==1"
			};// */
  /*std::vector<TString> cuts = {"mj12>500&&ht>1200&&njets>=4&&njets<=5",
                                "mj12>500&&ht>1200&&njets>=6&&njets<=7",
                                "mj12>500&&ht>1200&&njets>=8"
			};// */
  /*std::vector<TString> cuts = {"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
				"nbm==2&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
                                "nbm==2&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
                                "nbm==2&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
                                "nbm>=3&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
                                "nbm==3&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
                                "nbm==3&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
                                "nbm>=4&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
                                "nbm>=4&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
	};// */

  /*std::vector<TString> cuts = {"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==0&&mj12>500&&nleps==1&&ht>1200&&8<=njets",
  				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=4&&njets<=5",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&njets>=6&&njets<=7",
				"nbm==1&&mj12>500&&nleps==1&&ht>1200&&8<=njets"
	};// */

  for(auto icut : cuts){
    //vars.push_back(hfeats("nbm", 2, 0, 1, data, "N_{b}", icut,-1,"data"));
    //vars.push_back(hfeats("njets", 8, 4, 12, data, "NJets", icut,-1,"data"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, data, "mj12", icut,-1,"data"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, data, "H_{t}", icut,-1,"data"));//
    vars.back().normalize = true; // */
    //vars.push_back(hfeats("nbm", 6, 0, 6, ttbar, "N_{b}", icut,-1,"ttbar"));
    //vars.push_back(hfeats("njets", 10, 0, 20, ttbar, "NJets", icut,-1,"ttbar"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, ttbar, "mj12", icut,-1,"ttbar"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, ttbar, "H_{t}", icut,-1,"ttbar"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, qcd, "N_{b}", icut,-1,"qcd"));
    //vars.push_back(hfeats("njets", 6, 0, 12, qcd, "NJets", icut,-1,"qcd"));
    //vars.push_back(hfeats("Length$(fjets_pt)", 11, 0, 11, qcd, "FatJets", icut,-1,"qcd"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, qcd, "mj12", icut,-1,"qcd"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, qcd, "H_{t}", icut,-1,"qcd"));// 
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, other, "N_{b}", icut,-1,"other"));
    //vars.push_back(hfeats("njets", 6, 0, 12, other, "NJets", icut,-1,"other"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, other, "mj12", icut,-1,"other"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, other, "H_{t}", icut,-1,"other"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, wjets, "N_{b}", icut,-1,"wjets"));
    //vars.push_back(hfeats("njets", 6, 0, 12, wjets, "NJets", icut,-1,"wjets"));
    /*vars.push_back(hfeats("Length$(fjets_pt)", 10, 0, 10, wjets, "FatJets", icut,-1,"wjets"));
    //vars.push_back(hfeats("mj12", 3, 500, 1400, wjets, "mj12", icut,-1,"wjets"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, wjets, "H_{t}", icut,-1,"wjets"));//
    vars.back().normalize = true;// */
    //vars.push_back(hfeats("nbm", 6, 0, 6, all_bg, "N_{b}", icut,-1,"all_bg"));
    //vars.push_back(hfeats("njets", 9, 0, 18, all_bg, "Njets", icut,-1,"all_bg"));
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, all_bg, "mj12", icut,-1,"all_bg"));
    //vars.push_back(hfeats("ht", 20, 1200, 2600, all_bg, "H_{t}", icut,-1,"all_bg"));
    
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("mj12", 3, 500, 1400, sig_1600, "mj12", icut,-1,"sig_1600"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("ht", 20, 1200, 2600, sig_1600, "H_{t}", icut,-1,"sig_1600"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("njets", 11, 0, 22, sig_1600, "Njets", icut,-1,"sig_1600"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nbm", 4, 0, 4, sig_1600, "N_{b}", icut,-1,"sig_1600"));//
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nleps", 5, 0, 5, sig_1600, "N_{leps}", icut,-1,"sig_1600"));
    vars.back().normalize = true;// */

    /*vars.push_back(hfeats("mj12", 3, 500, 1400, sig_1800, "mj12", icut,-1,"sig_1800"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("ht", 20, 1200, 2600, sig_1800, "H_{t}", icut,-1,"sig_1800"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("njets", 11, 0, 22, sig_1800, "Njets", icut,-1,"sig_1800"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nbm", 4, 0, 4, sig_1800, "N_{b}", icut,-1,"sig_1800"));//
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nleps", 5, 0, 5, sig_1800, "N_{leps}", icut,-1,"sig_1800"));
    vars.back().normalize = true; // */

    /*vars.push_back(hfeats("mj12", 3, 500, 1400, sig_2000, "mj12", icut,-1,"sig_2000"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("ht", 20, 1200, 2600, sig_2000, "H_{t}", icut,-1,"sig_2000"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("njets", 11, 0, 22, sig_2000, "Njets", icut,-1,"sig_2000"));
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nbm", 4, 0, 4, sig_2000, "N_{b}", icut,-1,"sig_2000"));//
    vars.back().normalize = true;// */
    /*vars.push_back(hfeats("nleps", 5, 0, 5, sig_2000, "N_{leps}", icut,-1,"sig_2000"));
    vars.back().normalize = true;// */


    vars.push_back(hfeats("mj12", 3, 500, 1400, dy_njet_45, "M_{J}", icut,-1,"dy_njet_45"));
    vars.back().normalize = true;
    vars.push_back(hfeats("mj12", 3, 500, 1400, dy_njet_67, "M_{J}", icut,-1,"dy_njet_67"));
    vars.back().normalize = true;
    vars.push_back(hfeats("mj12", 3, 500, 1400, dy_njet_8, "M_{J}", icut,-1,"dy_njet_8"));
    vars.back().normalize = true;
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
