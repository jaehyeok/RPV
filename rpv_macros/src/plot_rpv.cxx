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

  bool showData = true; // Draw with/wihout data
  bool unblindSRs = true; // Draw data in (unblind) SRs
  TString json = "1";

  bool makeNm1 = true; // Make only N=1 plots. Does not draw data
  
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;

int main(int argc, char *argv[]){

  TString year;

  TString lumi = "35.9";
  TString trigger = "( trig_ht900 || trig_jet450)"; // PFHT800 OR PFHT900 OR PFJet450 */

  /*TString lumi = "41.5";
  TString trigger = "trig_ht1050";// */

  /*TString lumi = "59.7";
  TString trigger = "trig_ht1050";// */

  year = argv[1];
  cout << argc << endl;
  if(argc<1){
    cout<<"./run/plot_rpv [year] !!!!"<<endl;
  }
 // cout << "./run/plot_rpv.exe [year]" << endl;
  /*if(year == 2016){
  //  lumi = 35.9;
  //  trigger = "(trig_ht900 || trig_jet450)";
  }

  else if(year == 2017){
  //  lumi = 41.5;
  //  trigger = "trig_ht1050";
  }

  else if(year == 2018){
   // lumi = 59.7;
   //trigger = "trig_ht1050";
  }// */

  //cout << trigger << ": trigger"  << endl;

  // ntuple folders

  /*TString folder_dat = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/"; //FIXME
  TString folder_bkg = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/";
  TString folder_sig = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/";// */

  TString folder_bkg = folder_year(year,false).at(0);
  TString folder_dat = folder_year(year,false).at(1);
  TString folder_sig = folder_year(year,false).at(2);// */

  // Get file lists
  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1600 = getRPVProcess(folder_sig,"rpv_m1600");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");
  vector<TString> s_mStop_400 = getRPVProcess(folder_sig,"mStop-400");
  vector<TString> s_mStop_700 = getRPVProcess(folder_sig,"mStop-700");
  vector<TString> s_mStop_1100 = getRPVProcess(folder_sig,"mStop-1100");
  vector<TString> s_mStop_1400 = getRPVProcess(folder_sig,"mStop-1400");

  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");// */
  
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
  //Samples.push_back(sfeats(s_rpv_m1600, "m1600", kRed, 1, cutandweight("pass",extraweight)));
  //Samples.back().isSig = true;
  
  Samples.push_back(sfeats(s_qcd, "QCD", rpv::c_qcd, 1, cutandweight("pass",extraweight)));
  Samples.push_back(sfeats(s_wjets, "W+ jets", rpv::c_wjets, 1, cutandweight("pass",extraweight)));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt, 1, cutandweight("pass",extraweight)));
  Samples.push_back(sfeats(s_mStop_400, "mStop_400", kRed, 1, cutandweight("pass",extraweight)));Samples.back().isSig = true;
  Samples.push_back(sfeats(s_mStop_700, "mStop_700", kRed+1, 1, cutandweight("pass",extraweight)));Samples.back().isSig = true;
  Samples.push_back(sfeats(s_mStop_1100, "mStop_1100", kRed-1, 1, cutandweight("pass",extraweight)));Samples.back().isSig = true;
  Samples.push_back(sfeats(s_mStop_1400, "mStop_1400", kRed-2, 1, cutandweight("pass",extraweight)));Samples.back().isSig = true;// */
  Samples.push_back(sfeats(s_other, "Others", rpv::c_other, 1, cutandweight("pass",extraweight)));// */

  // Loop over samples
  vector<int> rpv_sam;
  for(unsigned sam(0); sam < Samples.size(); sam++) rpv_sam.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists;
  // Make analysis regions plots
  if(makeNm1==true){
    // Set cuts
    TString basecut = "mj12>=500";
    TString lepcuts = "nleps==1&&ht>1200";
    vector<TString> nbcuts = {"nbm==0","nbm==1"};
    //vector<TString> njetcuts = {"4<=njets&&njets<=5","6<=njets&&njets<=7","8<=njets"};
    vector<TString> njetcuts = {"0<=njets&&njets<=20"};

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
	  //hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cut));
	  //hists.push_back(hfeats("ht", 20, 1200, 3000, rpv_sam, "H_{T}", cut));
	  //hists.push_back(hfeats("nbm", 6, 0, 6, rpv_sam, "nbm", cut));
	  hists.push_back(hfeats("njets", 10, 0, 20, rpv_sam, "njets", cut));
	  //if(showData) hists.back().normalize = true;	
	}
      }
    
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", true, true);  
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
