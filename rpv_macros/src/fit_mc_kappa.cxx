#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TString.h"
#include "TTree.h"
#include "THStack.h"
#include "TLatex.h"
#include "TF1.h"

using namespace std;

// Define a function with three parameters.
double fitf(double *x,double *par) {
   double fitval;
   return fitval = par[0]*x[0] + par[1];
}

float return_y(float x, float slope, float y_intercept)
{ 
  return slope * x + y_intercept;
}

TString convert_systname(TString systname){
  TString real_systname;
  if(systname=="gs") real_systname="gluon splitting";
  else if(systname=="pileup") real_systname="pileup";
  else if(systname=="btag_bc") real_systname="b,c jet b-tag SF";
  else if(systname=="btag_udsg") real_systname="u,d,s,g jet b-tag SF";
  else if(systname=="jec") real_systname="jet energy scale";
  else if(systname=="jer") real_systname="jet energy resolution";
  else if(systname=="lep_eff") real_systname="lepton efficiency";
  else if(systname=="isr") real_systname="initial state radiation";
  else if(systname=="mur") real_systname="renormalization scale";
  else if(systname=="muf") real_systname="factorization scale";
  else if(systname=="murf") real_systname="renorm. and fact. scale";
  return real_systname;
}

int linecolor(unsigned int isyst){
  int icolor;
  if(isyst==0) icolor=3;
  else if(isyst==1) icolor=6;
  else if(isyst==2) icolor=7;
  else if(isyst==3) icolor=13; //
  else if(isyst==4) icolor=21; //
  else if(isyst==5) icolor=28;
  else if(isyst==6) icolor=38;
  else if(isyst==7) icolor=46;
  else if(isyst==8) icolor=51;
  else if(isyst==9) icolor=87;
  else if(isyst==10) icolor=95;
  return icolor;
}

void set_legend_style(TLegend *l){
  l->SetFillColor(0);
  l->SetLineColor(0);
  l->SetFillStyle(0);   //make the TLegend transparent
  l->SetBorderSize(0);
  l->SetTextFont(42);
  l->SetTextSize(0.03);
}

void drawHeader(){
  TLatex *lat = new TLatex;
  lat->SetTextSize(0.053);
  lat->DrawLatexNDC(0.12, 0.83, "CMS #scale[0.8]{#font[52]{Work In Progress}}");
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.76, 0.83, "35.9 fb^{-1} (13 TeV)");//FIXME
}

int main(int argc, char *argv[]){

  gStyle->SetOptStat(0);
  gStyle->SetLineStyleString(11,"20 10");  // 1 sigma UP systematics  // long dotted line
  gStyle->SetLineStyleString(12,"4 8");   // 1 sigma DOWN systematics // short dotted line

  TString Systematic, year;

  year = argv[1];

  if(argc<1){
    cout << "[Error] Not Enough Arguments! argument \"--help\" may help you" << endl;
    return 1;
  }

  if(Systematic == "--help" || argc<2){
    cout << "" <<endl;
    cout << "./run/fit_mc_kappa.exe [year]" << endl;
    cout << "" <<endl;
    cout << "year: 2016, 2017, 2018" << endl;
    cout << "" << endl;
    return 1;
  }


  vector<TString> syst_list; 
  syst_list = {"murf", "mur", "muf", 
               "jec", "jer", 
               "lep_eff", "pileup", "gs", 
 	       "btag_bc", "btag_udsg"}; 
  if(year == "2016") syst_list.push_back("isr");

  const int nsysts = syst_list.size();
  
  
  //
  // summary plot 
  //
  
  // hists for each syst 
  TH1F *h1_nb_fit_summary_up[nsysts][3], *h2_nb_fit_summary_up[nsysts][3]; 
  TH1F *h1_nb_fit_summary_down[nsysts][3], *h2_nb_fit_summary_down[nsysts][3]; 
  // combined 
  TH1F *h1_nb_fit_combined_up[3], *h2_nb_fit_combined_up[3]; 
  TH1F *h1_nb_fit_combined_down[3], *h2_nb_fit_combined_down[3]; 
  for(unsigned int ihist=0; ihist<3; ihist++)
  { 
    h1_nb_fit_combined_up[ihist]   = new TH1F(Form("h1_nb_fit_combined_up%d", ihist),   
                                              Form("Kappa1 Up, Njets %d", ihist*2+4),    5, -0.5, 4.5);
    h1_nb_fit_combined_down[ihist]   = new TH1F(Form("h1_nb_fit_combined_down%d", ihist),   
                                              Form("Kappa1 Down, Njets %d", ihist*2+4),    5, -0.5, 4.5);
    h2_nb_fit_combined_up[ihist]   = new TH1F(Form("h2_nb_fit_combined_up%d", ihist),   
                                              Form("Kappa2 Up, Njets %d", ihist*2+4),    5, -0.5, 4.5);
    h2_nb_fit_combined_down[ihist]   = new TH1F(Form("h2_nb_fit_combined_down%d", ihist),   
                                              Form("Kappa2 Down, Njets %d", ihist*2+4),    5, -0.5, 4.5);
  } 
  THStack *st1[3], *st2[3];
  for(unsigned int ist; ist<3; ist++) 
  {
    st1[ist] = new THStack(Form("st1_%d", ist), Form("st1_%d", ist));
    st2[ist] = new THStack(Form("st2_%d", ist), Form("st2_%d", ist));
  }

  //
  // Loop over systematics
  //
  for(unsigned int isyst=0; isyst<syst_list.size(); ++isyst)
  {
    // Define input file, histograms, etc
    TFile *f_up, *f_down;
    TH1F *h1_up, *h1_down, *h2_up, *h2_down;
    TH1F *h1_nb_up[3], *h2_nb_up[3]; 
    TH1F *h1_nb_down[3], *h2_nb_down[3]; 
    TH1F *h1_nb_fit_up[3], *h2_nb_fit_up[3]; 
    TH1F *h1_nb_fit_down[3], *h2_nb_fit_down[3]; 
   
    // initialize Nb hists
    for(unsigned int ihist=0; ihist<3; ihist++)
    { 
      h1_nb_up[ihist]   = new TH1F(syst_list[isyst]+"_"+Form("kappa1_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,   syst_list[isyst]+"_"+Form("kappa1_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,    5, -0.5, 4.5);
      h2_nb_up[ihist]   = new TH1F(syst_list[isyst]+"_"+Form("kappa2_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,   syst_list[isyst]+"_"+Form("kappa2_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,    5, -0.5, 4.5);
      h1_nb_down[ihist] = new TH1F(syst_list[isyst]+"_"+Form("kappa1_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year, syst_list[isyst]+"_"+Form("kappa1_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,  5, -0.5, 4.5);
      h2_nb_down[ihist] = new TH1F(syst_list[isyst]+"_"+Form("kappa2_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year, syst_list[isyst]+"_"+Form("kappa2_njet%d", 10*(2*ihist+4)+5+2*ihist)+"_"+year,  5, -0.5, 4.5);
      h1_nb_fit_up[ihist]   = new TH1F(Form("summary_kappa1_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,   Form("summary_kappa1_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,    5, -0.5, 4.5);
      h2_nb_fit_up[ihist]   = new TH1F(Form("summary_kappa2_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,   Form("summary_kappa2_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,    5, -0.5, 4.5);
      h1_nb_fit_down[ihist] = new TH1F(Form("summary_kappa1_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year, Form("summary_kappa1_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,  5, -0.5, 4.5);
      h2_nb_fit_down[ihist] = new TH1F(Form("summary_kappa2_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year, Form("summary_kappa2_njet%d_", 10*(2*ihist+4)+5+2*ihist)+year,  5, -0.5, 4.5);
    }



    //
    // Get up/down summary histograms from input files 
    //
    cout << "plots/kappa/"+year+"/kappa_summary_"+syst_list.at(isyst)+"Up_"+year+".root" << endl;
    cout << "plots/kappa/"+year+"/kappa_summary_"+syst_list.at(isyst)+"Down_"+year+".root" << endl;
    f_up = new TFile("plots/kappa/"+year+"/kappa_summary_"+syst_list.at(isyst)+"Up_"+year+".root");
    f_down = new TFile("plots/kappa/"+year+"/kappa_summary_"+syst_list.at(isyst)+"Down_"+year+".root");
    h1_up   = dynamic_cast<TH1F*>(f_up->Get("h1_1l_summary1"));
    h2_up   = dynamic_cast<TH1F*>(f_up->Get("h1_1l_summary2"));
    h1_down = dynamic_cast<TH1F*>(f_down->Get("h1_1l_summary1"));
    h2_down = dynamic_cast<TH1F*>(f_down->Get("h1_1l_summary2"));

    //
    // Fill Nb histograms from above histograms 
    //
    cout << "Fill Nb histograms ... " << endl; 
    for(unsigned int ihist=0; ihist<3; ihist++)
    {
      // kappa1 up
      cout << "kappa1 up : " << ihist << endl; 
      h1_nb_up[ihist]->SetBinContent(1, h1_up->GetBinContent(25*ihist+8)); 
      h1_nb_up[ihist]->SetBinError(1, h1_up->GetBinError(25*ihist+8)); 
      h1_nb_up[ihist]->SetBinContent(2, h1_up->GetBinContent(25*ihist+10)); 
      h1_nb_up[ihist]->SetBinError(2, h1_up->GetBinError(25*ihist+10)); 
      h1_nb_up[ihist]->SetBinContent(3, h1_up->GetBinContent(25*ihist+12)); 
      h1_nb_up[ihist]->SetBinError(3, h1_up->GetBinError(25*ihist+12)); 
      h1_nb_up[ihist]->SetBinContent(4, h1_up->GetBinContent(25*ihist+14)); 
      h1_nb_up[ihist]->SetBinError(4, h1_up->GetBinError(25*ihist+14)); 
      if(ihist>0) 
      {
        h1_nb_up[ihist]->SetBinContent(5, h1_up->GetBinContent(25*ihist+16)); 
        h1_nb_up[ihist]->SetBinError(5, h1_up->GetBinError(25*ihist+16)); 
      }


      // kappa1 down
      cout << "kappa1 down : " << ihist << endl; 
      h1_nb_down[ihist]->SetBinContent(1, h1_down->GetBinContent(25*ihist+8)); 
      h1_nb_down[ihist]->SetBinError(1, h1_down->GetBinError(25*ihist+8)); 
      h1_nb_down[ihist]->SetBinContent(2, h1_down->GetBinContent(25*ihist+10)); 
      h1_nb_down[ihist]->SetBinError(2, h1_down->GetBinError(25*ihist+10)); 
      h1_nb_down[ihist]->SetBinContent(3, h1_down->GetBinContent(25*ihist+12)); 
      h1_nb_down[ihist]->SetBinError(3, h1_down->GetBinError(25*ihist+12)); 
      h1_nb_down[ihist]->SetBinContent(4, h1_down->GetBinContent(25*ihist+14)); 
      h1_nb_down[ihist]->SetBinError(4, h1_down->GetBinError(25*ihist+14)); 
      if(ihist>0) 
      {
        h1_nb_down[ihist]->SetBinContent(5, h1_down->GetBinContent(25*ihist+16)); 
        h1_nb_down[ihist]->SetBinError(5, h1_down->GetBinError(25*ihist+16)); 
      }

      // kappa2 up
      cout << "kappa2 up : " << ihist << endl; 
      h2_nb_up[ihist]->SetBinContent(1, h2_up->GetBinContent(25*ihist+8)); 
      h2_nb_up[ihist]->SetBinError(1, h2_up->GetBinError(25*ihist+8)); 
      h2_nb_up[ihist]->SetBinContent(2, h2_up->GetBinContent(25*ihist+10)); 
      h2_nb_up[ihist]->SetBinError(2, h2_up->GetBinError(25*ihist+10)); 
      h2_nb_up[ihist]->SetBinContent(3, h2_up->GetBinContent(25*ihist+12)); 
      h2_nb_up[ihist]->SetBinError(3, h2_up->GetBinError(25*ihist+12)); 
      h2_nb_up[ihist]->SetBinContent(4, h2_up->GetBinContent(25*ihist+14)); 
      h2_nb_up[ihist]->SetBinError(4, h2_up->GetBinError(25*ihist+14)); 
      if(ihist>0) 
      {
        h2_nb_up[ihist]->SetBinContent(5, h2_up->GetBinContent(25*ihist+16)); 
        h2_nb_up[ihist]->SetBinError(5, h2_up->GetBinError(25*ihist+16)); 
      }

      // kappa2 down
      cout << "kappa2 down : " << ihist << endl; 
      h2_nb_down[ihist]->SetBinContent(1, h2_down->GetBinContent(25*ihist+8)); 
      h2_nb_down[ihist]->SetBinError(1, h2_down->GetBinError(25*ihist+8)); 
      h2_nb_down[ihist]->SetBinContent(2, h2_down->GetBinContent(25*ihist+10)); 
      h2_nb_down[ihist]->SetBinError(2, h2_down->GetBinError(25*ihist+10)); 
      h2_nb_down[ihist]->SetBinContent(3, h2_down->GetBinContent(25*ihist+12)); 
      h2_nb_down[ihist]->SetBinError(3, h2_down->GetBinError(25*ihist+12)); 
      h2_nb_down[ihist]->SetBinContent(4, h2_down->GetBinContent(25*ihist+14)); 
      h2_nb_down[ihist]->SetBinError(4, h2_down->GetBinError(25*ihist+14)); 
      if(ihist>0) 
      {
        h2_nb_down[ihist]->SetBinContent(5, h2_down->GetBinContent(25*ihist+16)); 
        h2_nb_down[ihist]->SetBinError(5, h2_down->GetBinError(25*ihist+16)); 
      }
    }

    //
    // Draw hists and perform fit
    //
    cout << "Draw canvas" << endl; 
      
    // Define linear fit
    TF1 *func = new TF1("fit",fitf,0,1,2);
    func->SetParameters(0,1);
    func->SetParNames("Slope","y intercept");

    //
    TCanvas *c;
    c = new TCanvas;
    c->Divide(3,2);

    for(unsigned int ihist=0; ihist<3; ++ihist)
    {
      // kappa1
      c->cd(ihist+1);
      c->cd(ihist+1)->SetLeftMargin(0.125);  //0.1 is defalut
    
      if(ihist==0) h1_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+4, ihist+5)+"  "+year);     //Use string() Because there is no definition of operator "+" that takes two char*s.
      else if(ihist==1) h1_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+5, ihist+6)+"  "+year);
      else if(ihist==2) h1_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet}", ihist+6)+"  "+year);
      h1_nb_up[ihist]->GetYaxis()->SetRangeUser(0,1.3);
      h1_nb_up[ihist]->SetLineColor(kRed);
      h1_nb_down[ihist]->SetLineColor(kBlue);
      h1_nb_up[ihist]->GetXaxis()->SetTitle("N_{b}");
      h1_nb_up[ihist]->GetYaxis()->SetTitle("#kappa^{MC}_{1}");
      h1_nb_up[ihist]->GetXaxis()->SetTitleSize(0.05);
      h1_nb_up[ihist]->GetYaxis()->SetTitleSize(0.05);
      h1_nb_up[ihist]->GetXaxis()->SetTitleOffset(0.8);
      h1_nb_up[ihist]->GetYaxis()->SetTitleOffset(1.);
      h1_nb_up[ihist]->GetXaxis()->SetNdivisions(5,true);
      h1_nb_up[ihist]->Draw("hist");  
      h1_nb_down[ihist]->Draw("hist same");  


      h1_nb_up[ihist]->Fit("fit");
      for(unsigned int inb=0; inb<5; inb++){
         h1_nb_fit_up[ihist]->SetBinContent(inb+1, 
             return_y(inb, func->GetParameter(0), func->GetParameter(1))); 
	 cout << func->GetParameter(0) << " 1 : " << func->GetParameter(1) << endl;
	 cout << return_y(inb, func->GetParameter(0), func->GetParameter(1)) << endl;
	 cout << h1_nb_fit_up[ihist]->GetBinContent(inb+1) << endl;
      }
      h1_nb_down[ihist]->Fit("fit");
      for(unsigned int inb=0; inb<5; inb++) {
         h1_nb_fit_down[ihist]->SetBinContent(inb+1, 
         return_y(inb, func->GetParameter(0), func->GetParameter(1))); 
      }
      h1_nb_fit_up[ihist]->SetLineColor(kRed);
      h1_nb_fit_down[ihist]->SetLineColor(kBlue);
      h1_nb_fit_up[ihist]->SetLineStyle(2);
      h1_nb_fit_down[ihist]->SetLineStyle(2);
      h1_nb_fit_up[ihist]->Draw("hist same");  
      h1_nb_fit_down[ihist]->Draw("hist same");  


      // kappa2
      c->cd(ihist+4);
      c->cd(ihist+4)->SetLeftMargin(0.125);  //0.1 is defalut

      h2_nb_up[ihist]->SetMinimum(0);
      h2_nb_up[ihist]->SetMaximum(1.3);
      h2_nb_up[ihist]->SetLineColor(kRed);
      h2_nb_down[ihist]->SetLineColor(kBlue);
      if(ihist==0) h2_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+4, ihist+5)+"  "+year);
      else if(ihist==1) h2_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+5, ihist+6)+"  "+year);
      else if(ihist==2) h2_nb_up[ihist]->SetTitle(string("#scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet}", ihist+6)+"  "+year);
      h2_nb_up[ihist]->GetXaxis()->SetTitle("N_{b}");
      h2_nb_up[ihist]->GetYaxis()->SetTitle("#kappa^{MC}_{2}");
      h2_nb_up[ihist]->GetXaxis()->SetTitleSize(0.05);
      h2_nb_up[ihist]->GetYaxis()->SetTitleSize(0.05);
      h2_nb_up[ihist]->GetXaxis()->SetTitleOffset(0.8);
      h2_nb_up[ihist]->GetYaxis()->SetTitleOffset(1.);
      h2_nb_up[ihist]->GetXaxis()->SetNdivisions(5,true);
      h2_nb_up[ihist]->Draw("hist");  
      h2_nb_down[ihist]->Draw("hist same");  

      // fit 
      h2_nb_up[ihist]->Fit("fit");
      for(unsigned int inb=0; inb<5; inb++)
         h2_nb_fit_up[ihist]->SetBinContent(inb+1, 
             return_y(inb, func->GetParameter(0), func->GetParameter(1))); 
      
      h2_nb_down[ihist]->Fit("fit");
      for(unsigned int inb=0; inb<5; inb++)
         h2_nb_fit_down[ihist]->SetBinContent(inb+1, 
             return_y(inb, func->GetParameter(0), func->GetParameter(1))); 

      h2_nb_fit_up[ihist]->SetLineColor(kRed);
      h2_nb_fit_up[ihist]->SetLineStyle(2);
      h2_nb_fit_down[ihist]->SetLineColor(kBlue);
      h2_nb_fit_down[ihist]->SetLineStyle(2);
      h2_nb_fit_up[ihist]->GetXaxis()->SetTitle("N_{b}");
      h2_nb_fit_up[ihist]->Draw("hist same");  
      h2_nb_fit_down[ihist]->Draw("hist same");

      // copy to summary hists
      h1_nb_fit_summary_up[isyst][ihist]    = dynamic_cast<TH1F*>(h1_nb_fit_up[ihist]->Clone());
      h1_nb_fit_summary_down[isyst][ihist]    = dynamic_cast<TH1F*>(h1_nb_fit_down[ihist]->Clone());
      h2_nb_fit_summary_up[isyst][ihist]    = dynamic_cast<TH1F*>(h2_nb_fit_up[ihist]->Clone());
      h2_nb_fit_summary_down[isyst][ihist]    = dynamic_cast<TH1F*>(h2_nb_fit_down[ihist]->Clone());
   
      // normalize such that first bin content is 1
      h1_nb_fit_summary_up[isyst][ihist]->Scale(1./h1_nb_fit_summary_up[isyst][ihist]->GetBinContent(1)); 
      h1_nb_fit_summary_down[isyst][ihist]->Scale(1./h1_nb_fit_summary_down[isyst][ihist]->GetBinContent(1)); 
      h2_nb_fit_summary_up[isyst][ihist]->Scale(1./h2_nb_fit_summary_up[isyst][ihist]->GetBinContent(1)); 
      h2_nb_fit_summary_down[isyst][ihist]->Scale(1./h2_nb_fit_summary_down[isyst][ihist]->GetBinContent(1)); 
      
      // subtract 1
      for(unsigned int inb=0; inb<5; inb++)
      {
        h1_nb_fit_summary_up[isyst][ihist]->SetBinContent(inb+1, 
            h1_nb_fit_summary_up[isyst][ihist]->GetBinContent(inb+1)-1.); 
        h1_nb_fit_summary_down[isyst][ihist]->SetBinContent(inb+1, 
            h1_nb_fit_summary_down[isyst][ihist]->GetBinContent(inb+1)-1.); 
        h2_nb_fit_summary_up[isyst][ihist]->SetBinContent(inb+1, 
            h2_nb_fit_summary_up[isyst][ihist]->GetBinContent(inb+1)-1.); 
        h2_nb_fit_summary_down[isyst][ihist]->SetBinContent(inb+1, 
            h2_nb_fit_summary_down[isyst][ihist]->GetBinContent(inb+1)-1.); 
      }

      // Fill stack
      //st1[ihist]->Add(h1_nb_fit_summary_up[isyst][ihist]);
      
    }

    // Define Legend 
    
    for(unsigned int ihist=0; ihist<3; ++ihist) {
      TLegend *l1, *l2;
      l1 = new TLegend(0.165,0.2,0.5,0.45);
      set_legend_style(l1);
      l1->SetTextSize(0.034);
      c->cd(ihist+1);
      l1->AddEntry(h1_nb_up[ihist], convert_systname(syst_list[isyst])+" 1#sigma up","l");
      l1->AddEntry(h1_nb_down[ihist], convert_systname(syst_list[isyst])+" 1#sigma down","l");
      l1->AddEntry(h1_nb_fit_up[ihist], "fitted "+convert_systname(syst_list[isyst])+" 1#sigma up","l");
      l1->AddEntry(h1_nb_fit_down[ihist], "fitted "+convert_systname(syst_list[isyst])+" 1#sigma down","l");
      l1->Draw();

      l2 = new TLegend(0.165,0.2,0.5,0.45);
      set_legend_style(l2);
      l2->SetTextSize(0.034);
      c->cd(ihist+4);
      l2->AddEntry(h2_nb_up[ihist], convert_systname(syst_list[isyst])+" 1#sigma up","l");
      l2->AddEntry(h2_nb_down[ihist], convert_systname(syst_list[isyst])+" 1#sigma down","l");
      l2->AddEntry(h2_nb_fit_up[ihist], "fitted "+convert_systname(syst_list[isyst])+" 1#sigma up","l");
      l2->AddEntry(h2_nb_fit_down[ihist], "fitted "+convert_systname(syst_list[isyst])+" 1#sigma down","l");
      l2->Draw();
    }
    c->SaveAs("plots/kappa/"+year+"/fit_kappa"+"_"+syst_list.at(isyst)+"_"+year+".pdf");
  }
  

  TCanvas *c_summary = new TCanvas;
  c_summary->Divide(3,2); 
  // kappa1
  for(unsigned int ihist=0; ihist<3; ++ihist) 
  {
    c_summary->cd(ihist+1);
    c_summary->cd(ihist+1)->SetLeftMargin(0.125);  //0.1 is defalut
    for(unsigned int isyst=0; isyst<syst_list.size(); ++isyst)
    {
      if(ihist==0) h1_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+4, ihist+5)+"   "+year);
      else if(ihist==1) h1_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+5, ihist+6)+"   "+year);
      else if(ihist==2) h1_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{1}}  ")+Form("%d #leq N_{jet}", ihist+6)+"  "+year);

      h1_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetRangeUser(-0.5, 0.5); 
      h1_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitle("N_{b}"); 
      h1_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitle("1-#kappa^{MC}_{1}"); 
      h1_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitleSize(0.05); 
      h1_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitleSize(0.05); 
      h1_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitleOffset(0.8); 
      h1_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitleOffset(1.2); 
      h1_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetNdivisions(5,true);
      h1_nb_fit_summary_up[isyst][ihist]->SetLineStyle(11); 
      h1_nb_fit_summary_down[isyst][ihist]->SetLineStyle(12);
      h1_nb_fit_summary_up[isyst][ihist]->SetLineColor(linecolor(isyst));
      h1_nb_fit_summary_down[isyst][ihist]->SetLineColor(linecolor(isyst)); 
      h1_nb_fit_summary_up[isyst][ihist]->Draw("same hist"); 
      h1_nb_fit_summary_down[isyst][ihist]->Draw("same hist"); 

      // sum in quad 
      for(unsigned int inb=0; inb<5; inb++) 
      { 
        float bin_content=-1;
        float bin_content_to_add = 0; 
        float new_bin_content = -0.5; 
        // up
        bin_content = h1_nb_fit_summary_up[isyst][ihist]->GetBinContent(inb+1); 
        bin_content_to_add = h1_nb_fit_combined_up[ihist]->GetBinContent(inb+1); 
        new_bin_content = TMath::Sqrt(bin_content*bin_content+bin_content_to_add*bin_content_to_add); 
        if(inb==4 && ihist==0) // low Njets, Nb=4
          h1_nb_fit_combined_up[ihist]->SetBinContent(inb+1, h1_nb_fit_combined_up[ihist]->GetBinContent(inb));  
        else
          h1_nb_fit_combined_up[ihist]->SetBinContent(inb+1, new_bin_content);  
        //down 
        bin_content = h1_nb_fit_summary_down[isyst][ihist]->GetBinContent(inb+1); 
        bin_content_to_add = h1_nb_fit_combined_down[ihist]->GetBinContent(inb+1); 
        new_bin_content = TMath::Sqrt(bin_content*bin_content+bin_content_to_add*bin_content_to_add); 
        if(inb==4 && ihist==0) // low Njets, Nb=4
          h1_nb_fit_combined_down[ihist]->SetBinContent(inb+1, h1_nb_fit_combined_down[ihist]->GetBinContent(inb));  
        else
          h1_nb_fit_combined_down[ihist]->SetBinContent(inb+1, new_bin_content);  
      } 
    }
    h1_nb_fit_combined_up[ihist]->SetLineStyle(1); 
    h1_nb_fit_combined_up[ihist]->SetLineColor(kRed); 
    h1_nb_fit_combined_down[ihist]->SetLineStyle(1); 
    h1_nb_fit_combined_down[ihist]->SetLineColor(kBlue); 
    h1_nb_fit_combined_up[ihist]->Draw("hist same"); 
    h1_nb_fit_combined_down[ihist]->Draw("hist same"); 

    // Define Legend 
        // kappa1
    TLegend *l3_1, *l3_2, *l3_3;
    l3_1 = new TLegend(0.15,0.12,0.5,0.42);
    l3_2 = new TLegend(0.15,0.6,0.5,0.88);
    l3_3 = new TLegend(0.5,0.75,0.8,0.89);

    c_summary->cd(ihist+1);
    set_legend_style(l3_1);
    set_legend_style(l3_2);
    set_legend_style(l3_3);
    for(unsigned int isyst=0; isyst<syst_list.size(); ++isyst) {
      if(isyst<=5) l3_1->AddEntry(h1_nb_fit_summary_up[isyst][ihist], convert_systname(syst_list[isyst]),"l");
      else if(isyst>5) l3_2->AddEntry(h1_nb_fit_summary_up[isyst][ihist], convert_systname(syst_list[isyst]),"l");
    }
    l3_3->AddEntry(h1_nb_fit_combined_up[ihist], "#splitline{Combined systematics}{1#sigma up}", "l");
    l3_3->AddEntry(h1_nb_fit_combined_down[ihist], "#splitline{Combined systematics}{1#sigma down}", "l");
    l3_1->Draw();
    l3_2->Draw();
    l3_3->Draw();
  }

  // kappa2
  for(unsigned int ihist=0; ihist<3; ++ihist) 
  {
    c_summary->cd(ihist+4);
    c_summary->cd(ihist+4)->SetLeftMargin(0.125);  //0.1 is defalut
    for(unsigned int isyst=0; isyst<syst_list.size(); ++isyst)
    {
      if(ihist==0) h2_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+4, ihist+5)+"   "+year);
      else if(ihist==1) h2_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet} #leq %d",ihist+5, ihist+6)+"   "+year);
      else if(ihist==2) h2_nb_fit_summary_up[isyst][ihist]->SetTitle(string("summary of  #scale[1.4]{#kappa_{2}}  ")+Form("%d #leq N_{jet}", ihist+6)+"  "+year);

      h2_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetRangeUser(-0.5, 0.5); 
      h2_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitle("N_{b}"); 
      h2_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitle("1-#kappa^{MC}_{2}"); 
      h2_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitleSize(0.05); 
      h2_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitleSize(0.05); 
      h2_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetTitleOffset(0.8); 
      h2_nb_fit_summary_up[isyst][ihist]->GetYaxis()->SetTitleOffset(1.2); 
      h2_nb_fit_summary_up[isyst][ihist]->GetXaxis()->SetNdivisions(5,true);
      h2_nb_fit_summary_up[isyst][ihist]->SetLineStyle(11); 
      h2_nb_fit_summary_down[isyst][ihist]->SetLineStyle(12);
      h2_nb_fit_summary_up[isyst][ihist]->SetLineColor(linecolor(isyst)); 
      h2_nb_fit_summary_down[isyst][ihist]->SetLineColor(linecolor(isyst)); 
      h2_nb_fit_summary_up[isyst][ihist]->Draw("same hist"); 
      h2_nb_fit_summary_down[isyst][ihist]->Draw("same hist"); 
      
      // sum in quad 
      for(unsigned int inb=0; inb<5; inb++) 
      { 
        float bin_content=-1;
        float bin_content_to_add = -1; 
        float new_bin_content = -0.5; 
        // up
        bin_content = h2_nb_fit_summary_up[isyst][ihist]->GetBinContent(inb+1); 
        bin_content_to_add = h2_nb_fit_combined_up[ihist]->GetBinContent(inb+1); 
        new_bin_content = TMath::Sqrt(bin_content*bin_content+bin_content_to_add*bin_content_to_add); 
        if(inb==4 && ihist==0) // low Njets, Nb=4
          h2_nb_fit_combined_up[ihist]->SetBinContent(inb+1, h2_nb_fit_combined_up[ihist]->GetBinContent(inb));  
        else
          h2_nb_fit_combined_up[ihist]->SetBinContent(inb+1, new_bin_content);  
        //down 
        bin_content = h2_nb_fit_summary_down[isyst][ihist]->GetBinContent(inb+1); 
        bin_content_to_add = h2_nb_fit_combined_down[ihist]->GetBinContent(inb+1); 
        new_bin_content = TMath::Sqrt(bin_content*bin_content+bin_content_to_add*bin_content_to_add); 
        if(inb==4 && ihist==0) // low Njets, Nb=4
          h2_nb_fit_combined_down[ihist]->SetBinContent(inb+1, h2_nb_fit_combined_down[ihist]->GetBinContent(inb));  
        else
          h2_nb_fit_combined_down[ihist]->SetBinContent(inb+1, new_bin_content);  
      } 
    }
    h2_nb_fit_combined_up[ihist]->SetLineStyle(1); 
    h2_nb_fit_combined_down[ihist]->SetLineStyle(1); 
    h2_nb_fit_combined_up[ihist]->SetLineColor(kRed); 
    h2_nb_fit_combined_down[ihist]->SetLineColor(kBlue); 
    h2_nb_fit_combined_up[ihist]->Draw("hist same"); 
    h2_nb_fit_combined_down[ihist]->Draw("hist same"); 

    // Define Legend 
        // kappa2
    TLegend *l4_1, *l4_2, *l4_3;
    l4_1 = new TLegend(0.15,0.12,0.5,0.42);
    l4_2 = new TLegend(0.15,0.6,0.5,0.88);
    l4_3 = new TLegend(0.5,0.75,0.8,0.89);
    c_summary->cd(ihist+4);
    set_legend_style(l4_1);
    set_legend_style(l4_2);
    set_legend_style(l4_3);
    for(unsigned int isyst=0; isyst<syst_list.size(); ++isyst) {
      if(isyst<=5) l4_1->AddEntry(h1_nb_fit_summary_up[isyst][ihist], convert_systname(syst_list[isyst]),"l");
      else if(isyst>5) l4_2->AddEntry(h1_nb_fit_summary_up[isyst][ihist], convert_systname(syst_list[isyst]),"l");
    }
    l4_3->AddEntry(h1_nb_fit_combined_up[ihist], "#splitline{Combined systematics}{1#sigma up}", "l");
    l4_3->AddEntry(h1_nb_fit_combined_down[ihist], "#splitline{Combined systematics}{1#sigma down}", "l");
    l4_1->Draw();
    l4_2->Draw();
    l4_3->Draw();
  }
  c_summary->SaveAs("plots/kappa/"+year+"/fit_kappa_summary_"+year+".pdf");
  
  // Write in file 
  TFile *f = new TFile("plots/kappa/"+year+"/fit_kappa_summary_"+year+".root","recreate");
  for(unsigned int ihist=0; ihist<3; ++ihist)
  {
    h1_nb_fit_combined_up[ihist]->Write(); 
    h1_nb_fit_combined_down[ihist]->Write(); 
    h2_nb_fit_combined_up[ihist]->Write(); 
    h2_nb_fit_combined_down[ihist]->Write(); 
  }
  f->Close();  
}
