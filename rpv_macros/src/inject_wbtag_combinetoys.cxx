// Changes the MC yield according to a x-sigma variation of the bc/udsg btag weight
// Useful for throwing toys with combine, since combine throws around the MC yield
// Note: When throwing toys make sure to freeze the nuisance that has been varied, since the up and down templates are not adjusted to match the variation
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){

  // Input arguments
  if(argc<=2){
    cout<<"Usage: ./run/inject_wbtag_combinetoys.exe <nominal file> <variation file>"<<endl;
    cout<<"\n<nominal file> is the file with the nominal MC central values and variations"<<endl;
    cout<<"<variation file> is the template file the variations will be appplied to. It can be the same as <nominal file>."<<endl;
    cout<<"\tThis is necessary when applying both the heavy- and light-flavor variations to a file in succession."<<endl;
    cout<<"\tExample: ./run/inject_wbtag_combinetoys.exe variations/sum_rescaled_mconly.root variations/sum_rescaled_mconly_bctag1.root"<<endl;
    exit(1);
  }

  // General variables
  TString btagType = "udsg"; // bc or udsg  
  vector<TString> btagStrength = {"0", "1", "3"};
  const int nsig = 11;
  TString mglu[nsig] = {"1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000"};

  const int nbins = 18;
  string binNames[nbins] = {
    "bin0", "bin1", "bin2",                     // bins for control region fit
    "bin3", "bin4", "bin5",                     // bins for control region fit
    "bin10", "bin11", "bin12",                  // signal bins
    "bin13", "bin14", "bin15","bin16","bin17",  // signal bins
    "bin18", "bin19", "bin20", "bin21"};        // signal bins

  //Get difference between nominal and 1sigma variation    
  TString rootfile(argv[1]);
  TFile *f = TFile::Open(rootfile);

  TH1F *qcdDiff[nbins], *ttbarDiff[nbins], *wjetsDiff[nbins], *otherDiff[nbins];
  TH1F* sigDiff[nbins][nsig];

  for(int ibin=0; ibin<nbins; ibin++){
    
    //Set binname
    TString binname(binNames[ibin].c_str());

    // Get up variations
    qcdDiff[ibin] = static_cast<TH1F*>(f->Get(binname+"/qcd_btag_"+btagType+"Up")->Clone());
    ttbarDiff[ibin] = static_cast<TH1F*>(f->Get(binname+"/ttbar_btag_"+btagType+"Up")->Clone());
    wjetsDiff[ibin] = static_cast<TH1F*>(f->Get(binname+"/wjets_btag_"+btagType+"Up")->Clone());
    otherDiff[ibin] = static_cast<TH1F*>(f->Get(binname+"/other_btag_"+btagType+"Up")->Clone());
    for(int isig=0; isig<nsig; isig++) 
      sigDiff[ibin][isig] = static_cast<TH1F*>(f->Get(binname+"/signal_M"+mglu[isig]+"_btag_"+btagType+"Up")->Clone());     

    // Subtract nominal variation to get difference
    qcdDiff[ibin]->Add(static_cast<TH1F*>(f->Get(binname+"/qcd")),-1);
    ttbarDiff[ibin]->Add(static_cast<TH1F*>(f->Get(binname+"/ttbar")),-1);
    wjetsDiff[ibin]->Add(static_cast<TH1F*>(f->Get(binname+"/wjets")),-1);
    otherDiff[ibin]->Add(static_cast<TH1F*>(f->Get(binname+"/other")),-1);
    for(int isig=0; isig<nsig; isig++)
      sigDiff[ibin][isig]->Add(static_cast<TH1F*>(f->Get(binname+"/signal_M"+mglu[isig])),-1);
  }  

  // Do the btag variations
  for(unsigned int istr=0; istr<btagStrength.size(); istr++){
    TString newfile = argv[2];
    TString tmpstr = btagStrength[istr];
    newfile.ReplaceAll(".root","_"+btagType+"tag"+tmpstr.ReplaceAll(".","p")+".root");
    TFile::Cp(argv[2], newfile);
    
    cout<<"Opening "<<newfile<<"\n"<<endl;
    TFile *f1 = TFile::Open(newfile,"update");

    for(int ibin=0; ibin<nbins; ibin++){
      
      TString binname(binNames[ibin].c_str());
      cout<<"\n--------"<<binname<<"--------"<<endl;
      
    
      // Get histograms to vary
    
      TH1F* qcdVar = static_cast<TH1F*>(f1->Get(binname+"/qcd"));    
      TH1F* ttbarVar = static_cast<TH1F*>(f1->Get(binname+"/ttbar"));
      TH1F* wjetsVar = static_cast<TH1F*>(f1->Get(binname+"/wjets"));
      TH1F* otherVar = static_cast<TH1F*>(f1->Get(binname+"/other"));
      TH1F* sigVar[nsig];
      for(int isig=0; isig<nsig; isig++)
	sigVar[isig] = static_cast<TH1F*>(f1->Get(binname+"/signal_M"+mglu[isig]));
      
      //Store Pre-varied yields
      double qcdOldYields[5], ttbarOldYields[5], wjetsOldYields[5], otherOldYields[5];
      double sigOldYields[5]; //Only doing one signal point (m=1800)
      for(int i=0; i<4; i++){
        //Bin 2 is Nb=1
	qcdOldYields[i] = qcdVar->GetBinContent(i+2);
	ttbarOldYields[i] = ttbarVar->GetBinContent(i+2);
	wjetsOldYields[i] = wjetsVar->GetBinContent(i+2);
	otherOldYields[i] = otherVar->GetBinContent(i+2);
	sigOldYields[i] = sigVar[8]->GetBinContent(i+2);
      }
      
      qcdOldYields[4] = qcdVar->Integral();
      ttbarOldYields[4] = ttbarVar->Integral();
      wjetsOldYields[4] = wjetsVar->Integral();
      otherOldYields[4] = otherVar->Integral();
      sigOldYields[4] = sigVar[8]->Integral();

      // Add difference multiplied by btag strength to get final yield
      qcdVar->Add(qcdDiff[ibin], btagStrength[istr].Atof());
      ttbarVar->Add(ttbarDiff[ibin], btagStrength[istr].Atof());
      wjetsVar->Add(wjetsDiff[ibin], btagStrength[istr].Atof());
      otherVar->Add(otherDiff[ibin], btagStrength[istr].Atof());
      for(int isig=0; isig<nsig; isig++)
	sigVar[isig]->Add(sigDiff[ibin][isig], btagStrength[istr].Atof());

      //Print values
      cout<<"--------QCD-------"<<endl;
      cout<<"Old total="<<qcdOldYields[4]<<", New total="<<qcdVar->Integral()<<endl;;
      for(int i=0; i<4; i++) cout<<"Nb="<<i+1<<", Old yields="<<qcdOldYields[i]<<", Variation="<<btagStrength[istr].Atof()<<"*"<<qcdDiff[ibin]->GetBinContent(i+2)<<", New Yield="<<qcdVar->GetBinContent(i+2)<<endl;
      cout<<"\n--------ttbar-------"<<endl;
      cout<<"Old total="<<ttbarOldYields[4]<<", New total="<<ttbarVar->Integral()<<endl;;
      for(int i=0; i<4; i++) cout<<"Nb="<<i+1<<", Old yields="<<ttbarOldYields[i]<<", Variation="<<btagStrength[istr].Atof()<<"*"<<ttbarDiff[ibin]->GetBinContent(i+2)<<", New Yield="<<ttbarVar->GetBinContent(i+2)<<endl;
      cout<<"\n--------Wjets-------"<<endl;
      cout<<"Old total="<<wjetsOldYields[4]<<", New total="<<wjetsVar->Integral()<<endl;;
      for(int i=0; i<4; i++) cout<<"Nb="<<i+1<<", Old yields="<<wjetsOldYields[i]<<", Variation="<<btagStrength[istr].Atof()<<"*"<<wjetsDiff[ibin]->GetBinContent(i+2)<<", New Yield="<<wjetsVar->GetBinContent(i+2)<<endl;
      cout<<"\n--------other-------"<<endl;
      cout<<"Old total="<<otherOldYields[4]<<", New total="<<otherVar->Integral()<<endl;;
      for(int i=0; i<4; i++) cout<<"Nb="<<i+1<<", Old yields="<<otherOldYields[i]<<", Variation="<<btagStrength[istr].Atof()<<"*"<<otherDiff[ibin]->GetBinContent(i+2)<<", New Yield="<<otherVar->GetBinContent(i+2)<<endl;
      cout<<"\n--------Signal m="<<mglu[8]<<"-------"<<endl;
      cout<<"Old total="<<sigOldYields[4]<<", New total="<<sigVar[8]->Integral()<<endl;;
      for(int i=0; i<4; i++) cout<<"Nb="<<i+1<<", Old yields="<<sigOldYields[i]<<", Variation="<<btagStrength[istr].Atof()<<"*"<<sigDiff[ibin][8]->GetBinContent(i+2)<<", New Yield="<<sigVar[8]->GetBinContent(i+2)<<endl;
      
      //Write histograms
      qcdVar->Write();
      ttbarVar->Write();
      wjetsVar->Write();
      otherVar->Write();
      for(int isig=0; isig<nsig; isig++)
	sigVar[isig]->Write();
    }
    f1->Write();
    f1->Close();
  }
  f->Close();
}
