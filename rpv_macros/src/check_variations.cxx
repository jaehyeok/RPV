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

int main(int argc, char *argv[]) {


  TString fname, mglu, year;
  fname = argv[1];
  mglu  = argv[2];
  year  = argv[3];

  TString year_comb, yr;
  year_comb = year;
  if(year=="UL2016_preVFP" || year=="UL2016_postVFP") year_comb="2016";
  else if(year=="UL2017" || year=="UL2018") year_comb="1718";

  if(year=="UL2016_preVFP") yr="2016preVFP";
  else if(year=="UL2016_postVFP") yr="2016postVFP";
  else if(year=="UL2017") yr="2017";
  else if(year=="UL2018") yr="2018";

  TFile* infile = new TFile(fname, "READ");


  TString syst_list[] = {"kappa1", "kappa2", "QCDscale_ren", "QCDscale_fac", "QCDscale", "CMS_eff_lep", 
	  		 "CMS_btag_fixedWP_comb_bc_uncorrelated", "CMS_btag_fixedWP_comb_bc_correlated", "CMS_btag_fixedWP_incl_light_uncorrelated", "CMS_btag_fixedWP_incl_light_correlated", "CMS_scale_j", "CMS_res_j",
			 "CMS_gs", "CMS_pileup", "MC_kappa1", "MC_kappa2", "MC_kappa1_jer", "MC_kappa2_jer",
			 "MC_kappa1_jec", "MC_kappa2_jec",  
			 "mjsyst_r1", "mjsyst_r2"};

  int num_syst = sizeof(syst_list)/sizeof(syst_list[0]);
  cout << num_syst << endl;

  TH1F *qcd[51][num_syst+1][2], *wjets[51][num_syst+1][2], *ttbar[51][num_syst+1][2], *other[51][num_syst+1][2], *signal[51][num_syst+1][2], *data_obs[51];


  infile->cd();
  for(int ibin=22; ibin<51; ibin++) {
    if(ibin==34 || ibin==49) continue;

    int ijet = (ibin-1)%3;
    int ind_ijet = 10*(2*ijet+4) + 2*ijet + 5;
    if(ind_ijet==89) ind_ijet=8;

    gDirectory->cd(Form("/bin%d", ibin));

    qcd[ibin][0][0]    = (TH1F*)infile->Get(Form("bin%d/qcd", ibin));
    wjets[ibin][0][0]  = (TH1F*)infile->Get(Form("bin%d/wjets", ibin));
    ttbar[ibin][0][0]  = (TH1F*)infile->Get(Form("bin%d/ttbar", ibin));
    other[ibin][0][0]  = (TH1F*)infile->Get(Form("bin%d/other", ibin));
    signal[ibin][0][0] = (TH1F*)infile->Get(Form("bin%d/signal_M%s", ibin, mglu.Data()));
    data_obs[ibin]  = (TH1F*)infile->Get(Form("bin%d/data_obs", ibin));

    for(int isyst=0; isyst<num_syst; isyst++) {
      for(int updo=0; updo<2; updo++) {
	TString UpDown = (updo==0) ? "Up" : "Down";
	if(isyst==0 || isyst==1) {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_njets%d_qcd_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_njets%d_wjets_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_njets%d_ttbar_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));

	}
	else if (isyst==2 || isyst==3 || isyst==4) {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_qcd%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_wjets%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_ttbar%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s_other%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s_sig%s", ibin, mglu.Data(), syst_list[isyst].Data(), UpDown.Data()));
	}
	else if (isyst==5 || isyst==6 || isyst==8 || isyst==10 || isyst==11 || isyst==13) {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_%s%s", ibin, syst_list[isyst].Data(), yr.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_%s%s", ibin, syst_list[isyst].Data(), yr.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_%s%s", ibin, syst_list[isyst].Data(), yr.Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s_%s%s", ibin, syst_list[isyst].Data(), yr.Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s_%s%s", ibin, mglu.Data(), syst_list[isyst].Data(), yr.Data(), UpDown.Data()));
	}
	else if (isyst==14 || isyst==15 || isyst==16 || isyst==17 || isyst==18 || isyst==19) {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_njets%d_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_njets%d_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_njets%d_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
	}
	else if(isyst==20 || isyst==21) {
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_njets%d_wjets_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_njets%d_ttbar_%s%s", ibin, syst_list[isyst].Data(), ind_ijet, year_comb.Data(), UpDown.Data()));
	}
	else {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s%s", ibin, syst_list[isyst].Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s%s", ibin, mglu.Data(), syst_list[isyst].Data(), UpDown.Data()));
	}
      }
    }
  }

  for(int ibin=22; ibin<37; ibin++) {
    cout << endl;
    cout << "bin" << ibin << endl;
    if (ibin==34) continue;
    for(int isyst=0; isyst<num_syst; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      for(int updo=0; updo<2; updo++) {

	//
	for(int imj=1; imj<4; imj++) {
	  if (qcd[ibin][0][0]->GetBinContent(imj)==0)    qcd[ibin][0][0]->SetBinContent(imj,1000);
	  if (wjets[ibin][0][0]->GetBinContent(imj)==0)  wjets[ibin][0][0]->SetBinContent(imj,1000);
	  if (ttbar[ibin][0][0]->GetBinContent(imj)==0)  ttbar[ibin][0][0]->SetBinContent(imj,1000);
	  if (other[ibin][0][0]->GetBinContent(imj)==0)  other[ibin][0][0]->SetBinContent(imj,1000);
	  if (signal[ibin][0][0]->GetBinContent(imj)==0) signal[ibin][0][0]->SetBinContent(imj,1000);
	}
	//

	TString UpDown = (updo==0) ? "Up" : "Down";
	cout << "  [" << UpDown << "]" << endl;
	if (isyst==20 || isyst==21) {
	  cout << "            wjets:  MJ[1] " << wjets[ibin][isyst+1][updo]->GetBinContent(1)/wjets[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << wjets[ibin][isyst+1][updo]->GetBinContent(2)/wjets[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << wjets[ibin][isyst+1][updo]->GetBinContent(3)/wjets[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            ttbar:  MJ[1] " << ttbar[ibin][isyst+1][updo]->GetBinContent(1)/ttbar[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << ttbar[ibin][isyst+1][updo]->GetBinContent(2)/ttbar[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << ttbar[ibin][isyst+1][updo]->GetBinContent(3)/ttbar[ibin][0][0]->GetBinContent(3) << endl;
	}
	else if (isyst==0 || isyst==1 || (isyst>13 && isyst<20)) {
	  cout << "            qcd:    MJ[1] " << qcd[ibin][isyst+1][updo]->GetBinContent(1)/qcd[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << qcd[ibin][isyst+1][updo]->GetBinContent(2)/qcd[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << qcd[ibin][isyst+1][updo]->GetBinContent(3)/qcd[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            wjets:  MJ[1] " << wjets[ibin][isyst+1][updo]->GetBinContent(1)/wjets[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << wjets[ibin][isyst+1][updo]->GetBinContent(2)/wjets[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << wjets[ibin][isyst+1][updo]->GetBinContent(3)/wjets[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            ttbar:  MJ[1] " << ttbar[ibin][isyst+1][updo]->GetBinContent(1)/ttbar[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << ttbar[ibin][isyst+1][updo]->GetBinContent(2)/ttbar[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << ttbar[ibin][isyst+1][updo]->GetBinContent(3)/ttbar[ibin][0][0]->GetBinContent(3) << endl;
	}
	else {
	  cout << "            qcd:    MJ[1] " << qcd[ibin][isyst+1][updo]->GetBinContent(1)/qcd[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << qcd[ibin][isyst+1][updo]->GetBinContent(2)/qcd[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << qcd[ibin][isyst+1][updo]->GetBinContent(3)/qcd[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            wjets:  MJ[1] " << wjets[ibin][isyst+1][updo]->GetBinContent(1)/wjets[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << wjets[ibin][isyst+1][updo]->GetBinContent(2)/wjets[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << wjets[ibin][isyst+1][updo]->GetBinContent(3)/wjets[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            ttbar:  MJ[1] " << ttbar[ibin][isyst+1][updo]->GetBinContent(1)/ttbar[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << ttbar[ibin][isyst+1][updo]->GetBinContent(2)/ttbar[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << ttbar[ibin][isyst+1][updo]->GetBinContent(3)/ttbar[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            other:  MJ[1] " << other[ibin][isyst+1][updo]->GetBinContent(1)/other[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << other[ibin][isyst+1][updo]->GetBinContent(2)/other[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << other[ibin][isyst+1][updo]->GetBinContent(3)/other[ibin][0][0]->GetBinContent(3) << endl;
	  cout << "            signal: MJ[1] " << signal[ibin][isyst+1][updo]->GetBinContent(1)/signal[ibin][0][0]->GetBinContent(1) << endl;
	  cout << "                    MJ[2] " << signal[ibin][isyst+1][updo]->GetBinContent(2)/signal[ibin][0][0]->GetBinContent(2) << endl;
	  cout << "                    MJ[3] " << signal[ibin][isyst+1][updo]->GetBinContent(3)/signal[ibin][0][0]->GetBinContent(3) << endl;
	}
      }
    }
  }



  return 0;
}















