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

float addInQuad(float a, float b);
void printOneLine(int nb, 
                  float data, float qcd, float ttbar, float wjets, float other, 
                  float sig1500, float sig1600, float sig1700, float sig1800, float sig1900,
                  float data_err, float qcd_err, float ttbar_err, float wjets_err, float other_err, 
                  float sig1500_err, float sig1600_err, float sig1700_err, float sig1800_err, float sig1900_err, bool doLatex);
//void printOneLine(int nb, 
//                  float qcd, float ttbar, float wjets, float other, 
//                  float sig1500, 
//                  float qcd_err, float ttbar_err, float wjets_err, float other_err, 
//                  float sig1500_err, bool doLatex);
void printYieldBin(int nb, float data,
                   float qcd, float ttbar, float wjets, float other, float sig,
                   float qcd_err, float ttbar_err, float wjets_err, float other_err,
                   float dataovermc, bool doNorm, bool printErr);


//
// main
//
int main(int argc, char* argv[])
{
    TString inputName = argv[1];
    cout << " ........................... "<< endl; 
    cout << " .. I am making yield table " << endl; 
    cout << " ........................... "<< endl; 

    const int nbins = 52;
    TString bin[nbins] = {
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
	"1-lepton,HT>1200,4#leq N_{jets}#leq5,N_{b}#geq4",//bin34 //ibin==34
	"1-lepton,HT>1200,6#leq N_{jets}#leq7,N_{b}#geq4",
	"1-lepton,HT>1200,N_{jets}#geq8,N_{b}#geq4",
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

    TString binLatex[nbins] = {
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
	"N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}\\geq3",    
	"N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=3",    
	"N_{leps}=1,H_{T}>1200~\\textrm{GeV}, N_{jets}\\geq8,N_{b}=3",
	"N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}\\geq4",//bin34
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

    //TFile* infile  = TFile::Open("variations/output_nominal_newnt.root", "READ");
    //TFile* infile  = TFile::Open("variations/output_newnt_nl0shape2017.root", "READ");
    //TFile* infile  = TFile::Open("variations/output_newnt_nl0shape2018.root", "READ");
    //TFile* infile  = TFile::Open("variations/output_nominal_newnt_nl0shape2016.root", "READ"); 
    TFile* infile  = TFile::Open(inputName, "READ"); 
 
    float data[nbins][3], qcd[nbins][3], ttbar[nbins][3], wjets[nbins][3], other[nbins][3],
          sig1500[nbins][3], sig1600[nbins][3], sig1700[nbins][3], sig1800[nbins][3], sig1900[nbins][3],
          data_err[nbins][3], qcd_err[nbins][3], ttbar_err[nbins][3], wjets_err[nbins][3], other_err[nbins][3],
          sig1500_err[nbins][3], sig1600_err[nbins][3], sig1700_err[nbins][3], sig1800_err[nbins][3], sig1900_err[nbins][3];
    for(int ibin=0; ibin<nbins; ibin++)  
    {
	if(ibin==34) continue; // exclude bin34
        //if(ibin>=6 && ibin<=9) continue;
        for(int inb=0; inb<3; inb++) 
        {
            data[ibin][inb] = 0;
            qcd[ibin][inb] = 0;
            ttbar[ibin][inb] = 0;
            wjets[ibin][inb] = 0;
            other[ibin][inb] = 0;
            sig1500[ibin][inb] = 0;
            sig1600[ibin][inb] = 0;
            sig1700[ibin][inb] = 0;
            sig1800[ibin][inb] = 0;
            sig1900[ibin][inb] = 0;   
            data_err[ibin][inb] = 0;
            qcd_err[ibin][inb] = 0;
            ttbar_err[ibin][inb] = 0;
            wjets_err[ibin][inb] = 0;
            other_err[ibin][inb] = 0;
            sig1500_err[ibin][inb] = 0;
            sig1600_err[ibin][inb] = 0;
            sig1700_err[ibin][inb] = 0;
            sig1800_err[ibin][inb] = 0;
            sig1900_err[ibin][inb] = 0;

        }
    }
    //
    for(int ibin=22; ibin<nbins; ibin++) 
    {
	if(ibin==34) continue; //exclude bin34
        //if(ibin>=6 && ibin<=9) continue;
        //TDirectory* dir = infile->GetDirectory(Form("bin%i", ibin));

        for(int inb=0; inb<3; inb++) 
        {
            data[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/data_obs", ibin)))->GetBinContent(inb+1);
	    qcd[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)))->GetBinContent(inb+1);
	    ttbar[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)))->GetBinContent(inb+1);
            wjets[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)))->GetBinContent(inb+1);
	    other[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin)))->GetBinContent(inb+1);
            //data[ibin][inb]=qcd[ibin][inb]+ttbar[ibin][inb]+wjets[ibin][inb]+other[ibin][inb];
            sig1500[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1500", ibin)))->GetBinContent(inb+1);
            sig1600[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1600", ibin)))->GetBinContent(inb+1);
            sig1700[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1700", ibin)))->GetBinContent(inb+1);
            sig1800[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1800", ibin)))->GetBinContent(inb+1);
            sig1900[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1900", ibin)))->GetBinContent(inb+1);// */
            
            data_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/data_obs", ibin)))->GetBinError(inb+1);
            qcd_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/qcd", ibin)))->GetBinError(inb+1);
            ttbar_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/ttbar", ibin)))->GetBinError(inb+1);
            wjets_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/wjets", ibin)))->GetBinError(inb+1);
            other_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/other", ibin)))->GetBinError(inb+1);
            data_err[ibin][inb]= TMath::Sqrt(data[ibin][inb]);
            sig1500_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1500", ibin)))->GetBinError(inb+1);
            sig1600_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1600", ibin)))->GetBinError(inb+1);
            sig1700_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1700", ibin)))->GetBinError(inb+1);
            sig1800_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1800", ibin)))->GetBinError(inb+1);
            sig1900_err[ibin][inb]= static_cast<TH1F*>(infile->Get(Form("bin%i/signal_M1900", ibin)))->GetBinError(inb+1);

        }  
    }
    float sig1500sum(0), sig1600sum(0), sig1700sum(0), sig1800sum(0), sig1900sum(0);
    for(int ibin=22; ibin<nbins; ibin++) 
    {
      if(ibin==34) continue;//exclude bin34
      //if(ibin>5 && ibin<10) continue; // skip low MJ bins 
      for(int inb=0; inb<3; inb++)  
      {
          sig1500sum = sig1500sum + sig1500[ibin][inb]; 
          sig1600sum = sig1600sum + sig1600[ibin][inb]; 
          sig1700sum = sig1700sum + sig1700[ibin][inb]; 
          sig1800sum = sig1800sum + sig1800[ibin][inb]; 
          sig1900sum = sig1900sum + sig1900[ibin][inb]; 
      }
    }

    // -----------------------------------------------------
    // table for AN
    // -----------------------------------------------------
    for(int ibin=22; ibin<nbins; ibin++) 
    {
	if(ibin==34) continue;
       //if(ibin>5 && ibin<10) continue; // skip low MJ bins

       if(formatLatex) 
       {

           cout << "\\begin{table}" << endl;
           cout << "\\centering" << endl;
           cout << "\\caption{Yields for $" << binLatex[ibin].Data()<< "$. Uncertainties are statistical only.}" << endl;
           cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c  c  c  }" << endl;
           cout << "\\hline\\hline" << endl;
           cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & $m_{\\tilde{g}}=1000$ & $m_{\\tilde{g}}=1700$ & $m_{\\tilde{g}}=1900$ \\\\"  << endl;
           cout << "\\hline" << endl;
       }
       else 
       {
        cout << "|" << 
            left << setw(142) << Form("Bin %i: %s",ibin, (bin[ibin].ReplaceAll("#leq","<=").ReplaceAll("#geq",">=")).Data())   << " |"  << endl;
        cout << "|" << 
            setw(4) << Form("Mj")   << " |"  <<
            //setw(10) << Form("%.2f",data) << " |" << 
            setw(16) << "qcd"  << " |" <<
            setw(16) << "ttbar" << " |" <<
            setw(16) << "wjets" << " |" << 
            setw(16) << "other" << " |" << 
            setw(20) << "M=1000(S/B)"<< " |" << 
            setw(20) << "M=1700(S/B)" << " |" << 
            setw(20) << "M=1900(S/B)" << " |" << endl;
        } 


/*
        for(int inb=0; inb<3; inb++) 
        { 
            printOneLine(inb,
                    data[ibin][inb], qcd[ibin][inb], ttbar[ibin][inb], wjets[ibin][inb], other[ibin][inb],
                    sig1500[ibin][inb], sig1600[ibin][inb], sig1700[ibin][inb], sig1800[ibin][inb], sig1900[ibin][inb],
                    //sig1500[ibin][inb]/sig1500sum, sig1600[ibin][inb]/sig1600sum, sig1700[ibin][inb]/sig1700sum, 
                    //    sig1800[ibin][inb]/sig1800sum, sig1900[ibin][inb]/sig1900sum,
                    data_err[ibin][inb], qcd_err[ibin][inb], ttbar_err[ibin][inb], wjets_err[ibin][inb], other_err[ibin][inb],
                    sig1500_err[ibin][inb], sig1600_err[ibin][inb], sig1700_err[ibin][inb], sig1800_err[ibin][inb], sig1900_err[ibin][inb],
                    formatLatex);
        } 
*/
        if(formatLatex)  
        {
            cout<< "\\hline" << endl;
            cout << "\\end{tabular}"<<endl;
            cout << "\\end{table}\n"; 
            cout << endl;
        } 
        else 
        { 
            cout << endl;
        }
    }
    
    // -----------------------------------------------------
    // table for supplementary material
    // -----------------------------------------------------

    // Get pre-fit errors
    float err[4][nbins][3];

    for(int ibin=22; ibin<nbins; ibin++)
    {
	if(ibin==34) continue;//exclude bin34
        for(int inb=0; inb<3; inb++)
        {
            err[0][ibin][inb] = qcd_err[ibin][inb];
            err[1][ibin][inb] = ttbar_err[ibin][inb];
            err[2][ibin][inb] = wjets_err[ibin][inb];
            err[3][ibin][inb] = other_err[ibin][inb];
        }
    }

    // Get relative error using up variations
    // using both up and down is be better way, but should be very close
    for(int ibin=22; ibin<nbins; ibin++) 
    {
	if(ibin==34) continue;//exclude bin34
        if(ibin>=6 && ibin<=9) continue;

        for(int iproc=0; iproc<4; iproc++)
        {
            std::string process;
            if(iproc==0)  process = "qcd";
            if(iproc==1)  process = "ttbar";
            if(iproc==2)  process = "wjets";
            if(iproc==3)  process = "other";

            // loop over nb bins
            for(int inb=0; inb<3; inb++)
            {
                float central;
                float up;

                if(infile->Get(Form("bin%i/%s", ibin, process.c_str()))==0x0) continue;
                central = static_cast<TH1F*>(infile->Get(Form("bin%i/%s", ibin, process.c_str())))->GetBinContent(inb+1);
/*                if(central !=0)
                {
                    // btag bc
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_btag_bcUp", ibin, process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = TMath::Abs(up-central)/central;

                    // btag udsg
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_btag_udsgUp", ibin, process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);

                    // pileup
//                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_pileupUp", ibin, process.c_str())))->GetBinContent(inb+1);
//                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);

                    // qcd flavor
                    if(iproc==0)
                    {
                        up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_qcd_flavorUp", ibin, process.c_str())))->GetBinContent(inb+1);
                        err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    }

                    // scale variations
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%s_murUp", ibin, process.c_str(), process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%s_mufUp", ibin, process.c_str(), process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_%s_murfUp", ibin, process.c_str(), process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);

                    // jer jes
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_jerUp", ibin, process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_jesUp", ibin, process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    
                    // pdf
//                    float pdferr=0;
//                    for(int ipdf=0; ipdf<100; ipdf++)
//                    {
//                        up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_w_pdf%iUp", ibin, process.c_str(), ipdf)))->GetBinContent(inb+1);
//                        pdferr  = addInQuad(pdferr,TMath::Abs(up-central)/central);
//                    }
 //                   err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],pdferr/10);
 //                   cout << "pdf: " <<  ibin << " " << inb << " " << pdferr << endl;

                    // Stats
                    if(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb))!=0x0)
                    {
                        up = static_cast<TH1F*>(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb)))->GetBinContent(inb+1);
                        err[iproc][ibin][inb] = addInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central);
                    }
                }
                // cout << "both: " <<  ibin << " " << inb << " " << err[iproc][ibin][inb]<< endl;
		*/
            }
        }

    }
   

    //
    // CR 
    //
    /*int tablebin_cr[6]={0,1,2,3,4,5};
    cout << "\\begin{table}" << endl;
    cout << "\\centering" << endl;
    cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
    cout << "\\hline" << endl;
    cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1500\\textrm{GeV}$\\\\"  << endl;
    cout << "\\hline\\hline" << endl;

    for(int ibin=22; ibin<6; ibin++)
    { 
        int tablebin=tablebin_cr[ibin];
        
        float databin(0), mcbin(0); 
        for(int inb=0; inb<3; inb++) 
        { 
            databin = databin + data[tablebin][inb]; 
            mcbin = mcbin + qcd[tablebin][inb] + ttbar[tablebin][inb] + wjets[tablebin][inb] + other[tablebin][inb]; 
        }

        cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$} \\\\" << endl;
        cout << "\\hline" << endl;
        for(int inb=0; inb<3; inb++)
            printYieldBin(inb,
                    data[tablebin][inb],
                    qcd[tablebin][inb],
                    ttbar[tablebin][inb],
                    wjets[tablebin][inb],
                    other[tablebin][inb],
                    sig1500[tablebin][inb],
                    err[0][tablebin][inb]*qcd[tablebin][inb],
                    err[1][tablebin][inb]*ttbar[tablebin][inb],
                    err[2][tablebin][inb]*wjets[tablebin][inb],
                    err[3][tablebin][inb]*other[tablebin][inb],
                    databin/mcbin, false*/ /*renormalize to data*//*,false);
        cout << "\\hline" << endl;
    }
    cout<< "\\hline" << endl;
    cout << "\\end{tabular}"<<endl;
    cout << "\\end{table}\n"<< endl;

    cout << endl;
    cout << endl;
    //
    // 0-lepton
    //
    int tablebin_0lep[6]={16,17,18,10,13,19};
    cout << "\\begin{table}" << endl;
    cout << "\\centering" << endl;
    cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
    cout << "\\hline" << endl;
    cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1600\\textrm{GeV}$\\\\"  << endl;
    cout << "\\hline\\hline" << endl;

    for(int ibin=22; ibin<6; ibin++)
    { 
        int tablebin=tablebin_0lep[ibin];
        
        float databin(0), mcbin(0); 
        for(int inb=0; inb<3; inb++) 
        { 
            databin = databin + data[tablebin][inb]; 
            mcbin = mcbin + qcd[tablebin][inb] + ttbar[tablebin][inb] + wjets[tablebin][inb] + other[tablebin][inb]; 
        }

        cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$} \\\\" << endl;
        cout << "\\hline" << endl;
        for(int inb=0; inb<3; inb++)
            printYieldBin(inb,
                    data[tablebin][inb],
                    qcd[tablebin][inb],
                    ttbar[tablebin][inb],
                    wjets[tablebin][inb],
                    other[tablebin][inb],
                    sig1600[tablebin][inb],
                    err[0][tablebin][inb]*qcd[tablebin][inb],
                    err[1][tablebin][inb]*ttbar[tablebin][inb],
                    err[2][tablebin][inb]*wjets[tablebin][inb],
                    err[3][tablebin][inb]*other[tablebin][inb],
                    databin/mcbin, false*/ /*renormalize to data*//*, false);
        cout << "\\hline" << endl;
    }
    cout<< "\\hline" << endl;
    cout << "\\end{tabular}"<<endl;
    cout << "\\end{table}\n"<< endl;

    cout << endl;
    cout << endl;
*/

    //
    // 1-lepton
    //
    int tablebin_1lep[30]={22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
    cout << "\\begin{table}" << endl;
    cout << "\\centering" << endl;
    cout << "\\resizebox{\\textwidth}{!}{%" << endl;
    cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
    cout << "\\hline" << endl;
    cout << "$M_{J}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1800$ $\\textrm{GeV}$\\\\"  << endl;
    cout << "\\hline\\hline" << endl;

//    for(int ibin=22; ibin<nbins; ibin++)
    for(int ibin=22; ibin<37; ibin++) // for only Nlep=1 bins
    { 
	if(ibin==34) continue;//exclude bin34
        int tablebin=tablebin_1lep[ibin-22];
        
        float databin(0), mcbin(0); 
        for(int inb=0; inb<3; inb++) 
        { 
            databin = databin + data[tablebin][inb]; 
            mcbin = mcbin + qcd[tablebin][inb] + ttbar[tablebin][inb] + wjets[tablebin][inb] + other[tablebin][inb]; 
        }

        cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$} \\\\" << endl;
        cout << "\\hline" << endl;
        for(int inb=0; inb<3; inb++) {
	  if(ibin==32 || ibin==33 || ibin==35 || ibin==36) {
	    data[tablebin][inb]=0;  //FIXME when unblinding
	  }
            printYieldBin(inb,
                    data[tablebin][inb],
                    qcd[tablebin][inb],
                    ttbar[tablebin][inb],
                    wjets[tablebin][inb],
                    other[tablebin][inb],
                    sig1800[tablebin][inb],
                    err[0][tablebin][inb],//*qcd[tablebin][inb],
                    err[1][tablebin][inb],//*ttbar[tablebin][inb],
                    err[2][tablebin][inb],//*wjets[tablebin][inb],
                    err[3][tablebin][inb],//*other[tablebin][inb],
                    databin/mcbin, false /*renormalize to data*/, true);
	}
        cout << "\\hline" << endl;
    }
    cout<< "\\hline" << endl;
    cout << "\\end{tabular}" << endl;
    cout << "}" << endl;
    cout << "\\end{table}\n"<< endl;

    infile->Close();

    return 0;
}

//
void printOneLine(int nb, 
                  float data, float qcd, float ttbar, float wjets, float other, 
                  float sig1500, float sig1600, float sig1700, float sig1800, float sig1900,
                  float data_err, float qcd_err, float ttbar_err, float wjets_err, float other_err, 
                  float sig1500_err, float sig1600_err, float sig1700_err, float sig1800_err, float sig1900_err, float doLatex)
{

    float how_to_deal_with_unused_vars;
    how_to_deal_with_unused_vars=data;
    how_to_deal_with_unused_vars=data_err;
    how_to_deal_with_unused_vars=sig1600;
    how_to_deal_with_unused_vars=sig1600_err;
    how_to_deal_with_unused_vars=sig1700;
    how_to_deal_with_unused_vars=sig1700_err;
    how_to_deal_with_unused_vars=sig1900;
    how_to_deal_with_unused_vars=sig1900_err;
    how_to_deal_with_unused_vars=4;

    float totbkg=qcd+ttbar+wjets+other;

    if(doLatex) 
    {
       cout << Form("%i", nb)   << " & "  
            << Form("$%.2f\\pm%.2f$",qcd,qcd_err)  << " & "
            << Form("$%.2f\\pm%.2f$",ttbar,ttbar_err) << " & " 
            << Form("$%.2f\\pm%.2f$",wjets,wjets_err) << " & " 
            << Form("$%.2f\\pm%.2f$",other,other_err) << " & " 
            //<< Form("$%.0f$",data) << " & " 
            << Form("$%.2f\\pm%.2f$",sig1500,sig1500_err) << " & " 
            << Form("$%.2f\\pm%.2f$",sig1700,sig1700_err) << " & " 
            << Form("$%.2f\\pm%.2f$",sig1900,sig1900_err) << " & " << endl;
    } 
    else 
    { 
       cout << "|" << 
            setw(how_to_deal_with_unused_vars) << nb   << " |"  <<
            setw(16) << Form("%.2f+-%.2f",qcd,qcd_err)  << " |" <<
            setw(16) << Form("%.2f+-%.2f",ttbar,ttbar_err) << " |" <<
            setw(16) << Form("%.2f+-%.2f",wjets,wjets_err) << " |" << 
            setw(16) << Form("%.2f+-%.2f",other,other_err) << " |" << 
            //setw(16) << Form("%.2f+-%.2f",data) << " |" << 
            setw(20) << Form("%.2f+-%.2f(%.2f)",sig1500,sig1500_err,sig1500/totbkg ) << " |" << 
            setw(20) << Form("%.2f+-%.2f(%.2f)",sig1700,sig1700_err,sig1700/totbkg) << " |" << 
            setw(20) << Form("%.2f+-%.2f(%.2f)",sig1900,sig1900_err,sig1900/totbkg) << " |" << endl;
    }
} 
/*
//
void printOneLine(int nb, 
                  float qcd, float ttbar, float wjets, float other, 
                  float sig1500,
                  float qcd_err, float ttbar_err, float wjets_err, float other_err, 
                  float sig1500_err, bool doLatex)
{

    float totbkg=qcd+ttbar+wjets+other;

    if(doLatex) 
    {
       cout << Form("%i", nb)   << " & "  
            << Form("$%.2f\\pm%.2f$",qcd,qcd_err)  << " & "
            << Form("$%.2f\\pm%.2f$",ttbar,ttbar_err) << " & " 
            << Form("$%.2f\\pm%.2f$",wjets,wjets_err) << " & " 
            << Form("$%.2f\\pm%.2f$",other,other_err) << " & " 
            //<< Form("$%.0f$",data) << " & " 
            << Form("$%.2f\\pm%.2f$",sig1500,sig1500_err) << " \\\\" << endl;
    } 
    else 
    { 
       cout << "|" << 
            setw(4) << nb   << " |"  <<
            setw(16) << Form("%.2f+-%.2f",qcd,qcd_err)  << " |" <<
            setw(16) << Form("%.2f+-%.2f",ttbar,ttbar_err) << " |" <<
            setw(16) << Form("%.2f+-%.2f",wjets,wjets_err) << " |" << 
            setw(16) << Form("%.2f+-%.2f",other,other_err) << " |" << 
            //setw(16) << Form("%.2f+-%.2f",data) << " |" << 
            setw(20) << Form("%.2f+-%.2f(%.2f)",sig1500,sig1500_err,sig1500/totbkg) << " |" << endl;
    }
} 
*/
void printYieldBin(int nb, float data, 
        float qcd, float ttbar, float wjets, float other, float sig,
        float qcd_err, float ttbar_err, float wjets_err, float other_err, 
        float dataovermc, bool doNorm, bool printErr)
{
    if(qcd==0) qcd_err=0;
    if(ttbar==0) ttbar_err=0;
    if(wjets==0) wjets_err=0;
    if(other==0) other_err=0;

    string nbbin;
    if(nb==0) nbbin="$500 ~ 800$";
    if(nb==1) nbbin="$800 ~ 1100$";
    if(nb==2) nbbin="$1100 ~$";
   
    if(doNorm)  
    { 
        qcd = qcd * dataovermc;     qcd_err = qcd_err * dataovermc; 
        ttbar = ttbar * dataovermc; ttbar_err = ttbar_err * dataovermc; 
        wjets = wjets * dataovermc; wjets_err = wjets_err * dataovermc; 
        other = other * dataovermc; other_err = other_err * dataovermc; 
    }

    float tot_err = TMath::Sqrt(qcd_err*qcd_err+ttbar_err*ttbar_err+wjets_err*wjets_err+other_err*other_err);
  
    if(printErr) 
    {
    cout << nbbin << " & "
        << Form("$%.1f \\pm %.1f$",qcd,qcd_err)  << " & "
        << Form("$%.1f \\pm %.1f$",ttbar,ttbar_err) << " & "
        << Form("$%.1f \\pm %.1f$",wjets,wjets_err) << " & "
        << Form("$%.1f \\pm %.1f$",other,other_err) << " & "
        << Form("$%.1f \\pm %.1f$",qcd+ttbar+wjets+other,tot_err) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;//FIXME
    }
    else 
    { 
    cout << nbbin << " & "
        << Form("$%.1f$",qcd)  << " & "
        << Form("$%.1f$",ttbar) << " & "
        << Form("$%.1f$",wjets) << " & "
        << Form("$%.1f$",other) << " & "
        << Form("$%.1f$",qcd+ttbar+wjets+other) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
    }

}

float addInQuad(float a, float b)
{
    return TMath::Sqrt(a*a+b*b);
}


