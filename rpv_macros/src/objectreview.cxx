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
#include "TStyle.h"
#include "TLatex.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

TString plot_type=".pdf";
TString plot_style="CMSPaper_Preliminary";

void muon_topology();
void btag_eff_map();
void lep_sf();


void muon_topology(TString year) {

  TString lumi;
  if(year=="UL2016_preVFP") lumi = "19.5";
  else if(year=="UL2016")   lumi = "16.8";
  else if(year=="UL2017")   lumi = "41.5";
  else if(year=="UL2018")   lumi = "59.8";

  TString folder_bkg, folder_sig;
  folder_bkg = "/mnt/data3/babies/250110/"+year+"/merged_rpvfitnbge0_mc/";
  folder_sig = "/mnt/data3/babies/250110/"+year+"/merged_rpvfitnbge0_sig/";

  vector<TString> s_qcd, s_ttbar, s_wjets, s_other, s_sig_m1800;
  s_qcd       = getRPVProcess(folder_bkg, "qcd");
  s_ttbar     = getRPVProcess(folder_bkg, "ttbar");
  s_wjets     = getRPVProcess(folder_bkg, "wjets");
  s_other     = getRPVProcess(folder_bkg, "other_public");
  s_sig_m1800 = getRPVProcess(folder_sig, "rpv_m1800");

  vector<sfeats> Samples;
  Samples.push_back(sfeats(s_sig_m1800, "m_{#tilde{g}}=1800 GeV", kRed, 1, cutandweight("pass","1."))); Samples.back().isSig = true;
  Samples.push_back(sfeats(s_qcd,   "QCD",      rpv::c_qcd,   1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_wjets, "W+jets",   rpv::c_wjets, 1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_ttbar, "t#bar{t}", rpv::c_tt,    1, cutandweight("pass","1.")));
  Samples.push_back(sfeats(s_other, "Others",   rpv::c_other, 1, cutandweight("pass","1.")));

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

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat(".3f");
  
  TString process[56] = {
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
    "ZZZ_TuneCP5_13TeV-amcatnlo-pythia8",
      // Signal
    "SMS-T1tbs_RPV_mGluino1000_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1100_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1200_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1300_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1400_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1500_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1600_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1700_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1800_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino1900_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino2000_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino2100_TuneCP5_13TeV-madgraphMLM-pythia8",
    "SMS-T1tbs_RPV_mGluino2200_TuneCP5_13TeV-madgraphMLM-pythia8"
  };


  TFile* f_btag[56];
  TH3D *comb[56], *comb_central[56], *incl[56];
  for(int i=0; i<56; i++) {
    f_btag[i]       = new TFile("data/btagEfficiency/ultralegacy/ptetabinned/"+year+"/btagEfficiency_"+process[i]+"_"+year+".root" , "READ");
    comb[i]         = static_cast<TH3D*>(f_btag[i]->Get("btagEfficiency_medium")->Clone(Form("btagEfficiency_medium_%d", i)));
  }

  int ind_b=3, ind_c=2, ind_lf=1;
  double pt_cuts[9]   = {30., 50., 70., 100., 140., 200., 300., 600., 1000.};
  double eta_cuts[13]  = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};
  TH2D *btag_eff_2D_b[56], *btag_eff_2D_c[56], *btag_eff_2D_lf[56];   // b, c, light-flavor quark
  for(int i=0; i<56; i++) {
    btag_eff_2D_b[i]  = new TH2D(Form("btag_eff_2D_b_%d", i), Form("btag_eff_2D_b_%d", i), 8, pt_cuts, 12, eta_cuts);
    btag_eff_2D_c[i]  = new TH2D(Form("btag_eff_2D_c_%d", i), Form("btag_eff_2D_c_%d", i), 8, pt_cuts, 12, eta_cuts);
    btag_eff_2D_lf[i] = new TH2D(Form("btag_eff_2D_lf_%d", i), Form("btag_eff_2D_lf_%d", i), 8, pt_cuts, 12, eta_cuts);

    for(int ip=1; ip<9; ip++) {
      for(int ie=1; ie<13; ie++) {
	btag_eff_2D_b[i]->SetBinContent(ip, ie, comb[i]->GetBinContent(ie, ip, ind_b));
	btag_eff_2D_b[i]->SetBinError(ip, ie, comb[i]->GetBinError(ie, ip, ind_b));
	btag_eff_2D_b[i]->SetTitle("btag_eff_b;Jet p_{T} (GeV);Jet |#eta|");
        btag_eff_2D_b[i]->SetTitleOffset(1.3);
	btag_eff_2D_c[i]->SetBinContent(ip, ie, comb[i]->GetBinContent(ie, ip, ind_c));
	btag_eff_2D_c[i]->SetBinError(ip, ie, comb[i]->GetBinError(ie, ip, ind_c));
	btag_eff_2D_c[i]->SetTitle("btag_eff_c;Jet p_{T} (GeV);Jet |#eta|");
        btag_eff_2D_c[i]->SetTitleOffset(1.3);
	btag_eff_2D_lf[i]->SetBinContent(ip, ie, comb[i]->GetBinContent(ie, ip, ind_lf));
	btag_eff_2D_lf[i]->SetBinError(ip, ie, comb[i]->GetBinError(ie, ip, ind_lf));
	btag_eff_2D_lf[i]->SetTitle("btag_eff_light;Jet p_{T} (GeV);Jet |#eta|");
        btag_eff_2D_lf[i]->SetTitleOffset(1.3);
      }
    }
  }

  TCanvas *c_b[56], *c_c[56], *c_lf[56];
  for(int i=0; i<56; i++) {
    c_b[i]  = new TCanvas(Form("c_b_%d", i), Form("c_b_%d", i), 1200, 1200);
    c_c[i]  = new TCanvas(Form("c_c_%d", i), Form("c_c_%d", i), 1200, 1200);
    c_lf[i] = new TCanvas(Form("c_lf_%d", i), Form("c_lf_%d", i), 1200, 1200);
    // b
    c_b[i]->cd();
    gPad->SetLogx();
    c_b[i]->SetRightMargin(0.15);
    btag_eff_2D_b[i]->Draw("colz text e");
    c_b[i]->Print(Form("plots/btagEfficiency/2dmap/%s/b/2D_btag_%s_%s_b.pdf", year.Data(), process[i].Data(), year.Data()));
    // c
    c_c[i]->cd();
    gPad->SetLogx();
    c_c[i]->SetRightMargin(0.15);
    btag_eff_2D_c[i]->SetTitleOffset(1.3);
    btag_eff_2D_c[i]->Draw("colz text e");
    c_c[i]->Print(Form("plots/btagEfficiency/2dmap/%s/c/2D_btag_%s_%s_c.pdf", year.Data(), process[i].Data(), year.Data()));
    // lf
    c_lf[i]->cd();
    c_lf[i]->SetRightMargin(0.15);
    gPad->SetLogx();
    btag_eff_2D_lf[i]->SetTitleOffset(1.3);
    btag_eff_2D_lf[i]->Draw("colz text e");
    c_lf[i]->Print(Form("plots/btagEfficiency/2dmap/%s/lf/2D_btag_%s_%s_lf.pdf", year.Data(), process[i].Data(), year.Data()));
  }


}


void lep_sf(TString year) {
  TFile* f_els_sf = new TFile(Form("data/leptonsf/fullsim_electron_isolated_%s.root", year.Data()), "READ");
  TFile* f_mus_sf = new TFile(Form("data/leptonsf/fullsim_muon_isolated_%s.root", year.Data()), "READ");

  TH2D* els_sf = new TH2D();
  TH2D* mus_sf = new TH2D();
  els_sf = static_cast<TH2D*>(f_els_sf->Get("EGamma_SF2D")->Clone("els_sf1"));
  mus_sf = static_cast<TH2D*>(f_mus_sf->Get("NUM_RazorPass_DEN_genTracks_abseta_pt")->Clone("mus_sf1"));

  TCanvas* c_els_sf = new TCanvas("c_els_sf", "c_els_sf", 1200, 1200);
  gPad->SetLogy();
  c_els_sf->cd();
  c_els_sf->SetRightMargin(0.2);
  els_sf->GetXaxis()->SetTitle("SuperCluster #eta");
  els_sf->GetXaxis()->SetTitleSize(0.2);
  els_sf->GetXaxis()->SetLabelSize(0.03);
  els_sf->GetYaxis()->SetTitle("p_{T} (GeV)");
  els_sf->GetYaxis()->SetLabelSize(0.03);
  els_sf->GetYaxis()->SetTitleSize(0.04);
  els_sf->GetZaxis()->SetLabelSize(0.03);
  els_sf->Draw("colz text");
  c_els_sf->Print(Form("plots/lepsf/%s/els_sf_%s.pdf", year.Data(), year.Data()));

  TCanvas* c_mus_sf = new TCanvas("c_mus_sf", "c_mus_sf", 1200, 1200);
  gPad->SetLogy();
  c_mus_sf->cd();
  c_mus_sf->SetRightMargin(0.2);
//  mus_sf->GetXaxis()->SetTitle("SuperCluster #eta");
  mus_sf->GetXaxis()->SetTitleSize(0.2);
  mus_sf->GetXaxis()->SetLabelSize(0.03);
//  mus_sf->GetYaxis()->SetTitle("p_{T} (GeV)");
  mus_sf->GetYaxis()->SetLabelSize(0.03);
  mus_sf->GetYaxis()->SetTitleSize(0.04);
  mus_sf->GetZaxis()->SetLabelSize(0.03);
  mus_sf->GetZaxis()->SetTitle("");
  mus_sf->SetTitle("#mu scale factors");
  mus_sf->Draw("colz text");
  c_mus_sf->Print(Form("plots/lepsf/%s/mus_sf_%s.pdf", year.Data(), year.Data()));


  
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
    else if(flag=="lepsf") {
      if(year=="UL2016_preVFP" || year=="UL2016_postVFP" || year=="UL2017" || year=="UL2018") {
        lep_sf(year);
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
