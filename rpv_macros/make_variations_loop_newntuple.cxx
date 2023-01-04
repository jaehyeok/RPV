#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "TROOT.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TROOT.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

struct winsize w;

void getSyst(small_tree_rpv &trees, TString variations, TString year, TFile *f, TString procname);
double addError(double error, double added_error);
double divideErrors(double x, double y, double dx, double dy);
TString color(TString procname);
//void fillTH1F(TH1F* &h1, double var, double weight);

TString str_year("");

float mjmin = 500;
float mjmax = 1400;
float binsize = 300;
bool nl0shape = true;

float lumi = 1.; // fb-1
const int nbins = 52;
int w_pdf_index = 0;

TString red = "\033[0;31m";
TString green = "\033[1;32m";
TString blue = "\033[1;34m";
TString yellow = "\033[1;33m";
TString gray = "\033[0;90m";
TString cyan = "\033[0;36m";
TString reset = "\033[0m";

int main(int argc, char *argv[])
{
  int nthreads=16;
  ROOT::EnableImplicitMT(nthreads);
  gErrorIgnoreLevel=kError+1;
  TH1::SetDefaultSumw2();

  ioctl(0,TIOCGWINSZ, &w);
  int cols = w.ws_col;

  TString year;
 //cout << cols << endl;
  cout<<argc<<endl;
  //
  TString test = argv[1];
  TString variations = "nominal";
  TString onoff = "on";
  if(argc<2) {
    cout << "[Error] Not Enough Arguments! argument \"--help\" may help you" << endl; 
    return 1;
  }
  else if(test == "--help" or argc<3){
    cout<< "./run/make_variations_loop_newntuple.exe [Systematics] [MJ minimum] [MJ maximum] [year]" << endl;
    cout<< "./run/make_variations_loop_newntuple.exe [Systematics] [MJ minimum] [MJ maximum] [year] [luminosity]" << endl;
    cout<< "./run/make_variations_loop_newntuple.exe [Systematics] [0 Lepton Shape on/off] [MJ minimum] [MJ maximum] [year] [luminosity]" << endl;
    return 1;
  }
  else if(argc<3) 
  { 
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << "Luminosity        : " << lumi << "fb-1" << endl;
    variations = argv[1];  
    if(variations=="w_pdf") 
    { 
      cout << "[Error] Provide an index for w_pdf:" << endl;
      return 1;
    }
    else 
    {
      if(onoff=="off") nl0shape = false;
      cout << "Running variation : " << variations << endl;
    }
  }
  else if(argc<4)
  {
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << "Luminosity        : " << lumi << "fb-1" << endl;
    variations = argv[1];  
    if(variations=="w_pdf")
    {
      w_pdf_index = atoi(argv[2]);  
      cout << "Running variation : " << variations << endl;
      cout << " with w_pdf index " << w_pdf_index; 
      cout << endl; 
    }
    else
    {
      // onoff=argv[2];
      if(onoff=="off") nl0shape = false; 
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off");
      cout << endl;
    }
  }
  else if(argc==5)
  {
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    variations = argv[1];  
    if(variations=="w_pdf")
    {
      w_pdf_index = atoi(argv[2]);  
      cout << "Running variation : " << variations << endl;
      cout << " with w_pdf index " << w_pdf_index; 
      cout << endl; 
    }
    else
    {
      //      onoff=argv[2];
      mjmin=atof(argv[2]);
      mjmax=atof(argv[3]);
      year =argv[4];
      cout<<year<<endl;
      if(year=="2016") lumi = 36.3;
      else if(year=="2017") lumi = 41.5;
      else if(year=="2018") lumi = 59.8;
      cout << "Luminosity        : " << lumi << "fb-1" << endl;
      if(onoff=="off") nl0shape = false; 
      cout << "There are only 5 arguments! 0 Lepton shape is entered as on..." << endl;
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off") << endl;
      //	cout << "MJ minimum        : " << mjmin << endl;
      //	cout << "MJ maximum        : " << mjmax << endl;
      binsize = (mjmax-mjmin)/3;
      cout << "Bins distribution : [ " << mjmin << ", " << mjmin + binsize << ", " << mjmin + 2*binsize << " ]" << endl;
    } 
  }
  else if(argc==6)
  {
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    variations = argv[1]; 
    TString temp = argv[2]; 
    if(variations=="w_pdf")
    {
      w_pdf_index = atoi(argv[2]);  
      cout << "Running variation : " << variations << endl;
      cout << " with w_pdf index " << w_pdf_index; 
      cout << endl; 
    }
    else if(temp=="on"||temp=="off"){
      onoff=argv[2];
      mjmin=atof(argv[3]);
      mjmax=atof(argv[4]);
      year = argv[5];
      if(year=="2016") lumi = 36.3;
      else if(year=="2017") lumi = 41.5;
      else if(year=="2018") lumi = 59.8;
      cout << "Luminosity        : " << lumi << "fb-1" << endl;
      if(onoff=="off") nl0shape = false; 
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off") << endl;
      //	cout << "MJ minimum        : " << mjmin << endl;
      //	cout << "MJ maximum        : " << mjmax << endl;
      binsize = (mjmax-mjmin)/3;
      cout << "Bins distribution : [ " << mjmin << ", " << mjmin + binsize << ", " << mjmin + 2*binsize << " ]" << endl;
    }
    else
    {
      //      onoff=argv[2];
      mjmin=atof(argv[2]);
      mjmax=atof(argv[3]);
      year =argv[4];
      lumi =atof(argv[5]);
      cout << "Luminosity        : " << lumi << "fb-1" << endl;
      if(onoff=="off") nl0shape = false; 
      cout << "There are only 6 arguments! 0 Lepton shape is entered as on..." << endl;
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off") << endl;
      //	cout << "MJ minimum        : " << mjmin << endl;
      //	cout << "MJ maximum        : " << mjmax << endl;
      binsize = (mjmax-mjmin)/3;
      cout << "Bins distribution : [ " << mjmin << ", " << mjmin + binsize << ", " << mjmin + 2*binsize << " ]" << endl;
    } 
  }
  else 
  {
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    variations = argv[1];  
    TString temp = argv[6];
    if(variations=="w_pdf")
    {
      w_pdf_index = atoi(argv[2]);  
      cout << "Running variation : " << variations << endl;
      cout << " with w_pdf index " << w_pdf_index; 
      cout << endl; 
    }
    else if(temp=="20178"){
      onoff=argv[2];
      mjmin=atof(argv[3]);
      mjmax=atof(argv[4]);
      year = argv[5];
      str_year = argv[6];
      if(year=="2016") lumi = 36.3;
      else if(year=="2017") lumi = 41.5;
      else if(year=="2018") lumi = 59.8;
      cout << "Luminosity        : " << lumi << "fb-1" << endl;
      if(onoff=="off") nl0shape = false; 
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off") << endl;
      //	cout << "MJ minimum        : " << mjmin << endl;
      //	cout << "MJ maximum        : " << mjmax << endl;
      binsize = (mjmax-mjmin)/3;
      cout << "Bins distribution : [ " << mjmin << ", " << mjmin + binsize << ", " << mjmin + 2*binsize << " ]" << endl;
    }
    else
    {
      onoff=argv[2];
      mjmin=atof(argv[3]);
      mjmax=atof(argv[4]);
      year = argv[5];
      lumi =atof(argv[6]);
      cout << "Luminosity        : " << lumi << "fb-1" << endl;
      if(onoff=="off") nl0shape = false; 
      cout << "Running variation : " << variations << endl;
      cout << "0 Lepton shape    : " << (nl0shape?"on":"off") << endl;
      //	cout << "MJ minimum        : " << mjmin << endl;
      //	cout << "MJ maximum        : " << mjmax << endl;
      binsize = (mjmax-mjmin)/3;
      cout << "Bins distribution : [ " << mjmin << ", " << mjmin + binsize << ", " << mjmin + 2*binsize << " ]" << endl;
    }
  }
  // Define samples
  //TString folder_bkg = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_11_07/skim_rpvfit/";
  //TString folder_sig = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/processed/";

  /*TString folder_bkg = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/";
    TString folder_dat = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/";
    TString folder_sig = "/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/merged_norm/";// */

  //  TString folder_bkg = "/net/cms26/cms26r0/jaehyeokyoo/rpv_ku_babies/2016v6/2020_05_11/merged_rpvfitnbge0/";
  //  TString folder_dat = "/net/cms26/cms26r0/jaehyeokyoo/rpv_ku_babies/2016v6/2020_05_11/merged_rpvfitnbge0/";
  //  TString folder_sig = "/net/cms26/cms26r0/jaehyeokyoo/rpv_ku_babies/2016v6/2020_05_11/merged_rpvfitnbge0/";

  TString folder_bkg = folder_year(year,false).at(0);
  TString folder_dat = folder_year(year,false).at(1);
  TString folder_sig = folder_year(year,false).at(2);


  vector<TString> s_jetht = getRPVProcess(folder_dat,"data");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");

  //rpv_signal
  vector<TString> s_rpv_m1000 = getRPVProcess(folder_sig,"rpv_m1000");
  vector<TString> s_rpv_m1100 = getRPVProcess(folder_sig,"rpv_m1100");
  vector<TString> s_rpv_m1200 = getRPVProcess(folder_sig,"rpv_m1200");
  vector<TString> s_rpv_m1300 = getRPVProcess(folder_sig,"rpv_m1300");
  vector<TString> s_rpv_m1400 = getRPVProcess(folder_sig,"rpv_m1400");
  vector<TString> s_rpv_m1500 = getRPVProcess(folder_sig,"rpv_m1500");
  vector<TString> s_rpv_m1600 = getRPVProcess(folder_sig,"rpv_m1600");
  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");
  vector<TString> s_rpv_m1800 = getRPVProcess(folder_sig,"rpv_m1800");
  vector<TString> s_rpv_m1900 = getRPVProcess(folder_sig,"rpv_m1900");
  vector<TString> s_rpv_m2000 = getRPVProcess(folder_sig,"rpv_m2000");
  vector<TString> s_rpv_m2100 = getRPVProcess(folder_sig,"rpv_m2100");
  vector<TString> s_rpv_m2200 = getRPVProcess(folder_sig,"rpv_m2200");// */

  //GluinoToNeutralino
  /*vector<TString> s_GN_1200 = getRPVProcess(folder_sig,"gn_1200");
  vector<TString> s_GN_1600 = getRPVProcess(folder_sig,"gn_1600");
  vector<TString> s_GN_2400 = getRPVProcess(folder_sig,"gn_2400");
  vector<TString> s_GN_3000 = getRPVProcess(folder_sig,"gn_3000");// */

  //StealthSHH
  /*vector<TString> s_mStop_300 = getRPVProcess(folder_sig,"mStop_300");  
  vector<TString> s_mStop_350 = getRPVProcess(folder_sig,"mStop_350");  
  vector<TString> s_mStop_400 = getRPVProcess(folder_sig,"mStop_400");  
  vector<TString> s_mStop_450 = getRPVProcess(folder_sig,"mStop_450");  
  vector<TString> s_mStop_500 = getRPVProcess(folder_sig,"mStop_500");  
  vector<TString> s_mStop_550 = getRPVProcess(folder_sig,"mStop_550");
  vector<TString> s_mStop_600 = getRPVProcess(folder_sig,"mStop_600");
  vector<TString> s_mStop_650 = getRPVProcess(folder_sig,"mStop_650");  
  vector<TString> s_mStop_700 = getRPVProcess(folder_sig,"mStop_700");  
  vector<TString> s_mStop_750 = getRPVProcess(folder_sig,"mStop_750");
  vector<TString> s_mStop_800 = getRPVProcess(folder_sig,"mStop_800");  
  vector<TString> s_mStop_850 = getRPVProcess(folder_sig,"mStop_850"); 
  vector<TString> s_mStop_900 = getRPVProcess(folder_sig,"mStop_900");
  vector<TString> s_mStop_950 = getRPVProcess(folder_sig,"mStop_950");  
  vector<TString> s_mStop_1000 = getRPVProcess(folder_sig,"mStop_1000");  
  vector<TString> s_mStop_1050 = getRPVProcess(folder_sig,"mStop_1050");  
  vector<TString> s_mStop_1100 = getRPVProcess(folder_sig,"mStop_1100");
  vector<TString> s_mStop_1150 = getRPVProcess(folder_sig,"mStop_1150");
  vector<TString> s_mStop_1200 = getRPVProcess(folder_sig,"mStop_1200");
  vector<TString> s_mStop_1250 = getRPVProcess(folder_sig,"mStop_1250");
  vector<TString> s_mStop_1300 = getRPVProcess(folder_sig,"mStop_1300");
  vector<TString> s_mStop_1350 = getRPVProcess(folder_sig,"mStop_1350");
  vector<TString> s_mStop_1400 = getRPVProcess(folder_sig,"mStop_1400");// */

  small_tree_rpv data((static_cast<std::string>(s_jetht.at(0))));

  // qcd ttbar wjets other 750 1000 1100 1200 1300 1400 1500
  small_tree_rpv qcd((static_cast<std::string>(s_qcd.at(0))));
  for(unsigned int iqcd=1; iqcd<s_qcd.size(); iqcd++) qcd.Add((static_cast<std::string>(s_qcd.at(iqcd))));
  small_tree_rpv ttbar((static_cast<std::string>(s_tt.at(0))));
  for(unsigned int ittbar=1; ittbar<s_tt.size(); ittbar++) ttbar.Add((static_cast<std::string>(s_tt.at(ittbar))));
  small_tree_rpv wjets((static_cast<std::string>(s_wjets.at(0))));
  for(unsigned int iwjets=1; iwjets<s_wjets.size(); iwjets++) wjets.Add((static_cast<std::string>(s_wjets.at(iwjets))));
  small_tree_rpv other((static_cast<std::string>(s_other.at(0))));
  for(unsigned int iother=1; iother<s_other.size(); iother++) other.Add((static_cast<std::string>(s_other.at(iother))));

  // rpv_signal
  small_tree_rpv rpv_m1000((static_cast<std::string>(s_rpv_m1000.at(0))));
  small_tree_rpv rpv_m1100((static_cast<std::string>(s_rpv_m1100.at(0))));
  small_tree_rpv rpv_m1200((static_cast<std::string>(s_rpv_m1200.at(0))));
  small_tree_rpv rpv_m1300((static_cast<std::string>(s_rpv_m1300.at(0))));
  small_tree_rpv rpv_m1400((static_cast<std::string>(s_rpv_m1400.at(0))));
  small_tree_rpv rpv_m1500((static_cast<std::string>(s_rpv_m1500.at(0))));
  small_tree_rpv rpv_m1600((static_cast<std::string>(s_rpv_m1600.at(0))));
  small_tree_rpv rpv_m1700((static_cast<std::string>(s_rpv_m1700.at(0))));
  small_tree_rpv rpv_m1800((static_cast<std::string>(s_rpv_m1800.at(0))));
  small_tree_rpv rpv_m1900((static_cast<std::string>(s_rpv_m1900.at(0))));
  small_tree_rpv rpv_m2000((static_cast<std::string>(s_rpv_m2000.at(0))));
  small_tree_rpv rpv_m2100((static_cast<std::string>(s_rpv_m2100.at(0))));
  small_tree_rpv rpv_m2200((static_cast<std::string>(s_rpv_m2200.at(0))));// */

  //GluinoToNeutralino
  /*small_tree_rpv gn_1200((static_cast<std::string>(s_GN_1200.at(0))));
  small_tree_rpv gn_1600((static_cast<std::string>(s_GN_1600.at(0))));
  small_tree_rpv gn_2400((static_cast<std::string>(s_GN_2400.at(0))));
  small_tree_rpv gn_3000((static_cast<std::string>(s_GN_3000.at(0))));// */

  // Stealth SUSY Signal
  /*small_tree_rpv mStop_300((static_cast<std::string>(s_mStop_300.at(0))));
  small_tree_rpv mStop_350((static_cast<std::string>(s_mStop_350.at(0))));
  small_tree_rpv mStop_400((static_cast<std::string>(s_mStop_400.at(0))));
  small_tree_rpv mStop_450((static_cast<std::string>(s_mStop_450.at(0))));
  small_tree_rpv mStop_500((static_cast<std::string>(s_mStop_500.at(0))));
  small_tree_rpv mStop_550((static_cast<std::string>(s_mStop_550.at(0))));
  small_tree_rpv mStop_600((static_cast<std::string>(s_mStop_600.at(0))));
  small_tree_rpv mStop_650((static_cast<std::string>(s_mStop_650.at(0))));
  small_tree_rpv mStop_700((static_cast<std::string>(s_mStop_700.at(0))));
  small_tree_rpv mStop_750((static_cast<std::string>(s_mStop_750.at(0))));
  small_tree_rpv mStop_800((static_cast<std::string>(s_mStop_800.at(0))));
  small_tree_rpv mStop_850((static_cast<std::string>(s_mStop_850.at(0))));
  small_tree_rpv mStop_900((static_cast<std::string>(s_mStop_900.at(0))));
  small_tree_rpv mStop_950((static_cast<std::string>(s_mStop_950.at(0))));
  small_tree_rpv mStop_1000((static_cast<std::string>(s_mStop_1000.at(0))));
  small_tree_rpv mStop_1050((static_cast<std::string>(s_mStop_1050.at(0))));
  small_tree_rpv mStop_1100((static_cast<std::string>(s_mStop_1100.at(0))));
  small_tree_rpv mStop_1150((static_cast<std::string>(s_mStop_1150.at(0))));
  small_tree_rpv mStop_1200((static_cast<std::string>(s_mStop_1200.at(0))));
  small_tree_rpv mStop_1250((static_cast<std::string>(s_mStop_1250.at(0))));
  small_tree_rpv mStop_1300((static_cast<std::string>(s_mStop_1300.at(0))));
  small_tree_rpv mStop_1350((static_cast<std::string>(s_mStop_1350.at(0))));
  small_tree_rpv mStop_1400((static_cast<std::string>(s_mStop_1400.at(0))));// */

  // open output root file
  TString shape = "_nl0shape";
  TString temp = argv[2];
  if(nl0shape == false) shape = "";
  TString output_filename = Form("variations/output_%s_newnt%s_%s.root", variations.Data(), shape.Data(), year.Data());
  cout<<str_year<<endl;
  if(argc==7&&str_year!="") output_filename = Form("variations/output_%s_newnt%s_%s_%s.root",variations.Data(), shape.Data(), year.Data(), str_year.Data());
  else if(argc==7) output_filename = Form("variations/output_%s_newnt%s_%s_%.0f.root",variations.Data(), shape.Data(), year.Data(), lumi);
  TFile *f = new TFile(output_filename, "recreate");

  // Depending on the process, turn on/off variation

  // data
  if(variations=="nominal") getSyst(data,  variations, year, f, "data_obs");

  // loop over a tree and get up/dawn shapes for all bins at once 
  getSyst(qcd,       variations, year, f, "qcd");
  getSyst(ttbar,     variations, year, f, "ttbar");
  getSyst(wjets,     variations, year, f, "wjets");
  getSyst(other,     variations, year, f, "other");

  //rpv_signal
  getSyst(rpv_m1000, variations, year, f, "signal_M1000");
  getSyst(rpv_m1100, variations, year, f, "signal_M1100");
  getSyst(rpv_m1200, variations, year, f, "signal_M1200");
  getSyst(rpv_m1300, variations, year, f, "signal_M1300");
  getSyst(rpv_m1400, variations, year, f, "signal_M1400");
  getSyst(rpv_m1500, variations, year, f, "signal_M1500");
  getSyst(rpv_m1600, variations, year, f, "signal_M1600");
  getSyst(rpv_m1700, variations, year, f, "signal_M1700");
  getSyst(rpv_m1800, variations, year, f, "signal_M1800");
  getSyst(rpv_m1900, variations, year, f, "signal_M1900");
  getSyst(rpv_m2000, variations, year, f, "signal_M2000");
  getSyst(rpv_m2100, variations, year, f, "signal_M2100");
  getSyst(rpv_m2200, variations, year, f, "signal_M2200");// */

  //GluinoToNeutralino
  /*getSyst(gn_1200, variations, year, f, "signal_M1200");
  getSyst(gn_1600, variations, year, f, "signal_M1600");
  getSyst(gn_2400, variations, year, f, "signal_M2400");
  getSyst(gn_3000, variations, year, f, "signal_M3000");// */

  //StealthSHH
  /*getSyst(mStop_300, variations, year, f, "Stop_M300");
  getSyst(mStop_350, variations, year, f, "Stop_M350");
  getSyst(mStop_400, variations, year, f, "Stop_M400");
  getSyst(mStop_450, variations, year, f, "Stop_M450");
  getSyst(mStop_500, variations, year, f, "Stop_M500");
  getSyst(mStop_550, variations, year, f, "Stop_M550");
  getSyst(mStop_600, variations, year, f, "Stop_M600");
  getSyst(mStop_650, variations, year, f, "Stop_M650");
  getSyst(mStop_700, variations, year, f, "Stop_M700");
  getSyst(mStop_750, variations, year, f, "Stop_M750");
  getSyst(mStop_800, variations, year, f, "Stop_M800");
  getSyst(mStop_850, variations, year, f, "Stop_M850");
  getSyst(mStop_900, variations, year, f, "Stop_M900");
  getSyst(mStop_950, variations, year, f, "Stop_M950");
  getSyst(mStop_1000, variations, year, f, "Stop_M1000");
  getSyst(mStop_1050, variations, year, f, "Stop_M1050");
  getSyst(mStop_1100, variations, year, f, "Stop_M1100");
  getSyst(mStop_1150, variations, year, f, "Stop_M1150");
  getSyst(mStop_1200, variations, year, f, "Stop_M1200");
  getSyst(mStop_1250, variations, year, f, "Stop_M1250");
  getSyst(mStop_1300, variations, year, f, "Stop_M1300");
  getSyst(mStop_1350, variations, year, f, "Stop_M1350");
  getSyst(mStop_1400, variations, year, f, "Stop_M1400");// */

  // close output root file 
  f->Close();
} 

void getSyst(small_tree_rpv &tree, TString variations, TString year, TFile *f, TString procname)
{
  ioctl(0,TIOCGWINSZ, &w);
  int cols = w.ws_col;

  cout << "Running syst      : " << variations << endl;  
  //TString procname = "qcd";
  TString nominalname = procname+"_"+variations+"_"+year;
  TString upname      = nominalname+"Up";
  TString downname    = nominalname+"Down";
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

  csv_weight_file->Close();
  csv_weight_file_highnjet->Close();
  f->cd();

  if(procname=="qcd") 
  { 
    std::cout << "Reweight b jets by " << bflavorValCentral << " +/ " << bflavorValError << std::endl;
    std::cout << "Reweight c jets by " << cflavorValCentral << " +/ " << cflavorValError << std::endl;
    std::cout << "Reweight l jets by " << lflavorValCentral << " +/ " << lflavorValError << std::endl;
  }
  // Get GS weights 
  std::vector<double> gs_dmc={1,1,1,1};
  std::vector<double> gs_dmc_err={0,0,0,0};
  std::vector<double> gs_dmc_syst={0,0,0,0};
  if(variations.Contains("gs")){

    TFile *gs_file = TFile::Open("data/syst_gs.root");
    TGraphErrors* h_gs_dmc = static_cast<TGraphErrors*>(gs_file->Get("dmc_ldrbb_allmj"));

    double temp_val;
    for(unsigned int ibin=0; ibin<4; ibin++)
    {
      h_gs_dmc->GetPoint(ibin,temp_val,gs_dmc[ibin]);   
      gs_dmc_err[ibin] = h_gs_dmc->GetErrorY(ibin);  
      gs_dmc_syst[ibin] = TMath::Sqrt((1-gs_dmc[ibin])*(1-gs_dmc[ibin])+gs_dmc_err[ibin]*gs_dmc_err[ibin]); 
    }
  } 

  // nominal, up and down histrograms  
  int MjBin=2;
  int NbBin=4;
  TH1F * h1nominal[nbins];
  TH1F * h1up[nbins];     
  TH1F * h1down[nbins];   
  float kappa1_err(0),kappa1_cont(0),kappa2_err(0),kappa2_cont(0);
  float kappa_syst[2][nbins][3][3];    
  float kappa_wgt[2][3][3];
  float other_wgt_up[3][52];
  float other_wgt_down[3][nbins];
  TFile *f_kappa_syst = TFile::Open("data/result_kappa_"+year+".root","read");
  TFile *f_other_syst = TFile::Open("data/other_syst_"+year+".root","read");
  if(str_year=="20178"){
    //f_kappa_syst->Close();
    //cout<<"20178 opened"<<endl;
    f_kappa_syst = TFile::Open("data/result_kappa_20178.root","read");
    cout<<"20178 opened"<<endl;
  }

  // to make kappa_1, kapp_2 histograms which act independently
  TH1F * h1nominal_[nbins][2];
  TH1F * h1up_[nbins][2];     
  TH1F * h1down_[nbins][2];   

  for(int ibin=0; ibin<nbins; ibin++)
  {
    if(ibin>21){
      TH1F *h_other_up;
      TH1F *h_other_down;
      if(variations=="muf"||variations=="mur"||variations=="murf"){
        h_other_up = static_cast<TH1F*>(f_other_syst->Get(Form("bin%d/ratio_other_"+variations+"_"+year+"Up",ibin)));
        h_other_down = static_cast<TH1F*>(f_other_syst->Get(Form("bin%d/ratio_other_"+variations+"_"+year+"Down",ibin)));
        for(int iratio=0 ; iratio<3 ; iratio++){
           other_wgt_up[iratio][ibin]=h_other_up->GetBinContent(iratio+1);
	 // cout<<" up weight iratio : " << iratio << " / ibin : " << ibin << " :: " <<other_wgt_up[iratio][ibin]<<endl;
           other_wgt_down[iratio][ibin]=h_other_down->GetBinContent(iratio+1);
	 // cout<<" down weight iratio : " << iratio << " / ibin : " << ibin << " :: " <<other_wgt_down[iratio][ibin]<<endl;
	 //other_wgt_up[iratio][ibin]=1;
	 //other_wgt_down[iratio][ibin]=1;
	}
      }

      int njbin(0), iproc(0);

      if(ibin%3==1) njbin=0;
      else if(ibin%3==2) njbin=1;
      else if(ibin%3==0) njbin=2;

      if(procname=="qcd") iproc=0;
      else if(procname=="wjets") iproc=1;
      else if(procname=="ttbar") iproc=2;


      TH1F *h_kap1  = static_cast<TH1F*>(f_kappa_syst->Get("hist_kappa1"));
      TH1F *h_kap2  = static_cast<TH1F*>(f_kappa_syst->Get("hist_kappa2"));
      kappa1_err  = h_kap1->GetBinError(njbin+3*iproc+1); 
      kappa1_cont = h_kap1->GetBinContent(njbin+3*iproc+1);
      kappa2_err  = h_kap2->GetBinError(njbin+3*iproc+1); 
      kappa2_cont = h_kap2->GetBinContent(njbin+3*iproc+1); 
      //cout << procname << " " << ibin << " " << njbin << " " << iproc << " " <<  njbin+3*iproc+1 << " " << kappa1_err << " "<< kappa1_cont << " " << kappa2_err << " " << kappa2_cont << endl; // FIXME
      kappa_syst[0][ibin][njbin][iproc] = TMath::Sqrt(kappa1_err*kappa1_err + (1-kappa1_cont)*(1-kappa1_cont));
      kappa_syst[1][ibin][njbin][iproc] = TMath::Sqrt(kappa2_err*kappa2_err + (1-kappa2_cont)*(1-kappa2_cont));
      //cout << kappa_syst[0][ibin][njbin][iproc] << " " << kappa_syst[1][ibin][njbin][iproc] << endl; // FIXME
      kappa_wgt[0][njbin][iproc] = 1;
      kappa_wgt[1][njbin][iproc] = 1;
      if(procname=="qcd") 
      {
        kappa_wgt[0][njbin][iproc] = kappa1_cont;
        kappa_wgt[1][njbin][iproc] = kappa2_cont;
      }
      float unc_dy(0);
      float unc_dy_2016[3][2]={
	      {0.20, 0.19},
	      {0.15, 0.19},
	      {0.12, 0.11}};
      float unc_dy_20178[3][2]={
	      {0.13, 0.15},
	      {0.14, 0.12},
	      {0.10, 0.05}};
      float unc_dy_2017[3][2]={
	      {0.13, 0.16},
	      {0.14, 0.15},
	      {0.10, 0.10}};
      float unc_dy_2018[3][2]={
	      {0.14, 0.14},
	      {0.13, 0.08},
	      {0.10, 0.01}};
      for(int ihb=0; ihb<2; ihb++){
        if(iproc==1){
          if(year=="2016"){
            unc_dy=unc_dy_2016[njbin][ihb];
          }
          if(year=="20178"){
            unc_dy=unc_dy_20178[njbin][ihb];
          }
          if(year=="2017"){
            unc_dy=unc_dy_2017[njbin][ihb];
          }
          if(year=="2018"){
            unc_dy=unc_dy_2018[njbin][ihb];
          }
          kappa_syst[ihb][ibin][njbin][iproc]=TMath::Sqrt(kappa_syst[ihb][ibin][njbin][iproc]*kappa_syst[ihb][ibin][njbin][iproc]+unc_dy*unc_dy);
        }
      }
    }
    else if(variations.Contains("kappa")&&ibin<22){
      for(int i=0; i<2; i++){
        for(int j=0; j<3; j++){
          for(int k=0; k<3; k++){
            kappa_syst[i][ibin][j][k] = 0;
          }
        }
      }
    }
    if(ibin<22){
      h1nominal[ibin]    = new TH1F(nominalname.Data(),  nominalname.Data(), NbBin, 1, NbBin+1);
      h1up[ibin]         = new TH1F(upname.Data(),       upname.Data(),      NbBin, 1, NbBin+1);
      h1down[ibin]       = new TH1F(downname.Data(),     downname.Data(),    NbBin, 1, NbBin+1);
      for(int j=0; j<2; j++){
        h1nominal_[ibin][j]    = new TH1F(nominalname.Data(),  nominalname.Data(), NbBin, 1, NbBin+1);
        h1up_[ibin][j]         = new TH1F(upname.Data(),       upname.Data(),      NbBin, 1, NbBin+1);
        h1down_[ibin][j]       = new TH1F(downname.Data(),     downname.Data(),    NbBin, 1, NbBin+1);
      }
    }
    else{
      h1nominal[ibin]    = new TH1F(Form("%s_bin%i",nominalname.Data(),ibin),    Form("%s_bin%i",nominalname.Data(),ibin), MjBin+1, mjmin, mjmax);
      h1up[ibin]         = new TH1F(Form("%s_bin%i",upname.Data(),ibin),         Form("%s_bin%i",upname.Data(),ibin), MjBin+1, mjmin, mjmax);
      h1down[ibin]       = new TH1F(Form("%s_bin%i",downname.Data(),ibin),       Form("%s_bin%i",downname.Data(),ibin), MjBin+1, mjmin, mjmax);
      for(int j=0; j<2; j++){
        h1nominal_[ibin][j]    = new TH1F(Form("%s_bin%i",nominalname.Data(),ibin),    Form("%s_bin%i",nominalname.Data(),ibin), MjBin+1, mjmin, mjmax);
        h1up_[ibin][j]         = new TH1F(Form("%s_bin%i",upname.Data(),ibin),         Form("%s_bin%i",upname.Data(),ibin), MjBin+1, mjmin, mjmax);
        h1down_[ibin][j]       = new TH1F(Form("%s_bin%i",downname.Data(),ibin),       Form("%s_bin%i",downname.Data(),ibin), MjBin+1, mjmin, mjmax);
      }
    }
  }

  // loop over tree 
  for(unsigned int ientry=0; ientry<tree.GetEntries(); ientry++)
  {
    float progress = 0.0;
    if(ientry%int(tree.GetEntries()/1000) == 0||ientry+1 == tree.GetEntries()){
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

    // 
    // Central weights
    // 
    float nominalweight = lumi*tree.weight();
<<<<<<< HEAD
=======
    //float nominalweight = lumi*tree.weight()*tree.frac1718(); // FIXME for 2017+2018 merging
>>>>>>> 1c5974e584c129549af1966e4c8b93b141350903
    //cout<<nominalweight<<endl;
    //else if (procname=="data_obs") nominalweight = tree.pass() * (tree.trig()[12]||tree.trig()[54]||tree.trig()[56]); // rereco

    //if (procname=="data_obs") nominalweight = tree.pass() * (tree.trig_jet450()||tree.trig_ht900()); // rereco FIXME
    if (procname=="data_obs" && year=="2016") nominalweight = tree.pass() * (tree.trig_ht900()||tree.trig_jet450());
    else if (procname=="data_obs") nominalweight = tree.pass() * tree.trig_ht1050(); // rereco // 2017 and 2018
    //else if (procname=="data_obs") nominalweight = tree.pass() * tree.trig()[12]; // prompt reco
    else if (procname=="signal") nominalweight = nominalweight * 1;
    //else if ((tree.nbm()==0||tree.nbm()==1) && tree.mj12()>1100 && tree.njets()>=4 && tree.njets()<=5) nominalweight=lumi*tree.weight()*0.4;//FIXME HEM issue
/*
    int nb_csv=0;
    for(unsigned int j=0; j<tree.jets_hflavor().size();j++){
      if(tree.jets_islep().at(j)) continue;
      if(tree.jets_pt().at(j)<30) continue;
      if(abs(tree.jets_eta().at(j))>2.4) continue;
      if(tree.jets_csv().at(j)>0.8484) nb_csv++;
    }
*//*
    int loose_lep(0), loose_els(0), loose_mus(0);
    for(unsigned int ie=0; ie<tree.els_pt().size(); ie++){
      if(tree.els_pt().at(ie)<20) continue;
      if(abs(tree.els_eta().at(ie))>2.5) continue;
      if(!tree.els_sigid().at(ie)) continue;
      if(tree.els_miniso().at(ie)>1.0) continue;
      if(tree.els_miniso().at(ie)<0.05) continue;
      loose_els++;
      loose_lep++;
    }
    for(unsigned int im=0; im<tree.mus_pt().size(); im++){
      if(tree.mus_pt().at(im)<20) continue;
      if(abs(tree.mus_eta().at(im))>2.4) continue;
      if(!tree.mus_sigid().at(im)) continue;
      if(tree.mus_miniso().at(im)>1.0) continue;
      if(tree.mus_miniso().at(im)<0.1) continue;
      loose_mus++;
      loose_lep++;
    }
*/
    // qcd jet flavor central weights
    /* if(procname=="qcd") 
       { 
       int n_bflavor=0;
       int n_cflavor=0;
       for(unsigned int j=0; j<tree.jets_hflavor().size(); j++)
       {   // FIXME: need to include these lines 
    //if(tree.jets_islep().at(j)) continue;
    //if(tree.jets_pt().at(j)<30) continue;
    //if(abs(tree.jets_eta().at(j))>2.4) continue; 

    if(tree.jets_hflavor().at(j)==5) n_bflavor++;
    if(tree.jets_hflavor().at(j)==4) n_cflavor++;
    }

    if(n_bflavor>0)  
    { 
    nominalweight = nominalweight*bflavorValCentral;
    }
    else if(n_cflavor>0)
    { 
    nominalweight = nominalweight*cflavorValCentral;
    }
    else 
    { 
    nominalweight = nominalweight*lflavorValCentral;
    }
    }*/

    //
    // Now assign up and down weights
    //
    float upweight      = nominalweight;
    float downweight    = nominalweight;

    // scale qcd normialzation
    //        if(procname=="qcd") {upweight = upweight*2; downweight = downweight/2;}

    // scale W+jet normialzation
    //        if(procname=="wjets") {upweight = upweight*2; downweight = downweight/2;}

    // scale ttbar normialzation
    //        if(procname=="ttbar") {upweight = upweight*2; downweight = downweight/2;}

    // scale other normialzation
    //        if(procname=="other") {upweight = upweight*2; downweight = downweight/2;}


    //
    // variations that are common in all processes
    //
    if(variations=="btag_bc") 
    { 
      //cout<<tree.sys_bctag()[0]<<"::"<<tree.sys_bctag()[1]<<endl;
      upweight    = upweight*tree.sys_bctag()[0]/tree.w_btag_dcsv();
      downweight  = downweight*tree.sys_bctag()[1]/tree.w_btag_dcsv();
      //cout<<tree.sys_bctag()[0]<<"::"<<tree.sys_bctag()[1]<<endl;
      //cout<<upweight<<"::"<<downweight<<"::"<<nominalweight<<endl;
    }
    if(variations=="btag_udsg") 
    { 
      upweight    = upweight*tree.sys_udsgtag()[0]/tree.w_btag_dcsv();
      downweight  = downweight*tree.sys_udsgtag()[1]/tree.w_btag_dcsv();
    }
    if(variations=="gs") 
    {
      if(tree.fromGS()==1){
        upweight    = upweight*(1.2*tree.fromGS());
        downweight  = downweight*(0.8*tree.fromGS()); 
      }
    }
    if(variations=="gs67") 
    { 
      if(tree.njets()==6 || tree.njets()==7)
      {
        upweight    = upweight*(1+gs_dmc_syst[1]*tree.fromGS());
        downweight  = downweight*(1-gs_dmc_syst[1]*tree.fromGS()); 
      } 
    }
    if(variations=="gs89") 
    { 
      if(tree.njets()==8 || tree.njets()==9)
      {
        upweight    = upweight*(1+gs_dmc_syst[2]*tree.fromGS());
        downweight  = downweight*(1-gs_dmc_syst[2]*tree.fromGS()); 
      } 
    }
    if(variations=="gs10Inf") 
    { 
      if(tree.njets()>=10)
      {
        upweight    = upweight*(1+gs_dmc_syst[3]*tree.fromGS());
        downweight  = downweight*(1-gs_dmc_syst[3]*tree.fromGS()); 
      } 
    }
    if(variations=="lep_eff") 
    {   
      //upweight    = upweight*tree.w_lep();
      //downweight  = downweight*(2-tree.w_lep());
      upweight    = upweight*tree.sys_lep()[0]/tree.w_lep();
      downweight  = downweight*tree.sys_lep()[1]/tree.w_lep();
    }
    if(variations=="pileup") 
    {
      if(procname.Contains("signal")){
	if(tree.w_pu()!=0){
          upweight    = upweight*tree.sys_pu()[0]/tree.w_pu();
          downweight  = downweight*tree.sys_pu()[1]/tree.w_pu();
	}
	else if(tree.w_pu()==0){
	  upweight    = 0;
          downweight  = 0;
	}// */
      }
      else{
        upweight    = upweight;
        downweight  = downweight;
      }
    }
    if(variations=="muf")
    {
      if(((year == "2017" || year == "2018") && procname == "ttbar")){
        upweight   = lumi*tree.weight();
        downweight   = lumi*tree.weight();
      }
      else {// procname!="other" //-->2016
        upweight    = upweight*tree.sys_muf()[0];
        downweight  = downweight*tree.sys_muf()[1];
      } 
    }
    if(variations=="mur")
    {
      if(procname=="ttbar"){
        upweight   = lumi*tree.weight();
        downweight   = lumi*tree.weight();
      }
      else {
        upweight = upweight*tree.sys_mur()[0];
        downweight = downweight*tree.sys_mur()[1];
      }
    }
    if(variations=="murf")
    {
      if(procname == "ttbar"){
        upweight   = lumi*tree.weight();
        downweight   = lumi*tree.weight();
      }
      else {
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      } 
    }
    if(variations=="w_pdf")  // PDF 
    { 
      upweight    = upweight*tree.w_pdf()[w_pdf_index];
      downweight  = downweight*(2-tree.w_pdf()[w_pdf_index]);
    }

    //
    // variations that depend on process 
    //  - ttbar : ttbar_pt, isr
    //  - signal: isr
    //  - QCD   : qcd_flavor 
    if(procname=="ttbar") 
    { 
      if(variations=="ttbar_pt")  
      { 
        upweight    = upweight*tree.w_toppt();
        downweight  = downweight*(2-tree.w_toppt());
      }
      if(variations=="isr") 
      {
	if(year == "2016"){
          upweight    = upweight*tree.sys_isr()[0]/tree.w_isr();
          downweight  = downweight*tree.sys_isr()[1]/tree.w_isr();// */ //FIXME
	}
	else {
	  upweight = upweight*tree.w_isr();
	  downweight = downweight*tree.w_isr();// */
	}
      }
      if(variations=="ttbar_muf") 
      { 
        upweight    = upweight*tree.sys_muf()[0];
        downweight  = downweight*tree.sys_muf()[1];
      }
      if(variations=="ttbar_mur") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="ttbar_murf") 
      { 
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      }
    }
    if(procname.Contains("signal")) 
    { 
      if(variations=="isr") 
      {
        if(year == "2016"){
	  upweight    = upweight*tree.sys_isr()[0]/tree.w_isr();
	  downweight  = downweight*tree.sys_isr()[1]/tree.w_isr();// */ //FIXME
        }
	else {
	  upweight = upweight*tree.w_isr();
	  downweight = downweight*tree.w_isr();// */
	}
      }
      if(variations=="signal_muf") 
      { 
        upweight    = upweight*tree.sys_muf()[0];
        downweight  = downweight*tree.sys_muf()[1];
      }
      if(variations=="signal_mur") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="signal_murf") 
      { 
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      }
    }
    if(procname=="qcd") 
    { 
      if(variations=="qcd_flavor") 
      {
        // apply weights
        int n_bflavor=0;
        int n_cflavor=0;
        for(unsigned int j=0; j<tree.jets_hflavor().size(); j++)
        {   
          // FIXME: need to include these lines
          //if(tree.jets_islep().at(j)) continue;
          //if(tree.jets_pt().at(j)<30) continue;
          //if(abs(tree.jets_eta().at(j))>2.4) continue;

          if(tree.jets_hflavor().at(j)==5) n_bflavor++;
          if(tree.jets_hflavor().at(j)==4) n_cflavor++;
        }

        if(n_bflavor>0)
        {
          upweight      = upweight*(bflavorValCentral+bflavorValError)/bflavorValCentral;
          downweight    = downweight*(bflavorValCentral-bflavorValError)/bflavorValCentral; 
        }
        else if(n_cflavor>0)
        {
          upweight      = upweight*(cflavorValCentral+cflavorValError)/cflavorValCentral;
          downweight    = downweight*(cflavorValCentral-cflavorValError)/cflavorValCentral;
        }
        else
        {
          upweight      = upweight*1;
          downweight    = downweight*1;
        }
      }
      if(variations=="qcd_muf") 
      { 
        upweight    = upweight*tree.sys_muf()[0];
        downweight  = downweight*tree.sys_muf()[1];
      }
      if(variations=="qcd_mur") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="qcd_murf") 
      { 
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      }
    }
    if(procname=="wjets") 
    { 
      if(variations=="wjets_muf") 
      { 
        upweight    = upweight*tree.sys_muf()[0];
        downweight  = downweight*tree.sys_muf()[1];
      }
      if(variations=="wjets_mur") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="wjets_murf") 
      { 
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      }
    }
    if(procname=="other") 
    { 
      if(variations=="other_muf") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="other_mur") 
      { 
        upweight    = upweight*tree.sys_mur()[0];
        downweight  = downweight*tree.sys_mur()[1];
      }
      if(variations=="other_murf") 
      { 
        upweight    = upweight*tree.sys_murf()[0];
        downweight  = downweight*tree.sys_murf()[1];
      }
    }

    //
    // fill Nb histograms   
    //
    float temp_nominal = nominalweight;
    float temp_up = upweight;
    float temp_down = downweight;
    if(tree.mj12()<500) nominalweight=0;
    //if(procname!="data_obs") cout<<nominalweight<<endl;
    bool flag=true;
    for(int ibin=0; ibin<nbins; ibin++)  
    {
      int ihb(0);
      int njbin(0), iproc(0);

      if(ibin%3==1) njbin=0;
      else if(ibin%3==2) njbin=1;
      else if(ibin%3==0) njbin=2;

      if(procname=="qcd") iproc=0;
      else if(procname=="wjets") iproc=1;
      else if(procname=="ttbar") iproc=2;

      if(tree.mj12()>mjmin && tree.mj12()<mjmin+300) ihb = 999;
      else if(tree.mj12()>mjmin+300 && tree.mj12()<mjmin+600) ihb = 0;
      else if(tree.mj12()>mjmin+600) ihb = 1;

//      if((iproc==1)&&ibin>21) cout << kappa_syst[0][ibin][njbin][iproc] << " " << kappa_syst[1][ibin][njbin][iproc] << endl; // FIXME

      flag=false;

      if(procname!="data_obs"&&procname!="other"&&ibin>22){
        if(ihb!=999){
          float kappa_w = kappa_wgt[ihb][njbin][iproc];
          nominalweight = temp_nominal*kappa_w;
          upweight = temp_up*kappa_w;          
          downweight = temp_down*kappa_w;
        }
      }
      else{
        nominalweight = temp_nominal;
        upweight = temp_up;
        downweight = temp_down;
      }

      if((procname=="other")&&(variations=="mur"||variations=="muf"||variations=="murf")){
        int hbother=(ihb+1)%1000;
	if(tree.sys_mur()[0]==1){
          upweight=nominalweight*other_wgt_up[hbother][ibin];
          downweight=nominalweight*other_wgt_down[hbother][ibin];
/*	  if(ibin==27){
	    cout<<hbother<<" :: "<<endl;
	    cout<<upweight/nominalweight<<endl;
	    cout<<downweight/nominalweight<<endl;
	    cout<<other_wgt_up[hbother][ibin]<<endl;
	  }
*/	}
      }
      //if(procname!="data_obs") cout<<nominalweight<<endl;
      if(ibin<22)
      {
        int hnbmax = 5-0.0001;
        int nb_csv = tree.nbm();
        if(tree.nleps()==0 && !nl0shape){
          hnbmax = 2-0.001;
        }
        if(variations=="jer")//jet energy resolution
        {  
          if(nb_csv>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
            h1nominal[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.nbm(), nominalweight);              // nominal  
          if(tree.sys_nbm()[2]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[2], tree.sys_njets()[2], tree.sys_mj12()[2], tree.sys_nbm()[2])) 
            h1up[ibin]->Fill(tree.sys_nbm()[2]>hnbmax?hnbmax:tree.sys_nbm()[2], upweight);          // up
          if(nb_csv>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[3], tree.sys_njets()[3], tree.sys_mj12()[3], tree.sys_nbm()[3])) 
            h1down[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.sys_nbm()[3], downweight);                    // down  

        } 
        else if(variations=="jec") //jet energy scale
        {
          if(nb_csv>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
            h1nominal[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.nbm(), nominalweight);              // nominal  
          if(tree.sys_nbm()[0]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[0], tree.sys_njets()[0], tree.sys_mj12()[0], tree.sys_nbm()[0]))  
            h1up[ibin]->Fill(tree.sys_nbm()[0]>hnbmax?hnbmax:tree.sys_nbm()[0], upweight);          // up 
          if(tree.sys_nbm()[1]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[1], tree.sys_njets()[1], tree.sys_mj12()[1], tree.sys_nbm()[1]))  
            h1down[ibin]->Fill(tree.sys_nbm()[1]>hnbmax?hnbmax:tree.sys_nbm()[1], downweight);      // down
        }
        else 
        {
          if(nb_csv>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
          {
            h1nominal[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.nbm(), nominalweight);  // nominal  
            h1up[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.nbm(), upweight);            // up  
            h1down[ibin]->Fill(nb_csv>hnbmax?hnbmax:tree.nbm(), downweight);        // down 
          }
        }
      }
      else{
        if(variations=="kappa")
        {
          float sys_kappaup,sys_kappadown;
          if(ihb==999||procname=="data_obs"){
            upweight    = nominalweight;
            downweight  = nominalweight;
          }
	  else{
	    upweight   = nominalweight;
            downweight = nominalweight;
            sys_kappaup   = 1+kappa_syst[ihb][ibin][njbin][iproc];
            sys_kappadown = 1-kappa_syst[ihb][ibin][njbin][iproc]; 
            if(sys_kappadown<0)  sys_kappadown = 0.01; 
            //cout<<sys_kappaup<<"::"<<sys_kappadown<<endl;

            //if(iproc==0) cout << "before " << nominalweight << " " << upweight << " " << downweight << endl; // FIXME   
            upweight    = upweight*sys_kappaup;
            downweight  = downweight*sys_kappadown;
            //if(iproc==0) cout << "after " <<  nominalweight << " " << upweight << " " << downweight << endl; // FIXME   
          }
          if(tree.mj12()>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
          {
            float hmjmax = mjmax-0.001;
            if(tree.nleps()==0 && !nl0shape){
              hmjmax = mjmin+(mjmax-mjmin)/(MjBin+1)-0.001;
            }
            //cout<<hmjmax<<endl;
            if(ihb!=999){
              int ihb_  = (ihb)%2;
              int ihb__ = (ihb+1)%2;
              h1nominal_[ibin][ihb_]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);  // nominal  
              h1up_[ibin][ihb_]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), upweight);            // up  
              h1down_[ibin][ihb_]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), downweight);        // down 
              h1nominal_[ibin][ihb__]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);  // nominal  
              h1up_[ibin][ihb__]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);            // up  
              h1down_[ibin][ihb__]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);        // down 
            }
            else{
              h1nominal_[ibin][0]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);  // nominal  
              h1up_[ibin][0]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);            // up  
              h1down_[ibin][0]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);        // down 
              h1nominal_[ibin][1]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);  // nominal  
              h1up_[ibin][1]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);            // up  
              h1down_[ibin][1]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);        // down 

            }
          }
        }
        else if(variations=="jer")//jet energy resolution
        {  
          float hmjmax = mjmax-0.001;
          if(tree.nleps()==0 && !nl0shape){
            hmjmax = mjmin+(mjmax-mjmin)/(MjBin+1)-0.001;
          }
          if(tree.mj12()>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
            h1nominal[ibin]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);              // nominal  
          if(tree.sys_mj12()[2]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[2], tree.sys_njets()[2], tree.sys_mj12()[2], tree.sys_nbm()[2])) 
            h1up[ibin]->Fill(tree.sys_mj12()[2]>hmjmax?hmjmax:tree.sys_mj12()[2], upweight);          // up
          if(tree.sys_mj12()[3]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[3], tree.sys_njets()[3], tree.sys_mj12()[3], tree.sys_nbm()[3])) 
            h1down[ibin]->Fill(tree.sys_mj12()[3]>hmjmax?hmjmax:tree.sys_mj12()[3], downweight);                    // down  

        } 
        else if(variations=="jec") //jet energy scale
        { 
          float hmjmax = mjmax-0.001;
          if(tree.nleps()==0 && !nl0shape){
            hmjmax = mjmin+(mjmax-mjmin)/(MjBin+1)-0.001;
          }
          if(tree.mj12()>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm())) 
            h1nominal[ibin]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);              // nominal  
          if(tree.sys_mj12()[0]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[0], tree.sys_njets()[0], tree.sys_mj12()[0], tree.sys_nbm()[0]))  
            h1up[ibin]->Fill(tree.sys_mj12()[0]>hmjmax?hmjmax:tree.sys_mj12()[0], upweight);          // up FIXME
          if(tree.sys_mj12()[1]>0 && passBinCut(ibin, tree.nleps(), tree.sys_ht()[1], tree.sys_njets()[1], tree.sys_mj12()[1], tree.sys_nbm()[1]))  
            h1down[ibin]->Fill(tree.sys_mj12()[1]>hmjmax?hmjmax:tree.sys_mj12()[1], downweight);      // down FIXME
        }
        else 
        {
          if(tree.mj12()>0 && passBinCut(ibin, tree.nleps(), tree.ht(), tree.njets(), tree.mj12(), tree.nbm()))
          {
           // if(loose_lep==0) nominalweight=0;
            float hmjmax = mjmax-0.001;
            if(tree.nleps()==0 && !nl0shape){
              hmjmax = mjmin+(mjmax-mjmin)/(MjBin+1)-0.001;
              //cout<<hmjmax<<endl;
            }
            h1nominal[ibin]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), nominalweight);  // nominal  
            h1up[ibin]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), upweight);            // up  
            h1down[ibin]->Fill(tree.mj12()>hmjmax?hmjmax:tree.mj12(), downweight);        // down 
          }
        }
      }
    }

  } //for(unsigned int ientry=0; ientry<tree.GetEntries(); ientry++) 

  //
  // Write histograms to an output file 
  //
  f->cd();
  for(int ibin=0; ibin<nbins; ibin++)
  {
    gDirectory->cd("/");
    TString directory(Form("bin%d", ibin));
    if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
    gDirectory->cd(directory);

    /*
    // rescale some histograms 
    //  - previously done by src/rescale_variations.cxx
    //  - no need to run it now
    if(variations=="qcd_flavor")
    { 
    h1up[ibin]->Scale( h1nominal[ibin]->Integral()/h1up[ibin]->Integral()); 
    h1down[ibin]->Scale( h1nominal[ibin]->Integral()/h1down[ibin]->Integral()); 
    }
    */       
    //
    if(variations=="nominal")
    {
      h1nominal[ibin]->SetTitle(procname.Data());
      h1nominal[ibin]->SetName(procname.Data());
      h1nominal[ibin]->Write();
    }
    else if(variations=="kappa")
    {
      for(int kap=1; kap<3; kap++){
        TString temp_;
        if(ibin%3==1) temp_ = Form("kappa%d_njets45_%s",kap, procname.Data());
        else if(ibin%3==2) temp_ = Form("kappa%d_njets67_%s",kap, procname.Data());
        else if(ibin%3==0) temp_ = Form("kappa%d_njets8_%s",kap, procname.Data());

        if(procname=="other"||procname.Contains("signal")) continue;

	if(str_year==""){
          upname = procname+"_"+temp_+"_"+year+"Up";
          downname = procname+"_"+temp_+"_"+year+"Down";
	}
	else{
          upname = procname+"_"+temp_+"_"+str_year+"Up";
          downname = procname+"_"+temp_+"_"+str_year+"Down";
	}

        h1up_[ibin][kap-1]->SetTitle(upname.Data());
        h1up_[ibin][kap-1]->SetName(upname.Data());
        h1down_[ibin][kap-1]->SetTitle(downname.Data());
        h1down_[ibin][kap-1]->SetName(downname.Data());
        h1up_[ibin][kap-1]->Write();
        h1down_[ibin][kap-1]->Write();
      }
    }
    else if(variations.Contains("mu")) 
    {
      TString procnamemu=procname;
      if(procname.Contains("signal"))procnamemu="sig";
      if(str_year==""){ // for 2017+2018 merging FIXME
        upname = procname+"_"+variations+"_"+procnamemu+"_"+year+"Up";
        downname = procname+"_"+variations+"_"+procnamemu+"_"+year+"Down";
      }
      else{
        upname = procname+"_"+variations+"_"+procnamemu+"_"+str_year+"Up";
        downname = procname+"_"+variations+"_"+procnamemu+"_"+str_year+"Down";
      }// */

      h1up[ibin]->SetTitle(upname.Data());
      h1up[ibin]->SetName(upname.Data());
      h1down[ibin]->SetTitle(downname.Data());
      h1down[ibin]->SetName(downname.Data());
      h1up[ibin]->Write();
      h1down[ibin]->Write();
    }
    else 
    {
      /*if(str_year==""){ // for 2017+2018 merging FIXME
        upname = procname+"_"+variations+"_"+year+"Up";
        downname = procname+"_"+variations+"_"+year+"Down";
      }
      else{
        upname = procname+"_"+variations+"_"+str_year+"Up";
        downname = procname+"_"+variations+"_"+str_year+"Down";
      }// */

      h1up[ibin]->SetTitle(upname.Data());
      h1up[ibin]->SetName(upname.Data());
      h1down[ibin]->SetTitle(downname.Data());
      h1down[ibin]->SetName(downname.Data());
      h1up[ibin]->Write();
      h1down[ibin]->Write();
    }
  }
  //f->Print();
  cout<<"\n"; 
  for(int al=0 ; al<cols ; al++) cout << "=";
  cout<<endl;
}

TString color(TString procname){
  if(procname == "data_obs") return reset;
  else if(procname == "qcd") return yellow;
  else if(procname == "ttbar") return blue;
  else if(procname == "wjets") return green;
  else if(procname == "other") return gray;
  else return red;
}
//void fillTH1F(TH1F* &h1, float var, float weight)
//{
//    if(var >= h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins()))
//        var=h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins())-0.00001;
//    if(var < h1->GetXaxis()->GetBinLowEdge(1))
//        var=h1->GetXaxis()->GetBinLowEdge(1)+0.00001;
//    h1->Fill(var, weight);
//}

