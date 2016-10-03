// Changes the shape of data in shapes file to test fit
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){

  vector<string> binNames = { 
    "bin0", "bin1", "bin2",                     // bins for control region fit
    "bin3", "bin4", "bin5",                     // bins for control region fit
    //        "bin6", "bin7", "bin8", "bin9",             // lower mj bins
    "bin10", "bin11", "bin12",                  // signal bins
    "bin13", "bin14", "bin15","bin16","bin17"}; // signal bins

  if(argc<=1){
    cout<<"Please provide a sum_rescaled root file."<<endl;
    exit(1);
  }

  string rootfile(argv[1]);
  TFile *f = TFile::Open(rootfile.c_str(), "update");

  for(unsigned int ibin=0; ibin<binNames.size(); ibin++){ 
    
    TString binname(binNames.at(ibin).c_str());
    f->cd(binname);

    TH1F* h_data = static_cast<TH1F*>(f->Get(binname+"/data_obs"));
      
    double norm = h_data->Integral();

    h_data->SetBinContent(2, h_data->GetBinContent(2) * 0.95);
    h_data->SetBinContent(3, h_data->GetBinContent(3) * 1.00);
    h_data->SetBinContent(4, h_data->GetBinContent(4) * 1.30);
    h_data->SetBinContent(5, h_data->GetBinContent(5) * 1.50);

    h_data->Scale(norm/h_data->Integral()); 
     
    h_data->Write();
    // go back to the top left directory to start processing next bin
    f->cd("/");
  }
  f->Write();
  f->Close(); 
}
