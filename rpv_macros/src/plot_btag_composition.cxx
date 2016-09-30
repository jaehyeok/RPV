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
  TString plot_type=".pdf";
  TString plot_style="CMSPaper_Preliminary_normalizeByBin";
}

using namespace std;
using std::cout;
using std::endl;


int main(){

  //Settings
  bool rpv2015 = true;
  bool dominant_bkg_only=false;
  bool do_gs_map=false;


  std::string extraWeight("1");

  TString outDir("composition_maps");

  TString folder_bkg = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/mc/skim_rpv_st1200/";
  string csvm = "0.800";

  if(rpv2015){
    extraWeight = "w_pu_rpv/eff_trig";
    folder_bkg = "/net/cms29/cms29r0/cawest/skims/ht1200/";
    csvm = "0.890";
  }


  vector<TString> s_allBG = getRPVProcess(folder_bkg,"all_bg");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");

  // Reading ntuples
  vector<sfeats> Samples; 

  int nsam;
  Samples.push_back(sfeats(s_allBG, "4 mistags", seq::five, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==4",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "3 mistags",seq::four, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==3",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "2 mistags",seq::three, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==2",extraWeight)));
  Samples.push_back(sfeats(s_allBG, "1 mistag",seq::two, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==1",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "No mistags", seq::one, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==0",extraWeight))); 

  vector<int> rpv_fakes;
  nsam = Samples.size();
  rpv_fakes.push_back(nsam-5);
  rpv_fakes.push_back(nsam-4);
  rpv_fakes.push_back(nsam-3);
  rpv_fakes.push_back(nsam-2);
  rpv_fakes.push_back(nsam-1);

  Samples.push_back(sfeats(s_qcd, "4 mistags", seq::five, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==4",extraWeight))); 
  Samples.push_back(sfeats(s_qcd, "3 mistags",seq::four, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==3",extraWeight))); 
  Samples.push_back(sfeats(s_qcd, "2 mistags",seq::three, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==2",extraWeight)));
  Samples.push_back(sfeats(s_qcd, "1 mistag",seq::two, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==1",extraWeight))); 
  Samples.push_back(sfeats(s_qcd, "No mistags", seq::one, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==0",extraWeight))); 

  vector<int> rpv_fakes_qcd;
  nsam = Samples.size();
  rpv_fakes_qcd.push_back(nsam-5);
  rpv_fakes_qcd.push_back(nsam-4);
  rpv_fakes_qcd.push_back(nsam-3);
  rpv_fakes_qcd.push_back(nsam-2);
  rpv_fakes_qcd.push_back(nsam-1);


  Samples.push_back(sfeats(s_ttbar, "4 mistags", seq::five, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==4",extraWeight))); 
  Samples.push_back(sfeats(s_ttbar, "3 mistags",seq::four, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==3",extraWeight))); 
  Samples.push_back(sfeats(s_ttbar, "2 mistags",seq::three, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==2",extraWeight)));
  Samples.push_back(sfeats(s_ttbar, "1 mistag",seq::two, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==1",extraWeight))); 
  Samples.push_back(sfeats(s_ttbar, "No mistags", seq::one, 1, cutandweight("Sum$(jets_pt>30&&abs(jets_hflavor)!=5&&jets_csv>"+csvm+")==0",extraWeight))); 

  vector<int> rpv_fakes_ttbar;
  nsam = Samples.size();
  rpv_fakes_ttbar.push_back(nsam-5);
  rpv_fakes_ttbar.push_back(nsam-4);
  rpv_fakes_ttbar.push_back(nsam-3);
  rpv_fakes_ttbar.push_back(nsam-2);
  rpv_fakes_ttbar.push_back(nsam-1);


  vector<int> rpv_gs;
  Samples.push_back(sfeats(s_allBG, "GS flag",seq::four, 1, cutandweight("fromGS",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "No GS flag", seq::two, 1, cutandweight("!fromGS",extraWeight))); 
  nsam = Samples.size();
  rpv_gs.push_back(nsam-2);
  rpv_gs.push_back(nsam-1);
  
  vector<int> rpv_gs_qcd;
  Samples.push_back(sfeats(s_qcd, "GS flag",seq::four, 1, cutandweight("fromGS",extraWeight))); 
  Samples.push_back(sfeats(s_qcd, "No GS flag", seq::two, 1, cutandweight("!fromGS",extraWeight))); 
  nsam = Samples.size();
  rpv_gs_qcd.push_back(nsam-2);
  rpv_gs_qcd.push_back(nsam-1);
  
  vector<int> rpv_gs_ttbar;
  Samples.push_back(sfeats(s_ttbar, "GS flag",seq::four, 1, cutandweight("fromGS",extraWeight))); 
  Samples.push_back(sfeats(s_ttbar, "No GS flag", seq::two, 1, cutandweight("!fromGS",extraWeight))); 
  nsam = Samples.size();
  rpv_gs_ttbar.push_back(nsam-2);
  rpv_gs_ttbar.push_back(nsam-1);
  

  //Could organize the same information as function of true btags instead of fakes, like this:
  Samples.push_back(sfeats(s_allBG, "4 true b-tags", 8, 1, cutandweight("Sum$(abs(jets_hflavor)==5&&jets_csv>0.89)==4",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "3 true b-tags", kBlue+1, 1, cutandweight("Sum$(abs(jets_hflavor)==5&&jets_csv>0.89)==3",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "2 true b-tags", kOrange, 1, cutandweight("Sum$(abs(jets_hflavor)==5&&jets_csv>0.89)==2",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "1 true b-tag", kMagenta+2, 1, cutandweight("Sum$(abs(jets_hflavor)==5&&jets_csv>0.89)==1",extraWeight))); 
  Samples.push_back(sfeats(s_allBG, "No true b-tags", kRed+1, 1, cutandweight("Sum$(abs(jets_hflavor)==5&&jets_csv>0.89)==0",extraWeight))); 

  vector<int> rpv_true;
  nsam = Samples.size();
  rpv_true.push_back(nsam-5);
  rpv_true.push_back(nsam-4);
  rpv_true.push_back(nsam-3);
  rpv_true.push_back(nsam-2);
  rpv_true.push_back(nsam-1);


  vector<hfeats> vars;

  std::vector<TString> basecut = {"(nmus+nels)==0", "(nmus+nels)==1"};
  std::vector<TString> mjcuts = {/*"mj<=300", "mj>300&&mj<=500",*/ "mj>500&&mj<=800", "mj>800"};
  std::vector<TString> njetcuts = {"njets>=4&&njets<=5", "njets>=6&&njets<=7","njets>=8&&njets<=9", "njets>=10"};
  TString htcut("ht>1500");

  for(auto ibasecut : basecut) {
    for(auto imjcut : mjcuts) {
      for(auto ijetcut : njetcuts) {

	if(ibasecut=="(nmus+nels)==1") {
	  if(ijetcut.EqualTo("njets>=8&&njets<=9")) continue;
	  ijetcut.ReplaceAll("njets>=10","njets>=8");
	  htcut="ht>1200";
	}
	
	TString cuts = ibasecut + "&&" + htcut + "&&" + ijetcut + "&&" + imjcut;
	  
	if(!do_gs_map){
	  if(!dominant_bkg_only) vars.push_back(hfeats("nbm", 4, 0.5, 4.5, rpv_fakes, "N_{b}", cuts,-1,"fakes"));
	  else{ 
	    if (ibasecut.EqualTo("(nmus+nels)==0")) vars.push_back(hfeats("nbm", 4, 0.5, 4.5, rpv_fakes_qcd, "N_{b}", cuts,-1,"qcd_fakes"));
	    else if (ibasecut.EqualTo("(nmus+nels)==1")) vars.push_back(hfeats("nbm", 4, 0.5, 4.5, rpv_fakes_ttbar, "N_{b}", cuts,-1,"ttbar_fakes"));
	  }
	  vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	}



	else if(do_gs_map){
	  if(!dominant_bkg_only){
	    vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 4, 0.5, 4.5, rpv_gs, "N_{true b-tags}", cuts+"&&nbm==4",-1,"gsvsfakes"));
	    vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	    vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 3, 0.5, 3.5, rpv_gs, "N_{true b-tags}", cuts+"&&nbm==3",-1,"gsvsfakes"));
	    vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	  }
	  else{
	    if(ibasecut.EqualTo("(nmus+nels)==0")){		
	      vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 4, 0.5, 4.5, rpv_gs_qcd, "N_{true b-tags}", cuts+"&&nbm==4",-1,"qcd_gsvsfakes"));
	      vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	      vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 3, 0.5, 3.5, rpv_gs_qcd, "N_{true b-tags}", cuts+"&&nbm==3",-1,"qcd_gsvsfakes"));
	      vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	    }
	    else if(ibasecut.EqualTo("(nmus+nels)==1")){		
	      vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 4, 0.5, 4.5, rpv_gs_ttbar, "N_{true b-tags}", cuts+"&&nbm==4",-1,"ttbar_gsvsfakes"));
	      vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	      vars.push_back(hfeats("Sum$(jets_pt>30&&abs(jets_hflavor)==5&&jets_csv>"+csvm+")", 3, 0.5, 3.5, rpv_gs_ttbar, "N_{true b-tags}", cuts+"&&nbm==3",-1,"ttbar_gsvsfakes"));
	      vars.back().normalizeByBin=true; vars.back().whichPlots="2";
	    }
	  }
	}

	//vars.push_back(hfeats("nbm", 4, 0.5, 4.5, rpv_true, "N_{b}", cuts,-1,"true"));
	//vars.back().normalizeByBin=true; vars.back().whichPlots="2";


      }
    }
  }
  plot_distributions(Samples, vars, rpv::luminosity, plot_type, plot_style, outDir, false,false); // last argument determines whether or not a ratio is drawn

}

