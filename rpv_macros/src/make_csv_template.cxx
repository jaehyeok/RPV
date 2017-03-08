B0;95;0c// make_csv_template.cxx: Makes templates of CSV template for jets passing
// the CSV requirement. Used for reweighting flavor composition of QCD MC

#include <iostream>
#include <vector>
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"
#include "TColor.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  const TString lumi = "36.8";
  const TString filename("csv_newmethod.root");
  const TString extraWeight("1");
  const TString extraCut("1");

  const int nBins=20;
  const float xMin=0.8484;
  const float xMax=1.0;
  const TString csvVar("jets_csv");
}

using namespace std;

void makeCSVHist(TFile *file, const vector<TString>& samples, const TString& name, const TString& extracut);

int main(){ 

  TString folder_dat = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/data/merged_rpvdata_rpvregion/";  
  //  TString folder_bkg = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/mc/merged_rpvmc_rpvregion/";
  TString folder_bkg = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/mc/merged_rpvmc_st1000/";

  vector<TString> s_data = getRPVProcess(folder_dat,"data");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  // The CSV reweighting only affects QCD; the flavor composition of other samples are well defined and does not need correction
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  // Add ttbar and wjets to other
  s_other.insert(s_other.end(),s_tt.begin(),s_tt.end());
  s_other.insert(s_other.end(),s_wjets.begin(),s_wjets.end());

  
  TFile *out = new TFile(filename, "recreate");
  //  TFile *out = new TFile("csv_newmethod_runGHsfGH.root", "recreate");

  // Njets<=7
  makeCSVHist(out, s_data, "data_low_njet", "njets<=7&&mj12>500&&nbm>=2&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_b_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_low_njet", "njets<=7&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  // Njets>=8
  makeCSVHist(out, s_data, "data_high_njet", "njets>=8&&mj12>500&&nbm>=2&&pass&&"+extraCut); 
  makeCSVHist(out, s_qcd, "QCD_b_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets>=8&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets>=8&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets>=8&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_high_njet", "njets>=8&&mj12>500&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  // 4<=Njets<=5 
  makeCSVHist(out, s_data, "data_45_njetbin", "mj12>500&&njets>=4&&njets<=5&&nbm>=2&&pass&&"+extraCut); 
  makeCSVHist(out, s_qcd, "QCD_b_45_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && mj12>500&&njets>=4&&njets<=5&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_45_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && mj12>500&&njets>=4&&njets<=5&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_45_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && mj12>500&&njets>=4&&njets<=5&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_45_njetbin", "mj12>500&&njets>=4&&njets<=5&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  // 6<=Njets<=7 
  makeCSVHist(out, s_data, "data_67_njetbin", "mj12>500&&njets>=6&&njets<=7&&nbm>=2&&pass&&"+extraCut); 
  makeCSVHist(out, s_qcd, "QCD_b_67_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && mj12>500&&njets>=6&&njets<=7&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_67_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && mj12>500&&njets>=6&&njets<=7&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_67_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && mj12>500&&njets>=6&&njets<=7&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_67_njetbin", "mj12>500&&njets>=6&&njets<=7&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  // 8<=Njets<=9
  makeCSVHist(out, s_data, "data_89_njetbin", "mj12>500&&njets>=8&&njets<=9&&nbm>=2&&pass&&"+extraCut); 
  makeCSVHist(out, s_qcd, "QCD_b_89_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && mj12>500&&njets>=8&&njets<=9&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_89_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && mj12>500&&njets>=8&&njets<=9&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_89_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && mj12>500&&njets>=8&&njets<=9&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_89_njetbin", "mj12>500&&njets>=8&&njets<=9&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  
  // njets>=10
  makeCSVHist(out, s_data, "data_10_njetbin", "mj12>500&&njets>=10&&nbm>=2&&pass&&"+extraCut); 
  makeCSVHist(out, s_qcd, "QCD_b_10_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && mj12>500&&njets>=10&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_10_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && mj12>500&&njets>=10&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_10_njetbin", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && mj12>500&&njets>=10&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_10_njetbin", "mj12>500&&njets>=10&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  
  // Njets<=7 && 300<MJ<500
  makeCSVHist(out, s_data, "data_low_njet_vlow_mj", "njets<=7 && mj12>300 && mj12<=500 && mj12<=800&&nbm>=2&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_b_low_njet_vlow_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7 && mj12>300 && mj12<=500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_low_njet_vlow_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7 && mj12>300 && mj12<=500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_low_njet_vlow_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7 && mj12>300 && mj12<=500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_low_njet_vlow_mj", "njets<=7 && mj12>300 && mj12<=500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  // Njets<=7 && 500<MJ<800
  makeCSVHist(out, s_data, "data_low_njet_low_mj", "njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_b_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_low_njet_low_mj", "njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  
  // Njets<=7 && MJ>800
  makeCSVHist(out, s_data, "data_low_njet_high_mj", "njets<=7 && mj12>800&&nbm>=2&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_b_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7 && mj12>800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_c_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7 && mj12>800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_qcd, "QCD_l_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7 && mj12>800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);
  makeCSVHist(out, s_other, "other_low_njet_high_mj", "njets<=7 && mj12>800&&nbm>=2&&stitch_ht&&pass&&"+extraCut);

  out->Close();
}

void makeCSVHist(TFile *file, const vector<TString>& samples, const TString& name, const TString& extracut)
{

  cout << "Making histograms " << name << " for cut " << extracut << endl;

  TChain *ch = new TChain("tree");
  for(auto isample : samples) {
    ch->Add(isample);
  }

  TString cut("nleps==0&&ht>1500&&njets>=4");
  TString weightandcut;
  if(extracut.Length()==0) {
    if(name.Contains("data")){
      weightandcut=Form("(%s)", cut.Data());
    }
    else{
      weightandcut=Form("%s*weight*%s*(%s)", lumi.Data(), extraWeight.Data(), cut.Data());
    }
  }
  else{
    if(name.Contains("data")){
      weightandcut=Form("(%s&&%s)", cut.Data(), extracut.Data());
    }
    else{
      weightandcut=Form("%s*weight*%s*(%s&&%s)", lumi.Data(), extraWeight.Data(), cut.Data(), extracut.Data());
    }
  }
  TString cutAndExtraCut(Form("(%s&&%s)", cut.Data(), extracut.Data()));

  // weighted histogram for convenient display
  TH1F *weightedHist = new TH1F(name, name, nBins, xMin, xMax);
  ch->Project(name, csvVar.Data(), weightandcut.Data());

  // raw number of MC counts
  TString rawHistName(Form("%s_raw", name.Data()));
  TH1F *rawHist = new TH1F(rawHistName, rawHistName, nBins, xMin, xMax);
  ch->Project(rawHistName, csvVar.Data(), cutAndExtraCut.Data());

  // weights need to be saved separately for proper application of Barlow-Beeston method
  TString weightHistName(Form("%s_weights", name.Data()));
  TH1F *weight = new TH1F(weightHistName, weightHistName, nBins, xMin, xMax);
  weight->Add(weightedHist);
  for(int i=1; i<=weight->GetNbinsX(); i++) {
    weight->SetBinContent(i, weightedHist->GetBinContent(i)/rawHist->GetBinContent(i));
    weight->SetBinError(i, weightedHist->GetBinError(i)/rawHist->GetBinContent(i));
  }

  file->cd();
  weightedHist->Write();
  weight->Write();
  rawHist->Write();
}
