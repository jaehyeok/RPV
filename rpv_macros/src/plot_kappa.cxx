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

bool formatLatex=false;

float addInQuad(float a, float b);
vector<float> ratioError(float a, float a_err, float b, float b_err); // a/b
vector<float> calculateR(TH1F* h1, int mjbin);


//
// main
//
int main(int argc, char *argv[])
{
    TString syst("nominal"), updo("X");
    float mjmin(500), mjmax(1400);
    TString arg(argv[1]);
    if(argc<=2){
      cout << "if you want to know about arguments, use --help to get help" << endl;
    }
    else if(argc<=2 && arg == "--help"){
      cout << "./run/plot_kappa.exe [Systematics] [Up/Down] [MJ minimum] [MJ maximum]" << endl;
      return 1;
    }
    else if(argc>2){

      syst = argv[1];
      updo = argv[2];
      if(argc>4){
        mjmin = atof(argv[3]);
        mjmax = atof(argv[4]);
      }
    }
    cout << "Systematics : " << syst <<endl;
    cout << "Up / Down   : " << updo <<endl;
    
    float binsize = (mjmax-mjmin)/3;
    cout << "MJ bimn     : [ " << mjmin << ", " << mjmin+binsize << ", " << mjmin+2*binsize << "+ ]" << endl; 
    cout << endl;

    cout << " ........................... "<< endl; 
    cout << " .... Evaluating kappas .... " << endl; 
    cout << " ........................... "<< endl; 

    TString bin[52] = {
        // control regions
        "0-lepton,HT>1500,4#leq N_{jets}#leq5,500<MJ<800",
        "0-lepton,HT>1500,6#leq N_{jets}#leq7,500<MJ<800",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,500<MJ<800", 
        "0-lepton,HT>1500,4#leq N_{jets}#leq5,MJ>800",
        "0-lepton,HT>1500,6#leq N_{jets}#leq7,MJ>800",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,MJ>800",
        // low MJ control regions
        "0-lepton,HT>1500,4#leq N_{jets}#leq5,300<MJ<500",  // 6
        "0-lepton,HT>1500,6#leq N_{jets}#leq7,300<MJ<500",
        "0-lepton,HT>1500,8#leq N_{jets}#leq9,300<MJ<500",
        "0-lepton,HT>1500,N_{jets}#geq10,300<MJ<500",
        // signal regions, low MJ
        "0-lepton,HT>1500,N_{jets}#geq10,500<MJ<800",       // 10
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,500<MJ<800",
        "1-lepton,HT>1200,N_{jets}#geq8,500<MJ<800",
        // signal regions, high MJ
        "0-lepton,HT>1500,N_{jets}#geq10,800<MJ<1000",           // 13
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,800<MJ<100",
        "1-lepton,HT>1200,N_{jets}#geq8,800<MJ<100",
        // Missing regions
        "0-lepton,HT>1500,8#leq N_{jets}#leq9,500<MJ<800",  // 16
        "0-lepton,HT>1500,8#leq N_{jets}#leq9,800<MJ<100", 
        // Very high MJ bins
        "0-lepton,HT>1500,8#leq N_{jets}#leq9,MJ>100",      // 18
        "0-lepton,HT>1500,N_{jets}#geq10,MJ>100",           
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,MJ>100",
        "1-lepton,HT>1200,N_{jets}#geq8,MJ>1000",
        // Njets-Nb basis
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=0",
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=0",
        "1-lepton,HT>1200,N_{jets}#geq8,N_{b}=0",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=1",
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=1",
        "1-lepton,HT>1200,N_{jets}#geq8,N_{b}=1",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=2",
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=2",
        "1-lepton,HT>1200,N_{jets}#geq8,N_{b}=2",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}=3",
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=3",
        "1-lepton,HT>1200,N_{jets}#geq8,N_{b}=3",
        "1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}#geq4",
        "1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq4",
        "1-lepton,HT>1200,N_{jets}#geq8,N_{b}#geq4"
        "0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=0",
        "0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=0",
        "0-lepton,HT>1200,N_{jets}#geq10,N_{b}=0",
        "0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=1",
        "0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=1",
        "0-lepton,HT>1200,N_{jets}#geq10,N_{b}=1",
        "0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=2",
        "0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=2",
        "0-lepton,HT>1200,N_{jets}#geq10,N_{b}=2",
        "0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}=3",
        "0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}=3",
        "0-lepton,HT>1200,N_{jets}#geq10,N_{b}=3",
        "0-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq4",
        "0-lepton,HT>1200,8#leq N_{jets}#leq9,N_{b}#geq4",
        "0-lepton,HT>1200,N_{jets}#geq10,N_{b}#geq4"
    };

    TString binLatex[52] = {
        // control regions
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},4\\leq N_{jets}\\leq5, 500<M_{J}<800~\\textrm{GeV}",
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},6\\leq N_{jets}\\leq7, 500<M_{J}<800~\\textrm{GeV}",
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5, 500<M_{J}<800~\\textrm{GeV}", 
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},4\\leq N_{jets}\\leq5, M_{J}>800~\\textrm{GeV}",
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},6\\leq N_{jets}\\leq7, M_{J}>800~\\textrm{GeV}",
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5, M_{J}>800~\\textrm{GeV}",
        // low M_{J} control regions
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},4\\leq N_{jets}\\leq5,300<M_{J}<500~\\textrm{GeV}",  // 6
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},6\\leq N_{jets}\\leq7,300<M_{J}<500~\\textrm{GeV}",
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},8\\leq N_{jets}\\leq9,300<M_{J}<500~\\textrm{GeV}",
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},N_{jets}\\geq10,300<M_{J}<500~\\textrm{GeV}",
        // signal regions, low M_{J}
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},N_{jets}\\geq10,500<M_{J}<800~\\textrm{GeV}",       // 10
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,500<M_{J}<800~\\textrm{GeV}",
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,500<M_{J}<800~\\textrm{GeV}",
        // signal regions, high M_{J}
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},N_{jets}\\geq10,800<M_{J}<1000~\\textrm{GeV}",           // 13
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,800<M_{J}<1000~\\textrm{GeV}",
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,800<M_{J}<1000~\\textrm{GeV}",
        // Missing regions
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},8\\leq N_{jets}\\leq9,500<M_{J}<800~\\textrm{GeV}",  // 16
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},8\\leq N_{jets}\\leq9,800<M_{J}<1000~\\textrm{GeV}",
        // Very high MJ bins
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},8\\leq N_{jets}\\leq9,M_{J}>1000~\\textrm{GeV}",
        "N_{leps}=0,H_{T}>1500~\\textrm{GeV},N_{jets}\\geq10,M_{J}>1000~\\textrm{GeV}",           // 13
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,M_{J}>1000~\\textrm{GeV}",
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,M_{J}>1000~\\textrm{GeV}",
        // Njets-Nb basis
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=0",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=0",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=0",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=1",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=1",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=1",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=2",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=2",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq8,N_{b}=2",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=3",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=3",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq8,N_{b}=3",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}\\geq4",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}\\geq4",    
        "N_{leps}=1,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq8,N_{b}\\geq4",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=0",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},7\\leq N_{jets}\\leq8,N_{b}=0",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq10,N_{b}=0",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=1",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},7\\leq N_{jets}\\leq8,N_{b}=1",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq10,N_{b}=1",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=2",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},7\\leq N_{jets}\\leq8,N_{b}=2",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq10,N_{b}=2",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=3",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},7\\leq N_{jets}\\leq8,N_{b}=3",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq10,N_{b}=3",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}\\geq4",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV},7\\leq N_{jets}\\leq8,N_{b}\\geq4",    
        "N_{leps}=0,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq10,N_{b}\\geq4"   
    };

    //TFile* infile  = TFile::Open("variations/output_nominal_newnt_inclnb0.root", "READ");
    TFile* infile  = TFile::Open("variations/output_newnt.root", "READ");
   
    vector<vector<float>> kappa1;
    vector<vector<float>> kappa2;
    
    //
    TH1F *h1_mj_data[52], *h1_mj_qcd[52], *h1_mj_ttbar[52], *h1_mj_wjets[52], *h1_mj_other[52], *h1_mj_mc[52];
    TH1F *h1_mj_qcd_syst[52], *h1_mj_ttbar_syst[52], *h1_mj_wjets_syst[52], *h1_mj_other_syst[52], *h1_mj_mc_syst[52];
    for(int ibin=22; ibin<52; ibin++)  
    { 
      // define histograms
      h1_mj_data[ibin]       = new TH1F(Form("h1_mj_data_bin%i", ibin), Form("h1_mj_data_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_qcd[ibin]        = new TH1F(Form("h1_mj_qcd_bin%i", ibin), Form("h1_mj_qcd_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_ttbar[ibin]      = new TH1F(Form("h1_mj_ttbar_bin%i", ibin), Form("h1_mj_ttbar_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_wjets[ibin]      = new TH1F(Form("h1_mj_wjets_bin%i", ibin), Form("h1_mj_wjets_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_other[ibin]      = new TH1F(Form("h1_mj_other_bin%i", ibin), Form("h1_mj_other_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_mc[ibin]         = new TH1F(Form("h1_mj_mc_bin%i", ibin), Form("h1_mj_mc_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_qcd_syst[ibin]   = new TH1F(Form("h1_mj_qcd_syst_bin%i", ibin), Form("h1_mj_qcd_syst_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_ttbar_syst[ibin] = new TH1F(Form("h1_mj_ttbar_syst_bin%i", ibin), Form("h1_mj_ttbar_syst_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_wjets_syst[ibin] = new TH1F(Form("h1_mj_wjets_syst_bin%i", ibin), Form("h1_mj_wjets_syst_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_other_syst[ibin] = new TH1F(Form("h1_mj_other_syst_bin%i", ibin), Form("h1_mj_other_syst_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_mc_syst[ibin]    = new TH1F(Form("h1_mj_mc_syst_bin%i", ibin), Form("h1_mj_mc_syst_bin%i", ibin), 3, mjmin, mjmax);
      h1_mj_data[ibin]->Sumw2(); 
      h1_mj_qcd[ibin]->Sumw2(); 
      h1_mj_ttbar[ibin]->Sumw2(); 
      h1_mj_wjets[ibin]->Sumw2(); 
      h1_mj_other[ibin]->Sumw2(); 
      h1_mj_mc[ibin]->Sumw2(); 
      h1_mj_qcd_syst[ibin]->Sumw2(); 
      h1_mj_ttbar_syst[ibin]->Sumw2(); 
      h1_mj_wjets_syst[ibin]->Sumw2(); 
      h1_mj_other_syst[ibin]->Sumw2(); 
      h1_mj_mc_syst[ibin]->Sumw2(); 

      // Get histograms from root file
      if(syst=="nominal"){
        h1_mj_data[ibin]  = static_cast<TH1F*>(infile->Get(Form("bin%i/data_obs", ibin))); 
      }
      else if(syst!="nominal"){
        h1_mj_qcd_syst[ibin]   = static_cast<TH1F*>(infile->Get(Form("bin%i/qcd_%s%s", ibin, syst.Data(), updo.Data()))); 
        h1_mj_ttbar_syst[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar_%s%s", ibin, syst.Data(), updo.Data()))); 
        h1_mj_wjets_syst[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/wjets_%s%s", ibin, syst.Data(), updo.Data()))); 
        //h1_mj_wjets[ibin]->Scale(1.53); //FIXME
        h1_mj_other_syst[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/other_%s%s", ibin, syst.Data(), updo.Data()))); 
        h1_mj_data[ibin] = static_cast<TH1F*>(h1_mj_qcd_syst[ibin]->Clone(Form("h1_mj_mc_syst_bin%i", ibin))); 
        h1_mj_data[ibin]->Add(h1_mj_ttbar_syst[ibin]);
        h1_mj_data[ibin]->Add(h1_mj_wjets_syst[ibin]);
        h1_mj_data[ibin]->Add(h1_mj_other_syst[ibin]);
      }
      h1_mj_qcd[ibin]   = static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin))); 
      h1_mj_ttbar[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin))); 
      h1_mj_wjets[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin))); 
      //h1_mj_wjets[ibin]->Scale(1.53); //FIXME
      h1_mj_other[ibin] = static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin))); 
      h1_mj_mc[ibin] = static_cast<TH1F*>(h1_mj_qcd[ibin]->Clone(Form("h1_mj_mc_bin%i", ibin))); 
      h1_mj_mc[ibin]->Add(h1_mj_ttbar[ibin]);
      h1_mj_mc[ibin]->Add(h1_mj_wjets[ibin]);
      h1_mj_mc[ibin]->Add(h1_mj_other[ibin]);
    } 
    
    for(int ibin=22; ibin<52; ibin++)
    {
       vector<float> r1_data;
       vector<float> r2_data;
       vector<float> r1_mc; 
       vector<float> r2_mc;
     
      TH1F* h1_mj_data_thisbin = h1_mj_data[ibin];
      TH1F* h1_mj_mc_thisbin = h1_mj_mc[ibin];

      // Calculate R and kappa values
      if((ibin>=31 && ibin<=33) || (ibin>=46 && ibin<=48)) // for nb=3, combine with nb=4 
      { 
        h1_mj_data_thisbin->Add(h1_mj_data[ibin+3]);
        h1_mj_mc_thisbin->Add(h1_mj_mc[ibin+3]);
      } 

      r1_data = calculateR(h1_mj_data_thisbin, 1);
      r2_data = calculateR(h1_mj_data_thisbin, 2);
      r1_mc   = calculateR(h1_mj_mc_thisbin, 1);
      r2_mc   = calculateR(h1_mj_mc_thisbin, 2);

      cout << ".... " << bin[ibin] << endl; 

      cout << "r1 data: " << r1_data[0] << " +- " << r1_data[1] <<  endl;
      cout << "r2 data: " << r2_data[0] << " +- " << r2_data[1] << endl;
      cout << "r1 mc:   " << r1_mc[0] << " +- " << r1_mc[1] << endl;
      cout << "r2 mc:   " << r2_mc[0] << " +- " << r2_mc[1] << endl;

      kappa1.push_back(ratioError(r1_data[0], r1_data[1], r1_mc[0], r1_mc[1]));
      kappa2.push_back(ratioError(r2_data[0], r2_data[1], r2_mc[0], r2_mc[1]));
      cout << "kappa1:   " << kappa1.at(ibin-22).at(0) << " +- " <<  kappa1.at(ibin-22).at(1) << endl;
      cout << "kappa2:   " << kappa2.at(ibin-22).at(0) << " +- " <<  kappa2.at(ibin-22).at(1) << endl;
    }   

    // visualize 
    TH1F *h1_0l_summary1 = new TH1F("h1_0l_summary1", "h1_0l_summary1", 75, 0, 75);
    TH1F *h1_0l_summary2 = new TH1F("h1_0l_summary2", "h1_0l_summary2", 75, 0, 75);
    TH1F *h1_1l_summary1 = new TH1F("h1_1l_summary1", "h1_1l_summary1", 75, 0, 75);
    TH1F *h1_1l_summary2 = new TH1F("h1_1l_summary2", "h1_1l_summary2", 75, 0, 75);
    for(int ibin=22; ibin<52; ibin++)
    { 
      // three Njets regions 
      int njets_region=1;
      if(ibin%3==2) njets_region=2;
      if(ibin%3==0) njets_region=3;
      // four Nb regions 
      int nb_region=0;
      if(ibin>=22 && ibin<=24) nb_region=0;
      if(ibin>=25 && ibin<=27) nb_region=1;
      if(ibin>=28 && ibin<=30) nb_region=2;
      if(ibin>=31 && ibin<=33) nb_region=3; 
      if(ibin>=34 && ibin<=36) continue; //nb_region=4;
      if(ibin>=37 && ibin<=39) nb_region=0;
      if(ibin>=40 && ibin<=42) nb_region=1;
      if(ibin>=43 && ibin<=45) nb_region=2;
      if(ibin>=46 && ibin<=48) nb_region=3;
      if(ibin>=49 && ibin<=51) continue; //nb_region=4;
      int bin_index= (njets_region-1)*25 + nb_region*2 + 8;
      if(kappa1.at(ibin-22).at(0)>=0)
      {
        if(ibin<37)
        {
          h1_1l_summary1->SetBinContent(bin_index, kappa1.at(ibin-22).at(0));
          h1_1l_summary1->SetBinError(bin_index, kappa1.at(ibin-22).at(1));
        }
        else
        { 
          h1_0l_summary1->SetBinContent(bin_index, kappa1.at(ibin-22).at(0));
          h1_0l_summary1->SetBinError(bin_index, kappa1.at(ibin-22).at(1));
        }
      }
      else 
      { 
        if(ibin<37)
        {
          h1_1l_summary1->SetBinContent(bin_index, -1);
          h1_1l_summary1->SetBinError(bin_index, 0);
        }
        else 
        {
          h1_0l_summary1->SetBinContent(bin_index, -1);
          h1_0l_summary1->SetBinError(bin_index, 0);
        }
      }
      if(kappa2.at(ibin-22).at(0)>=0){
        if(ibin<37)
        {
          h1_1l_summary2->SetBinContent(bin_index, kappa2.at(ibin-22).at(0));
          h1_1l_summary2->SetBinError(bin_index, kappa2.at(ibin-22).at(1));
        }
        else 
        { 
          h1_0l_summary2->SetBinContent(bin_index, kappa2.at(ibin-22).at(0));
          h1_0l_summary2->SetBinError(bin_index, kappa2.at(ibin-22).at(1));
        }
      }
      else 
      { 
        if(ibin<37)
        {
          h1_1l_summary2->SetBinContent(bin_index, -1);
          h1_1l_summary2->SetBinError(bin_index, 0);
        }
        else 
        {
          h1_0l_summary2->SetBinContent(bin_index, -1);
          h1_0l_summary2->SetBinError(bin_index, 0);
        }
      }
    }

    TCanvas *c = new TCanvas("c", "c", 1200, 1400);
    c->Divide(1,4);
    c->cd(1);
    h1_1l_summary1->SetTitle("#kappa (800-1100/500-800 GeV)");
    h1_1l_summary1->SetLineColor(kBlack);
    h1_1l_summary1->SetMarkerColor(kBlack);
    h1_1l_summary1->SetMarkerStyle(21);
    h1_1l_summary1->SetStats(0);
    h1_1l_summary1->SetMinimum(0);
    h1_1l_summary1->SetMaximum(3);
    h1_1l_summary1->Draw("ep");
    c->cd(2);
    h1_1l_summary2->SetTitle("#kappa (1100-inf/500-800 GeV)");
    h1_1l_summary2->SetLineColor(kBlack);
    h1_1l_summary2->SetMarkerColor(kBlack);
    h1_1l_summary2->SetMarkerStyle(21);
    h1_1l_summary2->SetStats(0);
    h1_1l_summary2->SetMinimum(0);
    h1_1l_summary2->SetMaximum(3);
    h1_1l_summary2->Draw("ep");
    c->cd(3);
    h1_0l_summary1->SetTitle("#kappa (800-1100/500-800 GeV)");
    h1_0l_summary1->SetLineColor(kBlue);
    h1_0l_summary1->SetMarkerColor(kBlue);
    h1_0l_summary1->SetMarkerStyle(21);
    h1_0l_summary1->SetStats(0);
    h1_0l_summary1->SetMinimum(0);
    h1_0l_summary1->SetMaximum(3);
    h1_0l_summary1->Draw("ep");
    c->cd(4);
    h1_0l_summary2->SetTitle("#kappa (1100-inf/500-800 GeV)");
    h1_0l_summary2->SetLineColor(kBlue);
    h1_0l_summary2->SetMarkerColor(kBlue);
    h1_0l_summary2->SetMarkerStyle(21);
    h1_0l_summary2->SetStats(0);
    h1_0l_summary2->SetMinimum(0);
    h1_0l_summary2->SetMaximum(3);
    h1_0l_summary2->Draw("ep");
    c->Print("plots/kappa_summary_"+syst+updo+".pdf");
    c->Print("plots/kappa_summary_"+syst+updo+".png");
   
/*
    //
    // 1-lepton
    //
    
    // tcanvas
    TCanvas *c_kappa12 = new TCanvas("c_kappa12","c_kappa12", 1200, 200);
    TCanvas *c_kappa13 = new TCanvas("c_kappa13","c_kappa13", 1300, 200);
    TCanvas *c_kappa23 = new TCanvas("c_kappa23","c_kappa23", 2300, 200);

    // kappa plots
    TH1F *h1_kappa_ttbar[3]; 
    TH1F *h1_kappa_qcd[3]; 
    TH1F *h1_kappa_wjets[3]; 
    TH1F *h1_kappa_other[3]; 
    TH1F *h1_kappa_all[3]; 
    TH1F *h1_kappa_data[3];

    for(int ikappa=0; ikappa<3; ikappa++)
    { 
        char* tag = "12";
        if(ikappa==1) tag = "13";
        else if(ikappa==2) tag = "23";
        h1_kappa_ttbar[ikappa] = new TH1F(Form("h1_kappa_qcd_%s", tag), Form("h1_kappa_qcd_%s", tag), );     
    }

    int tablebin_1lep[12]={22,23,24,25,26,27,28,29,30,31,32,33};
    for(int ibin=22; ibin<34; ibin++)
    { 
        int tablebin=tablebin_1lep[ibin-22];
       


        float databin(0), mcbin(0); 
        for(int imj=0; imj<3; imj++) 
        { 
            databin = databin + data[tablebin][imj]; 
            mcbin = mcbin + qcd[tablebin][imj] + ttbar[tablebin][imj] + wjets[tablebin][imj] + other[tablebin][imj]; 
        }

    }
*/
    infile->Close();

    return 0;
}

//
float addInQuad(float a, float b)
{
    return TMath::Sqrt(a*a+b*b);
}
//
vector<float> ratioError(float a, float a_err, float b, float b_err)
{
  float r = a/b;
  float r_err = r * TMath::Sqrt(a_err*a_err/a/a + b_err*b_err/b/b);
  if (b==0 || a<0 || b<0) {r=-1; r_err=0;}
  vector<float> results; 
  results.push_back(r);
  results.push_back(r_err);
  return results;
}

// 
vector<float> calculateR(TH1F* h1, int mjbin)
{
  float r = h1->GetBinContent(mjbin+1)/h1->GetBinContent(1);//mjbin);
  if(h1->GetBinContent(mjbin)==0) r=-1.;
  float r_err = r * TMath::Sqrt(h1->GetBinError(mjbin+1)*h1->GetBinError(mjbin+1)/h1->GetBinContent(mjbin+1)/h1->GetBinContent(mjbin+1) 
                              + h1->GetBinError(1/*mjbin*/)*h1->GetBinError(1/*mjbin*/)/h1->GetBinContent(1)/h1->GetBinContent(1));
  vector<float> results; 
  results.push_back(r);
  results.push_back(r_err);
  return results;
}


