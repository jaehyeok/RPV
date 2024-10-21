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
#include "TFile.h"
#include "TH3D.h"
#include "TH2D.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

TString plot_type=".pdf";
TString plot_style="CMSPaper_Preliminary";

void muon_topology();
void btag_eff_map();


void muon_topology(TString year) {

  TString lumi, yr;
  if(year=="UL2016_preVFP") lumi = "19.5";
  else if(year=="UL2016")   lumi = "16.8";
  else if(year=="UL2017")   {lumi = "41.5"; yr="2017";}
  else if(year=="UL2018")   {lumi = "59.8"; yr="2018";}

  TString folder_bkg, folder_sig;
  if(year=="UL2016_preVFP" || year=="UL2016") {
    folder_bkg = "/mnt/data3/babies/231001/2016/merged_norm_JER_0903_"+year+"/";
    folder_sig = "/mnt/data3/babies/231001/2016/merged_norm_sig_pu_"+year+"/";
  }
  else {
    folder_bkg = "/mnt/data3/babies/231001/"+yr+"/merged_norm_JER_0903/";
    folder_sig = "/mnt/data3/babies/231001/"+yr+"/merged_norm_sig_pu/";
  }

  vector<TString> s_qcd, s_ttbar, s_wjets, s_other, s_sig_m1800;
  s_qcd       = getRPVProcess(folder_bkg, "qcd");
  s_ttbar     = getRPVProcess(folder_bkg, "ttbar");
  s_wjets     = getRPVProcess(folder_bkg, "wjets");
  s_other     = getRPVProcess(folder_bkg, "other_public");
  s_sig_m1800 = getRPVProcess(folder_sig, "rpv_m1800");

  vector<sfeats> Samples;
  if(year=="UL2016_preVFP") {
    Samples.push_back(sfeats(s_sig_m1800, "m_{#tilde{g}}=1800 GeV", kRed, 1, cutandweight("pass","19.5/36.3"))); Samples.back().isSig = true;
    Samples.push_back(sfeats(s_qcd,   "QCD",      rpv::c_qcd,   1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_wjets, "W+jets",   rpv::c_wjets, 1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt,    1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_other, "Others",   rpv::c_other, 1, cutandweight("pass","1.")));
  }
  else if(year=="UL2016") {
    Samples.push_back(sfeats(s_sig_m1800, "m_{#tilde{g}}=1800 GeV", kRed, 1, cutandweight("pass","16.8/36.3"))); Samples.back().isSig = true;
    Samples.push_back(sfeats(s_qcd,   "QCD",      rpv::c_qcd,   1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_wjets, "W+jets",   rpv::c_wjets, 1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt,    1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_other, "Others",   rpv::c_other, 1, cutandweight("pass","1.")));
  }
  else {
    Samples.push_back(sfeats(s_sig_m1800, "m_{#tilde{g}}=1800 GeV", kRed, 1, cutandweight("pass","1."))); Samples.back().isSig = true;
    Samples.push_back(sfeats(s_qcd,   "QCD",      rpv::c_qcd,   1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_wjets, "W+jets",   rpv::c_wjets, 1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt,    1, cutandweight("pass","1.")));
    Samples.push_back(sfeats(s_other, "Others",   rpv::c_other, 1, cutandweight("pass","1.")));
  }

  vector<int> rpv_sam;
  for(unsigned sam(0); sam < Samples.size(); sam++) rpv_sam.push_back(sam);

  vector<hfeats> hists;
  
  std::vector<TString> cuts = {"nleps==1&&nmus==1&&njets>=4&&ht>1200&&mj12>500&&mus_sigid==1&&mus_miniso<0.2&&mus_pt>20&&abs(mus_eta)<2.4"};
  for(auto icut : cuts){
    hists.push_back(hfeats("mus_pt",  120, 0, 1200,  rpv_sam, "muon p_{T}", icut));
    hists.push_back(hfeats("mus_eta", 60, -3., 3.,   rpv_sam, "muon #eta",  icut));
    hists.push_back(hfeats("mus_phi", 70, -3.5, 3.5, rpv_sam, "muon #phi",  icut));
    hists.push_back(hfeats("mus_pt",  120, 0, 1200,  rpv_sam, "muon p_{T}", icut));
  }

  plot_distributions(Samples, hists, lumi, plot_type, plot_style, "objrev", false, true);

}

void btag_eff_map(TString year) {
  
  TString process[43] = {
    // TTbar
    "TTJets_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8",
    "TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8",
    "TTJets_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8",
    "TTJets_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8",
    "TTJets_TuneCP5_13TeV-madgraphMLM-pythia8",
    // QCD
    "QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
    "QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
    "QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
    "QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
    "QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8",
    // W+jets
    "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8",
    // Others
      // DY
    "DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8",
      // TT+X
    "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8",
    "TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8",
    "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
    "TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8",
    "TTTT_TuneCP5_13TeV-amcatnlo-pythia8",
    "ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8",
      // ST
    "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8",
    "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8",
    "ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8",
    "ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8",
    "ST_s-channel_4f_hadronicDecays_TuneCP5_13TeV-amcatnlo-pythia8",
    "ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8",
      // Di-Boson
    "WW_TuneCP5_13TeV-pythia8",
    "WZ_TuneCP5_13TeV-pythia8",
    "ZZ_TuneCP5_13TeV-pythia8",
    "WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8",
    "WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8",
    "WZZ_TuneCP5_13TeV-amcatnlo-pythia8",
    "ZZZ_TuneCP5_13TeV-amcatnlo-pythia8"
  };

  TString process_latex[43] = {
    // TTbar
    "TTJets\\_HT-600to800\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "TTJets\\_HT-800to1200\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "TTJets\\_HT-1200to2500\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "TTJets\\_HT-2500toInf\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "TTJets\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    // QCD
    "QCD\\_HT500to700\\_TuneCP5\\_PSWeights\\_13TeV-madgraph-pythia8",
    "QCD\\_HT700to1000\\_TuneCP5\\_PSWeights\\_13TeV-madgraph-pythia8",
    "QCD\\_HT1000to1500\\_TuneCP5\\_PSWeights\\_13TeV-madgraph-pythia8",
    "QCD\\_HT1500to2000\\_TuneCP5\\_PSWeights\\_13TeV-madgraph-pythia8",
    "QCD\\_HT2000toInf\\_TuneCP5\\_PSWeights\\_13TeV-madgraph-pythia8",
    // W+jets
    "WJetsToLNu\\_HT-100To200\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-200To400\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-400To600\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-600To800\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-800To1200\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-1200To2500\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu\\_HT-2500ToInf\\_TuneCP5\\_13TeV-madgraphMLM-pythia8",
    // Others
      // DY
    "DYJetsToLL\\_M-50\\_HT-100to200\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-200to400\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-400to600\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-600to800\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-800to1200\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-1200to2500\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL\\_M-50\\_HT-2500toInf\\_TuneCP5\\_PSweights\\_13TeV-madgraphMLM-pythia8",
      // TT+X
    "TTZToLLNuNu\\_M-10\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "TTZToQQ\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "TTWJetsToLNu\\_TuneCP5\\_13TeV-amcatnloFXFX-madspin-pythia8",
    "TTWJetsToQQ\\_TuneCP5\\_13TeV-amcatnloFXFX-madspin-pythia8",
    "TTTT\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "ttHJetTobb\\_M125\\_TuneCP5\\_13TeV\\_amcatnloFXFX\\_madspin\\_pythia8",
      // ST
    "ST\\_tW\\_antitop\\_5f\\_inclusiveDecays\\_TuneCP5\\_13TeV-powheg-pythia8",
    "ST\\_tW\\_top\\_5f\\_inclusiveDecays\\_TuneCP5\\_13TeV-powheg-pythia8",
    "ST\\_t-channel\\_antitop\\_4f\\_InclusiveDecays\\_TuneCP5\\_13TeV-powheg-madspin-pythia8",
    "ST\\_t-channel\\_top\\_4f\\_InclusiveDecays\\_TuneCP5\\_13TeV-powheg-madspin-pythia8",
    "ST\\_s-channel\\_4f\\_hadronicDecays\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "ST\\_s-channel\\_4f\\_leptonDecays\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
      // Di-Boson
    "WW\\_TuneCP5\\_13TeV-pythia8",
    "WZ\\_TuneCP5\\_13TeV-pythia8",
    "ZZ\\_TuneCP5\\_13TeV-pythia8",
    "WWW\\_4F\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "WWZ\\_4F\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "WZZ\\_TuneCP5\\_13TeV-amcatnlo-pythia8",
    "ZZZ\\_TuneCP5\\_13TeV-amcatnlo-pythia8"
  };



  bool formatLatex = true;
  TString yr;
  if(year=="UL2016_preVFP") yr = "UL2016\\_preVFP";
  else yr = year;

  TFile* f_btag[43];
  TH3D *comb[43], *comb_central[43], *incl[43];
  for(int i=0; i<43; i++) {
    f_btag[i]       = new TFile("btagEfficiency/ultralegacy/"+year+"/btagEfficiency_"+process[i]+"_"+year+".root" , "READ");
    comb[i]         = static_cast<TH3D*>(f_btag[i]->Get("btagEfficiency_medium_comb")->Clone(Form("btagEfficiency_medium_comb_%d", i)));
    comb_central[i] = static_cast<TH3D*>(f_btag[i]->Get("btagEfficiency_medium_comb_central")->Clone(Form("btagEfficiency_medium_comb_central_%d", i)));
    incl[i]         = static_cast<TH3D*>(f_btag[i]->Get("btagEfficiency_medium_incl")->Clone(Form("btagEfficiency_medium_comb_central_%d", i)));
  }


  if(formatLatex) {
    cout << endl;
    cout << "\\renewcommand{\\arraystretch}{1.3}" << endl;
    cout << endl;

    cout << "\\begin{table}" << endl;
    cout << "\\centering" << endl;
    cout << Form("\\caption{Summary table of B-tagging efficiencies for the Deep Combined Secondary Vertex (DeepCSV) algorithm at the medium working point for each %s Monte Carlo sample, categorized by hadron flavor.}", yr.Data()) << endl;
    cout << "\\resizebox{\\textwidth}{!}{" << endl;
    cout << "\\begin{tabular}{|c|>{\\centering\\arraybackslash}p{2.5cm}|>{\\centering\\arraybackslash}p{2.5cm}|>{\\centering\\arraybackslash}p{2.8cm}|}" << endl;
    cout << "\\hline" << endl;
    cout << "\\multirow{2}{*}{Process}    & \\multicolumn{3}{c|}{Efficiency}                                                               \\\\ \\cline{2-4}"     << endl;
    cout << "                             & b jets        & c jets        & light flavor jets  \\\\ \\hline"          << endl;
    cout << "\\hline" << endl;

    for(int i=0; i<43; i++) {
      cout << Form("         %s           & %.5f          & %.5f          &        %.5f        \\\\ \\hline",   process_latex[i].Data(), comb_central[i]->GetBinContent(1,1,3), comb_central[i]->GetBinContent(1,1,2), comb_central[i]->GetBinContent(1,1,1))          << endl;
    }

    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{table}" << endl;
  }



}

int main(int argc, char *argv[]){
  
  TString year  = argv[1];
  TString flag  = argv[2];

  if(argc==3) {
    if(flag=="muontopology") {
      if(year=="UL2016_preVFP" || year=="UL2016" || year=="UL2017" || year=="UL2018") {
        muon_topology(year);
      }
      else {
        cout << "ERROR::Please input year as UL2016_preVFP/UL2016/UL2017/UL2018" << endl;
      }
    }

    else if(flag=="btageffmap") {
      if(year=="UL2016_preVFP" || year=="UL2016" || year=="UL2017" || year=="UL2018") {
        btag_eff_map(year);
      }
      else {
        cout << "ERROR::Please input year as UL2016_preVFP/UL2016/UL2017/UL2018" << endl;
      }
    }

    else {
      cout << "./run/objectreview.exe [year] [flag]" << endl;
      cout << "ERROR::Please input year as UL2016_preVFP/UL2016/UL2017/UL2018" << endl;
      cout << "ERROR::Please input flag as muontopology/btageffmap" << endl;
    }
  }
  else {
    cout << "./run/objectreview.exe [year] [flag]" << endl;
    cout << "ERROR::Please input year as UL2016_preVFP/UL2016/UL2017/UL2018" << endl;
    cout << "ERROR::Please input flag as muontopology/btageffmap" << endl;
  }


}
