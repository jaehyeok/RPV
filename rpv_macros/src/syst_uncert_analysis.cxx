#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TRatioPlot.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMath.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

vector<float> latex_err={};
vector<float> latex_con={};

void make_fit_mconly(TFile *fhist, TFile *kappa, TFile *f_out, int ibin);
void make_fit(TFile *fhist, TFile *kappa, TFile *f_out, int ibin);
void make_table();
float SF_kap(TFile *kappa, int ikap, int ibin); 
float SF_kap_err(TFile *kappa, int ikap, int ibin);


int main(int argc, char* argv[]){
  TString n_input = "variations/output_2016.root";
  TString n_kappa = "plots/kappa/kappa_summary_nominalX_2016.root";
  if(argc==2){
    n_kappa = argv[1];
  }
  else if(argc==2){
    n_kappa = argv[1];
    n_input = argv[2];
  }
  TString temp = n_input;
  TString n_out = temp.ReplaceAll("output_","output_kappa");
  temp = n_input;
  TFile *kappa = new TFile(n_kappa,"READ");
  TFile *fhist = new TFile(n_input,"READ");
/*  if(n_kappa.Contains("mconly")){
    if(n_input.Contains("nominal")) n_out = temp.ReplaceAll("nominal","kappa");
    n_out = n_out.ReplaceAll("_mconly","");
    TFile *f_out = new TFile(n_out,"recreate");
    for(int rg=22;rg<52;rg++){make_fit_mconly(fhist,kappa,f_out,rg);}
    f_out->Close();
  }
*/
//  else{
    TFile *f_out = new TFile("data/result_kappa.root","recreate");

    make_fit(fhist,kappa,f_out,27); 
    make_fit(fhist,kappa,f_out,28); 
    make_fit(fhist,kappa,f_out,29); 

//    for(int rg=22;rg<52;rg++) make_fit(fhist,kappa,f_out,rg);
//  }
  make_table();
  kappa->Close();
  fhist->Close();
}

void make_fit_mconly( TFile *fhist, TFile *kappa, TFile *f_out, int ibin){

  TH1F *data   = static_cast<TH1F*>(fhist->Get(Form("bin%i/data_obs", ibin)));
  TH1F *qcd    = static_cast<TH1F*>(fhist->Get(Form("bin%i/qcd"     , ibin)));
  TH1F *ttbar  = static_cast<TH1F*>(fhist->Get(Form("bin%i/ttbar"   , ibin)));
  TH1F *wjets  = static_cast<TH1F*>(fhist->Get(Form("bin%i/wjets"   , ibin)));
  TH1F *other  = static_cast<TH1F*>(fhist->Get(Form("bin%i/other"   , ibin))); 
  TH1F *mc_tot = (TH1F *)qcd;

  float mjmin  = (float) data->GetXaxis()->GetBinLowEdge(1);
  float mjmax  = (float) data->GetXaxis()->GetBinUpEdge(3);

  mc_tot->Add(ttbar);
  mc_tot->Add(wjets);
  mc_tot->Add(other);

  float mjbin_data[3];
  float mjbin_mc[3];
  float mjerr_mc[3];
 
  for(int i=0; i<3; i++){
    mjbin_data[i] = (float) data->GetBinContent(i+1);
    mjbin_mc[i]   = (float) mc_tot->GetBinContent(i+1); 
    mjerr_mc[i]   = (float) mc_tot->GetBinError(i+1);
  }

  float err_sum[3];
  float err_dat(0), err_diff(0), err_kap(0);
  float dat_bin(0), mc_bin(0);

  float temp(0);

  for(int i=0; i<3; i++){
    dat_bin = (float)data->GetBinContent(i+1);
    mc_bin  = (float)mc_tot->GetBinContent(i+1);

    err_dat = (float)data->GetBinError(i+1);
    err_diff = abs((dat_bin-mc_bin));
    if(i==0) temp = 0;
    else temp = SF_kap_err(kappa,i,ibin);
    err_kap = TMath::Sqrt(mjerr_mc[i]*mjerr_mc[i]+temp*temp);  
    err_sum[i] = TMath::Sqrt(err_dat*err_dat+ err_diff*err_diff+err_kap*err_kap);
  }

  float SF     = mjbin_data[0]/mjbin_mc[0];
  float binsz  = (mjmax-mjmin)/3;

  vector<TString> proc = {"qcd","ttbar","wjets","other",

                        "signal_M1000","signal_M1100","signal_M1200","signal_M1300","signal_M1400","signal_M1500","signal_M1600","signal_M1700","signal_M1800","signal_M1900","signal_M2000","signal_M2100","signal_M2200"// */

			/*"Stop_M300","Stop_M350","Stop_M400","Stop_M450","Stop_M500","Stop_M550","Stop_M600","Stop_M650","Stop_M700","Stop_M750","Stop_M800","Stop_M850","Stop_M900","Stop_M950","Stop_M1000","Stop_M1050","Stop_M1100","Stop_M1150","Stop_M1200","Stop_M1250","Stop_M1300","Stop_M1350","Stop_M1400"// */

			};

  vector<TString> updo = {"Up","Down"};
  
  f_out->cd();
  gDirectory->cd("/");
  TString directory(Form("bin%d",ibin));
  if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
  gDirectory->cd(directory);

  for(auto updown : updo){
    for(auto process : proc){
      TH1F *h_process  = static_cast<TH1F*>(fhist->Get(Form("bin%i/%s"   , ibin,process.Data())));
      for(int i=0; i<3; i++){
        mjbin_mc[i]   = (float) h_process->GetBinContent(i+1); 
      }

      TString h_name  = process+"_kappa"+updown;
      TH1F *h_kappa = new TH1F(h_name.Data(),h_name.Data(),3,mjmin,mjmax); 
      float uncert1, uncert2;
      if(updown=="Up"){
        uncert1 = SF_kap_err(kappa,1,ibin);
        uncert2 = SF_kap_err(kappa,2,ibin);
      }
      else if(updown=="Down"){
        uncert1 = -SF_kap_err(kappa,1,ibin);
        uncert2 = -SF_kap_err(kappa,2,ibin);
      }
      h_kappa->SetBinContent(1, mjbin_mc[0]*SF);
      h_kappa->SetBinContent(2, mjbin_mc[1]*SF*(SF_kap(kappa,1,ibin)+uncert1));
      h_kappa->SetBinContent(3, mjbin_mc[2]*SF*(SF_kap(kappa,2,ibin)+uncert2));
      h_kappa->Write();
    }
  }
}

void make_fit( TFile *fhist, TFile *kappa, TFile *f, int ibin){

  cout<<ibin<<endl; 

  TH1F *data   = static_cast<TH1F*>(fhist->Get(Form("bin%i/data_obs", ibin)));
  TH1F *qcd    = static_cast<TH1F*>(fhist->Get(Form("bin%i/qcd"     , ibin)));
  TH1F *ttbar  = static_cast<TH1F*>(fhist->Get(Form("bin%i/ttbar"   , ibin)));
  TH1F *wjets  = static_cast<TH1F*>(fhist->Get(Form("bin%i/wjets"   , ibin)));
  TH1F *other  = static_cast<TH1F*>(fhist->Get(Form("bin%i/other"   , ibin))); 
  TH1F *mc_tot = (TH1F *)qcd;

  float mjmin  = (float) data->GetXaxis()->GetBinLowEdge(1);
  float mjmax  = (float) data->GetXaxis()->GetBinUpEdge(3);

  TH1F *h_mc_proc1   = new TH1F("h_mc_proc1","h_mc_proc1",3,mjmin,mjmax); 
  TH1F *h_mc         = new TH1F("h_mc","h_mc",3,mjmin,mjmax); 

  float binsz  = (mjmax-mjmin)/3;

  mc_tot->Add(ttbar);
  mc_tot->Add(wjets);
  mc_tot->Add(other);

  
  float mjbin_data[3];
  float mjbin_mc[3], mjerr_mc[3];
 
  for(int i=0; i<3; i++){
    mjbin_data[i] = (float) data->GetBinContent(i+1);
    mjbin_mc[i]   = (float) mc_tot->GetBinContent(i+1); 
    mjerr_mc[i]   = (float) mc_tot->GetBinError(i+1); 
    cout<<mjbin_mc[i]<<"::"<<mjbin_data[i]<<endl;
  }
 
  float SF          = mjbin_data[0]/mjbin_mc[0];

  for(int i=0; i<3; i++) h_mc_proc1->SetBinContent(i+1, mjbin_mc[i]*SF);

  h_mc->SetBinContent(1, mjbin_mc[0]*SF);
  h_mc->SetBinContent(2, mjbin_mc[1]*SF*SF_kap(kappa,1,ibin));
  h_mc->SetBinContent(3, mjbin_mc[2]*SF*SF_kap(kappa,2,ibin));

  for(int i=0;i<3;i++) cout<<h_mc->GetBinContent(i+1)<<endl;
  float err_sum[3];
  float err_dat(0), err_diff(0), err_kap(0);
  float dat_bin(0), mc_bin(0);

  float temp(0);

  for(int i=0; i<3; i++){
    dat_bin = (float)data->GetBinContent(i+1);
    mc_bin  = (float)h_mc->GetBinContent(i+1);

    err_dat = (float)data->GetBinError(i+1);
    err_diff = abs((dat_bin-mc_bin));
    if(i==0) temp = 0;
    else temp = SF_kap_err(kappa,i,ibin);
    err_kap = TMath::Sqrt(mjerr_mc[i]*mjerr_mc[i]+temp*temp*mc_bin*mc_bin);  
    cout<<"err_kap : "<<err_kap<<endl;
    err_sum[i] = TMath::Sqrt(err_dat*err_dat+ err_diff*err_diff+err_kap*err_kap);
    latex_err.push_back(err_sum[i]);
    latex_con.push_back(mc_bin);
  }

  f->cd(); 
  gDirectory->cd("/");
  TString directory(Form("bin%d",ibin));
  if(!gDirectory->GetDirectory(directory)) gDirectory->mkdir(directory);
  gDirectory->cd(directory);

  float ymax, ymin;

  data->SetTitle("data");
  data->SetStats(0);
  data->SetLineColor(kBlack);
  data->SetMarkerStyle(20);
//  data->SetLineWidth(2);
  data->SetLineWidth(0);
  data->GetXaxis()->SetTitle("M_{J}");
  data->Write();

  ymax = data->GetMaximum();
  ymin = data->GetMinimum();
  h_mc->SetTitle("MC with \{kappa} Factor Correction");
  h_mc->SetStats(0);
  h_mc->SetLineColor(kBlue);
//  h_mc->SetLineWidth(2);
  h_mc->SetLineWidth(0);
  h_mc->GetXaxis()->SetTitle("M_{J}");
  h_mc->Write();

  h_mc_proc1->SetTitle("MC with First bin rescaled");
  h_mc_proc1->SetStats(0);
  h_mc_proc1->SetLineColor(kRed);
//  h_mc_proc1->SetLineWidth(2);
  h_mc_proc1->SetLineWidth(0);
  h_mc_proc1->GetXaxis()->SetTitle("M_{J}");
  h_mc_proc1->Write();

  mc_tot->SetTitle("MC without any correction");
  mc_tot->SetStats(0);
  mc_tot->SetLineColor(kRed);
  mc_tot->SetLineWidth(0);
  mc_tot->GetXaxis()->SetTitle("M_{J}");
  mc_tot->Write();

  vector<double> lines = {1.};

  TCanvas *c = new TCanvas(Form("c%d",ibin),Form("c%d",ibin),1000,1000);

  TH1F *h_mc_cp       = dynamic_cast<TH1F*>(h_mc->Clone("h_mc_cp"));
  TH1F *data_cp       = dynamic_cast<TH1F*>(data->Clone("data_cp"));
  TH1F *h_mc_proc1_cp = dynamic_cast<TH1F*>(h_mc_proc1->Clone("h_mc_proc1_cp"));
  TH1F *mc_tot_cp     = dynamic_cast<TH1F*>(mc_tot->Clone("mc_tot_cp"));
  TH1F *comp_org      = dynamic_cast<TH1F*>(data->Clone("comp_org"));
  TH1F *h_mc_err      = dynamic_cast<TH1F*>(h_mc->Clone("h_mc_err"));
  for(int i=0;i<3;i++) h_mc_err->SetBinError(i+1,err_sum[i]);

  TRatioPlot *comp = new TRatioPlot(data,h_mc);

  h_mc_err->SetMarkerSize(0);
  h_mc_err->SetFillColor(kBlack);
  h_mc_err->SetLineColor(kBlack);
  h_mc_err->SetFillStyle(3354);

  h_mc_err->Write();



  comp_org->Divide(data,h_mc_proc1,1,1,"B");
  comp_org->SetLineColor(kRed); 
  comp_org->SetLineWidth(1); 
  comp_org->SetMarkerStyle(21);
  comp_org->SetMarkerSize(0.01);


  comp->SetGridlines(lines);
  comp->Draw("");
  comp->GetUpperPad()->cd();
  data->SetMarkerStyle(20);
  h_mc_cp->SetLineWidth(2);
  h_mc_proc1_cp->SetLineWidth(2);
  data_cp->SetLineWidth(2);
  h_mc_cp->Draw("same hist");
  h_mc_proc1_cp->Draw("hist same");
  data_cp->Draw("same");
  h_mc_err->Draw("same e2");

  TLegend *l = new TLegend(0.15,0.8,0.85,0.89);
  l->AddEntry(h_mc_cp,"Corrected by kappa factor","l");
  l->AddEntry(h_mc_proc1_cp,"Not Corrected","l");
  l->AddEntry(data_cp,"Data","lep");
  l->SetBorderSize(0);
  l->SetNColumns(3);
  l->Draw();

  comp->GetUpperPad()->SetLogy();
  comp->GetUpperRefYaxis()->SetTitle("Events");
  comp->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp->GetLowerRefYaxis()->SetRangeUser(0.3,2.1);
  comp->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  comp->GetLowerPad()->cd();
  comp_org->Draw("same");
//  comp_org->Draw("same");
  comp->GetLowerRefGraph()->SetLineColor(kBlue+2);
  comp->GetLowerRefGraph()->SetLineWidth(1);
  comp->GetLowerRefGraph()->SetMarkerStyle(21);
  comp->GetLowerRefGraph()->SetMarkerSize(0.01);
 // comp->GetLowerRefGraph()->Draw("same e");
 // c->Print(Form("plots/kappa_syst_uncert_%d.pdf",ibin));
/*
  TCanvas *c1 = new TCanvas("c1","c1",2700,800);
  c1->Divide(3,1);
  c1->cd(1);
  TRatioPlot *comp1 = new TRatioPlot(data,mc_tot);
  comp1->SetGridlines(lines);
  comp1->Draw("");
  comp1->GetUpperPad()->cd();
  data_cp->Draw("same");
  mc_tot_cp->SetLineWidth(2);
  mc_tot_cp->SetLineColor(kBlue);
  mc_tot_cp->Draw("same hist");
  h_mc_err->Draw("same e2");
  comp1->GetUpperRefYaxis()->SetTitle("Events");
  comp1->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp1->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp1->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp1->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp1->GetUpperPad()->SetLogy();
  comp1->GetLowerRefYaxis()->SetRangeUser(0.3,2.1);
  comp1->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  TLegend *l1 = new TLegend(0.75,0.75,0.85,0.89);
  l1->AddEntry(mc_tot_cp,"MC","l");
  l1->AddEntry(data_cp,"Data","lep");
  l1->SetBorderSize(0);
  l1->Draw();

  c1->cd(2);
  TRatioPlot *comp2 = new TRatioPlot(data,h_mc_proc1);
  comp2->SetGridlines(lines);
  comp2->Draw("");
  comp2->GetUpperPad()->cd();
  data_cp->Draw("same");
  h_mc_err->Draw("same e2");
  h_mc_proc1_cp->SetLineWidth(2);
  h_mc_proc1_cp->SetLineColor(kBlue);
  h_mc_proc1_cp->Draw("same hist");
  comp2->GetUpperRefYaxis()->SetTitle("Events");
  comp2->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp2->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp2->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp2->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp2->GetUpperPad()->SetLogy();
  comp2->GetLowerRefYaxis()->SetRangeUser(0.3,2.1);
  comp2->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  TLegend *l2 = new TLegend(0.75,0.75,0.85,0.89);
  l2->AddEntry(h_mc_proc1_cp,"MC","l");
  l2->AddEntry(data_cp,"Data","lep");
  l2->SetBorderSize(0);
  l2->Draw();

  
  c1->cd(3);
  TRatioPlot *comp3 = new TRatioPlot(data,h_mc);
  comp3->SetGridlines(lines);
  comp3->Draw("");
  comp3->GetUpperPad()->cd();
  data_cp->Draw("same");
  h_mc_err->Draw("same e2");
  h_mc_cp->SetLineWidth(2);
  h_mc_cp->Draw("same hist");
  comp3->GetUpperRefYaxis()->SetTitle("Events");
  comp3->GetLowerRefYaxis()->SetTitle("Data/MC");
  comp3->GetUpperRefYaxis()->SetLabelSize(0.02);
  comp3->GetLowerRefXaxis()->SetLabelSize(0.02);
  comp3->GetLowerRefYaxis()->SetLabelSize(0.02);
  comp3->GetUpperPad()->SetLogy();
  comp3->GetLowerRefYaxis()->SetRangeUser(0.3,2.1);
  comp3->GetUpperRefYaxis()->SetRangeUser(0.1,ymax*5);
  TLegend *l3 = new TLegend(0.75,0.75,0.85,0.89);
  l3->AddEntry(h_mc_cp,"MC","l");
  l3->AddEntry(data_cp,"Data","lep");
  l3->SetBorderSize(0);
  l3->Draw("same ");
  c1->Print(Form("plots/kappa_syst_uncert_comp_%d.pdf",ibin));
 */
 if(ibin==28||ibin==29||ibin==27) c->Print(Form("plots/kappa/kappa_syst_uncert_comp_%d.pdf",ibin));
 
}

void make_table(){

  vector<float> latex_per ={};

  for(int index=0; index<latex_err.size(); index++) latex_per.push_back(latex_err.at(index)/latex_con.at(index)*100.);

  cout<<"\\usepackage{multirow}"<<endl;

  cout<<"\\begin{table}[]"<<endl;
  cout<<"\\caption{}"<<endl;
  cout<<"\\label{tab:my-table}"<<endl;
  cout<<"\\begin{tabular}{cccc}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"\\multirow{2}{*}{} & \\multicolumn{3}{c}{$M_{J}$} \\\\ \\cline{2-4}"<<endl;
  cout<<" & 500 GeV $\\sim$800 GeV & 800 GeV $\\sim$1100 GeV & 1100 GeV $\\sim$ \\\\ \\hline\\hline"<<endl;
  for(int i=0 ; i<3 ; i++) cout<< setprecision(2) << "\\multicolumn{1}{c|}{Bin "<< 27+i <<"} & "<< latex_per.at(3*i)<<" \\% & "<< latex_per.at(3*i+1) <<" \\% & "<< latex_per.at(3*i+2) <<" \\% \\\\"<<endl;
  cout<<"\\end{tabular}"<<endl;
  cout<<"\\end{table}"<<endl;
}

float SF_kap(TFile *kappa, int ikap, int ibin){
  TH1F *h = static_cast<TH1F*> (kappa->Get(Form("h1_1l_summary%d",ikap)));

  int njets_region=1;
  if(ibin%3==2)njets_region=2;
  if(ibin%3==0)njets_region=3;
  int bin_index= (njets_region-1)*25 + 8;

  float kappa_0, kappa_1, kappa_2, kappa_ave;
  kappa_0 = (float)h->GetBinContent(bin_index-2); 
  kappa_1 = (float)h->GetBinContent(bin_index); 
  kappa_2 = (float)h->GetBinContent(bin_index+2); 
  if(njets_region==3) kappa_ave = kappa_1;
  else kappa_ave = (kappa_1+kappa_2)/2;
  cout<<kappa_ave<<endl;
  return kappa_ave;
}

float SF_kap_err(TFile *kappa, int ikap, int ibin){
  TH1F *h = static_cast<TH1F*> (kappa->Get(Form("h1_1l_summary%d",ikap)));

  int njets_region=1;
  if(ibin%3==2)njets_region=2;
  if(ibin%3==0)njets_region=3;
  int bin_index= (njets_region-1)*25 + 8;

  float err_kappa_0, err_kappa_1, err_kappa_2, err_kappa_ave;
  err_kappa_0 = (float)h->GetBinError(bin_index-2); 
  err_kappa_1 = (float)h->GetBinError(bin_index); 
  err_kappa_2 = (float)h->GetBinError(bin_index+2); 
  if(njets_region==3) err_kappa_ave = err_kappa_1;
  else  err_kappa_ave = TMath::Sqrt((err_kappa_1*err_kappa_1+err_kappa_2*err_kappa_2)/2);
  cout<<"error : "<<err_kappa_ave<<endl;
  return err_kappa_ave;
}
