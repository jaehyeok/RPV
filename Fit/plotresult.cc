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

#include "/homes/jaehyeokyoo/scratch/tdrstyle.C"

using namespace RooFit;

void setValues(RooWorkspace *work, RooFitResult *result);
void plotFitPulls(const RooArgList &pulls, const TString & pullString, const std::string & type);

//
// h1 cosmetics
//
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
TH1D* makeHistogram(TGraphAsymmErrors* graph){

    TString name = graph->GetName(); 
    TH1D* hist = new TH1D(Form("h_%s", graph->GetName()), Form("%s",graph->GetName()), 4, 1, 5);
    hist->SetDirectory(0);
    for (int i=0; i<graph->GetN();++i){
        Int_t bin;
        if(graph->GetX()[i]==1.5) hist->SetBinContent(1,graph->GetY()[i]);  
        if(graph->GetX()[i]==2.5) hist->SetBinContent(2,graph->GetY()[i]);  
        if(graph->GetX()[i]==3.5) hist->SetBinContent(3,graph->GetY()[i]);  
        if(graph->GetX()[i]==4.5) hist->SetBinContent(4,graph->GetY()[i]);   

        if(!name.Contains("data")) 
        { 
            if(graph->GetX()[i]==1.5) hist->SetBinError(1,0);  
            if(graph->GetX()[i]==2.5) hist->SetBinError(2,0);  
            if(graph->GetX()[i]==3.5) hist->SetBinError(3,0);  
            if(graph->GetX()[i]==4.5) hist->SetBinError(4,0);   
        }
    }
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

void plotresult(int gluinoMass=1200)
{
  bool plotSPlusB=false;
  bool doControl=true;

  setTDRStyle();
  gROOT->ForceStyle();

  std::string workspaceFilename;
  std::string resultsFilename;
  if(doControl) 
  { 
    workspaceFilename=Form("workspace_M%d_control.root", gluinoMass);
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

  std::vector<std::string> binname;
  std::vector<int> binnumber;
  if(doControl) 
  {
    binname = {"nlep0_nj45_lowmj",   "nlep0_nj67_lowmj",     "nlep1_nj45_lowmj",
   			   "nlep0_nj45_highmj",  "nlep0_nj67_highmj",    "nlep1_nj45_highmj"}; 
    binnumber = {0,1,2,3,4,5};
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

  for(int i=0; i<binname.size(); i++) { 
    
    TCanvas *c;
    TPad *pad_stack;
    TPad *pad_ratio;
    
    int ibin = binnumber.at(i);
    cout << "...... BIN: " << ibin << " :: " << binname[i]<< endl;
    std::cout << "Drawing frame" << std::endl;
    c = new TCanvas("c","c",300,300);
    c->cd();

    pad_stack = new TPad(Form("p_main_%i",i), Form("p_main_%i",i), 0.0, 0.3, 1.0, 1.0);
    pad_stack->SetTopMargin(0.1);
    pad_stack->SetBottomMargin(0.04);
    pad_stack->SetRightMargin(0.1);
    pad_stack->SetLeftMargin(0.2);
    pad_stack->Draw();
    pad_stack->cd();
    pad_stack->cd()->SetLogy(1);
    
    cat->setIndex(i);
    RooRealVar *Nb = static_cast<RooRealVar*>(work->arg("CMS_th1x"));
    Nb->setMin(1);
    Nb->setMax(6);
    RooPlot *xframe = Nb->frame();
    xframe->SetTitle(";N_{b};Events");
    xframe->GetXaxis()->SetNdivisions(505);
    TString channel(Form("CMS_channel==%d", i));
    histData->plotOn(xframe, Cut(channel.Data()), RooFit::Name("data")); 
    
    if(plotSPlusB)
    { 
    model_s->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_qcd_morph",ibin)), LineColor(kBlack), RooFit::Name("qcd"));
    model_s->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_ttbar_morph",ibin)), LineColor(kBlue), RooFit::Name("ttbar"));
    model_s->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_wjets_morph",ibin)), LineColor(kCyan), RooFit::Name("wjets"));
    model_s->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_other_morph",ibin)), LineColor(kMagenta), RooFit::Name("other"));
    model_s->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeSig_bin%d_signal_M%i_morph",ibin,gluinoMass)), LineColor(kRed), RooFit::Name("signal"));
    } 
    else 
    { 
    model_b->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_qcd_morph",ibin)), LineColor(kBlack), RooFit::Name("qcd"));
    model_b->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_ttbar_morph",ibin)), LineColor(kBlue), RooFit::Name("ttbar"));
    model_b->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_wjets_morph",ibin)), LineColor(kCyan), RooFit::Name("wjets"));
    model_b->plotOn(xframe, Slice(*cat), ProjWData(*cat, *histData), Components(Form("shapeBkg_bin%d_other_morph",ibin)), LineColor(kMagenta), RooFit::Name("other"));
    }
    histData->plotOn(xframe, Cut(channel.Data()));
    //xframe->Draw();

    // convert xframe to historgrams
    // getObject(idx): data qcd ttbar wjets other
    TH1D *h1_data    = makeHistogram((TGraphAsymmErrors*)xframe->getObject(0)); 
    TH1D *h1_qcd     = makeHistogram((TGraphAsymmErrors*)xframe->getObject(1)); 
    TH1D *h1_ttbar   = makeHistogram((TGraphAsymmErrors*)xframe->getObject(2)); 
    TH1D *h1_wjets   = makeHistogram((TGraphAsymmErrors*)xframe->getObject(3)); 
    TH1D *h1_other   = makeHistogram((TGraphAsymmErrors*)xframe->getObject(4)); 
    TH1D *h1_signal; 
    if(plotSPlusB) h1_signal = makeHistogram((TGraphAsymmErrors*)xframe->getObject(5)); 
 
    // cosmetics
    h1cosmetic(h1_data,          Form("Data bin%i", ibin),               kBlack, 2, 1,           "N_{b}");
    h1cosmetic(h1_qcd,           Form("QCD bin%i", ibin),                kBlack, 2, kYellow,     "N_{b}");
    h1cosmetic(h1_ttbar,         Form("ttbar bin%i", ibin),              kBlack, 2, kAzure+4,        "N_{b}");
    h1cosmetic(h1_wjets,         Form("Wjets bin%i", ibin),              kBlack, 2, kOrange,        "N_{b}");
    h1cosmetic(h1_other,         Form("other bin%i", ibin),              kBlack, 2, kBlue+4,     "N_{b}");
    if(plotSPlusB) h1cosmetic(h1_signal,        Form("signal bin%i", ibin),             kBlack,   2, kRed,           "N_{b}");
    
    // stack
    THStack *st = new THStack(Form("Bin %i", ibin), Form("Bin %i", ibin));
    st->Add(h1_other); 
    st->Add(h1_wjets); 
    st->Add(h1_ttbar); 
    st->Add(h1_qcd);  // can change order of ttbat and qcd in 1-lepton bins  
    if(plotSPlusB) st->Add(h1_signal); 

    st->SetMaximum(h1_data->GetMaximum()*50);
    st->SetMinimum(0.1);
    st->Draw("hist");
    h1_data->Draw("e same"); 
    //if(plotSPlusB) h1_signal->Draw("hist same"); 
    st->GetYaxis()->SetTitle("Events");
    st->GetXaxis()->SetLabelSize(0.0);
    st->GetXaxis()->SetTitle("N_{b}");

    // legend
    TLegend *leg = new TLegend(0.6, 0.55, 0.9, 0.85);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h1_data,  "Data",     "ELP");
    leg->AddEntry(h1_qcd,   "QCD",      "F");
    leg->AddEntry(h1_ttbar, "t#bar{t}", "F");
    leg->AddEntry(h1_wjets, "W+jets",   "F");
    leg->AddEntry(h1_other, "Other",    "F");
    if(plotSPlusB) leg->AddEntry(h1_signal, Form("m_{#tilde{g}}=%i GeV",gluinoMass), "F");
    leg->Draw();

    // CMS and lumi labels
    float textSize = 0.05;
    TLatex *TexEnergyLumi = new TLatex(0.9,0.92,Form("#font[42]{%.1f fb^{-1} (13 TeV)}", 2.7));
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
    textSize=textSize-0.01;
    TLatex *TexNlep, *TexNjets, *TexMJ;
    TString binname_tstr = binname[i]; 
    if(binname_tstr.Contains("nlep1"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 1");
    if(binname_tstr.Contains("nlep0"))   TexNlep = new TLatex(0.25,0.80,"N_{lep} = 0");
    TexNlep->SetNDC();
    TexNlep->SetTextSize(textSize);
    //TexNlep->SetLineWidth(2);
    if(binname_tstr.Contains("nj45_"))   TexNjets = new TLatex(0.25,0.75,"4 #leq N_{jet} #leq 5");
    if(binname_tstr.Contains("nj67_"))   TexNjets = new TLatex(0.25,0.75,"6 #leq N_{jet} #leq 7");
    if(binname_tstr.Contains("nj89_"))   TexNjets = new TLatex(0.25,0.75,"8 #leq N_{jet} #leq 9");
    if(binname_tstr.Contains("nj8_"))    TexNjets = new TLatex(0.25,0.75,"N_{jet} #geq 8");
    if(binname_tstr.Contains("nj10_"))   TexNjets = new TLatex(0.25,0.75,"N_{jet} #geq 10");
    TexNjets->SetNDC();
    TexNjets->SetTextSize(textSize);
    //TexNjets->SetLineWidth(2);
    if(binname_tstr.Contains("lowmj"))    TexMJ = new TLatex(0.25,0.70,"500 < M_{J} < 800 GeV");
    if(binname_tstr.Contains("highmj"))   TexMJ = new TLatex(0.25,0.70,"M_{J} > 800 GeV");
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
   
    TH1D *h1_mc = (TH1D*)h1_qcd->Clone("h1_qcd");
    h1_mc->Add(h1_ttbar);
    h1_mc->Add(h1_wjets);
    h1_mc->Add(h1_other);
    if(plotSPlusB) h1_mc->Add(h1_signal);

    TH1D *h1_ratio = (TH1D*)h1_data->Clone("h1_ratio");
    h1_ratio->Divide(h1_mc); 
    h1_ratio->SetLabelSize(0.16,"XY");
    h1_ratio->SetTitleSize(0.16,"XY");
    h1_ratio->SetTitleOffset(1.0);
    h1_ratio->GetYaxis()->SetNdivisions(3,true);
    h1_ratio->GetXaxis()->SetNdivisions(5,true);
    h1_ratio->SetMinimum(0);
    h1_ratio->SetMaximum(2);
    h1_ratio->SetYTitle("Data/MC");
    h1_ratio->Draw("e");  
 
    TLine *l = new TLine(1,1,5,1);
    l->SetLineStyle(2);
    l->Draw("same");

    c->Print(Form("plots/fit_%s.pdf", binname[i].c_str()));
  
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
    if(plotSPlusB) delete h1_signal; 
  }
  
  if(plotSPlusB) {
    plotFitPulls(result_s->floatParsFinal(), "plots/pulls_nopdf.pdf", "base");
    plotFitPulls(result_s->floatParsFinal(), "plots/pulls_pdf.pdf", "pdf");
    plotFitPulls(result_s->floatParsFinal(), "plots/pulls_mcstats.pdf", "mcstat");
  }
  else {
    plotFitPulls(result_b->floatParsFinal(), "plots/pulls_nopdf.pdf", "base");
    plotFitPulls(result_b->floatParsFinal(), "plots/pulls_pdf.pdf", "pdf");
    plotFitPulls(result_b->floatParsFinal(), "plots/pulls_mcstats.pdf", "mcstat");
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

void plotFitPulls(const RooArgList &pulls, const TString &pullString, const std::string &type)
{
  TCanvas *cPull = new TCanvas; 
  cPull->SetBottomMargin(0.2);

  int size = pulls.getSize();

  int goodVars=0;
  for(int i=0; i<size; i++) {
    RooRealVar *pullVar = static_cast<RooRealVar*>((pulls.at(i)));
    TString name(pullVar->GetName());
    if(name.BeginsWith("w_pdf") && type.find("pdf")!=std::string::npos) continue;
    else if(name.BeginsWith("mcstat") && type.find("mcstat")!=std::string::npos) continue;
    else if((name.BeginsWith("w_pdf") || name.BeginsWith("mcstat")) && type.find("base")!=std::string::npos) continue;
    if(!name.BeginsWith("r")) goodVars++;
  }
  std::cout << "Found " << goodVars << " nuisances to plot" << std::endl;

  TH1D *h = new TH1D("h", "h", goodVars, 0, goodVars);
  double pullRange=2.0;
  h->SetMaximum(pullRange);
  h->SetMinimum(-pullRange);

  int iGood=0;
  double sumChi2=0.0;
  for(int i=0; i<size; i++) {
    RooRealVar *pullVar = static_cast<RooRealVar*>(pulls.at(i));
    double value = pullVar->getVal();
    TString name(pullVar->GetName());
    if(!name.BeginsWith("w_pdf") && type.find("pdf")!=std::string::npos) continue;
    else if(!name.BeginsWith("mcstat") && type.find("mcstat")!=std::string::npos) continue;
    else if((name.BeginsWith("w_pdf") || name.BeginsWith("mcstat")) && type.find("base")!=std::string::npos) continue;
    if(!name.BeginsWith("r") ) {
      iGood++;
      double binErrorLo = fabs(pullVar->getErrorLo());
      double binErrorHi = fabs(pullVar->getErrorHi());
      double binError = (binErrorLo+binErrorHi)/2;
      double eps=0.0001;
      // if one of the errors is zero, the symmetrized error will be too low by a factor of two
      if(binErrorLo<eps || binErrorHi<eps) binError*=2;
      h->SetBinContent(iGood, value);
      h->SetBinError(iGood, binError);
      std::cout.precision(3);
      std::cout << " & \\texttt{" << name << "} & $" << value << " \\pm " <<  binError << "$\\\\" << std::endl;
      sumChi2+=pow(value/binError,2);
      h->GetXaxis()->LabelsOption("v");
      h->GetXaxis()->SetBinLabel(iGood, pullVar->GetName());
      h->GetYaxis()->SetTitle("Post-fit pulls");
    }
  }
  
  std::cout << "pull chi2/ndof: " << sumChi2 << "/" << iGood << std::endl;

  h->Draw();

  TBox *b = new TBox(0, -1, goodVars, 1);
  b->SetFillStyle(3003);
  b->SetFillColor(kBlue);
  b->Draw();
  h->Draw("same");

  cPull->Print(pullString);  
  TString pullStringC = pullString;
  pullStringC.ReplaceAll(".pdf", ".C");
  cPull->Print(pullStringC);

}
