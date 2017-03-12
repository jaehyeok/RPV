#include <iostream>
#include <fstream>
#include <vector>

#include "TDirectory.h"
#include "TFile.h"

#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  const int nBins=20;
  const float xMin=0.8484;
  const float xMax=1.0;

  TString lumi = "36.8";
  bool makeDatacard = true;
}

using namespace std;

int main(){ 

  TString folder_dat = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/data/merged_rpvdata_rpvregion/";  
  TString folder_bkg = "/net/cms27/cms27r0/babymaker/babies/2017_01_27/mc/merged_rpvmc_rpvregion/";
  TString folder_sig = "/net/cms2/cms2r0/jaehyeokyoo/babies/2017_01_10/mc/T1tbs/";

  vector<TString> s_data = getRPVProcess(folder_dat,"data");

  vector<TString> s_rpv_m1700 = getRPVProcess(folder_sig,"rpv_m1700");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  // The CSV reweighting only affects QCD; the flavor composition of other samples are well defined and does not need correction
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  // Add ttbar and wjets to other
  s_other.insert(s_other.end(),s_tt.begin(),s_tt.end());
  s_other.insert(s_other.end(),s_wjets.begin(),s_wjets.end());

  //Make chains
  TChain data("tree"), signal("tree"), qcd("tree"), other("tree");

  for(unsigned int ifile=0; ifile<s_data.size(); ifile++) 
    data.Add(s_data[ifile]);
  for(unsigned int ifile=0; ifile<s_rpv_m1700.size(); ifile++)   
    signal.Add(s_rpv_m1700[ifile]);
  for(unsigned int ifile=0; ifile<s_qcd.size(); ifile++)   
    qcd.Add(s_qcd[ifile]);
  for(unsigned int ifile=0; ifile<s_other.size(); ifile++) 
    other.Add(s_other[ifile]);
  
  TString databasecut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>500&&nbm>=2&&pass";
  TString basecut = "nleps==0&&ht>1500&&njets>=4&&njets<=7&&mj12>500&&nbm>=2&&pass&&stitch_ht";

  //Make histograms
  TH1::SetDefaultSumw2(true);

  cout<<"Making data histogram"<<endl;
  TH1D h_data("data_obs", "data_obs", nBins, xMin, xMax);
  data.Project("data_obs","jets_csv",databasecut);

  //Need a dummy signal shape
  cout<<"Making signal histogram"<<endl;
  TH1D h_signal("rpvsignal", "rpvsignal", nBins, xMin, xMax);
  signal.Project("rpvsignal","jets_csv",lumi+"*weight*("+basecut+")");

  cout<<"Making qcd_b histogram"<<endl;
  TH1D h_qcdb("qcd_b", "qcd_b", nBins, xMin, xMax);
  qcd.Project("qcd_b","jets_csv",lumi+"*weight*("+basecut+"&& Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)>=1)");

  cout<<"Making qcd_c histogram"<<endl;
  TH1D h_qcdc("qcd_c", "qcd_c", nBins, xMin, xMax);
  qcd.Project("qcd_c","jets_csv",lumi+"*weight*("+basecut+"&& Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==4)>=1)");

  cout<<"Making qcd_l histogram"<<endl;
  TH1D h_qcdl("qcd_l", "qcd_l", nBins, xMin, xMax);
  qcd.Project("qcd_l","jets_csv",lumi+"*weight*("+basecut+"&& Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==5)==0 && Sum$(jets_pt>30&&abs(jets_eta)<=2.4&&abs(jets_hflavor)==4)==0)");

  cout<<"Making other histogram"<<endl;
  TH1D h_other("other", "other", nBins, xMin, xMax);
  other.Project("other","jets_csv",lumi+"*weight*("+basecut+")");

  cout<<"Normalizing QCD yields to match data"<<endl;
  double scaling = (h_data.Integral() - h_other.Integral())/(h_qcdb.Integral() + h_qcdc.Integral() + h_qcdl.Integral());
  cout<<"Scaling factor is "<<scaling<<endl;

  h_qcdb.Scale(scaling);
  h_qcdc.Scale(scaling);
  h_qcdl.Scale(scaling);

  //Make file and write histograms to it
  TString filename = "csvfit_shapes.root";
  TFile *out = new TFile(filename, "recreate");
  TDirectory *bin =  out->mkdir("bin1");
  bin->cd();
  
  h_data.Write();
  h_signal.Write();
  h_qcdb.Write();
  h_qcdc.Write();
  h_qcdl.Write();
  h_other.Write();

  out->Write();
  out->Close();

  cout<<"Wrote out shapes file: "<<filename<<endl;

  //Make datacard
  if(makeDatacard){
    double ndata = h_data.Integral();
    double nsignal = h_signal.Integral();    
    double nqcdb = h_qcdb.Integral();
    double nqcdc = h_qcdc.Integral();
    double nqcdl =  h_qcdl.Integral();
    double nother = h_other.Integral();

    ofstream card;
    card.open("datacard_csvfit.dat");
    card << "# Datacard for csv flavor fit \n";
    card << "imax 1  number of channels \n";
    card << "jmax 4  number of backgrounds \n";
    card << "kmax *  number of nuisances \n";    
    card << "---------------------------------------------------------- \n";
    card << "shapes * bin1 csvfit_shapes.root bin1/$PROCESS bin1/$PROCESS_SYSTEMATIC \n";
    card << "---------------------------------------------------------- \n";
    card << "bin         bin1 \n";
    card << "observation "<<ndata<<" \n";
    card << "---------------------------------------------------------- \n";
    card << "bin         bin1        bin1     bin1     bin1     bin1 \n";
    card << "process     rpvsignal   qcd_b    qcd_c    qcd_l    other \n";
    card << "process     0           1        2        3        4 \n";
    card << "rate        "<<nsignal<<"     "<<nqcdb<<"  "<<nqcdc<<"  "<<nqcdl<<"  "<<nother<<" \n";
    card << "---------------------------------------------------------- \n";
    card << "norm_qcd_b     lnU - 5 - - - \n";
    card << "norm_qcd_c     lnU - - 5 - - \n";

    cout<<"Made datacard: datacard_csvfit.dat"<<endl;
  }  
}
