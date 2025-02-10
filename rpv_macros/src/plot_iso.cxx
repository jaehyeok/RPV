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
#include "TROOT.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {

  bool showData = true; // Draw with/wihout data
  bool unblindSRs = false; // Draw data in (unblind) SRs
  TString json = "1";

  bool makeNm1 = true; // Make only N=1 plots. Does not draw data
  
  TString plot_type=".C";
  TString plot_style="CMSPaper_WorkInProgress";
}

using namespace std;

int main(int argc, char *argv[]){

  int nthreads = 16;
  ROOT::EnableImplicitMT(nthreads);
  TString year;
  TString lumi;
  TString trigger;

  year = argv[1];
  cout << year << endl;
  cout << argc << endl;

  if(year=="UL2016_preVFP"){
    lumi = "19.5";
    trigger = "(trig_ht900 || trig_jet450)";
  }
  else if(year=="UL2016_postVFP"){
    lumi = "16.8";
    trigger = "(trig_ht900 || trig_jet450)";
  }
  else if(year=="UL2017"){
    lumi = "41.5";
    trigger = "trig_ht1050";
  }
  else if(year=="UL2018"){
    lumi = "59.8";
    trigger = "trig_ht1050";
  }


  // ntuple folders
  TString folder_dat = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_data/";
  TString folder_bkg = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_mc/";
  TString folder_sig = "/mnt/data3/babies/250110/"+year+"/merged_qcdfake_sig/";

  /*
  TString folder_bkg = folder_year(year,false).at(0);
  TString folder_dat = folder_year(year,false).at(1);
  TString folder_sig = folder_year(year,false).at(2);
  */
  
  cout<<folder_dat<<endl;

  // Get file lists
  vector<TString> s_data = getRPVProcess(folder_dat,"data");
  vector<TString> s_rpv_m1800 = getRPVProcess(folder_sig,"rpv_m1800");

  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
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
      //Samples.push_back(sfeats(s_data, "Data",kBlack,1,trigger+" && "+json+" && pass && ((nbm==0)||(nbm==1)||(nbm==2))"));
      Samples.push_back(sfeats(s_data, "Data",kBlack,1,trigger+" && "+json+" && pass && (nbm==0)"));
      //Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt, 1, cutandweight("pass","1.")));
      Samples.back().isData = true;
    }
  }

  string extraweight = "1";
  Samples.push_back(sfeats(s_rpv_m1800, "m1800", kRed, 1, cutandweight("pass",extraweight)));
  Samples.back().isSig = true;
  
  Samples.push_back(sfeats(s_qcd,   "QCD", 	rpv::c_qcd, 	1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_wjets, "W+ jets",  rpv::c_wjets, 	1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt, 	1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_other, "Others", 	rpv::c_other, 	1, cutandweight("pass","1.")));// */
												   //
  //Samples.push_back(sfeats(s_qcd,   "QCD", 	rpv::c_qcd, 	1, cutandweight("pass",extraweight)));
  //Samples.push_back(sfeats(s_wjets, "W+ jets",  rpv::c_wjets, 	1, cutandweight("pass",extraweight)));
  //Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt, 	1, cutandweight("pass",extraweight)));
  //Samples.push_back(sfeats(s_other, "Others", 	rpv::c_other, 	1, cutandweight("pass",extraweight)));// */


  // Loop over samples
  vector<int> rpv_sam;
  for(unsigned sam(0); sam < Samples.size(); sam++) rpv_sam.push_back(sam);

  // Define histogram vector
  vector<hfeats> hists;
  vector<hfeats> hists_for_table;
  // Make analysis regions plots
  if(makeNm1==true){
    // Set cuts
    //TString basecut = "mj12>1100&&ht>1200";
    TString basecut = "mj12<500&&ht>1200";
    TString lepcuts = "nleps==1";
    vector<TString> nbcuts = {"nbm==0","nbm==1"};
    vector<TString> njetcuts = {"(njets>=4&&njets<=5)","(njets>=6&&njets<=7)","njets>=8"};//&&njets<=9","njets>=10"};
    //vector<TString> njetcuts = {"njets>=8"};//&&njets<=9","njets>=10"};
    //
    //TString elscutid  = "(els_pt>20&&abs(els_eta)<2.5&&els_miniso<0.1)";
    //TString elscutiso  = "(els_pt>20&&abs(els_eta)<2.5&&els_sigid)";
    //TString muscutid  = "(mus_pt>20&&abs(mus_eta)<2.4&&mus_miniso<0.2)";
    //TString muscutiso  = "(mus_pt>20&&abs(mus_eta)<2.4&&mus_sigid)";
    TString elscutid  = "(els_pt>20&&abs(els_eta)<2.5)";
    TString elscutiso  = "(els_pt>20&&abs(els_eta)<2.5)";
    TString muscutid  = "(mus_pt>20&&abs(mus_eta)<2.4)";
    TString muscutiso  = "(mus_pt>20&&abs(mus_eta)<2.4)";

    // Loop over cuts to make histograms
    TString cut = "";


    /*
    for(auto injet : njetcuts) {
	// for table of ratio of real leptons to fake leptons
	//cut = "mj12<500&&ht>1200&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&(els_pt>20&&abs(els_eta)<2.5&&(els_miniso<0.1&&els_sigid==1)&&met<50)";
	cut = "mj12<500&&ht>1200&&(nbm==0)&&" + injet + "&&(els_pt>20&&abs(els_eta)<2.5&&(els_miniso<0.1&&els_sigid==1)&&met<50)";
    	hists_for_table.push_back(hfeats("mj12", 1, 0, 1, rpv_sam, "real electron", cut));
    	if(showData) hists_for_table.back().normalize = false;

	//cut = "mj12<500&&ht>1200&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&(els_pt>20&&abs(els_eta)<2.5&&(els_miniso>=0.1||els_sigid==0)&&met<50)";
	cut = "mj12<500&&ht>1200&&(nbm==0)&&" + injet + "&&(els_pt>20&&abs(els_eta)<2.5&&(els_miniso>=0.1||els_sigid==0)&&met<50)";
    	hists_for_table.push_back(hfeats("mj12", 1, 0, 1, rpv_sam, "fake electron", cut));
    	if(showData) hists_for_table.back().normalize = false;

	//cut = "mj12<500&&ht>1200&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&(mus_pt>20&&abs(mus_eta)<2.4&&(mus_miniso<0.2&&mus_sigid==1)&&met<50)";
	cut = "mj12<500&&ht>1200&&(nbm==0)&&" + injet + "&&(mus_pt>20&&abs(mus_eta)<2.4&&(mus_miniso<0.2&&mus_sigid==1)&&met<50)";
    	hists_for_table.push_back(hfeats("mj12", 1, 0, 1, rpv_sam, "real muon", cut));
    	if(showData) hists_for_table.back().normalize = false;

	//cut = "mj12<500&&ht>1200&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&(mus_pt>20&&abs(mus_eta)<2.4&&(mus_miniso>=0.2||mus_sigid==0)&&met<50)";
	cut = "mj12<500&&ht>1200&&(nbm==0)&&" + injet + "&&(mus_pt>20&&abs(mus_eta)<2.4&&(mus_miniso>=0.2||mus_sigid==0)&&met<50)";
    	hists_for_table.push_back(hfeats("mj12", 1, 0, 1, rpv_sam, "fake muon", cut));
    	if(showData) hists_for_table.back().normalize = false;

    }
    if(showData) hists_for_table.back().normalize = false;
    plot_distributions(Samples, hists_for_table, lumi, ".pdf", plot_style, "rpv_base", false, false);  
    if(showData) hists_for_table.back().normalize = false;
    */




    for(auto injet : njetcuts){
    	//cut = basecut + "&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&" + elscutid + "&&met<50";
    	cut = basecut + "&&(nbm==0)&&" + injet + "&&" + elscutid + "&&met<50";
	cout<<cut<<endl;
    	hists.push_back(hfeats("els_sigid", 2, 0, 2, rpv_sam, "els_{sigid}"/*"I_{mini}/P_{T}^{els}"* "els_sigid"*/, cut));
    	if(showData) hists.back().normalize = false;
    	//if(showData) hists.back().normalize = true;
	
	// In the first histogram, legend is misplaced. For this reason, the plot above is generated twice.
    	//cut = basecut + "&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&" + elscutid + "&&met<50";
    	cut = basecut + "&&(nbm==0)&&" + injet + "&&" + elscutid + "&&met<50";
	cout<<cut<<endl;
    	hists.push_back(hfeats("els_sigid", 2, 0, 2, rpv_sam, "els_{sigid}"/*"I_{mini}/P_{T}^{els}"* "els_sigid"*/, cut));
    	if(showData) hists.back().normalize = false;
    	//if(showData) hists.back().normalize = true;

    	//cut = basecut + "&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&" + elscutiso + "&&met<50";
    	cut = basecut + "&&(nbm==0)&&" + injet + "&&" + elscutiso + "&&met<50";
	cout<<cut<<endl;
    	hists.push_back(hfeats("els_miniso", 20, 0, 2, rpv_sam, "I_{mini}/P_{T}^{els}"/* "els_sigid"*/, cut));
    	if(showData) hists.back().normalize = false;
    	//if(showData) hists.back().normalize = true;

    	//cut = basecut + "&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&" + muscutid + "&&met<50";
    	cut = basecut + "&&(nbm==0)&&" + injet + "&&" + muscutid + "&&met<50";
	cout<<cut<<endl;
    	hists.push_back(hfeats("mus_sigid", 2, 0, 2, rpv_sam, "mus_{sigid}"/*"I_{mini}/P_{T}^{mus}"* "mus_sigid"*/, cut));
    	if(showData) hists.back().normalize = false;
    	//if(showData) hists.back().normalize = true;

    	//cut = basecut + "&&(nbm==0||nbm==1||nbm==2)&&" + injet + "&&" + muscutiso + "&&met<50";
    	cut = basecut + "&&(nbm==0)&&" + injet + "&&" + muscutiso + "&&met<50";
	cout<<cut<<endl;
    	hists.push_back(hfeats("mus_miniso", 10, 0, 2, rpv_sam, "I_{mini}/P_{T}^{mus}"/* "mus_sigid"*/, cut));
    	if(showData) hists.back().normalize = false;
    	//if(showData) hists.back().normalize = true;

    }
    //plot_distributions(Samples, hists, lumi, ".root", plot_style, "rpv_base", true, true);  
    if(showData) hists.back().normalize = false;
    //if(showData) hists.back().normalize = true;
    plot_distributions(Samples, hists, lumi, ".pdf", plot_style, "rpv_base", true, false);  
    if(showData) hists.back().normalize = false;
    //if(showData) hists.back().normalize = true;
    //if(showData) hists.back().normalize = false;
    /*
      for(auto inb : nbcuts) {
	for(auto injet : njetcuts){
	  ##Skip HERE##
	  // Handle different MJ binning at low njets (CR)
	  if(ilep == "nleps==0&&ht>1500"){
	    if(injet == "njets>=4&&njets<=5" || injet=="njets>=6&&njets<=7"){
	      if(inb == "mj12>800&&mj12<=1000") inb.ReplaceAll("mj12>800&&mj12<=1000","mj12>800");
	      else if(inb == "mj12>1000") continue;
	    }
	  }
	  else if(ilep == "nleps==1&&ht>900"){
	    if(injet == "njets>=4&&njets<=5"){
	      if(inb == "mj12>800&&mj12<=1000") inb.ReplaceAll("mj12>800&&mj12<=1000","mj12>800");
	      else if(inb == "mj12>1000") continue;
	    }
	  }
	  
	    // Handle different njet binning in 1 lep selection
	  i5(ilep == "nleps==1&&ht>900"){
	    if(injet == "njets>=8&&njets<=9") injet.ReplaceAll("njets>=8&&njets<=9","njets>=8");
	    else if(injet == "njets>=10") continue;
	  }
	  ##Skip ends at HERE##
	  // Set cuts
	  cut = lepcuts + "&&" + inb + "&&" + injet + "&&" + basecut;
	  
	  // Define histograms
	  hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cut));
	  //hists.push_back(hfeats("ht", 20, 900, 3000, rpv_sam, "H_{T}", cut));
	  //hists.push_back(hfeats("nbm", 6, 0, 6, rpv_sam, "nbm", cut));
	  //hists.push_back(hfeats("njets", 10, 0, 20, rpv_sam, "njets", cut));
	  if(showData) hists.back().normalize = true;	
	}
      }*/
    
   // plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", true, true);  
  }
  
  /*////////////
    N-1 PLOTS
  /////////// */

  else{
    // Set baseline cuts
    TString lepcutsNm1 = "nleps==1";
    TString htcutsNm1 =  "ht>1200";
    TString mjcutNm1 = "mj12>500";
    TString njetcutNm1 = "njets>=4&&njets<=5";
    TString nbcutNm1 = "nbm==0";

    TString cutNm1 = "";
      // Choose what ht cut to use based on nleps
      cutNm1 = lepcutsNm1 + "&&" + mjcutNm1 + "&&" + njetcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("ht", 40, 900, 3600, rpv_sam, "H_{T}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + njetcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam, "M_{J}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + mjcutNm1 + "&&" + nbcutNm1;
      hists.push_back(hfeats("njets", 10, 0, 20, rpv_sam, "N_{jets}", cutNm1));

      cutNm1 = lepcutsNm1 + "&&" + htcutsNm1 + "&&" + mjcutNm1 + "&&" + njetcutNm1;
      hists.push_back(hfeats("nbm", 6, 0, 6, rpv_sam, "N_{b}", cutNm1));
    
   
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "nminus1", true, true); 
  }
}
