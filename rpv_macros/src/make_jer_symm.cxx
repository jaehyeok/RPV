// 2024.2.26 //
// Both +1 sigma and -1 sigma systematic effects of Jet Energy Resolution exhibit a tendency to be larger than nominal value (not imposing syst. effect), which causes hindrance during the global fit.
// Therefore, we aim to make the effects of JER symmetric.

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
    cout << "[example]: ./run/make_jer_symm.exe 2017 variations/output_impact_2017_20178.root" << endl;
    return 0;
  }
  if(!(year=="UL2016_preVFP" || year=="UL2016_postVFP" || year=="UL2017" || year=="UL2018")) {
    cout << "year should be UL2016_preVFP, UL2016_postVFP, UL2017, or UL2018" << endl;
    return 0;
  }

  getOtherMuSyst(year, inputfile);

  return 0;
}

void getOtherMuSyst(TString year, TString inputfile)
{
  TH1::SetDefaultSumw2();

  TString yr;
  if(year=="UL2016_preVFP") yr="2016preVFP";
  else if(year=="UL2016_postVFP") yr="2016postVFP";
  else if(year=="UL2017") yr="2017";
  else if(year=="UL2018") yr="2018";

  TFile *f_input = new TFile(inputfile, "Update");

  TH1F *other[52],      *other_jer_up[52], 	*other_jer_down[52];
  TH1F *signal[13][52], *signal_jer_up[13][52], *signal_jer_down[13][52];

  TH1F *clone_other[52],      *clone_other_jer_up[52],      *clone_other_jer_down[52];
  TH1F *clone_signal[13][52], *clone_signal_jer_up[13][52], *clone_signal_jer_down[13][52];

  // Open the input file
  f_input->cd();
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    // Get the histograms
    other[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other", ibin)));
    other_jer_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_CMS_res_j_%sUp", ibin, yr.Data())));
    other_jer_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_CMS_res_j_%sDown", ibin, yr.Data())));
    for(int imass=0; imass<13; imass++) {
      signal[imass][ibin]          = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d", ibin, 1000+imass*100)));
      signal_jer_up[imass][ibin]   = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d_CMS_res_j_%sUp", ibin, 1000+imass*100, yr.Data())));
      signal_jer_down[imass][ibin] = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d_CMS_res_j_%sDown", ibin, 1000+imass*100, yr.Data())));
    }

    // Clone the histograms
    clone_other[ibin] 		= static_cast<TH1F*>(other[ibin]->Clone());
    clone_other_jer_up[ibin] 	= static_cast<TH1F*>(other_jer_up[ibin]->Clone(Form("ratio_other_jer_%sUp", year.Data())));
    clone_other_jer_down[ibin] 	= static_cast<TH1F*>(other_jer_down[ibin]->Clone(Form("ratio_other_jer_%sDown", year.Data())));
    for(int imass=0; imass<13; imass++) {
      clone_signal[imass][ibin] = static_cast<TH1F*>(signal[imass][ibin]->Clone(Form("ratio_signalM%d", 1000+imass*100)));
      clone_signal_jer_up[imass][ibin] = static_cast<TH1F*>(signal_jer_up[imass][ibin]->Clone(Form("ratio_signalM%d_jer_%sUp", 1000+imass*100, year.Data())));
      clone_signal_jer_down[imass][ibin] = static_cast<TH1F*>(signal_jer_down[imass][ibin]->Clone(Form("ratio_signalM%d_jer_%sDown", 1000+imass*100, year.Data())));
    }

    // Get the ratio of jer
    clone_other_jer_up[ibin]->Divide(clone_other[ibin]);
    clone_other_jer_down[ibin]->Divide(clone_other[ibin]);
    for(int imass=0; imass<13; imass++) {
      clone_signal_jer_up[imass][ibin]->Divide(clone_signal[imass][ibin]);
      clone_signal_jer_down[imass][ibin]->Divide(clone_signal[imass][ibin]);
    }

  }

  // Make JER symmetric
    // other
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    cout << "bin: " << ibin << endl;
    for(int imj=0; imj<3; imj++) {
      other_jer_up[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) + other[ibin]->GetBinContent(imj+1)*TMath::Abs((clone_other_jer_up[ibin]->GetBinContent(imj+1)-1)));
      other_jer_down[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) - other[ibin]->GetBinContent(imj+1)*TMath::Abs((clone_other_jer_up[ibin]->GetBinContent(imj+1)-1)));

    }
    other_jer_up[ibin]->Write(Form("other_jer_%sUp", year.Data()), TObject::kOverwrite);
    other_jer_down[ibin]->Write(Form("other_jer_%sDown", year.Data()), TObject::kOverwrite);
//    cout << Form("MJ[1]  %3.1f : %3.1f : %3.1f", other_jer_down[ibin]->GetBinContent(1), other[ibin]->GetBinContent(1), other_jer_up[ibin]->GetBinContent(1)) << endl;
//    cout << Form("MJ[2]  %3.1f : %3.1f : %3.1f", other_jer_down[ibin]->GetBinContent(2), other[ibin]->GetBinContent(2), other_jer_up[ibin]->GetBinContent(2)) << endl;
//    cout << Form("MJ[3]  %3.1f : %3.1f : %3.1f", other_jer_down[ibin]->GetBinContent(3), other[ibin]->GetBinContent(3), other_jer_up[ibin]->GetBinContent(3)) << endl;
  }

    // signal
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    for(int imass=0; imass<13; imass++) {
      cout << "bin: " << ibin << endl;
      for(int imj=0; imj<3; imj++) {
  	signal_jer_up[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) + signal[imass][ibin]->GetBinContent(imj+1)*TMath::Abs((clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)-1)));
  	signal_jer_down[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) - signal[imass][ibin]->GetBinContent(imj+1)*TMath::Abs((clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)-1)));
  
      }
      signal_jer_up[imass][ibin]->Write(Form("signal_M%d_jer_%sUp", 1000+imass*100, year.Data()), TObject::kOverwrite);
      signal_jer_down[imass][ibin]->Write(Form("signal_M%d_jer_%sDown", 1000+imass*100, year.Data()), TObject::kOverwrite);
//      cout << Form("MJ[1]  %3.1f : %3.1f : %3.1f", signal_jer_down[imass][ibin]->GetBinContent(1), signal[imass][ibin]->GetBinContent(1), signal_jer_up[imass][ibin]->GetBinContent(1)) << endl;
//      cout << Form("MJ[2]  %3.1f : %3.1f : %3.1f", signal_jer_down[imass][ibin]->GetBinContent(2), signal[imass][ibin]->GetBinContent(2), signal_jer_up[imass][ibin]->GetBinContent(2)) << endl;
//      cout << Form("MJ[3]  %3.1f : %3.1f : %3.1f", signal_jer_down[imass][ibin]->GetBinContent(3), signal[imass][ibin]->GetBinContent(3), signal_jer_up[imass][ibin]->GetBinContent(3)) << endl;
    }
  }


  // Close the input file
  f_input->Close();


}
