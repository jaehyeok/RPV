#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooFit.h"
#include "RooSimultaneous.h"
#include "RooWorkspace.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooPlot.h"

#include "TROOT.h"
#include "TLegend.h"
#include "TBox.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TPad.h"
#include "TLatex.h"
#include "THStack.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TMath.h"

#include "tdrstyle.C"

using namespace RooFit;


float AddInQuad(float a, float b);
void setValues(RooWorkspace *work, RooFitResult *result);
void plotFitPulls(const RooArgList &pulls, const TString & pullString, const std::string & type, const TString year);
void printYieldBin(int bin, int nb, float data, float qcd, float ttbar, float wjets, float other, float sig);
void printYieldBin(int bin, int nb, float data, 
                   float qcd, float ttbar, float wjets, float other, float sig, 
                   float qcd_err, float ttbar_err, float wjets_err, float other_err);
//void printYieldBin(int bin, int nb, float data, 
//                   float qcd, float ttbar, float wjets, float other, float sig, 
//                   float qcd_err, float ttbar_err, float wjets_err, float other_err, float allbkg_err);
void printYieldBin(int mjbin, float data,
		   float qcd, float ttbar, float wjets, float other, float sig,
		   float qcd_err, float ttbar_err, float wjets_err, float other_err,
		   float allbkg_err, bool printErr); 
//
// h1 cosmetics
//
void h1cosmetic(TH1D* &h1, char* title, int linewidth=1, TString process="ttbar", TString var="")
{
    TString hex_color;
    /*
    // 1
    if(process=="qcd")         hex_color="#ffa90e";
    else if(process=="ttbar")  hex_color="#3f90da";
    else if(process=="wjets")  hex_color="#b9ac70";
    else if(process=="other")  hex_color="#717581";
    else if(process=="dy")     hex_color="#832db6";
    else if(process=="signal") hex_color="#bd1f01";
    */

    /*
    // 2
    if(process=="qcd")         hex_color="#ffa90e";
    else if(process=="ttbar")  hex_color="#3f90da";
    else if(process=="wjets")  hex_color="#e76300";
    else if(process=="other")  hex_color="#717581";
    else if(process=="dy")     hex_color="#832db6";
    else if(process=="signal") hex_color="#bd1f01";
    */

    // 3
    /*
    if(process=="qcd")         hex_color="#ffa90e";
    else if(process=="ttbar")  hex_color="#3f90da";
    else if(process=="wjets")  hex_color="#a96b59";
    else if(process=="other")  hex_color="#717581";
    else if(process=="dy")     hex_color="#832db6";
    else if(process=="signal") hex_color="#bd1f01";
    */

    // 4
    if(process=="qcd")         hex_color="#ffa90e";
    else if(process=="ttbar")  hex_color="#3f90da";
    else if(process=="wjets")  hex_color="#832db6";
    else if(process=="other")  hex_color="#94a4a2";
    else if(process=="dy")     hex_color="#e76300";
    else if(process=="signal") hex_color="#bd1f01";

    // 5 color
    /*
    if(process=="qcd")         hex_color="#f89c20";
    else if(process=="ttbar")  hex_color="#5790fc";
    else if(process=="wjets")  hex_color="#7a21dd";
    else if(process=="other")  hex_color="#9c9ca1";
    else if(process=="dy")     hex_color="#964a8b";
    else if(process=="signal") hex_color="#e42536";
    */
    
    int hist_color = TColor::GetColor(hex_color);
    h1->SetLineColor(kBlack);
    h1->SetLineWidth(linewidth);
    h1->SetFillColor(hist_color);
    if(process=="signal") {
      h1->SetLineColor(hist_color);
      h1->SetFillColor(0);
    }
    h1->SetTitle(title);
    h1->SetXTitle(var);
    h1->SetStats(0);
    h1->SetMinimum(0.001);
    h1->SetMarkerColor(kBlack);
    h1->SetMarkerSize(0.6);
    h1->SetMarkerStyle(20);
}


// Convert TGraphAsymmErrors to TH1D
//
TH1D* changeHistogram(TH1D* h){

    TString name = h->GetName(); 
    TH1D* hist = new TH1D(Form("h_%s", h->GetName()), Form("%s",h->GetName()), 3, 500, 1400);
    hist->SetDirectory(0);
        
    hist->SetBinContent(1,h->GetBinContent(1));
    hist->SetBinContent(2,h->GetBinContent(2));
    hist->SetBinContent(3,h->GetBinContent(3));

    hist->SetStats(0); 
    cout << "1 :: " << hist->GetBinContent(1) << endl; 
    cout << "2 :: " << hist->GetBinContent(2) << endl; 
    cout << "3 :: " << hist->GetBinContent(3) << endl; 

    hist->GetXaxis()->SetBinLabel(1,"1");
    hist->GetXaxis()->SetBinLabel(2,"2");
    hist->GetXaxis()->SetBinLabel(3,"3");
    //hist->GetXaxis()->SetBinLabel(4,"#geq 4");
    return hist;
}

void plotresult(TString step="step1", TString year="UL2016",int gluinoMass=1800)
{
  float lumi = 36.3;
  if(year=="UL2016") lumi = 36.3;
  if(year=="UL2017") lumi = 41.5;
  if(year=="UL2017_20178") lumi = 41.5;
  if(year=="UL2018") lumi = 59.8;
  if(year=="UL2018_20178") lumi = 59.8;
  if(year=="UL20178") lumi = 101;
  if(year=="UL20168") lumi = 138;
  if(year=="fullrun2") lumi =138;
  //bool doPrefit=true;
  bool doPrefit=false;
  bool plotSPlusB=false;
  bool doControl=true;

  setTDRStyle();
  gROOT->ForceStyle();
  
  std::vector<std::string> binname;
  std::vector<int> binnumber;
  if(doControl) 
  {
    if(step=="step1"){  
      binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0", //    "nlep1_nj8_nb0",
     	         "nlep1_nj45_nb1",   "nlep1_nj67_nb1", //    "nlep1_nj8_nb1", 
   	         "nlep1_nj45_nb2",   "nlep1_nj67_nb2"}; //    "nlep1_nj8_nb2"};
      binnumber = {22,23,25,26,28,29};
    }
    else if(step=="step2"){
      binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0",     "nlep1_nj8_nb0",
   	         "nlep1_nj45_nb1",   "nlep1_nj67_nb1",     "nlep1_nj8_nb1", 
   	         "nlep1_nj45_nb2",   "nlep1_nj67_nb2"};
      binnumber = {22,23,24,25,26,27,28,29};
    }
    else if(step=="step3"){
      binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0",     "nlep1_nj8_nb0",
   	         "nlep1_nj45_nb1",   "nlep1_nj67_nb1",     "nlep1_nj8_nb1", 
   	         "nlep1_nj45_nb2",   "nlep1_nj67_nb2",
		 "nlep1_nj45_nb3"};
      binnumber = {22,23,24,25,26,27,28,29,31};
    }
    else if(step=="unblind"){
      binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0",     "nlep1_nj8_nb0",
   	         "nlep1_nj45_nb1",   "nlep1_nj67_nb1",     "nlep1_nj8_nb1", 
   	         "nlep1_nj45_nb2",   "nlep1_nj67_nb2",     "nlep1_nj8_nb2",
		 "nlep1_nj45_nb3",   "nlep1_nj67_nb3",     "nlep1_nj8_nb3",
				     "nlep1_nj67_nb4",     "nlep1_nj8_nb4"};
      binnumber = {22,23,24,25,26,27,28,29,30,31,32,33,35,36};
    }
    else if(step=="ttbar"){  
      binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0",     "nlep1_nj8_nb0",
     	         "nlep1_nj45_nb1",   "nlep1_nj67_nb1",     "nlep1_nj8_nb1", };
      binnumber = {22,23,24,25,26,27};
    }
   //			   "nlep1_nj45_nb3",  "nlep1_nj67_nb3",    "nlep1_nj8_nb3", 
  // 			   "nlep1_nj45_nb4",  "nlep1_nj67_nb4",    "nlep1_nj8_nb4"}; 
    //binnumber = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
   // binname = {"nlep1_nj45_lowmj", "nlep1_nj45_highmj", "nlep1_nj67_lowmj"}; 
   // binnumber = {2,5,11};
  } 
  else
  {
    binname = {"nlep0_nj45_lowmj", "nlep0_nj67_lowmj", "nlep1_nj45_lowmj",
  			  "nlep0_nj45_highmj", "nlep0_nj67_highmj", "nlep1_nj45_highmj",
  			  "nlep0_nj10_lowmj", "nlep1_nj67_lowmj", "nlep1_nj8_lowmj", "nlep0_nj10_highmj",
  			  "nlep1_nj67_highmj", "nlep1_nj8_highmj", "nlep0_nj89_lowmj", "nlep0_nj89_highmj"};
    binnumber = {0,1,2,
                 3,4,5,
                 10,11,12,13,
                 14,15,16,17};

  } 
// FIXME : this is for debug
//    binname = {"nlep1_nj45_lowmj"}; 
//    binnumber = {2};
  
  // for yield table  
  float data[31][3], qcd[31][3], ttbar[31][3], wjets[31][3], other[31][3], sig1200[31][3], sig1800[31][3]; 
  float err[5][31][4]; // first index : qcd, ttbar, wjets, other, all bkg
  
  for(int ibin=22; ibin<31; ibin++)
  {
      for(int inb=0; inb<3; inb++)
      {
          data[ibin][inb] = 0;
          qcd[ibin][inb] = 0;
          ttbar[ibin][inb] = 0;
          wjets[ibin][inb] = 0;
          other[ibin][inb] = 0;
          sig1200[ibin][inb] = 0;
          sig1800[ibin][inb] = 0;
          err[0][ibin][inb] = 0;
          err[1][ibin][inb] = 0;
          err[2][ibin][inb] = 0;
          err[3][ibin][inb] = 0;
          err[4][ibin][inb] = 0;
        // */
      }
  }
  
  // Get prefit signal  
  TH1D* h1_prefit_sig_m1200[31]; 
  TH1D* h1_prefit_sig_m1800[31]; 
  TH1D* h1_prefit_data[31]; 
  //TFile* infile  = TFile::Open("variations/output_tdatcard10_M1700.root", "READ");
//  TFile* infile  = TFile::Open(Form("output_tdatcard11_%s.root", year.Data()), "READ");
//  TFile* infile = TFile::Open(Form("output_CRFit_20178.root"),"read");
//
  TFile* infile  = TFile::Open(Form("variations/output_impact_%s.root", year.Data()), "READ");
//  TFile* infile  = TFile::Open(Form("variations/output_rescaled_impact_%s.root", year.Data()), "READ");
  for(unsigned int i=22; i<22+binname.size(); i++) {   
    int ibin = binnumber.at(i-22);
    if(ibin>=6 && ibin<=9) continue;
    h1_prefit_sig_m1200[i] = new TH1D(Form("h1_prefit_sig_m1200_bin%i",ibin), 
                                   Form("h1_prefit_sig_m1200_bin%i",ibin), 
                                   3, 500, 1400); 
    h1_prefit_sig_m1800[i] = new TH1D(Form("h1_prefit_sig_m1800_bin%i",ibin), 
                                   Form("h1_prefit_sig_m1800_bin%i",ibin), 
                                   3, 500, 1400); 
    h1_prefit_data[i] = new TH1D(Form("h1_prefit_data_bin%i",ibin), 
                                   Form("h1_prefit_data_bin%i",ibin), 
                                   3, 500, 1400); 
    //
    for(unsigned int inb=1; inb<4; inb++)
    {
        sig1200[i][inb-1]= (static_cast<TH1D*>(infile->Get(Form("bin%i/signal_M1200", ibin))))->GetBinContent(inb);  
	// mglu 1200 xsec X 0.1
        h1_prefit_sig_m1200[i]->SetBinContent(inb, sig1200[i][inb-1]*0.01);
        sig1800[i][inb-1]= (static_cast<TH1D*>(infile->Get(Form("bin%i/signal_M%i", ibin, gluinoMass))))->GetBinContent(inb);  
        h1_prefit_sig_m1800[i]->SetBinContent(inb, sig1800[i][inb-1]);
        data[i][inb-1]= (static_cast<TH1D*>(infile->Get(Form("bin%i/data_obs", ibin))))->GetBinContent(inb);  
        h1_prefit_data[i]->SetBinContent(inb, data[i][inb-1]);
    }  
  } 
  //infile->Close();
  /**/

  cout << "Pre or postfit Uncertatinty " << endl;
  // Get post-fit uncertainty 
  TFile* errfile;
  if(!(step=="ttbar"))
  {
    errfile = TFile::Open(Form("rpv_postfit_err_%s_%s.root",step.Data(),year.Data()),"READ");
    for(int i=22; i<22+binname.size(); i++) {   
        int ibin = binnumber.at(i-22);
        
        if(ibin>=6 && ibin<=9) continue;
  
        for(int iproc=0; iproc<5; iproc++)
        {
            std::string process;
            if(iproc==0)  process = "qcd";
            if(iproc==1)  process = "ttbar";
            if(iproc==2)  process = "wjets";
            if(iproc==3)  process = "other";
            if(iproc==4)  process = "allbkg";
  
            // loop over nb bins
            for(int inb=1; inb<4; inb++)
            { 
              err[iproc][ibin][inb-1] = ((TH1F*)errfile->Get(Form("h_bin%i_%s",  ibin, process.c_str())))->GetBinContent(inb); 
              cout << iproc << " ::: " << ibin << " " << inb << " :: " << err[iproc][ibin][inb-1] << endl;
            }
        }
    }
  }
// */  

// FIXME: these lines can be removed
/* 
  std::string workspaceFilename;
  std::string resultsFilename;
  if(doControl) 
  { 
    workspaceFilename=Form("workspace_M%d_control_nopdf.root", gluinoMass);
    resultsFilename=Form("mlfitM%d_control.root", gluinoMass);
  }
  else 
  { 
    workspaceFilename=Form("workspace_M%d.root", gluinoMass);
    resultsFilename=Form("mlfitM%d.root", gluinoMass); 
  }

  TFile *f = TFile::Open(workspaceFilename.c_str());
  TFile *fResults = TFile::Open(resultsFilename.c_str());

  RooWorkspace *work = static_cast<RooWorkspace*>(f->Get("w"));
  RooFitResult *result_b = static_cast<RooFitResult*>(fResults->Get("fit_b"));
  RooFitResult *result_s = static_cast<RooFitResult*>(fResults->Get("fit_s"));

  RooSimultaneous * model_b = static_cast<RooSimultaneous*>(work->pdf("model_b"));
  RooSimultaneous * model_s = static_cast<RooSimultaneous*>(work->pdf("model_s"));

  RooDataHist *histData = static_cast<RooDataHist*>(work->data("data_obs"));
  // get RooFitResults
  setValues(work, result_b);
  if(plotSPlusB) setValues(work, result_s);

  std::cout << "Setting category" << std::endl;
  RooCategory *cat = work->cat("CMS_channel");
  //cat->Print();
*/
  TString crvr = "";
  if(step=="step1") crvr="cr";
  if(step=="step2") crvr="vr";
  if(step=="step3") crvr="vr2";
  if(step=="unblind") crvr="unblind";
  if(step=="ttbar") crvr="cr_CRFit";
  std::string resultsFilename=Form("mlfit_%s_%s.root",crvr.Data(),year.Data());
//  std::string resultsFilename=Form("mlfit_%s.root",year.Data());
  TFile *fResults = TFile::Open(resultsFilename.c_str());
  RooFitResult *result_b = static_cast<RooFitResult*>(fResults->Get("fit_b"));
  RooFitResult *result_s = static_cast<RooFitResult*>(fResults->Get("fit_s"));

  for(unsigned int i=22; i<22+binname.size(); i++) { 
   
    TCanvas *c;
    TPad *pad_stack;
    TPad *pad_ratio;
    
    int ibin = binnumber.at(i-22);
    cout << "...... BIN: " << ibin << " :: " << binname[i-22]<< endl;
    cout<<i<<endl;
    std::cout << "Drawing frame" << std::endl;
    c = new TCanvas("c","c",300,300);
    c->cd();
    pad_stack = new TPad(Form("p_main_%i",i), Form("p_main_%i",i), 0.0, 0.28, 1.0, 1.0);
    pad_stack->SetTopMargin(0.1);
    pad_stack->SetBottomMargin(0.04);
    pad_stack->SetRightMargin(0.1);
    pad_stack->SetLeftMargin(0.2);
    pad_stack->Draw();
    pad_stack->cd();
    pad_stack->cd()->SetLogy(1);
    
    TH1D *h1_data = h1_prefit_data[i];     
    TH1D *h1_qcd;     
    TH1D *h1_ttbar;   
    TH1D *h1_wjets;   
    TH1D *h1_other;   
    TH1D *h1_signal_m1200; 
    TH1D *h1_signal_m1800; 
    TH1D *h1_sf;
    double err_num=0, err_den=0;
    float num=0, den=0;
    float sf=0, sf_unc=0;
    if(doPrefit)  
    {
        h1_qcd =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/qcd", ibin)))));
        h1_ttbar =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/ttbar", ibin)))));
        h1_wjets =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/wjets", ibin)))));
        h1_other =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/other", ibin))))); 

	h1_sf = (TH1D*)h1_qcd->Clone("h1_sf1");
	h1_sf->Add(h1_ttbar);
	h1_sf->Add(h1_wjets);
	h1_sf->Add(h1_other);
	num = h1_data->IntegralAndError(1,h1_data->GetNbinsX(),err_den);
	den = h1_sf->IntegralAndError(1,h1_sf->GetNbinsX(),err_num);
	sf = num/den;
	sf_unc = (num/den)*sqrt(pow(err_num/num,2)+pow(err_den/den,2));

        h1_qcd->Scale(sf);
        h1_ttbar->Scale(sf);
        h1_wjets->Scale(sf);
        h1_other->Scale(sf);
        if(plotSPlusB) {
	  h1_signal_m1200 =  h1_prefit_sig_m1200[i]; 
	  h1_signal_m1800 =  h1_prefit_sig_m1800[i]; 
	}

    }
    /*
    else if(plotSPlusB)
    {
        h1_qcd =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_s/bin%i/qcd", ibin)));
        h1_ttbar =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_s/bin%i/ttbar", ibin)));
        h1_wjets =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_s/bin%i/wjets", ibin)));
        h1_other =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_s/bin%i/other", ibin)));
        if(plotSPlusB) h1_signal =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_s/bin%i/signal_M1800", ibin)));
    }
    */
    else 
    {
        h1_qcd =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/qcd", ibin)));
        h1_ttbar =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/ttbar", ibin)));
        h1_wjets =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/wjets", ibin)));
        h1_other =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/other", ibin)));
        if(plotSPlusB) {
	  h1_signal_m1200 =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/signal_M1200", ibin)));
	  h1_signal_m1800 =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/signal_M1800", ibin)));
	}
    }

    //fill yields 
    for(unsigned int inb=1; inb<4; inb++)
    {
        data[ibin][inb-1]  = h1_data->GetBinContent(inb);
        qcd[ibin][inb-1]   = h1_qcd->GetBinContent(inb);
        ttbar[ibin][inb-1] = h1_ttbar->GetBinContent(inb);
        wjets[ibin][inb-1] = h1_wjets->GetBinContent(inb);
        other[ibin][inb-1] = h1_other->GetBinContent(inb); 
    }

    // cosmetics
    h1cosmetic(h1_data,          Form("Data bin%i", ibin),                2, 1,           "M_{J}");
    h1cosmetic(h1_qcd,           Form("QCD bin%i", ibin),                 2, "qcd",     "M_{J}");
    h1cosmetic(h1_ttbar,         Form("ttbar bin%i", ibin),               2, "ttbar",        "M_{J}");
    h1cosmetic(h1_wjets,         Form("Wjets bin%i", ibin),               2, "wjets",        "M_{J}");
    h1cosmetic(h1_other,         Form("other bin%i", ibin),               2, "other",     "M_{J}");
    if(plotSPlusB) {
      h1cosmetic(h1_signal_m1200,    Form("signal bin%i m1200", ibin),                    3, "signal",           "M_{J}");
      h1cosmetic(h1_signal_m1800,    Form("signal bin%i m1800", ibin),                    3, "signal",           "M_{J}");
    }
    h1cosmetic(h1_prefit_sig_m1200[i],        Form("prefit signal 1200 bin%i", ibin),        3, "signal",           "M_{J}");
    h1cosmetic(h1_prefit_sig_m1800[i],        Form("prefit signal 1800 bin%i", ibin),        3, "signal",           "M_{J}");
    h1_prefit_sig_m1200[i]->SetLineStyle(2); 
    h1_prefit_sig_m1800[i]->SetLineStyle(1); 

    // uncertainty band 
    TH1D *h1_mc = (TH1D*)h1_qcd->Clone("h1_qcd");
    h1_mc->Add(h1_ttbar);
    h1_mc->Add(h1_wjets);
    h1_mc->Add(h1_other);
    //if(plotSPlusB) h1_mc->Add(h1_signal);
    if(!(step=="ttbar")) {
      for(unsigned int inb=1; inb<4; inb++){
        cout<< err[4][ibin][inb-1] << endl;
        h1_mc->SetBinError(inb,err[4][ibin][inb-1]*h1_mc->GetBinContent(inb));
      }
    }
    h1_mc->SetMarkerSize(0);
    h1_mc->SetFillColor(kBlack);
    h1_mc->SetLineColor(kBlack);
    h1_mc->SetFillStyle(3354);

    // stack
    THStack *st = new THStack(Form("Bin %i", ibin), Form("Bin %i", ibin));
    st->Add(h1_other); 
    st->Add(h1_wjets); 
    st->Add(h1_ttbar); 
    st->Add(h1_qcd);  // can change order of ttbat and qcd in 1-lepton bins  
    //if(plotSPlusB) st->Add(h1_signal); 

    st->SetMaximum(h1_data->GetMaximum()*2000);
    st->SetMinimum(0.1);
    st->Draw("hist");
    h1_mc->Draw("same E2");
    h1_data->Draw("e same"); 
    //if(plotSPlusB) h1_signal->Draw("hist same"); 
    st->GetYaxis()->SetTitle("Events / (300 GeV)");
    st->GetYaxis()->SetTitleOffset(1.1);
    st->GetYaxis()->SetTitleSize(0.075);
    st->GetYaxis()->SetLabelSize(0.07);
    st->GetXaxis()->SetLabelSize(0.0);
    st->GetXaxis()->SetTitle("M_{J} [GeV]");
    
//    if(!doPrefit) h1_prefit_sig1800[i]->Draw("hist same"); 
    h1_prefit_sig_m1200[i]->Draw("hist same"); 
    h1_prefit_sig_m1800[i]->Draw("hist same"); 
    
    // legend
    TLegend *leg = new TLegend(0.55, 0.48, 0.85, 0.87);
    leg->SetNColumns(1);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(42);
    leg->SetTextAlign(12);
    leg->SetTextSize(0.045);
    leg->SetFillColor(kWhite);
    leg->SetLineColor(kWhite);
    leg->SetShadowColor(kWhite);
    leg->AddEntry(h1_data,  "Data",     "ELP");
    leg->AddEntry(h1_qcd,   "QCD",      "F");
    leg->AddEntry(h1_ttbar, "t#bar{t}", "F");
    leg->AddEntry(h1_wjets, "W+jets",   "F");
    leg->AddEntry(h1_other, "Other",    "F");
    if(!doControl) 
    {
        //leg->AddEntry(h1_signal, Form("m_{#tilde{g}}=%i GeV",gluinoMass), "F");
        //leg->AddEntry(h1_prefit_sig1200[i], Form("Expected m_{#tilde{g}}=%i GeV",gluinoMass), "L");
        leg->AddEntry(h1_prefit_sig_m1200[i], Form("Expected m_{#tilde{g}}=%i GeV",1200), "L");
        leg->AddEntry(h1_prefit_sig_m1800[i], Form("Expected m_{#tilde{g}}=%i GeV",gluinoMass) , "L");
    }
    leg->AddEntry(h1_prefit_sig_m1200[i], Form("m_{#tilde{g}}=%i GeV#times0.01",1200) , "L");
    leg->AddEntry(h1_prefit_sig_m1800[i], Form("m_{#tilde{g}}=%i GeV",gluinoMass) , "L");
    if(!doPrefit) leg->AddEntry(h1_mc, "Post-fit uncertainty",    "F");
    leg->Draw();

    // CMS and lumi labels
    float textSize = 0.06;
    float lumi = 36.3;
    if(year=="UL2016") lumi = 36.3;
    if(year=="UL2017") lumi = 41.5;
    if(year=="UL2017_20178") lumi = 41.5;
    if(year=="vr_2017_20178") lumi = 41.5;
    if(year=="cr_2017_20178") lumi = 41.5;
    if(year=="UL2018") lumi = 59.8;
    if(year=="UL2018_20178") lumi = 59.8;
    if(year=="vr_2018_20178") lumi = 59.8;
    if(year=="cr_2018_20178") lumi = 59.8;
    if(year=="UL20178") lumi = 101;
    if(year=="UL201678") lumi = 138;
    TLatex *TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%.1f fb^{-1} (13 TeV)}", lumi));
    if(year=="UL20178" || year=="UL201678") TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%d fb^{-1} (13 TeV)}", int(lumi)));
    TexEnergyLumi->SetNDC();
    TexEnergyLumi->SetTextSize(textSize);
    TexEnergyLumi->SetTextAlign (31);
    TexEnergyLumi->SetLineWidth(2);

    //TLatex *TexCMS = new TLatex(0.2,0.92,"CMS #font[52]{Work In Progress}");
    TLatex *TexCMS = new TLatex(0.2,0.92,"CMS #font[52]{Preliminary}");
    TexCMS->SetNDC();
    TexCMS->SetTextSize(textSize);
    TexCMS->SetLineWidth(2);
    TexEnergyLumi->Draw("same");
    TexCMS->Draw("same");
   
    // display cuts
    //
    //textSize=textSize-0.01;
    TLatex *TexNlep, *TexNjets, *TexNb;
    TString binname_tstr = binname[i-22]; 
    if(binname_tstr.Contains("nlep1"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 1");
    if(binname_tstr.Contains("nlep0"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 0");
    TexNlep->SetNDC();
    TexNlep->SetTextSize(textSize);
    //TexNlep->SetLineWidth(2);
    if(binname_tstr.Contains("nj45_"))   TexNjets = new TLatex(0.25,0.72,"4 #leq N_{jet} #leq 5");
    if(binname_tstr.Contains("nj67_"))   TexNjets = new TLatex(0.25,0.72,"6 #leq N_{jet} #leq 7");
    if(binname_tstr.Contains("nj89_"))   TexNjets = new TLatex(0.25,0.72,"8 #leq N_{jet} #leq 9");
    if(binname_tstr.Contains("nj8_"))    TexNjets = new TLatex(0.25,0.72,"N_{jet} #geq 8");
    if(binname_tstr.Contains("nj10_"))   TexNjets = new TLatex(0.25,0.72,"N_{jet} #geq 10");
    TexNjets->SetNDC();
    TexNjets->SetTextSize(textSize);
    //TexNjets->SetLineWidth(2);
    if(binname_tstr.Contains("nb0"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 0");
    if(binname_tstr.Contains("nb1"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 1");
    if(binname_tstr.Contains("nb2"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 2");
    if(binname_tstr.Contains("nb3"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 3");
    if(binname_tstr.Contains("nb4"))     TexNb = new TLatex(0.25,0.64,"N_{b} #geq 4");
    if(binname_tstr=="nlep1_nj45_nb3")   TexNb = new TLatex(0.25,0.64,"N_{b} #geq 3");
    TexNb->SetNDC();
    TexNb->SetTextSize(textSize);
    //TexMJ->SetLineWidth(2);

    TexNlep->SetTextFont(42);
    TexNjets->SetTextFont(42);
    TexNb->SetTextFont(42);
    TexNlep->Draw("same");
    TexNjets->Draw("same");
    TexNb->Draw("same");
    /*
    if(doPrefit) {
      TLatex *TexSF;
      TexSF = new TLatex(0.70,0.49,Form("(%.1f#pm%.1f)%%", sf*100, sf_unc*100));
      TexSF->SetNDC();
      TexSF->SetTextSize(textSize);
      TexSF->SetTextFont(42);
//      TexSF->SetTextAlign();
      TexSF->Draw("same");
    }
    */
    
    c->cd();
    pad_ratio = new TPad(Form("p_pull_%i",i), Form("p_pull_%i",i), 0.0, 0.0, 1.0, 0.305);
    pad_ratio->SetLeftMargin(0.2);
    pad_ratio->Draw();
    pad_ratio->cd();
    pad_ratio->SetTopMargin(0.04);
    pad_ratio->SetRightMargin(0.1);
    pad_ratio->SetBottomMargin(0.4);
   
    TLatex* tex_mj500  = new TLatex(0.17, 0.25,  "500");
    TLatex* tex_mj800  = new TLatex(0.40, 0.25,  "800");
    TLatex* tex_mj1100 = new TLatex(0.62, 0.25, "1100");
    TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
    //TLatex* tex_mj500  = new TLatex(0.12, 0.25,  "500");
    //TLatex* tex_mj800  = new TLatex(0.37, 0.25,  "800");
    //TLatex* tex_mj1100 = new TLatex(0.61, 0.25, "1100");
    //TLatex* tex_mj1400 = new TLatex(0.85, 0.25, "1400");
    tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
    tex_mj500->SetTextSize(0.16); tex_mj800->SetTextSize(0.16); tex_mj1100->SetTextSize(0.16); tex_mj1400->SetTextSize(0.16);
    tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

    TH1D *h1_ratio = (TH1D*)h1_data->Clone("h1_ratio"); 
    TH1D *h1_ratio_err = (TH1D*)h1_ratio->Clone("h1_ratio_err");  
    h1_ratio->Divide(h1_mc); 
    h1_ratio->SetLabelSize(0.16,"XY");
    //h1_ratio->SetLabelOffset(0.9);
    h1_ratio->GetYaxis()->SetLabelSize(0.17);
    h1_ratio->GetYaxis()->SetLabelOffset(0.015);
    h1_ratio->SetTitleSize(0.16,"XY");
    h1_ratio->SetTitleOffset(1.0);
    h1_ratio->GetYaxis()->SetNdivisions(/*3,false*/505);
    //h1_ratio->GetXaxis()->SetNdivisions(6,true);
    h1_ratio->GetXaxis()->SetNdivisions(505);
    //h1_ratio->SetMinimum(0.4);
    //h1_ratio->SetMaximum(1.6);
    h1_ratio->GetYaxis()->SetRangeUser(0.4, 1.6);
    if(doPrefit) h1_ratio->GetYaxis()->SetTitle("Data/MC");
    else h1_ratio->GetYaxis()->SetTitle("Data/Fit");
    h1_ratio->GetYaxis()->SetTitleSize(0.17);
    h1_ratio->GetYaxis()->SetTitleOffset(0.48);
    h1_ratio->GetXaxis()->SetTitle("M_{J} (GeV)");
    h1_ratio->GetXaxis()->SetTitleSize(0.18);
    h1_ratio->GetXaxis()->SetTitleOffset(1);
    h1_ratio->GetXaxis()->SetLabelSize(0);
    if(step=="ttbar") {
      TH1D* h1_ratio_clone = (TH1D*)h1_data->Clone("h1_ratio_clone");
      h1_ratio->SetBinError(1,h1_ratio_clone->GetBinError(1)/h1_mc->GetBinContent(1));
      h1_ratio->SetBinError(2,h1_ratio_clone->GetBinError(2)/h1_mc->GetBinContent(2));
      h1_ratio->SetBinError(3,h1_ratio_clone->GetBinError(3)/h1_mc->GetBinContent(3));
    }
    else {
      TH1D* h1_ratio_clone = (TH1D*)h1_data->Clone("h1_ratio_clone");
      h1_ratio->SetBinError(1, h1_ratio_clone->GetBinError(1)/h1_mc->GetBinContent(1));
      h1_ratio->SetBinError(2, h1_ratio_clone->GetBinError(2)/h1_mc->GetBinContent(2));
      h1_ratio->SetBinError(3, h1_ratio_clone->GetBinError(3)/h1_mc->GetBinContent(3));
    }
    h1_ratio->Draw("e");  
    tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
    
    if(!doPrefit && !(step=="ttbar")) {
      for(unsigned int inb=1; inb<4; inb++)  
      { 
          h1_ratio_err->SetBinContent(inb, 1);
          h1_ratio_err->SetBinError(inb, err[4][ibin][inb-1]);
      }
      h1_ratio_err->SetMarkerSize(0);
      h1_ratio_err->SetFillColor(kBlack);
      h1_ratio_err->SetLineColor(kBlack);
      h1_ratio_err->SetFillStyle(3354);
      h1_ratio_err->Draw("e2 same");
    }

    TLine *l = new TLine(500,1,1400,1);
    l->SetLineStyle(2);
    l->Draw("same");

    c->Print(Form("plots/%s_%s/%s_%s.pdf", year.Data(), step.Data(), doPrefit?"pre":"fit", binname[i-22].c_str()));
    c->Print(Form("plots/%s_%s/%s_%s.png", year.Data(), step.Data(), doPrefit?"pre":"fit", binname[i-22].c_str()));
    
    //debug
    if(!doPrefit) {
      for(unsigned int inb=1; inb<4; inb++)
      {   
          cout << inb << " ratio " <<h1_ratio_err->GetBinContent(inb) << endl;;
          cout << inb << " ratio " <<h1_ratio_err->GetBinError(inb) << endl;;
          cout << inb << " mc " <<h1_mc->GetBinContent(inb) << endl;;
          cout << inb << " mc " <<h1_mc->GetBinError(inb) << endl;;
      } 
    }
    delete pad_stack; 
    delete pad_ratio; 
    delete c; 
    delete st;
    delete h1_data; 
    delete h1_qcd; 
    delete h1_ttbar; 
    delete h1_wjets; 
    delete h1_other; 
    delete h1_ratio; 
    if(plotSPlusB) {
      delete h1_signal_m1200; 
      delete h1_signal_m1800; 
    }
  }
  
  // -------------------------------------------------------------------------------
  // ------------------- Print table  ----------------------------------------------
  // -------------------------------------------------------------------------------
  
  const int nbins = 15;
  TString binLatex[nbins] = {
    /*
      // control regions
      "4\\leq N_{jets}\\leq5, 500<M_{J}<800~\\GeV",
      "6\\leq N_{jets}\\leq7, 500<M_{J}<800~\\GeV",
      "4\\leq N_{jets}\\leq5, 500<M_{J}<800~\\GeV",
      "4\\leq N_{jets}\\leq5, M_{J}>800~\\GeV",
      "6\\leq N_{jets}\\leq7, M_{J}>800~\\GeV",
      "4\\leq N_{jets}\\leq5, M_{J}>800~\\GeV",
      // low M_{J} control regions
      "4\\leq N_{jets}\\leq5,300<M_{J}<500~\\GeV",  // 6
      "6\\leq N_{jets}\\leq7,300<M_{J}<500~\\GeV",
      "8\\leq N_{jets}\\leq9,300<M_{J}<500~\\GeV",
      "N_{jets}\\geq10,300<M_{J}<500~\\GeV",
      // signal regions, low M_{J}
      "N_{jets}\\geq10,500<M_{J}<800~\\GeV",       // 10
      "6\\leq N_{jets}\\leq7,500<M_{J}<800~\\GeV",
      "N_{jets}\\geq8,500<M_{J}<800~\\GeV",
      // signal regions, high M_{J}
      "N_{jets}\\geq10,M_{J}>800~\\GeV",           // 13
      "6\\leq N_{jets}\\leq7,M_{J}>800~\\GeV",
      "N_{jets}\\geq8,M_{J}>800~\\GeV",
      //Missing regions
      "8\\leq N_{jets}\\leq9,500<M_{J}<800~\\GeV",  // 16
      "8\\leq N_{jets}\\leq9,M_{J}>800~\\GeV"
      */
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=0",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=0",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=0",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=1",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=1",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=1",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}=2",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=2",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=2",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}\\geq3",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}=3",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}=3",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},4\\leq N_{jets}\\leq5,N_{b}\\geq4",//bin34
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},6\\leq N_{jets}\\leq7,N_{b}\\geq4",
      "N_{leps}=1,H_{T}>1200~\\textrm{GeV},N_{jets}\\geq8,N_{b}\\geq4",
  }; 

/* // This is for debug 
  int tablebin=0; 
  for(int inb=3; inb<4; inb++) 
    printYieldBin(tablebin, inb,  
                data[tablebin][inb-1], 
                qcd[tablebin][inb-1], 
                ttbar[tablebin][inb-1], 
                wjets[tablebin][inb-1], 
                other[tablebin][inb-1],
                sig1700[tablebin][inb-1],
                err[0][tablebin][inb-1]*qcd[tablebin][inb-1], 
                err[1][tablebin][inb-1]*ttbar[tablebin][inb-1], 
                err[2][tablebin][inb-1]*wjets[tablebin][inb-1], 
                err[3][tablebin][inb-1]*other[tablebin][inb-1],
                err[4][tablebin][inb-1]*(qcd[tablebin][inb-1]+ttbar[tablebin][inb-1]+wjets[tablebin][inb-1]+other[tablebin][inb-1]));
*/

  // 0-lepton
  /*
  int tablebin_0lep[4]={16,17,10,13};
  cout << "\\begin{table}" << endl;
  cout << "\\centering" << endl;
  cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
  cout << "\\hline" << endl;
  cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1700\\GeV$\\\\"  << endl;
  cout << "\\hline\\hline" << endl;

  for(int ibin=0; ibin<4; ibin++) 
  {
    int tablebin=tablebin_0lep[ibin]; 
  cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$} \\\\" << endl;
  cout << "\\hline" << endl;
  for(int inb=1; inb<4; inb++) 
    printYieldBin(tablebin, inb,  
                data[tablebin][inb-1], 
                qcd[tablebin][inb-1], 
                ttbar[tablebin][inb-1], 
                wjets[tablebin][inb-1], 
                other[tablebin][inb-1],
                sig1700[tablebin][inb-1],
                err[0][tablebin][inb-1]*qcd[tablebin][inb-1], 
                err[1][tablebin][inb-1]*ttbar[tablebin][inb-1], 
                err[2][tablebin][inb-1]*wjets[tablebin][inb-1], 
                err[3][tablebin][inb-1]*other[tablebin][inb-1],
                err[4][tablebin][inb-1]*(qcd[tablebin][inb-1]+ttbar[tablebin][inb-1]+wjets[tablebin][inb-1]+other[tablebin][inb-1]));
  cout << "\\hline" << endl;
  }
  cout<< "\\hline" << endl;
  cout << "\\end{tabular}"<<endl;
  cout << "\\end{table}\n"<< endl;

  cout << endl;
  cout << endl;
  */
  // 1-lepton
  int tablebin_1lep[15]={22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
  cout << "\\begin{table}" << endl;
  cout << "\\centering" << endl;
  cout << "\\vspace{1mm}" << endl;
  cout << "\\resizebox{\\textwidth}{!}{%" << endl;
  cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
  cout << "\\hline" << endl;
  cout << "$\\MJ$ $(\\textrm{GeV})$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1800$ $\\textrm{GeV}$\\\\"  << endl;
  cout << "\\hline\\hline" << endl;

  for(int ibin=22; ibin<32; ibin++) //FIXME when unblinding
  {
    if(ibin==30) continue;//bin30 becomes SR
    if(ibin==34) continue;//exclude bin34
    int tablebin=tablebin_1lep[ibin-22]; 

    cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin-22].Data() << "$} \\\\" << endl;
    cout << "\\hline" << endl;
    for(int inb=0; inb<3; inb++) { 
      printYieldBin(inb,  
		data[tablebin][inb], 
		qcd[tablebin][inb], 
		ttbar[tablebin][inb], 
		wjets[tablebin][inb], 
		other[tablebin][inb],
		sig1800[tablebin][inb],
		err[0][tablebin][inb]*qcd[tablebin][inb], 
		err[1][tablebin][inb]*ttbar[tablebin][inb], 
		err[2][tablebin][inb]*wjets[tablebin][inb], 
		err[3][tablebin][inb]*other[tablebin][inb],
		err[4][tablebin][inb]*(qcd[tablebin][inb]+ttbar[tablebin][inb]+wjets[tablebin][inb]+other[tablebin][inb]),
		true);
    }  
    cout << "\\hline" << endl;
  }
  cout<< "\\hline" << endl;
  cout << "\\end{tabular}"<<endl;
  cout << "}" << endl;
  cout << "\\end{table}\n"<< endl;

  // -------------------------------------------------------------------------------
  // ------------------------------- end table -------------------------------------
  // -------------------------------------------------------------------------------
 
 if(plotSPlusB) {
    plotFitPulls(result_s->floatParsFinal(), Form("plots/%s_%s/pulls_nopdf.pdf",year.Data(), step.Data()), "base",year);
    plotFitPulls(result_s->floatParsFinal(), "plots/pulls_pdf.pdf", "pdf",year);
    plotFitPulls(result_s->floatParsFinal(), "plots/pulls_mcstats.pdf", "mcstat",year);
  }
  else {
    plotFitPulls(result_b->floatParsFinal(), Form("plots/%s_%s/pulls_nopdf.pdf",year.Data(), step.Data()), "base",year);
    plotFitPulls(result_b->floatParsFinal(), "plots/pulls_pdf.pdf", "pdf",year);
    plotFitPulls(result_b->floatParsFinal(), "plots/pulls_mcstats.pdf", "mcstat",year);
  }
}

void setValues(RooWorkspace *work, RooFitResult *result)
{ 
  RooArgList variables = result->floatParsFinal();
  for(int i=0; i<variables.getSize(); i++) {
    RooRealVar *var = static_cast<RooRealVar*>(variables.at(i));
    std::string name(var->GetName());
    RooRealVar *varInWorkspace = static_cast<RooRealVar*>(work->arg(var->GetName()));
    varInWorkspace->setVal(var->getVal());
  }
}

void printYieldBin(int bin, int nb, float data, float qcd, float ttbar, float wjets, float other, float sig)
{ 
    cout << ((nb==3)?"$3$":"$\\geq 4$") << " & "
        << Form("$%.1f$",qcd)  << " & "
        << Form("$%.1f$",ttbar) << " & "
        << Form("$%.1f$",wjets) << " & "
        << Form("$%.1f$",other) << " & "
        << Form("$%.1f$",qcd+ttbar+wjets+other) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
}

void printYieldBin(int bin, int nb, float data, float qcd, float ttbar, float wjets, float other, float sig, 
                                    float qcd_err, float ttbar_err, float wjets_err, float other_err)
{ 
    if(qcd==0) qcd_err=0;
    if(ttbar==0) ttbar_err=0;
    if(wjets==0) wjets_err=0;
    if(other==0) other_err=0;
    
    float tot_err = TMath::Sqrt(qcd_err*qcd_err+ttbar_err*ttbar_err+wjets_err*wjets_err+other_err*other_err);
    cout << ((nb==3)?"$3$":"$\\geq 4$") << " & "
        //<< Form("$%.1f \\pm %.1f$",qcd,qcd_err)  << " & "
        //<< Form("$%.1f \\pm %.1f$",ttbar,ttbar_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",wjets,wjets_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",other,other_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",qcd+ttbar+wjets+other,tot_err) << " & "
        << Form("$%.1f $",qcd)  << " & "
        << Form("$%.1f $",ttbar) << " & "
        << Form("$%.1f $",wjets) << " & "
        << Form("$%.1f $",other) << " & "
        << Form("$%.1f $",qcd+ttbar+wjets+other) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
}

void printYieldBin(int mjbin, float data,
         float qcd, float ttbar, float wjets, float other, float sig,
	 float qcd_err, float ttbar_err, float wjets_err, float other_err,
	 float allbkg_err, bool printErr)	 
{
  if(qcd==0) qcd_err=0;
  if(ttbar==0) ttbar_err=0;
  if(wjets==0) wjets_err=0;
  if(other==0) other_err=0;

  string imj;
  if(mjbin==0) imj="$500 - 800$";
  if(mjbin==1) imj="$800 - 1100$";
  if(mjbin==2) imj="$1100 \\le$";
//  float allbkg_err = TMath::Sqrt(qcd_err*qcd_err + ttbar_err*ttbar_err + wjets_err*wjets_err + other_err*other_err);

  if(printErr)
  {
    cout << imj << " & "
//	<< Form("$%.1f \\pm %.1f$", qcd, qcd_err) << " & "
//	<< Form("$%.1f \\pm %.1f$", ttbar, ttbar_err) << " & "
//	<< Form("$%.1f \\pm %.1f$", wjets, wjets_err) << " & "
//	<< Form("$%.1f \\pm %.1f$", other, other_err) << " & "
	<< Form("$%.1f$", qcd) << " & "
	<< Form("$%.1f$", ttbar) << " & "
	<< Form("$%.1f$", wjets) << " & "
	<< Form("$%.1f$", other) << " & "
	<< Form("$%.1f \\pm %.1f$", qcd+ttbar+wjets+other, allbkg_err) << " & "
	<< Form("$%.0f$", data) << " & "
	<< Form("$%.1f$", sig) << " \\\\ " << endl;
  }
  else
  {
    cout << imj << " & "
	<< Form("$%.1f$", qcd) << " & "
	<< Form("$%.1f$", ttbar) << " & "
	<< Form("$%.1f$", wjets) << " & "
	<< Form("$%.1f$", other) << " & "
	<< Form("$%.1f$", qcd+ttbar+wjets+other) << " & "
	<< Form("$%.1f$", data) << " & "
	<< Form("$%.1f$", sig) << " \\\\ " << endl;
  }
}
/*
void printYieldBin(int ibin, int nb, float data, float qcd, float ttbar, float wjets, float other, float sig, 
                                    float qcd_err, float ttbar_err, float wjets_err, float other_err, float allbkg_err)
{ 
    if(qcd==0) qcd_err=0;
    if(ttbar==0) ttbar_err=0;
    if(wjets==0) wjets_err=0;
    if(other==0) other_err=0;

    string nbbin; 
    if(nb==0) nbbin="$0$";
    if(nb==1) nbbin="$1$";
    if(nb==2) nbbin="$2$";
    if(nb==3) nbbin="$3$";
    if(nb==4) nbbin="$\\geq 4$";

    cout << nbbin << " & "
        //<< Form("$%.1f \\pm %.1f$",qcd,qcd_err)  << " & "
        //<< Form("$%.1f \\pm %.1f$",ttbar,ttbar_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",wjets,wjets_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",other,other_err) << " & "
        //<< Form("$%.1f \\pm %.1f$",qcd+ttbar+wjets+other,allbkg_err) << " & "
        << Form("$%.1f $",qcd)  << " & "
        << Form("$%.1f $",ttbar) << " & "
        << Form("$%.1f $",wjets) << " & "
        << Form("$%.1f $",other) << " & "
        << Form("$%.1f $",qcd+ttbar+wjets+other) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
}
*/

float AddInQuad(float a, float b)
{
    return TMath::Sqrt(a*a+b*b);
} 

void plotFitPulls(const RooArgList &pulls, const TString &pullString, const std::string &type, const TString year)
{
  float PadTopMargin(0.08), PadRightMargin(0.08);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadTopMargin(PadTopMargin);
  gStyle->SetPadRightMargin(PadRightMargin);
  //TCanvas *cPull = new TCanvas("c","c",1600,800); 
  //TCanvas *cPull = new TCanvas("c","c",2000,1200); 
  TCanvas* cPull = new TCanvas("c","c",4000,4000);
  //cPull->SetBottomMargin(0.4);
  cPull->Divide(1,2);

  int size = pulls.getSize();

  int goodVars=0;
  for(int i=0; i<size; i++) {
    RooRealVar *pullVar = static_cast<RooRealVar*>((pulls.at(i)));
    TString name(pullVar->GetName());
    if(name.Contains("norm")) continue;
    //if(name.BeginsWith("prop")) continue;
    if(name.BeginsWith("w_pdf") && type.find("pdf")!=std::string::npos) continue;
    else if(name.BeginsWith("mcstat") && type.find("mcstat")!=std::string::npos) continue;
    else if((name.BeginsWith("w_pdf") || name.BeginsWith("mcstat")) && type.find("base")!=std::string::npos) continue;
    if(!name.BeginsWith("r")) goodVars++;
  }
  std::cout << "Found " << goodVars << " nuisances to plot" << std::endl;

  TH1D *h  = new TH1D("h",  "h",  goodVars,   0, goodVars);
  TH1D *h1 = new TH1D("h1", "h1", int(goodVars/2), 0, int(goodVars/2));
  TH1D *h2 = new TH1D("h2", "h2", goodVars-int(goodVars/2), 0, goodVars-int(goodVars/2));
  double pullRange=2.5;

  h->SetMaximum(pullRange);
  h->SetMinimum(-pullRange);
  h1->SetMaximum(pullRange);
  h1->SetMinimum(-pullRange);
  h2->SetMaximum(pullRange);
  h2->SetMinimum(-pullRange);

  int iGood=0;
  int iGood2=0;
  double sumChi2=0.0;

  cout << "Size: "<< size << endl;
  cout << "GoodVars "<< goodVars << endl;

  for(int i=0; i<size; i++) {
    RooRealVar *pullVar = static_cast<RooRealVar*>(pulls.at(i));
    double value = pullVar->getVal();
    TString name(pullVar->GetName()); 
    if(name.Contains("norm")) continue;
    //if(name.BeginsWith("prop")) continue;
    if(!name.BeginsWith("w_pdf") && type.find("pdf")!=std::string::npos) continue;
    else if(!name.BeginsWith("mcstat") && type.find("mcstat")!=std::string::npos) continue;
    else if((name.BeginsWith("w_pdf") || name.BeginsWith("mcstat")) && type.find("base")!=std::string::npos) continue;
    if(!name.BeginsWith("r") ) {
      iGood++;
      double binErrorLo = fabs(pullVar->getErrorLo());
      double binErrorHi = fabs(pullVar->getErrorHi());
      double binError = (binErrorLo+binErrorHi)/2;
      double eps=0.0001;
      if(iGood>=int(goodVars/2)) iGood2++;
      // if one of the errors is zero, the symmetrized error will be too low by a factor of two
      if(binErrorLo<eps || binErrorHi<eps) binError*=2;
      if(iGood<int(goodVars/2)) {
        h1->SetBinContent(iGood, value);
        h1->SetBinError(iGood, binError);
        std::cout.precision(3);
        std::cout << " & \\texttt{" << name.ReplaceAll("_","\\_") << "} & $" << value << " \\pm " <<  binError << "$\\\\" << std::endl;
        sumChi2+=pow(value/binError,2);
        h1->GetXaxis()->LabelsOption("v");
        h1->GetXaxis()->SetBinLabel(iGood, pullVar->GetName());
        h1->GetYaxis()->SetTitle("Post-fit pulls");
      }
      else {
        h2->SetBinContent(iGood2, value);
        h2->SetBinError(iGood2, binError);
        std::cout.precision(3);
        std::cout << " & \\texttt{" << name.ReplaceAll("_","\\_") << "} & $" << value << " \\pm " <<  binError << "$\\\\" << std::endl;
        sumChi2+=pow(value/binError,2);
        h2->GetXaxis()->LabelsOption("v");
        h2->GetXaxis()->SetBinLabel(iGood2, pullVar->GetName());
        h2->GetYaxis()->SetTitle("Post-fit pulls");
      }
    }
  }
  
  std::cout << "pull chi2/ndof: " << sumChi2 << "/" << iGood << std::endl;

  float lumi;
  if(year=="UL2016") lumi = 36.3;
  if(year=="UL2017") lumi = 41.5;
  if(year=="UL2018") lumi = 59.8;
  if(year=="UL20178") lumi = 101;
  if(year=="UL201678") lumi = 138;
  //TString cmslabel = "#font[62]{CMS} #font[52]{Preliminary}";
  TString lumilabel = TString::Format("%1.1f", lumi)+" fb^{-1}, 13 TeV";
  if(year=="UL20178" || year=="UL201678") lumilabel = TString::Format("%d", int(lumi))+" fb^{-1}, 13 TeV";
  TLatex *TexCMS = new TLatex(0.1,1-PadTopMargin+0.02,"CMS #font[52]{Preliminary}");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.04);
  TexCMS->SetLineWidth(2);

  // top
  cPull->cd(1);
  gPad->SetBottomMargin(0.35);
  h1->GetYaxis()->SetTitleOffset(0.7);
  h1->GetXaxis()->SetLabelSize(0.02);
  h1->Draw();
  TLatex label; label.SetNDC(kTRUE);
  label.SetTextSize(0.035);
  label.SetTextAlign(11);
  label.SetTextAlign(31);
  label.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,lumilabel);
  TexCMS->Draw("same");
  TBox *b = new TBox(0, -1, int(goodVars/2), 1);
  b->SetFillStyle(3003);
  b->SetFillColor(kBlue);
  b->Draw();
  h1->Draw("same");
  // bottom
  cPull->cd(2);
  gPad->SetBottomMargin(0.35);
  h2->GetYaxis()->SetTitleOffset(0.7);
  h2->GetXaxis()->SetLabelSize(0.02);
  h2->Draw();
  TLatex label2; label2.SetNDC(kTRUE);
  label2.SetTextSize(0.035);
  label2.SetTextAlign(11);
  label2.SetTextAlign(31);
  label2.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,lumilabel);
  TexCMS->Draw("same");
  TBox *b2 = new TBox(0, -1, goodVars-int(goodVars/2), 1);
  b2->SetFillStyle(3003);
  b2->SetFillColor(kBlue);
  b2->Draw();
  h2->Draw("same");

  cPull->Print(pullString);  
  TString pullStringC = pullString;
  pullStringC.ReplaceAll(".pdf", ".C");
  cPull->Print(pullStringC);
}
