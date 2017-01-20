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

//#include "tdrstyle.C"

using namespace std;

float AddInQuad(float a, float b);
void printYieldBin(int nb, float data, float qcd, float ttbar, float wjets, float other, float sig);
void printYieldBin(int nb, float data, 
                   float qcd, float ttbar, float wjets, float other, float sig, 
                   float qcd_err, float ttbar_err, float wjets_err, float other_err);
void printYieldBin(int nb, float data, 
                   float qcd, float ttbar, float wjets, float other, float sig, 
                   float qcd_err, float ttbar_err, float wjets_err, float other_err, float allbkg_err);
void h1cosmetic(TH1D* &h1, char* title, int linecolor, int linewidth, int fillcolor, TString var);
TH1D* changeHistogram(TH1D* h);

int main()
{

  //setTDRStyle();
  gROOT->ForceStyle(); 

  // variation file 
  TFile* infile  = TFile::Open("variations/11jan2017/12p9/sum_rescaled_control.root", "READ");
  
  // bin definition
  std::vector<std::string> binname;
  std::vector<int> binnumber;
  binname = {"nlep0_nj45_lowmj", "nlep0_nj67_lowmj", "nlep1_nj45_lowmj",
  		     "nlep0_nj45_highmj", "nlep0_nj67_highmj", "nlep1_nj45_highmj",
  		     "nlep0_nj10_lowmj", "nlep1_nj67_lowmj", "nlep1_nj8_lowmj", "nlep0_nj10_highmj",
  		     "nlep1_nj67_highmj", "nlep1_nj8_highmj", "nlep0_nj89_lowmj", "nlep0_nj89_highmj",
  		     "nlep0_nj89_vhighmj", "nlep0_nj10_vhighmj", "nlep1_nj67_vhighmj", "nlep1_nj8_vhighmj"
          };
  binnumber = {0,1,2,
               3,4,5,
               10,11,12,13,
               14,15,16,17,
               18,19,20,21};
  
  // for yield table  
  float data[22][5], qcd[22][5], ttbar[22][5], wjets[22][5], other[22][5], sig1500[22][5];//, sig1700[22][5]; 
  float err[5][22][4]; // first index : qcd, ttbar, wjets, other, all bkg
  
  // 
  // Get prefit uncertainty 
  // 
  // - loop over all variations and add them in quadrature
  // - errors are fractional: needs to be muptiplied by central value in the end
  // - error is caculcated with average of up and down variations: (up-down)/2/central
  //
  cout << "Get the prefit Uncertatinty " << endl;
  for(int ibin=0; ibin<22; ibin++)
  {
      for(int inb=0; inb<4; inb++)
      {
          data[ibin][inb] = 0;
          qcd[ibin][inb] = 0;
          ttbar[ibin][inb] = 0;
          wjets[ibin][inb] = 0;
          other[ibin][inb] = 0;
          sig1500[ibin][inb] = 0;
          //sig1700[ibin][inb] = 0;
          err[0][ibin][inb] = 0;
          err[1][ibin][inb] = 0;
          err[2][ibin][inb] = 0;
          err[3][ibin][inb] = 0;
          err[4][ibin][inb] = 0;
      }
  }

  // loop over bins in the variation file
  for(unsigned int i=0; i<binname.size(); i++) {   
      int ibin = binnumber.at(i);
        
      if(ibin>=6 && ibin<=9) continue; 
      if(ibin!=21) continue; 

      // Two categrories of systemtatics 
      // - correlated across processes
      // - uncorrelated across processes
      std::vector<std::string> syst_correl={"btag_bc","btag_udsg","gs45","gs67","gs89","gs10Inf","lep_eff","jes","jer"};
      std::vector<std::string> syst_uncorrel={"qcd_flavor","qcd_mur", "qcd_muf", "qcd_murf",
                                              "ttbar_mur", "ttbar_muf", "ttbar_murf",
                                              "wjets_mur", "wjets_muf", "wjets_murf",
                                              "other_mur", "other_muf", "other_murf"};

      // loop over correlated systs 
      for(unsigned int icorrel=0; icorrel<syst_correl.size(); icorrel++) 
      { 
          for(int inb=1; inb<5; inb++)
          {
              float central_allbkg=0; 
              float up_allbkg=0; 
              float down_allbkg=0; 
              for(int iproc=0; iproc<4; iproc++)
              {
                  std::string process;
                  if(iproc==0)  process = "qcd";
                  if(iproc==1)  process = "ttbar";
                  if(iproc==2)  process = "wjets";
                  if(iproc==3)  process = "other";

                  float central;
                  float up, down;

                  if(infile->Get(Form("bin%i/%s", ibin, process.c_str()))==0x0) continue; 

                  central = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s", ibin, process.c_str()))))->GetBinContent(inb+1);
                  up = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_%sUp", ibin, process.c_str(),syst_correl.at(icorrel).c_str()))))->GetBinContent(inb+1);
                  down = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_%sDown", ibin, process.c_str(),syst_correl.at(icorrel).c_str()))))->GetBinContent(inb+1);
                  err[iproc][ibin][inb-1] = AddInQuad(err[iproc][ibin][inb-1],TMath::Abs(up-down)/2/central);  
                  central_allbkg    = central_allbkg + central;
                  up_allbkg         = up_allbkg + up;
                  down_allbkg       = down_allbkg + down;
              }
              err[4][ibin][inb-1] = AddInQuad(err[4][ibin][inb-1],TMath::Abs(up_allbkg-down_allbkg)/2/central_allbkg);  
          }
      }

     // pdf uncertainties 

     // loop over uncorrelated systs
      for(unsigned int iuncorrel=0; iuncorrel<syst_uncorrel.size(); iuncorrel++) 
      { 
          for(int inb=1; inb<5; inb++)
          {
              float central_allbkg=0; 
              float up_allbkg=0; 
              float down_allbkg=0; 
              for(int iproc=0; iproc<4; iproc++)
              {
                  std::string process;
                  if(iproc==0)  process = "qcd";
                  if(iproc==1)  process = "ttbar";
                  if(iproc==2)  process = "wjets";
                  if(iproc==3)  process = "other";

                  float central;
                  float up, down;

                  if(infile->Get(Form("bin%i/%s", ibin, process.c_str()))==0x0) continue;
                  central = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s", ibin, process.c_str()))))->GetBinContent(inb+1);
                  up = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_%sUp", ibin, process.c_str(),syst_uncorrel.at(iuncorrel).c_str()))))->GetBinContent(inb+1);
                  down = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_%sDown", ibin, process.c_str(),syst_uncorrel.at(iuncorrel).c_str()))))->GetBinContent(inb+1);
                  err[iproc][ibin][inb-1] = AddInQuad(err[iproc][ibin][inb-1],TMath::Abs(up-down)/2/central);  
                  
                  central_allbkg    = central_allbkg + central;
                  up_allbkg         = AddInQuad(up_allbkg, up);
                  down_allbkg       = AddInQuad(down_allbkg, down);
              }
              err[4][ibin][inb-1] = AddInQuad(err[4][ibin][inb-1],TMath::Abs(up_allbkg-down_allbkg)/2/central_allbkg);  
          }
      }

      // Stats
      for(int inb=1; inb<5; inb++)
      {
          float central_allbkg=0; 
          float up_allbkg=0; 
          float down_allbkg=0; 
          for(int iproc=0; iproc<4; iproc++)
          {
              std::string process;
              if(iproc==0)  process = "qcd";
              if(iproc==1)  process = "ttbar";
              if(iproc==2)  process = "wjets";
              if(iproc==3)  process = "other";
                  
              if(infile->Get(Form("bin%i/%s", ibin, process.c_str()))==0x0) continue;

              // Stats
              if(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb))!=0x0)
              {
                  float central;
                  float up, down; 

                  central = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s", ibin, process.c_str()))))->GetBinContent(inb+1);
                  up = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb))))->GetBinContent(inb+1);
                  down = (static_cast<TH1D*>(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iDown", ibin, process.c_str(), process.c_str(),ibin,inb))))->GetBinContent(inb+1);
                  err[iproc][ibin][inb-1] = AddInQuad(err[iproc][ibin][inb-1],TMath::Abs(up-down)/2/central);

                  central_allbkg    = central_allbkg + central;
                  up_allbkg         = AddInQuad(up_allbkg, up);
                  down_allbkg       = AddInQuad(down_allbkg, down);
              }
          }
          err[4][ibin][inb-1] = AddInQuad(err[4][ibin][inb-1],TMath::Abs(up_allbkg-down_allbkg)/2/central_allbkg);  
      }
  }

  //
  // Draw plots
  //
  for(unsigned int i=0; i<binname.size(); i++) { 
   
    TCanvas *c;
    TPad *pad_stack;
    TPad *pad_ratio;
    
    int ibin = binnumber.at(i);
    cout << "...... BIN: " << ibin << " :: " << binname[i]<< endl;
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
    
    TH1D *h1_data; 
    TH1D *h1_qcd;     
    TH1D *h1_ttbar;   
    TH1D *h1_wjets;   
    TH1D *h1_other;   
    TH1D *h1_signal;  

    h1_data     =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/data_obs", ibin)))));
    h1_qcd      =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/qcd", ibin)))));
    h1_ttbar    =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/ttbar", ibin)))));
    h1_wjets    =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/wjets", ibin)))));
    h1_other    =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/other", ibin))))); 
    h1_signal   =  changeHistogram((static_cast<TH1D*>(infile->Get(Form("bin%i/signal_M1500", ibin))))); 
    float sf = h1_data->Integral()/(h1_qcd->Integral()+h1_ttbar->Integral()
                                   +h1_wjets->Integral()+h1_other->Integral());
    h1_qcd->Scale(sf);
    h1_ttbar->Scale(sf);
    h1_wjets->Scale(sf);
    h1_other->Scale(sf);

    //fill yields 
    for(int inb=1; inb<5; inb++)
    {
        data[ibin][inb-1]  = h1_data->GetBinContent(inb);
        qcd[ibin][inb-1]   = h1_qcd->GetBinContent(inb);
        ttbar[ibin][inb-1] = h1_ttbar->GetBinContent(inb);
        wjets[ibin][inb-1] = h1_wjets->GetBinContent(inb);
        other[ibin][inb-1] = h1_other->GetBinContent(inb); 
        sig1500[ibin][inb-1] = h1_signal->GetBinContent(inb); 
        //sig1700[ibin][inb-1] = h1_signal->GetBinContent(inb)*0.4; 
    }

    // cosmetics
    h1cosmetic(h1_data,          Form("Data bin%i", ibin),               kBlack, 2, 1,          "N_{b}");
    h1cosmetic(h1_qcd,           Form("QCD bin%i", ibin),                kBlack, 2, kYellow-7,  "N_{b}");
    h1cosmetic(h1_ttbar,         Form("ttbar bin%i", ibin),              kBlack, 2, kAzure+7,   "N_{b}");
    h1cosmetic(h1_wjets,         Form("Wjets bin%i", ibin),              kBlack, 2, kGreen+2,   "N_{b}");
    h1cosmetic(h1_other,         Form("other bin%i", ibin),              kBlack, 2, kGray+1,    "N_{b}");
    h1cosmetic(h1_signal,        Form("signal bin%i", ibin),             kRed,   3, 0,          "N_{b}");

    // uncertainty band 
    TH1D *h1_mc = static_cast<TH1D*>(h1_qcd->Clone("h1_qcd"));
    h1_mc->Add(h1_ttbar);
    h1_mc->Add(h1_wjets);
    h1_mc->Add(h1_other);
    for(int inb=1; inb<5; inb++)  h1_mc->SetBinError(inb,err[4][ibin][inb-1]*h1_mc->GetBinContent(inb));
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
    //st->SetMaximum(h1_data->GetMaximum()*2);
    st->SetMinimum(0.1);
    st->Draw("hist");
    //h1_mc->Draw("e2 same");
    h1_data->Draw("e same"); 
    //if(plotSPlusB) h1_signal->Draw("hist same"); 
    st->GetYaxis()->SetTitle("Events");
    st->GetXaxis()->SetLabelSize(0.0);
    st->GetXaxis()->SetTitle("N_{b}");
    st->GetYaxis()->SetLabelSize(0.06);
    
    h1_signal->Draw("hist same"); 
    
    // legend
    TLegend *leg = new TLegend(0.55, 0.45, 0.85, 0.87);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h1_data,  "Data",     "ELP");
    leg->AddEntry(h1_qcd,   "QCD",      "F");
    leg->AddEntry(h1_ttbar, "t#bar{t}", "F");
    leg->AddEntry(h1_wjets, "W+jets",   "F");
    leg->AddEntry(h1_other, "Other",    "F");
    leg->AddEntry(h1_signal, Form("Expected m_{#tilde{g}}=%i GeV",1500), "L");
    //leg->AddEntry(h1_mc,    "Pre-fit uncertainty",    "F");
    leg->Draw();

    // CMS and lumi labels
    float textSize = 0.05;
    TLatex *TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%.1f fb^{-1} (13 TeV)}", 12.9));
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
    //textSize=textSize-0.01;
    TLatex *TexNlep, *TexNjets, *TexMJ;
    TString binname_tstr = binname[i]; 
    TexNlep = new TLatex(0.25,0.80,"N_{lep} = 1");
    if(binname_tstr.Contains("nlep0"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 0");
    TexNlep->SetNDC();
    TexNlep->SetTextSize(textSize);
    //TexNlep->SetLineWidth(2);
    TexNjets = new TLatex(0.25,0.73,"4 #leq N_{jet} #leq 5");
    if(binname_tstr.Contains("nj67_"))   TexNjets = new TLatex(0.25,0.73,"6 #leq N_{jet} #leq 7");
    if(binname_tstr.Contains("nj89_"))   TexNjets = new TLatex(0.25,0.73,"8 #leq N_{jet} #leq 9");
    if(binname_tstr.Contains("nj8_"))    TexNjets = new TLatex(0.25,0.73,"N_{jet} #geq 8");
    if(binname_tstr.Contains("nj10_"))   TexNjets = new TLatex(0.25,0.73,"N_{jet} #geq 10");
    TexNjets->SetNDC();
    TexNjets->SetTextSize(textSize);
    //TexNjets->SetLineWidth(2);
    TexMJ = new TLatex(0.25,0.66,"500 < M_{J} < 800 GeV");
    if(binname_tstr.Contains("vhighmj"))   TexMJ = new TLatex(0.25,0.66,"M_{J} > 1000 GeV");
    else if(binname_tstr.Contains("highmj"))
    {   
        if(binname_tstr.Contains("nlep0_nj45") || 
           binname_tstr.Contains("nlep0_nj67") || 
           binname_tstr.Contains("nlep1_nj45"))
            TexMJ = new TLatex(0.25,0.66,"M_{J} > 800 GeV");   
        else 
            TexMJ = new TLatex(0.25,0.66,"800 < M_{J} < 1000 GeV");   
    }
    TexMJ->SetNDC();
    TexMJ->SetTextSize(textSize);
    //TexMJ->SetLineWidth(2);

    TexNlep->Draw("same");
    TexNjets->Draw("same");
    TexMJ->Draw("same");
    
    c->cd();
    pad_ratio = new TPad(Form("p_pull_%i",i), Form("p_pull_%i",i), 0.0, 0.0, 1.0, 0.3);
    pad_ratio->SetLeftMargin(0.2);
    pad_ratio->Draw();
    pad_ratio->cd();
    pad_ratio->SetTopMargin(0.04);
    pad_ratio->SetRightMargin(0.1);
    pad_ratio->SetBottomMargin(0.4);
   

    TH1D *h1_ratio = static_cast<TH1D*>(h1_data->Clone("h1_ratio")); 
    h1_ratio->Divide(h1_mc); 
    h1_ratio->SetLabelSize(0.15,"XY");
    h1_ratio->GetXaxis()->SetLabelSize(0.25);
    h1_ratio->SetTitleSize(0.16,"XY");
    h1_ratio->SetTitleOffset(1.0);
    h1_ratio->GetYaxis()->SetNdivisions(/*3,false*/706);
    h1_ratio->GetXaxis()->SetNdivisions(5,true);
    h1_ratio->SetMinimum(0.1);
    h1_ratio->SetMaximum(1.9);
    h1_ratio->GetYaxis()->SetTitle("Data/Fit");
    h1_ratio->GetYaxis()->SetTitleOffset(0.4);
    h1_ratio->Draw("e0");  
    
    TH1D *h1_ratio_err = static_cast<TH1D*>(h1_ratio->Clone("h1_ratio_err"));  
    for(int inb=1; inb<5; inb++)  
    { 
        h1_ratio_err->SetBinContent(inb, 1);
        h1_ratio_err->SetBinError(inb, err[4][ibin][inb-1]); 
        cout << inb << " :: " 
             <<  Form("%.2f",err[0][ibin][inb-1]) <<  "\t"  // FIXME
             <<  Form("%.2f",err[1][ibin][inb-1]) <<  "\t"  // FIXME
             <<  Form("%.2f",err[2][ibin][inb-1]) <<  "\t"  // FIXME
             <<  Form("%.2f",err[3][ibin][inb-1]) <<  "\t"  // FIXME
             <<  Form("%.2f",err[4][ibin][inb-1]) << endl;  // FIXME
    }
    h1_ratio_err->SetMarkerSize(0);
    h1_ratio_err->SetFillColor(kBlack);
    h1_ratio_err->SetLineColor(kBlack);
    h1_ratio_err->SetFillStyle(3354);
    h1_ratio_err->Draw("e2 same");

    TLine *l = new TLine(1,1,5,1);
    l->SetLineStyle(2);
    l->Draw("same");

    c->Print(Form("plots/pre_%s.jpeg", binname[i].c_str()));
    c->Print(Form("plots/pre_%s.pdf", binname[i].c_str()));
    c->Print(Form("plots/pre_%s.png", binname[i].c_str()));
    c->Print(Form("plots/pre_%s.root", binname[i].c_str()));
    
    if(1)//debug 
    {
        for(int inb=1; inb<5; inb++)
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
    delete h1_signal; 
  }
  
  // -------------------------------------------------------------------------------
  // ------------------- Print table  ----------------------------------------------
  // -------------------------------------------------------------------------------
  
  TString binLatex[18] = {
      // control regions
      "4\\leq N_{jets}\\leq5, 500<M_{J}<800~GeV",
      "6\\leq N_{jets}\\leq7, 500<M_{J}<800~GeV",
      "4\\leq N_{jets}\\leq5, 500<M_{J}<800~GeV",
      "4\\leq N_{jets}\\leq5, M_{J}>800~GeV",
      "6\\leq N_{jets}\\leq7, M_{J}>800~GeV",
      "4\\leq N_{jets}\\leq5, M_{J}>800~GeV",
      // low M_{J} control regions
      "4\\leq N_{jets}\\leq5,300<M_{J}<500~GeV",  // 6
      "6\\leq N_{jets}\\leq7,300<M_{J}<500~GeV",
      "8\\leq N_{jets}\\leq9,300<M_{J}<500~GeV",
      "N_{jets}\\geq10,300<M_{J}<500~GeV",
      // signal regions, low M_{J}
      "N_{jets}\\geq10,500<M_{J}<800~GeV",       // 10
      "6\\leq N_{jets}\\leq7,500<M_{J}<800~GeV",
      "N_{jets}\\geq8,500<M_{J}<800~GeV",
      // signal regions, high M_{J}
      "N_{jets}\\geq10,M_{J}>800~GeV",           // 13
      "6\\leq N_{jets}\\leq7,M_{J}>800~GeV",
      "N_{jets}\\geq8,M_{J}>800~GeV",
      //Missing regions
      "8\\leq N_{jets}\\leq9,500<M_{J}<800~GeV",  // 16
      "8\\leq N_{jets}\\leq9,M_{J}>800~GeV"
  }; 

/* // This is for debug 
  int tablebin=0; 
  for(int inb=3; inb<5; inb++) 
    printYieldBin(inb,  
                data[tablebin][inb-1], 
                qcd[tablebin][inb-1], 
                ttbar[tablebin][inb-1], 
                wjets[tablebin][inb-1], 
                other[tablebin][inb-1],
                sig1500[tablebin][inb-1],
                err[0][tablebin][inb-1]*qcd[tablebin][inb-1], 
                err[1][tablebin][inb-1]*ttbar[tablebin][inb-1], 
                err[2][tablebin][inb-1]*wjets[tablebin][inb-1], 
                err[3][tablebin][inb-1]*other[tablebin][inb-1],
                err[4][tablebin][inb-1]*(qcd[tablebin][inb-1]+ttbar[tablebin][inb-1]+wjets[tablebin][inb-1]+other[tablebin][inb-1]));
*/

  // 0-lepton
  int tablebin_0lep[4]={16,17,10,13};
  cout << "\\begin{table}" << endl;
  cout << "\\centering" << endl;
  cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
  cout << "\\hline" << endl;
  cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1500\\GeV$\\\\"  << endl;
  cout << "\\hline\\hline" << endl;

  for(int ibin=0; ibin<4; ibin++) 
  {
    int tablebin=tablebin_0lep[ibin]; 
  cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$} \\\\" << endl;
  cout << "\\hline" << endl;
  for(int inb=1; inb<5; inb++) 
    printYieldBin(inb,  
                data[tablebin][inb-1], 
                qcd[tablebin][inb-1], 
                ttbar[tablebin][inb-1], 
                wjets[tablebin][inb-1], 
                other[tablebin][inb-1],
                sig1500[tablebin][inb-1],
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
  
  // 1-lepton
  int tablebin_1lep[4]={11,14,12,15};
  cout << "\\begin{table}" << endl;
  cout << "\\centering" << endl;
  cout << "\\begin{tabular}[tbp!]{ l | c  c  c  c | c |  c | c  }" << endl;
  cout << "\\hline" << endl;
  cout << "$N_{b}$ & QCD & $t\\bar{t}$ & W+jets & Other & All bkg. & Data & $m_{\\tilde{g}}=1500\\GeV$\\\\"  << endl;
  cout << "\\hline\\hline" << endl;

  for(int ibin=0; ibin<4; ibin++) 
  {
    int tablebin=tablebin_1lep[ibin]; 
  cout <<"\\multicolumn{8}{c}{$" <<  binLatex[tablebin].Data() << "$}\\\\" << endl;
  cout << "\\hline" << endl;
  for(int inb=1; inb<5; inb++) 
    printYieldBin(inb,  
                data[tablebin][inb-1], 
                qcd[tablebin][inb-1], 
                ttbar[tablebin][inb-1], 
                wjets[tablebin][inb-1], 
                other[tablebin][inb-1],
                sig1500[tablebin][inb-1],
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

  return 0;
}

void printYieldBin(int nb, float data, float qcd, float ttbar, float wjets, float other, float sig)
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

void printYieldBin(int nb, float data, float qcd, float ttbar, float wjets, float other, float sig, 
                                    float qcd_err, float ttbar_err, float wjets_err, float other_err)
{ 
    if(qcd==0) qcd_err=0;
    if(ttbar==0) ttbar_err=0;
    if(wjets==0) wjets_err=0;
    if(other==0) other_err=0;
    
    float tot_err = TMath::Sqrt(qcd_err*qcd_err+ttbar_err*ttbar_err+wjets_err*wjets_err+other_err*other_err);
    cout << ((nb==3)?"$3$":"$\\geq 4$") << " & "
        << Form("$%.1f \\pm %.1f$",qcd,qcd_err)  << " & "
        << Form("$%.1f \\pm %.1f$",ttbar,ttbar_err) << " & "
        << Form("$%.1f \\pm %.1f$",wjets,wjets_err) << " & "
        << Form("$%.1f \\pm %.1f$",other,other_err) << " & "
        << Form("$%.1f \\pm %.1f$",qcd+ttbar+wjets+other,tot_err) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
}

void printYieldBin(int nb, float data, float qcd, float ttbar, float wjets, float other, float sig, 
                                    float qcd_err, float ttbar_err, float wjets_err, float other_err, float allbkg_err)
{ 
    if(qcd==0) qcd_err=0;
    if(ttbar==0) ttbar_err=0;
    if(wjets==0) wjets_err=0;
    if(other==0) other_err=0;

    string nbbin; 
    if(nb==1) nbbin="$1$";
    if(nb==2) nbbin="$2$";
    if(nb==3) nbbin="$3$";
    if(nb==4) nbbin="$\\geq 4$";

    cout << nbbin << " & "
        << Form("$%.1f \\pm %.1f$",qcd,qcd_err)  << " & "
        << Form("$%.1f \\pm %.1f$",ttbar,ttbar_err) << " & "
        << Form("$%.1f \\pm %.1f$",wjets,wjets_err) << " & "
        << Form("$%.1f \\pm %.1f$",other,other_err) << " & "
        << Form("$%.1f \\pm %.1f$",qcd+ttbar+wjets+other,allbkg_err) << " & "
        << Form("$%.0f$",data) << " & "
        << Form("$%.1f$",sig) << " \\\\ " << endl;
}

float AddInQuad(float a, float b)
{
    return TMath::Sqrt(a*a+b*b);
} 

void h1cosmetic(TH1D* &h1, char* title, int linecolor=kBlack, int linewidth=1, int fillcolor=0, TString var="")
{
    h1->SetLineColor(linecolor);
    h1->SetLineWidth(linewidth);
    h1->SetFillColor(fillcolor);
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
TH1D* changeHistogram(TH1D* h)
{

    TString name = h->GetName(); 
    TH1D* hist = new TH1D(Form("h_%s", h->GetName()), Form("%s",h->GetName()), 4, 1, 5);
    hist->SetDirectory(0);
        
    hist->SetBinContent(1,h->GetBinContent(2));
    hist->SetBinContent(2,h->GetBinContent(3));
    hist->SetBinContent(3,h->GetBinContent(4));
    hist->SetBinContent(4,h->GetBinContent(5));

    hist->SetStats(0); 
    cout << "1 :: " << hist->GetBinContent(1) << endl; 
    cout << "2 :: " << hist->GetBinContent(2) << endl; 
    cout << "3 :: " << hist->GetBinContent(3) << endl; 
    cout << "4 :: " << hist->GetBinContent(4) << endl;  

    hist->GetXaxis()->SetBinLabel(1,"1");
    hist->GetXaxis()->SetBinLabel(2,"2");
    hist->GetXaxis()->SetBinLabel(3,"3");
    hist->GetXaxis()->SetBinLabel(4,"#geq 4");
    return hist;
}
