// Changes the shape of data in shapes file to test fit
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){

  TString btagType = "bc"; // bc or udsg  
  bool doSigInject = true;

  vector<double> strength = {0.5, 1, 2, 3, 4, 5};
  vector<double> sigStrength = {0.5, 1, 2};


  vector<string> binNames = { 
    "bin0", "bin1", "bin2",                     // bins for control region fit
    "bin3", "bin4", "bin5",                     // bins for control region fit
    "bin10", "bin11", "bin12",                  // signal bins
    "bin13", "bin14", "bin15","bin16","bin17"}; // signal bins

  if(argc<=1){
    cout<<"Please provide a sum_rescaled root file."<<endl;
    exit(1);
  }

  //Get difference between nominal and 1sigma variation
  TString rootfile(argv[1]);
  TFile *f = TFile::Open(rootfile);
  
  double diff[14][4];
  for(unsigned int ibin=0; ibin<binNames.size(); ibin++){ 
    
    TString binname(binNames.at(ibin).c_str());
    f->cd(binname);
    
    TH1F* h_bkg = static_cast<TH1F*>(f->Get(binname+"/qcd"));
    h_bkg->Add(static_cast<TH1F*>(f->Get(binname+"/ttbar")));
    h_bkg->Add(static_cast<TH1F*>(f->Get(binname+"/wjets")));
    h_bkg->Add(static_cast<TH1F*>(f->Get(binname+"/other")));

    TH1F* h_bkg_up = static_cast<TH1F*>(f->Get(binname+"/qcd_btag_"+btagType+"Up"));
    h_bkg_up->Add(static_cast<TH1F*>(f->Get(binname+"/ttbar_btag_"+btagType+"Up")));
    h_bkg_up->Add(static_cast<TH1F*>(f->Get(binname+"/wjets_btag_"+btagType+"Up")));
    h_bkg_up->Add(static_cast<TH1F*>(f->Get(binname+"/other_btag_"+btagType+"Up")));
    
    cout<<"-----"<<binname<<"-----Nominal-----"<<endl;
    for(int i=0; i<4; i++){
      //Bin 2 is Nb=1
      diff[ibin][i] = h_bkg_up->GetBinContent(i+2)/h_bkg->GetBinContent(i+2);
      cout<<"Nb = "<<(i+1)<<": Nominal bkg = "<<h_bkg->GetBinContent(i+2)<<", Up bkg = "<<h_bkg_up->GetBinContent(i+2)<<", Diff = "<<diff[ibin][i]<<endl;
    }
    cout<<endl;
    
    // go back to the top directory to start processing next bin
    f->cd("/");
  }
  f->Close();
  
  // Do the btag variations
  for(unsigned int istr=0; istr<strength.size(); istr++){
    TString newfile = rootfile;
    newfile.ReplaceAll(".root","_"+btagType+"tag"+to_string(static_cast<int>(strength[istr]))+".root");
    TFile::Cp(rootfile, newfile);

    cout<<"Opening "<<newfile<<"\n"<<endl;
    
    TFile *f1 = TFile::Open(newfile,"update");
    
    for(unsigned int ibin=0; ibin<binNames.size(); ibin++){
      
      TString binname(binNames.at(ibin).c_str());
      f1->cd(binname);
      
      TH1F* h_data = static_cast<TH1F*>(f1->Get(binname+"/data_obs"));
      
      double norm = h_data->Integral();
      
      cout<<"-----"<<binname<<"-----Strength="<<strength[istr]<<"-----"<<endl;
      for(int i=0; i<4; i++){
	//Bin 2 is Nb=1
	double yield = h_data->GetBinContent(i+2);
	h_data->SetBinContent(i+2, yield*(1+(strength[istr]*(diff[ibin][i]-1))));
	cout<<"Nb = "<<(i+1)<<": Nominal yield = "<<yield<<", Up yield = "<<h_data->GetBinContent(i+2)<<endl;
      }
      cout<<endl;
      
      h_data->Scale(norm/h_data->Integral());

      h_data->Write();
      // go back to the top directory to start processing next bin
      f1->cd("/");
    }
    f1->Write();
    f1->Close();
    
    // Inject signal per btag variation
    if(doSigInject){
      for(unsigned int isig=0; isig<sigStrength.size(); isig++){
	TString newsigfile = newfile;
	newsigfile.ReplaceAll(".root","_sig"+to_string(static_cast<int>(sigStrength[isig]))+".root");
	TFile::Cp(newfile, newsigfile);

	cout<<"Opening "<<newsigfile<<"\n"<<endl;

	TFile *f2 = TFile::Open(newsigfile,"update");

	for(unsigned int ibin=0; ibin<binNames.size(); ibin++){
	  
	  TString binname(binNames.at(ibin).c_str());
	  f2->cd(binname);

	  TH1F* h_data = static_cast<TH1F*>(f2->Get(binname+"/data_obs"));
	  TH1F* h_sig = static_cast<TH1F*>(f2->Get(binname+"/signal_M1500"));

	  double ndata = h_data->Integral();

	  h_data->Add(h_sig, sigStrength[isig]);

	  cout<<"-----"<<binname<<"-----Strength="<<strength[istr]<<"-----"<<"-----Sig Strength="<<sigStrength[isig]<<"-----"<<endl;
	  cout<<"Data = "<<ndata<<", Signal = "<<h_sig->Integral()<<", Variation = "<<h_data->Integral()<<endl;
	  cout<<endl;

	  h_data->Write();
	  f2->cd("/");
	}
	f2->Write();
	f2->Close();
      }
    }
  }
}
