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

void remapping(TH1D* &h1, TH1D* &h2)
{
  
  h1->SetBinContent(1, h2->GetBinContent(1));
  h1->SetBinContent(2, h2->GetBinContent(2));
  h1->SetBinContent(3, h2->GetBinContent(3));
  h1->SetBinContent(4, h2->GetBinContent(10));
  h1->SetBinContent(5, h2->GetBinContent(11));
  h1->SetBinContent(6, h2->GetBinContent(12));
  h1->SetBinContent(7, h2->GetBinContent(19));
  h1->SetBinContent(8, h2->GetBinContent(20));
  h1->SetBinContent(9, h2->GetBinContent(21));
  h1->SetBinContent(10, h2->GetBinContent(28));
  h1->SetBinContent(11, h2->GetBinContent(29));
  h1->SetBinContent(12, h2->GetBinContent(30));
  h1->SetBinContent(13, h2->GetBinContent(4));
  h1->SetBinContent(14, h2->GetBinContent(5));
  h1->SetBinContent(15, h2->GetBinContent(6));
  h1->SetBinContent(16, h2->GetBinContent(13));
  h1->SetBinContent(17, h2->GetBinContent(14));
  h1->SetBinContent(18, h2->GetBinContent(15));
  h1->SetBinContent(19, h2->GetBinContent(22));
  h1->SetBinContent(20, h2->GetBinContent(23));
  h1->SetBinContent(21, h2->GetBinContent(24));
  h1->SetBinContent(22, h2->GetBinContent(7));
  h1->SetBinContent(23, h2->GetBinContent(8));
  h1->SetBinContent(24, h2->GetBinContent(9));
  h1->SetBinContent(25, h2->GetBinContent(16));
  h1->SetBinContent(26, h2->GetBinContent(17));
  h1->SetBinContent(27, h2->GetBinContent(18));
  h1->SetBinContent(28, h2->GetBinContent(31));
  h1->SetBinContent(29, h2->GetBinContent(32));
  h1->SetBinContent(30, h2->GetBinContent(33));
  h1->SetBinContent(31, h2->GetBinContent(37));
  h1->SetBinContent(32, h2->GetBinContent(38));
  h1->SetBinContent(33, h2->GetBinContent(39));
  h1->SetBinContent(34, h2->GetBinContent(25));
  h1->SetBinContent(35, h2->GetBinContent(26));
  h1->SetBinContent(36, h2->GetBinContent(27));
  h1->SetBinContent(37, h2->GetBinContent(34));
  h1->SetBinContent(38, h2->GetBinContent(35));
  h1->SetBinContent(39, h2->GetBinContent(36));
  h1->SetBinContent(40, h2->GetBinContent(40));
  h1->SetBinContent(41, h2->GetBinContent(41));
  h1->SetBinContent(42, h2->GetBinContent(42));
  h1->SetBinError(1, h2->GetBinError(1));
  h1->SetBinError(2, h2->GetBinError(2));
  h1->SetBinError(3, h2->GetBinError(3));
  h1->SetBinError(4, h2->GetBinError(10));
  h1->SetBinError(5, h2->GetBinError(11));
  h1->SetBinError(6, h2->GetBinError(12));
  h1->SetBinError(7, h2->GetBinError(19));
  h1->SetBinError(8, h2->GetBinError(20));
  h1->SetBinError(9, h2->GetBinError(21));
  h1->SetBinError(10, h2->GetBinError(28));
  h1->SetBinError(11, h2->GetBinError(29));
  h1->SetBinError(12, h2->GetBinError(30));
  h1->SetBinError(13, h2->GetBinError(4));
  h1->SetBinError(14, h2->GetBinError(5));
  h1->SetBinError(15, h2->GetBinError(6));
  h1->SetBinError(16, h2->GetBinError(13));
  h1->SetBinError(17, h2->GetBinError(14));
  h1->SetBinError(18, h2->GetBinError(15));
  h1->SetBinError(19, h2->GetBinError(22));
  h1->SetBinError(20, h2->GetBinError(23));
  h1->SetBinError(21, h2->GetBinError(24));
  h1->SetBinError(22, h2->GetBinError(7));
  h1->SetBinError(23, h2->GetBinError(8));
  h1->SetBinError(24, h2->GetBinError(9));
  h1->SetBinError(25, h2->GetBinError(16));
  h1->SetBinError(26, h2->GetBinError(17));
  h1->SetBinError(27, h2->GetBinError(18));
  h1->SetBinError(28, h2->GetBinError(31));
  h1->SetBinError(29, h2->GetBinError(32));
  h1->SetBinError(30, h2->GetBinError(33));
  h1->SetBinError(31, h2->GetBinError(37));
  h1->SetBinError(32, h2->GetBinError(38));
  h1->SetBinError(33, h2->GetBinError(39));
  h1->SetBinError(34, h2->GetBinError(25));
  h1->SetBinError(35, h2->GetBinError(26));
  h1->SetBinError(36, h2->GetBinError(27));
  h1->SetBinError(37, h2->GetBinError(34));
  h1->SetBinError(38, h2->GetBinError(35));
  h1->SetBinError(39, h2->GetBinError(36));
  h1->SetBinError(40, h2->GetBinError(40));
  h1->SetBinError(41, h2->GetBinError(41));
  h1->SetBinError(42, h2->GetBinError(42));
}
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

void plotresult_combine_pdf(int gluinoMass=1800)
{
  float lumi = 138;

  setTDRStyle();
  gROOT->ForceStyle();


  std::vector<std::string> binname;
  std::vector<int> binnumber;
  binname = {"nlep1_nj45_nb0",   "nlep1_nj67_nb0",     "nlep1_nj8_nb0",
             "nlep1_nj45_nb1",   "nlep1_nj67_nb1",     "nlep1_nj8_nb1", 
             "nlep1_nj45_nb2",   "nlep1_nj67_nb2",     "nlep1_nj8_nb2",
    	 "nlep1_nj45_nb3",   "nlep1_nj67_nb3",     "nlep1_nj8_nb3",
    			     "nlep1_nj67_nb4",     "nlep1_nj8_nb4"};
  binnumber = {22,23,24,25,26,27,28,29,30,31,32,33,35,36};
  
  // for yield table  
  float data[51][3], qcd[51][3], ttbar[51][3], wjets[51][3], other[51][3], sig1200[51][3], sig1800[51][3]; 
  float err[5][31][4]; // first index : qcd, ttbar, wjets, other, all bkg
  
  for(int ibin=22; ibin<52; ibin++)
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
  TFile* infile  = TFile::Open("variations/output_impact_UL201678.root", "READ");
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

  // Get post-fit uncertainty 
  TFile* errfile;
  errfile = TFile::Open("rpv_postfit_err_unblind_UL201678.root","READ");
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

  TString crvr = "unblind";
  std::string resultsFilename=Form("mlfit_unblind_UL201678.root");
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
    h1_qcd =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/qcd", ibin)));
    h1_ttbar =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/ttbar", ibin)));
    h1_wjets =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/wjets", ibin)));
    h1_other =  changeHistogram((TH1D*) fResults->Get(Form("shapes_fit_b/bin%i/other", ibin)));

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

    h1cosmetic(h1_prefit_sig_m1200[i],        Form("prefit signal 1200 bin%i", ibin),        3, "signal",           "M_{J}");
    h1cosmetic(h1_prefit_sig_m1800[i],        Form("prefit signal 1800 bin%i", ibin),        3, "signal",           "M_{J}");
    h1_prefit_sig_m1200[i]->SetLineStyle(2); 
    h1_prefit_sig_m1800[i]->SetLineStyle(1); 

    // uncertainty band 
    TH1D *h1_mc = (TH1D*)h1_qcd->Clone("h1_qcd");
    h1_mc->Add(h1_ttbar);
    h1_mc->Add(h1_wjets);
    h1_mc->Add(h1_other);
    for(unsigned int inb=1; inb<4; inb++){
      cout<< err[4][ibin][inb-1] << endl;
      h1_mc->SetBinError(inb,err[4][ibin][inb-1]*h1_mc->GetBinContent(inb));
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

    st->SetMaximum(h1_data->GetMaximum()*2000);
    st->SetMinimum(0.1);
    st->Draw("hist");
    h1_mc->Draw("same E2");
    h1_data->Draw("e same"); 
    st->GetYaxis()->SetTitle("Events / (300 GeV)");
    st->GetYaxis()->SetTitleOffset(1.1);
    st->GetYaxis()->SetTitleSize(0.075);
    st->GetYaxis()->SetLabelSize(0.07);
    st->GetXaxis()->SetLabelSize(0.0);
    st->GetXaxis()->SetTitle("M_{J} [GeV]");
    
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
    leg->AddEntry(h1_prefit_sig_m1200[i], Form("m_{#tilde{g}}=%i GeV#times0.01  ",1200) , "L");
    leg->AddEntry(h1_prefit_sig_m1800[i], Form("m_{#tilde{g}}=%i GeV",gluinoMass) , "L");
    leg->AddEntry(h1_mc, "Post-fit uncertainty",    "F");
    leg->Draw();

    // CMS and lumi labels
    float textSize = 0.06;
    float lumi = 138;
    TLatex* TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%d fb^{-1} (13 TeV)}", int(lumi)));
    TexEnergyLumi->SetNDC();
    TexEnergyLumi->SetTextSize(textSize);
    TexEnergyLumi->SetTextAlign (31);
    TexEnergyLumi->SetLineWidth(2);

    TLatex *TexCMS = new TLatex(0.2,0.92,"CMS #font[52]{Preliminary}");
    TexCMS->SetNDC();
    TexCMS->SetTextSize(textSize);
    TexCMS->SetLineWidth(2);
    TexEnergyLumi->Draw("same");
    TexCMS->Draw("same");
   
    // display cuts
    TLatex *TexNlep, *TexNjets, *TexNb;
    TString binname_tstr = binname[i-22]; 
    if(binname_tstr.Contains("nlep1"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 1");
    if(binname_tstr.Contains("nlep0"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 0");
    TexNlep->SetNDC();
    TexNlep->SetTextSize(textSize);
    if(binname_tstr.Contains("nj45_"))   TexNjets = new TLatex(0.25,0.72,"4 #leq N_{jet} #leq 5");
    if(binname_tstr.Contains("nj67_"))   TexNjets = new TLatex(0.25,0.72,"6 #leq N_{jet} #leq 7");
    if(binname_tstr.Contains("nj89_"))   TexNjets = new TLatex(0.25,0.72,"8 #leq N_{jet} #leq 9");
    if(binname_tstr.Contains("nj8_"))    TexNjets = new TLatex(0.25,0.72,"N_{jet} #geq 8");
    if(binname_tstr.Contains("nj10_"))   TexNjets = new TLatex(0.25,0.72,"N_{jet} #geq 10");
    TexNjets->SetNDC();
    TexNjets->SetTextSize(textSize);
    if(binname_tstr.Contains("nb0"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 0");
    if(binname_tstr.Contains("nb1"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 1");
    if(binname_tstr.Contains("nb2"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 2");
    if(binname_tstr.Contains("nb3"))     TexNb = new TLatex(0.25,0.64,"N_{b} = 3");
    if(binname_tstr.Contains("nb4"))     TexNb = new TLatex(0.25,0.64,"N_{b} #geq 4");
    if(binname_tstr=="nlep1_nj45_nb3")   TexNb = new TLatex(0.25,0.64,"N_{b} #geq 3");
    TexNb->SetNDC();
    TexNb->SetTextSize(textSize);

    TexNlep->SetTextFont(42);
    TexNjets->SetTextFont(42);
    TexNb->SetTextFont(42);
    TexNlep->Draw("same");
    TexNjets->Draw("same");
    TexNb->Draw("same");
    
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
    tex_mj500->SetNDC(); tex_mj800->SetNDC(); tex_mj1100->SetNDC(); tex_mj1400->SetNDC();
    tex_mj500->SetTextSize(0.16); tex_mj800->SetTextSize(0.16); tex_mj1100->SetTextSize(0.16); tex_mj1400->SetTextSize(0.16);
    tex_mj500->SetTextFont(42); tex_mj800->SetTextFont(42); tex_mj1100->SetTextFont(42); tex_mj1400->SetTextFont(42);

    TH1D *h1_ratio = (TH1D*)h1_data->Clone("h1_ratio"); 
    TH1D *h1_ratio_err = (TH1D*)h1_ratio->Clone("h1_ratio_err");  
    h1_ratio->Divide(h1_mc); 
    h1_ratio->SetLabelSize(0.16,"XY");
    h1_ratio->GetYaxis()->SetLabelSize(0.17);
    h1_ratio->GetYaxis()->SetLabelOffset(0.015);
    h1_ratio->SetTitleSize(0.16,"XY");
    h1_ratio->SetTitleOffset(1.0);
    h1_ratio->GetYaxis()->SetNdivisions(/*3,false*/505);
    h1_ratio->GetXaxis()->SetNdivisions(505);
    h1_ratio->GetYaxis()->SetRangeUser(0.4, 1.6);
    h1_ratio->GetYaxis()->SetTitle("Data/Fit");
    h1_ratio->GetYaxis()->SetTitleSize(0.17);
    h1_ratio->GetYaxis()->SetTitleOffset(0.48);
    h1_ratio->GetXaxis()->SetTitle("M_{J} (GeV)");
    h1_ratio->GetXaxis()->SetTitleSize(0.18);
    h1_ratio->GetXaxis()->SetTitleOffset(1);
    h1_ratio->GetXaxis()->SetLabelSize(0);
    TH1D* h1_ratio_clone = (TH1D*)h1_data->Clone("h1_ratio_clone");
    h1_ratio->SetBinError(1, h1_ratio_clone->GetBinError(1)/h1_mc->GetBinContent(1));
    h1_ratio->SetBinError(2, h1_ratio_clone->GetBinError(2)/h1_mc->GetBinContent(2));
    h1_ratio->SetBinError(3, h1_ratio_clone->GetBinError(3)/h1_mc->GetBinContent(3));
    h1_ratio->Draw("e");  
    tex_mj500->Draw(); tex_mj800->Draw(); tex_mj1100->Draw(); //tex_mj1400->Draw();
    
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

    TLine *l = new TLine(500,1,1400,1);
    l->SetLineStyle(2);
    l->Draw("same");

    c->Print(Form("plots/%s.pdf", binname[i-22].c_str()));
    
    //debug
    for(unsigned int inb=1; inb<4; inb++)
    {   
        cout << inb << " ratio " <<h1_ratio_err->GetBinContent(inb) << endl;;
        cout << inb << " ratio " <<h1_ratio_err->GetBinError(inb) << endl;;
        cout << inb << " mc " <<h1_mc->GetBinContent(inb) << endl;;
        cout << inb << " mc " <<h1_mc->GetBinError(inb) << endl;;
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
  }

  // Combined plot
  TH1D* h_combine_qcd = new TH1D("h_combine_qcd", "h_combine_qcd", 42, 0, 42);
  TH1D* h_combine_ttbar = new TH1D("h_combine_ttbar", "h_combine_ttbar", 42, 0, 42);
  TH1D* h_combine_wjets = new TH1D("h_combine_wjets", "h_combine_wjets", 42, 0, 42);
  TH1D* h_combine_other = new TH1D("h_combine_other", "h_combine_other", 42, 0, 42);
  TH1D* h_combine_data = new TH1D("h_combine_data", "h_combine_data", 42, 0, 42);
  TH1D* h_combine_sig1200 = new TH1D("h_combine_sig1200", "h_combine_sig1200", 42, 0, 42);
  TH1D* h_combine_sig1800 = new TH1D("h_combine_sig1800", "h_combine_sig1800", 42, 0, 42);
  TH1D* h_combine_ratio = new TH1D("h_combine_ratio", "h_combine_ratio", 42, 0, 42);
  TH1D* h_combine_ratio_postfit_err = new TH1D("h_combine_ratio_postfit_err", "h_combine_ratio_postfit_err", 42, 0, 42);
  for(int ibin=0; ibin<42; ibin++) {
    if(ibin>35) {
      h_combine_qcd->SetBinContent(ibin+1, qcd[23+int(ibin/3)][int(ibin%3)]);
      h_combine_ttbar->SetBinContent(ibin+1, ttbar[23+int(ibin/3)][int(ibin%3)]);
      h_combine_wjets->SetBinContent(ibin+1, wjets[23+int(ibin/3)][int(ibin%3)]);
      h_combine_other->SetBinContent(ibin+1, other[23+int(ibin/3)][int(ibin%3)]);
      h_combine_data->SetBinContent(ibin+1, data[23+int(ibin/3)][int(ibin%3)]);
//      h_combine_sig1200->SetBinContent(ibin+1, sig1200[23+int(ibin/3)][int(ibin%3)]);
//      h_combine_sig1800->SetBinContent(ibin+1, sig1800[23+int(ibin/3)][int(ibin%3)]);
    }
    else {
      h_combine_qcd->SetBinContent(ibin+1, qcd[22+int(ibin/3)][int(ibin%3)]);
      h_combine_ttbar->SetBinContent(ibin+1, ttbar[22+int(ibin/3)][int(ibin%3)]);
      h_combine_wjets->SetBinContent(ibin+1, wjets[22+int(ibin/3)][int(ibin%3)]);
      h_combine_other->SetBinContent(ibin+1, other[22+int(ibin/3)][int(ibin%3)]);
      h_combine_data->SetBinContent(ibin+1, data[22+int(ibin/3)][int(ibin%3)]);
    }
    h_combine_sig1200->SetBinContent(ibin+1, sig1200[22+int(ibin/3)][int(ibin%3)]);
    h_combine_sig1800->SetBinContent(ibin+1, sig1800[22+int(ibin/3)][int(ibin%3)]);
  }

  for(int ibin=0; ibin<42; ibin++) {
    h_combine_sig1200->SetBinContent(ibin+1, h_combine_sig1200->GetBinContent(ibin+1)*0.01);
  }
  cout << "A: " << h_combine_sig1800->GetBinContent(38) << endl;
  cout << "A: " << h_combine_sig1800->GetBinContent(39) << endl;
  cout << "A: " << h_combine_sig1800->GetBinContent(40) << endl;
  cout << "A: " << h_combine_sig1800->GetBinContent(41) << endl;
  cout << "A: " << h_combine_sig1800->GetBinContent(42) << endl;

  TH1D* h_combine_err = (TH1D*)h_combine_qcd->Clone("h_combine_err");
  h_combine_err->Add(h_combine_ttbar);
  h_combine_err->Add(h_combine_wjets);
  h_combine_err->Add(h_combine_other);
  for(int ibin=0; ibin<42; ibin++) {
    if(ibin>35) {
      h_combine_err->SetBinError(ibin+1, err[4][23+int(ibin/3)][int(ibin%3)]*h_combine_err->GetBinContent(ibin+1));
      h_combine_ratio_postfit_err->SetBinError(ibin+1, err[4][23+int(ibin/3)][int(ibin%3)]);
    }
    else {
      h_combine_err->SetBinError(ibin+1, err[4][22+int(ibin/3)][int(ibin%3)]*h_combine_err->GetBinContent(ibin+1));
      h_combine_ratio_postfit_err->SetBinError(ibin+1, err[4][22+int(ibin/3)][int(ibin%3)]);
    }
    h_combine_ratio_postfit_err->SetBinContent(ibin+1, 1);
    h_combine_ratio->SetBinContent(ibin+1, h_combine_data->GetBinContent(ibin+1)/h_combine_err->GetBinContent(ibin+1));
    h_combine_ratio->SetBinError(ibin+1, (h_combine_data->GetBinContent(ibin+1)/h_combine_err->GetBinContent(ibin+1))*(h_combine_data->GetBinError(ibin+1)/h_combine_data->GetBinContent(ibin+1)));
  }
  cout << "A: " << h_combine_err->GetBinError(1) << endl;
  cout << "A: " << h_combine_ratio_postfit_err->GetBinError(1) << endl;

  // Remapping
  TH1D* h_combine_qcd_clone = (TH1D*)h_combine_qcd->Clone("h_combine_qcd_clone");
  TH1D* h_combine_ttbar_clone = (TH1D*)h_combine_ttbar->Clone("h_combine_ttbar_clone");
  TH1D* h_combine_wjets_clone = (TH1D*)h_combine_wjets->Clone("h_combine_wjets_clone");
  TH1D* h_combine_other_clone = (TH1D*)h_combine_other->Clone("h_combine_other_clone");
  TH1D* h_combine_data_clone = (TH1D*)h_combine_data->Clone("h_combine_data_clone");
  TH1D* h_combine_sig1200_clone = (TH1D*)h_combine_sig1200->Clone("h_combine_sig1200_clone");
  TH1D* h_combine_sig1800_clone = (TH1D*)h_combine_sig1800->Clone("h_combine_sig1800_clone");
  TH1D* h_combine_err_clone = (TH1D*)h_combine_err->Clone("h_combine_err_clone");
  TH1D* h_combine_ratio_clone = (TH1D*)h_combine_ratio->Clone("h_combine_ratio_clone");
  TH1D* h_combine_ratio_postfit_err_clone = (TH1D*)h_combine_ratio_postfit_err->Clone("h_combine_ratio_postfit_err_clone");
  remapping(h_combine_qcd, h_combine_qcd_clone);
  remapping(h_combine_ttbar, h_combine_ttbar_clone);
  remapping(h_combine_wjets, h_combine_wjets_clone);
  remapping(h_combine_other, h_combine_other_clone);
  remapping(h_combine_data, h_combine_data_clone);
  remapping(h_combine_sig1200, h_combine_sig1200_clone);
  remapping(h_combine_sig1800, h_combine_sig1800_clone);
  remapping(h_combine_err, h_combine_err_clone);
  remapping(h_combine_ratio, h_combine_ratio_clone);
  remapping(h_combine_ratio_postfit_err, h_combine_ratio_postfit_err_clone);

  gStyle->SetHatchesSpacing(0.25);
  gStyle->SetLineStyleString(12,"4 4");
  // Cosmetics
  h_combine_qcd->SetLineColor(kBlack); h_combine_ttbar->SetLineColor(kBlack); h_combine_wjets->SetLineColor(kBlack); h_combine_other->SetLineColor(kBlack); h_combine_data->SetLineColor(kBlack);
  h_combine_qcd->SetLineWidth(1); h_combine_ttbar->SetLineWidth(1); h_combine_wjets->SetLineWidth(1); h_combine_other->SetLineWidth(1); h_combine_data->SetLineWidth(2);
  h_combine_qcd->SetFillColor(TColor::GetColor("#ffa90e")); h_combine_ttbar->SetFillColor(TColor::GetColor("#3f90da")); h_combine_wjets->SetFillColor(TColor::GetColor("#832db6")); h_combine_other->SetFillColor(TColor::GetColor("#94a4a2"));
  h_combine_sig1200->SetLineColor(TColor::GetColor("#bd1f01")); h_combine_sig1800->SetLineColor(TColor::GetColor("#bd1f01"));
  h_combine_sig1200->SetLineWidth(2); h_combine_sig1800->SetLineWidth(2);
  h_combine_sig1200->SetLineStyle(12);
    // tpad
  h_combine_err->SetLineWidth(0); h_combine_ratio_postfit_err->SetLineWidth(4);
  h_combine_err->SetMarkerSize(0); h_combine_ratio_postfit_err->SetMarkerSize(0);
  h_combine_err->SetFillColor(kBlack); h_combine_ratio_postfit_err->SetFillColor(kBlack);
  h_combine_err->SetLineColor(kBlack); h_combine_ratio_postfit_err->SetLineColor(kBlack);
  //h_combine_err->SetFillStyle(3020); h_combine_ratio_postfit_err->SetFillStyle(3020);
  h_combine_err->SetFillStyle(3354); h_combine_ratio_postfit_err->SetFillStyle(3354);
  //h_combine_err->SetFillStyle(3144); h_combine_ratio_postfit_err->SetFillStyle(3144);
  h_combine_data->GetXaxis()->SetLabelSize(0.07); // 0.05
  h_combine_data->GetYaxis()->SetLabelSize(0.07);
  h_combine_data->GetYaxis()->SetTitleSize(0.09);
  h_combine_data->GetYaxis()->SetTitleOffset(0.40);
  h_combine_data->SetMarkerStyle(20); h_combine_data->SetMarkerSize(2);
  h_combine_data->SetTitle("");
  h_combine_data->GetXaxis()->SetLabelOffset(1);
  h_combine_data->GetYaxis()->SetTitle("Events / bin");
  h_combine_data->SetMinimum(0.05); h_combine_data->SetMaximum(h_combine_data->GetMaximum()*200000);
  h_combine_data->GetYaxis()->SetTickLength(0.01);
  h_combine_data->GetYaxis()->SetLabelOffset(0.001);
    // bpad
  h_combine_ratio->SetLineWidth(2);
  h_combine_ratio->GetXaxis()->SetLabelSize(0.175); // 0.05
  h_combine_ratio->GetYaxis()->SetLabelSize(0.14); // 0.05
  h_combine_ratio->GetXaxis()->SetTitleSize(0.20); // 0.06
  h_combine_ratio->GetYaxis()->SetTitleSize(0.20); // 0.06
  h_combine_ratio->GetXaxis()->SetTitle("");
  h_combine_ratio->GetYaxis()->SetTitle("Data/MC");
  h_combine_ratio->GetYaxis()->SetTitleOffset(0.18);
  h_combine_ratio->GetYaxis()->SetRangeUser(0.4, 1.6);
  h_combine_ratio->GetYaxis()->SetNdivisions(505);
  h_combine_ratio->GetYaxis()->SetTickLength(0.01);
  h_combine_ratio->GetXaxis()->SetLabelOffset(0.02); // 0.007
  h_combine_ratio->GetXaxis()->SetTitleOffset(1.25); // 0.007

  h_combine_ratio->GetXaxis()->SetBinLabel(1, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(2, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(3, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(4, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(5, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(6, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(7, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(8, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(9, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(10, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(11, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(12, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(13, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(14, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(15, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(16, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(17, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(18, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(19, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(20, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(21, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(22, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(23, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(24, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(25, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(26, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(27, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(28, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(29, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(30, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(31, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(32, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(33, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(34, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(35, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(36, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(37, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(38, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(39, ">1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(40, "500-800");
  h_combine_ratio->GetXaxis()->SetBinLabel(41, "800-1100");
  h_combine_ratio->GetXaxis()->SetBinLabel(42, ">1100");

  THStack *st_combine = new THStack("st_combine", "st_combine");
  st_combine->Add(h_combine_other);
  st_combine->Add(h_combine_wjets);
  st_combine->Add(h_combine_ttbar);
  st_combine->Add(h_combine_qcd);

  // Tex

  TLatex *TexMJ = new TLatex(0.92, 0.12, "M_{J} [GeV]");
  TexMJ->SetNDC();
  TexMJ->SetTextSize(0.18);
  TexMJ->SetTextFont(42);
//  TexMJ->SetTextAlign(32);

  TLatex *TexCMS = new TLatex(0.08,0.885,"CMS");
  TexCMS->SetNDC();
  TexCMS->SetTextSize(0.09);
  TexCMS->SetLineWidth(2);

  TLatex* Texlumi = new TLatex(0.92, 0.92, "138 fb^{-1} (13 TeV)");
  Texlumi->SetNDC();
  Texlumi->SetTextAlign(32);
  Texlumi->SetTextFont(42);
  Texlumi->SetTextSize(0.09);

  TLatex* TexCR = new TLatex(0.408, 0.68, "Control Region");
  TexCR->SetNDC();
  TexCR->SetTextAlign(32);
  TexCR->SetTextFont(42);
  TexCR->SetTextSize(0.065);
  TLatex* TexSR = new TLatex(0.825, 0.68, "Signal Region");
  TexSR->SetNDC();
  TexSR->SetTextAlign(32);
  TexSR->SetTextFont(42);
  TexSR->SetTextSize(0.065);

  TLatex* TexNjets0 = new TLatex(0.23, 0.58, "N_{jet} = 4-5");
  TexNjets0->SetNDC();
  TexNjets0->SetTextAlign(32);
  TexNjets0->SetTextFont(42);
  TexNjets0->SetTextSize(0.06);
  TLatex* TexNjets1 = new TLatex(0.44, 0.58, "N_{jet} = 6-7");
  TexNjets1->SetNDC();
  TexNjets1->SetTextAlign(32);
  TexNjets1->SetTextFont(42);
  TexNjets1->SetTextSize(0.06);
  TLatex* TexNjets2 = new TLatex(0.584, 0.58, "N_{jet} #geq 8");
  TexNjets2->SetNDC();
  TexNjets2->SetTextAlign(32);
  TexNjets2->SetTextFont(42);
  TexNjets2->SetTextSize(0.06);
  TLatex* TexNjets3 = new TLatex(0.710, 0.58, "N_{jet} = 6-7");
  TexNjets3->SetNDC();
  TexNjets3->SetTextAlign(32);
  TexNjets3->SetTextFont(42);
  TexNjets3->SetTextSize(0.06);
  TLatex* TexNjets4 = new TLatex(0.854, 0.58, "N_{jet} #geq 8");
  TexNjets4->SetNDC();
  TexNjets4->SetTextAlign(32);
  TexNjets4->SetTextFont(42);
  TexNjets4->SetTextSize(0.06);

  TLatex* TexNb0 = new TLatex(0.131, 0.48, "N_{b} = 0");
  TexNb0->SetNDC();
  TexNb0->SetTextAlign(32);
  TexNb0->SetTextFont(42);
  TexNb0->SetTextSize(0.06);
  TLatex* TexNb1 = new TLatex(0.189, 0.48, "N_{b} = 1");
  TexNb1->SetNDC();
  TexNb1->SetTextAlign(32);
  TexNb1->SetTextFont(42);
  TexNb1->SetTextSize(0.06);
  TLatex* TexNb2 = new TLatex(0.250, 0.48, "N_{b} = 2");
  TexNb2->SetNDC();
  TexNb2->SetTextAlign(32);
  TexNb2->SetTextFont(42);
  TexNb2->SetTextSize(0.06);
  TLatex* TexNb3 = new TLatex(0.311, 0.48, "N_{b} #geq 3");
  TexNb3->SetNDC();
  TexNb3->SetTextAlign(32);
  TexNb3->SetTextFont(42);
  TexNb3->SetTextSize(0.06);
  TLatex* TexNb4 = new TLatex(0.371, 0.48, "N_{b} = 0");
  TexNb4->SetNDC();
  TexNb4->SetTextAlign(32);
  TexNb4->SetTextFont(42);
  TexNb4->SetTextSize(0.06);
  TLatex* TexNb5 = new TLatex(0.429, 0.48, "N_{b} = 1");
  TexNb5->SetNDC();
  TexNb5->SetTextAlign(32);
  TexNb5->SetTextFont(42);
  TexNb5->SetTextSize(0.06);
  TLatex* TexNb6 = new TLatex(0.490, 0.48, "N_{b} = 2");
  TexNb6->SetNDC();
  TexNb6->SetTextAlign(32);
  TexNb6->SetTextFont(42);
  TexNb6->SetTextSize(0.06);
  TLatex* TexNb7 = new TLatex(0.551, 0.48, "N_{b} = 0");
  TexNb7->SetNDC();
  TexNb7->SetTextAlign(32);
  TexNb7->SetTextFont(42);
  TexNb7->SetTextSize(0.06);
  TLatex* TexNb8 = new TLatex(0.609, 0.48, "N_{b} = 1");
  TexNb8->SetNDC();
  TexNb8->SetTextAlign(32);
  TexNb8->SetTextFont(42);
  TexNb8->SetTextSize(0.06);
  TLatex* TexNb9 = new TLatex(0.671, 0.48, "N_{b} = 3");
  TexNb9->SetNDC();
  TexNb9->SetTextAlign(32);
  TexNb9->SetTextFont(42);
  TexNb9->SetTextSize(0.06);
  TLatex* TexNb10 = new TLatex(0.73, 0.48, "N_{b} #geq 4");
  TexNb10->SetNDC();
  TexNb10->SetTextAlign(32);
  TexNb10->SetTextFont(42);
  TexNb10->SetTextSize(0.06);
  TLatex* TexNb11 = new TLatex(0.790, 0.48, "N_{b} = 2");
  TexNb11->SetNDC();
  TexNb11->SetTextAlign(32);
  TexNb11->SetTextFont(42);
  TexNb11->SetTextSize(0.06);
  TLatex* TexNb12 = new TLatex(0.851, 0.48, "N_{b} = 3");
  TexNb12->SetNDC();
  TexNb12->SetTextAlign(32);
  TexNb12->SetTextFont(42);
  TexNb12->SetTextSize(0.06);
  TLatex* TexNb13 = new TLatex(0.911, 0.48, "N_{b} #geq 4");
  TexNb13->SetNDC();
  TexNb13->SetTextAlign(32);
  TexNb13->SetTextFont(42);
  TexNb13->SetTextSize(0.06);


  // TLine
  TLine *line0 = new TLine(3, 0., 3, h_combine_data->GetMaximum()*0.00005);
  TLine *line1 = new TLine(6, 0., 6, h_combine_data->GetMaximum()*0.00005);
  TLine *line2 = new TLine(9, 0., 9, h_combine_data->GetMaximum()*0.00005);
  TLine *line3 = new TLine(12, 0., 12, h_combine_data->GetMaximum()*0.002);
  TLine *line4 = new TLine(15, 0., 15, h_combine_data->GetMaximum()*0.00005);
  TLine *line5 = new TLine(18, 0., 18, h_combine_data->GetMaximum()*0.00005);
  TLine *line6 = new TLine(21, 0., 21, h_combine_data->GetMaximum()*0.002);
  TLine *line7 = new TLine(24, 0., 24, h_combine_data->GetMaximum()*0.00005);
  TLine *line8 = new TLine(27, 0., 27, h_combine_data->GetMaximum()*0.02);
  TLine *line9 = new TLine(30, 0., 30, h_combine_data->GetMaximum()*0.00005);
  TLine *line10 = new TLine(33, 0., 33, h_combine_data->GetMaximum()*0.001);
  TLine *line11 = new TLine(36, 0., 36, h_combine_data->GetMaximum()*0.00005);
  TLine *line12 = new TLine(39, 0., 39, h_combine_data->GetMaximum()*0.00005);

  gStyle->SetLineStyleString(11,"15 5");
  line0->SetLineColor(kBlack); line0->SetLineWidth(1); line0->SetLineStyle(11);
  line1->SetLineColor(kBlack); line1->SetLineWidth(1); line1->SetLineStyle(11);
  line2->SetLineColor(kBlack); line2->SetLineWidth(1); line2->SetLineStyle(11);
  line3->SetLineColor(kBlack); line3->SetLineWidth(1); line3->SetLineStyle(11);
  line4->SetLineColor(kBlack); line4->SetLineWidth(1); line4->SetLineStyle(11);
  line5->SetLineColor(kBlack); line5->SetLineWidth(1); line5->SetLineStyle(11);
  line6->SetLineColor(kBlack); line6->SetLineWidth(1); line6->SetLineStyle(11);
  line7->SetLineColor(kBlack); line7->SetLineWidth(1); line7->SetLineStyle(11);
  line8->SetLineColor(kBlack); line8->SetLineWidth(1); line8->SetLineStyle(11);
  line9->SetLineColor(kBlack); line9->SetLineWidth(1); line9->SetLineStyle(11);
  line10->SetLineColor(kBlack); line10->SetLineWidth(1); line10->SetLineStyle(11);
  line11->SetLineColor(kBlack); line11->SetLineWidth(1); line11->SetLineStyle(11);
  line12->SetLineColor(kBlack); line12->SetLineWidth(1); line12->SetLineStyle(11);

  TLine *b_line0 = new TLine(3, 0.4, 3, 1.6);
  TLine *b_line1 = new TLine(6, 0.4, 6, 1.6);
  TLine *b_line2 = new TLine(9, 0.4, 9, 1.6);
  TLine *b_line3 = new TLine(12, 0.4, 12, 1.6);
  TLine *b_line4 = new TLine(15, 0.4, 15, 1.6);
  TLine *b_line5 = new TLine(18, 0.4, 18, 1.6);
  TLine *b_line6 = new TLine(21, 0.4, 21, 1.6);
  TLine *b_line7 = new TLine(24, 0.4, 24, 1.6);
  TLine *b_line8 = new TLine(27, 0.4, 27, 1.6);
  TLine *b_line9 = new TLine(30, 0.4, 30, 1.6);
  TLine *b_line10 = new TLine(33, 0.4, 33, 1.6);
  TLine *b_line11 = new TLine(36, 0.4, 36, 1.6);
  TLine *b_line12 = new TLine(39, 0.4, 39, 1.6);

  b_line0->SetLineColor(kBlack); b_line0->SetLineWidth(1); b_line0->SetLineStyle(11);
  b_line1->SetLineColor(kBlack); b_line1->SetLineWidth(1); b_line1->SetLineStyle(11);
  b_line2->SetLineColor(kBlack); b_line2->SetLineWidth(1); b_line2->SetLineStyle(11);
  b_line3->SetLineColor(kBlack); b_line3->SetLineWidth(1); b_line3->SetLineStyle(11);
  b_line4->SetLineColor(kBlack); b_line4->SetLineWidth(1); b_line4->SetLineStyle(11);
  b_line5->SetLineColor(kBlack); b_line5->SetLineWidth(1); b_line5->SetLineStyle(11);
  b_line6->SetLineColor(kBlack); b_line6->SetLineWidth(1); b_line6->SetLineStyle(11);
  b_line7->SetLineColor(kBlack); b_line7->SetLineWidth(1); b_line7->SetLineStyle(11);
  b_line8->SetLineColor(kBlack); b_line8->SetLineWidth(1); b_line8->SetLineStyle(11);
  b_line9->SetLineColor(kBlack); b_line9->SetLineWidth(1); b_line9->SetLineStyle(11);
  b_line10->SetLineColor(kBlack); b_line10->SetLineWidth(1); b_line10->SetLineStyle(11);
  b_line11->SetLineColor(kBlack); b_line11->SetLineWidth(1); b_line11->SetLineStyle(11);
  b_line12->SetLineColor(kBlack); b_line12->SetLineWidth(1); b_line12->SetLineStyle(11);

  // Legend
  TLegend* leg = new TLegend(0.085, 0.75, 0.911, 0.80);
  leg->SetTextAlign(12);
  leg->SetTextFont(42);
  leg->SetNColumns(8);
  leg->SetTextSize(0.060);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h_combine_data, "Data ", "elp");
  leg->AddEntry(h_combine_qcd, "QCD multijet ", "f");
  leg->AddEntry(h_combine_ttbar, "t#bar{t} ", "f");
  leg->AddEntry(h_combine_wjets, "W+jets ", "f");
  leg->AddEntry(h_combine_other, "Other ", "f");
  leg->AddEntry(h_combine_sig1200, "m_{#tilde{g}} = 1200 GeV#times0.01 ", "l");
  leg->AddEntry(h_combine_sig1800, "m_{#tilde{g}} = 1800 GeV ", "l");
  leg->AddEntry(h_combine_err, "Post-fit uncertainty", "f");

  gStyle->SetLineScalePS(1);
  // Draw
  TPad *tpad(NULL), *bpad(NULL);
  TCanvas* c_combine = new TCanvas("c_combine","c_combine", 3000, 1200);
  //TCanvas* c_combine = new TCanvas("c_combine","c_combine", 6000, 3000);
  c_combine->cd();
    // tpad
  tpad = new TPad("tpad", "tpad", 0., 0.3, 1., 1.);
  tpad->SetLeftMargin(0.08); tpad->SetRightMargin(0.08); tpad->SetBottomMargin(0.02); tpad->SetTopMargin(0.15);
  tpad->Draw();
  tpad->cd(); tpad->cd()->SetLogy(1);
  h_combine_data->Draw("EP");
  st_combine->Draw("same hist");
  h_combine_data->Draw("same EP");
  h_combine_sig1200->Draw("same hist");
  h_combine_sig1800->Draw("same hist");
  h_combine_err->Draw("same E2");
  TexCMS->Draw();
  Texlumi->Draw();
  line0->Draw("same"); line1->Draw("same"); line2->Draw("same"); line3->Draw("same"); line4->Draw("same");
  line5->Draw("same"); line6->Draw("same"); line7->Draw("same"); line8->Draw("same");
  line9->Draw("same"); line10->Draw("same"); line11->Draw("same"); line12->Draw("same");
  TexCR->Draw(); TexSR->Draw();
  TexNjets0->Draw(); TexNjets1->Draw(); TexNjets2->Draw(); TexNjets3->Draw(); TexNjets4->Draw();
  TexNb0->Draw(); TexNb1->Draw(); TexNb2->Draw(); TexNb3->Draw(); TexNb4->Draw();
  TexNb5->Draw(); TexNb6->Draw(); TexNb7->Draw(); TexNb8->Draw(); TexNb9->Draw();
  TexNb10->Draw(); TexNb11->Draw(); TexNb12->Draw(); TexNb13->Draw();
  leg->Draw();
  gPad->RedrawAxis();

    // bpad
  c_combine->cd();
  bpad = new TPad("bpad", "bpad", 0., 0., 1., 0.305);
  bpad->SetLeftMargin(0.08); bpad->SetRightMargin(0.08);
  bpad->SetTopMargin(0.); bpad->SetBottomMargin(0.5); bpad->SetFillStyle(4000);
  bpad->Draw(); bpad->cd();
  h_combine_ratio->Draw("e");
  h_combine_ratio_postfit_err->Draw("e2 same");
  b_line0->Draw("same"); b_line1->Draw("same"); b_line2->Draw("same"); b_line3->Draw("same"); b_line4->Draw("same");
  b_line5->Draw("same"); b_line6->Draw("same"); b_line7->Draw("same"); b_line8->Draw("same");
  b_line9->Draw("same"); b_line10->Draw("same"); b_line11->Draw("same"); b_line12->Draw("same");
  TexMJ->Draw();
  h_combine_ratio->GetXaxis()->LabelsOption("v");
  c_combine->Modified();
  c_combine->Update();
  c_combine->Print("plots/test.pdf");
  c_combine->Print("plots/test.png");

 
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

  float lumi=138;
  TString lumilabel = TString::Format("%d", int(lumi))+" fb^{-1}, 13 TeV";
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
