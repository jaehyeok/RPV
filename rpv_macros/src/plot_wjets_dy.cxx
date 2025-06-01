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
#include "TLorentzVector.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLatex.h"
#include "THStack.h"
#include "TGaxis.h"

#include "small_tree_rpv.hpp"
#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;


void appendTree(vector<TString> s_process, small_tree &tree_in);
void pass_dy_selection(small_tree_rpv &tree, TH1D* h, TString datamc, TString njets, TString year, TString mjORnjets);

void compare_shape_wjets_dy(TString year);      // Fig. 17
void wjets_kappa_plot_dy_region(TString year);  // Fig. 18
void comp_njets_dy_data(TString year);          // Fig. 31


void appendTree(vector<TString> s_process, small_tree &tree_in)
{
  cout << "flist of s_process: " << s_process.at(0) << endl;
  if(s_process.size()>1) {
    for(int i=1; i<s_process.size(); i++) {
      tree_in.Add((static_cast<std::string>(s_process.at(i))));
      cout << "       " << s_process.at(i) << " is appended" << endl;
    }
  }
  cout << endl;
}

void pass_dy_selection(small_tree_rpv &tree, TH1D* h, TString datamc, TString njets, TString year, TString mjORnjets)
{
  gErrorIgnoreLevel = kError+1;

  double lumi;
  TString lumi_title, trigger;
  if(year=="UL2016_preVFP") 	  {lumi=19.5;  trigger="(trig_jet450 || trig_ht900)";}
  else if(year=="UL2016_postVFP") {lumi=16.8;  trigger="(trig_jet450 || trig_ht900)";}
  else if(year=="UL2017")         {lumi=41.5;  trigger="trig_ht1050";}
  else if(year=="UL2018")  	  {lumi=59.8;  trigger="trig_ht1050";}
  else if(year=="UL2016_comb") 	  {lumi=36.3;  trigger="(trig_jet450 || trig_ht900";}
  else if(year=="UL20178_comb")	  {lumi=101.3; trigger="trig_ht1050";}
  else {cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018/UL2016_comb/UL20178_comb" << endl;}

  for(unsigned int ievt=0; ievt<tree.GetEntries(); ievt++) {
    tree.GetEntry(ievt);
    float mll=0;
    float mass=0;
    TLorentzVector mom1, mom2;

    // baseline selection
    if(tree.stitch_ht()==0) continue;
    if(tree.nleps()!=2) continue;
    if(tree.nbm()>2) continue;
    if(tree.njets()<3) continue;
    if(tree.ht()<1200) continue;
    if(tree.mj12()<500) continue;
    if(tree.pass()!=1) continue;
    if(tree.mj12()>=1400) tree.mj12()=1399.99; // to consider overflow
    if(tree.njets()>=9)   tree.njets()=8.99;   // to consider overflow
  
    // cut for OSSF and mll
    if(tree.leps_pdgid().at(0)*tree.leps_pdgid().at(1)==-121) mass = 0.510*0.001;
    else if(tree.leps_pdgid().at(0)*tree.leps_pdgid().at(1)==-169) mass = 105.66*0.001;
    else continue;

    mom1.SetPtEtaPhiM(tree.leps_pt().at(0), tree.leps_eta().at(0), tree.leps_phi().at(0), mass);
    mom2.SetPtEtaPhiM(tree.leps_pt().at(1), tree.leps_eta().at(1), tree.leps_phi().at(1), mass);
    TLorentzVector momtot = mom1+mom2;
    mll = momtot.M();
    if(mll<81 || mll>101) continue;


    // Fill histogram
    if(mjORnjets=="mj") { // For mj distribution - Fig. 18
      if(year=="UL2016_comb") {
        if(njets=="34") {
  	  if(datamc=="data") {
	    if(tree.njets()>=3 && tree.njets()<=4 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
	    if(tree.njets()>=3 && tree.njets()<=4) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="56") {
	  if(datamc=="data") {
            if(tree.njets()>=5 && tree.njets()<=6 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=5 && tree.njets()<=6) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="7") {
	  if(datamc=="data") {
	    if(tree.njets()>=7 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
	    if(tree.njets()>=7) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else cout << "input njets as 34/56/7" << endl;
      }
      else if(year=="UL20178_comb") {
        if(njets=="34") {
	  if(datamc=="data") {
            if(tree.njets()>=3 && tree.njets()<=4 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=3 && tree.njets()<=4) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="56") {
	  if(datamc=="data") {
            if(tree.njets()>=5 && tree.njets()<=6 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=5 && tree.njets()<=6) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="7") {
	  if(datamc=="data") {
            if(tree.njets()>=7 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=7) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else cout << "input njets as 34/56/7" << endl;
      }
      else {
        if(njets=="34") {
	  if(datamc=="data") {
            if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
	      if(tree.njets()>=3 && tree.njets()<=4 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	    }
	    else if(year=="UL2017" || year=="UL2018") {
	      if(tree.njets()>=3 && tree.njets()<=4 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	    }
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=3 && tree.njets()<=4) h->Fill(tree.mj12(), lumi*tree.weight());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="56") {
	  if(datamc=="data") {
	    if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
              if(tree.njets()>=5 && tree.njets()<=6 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	    }
	    else if(year=="UL2017" || year=="UL2018") {
              if(tree.njets()>=5 && tree.njets()<=6 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	    }
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=5 && tree.njets()<=6) h->Fill(tree.mj12(), lumi*tree.weight());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else if(njets=="7") {
  	  if(datamc=="data") {
	    if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
              if(tree.njets()>=7 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
	    }
	    else if(year=="UL2017" || year=="UL2018") {
	      if(tree.njets()>=7 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
	    }
	  }
	  else if(datamc=="mc") {
            if(tree.njets()>=7) h->Fill(tree.mj12(), lumi*tree.weight());
	  }
	  else cout << "input datamc as data/mc" << endl;
        }
        else cout << "input njets as 34/56/7" << endl;
      }
    }
    else if(mjORnjets=="njets") { // For njets distribution - Fig. 31
      if(year=="UL2016_comb") {
	if(datamc=="data") {
	  if(tree.trig_jet450()||tree.trig_ht900()) {
	    h->Fill(tree.njets(), 1);
	  }
	}
	else if(datamc=="mc") h->Fill(tree.njets(), lumi*tree.weight()*tree.frac16());
      }
      else if(year=="UL20178_comb") {
	if(datamc=="data") {
	  if(tree.trig_ht1050()) {
	    h->Fill(tree.njets(), 1);
	  }
	}
	else if(datamc=="mc") h->Fill(tree.njets(), lumi*tree.weight()*tree.frac1718());
      }
      else {
	if(datamc=="data") {
	  if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
	    if(tree.trig_jet450()||tree.trig_ht900()) {
	      h->Fill(tree.njets(), 1);
	    }
	  }
	  else if(year=="UL2017" || year=="UL2018") {
	    if(tree.trig_ht1050()) {
	      h->Fill(tree.njets(), 1);
	    }
	  }
	}
	else if(datamc=="mc") h->Fill(tree.njets(), lumi*tree.weight());
      }
    }

  } // end event loop
}

void compare_shape_wjets_dy(TString year)
{
  gErrorIgnoreLevel = kError+1;
  TH1::SetDefaultSumw2();

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  styles style("CMSPaper");
  style.LabelSize    *= 1.1;
  style.LegendSize   *= 1.0;
  style.TitleSize    *= 1.1;
  style.yTitleOffset /= 1.3;
  style.xTitleOffset /= 1.08;

  double lumi;
  TString lumi_title;
  if(year=="UL2016_preVFP") 	  {lumi=19.5;  lumi_title="19p5";}
  else if(year=="UL2016_postVFP") {lumi=16.8;  lumi_title="16p8";}
  else if(year=="UL2017")         {lumi=41.5;  lumi_title="41p5";}
  else if(year=="UL2018")  	  {lumi=59.8;  lumi_title="59p8";}
  else if(year=="UL2016_comb") 	  {lumi=36.3;  lumi_title="36p3";}
  else if(year=="UL20178_comb")	  {lumi=101.3; lumi_title="101p3";}
  else {cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018/UL2016_comb/UL20178_comb" << endl;}

  TString folder_wjets   = folder_year(year, false).at(0);
  TString folder_dy_mc   = folder_year(year, false).at(3);

  vector<TString> s_wjets   = getRPVProcess(folder_wjets,   "wjets");
  vector<TString> s_dy_mc   = getRPVProcess(folder_dy_mc,   "DY");

  // make small tree
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_dy((static_cast<std::string>(s_dy_mc.at(0))));

  // define histogram
  TH1D* h_wjets_njets45 = new TH1D("h_wjets_njets45", "h_wjets_njets45", 3, 500, 1400);
  TH1D* h_wjets_njets67 = new TH1D("h_wjets_njets67", "h_wjets_njets67", 3, 500, 1400);
  TH1D* h_wjets_njets8 	= new TH1D("h_wjets_njets8",  "h_wjets_njets8",  3, 500, 1400);
  TH1D* h_dy_njets34 	= new TH1D("h_dy_njets34",    "h_dy_njets34",    3, 500, 1400);
  TH1D* h_dy_njets56 	= new TH1D("h_dy_njets56",    "h_dy_njets56",    3, 500, 1400);
  TH1D* h_dy_njets7 	= new TH1D("h_dy_njets7",     "h_dy_njets7",     3, 500, 1400);

  // event loop for DY
  for(unsigned int ievt=0; ievt<tree_dy.GetEntries(); ievt++) {

    tree_dy.GetEntry(ievt);
    float mll=0;
    float mass=0;
    TLorentzVector mom1, mom2;

    // baseline cut
    if(tree_dy.nleps()!=2) continue;
    if(tree_dy.nbm()>2) continue;
    if(tree_dy.njets()<3) continue;
    if(tree_dy.ht()<1200) continue;
    if(tree_dy.mj12()<500) continue;
    if(tree_dy.pass()!=1) continue;
    if(tree_dy.mj12()>=1400) tree_dy.mj12()=1399.99; // to consider overflow

    // cut for OSSF and mll
    if(tree_dy.leps_pdgid().at(0)*tree_dy.leps_pdgid().at(1)==-121) mass = 0.510*0.001;
    else if(tree_dy.leps_pdgid().at(0)*tree_dy.leps_pdgid().at(1)==-169) mass = 105.66*0.001;
    else continue;

    mom1.SetPtEtaPhiM(tree_dy.leps_pt().at(0), tree_dy.leps_eta().at(0), tree_dy.leps_phi().at(0), mass);
    mom2.SetPtEtaPhiM(tree_dy.leps_pt().at(1), tree_dy.leps_eta().at(1), tree_dy.leps_phi().at(1), mass);
    TLorentzVector momtot = mom1+mom2;
    mll = momtot.M();
    if(mll<81 || mll>101) continue;

    // Fill histogram
    if(year=="UL2016") {
      if(tree_dy.njets()>=3 && tree_dy.njets()<=4) h_dy_njets34->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
      if(tree_dy.njets()>=5 && tree_dy.njets()<=6) h_dy_njets56->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
      if(tree_dy.njets()>=7) h_dy_njets7->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac16());
    }
    else if(year=="UL20178") {
      if(tree_dy.njets()>=3 && tree_dy.njets()<=4) h_dy_njets34->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
      if(tree_dy.njets()>=5 && tree_dy.njets()<=6) h_dy_njets56->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
      if(tree_dy.njets()>=7) h_dy_njets7->Fill(tree_dy.mj12(), lumi*tree_dy.weight()*tree_dy.frac1718());
    }
    else {
      if(tree_dy.njets()>=3 && tree_dy.njets()<=4) h_dy_njets34->Fill(tree_dy.mj12(), lumi*tree_dy.weight());
      if(tree_dy.njets()>=5 && tree_dy.njets()<=6) h_dy_njets56->Fill(tree_dy.mj12(), lumi*tree_dy.weight());
      if(tree_dy.njets()>=7) h_dy_njets7->Fill(tree_dy.mj12(), lumi*tree_dy.weight());
    }
  }

  // event loop for wjets
  for(unsigned int ievt=0; ievt<tree_wjets.GetEntries(); ievt++) {

    tree_wjets.GetEntry(ievt);

    // baseline cut
    if(tree_wjets.nleps()!=1) continue;
    if(tree_wjets.nbm()>2) continue;
    if(tree_wjets.njets()<4) continue;
    if(tree_wjets.ht()<1200) continue;
    if(tree_wjets.mj12()<500) continue;
    if(tree_wjets.pass()!=1) continue;
    if(tree_wjets.mj12()>=1400) tree_wjets.mj12()=1399.99; // to consider overflow

    // Fill histogram
    if(year=="UL2016") {
      if(tree_wjets.njets()>=4 && tree_wjets.njets()<=5) h_wjets_njets45->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
      if(tree_wjets.njets()>=6 && tree_wjets.njets()<=7) h_wjets_njets67->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
      if(tree_wjets.njets()>=8) h_wjets_njets8->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac16());
    }
    else if(year=="UL20178") {
      if(tree_wjets.njets()>=4 && tree_wjets.njets()<=5) h_wjets_njets45->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
      if(tree_wjets.njets()>=6 && tree_wjets.njets()<=7) h_wjets_njets67->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
      if(tree_wjets.njets()>=8) h_wjets_njets8->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight()*tree_wjets.frac1718());
    }
    else {
      if(tree_wjets.njets()>=4 && tree_wjets.njets()<=5) h_wjets_njets45->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight());
      if(tree_wjets.njets()>=6 && tree_wjets.njets()<=7) h_wjets_njets67->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight());
      if(tree_wjets.njets()>=8) h_wjets_njets8->Fill(tree_wjets.mj12(), lumi*tree_wjets.weight());
    }
  }

  /*
  cout << "njets34: " << h_dy_njets34->GetBinContent(1) << " " << h_dy_njets34->GetBinContent(2) << " " << h_dy_njets34->GetBinContent(3) << endl;
  cout << "njets34: " << h_dy_njets34->GetBinError(1) << " " << h_dy_njets34->GetBinError(2) << " " << h_dy_njets34->GetBinError(3) << endl;
  cout << "njets56: " << h_dy_njets56->GetBinContent(1) << " " << h_dy_njets56->GetBinContent(2) << " " << h_dy_njets56->GetBinContent(3) << endl;
  cout << "njets56: " << h_dy_njets56->GetBinError(1) << " " << h_dy_njets56->GetBinError(2) << " " << h_dy_njets56->GetBinError(3) << endl;
  cout << "njets7: " << h_dy_njets7->GetBinContent(1) << " " << h_dy_njets7->GetBinContent(2) << " " << h_dy_njets7->GetBinContent(3) << endl;
  cout << "njets7: " << h_dy_njets7->GetBinError(1) << " " << h_dy_njets7->GetBinError(2) << " " << h_dy_njets7->GetBinError(3) << endl;
  cout << "njets45: " << h_wjets_njets45->GetBinContent(1) << " " << h_wjets_njets45->GetBinContent(2) << " " << h_wjets_njets45->GetBinContent(3) << endl;
  cout << "njets45: " << h_wjets_njets45->GetBinError(1) << " " << h_wjets_njets45->GetBinError(2) << " " << h_wjets_njets45->GetBinError(3) << endl;
  cout << "njets67: " << h_wjets_njets67->GetBinContent(1) << " " << h_wjets_njets67->GetBinContent(2) << " " << h_wjets_njets67->GetBinContent(3) << endl;
  cout << "njets67: " << h_wjets_njets67->GetBinError(1) << " " << h_wjets_njets67->GetBinError(2) << " " << h_wjets_njets67->GetBinError(3) << endl;
  cout << "njets8: " << h_wjets_njets8->GetBinContent(1) << " " << h_wjets_njets8->GetBinContent(2) << " " << h_wjets_njets8->GetBinContent(3) << endl;
  cout << "njets8: " << h_wjets_njets8->GetBinError(1) << " " << h_wjets_njets8->GetBinError(2) << " " << h_wjets_njets8->GetBinError(3) << endl;
  */

  // Calculate unc_dy
  cout << endl;
  cout << "unc_dy" << endl;
  cout << "[low njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets45->GetBinContent(2)/h_wjets_njets45->GetBinContent(1))/(h_dy_njets34->GetBinContent(2)/h_dy_njets34->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets45->GetBinContent(3)/h_wjets_njets45->GetBinContent(1))/(h_dy_njets34->GetBinContent(3)/h_dy_njets34->GetBinContent(1)) << endl;
  cout << "[mid njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets67->GetBinContent(2)/h_wjets_njets67->GetBinContent(1))/(h_dy_njets56->GetBinContent(2)/h_dy_njets56->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets67->GetBinContent(3)/h_wjets_njets67->GetBinContent(1))/(h_dy_njets56->GetBinContent(3)/h_dy_njets56->GetBinContent(1)) << endl;
  cout << "[high njets]" << endl;
  cout << "	       * unc_dy of kappa1: " << 1 - (h_wjets_njets8->GetBinContent(2)/h_wjets_njets8->GetBinContent(1))/(h_dy_njets7->GetBinContent(2)/h_dy_njets7->GetBinContent(1)) << endl;
  cout << "	       * unc_dy of kappa2: " << 1 - (h_wjets_njets8->GetBinContent(3)/h_wjets_njets8->GetBinContent(1))/(h_dy_njets7->GetBinContent(3)/h_dy_njets7->GetBinContent(1)) << endl;


  // Draw plots

    // make clone
  TH1D* h_dy_njets34_clone = (TH1D*)h_dy_njets34->Clone("h_dy_njets34_clone");
  TH1D* h_dy_njets56_clone = (TH1D*)h_dy_njets56->Clone("h_dy_njets56_clone");
  TH1D* h_dy_njets7_clone  = (TH1D*)h_dy_njets7->Clone("h_dy_njets7_clone");
  TH1D* h_wjets_njets45_clone = (TH1D*)h_wjets_njets45->Clone("h_wjets_njets45_clone");
  TH1D* h_wjets_njets67_clone = (TH1D*)h_wjets_njets67->Clone("h_wjets_njets67_clone");
  TH1D* h_wjets_njets8_clone  = (TH1D*)h_wjets_njets8->Clone("h_wjets_njets8_clone");

    // cosmetics
      // tpad
        // njets 4-5
  h_wjets_njets45->SetTitle("");
  h_wjets_njets45->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets45->GetYaxis()->SetLabelSize(0.06); h_wjets_njets45->GetYaxis()->SetTitle("Events"); h_wjets_njets45->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets45->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets45->SetMinimum(0.31); h_wjets_njets45->SetMaximum(h_wjets_njets45->GetBinContent(1)*100); h_wjets_njets45->SetLineColor(TColor::GetColor("#832db6")); h_dy_njets34->SetLineColor(TColor::GetColor("#e76300"));
  h_wjets_njets45->SetLineWidth(3); h_dy_njets34->SetLineWidth(3);
        // njets 6-7
  h_wjets_njets67->SetTitle("");
  h_wjets_njets67->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets67->GetYaxis()->SetLabelSize(0.06); h_wjets_njets67->GetYaxis()->SetTitle("Events"); h_wjets_njets67->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets67->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets67->SetMinimum(0.31); h_wjets_njets67->SetMaximum(h_wjets_njets67->GetBinContent(1)*100); h_wjets_njets67->SetLineColor(TColor::GetColor("#832db6")); h_dy_njets56->SetLineColor(TColor::GetColor("#e76300"));
  h_wjets_njets67->SetLineWidth(3); h_dy_njets56->SetLineWidth(3);
        // njets 8-
  h_wjets_njets8->SetTitle("");
  h_wjets_njets8->GetXaxis()->SetLabelOffset(1);
  h_wjets_njets8->GetYaxis()->SetLabelSize(0.06); h_wjets_njets8->GetYaxis()->SetTitle("Events"); h_wjets_njets8->GetYaxis()->SetTitleOffset(0.95); h_wjets_njets8->GetYaxis()->SetTitleSize(0.06);
  h_wjets_njets8->SetMinimum(0.31); h_wjets_njets8->SetMaximum(h_wjets_njets8->GetBinContent(1)*100); h_wjets_njets8->SetLineColor(TColor::GetColor("#832db6")); h_dy_njets7->SetLineColor(TColor::GetColor("#e76300"));
  h_wjets_njets8->SetLineWidth(3); h_dy_njets7->SetLineWidth(3);
      // bpad
        // njets 4-5
  h_wjets_njets45_clone->SetTitle("");
  h_wjets_njets45_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets45_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets45_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets45_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets45_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets45_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets45_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets45_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets45_clone->GetYaxis()->SetTitle("W+jets / Drell-Yan"); h_wjets_njets45_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets45_clone->GetYaxis()->SetTitleOffset(0.4);
        // njets 6-7
  h_wjets_njets67_clone->SetTitle("");
  h_wjets_njets67_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets67_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets67_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets67_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets67_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets67_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets67_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets67_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets67_clone->GetYaxis()->SetTitle("W+jets / Drell-Yan"); h_wjets_njets67_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets67_clone->GetYaxis()->SetTitleOffset(0.4);
        // njets 8
  h_wjets_njets8_clone->SetTitle("");
  h_wjets_njets8_clone->GetXaxis()->SetNdivisions(505); h_wjets_njets8_clone->GetXaxis()->SetLabelSize(0.12); h_wjets_njets8_clone->GetXaxis()->SetLabelOffset(0.025); h_wjets_njets8_clone->GetXaxis()->SetTitle("M_{J}"); h_wjets_njets8_clone->GetXaxis()->SetTitleOffset(1.); h_wjets_njets8_clone->GetXaxis()->SetTitleSize(0.14);
  h_wjets_njets8_clone->GetYaxis()->SetNdivisions(505); h_wjets_njets8_clone->GetYaxis()->SetLabelSize(0.12); h_wjets_njets8_clone->GetYaxis()->SetTitle("W+jets / Drell-Yan"); h_wjets_njets8_clone->GetYaxis()->SetTitleSize(0.12); h_wjets_njets8_clone->GetYaxis()->SetTitleOffset(0.4);

    // Make TLatex
  double err_wjets_njets45=0, err_wjets_njets67=0, err_wjets_njets8=0;
  double err_dy_njets34=0,    err_dy_njets56=0,    err_dy_njets7=0;

  float num_wjets_njets45 = h_wjets_njets45_clone->IntegralAndError(1, h_wjets_njets45->GetNbinsX(), err_wjets_njets45);
  float num_wjets_njets67 = h_wjets_njets67_clone->IntegralAndError(1, h_wjets_njets67->GetNbinsX(), err_wjets_njets67);
  float num_wjets_njets8  = h_wjets_njets8_clone->IntegralAndError(1, h_wjets_njets8->GetNbinsX(), err_wjets_njets8);
  float num_dy_njets34    = h_dy_njets34_clone->IntegralAndError(1, h_dy_njets34->GetNbinsX(), err_dy_njets34);
  float num_dy_njets56    = h_dy_njets56_clone->IntegralAndError(1, h_dy_njets56->GetNbinsX(), err_dy_njets56);
  float num_dy_njets7     = h_dy_njets7_clone->IntegralAndError(1, h_dy_njets7->GetNbinsX(), err_dy_njets7);

  double err_tot_34       = (num_wjets_njets45/num_dy_njets34)*TMath::Sqrt(TMath::Power(err_dy_njets34/num_dy_njets34, 2) + TMath::Power(err_wjets_njets45/num_wjets_njets45, 2));
  double err_tot_56       = (num_wjets_njets67/num_dy_njets56)*TMath::Sqrt(TMath::Power(err_dy_njets56/num_dy_njets56, 2) + TMath::Power(err_wjets_njets67/num_wjets_njets67, 2));
  double err_tot_7        = (num_wjets_njets8/num_dy_njets7)*TMath::Sqrt(TMath::Power(err_dy_njets7/num_dy_njets7, 2) + TMath::Power(err_wjets_njets8/num_wjets_njets8, 2));

  TLatex* tex_njets34 = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets45/num_dy_njets34)*100, err_tot_34*100));
  tex_njets34->SetNDC();
  tex_njets34->SetTextSize(0.045);
  TLatex* tex_njets56 = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets67/num_dy_njets56)*100, err_tot_56*100));
  tex_njets56->SetNDC();
  tex_njets56->SetTextSize(0.045);
  TLatex* tex_njets7  = new TLatex(0.58, 0.8, Form("%.1f fb^{-1}, (%.1f#pm%.1f)\%", lumi, (num_wjets_njets8/num_dy_njets7)*100, err_tot_7*100));
  tex_njets7->SetNDC();
  tex_njets7->SetTextSize(0.045);

  TString yr;
  yr = year;
  if(year=="UL2016_comb")  yr="UL2016";
  if(year=="UL20178_comb") yr="UL20178";


  // Make TLegend
    // njets 4-5
  TLegend* l_njets34 = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets34->SetBorderSize(0);
  l_njets34->AddEntry(h_wjets_njets45, Form("%s W+jets [N=%.0f]", yr.Data(), h_wjets_njets45_clone->Integral()));
  l_njets34->AddEntry(h_dy_njets34, Form("%s Drell-Yan [N=%.0f]", yr.Data(), h_wjets_njets45_clone->Integral()));
  l_njets34->SetTextSize(0.05);
    // njets 6-7
  TLegend* l_njets56  = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets56->SetBorderSize(0);
  l_njets56->AddEntry(h_wjets_njets67, Form("%s W+jets [N=%.0f]", yr.Data(), h_wjets_njets67_clone->Integral()));
  l_njets56->AddEntry(h_dy_njets56, Form("%s Drell-Yan [N=%.0f]", yr.Data(), h_wjets_njets67_clone->Integral()));
  l_njets56->SetTextSize(0.05);
    // njets 8-
  TLegend* l_njets7 = new TLegend(0.15, 0.05, 0.5, 0.20);
  l_njets7->SetBorderSize(0);
  l_njets7->AddEntry(h_wjets_njets8, Form("%s W+jets [N=%.0f]", yr.Data(), h_wjets_njets8_clone->Integral()));
  l_njets7->AddEntry(h_dy_njets7, Form("%s Drell-Yan [N=%.0f]", yr.Data(), h_wjets_njets8_clone->Integral()));
  l_njets7->SetTextSize(0.05);

  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);
    // njets 4-5
  TPad *tpad_njets45(NULL), *bpad_njets45(NULL);
      // tpad
  TCanvas* c_njets34 = new TCanvas("c_njets34", "c_njets34", 800, 800);
  c_njets34->cd();
  tpad_njets45 = new TPad("tpad_njets45","tpad_njets45",0.,0.3,1.,1.);
  tpad_njets45->SetLeftMargin(0.12); tpad_njets45->SetBottomMargin(0.02); tpad_njets45->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets45->Draw();
  tpad_njets45->cd();
  gPad->SetLogy();
  h_wjets_njets45->Draw("hist");
  h_dy_njets34->Scale(1.*h_wjets_njets45_clone->Integral()/h_dy_njets34_clone->Integral());
  h_dy_njets34->Draw("same PL");
  l_njets34->Draw();
  tex_njets34->Draw();
      // bpad
  c_njets34->cd();
  bpad_njets45 = new TPad("bpad_njets45","bpad_njets45",0.,0.,1.,0.305);
  bpad_njets45->SetLeftMargin(0.12);
  bpad_njets45->SetTopMargin(0.); bpad_njets45->SetBottomMargin(0.4); bpad_njets45->SetFillStyle(4000);
  bpad_njets45->Draw(); bpad_njets45->cd();
  h_wjets_njets45_clone->Scale(1.*h_dy_njets34_clone->Integral()/h_wjets_njets45_clone->Integral());
  h_wjets_njets45_clone->Divide(h_dy_njets34_clone);
  //h_wjets_njets45_clone->SetMarkerStyle(20);
  h_wjets_njets45_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets45_clone->SetLineColor(kBlack);
  h_wjets_njets45_clone->SetLineWidth(2);
  h_wjets_njets45_clone->Draw("B e");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets34->Print(Form("plots/wjets_kappa/log_norm_dy_njet_45_mj12_mj12ge500_htg1200_nbmse2_lumi%s.pdf", lumi_title.Data()));

    // njets 6-7
  TPad *tpad_njets67(NULL), *bpad_njets67(NULL);
      // tpad
  TCanvas* c_njets56 = new TCanvas("c_njets56", "c_njets56", 800, 800);
  c_njets56->cd();
  tpad_njets67 = new TPad("tpad_njets67","tpad_njets67",0.,0.3,1.,1.);
  tpad_njets67->SetLeftMargin(0.12); tpad_njets67->SetBottomMargin(0.02); tpad_njets67->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets67->Draw();
  tpad_njets67->cd();
  gPad->SetLogy();
  h_wjets_njets67->Draw("hist");
  h_dy_njets56->Scale(1.*h_wjets_njets67_clone->Integral()/h_dy_njets56_clone->Integral());
  h_dy_njets56->Draw("same PL");
  l_njets56->Draw();
  tex_njets56->Draw();
      // bpad
  c_njets56->cd();
  bpad_njets67 = new TPad("bpad_njets67","bpad_njets67",0.,0.,1.,0.305);
  bpad_njets67->SetLeftMargin(0.12);
  bpad_njets67->SetTopMargin(0.); bpad_njets67->SetBottomMargin(0.4); bpad_njets67->SetFillStyle(4000);
  bpad_njets67->Draw(); bpad_njets67->cd();
  h_wjets_njets67_clone->Scale(1.*h_dy_njets56_clone->Integral()/h_wjets_njets67_clone->Integral());
  h_wjets_njets67_clone->Divide(h_dy_njets56_clone);
  //h_wjets_njets67_clone->SetMarkerStyle(20);
  h_wjets_njets67_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets67_clone->SetLineColor(kBlack);
  h_wjets_njets67_clone->SetLineWidth(2);
  h_wjets_njets67_clone->Draw("B e");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets56->Print(Form("plots/wjets_kappa/log_norm_dy_njet_67_mj12_mj12ge500_htg1200_nbmse2_lumi%s.pdf", lumi_title.Data()));

    // njets 8-
  TPad *tpad_njets8(NULL), *bpad_njets8(NULL);
      // tpad
  TCanvas* c_njets7 = new TCanvas("c_njets7", "c_njets7", 800, 800);
  c_njets7->cd();
  tpad_njets8 = new TPad("tpad_njets8","tpad_njets8",0.,0.3,1.,1.);
  tpad_njets8->SetLeftMargin(0.12); tpad_njets8->SetBottomMargin(0.02); tpad_njets8->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets8->Draw();
  tpad_njets8->cd();
  gPad->SetLogy();
  h_wjets_njets8->Draw("hist");
  h_dy_njets7->Scale(1.*h_wjets_njets8_clone->Integral()/h_dy_njets7_clone->Integral());
  h_dy_njets7->Draw("same PL");
  l_njets7->Draw();
  tex_njets7->Draw();
      // bpad
  c_njets7->cd();
  bpad_njets8 = new TPad("bpad_njets8","bpad_njets8",0.,0.,1.,0.305);
  bpad_njets8->SetLeftMargin(0.12);
  bpad_njets8->SetTopMargin(0.); bpad_njets8->SetBottomMargin(0.4); bpad_njets8->SetFillStyle(4000);
  bpad_njets8->Draw(); bpad_njets8->cd();
  h_wjets_njets8_clone->Scale(1.*h_dy_njets7_clone->Integral()/h_wjets_njets8_clone->Integral());
  h_wjets_njets8_clone->Divide(h_dy_njets7_clone);
  //h_wjets_njets8_clone->SetMarkerStyle(20);
  h_wjets_njets8_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_wjets_njets8_clone->SetLineColor(kBlack);
  h_wjets_njets8_clone->SetLineWidth(2);
  h_wjets_njets8_clone->Draw("B e");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets7->Print(Form("plots/wjets_kappa/log_norm_dy_njet_8_mj12_mj12ge500_htg1200_nbmse2_lumi%s.pdf", lumi_title.Data()));




}

void wjets_kappa_plot_dy_region(TString year)
{
  gErrorIgnoreLevel = kError+1;
  TH1::SetDefaultSumw2();

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  styles style("CMSPaper");
  style.LabelSize    *= 1.1;
  style.LegendSize   *= 1.0;
  style.TitleSize    *= 1.1;
  style.yTitleOffset /= 1.3;
  style.xTitleOffset /= 1.08;

  double lumi;
  TString lumi_title;
  if(year=="UL2016_preVFP") 	  {lumi=19.5;  lumi_title="19p5";}
  else if(year=="UL2016_postVFP") {lumi=16.8;  lumi_title="16p8";}
  else if(year=="UL2017")         {lumi=41.5;  lumi_title="41p5";}
  else if(year=="UL2018")  	  {lumi=59.8;  lumi_title="59p8";}
  else if(year=="UL2016_comb") 	  {lumi=36.3;  lumi_title="36p3";}
  else if(year=="UL20178_comb")	  {lumi=101.3; lumi_title="101p3";}
  else {cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018/UL2016_comb/UL20178_comb" << endl;}

  TString folder_kwj_dat = folder_year(year, false).at(4);
  TString folder_kwj     = folder_year(year, false).at(3);
  TString folder_sig     = folder_year(year, false).at(2);

  vector<TString> s_data  = getRPVProcess(folder_kwj_dat, "data");
  vector<TString> s_dy    = getRPVProcess(folder_kwj,     "DY");

  vector<TString> s_qcd   = getRPVProcess(folder_kwj, "qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_kwj, "ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_kwj, "wjets");
  vector<TString> s_other = getRPVProcess(folder_kwj, "other_public_DY_without_wjets");
  vector<TString> s_sig_1800 = getRPVProcess(folder_sig, "rpv_m1800");

  // make small tree
  small_tree_rpv tree_data((static_cast<std::string>(s_data.at(0))));
  small_tree_rpv tree_dy((static_cast<std::string>(s_dy.at(0))));

  small_tree_rpv tree_qcd((static_cast<std::string>(s_qcd.at(0))));
  small_tree_rpv tree_ttbar((static_cast<std::string>(s_ttbar.at(0))));
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_other((static_cast<std::string>(s_other.at(0))));
  small_tree_rpv tree_signal((static_cast<std::string>(s_sig_1800.at(0))));

  // append small tree
  appendTree(s_data, tree_data);
  appendTree(s_dy, tree_dy);
  appendTree(s_qcd, tree_qcd);
  appendTree(s_ttbar, tree_ttbar);
  appendTree(s_wjets, tree_wjets);
  appendTree(s_other, tree_other);
  appendTree(s_sig_1800, tree_signal);


  // define histogram
  TH1D* h_data_njets34  = new TH1D("h_data_njets34",  "h_data_njets34",  3, 500, 1400);
  TH1D* h_data_njets56  = new TH1D("h_data_njets56",  "h_data_njets56",  3, 500, 1400);
  TH1D* h_data_njets7   = new TH1D("h_data_njets7",   "h_data_njets7",   3, 500, 1400);
  TH1D* h_dy_njets34    = new TH1D("h_dy_njets34",    "h_dy_njets34",    3, 500, 1400);
  TH1D* h_dy_njets56    = new TH1D("h_dy_njets56",    "h_dy_njets56",    3, 500, 1400);
  TH1D* h_dy_njets7     = new TH1D("h_dy_njets7",     "h_dy_njets7",     3, 500, 1400);
  TH1D* h_qcd_njets34   = new TH1D("h_qcd_njets34",   "h_qcd_njets34",   3, 500, 1400);
  TH1D* h_qcd_njets56   = new TH1D("h_qcd_njets56",   "h_qcd_njets56",   3, 500, 1400);
  TH1D* h_qcd_njets7    = new TH1D("h_qcd_njets7",    "h_qcd_njets7",    3, 500, 1400);
  TH1D* h_ttbar_njets34 = new TH1D("h_ttbar_njets34", "h_ttbar_njets34", 3, 500, 1400);
  TH1D* h_ttbar_njets56 = new TH1D("h_ttbar_njets56", "h_ttbar_njets56", 3, 500, 1400);
  TH1D* h_ttbar_njets7  = new TH1D("h_ttbar_njets7",  "h_ttbar_njets7",  3, 500, 1400);
  TH1D* h_wjets_njets34 = new TH1D("h_wjets_njets34", "h_wjets_njets34", 3, 500, 1400);
  TH1D* h_wjets_njets56 = new TH1D("h_wjets_njets56", "h_wjets_njets56", 3, 500, 1400);
  TH1D* h_wjets_njets7  = new TH1D("h_wjets_njets7",  "h_wjets_njets7",  3, 500, 1400);
  TH1D* h_other_njets34 = new TH1D("h_other_njets34", "h_other_njets34", 3, 500, 1400);
  TH1D* h_other_njets56 = new TH1D("h_other_njets56", "h_other_njets56", 3, 500, 1400);
  TH1D* h_other_njets7  = new TH1D("h_other_njets7",  "h_other_njets7",  3, 500, 1400);
  TH1D* h_signal_njets34 = new TH1D("h_signal_njets34", "h_signal_njets34", 3, 500, 1400);
  TH1D* h_signal_njets56 = new TH1D("h_signal_njets56", "h_signal_njets56", 3, 500, 1400);
  TH1D* h_signal_njets7  = new TH1D("h_signal_njets7",  "h_signal_njets7",  3, 500, 1400);


  // Fill histogram after applying selection for DY-dominant region
  pass_dy_selection(tree_data,  h_data_njets34,  "data", "34", year, "mj");
  pass_dy_selection(tree_data,  h_data_njets56,  "data", "56", year, "mj");
  pass_dy_selection(tree_data,  h_data_njets7,   "data", "7",  year, "mj");
  pass_dy_selection(tree_dy,    h_dy_njets34,    "mc",   "34", year, "mj");
  pass_dy_selection(tree_dy,    h_dy_njets56,    "mc",   "56", year, "mj");
  pass_dy_selection(tree_dy,    h_dy_njets7,     "mc",   "7",  year, "mj");
  pass_dy_selection(tree_qcd,   h_qcd_njets34,   "mc",   "34", year, "mj");
  pass_dy_selection(tree_qcd,   h_qcd_njets56,   "mc",   "56", year, "mj");
  pass_dy_selection(tree_qcd,   h_qcd_njets7,    "mc",   "7",  year, "mj");
  pass_dy_selection(tree_ttbar, h_ttbar_njets34, "mc",   "34", year, "mj");
  pass_dy_selection(tree_ttbar, h_ttbar_njets56, "mc",   "56", year, "mj");
  pass_dy_selection(tree_ttbar, h_ttbar_njets7,  "mc",   "7",  year, "mj");
  pass_dy_selection(tree_wjets, h_wjets_njets34, "mc",   "34", year, "mj");
  pass_dy_selection(tree_wjets, h_wjets_njets56, "mc",   "56", year, "mj");
  pass_dy_selection(tree_wjets, h_wjets_njets7,  "mc",   "7",  year, "mj");
  pass_dy_selection(tree_other, h_other_njets34, "mc",   "34", year, "mj");
  pass_dy_selection(tree_other, h_other_njets56, "mc",   "56", year, "mj");
  pass_dy_selection(tree_other, h_other_njets7,  "mc",   "7",  year, "mj");
  pass_dy_selection(tree_signal, h_signal_njets34, "mc",   "34", year, "mj");
  pass_dy_selection(tree_signal, h_signal_njets56, "mc",   "56", year, "mj");
  pass_dy_selection(tree_signal, h_signal_njets7,  "mc",   "7",  year, "mj");

  // Make clone
  TH1D* h_data_njets34_clone  = (TH1D*)h_data_njets34->Clone("h_data_njets34_clone");
  TH1D* h_data_njets56_clone  = (TH1D*)h_data_njets56->Clone("h_data_njets56_clone");
  TH1D* h_data_njets7_clone   = (TH1D*)h_data_njets7->Clone("h_data_njets7_clone");
  TH1D* h_dy_njets34_clone    = (TH1D*)h_dy_njets34->Clone("h_dy_njets34_clone");
  TH1D* h_dy_njets56_clone    = (TH1D*)h_dy_njets56->Clone("h_dy_njets56_clone");
  TH1D* h_dy_njets7_clone     = (TH1D*)h_dy_njets7->Clone("h_dy_njets7_clone");
  TH1D* h_qcd_njets34_clone   = (TH1D*)h_qcd_njets34->Clone("h_qcd_njets34_clone");
  TH1D* h_qcd_njets56_clone   = (TH1D*)h_qcd_njets56->Clone("h_qcd_njets56_clone");
  TH1D* h_qcd_njets7_clone    = (TH1D*)h_qcd_njets7->Clone("h_qcd_njets7_clone");
  TH1D* h_ttbar_njets34_clone = (TH1D*)h_ttbar_njets34->Clone("h_ttbar_njets34_clone");
  TH1D* h_ttbar_njets56_clone = (TH1D*)h_ttbar_njets56->Clone("h_ttbar_njets56_clone");
  TH1D* h_ttbar_njets7_clone  = (TH1D*)h_ttbar_njets7->Clone("h_ttbar_njets7_clone");
  TH1D* h_wjets_njets34_clone = (TH1D*)h_wjets_njets34->Clone("h_wjets_njets34_clone");
  TH1D* h_wjets_njets56_clone = (TH1D*)h_wjets_njets56->Clone("h_wjets_njets56_clone");
  TH1D* h_wjets_njets7_clone  = (TH1D*)h_wjets_njets7->Clone("h_wjets_njets7_clone");
  TH1D* h_other_njets34_clone = (TH1D*)h_other_njets34->Clone("h_other_njets34_clone");
  TH1D* h_other_njets56_clone = (TH1D*)h_other_njets56->Clone("h_other_njets56_clone");
  TH1D* h_other_njets7_clone  = (TH1D*)h_other_njets7->Clone("h_other_njets7_clone");

  // Total MC histograms
  TH1D* h_tot_mc_njets34 = (TH1D*)h_dy_njets34->Clone("h_tot_mc_njets34");
  TH1D* h_tot_mc_njets56 = (TH1D*)h_dy_njets56->Clone("h_tot_mc_njets56");
  TH1D* h_tot_mc_njets7  = (TH1D*)h_dy_njets7->Clone("h_tot_mc_njets7");
  h_tot_mc_njets34->Add(h_qcd_njets34_clone); h_tot_mc_njets34->Add(h_ttbar_njets34_clone); h_tot_mc_njets34->Add(h_wjets_njets34_clone); h_tot_mc_njets34->Add(h_other_njets34_clone);
  h_tot_mc_njets56->Add(h_qcd_njets56_clone); h_tot_mc_njets56->Add(h_ttbar_njets56_clone); h_tot_mc_njets56->Add(h_wjets_njets56_clone); h_tot_mc_njets56->Add(h_other_njets56_clone);
  h_tot_mc_njets7->Add(h_qcd_njets7_clone); h_tot_mc_njets7->Add(h_ttbar_njets7_clone); h_tot_mc_njets7->Add(h_wjets_njets7_clone); h_tot_mc_njets7->Add(h_other_njets7_clone);

  cout << "Purity" << endl;
  cout << "Low Njets:  " << h_dy_njets34->Integral(1,3) << " / " << h_tot_mc_njets34->Integral(1,3) << " = " << h_dy_njets34->Integral(1,3)/h_tot_mc_njets34->Integral(1,3)*100 << "\%" << endl;
  cout << "Mid Njets:  " << h_dy_njets56->Integral(1,3) << " / " << h_tot_mc_njets56->Integral(1,3) << " = " << h_dy_njets56->Integral(1,3)/h_tot_mc_njets56->Integral(1,3)*100 << "\%" << endl;
  cout << "High Njets: " << h_dy_njets7->Integral(1,3) << " / " << h_tot_mc_njets7->Integral(1,3) << " = " << h_dy_njets7->Integral(1,3)/h_tot_mc_njets7->Integral(1,3)*100 << "\%" << endl;
  cout << endl;

  cout << "signal yield" << endl;
  cout << "Low Njets:  " << endl;
  cout << "          (1)" << h_signal_njets34->GetBinContent(1) << endl;
  cout << "          (2)" << h_signal_njets34->GetBinContent(2) << endl;
  cout << "          (3)" << h_signal_njets34->GetBinContent(3) << endl;
  cout << "Mid Njets:  " << endl;
  cout << "          (1)" << h_signal_njets56->GetBinContent(1) << endl;
  cout << "          (2)" << h_signal_njets56->GetBinContent(2) << endl;
  cout << "          (3)" << h_signal_njets56->GetBinContent(3) << endl;
  cout << "High Njets:  " << endl;
  cout << "          (1)" << h_signal_njets7->GetBinContent(1) << endl;
  cout << "          (2)" << h_signal_njets7->GetBinContent(2) << endl;
  cout << "          (3)" << h_signal_njets7->GetBinContent(3) << endl;
  cout << endl;

  // To validate kappa values against those from ./run/make_kappa_CRFit.exe
    // normalize
      // total mc
  TH1D* h_tot_mc_njets34_clone = (TH1D*)h_tot_mc_njets34->Clone("h_tot_mc_njets34_clone");
  TH1D* h_tot_mc_njets56_clone = (TH1D*)h_tot_mc_njets56->Clone("h_tot_mc_njets56_clone");
  TH1D* h_tot_mc_njets7_clone  = (TH1D*)h_tot_mc_njets7->Clone("h_tot_mc_njets7_clone");

      // SF
  float sf_njets34 = h_data_njets34->Integral(1,-1)/h_tot_mc_njets34_clone->Integral(1,-1);
  float sf_njets56 = h_data_njets56->Integral(1,-1)/h_tot_mc_njets56_clone->Integral(1,-1);
  float sf_njets7  = h_data_njets7->Integral(1,-1)/h_tot_mc_njets7_clone->Integral(1,-1);

      // other mc (total mc - dy)
  TH1D* h_other_mc_njets34 = (TH1D*)h_qcd_njets34_clone->Clone("h_other_mc_njets34");
  TH1D* h_other_mc_njets56 = (TH1D*)h_qcd_njets56_clone->Clone("h_other_mc_njets56");
  TH1D* h_other_mc_njets7  = (TH1D*)h_qcd_njets7_clone->Clone("h_other_mc_njets7");
  h_other_mc_njets34->Add(h_ttbar_njets34_clone); h_other_mc_njets34->Add(h_wjets_njets34_clone); h_other_mc_njets34->Add(h_other_njets34_clone);
  h_other_mc_njets56->Add(h_ttbar_njets56_clone); h_other_mc_njets56->Add(h_wjets_njets56_clone); h_other_mc_njets56->Add(h_other_njets56_clone);
  h_other_mc_njets7->Add(h_ttbar_njets7_clone); h_other_mc_njets7->Add(h_wjets_njets7_clone); h_other_mc_njets7->Add(h_other_njets7_clone);
      // normalized other mc
  h_other_mc_njets34->Scale(sf_njets34);
  h_other_mc_njets56->Scale(sf_njets56);
  h_other_mc_njets7->Scale(sf_njets7);

      // data - other mc
  TH1D* h_data_minus_others_njets34_clone = (TH1D*)h_data_njets34->Clone("h_data_minus_others_njets34_clone");
  TH1D* h_data_minus_others_njets56_clone = (TH1D*)h_data_njets56->Clone("h_data_minus_others_njets56_clone");
  TH1D* h_data_minus_others_njets7_clone  = (TH1D*)h_data_njets7->Clone("h_data_minus_others_njets7_clone");
  h_data_minus_others_njets34_clone->Add(h_other_mc_njets34,-1);
  h_data_minus_others_njets56_clone->Add(h_other_mc_njets56,-1);
  h_data_minus_others_njets7_clone->Add(h_other_mc_njets7,-1);

  cout << "Kappa" << endl;
  cout << "Low Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets34_clone->GetBinContent(2)/h_data_minus_others_njets34_clone->GetBinContent(1))/(h_dy_njets34_clone->GetBinContent(2)/h_dy_njets34_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets34_clone->GetBinContent(3)/h_data_minus_others_njets34_clone->GetBinContent(1))/(h_dy_njets34_clone->GetBinContent(3)/h_dy_njets34_clone->GetBinContent(1)) << endl;
  cout << "Mid Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets56_clone->GetBinContent(2)/h_data_minus_others_njets56_clone->GetBinContent(1))/(h_dy_njets56_clone->GetBinContent(2)/h_dy_njets56_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets56_clone->GetBinContent(3)/h_data_minus_others_njets56_clone->GetBinContent(1))/(h_dy_njets56_clone->GetBinContent(3)/h_dy_njets56_clone->GetBinContent(1)) << endl;
  cout << "High Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets7_clone->GetBinContent(2)/h_data_minus_others_njets7_clone->GetBinContent(1))/(h_dy_njets7_clone->GetBinContent(2)/h_dy_njets7_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets7_clone->GetBinContent(3)/h_data_minus_others_njets7_clone->GetBinContent(1))/(h_dy_njets7_clone->GetBinContent(3)/h_dy_njets7_clone->GetBinContent(1)) << endl;
  // validate end

  /*
  // test
  TH1D* h_data_njets34_clone_test = (TH1D*)h_data_njets34->Clone("h_data_njets34_clone_test");
  TH1D* h_data_njets56_clone_test = (TH1D*)h_data_njets56->Clone("h_data_njets56_clone_test");
  TH1D* h_data_njets7_clone_test = (TH1D*)h_data_njets7->Clone("h_data_njets7_clone_test");
  h_data_njets34_clone_test->Add(h_tot_mc_njets34, -1);
  h_data_njets56_clone_test->Add(h_tot_mc_njets56, -1);
  h_data_njets7_clone_test->Add(h_tot_mc_njets7, -1);
  cout << "njets 34" << endl;
  cout << "data_obs: " << h_data_njets34_clone->GetBinContent(1) << " / " << h_data_njets34_clone->GetBinContent(2) << " / " << h_data_njets34_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets34_clone->GetBinError(1) << " / " << h_data_njets34_clone->GetBinError(2) << " / " << h_data_njets34_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets34_clone_test->GetBinContent(1) << " / " << h_data_njets34_clone_test->GetBinContent(2) << " / " << h_data_njets34_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets34_clone_test->GetBinError(1) << " / " << h_data_njets34_clone_test->GetBinError(2) << " / " << h_data_njets34_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets34_clone->GetBinContent(1) << " / " << h_dy_njets34_clone->GetBinContent(2) << " / " << h_dy_njets34_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets34_clone->GetBinError(1) << " / " << h_dy_njets34_clone->GetBinError(2) << " / " << h_dy_njets34_clone->GetBinError(3) << endl;
  float kap1_34=0, unc_kap1_34=0;
  float kap2_34=0, unc_kap2_34=0;
  kap1_34 = (h_data_njets34_clone_test->GetBinContent(2)/h_dy_njets34_clone->GetBinContent(2))/(h_data_njets34_clone_test->GetBinContent(1)/h_dy_njets34_clone->GetBinContent(1));
  unc_kap1_34 = kap1_34*TMath::Sqrt(TMath::Power(h_data_njets34_clone_test->GetBinError(1)/h_data_njets34_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets34_clone_test->GetBinError(2)/h_data_njets34_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets34_clone->GetBinError(1)/h_dy_njets34_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets34_clone->GetBinError(2)/h_dy_njets34_clone->GetBinContent(2),2));
  kap2_34 = (h_data_njets34_clone_test->GetBinContent(3)/h_dy_njets34_clone->GetBinContent(3))/(h_data_njets34_clone_test->GetBinContent(1)/h_dy_njets34_clone->GetBinContent(1));
  unc_kap2_34 = kap2_34*TMath::Sqrt(TMath::Power(h_data_njets34_clone_test->GetBinError(1)/h_data_njets34_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets34_clone_test->GetBinError(3)/h_data_njets34_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets34_clone->GetBinError(1)/h_dy_njets34_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets34_clone->GetBinError(3)/h_dy_njets34_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34/kap1_34 << endl;
  cout << "kap2:     " << kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34/kap2_34 << endl;
  cout << endl;
  cout << "njets 56" << endl;
  cout << "data_obs: " << h_data_njets56_clone->GetBinContent(1) << " / " << h_data_njets56_clone->GetBinContent(2) << " / " << h_data_njets56_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets56_clone->GetBinError(1) << " / " << h_data_njets56_clone->GetBinError(2) << " / " << h_data_njets56_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets56_clone_test->GetBinContent(1) << " / " << h_data_njets56_clone_test->GetBinContent(2) << " / " << h_data_njets56_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets56_clone_test->GetBinError(1) << " / " << h_data_njets56_clone_test->GetBinError(2) << " / " << h_data_njets56_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets56_clone->GetBinContent(1) << " / " << h_dy_njets56_clone->GetBinContent(2) << " / " << h_dy_njets56_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets56_clone->GetBinError(1) << " / " << h_dy_njets56_clone->GetBinError(2) << " / " << h_dy_njets56_clone->GetBinError(3) << endl;
  float kap1_56=0, unc_kap1_56=0;
  float kap2_56=0, unc_kap2_56=0;
  kap1_56 = (h_data_njets56_clone_test->GetBinContent(2)/h_dy_njets56_clone->GetBinContent(2))/(h_data_njets56_clone_test->GetBinContent(1)/h_dy_njets56_clone->GetBinContent(1));
  unc_kap1_56 = kap1_56*TMath::Sqrt(TMath::Power(h_data_njets56_clone_test->GetBinError(1)/h_data_njets56_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets56_clone_test->GetBinError(2)/h_data_njets56_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets56_clone->GetBinError(1)/h_dy_njets56_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets56_clone->GetBinError(2)/h_dy_njets56_clone->GetBinContent(2),2));
  kap2_56 = (h_data_njets56_clone_test->GetBinContent(3)/h_dy_njets56_clone->GetBinContent(3))/(h_data_njets56_clone_test->GetBinContent(1)/h_dy_njets56_clone->GetBinContent(1));
  unc_kap2_56 = kap2_56*TMath::Sqrt(TMath::Power(h_data_njets56_clone_test->GetBinError(1)/h_data_njets56_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets56_clone_test->GetBinError(3)/h_data_njets56_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets56_clone->GetBinError(1)/h_dy_njets56_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets56_clone->GetBinError(3)/h_dy_njets56_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56/kap1_56 << endl;
  cout << "kap2:     " << kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56/kap2_56 << endl;
  cout << endl;
  cout << "njets 7" << endl;
  cout << "data_obs: " << h_data_njets7_clone->GetBinContent(1) << " / " << h_data_njets7_clone->GetBinContent(2) << " / " << h_data_njets7_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets7_clone->GetBinError(1) << " / " << h_data_njets7_clone->GetBinError(2) << " / " << h_data_njets7_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets7_clone_test->GetBinContent(1) << " / " << h_data_njets7_clone_test->GetBinContent(2) << " / " << h_data_njets7_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets7_clone_test->GetBinError(1) << " / " << h_data_njets7_clone_test->GetBinError(2) << " / " << h_data_njets7_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets7_clone->GetBinContent(1) << " / " << h_dy_njets7_clone->GetBinContent(2) << " / " << h_dy_njets7_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets7_clone->GetBinError(1) << " / " << h_dy_njets7_clone->GetBinError(2) << " / " << h_dy_njets7_clone->GetBinError(3) << endl;
  float kap1_7=0, unc_kap1_7=0;
  float kap2_7=0, unc_kap2_7=0;
  kap1_7 = (h_data_njets7_clone_test->GetBinContent(2)/h_dy_njets7_clone->GetBinContent(2))/(h_data_njets7_clone_test->GetBinContent(1)/h_dy_njets7_clone->GetBinContent(1));
  unc_kap1_7 = kap1_7*TMath::Sqrt(TMath::Power(h_data_njets7_clone_test->GetBinError(1)/h_data_njets7_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets7_clone_test->GetBinError(2)/h_data_njets7_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets7_clone->GetBinError(1)/h_dy_njets7_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets7_clone->GetBinError(2)/h_dy_njets7_clone->GetBinContent(2),2));
  kap2_7 = (h_data_njets7_clone_test->GetBinContent(3)/h_dy_njets7_clone->GetBinContent(3))/(h_data_njets7_clone_test->GetBinContent(1)/h_dy_njets7_clone->GetBinContent(1));
  unc_kap2_7 = kap2_7*TMath::Sqrt(TMath::Power(h_data_njets7_clone_test->GetBinError(1)/h_data_njets7_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets7_clone_test->GetBinError(3)/h_data_njets7_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets7_clone->GetBinError(1)/h_dy_njets7_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets7_clone->GetBinError(3)/h_dy_njets7_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_7 << endl;
  cout << "unc_kap1: " << unc_kap1_7 << endl;
  cout << "unc_kap1: " << unc_kap1_7/kap1_7 << endl;
  cout << "kap2:     " << kap2_7 << endl;
  cout << "unc_kap2: " << unc_kap2_7 << endl;
  cout << "unc_kap2: " << unc_kap2_7/kap2_7 << endl;

  // test end
  // */

  // Cosmetics
    // njets 3-4
  h_data_njets34->SetMarkerStyle(20); h_data_njets34->SetMarkerSize(1.5);
  h_data_njets34->SetLineColor(kBlack); h_dy_njets34->SetLineColor(kBlack); h_qcd_njets34->SetLineColor(kBlack); h_ttbar_njets34->SetLineColor(kBlack); h_wjets_njets34->SetLineColor(kBlack); h_other_njets34->SetLineColor(kBlack);
  h_dy_njets34->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets34->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets34->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets34->SetFillColor(TColor::GetColor("#832db6")); h_other_njets34->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets34->SetLineWidth(2); h_dy_njets34->SetLineWidth(1); h_qcd_njets34->SetLineWidth(1); h_ttbar_njets34->SetLineWidth(1); h_wjets_njets34->SetLineWidth(1); h_other_njets34->SetLineWidth(1);
  h_data_njets34->SetTitle("");
  h_data_njets34->GetXaxis()->SetLabelOffset(1);
  h_data_njets34->GetYaxis()->SetLabelSize(0.06); h_data_njets34->GetYaxis()->SetTitle("Events"); h_data_njets34->GetYaxis()->SetTitleOffset(0.95); h_data_njets34->GetYaxis()->SetTitleSize(0.06);
  h_data_njets34->SetMinimum(0.02); h_data_njets34->SetMaximum(h_data_njets34->GetBinContent(1)*100);
  h_data_njets34_clone->SetTitle("");
  h_data_njets34_clone->GetXaxis()->SetNdivisions(505); h_data_njets34_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets34_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets34_clone->GetXaxis()->SetTitle("M_{J}"); h_data_njets34_clone->GetXaxis()->SetTitleOffset(1.); h_data_njets34_clone->GetXaxis()->SetTitleSize(0.14);
  h_data_njets34_clone->GetYaxis()->SetNdivisions(505); h_data_njets34_clone->GetYaxis()->SetLabelSize(0.12); h_data_njets34_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets34_clone->GetYaxis()->SetTitleSize(0.12); h_data_njets34_clone->GetYaxis()->SetTitleOffset(0.4);
    // njets 5-6
  h_data_njets56->SetMarkerStyle(20); h_data_njets56->SetMarkerSize(1.5);
  h_data_njets56->SetLineColor(kBlack); h_dy_njets56->SetLineColor(kBlack); h_qcd_njets56->SetLineColor(kBlack); h_ttbar_njets56->SetLineColor(kBlack); h_wjets_njets56->SetLineColor(kBlack); h_other_njets56->SetLineColor(kBlack);
  h_dy_njets56->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets56->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets56->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets56->SetFillColor(TColor::GetColor("#832db6")); h_other_njets56->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets56->SetLineWidth(2); h_dy_njets56->SetLineWidth(1); h_qcd_njets56->SetLineWidth(1); h_ttbar_njets56->SetLineWidth(1); h_wjets_njets56->SetLineWidth(1); h_other_njets56->SetLineWidth(1);
  h_data_njets56->SetTitle("");
  h_data_njets56->GetXaxis()->SetLabelOffset(1);
  h_data_njets56->GetYaxis()->SetLabelSize(0.06); h_data_njets56->GetYaxis()->SetTitle("Events"); h_data_njets56->GetYaxis()->SetTitleOffset(0.95); h_data_njets56->GetYaxis()->SetTitleSize(0.06);
  h_data_njets56->SetMinimum(0.02); h_data_njets56->SetMaximum(h_data_njets56->GetBinContent(1)*100);
  h_data_njets56_clone->SetTitle("");
  h_data_njets56_clone->GetXaxis()->SetNdivisions(505); h_data_njets56_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets56_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets56_clone->GetXaxis()->SetTitle("M_{J}"); h_data_njets56_clone->GetXaxis()->SetTitleOffset(1.); h_data_njets56_clone->GetXaxis()->SetTitleSize(0.14);
  h_data_njets56_clone->GetYaxis()->SetNdivisions(505); h_data_njets56_clone->GetYaxis()->SetLabelSize(0.12); h_data_njets56_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets56_clone->GetYaxis()->SetTitleSize(0.12); h_data_njets56_clone->GetYaxis()->SetTitleOffset(0.4);
    // njets 7-
  h_data_njets7->SetMarkerStyle(20); h_data_njets7->SetMarkerSize(1.5);
  h_data_njets7->SetLineColor(kBlack); h_dy_njets7->SetLineColor(kBlack); h_qcd_njets7->SetLineColor(kBlack); h_ttbar_njets7->SetLineColor(kBlack); h_wjets_njets7->SetLineColor(kBlack); h_other_njets7->SetLineColor(kBlack);
  h_data_njets7->SetLineWidth(2); h_dy_njets7->SetLineWidth(1); h_qcd_njets7->SetLineWidth(1); h_ttbar_njets7->SetLineWidth(1); h_wjets_njets7->SetLineWidth(1); h_other_njets7->SetLineWidth(1);
  h_dy_njets7->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets7->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets7->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets7->SetFillColor(TColor::GetColor("#832db6")); h_other_njets7->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets7->SetTitle("");
  h_data_njets7->GetXaxis()->SetLabelOffset(1);
  h_data_njets7->GetYaxis()->SetLabelSize(0.06); h_data_njets7->GetYaxis()->SetTitle("Events"); h_data_njets7->GetYaxis()->SetTitleOffset(0.95); h_data_njets7->GetYaxis()->SetTitleSize(0.06);
  h_data_njets7->SetMinimum(0.02); h_data_njets7->SetMaximum(h_data_njets7->GetBinContent(1)*100);
  h_data_njets7_clone->SetTitle("");
  h_data_njets7_clone->GetXaxis()->SetNdivisions(505); h_data_njets7_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets7_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets7_clone->GetXaxis()->SetTitle("M_{J}"); h_data_njets7_clone->GetXaxis()->SetTitleOffset(1.); h_data_njets7_clone->GetXaxis()->SetTitleSize(0.14);
  h_data_njets7_clone->GetYaxis()->SetNdivisions(505); h_data_njets7_clone->GetYaxis()->SetLabelSize(0.12); h_data_njets7_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets7_clone->GetYaxis()->SetTitleSize(0.12); h_data_njets7_clone->GetYaxis()->SetTitleOffset(0.4);

  h_signal_njets34->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets34->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets34->SetLineWidth(5); h_signal_njets34->SetLineStyle(2);
  h_signal_njets56->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets56->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets56->SetLineWidth(5); h_signal_njets56->SetLineStyle(2);
  h_signal_njets7->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets7->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets7->SetLineWidth(5); h_signal_njets7->SetLineStyle(2);

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.88, 0.95, Form("%.1f fb^{-1} (13 TeV)", lumi));
  if(year=="UL20178_comb") tex_lumi = new TLatex(0.88, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.05);
  TLatex *TexCMS = new TLatex(0.13,0.92,"CMS #font[52]{Preliminary}");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.05);
  TexCMS->SetLineWidth(2);

  // Normalize
  h_qcd_njets34->Scale(sf_njets34);    h_other_njets34->Scale(sf_njets34);  h_wjets_njets34->Scale(sf_njets34); h_ttbar_njets34->Scale(sf_njets34); h_dy_njets34->Scale(sf_njets34);
  h_qcd_njets56->Scale(sf_njets56);    h_other_njets56->Scale(sf_njets56);  h_wjets_njets56->Scale(sf_njets56); h_ttbar_njets56->Scale(sf_njets56); h_dy_njets56->Scale(sf_njets56);
  h_qcd_njets7->Scale(sf_njets7);      h_other_njets7->Scale(sf_njets7);    h_wjets_njets7->Scale(sf_njets7);   h_ttbar_njets7->Scale(sf_njets7);   h_dy_njets7->Scale(sf_njets7);
  h_tot_mc_njets34->Scale(sf_njets34); h_tot_mc_njets56->Scale(sf_njets56); h_tot_mc_njets7->Scale(sf_njets7);
  cout << "sf_njets34: " << sf_njets34 << endl;
  cout << "sf_njets56: " << sf_njets56 << endl;
  cout << "sf_njets7: " << sf_njets7 << endl;

  // Make THStack
  THStack* st_mc_njets34 = new THStack("st_mc_njets34", "st_mc_njets34");
  THStack* st_mc_njets56 = new THStack("st_mc_njets56", "st_mc_njets56");
  THStack* st_mc_njets7  = new THStack("st_mc_njets7",  "st_mc_njets7");
  st_mc_njets34->Add(h_qcd_njets34); st_mc_njets34->Add(h_other_njets34); st_mc_njets34->Add(h_wjets_njets34); st_mc_njets34->Add(h_ttbar_njets34); st_mc_njets34->Add(h_dy_njets34);
  st_mc_njets56->Add(h_qcd_njets56); st_mc_njets56->Add(h_other_njets56); st_mc_njets56->Add(h_wjets_njets56); st_mc_njets56->Add(h_ttbar_njets56); st_mc_njets56->Add(h_dy_njets56);
  st_mc_njets7->Add(h_qcd_njets7); st_mc_njets7->Add(h_other_njets7); st_mc_njets7->Add(h_wjets_njets7); st_mc_njets7->Add(h_ttbar_njets7); st_mc_njets7->Add(h_dy_njets7);


  // Make TLegend
    // njets 3-4
  TLegend* l_njets34_1 = new TLegend(0.15, 0.73, 0.5, 0.87);
  l_njets34_1->SetTextSize(0.06);
  l_njets34_1->SetBorderSize(0);
  l_njets34_1->SetFillStyle(0);
  l_njets34_1->AddEntry(h_data_njets34,  "data", "elp");
  l_njets34_1->AddEntry(h_dy_njets34,    "Drell-Yan", "f");
  TLegend* l_njets34_2 = new TLegend(0.55, 0.55, 0.9, 0.87);
  l_njets34_2->SetTextSize(0.06);
  l_njets34_2->SetBorderSize(0);
  l_njets34_2->SetFillStyle(0);
  l_njets34_2->AddEntry(h_qcd_njets34,   "QCD", "f");
  l_njets34_2->AddEntry(h_ttbar_njets34, "t#bar{t}", "f");
  l_njets34_2->AddEntry(h_wjets_njets34, "W+jets", "f");
  l_njets34_2->AddEntry(h_other_njets34, "Other", "f");
  l_njets34_2->AddEntry(h_signal_njets34, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 5-6
  TLegend* l_njets56_1 = new TLegend(0.15, 0.73, 0.5, 0.87);
  l_njets56_1->SetTextSize(0.06);
  l_njets56_1->SetBorderSize(0);
  l_njets56_1->SetFillStyle(0);
  l_njets56_1->AddEntry(h_data_njets56,  "data", "elp");
  l_njets56_1->AddEntry(h_dy_njets56,    "Drell-Yan", "f");
  TLegend* l_njets56_2 = new TLegend(0.55, 0.55, 0.9, 0.87);
  l_njets56_2->SetTextSize(0.06);
  l_njets56_2->SetBorderSize(0);
  l_njets56_2->SetFillStyle(0);
  l_njets56_2->AddEntry(h_qcd_njets56,   "QCD", "f");
  l_njets56_2->AddEntry(h_ttbar_njets56, "t#bar{t}", "f");
  l_njets56_2->AddEntry(h_wjets_njets56, "W+jets", "f");
  l_njets56_2->AddEntry(h_other_njets56, "Other", "f");
  l_njets56_2->AddEntry(h_signal_njets56, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 7
  TLegend* l_njets7_1 = new TLegend(0.15, 0.73, 0.5, 0.87);
  l_njets7_1->SetTextSize(0.06);
  l_njets7_1->SetBorderSize(0);
  l_njets7_1->SetFillStyle(0);
  l_njets7_1->AddEntry(h_data_njets7,  "data", "elp");
  l_njets7_1->AddEntry(h_dy_njets7,    "Drell-Yan", "f");
  TLegend* l_njets7_2 = new TLegend(0.55, 0.55, 0.9, 0.87);
  l_njets7_2->SetTextSize(0.06);
  l_njets7_2->SetBorderSize(0);
  l_njets7_2->SetFillStyle(0);
  l_njets7_2->AddEntry(h_qcd_njets7,   "QCD", "f");
  l_njets7_2->AddEntry(h_ttbar_njets7, "t#bar{t}", "f");
  l_njets7_2->AddEntry(h_wjets_njets7, "W+jets", "f");
  l_njets7_2->AddEntry(h_other_njets7, "Other", "f");
  l_njets7_2->AddEntry(h_signal_njets7, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);

    // njets 4-5
  TPad *tpad_njets34(NULL), *bpad_njets34(NULL);
      // tpad
  TCanvas* c_njets34 = new TCanvas("c_njets34", "c_njets34", 800, 800);
  c_njets34->cd();
  tpad_njets34 = new TPad("tpad_njets34","tpad_njets34",0.,0.3,1.,1.);
  tpad_njets34->SetLeftMargin(0.12); tpad_njets34->SetBottomMargin(0.02); tpad_njets34->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets34->Draw();
  tpad_njets34->cd();
  gPad->SetLogy();
  h_data_njets34->Draw("EP");
  st_mc_njets34->Draw("same hist");
  h_data_njets34->Draw("same EP");
  h_signal_njets34->Draw("same hist");
  gPad->RedrawAxis();
  l_njets34_1->Draw();
  l_njets34_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
      // bpad
  c_njets34->cd();
  bpad_njets34 = new TPad("bpad_njets34","bpad_njets34",0.,0.,1.,0.305);
  bpad_njets34->SetLeftMargin(0.12);
  bpad_njets34->SetTopMargin(0.); bpad_njets34->SetBottomMargin(0.4); bpad_njets34->SetFillStyle(4000);
  bpad_njets34->Draw(); bpad_njets34->cd();
  h_data_njets34_clone->Divide(h_tot_mc_njets34);
  h_data_njets34_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_data_njets34_clone->SetLineColor(kBlack);
  h_data_njets34_clone->SetLineWidth(2);
  h_data_njets34_clone->SetMarkerStyle(20);
  h_data_njets34_clone->SetMarkerSize(1.5);
  h_data_njets34_clone->Draw("ep");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets34->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets34_lumi%s.pdf", lumi_title.Data()));

    // njets 5-6
  TPad *tpad_njets56(NULL), *bpad_njets56(NULL);
      // tpad
  TCanvas* c_njets56 = new TCanvas("c_njets56", "c_njets56", 800, 800);
  c_njets56->cd();
  tpad_njets56 = new TPad("tpad_njets56","tpad_njets56",0.,0.3,1.,1.);
  tpad_njets56->SetLeftMargin(0.12); tpad_njets56->SetBottomMargin(0.02); tpad_njets56->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets56->Draw();
  tpad_njets56->cd();
  gPad->SetLogy();
  h_data_njets56->Draw("EP");
  st_mc_njets56->Draw("same hist");
  h_data_njets56->Draw("same EP");
  h_signal_njets56->Draw("same hist");
  gPad->RedrawAxis();
  l_njets56_1->Draw();
  l_njets56_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
      // bpad
  c_njets56->cd();
  bpad_njets56 = new TPad("bpad_njets56","bpad_njets56",0.,0.,1.,0.305);
  bpad_njets56->SetLeftMargin(0.12);
  bpad_njets56->SetTopMargin(0.); bpad_njets56->SetBottomMargin(0.4); bpad_njets56->SetFillStyle(4000);
  bpad_njets56->Draw(); bpad_njets56->cd();
  h_data_njets56_clone->Divide(h_tot_mc_njets56);
  h_data_njets56_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_data_njets56_clone->SetLineColor(kBlack);
  h_data_njets56_clone->SetLineWidth(2);
  h_data_njets56_clone->SetMarkerStyle(20);
  h_data_njets56_clone->SetMarkerSize(1.5);
  h_data_njets56_clone->Draw("ep");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets56->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets56_lumi%s.pdf", lumi_title.Data()));

    // njets 7-
  TPad *tpad_njets7(NULL), *bpad_njets7(NULL);
      // tpad
  TCanvas* c_njets7 = new TCanvas("c_njets7", "c_njets7", 800, 800);
  c_njets7->cd();
  tpad_njets7 = new TPad("tpad_njets7","tpad_njets7",0.,0.3,1.,1.);
  tpad_njets7->SetLeftMargin(0.12); tpad_njets7->SetBottomMargin(0.02); tpad_njets7->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets7->Draw();
  tpad_njets7->cd();
  gPad->SetLogy();
  h_data_njets7->Draw("EP");
  st_mc_njets7->Draw("same hist");
  h_data_njets7->Draw("same EP");
  h_signal_njets7->Draw("same hist");
  gPad->RedrawAxis();
  l_njets7_1->Draw();
  l_njets7_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
      // bpad
  c_njets7->cd();
  bpad_njets7 = new TPad("bpad_njets7","bpad_njets7",0.,0.,1.,0.305);
  bpad_njets7->SetLeftMargin(0.12);
  bpad_njets7->SetTopMargin(0.); bpad_njets7->SetBottomMargin(0.4); bpad_njets7->SetFillStyle(4000);
  bpad_njets7->Draw(); bpad_njets7->cd();
  h_data_njets7_clone->Divide(h_tot_mc_njets7);
  h_data_njets7_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_data_njets7_clone->SetLineColor(kBlack);
  h_data_njets7_clone->SetLineWidth(2);
  h_data_njets7_clone->SetMarkerStyle(20);
  h_data_njets7_clone->SetMarkerSize(1.5);
  h_data_njets7_clone->Draw("ep");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets7->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets7_lumi%s.pdf", lumi_title.Data()));


}

void comp_njets_dy_data(TString year)
{
  gErrorIgnoreLevel = kError+1;
  TH1::SetDefaultSumw2();

  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  styles style("CMSPaper");
  style.LabelSize    *= 1.1;
  style.LegendSize   *= 1.0;
  style.TitleSize    *= 1.1;
  style.yTitleOffset /= 1.3;
  style.xTitleOffset /= 1.08;

  double lumi;
  TString lumi_title;
  if(year=="UL2016_preVFP") 	  {lumi=19.5;  lumi_title="19p5";}
  else if(year=="UL2016_postVFP") {lumi=16.8;  lumi_title="16p8";}
  else if(year=="UL2017")         {lumi=41.5;  lumi_title="41p5";}
  else if(year=="UL2018")  	  {lumi=59.8;  lumi_title="59p8";}
  else if(year=="UL2016_comb") 	  {lumi=36.3;  lumi_title="36p3";}
  else if(year=="UL20178_comb")	  {lumi=101.3; lumi_title="101p3";}
  else {cout << "Please input the year as UL2016_preVFP/UL2016_postVFP/UL2017/UL2018/UL2016_comb/UL20178_comb" << endl;}

  TString folder_kwj_dat = folder_year(year, false).at(4);
  TString folder_kwj     = folder_year(year, false).at(3);
  TString folder_sig     = folder_year(year, false).at(2);

  vector<TString> s_data  = getRPVProcess(folder_kwj_dat, "data");
  vector<TString> s_dy    = getRPVProcess(folder_kwj,     "DY");

  vector<TString> s_qcd   = getRPVProcess(folder_kwj, "qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_kwj, "ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_kwj, "wjets");
  vector<TString> s_other = getRPVProcess(folder_kwj, "other_public_DY_without_wjets");
  vector<TString> s_sig_1800 = getRPVProcess(folder_sig, "rpv_m1800");

  // make small tree
  small_tree_rpv tree_data((static_cast<std::string>(s_data.at(0))));
  small_tree_rpv tree_dy((static_cast<std::string>(s_dy.at(0))));

  small_tree_rpv tree_qcd((static_cast<std::string>(s_qcd.at(0))));
  small_tree_rpv tree_ttbar((static_cast<std::string>(s_ttbar.at(0))));
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_other((static_cast<std::string>(s_other.at(0))));
  small_tree_rpv tree_signal((static_cast<std::string>(s_sig_1800.at(0))));

  // append small tree
  appendTree(s_data, tree_data);
  appendTree(s_dy, tree_dy);
  appendTree(s_qcd, tree_qcd);
  appendTree(s_ttbar, tree_ttbar);
  appendTree(s_wjets, tree_wjets);
  appendTree(s_other, tree_other);
  appendTree(s_sig_1800, tree_signal);


  // define histogram
  TH1D* h_data  = new TH1D("h_data",  "h_data",  3, 3, 9);
  TH1D* h_dy    = new TH1D("h_dy",    "h_dy",    3, 3, 9);
  TH1D* h_qcd   = new TH1D("h_qcd",   "h_qcd",   3, 3, 9);
  TH1D* h_ttbar = new TH1D("h_ttbar", "h_ttbar", 3, 3, 9);
  TH1D* h_wjets = new TH1D("h_wjets", "h_wjets", 3, 3, 9);
  TH1D* h_other = new TH1D("h_other", "h_other", 3, 3, 9);
  TH1D* h_signal = new TH1D("h_signal", "h_signal", 3, 3, 9);

  // Fill histogram after applying selection for DY-dominant region
  pass_dy_selection(tree_data,  h_data,  "data", "", year, "njets");
  pass_dy_selection(tree_dy,    h_dy,    "mc",   "", year, "njets");
  pass_dy_selection(tree_qcd,   h_qcd,   "mc",   "", year, "njets");
  pass_dy_selection(tree_ttbar, h_ttbar, "mc",   "", year, "njets");
  pass_dy_selection(tree_wjets, h_wjets, "mc",   "", year, "njets");
  pass_dy_selection(tree_other, h_other, "mc",   "", year, "njets");
  pass_dy_selection(tree_signal, h_signal, "mc",   "", year, "njets");

  // Make clone
  TH1D* h_data_clone  = (TH1D*)h_data->Clone("h_data_clone");
  TH1D* h_dy_clone    = (TH1D*)h_dy->Clone("h_dy_clone");
  TH1D* h_qcd_clone   = (TH1D*)h_qcd->Clone("h_qcd_clone");
  TH1D* h_ttbar_clone = (TH1D*)h_ttbar->Clone("h_ttbar_clone");
  TH1D* h_wjets_clone = (TH1D*)h_wjets->Clone("h_wjets_clone");
  TH1D* h_other_clone = (TH1D*)h_other->Clone("h_other_clone");

  // Total MC histograms
  TH1D* h_tot_mc = (TH1D*)h_dy->Clone("h_tot_mc");
  h_tot_mc->Add(h_qcd_clone); h_tot_mc->Add(h_ttbar_clone); h_tot_mc->Add(h_wjets_clone); h_tot_mc->Add(h_other_clone);


  // Calculate norm_wjets
  TH1D* h_data_cal = (TH1D*)h_data->Clone("h_data_cal");
  TH1D* h_dy_cal    = (TH1D*)h_dy->Clone("h_dy_cal");
  TH1D* h_qcd_cal   = (TH1D*)h_qcd->Clone("h_qcd_cal");
  TH1D* h_ttbar_cal = (TH1D*)h_ttbar->Clone("h_ttbar_cal");
  TH1D* h_wjets_cal = (TH1D*)h_wjets->Clone("h_wjets_cal");
  TH1D* h_other_cal = (TH1D*)h_other->Clone("h_other_cal");
  
  h_data_cal->Add(h_qcd_cal,-1); h_data_cal->Add(h_ttbar_cal,-1); h_data_cal->Add(h_wjets_cal,-1); h_data_cal->Add(h_other_cal,-1);

  float sf=0, diff_1=0, diff_2=0, err_stat_1=0, err_stat_2=0, tot_err_1=0, tot_err_2=0;
  sf = h_data_cal->GetBinContent(1)/h_dy_cal->GetBinContent(1);

  diff_1     = TMath::Abs((h_dy_cal->GetBinContent(2)*sf - h_data_cal->GetBinContent(2))/(h_dy_cal->GetBinContent(2)*sf));
  err_stat_1 = TMath::Sqrt((1/h_data_cal->GetBinContent(1))+(1/h_data_cal->GetBinContent(2)));
  diff_2     = TMath::Abs((h_dy_cal->GetBinContent(3)*sf - h_data_cal->GetBinContent(3))/(h_dy_cal->GetBinContent(3)*sf));
  err_stat_2 = TMath::Sqrt((1/h_data_cal->GetBinContent(1))+(1/h_data_cal->GetBinContent(3)));
  
  tot_err_1 = TMath::Sqrt(diff_1*diff_1 + err_stat_1*err_stat_1);
  tot_err_2 = TMath::Sqrt(diff_2*diff_2 + err_stat_2*err_stat_2);

  cout << "low-mid:  " << tot_err_1 << " = " << diff_1 << " +- " << err_stat_1 << endl;
  cout << "low-high: " << tot_err_2 << " = " << diff_2 << " +- " << err_stat_2 << endl;

  // Modify xsec of signal process (NLO+NLL -> NNLO+NNLL)
    // gluino mass 1800
  TH1D* h_signal_clone = (TH1D*)h_signal->Clone("h_signal_clone");
  for(int i=1; i<4; i++) {
    h_signal->SetBinContent(i, h_signal_clone->GetBinContent(i)*0.003349/0.293E-02);
  }

  cout << "signal yield" << endl;
  cout << "          (1)" << h_signal->GetBinContent(1) << endl;
  cout << "          (2)" << h_signal->GetBinContent(2) << endl;
  cout << "          (3)" << h_signal->GetBinContent(3) << endl;


  


  // Cosmetics
  h_data->SetMarkerStyle(20);
  h_data->SetLineColor(kBlack); h_dy->SetLineColor(kBlack); h_qcd->SetLineColor(kBlack); h_ttbar->SetLineColor(kBlack); h_wjets->SetLineColor(kBlack); h_other->SetLineColor(kBlack);
  h_dy->SetFillColor(TColor::GetColor("#e76300")); h_qcd->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar->SetFillColor(TColor::GetColor("#3f90da")); h_wjets->SetFillColor(TColor::GetColor("#832db6")); h_other->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data->SetLineWidth(1); h_dy->SetLineWidth(1); h_qcd->SetLineWidth(1); h_ttbar->SetLineWidth(1); h_wjets->SetLineWidth(1); h_other->SetLineWidth(1);
  h_data->SetTitle("");
  h_data->GetXaxis()->SetLabelOffset(1);
  h_data->GetYaxis()->SetLabelSize(0.06); h_data->GetYaxis()->SetTitle("Events"); h_data->GetYaxis()->SetTitleOffset(0.95); h_data->GetYaxis()->SetTitleSize(0.06);
  h_data->SetMinimum(0.21); h_data->SetMaximum(h_data->GetBinContent(1)*20);
  h_data_clone->SetTitle("");
  h_data_clone->GetXaxis()->SetNdivisions(404); h_data_clone->GetXaxis()->SetLabelSize(0.14); h_data_clone->GetXaxis()->SetLabelOffset(0.025); h_data_clone->GetXaxis()->SetTitle("N_{jet}"); h_data_clone->GetXaxis()->SetTitleOffset(1.); h_data_clone->GetXaxis()->SetTitleSize(0.14);
  h_data_clone->GetYaxis()->SetNdivisions(505); h_data_clone->GetYaxis()->SetLabelSize(0.12); h_data_clone->GetYaxis()->SetTitle("Data / MC"); h_data_clone->GetYaxis()->SetTitleSize(0.12); h_data_clone->GetYaxis()->SetTitleOffset(0.4);
  h_data_clone->GetXaxis()->SetBinLabel(1, "3 #leq N_{jet} #leq 4");
  h_data_clone->GetXaxis()->SetBinLabel(2, "5 #leq N_{jet} #leq 6");
  h_data_clone->GetXaxis()->SetBinLabel(3, "N_{jet} #geq 7");
//  h_data_clone->GetXaxis()->SetBinLabel(1, "3");
//  h_data_clone->GetXaxis()->SetBinLabel(2, "5");
//  h_data_clone->GetXaxis()->SetBinLabel(3, "7");
//  h_data_clone->GetXaxis()->SetBinLabel(4, "9");
  h_signal->SetLineColor(TColor::GetColor("#bd1f01")); h_signal->SetFillColor(TColor::GetColor("#bd1f01")); h_signal->SetLineWidth(3); h_signal->SetLineStyle(2);

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.88, 0.95, Form("%.1f fb^{-1} (13 TeV)", lumi));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.05);

  // Make THStack
  THStack* st_mc = new THStack("st_mc", "st_mc");
  st_mc->Add(h_qcd); st_mc->Add(h_other); st_mc->Add(h_wjets); st_mc->Add(h_ttbar); st_mc->Add(h_dy);


  // Make TLegend
  TLegend* l = new TLegend(0.14, 0.69, 0.85, 0.87);
  l->SetTextSize(0.05);
  l->SetNColumns(2);
  l->SetBorderSize(0);
  l->AddEntry(h_data,  "data", "elp");
  l->AddEntry(h_dy,    "Drell-Yan", "f");
  l->AddEntry(h_qcd,   "QCD", "f");
  l->AddEntry(h_ttbar, "t#bar{t}", "f");
  l->AddEntry(h_wjets, "W+jets", "f");
  l->AddEntry(h_other, "Other", "f");
  l->AddEntry(h_signal, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(3, 1., 9, 1.);
  TPad *tpad(NULL), *bpad(NULL);
      // tpad
  TCanvas* c = new TCanvas("c", "c", 800, 800);
  c->cd();
  tpad = new TPad("tpad","tpad",0.,0.3,1.,1.);
  tpad->SetLeftMargin(0.12); tpad->SetBottomMargin(0.02); tpad->SetTopMargin(style.PadTopMargin+0.01);
  tpad->Draw();
  tpad->cd();
  gPad->SetLogy();
  h_data->Draw("EP");
  st_mc->Draw("same hist");
  h_data->Draw("same EP");
  h_signal->Draw("same hist");
  gPad->RedrawAxis();
  l->Draw();
  tex_lumi->Draw();
      // bpad
  c->cd();
  bpad = new TPad("bpad","bpad",0.,0.,1.,0.305);
  bpad->SetLeftMargin(0.12);
  bpad->SetTopMargin(0.); bpad->SetBottomMargin(0.4); bpad->SetFillStyle(4000);
  bpad->Draw(); bpad->cd();
  h_data_clone->Divide(h_tot_mc);
  h_data_clone->GetYaxis()->SetRangeUser(0.1, 1.9);
  h_data_clone->SetLineColor(kBlack);
  h_data_clone->SetLineWidth(2);
  h_data_clone->SetMarkerStyle(20);
  h_data_clone->Draw("ep");
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c->Print(Form("plots/wjets_kappa/comp_njets_dy_data_lumi%s.pdf", lumi_title.Data()));

}



int main(int argc, char **argv)
{
  TString year, fig;
  year = argv[1];
  fig  = argv[2];
 
  if(fig=="17") compare_shape_wjets_dy(year); // Fig. 17

  if(fig=="18") wjets_kappa_plot_dy_region(year); // Fig. 18

  if(fig=="31") comp_njets_dy_data(year);  // Fig. 31


  return 0;
}
