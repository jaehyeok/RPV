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
  TString luminosity="1.";
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



  
  //Data
   TString folder_dat_16 = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/data/skim_rpv_st1200/";
   vector<TString> s_data_2016 = getRPVProcess(folder_dat_16,"data");

   vector<TString> s_data_2015;
   s_data_2015.push_back(filestring("JetHT_Run2015C_25ns-05Oct2015-v1"));
   s_data_2015.push_back(filestring("JetHT_Run2015D-05Oct2015-v1"));
   s_data_2015.push_back(filestring("JetHT_Run2015D-PromptReco-v4"));
 
   //MC
   TString folder_bkg_16 = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/mc/skim_rpv_st1200/";
   vector<TString> s_allBG_2016 = getRPVProcess(folder_bkg_16,"all_bg");
   vector<TString> s_ttbar_2016 = getRPVProcess(folder_bkg_16,"ttbar");
   vector<TString> s_qcd_2016 = getRPVProcess(folder_bkg_16,"qcd");
   vector<TString> s_other_2016 = getRPVProcess(folder_bkg_16,"other_public"); //This doesn't include W+jets

   TString folder_bkg_15 = "/net/cms29/cms29r0/cawest/skims/ht1200/";
   vector<TString> s_allBG_2015 = getRPVProcess(folder_bkg_15,"all_bg");
   vector<TString> s_ttbar_2015 = getRPVProcess(folder_bkg_15,"ttbar");
   vector<TString> s_qcd_2015 = getRPVProcess(folder_bkg_15,"qcd");
   vector<TString> s_other_2015 = getRPVProcess(folder_bkg_15,"other_public"); //This doesn't include W+jets

  

   /*
     if(rpv2015){
    extraWeight = "w_pu_rpv/eff_trig";
    cutandweight("stitch&&pass",extraWeight)
    csvm = "0.890";
  }
   */


   //2015 MC weight
   std::string extraWeight = "w_pu_rpv/eff_trig";

  vector<sfeats> Samples;

  Samples.push_back(sfeats(s_data_2016, "2016 data (7.7 fb^{-1})", kBlack,1,"trig[12] && pass && json7p65")); Samples.back().isData=true;
  Samples.push_back(sfeats(s_data_2015, "2015 data (2.7 fb^{-1})", kBlue+2,1,"trig[12] && pass")); //Samples.back().isData=true; //
  Samples.back().doBand = true;
  vector<int> data;
  data.push_back(0);
  data.push_back(1);
  
  Samples.push_back(sfeats(s_qcd_2016, "2016 QCD", kBlack,1,"stitch&&pass")); Samples.back().mcerr=true; Samples.back().isSig=true;
  Samples.push_back(sfeats(s_qcd_2015, "2015 QCD", kBlue+2,1,cutandweight("stitch&&pass",extraWeight))); 
  Samples.back().doBand = true;
  vector<int> qcd;
  qcd.push_back(2);
  qcd.push_back(3);

  Samples.push_back(sfeats(s_ttbar_2016, "2016 ttbar", kBlack,1,"stitch&&pass")); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_ttbar_2015, "2015 ttbar", kBlue+2,1,cutandweight("stitch&&pass",extraWeight))); 
  Samples.back().doBand = true;
  vector<int> ttbar;
  ttbar.push_back(4);
  ttbar.push_back(5);
  
  Samples.push_back(sfeats(s_other_2016, "2016 other", kBlack,1,"stitch&&pass")); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_other_2015, "2015 other", kBlue+2,1,cutandweight("stitch&&pass",extraWeight))); 
  Samples.back().doBand = true;
  vector<int> other;
  other.push_back(6);
  other.push_back(7);
  
  Samples.push_back(sfeats(s_allBG_2016, "2016 all BG", kBlack,1,"stitch&&pass")); Samples.back().mcerr=true;Samples.back().isSig=true;
  Samples.push_back(sfeats(s_allBG_2015, "2015 all BG", kBlue+2,1,cutandweight("stitch&&pass",extraWeight))); 
  Samples.back().doBand = true;
  vector<int> allbg;
  allbg.push_back(8);
  allbg.push_back(9);
  


  /*
   Samples.push_back(sfeats(s_2016, "Dilepton events", kBlack,1,"nonblind&&((nleps==2&&nbm>=0&&nbm<=2&&njets>=5)||(nleps==1&&nveto==1&&nbm>=1&&nbm<=2&&njets>=6&&mt>140))&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass")); Samples.back().isData=true;
   Samples.push_back(sfeats(s_2016, "Single lepton events, m_{T} < 140", kBlue+2,1,"nonblind&&nleps==1&&nveto==0&&nbm>=1&&njets>=6&&mt<=140&&(trig[4]||trig[8]||trig[13]||trig[33])&&pass"));   Samples.back().doBand = true;*/
  


  vector<hfeats> vars;
  std::vector<TString> cuts = {"(nmus+nels)==0&&ht>1500&&njets>=4&&njets<=5","(nmus+nels)==0&&ht>1500&&njets>=6&&njets<=7","(nmus+nels)==1&&ht>1200&&njets>=4&&njets<=5"};
  
  for(auto icut : cuts){
    vars.push_back(hfeats("nbm", 6, 0, 6, data, "N_{b}", icut,-1,"data"));
    vars.back().normalize = true;
    vars.push_back(hfeats("nbm", 6, 0, 6, ttbar, "N_{b}", icut,-1,"ttbar"));
    vars.back().normalize = true;
    vars.push_back(hfeats("nbm", 6, 0, 6, qcd, "N_{b}", icut,-1,"qcd"));
    vars.back().normalize = true;
    vars.push_back(hfeats("nbm", 6, 0, 6, other, "N_{b}", icut,-1,"other"));
    vars.back().normalize = true;
    vars.push_back(hfeats("nbm", 6, 0, 6, allbg, "N_{b}", icut,-1,"allbg"));
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
