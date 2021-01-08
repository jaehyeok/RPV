//**********     Author : Chang Whan Jung     **********//
//
// This code is referred by src/make_variation_loop.cxx
// 

#include <fstream>
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
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TBox.h"
#include "TGaxis.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

struct winsize w;

void genKappaRegions(small_tree_rpv &tree, TString year, TFile *f, bool flag_kwj, TString procname);
void genKappaFactors(TFile *f, TString year);
void genKappaForTTJets(TFile *f_CRFit, float kappa[2][3][3], float kappa_unc[2][3][3], float mc_unc[2][3][3]);
vector<TH1F*> ApplyKappaFactor(TFile *f, int ibin, float kappa[2][3][3]);
int genMConly(TFile *f, bool mconly);
TString color(TString procname);

std::vector<float> morphBin={1.00,0.90,0.80};
TString temp_eval_, temp_help_;

int nbins = 18;
float mjmin = 500;
float mjmax = 1400;

bool debug = true;
bool debug_unc = true;
bool mconly = true;

float lumi = 35.9;

vector<int> bins = {0, 1, 2, 
                    3, 4, 5,  
                    6, 7, 8,
		    9, 10, 11};

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

  temp_eval_=argv[1];
  temp_help_=argv[1];

  if(argc==6){
    if(temp_eval_=="on"||temp_eval_=="morph") mconly=true;
    else if(temp_eval_=="off") mconly=false;
    mjmin = atof(argv[2]);
    mjmax = atof(argv[3]);
    year = argv[4];
    lumi = atof(argv[5]);
  }
  else if(argc==5){
    if(temp_eval_=="on"||temp_eval_=="morph") mconly=true;
    else if(temp_eval_=="off") mconly=false;
    mjmin = atof(argv[2]);
    mjmax = atof(argv[3]);
    year = argv[4];
  }
  else if(argc==2&&(temp_help_=="--help"||temp_help_=="-h")){
    cout<<"How to run this program : "<<endl;
    cout<<"./run/make_kappa [MC only mode] [MJ minimum] [MJ maximum] [year] [luminosity]" << endl;
    cout<<"Chang Whan Jung, changhwanjung95@gmail.com"<<endl;
    return 0;
  }
  else if(argc==1){
    year = argv[1];
  }
  else{
    cout<<"[ERROR] Invalid Number of Arguments!"<<endl;
    cout<<"How to run this program : "<<endl;
    cout<<"./run/make_kappa [MC only mode] [MJ minimum] [MJ maximum] [year] [luminosity]" << endl;
    cout<<"Chang Whan Jung, changhwanjung95@gmail.com"<<endl;
    return 0;
  }

  if(!(year=="2016"||year=="2017"||year=="2018"||year=="20178")) return 0;

  vector<TString> years;

  if(year=="20178"){
    years.push_back("2017");
    years.push_back("2018");
  }
  else years.push_back(year);
  ifstream chf;
  chf.open("variations/output_kappa_regions_"+year+".root");
  if(!chf) remove("variations/output_kappa_regions_"+year+".root");
  TFile *f = new TFile("variations/output_kappa_regions_"+year+".root", "recreate");

  for(auto iyear : years){

    if(argc==5||argc==1){
      if(iyear=="2016") lumi = 35.9;
      else if(iyear=="2017") lumi = 41.5;
      else if(iyear=="2018") lumi = 59.7;
    }
    cout<<argc<<endl;

    cout<<"year                         : "<< iyear    <<endl;
    cout<<"luminosity                   : "<< lumi    <<endl;
    TString temp_=mconly==true?"on":"off";
    cout<<"MConly                       : "<< temp_   <<endl;
    cout<<"MJ minimum                   : "<< mjmin   <<endl;
    cout<<"MJ maximum                   : "<< mjmax   <<endl;

    if(temp_eval_=="morph") cout<<"data_obs is morphed : { "<<morphBin.at(0)<<", "<<morphBin.at(1)<<", "<<morphBin.at(2)<<" }"<<endl;
    cout<<argc<<endl;

    TString folder_bkg = folder_year(iyear,false).at(0);
    TString folder_dat = folder_year(iyear,false).at(1);
    TString folder_sig = folder_year(iyear,false).at(2);
    TString folder_kwj = folder_year(iyear,false).at(3);

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
    //getKappa(data, iyear, f, "data_obs");
    
    vector<TString> s_rpv_m1900 = getRPVProcess(folder_sig, "rpv_m1900");
    small_tree_rpv rpv_m1900(static_cast<std::string>(s_rpv_m1900.at(0)));

    if(!(mconly)) genKappaRegions( data, iyear, f, false, "data_obs");

    genKappaRegions(  qcd, iyear, f, false,   "qcd");
    genKappaRegions(ttbar, iyear, f, false, "ttbar");
    genKappaRegions(wjets, iyear, f, false, "wjets");  
    genKappaRegions(other, iyear, f, false, "other");

    if(!(mconly)) genKappaRegions( data_kwj, iyear, f, true, "data_obs");

    genKappaRegions(  qcd_kwj, iyear, f, true,   "qcd");
    genKappaRegions(ttbar_kwj, iyear, f, true, "ttbar");
    genKappaRegions(   DY_kwj, iyear, f, true,    "DY");  
    genKappaRegions(other_kwj, iyear, f, true, "other");

    genKappaRegions(rpv_m1900, iyear, f, false, "signal_M1900");
  } 

  genMConly(f, mconly);

  f->Close();

  TFile *f_ = new TFile("variations/output_kappa_regions_"+year+".root", "read");
  genKappaFactors(f_,year); 

  f_->Close();
}

void genKappaRegions(small_tree_rpv &tree, TString year, TFile *f, bool flag_kwj, TString procname){
  ioctl(0,TIOCGWINSZ, &w);
  int cols = w.ws_col;


  vector<int> bins = {0, 1, 2, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  if(flag_kwj) bins = {3, 4, 5};

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
    if(f->Get(Form("/bin%d/%s", ibin, procname.Data()))){
      h1nominal[index] = static_cast<TH1F*>(f->Get(Form("bin%d/%s", ibin, procname.Data())));
    }
    else h1nominal[index]    = new TH1F(Form("%s_bin%i",procname.Data(),ibin),    Form("%s_bin%i",procname.Data(),ibin), MjBin+1, mjmin, mjmax);
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
	if(ibin>11) hmjmax = mjmin+(mjmax-mjmin)/3-0.001;
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

int genMConly(TFile *f, bool mconly){
  vector<int> bins_;
  if(!mconly) return 0;

  if(debug)cout<<bins.at(0)<<","<<bins.at(3)<<endl;

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
    if(ibin==3||ibin==4||ibin==5){
      wjets = static_cast<TH1F*>(f->Get(Form("/bin%d/DY",ibin)));
    }
    else wjets = static_cast<TH1F*>(f->Get(Form("/bin%d/wjets",ibin)));
    for(int i=1; i<=data_obs->GetNbinsX(); i++){
      if(temp_eval_=="morph") data_obs->SetBinContent(i, (qcd->GetBinContent(i) + ttbar->GetBinContent(i) + wjets->GetBinContent(i) + other->GetBinContent(i))*morphBin.at(i-1));
      else data_obs->SetBinContent(i, (qcd->GetBinContent(i) + ttbar->GetBinContent(i) + wjets->GetBinContent(i) + other->GetBinContent(i)));
      if(debug) cout<<"bin : " << ibin << "|| Content : " <<(qcd->GetBinContent(i) + ttbar->GetBinContent(i) + wjets->GetBinContent(i) + other->GetBinContent(i)) << "\n qcd :" << qcd->GetBinContent(i) << "\n ttbar : " << ttbar->GetBinContent(i) << "\n wjets : " << wjets->GetBinContent(i) << "\n other : " << other->GetBinContent(i) << endl;
      data_obs->SetBinError(i, TMath::Sqrt(data_obs->GetBinContent(i)));
    }
    gDirectory->cd(Form("/bin%d",ibin));
    data_obs->Write("",TObject::kOverwrite);
  }
  return 0;
}

void genKappaFactors(TFile *f, TString year){
  vector<TString> process  = {"qcd", "wjets", "ttbar"};
  vector<TString> njRegion = {"Low Njets ", "Med Njets ", "High Njets "};

  float kappa[2][3][3], kappa_unc[2][3][3], mc_unc[2][3][3];
  for(int i=0 ; i<3 ; i++ ){
    for(int j=0 ; j<3 ; j++ ){
      for(int k=0 ; k<2 ; k++ ){
        kappa[k][i][j] = 1;
        kappa_unc[k][i][j] = 0;
        mc_unc[k][i][j] = 0;
      }
    }
  }

  f->cd();

  for(auto ibin : bins){
    if(ibin>5) continue;
    int ind_ibin    = ibin%3;        // ind_ibin = 0 : Low Njets, ind_ibin = 1 : Med Njets, ind_ibin = 2 : High Njets
    int ind_proc    = int(ibin/3);   // ind_proc = 0 : qcd, ind_proc = 1 : wjets, ind_proc = 2 : ttbar
    float ratio[3];
    vector<TH1F*> ret;
    TH1F *mc_kap, *ratio_dmc, *data_obs;
    ret = ApplyKappaFactor(f, ibin, kappa);
    data_obs = ret.at(0);
    mc_kap   = ret.at(1);

    ratio_dmc = static_cast<TH1F*>(data_obs->Clone("ratio_dmc"));
    ratio_dmc->Divide(mc_kap);
    for(int i=0 ; i<3 ; i++){
      ratio[i] = ratio_dmc->GetBinContent(i+1);
      cout<<"ratio "<<i<<" : "<<ratio[i]<<endl;
    }
    kappa[0][ind_ibin][ind_proc] = ratio[1]/ratio[0];
    kappa[1][ind_ibin][ind_proc] = ratio[2]/ratio[0];
    cout<<"ind_bin : "<<ind_ibin<<endl;
    cout<<"ind_iproc : "<<ind_ibin<<endl;

    TH1F *mc_kap_ = static_cast<TH1F*>(mc_kap->Clone("mc_kap_"));
    for(int j=1 ; j<3 ; j++){
      float BinCont = mc_kap_->GetBinContent(j+1);
      mc_kap_->SetBinContent(j+1, BinCont*kappa[j-1][ind_ibin][ind_proc]);
    }
    for(int i=1 ; i<3 ; i++){
      float unc_diff(0), unc_stat(0), unc_mc(0), temp_mc_(0);
      temp_mc_ = mc_kap_->GetBinContent(i+1);
      unc_diff = abs(data_obs->GetBinContent(i+1)-mc_kap_->GetBinContent(i+1));
      if(debug_unc){
        cout<<"Data's " << i+1 << "th Bin      : " <<data_obs->GetBinError(i+1)/temp_mc_<<endl;
        cout<<"MC's " << i+1 << "th Bin        : " << mc_kap_->GetBinError(i+1)/temp_mc_<<endl;
        cout<<"Data's " << i+1 << "th Bin      : " <<data_obs->GetBinContent(i+1)<<endl;
        cout<<"MC's " << i+1 << "th Bin        : " << mc_kap_->GetBinContent(i+1)<<endl;
        cout<<"kappa uncertainty   : "<<unc_diff<<endl;
        cout<<"temp_mc_          : "<<temp_mc_<<endl;
      }
      unc_stat = data_obs->GetBinError(i+1);
      unc_mc   = mc_kap_->GetBinError(i+1);
      kappa_unc[i-1][ind_ibin][ind_proc] = TMath::Sqrt(unc_diff*unc_diff+unc_stat*unc_stat+unc_mc*unc_mc)/temp_mc_; 
      mc_unc[i-1][ind_ibin][ind_proc] = unc_mc/temp_mc_;
    }
  }
 TH1F *hist_kappa1 = new TH1F("hist_kappa1", "hist_kappa1", 9, 0, 9);
  TH1F *hist_kappa1_mc = new TH1F("hist_kappa1_mc", "hist_kappa1_mc", 9, 0, 9);
  TH1F *hist_kappa2 = new TH1F("hist_kappa2", "hist_kappa2", 9, 0, 9);
  TH1F *hist_kappa2_mc = new TH1F("hist_kappa2_mc", "hist_kappa2_mc", 9, 0, 9);
  for(int ibin=0 ; ibin<3 ; ibin++){
    for(int jproc=0 ; jproc<3 ; jproc++){
      hist_kappa1->SetBinContent((ibin+1)+jproc*3,kappa[0][ibin][jproc]);
      hist_kappa1->SetBinError((ibin+1)+jproc*3,kappa_unc[0][ibin][jproc]);
      hist_kappa1->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
      hist_kappa1_mc->SetBinContent((ibin+1)+jproc*3,kappa[0][ibin][jproc]);
      hist_kappa1_mc->SetBinError((ibin+1)+jproc*3,mc_unc[0][ibin][jproc]);
      hist_kappa2->SetBinContent((ibin+1)+jproc*3,kappa[1][ibin][jproc]);
      hist_kappa2->SetBinError((ibin+1)+jproc*3,kappa_unc[1][ibin][jproc]);
      hist_kappa2->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
      hist_kappa2_mc->SetBinContent((ibin+1)+jproc*3,kappa[1][ibin][jproc]);
      hist_kappa2_mc->SetBinError((ibin+1)+jproc*3,mc_unc[1][ibin][jproc]);
    }
  }
  hist_kappa1->SetStats(0);
  hist_kappa1->SetMaximum(2);
  hist_kappa1->SetMinimum(-2);
  hist_kappa1->SetTitle("kappa1");
  hist_kappa2->SetStats(0);
  hist_kappa2->SetMaximum(2);
  hist_kappa2->SetMinimum(-2);
  hist_kappa2->SetTitle("kappa2");

  TFile *g = new TFile("data/result_kappa_"+year+".root","recreate");
  g->cd();
  hist_kappa1->Write();
  hist_kappa2->Write();
  g->Close();

  TString str_mconly("off");
  if(mconly) str_mconly="on";

  system("cp scripts/make_CRFit.sh .");
  system("cp scripts/repack.C .");
  system(Form("./make_CRFit.sh %s %s",year.Data(),str_mconly.Data()));
  system("rm make_CRFit.sh");
  system("rm repack.C");

  TFile *f_CRFit = new TFile("mlfit_cr_CRFit_"+year+".root","read");
  genKappaForTTJets(f_CRFit, kappa, kappa_unc, mc_unc);
  for(int ibin=0 ; ibin<3 ; ibin++){
    for(int jproc=0 ; jproc<3 ; jproc++){
      cout<<kappa_unc[0][ibin][jproc]<<endl;
      hist_kappa1->SetBinContent((ibin+1)+jproc*3,kappa[0][ibin][jproc]);
      hist_kappa1->SetBinError((ibin+1)+jproc*3,kappa_unc[0][ibin][jproc]);
      hist_kappa1->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
      hist_kappa1_mc->SetBinContent((ibin+1)+jproc*3,kappa[0][ibin][jproc]);
      hist_kappa1_mc->SetBinError((ibin+1)+jproc*3,mc_unc[0][ibin][jproc]);
      hist_kappa2->SetBinContent((ibin+1)+jproc*3,kappa[1][ibin][jproc]);
      hist_kappa2->SetBinError((ibin+1)+jproc*3,kappa_unc[1][ibin][jproc]);
      hist_kappa2->GetXaxis()->SetBinLabel((ibin+1)+jproc*3,njRegion.at(ibin)+process.at(jproc));
      hist_kappa2_mc->SetBinContent((ibin+1)+jproc*3,kappa[1][ibin][jproc]);
      hist_kappa2_mc->SetBinError((ibin+1)+jproc*3,mc_unc[1][ibin][jproc]);
    }
  }
  hist_kappa1->SetStats(0);
  hist_kappa1->SetMaximum(2);
  hist_kappa1->SetMinimum(-2);
  hist_kappa1->SetTitle("kappa1");
  hist_kappa2->SetStats(0);
  hist_kappa2->SetMaximum(2);
  hist_kappa2->SetMinimum(-2);
  hist_kappa2->SetTitle("kappa2");

  TFile *g_ = new TFile("data/result_kappa_"+year+".root","recreate");
  g_->cd();
  hist_kappa1->Write();
  hist_kappa2->Write();
  g_->Close();

  if(debug){
    for(int ibin=0 ; ibin<3 ; ibin++){
      for(int jproc=0 ; jproc<3 ; jproc++){
        cout << "kappa 1 in NJets " << ibin<<" process " <<jproc << " : " << kappa[0][ibin][jproc] << endl;
        cout << "kappa 2 in NJets " << ibin<<" process " <<jproc << " : " << kappa[1][ibin][jproc] << endl;
      }
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
 

  TCanvas *c = new TCanvas("c","c",1600,1600);
  c->Divide(1,2);
  c->cd(1);
  TBox *b1 = new TBox(0.,-1.99, 3., 1.99*c->GetUymax());
  b1->SetFillColor(kYellow-9);
  TBox *b2 = new TBox(3.,-1.99, 6., 1.99*c->GetUymax());
  b2->SetFillColor(kGreen-6);
  TBox *b3 = new TBox(6.,-1.99, 8.99, 1.99*c->GetUymax());
  b3->SetFillColor(kBlue-7);
  hist_kappa1->Draw("e0 x0");
  TGaxis *ax1 = static_cast<TGaxis*>(hist_kappa1->GetXaxis()->Clone());
  TGaxis *ay1 = static_cast<TGaxis*>(hist_kappa1->GetYaxis()->Clone());
  //b1->SetFillStyle(3254);
  //b2->SetFillStyle(3254);
  //b3->SetFillStyle(3254);
  b1->Draw("same");
  b2->Draw("same");
  b3->Draw("same");
  hist_kappa1->SetFillStyle(4000);
  hist_kappa1->Draw("same e0 x0");
  hist_kappa1_mc->SetFillStyle(3254);
  hist_kappa1_mc->SetFillColor(kRed);
  hist_kappa1_mc->SetLineWidth(2);
  hist_kappa1_mc->SetLineColor(kRed);
  hist_kappa1_mc->SetMarkerStyle(40);
  hist_kappa1_mc->SetMarkerSize(1.2);
  hist_kappa1_mc->Draw("same x0 e0");
  ax1->Draw("same");
  ay1->Draw("same");
  c->cd(1)->RedrawAxis("F");
  c->cd(1)->Modified();
  c->cd(1)->Update();
  c->cd(2);
  TBox *b4 = new TBox(0.,-1.99, 3., 1.99*c->GetUymax());
  b4->SetFillColor(kYellow-9);
  TBox *b5 = new TBox(3.,-1.99, 6., 1.99*c->GetUymax());
  b5->SetFillColor(kGreen-6);
  TBox *b6 = new TBox(6.,-1.99, 8.99, 1.99*c->GetUymax());
  b6->SetFillColor(kBlue-7);
  hist_kappa2->Draw("e0 x0");
  TGaxis *ax2 = static_cast<TGaxis*>(hist_kappa2->GetXaxis()->Clone());
  TGaxis *ay2 = static_cast<TGaxis*>(hist_kappa2->GetYaxis()->Clone());
  //b4->SetFillStyle(3254);
  //b5->SetFillStyle(3254);
  //b6->SetFillStyle(3254);
  b4->Draw("same");
  b5->Draw("same");
  b6->Draw("same");
  hist_kappa1->SetFillStyle(4000);
  hist_kappa2->Draw("same e0 x0");
  hist_kappa2_mc->SetFillStyle(3254);
  hist_kappa2_mc->SetFillColor(kRed);
  hist_kappa2_mc->SetLineWidth(2);
  hist_kappa2_mc->SetLineColor(kRed);
  hist_kappa2_mc->SetMarkerStyle(40);
  hist_kappa2_mc->SetMarkerSize(1.2);
  hist_kappa2_mc->Draw("same x0 e0");
  ax2->Draw("same"); 
  ay2->Draw("same"); 
  c->cd(2)->RedrawAxis("F");
  c->cd(2)->Modified();
  c->cd(2)->Update();
  c->Print("kappa_result_"+year+".pdf");
}

void genKappaForTTJets(TFile *f_CRFit, float kappa[2][3][3], float kappa_unc[2][3][3], float mc_unc[2][3][3]){
  TH1F *qcd, *wjets, *ttbar, *other, *bkg;
  TGraphAsymmErrors *data;
  vector<int> bins = {25, 26, 27};
  for(auto ibin : bins){
    data = static_cast<TGraphAsymmErrors*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/data",ibin)));
    auto nPoints = data->GetN();
    TH1F *dat = new TH1F("data","data",3,mjmin,mjmax);
    for(int i=0 ; i < nPoints ; ++i){
      double x,y;
      data->GetPoint(i,x,y);
      dat->SetBinContent(i+1,y);
      dat->SetBinError(i+1,TMath::Sqrt(y));
    }
    qcd = static_cast<TH1F*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/qcd",ibin)));
    wjets = static_cast<TH1F*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/wjets",ibin)));
    ttbar = static_cast<TH1F*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/ttbar",ibin)));
    other = static_cast<TH1F*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/other",ibin)));
    bkg = static_cast<TH1F*>(f_CRFit->Get(Form("shapes_fit_b/bin%d/total_background",ibin)));
    float datbc = dat->GetBinContent(1);
    float bkgbc = bkg->GetBinContent(1);
    float SF = datbc/bkgbc;
    qcd->Scale(SF);
    wjets->Scale(SF);
    other->Scale(SF);
    dat->Add(qcd,-1);
    dat->Add(wjets,-1);
    dat->Add(other,-1);
    float ratio[3];
    for(int j=0 ; j<3 ; j++) ratio[j] = dat->GetBinContent(j+1)/ttbar->GetBinContent(j+1);
    int ind_ibin = (ibin+2)%3;
    kappa[0][ind_ibin][2] = ratio[1]/ratio[0];
    kappa[1][ind_ibin][2] = ratio[2]/ratio[0];
    for(int i=1 ; i<3 ; i++){
      float unc_diff(0), unc_stat(0), unc_mc(0), temp_mc_(0);
      temp_mc_ = ttbar->GetBinContent(i+1);
      unc_diff = abs(dat->GetBinContent(i+1)-ttbar->GetBinContent(i+1));
      unc_stat = dat->GetBinError(i+1);
      unc_mc   = ttbar->GetBinError(i+1);
      kappa_unc[i-1][ind_ibin][2] = TMath::Sqrt(unc_diff*unc_diff+unc_stat*unc_stat+unc_mc*unc_mc)/temp_mc_; 
      mc_unc[i-1][ind_ibin][2] = unc_mc/temp_mc_;
    }
  }
}

vector<TH1F*> ApplyKappaFactor(TFile *f, int ibin, float kappa[2][3][3]){
  int index       = find(bins.begin(), bins.end(), ibin) - bins.begin();
  int ind_ibin    = ibin%3;        // ind_ibin = 0 : Low Njets, ind_ibin = 1 : Med Njets, ind_ibin = 2 : High Njets
  int ind_proc    = int(ibin/3);   // ind_proc = 0 : qcd, ind_proc = 1 : wjets, ind_proc = 2 : ttbar
  TString procname;

  if(ind_proc==0) procname = "qcd";
  if(ind_proc==1) procname = "DY";
  if(ind_proc==2) procname = "ttbar";

  vector<TString> process = {"qcd","wjets","ttbar","other"};
  vector<TString> proc_other ={};

  for(auto iproc : process){
    if(iproc==procname) continue;
    else if(procname=="DY"&&iproc=="wjets") continue;
    else proc_other.push_back(iproc);
  }

  float SF(1);
  gDirectory->cd("/");
  TH1F *data_obs  = static_cast<TH1F*>(f->Get(Form("/bin%d/data_obs", ibin)));
  TH1F *mc_kap    = static_cast<TH1F*>(f->Get(Form("/bin%d/%s", ibin, procname.Data())));

  TH1F *mc_tot    = static_cast<TH1F*>(mc_kap->Clone("mc_tot"));
  TH1F *mc_other[3], *mc_other_kap[3];
  int temp_ind;
  for(int i=0 ; i<3 ; i++){
    TString iproc = proc_other.at(i);
    mc_other[i] = static_cast<TH1F*>(f->Get(Form("/bin%d/%s", ibin, iproc.Data())));
    mc_other_kap[i] = static_cast<TH1F*>(f->Get(Form("/bin%d/%s", ibin, iproc.Data())));
    mc_tot->Add(mc_other[i]);
    if(iproc=="qcd") temp_ind = 0;
    if(iproc=="wjets") temp_ind = 1;
    if(iproc=="ttbar") temp_ind = 2;
    if(iproc=="other") continue;
    if(procname == "ttbar"){
      for(int j=1 ; j<3 ; j++){
        float BinCont = mc_other[i]->GetBinContent(j+1);
        mc_other_kap[i]->SetBinContent(j+1, BinCont*kappa[j-1][ind_ibin][temp_ind]);
      }
    }
  }

  float num = data_obs->GetBinContent(1);
  float den = mc_tot->GetBinContent(1);
  SF = num/den;
  if(debug){
    cout<<SF<<endl;
    cout<<"data_obs : " << data_obs->GetBinContent(1)<<" mc_tot : "<<mc_tot->GetBinContent(1)<<endl;
  }
  for(int i=0 ; i<3 ; i++){
    mc_other_kap[i]->Scale(SF);
    data_obs->Add(mc_other_kap[i],-1);
  }
  mc_kap->Scale(SF);
  vector<TH1F*> ret;
  ret.push_back(data_obs);
  ret.push_back(mc_kap);
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




