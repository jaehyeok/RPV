// 2023.10.16 //
// WW_TuneCP5_13TeV-pythia8, WZ_TuneCP5_13TeV-pythia8, and ZZ_TuneCP5_13TeV-pythia8 Ultra-Legacy samples do not have the <LHEScaleWeight> branch, which contains systematic informations about mur, muf, and murf. //
// In the make_variations_loop_newntuple.cxx, it reads the output file of this code and provides systematic information to the above samples. //
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TString.h"
#include "TTree.h"
#include "THStack.h"
#include "TLatex.h"
#include "TF1.h"
#include "TLine.h"

using namespace std;

void getOtherMuSyst(TString year, TString inputfile);


int main(int argc, char *argv[])
{

  TString year, inputfile;

  year      = argv[1];
  inputfile = argv[2];

  if(argc<3) {
    cout << "You should input [year] and [inputfile]" << endl;
    cout << "[example]: ./run/make_other_mu_syst.exe 2017 variations/output_impact_2017_20178.root" << endl;
    return 0;
  }
  if(!(year=="2016" || year=="2017" || year=="2018")) {
    cout << "year should be 2016, 2017, or 2018" << endl;
    return 0;
  }

  getOtherMuSyst(year, inputfile);

  return 0;
}

void getOtherMuSyst(TString year, TString inputfile)
{
  TH1::SetDefaultSumw2();

  TString yr;
  if(year=="2017" || year=="2018") yr="20178";
  else yr="2016";

  TFile *f_input = new TFile(inputfile, "READ");

  TH1F *other[52];
  TH1F *other_mur_up[52],  *other_mur_down[52];
  TH1F *other_muf_up[52],  *other_muf_down[52];
  TH1F *other_murf_up[52], *other_murf_down[52];

  TH1F *clone_other[52];
  TH1F *clone_other_mur_up[52],  *clone_other_mur_down[52];
  TH1F *clone_other_muf_up[52],  *clone_other_muf_down[52];
  TH1F *clone_other_murf_up[52], *clone_other_murf_down[52];

  // Open the input file
  f_input->cd();
  for(int ibin=22; ibin<52; ibin++) {
    // Get the histograms
    other[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other", ibin)));
    other_mur_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_mur_other_%sUp", ibin, yr.Data())));
    other_mur_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_mur_other_%sDown", ibin, yr.Data())));
    other_muf_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_muf_other_%sUp", ibin, yr.Data())));
    other_muf_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_muf_other_%sDown", ibin, yr.Data())));
    other_murf_up[ibin]   = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_murf_other_%sUp", ibin, yr.Data())));
    other_murf_down[ibin] = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_murf_other_%sDown", ibin, yr.Data())));

    // Clone the histograms
    clone_other[ibin] 		= static_cast<TH1F*>(other[ibin]->Clone());
    clone_other_mur_up[ibin] 	= static_cast<TH1F*>(other_mur_up[ibin]->Clone(Form("ratio_other_mur_%sUp", year.Data())));
    clone_other_mur_down[ibin] 	= static_cast<TH1F*>(other_mur_down[ibin]->Clone(Form("ratio_other_mur_%sDown", year.Data())));
    clone_other_muf_up[ibin] 	= static_cast<TH1F*>(other_muf_up[ibin]->Clone(Form("ratio_other_muf_%sUp", year.Data())));
    clone_other_muf_down[ibin] 	= static_cast<TH1F*>(other_muf_down[ibin]->Clone(Form("ratio_other_muf_%sDown", year.Data())));
    clone_other_murf_up[ibin] 	= static_cast<TH1F*>(other_murf_up[ibin]->Clone(Form("ratio_other_murf_%sUp", year.Data())));
    clone_other_murf_down[ibin] = static_cast<TH1F*>(other_murf_down[ibin]->Clone(Form("ratio_other_murf_%sDown", year.Data())));

    // Get the ratio of mur, muf and murf for other process
    clone_other_mur_up[ibin]->Divide(other[ibin]);
    clone_other_mur_down[ibin]->Divide(other[ibin]);
    clone_other_muf_up[ibin]->Divide(other[ibin]);
    clone_other_muf_down[ibin]->Divide(other[ibin]);
    clone_other_murf_up[ibin]->Divide(other[ibin]);
    clone_other_murf_down[ibin]->Divide(other[ibin]);
  }
  
  // Create the output file
  TFile *f_output = new TFile(Form("data/other_syst_%s.root", year.Data()), "RECREATE");

  f_output->cd();
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd("/");
    TString directory(Form("bin%d", ibin));
    if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
    gDirectory->cd(directory);

    clone_other_mur_up[ibin]->Write();
    clone_other_mur_down[ibin]->Write();
    clone_other_muf_up[ibin]->Write();
    clone_other_muf_down[ibin]->Write();
    clone_other_murf_up[ibin]->Write();
    clone_other_murf_down[ibin]->Write();
  }
  // Close the output file
  f_output->Close();
  cout << Form("Successfully save the output file as %s", f_output->GetName()) << endl;

  // Close the input file
  f_input->Close();


}
