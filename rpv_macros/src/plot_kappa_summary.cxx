#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooFit.h"
#include "RooSimultaneous.h"
#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooPlot.h"

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
#include "TFile.h"

#include "small_tree_rpv.hpp"
#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;


void appendTree(vector<TString> s_process, small_tree &tree_in);
void pass_qcd_selection(small_tree_rpv &tree, TH1D* h, TString datamc, TString njets, TString year);
void pass_dy_selection(small_tree_rpv &tree, TH1D* h, TString datamc, TString njets, TString year, TString mjORnjets);

void qcd_kappa_plot(TString year);  // Fig. 16
void wjets_kappa_plot_dy_region(TString year);  // Fig. 18
void ttbar_kappa_plot(TString year);  // Fig. 19
void kappa_summary_plot(TString year);  // Fig.20

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

void pass_qcd_selection(small_tree_rpv &tree, TH1D* h, TString datamc, TString njets, TString year)
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

    // baseline selection
    if(tree.stitch_ht()==0) continue;
    if(tree.nleps()!=0) continue;
    if(tree.nbm()>0) continue;
    if(tree.njets()<5) continue;
    if(tree.ht()<1200) continue;
    if(tree.mj12()<500) continue;
    if(tree.pass()!=1) continue;
    if(tree.mj12()>=1400) tree.mj12()=1399.99; // to consider overflow
  
    // Fill histogram
    if(year=="UL2016_comb") {
      if(njets=="67") {
        if(datamc=="data") {
          if(tree.njets()>=5 && tree.njets()<=6 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=5 && tree.njets()<=6) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="89") {
        if(datamc=="data") {
          if(tree.njets()>=7 && tree.njets()<=8 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=7 && tree.njets()<=8) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="10") {
        if(datamc=="data") {
          if(tree.njets()>=9 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=9) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac16());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else cout << "input njets as 67/89/10" << endl;
    }
    else if(year=="UL20178_comb") {
      if(njets=="67") {
        if(datamc=="data") {
          if(tree.njets()>=5 && tree.njets()<=6 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=5 && tree.njets()<=6) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="89") {
        if(datamc=="data") {
          if(tree.njets()>=7 && tree.njets()<=8 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=7 && tree.njets()<=8) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="10") {
        if(datamc=="data") {
          if(tree.njets()>=9 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
        }
        else if(datamc=="mc") {
          if(tree.njets()>=9) h->Fill(tree.mj12(), lumi*tree.weight()*tree.frac1718());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else cout << "input njets as 67/89/10" << endl;
    }
    else {
      if(njets=="67") {
        if(datamc=="data") {
          if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
            if(tree.njets()>=6 && tree.njets()<=7 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
          }
          else if(year=="UL2017" || year=="UL2018") {
            if(tree.njets()>=6 && tree.njets()<=7 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
          }
        }
        else if(datamc=="mc") {
          if(tree.njets()>=6 && tree.njets()<=7) h->Fill(tree.mj12(), lumi*tree.weight());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="89") {
        if(datamc=="data") {
          if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
            if(tree.njets()>=8 && tree.njets()<=9 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
          }
          else if(year=="UL2017" || year=="UL2018") {
            if(tree.njets()>=8 && tree.njets()<=9 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
          }
        }
        else if(datamc=="mc") {
          if(tree.njets()>=8 && tree.njets()<=9) h->Fill(tree.mj12(), lumi*tree.weight());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else if(njets=="10") {
        if(datamc=="data") {
          if(year=="UL2016_preVFP" || year=="UL2016_postVFP") {
            if(tree.njets()>=10 && (tree.trig_jet450()||tree.trig_ht900())) h->Fill(tree.mj12(), 1);
          }
          else if(year=="UL2017" || year=="UL2018") {
            if(tree.njets()>=10 && tree.trig_ht1050()) h->Fill(tree.mj12(), 1);
          }
        }
        else if(datamc=="mc") {
          if(tree.njets()>=10) h->Fill(tree.mj12(), lumi*tree.weight());
        }
        else cout << "input datamc as data/mc" << endl;
      }
      else cout << "input njets as 67/89/10" << endl;
    }
  } // end event loop
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
    if(mjORnjets=="mj") { // For mj distribution - Fig. 17
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
    else if(mjORnjets=="njets") { // For njets distribution - Fig. 30
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

void qcd_kappa_plot(TString year)
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

  TString folder_bkg     = folder_year(year, false).at(0);
  TString folder_dat     = folder_year(year, false).at(1);
  TString folder_sig     = folder_year(year, false).at(2);

  vector<TString> s_data  = getRPVProcess(folder_dat, "data");
  vector<TString> s_qcd   = getRPVProcess(folder_bkg, "qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg, "ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg, "wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg, "other_public");
  vector<TString> s_sig_m1200 = getRPVProcess(folder_sig, "rpv_m1200");
  vector<TString> s_sig_m1800 = getRPVProcess(folder_sig, "rpv_m1800");

  // make small tree
  small_tree_rpv tree_data((static_cast<std::string>(s_data.at(0))));
  small_tree_rpv tree_qcd((static_cast<std::string>(s_qcd.at(0))));
  small_tree_rpv tree_ttbar((static_cast<std::string>(s_ttbar.at(0))));
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_other((static_cast<std::string>(s_other.at(0))));
  small_tree_rpv tree_signal_m1200((static_cast<std::string>(s_sig_m1200.at(0))));
  small_tree_rpv tree_signal_m1800((static_cast<std::string>(s_sig_m1800.at(0))));

  // append small tree
  appendTree(s_data, tree_data);
  appendTree(s_qcd, tree_qcd);
  appendTree(s_ttbar, tree_ttbar);
  appendTree(s_wjets, tree_wjets);
  appendTree(s_other, tree_other);
  appendTree(s_sig_m1200, tree_signal_m1200);
  appendTree(s_sig_m1800, tree_signal_m1800);


  // define histogram
  TH1D* h_data_njets67   = new TH1D("h_data_njets67",   "h_data_njets67",   3, 500, 1400);
  TH1D* h_data_njets89   = new TH1D("h_data_njets89",   "h_data_njets89",   3, 500, 1400);
  TH1D* h_data_njets10   = new TH1D("h_data_njets10",   "h_data_njets10",   3, 500, 1400);
  TH1D* h_qcd_njets67    = new TH1D("h_qcd_njets67",    "h_qcd_njets67",    3, 500, 1400);
  TH1D* h_qcd_njets89    = new TH1D("h_qcd_njets89",    "h_qcd_njets89",    3, 500, 1400);
  TH1D* h_qcd_njets10    = new TH1D("h_qcd_njets10",    "h_qcd_njets10",    3, 500, 1400);
  TH1D* h_ttbar_njets67  = new TH1D("h_ttbar_njets67",  "h_ttbar_njets67",  3, 500, 1400);
  TH1D* h_ttbar_njets89  = new TH1D("h_ttbar_njets89",  "h_ttbar_njets89",  3, 500, 1400);
  TH1D* h_ttbar_njets10  = new TH1D("h_ttbar_njets10",  "h_ttbar_njets10",  3, 500, 1400);
  TH1D* h_wjets_njets67  = new TH1D("h_wjets_njets67",  "h_wjets_njets67",  3, 500, 1400);
  TH1D* h_wjets_njets89  = new TH1D("h_wjets_njets89",  "h_wjets_njets89",  3, 500, 1400);
  TH1D* h_wjets_njets10  = new TH1D("h_wjets_njets10",  "h_wjets_njets10",  3, 500, 1400);
  TH1D* h_other_njets67  = new TH1D("h_other_njets67",  "h_other_njets67",  3, 500, 1400);
  TH1D* h_other_njets89  = new TH1D("h_other_njets89",  "h_other_njets89",  3, 500, 1400);
  TH1D* h_other_njets10  = new TH1D("h_other_njets10",  "h_other_njets10",  3, 500, 1400);
  TH1D* h_signal_njets67_m1200 = new TH1D("h_signal_njets67_m1200", "h_signal_njets67_m1200", 3, 500, 1400);
  TH1D* h_signal_njets89_m1200 = new TH1D("h_signal_njets89_m1200", "h_signal_njets89_m1200", 3, 500, 1400);
  TH1D* h_signal_njets10_m1200 = new TH1D("h_signal_njets10_m1200", "h_signal_njets10_m1200", 3, 500, 1400);
  TH1D* h_signal_njets67_m1800 = new TH1D("h_signal_njets67_m1800", "h_signal_njets67_m1800", 3, 500, 1400);
  TH1D* h_signal_njets89_m1800 = new TH1D("h_signal_njets89_m1800", "h_signal_njets89_m1800", 3, 500, 1400);
  TH1D* h_signal_njets10_m1800 = new TH1D("h_signal_njets10_m1800", "h_signal_njets10_m1800", 3, 500, 1400);


  // Fill histogram after applying selection for DY-dominant region
  pass_qcd_selection(tree_data,  h_data_njets67,    "data", "67", year);
  pass_qcd_selection(tree_data,  h_data_njets89,    "data", "89", year);
  pass_qcd_selection(tree_data,  h_data_njets10,    "data", "10", year);
  pass_qcd_selection(tree_qcd,   h_qcd_njets67,     "mc",   "67", year);
  pass_qcd_selection(tree_qcd,   h_qcd_njets89,     "mc",   "89", year);
  pass_qcd_selection(tree_qcd,   h_qcd_njets10,     "mc",   "10", year);
  pass_qcd_selection(tree_ttbar, h_ttbar_njets67,   "mc",   "67", year);
  pass_qcd_selection(tree_ttbar, h_ttbar_njets89,   "mc",   "89", year);
  pass_qcd_selection(tree_ttbar, h_ttbar_njets10,   "mc",   "10", year);
  pass_qcd_selection(tree_wjets, h_wjets_njets67,   "mc",   "67", year);
  pass_qcd_selection(tree_wjets, h_wjets_njets89,   "mc",   "89", year);
  pass_qcd_selection(tree_wjets, h_wjets_njets10,   "mc",   "10", year);
  pass_qcd_selection(tree_other, h_other_njets67,   "mc",   "67", year);
  pass_qcd_selection(tree_other, h_other_njets89,   "mc",   "89", year);
  pass_qcd_selection(tree_other, h_other_njets10,   "mc",   "10", year);
  pass_qcd_selection(tree_signal_m1200, h_signal_njets67_m1200, "mc",   "67", year);
  pass_qcd_selection(tree_signal_m1200, h_signal_njets89_m1200, "mc",   "89", year);
  pass_qcd_selection(tree_signal_m1200, h_signal_njets10_m1200, "mc",   "10", year);
  pass_qcd_selection(tree_signal_m1800, h_signal_njets67_m1800, "mc",   "67", year);
  pass_qcd_selection(tree_signal_m1800, h_signal_njets89_m1800, "mc",   "89", year);
  pass_qcd_selection(tree_signal_m1800, h_signal_njets10_m1800, "mc",   "10", year);

  // Make clone
  TH1D* h_data_njets67_clone  = (TH1D*)h_data_njets67->Clone("h_data_njets67_clone");
  TH1D* h_data_njets89_clone  = (TH1D*)h_data_njets89->Clone("h_data_njets89_clone");
  TH1D* h_data_njets10_clone   = (TH1D*)h_data_njets10->Clone("h_data_njets10_clone");
  TH1D* h_qcd_njets67_clone   = (TH1D*)h_qcd_njets67->Clone("h_qcd_njets67_clone");
  TH1D* h_qcd_njets89_clone   = (TH1D*)h_qcd_njets89->Clone("h_qcd_njets89_clone");
  TH1D* h_qcd_njets10_clone    = (TH1D*)h_qcd_njets10->Clone("h_qcd_njets10_clone");
  TH1D* h_ttbar_njets67_clone = (TH1D*)h_ttbar_njets67->Clone("h_ttbar_njets67_clone");
  TH1D* h_ttbar_njets89_clone = (TH1D*)h_ttbar_njets89->Clone("h_ttbar_njets89_clone");
  TH1D* h_ttbar_njets10_clone  = (TH1D*)h_ttbar_njets10->Clone("h_ttbar_njets10_clone");
  TH1D* h_wjets_njets67_clone = (TH1D*)h_wjets_njets67->Clone("h_wjets_njets67_clone");
  TH1D* h_wjets_njets89_clone = (TH1D*)h_wjets_njets89->Clone("h_wjets_njets89_clone");
  TH1D* h_wjets_njets10_clone  = (TH1D*)h_wjets_njets10->Clone("h_wjets_njets10_clone");
  TH1D* h_other_njets67_clone = (TH1D*)h_other_njets67->Clone("h_other_njets67_clone");
  TH1D* h_other_njets89_clone = (TH1D*)h_other_njets89->Clone("h_other_njets89_clone");
  TH1D* h_other_njets10_clone  = (TH1D*)h_other_njets10->Clone("h_other_njets10_clone");

  // Total MC histograms
  TH1D* h_tot_mc_njets67 = (TH1D*)h_qcd_njets67->Clone("h_tot_mc_njets67");
  TH1D* h_tot_mc_njets89 = (TH1D*)h_qcd_njets89->Clone("h_tot_mc_njets89");
  TH1D* h_tot_mc_njets10  = (TH1D*)h_qcd_njets10->Clone("h_tot_mc_njets10");
  h_tot_mc_njets67->Add(h_ttbar_njets67_clone); h_tot_mc_njets67->Add(h_wjets_njets67_clone); h_tot_mc_njets67->Add(h_other_njets67_clone);
  h_tot_mc_njets89->Add(h_ttbar_njets89_clone); h_tot_mc_njets89->Add(h_wjets_njets89_clone); h_tot_mc_njets89->Add(h_other_njets89_clone);
  h_tot_mc_njets10->Add(h_ttbar_njets10_clone); h_tot_mc_njets10->Add(h_wjets_njets10_clone); h_tot_mc_njets10->Add(h_other_njets10_clone);

  cout << "Purity" << endl;
  cout << "Low Njets:  " << h_qcd_njets67->Integral(1,3) << " / " << h_tot_mc_njets67->Integral(1,3) << " = " << h_qcd_njets67->Integral(1,3)/h_tot_mc_njets67->Integral(1,3)*100 << "\%" << endl;
  cout << "Mid Njets:  " << h_qcd_njets89->Integral(1,3) << " / " << h_tot_mc_njets89->Integral(1,3) << " = " << h_qcd_njets89->Integral(1,3)/h_tot_mc_njets89->Integral(1,3)*100 << "\%" << endl;
  cout << "High Njets: " << h_qcd_njets10->Integral(1,3) << " / " << h_tot_mc_njets10->Integral(1,3) << " = " << h_qcd_njets10->Integral(1,3)/h_tot_mc_njets10->Integral(1,3)*100 << "\%" << endl;
  cout << endl;

  // Modify xsec of signal process (NLO+NLL -> NNLO+NNLL)
    // gluino mass 1200
  TH1D* h_signal_njets67_m1200_clone = (TH1D*)h_signal_njets67_m1200->Clone("h_signal_njets67_m1200_clone");
  TH1D* h_signal_njets89_m1200_clone = (TH1D*)h_signal_njets89_m1200->Clone("h_signal_njets89_m1200_clone");
  TH1D* h_signal_njets10_m1200_clone = (TH1D*)h_signal_njets10_m1200->Clone("h_signal_njets10_m1200_clone");
    // gluino mass 1800
  TH1D* h_signal_njets67_m1800_clone = (TH1D*)h_signal_njets67_m1800->Clone("h_signal_njets67_m1800_clone");
  TH1D* h_signal_njets89_m1800_clone = (TH1D*)h_signal_njets89_m1800->Clone("h_signal_njets89_m1800_clone");
  TH1D* h_signal_njets10_m1800_clone = (TH1D*)h_signal_njets10_m1800->Clone("h_signal_njets10_m1800_clone");
  for(int i=1; i<4; i++) {
    // gluino mass 1200
    h_signal_njets67_m1200->SetBinContent(i, h_signal_njets67_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    h_signal_njets89_m1200->SetBinContent(i, h_signal_njets89_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    h_signal_njets10_m1200->SetBinContent(i, h_signal_njets10_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    // gluino mass 1800
    h_signal_njets67_m1800->SetBinContent(i, h_signal_njets67_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
    h_signal_njets89_m1800->SetBinContent(i, h_signal_njets89_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
    h_signal_njets10_m1800->SetBinContent(i, h_signal_njets10_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
  }

  // for year-combined plots
  TFile* f = new TFile("data/qcd_kappa_meas_"+year+".root", "recreate");
  f->cd();
  h_data_njets67_clone->Write();
  h_data_njets89_clone->Write();
  h_data_njets10_clone->Write();
  h_qcd_njets67_clone->Write();
  h_qcd_njets89_clone->Write();
  h_qcd_njets10_clone->Write();
  h_ttbar_njets67_clone->Write();
  h_ttbar_njets89_clone->Write();
  h_ttbar_njets10_clone->Write();
  h_wjets_njets67_clone->Write();
  h_wjets_njets89_clone->Write();
  h_wjets_njets10_clone->Write();
  h_other_njets67_clone->Write();
  h_other_njets89_clone->Write();
  h_other_njets10_clone->Write();
  h_signal_njets67_m1200->Write();
  h_signal_njets89_m1200->Write();
  h_signal_njets10_m1200->Write();
  h_signal_njets67_m1800->Write();
  h_signal_njets89_m1800->Write();
  h_signal_njets10_m1800->Write();
  f->Close();

  cout << "[m1200]" << endl;
  cout << "    njet67" << endl;
  cout << "[1]: " << h_signal_njets67_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets67_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets67_m1200->GetBinContent(3) << endl;
  cout << "    njet89" << endl;
  cout << "[1]: " << h_signal_njets89_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets89_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets89_m1200->GetBinContent(3) << endl;
  cout << "    njet10" << endl;
  cout << "[1]: " << h_signal_njets10_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets10_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets10_m1200->GetBinContent(3) << endl;
  cout << endl;
  cout << "[m1800]" << endl;
  cout << "    njet67" << endl;
  cout << "[1]: " << h_signal_njets67_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets67_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets67_m1800->GetBinContent(3) << endl;
  cout << "    njet89" << endl;
  cout << "[1]: " << h_signal_njets89_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets89_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets89_m1800->GetBinContent(3) << endl;
  cout << "    njet10" << endl;
  cout << "[1]: " << h_signal_njets10_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets10_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets10_m1800->GetBinContent(3) << endl;

  // To validate kappa values against those from ./run/make_kappa_CRFit.exe
    // normalize
      // total mc
  TH1D* h_tot_mc_njets67_clone = (TH1D*)h_tot_mc_njets67->Clone("h_tot_mc_njets67_clone");
  TH1D* h_tot_mc_njets89_clone = (TH1D*)h_tot_mc_njets89->Clone("h_tot_mc_njets89_clone");
  TH1D* h_tot_mc_njets10_clone  = (TH1D*)h_tot_mc_njets10->Clone("h_tot_mc_njets10_clone");

      // SF
  float sf_njets67 = h_data_njets67->Integral(1,-1)/h_tot_mc_njets67_clone->Integral(1,-1);
  float sf_njets89 = h_data_njets89->Integral(1,-1)/h_tot_mc_njets89_clone->Integral(1,-1);
  float sf_njets10  = h_data_njets10->Integral(1,-1)/h_tot_mc_njets10_clone->Integral(1,-1);

      // other mc (total mc - qcd)
  TH1D* h_other_mc_njets67 = (TH1D*)h_ttbar_njets67_clone->Clone("h_other_mc_njets67");
  TH1D* h_other_mc_njets89 = (TH1D*)h_ttbar_njets89_clone->Clone("h_other_mc_njets89");
  TH1D* h_other_mc_njets10  = (TH1D*)h_ttbar_njets10_clone->Clone("h_other_mc_njets10");
  h_other_mc_njets67->Add(h_wjets_njets67_clone); h_other_mc_njets67->Add(h_other_njets67_clone);
  h_other_mc_njets89->Add(h_wjets_njets89_clone); h_other_mc_njets89->Add(h_other_njets89_clone);
  h_other_mc_njets10->Add(h_wjets_njets10_clone); h_other_mc_njets10->Add(h_other_njets10_clone);
      // normalized other mc
  h_other_mc_njets67->Scale(sf_njets67);
  h_other_mc_njets89->Scale(sf_njets89);
  h_other_mc_njets10->Scale(sf_njets10);

      // data - other mc
  TH1D* h_data_minus_others_njets67_clone = (TH1D*)h_data_njets67->Clone("h_data_minus_others_njets67_clone");
  TH1D* h_data_minus_others_njets89_clone = (TH1D*)h_data_njets89->Clone("h_data_minus_others_njets89_clone");
  TH1D* h_data_minus_others_njets10_clone  = (TH1D*)h_data_njets10->Clone("h_data_minus_others_njets10_clone");
  h_data_minus_others_njets67_clone->Add(h_other_mc_njets67,-1);
  h_data_minus_others_njets89_clone->Add(h_other_mc_njets89,-1);
  h_data_minus_others_njets10_clone->Add(h_other_mc_njets10,-1);

  cout << "Kappa" << endl;
  cout << "Low Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets67_clone->GetBinContent(2)/h_data_minus_others_njets67_clone->GetBinContent(1))/(h_qcd_njets67_clone->GetBinContent(2)/h_qcd_njets67_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets67_clone->GetBinContent(3)/h_data_minus_others_njets67_clone->GetBinContent(1))/(h_qcd_njets67_clone->GetBinContent(3)/h_qcd_njets67_clone->GetBinContent(1)) << endl;
  cout << "Mid Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets89_clone->GetBinContent(2)/h_data_minus_others_njets89_clone->GetBinContent(1))/(h_qcd_njets89_clone->GetBinContent(2)/h_qcd_njets89_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets89_clone->GetBinContent(3)/h_data_minus_others_njets89_clone->GetBinContent(1))/(h_qcd_njets89_clone->GetBinContent(3)/h_qcd_njets89_clone->GetBinContent(1)) << endl;
  cout << "High Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets10_clone->GetBinContent(2)/h_data_minus_others_njets10_clone->GetBinContent(1))/(h_qcd_njets10_clone->GetBinContent(2)/h_qcd_njets10_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets10_clone->GetBinContent(3)/h_data_minus_others_njets10_clone->GetBinContent(1))/(h_qcd_njets10_clone->GetBinContent(3)/h_qcd_njets10_clone->GetBinContent(1)) << endl;
  // validate end

  /*
  // test
  TH1D* h_data_njets67_clone_test = (TH1D*)h_data_njets67->Clone("h_data_njets67_clone_test");
  TH1D* h_data_njets89_clone_test = (TH1D*)h_data_njets89->Clone("h_data_njets89_clone_test");
  TH1D* h_data_njets10_clone_test = (TH1D*)h_data_njets10->Clone("h_data_njets10_clone_test");
  h_data_njets67_clone_test->Add(h_tot_mc_njets67, -1);
  h_data_njets89_clone_test->Add(h_tot_mc_njets89, -1);
  h_data_njets10_clone_test->Add(h_tot_mc_njets10, -1);
  cout << "njets 34" << endl;
  cout << "data_obs: " << h_data_njets67_clone->GetBinContent(1) << " / " << h_data_njets67_clone->GetBinContent(2) << " / " << h_data_njets67_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets67_clone->GetBinError(1) << " / " << h_data_njets67_clone->GetBinError(2) << " / " << h_data_njets67_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets67_clone_test->GetBinContent(1) << " / " << h_data_njets67_clone_test->GetBinContent(2) << " / " << h_data_njets67_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets67_clone_test->GetBinError(1) << " / " << h_data_njets67_clone_test->GetBinError(2) << " / " << h_data_njets67_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets67_clone->GetBinContent(1) << " / " << h_dy_njets67_clone->GetBinContent(2) << " / " << h_dy_njets67_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets67_clone->GetBinError(1) << " / " << h_dy_njets67_clone->GetBinError(2) << " / " << h_dy_njets67_clone->GetBinError(3) << endl;
  float kap1_34=0, unc_kap1_34=0;
  float kap2_34=0, unc_kap2_34=0;
  kap1_34 = (h_data_njets67_clone_test->GetBinContent(2)/h_dy_njets67_clone->GetBinContent(2))/(h_data_njets67_clone_test->GetBinContent(1)/h_dy_njets67_clone->GetBinContent(1));
  unc_kap1_34 = kap1_34*TMath::Sqrt(TMath::Power(h_data_njets67_clone_test->GetBinError(1)/h_data_njets67_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets67_clone_test->GetBinError(2)/h_data_njets67_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets67_clone->GetBinError(1)/h_dy_njets67_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets67_clone->GetBinError(2)/h_dy_njets67_clone->GetBinContent(2),2));
  kap2_34 = (h_data_njets67_clone_test->GetBinContent(3)/h_dy_njets67_clone->GetBinContent(3))/(h_data_njets67_clone_test->GetBinContent(1)/h_dy_njets67_clone->GetBinContent(1));
  unc_kap2_34 = kap2_34*TMath::Sqrt(TMath::Power(h_data_njets67_clone_test->GetBinError(1)/h_data_njets67_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets67_clone_test->GetBinError(3)/h_data_njets67_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets67_clone->GetBinError(1)/h_dy_njets67_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets67_clone->GetBinError(3)/h_dy_njets67_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34/kap1_34 << endl;
  cout << "kap2:     " << kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34/kap2_34 << endl;
  cout << endl;
  cout << "njets 56" << endl;
  cout << "data_obs: " << h_data_njets89_clone->GetBinContent(1) << " / " << h_data_njets89_clone->GetBinContent(2) << " / " << h_data_njets89_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets89_clone->GetBinError(1) << " / " << h_data_njets89_clone->GetBinError(2) << " / " << h_data_njets89_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets89_clone_test->GetBinContent(1) << " / " << h_data_njets89_clone_test->GetBinContent(2) << " / " << h_data_njets89_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets89_clone_test->GetBinError(1) << " / " << h_data_njets89_clone_test->GetBinError(2) << " / " << h_data_njets89_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets89_clone->GetBinContent(1) << " / " << h_dy_njets89_clone->GetBinContent(2) << " / " << h_dy_njets89_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets89_clone->GetBinError(1) << " / " << h_dy_njets89_clone->GetBinError(2) << " / " << h_dy_njets89_clone->GetBinError(3) << endl;
  float kap1_56=0, unc_kap1_56=0;
  float kap2_56=0, unc_kap2_56=0;
  kap1_56 = (h_data_njets89_clone_test->GetBinContent(2)/h_dy_njets89_clone->GetBinContent(2))/(h_data_njets89_clone_test->GetBinContent(1)/h_dy_njets89_clone->GetBinContent(1));
  unc_kap1_56 = kap1_56*TMath::Sqrt(TMath::Power(h_data_njets89_clone_test->GetBinError(1)/h_data_njets89_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets89_clone_test->GetBinError(2)/h_data_njets89_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets89_clone->GetBinError(1)/h_dy_njets89_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets89_clone->GetBinError(2)/h_dy_njets89_clone->GetBinContent(2),2));
  kap2_56 = (h_data_njets89_clone_test->GetBinContent(3)/h_dy_njets89_clone->GetBinContent(3))/(h_data_njets89_clone_test->GetBinContent(1)/h_dy_njets89_clone->GetBinContent(1));
  unc_kap2_56 = kap2_56*TMath::Sqrt(TMath::Power(h_data_njets89_clone_test->GetBinError(1)/h_data_njets89_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets89_clone_test->GetBinError(3)/h_data_njets89_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets89_clone->GetBinError(1)/h_dy_njets89_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets89_clone->GetBinError(3)/h_dy_njets89_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56/kap1_56 << endl;
  cout << "kap2:     " << kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56/kap2_56 << endl;
  cout << endl;
  cout << "njets 7" << endl;
  cout << "data_obs: " << h_data_njets10_clone->GetBinContent(1) << " / " << h_data_njets10_clone->GetBinContent(2) << " / " << h_data_njets10_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets10_clone->GetBinError(1) << " / " << h_data_njets10_clone->GetBinError(2) << " / " << h_data_njets10_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets10_clone_test->GetBinContent(1) << " / " << h_data_njets10_clone_test->GetBinContent(2) << " / " << h_data_njets10_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets10_clone_test->GetBinError(1) << " / " << h_data_njets10_clone_test->GetBinError(2) << " / " << h_data_njets10_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets10_clone->GetBinContent(1) << " / " << h_dy_njets10_clone->GetBinContent(2) << " / " << h_dy_njets10_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets10_clone->GetBinError(1) << " / " << h_dy_njets10_clone->GetBinError(2) << " / " << h_dy_njets10_clone->GetBinError(3) << endl;
  float kap1_7=0, unc_kap1_7=0;
  float kap2_7=0, unc_kap2_7=0;
  kap1_7 = (h_data_njets10_clone_test->GetBinContent(2)/h_dy_njets10_clone->GetBinContent(2))/(h_data_njets10_clone_test->GetBinContent(1)/h_dy_njets10_clone->GetBinContent(1));
  unc_kap1_7 = kap1_7*TMath::Sqrt(TMath::Power(h_data_njets10_clone_test->GetBinError(1)/h_data_njets10_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets10_clone_test->GetBinError(2)/h_data_njets10_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets10_clone->GetBinError(1)/h_dy_njets10_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets10_clone->GetBinError(2)/h_dy_njets10_clone->GetBinContent(2),2));
  kap2_7 = (h_data_njets10_clone_test->GetBinContent(3)/h_dy_njets10_clone->GetBinContent(3))/(h_data_njets10_clone_test->GetBinContent(1)/h_dy_njets10_clone->GetBinContent(1));
  unc_kap2_7 = kap2_7*TMath::Sqrt(TMath::Power(h_data_njets10_clone_test->GetBinError(1)/h_data_njets10_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets10_clone_test->GetBinError(3)/h_data_njets10_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets10_clone->GetBinError(1)/h_dy_njets10_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets10_clone->GetBinError(3)/h_dy_njets10_clone->GetBinContent(3),2));
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
    // njets 5-6
  h_data_njets67->SetMarkerStyle(20); h_data_njets67->SetMarkerSize(2);
  h_data_njets67->SetLineColor(kBlack); h_qcd_njets67->SetLineColor(kBlack); h_ttbar_njets67->SetLineColor(kBlack); h_wjets_njets67->SetLineColor(kBlack); h_other_njets67->SetLineColor(kBlack);
  h_qcd_njets67->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets67->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets67->SetFillColor(TColor::GetColor("#832db6")); h_other_njets67->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets67->SetLineWidth(2); h_qcd_njets67->SetLineWidth(1); h_ttbar_njets67->SetLineWidth(1); h_wjets_njets67->SetLineWidth(1); h_other_njets67->SetLineWidth(1);
  h_data_njets67->SetTitle("");
  h_data_njets67->GetXaxis()->SetLabelOffset(1);
  h_data_njets67->GetYaxis()->SetLabelSize(0.07); h_data_njets67->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets67->GetYaxis()->SetTitleOffset(0.92); h_data_njets67->GetYaxis()->SetTitleSize(0.08);
  h_data_njets67->SetMinimum(0.02); h_data_njets67->SetMaximum(h_data_njets67->GetBinContent(1)*2000000);
  h_data_njets67_clone->SetTitle("");
  h_data_njets67_clone->GetXaxis()->SetNdivisions(505); h_data_njets67_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets67_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets67_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets67_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets67_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets67_clone->GetYaxis()->SetNdivisions(505); h_data_njets67_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets67_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets67_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets67_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets67_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets67_clone->GetXaxis()->SetLabelSize(0);
    // njets 7-8
  h_data_njets89->SetMarkerStyle(20); h_data_njets89->SetMarkerSize(2);
  h_data_njets89->SetLineColor(kBlack); h_qcd_njets89->SetLineColor(kBlack); h_ttbar_njets89->SetLineColor(kBlack); h_wjets_njets89->SetLineColor(kBlack); h_other_njets89->SetLineColor(kBlack);
  h_qcd_njets89->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets89->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets89->SetFillColor(TColor::GetColor("#832db6")); h_other_njets89->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets89->SetLineWidth(2); h_qcd_njets89->SetLineWidth(1); h_ttbar_njets89->SetLineWidth(1); h_wjets_njets89->SetLineWidth(1); h_other_njets89->SetLineWidth(1);
  h_data_njets89->SetTitle("");
  h_data_njets89->GetXaxis()->SetLabelOffset(1);
  h_data_njets89->GetYaxis()->SetLabelSize(0.07); h_data_njets89->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets89->GetYaxis()->SetTitleOffset(0.92); h_data_njets89->GetYaxis()->SetTitleSize(0.08);
  h_data_njets89->SetMinimum(0.02); h_data_njets89->SetMaximum(h_data_njets89->GetBinContent(1)*2000000);
  h_data_njets89_clone->SetTitle("");
  h_data_njets89_clone->GetXaxis()->SetNdivisions(505); h_data_njets89_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets89_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets89_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets89_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets89_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets89_clone->GetYaxis()->SetNdivisions(505); h_data_njets89_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets89_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets89_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets89_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets89_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets89_clone->GetXaxis()->SetLabelSize(0);
    // njets 9-
  h_data_njets10->SetMarkerStyle(20); h_data_njets10->SetMarkerSize(2);
  h_data_njets10->SetLineColor(kBlack); h_qcd_njets10->SetLineColor(kBlack); h_ttbar_njets10->SetLineColor(kBlack); h_wjets_njets10->SetLineColor(kBlack); h_other_njets10->SetLineColor(kBlack);
  h_data_njets10->SetLineWidth(2); h_qcd_njets10->SetLineWidth(1); h_ttbar_njets10->SetLineWidth(1); h_wjets_njets10->SetLineWidth(1); h_other_njets10->SetLineWidth(1);
  h_qcd_njets10->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets10->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets10->SetFillColor(TColor::GetColor("#832db6")); h_other_njets10->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets10->SetTitle("");
  h_data_njets10->GetXaxis()->SetLabelOffset(1);
  h_data_njets10->GetYaxis()->SetLabelSize(0.07); h_data_njets10->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets10->GetYaxis()->SetTitleOffset(0.92); h_data_njets10->GetYaxis()->SetTitleSize(0.08);
  h_data_njets10->SetMinimum(0.02); h_data_njets10->SetMaximum(h_data_njets10->GetBinContent(1)*2000000);
  h_data_njets10_clone->SetTitle("");
  h_data_njets10_clone->GetXaxis()->SetNdivisions(505); h_data_njets10_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets10_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets10_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets10_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets10_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets10_clone->GetYaxis()->SetNdivisions(505); h_data_njets10_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets10_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets10_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets10_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets10_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets10_clone->GetXaxis()->SetLabelSize(0);

  h_signal_njets67_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets67_m1200->SetLineWidth(4); h_signal_njets67_m1200->SetLineStyle(2);
  h_signal_njets89_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets89_m1200->SetLineWidth(4); h_signal_njets89_m1200->SetLineStyle(2);
  h_signal_njets10_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets10_m1200->SetLineWidth(4); h_signal_njets10_m1200->SetLineStyle(2);
  h_signal_njets67_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets67_m1800->SetLineWidth(4); h_signal_njets67_m1800->SetLineStyle(1);
  h_signal_njets89_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets89_m1800->SetLineWidth(4); h_signal_njets89_m1800->SetLineStyle(1);
  h_signal_njets10_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets10_m1800->SetLineWidth(4); h_signal_njets10_m1800->SetLineStyle(1);

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.89, 0.95, Form("%.1f fb^{-1} (13 TeV)", lumi));
  if(year=="UL20178_comb") tex_lumi = new TLatex(0.89, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.07);
  //TLatex *TexCMS = new TLatex(0.15,0.925,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.15,0.925,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.07);
  TexCMS->SetLineWidth(2);

  TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
  TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
  TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
  TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
  tex_mj500->SetTextSize(0.15); tex_mj800->SetTextSize(0.15); tex_mj1100->SetTextSize(0.15); tex_mj1400->SetTextSize(0.15);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

  TLatex* tex_Nlep0   = new TLatex(0.20, 0.78, "N_{lep} = 0");
  TLatex* tex_Njets56 = new TLatex(0.20, 0.67, "5 #leq N_{jet} #leq 6");
  TLatex* tex_Njets78 = new TLatex(0.20, 0.67, "7 #leq N_{jet} #leq 8");
  TLatex* tex_Njets9  = new TLatex(0.20, 0.67, "N_{jet} #geq 9");
  TLatex* tex_Nb0     = new TLatex(0.20, 0.56, "N_{b} = 0");
  tex_Nlep0->SetNDC();   tex_Nlep0->SetTextFont(42);   tex_Nlep0->SetTextSize(0.07);
  tex_Njets56->SetNDC(); tex_Njets56->SetTextFont(42); tex_Njets56->SetTextSize(0.07);
  tex_Njets78->SetNDC(); tex_Njets78->SetTextFont(42); tex_Njets78->SetTextSize(0.07);
  tex_Njets9->SetNDC();  tex_Njets9->SetTextFont(42);  tex_Njets9->SetTextSize(0.07);
  tex_Nb0->SetNDC();     tex_Nb0->SetTextFont(42);     tex_Nb0->SetTextSize(0.07);

  // Normalize
  h_qcd_njets67->Scale(sf_njets67);    h_other_njets67->Scale(sf_njets67);  h_wjets_njets67->Scale(sf_njets67); h_ttbar_njets67->Scale(sf_njets67);
  h_qcd_njets89->Scale(sf_njets89);    h_other_njets89->Scale(sf_njets89);  h_wjets_njets89->Scale(sf_njets89); h_ttbar_njets89->Scale(sf_njets89);
  h_qcd_njets10->Scale(sf_njets10);    h_other_njets10->Scale(sf_njets10);  h_wjets_njets10->Scale(sf_njets10); h_ttbar_njets10->Scale(sf_njets10);
  h_tot_mc_njets67->Scale(sf_njets67); h_tot_mc_njets89->Scale(sf_njets89); h_tot_mc_njets10->Scale(sf_njets10);
  cout << "sf_njets67: " << sf_njets67 << endl;
  cout << "sf_njets89: " << sf_njets89 << endl;
  cout << "sf_njets10: " << sf_njets10 << endl;


  // Make THStack
  THStack* st_mc_njets67 = new THStack("st_mc_njets67", "st_mc_njets67");
  THStack* st_mc_njets89 = new THStack("st_mc_njets89", "st_mc_njets89");
  THStack* st_mc_njets10  = new THStack("st_mc_njets10",  "st_mc_njets10");
  st_mc_njets67->Add(h_other_njets67); st_mc_njets67->Add(h_ttbar_njets67); st_mc_njets67->Add(h_wjets_njets67); st_mc_njets67->Add(h_qcd_njets67);
  st_mc_njets89->Add(h_other_njets89); st_mc_njets89->Add(h_ttbar_njets89); st_mc_njets89->Add(h_wjets_njets89); st_mc_njets89->Add(h_qcd_njets89);
  st_mc_njets10->Add(h_other_njets10); st_mc_njets10->Add(h_ttbar_njets10); st_mc_njets10->Add(h_wjets_njets10); st_mc_njets10->Add(h_qcd_njets10);


  // Make TLegend
    // njets 3-4
  TLegend* l_njets67_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets67_2->SetTextSize(0.055);
  l_njets67_2->SetBorderSize(0);
  l_njets67_2->SetFillStyle(0);
  l_njets67_2->AddEntry(h_data_njets67,   "data", "elp");
  l_njets67_2->AddEntry(h_qcd_njets67,    "QCD", "f");
  l_njets67_2->AddEntry(h_ttbar_njets67,  "t#bar{t}", "f");
  l_njets67_2->AddEntry(h_wjets_njets67,  "W+jets", "f");
  l_njets67_2->AddEntry(h_other_njets67,  "Other", "f");
  l_njets67_2->AddEntry(h_signal_njets67_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets67_2->AddEntry(h_signal_njets67_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 5-6
  TLegend* l_njets89_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets89_2->SetTextSize(0.055);
  l_njets89_2->SetBorderSize(0);
  l_njets89_2->SetFillStyle(0);
  l_njets89_2->AddEntry(h_data_njets89,   "data", "elp");
  l_njets89_2->AddEntry(h_qcd_njets89,    "QCD", "f");
  l_njets89_2->AddEntry(h_ttbar_njets89,  "t#bar{t}", "f");
  l_njets89_2->AddEntry(h_wjets_njets89,  "W+jets", "f");
  l_njets89_2->AddEntry(h_other_njets89,  "Other", "f");
  l_njets89_2->AddEntry(h_signal_njets89_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets89_2->AddEntry(h_signal_njets89_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 7
  TLegend* l_njets10_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets10_2->SetTextSize(0.055);
  l_njets10_2->SetBorderSize(0);
  l_njets10_2->SetFillStyle(0);
  l_njets10_2->AddEntry(h_data_njets10,   "data", "elp");
  l_njets10_2->AddEntry(h_qcd_njets10,    "QCD", "f");
  l_njets10_2->AddEntry(h_ttbar_njets10,  "t#bar{t}", "f");
  l_njets10_2->AddEntry(h_wjets_njets10,  "W+jets", "f");
  l_njets10_2->AddEntry(h_other_njets10,  "Other", "f");
  l_njets10_2->AddEntry(h_signal_njets10_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets10_2->AddEntry(h_signal_njets10_m1800, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);

    // njets 5-6
  TPad *tpad_njets67(NULL), *bpad_njets67(NULL);
      // tpad
  TCanvas* c_njets67 = new TCanvas("c_njets67", "c_njets67", 800, 800);
  c_njets67->cd();
  tpad_njets67 = new TPad("tpad_njets67","tpad_njets67",0.,0.3,1.,1.);
  tpad_njets67->SetLeftMargin(0.15); tpad_njets67->SetBottomMargin(0.02); tpad_njets67->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets67->Draw();
  tpad_njets67->cd();
  gPad->SetLogy();
  h_data_njets67->GetYaxis()->SetLabelSize(0);
  h_data_njets67->Draw("EP");
  st_mc_njets67->Draw("same hist");
  h_data_njets67->Draw("same EP");
  h_signal_njets67_m1200->Draw("same hist");
  h_signal_njets67_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets67_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets56->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  // test
  if(year=="UL2016_comb") {
    TLatex* label_njets56_1 = new TLatex(0.12, 0.11, "1");
    label_njets56_1->SetNDC(); label_njets56_1->SetTextSize(0.07); label_njets56_1->SetTextFont(42);
    TLatex* label_njets56_2 = new TLatex(0.075, 0.235, "10^{2}");
    label_njets56_2->SetNDC(); label_njets56_2->SetTextSize(0.07); label_njets56_2->SetTextFont(42);
    TLatex* label_njets56_3 = new TLatex(0.075, 0.37, "10^{4}");
    label_njets56_3->SetNDC(); label_njets56_3->SetTextSize(0.07); label_njets56_3->SetTextFont(42);
    TLatex* label_njets56_4 = new TLatex(0.075, 0.495, "10^{6}");
    label_njets56_4->SetNDC(); label_njets56_4->SetTextSize(0.07); label_njets56_4->SetTextFont(42);
    TLatex* label_njets56_5 = new TLatex(0.075, 0.625, "10^{8}");
    label_njets56_5->SetNDC(); label_njets56_5->SetTextSize(0.07); label_njets56_5->SetTextFont(42);
    TLatex* label_njets56_6 = new TLatex(0.059, 0.755, "10^{10}");
    label_njets56_6->SetNDC(); label_njets56_6->SetTextSize(0.07); label_njets56_6->SetTextFont(42);
    label_njets56_1->Draw();
    label_njets56_2->Draw();
    label_njets56_3->Draw();
    label_njets56_4->Draw();
    label_njets56_5->Draw();
    label_njets56_6->Draw();
  }
  else {
    TLatex* label_njets56_1 = new TLatex(0.12, 0.11, "1");
    label_njets56_1->SetNDC(); label_njets56_1->SetTextSize(0.07); label_njets56_1->SetTextFont(42);
    TLatex* label_njets56_2 = new TLatex(0.075, 0.235, "10^{2}");
    label_njets56_2->SetNDC(); label_njets56_2->SetTextSize(0.07); label_njets56_2->SetTextFont(42);
    TLatex* label_njets56_3 = new TLatex(0.075, 0.355, "10^{4}");
    label_njets56_3->SetNDC(); label_njets56_3->SetTextSize(0.07); label_njets56_3->SetTextFont(42);
    TLatex* label_njets56_4 = new TLatex(0.075, 0.47, "10^{6}");
    label_njets56_4->SetNDC(); label_njets56_4->SetTextSize(0.07); label_njets56_4->SetTextFont(42);
    TLatex* label_njets56_5 = new TLatex(0.075, 0.595, "10^{8}");
    label_njets56_5->SetNDC(); label_njets56_5->SetTextSize(0.07); label_njets56_5->SetTextFont(42);
    TLatex* label_njets56_6 = new TLatex(0.059, 0.71, "10^{10}");
    label_njets56_6->SetNDC(); label_njets56_6->SetTextSize(0.07); label_njets56_6->SetTextFont(42);
    label_njets56_1->Draw();
    label_njets56_2->Draw();
    label_njets56_3->Draw();
    label_njets56_4->Draw();
    label_njets56_5->Draw();
    label_njets56_6->Draw();
  }
  // test end
      // bpad
  c_njets67->cd();
  bpad_njets67 = new TPad("bpad_njets67","bpad_njets67",0.,0.,1.,0.305);
  bpad_njets67->SetLeftMargin(0.15);
  bpad_njets67->SetTopMargin(0.); bpad_njets67->SetBottomMargin(0.4); bpad_njets67->SetFillStyle(4000);
  bpad_njets67->Draw(); bpad_njets67->cd();

  TH1D* h_data_njets67_err = (TH1D*)h_data_njets67->Clone("h_data_njets67_err");
  h_data_njets67_err->SetMarkerSize(0);
  h_data_njets67_err->SetFillColor(kBlack);
  h_data_njets67_err->SetLineColor(kBlack);
  h_data_njets67_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets67_err->SetBinContent(imj, h_data_njets67->GetBinContent(imj)/h_tot_mc_njets67->GetBinContent(imj));
    h_data_njets67_err->SetBinError(imj, (h_data_njets67->GetBinContent(imj)/h_tot_mc_njets67->GetBinContent(imj))*(h_tot_mc_njets67->GetBinError(imj)/h_tot_mc_njets67->GetBinContent(imj)));
  }
  cout << h_data_njets67->GetBinContent(1) << endl;
  cout << h_data_njets67->GetBinError(1) << endl;
  cout << h_tot_mc_njets67->GetBinContent(1) << endl;
  cout << h_tot_mc_njets67->GetBinError(1) << endl;

  h_data_njets67_clone->Divide(h_tot_mc_njets67);
  h_data_njets67_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets67_clone->SetLineColor(kBlack);
  h_data_njets67_clone->SetLineWidth(2);
  h_data_njets67_clone->SetMarkerStyle(20);
  h_data_njets67_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets67_clone->SetBinError(imj, h_data_njets67_clone->GetBinContent(imj)*(h_data_njets67->GetBinError(imj)/h_data_njets67->GetBinContent(imj)));
  }
  h_data_njets67_clone->Draw("ep");
  h_data_njets67_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets67->Print(Form("plots/qcd_kappa/qcd_kappa_njets56_lumi%s.pdf", lumi_title.Data()));

    // njets 7-8
  TPad *tpad_njets89(NULL), *bpad_njets89(NULL);
      // tpad
  TCanvas* c_njets89 = new TCanvas("c_njets89", "c_njets89", 800, 800);
  c_njets89->cd();
  tpad_njets89 = new TPad("tpad_njets89","tpad_njets89",0.,0.3,1.,1.);
  tpad_njets89->SetLeftMargin(0.15); tpad_njets89->SetBottomMargin(0.02); tpad_njets89->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets89->Draw();
  tpad_njets89->cd();
  gPad->SetLogy();
  h_data_njets89->GetYaxis()->SetLabelSize(0);
  h_data_njets89->Draw("EP");
  st_mc_njets89->Draw("same hist");
  h_data_njets89->Draw("same EP");
  h_signal_njets89_m1200->Draw("same hist");
  h_signal_njets89_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets89_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets78->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  // test
  if(year=="UL2016_comb") {
    TLatex* label_njets78_1 = new TLatex(0.125, 0.11, "1");
    TLatex* label_njets78_2 = new TLatex(0.075, 0.24, "10^{2}");
    TLatex* label_njets78_3 = new TLatex(0.075, 0.37, "10^{4}");
    TLatex* label_njets78_4 = new TLatex(0.075, 0.505, "10^{6}");
    TLatex* label_njets78_5 = new TLatex(0.075, 0.635, "10^{8}");
    TLatex* label_njets78_6 = new TLatex(0.059, 0.765, "10^{10}");
    label_njets78_1->SetNDC(); label_njets78_1->SetTextSize(0.07); label_njets78_1->SetTextFont(42);
    label_njets78_2->SetNDC(); label_njets78_2->SetTextSize(0.07); label_njets78_2->SetTextFont(42);
    label_njets78_3->SetNDC(); label_njets78_3->SetTextSize(0.07); label_njets78_3->SetTextFont(42);
    label_njets78_4->SetNDC(); label_njets78_4->SetTextSize(0.07); label_njets78_4->SetTextFont(42);
    label_njets78_5->SetNDC(); label_njets78_5->SetTextSize(0.07); label_njets78_5->SetTextFont(42);
    label_njets78_6->SetNDC(); label_njets78_6->SetTextSize(0.07); label_njets78_6->SetTextFont(42);
    label_njets78_1->Draw();
    label_njets78_2->Draw();
    label_njets78_3->Draw();
    label_njets78_4->Draw();
    label_njets78_5->Draw();
    label_njets78_6->Draw();
  }
  else {
    TLatex* label_njets78_1 = new TLatex(0.125, 0.11, "1");
    TLatex* label_njets78_2 = new TLatex(0.075, 0.24, "10^{2}");
    TLatex* label_njets78_3 = new TLatex(0.075, 0.37, "10^{4}");
    TLatex* label_njets78_4 = new TLatex(0.075, 0.505, "10^{6}");
    TLatex* label_njets78_5 = new TLatex(0.075, 0.635, "10^{8}");
    TLatex* label_njets78_6 = new TLatex(0.059, 0.765, "10^{10}");
    label_njets78_1->SetNDC(); label_njets78_1->SetTextSize(0.07); label_njets78_1->SetTextFont(42);
    label_njets78_2->SetNDC(); label_njets78_2->SetTextSize(0.07); label_njets78_2->SetTextFont(42);
    label_njets78_3->SetNDC(); label_njets78_3->SetTextSize(0.07); label_njets78_3->SetTextFont(42);
    label_njets78_4->SetNDC(); label_njets78_4->SetTextSize(0.07); label_njets78_4->SetTextFont(42);
    label_njets78_5->SetNDC(); label_njets78_5->SetTextSize(0.07); label_njets78_5->SetTextFont(42);
    label_njets78_6->SetNDC(); label_njets78_6->SetTextSize(0.07); label_njets78_6->SetTextFont(42);
    label_njets78_1->Draw();
    label_njets78_2->Draw();
    label_njets78_3->Draw();
    label_njets78_4->Draw();
    label_njets78_5->Draw();
    label_njets78_6->Draw();
  }
  // test end
      // bpad
  c_njets89->cd();
  bpad_njets89 = new TPad("bpad_njets89","bpad_njets89",0.,0.,1.,0.305);
  bpad_njets89->SetLeftMargin(0.15);
  bpad_njets89->SetTopMargin(0.); bpad_njets89->SetBottomMargin(0.4); bpad_njets89->SetFillStyle(4000);
  bpad_njets89->Draw(); bpad_njets89->cd();

  TH1D* h_data_njets89_err = (TH1D*)h_data_njets89->Clone("h_data_njets89_err");
  h_data_njets89_err->SetMarkerSize(0);
  h_data_njets89_err->SetFillColor(kBlack);
  h_data_njets89_err->SetLineColor(kBlack);
  h_data_njets89_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets89_err->SetBinContent(imj, h_data_njets89->GetBinContent(imj)/h_tot_mc_njets89->GetBinContent(imj));
    h_data_njets89_err->SetBinError(imj, (h_data_njets89->GetBinContent(imj)/h_tot_mc_njets89->GetBinContent(imj))*(h_tot_mc_njets89->GetBinError(imj)/h_tot_mc_njets89->GetBinContent(imj)));
  }

  h_data_njets89_clone->Divide(h_tot_mc_njets89);
  h_data_njets89_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets89_clone->SetLineColor(kBlack);
  h_data_njets89_clone->SetLineWidth(2);
  h_data_njets89_clone->SetMarkerStyle(20);
  h_data_njets89_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets89_clone->SetBinError(imj, h_data_njets89_clone->GetBinContent(imj)*(h_data_njets89->GetBinError(imj)/h_data_njets89->GetBinContent(imj)));
  }
  h_data_njets89_clone->Draw("ep");
  h_data_njets89_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets89->Print(Form("plots/qcd_kappa/qcd_kappa_njets78_lumi%s.pdf", lumi_title.Data()));

    // njets 9-
  TPad *tpad_njets10(NULL), *bpad_njets10(NULL);
      // tpad
  TCanvas* c_njets10 = new TCanvas("c_njets10", "c_njets10", 800, 800);
  c_njets10->cd();
  tpad_njets10 = new TPad("tpad_njets10","tpad_njets10",0.,0.3,1.,1.);
  tpad_njets10->SetLeftMargin(0.15); tpad_njets10->SetBottomMargin(0.02); tpad_njets10->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets10->Draw();
  tpad_njets10->cd();
  gPad->SetLogy();
  h_data_njets10->GetYaxis()->SetLabelSize(0);
  h_data_njets10->Draw("EP");
  st_mc_njets10->Draw("same hist");
  h_data_njets10->Draw("same EP");
  h_signal_njets10_m1200->Draw("same hist");
  h_signal_njets10_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets10_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets9->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  // test
  if(year=="UL2016_comb") {
    TLatex* label_njets9_1 = new TLatex(0.12, 0.11, "1");
    label_njets9_1->SetNDC(); label_njets9_1->SetTextSize(0.07); label_njets9_1->SetTextFont(42);
    TLatex* label_njets9_2 = new TLatex(0.075, 0.252, "10^{2}");
    label_njets9_2->SetNDC(); label_njets9_2->SetTextSize(0.07); label_njets9_2->SetTextFont(42);
    TLatex* label_njets9_3 = new TLatex(0.075, 0.385, "10^{4}");
    label_njets9_3->SetNDC(); label_njets9_3->SetTextSize(0.07); label_njets9_3->SetTextFont(42);
    TLatex* label_njets9_4 = new TLatex(0.075, 0.52, "10^{6}");
    label_njets9_4->SetNDC(); label_njets9_4->SetTextSize(0.07); label_njets9_4->SetTextFont(42);
    TLatex* label_njets9_5 = new TLatex(0.075, 0.655, "10^{8}");
    label_njets9_5->SetNDC(); label_njets9_5->SetTextSize(0.07); label_njets9_5->SetTextFont(42);
    TLatex* label_njets9_6 = new TLatex(0.059, 0.788, "10^{10}");
    label_njets9_6->SetNDC(); label_njets9_6->SetTextSize(0.07); label_njets9_6->SetTextFont(42);
    label_njets9_1->Draw();
    label_njets9_2->Draw();
    label_njets9_3->Draw();
    label_njets9_4->Draw();
    label_njets9_5->Draw();
    label_njets9_6->Draw();
  }
  else {
    TLatex* label_njets9_1 = new TLatex(0.12, 0.11, "1");
    label_njets9_1->SetNDC(); label_njets9_1->SetTextSize(0.07); label_njets9_1->SetTextFont(42);
    TLatex* label_njets9_2 = new TLatex(0.075, 0.242, "10^{2}");
    label_njets9_2->SetNDC(); label_njets9_2->SetTextSize(0.07); label_njets9_2->SetTextFont(42);
    TLatex* label_njets9_3 = new TLatex(0.075, 0.372, "10^{4}");
    label_njets9_3->SetNDC(); label_njets9_3->SetTextSize(0.07); label_njets9_3->SetTextFont(42);
    TLatex* label_njets9_4 = new TLatex(0.075, 0.505, "10^{6}");
    label_njets9_4->SetNDC(); label_njets9_4->SetTextSize(0.07); label_njets9_4->SetTextFont(42);
    TLatex* label_njets9_5 = new TLatex(0.075, 0.628, "10^{8}");
    label_njets9_5->SetNDC(); label_njets9_5->SetTextSize(0.07); label_njets9_5->SetTextFont(42);
    TLatex* label_njets9_6 = new TLatex(0.059, 0.765, "10^{10}");
    label_njets9_6->SetNDC(); label_njets9_6->SetTextSize(0.07); label_njets9_6->SetTextFont(42);
    label_njets9_1->Draw();
    label_njets9_2->Draw();
    label_njets9_3->Draw();
    label_njets9_4->Draw();
    label_njets9_5->Draw();
    label_njets9_6->Draw();
  }
  // test end
      // bpad
  c_njets10->cd();
  bpad_njets10 = new TPad("bpad_njets10","bpad_njets10",0.,0.,1.,0.305);
  bpad_njets10->SetLeftMargin(0.15);
  bpad_njets10->SetTopMargin(0.); bpad_njets10->SetBottomMargin(0.4); bpad_njets10->SetFillStyle(4000);
  bpad_njets10->Draw(); bpad_njets10->cd();

  TH1D* h_data_njets10_err = (TH1D*)h_data_njets10->Clone("h_data_njets10_err");
  h_data_njets10_err->SetMarkerSize(0);
  h_data_njets10_err->SetFillColor(kBlack);
  h_data_njets10_err->SetLineColor(kBlack);
  h_data_njets10_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets10_err->SetBinContent(imj, h_data_njets10->GetBinContent(imj)/h_tot_mc_njets10->GetBinContent(imj));
    h_data_njets10_err->SetBinError(imj, (h_data_njets10->GetBinContent(imj)/h_tot_mc_njets10->GetBinContent(imj))*(h_tot_mc_njets10->GetBinError(imj)/h_tot_mc_njets10->GetBinContent(imj)));
  }

  h_data_njets10_clone->Divide(h_tot_mc_njets10);
  h_data_njets10_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets10_clone->SetLineColor(kBlack);
  h_data_njets10_clone->SetLineWidth(2);
  h_data_njets10_clone->SetMarkerStyle(20);
  h_data_njets10_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets10_clone->SetBinError(imj, h_data_njets10_clone->GetBinContent(imj)*(h_data_njets10->GetBinError(imj)/h_data_njets10->GetBinContent(imj)));
  }
  h_data_njets10_clone->Draw("ep");
  h_data_njets10_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets10->Print(Form("plots/qcd_kappa/qcd_kappa_njets9_lumi%s.pdf", lumi_title.Data()));


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
  TString folder_sig     = folder_year(year, false).at(3);

  vector<TString> s_data  = getRPVProcess(folder_kwj_dat, "data");
  vector<TString> s_dy    = getRPVProcess(folder_kwj,     "DY");

  vector<TString> s_qcd   = getRPVProcess(folder_kwj, "qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_kwj, "ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_kwj, "wjets");
  vector<TString> s_other = getRPVProcess(folder_kwj, "other_public_DY_without_wjets");
  vector<TString> s_sig_m1200 = getRPVProcess(folder_sig, "rpv_m1200");
  vector<TString> s_sig_m1800 = getRPVProcess(folder_sig, "rpv_m1800");

  // make small tree
  small_tree_rpv tree_data((static_cast<std::string>(s_data.at(0))));
  small_tree_rpv tree_dy((static_cast<std::string>(s_dy.at(0))));

  small_tree_rpv tree_qcd((static_cast<std::string>(s_qcd.at(0))));
  small_tree_rpv tree_ttbar((static_cast<std::string>(s_ttbar.at(0))));
  small_tree_rpv tree_wjets((static_cast<std::string>(s_wjets.at(0))));
  small_tree_rpv tree_other((static_cast<std::string>(s_other.at(0))));
  small_tree_rpv tree_signal_m1200((static_cast<std::string>(s_sig_m1200.at(0))));
  small_tree_rpv tree_signal_m1800((static_cast<std::string>(s_sig_m1800.at(0))));

  // append small tree
  appendTree(s_data, tree_data);
  appendTree(s_dy, tree_dy);
  appendTree(s_qcd, tree_qcd);
  appendTree(s_ttbar, tree_ttbar);
  appendTree(s_wjets, tree_wjets);
  appendTree(s_other, tree_other);
  appendTree(s_sig_m1200, tree_signal_m1200);
  appendTree(s_sig_m1800, tree_signal_m1800);


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
  TH1D* h_signal_njets34_m1200 = new TH1D("h_signal_njets34_m1200", "h_signal_njets34_m1200", 3, 500, 1400);
  TH1D* h_signal_njets56_m1200 = new TH1D("h_signal_njets56_m1200", "h_signal_njets56_m1200", 3, 500, 1400);
  TH1D* h_signal_njets7_m1200  = new TH1D("h_signal_njets7_m1200",  "h_signal_njets7_m1200",  3, 500, 1400);
  TH1D* h_signal_njets34_m1800 = new TH1D("h_signal_njets34_m1800", "h_signal_njets34_m1800", 3, 500, 1400);
  TH1D* h_signal_njets56_m1800 = new TH1D("h_signal_njets56_m1800", "h_signal_njets56_m1800", 3, 500, 1400);
  TH1D* h_signal_njets7_m1800  = new TH1D("h_signal_njets7_m1800",  "h_signal_njets7_m1800",  3, 500, 1400);


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
  pass_dy_selection(tree_signal_m1200, h_signal_njets34_m1200, "mc",   "34", year, "mj");
  pass_dy_selection(tree_signal_m1200, h_signal_njets56_m1200, "mc",   "56", year, "mj");
  pass_dy_selection(tree_signal_m1200, h_signal_njets7_m1200,  "mc",   "7",  year, "mj");
  pass_dy_selection(tree_signal_m1800, h_signal_njets34_m1800, "mc",   "34", year, "mj");
  pass_dy_selection(tree_signal_m1800, h_signal_njets56_m1800, "mc",   "56", year, "mj");
  pass_dy_selection(tree_signal_m1800, h_signal_njets7_m1800,  "mc",   "7",  year, "mj");

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

  // Modify xsec of signal process (NLO+NLL -> NNLO+NNLL)
    // gluino mass 1200
  TH1D* h_signal_njets34_m1200_clone = (TH1D*)h_signal_njets34_m1200->Clone("h_signal_njets34_m1200_clone");
  TH1D* h_signal_njets56_m1200_clone = (TH1D*)h_signal_njets56_m1200->Clone("h_signal_njets56_m1200_clone");
  TH1D* h_signal_njets7_m1200_clone = (TH1D*)h_signal_njets7_m1200->Clone("h_signal_njets7_m1200_clone");
    // gluino mass 1800
  TH1D* h_signal_njets34_m1800_clone = (TH1D*)h_signal_njets34_m1800->Clone("h_signal_njets34_m1800_clone");
  TH1D* h_signal_njets56_m1800_clone = (TH1D*)h_signal_njets56_m1800->Clone("h_signal_njets56_m1800_clone");
  TH1D* h_signal_njets7_m1800_clone = (TH1D*)h_signal_njets7_m1800->Clone("h_signal_njets7_m1800_clone");
  for(int i=1; i<4; i++) {
    h_signal_njets34_m1200->SetBinContent(i, h_signal_njets34_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    h_signal_njets56_m1200->SetBinContent(i, h_signal_njets56_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    h_signal_njets7_m1200->SetBinContent(i, h_signal_njets7_m1200_clone->GetBinContent(i)*0.01*0.1024/0.985E-01);
    h_signal_njets34_m1800->SetBinContent(i, h_signal_njets34_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
    h_signal_njets56_m1800->SetBinContent(i, h_signal_njets56_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
    h_signal_njets7_m1800->SetBinContent(i, h_signal_njets7_m1800_clone->GetBinContent(i)*0.003349/0.293E-02);
  }

  // for year-combined plots
  TFile* f = new TFile("data/wjets_kappa_meas_"+year+".root", "recreate");
  f->cd();
  h_data_njets34_clone->Write();
  h_data_njets56_clone->Write();
  h_data_njets7_clone->Write();
  h_dy_njets34_clone->Write();
  h_dy_njets56_clone->Write();
  h_dy_njets7_clone->Write();
  h_qcd_njets34_clone->Write();
  h_qcd_njets56_clone->Write();
  h_qcd_njets7_clone->Write();
  h_ttbar_njets34_clone->Write();
  h_ttbar_njets56_clone->Write();
  h_ttbar_njets7_clone->Write();
  h_wjets_njets34_clone->Write();
  h_wjets_njets56_clone->Write();
  h_wjets_njets7_clone->Write();
  h_other_njets34_clone->Write();
  h_other_njets56_clone->Write();
  h_other_njets7_clone->Write();
  h_signal_njets34_m1200->Write();
  h_signal_njets56_m1200->Write();
  h_signal_njets7_m1200->Write();
  h_signal_njets34_m1800->Write();
  h_signal_njets56_m1800->Write();
  h_signal_njets7_m1800->Write();
  f->Close();


  cout << "[m1200]" << endl;
  cout << "    njet34" << endl;
  cout << "[1]: " << h_signal_njets34_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets34_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets34_m1200->GetBinContent(3) << endl;
  cout << "njet56" << endl;
  cout << "[1]: " << h_signal_njets56_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets56_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets56_m1200->GetBinContent(3) << endl;
  cout << "njet7" << endl;
  cout << "[1]: " << h_signal_njets7_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets7_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets7_m1200->GetBinContent(3) << endl;
  cout << endl;
  cout << "[m1800]" << endl;
  cout << "    njet34" << endl;
  cout << "[1]: " << h_signal_njets34_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets34_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets34_m1800->GetBinContent(3) << endl;
  cout << "njet56" << endl;
  cout << "[1]: " << h_signal_njets56_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets56_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets56_m1800->GetBinContent(3) << endl;
  cout << "njet7" << endl;
  cout << "[1]: " << h_signal_njets7_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets7_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets7_m1800->GetBinContent(3) << endl;

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
  h_data_njets34_clone_test->Add(h_other_mc_njets34, -1);
  h_data_njets56_clone_test->Add(h_other_mc_njets56, -1);
  h_data_njets7_clone_test->Add(h_other_mc_njets7, -1);
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
  h_data_njets34->SetMarkerStyle(20); h_data_njets34->SetMarkerSize(2);
  h_data_njets34->SetLineColor(kBlack); h_dy_njets34->SetLineColor(kBlack); h_qcd_njets34->SetLineColor(kBlack); h_ttbar_njets34->SetLineColor(kBlack); h_wjets_njets34->SetLineColor(kBlack); h_other_njets34->SetLineColor(kBlack);
  h_dy_njets34->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets34->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets34->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets34->SetFillColor(TColor::GetColor("#832db6")); h_other_njets34->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets34->SetLineWidth(2); h_dy_njets34->SetLineWidth(1); h_qcd_njets34->SetLineWidth(1); h_ttbar_njets34->SetLineWidth(1); h_wjets_njets34->SetLineWidth(1); h_other_njets34->SetLineWidth(1);
  h_data_njets34->SetTitle("");
  h_data_njets34->GetXaxis()->SetLabelOffset(1);
  h_data_njets34->GetYaxis()->SetLabelSize(0.07); h_data_njets34->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets34->GetYaxis()->SetTitleOffset(0.92); h_data_njets34->GetYaxis()->SetTitleSize(0.08);
  h_data_njets34->SetMinimum(0.002); h_data_njets34->SetMaximum(h_data_njets34->GetBinContent(1)*100000);
  h_data_njets34_clone->SetTitle("");
  h_data_njets34_clone->GetXaxis()->SetNdivisions(505); h_data_njets34_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets34_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets34_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets34_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets34_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets34_clone->GetYaxis()->SetNdivisions(505); h_data_njets34_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets34_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets34_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets34_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets34_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets34_clone->GetXaxis()->SetLabelSize(0);
    // njets 5-6
  h_data_njets56->SetMarkerStyle(20); h_data_njets56->SetMarkerSize(2);
  h_data_njets56->SetLineColor(kBlack); h_dy_njets56->SetLineColor(kBlack); h_qcd_njets56->SetLineColor(kBlack); h_ttbar_njets56->SetLineColor(kBlack); h_wjets_njets56->SetLineColor(kBlack); h_other_njets56->SetLineColor(kBlack);
  h_dy_njets56->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets56->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets56->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets56->SetFillColor(TColor::GetColor("#832db6")); h_other_njets56->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets56->SetLineWidth(2); h_dy_njets56->SetLineWidth(1); h_qcd_njets56->SetLineWidth(1); h_ttbar_njets56->SetLineWidth(1); h_wjets_njets56->SetLineWidth(1); h_other_njets56->SetLineWidth(1);
  h_data_njets56->SetTitle("");
  h_data_njets56->GetXaxis()->SetLabelOffset(1);
  h_data_njets56->GetYaxis()->SetLabelSize(0.07); h_data_njets56->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets56->GetYaxis()->SetTitleOffset(0.92); h_data_njets56->GetYaxis()->SetTitleSize(0.08);
  h_data_njets56->SetMinimum(0.002); h_data_njets56->SetMaximum(h_data_njets56->GetBinContent(1)*100000);
  h_data_njets56_clone->SetTitle("");
  h_data_njets56_clone->GetXaxis()->SetNdivisions(505); h_data_njets56_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets56_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets56_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets56_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets56_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets56_clone->GetYaxis()->SetNdivisions(505); h_data_njets56_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets56_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets56_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets56_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets56_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets56_clone->GetXaxis()->SetLabelSize(0);
    // njets 7-
  h_data_njets7->SetMarkerStyle(20); h_data_njets7->SetMarkerSize(2);
  h_data_njets7->SetLineColor(kBlack); h_dy_njets7->SetLineColor(kBlack); h_qcd_njets7->SetLineColor(kBlack); h_ttbar_njets7->SetLineColor(kBlack); h_wjets_njets7->SetLineColor(kBlack); h_other_njets7->SetLineColor(kBlack);
  h_data_njets7->SetLineWidth(2); h_dy_njets7->SetLineWidth(1); h_qcd_njets7->SetLineWidth(1); h_ttbar_njets7->SetLineWidth(1); h_wjets_njets7->SetLineWidth(1); h_other_njets7->SetLineWidth(1);
  h_dy_njets7->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets7->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets7->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets7->SetFillColor(TColor::GetColor("#832db6")); h_other_njets7->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets7->SetTitle("");
  h_data_njets7->GetXaxis()->SetLabelOffset(1);
  h_data_njets7->GetYaxis()->SetLabelSize(0.07); h_data_njets7->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets7->GetYaxis()->SetTitleOffset(0.92); h_data_njets7->GetYaxis()->SetTitleSize(0.08);
  h_data_njets7->SetMinimum(0.002); h_data_njets7->SetMaximum(h_data_njets7->GetBinContent(1)*100000);
  h_data_njets7_clone->SetTitle("");
  h_data_njets7_clone->GetXaxis()->SetNdivisions(505); h_data_njets7_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets7_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets7_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets7_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets7_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets7_clone->GetYaxis()->SetNdivisions(505); h_data_njets7_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets7_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets7_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets7_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets7_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets7_clone->GetXaxis()->SetLabelSize(0);

  h_signal_njets34_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1200->SetLineWidth(4); h_signal_njets34_m1200->SetLineStyle(2);
  h_signal_njets56_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1200->SetLineWidth(4); h_signal_njets56_m1200->SetLineStyle(2);
  h_signal_njets7_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1200->SetLineWidth(4); h_signal_njets7_m1200->SetLineStyle(2);
  h_signal_njets34_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1800->SetLineWidth(4); h_signal_njets34_m1800->SetLineStyle(1);
  h_signal_njets56_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1800->SetLineWidth(4); h_signal_njets56_m1800->SetLineStyle(1);
  h_signal_njets7_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1800->SetLineWidth(4); h_signal_njets7_m1800->SetLineStyle(1);

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.89, 0.95, Form("%.1f fb^{-1} (13 TeV)", lumi));
  if(year=="UL20178_comb") tex_lumi = new TLatex(0.89, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.07);
  //TLatex *TexCMS = new TLatex(0.15,0.925,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.15,0.925,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.07);
  TexCMS->SetLineWidth(2);

  TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
  TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
  TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
  TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
  tex_mj500->SetTextSize(0.15); tex_mj800->SetTextSize(0.15); tex_mj1100->SetTextSize(0.15); tex_mj1400->SetTextSize(0.15);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

  TLatex* tex_Nlep2   = new TLatex(0.19, 0.81, "N_{lep} = 2 (OSSF)");
  TLatex* tex_mll     = new TLatex(0.19, 0.715, "81 < m_{ll} < 101 GeV");
  TLatex* tex_Njets34 = new TLatex(0.19, 0.62, "3 #leq N_{jet} #leq 4");
  TLatex* tex_Njets56 = new TLatex(0.19, 0.62, "5 #leq N_{jet} #leq 6");
  TLatex* tex_Njets7  = new TLatex(0.19, 0.62, "N_{jet} #geq 7");
  TLatex* tex_Nb2     = new TLatex(0.19, 0.525, "N_{b} #leq 2");
  tex_Nlep2->SetNDC();   tex_Nlep2->SetTextFont(42);   tex_Nlep2->SetTextSize(0.055);
  tex_mll->SetNDC();     tex_mll->SetTextFont(42);     tex_mll->SetTextSize(0.055);
  tex_Njets34->SetNDC(); tex_Njets34->SetTextFont(42); tex_Njets34->SetTextSize(0.055);
  tex_Njets56->SetNDC(); tex_Njets56->SetTextFont(42); tex_Njets56->SetTextSize(0.055);
  tex_Njets7->SetNDC();  tex_Njets7->SetTextFont(42);  tex_Njets7->SetTextSize(0.055);
  tex_Nb2->SetNDC();     tex_Nb2->SetTextFont(42);     tex_Nb2->SetTextSize(0.055);

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
  TLegend* l_njets34_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets34_2->SetTextSize(0.05);
  l_njets34_2->SetBorderSize(0);
  l_njets34_2->SetFillStyle(0);
  l_njets34_2->AddEntry(h_data_njets34,  "data", "elp");
  l_njets34_2->AddEntry(h_dy_njets34,    "Drell-Yan", "f");
  l_njets34_2->AddEntry(h_qcd_njets34,   "QCD", "f");
  l_njets34_2->AddEntry(h_ttbar_njets34, "t#bar{t}", "f");
  l_njets34_2->AddEntry(h_wjets_njets34, "W+jets", "f");
  l_njets34_2->AddEntry(h_other_njets34, "Other", "f");
  l_njets34_2->AddEntry(h_signal_njets34_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets34_2->AddEntry(h_signal_njets34_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 5-6
  TLegend* l_njets56_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets56_2->SetTextSize(0.05);
  l_njets56_2->SetBorderSize(0);
  l_njets56_2->SetFillStyle(0);
  l_njets56_2->AddEntry(h_data_njets56,  "data", "elp");
  l_njets56_2->AddEntry(h_dy_njets56,    "Drell-Yan", "f");
  l_njets56_2->AddEntry(h_qcd_njets56,   "QCD", "f");
  l_njets56_2->AddEntry(h_ttbar_njets56, "t#bar{t}", "f");
  l_njets56_2->AddEntry(h_wjets_njets56, "W+jets", "f");
  l_njets56_2->AddEntry(h_other_njets56, "Other", "f");
  l_njets56_2->AddEntry(h_signal_njets56_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets56_2->AddEntry(h_signal_njets56_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 7
  TLegend* l_njets7_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets7_2->SetTextSize(0.05);
  l_njets7_2->SetBorderSize(0);
  l_njets7_2->SetFillStyle(0);
  l_njets7_2->AddEntry(h_data_njets7,  "data", "elp");
  l_njets7_2->AddEntry(h_dy_njets7,    "Drell-Yan", "f");
  l_njets7_2->AddEntry(h_qcd_njets7,   "QCD", "f");
  l_njets7_2->AddEntry(h_ttbar_njets7, "t#bar{t}", "f");
  l_njets7_2->AddEntry(h_wjets_njets7, "W+jets", "f");
  l_njets7_2->AddEntry(h_other_njets7, "Other", "f");
  l_njets7_2->AddEntry(h_signal_njets7_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets7_2->AddEntry(h_signal_njets7_m1800, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);

    // njets 4-5
  TPad *tpad_njets34(NULL), *bpad_njets34(NULL);
      // tpad
  TCanvas* c_njets34 = new TCanvas("c_njets34", "c_njets34", 800, 800);
  c_njets34->cd();
  tpad_njets34 = new TPad("tpad_njets34","tpad_njets34",0.,0.3,1.,1.);
  tpad_njets34->SetLeftMargin(0.15); tpad_njets34->SetBottomMargin(0.02); tpad_njets34->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets34->Draw();
  tpad_njets34->cd();
  gPad->SetLogy();
  h_data_njets34->Draw("EP");
  st_mc_njets34->Draw("same hist");
  h_data_njets34->Draw("same EP");
  h_signal_njets34_m1200->SetFillStyle(0);
  h_signal_njets34_m1200->Draw("same hist");
  h_signal_njets34_m1800->SetFillStyle(0);
  h_signal_njets34_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets34_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets34->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets34->cd();
  bpad_njets34 = new TPad("bpad_njets34","bpad_njets34",0.,0.,1.,0.305);
  bpad_njets34->SetLeftMargin(0.15);
  bpad_njets34->SetTopMargin(0.); bpad_njets34->SetBottomMargin(0.4); bpad_njets34->SetFillStyle(4000);
  bpad_njets34->Draw(); bpad_njets34->cd();

  TH1D* h_data_njets34_err = (TH1D*)h_data_njets34->Clone("h_data_njets34_err");
  h_data_njets34_err->SetMarkerSize(0);
  h_data_njets34_err->SetFillColor(kBlack);
  h_data_njets34_err->SetLineColor(kBlack);
  h_data_njets34_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets34_err->SetBinContent(imj, h_data_njets34->GetBinContent(imj)/h_tot_mc_njets34->GetBinContent(imj));
    h_data_njets34_err->SetBinError(imj, (h_data_njets34->GetBinContent(imj)/h_tot_mc_njets34->GetBinContent(imj))*(h_tot_mc_njets34->GetBinError(imj)/h_tot_mc_njets34->GetBinContent(imj)));
  }

  h_data_njets34_clone->Divide(h_tot_mc_njets34);
  h_data_njets34_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets34_clone->SetLineColor(kBlack);
  h_data_njets34_clone->SetLineWidth(2);
  h_data_njets34_clone->SetMarkerStyle(20);
  h_data_njets34_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets34_clone->SetBinError(imj, h_data_njets34_clone->GetBinContent(imj)*(h_data_njets34->GetBinError(imj)/h_data_njets34->GetBinContent(imj)));
  }
  h_data_njets34_clone->Draw("ep");
  h_data_njets34_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets34->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets34_lumi%s.pdf", lumi_title.Data()));

    // njets 5-6
  TPad *tpad_njets56(NULL), *bpad_njets56(NULL);
      // tpad
  TCanvas* c_njets56 = new TCanvas("c_njets56", "c_njets56", 800, 800);
  c_njets56->cd();
  tpad_njets56 = new TPad("tpad_njets56","tpad_njets56",0.,0.3,1.,1.);
  tpad_njets56->SetLeftMargin(0.15); tpad_njets56->SetBottomMargin(0.02); tpad_njets56->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets56->Draw();
  tpad_njets56->cd();
  gPad->SetLogy();
  h_data_njets56->Draw("EP");
  st_mc_njets56->Draw("same hist");
  h_data_njets56->Draw("same EP");
  h_signal_njets56_m1200->SetFillStyle(0);
  h_signal_njets56_m1200->Draw("same hist");
  h_signal_njets56_m1800->SetFillStyle(0);
  h_signal_njets56_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets56_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets56->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets56->cd();
  bpad_njets56 = new TPad("bpad_njets56","bpad_njets56",0.,0.,1.,0.305);
  bpad_njets56->SetLeftMargin(0.15);
  bpad_njets56->SetTopMargin(0.); bpad_njets56->SetBottomMargin(0.4); bpad_njets56->SetFillStyle(4000);
  bpad_njets56->Draw(); bpad_njets56->cd();

  TH1D* h_data_njets56_err = (TH1D*)h_data_njets56->Clone("h_data_njets56_err");
  h_data_njets56_err->SetMarkerSize(0);
  h_data_njets56_err->SetFillColor(kBlack);
  h_data_njets56_err->SetLineColor(kBlack);
  h_data_njets56_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets56_err->SetBinContent(imj, h_data_njets56->GetBinContent(imj)/h_tot_mc_njets56->GetBinContent(imj));
    h_data_njets56_err->SetBinError(imj, (h_data_njets56->GetBinContent(imj)/h_tot_mc_njets56->GetBinContent(imj))*(h_tot_mc_njets56->GetBinError(imj)/h_tot_mc_njets56->GetBinContent(imj)));
  }

  h_data_njets56_clone->Divide(h_tot_mc_njets56);
  h_data_njets56_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets56_clone->SetLineColor(kBlack);
  h_data_njets56_clone->SetLineWidth(2);
  h_data_njets56_clone->SetMarkerStyle(20);
  h_data_njets56_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets56_clone->SetBinError(imj, h_data_njets56_clone->GetBinContent(imj)*(h_data_njets56->GetBinError(imj)/h_data_njets56->GetBinContent(imj)));
  }
  h_data_njets56_clone->Draw("ep");
  h_data_njets56_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets56->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets56_lumi%s.pdf", lumi_title.Data()));

    // njets 7-
  TPad *tpad_njets7(NULL), *bpad_njets7(NULL);
      // tpad
  TCanvas* c_njets7 = new TCanvas("c_njets7", "c_njets7", 800, 800);
  c_njets7->cd();
  tpad_njets7 = new TPad("tpad_njets7","tpad_njets7",0.,0.3,1.,1.);
  tpad_njets7->SetLeftMargin(0.15); tpad_njets7->SetBottomMargin(0.02); tpad_njets7->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets7->Draw();
  tpad_njets7->cd();
  gPad->SetLogy();
  h_data_njets7->Draw("EP");
  st_mc_njets7->Draw("same hist");
  h_data_njets7->Draw("same EP");
  h_signal_njets7_m1200->SetFillStyle(0);
  h_signal_njets7_m1200->Draw("same hist");
  h_signal_njets7_m1800->SetFillStyle(0);
  h_signal_njets7_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets7_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets7->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets7->cd();
  bpad_njets7 = new TPad("bpad_njets7","bpad_njets7",0.,0.,1.,0.305);
  bpad_njets7->SetLeftMargin(0.15);
  bpad_njets7->SetTopMargin(0.); bpad_njets7->SetBottomMargin(0.4); bpad_njets7->SetFillStyle(4000);
  bpad_njets7->Draw(); bpad_njets7->cd();

  TH1D* h_data_njets7_err = (TH1D*)h_data_njets7->Clone("h_data_njets7_err");
  h_data_njets7_err->SetMarkerSize(0);
  h_data_njets7_err->SetFillColor(kBlack);
  h_data_njets7_err->SetLineColor(kBlack);
  h_data_njets7_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets7_err->SetBinContent(imj, h_data_njets7->GetBinContent(imj)/h_tot_mc_njets7->GetBinContent(imj));
    h_data_njets7_err->SetBinError(imj, (h_data_njets7->GetBinContent(imj)/h_tot_mc_njets7->GetBinContent(imj))*(h_tot_mc_njets7->GetBinError(imj)/h_tot_mc_njets7->GetBinContent(imj)));
  }

  h_data_njets7_clone->Divide(h_tot_mc_njets7);
  h_data_njets7_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets7_clone->SetLineColor(kBlack);
  h_data_njets7_clone->SetLineWidth(2);
  h_data_njets7_clone->SetMarkerStyle(20);
  h_data_njets7_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets7_clone->SetBinError(imj, h_data_njets7_clone->GetBinContent(imj)*(h_data_njets7->GetBinError(imj)/h_data_njets7->GetBinContent(imj)));
  }
  h_data_njets7_clone->Draw("ep");
  h_data_njets7_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets7->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets7_lumi%s.pdf", lumi_title.Data()));


}

void ttbar_kappa_plot(TString year)
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
  if(year=="UL2016") 		  {lumi=36.3;  lumi_title="36p3";}
  else if(year=="UL20178")	  {lumi=101.3; lumi_title="101p3";}
  else if(year=="UL201678")	  {lumi=138; lumi_title="138";}
  else {cout << "Please input the year as UL2016/UL20178/UL201678" << endl;}

  // for data
  TFile* infile = new TFile(Form("variations/output_impact_%s.root", year.Data()), "READ");
  // for mc
  std::string resultsFilename;
  if(year=="UL201678") resultsFilename=Form("mlfit_cr_CRFit_%s_hadded.root",year.Data());
  else resultsFilename=Form("mlfit_cr_CRFit_%s.root",year.Data());
  TFile *fResults = TFile::Open(resultsFilename.c_str());
  RooFitResult *result_b = static_cast<RooFitResult*>(fResults->Get("fit_b"));

  TH1F *h_data[6], *h_qcd_mlfit[6], *h_ttbar_mlfit[6], *h_wjets_mlfit[6], *h_other_mlfit[6], *h_signal_m1200[6], *h_signal_m1800[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_data[ibin]    = static_cast<TH1F*>(infile->Get(Form("bin%i/data_obs", i)));
    h_signal_m1200[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1200", i)));
    h_signal_m1800[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1800", i)));
    h_qcd_mlfit[ibin]    = static_cast<TH1F*>(fResults->Get(Form("shapes_fit_b/bin%i/qcd", i)));
    h_ttbar_mlfit[ibin]  = static_cast<TH1F*>(fResults->Get(Form("shapes_fit_b/bin%i/ttbar", i)));
    h_wjets_mlfit[ibin]  = static_cast<TH1F*>(fResults->Get(Form("shapes_fit_b/bin%i/wjets", i)));
    h_other_mlfit[ibin]  = static_cast<TH1F*>(fResults->Get(Form("shapes_fit_b/bin%i/other", i)));
  }

  TH1F *h_qcd[6], *h_ttbar[6], *h_wjets[6], *h_other[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_qcd[ibin] = new TH1F(Form("h_qcd_%d",ibin), Form("h_qcd_%d",ibin), 3, 500, 1400);
    h_ttbar[ibin] = new TH1F(Form("h_ttbar_%d",ibin), Form("h_ttbar_%d",ibin), 3, 500, 1400);
    h_wjets[ibin] = new TH1F(Form("h_wjets_%d",ibin), Form("h_wjets_%d",ibin), 3, 500, 1400);
    h_other[ibin] = new TH1F(Form("h_other_%d",ibin), Form("h_other_%d",ibin), 3, 500, 1400);
    for(int imj=1; imj<4; imj++) {
      h_qcd[ibin]->SetBinContent(imj, h_qcd_mlfit[ibin]->GetBinContent(imj));
      h_ttbar[ibin]->SetBinContent(imj, h_ttbar_mlfit[ibin]->GetBinContent(imj));
      h_wjets[ibin]->SetBinContent(imj, h_wjets_mlfit[ibin]->GetBinContent(imj));
      h_other[ibin]->SetBinContent(imj, h_other_mlfit[ibin]->GetBinContent(imj));
    }
  }

  // Make clone
  TH1F *h_data_clone[6], *h_qcd_clone[6], *h_ttbar_clone[6], *h_wjets_clone[6], *h_other_clone[6], *h_data_err[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_data_clone[ibin]   = (TH1F*)h_data[ibin]->Clone(Form("h_data_clone_%d", ibin));
    h_qcd_clone[ibin]    = (TH1F*)h_qcd[ibin]->Clone(Form("h_data_clone_%d", ibin));
    h_ttbar_clone[ibin]  = (TH1F*)h_ttbar[ibin]->Clone(Form("h_ttbar_clone_%d", ibin));
    h_wjets_clone[ibin]  = (TH1F*)h_wjets[ibin]->Clone(Form("h_data_clone_%d", ibin));
    h_other_clone[ibin]  = (TH1F*)h_other[ibin]->Clone(Form("h_other_clone_%d", ibin));
    h_data_err[ibin]   = (TH1F*)h_data[ibin]->Clone(Form("h_data_err_%d", ibin));
  }

  // Modify xsec of signal process (NLO+NLL -> NNLO+NNLL)
    // gluino mass 1800
    // error is not considered because it is not drawn in the plot

  // It does not need to change xsec of signal process because in ttbar kappa meas signal is from variations file
  TH1F *h_signal_m1200_clone[6], *h_sigmal_m1800_clone[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_signal_m1200_clone[ibin] = (TH1F*)h_signal_m1200[ibin]->Clone(Form("h_signal_m1200_clone_%d", ibin));
    h_signal_m1200[ibin]->SetBinContent(1, h_signal_m1200_clone[ibin]->GetBinContent(1)*0.01);
    h_signal_m1200[ibin]->SetBinContent(2, h_signal_m1200_clone[ibin]->GetBinContent(2)*0.01);
    h_signal_m1200[ibin]->SetBinContent(3, h_signal_m1200_clone[ibin]->GetBinContent(3)*0.01);
  }

  TH1F *h_tot_mc[6], *h_other_mc[6], *h_data_minus_others[6], *h_tot_mc_clone[6];
  float sf[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    // total mc
    h_tot_mc[ibin] = (TH1F*)h_ttbar_clone[ibin]->Clone(Form("h_tot_mc_%d", ibin));
    h_tot_mc[ibin]->Add(h_qcd_clone[ibin]); h_tot_mc[ibin]->Add(h_wjets_clone[ibin]); h_tot_mc[ibin]->Add(h_other_clone[ibin]);
    h_tot_mc_clone[ibin] = (TH1F*)h_tot_mc[ibin]->Clone(Form("h_tot_mc_clone_%d",ibin));

    // SF
    sf[ibin] = h_data[ibin]->Integral(1,-1)/h_tot_mc[ibin]->Integral(1,-1);
    // other mc (total mc - qcd)
    h_other_mc[ibin] = (TH1F*)h_qcd_clone[ibin]->Clone(Form("h_other_mc_%d", ibin));
    h_other_mc[ibin]->Add(h_wjets_clone[ibin]); h_other_mc[ibin]->Add(h_other_clone[ibin]);
    // normalized other mc
    h_other_mc[ibin]->Scale(sf[ibin]);
    // data - other mc
    h_data_minus_others[ibin] = (TH1F*)h_data_clone[ibin]->Clone(Form("h_data_minus_others_%d", ibin));
    h_data_minus_others[ibin]->Add(h_other_mc[ibin],-1);
  }

  // To validate kappa values against those from ./run/make_kappa_CRFit.exe
  cout << "Kappa" << endl;
  cout << "Low Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others[3]->GetBinContent(2)/h_data_minus_others[3]->GetBinContent(1))/(h_ttbar_clone[3]->GetBinContent(2)/h_ttbar_clone[3]->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others[3]->GetBinContent(3)/h_data_minus_others[3]->GetBinContent(1))/(h_ttbar_clone[3]->GetBinContent(3)/h_ttbar_clone[3]->GetBinContent(1)) << endl;
  cout << "Mid Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others[4]->GetBinContent(2)/h_data_minus_others[4]->GetBinContent(1))/(h_ttbar_clone[4]->GetBinContent(2)/h_ttbar_clone[4]->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others[4]->GetBinContent(3)/h_data_minus_others[4]->GetBinContent(1))/(h_ttbar_clone[4]->GetBinContent(3)/h_ttbar_clone[4]->GetBinContent(1)) << endl;
  cout << "High Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others[5]->GetBinContent(2)/h_data_minus_others[5]->GetBinContent(1))/(h_ttbar_clone[5]->GetBinContent(2)/h_ttbar_clone[5]->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others[5]->GetBinContent(3)/h_data_minus_others[5]->GetBinContent(1))/(h_ttbar_clone[5]->GetBinContent(3)/h_ttbar_clone[5]->GetBinContent(1)) << endl;
  cout << endl;
  // validate end

  // Cosmetics
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_data[ibin]->SetMarkerStyle(20); h_data[ibin]->SetMarkerSize(2);
    h_data[ibin]->SetLineColor(kBlack); h_qcd[ibin]->SetLineColor(kBlack); h_ttbar[ibin]->SetLineColor(kBlack); h_wjets[ibin]->SetLineColor(kBlack); h_other[ibin]->SetLineColor(kBlack);
    h_qcd[ibin]->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar[ibin]->SetFillColor(TColor::GetColor("#3f90da")); h_wjets[ibin]->SetFillColor(TColor::GetColor("#832db6")); h_other[ibin]->SetFillColor(TColor::GetColor("#94a4a2"));
    h_data[ibin]->SetLineWidth(2); h_qcd[ibin]->SetLineWidth(1); h_ttbar[ibin]->SetLineWidth(1); h_wjets[ibin]->SetLineWidth(1); h_other[ibin]->SetLineWidth(1);
    h_data[ibin]->SetTitle("");
    h_data[ibin]->GetXaxis()->SetLabelOffset(1);
    h_data[ibin]->GetYaxis()->SetLabelSize(0.07); h_data[ibin]->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data[ibin]->GetYaxis()->SetTitleOffset(0.92); h_data[ibin]->GetYaxis()->SetTitleSize(0.08);
    h_data[ibin]->SetMinimum(0.02); h_data[ibin]->SetMaximum(h_data[ibin]->GetBinContent(1)*100000);
    h_data_clone[ibin]->SetTitle("");
    h_data_clone[ibin]->GetXaxis()->SetNdivisions(505); h_data_clone[ibin]->GetXaxis()->SetLabelSize(0.12); h_data_clone[ibin]->GetXaxis()->SetLabelOffset(0.025); h_data_clone[ibin]->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_clone[ibin]->GetXaxis()->SetTitleOffset(0.95); h_data_clone[ibin]->GetXaxis()->SetTitleSize(0.19);
    h_data_clone[ibin]->GetYaxis()->SetNdivisions(505); h_data_clone[ibin]->GetYaxis()->SetLabelSize(0.15); h_data_clone[ibin]->GetYaxis()->SetTitle("Data / MC"); h_data_clone[ibin]->GetYaxis()->SetTitleSize(0.18); h_data_clone[ibin]->GetYaxis()->SetTitleOffset(0.41); h_data_clone[ibin]->GetYaxis()->SetLabelOffset(0.015);
    h_data_clone[ibin]->GetXaxis()->SetLabelSize(0);

    h_signal_m1200[ibin]->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_m1200[ibin]->SetLineWidth(4); h_signal_m1200[ibin]->SetLineStyle(2);
    h_signal_m1800[ibin]->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_m1800[ibin]->SetLineWidth(4); h_signal_m1800[ibin]->SetLineStyle(1);
  }

  // Normalize
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    h_qcd[ibin]->Scale(sf[ibin]);    h_other[ibin]->Scale(sf[ibin]);  h_wjets[ibin]->Scale(sf[ibin]); h_ttbar[ibin]->Scale(sf[ibin]); h_tot_mc[ibin]->Scale(sf[ibin]);
    cout << Form("sf[bin%d]: ", i) << sf[ibin] << endl;
  }

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.89, 0.95, Form("%.1f fb^{-1} (13 TeV)", lumi));
  if(year=="UL20178"||year=="UL201678") tex_lumi = new TLatex(0.89, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.07);
  //TLatex *TexCMS = new TLatex(0.15,0.925,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.15,0.925,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.07);
  TexCMS->SetLineWidth(2);

  TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
  TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
  TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
  TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
  tex_mj500->SetTextSize(0.15); tex_mj800->SetTextSize(0.15); tex_mj1100->SetTextSize(0.15); tex_mj1400->SetTextSize(0.15);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

  TLatex* tex_Nlep1   = new TLatex(0.20, 0.78, "N_{lep} = 1");
  TLatex* tex_Njets45 = new TLatex(0.20, 0.67, "4 #leq N_{jet} #leq 5");
  TLatex* tex_Njets67 = new TLatex(0.20, 0.67, "6 #leq N_{jet} #leq 7");
  TLatex* tex_Njets8  = new TLatex(0.20, 0.67, "N_{jet} #geq 8");
  TLatex* tex_Nb0     = new TLatex(0.20, 0.56, "N_{b} = 0");
  TLatex* tex_Nb1     = new TLatex(0.20, 0.56, "N_{b} = 1");
  tex_Nlep1->SetNDC();   tex_Nlep1->SetTextFont(42);   tex_Nlep1->SetTextSize(0.07);
  tex_Njets45->SetNDC(); tex_Njets45->SetTextFont(42); tex_Njets45->SetTextSize(0.07);
  tex_Njets67->SetNDC(); tex_Njets67->SetTextFont(42); tex_Njets67->SetTextSize(0.07);
  tex_Njets8->SetNDC();  tex_Njets8->SetTextFont(42);  tex_Njets8->SetTextSize(0.07);
  tex_Nb0->SetNDC();     tex_Nb0->SetTextFont(42);     tex_Nb0->SetTextSize(0.07);
  tex_Nb1->SetNDC();     tex_Nb1->SetTextFont(42);     tex_Nb1->SetTextSize(0.07);

  // Make THStack
  THStack* st_mc[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    st_mc[ibin] = new THStack(Form("st_mc_%d", i), Form("st_mc_%d",i));
    st_mc[ibin]->Add(h_other[ibin]); st_mc[ibin]->Add(h_wjets[ibin]); st_mc[ibin]->Add(h_ttbar[ibin]); st_mc[ibin]->Add(h_qcd[ibin]);
  }

  // Make TLegend
  TLegend *l_2[6];
  for(int i=22; i<28; i++) {
    int ibin = i-22;
    l_2[ibin] = new TLegend(0.45, 0.43, 0.85, 0.87);
    l_2[ibin]->SetTextSize(0.055);
    l_2[ibin]->SetBorderSize(0);
    l_2[ibin]->SetFillStyle(0);
    l_2[ibin]->AddEntry(h_data[ibin],  "data", "elp");
    l_2[ibin]->AddEntry(h_ttbar[ibin],   "t#bar{t}", "f");
    l_2[ibin]->AddEntry(h_qcd[ibin],    "QCD", "f");
    l_2[ibin]->AddEntry(h_wjets[ibin],  "W+jets", "f");
    l_2[ibin]->AddEntry(h_other[ibin],  "Other", "f");
    l_2[ibin]->AddEntry(h_signal_m1200[ibin], "m_{#tilde{g}}=1200 GeV#times0.01", "l");
    l_2[ibin]->AddEntry(h_signal_m1800[ibin], "m_{#tilde{g}}=1800 GeV", "l");
  }

  // Draw plots
  TCanvas* c[6];
  TPad *tpad[6]={nullptr}, *bpad[6]={nullptr};
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);
  for(int i=22; i<28; i++) {
    int ibin = i-22;
     
    c[ibin] = new TCanvas(Form("c_%d", ibin),Form("c_%d", ibin),800, 800);
    // tpad
    c[ibin]->cd();
    tpad[ibin] = new TPad(Form("tpad_%d", ibin),Form("tpad_%d", ibin),0.,0.3,1.,1.);
    tpad[ibin]->SetLeftMargin(0.15); tpad[ibin]->SetBottomMargin(0.02); tpad[ibin]->SetTopMargin(style.PadTopMargin+0.01);
    tpad[ibin]->Draw();
    tpad[ibin]->cd();
    gPad->SetLogy();
    h_data[ibin]->Draw("EP");
    st_mc[ibin]->Draw("same hist");
    h_data[ibin]->Draw("same EP");
    h_signal_m1200[ibin]->Draw("same hist");
    h_signal_m1800[ibin]->Draw("same hist");
    gPad->RedrawAxis();
    l_2[ibin]->Draw();
    tex_lumi->Draw();
    TexCMS->Draw();
    tex_Nlep1->Draw();
    if(i==22||i==25) tex_Njets45->Draw();
    else if(i==23||i==26) tex_Njets67->Draw();
    else if(i==24||i==27) tex_Njets8->Draw();
    if(i==22||i==23||i==24) tex_Nb0->Draw();
    else if(i==25||i==26||i==27) tex_Nb1->Draw();
    // bpad
    c[ibin]->cd();
    bpad[ibin] = new TPad(Form("bpad_%d", ibin),Form("bpad_%d", ibin),0.,0.,1.,0.305);
    bpad[ibin]->SetLeftMargin(0.15);
    bpad[ibin]->SetTopMargin(0.); bpad[ibin]->SetBottomMargin(0.4); bpad[ibin]->SetFillStyle(4000);
    bpad[ibin]->Draw(); bpad[ibin]->cd();
    h_data_clone[ibin]->Divide(h_tot_mc[ibin]);
    h_data_clone[ibin]->GetYaxis()->SetRangeUser(0.4, 1.6);
    h_data_clone[ibin]->SetLineColor(kBlack);
    h_data_clone[ibin]->SetLineWidth(2);
    h_data_clone[ibin]->SetMarkerStyle(20);
    h_data_clone[ibin]->SetMarkerSize(2);
    for(int imj=1; imj<4; imj++) {
      h_data_clone[ibin]->SetBinError(imj, h_data_clone[ibin]->GetBinContent(imj)*(h_data[ibin]->GetBinError(imj)/h_data[ibin]->GetBinContent(imj)));
      h_data_err[ibin]->SetBinContent(imj, h_data[ibin]->GetBinContent(imj)/h_tot_mc[ibin]->GetBinContent(imj));
      h_data_err[ibin]->SetBinError(imj, (h_data[ibin]->GetBinContent(imj)/h_tot_mc[ibin]->GetBinContent(imj))/(h_tot_mc[ibin]->GetBinError(imj)/h_tot_mc[ibin]->GetBinContent(imj)));
    }
    h_data_clone[ibin]->Draw("ep");

    tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
    line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
    line->Draw("same");
    c[ibin]->Print(Form("plots/ttbar_kappa/ttbar_kappa_lumi%s_bin%d.pdf", lumi_title.Data(), i));
  }
}

void kappa_summary_plot(TString year) {
  float lumi=0;
  if(year=="UL2016") lumi=36.3;
  else if(year=="UL20178") lumi=101.3;

  TFile* f_kappa = new TFile("data/result_kappa_"+year+".root", "READ");

  TH1F *hist_kappa1, *hist_kappa2;
  hist_kappa1 = static_cast<TH1F*>(f_kappa->Get("hist_kappa1"));
  hist_kappa2 = static_cast<TH1F*>(f_kappa->Get("hist_kappa2"));
//  hist_kappa2->GetXaxis()->SetBinLabel(1, "#splitline{Low}{(4-5)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(2, "#splitline{Mid}{(6-7)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(3, "#splitline{High}{(\\geq8)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(4, "#splitline{Low}{(4-5)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(5, "#splitline{Mid}{(6-7)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(6, "#splitline{High}{(\\geq8)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(7, "#splitline{Low}{(4-5)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(8, "#splitline{Mid}{(6-7)}");
//  hist_kappa2->GetXaxis()->SetBinLabel(9, "#splitline{High}{(\\geq8)}");
  hist_kappa2->GetXaxis()->SetBinLabel(1, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(2, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(3, "High");
  hist_kappa2->GetXaxis()->SetBinLabel(4, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(5, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(6, "High");
  hist_kappa2->GetXaxis()->SetBinLabel(7, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(8, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(9, "High");
  //hist_kappa2->GetXaxis()->SetBinLabel(9, "#splitline{High}{   N_{jet}}");
  hist_kappa2->GetXaxis()->LabelsOption("h");

  hist_kappa1->SetTitle("");
  hist_kappa2->SetTitle("");
  hist_kappa1->GetYaxis()->SetRangeUser(0.,2.99);
  hist_kappa2->GetYaxis()->SetRangeUser(0.,2.99);
  hist_kappa1->SetMinimum(0.001);
  hist_kappa2->GetXaxis()->SetLabelSize(0.09);
  hist_kappa2->GetXaxis()->SetLabelOffset(0.01);
  //hist_kappa2->GetXaxis()->SetTitle("N_{jet}");
  //hist_kappa2->GetXaxis()->SetTitleOffset(1.5);
  hist_kappa1->GetYaxis()->SetLabelSize(0.075);
  hist_kappa2->GetYaxis()->SetLabelSize(0.07);
//  hist_kappa1->SetTitleSize(2);
//  hist_kappa2->SetTitle("#kappa_{2}");
//  hist_kappa2->SetTitleSize(0.9);
  TLatex* tex_lumi = new TLatex(0.93, 0.86, Form("%.1f fb^{-1} (13 TeV)", lumi));
  if(year=="UL20178") tex_lumi = new TLatex(0.93, 0.86, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.09);
  //TLatex *TexCMS = new TLatex(0.138,0.82,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.138,0.82,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.10);
  TexCMS->SetLineWidth(2);
  TLatex *TexTitle_kap1 = new TLatex(0.02,0.77,"#kappa_{1}");
  TexTitle_kap1->SetNDC();
  TexTitle_kap1->SetTextSize(0.13);
  TLatex *TexTitle_kap2 = new TLatex(0.02,0.93,"#kappa_{2}");
  TexTitle_kap2->SetNDC();
  TexTitle_kap2->SetTextSize(0.12);

  // Tex QCD, ttbar, and wjets
  TLatex *Tex_QCD = new TLatex(0.215,0.03,"QCD");
  Tex_QCD->SetNDC();
  Tex_QCD->SetTextFont(42);
  Tex_QCD->SetTextSize(0.11);
  TLatex *Tex_wjets = new TLatex(0.45,0.03,"W+jets");
  Tex_wjets->SetNDC();
  Tex_wjets->SetTextFont(42);
  Tex_wjets->SetTextSize(0.11);
  TLatex *Tex_ttbar = new TLatex(0.785,0.03,"t#bar{t}");
  Tex_ttbar->SetNDC();
  Tex_ttbar->SetTextFont(42);
  Tex_ttbar->SetTextSize(0.11);
  TLatex *Tex_Njet = new TLatex(0.935,0.20,"N_{jet}");
  Tex_Njet->SetNDC();
  Tex_Njet->SetTextFont(42);
  Tex_Njet->SetTextSize(0.09);

  // Tex (4-5), (6-7) and (\\geq8)
  TLatex *Tex_45_1 = new TLatex(0.152,0.165,"(4-5)");
  Tex_45_1->SetNDC();
  Tex_45_1->SetTextFont(42);
  Tex_45_1->SetTextSize(0.06);
  TLatex *Tex_67_1 = new TLatex(0.242,0.165,"(6-7)");
  Tex_67_1->SetNDC();
  Tex_67_1->SetTextFont(42);
  Tex_67_1->SetTextSize(0.06);
  TLatex *Tex_8_1 = new TLatex(0.332,0.165,"(\\geq8)");
  Tex_8_1->SetNDC();
  Tex_8_1->SetTextFont(42);
  Tex_8_1->SetTextSize(0.06);
  TLatex *Tex_45_2 = new TLatex(0.415,0.165,"(4-5)");
  Tex_45_2->SetNDC();
  Tex_45_2->SetTextFont(42);
  Tex_45_2->SetTextSize(0.06);
  TLatex *Tex_67_2 = new TLatex(0.505,0.165,"(6-7)");
  Tex_67_2->SetNDC();
  Tex_67_2->SetTextFont(42);
  Tex_67_2->SetTextSize(0.06);
  TLatex *Tex_8_2 = new TLatex(0.595,0.165,"(\\geq8)");
  Tex_8_2->SetNDC();
  Tex_8_2->SetTextFont(42);
  Tex_8_2->SetTextSize(0.06);
  TLatex *Tex_45_3 = new TLatex(0.678,0.165,"(4-5)");
  Tex_45_3->SetNDC();
  Tex_45_3->SetTextFont(42);
  Tex_45_3->SetTextSize(0.06);
  TLatex *Tex_67_3 = new TLatex(0.768,0.165,"(6-7)");
  Tex_67_3->SetNDC();
  Tex_67_3->SetTextFont(42);
  Tex_67_3->SetTextSize(0.06);
  TLatex *Tex_8_3 = new TLatex(0.858,0.165,"(\\geq8)");
  Tex_8_3->SetNDC();
  Tex_8_3->SetTextFont(42);
  Tex_8_3->SetTextSize(0.06);

  TLine *line;
  line = new TLine(0, 1., 8.99, 1.);
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);

  TCanvas *c = new TCanvas("c","c",1600,1600);
  c->Divide(1,2,0.01,0);
  // To avoid overlapping with the y-axis label ("0" of the kappa1 plot), cd(2) is drawn first
  c->cd(2);
  TBox *b4 = new TBox(0.,0., 3., 2.99*c->GetUymax());
  b4->SetFillColorAlpha(TColor::GetColor("#ffa90e"), 0.85);
  TBox *b5 = new TBox(3.,0., 6., 2.99*c->GetUymax());
  b5->SetFillColorAlpha(TColor::GetColor("#832db6"), 0.85);
  TBox *b6 = new TBox(6.,0., 8.99, 2.99*c->GetUymax());
  b6->SetFillColorAlpha(TColor::GetColor("#3f90da"), 0.85);
  hist_kappa2->Draw("ex0");
  TGaxis *ax2 = static_cast<TGaxis*>(hist_kappa2->GetXaxis()->Clone());
  TGaxis *ay2 = static_cast<TGaxis*>(hist_kappa2->GetYaxis()->Clone());
  b4->Draw("same");
  b5->Draw("same");
  b6->Draw("same");
  hist_kappa2->SetFillStyle(3254);
  hist_kappa2->SetMarkerStyle(8);
  hist_kappa2->SetLineColor(kBlack);
  hist_kappa2->SetLineWidth(2);
  hist_kappa2->SetMarkerSize(3);
  hist_kappa2->Draw("same ex0");
  ax2->Draw("same");
  TexTitle_kap2->Draw();
  Tex_QCD->Draw();
  Tex_wjets->Draw();
  Tex_ttbar->Draw();
  Tex_45_1->Draw();
  Tex_67_1->Draw();
  Tex_8_1->Draw();
  Tex_45_2->Draw();
  Tex_67_2->Draw();
  Tex_8_2->Draw();
  Tex_45_3->Draw();
  Tex_67_3->Draw();
  Tex_8_3->Draw();
  Tex_Njet->Draw();
  ay2->Draw("same");
  line->Draw("same");
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.07);
  gPad->SetBottomMargin(0.30);
  c->cd(2)->RedrawAxis();
  c->cd(2)->Modified();
  c->cd(2)->Update();

  c->cd(1);
  TBox *b1 = new TBox(0.,0., 3., 2.98*c->GetUymax());
  b1->SetFillColorAlpha(TColor::GetColor("#ffa90e"), 0.85);
  TBox *b2 = new TBox(3.,0., 6., 2.98*c->GetUymax());
  b2->SetFillColorAlpha(TColor::GetColor("#832db6"), 0.85);
  TBox *b3 = new TBox(6.,0., 8.99, 2.99*c->GetUymax());
  b3->SetFillColorAlpha(TColor::GetColor("#3f90da"), 0.85);
  hist_kappa1->Draw("ex0");
  TGaxis *ax1 = static_cast<TGaxis*>(hist_kappa1->GetXaxis()->Clone());
  TGaxis *ay1 = static_cast<TGaxis*>(hist_kappa1->GetYaxis()->Clone());
  b1->Draw("same");
  b2->Draw("same");
  b3->Draw("same");
  hist_kappa1->SetFillStyle(3254);
  hist_kappa1->SetMarkerStyle(20);
  hist_kappa1->SetMarkerSize(3);
  hist_kappa1->SetLineColor(kBlack);
  hist_kappa1->SetLineWidth(2);
  hist_kappa1->Draw("same ex0");
  ax1->Draw("same");
  ay1->Draw("same");
  line->Draw("same");
  tex_lumi->Draw();
  TexCMS->Draw();
  TexTitle_kap1->Draw();
  gPad->SetLeftMargin(0.14);
  //gPad->SetTopMargin(0.16);
  gPad->SetTopMargin(0.21);
  gPad->SetRightMargin(0.07);
  c->cd(1)->RedrawAxis();
  c->cd(1)->Modified();
  c->cd(1)->Update();

  
  c->Print("kappa_result_"+year+".pdf");
}

void qcd_kappa_plot_combine()
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

  double lumi=138.;
  TString lumi_title="138";

  // define histogram
  TH1D* h_data_njets67_16   = new TH1D("h_data_njets67_16",   "h_data_njets67_16",   3, 500, 1400);
  TH1D* h_data_njets67_1718   = new TH1D("h_data_njets67_1718",   "h_data_njets67_1718",   3, 500, 1400);
  TH1D* h_data_njets89_16   = new TH1D("h_data_njets89_16",   "h_data_njets89_16",   3, 500, 1400);
  TH1D* h_data_njets89_1718   = new TH1D("h_data_njets89_1718",   "h_data_njets89_1718",   3, 500, 1400);
  TH1D* h_data_njets10_16   = new TH1D("h_data_njets10_16",   "h_data_njets10_16",   3, 500, 1400);
  TH1D* h_data_njets10_1718   = new TH1D("h_data_njets10_1718",   "h_data_njets10_1718",   3, 500, 1400);
  TH1D* h_qcd_njets67_16    = new TH1D("h_qcd_njets67_16",    "h_qcd_njets67_16",    3, 500, 1400);
  TH1D* h_qcd_njets67_1718    = new TH1D("h_qcd_njets67_1718",    "h_qcd_njets67_1718",    3, 500, 1400);
  TH1D* h_qcd_njets89_16    = new TH1D("h_qcd_njets89_16",    "h_qcd_njets89_16",    3, 500, 1400);
  TH1D* h_qcd_njets89_1718    = new TH1D("h_qcd_njets89_1718",    "h_qcd_njets89_1718",    3, 500, 1400);
  TH1D* h_qcd_njets10_16    = new TH1D("h_qcd_njets10_16",    "h_qcd_njets10_16",    3, 500, 1400);
  TH1D* h_qcd_njets10_1718    = new TH1D("h_qcd_njets10_1718",    "h_qcd_njets10_1718",    3, 500, 1400);
  TH1D* h_ttbar_njets67_16  = new TH1D("h_ttbar_njets67_16",  "h_ttbar_njets67_16",  3, 500, 1400);
  TH1D* h_ttbar_njets67_1718  = new TH1D("h_ttbar_njets67_1718",  "h_ttbar_njets67_1718",  3, 500, 1400);
  TH1D* h_ttbar_njets89_16  = new TH1D("h_ttbar_njets89_16",  "h_ttbar_njets89_16",  3, 500, 1400);
  TH1D* h_ttbar_njets89_1718  = new TH1D("h_ttbar_njets89_1718",  "h_ttbar_njets89_1718",  3, 500, 1400);
  TH1D* h_ttbar_njets10_16  = new TH1D("h_ttbar_njets10_16",  "h_ttbar_njets10_16",  3, 500, 1400);
  TH1D* h_ttbar_njets10_1718  = new TH1D("h_ttbar_njets10_1718",  "h_ttbar_njets10_1718",  3, 500, 1400);
  TH1D* h_wjets_njets67_16  = new TH1D("h_wjets_njets67_16",  "h_wjets_njets67_16",  3, 500, 1400);
  TH1D* h_wjets_njets67_1718  = new TH1D("h_wjets_njets67_1718",  "h_wjets_njets67_1718",  3, 500, 1400);
  TH1D* h_wjets_njets89_16  = new TH1D("h_wjets_njets89_16",  "h_wjets_njets89_16",  3, 500, 1400);
  TH1D* h_wjets_njets89_1718  = new TH1D("h_wjets_njets89_1718",  "h_wjets_njets89_1718",  3, 500, 1400);
  TH1D* h_wjets_njets10_16  = new TH1D("h_wjets_njets10_16",  "h_wjets_njets10_16",  3, 500, 1400);
  TH1D* h_wjets_njets10_1718  = new TH1D("h_wjets_njets10_1718",  "h_wjets_njets10_1718",  3, 500, 1400);
  TH1D* h_other_njets67_16  = new TH1D("h_other_njets67_16",  "h_other_njets67_16",  3, 500, 1400);
  TH1D* h_other_njets67_1718  = new TH1D("h_other_njets67_1718",  "h_other_njets67_1718",  3, 500, 1400);
  TH1D* h_other_njets89_16  = new TH1D("h_other_njets89_16",  "h_other_njets89_16",  3, 500, 1400);
  TH1D* h_other_njets89_1718  = new TH1D("h_other_njets89_1718",  "h_other_njets89_1718",  3, 500, 1400);
  TH1D* h_other_njets10_16  = new TH1D("h_other_njets10_16",  "h_other_njets10_16",  3, 500, 1400);
  TH1D* h_other_njets10_1718  = new TH1D("h_other_njets10_1718",  "h_other_njets10_1718",  3, 500, 1400);
  TH1D* h_signal_njets67_m1200_16 = new TH1D("h_signal_njets67_m1200_16", "h_signal_njets67_m1200_16", 3, 500, 1400);
  TH1D* h_signal_njets67_m1200_1718 = new TH1D("h_signal_njets67_m1200_1718", "h_signal_njets67_m1200_1718", 3, 500, 1400);
  TH1D* h_signal_njets89_m1200_16 = new TH1D("h_signal_njets89_m1200_16", "h_signal_njets89_m1200_16", 3, 500, 1400);
  TH1D* h_signal_njets89_m1200_1718 = new TH1D("h_signal_njets89_m1200_1718", "h_signal_njets89_m1200_1718", 3, 500, 1400);
  TH1D* h_signal_njets10_m1200_16 = new TH1D("h_signal_njets10_m1200_16", "h_signal_njets10_m1200_16", 3, 500, 1400);
  TH1D* h_signal_njets10_m1200_1718 = new TH1D("h_signal_njets10_m1200_1718", "h_signal_njets10_m1200_1718", 3, 500, 1400);
  TH1D* h_signal_njets67_m1800_16 = new TH1D("h_signal_njets67_m1800_16", "h_signal_njets67_m1800_16", 3, 500, 1400);
  TH1D* h_signal_njets67_m1800_1718 = new TH1D("h_signal_njets67_m1800_1718", "h_signal_njets67_m1800_1718", 3, 500, 1400);
  TH1D* h_signal_njets89_m1800_16 = new TH1D("h_signal_njets89_m1800_16", "h_signal_njets89_m1800_16", 3, 500, 1400);
  TH1D* h_signal_njets89_m1800_1718 = new TH1D("h_signal_njets89_m1800_1718", "h_signal_njets89_m1800_1718", 3, 500, 1400);
  TH1D* h_signal_njets10_m1800_16 = new TH1D("h_signal_njets10_m1800_16", "h_signal_njets10_m1800_16", 3, 500, 1400);
  TH1D* h_signal_njets10_m1800_1718 = new TH1D("h_signal_njets10_m1800_1718", "h_signal_njets10_m1800_1718", 3, 500, 1400);

  TFile* f_16   = new TFile("data/qcd_kappa_meas_UL2016_comb.root", "READ");
  TFile* f_1718 = new TFile("data/qcd_kappa_meas_UL20178_comb.root", "READ");

  h_data_njets67_16 = static_cast<TH1D*>(f_16->Get("h_data_njets67_clone"));
  h_data_njets67_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets67_clone"));
  h_data_njets89_16 = static_cast<TH1D*>(f_16->Get("h_data_njets89_clone"));
  h_data_njets89_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets89_clone"));
  h_data_njets10_16 = static_cast<TH1D*>(f_16->Get("h_data_njets10_clone"));
  h_data_njets10_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets10_clone"));
  h_qcd_njets67_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets67_clone"));
  h_qcd_njets67_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets67_clone"));
  h_qcd_njets89_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets89_clone"));
  h_qcd_njets89_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets89_clone"));
  h_qcd_njets10_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets10_clone"));
  h_qcd_njets10_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets10_clone"));
  h_ttbar_njets67_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets67_clone"));
  h_ttbar_njets67_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets67_clone"));
  h_ttbar_njets89_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets89_clone"));
  h_ttbar_njets89_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets89_clone"));
  h_ttbar_njets10_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets10_clone"));
  h_ttbar_njets10_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets10_clone"));
  h_wjets_njets67_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets67_clone"));
  h_wjets_njets67_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets67_clone"));
  h_wjets_njets89_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets89_clone"));
  h_wjets_njets89_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets89_clone"));
  h_wjets_njets10_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets10_clone"));
  h_wjets_njets10_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets10_clone"));
  h_other_njets67_16 = static_cast<TH1D*>(f_16->Get("h_other_njets67_clone"));
  h_other_njets67_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets67_clone"));
  h_other_njets89_16 = static_cast<TH1D*>(f_16->Get("h_other_njets89_clone"));
  h_other_njets89_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets89_clone"));
  h_other_njets10_16 = static_cast<TH1D*>(f_16->Get("h_other_njets10_clone"));
  h_other_njets10_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets10_clone"));
  h_signal_njets67_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets67_m1200"));
  h_signal_njets67_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets67_m1200"));
  h_signal_njets89_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets89_m1200"));
  h_signal_njets89_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets89_m1200"));
  h_signal_njets10_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets10_m1200"));
  h_signal_njets10_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets10_m1200"));
  h_signal_njets67_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets67_m1800"));
  h_signal_njets67_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets67_m1800"));
  h_signal_njets89_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets89_m1800"));
  h_signal_njets89_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets89_m1800"));
  h_signal_njets10_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets10_m1800"));
  h_signal_njets10_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets10_m1800"));


  TH1D* h_data_njets67   = (TH1D*)h_data_njets67_16->Clone("h_data_njets67");
  h_data_njets67->Add(h_data_njets67_1718);
  TH1D* h_data_njets89   = (TH1D*)h_data_njets89_16->Clone("h_data_njets89");
  h_data_njets89->Add(h_data_njets89_1718);
  TH1D* h_data_njets10   = (TH1D*)h_data_njets10_16->Clone("h_data_njets10");
  h_data_njets10->Add(h_data_njets10_1718);
  TH1D* h_qcd_njets67   = (TH1D*)h_qcd_njets67_16->Clone("h_qcd_njets67");
  h_qcd_njets67->Add(h_qcd_njets67_1718);
  TH1D* h_qcd_njets89   = (TH1D*)h_qcd_njets89_16->Clone("h_qcd_njets89");
  h_qcd_njets89->Add(h_qcd_njets89_1718);
  TH1D* h_qcd_njets10   = (TH1D*)h_qcd_njets10_16->Clone("h_qcd_njets10");
  h_qcd_njets10->Add(h_qcd_njets10_1718);
  TH1D* h_ttbar_njets67   = (TH1D*)h_ttbar_njets67_16->Clone("h_ttbar_njets67");
  h_ttbar_njets67->Add(h_ttbar_njets67_1718);
  TH1D* h_ttbar_njets89   = (TH1D*)h_ttbar_njets89_16->Clone("h_ttbar_njets89");
  h_ttbar_njets89->Add(h_ttbar_njets89_1718);
  TH1D* h_ttbar_njets10   = (TH1D*)h_ttbar_njets10_16->Clone("h_ttbar_njets10");
  h_ttbar_njets10->Add(h_ttbar_njets10_1718);
  TH1D* h_wjets_njets67   = (TH1D*)h_wjets_njets67_16->Clone("h_wjets_njets67");
  h_wjets_njets67->Add(h_wjets_njets67_1718);
  TH1D* h_wjets_njets89   = (TH1D*)h_wjets_njets89_16->Clone("h_wjets_njets89");
  h_wjets_njets89->Add(h_wjets_njets89_1718);
  TH1D* h_wjets_njets10   = (TH1D*)h_wjets_njets10_16->Clone("h_wjets_njets10");
  h_wjets_njets10->Add(h_wjets_njets10_1718);
  TH1D* h_other_njets67   = (TH1D*)h_other_njets67_16->Clone("h_other_njets67");
  h_other_njets67->Add(h_other_njets67_1718);
  TH1D* h_other_njets89   = (TH1D*)h_other_njets89_16->Clone("h_other_njets89");
  h_other_njets89->Add(h_other_njets89_1718);
  TH1D* h_other_njets10   = (TH1D*)h_other_njets10_16->Clone("h_other_njets10");
  h_other_njets10->Add(h_other_njets10_1718);
  TH1D* h_signal_njets67_m1200   = (TH1D*)h_signal_njets67_m1200_16->Clone("h_signal_njets67_m1200");
  h_signal_njets67_m1200->Add(h_signal_njets67_m1200_1718);
  TH1D* h_signal_njets89_m1200   = (TH1D*)h_signal_njets89_m1200_16->Clone("h_signal_njets89_m1200");
  h_signal_njets89_m1200->Add(h_signal_njets89_m1200_1718);
  TH1D* h_signal_njets10_m1200   = (TH1D*)h_signal_njets10_m1200_16->Clone("h_signal_njets10_m1200");
  h_signal_njets10_m1200->Add(h_signal_njets10_m1200_1718);
  TH1D* h_signal_njets67_m1800   = (TH1D*)h_signal_njets67_m1800_16->Clone("h_signal_njets67_m1800");
  h_signal_njets67_m1800->Add(h_signal_njets67_m1800_1718);
  TH1D* h_signal_njets89_m1800   = (TH1D*)h_signal_njets89_m1800_16->Clone("h_signal_njets89_m1800");
  h_signal_njets89_m1800->Add(h_signal_njets89_m1800_1718);
  TH1D* h_signal_njets10_m1800   = (TH1D*)h_signal_njets10_m1800_16->Clone("h_signal_njets10_m1800");
  h_signal_njets10_m1800->Add(h_signal_njets10_m1800_1718);


  // Make clone
  TH1D* h_data_njets67_clone  = (TH1D*)h_data_njets67->Clone("h_data_njets67_clone");
  TH1D* h_data_njets89_clone  = (TH1D*)h_data_njets89->Clone("h_data_njets89_clone");
  TH1D* h_data_njets10_clone   = (TH1D*)h_data_njets10->Clone("h_data_njets10_clone");
  TH1D* h_qcd_njets67_clone   = (TH1D*)h_qcd_njets67->Clone("h_qcd_njets67_clone");
  TH1D* h_qcd_njets89_clone   = (TH1D*)h_qcd_njets89->Clone("h_qcd_njets89_clone");
  TH1D* h_qcd_njets10_clone    = (TH1D*)h_qcd_njets10->Clone("h_qcd_njets10_clone");
  TH1D* h_ttbar_njets67_clone = (TH1D*)h_ttbar_njets67->Clone("h_ttbar_njets67_clone");
  TH1D* h_ttbar_njets89_clone = (TH1D*)h_ttbar_njets89->Clone("h_ttbar_njets89_clone");
  TH1D* h_ttbar_njets10_clone  = (TH1D*)h_ttbar_njets10->Clone("h_ttbar_njets10_clone");
  TH1D* h_wjets_njets67_clone = (TH1D*)h_wjets_njets67->Clone("h_wjets_njets67_clone");
  TH1D* h_wjets_njets89_clone = (TH1D*)h_wjets_njets89->Clone("h_wjets_njets89_clone");
  TH1D* h_wjets_njets10_clone  = (TH1D*)h_wjets_njets10->Clone("h_wjets_njets10_clone");
  TH1D* h_other_njets67_clone = (TH1D*)h_other_njets67->Clone("h_other_njets67_clone");
  TH1D* h_other_njets89_clone = (TH1D*)h_other_njets89->Clone("h_other_njets89_clone");
  TH1D* h_other_njets10_clone  = (TH1D*)h_other_njets10->Clone("h_other_njets10_clone");

  // Total MC histograms
  TH1D* h_tot_mc_njets67 = (TH1D*)h_qcd_njets67->Clone("h_tot_mc_njets67");
  TH1D* h_tot_mc_njets89 = (TH1D*)h_qcd_njets89->Clone("h_tot_mc_njets89");
  TH1D* h_tot_mc_njets10  = (TH1D*)h_qcd_njets10->Clone("h_tot_mc_njets10");
  h_tot_mc_njets67->Add(h_ttbar_njets67_clone); h_tot_mc_njets67->Add(h_wjets_njets67_clone); h_tot_mc_njets67->Add(h_other_njets67_clone);
  h_tot_mc_njets89->Add(h_ttbar_njets89_clone); h_tot_mc_njets89->Add(h_wjets_njets89_clone); h_tot_mc_njets89->Add(h_other_njets89_clone);
  h_tot_mc_njets10->Add(h_ttbar_njets10_clone); h_tot_mc_njets10->Add(h_wjets_njets10_clone); h_tot_mc_njets10->Add(h_other_njets10_clone);

  cout << "Purity" << endl;
  cout << "Low Njets:  " << h_qcd_njets67->Integral(1,3) << " / " << h_tot_mc_njets67->Integral(1,3) << " = " << h_qcd_njets67->Integral(1,3)/h_tot_mc_njets67->Integral(1,3)*100 << "\%" << endl;
  cout << "Mid Njets:  " << h_qcd_njets89->Integral(1,3) << " / " << h_tot_mc_njets89->Integral(1,3) << " = " << h_qcd_njets89->Integral(1,3)/h_tot_mc_njets89->Integral(1,3)*100 << "\%" << endl;
  cout << "High Njets: " << h_qcd_njets10->Integral(1,3) << " / " << h_tot_mc_njets10->Integral(1,3) << " = " << h_qcd_njets10->Integral(1,3)/h_tot_mc_njets10->Integral(1,3)*100 << "\%" << endl;
  cout << endl;

  cout << "[m1200]" << endl;
  cout << "    njet67" << endl;
  cout << "[1]: " << h_signal_njets67_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets67_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets67_m1200->GetBinContent(3) << endl;
  cout << "    njet89" << endl;
  cout << "[1]: " << h_signal_njets89_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets89_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets89_m1200->GetBinContent(3) << endl;
  cout << "    njet10" << endl;
  cout << "[1]: " << h_signal_njets10_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets10_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets10_m1200->GetBinContent(3) << endl;
  cout << endl;
  cout << "[m1800]" << endl;
  cout << "    njet67" << endl;
  cout << "[1]: " << h_signal_njets67_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets67_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets67_m1800->GetBinContent(3) << endl;
  cout << "    njet89" << endl;
  cout << "[1]: " << h_signal_njets89_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets89_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets89_m1800->GetBinContent(3) << endl;
  cout << "    njet10" << endl;
  cout << "[1]: " << h_signal_njets10_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets10_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets10_m1800->GetBinContent(3) << endl;

  // To validate kappa values against those from ./run/make_kappa_CRFit.exe
    // normalize
      // total mc
  TH1D* h_tot_mc_njets67_clone = (TH1D*)h_tot_mc_njets67->Clone("h_tot_mc_njets67_clone");
  TH1D* h_tot_mc_njets89_clone = (TH1D*)h_tot_mc_njets89->Clone("h_tot_mc_njets89_clone");
  TH1D* h_tot_mc_njets10_clone  = (TH1D*)h_tot_mc_njets10->Clone("h_tot_mc_njets10_clone");

      // SF
  float sf_njets67 = h_data_njets67->Integral(1,-1)/h_tot_mc_njets67_clone->Integral(1,-1);
  float sf_njets89 = h_data_njets89->Integral(1,-1)/h_tot_mc_njets89_clone->Integral(1,-1);
  float sf_njets10  = h_data_njets10->Integral(1,-1)/h_tot_mc_njets10_clone->Integral(1,-1);

      // other mc (total mc - qcd)
  TH1D* h_other_mc_njets67 = (TH1D*)h_ttbar_njets67_clone->Clone("h_other_mc_njets67");
  TH1D* h_other_mc_njets89 = (TH1D*)h_ttbar_njets89_clone->Clone("h_other_mc_njets89");
  TH1D* h_other_mc_njets10  = (TH1D*)h_ttbar_njets10_clone->Clone("h_other_mc_njets10");
  h_other_mc_njets67->Add(h_wjets_njets67_clone); h_other_mc_njets67->Add(h_other_njets67_clone);
  h_other_mc_njets89->Add(h_wjets_njets89_clone); h_other_mc_njets89->Add(h_other_njets89_clone);
  h_other_mc_njets10->Add(h_wjets_njets10_clone); h_other_mc_njets10->Add(h_other_njets10_clone);
      // normalized other mc
  h_other_mc_njets67->Scale(sf_njets67);
  h_other_mc_njets89->Scale(sf_njets89);
  h_other_mc_njets10->Scale(sf_njets10);

      // data - other mc
  TH1D* h_data_minus_others_njets67_clone = (TH1D*)h_data_njets67->Clone("h_data_minus_others_njets67_clone");
  TH1D* h_data_minus_others_njets89_clone = (TH1D*)h_data_njets89->Clone("h_data_minus_others_njets89_clone");
  TH1D* h_data_minus_others_njets10_clone  = (TH1D*)h_data_njets10->Clone("h_data_minus_others_njets10_clone");
  h_data_minus_others_njets67_clone->Add(h_other_mc_njets67,-1);
  h_data_minus_others_njets89_clone->Add(h_other_mc_njets89,-1);
  h_data_minus_others_njets10_clone->Add(h_other_mc_njets10,-1);

  cout << "Kappa" << endl;
  cout << "Low Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets67_clone->GetBinContent(2)/h_data_minus_others_njets67_clone->GetBinContent(1))/(h_qcd_njets67_clone->GetBinContent(2)/h_qcd_njets67_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets67_clone->GetBinContent(3)/h_data_minus_others_njets67_clone->GetBinContent(1))/(h_qcd_njets67_clone->GetBinContent(3)/h_qcd_njets67_clone->GetBinContent(1)) << endl;
  cout << "Mid Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets89_clone->GetBinContent(2)/h_data_minus_others_njets89_clone->GetBinContent(1))/(h_qcd_njets89_clone->GetBinContent(2)/h_qcd_njets89_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets89_clone->GetBinContent(3)/h_data_minus_others_njets89_clone->GetBinContent(1))/(h_qcd_njets89_clone->GetBinContent(3)/h_qcd_njets89_clone->GetBinContent(1)) << endl;
  cout << "High Njets:  " << endl;
  cout << "     kap1: " << (h_data_minus_others_njets10_clone->GetBinContent(2)/h_data_minus_others_njets10_clone->GetBinContent(1))/(h_qcd_njets10_clone->GetBinContent(2)/h_qcd_njets10_clone->GetBinContent(1)) << endl;
  cout << "     kap2: " << (h_data_minus_others_njets10_clone->GetBinContent(3)/h_data_minus_others_njets10_clone->GetBinContent(1))/(h_qcd_njets10_clone->GetBinContent(3)/h_qcd_njets10_clone->GetBinContent(1)) << endl;
  // validate end

  /*
  // test
  TH1D* h_data_njets67_clone_test = (TH1D*)h_data_njets67->Clone("h_data_njets67_clone_test");
  TH1D* h_data_njets89_clone_test = (TH1D*)h_data_njets89->Clone("h_data_njets89_clone_test");
  TH1D* h_data_njets10_clone_test = (TH1D*)h_data_njets10->Clone("h_data_njets10_clone_test");
  h_data_njets67_clone_test->Add(h_tot_mc_njets67, -1);
  h_data_njets89_clone_test->Add(h_tot_mc_njets89, -1);
  h_data_njets10_clone_test->Add(h_tot_mc_njets10, -1);
  cout << "njets 34" << endl;
  cout << "data_obs: " << h_data_njets67_clone->GetBinContent(1) << " / " << h_data_njets67_clone->GetBinContent(2) << " / " << h_data_njets67_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets67_clone->GetBinError(1) << " / " << h_data_njets67_clone->GetBinError(2) << " / " << h_data_njets67_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets67_clone_test->GetBinContent(1) << " / " << h_data_njets67_clone_test->GetBinContent(2) << " / " << h_data_njets67_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets67_clone_test->GetBinError(1) << " / " << h_data_njets67_clone_test->GetBinError(2) << " / " << h_data_njets67_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets67_clone->GetBinContent(1) << " / " << h_dy_njets67_clone->GetBinContent(2) << " / " << h_dy_njets67_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets67_clone->GetBinError(1) << " / " << h_dy_njets67_clone->GetBinError(2) << " / " << h_dy_njets67_clone->GetBinError(3) << endl;
  float kap1_34=0, unc_kap1_34=0;
  float kap2_34=0, unc_kap2_34=0;
  kap1_34 = (h_data_njets67_clone_test->GetBinContent(2)/h_dy_njets67_clone->GetBinContent(2))/(h_data_njets67_clone_test->GetBinContent(1)/h_dy_njets67_clone->GetBinContent(1));
  unc_kap1_34 = kap1_34*TMath::Sqrt(TMath::Power(h_data_njets67_clone_test->GetBinError(1)/h_data_njets67_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets67_clone_test->GetBinError(2)/h_data_njets67_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets67_clone->GetBinError(1)/h_dy_njets67_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets67_clone->GetBinError(2)/h_dy_njets67_clone->GetBinContent(2),2));
  kap2_34 = (h_data_njets67_clone_test->GetBinContent(3)/h_dy_njets67_clone->GetBinContent(3))/(h_data_njets67_clone_test->GetBinContent(1)/h_dy_njets67_clone->GetBinContent(1));
  unc_kap2_34 = kap2_34*TMath::Sqrt(TMath::Power(h_data_njets67_clone_test->GetBinError(1)/h_data_njets67_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets67_clone_test->GetBinError(3)/h_data_njets67_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets67_clone->GetBinError(1)/h_dy_njets67_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets67_clone->GetBinError(3)/h_dy_njets67_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34 << endl;
  cout << "unc_kap1: " << unc_kap1_34/kap1_34 << endl;
  cout << "kap2:     " << kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34 << endl;
  cout << "unc_kap2: " << unc_kap2_34/kap2_34 << endl;
  cout << endl;
  cout << "njets 56" << endl;
  cout << "data_obs: " << h_data_njets89_clone->GetBinContent(1) << " / " << h_data_njets89_clone->GetBinContent(2) << " / " << h_data_njets89_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets89_clone->GetBinError(1) << " / " << h_data_njets89_clone->GetBinError(2) << " / " << h_data_njets89_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets89_clone_test->GetBinContent(1) << " / " << h_data_njets89_clone_test->GetBinContent(2) << " / " << h_data_njets89_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets89_clone_test->GetBinError(1) << " / " << h_data_njets89_clone_test->GetBinError(2) << " / " << h_data_njets89_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets89_clone->GetBinContent(1) << " / " << h_dy_njets89_clone->GetBinContent(2) << " / " << h_dy_njets89_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets89_clone->GetBinError(1) << " / " << h_dy_njets89_clone->GetBinError(2) << " / " << h_dy_njets89_clone->GetBinError(3) << endl;
  float kap1_56=0, unc_kap1_56=0;
  float kap2_56=0, unc_kap2_56=0;
  kap1_56 = (h_data_njets89_clone_test->GetBinContent(2)/h_dy_njets89_clone->GetBinContent(2))/(h_data_njets89_clone_test->GetBinContent(1)/h_dy_njets89_clone->GetBinContent(1));
  unc_kap1_56 = kap1_56*TMath::Sqrt(TMath::Power(h_data_njets89_clone_test->GetBinError(1)/h_data_njets89_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets89_clone_test->GetBinError(2)/h_data_njets89_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets89_clone->GetBinError(1)/h_dy_njets89_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets89_clone->GetBinError(2)/h_dy_njets89_clone->GetBinContent(2),2));
  kap2_56 = (h_data_njets89_clone_test->GetBinContent(3)/h_dy_njets89_clone->GetBinContent(3))/(h_data_njets89_clone_test->GetBinContent(1)/h_dy_njets89_clone->GetBinContent(1));
  unc_kap2_56 = kap2_56*TMath::Sqrt(TMath::Power(h_data_njets89_clone_test->GetBinError(1)/h_data_njets89_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets89_clone_test->GetBinError(3)/h_data_njets89_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets89_clone->GetBinError(1)/h_dy_njets89_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets89_clone->GetBinError(3)/h_dy_njets89_clone->GetBinContent(3),2));
  cout << endl;
  cout << "kap1:     " << kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56 << endl;
  cout << "unc_kap1: " << unc_kap1_56/kap1_56 << endl;
  cout << "kap2:     " << kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56 << endl;
  cout << "unc_kap2: " << unc_kap2_56/kap2_56 << endl;
  cout << endl;
  cout << "njets 7" << endl;
  cout << "data_obs: " << h_data_njets10_clone->GetBinContent(1) << " / " << h_data_njets10_clone->GetBinContent(2) << " / " << h_data_njets10_clone->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets10_clone->GetBinError(1) << " / " << h_data_njets10_clone->GetBinError(2) << " / " << h_data_njets10_clone->GetBinError(3) << endl;
  cout << "[after subtracting other]" << endl;
  cout << "data_obs: " << h_data_njets10_clone_test->GetBinContent(1) << " / " << h_data_njets10_clone_test->GetBinContent(2) << " / " << h_data_njets10_clone_test->GetBinContent(3) << endl;
  cout << "data_obs: " << h_data_njets10_clone_test->GetBinError(1) << " / " << h_data_njets10_clone_test->GetBinError(2) << " / " << h_data_njets10_clone_test->GetBinError(3) << endl;
  cout << "DY      : " << h_dy_njets10_clone->GetBinContent(1) << " / " << h_dy_njets10_clone->GetBinContent(2) << " / " << h_dy_njets10_clone->GetBinContent(3) << endl;
  cout << "DY      : " << h_dy_njets10_clone->GetBinError(1) << " / " << h_dy_njets10_clone->GetBinError(2) << " / " << h_dy_njets10_clone->GetBinError(3) << endl;
  float kap1_7=0, unc_kap1_7=0;
  float kap2_7=0, unc_kap2_7=0;
  kap1_7 = (h_data_njets10_clone_test->GetBinContent(2)/h_dy_njets10_clone->GetBinContent(2))/(h_data_njets10_clone_test->GetBinContent(1)/h_dy_njets10_clone->GetBinContent(1));
  unc_kap1_7 = kap1_7*TMath::Sqrt(TMath::Power(h_data_njets10_clone_test->GetBinError(1)/h_data_njets10_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets10_clone_test->GetBinError(2)/h_data_njets10_clone_test->GetBinContent(2),2) + TMath::Power(h_dy_njets10_clone->GetBinError(1)/h_dy_njets10_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets10_clone->GetBinError(2)/h_dy_njets10_clone->GetBinContent(2),2));
  kap2_7 = (h_data_njets10_clone_test->GetBinContent(3)/h_dy_njets10_clone->GetBinContent(3))/(h_data_njets10_clone_test->GetBinContent(1)/h_dy_njets10_clone->GetBinContent(1));
  unc_kap2_7 = kap2_7*TMath::Sqrt(TMath::Power(h_data_njets10_clone_test->GetBinError(1)/h_data_njets10_clone_test->GetBinContent(1),2) + TMath::Power(h_data_njets10_clone_test->GetBinError(3)/h_data_njets10_clone_test->GetBinContent(3),2) + TMath::Power(h_dy_njets10_clone->GetBinError(1)/h_dy_njets10_clone->GetBinContent(1),2) + TMath::Power(h_dy_njets10_clone->GetBinError(3)/h_dy_njets10_clone->GetBinContent(3),2));
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
    // njets 5-6
  h_data_njets67->SetMarkerStyle(20); h_data_njets67->SetMarkerSize(2);
  h_data_njets67->SetLineColor(kBlack); h_qcd_njets67->SetLineColor(kBlack); h_ttbar_njets67->SetLineColor(kBlack); h_wjets_njets67->SetLineColor(kBlack); h_other_njets67->SetLineColor(kBlack);
  h_qcd_njets67->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets67->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets67->SetFillColor(TColor::GetColor("#832db6")); h_other_njets67->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets67->SetLineWidth(2); h_qcd_njets67->SetLineWidth(1); h_ttbar_njets67->SetLineWidth(1); h_wjets_njets67->SetLineWidth(1); h_other_njets67->SetLineWidth(1);
  h_data_njets67->SetTitle("");
  h_data_njets67->GetXaxis()->SetLabelOffset(1);
  h_data_njets67->GetYaxis()->SetLabelSize(0.07); h_data_njets67->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets67->GetYaxis()->SetTitleOffset(0.92); h_data_njets67->GetYaxis()->SetTitleSize(0.08);
  h_data_njets67->SetMinimum(0.02); h_data_njets67->SetMaximum(h_data_njets67->GetBinContent(1)*20000000);
  h_data_njets67_clone->SetTitle("");
  h_data_njets67_clone->GetXaxis()->SetNdivisions(505); h_data_njets67_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets67_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets67_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets67_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets67_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets67_clone->GetYaxis()->SetNdivisions(505); h_data_njets67_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets67_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets67_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets67_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets67_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets67_clone->GetXaxis()->SetLabelSize(0);
    // njets 7-8
  h_data_njets89->SetMarkerStyle(20); h_data_njets89->SetMarkerSize(2);
  h_data_njets89->SetLineColor(kBlack); h_qcd_njets89->SetLineColor(kBlack); h_ttbar_njets89->SetLineColor(kBlack); h_wjets_njets89->SetLineColor(kBlack); h_other_njets89->SetLineColor(kBlack);
  h_qcd_njets89->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets89->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets89->SetFillColor(TColor::GetColor("#832db6")); h_other_njets89->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets89->SetLineWidth(2); h_qcd_njets89->SetLineWidth(1); h_ttbar_njets89->SetLineWidth(1); h_wjets_njets89->SetLineWidth(1); h_other_njets89->SetLineWidth(1);
  h_data_njets89->SetTitle("");
  h_data_njets89->GetXaxis()->SetLabelOffset(1);
  h_data_njets89->GetYaxis()->SetLabelSize(0.07); h_data_njets89->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets89->GetYaxis()->SetTitleOffset(0.92); h_data_njets89->GetYaxis()->SetTitleSize(0.08);
  h_data_njets89->SetMinimum(0.02); h_data_njets89->SetMaximum(h_data_njets89->GetBinContent(1)*20000000);
  h_data_njets89_clone->SetTitle("");
  h_data_njets89_clone->GetXaxis()->SetNdivisions(505); h_data_njets89_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets89_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets89_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets89_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets89_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets89_clone->GetYaxis()->SetNdivisions(505); h_data_njets89_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets89_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets89_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets89_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets89_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets89_clone->GetXaxis()->SetLabelSize(0);
    // njets 9-
  h_data_njets10->SetMarkerStyle(20); h_data_njets10->SetMarkerSize(2);
  h_data_njets10->SetLineColor(kBlack); h_qcd_njets10->SetLineColor(kBlack); h_ttbar_njets10->SetLineColor(kBlack); h_wjets_njets10->SetLineColor(kBlack); h_other_njets10->SetLineColor(kBlack);
  h_data_njets10->SetLineWidth(2); h_qcd_njets10->SetLineWidth(1); h_ttbar_njets10->SetLineWidth(1); h_wjets_njets10->SetLineWidth(1); h_other_njets10->SetLineWidth(1);
  h_qcd_njets10->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets10->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets10->SetFillColor(TColor::GetColor("#832db6")); h_other_njets10->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets10->SetTitle("");
  h_data_njets10->GetXaxis()->SetLabelOffset(1);
  h_data_njets10->GetYaxis()->SetLabelSize(0.07); h_data_njets10->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets10->GetYaxis()->SetTitleOffset(0.92); h_data_njets10->GetYaxis()->SetTitleSize(0.08);
  h_data_njets10->SetMinimum(0.02); h_data_njets10->SetMaximum(h_data_njets10->GetBinContent(1)*20000000);
  h_data_njets10_clone->SetTitle("");
  h_data_njets10_clone->GetXaxis()->SetNdivisions(505); h_data_njets10_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets10_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets10_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets10_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets10_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets10_clone->GetYaxis()->SetNdivisions(505); h_data_njets10_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets10_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets10_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets10_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets10_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets10_clone->GetXaxis()->SetLabelSize(0);

  h_signal_njets67_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets67_m1200->SetLineWidth(4); h_signal_njets67_m1200->SetLineStyle(2);
  h_signal_njets89_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets89_m1200->SetLineWidth(4); h_signal_njets89_m1200->SetLineStyle(2);
  h_signal_njets10_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets10_m1200->SetLineWidth(4); h_signal_njets10_m1200->SetLineStyle(2);
  h_signal_njets67_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets67_m1800->SetLineWidth(4); h_signal_njets67_m1800->SetLineStyle(1);
  h_signal_njets89_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets89_m1800->SetLineWidth(4); h_signal_njets89_m1800->SetLineStyle(1);
  h_signal_njets10_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets10_m1800->SetLineWidth(4); h_signal_njets10_m1800->SetLineStyle(1);

  // Make TLatex
  TLatex* tex_lumi = new TLatex(0.89, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.07);
  //TLatex *TexCMS = new TLatex(0.15,0.925,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.15,0.925,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.07);
  TexCMS->SetLineWidth(2);

  TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
  TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
  TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
  TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
  tex_mj500->SetTextSize(0.15); tex_mj800->SetTextSize(0.15); tex_mj1100->SetTextSize(0.15); tex_mj1400->SetTextSize(0.15);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

  TLatex* tex_Nlep0   = new TLatex(0.20, 0.78, "N_{lep} = 0");
  TLatex* tex_Njets56 = new TLatex(0.20, 0.67, "5 #leq N_{jet} #leq 6");
  TLatex* tex_Njets78 = new TLatex(0.20, 0.67, "7 #leq N_{jet} #leq 8");
  TLatex* tex_Njets9  = new TLatex(0.20, 0.67, "N_{jet} #geq 9");
  TLatex* tex_Nb0     = new TLatex(0.20, 0.56, "N_{b} = 0");
  tex_Nlep0->SetNDC();   tex_Nlep0->SetTextFont(42);   tex_Nlep0->SetTextSize(0.07);
  tex_Njets56->SetNDC(); tex_Njets56->SetTextFont(42); tex_Njets56->SetTextSize(0.07);
  tex_Njets78->SetNDC(); tex_Njets78->SetTextFont(42); tex_Njets78->SetTextSize(0.07);
  tex_Njets9->SetNDC();  tex_Njets9->SetTextFont(42);  tex_Njets9->SetTextSize(0.07);
  tex_Nb0->SetNDC();     tex_Nb0->SetTextFont(42);     tex_Nb0->SetTextSize(0.07);

  // Normalize
  h_qcd_njets67->Scale(sf_njets67);    h_other_njets67->Scale(sf_njets67);  h_wjets_njets67->Scale(sf_njets67); h_ttbar_njets67->Scale(sf_njets67);
  h_qcd_njets89->Scale(sf_njets89);    h_other_njets89->Scale(sf_njets89);  h_wjets_njets89->Scale(sf_njets89); h_ttbar_njets89->Scale(sf_njets89);
  h_qcd_njets10->Scale(sf_njets10);    h_other_njets10->Scale(sf_njets10);  h_wjets_njets10->Scale(sf_njets10); h_ttbar_njets10->Scale(sf_njets10);
  h_tot_mc_njets67->Scale(sf_njets67); h_tot_mc_njets89->Scale(sf_njets89); h_tot_mc_njets10->Scale(sf_njets10);
  cout << "sf_njets67: " << sf_njets67 << endl;
  cout << "sf_njets89: " << sf_njets89 << endl;
  cout << "sf_njets10: " << sf_njets10 << endl;


  // Make THStack
  THStack* st_mc_njets67 = new THStack("st_mc_njets67", "st_mc_njets67");
  THStack* st_mc_njets89 = new THStack("st_mc_njets89", "st_mc_njets89");
  THStack* st_mc_njets10  = new THStack("st_mc_njets10",  "st_mc_njets10");
  st_mc_njets67->Add(h_other_njets67); st_mc_njets67->Add(h_ttbar_njets67); st_mc_njets67->Add(h_wjets_njets67); st_mc_njets67->Add(h_qcd_njets67);
  st_mc_njets89->Add(h_other_njets89); st_mc_njets89->Add(h_ttbar_njets89); st_mc_njets89->Add(h_wjets_njets89); st_mc_njets89->Add(h_qcd_njets89);
  st_mc_njets10->Add(h_other_njets10); st_mc_njets10->Add(h_ttbar_njets10); st_mc_njets10->Add(h_wjets_njets10); st_mc_njets10->Add(h_qcd_njets10);


  // Make TLegend
    // njets 3-4
  TLegend* l_njets67_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets67_2->SetTextSize(0.055);
  l_njets67_2->SetBorderSize(0);
  l_njets67_2->SetFillStyle(0);
  l_njets67_2->AddEntry(h_data_njets67,   "data", "elp");
  l_njets67_2->AddEntry(h_qcd_njets67,    "QCD", "f");
  l_njets67_2->AddEntry(h_ttbar_njets67,  "t#bar{t}", "f");
  l_njets67_2->AddEntry(h_wjets_njets67,  "W+jets", "f");
  l_njets67_2->AddEntry(h_other_njets67,  "Other", "f");
  l_njets67_2->AddEntry(h_signal_njets67_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets67_2->AddEntry(h_signal_njets67_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 5-6
  TLegend* l_njets89_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets89_2->SetTextSize(0.055);
  l_njets89_2->SetBorderSize(0);
  l_njets89_2->SetFillStyle(0);
  l_njets89_2->AddEntry(h_data_njets89,   "data", "elp");
  l_njets89_2->AddEntry(h_qcd_njets89,    "QCD", "f");
  l_njets89_2->AddEntry(h_ttbar_njets89,  "t#bar{t}", "f");
  l_njets89_2->AddEntry(h_wjets_njets89,  "W+jets", "f");
  l_njets89_2->AddEntry(h_other_njets89,  "Other", "f");
  l_njets89_2->AddEntry(h_signal_njets89_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets89_2->AddEntry(h_signal_njets89_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 7
  TLegend* l_njets10_2 = new TLegend(0.45, 0.45, 0.85, 0.87);
  l_njets10_2->SetTextSize(0.055);
  l_njets10_2->SetBorderSize(0);
  l_njets10_2->SetFillStyle(0);
  l_njets10_2->AddEntry(h_data_njets10,   "data", "elp");
  l_njets10_2->AddEntry(h_qcd_njets10,    "QCD", "f");
  l_njets10_2->AddEntry(h_ttbar_njets10,  "t#bar{t}", "f");
  l_njets10_2->AddEntry(h_wjets_njets10,  "W+jets", "f");
  l_njets10_2->AddEntry(h_other_njets10,  "Other", "f");
  l_njets10_2->AddEntry(h_signal_njets10_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets10_2->AddEntry(h_signal_njets10_m1800, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);

    // njets 5-6
  TPad *tpad_njets67(NULL), *bpad_njets67(NULL);
      // tpad
  TCanvas* c_njets67 = new TCanvas("c_njets67", "c_njets67", 800, 800);
  c_njets67->cd();
  tpad_njets67 = new TPad("tpad_njets67","tpad_njets67",0.,0.3,1.,1.);
  tpad_njets67->SetLeftMargin(0.15); tpad_njets67->SetBottomMargin(0.02); tpad_njets67->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets67->Draw();
  tpad_njets67->cd();
  gPad->SetLogy();
  h_data_njets67->GetYaxis()->SetLabelSize(0);
  h_data_njets67->Draw("EP");
  st_mc_njets67->Draw("same hist");
  h_data_njets67->Draw("same EP");
  h_signal_njets67_m1200->Draw("same hist");
  h_signal_njets67_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets67_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets56->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  TLatex* label_njets56_1 = new TLatex(0.12, 0.11, "1");
  label_njets56_1->SetNDC(); label_njets56_1->SetTextSize(0.07); label_njets56_1->SetTextFont(42);
  TLatex* label_njets56_2 = new TLatex(0.075, 0.235, "10^{2}");
  label_njets56_2->SetNDC(); label_njets56_2->SetTextSize(0.07); label_njets56_2->SetTextFont(42);
  TLatex* label_njets56_3 = new TLatex(0.075, 0.355, "10^{4}");
  label_njets56_3->SetNDC(); label_njets56_3->SetTextSize(0.07); label_njets56_3->SetTextFont(42);
  TLatex* label_njets56_4 = new TLatex(0.075, 0.47, "10^{6}");
  label_njets56_4->SetNDC(); label_njets56_4->SetTextSize(0.07); label_njets56_4->SetTextFont(42);
  TLatex* label_njets56_5 = new TLatex(0.075, 0.595, "10^{8}");
  label_njets56_5->SetNDC(); label_njets56_5->SetTextSize(0.07); label_njets56_5->SetTextFont(42);
  TLatex* label_njets56_6 = new TLatex(0.059, 0.71, "10^{10}");
  label_njets56_6->SetNDC(); label_njets56_6->SetTextSize(0.07); label_njets56_6->SetTextFont(42);
  label_njets56_1->Draw();
  label_njets56_2->Draw();
  label_njets56_3->Draw();
  label_njets56_4->Draw();
  label_njets56_5->Draw();
  label_njets56_6->Draw();
  
  // test end
      // bpad
  c_njets67->cd();
  bpad_njets67 = new TPad("bpad_njets67","bpad_njets67",0.,0.,1.,0.305);
  bpad_njets67->SetLeftMargin(0.15);
  bpad_njets67->SetTopMargin(0.); bpad_njets67->SetBottomMargin(0.4); bpad_njets67->SetFillStyle(4000);
  bpad_njets67->Draw(); bpad_njets67->cd();

  TH1D* h_data_njets67_err = (TH1D*)h_data_njets67->Clone("h_data_njets67_err");
  h_data_njets67_err->SetMarkerSize(0);
  h_data_njets67_err->SetFillColor(kBlack);
  h_data_njets67_err->SetLineColor(kBlack);
  h_data_njets67_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets67_err->SetBinContent(imj, h_data_njets67->GetBinContent(imj)/h_tot_mc_njets67->GetBinContent(imj));
    h_data_njets67_err->SetBinError(imj, (h_data_njets67->GetBinContent(imj)/h_tot_mc_njets67->GetBinContent(imj))*(h_tot_mc_njets67->GetBinError(imj)/h_tot_mc_njets67->GetBinContent(imj)));
  }
  cout << h_data_njets67->GetBinContent(1) << endl;
  cout << h_data_njets67->GetBinError(1) << endl;
  cout << h_tot_mc_njets67->GetBinContent(1) << endl;
  cout << h_tot_mc_njets67->GetBinError(1) << endl;

  h_data_njets67_clone->Divide(h_tot_mc_njets67);
  h_data_njets67_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets67_clone->SetLineColor(kBlack);
  h_data_njets67_clone->SetLineWidth(2);
  h_data_njets67_clone->SetMarkerStyle(20);
  h_data_njets67_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets67_clone->SetBinError(imj, h_data_njets67_clone->GetBinContent(imj)*(h_data_njets67->GetBinError(imj)/h_data_njets67->GetBinContent(imj)));
  }
  h_data_njets67_clone->Draw("ep");
  h_data_njets67_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets67->Print(Form("plots/qcd_kappa/qcd_kappa_njets56_lumi%s.pdf", lumi_title.Data()));

    // njets 7-8
  TPad *tpad_njets89(NULL), *bpad_njets89(NULL);
      // tpad
  TCanvas* c_njets89 = new TCanvas("c_njets89", "c_njets89", 800, 800);
  c_njets89->cd();
  tpad_njets89 = new TPad("tpad_njets89","tpad_njets89",0.,0.3,1.,1.);
  tpad_njets89->SetLeftMargin(0.15); tpad_njets89->SetBottomMargin(0.02); tpad_njets89->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets89->Draw();
  tpad_njets89->cd();
  gPad->SetLogy();
  h_data_njets89->GetYaxis()->SetLabelSize(0);
  h_data_njets89->Draw("EP");
  st_mc_njets89->Draw("same hist");
  h_data_njets89->Draw("same EP");
  h_signal_njets89_m1200->Draw("same hist");
  h_signal_njets89_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets89_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets78->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  TLatex* label_njets78_1 = new TLatex(0.125, 0.11, "1");
  TLatex* label_njets78_2 = new TLatex(0.075, 0.24, "10^{2}");
  TLatex* label_njets78_3 = new TLatex(0.075, 0.37, "10^{4}");
  TLatex* label_njets78_4 = new TLatex(0.075, 0.505, "10^{6}");
  TLatex* label_njets78_5 = new TLatex(0.075, 0.635, "10^{8}");
  TLatex* label_njets78_6 = new TLatex(0.059, 0.765, "10^{10}");
  label_njets78_1->SetNDC(); label_njets78_1->SetTextSize(0.07); label_njets78_1->SetTextFont(42);
  label_njets78_2->SetNDC(); label_njets78_2->SetTextSize(0.07); label_njets78_2->SetTextFont(42);
  label_njets78_3->SetNDC(); label_njets78_3->SetTextSize(0.07); label_njets78_3->SetTextFont(42);
  label_njets78_4->SetNDC(); label_njets78_4->SetTextSize(0.07); label_njets78_4->SetTextFont(42);
  label_njets78_5->SetNDC(); label_njets78_5->SetTextSize(0.07); label_njets78_5->SetTextFont(42);
  label_njets78_6->SetNDC(); label_njets78_6->SetTextSize(0.07); label_njets78_6->SetTextFont(42);
  label_njets78_1->Draw();
  label_njets78_2->Draw();
  label_njets78_3->Draw();
  label_njets78_4->Draw();
  label_njets78_5->Draw();
  label_njets78_6->Draw();
  
  // test end
      // bpad
  c_njets89->cd();
  bpad_njets89 = new TPad("bpad_njets89","bpad_njets89",0.,0.,1.,0.305);
  bpad_njets89->SetLeftMargin(0.15);
  bpad_njets89->SetTopMargin(0.); bpad_njets89->SetBottomMargin(0.4); bpad_njets89->SetFillStyle(4000);
  bpad_njets89->Draw(); bpad_njets89->cd();

  TH1D* h_data_njets89_err = (TH1D*)h_data_njets89->Clone("h_data_njets89_err");
  h_data_njets89_err->SetMarkerSize(0);
  h_data_njets89_err->SetFillColor(kBlack);
  h_data_njets89_err->SetLineColor(kBlack);
  h_data_njets89_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets89_err->SetBinContent(imj, h_data_njets89->GetBinContent(imj)/h_tot_mc_njets89->GetBinContent(imj));
    h_data_njets89_err->SetBinError(imj, (h_data_njets89->GetBinContent(imj)/h_tot_mc_njets89->GetBinContent(imj))*(h_tot_mc_njets89->GetBinError(imj)/h_tot_mc_njets89->GetBinContent(imj)));
  }

  h_data_njets89_clone->Divide(h_tot_mc_njets89);
  h_data_njets89_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets89_clone->SetLineColor(kBlack);
  h_data_njets89_clone->SetLineWidth(2);
  h_data_njets89_clone->SetMarkerStyle(20);
  h_data_njets89_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets89_clone->SetBinError(imj, h_data_njets89_clone->GetBinContent(imj)*(h_data_njets89->GetBinError(imj)/h_data_njets89->GetBinContent(imj)));
  }
  h_data_njets89_clone->Draw("ep");
  h_data_njets89_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets89->Print(Form("plots/qcd_kappa/qcd_kappa_njets78_lumi%s.pdf", lumi_title.Data()));

    // njets 9-
  TPad *tpad_njets10(NULL), *bpad_njets10(NULL);
      // tpad
  TCanvas* c_njets10 = new TCanvas("c_njets10", "c_njets10", 800, 800);
  c_njets10->cd();
  tpad_njets10 = new TPad("tpad_njets10","tpad_njets10",0.,0.3,1.,1.);
  tpad_njets10->SetLeftMargin(0.15); tpad_njets10->SetBottomMargin(0.02); tpad_njets10->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets10->Draw();
  tpad_njets10->cd();
  gPad->SetLogy();
  h_data_njets10->GetYaxis()->SetLabelSize(0);
  h_data_njets10->Draw("EP");
  st_mc_njets10->Draw("same hist");
  h_data_njets10->Draw("same EP");
  h_signal_njets10_m1200->Draw("same hist");
  h_signal_njets10_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets10_2->Draw();
  tex_Nlep0->Draw();
  tex_Njets9->Draw();
  tex_Nb0->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  TLatex* label_njets9_1 = new TLatex(0.12, 0.10, "1");
  label_njets9_1->SetNDC(); label_njets9_1->SetTextSize(0.07); label_njets9_1->SetTextFont(42);
  TLatex* label_njets9_2 = new TLatex(0.075, 0.22, "10^{2}");
  label_njets9_2->SetNDC(); label_njets9_2->SetTextSize(0.07); label_njets9_2->SetTextFont(42);
  TLatex* label_njets9_3 = new TLatex(0.075, 0.34, "10^{4}");
  label_njets9_3->SetNDC(); label_njets9_3->SetTextSize(0.07); label_njets9_3->SetTextFont(42);
  TLatex* label_njets9_4 = new TLatex(0.075, 0.46, "10^{6}");
  label_njets9_4->SetNDC(); label_njets9_4->SetTextSize(0.07); label_njets9_4->SetTextFont(42);
  TLatex* label_njets9_5 = new TLatex(0.075, 0.58, "10^{8}");
  label_njets9_5->SetNDC(); label_njets9_5->SetTextSize(0.07); label_njets9_5->SetTextFont(42);
  TLatex* label_njets9_6 = new TLatex(0.059, 0.705, "10^{10}");
  label_njets9_6->SetNDC(); label_njets9_6->SetTextSize(0.07); label_njets9_6->SetTextFont(42);
  TLatex* label_njets9_7 = new TLatex(0.059, 0.824, "10^{12}");
  label_njets9_7->SetNDC(); label_njets9_7->SetTextSize(0.07); label_njets9_7->SetTextFont(42);
  label_njets9_1->Draw();
  label_njets9_2->Draw();
  label_njets9_3->Draw();
  label_njets9_4->Draw();
  label_njets9_5->Draw();
  label_njets9_6->Draw();
  label_njets9_7->Draw();
  
  // test end
      // bpad
  c_njets10->cd();
  bpad_njets10 = new TPad("bpad_njets10","bpad_njets10",0.,0.,1.,0.305);
  bpad_njets10->SetLeftMargin(0.15);
  bpad_njets10->SetTopMargin(0.); bpad_njets10->SetBottomMargin(0.4); bpad_njets10->SetFillStyle(4000);
  bpad_njets10->Draw(); bpad_njets10->cd();

  TH1D* h_data_njets10_err = (TH1D*)h_data_njets10->Clone("h_data_njets10_err");
  h_data_njets10_err->SetMarkerSize(0);
  h_data_njets10_err->SetFillColor(kBlack);
  h_data_njets10_err->SetLineColor(kBlack);
  h_data_njets10_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets10_err->SetBinContent(imj, h_data_njets10->GetBinContent(imj)/h_tot_mc_njets10->GetBinContent(imj));
    h_data_njets10_err->SetBinError(imj, (h_data_njets10->GetBinContent(imj)/h_tot_mc_njets10->GetBinContent(imj))*(h_tot_mc_njets10->GetBinError(imj)/h_tot_mc_njets10->GetBinContent(imj)));
  }

  h_data_njets10_clone->Divide(h_tot_mc_njets10);
  h_data_njets10_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets10_clone->SetLineColor(kBlack);
  h_data_njets10_clone->SetLineWidth(2);
  h_data_njets10_clone->SetMarkerStyle(20);
  h_data_njets10_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets10_clone->SetBinError(imj, h_data_njets10_clone->GetBinContent(imj)*(h_data_njets10->GetBinError(imj)/h_data_njets10->GetBinContent(imj)));
  }
  h_data_njets10_clone->Draw("ep");
  h_data_njets10_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets10->Print(Form("plots/qcd_kappa/qcd_kappa_njets9_lumi%s.pdf", lumi_title.Data()));


}

void wjets_kappa_plot_dy_region_combine()
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

  double lumi=138.;
  TString lumi_title="138";

  // define histogram
  TH1D* h_data_njets34_16  = new TH1D("h_data_njets34_16",  "h_data_njets34_16",  3, 500, 1400);
  TH1D* h_data_njets34_1718  = new TH1D("h_data_njets34_1718",  "h_data_njets34_1718",  3, 500, 1400);
  TH1D* h_data_njets56_16  = new TH1D("h_data_njets56_16",  "h_data_njets56_16",  3, 500, 1400);
  TH1D* h_data_njets56_1718  = new TH1D("h_data_njets56_1718",  "h_data_njets56_1718",  3, 500, 1400);
  TH1D* h_data_njets7_16   = new TH1D("h_data_njets7_16",   "h_data_njets7_16",   3, 500, 1400);
  TH1D* h_data_njets7_1718   = new TH1D("h_data_njets7_1718",   "h_data_njets7_1718",   3, 500, 1400);
  TH1D* h_dy_njets34_16    = new TH1D("h_dy_njets34_16",    "h_dy_njets34_16",    3, 500, 1400);
  TH1D* h_dy_njets34_1718    = new TH1D("h_dy_njets34_1718",    "h_dy_njets34_1718",    3, 500, 1400);
  TH1D* h_dy_njets56_16    = new TH1D("h_dy_njets56_16",    "h_dy_njets56_16",    3, 500, 1400);
  TH1D* h_dy_njets56_1718    = new TH1D("h_dy_njets56_1718",    "h_dy_njets56_1718",    3, 500, 1400);
  TH1D* h_dy_njets7_16     = new TH1D("h_dy_njets7_16",     "h_dy_njets7_16",     3, 500, 1400);
  TH1D* h_dy_njets7_1718     = new TH1D("h_dy_njets7_1718",     "h_dy_njets7_1718",     3, 500, 1400);
  TH1D* h_qcd_njets34_16   = new TH1D("h_qcd_njets34_16",   "h_qcd_njets34_16",   3, 500, 1400);
  TH1D* h_qcd_njets34_1718   = new TH1D("h_qcd_njets34_1718",   "h_qcd_njets34_1718",   3, 500, 1400);
  TH1D* h_qcd_njets56_16   = new TH1D("h_qcd_njets56_16",   "h_qcd_njets56_16",   3, 500, 1400);
  TH1D* h_qcd_njets56_1718   = new TH1D("h_qcd_njets56_1718",   "h_qcd_njets56_1718",   3, 500, 1400);
  TH1D* h_qcd_njets7_16    = new TH1D("h_qcd_njets7_16",    "h_qcd_njets7_16",    3, 500, 1400);
  TH1D* h_qcd_njets7_1718    = new TH1D("h_qcd_njets7_1718",    "h_qcd_njets7_1718",    3, 500, 1400);
  TH1D* h_ttbar_njets34_16 = new TH1D("h_ttbar_njets34_16", "h_ttbar_njets34_16", 3, 500, 1400);
  TH1D* h_ttbar_njets34_1718 = new TH1D("h_ttbar_njets34_1718", "h_ttbar_njets34_1718", 3, 500, 1400);
  TH1D* h_ttbar_njets56_16 = new TH1D("h_ttbar_njets56_16", "h_ttbar_njets56_16", 3, 500, 1400);
  TH1D* h_ttbar_njets56_1718 = new TH1D("h_ttbar_njets56_1718", "h_ttbar_njets56_1718", 3, 500, 1400);
  TH1D* h_ttbar_njets7_16  = new TH1D("h_ttbar_njets7_16",  "h_ttbar_njets7_16",  3, 500, 1400);
  TH1D* h_ttbar_njets7_1718  = new TH1D("h_ttbar_njets7_1718",  "h_ttbar_njets7_1718",  3, 500, 1400);
  TH1D* h_wjets_njets34_16 = new TH1D("h_wjets_njets34_16", "h_wjets_njets34_16", 3, 500, 1400);
  TH1D* h_wjets_njets34_1718 = new TH1D("h_wjets_njets34_1718", "h_wjets_njets34_1718", 3, 500, 1400);
  TH1D* h_wjets_njets56_16 = new TH1D("h_wjets_njets56_16", "h_wjets_njets56_16", 3, 500, 1400);
  TH1D* h_wjets_njets56_1718 = new TH1D("h_wjets_njets56_1718", "h_wjets_njets56_1718", 3, 500, 1400);
  TH1D* h_wjets_njets7_16  = new TH1D("h_wjets_njets7_16",  "h_wjets_njets7_16",  3, 500, 1400);
  TH1D* h_wjets_njets7_1718  = new TH1D("h_wjets_njets7_1718",  "h_wjets_njets7_1718",  3, 500, 1400);
  TH1D* h_other_njets34_16 = new TH1D("h_other_njets34_16", "h_other_njets34_16", 3, 500, 1400);
  TH1D* h_other_njets34_1718 = new TH1D("h_other_njets34_1718", "h_other_njets34_1718", 3, 500, 1400);
  TH1D* h_other_njets56_16 = new TH1D("h_other_njets56_16", "h_other_njets56_16", 3, 500, 1400);
  TH1D* h_other_njets56_1718 = new TH1D("h_other_njets56_1718", "h_other_njets56_1718", 3, 500, 1400);
  TH1D* h_other_njets7_16  = new TH1D("h_other_njets7_16",  "h_other_njets7_16",  3, 500, 1400);
  TH1D* h_other_njets7_1718  = new TH1D("h_other_njets7_1718",  "h_other_njets7_1718",  3, 500, 1400);
  TH1D* h_signal_njets34_m1200_16 = new TH1D("h_signal_njets34_m1200_16", "h_signal_njets34_m1200_16", 3, 500, 1400);
  TH1D* h_signal_njets34_m1200_1718 = new TH1D("h_signal_njets34_m1200_1718", "h_signal_njets34_m1200_1718", 3, 500, 1400);
  TH1D* h_signal_njets56_m1200_16 = new TH1D("h_signal_njets56_m1200_16", "h_signal_njets56_m1200_16", 3, 500, 1400);
  TH1D* h_signal_njets56_m1200_1718 = new TH1D("h_signal_njets56_m1200_1718", "h_signal_njets56_m1200_1718", 3, 500, 1400);
  TH1D* h_signal_njets7_m1200_16  = new TH1D("h_signal_njets7_m1200_16",  "h_signal_njets7_m1200_16",  3, 500, 1400);
  TH1D* h_signal_njets7_m1200_1718  = new TH1D("h_signal_njets7_m1200_1718",  "h_signal_njets7_m1200_1718",  3, 500, 1400);
  TH1D* h_signal_njets34_m1800_16 = new TH1D("h_signal_njets34_m1800_16", "h_signal_njets34_m1800_16", 3, 500, 1400);
  TH1D* h_signal_njets34_m1800_1718 = new TH1D("h_signal_njets34_m1800_1718", "h_signal_njets34_m1800_1718", 3, 500, 1400);
  TH1D* h_signal_njets56_m1800_16 = new TH1D("h_signal_njets56_m1800_16", "h_signal_njets56_m1800_16", 3, 500, 1400);
  TH1D* h_signal_njets56_m1800_1718 = new TH1D("h_signal_njets56_m1800_1718", "h_signal_njets56_m1800_1718", 3, 500, 1400);
  TH1D* h_signal_njets7_m1800_16  = new TH1D("h_signal_njets7_m1800_16",  "h_signal_njets7_m1800_16",  3, 500, 1400);
  TH1D* h_signal_njets7_m1800_1718  = new TH1D("h_signal_njets7_m1800_1718",  "h_signal_njets7_m1800_1718",  3, 500, 1400);

  TFile* f_16   = new TFile("data/wjets_kappa_meas_UL2016_comb.root", "READ");
  TFile* f_1718 = new TFile("data/wjets_kappa_meas_UL20178_comb.root", "READ");

  h_data_njets34_16 = static_cast<TH1D*>(f_16->Get("h_data_njets34_clone"));
  h_data_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets34_clone"));
  h_data_njets56_16 = static_cast<TH1D*>(f_16->Get("h_data_njets56_clone"));
  h_data_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets56_clone"));
  h_data_njets7_16 = static_cast<TH1D*>(f_16->Get("h_data_njets7_clone"));
  h_data_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_data_njets7_clone"));
  h_dy_njets34_16 = static_cast<TH1D*>(f_16->Get("h_dy_njets34_clone"));
  h_dy_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_dy_njets34_clone"));
  h_dy_njets56_16 = static_cast<TH1D*>(f_16->Get("h_dy_njets56_clone"));
  h_dy_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_dy_njets56_clone"));
  h_dy_njets7_16 = static_cast<TH1D*>(f_16->Get("h_dy_njets7_clone"));
  h_dy_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_dy_njets7_clone"));
  h_qcd_njets34_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets34_clone"));
  h_qcd_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets34_clone"));
  h_qcd_njets56_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets56_clone"));
  h_qcd_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets56_clone"));
  h_qcd_njets7_16 = static_cast<TH1D*>(f_16->Get("h_qcd_njets7_clone"));
  h_qcd_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_qcd_njets7_clone"));
  h_ttbar_njets34_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets34_clone"));
  h_ttbar_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets34_clone"));
  h_ttbar_njets56_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets56_clone"));
  h_ttbar_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets56_clone"));
  h_ttbar_njets7_16 = static_cast<TH1D*>(f_16->Get("h_ttbar_njets7_clone"));
  h_ttbar_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_ttbar_njets7_clone"));
  h_wjets_njets34_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets34_clone"));
  h_wjets_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets34_clone"));
  h_wjets_njets56_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets56_clone"));
  h_wjets_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets56_clone"));
  h_wjets_njets7_16 = static_cast<TH1D*>(f_16->Get("h_wjets_njets7_clone"));
  h_wjets_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_wjets_njets7_clone"));
  h_other_njets34_16 = static_cast<TH1D*>(f_16->Get("h_other_njets34_clone"));
  h_other_njets34_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets34_clone"));
  h_other_njets56_16 = static_cast<TH1D*>(f_16->Get("h_other_njets56_clone"));
  h_other_njets56_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets56_clone"));
  h_other_njets7_16 = static_cast<TH1D*>(f_16->Get("h_other_njets7_clone"));
  h_other_njets7_1718 = static_cast<TH1D*>(f_1718->Get("h_other_njets7_clone"));
  h_signal_njets34_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets34_m1200"));
  h_signal_njets34_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets34_m1200"));
  h_signal_njets56_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets56_m1200"));
  h_signal_njets56_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets56_m1200"));
  h_signal_njets7_m1200_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets7_m1200"));
  h_signal_njets7_m1200_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets7_m1200"));
  h_signal_njets34_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets34_m1800"));
  h_signal_njets34_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets34_m1800"));
  h_signal_njets56_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets56_m1800"));
  h_signal_njets56_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets56_m1800"));
  h_signal_njets7_m1800_16 = static_cast<TH1D*>(f_16->Get("h_signal_njets7_m1800"));
  h_signal_njets7_m1800_1718 = static_cast<TH1D*>(f_1718->Get("h_signal_njets7_m1800"));



  TH1D* h_data_njets34  = (TH1D*)h_data_njets34_16->Clone("h_data_njets34");
  h_data_njets34->Add(h_data_njets34_1718);
  TH1D* h_data_njets56  = (TH1D*)h_data_njets56_16->Clone("h_data_njets56");
  h_data_njets56->Add(h_data_njets56_1718);
  TH1D* h_data_njets7  = (TH1D*)h_data_njets7_16->Clone("h_data_njets7");
  h_data_njets7->Add(h_data_njets7_1718);
  TH1D* h_dy_njets34  = (TH1D*)h_dy_njets34_16->Clone("h_dy_njets34");
  h_dy_njets34->Add(h_dy_njets34_1718);
  TH1D* h_dy_njets56  = (TH1D*)h_dy_njets56_16->Clone("h_dy_njets56");
  h_dy_njets56->Add(h_dy_njets56_1718);
  TH1D* h_dy_njets7  = (TH1D*)h_dy_njets7_16->Clone("h_dy_njets7");
  h_dy_njets7->Add(h_dy_njets7_1718);
  TH1D* h_qcd_njets34  = (TH1D*)h_qcd_njets34_16->Clone("h_qcd_njets34");
  h_qcd_njets34->Add(h_qcd_njets34_1718);
  TH1D* h_qcd_njets56  = (TH1D*)h_qcd_njets56_16->Clone("h_qcd_njets56");
  h_qcd_njets56->Add(h_qcd_njets56_1718);
  TH1D* h_qcd_njets7  = (TH1D*)h_qcd_njets7_16->Clone("h_qcd_njets7");
  h_qcd_njets7->Add(h_qcd_njets7_1718);
  TH1D* h_ttbar_njets34  = (TH1D*)h_ttbar_njets34_16->Clone("h_ttbar_njets34");
  h_ttbar_njets34->Add(h_ttbar_njets34_1718);
  TH1D* h_ttbar_njets56  = (TH1D*)h_ttbar_njets56_16->Clone("h_ttbar_njets56");
  h_ttbar_njets56->Add(h_ttbar_njets56_1718);
  TH1D* h_ttbar_njets7  = (TH1D*)h_ttbar_njets7_16->Clone("h_ttbar_njets7");
  h_ttbar_njets7->Add(h_ttbar_njets7_1718);
  TH1D* h_wjets_njets34  = (TH1D*)h_wjets_njets34_16->Clone("h_wjets_njets34");
  h_wjets_njets34->Add(h_wjets_njets34_1718);
  TH1D* h_wjets_njets56  = (TH1D*)h_wjets_njets56_16->Clone("h_wjets_njets56");
  h_wjets_njets56->Add(h_wjets_njets56_1718);
  TH1D* h_wjets_njets7  = (TH1D*)h_wjets_njets7_16->Clone("h_wjets_njets7");
  h_wjets_njets7->Add(h_wjets_njets7_1718);
  TH1D* h_other_njets34  = (TH1D*)h_other_njets34_16->Clone("h_other_njets34");
  h_other_njets34->Add(h_other_njets34_1718);
  TH1D* h_other_njets56  = (TH1D*)h_other_njets56_16->Clone("h_other_njets56");
  h_other_njets56->Add(h_other_njets56_1718);
  TH1D* h_other_njets7  = (TH1D*)h_other_njets7_16->Clone("h_other_njets7");
  h_other_njets7->Add(h_other_njets7_1718);
  TH1D* h_signal_njets34_m1200  = (TH1D*)h_signal_njets34_m1200_16->Clone("h_signal_njets34_m1200");
  h_signal_njets34_m1200->Add(h_signal_njets34_m1200_1718);
  TH1D* h_signal_njets56_m1200  = (TH1D*)h_signal_njets56_m1200_16->Clone("h_signal_njets56_m1200");
  h_signal_njets56_m1200->Add(h_signal_njets56_m1200_1718);
  TH1D* h_signal_njets7_m1200  = (TH1D*)h_signal_njets7_m1200_16->Clone("h_signal_njets7_m1200");
  h_signal_njets7_m1200->Add(h_signal_njets7_m1200_1718);
  TH1D* h_signal_njets34_m1800  = (TH1D*)h_signal_njets34_m1800_16->Clone("h_signal_njets34_m1800");
  h_signal_njets34_m1800->Add(h_signal_njets34_m1800_1718);
  TH1D* h_signal_njets56_m1800  = (TH1D*)h_signal_njets56_m1800_16->Clone("h_signal_njets56_m1800");
  h_signal_njets56_m1800->Add(h_signal_njets56_m1800_1718);
  TH1D* h_signal_njets7_m1800  = (TH1D*)h_signal_njets7_m1800_16->Clone("h_signal_njets7_m1800");
  h_signal_njets7_m1800->Add(h_signal_njets7_m1800_1718);

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

  cout << "[m1200]" << endl;
  cout << "    njet34" << endl;
  cout << "[1]: " << h_signal_njets34_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets34_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets34_m1200->GetBinContent(3) << endl;
  cout << "njet56" << endl;
  cout << "[1]: " << h_signal_njets56_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets56_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets56_m1200->GetBinContent(3) << endl;
  cout << "njet7" << endl;
  cout << "[1]: " << h_signal_njets7_m1200->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets7_m1200->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets7_m1200->GetBinContent(3) << endl;
  cout << endl;
  cout << "[m1800]" << endl;
  cout << "    njet34" << endl;
  cout << "[1]: " << h_signal_njets34_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets34_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets34_m1800->GetBinContent(3) << endl;
  cout << "njet56" << endl;
  cout << "[1]: " << h_signal_njets56_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets56_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets56_m1800->GetBinContent(3) << endl;
  cout << "njet7" << endl;
  cout << "[1]: " << h_signal_njets7_m1800->GetBinContent(1) << endl;
  cout << "[2]: " << h_signal_njets7_m1800->GetBinContent(2) << endl;
  cout << "[3]: " << h_signal_njets7_m1800->GetBinContent(3) << endl;

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
  h_data_njets34_clone_test->Add(h_other_mc_njets34, -1);
  h_data_njets56_clone_test->Add(h_other_mc_njets56, -1);
  h_data_njets7_clone_test->Add(h_other_mc_njets7, -1);
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
  h_data_njets34->SetMarkerStyle(20); h_data_njets34->SetMarkerSize(2);
  h_data_njets34->SetLineColor(kBlack); h_dy_njets34->SetLineColor(kBlack); h_qcd_njets34->SetLineColor(kBlack); h_ttbar_njets34->SetLineColor(kBlack); h_wjets_njets34->SetLineColor(kBlack); h_other_njets34->SetLineColor(kBlack);
  h_dy_njets34->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets34->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets34->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets34->SetFillColor(TColor::GetColor("#832db6")); h_other_njets34->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets34->SetLineWidth(2); h_dy_njets34->SetLineWidth(1); h_qcd_njets34->SetLineWidth(1); h_ttbar_njets34->SetLineWidth(1); h_wjets_njets34->SetLineWidth(1); h_other_njets34->SetLineWidth(1);
  h_data_njets34->SetTitle("");
  h_data_njets34->GetXaxis()->SetLabelOffset(1);
  h_data_njets34->GetYaxis()->SetLabelSize(0.07); h_data_njets34->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets34->GetYaxis()->SetTitleOffset(0.92); h_data_njets34->GetYaxis()->SetTitleSize(0.08);
  h_data_njets34->SetMinimum(0.002); h_data_njets34->SetMaximum(h_data_njets34->GetBinContent(1)*1000000);
  h_data_njets34_clone->SetTitle("");
  h_data_njets34_clone->GetXaxis()->SetNdivisions(505); h_data_njets34_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets34_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets34_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets34_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets34_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets34_clone->GetYaxis()->SetNdivisions(505); h_data_njets34_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets34_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets34_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets34_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets34_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets34_clone->GetXaxis()->SetLabelSize(0);
    // njets 5-6
  h_data_njets56->SetMarkerStyle(20); h_data_njets56->SetMarkerSize(2);
  h_data_njets56->SetLineColor(kBlack); h_dy_njets56->SetLineColor(kBlack); h_qcd_njets56->SetLineColor(kBlack); h_ttbar_njets56->SetLineColor(kBlack); h_wjets_njets56->SetLineColor(kBlack); h_other_njets56->SetLineColor(kBlack);
  h_dy_njets56->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets56->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets56->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets56->SetFillColor(TColor::GetColor("#832db6")); h_other_njets56->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets56->SetLineWidth(2); h_dy_njets56->SetLineWidth(1); h_qcd_njets56->SetLineWidth(1); h_ttbar_njets56->SetLineWidth(1); h_wjets_njets56->SetLineWidth(1); h_other_njets56->SetLineWidth(1);
  h_data_njets56->SetTitle("");
  h_data_njets56->GetXaxis()->SetLabelOffset(1);
  h_data_njets56->GetYaxis()->SetLabelSize(0.07); h_data_njets56->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets56->GetYaxis()->SetTitleOffset(0.92); h_data_njets56->GetYaxis()->SetTitleSize(0.08);
  h_data_njets56->SetMinimum(0.002); h_data_njets56->SetMaximum(h_data_njets56->GetBinContent(1)*1000000);
  h_data_njets56_clone->SetTitle("");
  h_data_njets56_clone->GetXaxis()->SetNdivisions(505); h_data_njets56_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets56_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets56_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets56_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets56_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets56_clone->GetYaxis()->SetNdivisions(505); h_data_njets56_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets56_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets56_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets56_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets56_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets56_clone->GetXaxis()->SetLabelSize(0);
    // njets 7-
  h_data_njets7->SetMarkerStyle(20); h_data_njets7->SetMarkerSize(2);
  h_data_njets7->SetLineColor(kBlack); h_dy_njets7->SetLineColor(kBlack); h_qcd_njets7->SetLineColor(kBlack); h_ttbar_njets7->SetLineColor(kBlack); h_wjets_njets7->SetLineColor(kBlack); h_other_njets7->SetLineColor(kBlack);
  h_data_njets7->SetLineWidth(2); h_dy_njets7->SetLineWidth(1); h_qcd_njets7->SetLineWidth(1); h_ttbar_njets7->SetLineWidth(1); h_wjets_njets7->SetLineWidth(1); h_other_njets7->SetLineWidth(1);
  h_dy_njets7->SetFillColor(TColor::GetColor("#e76300")); h_qcd_njets7->SetFillColor(TColor::GetColor("#ffa90e")); h_ttbar_njets7->SetFillColor(TColor::GetColor("#3f90da")); h_wjets_njets7->SetFillColor(TColor::GetColor("#832db6")); h_other_njets7->SetFillColor(TColor::GetColor("#94a4a2"));
  h_data_njets7->SetTitle("");
  h_data_njets7->GetXaxis()->SetLabelOffset(1);
  h_data_njets7->GetYaxis()->SetLabelSize(0.07); h_data_njets7->GetYaxis()->SetTitle("Events / (300 GeV)"); h_data_njets7->GetYaxis()->SetTitleOffset(0.92); h_data_njets7->GetYaxis()->SetTitleSize(0.08);
  h_data_njets7->SetMinimum(0.002); h_data_njets7->SetMaximum(h_data_njets7->GetBinContent(1)*1000000);
  h_data_njets7_clone->SetTitle("");
  h_data_njets7_clone->GetXaxis()->SetNdivisions(505); h_data_njets7_clone->GetXaxis()->SetLabelSize(0.12); h_data_njets7_clone->GetXaxis()->SetLabelOffset(0.025); h_data_njets7_clone->GetXaxis()->SetTitle("M_{J} [GeV]"); h_data_njets7_clone->GetXaxis()->SetTitleOffset(0.95); h_data_njets7_clone->GetXaxis()->SetTitleSize(0.19);
  h_data_njets7_clone->GetYaxis()->SetNdivisions(505); h_data_njets7_clone->GetYaxis()->SetLabelSize(0.15); h_data_njets7_clone->GetYaxis()->SetTitle("Data / MC"); h_data_njets7_clone->GetYaxis()->SetTitleSize(0.18); h_data_njets7_clone->GetYaxis()->SetTitleOffset(0.41); h_data_njets7_clone->GetYaxis()->SetLabelOffset(0.015);
  h_data_njets7_clone->GetXaxis()->SetLabelSize(0);

  h_signal_njets34_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1200->SetLineWidth(4); h_signal_njets34_m1200->SetLineStyle(2);
  h_signal_njets56_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1200->SetLineWidth(4); h_signal_njets56_m1200->SetLineStyle(2);
  h_signal_njets7_m1200->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1200->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1200->SetLineWidth(4); h_signal_njets7_m1200->SetLineStyle(2);
  h_signal_njets34_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets34_m1800->SetLineWidth(4); h_signal_njets34_m1800->SetLineStyle(1);
  h_signal_njets56_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets56_m1800->SetLineWidth(4); h_signal_njets56_m1800->SetLineStyle(1);
  h_signal_njets7_m1800->SetLineColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1800->SetFillColor(TColor::GetColor("#bd1f01")); h_signal_njets7_m1800->SetLineWidth(4); h_signal_njets7_m1800->SetLineStyle(1);

  // Make TLatex
  TLatex* tex_lumi = tex_lumi = new TLatex(0.89, 0.95, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  tex_lumi->SetTextSize(0.07);
  //TLatex *TexCMS = new TLatex(0.15,0.925,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.15,0.925,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.07);
  TexCMS->SetLineWidth(2);

  TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
  TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
  TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
  TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
  tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
  tex_mj500->SetTextSize(0.15); tex_mj800->SetTextSize(0.15); tex_mj1100->SetTextSize(0.15); tex_mj1400->SetTextSize(0.15);
  tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

  TLatex* tex_Nlep2   = new TLatex(0.19, 0.81, "N_{lep} = 2 (OSSF)");
  TLatex* tex_mll     = new TLatex(0.19, 0.715, "81 < m_{ll} < 101 GeV");
  TLatex* tex_Njets34 = new TLatex(0.19, 0.62, "3 #leq N_{jet} #leq 4");
  TLatex* tex_Njets56 = new TLatex(0.19, 0.62, "5 #leq N_{jet} #leq 6");
  TLatex* tex_Njets7  = new TLatex(0.19, 0.62, "N_{jet} #geq 7");
  TLatex* tex_Nb2     = new TLatex(0.19, 0.525, "N_{b} #leq 2");
  tex_Nlep2->SetNDC();   tex_Nlep2->SetTextFont(42);   tex_Nlep2->SetTextSize(0.055);
  tex_mll->SetNDC();     tex_mll->SetTextFont(42);     tex_mll->SetTextSize(0.055);
  tex_Njets34->SetNDC(); tex_Njets34->SetTextFont(42); tex_Njets34->SetTextSize(0.055);
  tex_Njets56->SetNDC(); tex_Njets56->SetTextFont(42); tex_Njets56->SetTextSize(0.055);
  tex_Njets7->SetNDC();  tex_Njets7->SetTextFont(42);  tex_Njets7->SetTextSize(0.055);
  tex_Nb2->SetNDC();     tex_Nb2->SetTextFont(42);     tex_Nb2->SetTextSize(0.055);

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
  TLegend* l_njets34_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets34_2->SetTextSize(0.05);
  l_njets34_2->SetBorderSize(0);
  l_njets34_2->SetFillStyle(0);
  l_njets34_2->AddEntry(h_data_njets34,  "data", "elp");
  l_njets34_2->AddEntry(h_dy_njets34,    "Drell-Yan", "f");
  l_njets34_2->AddEntry(h_qcd_njets34,   "QCD", "f");
  l_njets34_2->AddEntry(h_ttbar_njets34, "t#bar{t}", "f");
  l_njets34_2->AddEntry(h_wjets_njets34, "W+jets", "f");
  l_njets34_2->AddEntry(h_other_njets34, "Other", "f");
  l_njets34_2->AddEntry(h_signal_njets34_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets34_2->AddEntry(h_signal_njets34_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 5-6
  TLegend* l_njets56_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets56_2->SetTextSize(0.05);
  l_njets56_2->SetBorderSize(0);
  l_njets56_2->SetFillStyle(0);
  l_njets56_2->AddEntry(h_data_njets56,  "data", "elp");
  l_njets56_2->AddEntry(h_dy_njets56,    "Drell-Yan", "f");
  l_njets56_2->AddEntry(h_qcd_njets56,   "QCD", "f");
  l_njets56_2->AddEntry(h_ttbar_njets56, "t#bar{t}", "f");
  l_njets56_2->AddEntry(h_wjets_njets56, "W+jets", "f");
  l_njets56_2->AddEntry(h_other_njets56, "Other", "f");
  l_njets56_2->AddEntry(h_signal_njets56_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets56_2->AddEntry(h_signal_njets56_m1800, "m_{#tilde{g}}=1800 GeV", "l");

    // njets 7
  TLegend* l_njets7_2 = new TLegend(0.49, 0.43, 0.85, 0.87);
  l_njets7_2->SetTextSize(0.05);
  l_njets7_2->SetBorderSize(0);
  l_njets7_2->SetFillStyle(0);
  l_njets7_2->AddEntry(h_data_njets7,  "data", "elp");
  l_njets7_2->AddEntry(h_dy_njets7,    "Drell-Yan", "f");
  l_njets7_2->AddEntry(h_qcd_njets7,   "QCD", "f");
  l_njets7_2->AddEntry(h_ttbar_njets7, "t#bar{t}", "f");
  l_njets7_2->AddEntry(h_wjets_njets7, "W+jets", "f");
  l_njets7_2->AddEntry(h_other_njets7, "Other", "f");
  l_njets7_2->AddEntry(h_signal_njets7_m1200, "m_{#tilde{g}}=1200 GeV#times0.01", "l");
  l_njets7_2->AddEntry(h_signal_njets7_m1800, "m_{#tilde{g}}=1800 GeV", "l");
  
  // Draw plots
  TLine *line;
  line = new TLine(500, 1., 1400, 1.);

    // njets 4-5
  TPad *tpad_njets34(NULL), *bpad_njets34(NULL);
      // tpad
  TCanvas* c_njets34 = new TCanvas("c_njets34", "c_njets34", 800, 800);
  c_njets34->cd();
  tpad_njets34 = new TPad("tpad_njets34","tpad_njets34",0.,0.3,1.,1.);
  tpad_njets34->SetLeftMargin(0.15); tpad_njets34->SetBottomMargin(0.02); tpad_njets34->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets34->Draw();
  tpad_njets34->cd();
  gPad->SetLogy();
  h_data_njets34->Draw("EP");
  st_mc_njets34->Draw("same hist");
  h_data_njets34->Draw("same EP");
  h_signal_njets34_m1200->SetFillStyle(0);
  h_signal_njets34_m1200->Draw("same hist");
  h_signal_njets34_m1800->SetFillStyle(0);
  h_signal_njets34_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets34_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets34->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets34->cd();
  bpad_njets34 = new TPad("bpad_njets34","bpad_njets34",0.,0.,1.,0.305);
  bpad_njets34->SetLeftMargin(0.15);
  bpad_njets34->SetTopMargin(0.); bpad_njets34->SetBottomMargin(0.4); bpad_njets34->SetFillStyle(4000);
  bpad_njets34->Draw(); bpad_njets34->cd();

  TH1D* h_data_njets34_err = (TH1D*)h_data_njets34->Clone("h_data_njets34_err");
  h_data_njets34_err->SetMarkerSize(0);
  h_data_njets34_err->SetFillColor(kBlack);
  h_data_njets34_err->SetLineColor(kBlack);
  h_data_njets34_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets34_err->SetBinContent(imj, h_data_njets34->GetBinContent(imj)/h_tot_mc_njets34->GetBinContent(imj));
    h_data_njets34_err->SetBinError(imj, (h_data_njets34->GetBinContent(imj)/h_tot_mc_njets34->GetBinContent(imj))*(h_tot_mc_njets34->GetBinError(imj)/h_tot_mc_njets34->GetBinContent(imj)));
  }

  h_data_njets34_clone->Divide(h_tot_mc_njets34);
  h_data_njets34_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets34_clone->SetLineColor(kBlack);
  h_data_njets34_clone->SetLineWidth(2);
  h_data_njets34_clone->SetMarkerStyle(20);
  h_data_njets34_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets34_clone->SetBinError(imj, h_data_njets34_clone->GetBinContent(imj)*(h_data_njets34->GetBinError(imj)/h_data_njets34->GetBinContent(imj)));
  }
  h_data_njets34_clone->Draw("ep");
  h_data_njets34_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets34->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets34_lumi%s.pdf", lumi_title.Data()));

    // njets 5-6
  TPad *tpad_njets56(NULL), *bpad_njets56(NULL);
      // tpad
  TCanvas* c_njets56 = new TCanvas("c_njets56", "c_njets56", 800, 800);
  c_njets56->cd();
  tpad_njets56 = new TPad("tpad_njets56","tpad_njets56",0.,0.3,1.,1.);
  tpad_njets56->SetLeftMargin(0.15); tpad_njets56->SetBottomMargin(0.02); tpad_njets56->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets56->Draw();
  tpad_njets56->cd();
  gPad->SetLogy();
  h_data_njets56->Draw("EP");
  st_mc_njets56->Draw("same hist");
  h_data_njets56->Draw("same EP");
  h_signal_njets56_m1200->SetFillStyle(0);
  h_signal_njets56_m1200->Draw("same hist");
  h_signal_njets56_m1800->SetFillStyle(0);
  h_signal_njets56_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets56_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets56->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets56->cd();
  bpad_njets56 = new TPad("bpad_njets56","bpad_njets56",0.,0.,1.,0.305);
  bpad_njets56->SetLeftMargin(0.15);
  bpad_njets56->SetTopMargin(0.); bpad_njets56->SetBottomMargin(0.4); bpad_njets56->SetFillStyle(4000);
  bpad_njets56->Draw(); bpad_njets56->cd();

  TH1D* h_data_njets56_err = (TH1D*)h_data_njets56->Clone("h_data_njets56_err");
  h_data_njets56_err->SetMarkerSize(0);
  h_data_njets56_err->SetFillColor(kBlack);
  h_data_njets56_err->SetLineColor(kBlack);
  h_data_njets56_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets56_err->SetBinContent(imj, h_data_njets56->GetBinContent(imj)/h_tot_mc_njets56->GetBinContent(imj));
    h_data_njets56_err->SetBinError(imj, (h_data_njets56->GetBinContent(imj)/h_tot_mc_njets56->GetBinContent(imj))*(h_tot_mc_njets56->GetBinError(imj)/h_tot_mc_njets56->GetBinContent(imj)));
  }

  h_data_njets56_clone->Divide(h_tot_mc_njets56);
  h_data_njets56_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets56_clone->SetLineColor(kBlack);
  h_data_njets56_clone->SetLineWidth(2);
  h_data_njets56_clone->SetMarkerStyle(20);
  h_data_njets56_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets56_clone->SetBinError(imj, h_data_njets56_clone->GetBinContent(imj)*(h_data_njets56->GetBinError(imj)/h_data_njets56->GetBinContent(imj)));
  }
  h_data_njets56_clone->Draw("ep");
  h_data_njets56_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets56->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets56_lumi%s.pdf", lumi_title.Data()));

    // njets 7-
  TPad *tpad_njets7(NULL), *bpad_njets7(NULL);
      // tpad
  TCanvas* c_njets7 = new TCanvas("c_njets7", "c_njets7", 800, 800);
  c_njets7->cd();
  tpad_njets7 = new TPad("tpad_njets7","tpad_njets7",0.,0.3,1.,1.);
  tpad_njets7->SetLeftMargin(0.15); tpad_njets7->SetBottomMargin(0.02); tpad_njets7->SetTopMargin(style.PadTopMargin+0.01);
  tpad_njets7->Draw();
  tpad_njets7->cd();
  gPad->SetLogy();
  h_data_njets7->Draw("EP");
  st_mc_njets7->Draw("same hist");
  h_data_njets7->Draw("same EP");
  h_signal_njets7_m1200->SetFillStyle(0);
  h_signal_njets7_m1200->Draw("same hist");
  h_signal_njets7_m1800->SetFillStyle(0);
  h_signal_njets7_m1800->Draw("same hist");
  gPad->RedrawAxis();
  l_njets7_2->Draw();
  tex_lumi->Draw();
  TexCMS->Draw();
  tex_Nlep2->Draw();
  tex_mll->Draw();
  tex_Njets7->Draw();
  tex_Nb2->Draw();
      // bpad
  c_njets7->cd();
  bpad_njets7 = new TPad("bpad_njets7","bpad_njets7",0.,0.,1.,0.305);
  bpad_njets7->SetLeftMargin(0.15);
  bpad_njets7->SetTopMargin(0.); bpad_njets7->SetBottomMargin(0.4); bpad_njets7->SetFillStyle(4000);
  bpad_njets7->Draw(); bpad_njets7->cd();

  TH1D* h_data_njets7_err = (TH1D*)h_data_njets7->Clone("h_data_njets7_err");
  h_data_njets7_err->SetMarkerSize(0);
  h_data_njets7_err->SetFillColor(kBlack);
  h_data_njets7_err->SetLineColor(kBlack);
  h_data_njets7_err->SetFillStyle(3354);
  for(int imj=1; imj<4; imj++) {
    h_data_njets7_err->SetBinContent(imj, h_data_njets7->GetBinContent(imj)/h_tot_mc_njets7->GetBinContent(imj));
    h_data_njets7_err->SetBinError(imj, (h_data_njets7->GetBinContent(imj)/h_tot_mc_njets7->GetBinContent(imj))*(h_tot_mc_njets7->GetBinError(imj)/h_tot_mc_njets7->GetBinContent(imj)));
  }

  h_data_njets7_clone->Divide(h_tot_mc_njets7);
  h_data_njets7_clone->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_data_njets7_clone->SetLineColor(kBlack);
  h_data_njets7_clone->SetLineWidth(2);
  h_data_njets7_clone->SetMarkerStyle(20);
  h_data_njets7_clone->SetMarkerSize(2);
  for(int imj=1; imj<4; imj++) {
    h_data_njets7_clone->SetBinError(imj, h_data_njets7_clone->GetBinContent(imj)*(h_data_njets7->GetBinError(imj)/h_data_njets7->GetBinContent(imj)));
  }
  h_data_njets7_clone->Draw("ep");
  h_data_njets7_err->Draw("e2 same");
  tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);
  line->Draw("same");
  c_njets7->Print(Form("plots/wjets_kappa/wjets_kappa_dy_njets7_lumi%s.pdf", lumi_title.Data()));


}



void kappa_summary_plot_combine() {
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  float lumi=138, lumi_16=36.3, lumi_1718=101.3;

  TFile* f_kappa_16   = new TFile("data/result_kappa_UL2016.root", "READ");
  TFile* f_kappa_1718 = new TFile("data/result_kappa_UL20178.root", "READ");

  TH1F *hist_kappa1_16, *hist_kappa2_16, *hist_kappa1_1718, *hist_kappa2_1718;
  hist_kappa1_16 = static_cast<TH1F*>(f_kappa_16->Get("hist_kappa1"));
  hist_kappa2_16 = static_cast<TH1F*>(f_kappa_16->Get("hist_kappa2"));
  hist_kappa1_1718 = static_cast<TH1F*>(f_kappa_1718->Get("hist_kappa1"));
  hist_kappa2_1718 = static_cast<TH1F*>(f_kappa_1718->Get("hist_kappa2"));

  TH1F* hist_kappa1 = new TH1F("hist_kappa1", "hist_kappa1", 9, 0, 9);
  TH1F* hist_kappa2 = new TH1F("hist_kappa2", "hist_kappa2", 9, 0, 9);

  for(int i=1; i<10; i++) {
    hist_kappa1->SetBinContent(i, (lumi_16*hist_kappa1_16->GetBinContent(i)+lumi_1718*hist_kappa1_1718->GetBinContent(i))/(lumi_16+lumi_1718));
    hist_kappa1->SetBinError(i, (1./137.6)*TMath::Sqrt(((36.3*hist_kappa1_16->GetBinError(i))*(36.3*hist_kappa1_16->GetBinError(i)) + (101.3*hist_kappa1_1718->GetBinError(i))*(101.3*hist_kappa1_1718->GetBinError(i)))));
    hist_kappa2->SetBinContent(i, (lumi_16*hist_kappa2_16->GetBinContent(i)+lumi_1718*hist_kappa2_1718->GetBinContent(i))/(lumi_16+lumi_1718));
    hist_kappa2->SetBinError(i, (1./137.6)*TMath::Sqrt(((36.3*hist_kappa2_16->GetBinError(i))*(36.3*hist_kappa2_16->GetBinError(i)) + (101.3*hist_kappa2_1718->GetBinError(i))*(101.3*hist_kappa2_1718->GetBinError(i)))));
  }


  cout << "kappa 1" << endl;
  cout << "   [QCD]" << endl;
  cout << "   Low :" << hist_kappa1->GetBinContent(1) << " +- " << std::max(hist_kappa1->GetBinError(1), 1-hist_kappa1->GetBinContent(1)) << endl;
  cout << "   Mid :" << hist_kappa1->GetBinContent(2) << " +- " << std::max(hist_kappa1->GetBinError(2), 1-hist_kappa1->GetBinContent(2)) << endl;
  cout << "   High:" << hist_kappa1->GetBinContent(3) << " +- " << std::max(hist_kappa1->GetBinError(3), 1-hist_kappa1->GetBinContent(3)) << endl;
  cout << "   [W+jets]" << endl;
  cout << "   Low :" << hist_kappa1->GetBinContent(4) << " +- " << std::max(hist_kappa1->GetBinError(4), 1-hist_kappa1->GetBinContent(4)) << endl;
  cout << "   Mid :" << hist_kappa1->GetBinContent(5) << " +- " << std::max(hist_kappa1->GetBinError(5), 1-hist_kappa1->GetBinContent(5)) << endl;
  cout << "   High:" << hist_kappa1->GetBinContent(6) << " +- " << std::max(hist_kappa1->GetBinError(6), 1-hist_kappa1->GetBinContent(6)) << endl;
  cout << "   [ttbar]" << endl;
  cout << "   Low :" << hist_kappa1->GetBinContent(7) << " +- " << std::max(hist_kappa1->GetBinError(7), 1-hist_kappa1->GetBinContent(7)) << endl;
  cout << "   Mid :" << hist_kappa1->GetBinContent(8) << " +- " << std::max(hist_kappa1->GetBinError(8), 1-hist_kappa1->GetBinContent(8)) << endl;
  cout << "   High:" << hist_kappa1->GetBinContent(9) << " +- " << std::max(hist_kappa1->GetBinError(9), 1-hist_kappa1->GetBinContent(9)) << endl;
  cout << "kappa 2" << endl;
  cout << "   [QCD]" << endl;
  cout << "   Low :" << hist_kappa2->GetBinContent(1) << " +- " << std::max(hist_kappa2->GetBinError(1), 1-hist_kappa2->GetBinContent(1)) << endl;
  cout << "   Mid :" << hist_kappa2->GetBinContent(2) << " +- " << std::max(hist_kappa2->GetBinError(2), 1-hist_kappa2->GetBinContent(2)) << endl;
  cout << "   High:" << hist_kappa2->GetBinContent(3) << " +- " << std::max(hist_kappa2->GetBinError(3), 1-hist_kappa2->GetBinContent(3)) << endl;
  cout << "   [W+jets]" << endl;
  cout << "   Low :" << hist_kappa2->GetBinContent(4) << " +- " << std::max(hist_kappa2->GetBinError(4), 1-hist_kappa2->GetBinContent(4)) << endl;
  cout << "   Mid :" << hist_kappa2->GetBinContent(5) << " +- " << std::max(hist_kappa2->GetBinError(5), 1-hist_kappa2->GetBinContent(5)) << endl;
  cout << "   High:" << hist_kappa2->GetBinContent(6) << " +- " << std::max(hist_kappa2->GetBinError(6), 1-hist_kappa2->GetBinContent(6)) << endl;
  cout << "   [ttbar]" << endl;
  cout << "   Low :" << hist_kappa2->GetBinContent(7) << " +- " << std::max(hist_kappa2->GetBinError(7), 1-hist_kappa2->GetBinContent(7)) << endl;
  cout << "   Mid :" << hist_kappa2->GetBinContent(8) << " +- " << std::max(hist_kappa2->GetBinError(8), 1-hist_kappa2->GetBinContent(8)) << endl;
  cout << "   High:" << hist_kappa2->GetBinContent(9) << " +- " << std::max(hist_kappa2->GetBinError(9), 1-hist_kappa2->GetBinContent(9)) << endl;

  hist_kappa2->GetXaxis()->SetBinLabel(1, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(2, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(3, "High");
  hist_kappa2->GetXaxis()->SetBinLabel(4, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(5, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(6, "High");
  hist_kappa2->GetXaxis()->SetBinLabel(7, "Low");
  hist_kappa2->GetXaxis()->SetBinLabel(8, "Mid");
  hist_kappa2->GetXaxis()->SetBinLabel(9, "High");
  //hist_kappa2->GetXaxis()->SetBinLabel(9, "#splitline{High}{   N_{jet}}");
  hist_kappa2->GetXaxis()->LabelsOption("h");

  hist_kappa1->SetTitle("");
  hist_kappa2->SetTitle("");
  hist_kappa1->GetYaxis()->SetRangeUser(0.,2.99);
  hist_kappa2->GetYaxis()->SetRangeUser(0.,2.99);
  hist_kappa1->SetMinimum(0.001);
  hist_kappa2->GetXaxis()->SetLabelSize(0.09);
  hist_kappa2->GetXaxis()->SetLabelOffset(0.01);
  //hist_kappa2->GetXaxis()->SetTitle("N_{jet}");
  //hist_kappa2->GetXaxis()->SetTitleOffset(1.5);
  hist_kappa1->GetYaxis()->SetLabelSize(0.075);
  hist_kappa2->GetYaxis()->SetLabelSize(0.07);
//  hist_kappa1->SetTitleSize(2);
//  hist_kappa2->SetTitle("#kappa_{2}");
//  hist_kappa2->SetTitleSize(0.9);
  TLatex* tex_lumi = new TLatex(0.92, 0.86, Form("%d fb^{-1} (13 TeV)", int(lumi)));
  tex_lumi->SetNDC();
  tex_lumi->SetTextAlign(32);
  tex_lumi->SetTextFont(42);
  //tex_lumi->SetTextSize(0.09);
  tex_lumi->SetTextSize(0.10);
  //TLatex *TexCMS = new TLatex(0.138,0.82,"CMS #font[52]{Preliminary}");
  TLatex *TexCMS = new TLatex(0.138,0.82,"CMS");
  TexCMS->SetNDC();
  //TexCMS->SetTextSize(0.10);
  TexCMS->SetTextSize(0.11);
  TexCMS->SetLineWidth(2);
  TLatex *TexTitle_kap1 = new TLatex(0.02,0.77,"#kappa_{1}");
  TexTitle_kap1->SetNDC();
  TexTitle_kap1->SetTextSize(0.13);
  TLatex *TexTitle_kap2 = new TLatex(0.02,0.93,"#kappa_{2}");
  TexTitle_kap2->SetNDC();
  TexTitle_kap2->SetTextSize(0.12);

  // Tex QCD, ttbar, and wjets
  TLatex *Tex_QCD = new TLatex(0.215,0.03,"QCD");
  Tex_QCD->SetNDC();
  Tex_QCD->SetTextFont(42);
  Tex_QCD->SetTextSize(0.11);
  TLatex *Tex_wjets = new TLatex(0.45,0.03,"W+jets");
  Tex_wjets->SetNDC();
  Tex_wjets->SetTextFont(42);
  Tex_wjets->SetTextSize(0.11);
  TLatex *Tex_ttbar = new TLatex(0.785,0.03,"t#bar{t}");
  Tex_ttbar->SetNDC();
  Tex_ttbar->SetTextFont(42);
  Tex_ttbar->SetTextSize(0.11);
  TLatex *Tex_Njet = new TLatex(0.935,0.20,"N_{jet}");
  Tex_Njet->SetNDC();
  Tex_Njet->SetTextFont(42);
  Tex_Njet->SetTextSize(0.09);

  // Tex (4-5), (6-7) and (\\geq8)
  TLatex *Tex_45_1 = new TLatex(0.152,0.165,"(4-5)");
  Tex_45_1->SetNDC();
  Tex_45_1->SetTextFont(42);
  Tex_45_1->SetTextSize(0.06);
  TLatex *Tex_67_1 = new TLatex(0.242,0.165,"(6-7)");
  Tex_67_1->SetNDC();
  Tex_67_1->SetTextFont(42);
  Tex_67_1->SetTextSize(0.06);
  TLatex *Tex_8_1 = new TLatex(0.332,0.165,"(\\geq8)");
  Tex_8_1->SetNDC();
  Tex_8_1->SetTextFont(42);
  Tex_8_1->SetTextSize(0.06);
  TLatex *Tex_45_2 = new TLatex(0.415,0.165,"(4-5)");
  Tex_45_2->SetNDC();
  Tex_45_2->SetTextFont(42);
  Tex_45_2->SetTextSize(0.06);
  TLatex *Tex_67_2 = new TLatex(0.505,0.165,"(6-7)");
  Tex_67_2->SetNDC();
  Tex_67_2->SetTextFont(42);
  Tex_67_2->SetTextSize(0.06);
  TLatex *Tex_8_2 = new TLatex(0.595,0.165,"(\\geq8)");
  Tex_8_2->SetNDC();
  Tex_8_2->SetTextFont(42);
  Tex_8_2->SetTextSize(0.06);
  TLatex *Tex_45_3 = new TLatex(0.678,0.165,"(4-5)");
  Tex_45_3->SetNDC();
  Tex_45_3->SetTextFont(42);
  Tex_45_3->SetTextSize(0.06);
  TLatex *Tex_67_3 = new TLatex(0.768,0.165,"(6-7)");
  Tex_67_3->SetNDC();
  Tex_67_3->SetTextFont(42);
  Tex_67_3->SetTextSize(0.06);
  TLatex *Tex_8_3 = new TLatex(0.858,0.165,"(\\geq8)");
  Tex_8_3->SetNDC();
  Tex_8_3->SetTextFont(42);
  Tex_8_3->SetTextSize(0.06);

  TLine *line;
  line = new TLine(0, 1., 8.99, 1.);
  line->SetLineColor(kBlack); line->SetLineWidth(1); line->SetLineStyle(2);

  TCanvas *c = new TCanvas("c","c",1600,1600);
  c->Divide(1,2,0.01,0);
  // To avoid overlapping with the y-axis label ("0" of the kappa1 plot), cd(2) is drawn first
  c->cd(2);
  TBox *b4 = new TBox(0.,0., 3., 2.99*c->GetUymax());
  b4->SetFillColorAlpha(TColor::GetColor("#ffa90e"), 0.85);
  TBox *b5 = new TBox(3.,0., 6., 2.99*c->GetUymax());
  b5->SetFillColorAlpha(TColor::GetColor("#832db6"), 0.85);
  TBox *b6 = new TBox(6.,0., 8.99, 2.99*c->GetUymax());
  b6->SetFillColorAlpha(TColor::GetColor("#3f90da"), 0.85);
  hist_kappa2->Draw("ex0");
  TGaxis *ax2 = static_cast<TGaxis*>(hist_kappa2->GetXaxis()->Clone());
  TGaxis *ay2 = static_cast<TGaxis*>(hist_kappa2->GetYaxis()->Clone());
  b4->Draw("same");
  b5->Draw("same");
  b6->Draw("same");
  hist_kappa2->SetFillStyle(3254);
  hist_kappa2->SetMarkerStyle(8);
  hist_kappa2->SetLineColor(kBlack);
  hist_kappa2->SetLineWidth(2);
  hist_kappa2->SetMarkerSize(3);
  hist_kappa2->Draw("same ex0");
  ax2->Draw("same");
  TexTitle_kap2->Draw();
  Tex_QCD->Draw();
  Tex_wjets->Draw();
  Tex_ttbar->Draw();
  Tex_45_1->Draw();
  Tex_67_1->Draw();
  Tex_8_1->Draw();
  Tex_45_2->Draw();
  Tex_67_2->Draw();
  Tex_8_2->Draw();
  Tex_45_3->Draw();
  Tex_67_3->Draw();
  Tex_8_3->Draw();
  Tex_Njet->Draw();
  ay2->Draw("same");
  line->Draw("same");
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.07);
  gPad->SetBottomMargin(0.30);
  c->cd(2)->RedrawAxis();
  c->cd(2)->Modified();
  c->cd(2)->Update();

  c->cd(1);
  TBox *b1 = new TBox(0.,0., 3., 2.98*c->GetUymax());
  b1->SetFillColorAlpha(TColor::GetColor("#ffa90e"), 0.85);
  TBox *b2 = new TBox(3.,0., 6., 2.98*c->GetUymax());
  b2->SetFillColorAlpha(TColor::GetColor("#832db6"), 0.85);
  TBox *b3 = new TBox(6.,0., 8.99, 2.99*c->GetUymax());
  b3->SetFillColorAlpha(TColor::GetColor("#3f90da"), 0.85);
  hist_kappa1->Draw("ex0");
  TGaxis *ax1 = static_cast<TGaxis*>(hist_kappa1->GetXaxis()->Clone());
  TGaxis *ay1 = static_cast<TGaxis*>(hist_kappa1->GetYaxis()->Clone());
  b1->Draw("same");
  b2->Draw("same");
  b3->Draw("same");
  hist_kappa1->SetFillStyle(3254);
  hist_kappa1->SetMarkerStyle(20);
  hist_kappa1->SetMarkerSize(3);
  hist_kappa1->SetLineColor(kBlack);
  hist_kappa1->SetLineWidth(2);
  hist_kappa1->Draw("same ex0");
  ax1->Draw("same");
  ay1->Draw("same");
  line->Draw("same");
  tex_lumi->Draw();
  TexCMS->Draw();
  TexTitle_kap1->Draw();
  gPad->SetLeftMargin(0.14);
  //gPad->SetTopMargin(0.16);
  gPad->SetTopMargin(0.21);
  gPad->SetRightMargin(0.07);
  c->cd(1)->RedrawAxis();
  c->cd(1)->Modified();
  c->cd(1)->Update();

  
  c->Print("kappa_result_UL201678.pdf");
}



int main(int argc, char **argv)
{
  TString year, proc;
  year  = argv[1];
  proc  = argv[2];
 
  if(proc=="qcd") qcd_kappa_plot(year); // Fig. 16
  else if(proc=="wjets") wjets_kappa_plot_dy_region(year); // Fig. 18
  else if(proc=="ttbar") ttbar_kappa_plot(year); // Fig. 19
  else if(proc=="summary") kappa_summary_plot(year);
  else if(proc=="qcd_combine") qcd_kappa_plot_combine();
  else if(proc=="wjets_combine") wjets_kappa_plot_dy_region_combine();
  else if(proc=="summary_combine") kappa_summary_plot_combine();


  return 0;
}
