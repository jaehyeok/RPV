#include <iostream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

void getSyst(small_tree_rpv &trees, TString variations, TFile *f, TString procname);
double addError(double error, double added_error);
double divideErrors(double x, double y, double dx, double dy);

float lumi = 2.69; // fb-1

int main(){
/*  
  // Define samples
  TString folder_bkg = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/mc/skim_rpv_st1200/";
  TString folder_sig = "/net/cms9/cms9r0/rohan/babies/2016_07_13/T1tbs/split/renorm/";
  TString folder_dat = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/data/skim_rpv_st1200/";

  vector<TString> s_jetht = getRPVProcess(folder_dat,"data");

  //vector<TString> s_rpv_m1500 = getRPVProcess(folder_sig,"rpv_m1500");

  vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
  vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
  vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
  vector<TString> s_other = getRPVProcess(folder_bkg,"other_public");
  string folder = "/net/cms29/cms29r0/cawest/skims/ht1200/";
*/
  
  string folder = "/net/cms29/cms29r0/cawest/skims/ht1200/";

  // qcd ttbar wjets other 750 1000 1100 1200 1300 1400 1500
  small_tree_rpv qcd(folder+"*QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  qcd.Add(folder+"*QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");
  qcd.Add(folder+"*QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  qcd.Add(folder+"*QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");
  qcd.Add(folder+"*QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  qcd.Add(folder+"*QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");

  small_tree_rpv ttbar("/net/cms2/cms2r0/jaehyeokyoo/babies/skim_ht1200/*TTJets_TuneCUETP8M1_13TeV-madgraphMLM*"); //ntruleps==0&&ht>1200
  ttbar.Add(folder+"*TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  ttbar.Add(folder+"*TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");
  ttbar.Add(folder+"*TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  ttbar.Add(folder+"*TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");
  ttbar.Add(folder+"*TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  ttbar.Add(folder+"*TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1*");
  
  small_tree_rpv wjets(folder+"*WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  wjets.Add(folder+"*WJetsToQQ_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  
  small_tree_rpv other(folder+"*ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1*");
  other.Add(folder+"*ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1*");
  other.Add(folder+"*ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1*");
  other.Add(folder+"*ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1*");
  other.Add(folder+"*ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1*");
  other.Add(folder+"*DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*");
  other.Add(folder+"*ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8*");
  other.Add(folder+"*TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8*");
  other.Add(folder+"*TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*");
  other.Add(folder+"*TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8*");
  other.Add(folder+"*TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8*");
  other.Add(folder+"*TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8*");
  other.Add(folder+"*ZJetsToQQ_HT600toInf_13TeV-madgraph*");


  // signal...

  // open output root file
  TString variations = "nominal";
  TFile *f = new TFile(Form("variations/output_%s.root", variations.Data()), "recreate");

  // Depending on the process, turn on/off variation

  // loop over a tree and get up/dawn shapes for all bins at once 
  getSyst(qcd,   variations, f, "qcd");
  getSyst(ttbar, variations, f, "ttbar");
  getSyst(wjets, variations, f, "wjets");
  getSyst(other, variations, f, "other");

  // close output root file
  f->Close();
} 

void getSyst(small_tree_rpv &tree, TString variations, TFile *f, TString procname){

    cout << "Running syst: " << variations << endl;  
    //TString procname = "qcd";
    TString nominalname = procname+"_"+variations;
    TString upname      = nominalname+"Up";
    TString downname    = nominalname+"Down";
        
    // Get QCD flavor weights 
    TFile *csv_weight_file = TFile::Open("data/low_njet.root");
    TH1F *csv_weight = static_cast<TH1F*>(csv_weight_file->Get("csv_weight"));
    float bflavorValCentral = csv_weight->GetBinContent(1);
    float bflavorValError = csv_weight->GetBinError(1);
    float cflavorValCentral = csv_weight->GetBinContent(2);
    // negative sign implements anticorrelation between b and c reweightings
    float cflavorValError = -csv_weight->GetBinError(2);
    float lflavorValCentral = csv_weight->GetBinContent(3);
    float lflavorValError = csv_weight->GetBinError(3);
    csv_weight_file->Close();
    f->cd(); 
  
    bflavorValCentral = 1.0; 
    cflavorValCentral = 1.0; 
    lflavorValCentral = 1.0; 

    if(procname.Contains("qcd")) 
    { 
        std::cout << "Reweight b jets by " << bflavorValCentral << " +/ " << bflavorValError << std::endl;
        std::cout << "Reweight c jets by " << cflavorValCentral << " +/ " << cflavorValError << std::endl;
        std::cout << "Reweight l jets by " << lflavorValCentral << " +/ " << lflavorValError << std::endl;
    }

    // Get GS weights 
    std::vector<double> gs_dmc={1,1,1,1};
    std::vector<double> gs_dmc_err={0,0,0,0};
    std::vector<double> gs_dmc_syst={0,0,0,0};
    if(std::string::npos != variations.Contains("gs")){

        TFile *gs_file = TFile::Open("data/syst_gs.root");
        TGraphErrors* h_gs_dmc = static_cast<TGraphErrors*>(gs_file->Get("dmc_ldrbb_allmj"));

        double temp_val;
        for(unsigned int ibin=0; ibin<4; ibin++)
        {
            h_gs_dmc->GetPoint(ibin,temp_val,gs_dmc[ibin]);   
            gs_dmc_err[ibin] = h_gs_dmc->GetErrorY(ibin);  
            gs_dmc_syst[ibin] = TMath::Sqrt((1-gs_dmc[ibin])*(1-gs_dmc[ibin])+gs_dmc_err[ibin]*gs_dmc_err[ibin]); 
        }
    } 

    // nominal, up and down histrograms  
    int nBBins=4;
    TH1F * h1nominal = new TH1F(nominalname.Data(), nominalname.Data(), nBBins+1, 0, nBBins+1);
    TH1F * h1up     = new TH1F(upname.Data(), upname.Data(), nBBins+1, 0, nBBins+1);
    TH1F * h1down   = new TH1F(downname.Data(), downname.Data(), nBBins+1, 0, nBBins+1);

    // loop over tree 
    for(unsigned int ientry=0; ientry<tree.GetEntries(); ientry++){

        tree.GetEntry(ientry); 

        // 
        // Weights
        // 
        float nominalweight = lumi*tree.weight()*tree.w_pu_rpv()/tree.eff_trig();   
        float upweight      = nominalweight;
        float downweight    = nominalweight;
       
        
        // jet flavor 
        if(procname.Contains("qcd")) 
        { 
            // To provide QCD flavor reweighting
            //double bflavorValUp, bflavorValDown;
            //bflavorValUp=bflavorValCentral+bflavorValError;
            //bflavorValDown=bflavorValCentral-bflavorValError;
            //double cflavorValUp, cflavorValDown;
            //cflavorValUp=cflavorValCentral+cflavorValError;
            //cflavorValDown=cflavorValCentral-cflavorValError;
            //double lflavorValUp, lflavorValDown;
            //lflavorValUp=lflavorValCentral=lflavorValDown=1.0;

            int n_bflavor=0;
            int n_cflavor=0;
            for(unsigned int j=0; j<tree.jets_hflavor().size(); j++)
            { 
                if(tree.jets_islep().at(j)) continue;
                if(tree.jets_pt().at(j)<30) continue;
                if(abs(tree.jets_eta().at(j))>2.4) continue; 
            
                if(tree.jets_hflavor().at(j)==5) n_bflavor++;
                if(tree.jets_hflavor().at(j)==4) n_cflavor++;
            }

            if(n_bflavor>0)  
            { 
                nominalweight = nominalweight * bflavorValCentral;
            }
            else if(n_cflavor>0)
            { 
                nominalweight = nominalweight * cflavorValCentral;
            }
            else 
            { 
                nominalweight = nominalweight * lflavorValCentral;
            }

            //nominalweight = nominalweight * ((n_bflavor>0)*bflavorValCentral + (n_bflavor==0&&n_cflavor>0)*cflavorValCentral + (n_bflavor==0&&n_cflavor==0)*lflavorValCentral);
        }

        // assigne up and down weights
        
        //
        // loop over bins   
        //
        if(tree.ht()>1500 && tree.nleps()==0 && tree.nbm()>0 && tree.njets()>=4 && tree.njets()<=5 && tree.mj()>500 && tree.mj()<800) { 
            // nominal  
            h1nominal->Fill(tree.nbm(), nominalweight);
            // up  
            h1up->Fill(tree.nbm(), upweight);
            // down 
            h1down->Fill(tree.nbm(), downweight);
        }

    } //for(unsigned int ientry=0; ientry<tree.GetEntries(); ientry++){ 
    f->cd();
    h1up->Write();
    h1down->Write();

    f->Print();
}

