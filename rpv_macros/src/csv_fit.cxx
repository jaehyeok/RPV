#include "tdrstyle.C"
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TFractionFitter.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "Fit/Fitter.h"
#include "TROOT.h"
#include <iostream>

#include "utilities_macros_rpv.hpp"

int main(int argc, char *argv[])
{
  bool fitCharmWithLight=false;
  bool excludeHighCSV=false;

  TString luminosity = rpv::luminosity;
  int maxbin=20;

  // by default, want to look at low njet region
  TString fitType="low_njet";
  // otherwise parse second parameter
  if(argc>1) {
    fitType=Form("%s", argv[1]);
    // options: low_njet, low_njet_low_mj, low_njet_high_mj, high_njet, exclude_high_csv 
    if(fitType!="low_njet" && 
       fitType!="high_njet" &&
       fitType!="low_njet_vlow_mj" && 
       fitType!="low_njet_low_mj" && 
       fitType!="low_njet_high_mj" && 
       fitType!="45_njetbin" && 
       fitType!="67_njetbin" && 
       fitType!="89_njetbin" && 
       fitType!="10_njetbin") {
      std::cout << "Invalid fit type: " << fitType 
		<< "\nValid fit types are: low_njet, high_njet, "
		<< "45_njetbin, 67_njetbin, 89_njetbin, 10_njetbin, "
		<< "low_njet_vlow_mj, low_njet_low_mj, low_njet_high_mj"  << std::endl;
      return 1;
    }
    if(fitType=="exclude_high_csv") {
      maxbin=16;
      excludeHighCSV=true;
      // still want to fit low_njet region
      fitType="low_njet";
    }
  }  
  setTDRStyle();
  gROOT->ForceStyle();

  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetTitleOffset(1.43,"y");

  TString filename = "csv_newmethod.root";
  if(argc>2) filename = argv[2];
  TFile *f = TFile::Open(filename);

  std::cout << "Getting weighted histograms" << std::endl;
  TH1F *qcd_b = static_cast<TH1F*>(f->Get(Form("QCD_b_%s", fitType.Data())));
  TH1F *qcd_c = static_cast<TH1F*>(f->Get(Form("QCD_c_%s", fitType.Data())));
  TH1F *qcd_l = static_cast<TH1F*>(f->Get(Form("QCD_l_%s", fitType.Data())));
  TH1F *other = static_cast<TH1F*>(f->Get(Form("other_%s", fitType.Data())));
  TH1F *qcd_cl = static_cast<TH1F*>(qcd_c->Clone());
  qcd_cl->Add(qcd_l);

  std::cout << "Getting raw histograms" << std::endl;
  TH1F *data = static_cast<TH1F*>(f->Get(Form("data_%s", fitType.Data())));
  TH1F *qcd_b_raw = static_cast<TH1F*>(f->Get(Form("QCD_b_%s_raw", fitType.Data())));
  TH1F *qcd_c_raw = static_cast<TH1F*>(f->Get(Form("QCD_c_%s_raw", fitType.Data())));
  TH1F *qcd_l_raw = static_cast<TH1F*>(f->Get(Form("QCD_l_%s_raw", fitType.Data())));
  TH1F *other_raw = static_cast<TH1F*>(f->Get(Form("other_%s_raw", fitType.Data())));
  TH1F *qcd_cl_raw = static_cast<TH1F*>(qcd_c_raw->Clone());
  qcd_cl_raw->Add(qcd_l_raw);

  std::cout << "Getting weights" << std::endl;
  TH1F *qcd_b_weights = static_cast<TH1F*>(f->Get(Form("QCD_b_%s_weights", fitType.Data())));
  TH1F *qcd_c_weights = static_cast<TH1F*>(f->Get(Form("QCD_c_%s_weights", fitType.Data())));
  TH1F *qcd_l_weights = static_cast<TH1F*>(f->Get(Form("QCD_l_%s_weights", fitType.Data())));
  TH1F *other_weights = static_cast<TH1F*>(f->Get(Form("other_%s_weights", fitType.Data())));
  TH1F *qcd_cl_weights = static_cast<TH1F*>(qcd_c_weights->Clone());
  qcd_cl_weights->Add(qcd_l_weights);


  float qcd_yield = qcd_b->Integral()+qcd_c->Integral()+qcd_l->Integral();
  float scaling = (data->Integral()-other->Integral())/qcd_yield;
  std::cout << "Scaling qcd by a factor: " << scaling << std::endl;
  qcd_b->Scale(scaling);
  qcd_c->Scale(scaling);
  qcd_l->Scale(scaling);
  qcd_cl->Scale(scaling);

  qcd_b_weights->Scale(scaling);
  qcd_c_weights->Scale(scaling);
  qcd_l_weights->Scale(scaling);
  qcd_cl_weights->Scale(scaling);
  
  TH1F *mc_total = static_cast<TH1F*>(qcd_b->Clone());
  mc_total->Add(qcd_c);
  mc_total->Add(qcd_l);
  mc_total->Add(other);
  
  double total_err(0), qcd_b_err(0), qcd_c_err(0), qcd_l_err(0), qcd_cl_err(0), other_err(0);

  float total_yield = mc_total->IntegralAndError(1,maxbin,total_err);
  std::cout<<"Total Yield: "<<total_yield<<std::endl;
  float qcd_b_fracbefore = qcd_b->IntegralAndError(1,maxbin,qcd_b_err)/total_yield;
  float qcd_c_fracbefore = qcd_c->IntegralAndError(1,maxbin,qcd_c_err)/total_yield;
  float qcd_l_fracbefore = qcd_l->IntegralAndError(1,maxbin,qcd_l_err)/total_yield;
  float qcd_cl_fracbefore = (qcd_cl->IntegralAndError(1,maxbin,qcd_cl_err))/total_yield;
  float other_fracbefore = other->IntegralAndError(1,maxbin,other_err)/total_yield;

  float qcd_b_fracbefore_err = qcd_b_fracbefore*sqrt(pow(qcd_b_err/qcd_b->Integral(1,maxbin),2)+pow(total_err/total_yield,2));
  float qcd_c_fracbefore_err = qcd_c_fracbefore*sqrt(pow(qcd_c_err/qcd_c->Integral(1,maxbin),2)+pow(total_err/total_yield,2));
  float qcd_l_fracbefore_err = qcd_l_fracbefore*sqrt(pow(qcd_l_err/qcd_l->Integral(1,maxbin),2)+pow(total_err/total_yield,2));
  float qcd_cl_fracbefore_err = qcd_cl_fracbefore*sqrt(pow(qcd_cl_err/qcd_cl->Integral(1,maxbin),2)+pow(total_err/total_yield,2));
  float other_fracbefore_err = other_fracbefore*sqrt(pow(other_err/other->Integral(1,maxbin),2)+pow(total_err/total_yield,2));

  std::cout << "fractions before fit:\n"
  	    << "b: " << qcd_b_fracbefore << " +/- " << qcd_b_fracbefore_err << std::endl
  	    << "c: " << qcd_c_fracbefore << " +/- " << qcd_c_fracbefore_err <<std::endl
  	    << "l: " << qcd_l_fracbefore << " +/- " << qcd_l_fracbefore_err <<std::endl
  	    << "cl: " << qcd_cl_fracbefore << " +/- " << qcd_cl_fracbefore_err <<std::endl
  	    << "other: " << other_fracbefore << " +/- " << other_fracbefore_err <<std::endl;

  TObjArray *mc = new TObjArray(4);
  mc->Add(qcd_b_raw);
  mc->Add(other_raw);
  if(fitCharmWithLight) {
    mc->Add(qcd_cl_raw);
  }
  else {
    mc->Add(qcd_c_raw);
    mc->Add(qcd_l_raw);
  }
  
  TFractionFitter *fit = new TFractionFitter(data, mc,"V");
  fit->Constrain(0, 1e-4, 1.0);
  fit->Constrain(1, 1e-4, 1.0);
  fit->Constrain(2, 1e-4, 1.0);
  if(!fitCharmWithLight) fit->Constrain(3, 1e-4, 1.0);

  fit->SetWeight(0, qcd_b_weights);
  fit->SetWeight(1, other_weights);
  if(fitCharmWithLight) {
    fit->SetWeight(2, qcd_cl_weights);
  }
  else {
    fit->SetWeight(2, qcd_c_weights);
    fit->SetWeight(3, qcd_l_weights);
  }
  // allow variation of range
  fit->SetRangeX(1, maxbin);

  ROOT::Fit::Fitter* fitter = (ROOT::Fit::Fitter*)fit->GetFitter();
  fitter->Config().ParSettings(1).SetValue(other->Integral()/total_yield);
  fitter->Config().ParSettings(1).Fix();
  if(!fitCharmWithLight){
    fitter->Config().ParSettings(3).SetValue(qcd_l->Integral()/total_yield);
    fitter->Config().ParSettings(3).Fix();
  }

  Int_t status = fit->Fit();
  if(status==0) {
    // get degrees of freedom (the fitter does not calculate the number of degrees of freedom correctly
    // when there are fixed parameters
    const std::vector<ROOT::Fit::ParameterSettings>& settings = fitter->Config().ParamsSettings();
    int ndof = maxbin;
    for (auto isetting : settings) {
      if(!isetting.IsFixed()) ndof--;
    }
    std::cout << "chi^2/ndof: " << fit->GetChisquare() << "/" << ndof << ", prob = " << fit->GetProb() << std::endl;
    data->SetMinimum(0);
    data->GetXaxis()->SetNdivisions(505);
    data->SetMarkerSize(1);
    data->SetLineColor(kBlack);
    data->SetMarkerStyle(kFullCircle);
    data->GetYaxis()->SetLabelSize(0.04);
    data->SetTitle(";CSV;Events / 0.005");
    TCanvas *c = new TCanvas;
    data->Draw("e");

    TH1F* result_b = static_cast<TH1F*>(fit->GetMCPrediction(0));
    TH1F* result_other = static_cast<TH1F*>(fit->GetMCPrediction(1));
    TH1F* result_c = 0;
    TH1F* result_l = 0;
    TH1F* result_cl = 0;

    if(fitCharmWithLight) {
      result_cl = static_cast<TH1F*>(fit->GetMCPrediction(2));
    }
    else {
      result_c = static_cast<TH1F*>(fit->GetMCPrediction(2));
      result_l = static_cast<TH1F*>(fit->GetMCPrediction(3));
    }


    result_b->SetLineColor(kRed);
    result_b->SetLineWidth(3);
    result_b->SetLineStyle(kDashed);
    result_b->SetMarkerSize(0);
    result_b->Multiply(qcd_b_weights);
    result_b->Draw("same");
    result_b->Draw("same,hist");
    if(fitCharmWithLight) {
      result_cl->SetLineColor(kBlack);
      result_cl->SetLineWidth(3);
      result_cl->SetLineStyle(kDashed);
      result_cl->SetMarkerSize(0);
      result_cl->Draw("same");
      result_cl->Draw("same,hist");
    }
    else {
      result_c->SetLineColor(kBlack);
      result_c->SetLineWidth(3);
      result_c->SetLineStyle(kDashed);
      result_c->SetMarkerSize(0);
      result_c->Multiply(qcd_c_weights);
      result_c->Draw("same");
      result_c->Draw("same,hist");
      result_l->SetLineColor(kMagenta);
      result_l->SetLineWidth(3);
      result_l->SetLineStyle(kDashed);
      result_l->SetMarkerSize(0);
      result_l->Multiply(qcd_l_weights);
      result_l->Draw("same");
      result_l->Draw("same,hist");
    }
    result_other->SetLineColor(kGreen);
    result_other->SetLineWidth(3);
    result_other->SetLineStyle(kDashed);
    result_other->Multiply(other_weights);
    result_other->SetMarkerSize(0);
    result_other->Draw("same");
    result_other->Draw("same,hist");
    TH1F* sum = static_cast<TH1F*>( fit->GetPlot());
    
    //Original calculation: not actually correct; see documentation for TFractionFitter::GetMCPrediction()
    /*TH1F *sum = static_cast<TH1F*>(result_b->Clone());
    if(fitCharmWithLight) {
      sum->Add(result_cl);
    }
    else {
      sum->Add(result_c);
      sum->Add(result_l);
    }
    sum->Add(result_other);*/
    sum->SetLineColor(kBlue);
    sum->SetLineStyle(kSolid);
    sum->SetLineWidth(3);
    sum->SetMarkerSize(0);
    sum->Draw("same");
    sum->Draw("same,hist");
    data->Draw("e,same");

    TLegend *leg1 = new TLegend(0.25, 0.5, 0.65, 0.87);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->AddEntry(data, "Data", "ELP");
    leg1->AddEntry(sum, "Total fit", "L");
    leg1->AddEntry(result_b, "b events", "PL");
    leg1->AddEntry(result_c, "c events", "PL");
    leg1->AddEntry(result_l, "Light-parton events", "PL");
    leg1->AddEntry(result_other, "Non-QCD events", "PL");
    leg1->Draw();
    
    TLatex tla;
    tla.SetTextSize(0.038);
    
    
    TString cmslabel = "#font[62]{CMS} #scale[0.8]{#font[52]{Preliminary}}";
    TString lumilabel = TString::Format("%1.1f",luminosity.Atof())+" fb^{-1} (13 TeV)";

    tla.DrawLatexNDC(0.18,0.93,cmslabel);
    tla.SetTextFont(42);
    tla.DrawLatexNDC(0.71,0.93,lumilabel);

    double qcd_b_fracafter, qcd_b_fracafter_err;    
    double qcd_c_fracafter, qcd_c_fracafter_err;    

    fit->GetResult(0, qcd_b_fracafter, qcd_b_fracafter_err);
    fit->GetResult(2, qcd_c_fracafter, qcd_c_fracafter_err);
    float other_fracafter = fitter->Config().ParSettings(1).Value();
    float qcd_l_fracafter = -1.0;
    float qcd_cl_fracafter = -1.0;
    if(fitCharmWithLight) {
      qcd_cl_fracafter = fitter->Config().ParSettings(2).Value();
    }
    else {
      qcd_c_fracafter = fitter->Config().ParSettings(2).Value();
      qcd_l_fracafter = fitter->Config().ParSettings(3).Value();
    }

    float qcd_b_ratio=qcd_b_fracafter/qcd_b_fracbefore;
    float qcd_b_ratio_err=qcd_b_ratio*sqrt(pow(qcd_b_fracafter_err/qcd_b_fracafter,2)+pow(qcd_b_fracbefore_err/qcd_b_fracbefore,2));
    float other_ratio=other_fracafter/other_fracbefore;
    float qcd_l_ratio, qcd_c_ratio, qcd_cl_ratio;
    float qcd_l_ratio_err=0.0;
    qcd_c_ratio = qcd_l_ratio = qcd_cl_ratio = -1;
    if(fitCharmWithLight) {
      qcd_cl_ratio = qcd_cl_fracafter/qcd_cl_fracbefore;
    }
    else {
      qcd_c_ratio = qcd_c_fracafter/qcd_c_fracbefore;
      qcd_l_ratio = qcd_l_fracafter/qcd_l_fracbefore;
    }

    float qcd_c_ratio_err=qcd_c_ratio*sqrt(pow(qcd_c_fracafter_err/qcd_c_fracafter,2)+pow(qcd_c_fracbefore_err/qcd_c_fracbefore,2));

    std::cout << "fractions before fit:\n"
	      << "b: " << qcd_b_fracbefore << " +/- " << qcd_b_fracbefore_err << std::endl
	      << "c: " << qcd_c_fracbefore << " +/- " << qcd_c_fracbefore_err <<std::endl
	      << "l: " << qcd_l_fracbefore << " +/- " << qcd_l_fracbefore_err <<std::endl
	      << "cl: " << qcd_cl_fracbefore << " +/- " << qcd_cl_fracbefore_err <<std::endl
	      << "other: " << other_fracbefore << " +/- " << other_fracbefore_err <<std::endl;
    std::cout << "fractions after fit:\n"
    	      << "b: " << qcd_b_fracafter << " +/- " << qcd_b_fracafter_err << std::endl
    	      << "c: " << qcd_c_fracafter << " +/- " << qcd_c_fracafter_err << std::endl
    	      << "l: " << qcd_l_fracafter << std::endl
    	      << "cl: " << qcd_cl_fracafter << std::endl
    	      << "other: " << other_fracafter << std::endl;
    std::cout << "after/before fit ratio:\n"
    	      << "b: " << qcd_b_ratio << " +/- " << qcd_b_ratio_err << std::endl
    	      << "c: " << qcd_c_ratio << " +/- " << qcd_c_ratio_err << std::endl
    	      << "l: " << qcd_l_ratio << " +/- " << qcd_l_ratio_err << std::endl
    	      << "cl: " << qcd_cl_ratio << std::endl
    	      << "other: " << other_ratio << std::endl;
    if(excludeHighCSV)
      c->Print(Form("plots/csv/csvfit_%s.png", "exclude_high_csv"));
    else
      c->Print(Form("plots/csv/csvfit_%s.png", fitType.Data()));
  
    std::cout << "chi^2/ndof from TFractionFitter: " << fit->GetChisquare() << "/" << ndof << ", prob = " << fit->GetProb() << std::endl;
    float chi2 =0.;
    for(int ib =1; ib<=sum->GetNbinsX();ib++){
      /*std::cout<<"Data yield: "<<data->GetBinContent(ib)<<std::endl;
      std::cout<<"Sum yield: "<<sum->GetBinContent(ib)<<std::endl;
      std::cout<<"Uncertainty on difference : "<<sqrt(pow(data->GetBinError(ib),2)+pow(sum->GetBinError(ib),2))<<std::endl;
      std::cout<<"Sigma "<<(data->GetBinContent(ib) - sum->GetBinContent(ib))/sqrt(pow(sum->GetBinError(ib),2)+pow(data->GetBinError(ib),2))<<std::endl;*/
      chi2+=pow((data->GetBinContent(ib) - sum->GetBinContent(ib))/sqrt(pow(sum->GetBinError(ib),2)+pow(data->GetBinError(ib),2)),2);
    }
    std::cout<<"Total chi2, by hand, is "<<chi2<<std::endl;

    //  qcd_b->Scale(qcd_b_ratio);
    // qcd_c->Scale(qcd_c_ratio);

    float chi2_b =0.;
    for(int ib =1; ib<=sum->GetNbinsX();ib++){
      /*  std::cout<<"b result yield: "<<result_b->GetBinContent(ib)<<std::endl;
      std::cout<<" b scaled prefit yield: "<<qcd_b->GetBinContent(ib)<<std::endl;
      std::cout<<"Uncertainty on difference : "<<sqrt(pow(result_b->GetBinError(ib),2)+pow(qcd_b->GetBinError(ib),2))<<std::endl;
      std::cout<<"Sigma "<<(result_b->GetBinContent(ib) - qcd_b->GetBinContent(ib))/sqrt(pow(qcd_b->GetBinError(ib),2)+pow(result_b->GetBinError(ib),2))<<std::endl;*/
      chi2_b+=pow((result_b->GetBinContent(ib) - qcd_b->GetBinContent(ib))/sqrt(pow(qcd_b->GetBinError(ib),2)+pow(result_b->GetBinError(ib),2)),2);
    }
    std::cout<<"Total chi2 for b hist is "<<chi2_b<<std::endl;

      float chi2_c =0.;
    for(int ib =1; ib<=sum->GetNbinsX();ib++){
      /* std::cout<<"charm Result yield: "<<result_c->GetBinContent(ib)<<std::endl;
      std::cout<<"charm Scaled prefit yield: "<<qcd_c->GetBinContent(ib)<<std::endl;
      std::cout<<"Uncertainty on difference : "<<sqrt(pow(result_c->GetBinError(ib),2)+pow(qcd_c->GetBinError(ib),2))<<std::endl;
      std::cout<<"Sigma "<<(result_c->GetBinContent(ib) - qcd_c->GetBinContent(ib))/sqrt(pow(qcd_c->GetBinError(ib),2)+pow(result_c->GetBinError(ib),2))<<std::endl;*/
      chi2_c+=pow((result_c->GetBinContent(ib) - qcd_c->GetBinContent(ib))/sqrt(pow(qcd_c->GetBinError(ib),2)+pow(result_c->GetBinError(ib),2)),2);
    }
    std::cout<<"Total chi2 for c hist is "<<chi2_c<<std::endl;

    std::cout<<"Total chi2 for b,c, and sum is "<<chi2_c+chi2_b+chi2<<std::endl;
    // don't want to recreate files for variations
    TFile *out;
    if(excludeHighCSV)
      out = new TFile(Form("data/csvfit_%s.root","exclude_high_csv"), "recreate");
    else 
      out = new TFile(Form("data/csvfit_%s.root", fitType.Data()), "recreate");
    TH1F *csv_weight = new TH1F("csv_weight", "csv_weight", 3, 0, 3);
    csv_weight->SetBinContent(1, qcd_b_ratio);
    csv_weight->SetBinError(1, qcd_b_ratio_err);
    csv_weight->GetXaxis()->SetBinLabel(1, "b");
    csv_weight->SetBinContent(2, qcd_c_ratio);
    csv_weight->SetBinError(2, qcd_c_ratio_err);
    csv_weight->GetXaxis()->SetBinLabel(2, "c");
    csv_weight->SetBinContent(3, qcd_l_ratio);
    csv_weight->SetBinError(3, qcd_l_ratio_err);
    csv_weight->GetXaxis()->SetBinLabel(3, "l");
    csv_weight->Write();
    out->Close();
  }
  return 0;
}
