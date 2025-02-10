#include <iostream> 
#include <vector> 
#include <iomanip> 

#include "TStyle.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TMath.h"

using namespace std;

bool formatLatex=true;

float getKappaUnc(TString filename, TString procname, int ikap, int ibin, TString syst, TString updown);

//
// main
//
int main(int argc, char* argv[])
{
    TString year     = argv[1];
    TString filename = argv[2];

    TFile* infile = TFile::Open(filename, "READ"); 

    const int nbins = 37;
    float kap_qcd_up[2][nbins],     mckap_qcd_up[2][nbins],     mjsyst_qcd_up[2][nbins],                                      tot_qcd_up[2][nbins],
          kap_qcd_down[2][nbins],   mckap_qcd_down[2][nbins],   mjsyst_qcd_down[2][nbins],                                    tot_qcd_down[2][nbins],
          kap_wjets_up[2][nbins],   mckap_wjets_up[2][nbins],   mjsyst_wjets_up[2][nbins],   mjshape_dy_wjets_up[2][nbins],   tot_wjets_up[2][nbins],
          kap_wjets_down[2][nbins], mckap_wjets_down[2][nbins], mjsyst_wjets_down[2][nbins], mjshape_dy_wjets_down[2][nbins], tot_wjets_down[2][nbins],
          kap_ttbar_up[2][nbins],   mckap_ttbar_up[2][nbins],   mjsyst_ttbar_up[2][nbins],                                    tot_ttbar_up[2][nbins],
          kap_ttbar_down[2][nbins], mckap_ttbar_down[2][nbins], mjsyst_ttbar_down[2][nbins],                                  tot_ttbar_down[2][nbins];

    TString notapply = "-";
    TString noyield  = "x";

    // Initialize arrays
    for(int ibin=0; ibin<nbins; ibin++) {

      if(ibin==34) continue; // Exclude bin34. This bin is merged with bin31.
      for(int ikap=0; ikap<2; ikap++) {
        kap_qcd_up[ikap][ibin]=0;     mckap_qcd_up[ikap][ibin]=0;     mjsyst_qcd_up[ikap][ibin]=0;                                       tot_qcd_up[ikap][ibin]=0;
        kap_qcd_down[ikap][ibin]=0;   mckap_qcd_down[ikap][ibin]=0;   mjsyst_qcd_down[ikap][ibin]=0;                                     tot_qcd_down[ikap][ibin]=0;
        kap_wjets_up[ikap][ibin]=0;   mckap_wjets_up[ikap][ibin]=0;   mjsyst_wjets_up[ikap][ibin]=0;   mjshape_dy_wjets_up[2][nbins];    tot_wjets_up[ikap][ibin]=0;
        kap_wjets_down[ikap][ibin]=0; mckap_wjets_down[ikap][ibin]=0; mjsyst_wjets_down[ikap][ibin]=0; mjshape_dy_wjets_down[2][nbins];  tot_wjets_down[ikap][ibin]=0;
        kap_ttbar_up[ikap][ibin]=0;   mckap_ttbar_up[ikap][ibin]=0;   mjsyst_ttbar_up[ikap][ibin]=0;                                     tot_ttbar_up[ikap][ibin]=0;
        kap_ttbar_down[ikap][ibin]=0; mckap_ttbar_down[ikap][ibin]=0; mjsyst_ttbar_down[ikap][ibin]=0;                                   tot_ttbar_down[ikap][ibin]=0;
      }
    }
    for(int ibin=22; ibin<nbins; ibin++) {
      if(ibin==34) continue;
      for(int ikap=0; ikap<2; ikap++) {
        kap_qcd_up[ikap][ibin]            = getKappaUnc(filename, "qcd", ikap+1, ibin, "kappa", "up");
        kap_qcd_down[ikap][ibin]          = getKappaUnc(filename, "qcd", ikap+1, ibin, "kappa", "down");
        mckap_qcd_up[ikap][ibin]          = getKappaUnc(filename, "qcd", ikap+1, ibin, "mckappa", "up");
        mckap_qcd_down[ikap][ibin]        = getKappaUnc(filename, "qcd", ikap+1, ibin, "mckappa", "down");
        mjsyst_qcd_up[ikap][ibin]         = getKappaUnc(filename, "qcd", ikap+1, ibin, "mjsyst", "up");
        mjsyst_qcd_down[ikap][ibin]       = getKappaUnc(filename, "qcd", ikap+1, ibin, "mjsyst", "down");
	tot_qcd_up[ikap][ibin]            = TMath::Sqrt(TMath::Power(kap_qcd_up[ikap][ibin], 2) + TMath::Power(mckap_qcd_up[ikap][ibin], 2) + TMath::Power(mjsyst_qcd_up[ikap][ibin], 2));
	tot_qcd_down[ikap][ibin]          = TMath::Sqrt(TMath::Power(kap_qcd_down[ikap][ibin], 2) + TMath::Power(mckap_qcd_down[ikap][ibin], 2) + TMath::Power(mjsyst_qcd_down[ikap][ibin], 2));

        kap_wjets_up[ikap][ibin]          = getKappaUnc(filename, "wjets", ikap+1, ibin, "kappa", "up");
        kap_wjets_down[ikap][ibin]        = getKappaUnc(filename, "wjets", ikap+1, ibin, "kappa", "down");
        mckap_wjets_up[ikap][ibin]        = getKappaUnc(filename, "wjets", ikap+1, ibin, "mckappa", "up");
        mckap_wjets_down[ikap][ibin]      = getKappaUnc(filename, "wjets", ikap+1, ibin, "mckappa", "down");
        mjsyst_wjets_up[ikap][ibin]       = getKappaUnc(filename, "wjets", ikap+1, ibin, "mjsyst", "up");
        mjsyst_wjets_down[ikap][ibin]     = getKappaUnc(filename, "wjets", ikap+1, ibin, "mjsyst", "down");
        mjshape_dy_wjets_up[ikap][ibin]   = getKappaUnc(filename, "wjets", ikap+1, ibin, "mjshape_dy", "up");
        mjshape_dy_wjets_down[ikap][ibin] = getKappaUnc(filename, "wjets", ikap+1, ibin, "mjshape_dy", "down");
	tot_wjets_up[ikap][ibin]          = TMath::Sqrt(TMath::Power(kap_wjets_up[ikap][ibin], 2) + TMath::Power(mckap_wjets_up[ikap][ibin], 2) + TMath::Power(mjsyst_wjets_up[ikap][ibin], 2) + TMath::Power(mjshape_dy_wjets_up[ikap][ibin], 2));
	tot_wjets_down[ikap][ibin]        = TMath::Sqrt(TMath::Power(kap_wjets_down[ikap][ibin], 2) + TMath::Power(mckap_wjets_down[ikap][ibin], 2) + TMath::Power(mjsyst_wjets_down[ikap][ibin], 2) + TMath::Power(mjshape_dy_wjets_down[ikap][ibin], 2));

        kap_ttbar_up[ikap][ibin]          = getKappaUnc(filename, "ttbar", ikap+1, ibin, "kappa", "up");
        kap_ttbar_down[ikap][ibin]        = getKappaUnc(filename, "ttbar", ikap+1, ibin, "kappa", "down");
        mckap_ttbar_up[ikap][ibin]        = getKappaUnc(filename, "ttbar", ikap+1, ibin, "mckappa", "up");
        mckap_ttbar_down[ikap][ibin]      = getKappaUnc(filename, "ttbar", ikap+1, ibin, "mckappa", "down");
        mjsyst_ttbar_up[ikap][ibin]       = getKappaUnc(filename, "ttbar", ikap+1, ibin, "mjsyst", "up");
        mjsyst_ttbar_down[ikap][ibin]     = getKappaUnc(filename, "ttbar", ikap+1, ibin, "mjsyst", "down");
	tot_ttbar_up[ikap][ibin]          = TMath::Sqrt(TMath::Power(kap_ttbar_up[ikap][ibin], 2) + TMath::Power(mckap_ttbar_up[ikap][ibin], 2) + TMath::Power(mjsyst_ttbar_up[ikap][ibin], 2));
	tot_ttbar_down[ikap][ibin]        = TMath::Sqrt(TMath::Power(kap_ttbar_down[ikap][ibin], 2) + TMath::Power(mckap_ttbar_down[ikap][ibin], 2) + TMath::Power(mjsyst_ttbar_down[ikap][ibin], 2));
      }
    }
    for(int ibin=22; ibin<nbins; ibin++) {
      if(ibin==34) continue;
      for(int ikap=0; ikap<2; ikap++) {
	cout << "kap" << ikap+1 << endl;
	cout << "[bin" << ibin << "] qcd kappa up  : "   <<  kap_qcd_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] qcd kappa down: "   <<  kap_qcd_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] qcd mckappa up  : " <<  mckap_qcd_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] qcd mckappa down: " <<  mckap_qcd_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] qcd mjsyst up  : "  <<  mjsyst_qcd_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] qcd mjsyst down: "  <<  mjsyst_qcd_down[ikap][ibin] << endl;
	cout << endl;
      }
    }
    for(int ibin=22; ibin<nbins; ibin++) {
      if(ibin==34) continue;
      for(int ikap=0; ikap<2; ikap++) {
	cout << "kap" << ikap+1 << endl;
	cout << "[bin" << ibin << "] wjets kappa up  : "       <<  kap_wjets_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets kappa down: "       <<  kap_wjets_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mckappa up  : "     <<  mckap_wjets_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mckappa down: "     <<  mckap_wjets_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mjsyst up  : "      <<  mjsyst_wjets_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mjsyst down: "      <<  mjsyst_wjets_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mjshape_dy up  : "  <<  mjshape_dy_wjets_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] wjets mjshape_dy down: "  <<  mjshape_dy_wjets_down[ikap][ibin] << endl;
	cout << endl;
      }
    }
    for(int ibin=22; ibin<nbins; ibin++) {
      if(ibin==34) continue;
      for(int ikap=0; ikap<2; ikap++) {
	cout << "kap" << ikap+1 << endl;
	cout << "[bin" << ibin << "] ttbar kappa up  : " <<  kap_ttbar_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] ttbar kappa down: " <<  kap_ttbar_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] ttbar mckappa up  : " <<  mckap_ttbar_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] ttbar mckappa down: " <<  mckap_ttbar_down[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] ttbar mjsyst up  : " <<  mjsyst_ttbar_up[ikap][ibin] << endl;
	cout << "[bin" << ibin << "] ttbar mjsyst down: " <<  mjsyst_ttbar_down[ikap][ibin] << endl;
	cout << endl;
      }
    }

    // -----------------------------------------------------
    // table for AN
    // -----------------------------------------------------
    
    ///////////////////////////////////
    /////////////// QCD ///////////////
    ///////////////////////////////////

    TString latex_year;
    latex_year=year;
    if(year=="UL2016_preVFP") latex_year="2016preVFP";
    else if(year=="UL2016_postVFP") latex_year="2016postVFP";
    else if(year=="UL2017") latex_year="2017";
    else if(year=="UL2018") latex_year="2018";

    if(formatLatex) {
      cout << "\\begin{table}" << endl;
      cout << "\\centering" << endl;
      cout << Form("\\caption{The summary table of the uncertainties in the kappa factor for QCD process using %s samples.}", latex_year.Data()) << endl;
      cout << "\\resizebox{\\textwidth}{!}{" << endl;
      cout << "\\begin{tabular}[tbp!]{|c|c|cccccccc|cccccccc|cccccccc|}" << endl;
      cout << "\\hline" << endl;
      cout << "\\multicolumn{2}{|c|}{\\multirow{3}{*}{}} & \\multicolumn{8}{c|}{$4\\leq \\Njet \\leq5$} & \\multicolumn{8}{c|}{$6\\leq \\Njet \\leq7$} & \\multicolumn{8}{c|}{$8\\leq \\Njet$} \\\\" << endl;
      cout << "\\hline\\hline" << endl;
      
      cout << " \\multicolumn{2}{|c|}{} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} \\\\" << endl;
      cout << "\\multicolumn{2}{|c|}{} & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ \\\\" << endl;
      cout << "\\hline" << endl;
      for(int ibin=23; ibin<nbins; ibin+=3) {
        int inb = int(ibin-23)/3;
        if(inb==0) {
      	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_qcd_up[0][ibin-1])    << " & " << Form("%.2f", kap_qcd_up[1][ibin-1])    << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin-1])    << " & " << Form("%.2f", tot_qcd_up[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_qcd_up[0][ibin])      << " & " << Form("%.2f", kap_qcd_up[1][ibin])      << " & "
               << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
               << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin])      << " & " << Form("%.2f", tot_qcd_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_up[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_up[1][ibin+1])    << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_qcd_down[0][ibin-1])    << " & " << Form("%.2f", kap_qcd_down[1][ibin-1])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin-1])    << " & " << Form("%.2f", tot_qcd_down[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_qcd_down[0][ibin])      << " & " << Form("%.2f", kap_qcd_down[1][ibin])      << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin])      << " & " << Form("%.2f", tot_qcd_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_down[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_down[1][ibin+1])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else if(ibin==35) {
      	  cout << Form("\\multirow{2}{*}{$\\Nb\\ge%d$} & $+1\\sigma$ &", inb)
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_qcd_up[0][ibin])      << " & " << Form("%.2f", kap_qcd_up[1][ibin])      << " & "
               << Form("%.2f", mckap_qcd_up[0][ibin])    << " & " << Form("%.2f", mckap_qcd_up[1][ibin])    << " & "
               << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin])      << " & " << Form("%.2f", tot_qcd_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_up[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_up[1][ibin+1])    << " & "
     	       << Form("%.2f", mckap_qcd_up[0][ibin+1])  << " & " << Form("%.2f", mckap_qcd_up[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_qcd_down[0][ibin])      << " & " << Form("%.2f", kap_qcd_down[1][ibin])      << " & "
      	       << Form("%.2f", mckap_qcd_down[0][ibin])    << " & " << Form("%.2f", mckap_qcd_down[1][ibin])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin])      << " & " << Form("%.2f", tot_qcd_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_down[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_down[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_qcd_down[0][ibin+1])  << " & " << Form("%.2f", mckap_qcd_down[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else {
      	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_qcd_up[0][ibin-1])    << " & " << Form("%.2f", kap_qcd_up[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_qcd_up[0][ibin-1])  << " & " << Form("%.2f", mckap_qcd_up[1][ibin-1])  << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin-1])    << " & " << Form("%.2f", tot_qcd_up[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_qcd_up[0][ibin])      << " & " << Form("%.2f", kap_qcd_up[1][ibin])      << " & "
               << Form("%.2f", mckap_qcd_up[0][ibin])    << " & " << Form("%.2f", mckap_qcd_up[1][ibin])    << " & "
               << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin])      << " & " << Form("%.2f", tot_qcd_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_up[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_up[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_qcd_up[0][ibin+1])  << " & " << Form("%.2f", mckap_qcd_up[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())          << " & " << Form("%s",   notapply.Data())          << " & "
      	       << Form("%.2f", tot_qcd_up[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_qcd_down[0][ibin-1])    << " & " << Form("%.2f", kap_qcd_down[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_qcd_down[0][ibin-1])  << " & " << Form("%.2f", mckap_qcd_down[1][ibin-1])  << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin-1])    << " & " << Form("%.2f", tot_qcd_down[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_qcd_down[0][ibin])      << " & " << Form("%.2f", kap_qcd_down[1][ibin])      << " & "
      	       << Form("%.2f", mckap_qcd_down[0][ibin])    << " & " << Form("%.2f", mckap_qcd_down[1][ibin])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin])      << " & " << Form("%.2f", tot_qcd_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_qcd_down[0][ibin+1])    << " & " << Form("%.2f", kap_qcd_down[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_qcd_down[0][ibin+1])  << " & " << Form("%.2f", mckap_qcd_down[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_qcd_down[0][ibin+1])    << " & " << Form("%.2f", tot_qcd_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
      }
      cout << "\\end{tabular}"<<endl;
      cout << "}" << endl;
      cout << Form("\\label{tab:kap_unc_table_qcd_%s}", year.Data()) << endl;
      cout << "\\end{table}\n"; 
      cout << endl;
    }
    else {
    }

    ////////////////////////////////////
    ////////////// W+jets //////////////
    ////////////////////////////////////

    if(formatLatex) {
      cout << "\\begin{table}" << endl;
      cout << "\\centering" << endl;
      cout << Form("\\caption{The summary table of the uncertainties in the kappa factor for $\\wjets$ process using %s samples.}", latex_year.Data()) << endl;
      cout << "\\resizebox{\\textwidth}{!}{" << endl;
      cout << "\\begin{tabular}[tbp!]{|c|c|cccccccccc|cccccccccc|cccccccccc|}" << endl;
      cout << "\\hline" << endl;
      cout << "\\multicolumn{2}{|c|}{\\multirow{3}{*}{}} & \\multicolumn{10}{c|}{$4\\leq \\Njet \\leq5$} & \\multicolumn{10}{c|}{$6\\leq \\Njet \\leq7$} & \\multicolumn{10}{c|}{$8\\leq \\Njet$} \\\\" << endl;
      cout << "\\hline\\hline" << endl;
      
      cout << " \\multicolumn{2}{|c|}{} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c}{DY $\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c}{DY $\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c}{DY $\\MJ$ shape} & \\multicolumn{2}{c|}{total} \\\\" << endl;
      cout << "\\multicolumn{2}{|c|}{} & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ \\\\" << endl;
      cout<< "\\hline" << endl;
      for(int ibin=23; ibin<nbins; ibin+=3) {
        int inb = int(ibin-23)/3;
	if (inb==0) {
	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_wjets_up[0][ibin-1])           << " & " << Form("%.2f", kap_wjets_up[1][ibin-1])           << " & "
      	       << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
      	       << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin-1])    << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin-1])    << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin-1])           << " & " << Form("%.2f", tot_wjets_up[1][ibin-1])           << " & "
      	       << Form("%.2f", kap_wjets_up[0][ibin])             << " & " << Form("%.2f", kap_wjets_up[1][ibin])             << " & "
               << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
               << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin])             << " & " << Form("%.2f", tot_wjets_up[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_up[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_up[1][ibin+1])           << " & "
      	       << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
      	       << Form("%s",   notapply.Data())                   << " & " << Form("%s",   notapply.Data())                   << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_up[1][ibin+1])           << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_wjets_down[0][ibin-1])           << " & " << Form("%.2f", kap_wjets_down[1][ibin-1])           << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin-1])    << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin-1])    << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin-1])           << " & " << Form("%.2f", tot_wjets_down[1][ibin-1])           << " & "
      	       << Form("%.2f", kap_wjets_down[0][ibin])             << " & " << Form("%.2f", kap_wjets_down[1][ibin])             << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin])             << " & " << Form("%.2f", tot_wjets_down[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_down[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_down[1][ibin+1])           << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%s",   notapply.Data())                     << " & " << Form("%s",   notapply.Data())                     << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_down[1][ibin+1])           << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else if(ibin==35) {
      	  cout << Form("\\multirow{2}{*}{$\\Nb\\ge%d$} & $+1\\sigma$ &", inb)
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_wjets_up[0][ibin])             << " & " << Form("%.2f", kap_wjets_up[1][ibin])             << " & "
               << Form("%.2f", mckap_wjets_up[0][ibin])           << " & " << Form("%.2f", mckap_wjets_up[1][ibin])           << " & "
               << Form("%.2f", mjsyst_wjets_up[0][ibin])          << " & " << Form("%.2f", mjsyst_wjets_up[1][ibin])          << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin])             << " & " << Form("%.2f", tot_wjets_up[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_up[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_up[1][ibin+1])           << " & "
      	       << Form("%.2f", mckap_wjets_up[0][ibin+1])         << " & " << Form("%.2f", mckap_wjets_up[1][ibin+1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_up[0][ibin+1])        << " & " << Form("%.2f", mjsyst_wjets_up[1][ibin+1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_up[1][ibin+1])           << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_wjets_down[0][ibin])             << " & " << Form("%.2f", kap_wjets_down[1][ibin])             << " & "
      	       << Form("%.2f", mckap_wjets_down[0][ibin])           << " & " << Form("%.2f", mckap_wjets_down[1][ibin])           << " & "
      	       << Form("%.2f", mjsyst_wjets_down[0][ibin])          << " & " << Form("%.2f", mjsyst_wjets_down[1][ibin])          << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin])             << " & " << Form("%.2f", tot_wjets_down[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_down[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_down[1][ibin+1])           << " & "
      	       << Form("%.2f", mckap_wjets_down[0][ibin+1])         << " & " << Form("%.2f", mckap_wjets_down[1][ibin+1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_down[0][ibin+1])        << " & " << Form("%.2f", mjsyst_wjets_down[1][ibin+1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_down[1][ibin+1])           << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else {
      	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_wjets_up[0][ibin-1])           << " & " << Form("%.2f", kap_wjets_up[1][ibin-1])           << " & "
      	       << Form("%.2f", mckap_wjets_up[0][ibin-1])         << " & " << Form("%.2f", mckap_wjets_up[1][ibin-1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_up[0][ibin-1])        << " & " << Form("%.2f", mjsyst_wjets_up[1][ibin-1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin-1])    << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin-1])    << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin-1])           << " & " << Form("%.2f", tot_wjets_up[1][ibin-1])           << " & "
      	       << Form("%.2f", kap_wjets_up[0][ibin])             << " & " << Form("%.2f", kap_wjets_up[1][ibin])             << " & "
               << Form("%.2f", mckap_wjets_up[0][ibin])           << " & " << Form("%.2f", mckap_wjets_up[1][ibin])           << " & "
               << Form("%.2f", mjsyst_wjets_up[0][ibin])          << " & " << Form("%.2f", mjsyst_wjets_up[1][ibin])          << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin])             << " & " << Form("%.2f", tot_wjets_up[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_up[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_up[1][ibin+1])           << " & "
      	       << Form("%.2f", mckap_wjets_up[0][ibin+1])         << " & " << Form("%.2f", mckap_wjets_up[1][ibin+1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_up[0][ibin+1])        << " & " << Form("%.2f", mjsyst_wjets_up[1][ibin+1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_up[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_up[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_up[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_up[1][ibin+1])           << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_wjets_down[0][ibin-1])           << " & " << Form("%.2f", kap_wjets_down[1][ibin-1])           << " & "
      	       << Form("%.2f", mckap_wjets_down[0][ibin-1])         << " & " << Form("%.2f", mckap_wjets_down[1][ibin-1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_down[0][ibin-1])        << " & " << Form("%.2f", mjsyst_wjets_down[1][ibin-1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin-1])    << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin-1])    << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin-1])           << " & " << Form("%.2f", tot_wjets_down[1][ibin-1])           << " & "
      	       << Form("%.2f", kap_wjets_down[0][ibin])             << " & " << Form("%.2f", kap_wjets_down[1][ibin])             << " & "
      	       << Form("%.2f", mckap_wjets_down[0][ibin])           << " & " << Form("%.2f", mckap_wjets_down[1][ibin])           << " & "
      	       << Form("%.2f", mjsyst_wjets_down[0][ibin])          << " & " << Form("%.2f", mjsyst_wjets_down[1][ibin])          << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin])      << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin])      << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin])             << " & " << Form("%.2f", tot_wjets_down[1][ibin])             << " & "
      	       << Form("%.2f", kap_wjets_down[0][ibin+1])           << " & " << Form("%.2f", kap_wjets_down[1][ibin+1])           << " & "
      	       << Form("%.2f", mckap_wjets_down[0][ibin+1])         << " & " << Form("%.2f", mckap_wjets_down[1][ibin+1])         << " & "
      	       << Form("%.2f", mjsyst_wjets_down[0][ibin+1])        << " & " << Form("%.2f", mjsyst_wjets_down[1][ibin+1])        << " & "
      	       << Form("%.2f", mjshape_dy_wjets_down[0][ibin+1])    << " & " << Form("%.2f", mjshape_dy_wjets_down[1][ibin+1])    << " & "
      	       << Form("%.2f", tot_wjets_down[0][ibin+1])           << " & " << Form("%.2f", tot_wjets_down[1][ibin+1])           << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
      }
      cout << "\\end{tabular}"<<endl;
      cout << "}" << endl;
      cout << Form("\\label{tab:kap_unc_table_wjets_%s}", year.Data()) << endl;
      cout << "\\end{table}\n"; 
      cout << endl;
    }
    else {
    }

    ///////////////////////////////////
    ////////////// TTbar //////////////
    ///////////////////////////////////

    if(formatLatex) {
      cout << "\\begin{table}" << endl;
      cout << "\\centering" << endl;
      cout << Form("\\caption{The summary table of the uncertainties in the kappa factor for $\\ttbar$ process using %s samples.}", latex_year.Data()) << endl;
      cout << "\\resizebox{\\textwidth}{!}{" << endl;
      cout << "\\begin{tabular}[tbp!]{|c|c|cccccccc|cccccccc|cccccccc|}" << endl;
      cout << "\\hline" << endl;
      cout << "\\multicolumn{2}{|c|}{\\multirow{3}{*}{}} & \\multicolumn{8}{c|}{$4\\leq \\Njet \\leq5$} & \\multicolumn{8}{c|}{$6\\leq \\Njet \\leq7$} & \\multicolumn{8}{c|}{$8\\leq \\Njet$} \\\\" << endl;
      cout << "\\hline\\hline" << endl;
      
      cout << " \\multicolumn{2}{|c|}{} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} & \\multicolumn{2}{c}{data kappa} & \\multicolumn{2}{c}{MC kappa} & \\multicolumn{2}{c}{$\\MJ$ shape} & \\multicolumn{2}{c|}{total} \\\\" << endl;
      cout << "\\multicolumn{2}{|c|}{} & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ & $\\kappa_{1}$ & $\\kappa_{2}$ \\\\" << endl;
      cout << "\\hline" << endl;
      for(int ibin=23; ibin<nbins; ibin+=3) {
        int inb = int(ibin-23)/3;
	if (inb==0) {
	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", mjsyst_ttbar_up[0][ibin-1]) << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin-1]) << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin])      << " & " << Form("%.2f", kap_ttbar_up[1][ibin])      << " & "
               << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())    << " & "
               << Form("%.2f", mjsyst_ttbar_up[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin])      << " & " << Form("%.2f", tot_ttbar_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin+1])    << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", mjsyst_ttbar_up[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin-1]) << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin-1]) << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin])      << " & " << Form("%.2f", kap_ttbar_down[1][ibin])      << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin])      << " & " << Form("%.2f", tot_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin+1])    << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else if (inb==1) {
      	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_ttbar_up[0][ibin-1])  << " & " << Form("%.2f", mckap_ttbar_up[1][ibin-1])  << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin])      << " & " << Form("%.2f", kap_ttbar_up[1][ibin])      << " & "
               << Form("%.2f", mckap_ttbar_up[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_up[1][ibin])    << " & "
               << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin])      << " & " << Form("%.2f", tot_ttbar_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_up[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_up[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())            << " & " << Form("%s",   notapply.Data())            << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin-1])  << " & " << Form("%.2f", mckap_ttbar_down[1][ibin-1])  << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin])      << " & " << Form("%.2f", kap_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_down[1][ibin])    << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin])      << " & " << Form("%.2f", tot_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_down[1][ibin+1])  << " & "
      	       << Form("%s",   notapply.Data())              << " & " << Form("%s",   notapply.Data())              << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else if(ibin==35) {
      	  cout << Form("\\multirow{2}{*}{$\\Nb\\ge%d$} & $+1\\sigma$ &", inb)
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin])      << " & " << Form("%.2f", kap_ttbar_up[1][ibin])      << " & "
               << Form("%.2f", mckap_ttbar_up[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_up[1][ibin])    << " & "
               << Form("%.2f", mjsyst_ttbar_up[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin])      << " & " << Form("%.2f", tot_ttbar_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_up[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_up[1][ibin+1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_up[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << " & & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin])      << " & " << Form("%.2f", kap_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_down[1][ibin])    << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin])      << " & " << Form("%.2f", tot_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_down[1][ibin+1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
	else {
      	  cout << Form("\\multirow{2}{*}{$\\Nb=%d$} & $+1\\sigma$ &", inb)
      	       << Form("%.2f", kap_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_ttbar_up[0][ibin-1])  << " & " << Form("%.2f", mckap_ttbar_up[1][ibin-1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_up[0][ibin-1]) << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin-1]) << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin])      << " & " << Form("%.2f", kap_ttbar_up[1][ibin])      << " & "
               << Form("%.2f", mckap_ttbar_up[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_up[1][ibin])    << " & "
               << Form("%.2f", mjsyst_ttbar_up[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin])      << " & " << Form("%.2f", tot_ttbar_up[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_up[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_up[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_up[1][ibin+1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_up[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_up[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_up[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_up[1][ibin+1])    << " \\\\"
      	       << endl;
      	  cout << " & $-1\\sigma$ &"
      	       << Form("%.2f", kap_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin-1])  << " & " << Form("%.2f", mckap_ttbar_down[1][ibin-1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin-1]) << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin-1]) << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin-1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin-1])    << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin])      << " & " << Form("%.2f", kap_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin])    << " & " << Form("%.2f", mckap_ttbar_down[1][ibin])    << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin])   << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin])   << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin])      << " & " << Form("%.2f", tot_ttbar_down[1][ibin])      << " & "
      	       << Form("%.2f", kap_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", kap_ttbar_down[1][ibin+1])    << " & "
      	       << Form("%.2f", mckap_ttbar_down[0][ibin+1])  << " & " << Form("%.2f", mckap_ttbar_down[1][ibin+1])  << " & "
      	       << Form("%.2f", mjsyst_ttbar_down[0][ibin+1]) << " & " << Form("%.2f", mjsyst_ttbar_down[1][ibin+1]) << " & "
      	       << Form("%.2f", tot_ttbar_down[0][ibin+1])    << " & " << Form("%.2f", tot_ttbar_down[1][ibin+1])    << " \\\\"
      	       << endl;
	  cout << "\\hline" << endl;
	}
      }
      cout << "\\end{tabular}"<<endl;
      cout << "}" << endl;
      cout << Form("\\label{tab:kap_unc_table_ttbar_%s}", year.Data()) << endl;
      cout << "\\end{table}\n"; 
      cout << endl;
    }
    else {
    }

    


    infile->Close();

    return 0;
}

float getKappaUnc(TString filename, TString procname, int ikap, int ibin, TString syst, TString updown) {

  TFile* infile = TFile::Open(filename, "READ");
  TString year;
  if(filename.Contains("2016")) year = "UL2016";
  else if(filename.Contains("2017")||filename.Contains("2018")||filename.Contains("20178")) year = "UL20178";
  else {
    cout << "ERROR: The inputfile name should include the year" << endl;
    return 0;
  }
  int ijet = (ibin-1)%3;
  int ind_ijet = 10*(2*ijet+4) + 2*ijet + 5;
  if (ind_ijet==89) ind_ijet=8;

  TH1F *h_nominal, *h_up, *h_down;
  TH1F *h_mckappa_jer_up, *h_mckappa_jer_down, *h_mckappa_jec_up, *h_mckappa_jec_down;
  float kap_nom=0, kap_up=0, kap_down=0;
  float kap_jec_up=0, kap_jec_down=0, kap_jer_up=0, kap_jer_down=0;

  if(syst=="kappa") {
    h_nominal = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", ibin, procname.Data())));
    h_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_kappa%d_njets%d_%s_%sUp", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
    h_down    = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_kappa%d_njets%d_%s_%sDown", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
  }
  else if(syst=="mjsyst") {
    h_nominal = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", ibin, procname.Data())));
    h_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_mjsyst_r%d_njets%d_%s_%sUp", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
    h_down    = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_mjsyst_r%d_njets%d_%s_%sDown", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
  }
  else if(syst=="mckappa") {
    // mckappa consists of jec, jer, and combined systs
    h_nominal = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", ibin, procname.Data())));
    h_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_njets%d_%sUp", ibin, procname.Data(), ikap, ind_ijet, year.Data())));
    h_down    = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_njets%d_%sDown", ibin, procname.Data(), ikap, ind_ijet, year.Data())));
    h_mckappa_jec_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_jec_njets%d_%sUp", ibin, procname.Data(), ikap, ind_ijet, year.Data())));
    h_mckappa_jec_down      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_jec_njets%d_%sDown", ibin, procname.Data(), ikap, ind_ijet, year.Data())));
    h_mckappa_jer_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_jer_njets%d_%sUp", ibin, procname.Data(), ikap, ind_ijet, year.Data())));
    h_mckappa_jer_down      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_MC_kappa%d_jer_njets%d_%sDown", ibin, procname.Data(), ikap, ind_ijet, year.Data())));

    kap_jec_up   = h_mckappa_jec_up->GetBinContent(ikap+1)/h_mckappa_jec_up->GetBinContent(1);
    kap_jec_down = h_mckappa_jec_down->GetBinContent(ikap+1)/h_mckappa_jec_down->GetBinContent(1);
    kap_jer_up   = h_mckappa_jer_up->GetBinContent(ikap+1)/h_mckappa_jer_up->GetBinContent(1);
    kap_jer_down = h_mckappa_jer_down->GetBinContent(ikap+1)/h_mckappa_jer_down->GetBinContent(1);
  }
  else if(syst=="mjshape_dy") {
    h_nominal = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", ibin, procname.Data())));
    h_up      = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_kappa%d_unc_dy_njets%d_%s_%sUp", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
    h_down    = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_kappa%d_unc_dy_njets%d_%s_%sDown", ibin, procname.Data(), ikap, ind_ijet, procname.Data(), year.Data())));
  }

  kap_nom  = h_nominal->GetBinContent(ikap+1)/h_nominal->GetBinContent(1);
  kap_up   = h_up->GetBinContent(ikap+1)/h_up->GetBinContent(1);
  kap_down = h_down->GetBinContent(ikap+1)/h_down->GetBinContent(1);

  float ratio_up=0, ratio_down=0;
  // mckappa consists of jec, jer, and combined systs
  if(syst=="mckappa") {
    ratio_up   = TMath::Sqrt(TMath::Power(((kap_up/kap_nom)-1),2)   + TMath::Power(((kap_jec_up/kap_nom)-1),2)   + TMath::Power(((kap_jer_up/kap_nom)-1),2));
    ratio_down = TMath::Sqrt(TMath::Power((1-(kap_down/kap_nom)),2) + TMath::Power((1-(kap_jec_down/kap_nom)),2) + TMath::Power((1-(kap_jer_down/kap_nom)),2));
  }
  else {
    ratio_up   = TMath::Abs((kap_up/kap_nom)-1);
    ratio_down = TMath::Abs(1-(kap_down/kap_nom));
  }

  if(h_nominal->GetBinContent(1)==0 || h_nominal->GetBinContent(1+ikap)==0) {
    ratio_up=0;
    ratio_down=0;
  }
  
  if(updown=="up") return ratio_up;
  else if(updown=="down") return ratio_down;
  else return 0;
}

