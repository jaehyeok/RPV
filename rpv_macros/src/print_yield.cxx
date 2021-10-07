#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TString.h"
#include "TLatex.h"
#include "TSystem.h"

using namespace std;

int main(int argc, char *argv[]){

	TString inputdir;
	inputdir = "variations/";

	TFile* infile1 = TFile::Open(inputdir+"output_2016.root");
	TFile* infile2 = TFile::Open(inputdir+"output_2016.root");

	const int nbins = 37;

        float qcd_1[nbins], ttbar_1[nbins], wjets_1[nbins], other_1[nbins], sig1800_1[nbins];
        for(int ibin=22; ibin<nbins; ibin++){
                        qcd_1[ibin] = 0;
                        ttbar_1[ibin] = 0;
                        wjets_1[ibin] = 0;
                        other_1[ibin] = 0;
                        sig1800_1[ibin] = 0;
        }

        for(int ibin=22; ibin<nbins; ibin++){
                        qcd_1[ibin] = static_cast<TH1F*>(infile1->Get(Form("bin%i/qcd", ibin)))->Integral();
                        ttbar_1[ibin] = static_cast<TH1F*>(infile1->Get(Form("bin%i/ttbar", ibin)))->Integral();
                        wjets_1[ibin] = static_cast<TH1F*>(infile1->Get(Form("bin%i/wjets", ibin)))->Integral();
                        other_1[ibin] = static_cast<TH1F*>(infile1->Get(Form("bin%i/other", ibin)))->Integral();
                        sig1800_1[ibin] = static_cast<TH1F*>(infile1->Get(Form("bin%i/signal_M1800", ibin)))->Integral();
        }

	float qcd_2[nbins], ttbar_2[nbins], wjets_2[nbins], other_2[nbins], sig1800_2[nbins];
        for(int ibin=22; ibin<nbins; ibin++){
                        qcd_2[ibin] = 0;
                        ttbar_2[ibin] = 0;
                        wjets_2[ibin] = 0;
                        other_2[ibin] = 0;
                        sig1800_2[ibin] = 0;
        }

	for(int ibin=22; ibin<nbins; ibin++){
                        qcd_2[ibin] = static_cast<TH1F*>(infile2->Get(Form("bin%i/qcd", ibin)))->Integral();
                        ttbar_2[ibin] = static_cast<TH1F*>(infile2->Get(Form("bin%i/ttbar", ibin)))->Integral();
                        wjets_2[ibin] = static_cast<TH1F*>(infile2->Get(Form("bin%i/wjets", ibin)))->Integral();
                        other_2[ibin] = static_cast<TH1F*>(infile2->Get(Form("bin%i/other", ibin)))->Integral();
                        sig1800_2[ibin] = static_cast<TH1F*>(infile2->Get(Form("bin%i/signal_M1800", ibin)))->Integral();
        }

	for(int ibin = 22; ibin<nbins; ibin++){
		cout<<"bin " << ibin << endl;
		cout<<"qcd_1	 : "<<qcd_1[ibin] << ", qcd_2 : "<<qcd_2[ibin]<<"-- 	ratio	: "<<qcd_1[ibin]/qcd_2[ibin]<<endl;
		cout<<"ttbar_1	 : "<<ttbar_1[ibin]<< ", ttbar_2 : "<<ttbar_2[ibin]<<"--	ratio	 	: "<<ttbar_1[ibin]/ttbar_2[ibin]<<endl;
		cout<<"wjets_1	 : "<<wjets_1[ibin]<< ", wjets_2 : "<<wjets_2[ibin]<<"--	ratio		: "<<wjets_1[ibin]/wjets_2[ibin]<<endl;
		cout<<"others_1  : "<<other_1[ibin]<< ", other_2 : "<<other_2[ibin]<<"--ratio		: "<<other_1[ibin]/other_2[ibin]<<endl;
		cout<<"sig1800_1 : "<<sig1800_1[ibin]<< ", sig1800_2 : "<<sig1800_2[ibin]<<"--	ratio	: "<<sig1800_1[ibin]/sig1800_2[ibin]<<endl;
		cout<<""<<endl;
	}

}
