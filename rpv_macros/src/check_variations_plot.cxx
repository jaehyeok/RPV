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

int linecolor(unsigned int isyst){
/*
  int icolor;
  if(isyst==0) icolor=3;
  else if(isyst==1) icolor=3;
  else if(isyst==2) icolor=7;
  else if(isyst==3) icolor=13; //
  else if(isyst==4) icolor=21; //
  else if(isyst==5) icolor=28;
  else if(isyst==6) icolor=38;
  else if(isyst==7) icolor=46;
  else if(isyst==8) icolor=51;
  else if(isyst==9) icolor=87;
  else if(isyst==10) icolor=95;
  else if(isyst==11) icolor=3;
  else if(isyst==12) icolor=6;
//  21
*/
  int icolor;
  if(isyst==0)       icolor=1;
  else if(isyst==1)  icolor=2;
  else if(isyst==2)  icolor=3;
  else if(isyst==3)  icolor=4;
  else if(isyst==4)  icolor=64;
  else if(isyst==5)  icolor=6;
  else if(isyst==6)  icolor=7;
  else if(isyst==7)  icolor=8;
  else if(isyst==8)  icolor=9;
  else if(isyst==9)  icolor=28;
  else if(isyst==10) icolor=30;
  else if(isyst==11) icolor=38;
  else if(isyst==12) icolor=41;
  else if(isyst==13) icolor=42;
  else if(isyst==14) icolor=46;
  else if(isyst==15) icolor=50;
  else if(isyst==16) icolor=51;
  else if(isyst==17) icolor=54;
  else if(isyst==18) icolor=56;
  else if(isyst==19) icolor=58;
  else if(isyst==20) icolor=61;
  else if(isyst==21) icolor=62;
  return icolor;
}

int main(int argc, char *argv[]) {
	
  gStyle->SetOptStat(0);

  TString fname, mglu, year;
  fname = argv[1];
  mglu  = argv[2];
  year  = argv[3];

  TString year_comb;
  year_comb = year;
  if(year=="UL2016_preVFP" || year=="UL2016_postVFP") year_comb="UL2016";
  else if(year=="UL2017" || year=="UL2018") year_comb="UL20178";

  TFile* infile = new TFile(fname, "READ");


  TString syst_list[] = {"kappa1", "kappa2", "mur", "murf", "muf", "lep_eff", 
	  		 "btag_udsg_uncor", "btag_udsg_cor", "btag_bc_uncor", "btag_bc_cor", "jec", "jer",
			 "gs", "pileup", "MC_kappa1", "MC_kappa2", "MC_kappa1_jer", "MC_kappa2_jer",
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
    qcd[ibin][0][1]    = (TH1F*)infile->Get(Form("bin%d/qcd", ibin));
    wjets[ibin][0][1]  = (TH1F*)infile->Get(Form("bin%d/wjets", ibin));
    ttbar[ibin][0][1]  = (TH1F*)infile->Get(Form("bin%d/ttbar", ibin));
    other[ibin][0][1]  = (TH1F*)infile->Get(Form("bin%d/other", ibin));
    signal[ibin][0][1] = (TH1F*)infile->Get(Form("bin%d/signal_M%s", ibin, mglu.Data()));
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
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_qcd_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_wjets_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_ttbar_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s_other_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s_sig_%s%s", ibin, mglu.Data(), syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
	}
	else if (isyst==6 || isyst==8 || isyst==10 || isyst==11) {
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_%s%s", ibin, syst_list[isyst].Data(), year.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_%s%s", ibin, syst_list[isyst].Data(), year.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_%s%s", ibin, syst_list[isyst].Data(), year.Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s_%s%s", ibin, syst_list[isyst].Data(), year.Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s_%s%s", ibin, mglu.Data(), syst_list[isyst].Data(), year.Data(), UpDown.Data()));
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
          qcd[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/qcd_%s_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          wjets[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/wjets_%s_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          ttbar[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/ttbar_%s_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          other[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/other_%s_%s%s", ibin, syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
          signal[ibin][isyst+1][updo] = (TH1F*)infile->Get(Form("bin%d/signal_M%s_%s_%s%s", ibin, mglu.Data(), syst_list[isyst].Data(), year_comb.Data(), UpDown.Data()));
	}
      }
    }
  }

  cout << "QCD" << endl;

  cout << "UP" << endl;
  TCanvas* c_qcd_up = new TCanvas("c_qcd_up", "c_qcd_up", 2000, 1200);
  c_qcd_up->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_qcd_up->cd(ibin-21);

    TLegend* leg_qcd = new TLegend(0.5,0.11,0.89,0.89);
    leg_qcd->SetNColumns(3);
    if(ibin==34) {
      qcd[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{QCD up}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst-2; isyst++) {
        leg_qcd->AddEntry(qcd[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_qcd->AddEntry(qcd[22][0][0], "nominal", "l");
      leg_qcd->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst-2; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      qcd[ibin][isyst][0]->GetYaxis()->SetRangeUser(0.1, 1.5*qcd[ibin][isyst][0]->GetMaximum());
      qcd[ibin][isyst][0]->SetLineColor(linecolor(isyst));
      qcd[ibin][isyst][0]->Draw("hist same");
//      leg_qcd->AddEntry(qcd[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_qcd->AddEntry(qcd[ibin][0][0], "nominal", "l");
//    leg_qcd->Draw();
  }
  c_qcd_up->Print(Form("plots_variations_qcd_up_%s.pdf", year.Data()));


  cout << "Down" << endl;
  TCanvas* c_qcd_down = new TCanvas("c_qcd_down", "c_qcd_down", 2000, 1200);
  c_qcd_down->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_qcd_down->cd(ibin-21);

    TLegend* leg_qcd = new TLegend(0.5,0.11,0.89,0.89);
    leg_qcd->SetNColumns(3);
    if(ibin==34) {
      qcd[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{QCD down}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst-2; isyst++) {
        leg_qcd->AddEntry(qcd[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_qcd->AddEntry(qcd[22][0][0], "nominal", "l");
      leg_qcd->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst-2; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      qcd[ibin][isyst][1]->GetYaxis()->SetRangeUser(0.1, 1.5*qcd[ibin][isyst][0]->GetMaximum());
      qcd[ibin][isyst][1]->SetLineColor(linecolor(isyst));
      qcd[ibin][isyst][1]->Draw("hist same");
//      leg_qcd->AddEntry(qcd[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_qcd->AddEntry(qcd[ibin][0][0], "nominal", "l");
//    leg_qcd->Draw();
  }
  c_qcd_down->Print(Form("plots_variations_qcd_down_%s.pdf", year.Data()));




  cout << "ttbar" << endl;

  cout << "UP" << endl;
  TCanvas* c_ttbar_up = new TCanvas("c_ttbar_up", "c_ttbar_up", 2000, 1200);
  c_ttbar_up->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_ttbar_up->cd(ibin-21);

    TLegend* leg_ttbar = new TLegend(0.5,0.11,0.89,0.89);
    leg_ttbar->SetNColumns(3);
    if(ibin==34) {
      ttbar[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{ttbar up}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst; isyst++) {
        leg_ttbar->AddEntry(ttbar[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_ttbar->AddEntry(ttbar[22][0][0], "nominal", "l");
      leg_ttbar->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      ttbar[ibin][isyst][0]->GetYaxis()->SetRangeUser(0.1, 1.5*ttbar[ibin][isyst][0]->GetMaximum());
      ttbar[ibin][isyst][0]->SetLineColor(linecolor(isyst));
      ttbar[ibin][isyst][0]->Draw("hist same");
//      leg_ttbar->AddEntry(ttbar[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_ttbar->AddEntry(ttbar[ibin][0][0], "nominal", "l");
//    leg_ttbar->Draw();
  }
  c_ttbar_up->Print(Form("plots_variations_ttbar_up_%s.pdf", year.Data()));


  cout << "Down" << endl;
  TCanvas* c_ttbar_down = new TCanvas("c_ttbar_down", "c_ttbar_down", 2000, 1200);
  c_ttbar_down->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_ttbar_down->cd(ibin-21);

    TLegend* leg_ttbar = new TLegend(0.5,0.11,0.89,0.89);
    leg_ttbar->SetNColumns(3);
    if(ibin==34) {
      ttbar[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{ttbar down}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst; isyst++) {
        leg_ttbar->AddEntry(ttbar[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_ttbar->AddEntry(ttbar[22][0][0], "nominal", "l");
      leg_ttbar->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      ttbar[ibin][isyst][1]->GetYaxis()->SetRangeUser(0.1, 1.5*ttbar[ibin][isyst][0]->GetMaximum());
      ttbar[ibin][isyst][1]->SetLineColor(linecolor(isyst));
      ttbar[ibin][isyst][1]->Draw("hist same");
//      leg_ttbar->AddEntry(ttbar[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_ttbar->AddEntry(ttbar[ibin][0][0], "nominal", "l");
//    leg_ttbar->Draw();
  }
  c_ttbar_down->Print(Form("plots_variations_ttbar_down_%s.pdf", year.Data()));




  cout << "wjets" << endl;

  cout << "UP" << endl;
  TCanvas* c_wjets_up = new TCanvas("c_wjets_up", "c_wjets_up", 2000, 1200);
  c_wjets_up->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_wjets_up->cd(ibin-21);

    TLegend* leg_wjets = new TLegend(0.5,0.11,0.89,0.89);
    leg_wjets->SetNColumns(3);
    if(ibin==34) {
      wjets[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{wjets up}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst; isyst++) {
        leg_wjets->AddEntry(wjets[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_wjets->AddEntry(wjets[22][0][0], "nominal", "l");
      leg_wjets->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      wjets[ibin][isyst][0]->GetYaxis()->SetRangeUser(0.1, 1.5*wjets[ibin][isyst][0]->GetMaximum());
      wjets[ibin][isyst][0]->SetLineColor(linecolor(isyst));
      wjets[ibin][isyst][0]->Draw("hist same");
//      leg_wjets->AddEntry(wjets[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_wjets->AddEntry(wjets[ibin][0][0], "nominal", "l");
//    leg_wjets->Draw();
  }
  c_wjets_up->Print(Form("plots_variations_wjets_up_%s.pdf", year.Data()));


  cout << "Down" << endl;
  TCanvas* c_wjets_down = new TCanvas("c_wjets_down", "c_wjets_down", 2000, 1200);
  c_wjets_down->Divide(3,5);
  for(int ibin=22; ibin<37; ibin++) {
    cout << "ibin: " << ibin << endl;
    c_wjets_down->cd(ibin-21);

    TLegend* leg_wjets = new TLegend(0.5,0.11,0.89,0.89);
    leg_wjets->SetNColumns(3);
    if(ibin==34) {
      wjets[22][0][0]->Draw("AXIS");
      TLatex* bin_34 = new TLatex(0.2, 0.5, Form("#splitline{wjets down}{%s}", year.Data()));
      bin_34->SetTextSize(0.1);
      bin_34->SetNDC();
      bin_34->Draw();
      for(int isyst=0; isyst<num_syst; isyst++) {
        leg_wjets->AddEntry(wjets[22][isyst+1][0], syst_list[isyst], "l");
      }
      leg_wjets->AddEntry(wjets[22][0][0], "nominal", "l");
      leg_wjets->Draw();
      continue;
    }

    gPad->SetLogy();
    for(int isyst=0; isyst<num_syst; isyst++) {
      cout << "syst: " << syst_list[isyst] << endl;
      wjets[ibin][isyst][1]->GetYaxis()->SetRangeUser(0.1, 1.5*wjets[ibin][isyst][0]->GetMaximum());
      wjets[ibin][isyst][1]->SetLineColor(linecolor(isyst));
      wjets[ibin][isyst][1]->Draw("hist same");
//      leg_wjets->AddEntry(wjets[ibin][isyst+1][0], syst_list[isyst], "l");
    }
//    leg_wjets->AddEntry(wjets[ibin][0][0], "nominal", "l");
//    leg_wjets->Draw();
  }
  c_wjets_down->Print(Form("plots_variations_wjets_down_%s.pdf", year.Data()));









  /*
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
  */



  return 0;
}















