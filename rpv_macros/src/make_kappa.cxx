//**********     Author : Chang Whan Jung     **********//
//
// This code is referred by src/make_variation_loop.cxx
// 

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

struct winsize w;

void genKappaRegions(small_tree_rpv &tree, TString year, TFile *f, bool flag_kwj, TString procname);
void genKappaFactors(TFile *f);
vector<TH1F*> ApplyKappaFactor(TFile *f, int ibin, float kappa[2][3][3]);
int genMConly(TFile *f, bool mconly_eval, bool mconly_vali);
TString color(TString procname);


int nbins = 18;
float mjmin = 500;
float mjmax = 1400;

bool debug = true;
bool mconly_eval_(true), mconly_vali_(true);

float lumi = 35.9;

vector<int> bins_tot = {0, 1, 2, 
                        3, 4, 5,  
                        6, 7, 8,
                        9, 10, 11, 
                        12, 13, 14, 
                        15, 16, 17};

vector<int> bins_eval = {0, 1, 2,     //QCD
                         6, 7, 8,     //Wjets
                         12, 13, 14}; //ttbar

vector<int> bins_vali = {3, 4, 5,     //QCD
                         9, 10, 11,   //Wjets
                         15, 16, 17}; //ttbar
TString red = "\033[0;31m";
TString green = "\033[1;32m";
TString blue = "\033[1;34m";
TString yellow = "\033[1;33m";
TString gray = "\033[0;90m";
TString cyan = "\033[0;36m";
TString reset = "\033[0m";

int main(int argc, char *argv[]){
  gErrorIgnoreLevel=kError+1;
  TH1::SetDefaultSumw2();

  ioctl(0, TIOCGWINSZ, &w);
  int cols = w.ws_col;

  TString year="2016";

  TString temp_eval_(argv[2]), temp_vali_(argv[3]), temp_help_(argv[1]);

  if(argc==5){
    year = argv[1];
    if(temp_eval_=="on") mconly_eval_=true;
    else if(temp_eval_=="off") mconly_eval_=false;
    if(temp_vali_=="on") mconly_vali_=true;
    else if(temp_vali_=="off") mconly_vali_=false;
    lumi = atof(argv[4]);
  }
  else if(argc==4){
    year = argv[1];
    if(temp_eval_=="on") mconly_eval_=true;
    else if(temp_eval_=="off") mconly_eval_=false;
    if(temp_vali_=="on") mconly_vali_=true;
    else if(temp_vali_=="off") mconly_vali_=false;
  }
  else if(argc==2&&(temp_help_=="--help"||temp_help_=="-h")){
    cout<<"How to run this program : "<<endl;
    cout<<"./run/make_kappa [year] [MC only mode for evaluation region] [MC only mode for validation region] [luminosity]" << endl;
    cout<<"Chang Whan Jung, changhwanjung95@gmail.com"<<endl;
    return 0;
  }
  else if(argc==1){
    year = argv[1];
  }

  if(argc==4||argc==1){
    if(year=="2016") lumi = 35.9;
    if(year=="2017") lumi = 41.5;
    if(year=="2018") lumi = 59.7;
  }

  cout<<mconly_eval_<<endl;
  cout<<argc<<endl;

  cout<<"year                         : "<< year    <<endl;
  cout<<"luminosity                   : "<< lumi    <<endl;
  TString temp_=mconly_eval_==true?"on":"off";
  cout<<"MConly for evaluation region : "<< temp_   <<endl;
  temp_=mconly_vali_==true?"on":"off";
  cout<<"MConly for validation region : "<< temp_   <<endl;

  cout<<argc<<endl;

  TString folder_bkg = folder_year(year,false).at(0);
  TString folder_dat = folder_year(year,false).at(1);
  TString folder_sig = folder_year(year,false).at(2);
  TString folder_kwj = folder_year(year,false).at(3);

  cout<<folder_bkg<<endl;

  vector<TString> s_jetht = getRPVProcess(folder_dat, "data");

  vector<TString> s_qcd = getRPVProcess(folder_bkg, "qcd");
  vector<TString> s_ttbar = getRPVProcess(folder_bkg, "ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg, "wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg, "other_public");

  small_tree_rpv data((static_cast<std::string>(s_jetht.at(0))));

  small_tree_rpv qcd((static_cast<std::string>(s_qcd.at(0))));
  for(auto iqcd : s_qcd) qcd.Add((static_cast<std::string>(iqcd)));
  small_tree_rpv ttbar((static_cast<std::string>(s_ttbar.at(0))));
  for(auto ittbar : s_ttbar) ttbar.Add((static_cast<std::string>(ittbar)));
  small_tree_rpv wjets((static_cast<std::string>(s_wjets.at(0))));
  for(auto iwjets : s_wjets) wjets.Add((static_cast<std::string>(iwjets)));
  small_tree_rpv other((static_cast<std::string>(s_other.at(0))));
  for(auto iother : s_other) other.Add((static_cast<std::string>(iother)));

  vector<TString> s_jetht_kwj = getRPVProcess(folder_kwj, "data");

  vector<TString> s_qcd_kwj   = getRPVProcess(folder_kwj, "qcd");
  vector<TString> s_ttbar_kwj = getRPVProcess(folder_kwj, "ttbar");
  vector<TString> s_DY_kwj = getRPVProcess(folder_kwj, "DY");
  vector<TString> s_other_kwj = getRPVProcess(folder_kwj, "other_DY");

  small_tree_rpv data_kwj((static_cast<std::string>(s_jetht_kwj.at(0))));

  small_tree_rpv qcd_kwj((static_cast<std::string>(s_qcd_kwj.at(0))));
  for(auto iqcd_kwj : s_qcd_kwj) qcd.Add((static_cast<std::string>(iqcd_kwj)));
  small_tree_rpv ttbar_kwj((static_cast<std::string>(s_ttbar_kwj.at(0))));
  for(auto ittbar_kwj : s_ttbar_kwj) ttbar_kwj.Add((static_cast<std::string>(ittbar_kwj)));
  small_tree_rpv DY_kwj((static_cast<std::string>(s_DY_kwj.at(0))));
  for(auto iDY_kwj : s_DY_kwj) DY_kwj.Add((static_cast<std::string>(iDY_kwj)));
  small_tree_rpv other_kwj((static_cast<std::string>(s_other_kwj.at(0))));
  for(auto iother_kwj : s_other_kwj) other_kwj.Add((static_cast<std::string>(iother_kwj)));
  //getKappa(data, year, f, "data_obs");
  TFile *f = new TFile("variations/output_kappa_regions.root", "recreate");

  if(!(mconly_eval_&&mconly_vali_)) genKappaRegions( data, year, f, false, "data_obs");

  genKappaRegions(  qcd, year, f, false,   "qcd");
  genKappaRegions(ttbar, year, f, false, "ttbar");
  genKappaRegions(wjets, year, f, false, "wjets");  
  genKappaRegions(other, year, f, false, "other");

  if(!(mconly_eval_&&mconly_vali_)) genKappaRegions( data_kwj, year, f, true, "data_obs");

  genKappaRegions(  qcd_kwj, year, f, true,   "qcd");
  genKappaRegions(ttbar_kwj, year, f, true, "ttbar");
  genKappaRegions(   DY_kwj, year, f, true,    "DY");  
  genKappaRegions(other_kwj, year, f, true, "other");
  
  genMConly(f, mconly_eval_, mconly_vali_);
  
  f->Close();

  TFile *f_ = new TFile("variations/output_kappa_regions.root", "read");
  genKappaFactors(f_); 

  f_->Close();
}

void genKappaRegions(small_tree_rpv &tree, TString year, TFile *f, bool flag_kwj, TString procname){
  ioctl(0,TIOCGWINSZ, &w);
  int cols = w.ws_col;


  vector<int> bins = {0, 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  if(flag_kwj) bins = {6, 7, 8};

  // Get QCD flavor weights/systematics
  TFile *csv_weight_file = TFile::Open("data/csvfit_low_njet.root");
  TH1F *csv_weight = static_cast<TH1F*>(csv_weight_file->Get("csv_weight"));

  TFile *csv_weight_file_highnjet = TFile::Open("data/csvfit_high_njet.root");
  TH1F *csv_weight_highnjet = static_cast<TH1F*>(csv_weight_file_highnjet->Get("csv_weight"));

  float bflavorValCentral = csv_weight->GetBinContent(1);
  float bflavorValError = csv_weight->GetBinError(1);
  float cflavorValCentral = csv_weight->GetBinContent(2);
  float cflavorValError = csv_weight->GetBinError(2);
  float lflavorValCentral = csv_weight->GetBinContent(3);
  float lflavorValError = csv_weight->GetBinError(3);

  if(procname=="qcd")  
  {
    std::cout << "CSV fit low Njets results: " << std::endl;
    std::cout << "Reweight b jets by " << bflavorValCentral << " +/- " << bflavorValError << std::endl;
    std::cout << "Reweight c jets by " << cflavorValCentral << " +/- " << cflavorValError << std::endl;
    std::cout << "Reweight l jets by " << lflavorValCentral << " +/- " << lflavorValError << std::endl;
    std::cout << "CSV fit high Njets results: " << std::endl;
    std::cout << "Reweight b jets by " << csv_weight_highnjet->GetBinContent(1)
      << " +/ " << csv_weight_highnjet->GetBinError(1) << std::endl;
    std::cout << "Reweight c jets by " << csv_weight_highnjet->GetBinContent(2)
      << " +/ " << csv_weight_highnjet->GetBinError(2) << std::endl;
    std::cout << "Reweight l jets by " << csv_weight_highnjet->GetBinContent(3)
      << " +/ " << csv_weight_highnjet->GetBinError(3) << std::endl;
  }

  // Increase uncertainty on variation by difference between nominal and high njet fit (from Pieter's comment)
  float bflavorValDiff_low_high = bflavorValCentral - csv_weight_highnjet->GetBinContent(1);
  bflavorValError = sqrt(pow(bflavorValError,2) + pow(bflavorValDiff_low_high,2));
  float cflavorValDiff_low_high = cflavorValCentral - csv_weight_highnjet->GetBinContent(2);
  // Negative sign implements anticorrelation between b and c reweightings
  cflavorValError = -1*(sqrt(pow(cflavorValError,2) + pow(cflavorValDiff_low_high,2)));
  float lflavorValDiff_low_high = lflavorValCentral - csv_weight_highnjet->GetBinContent(3);
  lflavorValError = sqrt(pow(lflavorValError,2) + pow(lflavorValDiff_low_high,2));

  if(procname=="qcd") 
  { 
    std::cout << "Reweight b jets by " << bflavorValCentral << " +/ " << bflavorValError << std::endl;
    std::cout << "Reweight c jets by " << cflavorValCentral << " +/ " << cflavorValError << std::endl;
    std::cout << "Reweight l jets by " << lflavorValCentral << " +/ " << lflavorValError << std::endl;
  }

  csv_weight_file->Close();
  csv_weight_file_highnjet->Close();
  f->cd();

  // nominal, up and down histrograms  
  int MjBin=2;
  int NbBin=4;
  nbins = bins.size();
  TH1F * h1nominal[nbins];

  for(auto ibin : bins)
  {
    int index;
    index = find(bins.begin(), bins.end(), ibin) - bins.begin();
    h1nominal[index]    = new TH1F(Form("%s_bin%i",procname.Data(),ibin),    Form("%s_bin%i",procname.Data(),ibin), MjBin+1, mjmin, mjmax);
  }
  // Loop over tree
  for(unsigned int ientry=0; ientry<tree.GetEntries();ientry++){
    float progress = 0.0;
    if(ientry%int(tree.GetEntries()/min(1000,int(tree.GetEntries()))) == 0||ientry+1 == tree.GetEntries()){
      ioctl(0,TIOCGWINSZ, &w);
      cols = w.ws_col;
      //cols = 104;
      progress = float(ientry+1)/float(tree.GetEntries());
      int barWidth = cols - 79;
      TString space = "";
      for(int sp = 0 ; sp < 20-strlen(procname.Data()) ; sp++){
        space = space + " "; 
      }
      cout << "Process name      : " << procname.Data() << space.Data() <<  "[";
      int pos = barWidth*progress;
      for(int i = 0; i < barWidth;++i){
        if(i < pos) cout << color(procname).Data() << "■";
        else if(i==pos) cout << color(procname).Data() << "■";
        else cout << " ";
      } 
      cout<<"\033[0m]";
      TString space2 = "";
      TString space3 = "";
      for(int sp2 = 0 ; sp2 < 22-strlen(Form("%d",ientry))-strlen(Form("%d",tree.GetEntries())) ; sp2++) space2 = space2 +" ";
      cout << space2.Data() << ientry+1 << " / " << tree.GetEntries() << "   (" << space3.Data() << Form("%5.1f",progress*100.0) <<"%)\r";
      cout.flush();
    }
    tree.GetEntry(ientry); 

    float mll(0);
    TLorentzVector mom1, mom2;
    if(flag_kwj && tree.nleps()!=2){
      cout<< tree.nleps() << endl;
      continue;
    }
    else if(flag_kwj){
      float mass(0);
      if(tree.leps_pdgid().at(0)*tree.leps_pdgid().at(1)==-121) mass = 0.510*0.001;
      else if(tree.leps_pdgid().at(0)*tree.leps_pdgid().at(1)==-169) mass = 105.66*0.001;
      else continue;
      mom1.SetPtEtaPhiM(tree.leps_pt().at(0), tree.leps_eta().at(0), tree.leps_phi().at(0), mass);
      mom2.SetPtEtaPhiM(tree.leps_pt().at(1), tree.leps_eta().at(1), tree.leps_phi().at(1), mass);
      TLorentzVector momtot = mom1+mom2;
      mll = momtot.M();
    }
    else mll=0;
    float weight = lumi*tree.weight();
    if(procname=="data_obs") weight = 1;
    for(auto ibin : bins){
      if(tree.mj12()>0 && passKapBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm(), mll)) 
      {
        int index;
        index = find(bins.begin(), bins.end(), ibin) - bins.begin();
        float hmjmax = mjmax-0.001;
        h1nominal[index]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), weight);  // nominal  
      }
    }
  }
  for(auto ibin : bins){
    int index;
    index = find(bins.begin(), bins.end(), ibin) - bins.begin();
    //cout << index << "&" << ibin << endl;

    gDirectory->cd("/");
      TString directory(Form("bin%d", ibin));
    if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
    gDirectory->cd(directory);


    h1nominal[index]->SetTitle(procname.Data());
    h1nominal[index]->SetName(procname.Data());
    h1nominal[index]->Write();
  }
  cout<<"\n"; 
  for(int al=0 ; al<cols ; al++) cout << "=";
  cout<<endl;
}

int genMConly(TFile *f, bool mconly_eval, bool mconly_vali){
  vector<int> bins;
  if(mconly_eval&&!mconly_vali) bins = bins_eval;
  if(!mconly_eval&&mconly_vali) bins = bins_vali;
  if(mconly_eval&&mconly_vali) bins = bins_tot;
  if(!mconly_eval&&!mconly_vali) return 0;

  cout<<bins.at(0)<<","<<bins.at(3)<<endl;

  int MjBin=2;
  int NbBin=4;

  nbins = bins.size();

  for(auto ibin: bins){
    TH1F *data_obs = new TH1F("data_obs", "data_obs", MjBin+1, mjmin, mjmax);
    f->cd();
    gDirectory->cd("/");
    TH1F *qcd   = static_cast<TH1F*>(f->Get(Form("/bin%d/qcd",ibin)));
    TH1F *ttbar = static_cast<TH1F*>(f->Get(Form("/bin%d/ttbar",ibin)));
    TH1F *other = static_cast<TH1F*>(f->Get(Form("/bin%d/other",ibin)));
    TH1F *wjets; 
    if(ibin==6||ibin==7||ibin==8){
      wjets = static_cast<TH1F*>(f->Get(Form("/bin%d/DY",ibin)));
    }
    else wjets = static_cast<TH1F*>(f->Get(Form("/bin%d/wjets",ibin)));
    for(int i=1; i<=data_obs->GetNbinsX(); i++){
      data_obs->SetBinContent(i, (qcd->GetBinContent(i) + ttbar->GetBinContent(i) + wjets->GetBinContent(i) + other->GetBinContent(i)));
      if(debug) cout<<"bin : " << ibin << "|| Content : " <<(qcd->GetBinContent(i) + ttbar->GetBinContent(i) + wjets->GetBinContent(i) + other->GetBinContent(i)) << "\n qcd :" << qcd->GetBinContent(i) << "\n ttbar : " << ttbar->GetBinContent(i) << "\n wjets : " << wjets->GetBinContent(i) << "\n other : " << other->GetBinContent(i) << endl;
      data_obs->SetBinError(i, TMath::Sqrt(data_obs->GetBinContent(i)));
    }
    gDirectory->cd(Form("/bin%d",ibin));
    data_obs->Write("",TObject::kOverwrite);
  }
  return 0;
}

void genKappaFactors(TFile *f){

  float kappa[2][3][3], kappa_unc[2][3][3];
  for(int i=0 ; i<3 ; i++ ){
    for(int j=0 ; j<3 ; j++ ){
      for(int k=0 ; k<2 ; k++ ){
        kappa[k][i][j] = 1;
      }
    }
  }

  f->cd();

  for(auto ibin : bins_eval){
    int ind_ibin    = ibin%3;        // ind_ibin = 0 : Low Njets, ind_ibin = 1 : Med Njets, ind_ibin = 2 : High Njets
    int ind_proc    = int(ibin/6);   // ind_proc = 0 : qcd, ind_proc = 1 : wjets, ind_proc = 2 : ttbar
    float ratio[3];
    vector<TH1F*> ret;
    TH1F *mc_tot, *ratio_dmc, *data_obs;
    ret = ApplyKappaFactor(f, ibin, kappa);
    data_obs = ret.at(0);
    mc_tot   = ret.at(1);

    ratio_dmc = static_cast<TH1F*>(data_obs->Clone("ratio_dmc"));
    ratio_dmc->Divide(mc_tot);
    for(int i=0 ; i<3 ; i++){
      ratio[i] = ratio_dmc->GetBinContent(i+1);
    }
    kappa[0][ind_ibin][ind_proc] = ratio[1]/ratio[0];
    kappa[1][ind_ibin][ind_proc] = ratio[2]/ratio[0];
  }
  if(debug){
    for(int ibin=0 ; ibin<3 ; ibin++){
      for(int jproc=0 ; jproc<3 ; jproc++){
        cout << "kappa 1 in NJets " << ibin<<" process : " <<jproc << " : " << kappa[0][ibin][jproc] << endl;
        cout << "kappa 2 in NJets " << ibin<<" process : " <<jproc << " : " << kappa[1][ibin][jproc] << endl;
      }
    }
  }
  for(auto ibin : bins_vali){
    int ind_ibin    = ibin%3;        // ind_ibin = 0 : Low Njets, ind_ibin = 1 : Med Njets, ind_ibin = 2 : High Njets
    int ind_proc    = int(ibin/6);   // ind_proc = 0 : qcd, ind_proc = 1 : wjets, ind_proc = 2 : ttbar
    TH1F *mc_tot, *ratio_dmc, *data_obs;
    vector<TH1F*> ret;
    ret = ApplyKappaFactor(f, ibin, kappa);
    data_obs = ret.at(0);
    mc_tot   = ret.at(1);
    for(int i=1 ; i<3 ; i++){
      float unc_diff(0), unc_stat(0), unc_mc(0), temp_data_(0);
      unc_diff = abs(data_obs->GetBinContent(i+1)-mc_tot->GetBinContent(i+1));
      temp_data_ = data_obs->GetBinContent(i+1);
      if(debug){
      cout<<"Data's " << i+1 << "th Bin : " <<data_obs->GetBinContent(i+1)<<endl;
      cout<<"MC's " << i+1 << "th Bin   : " << mc_tot->GetBinContent(i+1)<<endl;
      cout<<"kappa uncertainty : "<<unc_diff/temp_data_<<endl;
      }
      unc_stat = data_obs->GetBinError(i+1);
      unc_mc   = mc_tot->GetBinError(i+1);
      kappa_unc[i-1][ind_ibin][ind_proc] = unc_diff/temp_data_; 
    }
  }
  if(debug){
    for(int ibin=0 ; ibin<3 ; ibin++){
      for(int jproc=0 ; jproc<3 ; jproc++){
        cout << "kappa 1 uncertainty in NJets " << ibin<<" process : " <<jproc << " : " << kappa_unc[0][ibin][jproc] << endl;
        cout << "kappa 2 uncertainty in NJets " << ibin<<" process : " <<jproc << " : " << kappa_unc[1][ibin][jproc] << endl;
      }
    }
  }
  vector<TString> process  = {"qcd", "wjets", "ttbar"};
  vector<TString> njRegion = {"Low Njets ", "Med Njets ", "High Njets "};
  TH1F *hist_kappa1 = new TH1F("hist_kappa1", "hist_kappa1", 9, 0, 9);
  TH1F *hist_kappa2 = new TH1F("hist_kappa2", "hist_kappa2", 9, 0, 9);
  for(int ibin=0 ; ibin<3 ; ibin++){
    for(int jproc=0 ; jproc<3 ; jproc++){
      hist_kappa1->SetBinContent((ibin+1)+jproc*3,kappa[0][ibin][jproc]);
      hist_kappa1->SetBinError((ibin+1)+jproc*3,kappa_unc[0][ibin][jproc]);
      hist_kappa1->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
      hist_kappa2->SetBinContent((ibin+1)+jproc*3,kappa[1][ibin][jproc]);
      hist_kappa2->SetBinError((ibin+1)+jproc*3,kappa_unc[1][ibin][jproc]);
      hist_kappa2->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
    }
  }
  hist_kappa1->SetStats(0);
  hist_kappa1->SetMaximum(2);
  hist_kappa1->SetMinimum(0);
  hist_kappa1->SetTitle("kappa1");
  hist_kappa2->SetStats(0);
  hist_kappa2->SetMaximum(2);
  hist_kappa2->SetMinimum(0);
  hist_kappa2->SetTitle("kappa2");
  TFile *g = new TFile("data/kappa_result.root","recreate");
  g->cd();
  hist_kappa1->Write();
  hist_kappa2->Write();
  TCanvas *c = new TCanvas("c","c",1600,1600);
  c->Divide(1,2);
  c->cd(1);
  hist_kappa1->Draw("e");
  c->cd(2);
  hist_kappa2->Draw("e");
  
  c->Print("kappa_result.pdf");
}

vector<TH1F*> ApplyKappaFactor(TFile *f, int ibin, float kappa[2][3][3]){
  int index       = find(bins_eval.begin(), bins_eval.end(), ibin) - bins_eval.begin();
  int ind_ibin    = ibin%3;        // ind_ibin = 0 : Low Njets, ind_ibin = 1 : Med Njets, ind_ibin = 2 : High Njets
  int ind_proc    = int(ibin/6);   // ind_proc = 0 : qcd, ind_proc = 1 : wjets, ind_proc = 2 : ttbar
  float SF(1);
  gDirectory->cd("/");
  TH1F* data_obs  = static_cast<TH1F*>(f->Get(Form("/bin%d/data_obs",ibin)));
  if(debug) cout<<"bin : "<<ibin<<endl;
  TH1F* mc_qcd    = static_cast<TH1F*>(f->Get(Form("/bin%d/qcd",ibin)));
  TH1F* mc_wjets; 
  if(ibin==6||ibin==7||ibin==8) mc_wjets = static_cast<TH1F*>(f->Get(Form("/bin%d/DY",ibin)));
  else mc_wjets   = static_cast<TH1F*>(f->Get(Form("/bin%d/wjets",ibin)));
  TH1F* mc_ttbar  = static_cast<TH1F*>(f->Get(Form("/bin%d/ttbar",ibin)));
  TH1F* mc_other  = static_cast<TH1F*>(f->Get(Form("/bin%d/other",ibin)));

  TH1F* kap_qcd    = static_cast<TH1F*>(mc_qcd->Clone(Form("kap_qcd_bin%d",ibin)));
  TH1F* kap_wjets  = static_cast<TH1F*>(mc_wjets->Clone(Form("kap_wjets_bin%d",ibin)));
  TH1F* kap_ttbar  = static_cast<TH1F*>(mc_ttbar->Clone(Form("kap_ttbar_bin%d",ibin)));
  TH1F* kap_other  = static_cast<TH1F*>(mc_other->Clone(Form("kap_other_bin%d",ibin)));

  for(int bin=2 ; bin<4; bin++){
    if(debug)cout<<bin<<endl;
    float temp_kap_ = kappa[bin-2][ind_ibin][0];
    kap_qcd->SetBinContent(bin, mc_qcd->GetBinContent(bin)*temp_kap_);
    temp_kap_ = kappa[bin-2][ind_ibin][1];
    kap_wjets->SetBinContent(bin, mc_wjets->GetBinContent(bin)*temp_kap_);
    temp_kap_ = kappa[bin-2][ind_ibin][2];
    kap_ttbar->SetBinContent(bin, mc_ttbar->GetBinContent(bin)*temp_kap_);
  }

  TH1F* mc_tot    = static_cast<TH1F*>(kap_qcd->Clone(Form("mc_tot_bin%d",ibin)));
  mc_tot->Add(kap_wjets);
  mc_tot->Add(kap_ttbar);
  mc_tot->Add(kap_other);

  float num = data_obs->GetBinContent(1);
  float den = mc_tot->GetBinContent(1);
  SF = num/den;
  if(debug){
    cout<<SF<<endl;
    cout<<"data_obs : " << data_obs->GetBinContent(1)<<" mc_tot : "<<mc_tot->GetBinContent(1)<<endl;
  }
  mc_tot->Scale(SF);
  vector<TH1F*> ret;
  ret.push_back(data_obs);
  ret.push_back(mc_tot);
  return ret;
}

TString color(TString procname){
  if(procname == "data_obs") return reset;
  else if(procname == "qcd") return yellow;
  else if(procname == "ttbar") return blue;
  else if(procname == "wjets") return green;
  else if(procname == "other") return gray;
  else if(procname == "Stop") return cyan;
  else return red;
}




