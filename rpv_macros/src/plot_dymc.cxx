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

  TString lumi = "36.3"; //FIXME
  TString trigger = "( trig_ht900 || trig_jet450)"; // PFHT800 OR PFHT900 OR PFJet450 */

  /*TString lumi = "41.5";
  TString trigger = "trig_ht1050";// */

  /*TString lumi = "59.8";
  TString trigger = "trig_ht1050";// */
  
  bool showData = true; // Draw with/wihout data
  bool unblindSRs = true; // Draw data in (unblind) SRs
  TString json = "1";

  bool makeNm1 = true; // Make only N=1 plots. Does not draw data
  
  TString plot_type=".pdf";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;

int main(){

  for(unsigned int iyear=2016; iyear<2019; iyear++)
  {
    TString year = Form("%d", iyear);
    cout << year << endl;

    if(year=="2017")
    {
      lumi = "41.5";
      trigger = "trig_ht1050";
    }
    if(year=="2018")
    {
      lumi = "59.8";
      trigger = "trig_ht1050";
    }

    // ntuple folders
    TString folder_bkg = "/mnt/data3/babies/210910/"+year+"/merged_norm_JER_0903/";
    TString folder_dat = "/mnt/data3/babies/210910/"+year+"/JetHTRun_rpvfitnbge0_step3/";
    TString folder_sig = "/mnt/data3/babies/210910/"+year+"/merged_norm_sig_pu/";
    TString folder_dy = "/mnt/data1/babies/20210702/"+year+"/merged_norm_njets3nleps2/";

    // Get file lists
    vector<TString> s_data = getRPVProcess(folder_dat,"data");
    vector<TString> s_rpv_m1600 = getRPVProcess(folder_sig,"rpv_m1600");
    vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

    vector<TString> s_wjets   = getRPVProcess(folder_bkg,"wjets");
    vector<TString> s_dy      = getRPVProcess(folder_dy,"DY");

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
    Samples.push_back(sfeats(s_wjets, "W+jets", rpv::c_wjets, 1, cutandweight("pass*(nleps==1&&njets>=4&&njets<=5)",extraweight)));
    Samples.push_back(sfeats(s_dy, "DY", rpv::c_other, 1, cutandweight("pass*(nleps==2&&njets>=3&&njets<=4)",extraweight)));

    Samples.push_back(sfeats(s_wjets, "W+jets", rpv::c_wjets, 1, cutandweight("pass*(nleps==1&&njets>=6&&njets<=7)",extraweight)));
    Samples.push_back(sfeats(s_dy, "DY", rpv::c_other, 1, cutandweight("pass*(nleps==2&&njets>=5&&njets<=6)",extraweight)));

    Samples.push_back(sfeats(s_wjets, "W+jets", rpv::c_wjets, 1, cutandweight("pass*(nleps==1&&njets>=8)",extraweight)));
    Samples.push_back(sfeats(s_dy, "DY", rpv::c_other, 1, cutandweight("pass*(nleps==2&&njets>=7)",extraweight)));

    // e = p = TMath::Sqrt(leps_pt*kep)
    // px = leps_pt * TMath::Cos(leps_phi)  
    // py = leps_pt * TMath::Sin(leps_phi)  
    // pz = leps_pt / TMath::Tan(leps_theta)  // leps_theta = 2 * TMath::ATan(TMath::Exp(-1*leps_eta))  

    // mll = TMath::Sqrt()

    // Loop over samples
    vector<int> rpv_sam45;
    for(unsigned sam(0); sam < 2; sam++) rpv_sam45.push_back(sam);
    vector<int> rpv_sam67;
    for(unsigned sam(2); sam < 4; sam++) rpv_sam67.push_back(sam);
    vector<int> rpv_sam8;
    for(unsigned sam(4); sam < 6; sam++) rpv_sam8.push_back(sam);

    // Define histogram vector
    vector<hfeats> hists;

    // Make analysis regions plots
    // Set cuts
    TString basecut = "mj12>=500&&ht>1200&&nbm<=2";

    // Loop over cuts to make histograms
    TString cut = "";
    // Set cuts
    cut = basecut;

    // Define histograms
    hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam45, "M_{J}", cut));
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", showData, true);  
    hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam67, "M_{J}", cut+"&&1"));
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", showData, true);  
    hists.push_back(hfeats("mj12", 3, 500, 1400, rpv_sam8, "M_{J}", cut+"&&11"));
    plot_distributions(Samples, hists, lumi, plot_type, plot_style, "rpv_base", showData, true);  
  }

}
