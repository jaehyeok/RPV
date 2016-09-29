// make_csv_template.cxx: Makes templates of CSV template for jets passing
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
  const int nBins=20;
  const float xMin=0.80;
  const float xMax=1.0;
  const TString csvVar("jets_csv");
}

using namespace std;

void makeCSVHist(TFile *file, const vector<TString>& samples, const TString& name, const TString& extracut);

int main(){ 
  
  TString folder_bkg = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/mc/skim_rpv_st1200/";
  TString folder_dat = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/data/skim_rpv_st1200/";

  vector<TString> s_jetht = getRPVProcess(folder_dat,"data");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  // The CSV reweighting only affects QCD; the flavor composition of other samples well defined and does not need correction
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  // Add ttbar and wjets to other
  s_other.insert(s_other.end(),s_tt.begin(),s_tt.end());
  s_other.insert(s_other.end(),s_wjets.begin(),s_wjets.end());

  
  TFile *out = new TFile("csv_newmethod.root", "recreate");

  makeCSVHist(out, s_jetht, "data_low_njet", "(trig[11] || trig[12])&&njets<=7&&nbm>=2&&json12p9&&pass");
  makeCSVHist(out, s_qcd, "QCD_b_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_c_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1  && njets<=7&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_l_low_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_other, "other_low_njet", "njets<=7&&nbm>=2&&stitch&&pass");
  
  makeCSVHist(out, s_jetht, "data_high_njet", "(trig[11] || trig[12])&&njets>=8&&nbm>=2&&json12p9&&pass"); 
  makeCSVHist(out, s_qcd, "QCD_b_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets>=8&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_c_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets>=8&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_l_high_njet", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets>=8&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_other, "other_high_njet", "njets>=8&&nbm>=2&&stitch&&pass");
  
  makeCSVHist(out, s_jetht, "data_low_njet_low_mj", "(trig[11] || trig[12])&&njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&json12p9&&pass");
  makeCSVHist(out, s_qcd, "QCD_b_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_c_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_l_low_njet_low_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_other, "other_low_njet_low_mj", "njets<=7 && mj12>500 && mj12<=800&&nbm>=2&&stitch&&pass");
  
  makeCSVHist(out, s_jetht, "data_low_njet_high_mj", "(trig[11] || trig[12])&&njets<=7 && mj12>800&&nbm>=2&&json12p9&&pass");
  makeCSVHist(out, s_qcd, "QCD_b_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)>=1 && njets<=7 && mj12>800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_c_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)>=1 && njets<=7 && mj12>800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_qcd, "QCD_l_low_njet_high_mj", "Sum$(jets_pt>30&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_hflavor)==4)==0 && njets<=7 && mj12>800&&nbm>=2&&stitch&&pass");
  makeCSVHist(out, s_other, "other_low_njet_high_mj", "njets<=7 && mj12>800&&nbm>=2&&stitch&&pass"); 

  out->Close();
}

void makeCSVHist(TFile *file, const vector<TString>& samples, const TString& name, const TString& extracut)
{

  cout << "Making histograms " << name << " for cut " << extracut << endl;

  TChain *ch = new TChain("tree");
  for(auto isample : samples) {
    ch->Add(isample);
  }

  TString cut("nleps==0&&ht>1500&&njets>=6");
  TString weightandcut;
  if(extracut.Length()==0) {
    weightandcut=Form("%s*weight*(%s)", rpv::luminosity.Data(), cut.Data());
  }
  else weightandcut=Form("%s*weight*(%s&&%s)", rpv::luminosity.Data(), cut.Data(), extracut.Data());
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
