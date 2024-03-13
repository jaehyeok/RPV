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

  TFile *f_input = new TFile(inputfile, "Update");

  TH1F *qcd[52],   	*qcd_jer_up[52],   	*qcd_jer_down[52];
  TH1F *wjets[52], 	*wjets_jer_up[52], 	*wjets_jer_down[52];
  TH1F *ttbar[52], 	*ttbar_jer_up[52], 	*ttbar_jer_down[52];
  TH1F *other[52],      *other_jer_up[52], 	*other_jer_down[52];
  TH1F *signal[13][52], *signal_jer_up[13][52], *signal_jer_down[13][52];

  TH1F *clone_qcd[52],        *clone_qcd_jer_up[52],        *clone_qcd_jer_down[52];
  TH1F *clone_wjets[52],      *clone_wjets_jer_up[52],      *clone_wjets_jer_down[52];
  TH1F *clone_ttbar[52],      *clone_ttbar_jer_up[52],      *clone_ttbar_jer_down[52];
  TH1F *clone_other[52],      *clone_other_jer_up[52],      *clone_other_jer_down[52];
  TH1F *clone_signal[13][52], *clone_signal_jer_up[13][52], *clone_signal_jer_down[13][52];

  // Open the input file
  f_input->cd();
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    // Get the histograms
    qcd[ibin] 	  	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/qcd", ibin)));
    qcd_jer_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/qcd_jer_%sUp", ibin, yr.Data())));
    qcd_jer_down[ibin]    = static_cast<TH1F*>(f_input->Get(Form("/bin%d/qcd_jer_%sDown", ibin, yr.Data())));
    wjets[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/wjets", ibin)));
    wjets_jer_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/wjets_jer_%sUp", ibin, yr.Data())));
    wjets_jer_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/wjets_jer_%sDown", ibin, yr.Data())));
    ttbar[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/ttbar", ibin)));
    ttbar_jer_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/ttbar_jer_%sUp", ibin, yr.Data())));
    ttbar_jer_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/ttbar_jer_%sDown", ibin, yr.Data())));
    other[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other", ibin)));
    other_jer_up[ibin] 	  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_jer_%sUp", ibin, yr.Data())));
    other_jer_down[ibin]  = static_cast<TH1F*>(f_input->Get(Form("/bin%d/other_jer_%sDown", ibin, yr.Data())));
    for(int imass=0; imass<13; imass++) {
      signal[imass][ibin]          = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d", ibin, 1000+imass*100)));
      signal_jer_up[imass][ibin]   = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d_jer_%sUp", ibin, 1000+imass*100, yr.Data())));
      signal_jer_down[imass][ibin] = static_cast<TH1F*>(f_input->Get(Form("/bin%d/signal_M%d_jer_%sDown", ibin, 1000+imass*100, yr.Data())));
    }

    // Clone the histograms
    clone_qcd[ibin] 		= static_cast<TH1F*>(qcd[ibin]->Clone());
    clone_qcd_jer_up[ibin] 	= static_cast<TH1F*>(qcd_jer_up[ibin]->Clone(Form("ratio_qcd_jer_%sUp", year.Data())));
    clone_qcd_jer_down[ibin] 	= static_cast<TH1F*>(qcd_jer_down[ibin]->Clone(Form("ratio_qcd_jer_%sDown", year.Data())));
    clone_wjets[ibin] 		= static_cast<TH1F*>(wjets[ibin]->Clone());
    clone_wjets_jer_up[ibin] 	= static_cast<TH1F*>(wjets_jer_up[ibin]->Clone(Form("ratio_wjets_jer_%sUp", year.Data())));
    clone_wjets_jer_down[ibin] 	= static_cast<TH1F*>(wjets_jer_down[ibin]->Clone(Form("ratio_wjets_jer_%sDown", year.Data())));
    clone_ttbar[ibin] 		= static_cast<TH1F*>(ttbar[ibin]->Clone());
    clone_ttbar_jer_up[ibin] 	= static_cast<TH1F*>(ttbar_jer_up[ibin]->Clone(Form("ratio_ttbar_jer_%sUp", year.Data())));
    clone_ttbar_jer_down[ibin] 	= static_cast<TH1F*>(ttbar_jer_down[ibin]->Clone(Form("ratio_ttbar_jer_%sDown", year.Data())));
    clone_other[ibin] 		= static_cast<TH1F*>(other[ibin]->Clone());
    clone_other_jer_up[ibin] 	= static_cast<TH1F*>(other_jer_up[ibin]->Clone(Form("ratio_other_jer_%sUp", year.Data())));
    clone_other_jer_down[ibin] 	= static_cast<TH1F*>(other_jer_down[ibin]->Clone(Form("ratio_other_jer_%sDown", year.Data())));
    for(int imass=0; imass<13; imass++) {
      clone_signal[imass][ibin] = static_cast<TH1F*>(signal[imass][ibin]->Clone(Form("ratio_signalM%d", 1000+imass*100)));
      clone_signal_jer_up[imass][ibin] = static_cast<TH1F*>(signal_jer_up[imass][ibin]->Clone(Form("ratio_signalM%d_jer_%sUp", 1000+imass*100, yr.Data())));
      clone_signal_jer_down[imass][ibin] = static_cast<TH1F*>(signal_jer_down[imass][ibin]->Clone(Form("ratio_signalM%d_jer_%sDown", 1000+imass*100, yr.Data())));
    }

    // Get the ratio of jer
    clone_qcd_jer_up[ibin]->Divide(clone_qcd[ibin]);
    clone_qcd_jer_down[ibin]->Divide(clone_qcd[ibin]);
    clone_wjets_jer_up[ibin]->Divide(clone_wjets[ibin]);
    clone_wjets_jer_down[ibin]->Divide(clone_wjets[ibin]);
    clone_ttbar_jer_up[ibin]->Divide(clone_ttbar[ibin]);
    clone_ttbar_jer_down[ibin]->Divide(clone_ttbar[ibin]);
    clone_other_jer_up[ibin]->Divide(clone_other[ibin]);
    clone_other_jer_down[ibin]->Divide(clone_other[ibin]);
    for(int imass=0; imass<13; imass++) {
      clone_signal_jer_up[imass][ibin]->Divide(clone_signal[imass][ibin]);
      clone_signal_jer_down[imass][ibin]->Divide(clone_signal[imass][ibin]);
    }

  }

  // FIXME: Need to make the following lines neat
  // QCD
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    cout << "bin: " << ibin << endl;
    for(int imj=0; imj<3; imj++) {
      if(clone_qcd_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_qcd_jer_down[ibin]->GetBinContent(imj+1)<1) {
	continue;
      }
      else if(clone_qcd_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_qcd_jer_down[ibin]->GetBinContent(imj+1)>1) {
	qcd_jer_up[ibin]->SetBinContent(imj+1, qcd[ibin]->GetBinContent(imj+1) + qcd[ibin]->GetBinContent(imj+1)*(clone_qcd_jer_up[ibin]->GetBinContent(imj+1)-1));
	qcd_jer_down[ibin]->SetBinContent(imj+1, qcd[ibin]->GetBinContent(imj+1) - qcd[ibin]->GetBinContent(imj+1)*(clone_qcd_jer_up[ibin]->GetBinContent(imj+1)-1));
      }
      else {
	qcd_jer_up[ibin]->SetBinContent(imj+1, qcd[ibin]->GetBinContent(imj+1) + qcd[ibin]->GetBinContent(imj+1)*(1-clone_qcd_jer_up[ibin]->GetBinContent(imj+1)));
	qcd_jer_down[ibin]->SetBinContent(imj+1, qcd[ibin]->GetBinContent(imj+1) - qcd[ibin]->GetBinContent(imj+1)*(1-clone_qcd_jer_up[ibin]->GetBinContent(imj+1)));
      }

    }
    qcd_jer_up[ibin]->Write(Form("qcd_jer_%sUp", yr.Data()), TObject::kOverwrite);
    qcd_jer_down[ibin]->Write(Form("qcd_jer_%sDown", yr.Data()), TObject::kOverwrite);
  }

  // W+jets
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    cout << "bin: " << ibin << endl;
    for(int imj=0; imj<3; imj++) {
      if(clone_wjets_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_wjets_jer_down[ibin]->GetBinContent(imj+1)<1) {
	continue;
      }
      else if(clone_wjets_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_wjets_jer_down[ibin]->GetBinContent(imj+1)>1) {
	wjets_jer_up[ibin]->SetBinContent(imj+1, wjets[ibin]->GetBinContent(imj+1) + wjets[ibin]->GetBinContent(imj+1)*(clone_wjets_jer_up[ibin]->GetBinContent(imj+1)-1));
	wjets_jer_down[ibin]->SetBinContent(imj+1, wjets[ibin]->GetBinContent(imj+1) - wjets[ibin]->GetBinContent(imj+1)*(clone_wjets_jer_up[ibin]->GetBinContent(imj+1)-1));
      }
      else {
	wjets_jer_up[ibin]->SetBinContent(imj+1, wjets[ibin]->GetBinContent(imj+1) + wjets[ibin]->GetBinContent(imj+1)*(1-clone_wjets_jer_up[ibin]->GetBinContent(imj+1)));
	wjets_jer_down[ibin]->SetBinContent(imj+1, wjets[ibin]->GetBinContent(imj+1) - wjets[ibin]->GetBinContent(imj+1)*(1-clone_wjets_jer_up[ibin]->GetBinContent(imj+1)));
      }

    }
    wjets_jer_up[ibin]->Write(Form("wjets_jer_%sUp", yr.Data()), TObject::kOverwrite);
    wjets_jer_down[ibin]->Write(Form("wjets_jer_%sDown", yr.Data()), TObject::kOverwrite);
  }

  // ttbar
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    cout << "bin: " << ibin << endl;
    for(int imj=0; imj<3; imj++) {
      if(clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_ttbar_jer_down[ibin]->GetBinContent(imj+1)<1) {
	continue;
      }
      else if(clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_ttbar_jer_down[ibin]->GetBinContent(imj+1)>1) {
	ttbar_jer_up[ibin]->SetBinContent(imj+1, ttbar[ibin]->GetBinContent(imj+1) + ttbar[ibin]->GetBinContent(imj+1)*(clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)-1));
	ttbar_jer_down[ibin]->SetBinContent(imj+1, ttbar[ibin]->GetBinContent(imj+1) - ttbar[ibin]->GetBinContent(imj+1)*(clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)-1));
      }
      else {
	ttbar_jer_up[ibin]->SetBinContent(imj+1, ttbar[ibin]->GetBinContent(imj+1) + ttbar[ibin]->GetBinContent(imj+1)*(1-clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)));
	ttbar_jer_down[ibin]->SetBinContent(imj+1, ttbar[ibin]->GetBinContent(imj+1) - ttbar[ibin]->GetBinContent(imj+1)*(1-clone_ttbar_jer_up[ibin]->GetBinContent(imj+1)));
      }

    }
    ttbar_jer_up[ibin]->Write(Form("ttbar_jer_%sUp", yr.Data()), TObject::kOverwrite);
    ttbar_jer_down[ibin]->Write(Form("ttbar_jer_%sDown", yr.Data()), TObject::kOverwrite);
  }

  // other
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    cout << "bin: " << ibin << endl;
    for(int imj=0; imj<3; imj++) {
      if(clone_other_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_other_jer_down[ibin]->GetBinContent(imj+1)<1) {
	continue;
      }
      else if(clone_other_jer_up[ibin]->GetBinContent(imj+1)>1 && clone_other_jer_down[ibin]->GetBinContent(imj+1)>1) {
	other_jer_up[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) + other[ibin]->GetBinContent(imj+1)*(clone_other_jer_up[ibin]->GetBinContent(imj+1)-1));
	other_jer_down[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) - other[ibin]->GetBinContent(imj+1)*(clone_other_jer_up[ibin]->GetBinContent(imj+1)-1));
      }
      else {
	other_jer_up[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) + other[ibin]->GetBinContent(imj+1)*(1-clone_other_jer_up[ibin]->GetBinContent(imj+1)));
	other_jer_down[ibin]->SetBinContent(imj+1, other[ibin]->GetBinContent(imj+1) - other[ibin]->GetBinContent(imj+1)*(1-clone_other_jer_up[ibin]->GetBinContent(imj+1)));
      }

    }
    other_jer_up[ibin]->Write(Form("other_jer_%sUp", yr.Data()), TObject::kOverwrite);
    other_jer_down[ibin]->Write(Form("other_jer_%sDown", yr.Data()), TObject::kOverwrite);
  }

  // signal
  for(int ibin=22; ibin<52; ibin++) {
    gDirectory->cd(Form("/bin%d", ibin));
    for(int imass=0; imass<13; imass++) {
      cout << "bin: " << ibin << endl;
      for(int imj=0; imj<3; imj++) {
        if(clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)>1 && clone_signal_jer_down[imass][ibin]->GetBinContent(imj+1)<1) {
  	  continue;
        }
        else if(clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)>1 && clone_signal_jer_down[imass][ibin]->GetBinContent(imj+1)>1) {
  	  signal_jer_up[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) + signal[imass][ibin]->GetBinContent(imj+1)*(clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)-1));
  	  signal_jer_down[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) - signal[imass][ibin]->GetBinContent(imj+1)*(clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)-1));
        }
        else {
  	  signal_jer_up[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) + signal[imass][ibin]->GetBinContent(imj+1)*(1-clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)));
  	  signal_jer_down[imass][ibin]->SetBinContent(imj+1, signal[imass][ibin]->GetBinContent(imj+1) - signal[imass][ibin]->GetBinContent(imj+1)*(1-clone_signal_jer_up[imass][ibin]->GetBinContent(imj+1)));
        }
  
      }
      signal_jer_up[imass][ibin]->Write(Form("signal_M%d_jer_%sUp", 1000+imass*100, yr.Data()), TObject::kOverwrite);
      signal_jer_down[imass][ibin]->Write(Form("signal_M%d_jer_%sDown", 1000+imass*100, yr.Data()), TObject::kOverwrite);
    }
  }


  // Close the input file
  f_input->Close();


}
