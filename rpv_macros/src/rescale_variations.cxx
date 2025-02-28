// rescales selected nuisance parameters and adds variations corresponding to statistical uncertainties
#include "TString.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1.h"
#include <iostream>
#include "small_tree_rpv.hpp"

//TString msig = "1500";

std::vector<float> morphBins = {1.00, 0.900, 0.800};
using namespace std;

bool isBlinded(const std::string &binName, const std::vector<std::string>& blindBins);

int main(int argc, char* argv[])
{
    TH1::SetDefaultSumw2();
    // Choose the type of cards to produce: mconly, control, and default
    //    For signal injection studies(mconly), only want to use MC as nuisance parameters
    //    are different for data in sideband regions and MC
    std::string cardType=argv[1]; 
  //    std::string cardType="control";

    //TString year = "2016";
    TString rootfile_org = argv[2];
    TString year = argv[3];
    TString msig = argv[4];
    //if(argc==4) msig = argv[4];
    cout << "argc: " << argc << endl;
    cout << "msig: " << msig << endl;
    cout << "year: " << year << endl;
    //./run/rescale_variations.exe [cardType] [inputdir] [year] [mass]
    TString temp = rootfile_org;
    TString rootfile(temp.ReplaceAll(".root","_rescaled.root"));
    if(cardType=="mconly") rootfile = rootfile.ReplaceAll("_rescaled","_mconly");
    else if(cardType=="mconlyold") rootfile = rootfile.ReplaceAll("_rescaled","_mconlyold");
    else if(cardType=="mconlymorph") rootfile = rootfile.ReplaceAll("_rescaled","_mconlymorph");
    else if(cardType=="mconlySplusB") rootfile = rootfile.ReplaceAll("_rescaled","_mconlySplusB");
    else if(cardType=="control") rootfile = rootfile.ReplaceAll("_rescaled","_control");
    TFile *f = TFile::Open(rootfile_org.Data(), "read");
    TFile *g = TFile::Open(rootfile.Data(), "recreate");
/*
    std::string rootfile("variations/sum_rescaled.root");
    if(cardType=="mconly") rootfile = "variations/sum_rescaled_mconly.root";
    else if(cardType=="control") rootfile = "variations/sum_rescaled_control.root";
    TFile *f = TFile::Open(rootfile.c_str(), "update");
*/
    // samples for which MC statistics should be considered
/*    std::vector<std::string> mcStatisticsList = {
      "signal_M1000", "signal_M1100", "signal_M1200", "signal_M1300", "signal_M1400", "signal_M1500", 
      "signal_M1600", "signal_M1700", "signal_M1800", "signal_M1900", "signal_M2000", "signal_M2100", "signal_M2200",
      "qcd", "ttbar", "wjets", "other"};
*/
    std::vector<std::string> mcStatisticsList = {};    
    // only QCD, ttbar, wjets shapes should be rescaled
    // as only these processes have a floating normalization
    // in the fit
    std::vector<std::string> rescaleProcess = {"other","ttbar","qcd","wjets"};
    //std::vector<std::string> rescaleProcess = {"other"};

    // systematics for which the template should be rescaled for qcd, ttbar, and wjets

//    std::vector<std::string> rescaleList = {""};

    //std::vector<std::string> kappaList = {"kappa1","kappa2"};


    std::vector<std::string> rescaleList = {
      "btag_bc","btag_udsg","jec","jer","lep_eff","mur", "muf", "murf", "gs", "pileup"
    };  // */

//    std::vector<std::string> rescaleList = {
//      "btag_bc","btag_udsg","jec","jer","lep_eff", "isr","mur", "muf", "murf", "gs", "pileup"
//    };  // */
    //std::vector<std::string> rescaleList = {""}; 
    // signal list
    std::vector<std::string> signalList = 
    {
      "signal_M1000", "signal_M1100", "signal_M1200", "signal_M1300", "signal_M1400", 
      "signal_M1500", "signal_M1600", "signal_M1700", "signal_M1800", "signal_M1900",
	"signal_M2000", "signal_M2100", "signal_M2200"
    };// */

    //std::vector<std::string> signalList = {""};

    std::vector<std::string> signalRescaleList = {""};

    std::vector<std::string> upAndDown = {"Up", "Down"}; 
  
    // Bins
    std::vector<std::string> binNames_old = {
      "bin0","bin1","bin2","bin3","bin4","bin5","bin6","bin7","bin8","bin9",
      "bin10","bin11","bin12","bin13","bin14","bin15","bin16","bin17","bin18","bin19",
      "bin20","bin21"};
    std::vector<std::string> binNames = { 

      "bin22", "bin23", "bin24",                  // bins for control region fit
      "bin25", "bin26", "bin27",                  // bins for control region fit
      "bin28", "bin29", "bin30",                  // signal bins
      "bin31", "bin32", "bin33",
      "bin34", "bin35", "bin36",                  
      "bin37", "bin38", "bin39",                  // 0 lepton bins
      "bin40", "bin41", "bin42",
      "bin43", "bin44", "bin45",
      "bin46", "bin47", "bin48",
      "bin49", "bin50", "bin51"};                 // signal bins
    std::vector<std::string> blindedBins={};      // bins where data_obs = sum of bkg mc
    if(cardType=="control") blindedBins = { 
      "bin22", "bin23", "bin24",                  // bins for control region fit
      "bin25",                                    // bins for control region fit
      "bin28",                                    // signal bins
      "bin31", 
      "bin37", "bin38", "bin39",                  // 0 lepton bins
      "bin40", 
      "bin43", 
      "bin46", 
      "bin49" }; 
    else if (cardType=="mconlyold"){
	binNames=binNames_old; 
	blindedBins=binNames_old;
    }
    else if (cardType=="mconly") blindedBins=binNames; 
    else if (cardType=="mconlymorph") blindedBins=binNames; 
    else if (cardType=="mconlySplusB") blindedBins=binNames; 
    
    unsigned int nbins=binNames.size();
    
    // Add pdfs to the background (qcd, ttbar, wjets) and signal rescale list
    for(unsigned int i=0; i<100; i++) {
      //rescaleList.push_back("w_pdf"+std::to_string(i));
      //      signalRescaleList.push_back("w_pdf"+std::to_string(i));
    }
    g->cd();
    for(unsigned int ibin=0; ibin<nbins; ibin++) { 
      TString binname(binNames.at(ibin).c_str());
      if(!g->GetDirectory(binname)) g->mkdir(binname);
      g->cd(binname);
        for(unsigned int isyst=0; isyst<rescaleList.size(); isyst++) 
        {
            for(unsigned int idir=0; idir<upAndDown.size(); idir++) 
            {
		//for(unsigned int ikap=0; ikap<kappaList.size(); ikap++)
		//{
                for(unsigned int iproc=0; iproc<rescaleProcess.size(); iproc++) 
                {
                    std::string process = rescaleProcess.at(iproc).c_str();

                    //if(rescaleList.at(isyst).find("ttbar")!=std::string::npos) process="ttbar";

                    TString histnameNominal(Form("%s/%s", binNames.at(ibin).c_str(), process.c_str()));
                    std::cout << "Getting histogram " << histnameNominal << std::endl;
		    //TString histnameKappa(Form("%s/%s_%s_%s_%s_%s%s", binNames.at(ibin).c_str(), process.c_str(),kappaList.at(ikap).c_str(),year.Data() ,upAndDown.at(idir).c_str()));
                    //std::cout << "Getting histogram " << histnameKappa << std::endl;
		    //TString histnameRescale(Form("%s/%s_%s_%s%s", binNames.at(ibin).c_str(), process.c_str(), rescaleList.at(isyst).c_str(), year.Data() ,upAndDown.at(idir).c_str()));
		    TString histnameRescale(Form("%s/%s", binNames.at(ibin).c_str(), process.c_str()));
                    std::cout << "Getting histogram " << histnameRescale << std::endl;
                    TH1F *nominal = static_cast<TH1F*>(f->Get(histnameNominal));
                    //TH1F *kappa = static_cast<TH1F*>(f->Get(histnameKappa));
                    TH1F *rescale = static_cast<TH1F*>(f->Get(histnameRescale));
                    if(rescale->Integral()!=0) {
                        rescale->Scale(nominal->Integral()/rescale->Integral());
                    }// */

                    rescale->Write("",TObject::kOverwrite);
                    nominal->Write("",TObject::kOverwrite);
                   // rescale->Write();
                }
		//}
            }
        }
        // rescale signal systematics
        for(auto isignal : signalList) {
            for(unsigned int isyst=0; isyst<signalRescaleList.size(); isyst++) {
                for(unsigned int idir=0; idir<upAndDown.size(); idir++) {
                    TString histnameNominal(Form("%s/%s", binNames.at(ibin).c_str(), isignal.c_str()));
                    std::cout << "Getting histogram " << histnameNominal << std::endl;
                    //TString histnameRescale(Form("%s/%s_%s_%s%s", binNames.at(ibin).c_str(), isignal.c_str(), signalRescaleList.at(isyst).c_str(), year.Data(), upAndDown.at(idir).c_str()));
		    TString histnameRescale = Form("%s/%s", binNames.at(ibin).c_str(), isignal.c_str());
                    std::cout << "Getting signal histogram " << histnameRescale << std::endl;
                    TH1F *nominal = static_cast<TH1F*>(f->Get(histnameNominal));
                    TH1F *rescale = static_cast<TH1F*>(f->Get(histnameRescale));
                    if(rescale->Integral()!=0) {
                        rescale->Scale(nominal->Integral()/rescale->Integral());
                    }// */

                    rescale->Write("",TObject::kOverwrite);
                    nominal->Write("",TObject::kOverwrite);
                    //rescale->Write();
                }
            }
        } // end rescaling of signal systematics

        // add histograms for MC statistics so that Barlow-Beeston method can be implemented
        // ignore variations for samples with very small contributions
        // to avoid profusion of useless nuisance parameters
        for(auto isample : mcStatisticsList) {
            TString histnameNominal(Form("%s/%s", binNames.at(ibin).c_str(), isample.c_str()));
            TH1F *nominal = static_cast<TH1F*>(f->Get(histnameNominal));
            for(unsigned int ib=1; ib<=nbins; ib++) {
                TH1F *up = static_cast<TH1F*>(nominal->Clone());
                TH1F *down = static_cast<TH1F*>(nominal->Clone());
                up->SetBinContent(ib, nominal->GetBinContent(ib)+nominal->GetBinError(ib));
                float downvalue = nominal->GetBinContent(ib)-nominal->GetBinError(ib);
                if(downvalue<0) downvalue=0.0;
                down->SetBinContent(ib, downvalue);

                TString basename(nominal->GetName());
                TString upname(Form("%s_mcstat_%s_%s_nb%dUp", nominal->GetName(), isample.c_str(), binname.Data(), ib-1));
                TString downname(Form("%s_mcstat_%s_%s_nb%dDown", nominal->GetName(), isample.c_str(), binname.Data(), ib-1));
                up->SetName(upname);
                down->SetName(downname);

		up->Scale(nominal->Integral()/up->Integral());
		down->Scale(nominal->Integral()/down->Integral());

                //up->Write();
                //down->Write();
            }
        }

        if(isBlinded(binNames.at(ibin), blindedBins)) {
            // add fake data_obs histogram for blinded bins
            std::cout << "Getting histogram " << Form("%s/data_obs", binNames.at(ibin).c_str()) << std::endl;
            TH1F *data_obs = static_cast<TH1F*>(f->Get(Form("%s/data_obs", binNames.at(ibin).c_str())));
            TH1F *qcd = static_cast<TH1F*>(f->Get(Form("%s/qcd", binNames.at(ibin).c_str())));
            TH1F *ttbar = static_cast<TH1F*>(f->Get(Form("%s/ttbar", binNames.at(ibin).c_str())));
            TH1F *wjets = static_cast<TH1F*>(f->Get(Form("%s/wjets", binNames.at(ibin).c_str())));
            TH1F *other = static_cast<TH1F*>(f->Get(Form("%s/other", binNames.at(ibin).c_str())));
            TH1F *signal = new TH1F("signal","signal",3,500,1400);
            signal->Print("all");
            int binnumber = atoi(binname.ReplaceAll("bin","").Data());
            if(cardType=="mconlySplusB"&&binnumber>21){
              signal = static_cast<TH1F*>(f->Get(Form("%s/signal_M%s", binNames.at(ibin).c_str(), msig.Data())));
              std::cout<<binNames.at(ibin).c_str()<<std::endl;
              std::cout<<Form("%s/signal_M%s", binNames.at(ibin).c_str(), msig.Data())<<std::endl;
            }
            
            for(int i=1; i<=data_obs->GetNbinsX(); i++) {
                if(cardType=="mconlymorph"){
                   data_obs->SetBinContent(i, (qcd->GetBinContent(i)
                            + ttbar->GetBinContent(i)
                            + wjets->GetBinContent(i)
                            + other->GetBinContent(i))*morphBins.at(i-1));
                }
                else if(cardType=="mconlySplusB"&&binnumber>21){
            std::cout<<signal->GetBinContent(i)<<std::endl;
                   data_obs->SetBinContent(i, (qcd->GetBinContent(i)
                            + ttbar->GetBinContent(i)
                            + wjets->GetBinContent(i)
                            + other->GetBinContent(i)
                            + signal->GetBinContent(i)));
                }
                else data_obs->SetBinContent(i, (qcd->GetBinContent(i)
                            + ttbar->GetBinContent(i)
                            + wjets->GetBinContent(i)
                            + other->GetBinContent(i)));
		            data_obs->SetBinError(i, TMath::Sqrt(data_obs->GetBinContent(i)));
//		            data_obs->SetBinError(i, TMath::Sqrt(qcd->GetBinError(i)*qcd->GetBinError(i) + ttbar->GetBinError(i)*ttbar->GetBinError(i) + wjets->GetBinError(i)*wjets->GetBinError(i) + other->GetBinError(i)*other->GetBinError(i))); // 231006 for comparison of MJ distribution between 2016_pre and 2016_post
            }
            data_obs->Write("",TObject::kOverwrite);
            //data_obs->Write();
        }

        // go back to the top left directory to start processing next bin
        g->cd("/");
    }

    g->Write();
    g->Close();
    f->Close();

    return 0;
}

bool isBlinded(const std::string &binName, const std::vector<std::string>& blindBins)
{
    for(auto iblind : blindBins) {
        if(binName == iblind) return true;
    }

    return false;
}
