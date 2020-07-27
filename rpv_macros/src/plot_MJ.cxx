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
  TString trigger = "( trig_ht900 || trig_jet450)"; // PFHT800 OR PFHT900 OR PFJet450 */

  /*TString lumi = "41.5";
  TString trigger = "trig_ht1050";// */

  /*TString lumi = "59.7";
  TString trigger = "trig_ht1050";// */
  
  bool showData = true; // Draw with/wihout data
  bool unblindSRs = false; // Draw data in (unblind) SRs
  TString json = "1";

  bool makeNm1 = true; // Make only N=1 plots. Does not draw data
  
  TString plot_type=".png";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;

int main(int argc, char *argv[]){

  TString year;
  year = argv[1];
  cout << argc << endl;
  if(argc < 1){
    cout << "./run/plot_MJ.exe 2016" << endl;
  }

  // ntuple folders
  TString folder_bkg = folder_year(year,false).at(0);
  TString folder_dat = folder_year(year,false).at(1);
  TString folder_sig = folder_year(year,false).at(2);

  // Get file lists
  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1500 = getRPVProcess(folder_sig,"rpv_m1500");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  
  // Reading ntuples
  vector<sfeats> Samples; 
  string extraweight = "1";
  // Plot with data if showData == true
  if(showData) {
    if(unblindSRs){
      Samples.push_back(sfeats(s_data, "Data",kBlack,1,trigger+" && "+json+" && pass"));
      Samples.back().isData = true;
    }
    else{
    //  Samples.push_back(sfeats(s_ttbar, "t#bar{t} nb==2",kRed, 1, "pass&&nbm==2"));
    //  Samples.back().mcerr=true;Samples.back().isSig = true;
    }
  }

  Samples.push_back(sfeats(s_ttbar, "t#bar{t}",kBlue, 1, "pass"));
  Samples.back().isSig = true; Samples.back().mcerr = true;
  Samples.push_back(sfeats(s_ttbar, "t#bar{t} with GS", kRed, 1, "pass&&fromGS"));
  Samples.back().doBand = true;

  /*Samples.push_back(sfeats(s_qcd, "qcd nb==2",kRed, 1, "pass&&nbm==2"));
  Samples.back().isSig = true;
  Samples.push_back(sfeats(s_qcd, "qcd nb>=3", rpv::c_wjets, 1, "pass&&nbm>=3"));
  Samples.back().isSig = true;
  Samples.push_back(sfeats(s_qcd, "qcd nb==0", kBlue, 1, "pass&&nbm==0"));
  Samples.back().isSig = true;
  Samples.push_back(sfeats(s_qcd, "qcd nb==1", rpv::c_other, 1, "pass&&nbm==1"));
  Samples.back().isSig = true;// */

  /*Samples.push_back(sfeats(s_wjets, "wjets nb==2",kRed, 1, "pass&&nbm==2"));
  Samples.push_back(sfeats(s_wjets, "wjets nb>=3", rpv::c_wjets, 1, "pass&&nbm>=3"));
  Samples.push_back(sfeats(s_wjets, "wjets nb==0", kBlue, 1, "pass&&nbm==0"));
  Samples.push_back(sfeats(s_wjets, "wjets nb==1", rpv::c_other, 1, "pass&&nbm==1"));
  Samples.back().isSig = true;// */

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
  if(makeNm1==true){
    // Set cuts
    TString basecut = "mj12>=500";
    TString lepcuts = "nleps==1&&ht>1200";
    vector<TString> nbcuts = {"nbm==0","nbm==1","nbm==2","nbm==3","nbm>=4"};
    //vector<TString> nbcuts = {"nbm>=4"};
    //vector<TString> njetcuts = {"njets>=4&&njets<=5","njets>=6&&njets<=7","njets>=8"};
    vector<TString> njetcuts = {"njets>=4&&njets<=5"};

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
	  //hists.push_back(hfeats("ht", 20, 1200, 2600, rpv_sam, "H_{T}", cut));
	  //hists.push_back(hfeats("nbm", 6, 0, 6, rpv_sam, "nbm", cut));
	  //hists.push_back(hfeats("njets", 9, 0, 18, rpv_sam, "njets", cut));
	  //if(showData) hists.back().normalize = true;	
	}
      }
    
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "plot_MJ", true, true);  
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
