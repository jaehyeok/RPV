//----------------------------------------------------------------------------
// utilities_macros - Various functions used accross the code
//----------------------------------------------------------------------------

#ifndef INT_ROOT
#include "utilities_macros.hpp"
#endif

#include <cmath>
#include <vector>

#include <iostream>
#include <string>
#include <stdexcept>
#include <unistd.h>

#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TString.h"
#include "TColor.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "TSystem.h"
#include "TDirectory.h"
#include "TROOT.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"

using namespace std;

void plot_distributions(vector<sfeats> Samples, vector<hfeats> vars, TString luminosity, 
                        TString filetype, TString namestyle, TString dir, bool doRatio, bool showcuts){
  TH1::SetDefaultSumw2();

  TString outfolder("plots/"+dir);
  gSystem->mkdir(outfolder, kTRUE);

  TString CMStype("");
  if(namestyle.Contains("_Supplementary")) {
    CMStype = "Supplementary";
    namestyle.ReplaceAll("_Supplementary","");
  }
  if(namestyle.Contains("_Preliminary")) {
    CMStype = "Preliminary";
    namestyle.ReplaceAll("_Preliminary","");
  }
  if(namestyle.Contains("_WorkInProgress")) {
    CMStype = "Work In Progress";
    namestyle.ReplaceAll("_WorkInProgress","");
  }
  bool normByBin=false;
  if(namestyle.Contains("_normalizeByBin")) {
    normByBin=true;
    namestyle.ReplaceAll("_normalizeByBin","");
  }

  if (doRatio) namestyle = "CMSPaper";
  styles style(namestyle);
  if(namestyle.Contains("CMSPaper")) style.nDivisions = 706;
  if (doRatio){
    style.LabelSize    *= 1.1;
    style.LegendSize   *= 1.0;
    style.TitleSize    *= 1.1;
    style.yTitleOffset /= 1.3;
    style.xTitleOffset /= 1.08;
  }

  if(normByBin) style.xTitleOffset *= 0.86;

  if(showcuts) style.LegendSize *= 0.85;
  style.setDefaultStyle();
  TCanvas can;
  can.cd();
  TPad *pad(NULL), *bpad(NULL); //bpad (stands for bottom pad) is for ratio
  if (doRatio){
    float bpadHeight = 0.3;
    pad = new TPad("tpad","tpad",0.,bpadHeight,1.,1.); // assign 
    pad->SetBottomMargin(0.02);
    pad->SetTopMargin(style.PadTopMargin+0.01);
    pad->Draw();    
    bpad = new TPad("bpad","bpad",0.,0.,1.,bpadHeight+0.005); // assign 
    bpad->SetTopMargin(0.);
    bpad->SetBottomMargin(2.35*style.PadBottomMargin);
    bpad->SetFillStyle(4000);
    bpad->Draw();
  } else {
    pad = static_cast<TPad *>(can.cd());
  }

  // Reading ntuples
  vector<TChain *> chain;
  for(unsigned sam(0); sam < Samples.size(); sam++){
    chain.push_back(new TChain("tree"));
    for(unsigned insam(0); insam < Samples[sam].file.size(); insam++){
      // cout<<"Reading "<<Samples[sam].file[insam]<<endl;
      chain[sam]->Add(Samples[sam].file[insam]);
      // cout<<"Entries "<<chain[sam]->GetEntries()<<endl;
    }
  }

  TString lumi_nodot = luminosity; lumi_nodot.ReplaceAll(".","p");
  TString plot_tag("_lumi"+lumi_nodot+filetype);
  float minLog = 0.5, fracLeg = 0.36; // Fraction of the histo pad devoted to the legend
//  float minLog = 0.01, fracLeg = 0.36; // Fraction of the histo pad devoted to the legend // FIXME for objectreview

  double legLeft(style.PadLeftMargin+0.03), legRight(1-style.PadRightMargin-0.03);
  double legY(1-style.PadTopMargin-0.020)/*-0.027*/, legSingle = 0.052;//= 0.052
  if (doRatio) {legY=1-style.PadTopMargin-0.020; legSingle = 0.052;}
  double legW = 0.33, legH = legSingle*(vars[0].samples.size()+1)/2;
  double legX1[2] = {legLeft, (legLeft+legRight)/2};
  TLegend leg[2]; int nLegs(2);
  for(int ileg(0); ileg<nLegs; ileg++){
    leg[ileg].SetX1NDC(legX1[ileg]); leg[ileg].SetX2NDC(legX1[ileg]+legW); 
    leg[ileg].SetY1NDC(legY-legH); leg[ileg].SetY2NDC(legY); 
    leg[ileg].SetTextSize(style.LegendSize); leg[ileg].SetFillColor(0); 
    leg[ileg].SetFillStyle(0); leg[ileg].SetBorderSize(0);
    leg[ileg].SetTextFont(style.nFont); 
//    leg[ileg].SetTextSize(0.03);  // FIXME for objectreview
  }
  TLine line; line.SetLineColor(1); line.SetLineWidth(5); line.SetLineStyle(2);
  vector< vector<TH1D*> > histo[2];
  vector<TH1D*> varhisto;
  vector<float> nentries;
  TString hname, pname, variable, samVariable, leghisto, totCut, title, ytitle, lumilabel, cmslabel;
  for(unsigned var(0); var<vars.size(); var++){
    bool variableBins = vars[var].minx == -1;
    if (vars[var].minx == -1) vars[var].minx = vars[var].binning[0];
    const unsigned Nsam(vars[var].samples.size());
    legH = (Nsam<=3?legSingle*Nsam:legSingle*(Nsam+1)/2);
    // Calculating fraction of internal pad taken by the legend, and adding a 4% buffer
    fracLeg = (legH+1-style.PadTopMargin-legY)/(1-style.PadTopMargin-style.PadBottomMargin) + 0.01;
    for(int ileg(0); ileg<nLegs; ileg++){
	leg[ileg].SetY1NDC(legY-legH);
	leg[ileg].SetY2NDC(legY); 
	}
    leg[1].SetX1NDC(legX1[1]+vars[var].moveRLegend); leg[1].SetX2NDC(legX1[1]+legW+vars[var].moveRLegend); 

    cout<<endl;

    bool someBands = false;
    // Generating vector of histograms
    title = cuts2title(vars[var].cuts);
    if(namestyle.Contains("CMSPaper") && !showcuts) title = "";
    for(unsigned his(0); his < 2; his++){
      varhisto.resize(0);
      for(unsigned sam(0); sam < Nsam; sam++){ 
	if(Samples[vars[var].samples[sam]].doBand) someBands = true;
        hname = "histo"; hname += var; hname += his; hname += sam;  
	delete gROOT->FindObject(hname); // For some reason, the deletion at the end is not enough
        if(variableBins) { 
          vars[var].minx = vars[var].binning[0];
          varhisto.push_back(new TH1D(hname, title, vars[var].nbins, vars[var].binning));
        }else {
          varhisto.push_back(new TH1D(hname, title, vars[var].nbins, vars[var].minx, vars[var].maxx));
        }
      }
      histo[his].push_back(varhisto);
    }
    nentries.resize(Nsam);
    variable = vars[var].varname;
    float maxhisto(-999);
    int nbkg(0);
    for(unsigned sam(Nsam-1); sam < Nsam; sam--){
      int isam = vars[var].samples[sam];
      if(!Samples[isam].isSig && !Samples[isam].isData) nbkg++;
      samVariable = Samples[isam].samVariable;
      totCut = Samples[isam].factor+"*"+luminosity+"*weight*("+vars[var].cuts+"&&"+Samples[isam].cut+")";
//      totCut = Samples[isam].factor+"*"+luminosity+"*frac16*frac1718*weight*("+vars[var].cuts+"&&"+Samples[isam].cut+")"; //FIXME
//      totCut = Samples[isam].factor+"*"+luminosity+"*weight*("+vars[var].cuts+"&&"+Samples[isam].cut+")"; //FIXME
      if(Samples[isam].isData) totCut= vars[var].cuts+"&&"+Samples[isam].cut;
      if(vars[var].PU_reweight && !Samples[isam].isData) totCut = Samples[isam].factor+"*"+luminosity+"*weight*wpu*("+vars[var].cuts+"&&"+Samples[isam].cut+")";
      cout<<"total cut: " << totCut<<endl;
      //histo[0][var][sam]->Sumw2();
      histo[0][var][sam]->SetBinErrorOption(TH1::kPoisson);
      if(samVariable=="noPlot") chain[isam]->Project(histo[0][var][sam]->GetName(), variable, totCut);
      else chain[isam]->Project(histo[0][var][sam]->GetName(), samVariable, totCut);
      histo[0][var][sam]->SetTitle(title); 
      if(vars[var].addOverflow) 
	histo[0][var][sam]->SetBinContent(vars[var].nbins,
	histo[0][var][sam]->GetBinContent(vars[var].nbins)+
	histo[0][var][sam]->GetBinContent(vars[var].nbins+1));
      
        nentries[sam] = histo[0][var][sam]->Integral(1,vars[var].nbins);
        if(nentries[sam]<0) nentries[sam]=0;
        ytitle = "Events";
        if(vars[var].normalizeByBin){
	ytitle = "Events [% by bin]";
      }      


      if(!namestyle.Contains("CMSPaper") || showcuts) {
        // ytitle = "Events for "+luminosity+" fb^{-1}";
        lumilabel = "";
        cmslabel = "";
      } else {
        //lumilabel = TString::Format("L = %1.f",luminosity.Atof()*1000.)+" pb^{-1} (13 TeV)";
	lumilabel = TString::Format("#scale[0.8]{13 TeV}");
        cmslabel = "#font[62]{CMS} #scale[0.8]{#font[52]{Simulation}}";
        if(CMStype=="Supplementary")cmslabel = "#scale[0.8]{#font[62]{CMS}} #scale[0.6]{#font[52]{Supplementary (Simulation)}}";
	bool contains_data = false;
	for(unsigned is=0;is<Samples.size();is++){if(Samples[is].isData){contains_data=true; break;} }
	if(contains_data){ 
	  cmslabel = "#font[62]{CMS}";
	  cmslabel += " #scale[0.8]{#font[52]{"+CMStype+"}}";  
	  lumilabel = TString::Format("%1.1f",luminosity.Atof())+" fb^{-1} (13 TeV)";}
      }
      if(vars[var].unit!="") {
        int digits(0);
        float binwidth((vars[var].maxx-vars[var].minx)/static_cast<float>(vars[var].nbins));
        if(binwidth<1) digits = 1;
        if (!variableBins) ytitle += ("/("+RoundNumber(binwidth,digits) +" "+vars[var].unit+")");
      }
      histo[0][var][sam]->SetYTitle(ytitle);
      // Cloning histos for later
      for(int bin(0); bin<=histo[0][var][sam]->GetNbinsX()+1; bin++){
        double val(histo[0][var][sam]->GetBinContent(bin));
        histo[1][var][sam]->SetBinContent(bin, val);
        //if(Samples[isam].isData) histo[0][var][sam]->SetBinError(bin, sqrt(val));
        histo[1][var][sam]->SetBinError(bin, histo[0][var][sam]->GetBinErrorUp(bin));
      }
    }
    
    if(nbkg>0 && (vars[var].whichPlots.Contains("0") || vars[var].whichPlots.Contains("1") 
                  || vars[var].whichPlots.Contains("2"))){
      //// Plotting lumi-weighted distributions in histo[0], and then area-normalized in histo[1] ///
      int bkgind(-1);
      unsigned int last_hist=9999;
      float normalization_ratio=1; 
      for(unsigned sam(Nsam-1); sam < Nsam; sam--){
        int isam = vars[var].samples[sam];
        bool noStack = Samples[isam].isSig || Samples[isam].isData;
        if(!noStack){ // Adding previous bkg histos
	  if(sam<last_hist) last_hist=sam;
          for(unsigned bsam(sam+1); bsam < Nsam; bsam++){
            histo[0][var][sam]->Add(histo[0][var][bsam]);
            break;
          }
	  histo[0][var][sam]->SetFillStyle(1001);
	  if(Samples[isam].doBand){
	    histo[0][var][sam]->SetFillColor(Samples[isam].color-12);
	    histo[0][var][sam]->SetLineColor(Samples[isam].color);
	    histo[0][var][sam]->SetLineWidth(3);
	  } else {
	    histo[0][var][sam]->SetFillColor(Samples[isam].color);
	    histo[0][var][sam]->SetLineColor(1);
	    histo[0][var][sam]->SetLineWidth(1);
	  }
          bkgind = sam;
        } else {
          histo[0][var][sam]->SetLineColor(Samples[isam].color);
          if(Samples[isam].isData){
            histo[0][var][sam]->SetMarkerStyle(20);
            histo[0][var][sam]->SetMarkerSize(1.2);         
            histo[0][var][sam]->SetLineWidth(2);
          } else {
            if(someBands) histo[0][var][sam]->SetLineWidth(3);
	    else histo[0][var][sam]->SetLineWidth(6);
            histo[0][var][sam]->SetLineStyle(abs(Samples[isam].style));
	    if(vars[var].normalizeByBin){
	      histo[0][var][sam]->SetLineColor(Samples[isam].color);
	      histo[0][var][sam]->SetLineWidth(0);
	      }
          }
          if(Samples[isam].doStack)  histo[0][var][sam]->Add(histo[0][var][bkgind]);
	  if(vars[var].normalizeByBin){ histo[0][var][sam]->SetLineWidth(0);histo[0][var][sam]->SetLineColor(Samples[isam].color);}
        }

      }
      TString norm_s("");
      if(vars[var].normalize || doRatio){
	double err_num(0), err_den(0);
	float num = histo[0][var][0]->IntegralAndError(1,histo[0][var][0]->GetNbinsX(),err_num);
	float den = histo[0][var][last_hist]->IntegralAndError(1,histo[0][var][last_hist]->GetNbinsX(),err_den);
	normalization_ratio = num/den; //I want this to crash if den=0
	double err_tot(den/num*sqrt(pow(err_num/num,2)+pow(err_den/den,2)));
	err_tot = num/den*sqrt(pow(err_num/num,2)+pow(err_den/den,2));
	//cout<<"Histogram [MC] is ("<<RoundNumber((den/num-1)*100,1)
	//    <<" +- "<<RoundNumber(err_tot*100,1)<<")% larger than markers [data]"<<endl; 
	norm_s = "("+RoundNumber((num/den)*100,1)+"#pm"+RoundNumber(err_tot*100,1)+")%";
	cout<<"Markers [data] are ("<<RoundNumber((num/den)*100,1)
	    <<" +- "<<RoundNumber(err_tot*100,1)<<")% the histogram [MC]. Data yield is "<<num<<endl;
      }
      
      for(unsigned sam(Nsam-1) ; sam < Nsam ; sam--){
	int isam = vars[var].samples[sam];
	int maxbin = 20;
	if(title.Contains("mus")) maxbin = 10;	
	maxbin =2 ;
        cout<< Samples[isam].label << " : " << "first bin content:  " <<histo[0][var][sam]->Integral(1,1)  << endl;
        cout<< Samples[isam].label << " : " << "second bin content: " <<histo[0][var][sam]->Integral(2,2)  << endl;
        cout<< Samples[isam].label << " : " << "third bin content:  " <<histo[0][var][sam]->Integral(3,3)  << endl;
	double error1(0), errorother(0);
	double quad=0;
	for(unsigned int ibin=1 ; ibin<maxbin ; ibin++){
		double temp;
		temp = histo[0][var][sam]->GetBinError(ibin+1);
		quad = quad + temp*temp;
	}
	error1 = histo[0][var][sam]->GetBinError(1);
	errorother = TMath::Sqrt(quad);
        cout<< Samples[isam].label << " : " << "first bin error : " << error1 << endl;
	cout<< Samples[isam].label << " : " << "second bin error: " << histo[0][var][sam]->GetBinError(2) << endl;
	cout<< Samples[isam].label << " : " << "third bin error:  " << histo[0][var][sam]->GetBinError(3) << endl;
	//cout<< Samples[isam].label << " : " << "err first bin :" <<histo[0][var][sam]->GetBinError(1) << endl;
	//for(unsigned int i=0;i<maxbin;i++) 
//	cout<< Samples[isam].label << " : " << "bin 5 to max :" <<histo[0][var][sam]->Integral(5,maxbin) << endl;	
      }

      for(unsigned sam(Nsam-1); sam < Nsam; sam--){
	int isam = vars[var].samples[sam];
	//bool noStack = Samples[isam].isSig || Samples[isam].isData;
	if(sam>=last_hist && vars[var].normalize && !Samples[isam].isSig){ 
	  histo[0][var][sam]->Scale(normalization_ratio); //FIXME
	  nentries[sam]*= normalization_ratio;

	}
	
	if(vars[var].normalizeByBin){
	  for(int ibin=1;ibin<=histo[0][var][sam]->GetNbinsX();ibin++){
	    cout<<"bin content "<<ibin<<": "<<histo[0][var][sam]->GetBinContent(ibin)<<endl;
	    cout<<"denominator :"<<histo[0][var][last_hist]->GetBinContent(ibin)<<endl;
	    float fractional_content;
	    if(histo[0][var][last_hist]->GetBinContent(ibin)>0) fractional_content = 100.*histo[0][var][sam]->GetBinContent(ibin)/histo[0][var][last_hist]->GetBinContent(ibin);
	    else fractional_content=0.;
	    cout<<"fraction content: "<<fractional_content<<endl;
	    histo[0][var][sam]->SetBinContent(ibin,fractional_content);
	  }
	}


        if(Samples[isam].mcerr){ histo[0][var][sam]->SetLineWidth(4);  histo[0][var][sam]->SetMarkerStyle(20); 
          //histo[0][var][sam]->SetMarkerColor(Samples[isam].color);
          histo[0][var][sam]->SetMarkerSize(1.2);
          histo[0][var][sam]->SetLineStyle(abs(Samples[isam].style));
          if(Nsam>=3) histo[0][var][2]->SetFillColorAlpha(Samples[2].color, 0.5);
        }
        double maxval(histo[0][var][sam]->GetMaximum());
        if(maxhisto < maxval)  maxhisto = maxval;
	//maxval += histo[0][var][sam]->GetBinErrorUp(histo[0][var][sam]->GetMaximumBin());//FIXME
	//if((Samples[isam].isData || Samples[isam].mcerr) && maxhisto < maxval) maxhisto = maxval;//FIXME
      }


      // First loop over samples
      pad->cd();
      for(int ileg(0); ileg<nLegs; ileg++) leg[ileg].Clear();
      unsigned legcount(0);
      int firstplotted(-1);
      for(unsigned sam(0); sam < Nsam; sam++){
        int isam = vars[var].samples[sam];
        leghisto = Samples[isam].label;
        if(!namestyle.Contains("CMSPaper") || showcuts) leghisto += " [N=" + RoundNumber(nentries[sam],0) + "]";
        //leghisto += " [N=" + RoundNumber(nentries[sam],0) + "]";
        bool noStack = Samples[isam].isSig || Samples[isam].isData;
        unsigned ileg = (Nsam<=3?0:legcount>=(Nsam+1)/2);
        if(!noStack){
          if(Samples[isam].doBand) leg[ileg].AddEntry(histo[0][var][sam], leghisto,"l");//FIXME
	  else leg[ileg].AddEntry(histo[0][var][sam], leghisto,"f");
          legcount++;
          if(firstplotted < 0) {
            if(!Samples[isam].mcerr) {
	      if(!Samples[isam].doBand) histo[0][var][sam]->Draw("hist");
	      else {
		histo[0][var][sam]->Draw("E2");
		TString hcname("hclone"); hcname += var;
		TH1F *hclone = static_cast<TH1F*>(histo[0][var][sam]->Clone(hcname));
		hclone->SetLineColor(Samples[isam].color);
		hclone->SetLineWidth(3);
		if(vars[var].normalizeByBin) hclone->SetLineWidth(0);
		hclone->SetFillColor(0);
		hclone->Draw("hist same");
	      }
            } else histo[0][var][sam]->Draw("E0LP");
            firstplotted = sam;
            style.setTitles(histo[0][var][sam],vars[var].title, ytitle, cmslabel, lumilabel);
          } else {
            if(!Samples[isam].mcerr) histo[0][var][sam]->Draw("hist same");
            else histo[0][var][sam]->Draw("E0LP same");
          }
        } else {
          if(Samples[isam].isSig) leg[ileg].AddEntry(histo[0][var][sam], leghisto,"l");
          else leg[ileg].AddEntry(histo[0][var][sam], leghisto,"elp");
          legcount++;
        }
      }
      for(int sam(Nsam-1); sam >= 0; sam--){
        int isam = vars[var].samples[sam];
        if(Samples[isam].isSig){if(!Samples[isam].mcerr) histo[0][var][sam]->Draw("hist same"); else histo[0][var][sam]->Draw("EP same"); }
        //if(Samples[isam].isData) histo[0][var][sam]->Draw("e0 same");
        if(Samples[isam].isData) histo[0][var][sam]->Draw("same");
      }
      for(int ileg(0); ileg<nLegs; ileg++) leg[ileg].Draw(); 

      // Setting Y-axis for log_lumi plot
      if(histo[0][var][firstplotted]->GetMinimum() > minLog) histo[0][var][firstplotted]->SetMinimum(minLog);
      float maxpadLog(maxhisto*10*exp(fracLeg*log(maxhisto/minLog)/(1-fracLeg)));
      histo[0][var][firstplotted]->SetMinimum(minLog);
      histo[0][var][firstplotted]->SetMaximum(maxpadLog);
      /*for(int bin(0); bin<=histo[0][var][firstplotted]->GetNbinsX()+1; bin++){
	histo[0][var][firstplotted]->SetBinError(bin,0);//FIXME//command out this line when the testing pre-firing issue
      }// */
      if (!doRatio) style.moveYAxisLabel(histo[0][var][firstplotted], maxpadLog, true);
      histo[0][var][firstplotted]->Draw("axis same");
      if(vars[var].cut>0) line.DrawLine(vars[var].cut, 0, vars[var].cut, maxhisto*1.05);

      //ratio
      TH1D* hratio_data(NULL);
      TLine* l1(NULL);
      if (doRatio){
        // TH1D* hratio_mc = static_cast<TH1D*>(histo[0][var][firstplotted]->Clone());
        TH1D* hdata(NULL);
        unsigned ndatasam(0);
        for(unsigned sam(Nsam-1); sam < Nsam; sam--) {
          int isam = vars[var].samples[sam];
          if (Samples[isam].isData || (Samples[isam].mcerr && sam==0)) {
            if (ndatasam==0) hdata = static_cast<TH1D*>(histo[0][var][sam]->Clone());
            else hdata->Add(histo[0][var][sam]); //in case the different PDs are put in as separate samples
            ndatasam++;
          }
        }        
        if (ndatasam) {
	  float maxRatio = 1.9;
	  if(vars[var].maxRatio > 0) maxRatio = vars[var].maxRatio;
          hratio_data = static_cast<TH1D*>(hdata->Clone());
          hratio_data->SetTitle("");
          hratio_data->Divide(histo[0][var][firstplotted]);
          hratio_data->GetYaxis()->SetRangeUser(0.1,maxRatio);//FIXME
	  // L1 Prefiring Issue
//          hratio_data->GetYaxis()->SetRangeUser(0.75,1.25);//FIXME // for L1 Prefiring Issue
          hratio_data->GetXaxis()->SetLabelOffset(0.025);
          hratio_data->GetXaxis()->SetLabelSize(style.LabelSize*2.2);
          hratio_data->GetYaxis()->SetLabelSize(style.LabelSize*2.1);
          hratio_data->GetYaxis()->SetTitle("Data / MC ");
	  if(Nsam==2) {
	    size_t idata = vars[var].samples[0];
	    if(Samples[idata].label.Contains("2l")) hratio_data->GetYaxis()->SetTitle("2l / 1l");
	    else hratio_data->GetYaxis()->SetTitle("high / low");
	  }
          hratio_data->GetXaxis()->SetTitle(histo[0][var][firstplotted]->GetXaxis()->GetTitle());
          hratio_data->GetYaxis()->SetTitleSize(style.TitleSize*3);
          hratio_data->GetYaxis()->SetTitleOffset(0.5); //can't use relative size, since somehow it changes between plots...
          hratio_data->GetXaxis()->SetTitleSize(style.TitleSize*3);
          hratio_data->GetXaxis()->SetTitleOffset(style.xTitleOffset*0.9);
          //move  the labels ou tof the way
          histo[0][var][firstplotted]->GetXaxis()->SetLabelOffset(2.);
          //line at 1
          bpad->cd();
          //hratio_data->Draw("e0");     //comment out when drawing pre-fit SR MJ templates
          hratio_data->Draw();
	  //          for (int ko=0; ko< hratio_data->GetNbinsX(); ko++){
          //  cout<<hratio_data->GetBinLowEdge(ko+1)<<" "<<(hratio_data->GetBinLowEdge(ko+1)+hratio_data->GetBinWidth(ko+1))
          //      <<hratio_data->GetBinContent(ko+1)<<std::endl;
          //}

          l1 = new TLine(histo[0][var][firstplotted]->GetXaxis()->GetXmin(), 1., histo[0][var][firstplotted]->GetXaxis()->GetXmax(), 1.);
          l1->SetLineStyle(2);
          l1->Draw("same");
        } else {
          cerr<<"ERROR: Ratio plots currently only supported for plots with data."<<endl;
          exit(1);
        }
        delete hdata;
      }

      //label lumi
      pad->cd();
      if(!namestyle.Contains("CMSPaper") || showcuts) {
	TString lumilbl = TString::Format("%1.1f",luminosity.Atof())+" fb^{-1}, "+norm_s;
//	TString lumilbl = TString::Format("%1.1f",luminosity.Atof())+" fb^{-1}"; // FIXME for pre-fit SR
//	TString lumilbl = ""; // FIXME for HEM
	TLatex llbl;
	llbl.SetTextSize(style.LegendSize); 
	llbl.SetNDC(); llbl.SetTextAlign(33);
	llbl.DrawLatex(1-style.PadRightMargin-0.02,leg[0].GetY1NDC()-0.02,lumilbl);
      }
      // label nb
      if(vars[var].tag.Contains("results") && vars[var].cuts.Contains("nbm")){
	TLatex tla;
	tla.SetTextSize(0.055);
	tla.SetTextFont(42);
	if(vars[var].cuts.Contains("nbm==1")) tla.DrawLatexNDC(0.73,0.64,"#font[62]{N_{b} = 1}");
	if(vars[var].cuts.Contains("nbm>=2")) tla.DrawLatexNDC(0.73,0.64,"#font[62]{N_{b} #geq 2}");
      }

      if(vars[var].normalizeByBin){

	float textSize = 0.055;
	TLatex *TexNlep = new TLatex();
	TLatex *TexNjets = new TLatex();
	TLatex *TexMJ = new TLatex();
	TString binname_tstr = vars[var].cuts;
	if(binname_tstr.Contains("(nmus+nels)==1"))   TexNlep = new TLatex(0.22,0.33,"N_{lep} = 1");
	if(binname_tstr.Contains("(nmus+nels)==0"))   TexNlep = new TLatex(0.22,0.33,"N_{lep} = 0");
	TexNlep->SetNDC();
	TexNlep->SetTextSize(textSize);
	//TexNlep->SetLineWidth(2);
	if(binname_tstr.Contains("njets<="))   TexNjets = new TLatex(0.22,0.26,"4 #leq N_{jet} #leq 5");
	if(binname_tstr.Contains("njets<=7"))   TexNjets = new TLatex(0.22,0.26,"6 #leq N_{jet} #leq 7");
	if(binname_tstr.Contains("njets<=9"))   TexNjets = new TLatex(0.22,0.26,"8 #leq N_{jet} #leq 9");
	if(binname_tstr.Contains("njets>=8")&&!binname_tstr.Contains("njets<=9"))    TexNjets = new TLatex(0.22,0.26,"N_{jet} #geq 8");
	if(binname_tstr.Contains("njets>=10"))   TexNjets = new TLatex(0.22,0.26,"N_{jet} #geq 10");
	TexNjets->SetNDC();
	TexNjets->SetTextSize(textSize);
	//TexNjets->SetLineWidth(2);
	if(binname_tstr.Contains("mj>500"))    TexMJ = new TLatex(0.22,0.19,"500 < M_{J} < 800 GeV");
	if(binname_tstr.Contains("mj>800"))   TexMJ = new TLatex(0.22,0.19,"M_{J} > 800 GeV");
	TexMJ->SetNDC();
	TexMJ->SetTextSize(textSize);
	//TexMJ->SetLineWidth(2);

	TexNlep->Draw("same");
	TexNjets->Draw("same");
	TexMJ->Draw("same");



      }


      //save canvas
      pad->SetLogy(1);
      pname = outfolder+"/log_lumi_"+vars[var].tag+plot_tag;
      if(vars[var].normalize) pname.ReplaceAll("/log_lumi","/log_norm");
      if(!vars[var].skiplog && (vars[var].whichPlots.Contains("0") || vars[var].whichPlots.Contains("1")))
        can.SaveAs(pname);
      pad->SetLogy(0);
 
      // Setting Y-axis for lumi plot (non-log)
      float minhisto(0), maxpad(minhisto + (maxhisto-minhisto)/(1-fracLeg));
      if(vars[var].maxYaxis > 0) maxpad = vars[var].maxYaxis;
      histo[0][var][firstplotted]->SetMinimum(minhisto);
      histo[0][var][firstplotted]->SetMaximum(maxpad);
      // pad = static_cast<TPad *>(can.cd(1));
      if (!doRatio) style.moveYAxisLabel(histo[0][var][firstplotted], maxpad, false);
      pname = outfolder+"/lumi_"+vars[var].tag+plot_tag;
      if(vars[var].normalize) pname.ReplaceAll("/lumi","/norm");
      if(vars[var].whichPlots.Contains("0") || vars[var].whichPlots.Contains("2")) can.SaveAs(pname);
    } // Lumi plots


    //////////// Plotting area-normalized distributions ////////////
    maxhisto = -999;
    for(int ileg(0); ileg<nLegs; ileg++) leg[ileg].Clear();
    unsigned legcount = 0;
    for(unsigned sam(0); sam < Nsam; sam++){
      int isam = vars[var].samples[sam];
      histo[1][var][sam]->SetLineColor(Samples[isam].color);
      histo[1][var][sam]->SetMarkerColor(Samples[isam].color);
      histo[1][var][sam]->SetMarkerStyle(20);
      histo[1][var][sam]->SetLineStyle(abs(Samples[isam].style));
      histo[1][var][sam]->SetLineWidth(4);
      if(nentries[sam]) histo[1][var][sam]->Scale(100./nentries[sam]);
      if(maxhisto < histo[1][var][sam]->GetMaximum()) maxhisto = histo[1][var][sam]->GetMaximum();
      style.setTitles(histo[1][var][sam],vars[var].title, "", cmslabel, lumilabel);
      if(sam==0){
	histo[1][var][sam]->SetXTitle(vars[var].title);
	ytitle = "% events";
	if(vars[var].unit!="") {
	  int digits(0);
	  float binwidth((vars[var].maxx-vars[var].minx)/static_cast<float>(vars[var].nbins));
	  if(binwidth<1) digits = 1;
	  if (!variableBins) ytitle += ("/("+RoundNumber(binwidth,digits) +" "+vars[var].unit+")");
	}	
        histo[1][var][sam]->SetYTitle(ytitle);
        if(Samples[isam].style>0) histo[1][var][sam]->Draw("hist E"); //220727 draw error bar
        else histo[1][var][sam]->Draw("E");
      } else {
        if(Samples[isam].style>0) histo[1][var][sam]->Draw("hist E same"); //220727 draw error bar
        else histo[1][var][sam]->Draw("E same");
      }
      leghisto = Samples[isam].label;
      unsigned ileg = (Nsam<=5?0:legcount>=(Nsam+1)/2);
      if(!namestyle.Contains("CMSPaper") || showcuts){
        if(vars[var].nevents.at(sam)<0){
	  leg[ileg].SetX1NDC(0.23); leg[ileg].SetX2NDC(0.43); //220727 make plot look pretty
	  leg[ileg].SetY1NDC(0.2); leg[ileg].SetY2NDC(0.35);
//	  if(sam>1) {     //230330 make plot look pretty, for Figure21~23 (mjsyst), Figure2
	  if(sam>3) {    //230330 make plot look pretty, for Figure15, pre-postfit plots (nbm=0 plots)
	    leg[ileg].SetX1NDC(0.6); leg[ileg].SetX2NDC(0.8); //220727 make plot look pretty, Figure2
	    leg[ileg].SetY1NDC(0.55); leg[ileg].SetY2NDC(0.9);  //230109 make plot look pretty (Nb bin: 4 -> 5), Figure2
//            leg[ileg].SetTextSize(0.75*style.LegendSize);    // 241223 Figure2, Figure21~23 // when plotting Figure15, pre-postfit plots, comment out this line
	  }
          leghisto += " [#mu=";
          int digits(0);
          if(histo[1][var][sam]->GetMean()<30) digits = 1;
          leghisto += RoundNumber(histo[1][var][sam]->GetMean(),digits) + "]";
        } else{
	    leg[ileg].SetX1NDC(0.5); leg[ileg].SetX2NDC(0.7); //220727 make plot look pretty
	    leg[ileg].SetY1NDC(0.5); leg[ileg].SetY2NDC(0.7);
          leg[ileg].SetX1NDC(0.24); leg[ileg].SetX2NDC(0.7);    //231018 make plot look pretty, for Figure15 (nbm=0 plots)
          leg[ileg].SetTextSize(0.75*style.LegendSize);
          //leg[ileg].SetTextSize(0.5*style.LegendSize);
	  if(vars[var].varname.Contains("tks")) leghisto +=  "[N_{tks} = " + RoundNumber(nentries[sam],1) + ", from N_{events} = "
            +RoundNumber(vars[var].nevents.at(sam),1)+"]";
        }
      }
      
      if(Samples[isam].style>0) leg[ileg].AddEntry(histo[1][var][sam], leghisto, "l");
      else leg[ileg].AddEntry(histo[1][var][sam], leghisto, "p");
      legcount++;
    } // Loop over samples
//    for(int ileg(0); ileg<nLegs; ileg++) {leg[ileg].Draw(); leg[ileg].SetTextSize(0.03);} //FIXME for objectreview
    for(int ileg(0); ileg<nLegs; ileg++) leg[ileg].Draw();
    if(vars[var].cut>0) line.DrawLine(vars[var].cut, 0, vars[var].cut, maxhisto*1.05);

    // Setting Y-axis for shapes plot (non-log)
    float minhisto(0), maxpad(minhisto + (maxhisto-minhisto)/(1-fracLeg));
    histo[1][var][0]->SetMinimum(minhisto);
    histo[1][var][0]->SetMaximum(maxpad);
    histo[1][var][0]->Draw("axis same");
    style.moveYAxisLabel(histo[1][var][0], maxpad, false);
    can.SetLogy(0);
    if(vars[var].cuts.Contains("abs(isr_tru_pt)")){
      TLatex tla;
      tla.SetTextSize(0.055);
      tla.SetTextFont(42);
      if(vars[var].cuts.Contains("abs(isr_tru_pt)<10")) tla.DrawLatexNDC(0.63,0.79,"#font[62]{ISR p_{T} < 10 GeV}");
      if(vars[var].cuts.Contains("abs(isr_tru_pt)>100")) tla.DrawLatexNDC(0.63,0.79,"#font[62]{ISR p_{T} > 100 GeV}");
    }
    else if(vars[var].cuts.Contains("nleps<1234")){
      TString lsp = "{#lower[-0.1]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}}";
      TString t1t_label = "#scale[0.95]{#tilde{g}#kern[0.2]{#tilde{g}}, #tilde{g}#rightarrowt#kern[0.18]{#bar{t}}#kern[0.18]"+lsp;
      TLatex tla;
      tla.SetTextSize(0.055);
      tla.SetTextFont(42);
      tla.DrawLatexNDC(0.52,0.70,"#font[62]{"+t1t_label+" (1500,100)}}");
      histo[1][var][0]->SetMaximum(60);
    }

    pname = outfolder+"/shapes_"+vars[var].tag+plot_tag;
    if(vars[var].whichPlots.Contains("0") || vars[var].whichPlots.Contains("3")) can.SaveAs(pname);
    float maxpadLog = maxhisto*exp(fracLeg*log(maxhisto/minLog)/(1-fracLeg));
    histo[1][var][0]->SetMaximum(maxpadLog);
    histo[1][var][0]->SetMinimum(minLog);
    style.moveYAxisLabel(histo[1][var][0], maxpadLog, true);
    can.SetLogy(1);
    pname = outfolder+"/log_shapes_"+vars[var].tag+plot_tag;
    if(!vars[var].skiplog && (vars[var].whichPlots.Contains("0") || vars[var].whichPlots.Contains("4"))) 
      can.SaveAs(pname);
  }// Loop over variables
  cout<<endl;

  for(unsigned var(0); var<vars.size(); var++){
    for(unsigned his(0); his < 2; his++){
      for(unsigned sam(0); sam < vars[var].samples.size(); sam++)
        if(histo[his][var][sam]) {
	  //cout<<"Deleting "<<histo[his][var][sam]->GetName()<<endl;
	  delete histo[his][var][sam];
	}
    }
  }
}

// Right now you have to use full samples, i.e. cuts added to sfeats is ignored (e.g. ntruleps==1 for 1l ttbar)
void plot_2D_distributions(vector<sfeats> Samples, vector<hfeats> vars, TString luminosity,
			   TString filetype, TString namestyle, TString dir){

  TString lumi_nodot = luminosity; lumi_nodot.ReplaceAll(".","p");

  styles style(namestyle);
  if(namestyle.Contains("CMSPaper")) style.nDivisions = 706;
  style.setDefaultStyle();
  TCanvas can;
  can.cd();
  TPad *pad(NULL);
  pad = static_cast<TPad *>(can.cd());
  pad->SetRightMargin(0.2);
  // Reading ntuples
  vector<TChain *> chain;
  for(unsigned sam(0); sam < Samples.size(); sam++){
    chain.push_back(new TChain("tree"));
    for(unsigned insam(0); insam < Samples[sam].file.size(); insam++){
      //cout<<"Reading "<<Samples[sam].file[insam]<<endl;
      chain[sam]->Add(Samples[sam].file[insam]);
      //cout<<"Entries "<<chain[sam]->GetEntries()<<endl;
    }
  }

  vector<TH2D*> hists;
  TString hname, title, variable, totCut;

  // Looping over histograms
  for(unsigned int i=0; i<vars.size(); i++){
    hname = "hist"; hname += i;
    title = cuts2title(vars[i].cuts); title += ";"; title += vars[i].titlex; title += ";"; title += vars[i].titley;
    variable = vars[i].varnamey+":"+vars[i].varnamex;
    totCut = luminosity+"*weight*("+vars[i].cuts+")";

    // Add together chains for the samples that should be in this plot

    if (isatty(1)) {
      printf("\rSetting up chain %i of %lu for 2D plots...",i+1,vars.size());
      fflush(stdout);
      if(i==vars.size()-1) printf("\n");
    }

    //cout<<"Setting up chain "<<i+1<<" of "<<vars.size()<<endl;
    TChain *tempChain = new TChain("tree");
    for(unsigned int j=0; j<vars[i].samples.size(); j++){
      //cout<<"Reading "<<chain[vars[i].samples[j]]<<endl;
      tempChain->Add(chain[vars[i].samples[j]]);
      //cout<<"Entries "<<tempChain->GetEntries()<<endl;
    }

    //Create and project histogram
    hists.push_back(new TH2D(hname, title, vars[i].nbinsx,vars[i].minx,vars[i].maxx,vars[i].nbinsy,vars[i].miny,vars[i].maxy));
    tempChain->Project(hname, variable, totCut, "colz");
    for(int iby=1;iby<=vars[i].nbinsy;iby++){
      hists.back()->SetBinContent(vars[i].nbinsx,iby,hists.back()->GetBinContent(vars[i].nbinsx,iby)+hists.back()->GetBinContent(vars[i].nbinsx+1,iby));
    }
    for(int ibx=1;ibx<=vars[i].nbinsx;ibx++){
      hists.back()->SetBinContent(ibx,vars[i].nbinsy,hists.back()->GetBinContent(ibx,vars[i].nbinsy)+hists.back()->GetBinContent(ibx,vars[i].nbinsy+1));
    }

  }

  // Save and format histograms
  gStyle->SetOptStat("emr");
  gStyle->SetStatX(0.338); gStyle->SetStatW(0.18); gStyle->SetStatY(0.90);  gStyle->SetStatH(0.14);

  cout<<"Printing 2D plots"<<endl;
  for(unsigned int doLogz=0; doLogz<2; doLogz++){
    for(unsigned int i=0; i<vars.size(); i++){
      if(doLogz==0 && vars[i].whichPlots.Contains("2")) continue;
      if(doLogz==1 && vars[i].whichPlots.Contains("1")) continue;
      TString pname;
      TString plot_tag("_lumi"+lumi_nodot+filetype);
      hists[i]->SetStats(0);
      hists[i]->Draw("colz");
      pname = "plots/"+dir+"/"+vars[i].tag+plot_tag;
      if(doLogz) pname = "plots/"+dir+"/logz_"+vars[i].tag+plot_tag;
      can.SetLogz(doLogz);
      // Draw cut lines
      if(vars[i].cutx>0 || vars[i].cuty>0){
        TLine line; line.SetLineColor(1); line.SetLineWidth(6); line.SetLineStyle(2);
        if(vars[i].cutx>0 && vars[i].cuty>0){
          line.DrawLine(vars[i].cutx,0,vars[i].cutx,vars[i].cuty);
          line.DrawLine(0,vars[i].cuty,vars[i].cutx,vars[i].cuty);
        }
        else if(vars[i].cutx>0 && vars[i].cuty<0){
          line.DrawLine(vars[i].cutx,0,vars[i].cutx,vars[i].maxy);
        }
        else if(vars[i].cutx<0 && vars[i].cuty>0){
          line.DrawLine(0,vars[i].cuty,vars[i].maxx,vars[i].cuty);
        }
      }
      can.SaveAs(pname);
    }
  }
  // Delete historgrams
  for(unsigned int i=0; i<vars.size(); i++){
    if(hists[i]) hists[i]->Delete();
  }
}

TString cuts2title(TString title){
  if(title=="1") title = "";
  title.ReplaceAll("1==1", "Full Sample");
  title.ReplaceAll("el_tks_chg*lep_charge<0", "OS");title.ReplaceAll("mu_tks_chg*lep_charge<0", "OS");title.ReplaceAll("had_tks_chg*lep_charge<0", "OS");
  title.ReplaceAll("Sum$(abs(mc_id)==11)","n^{true}_{e}");
  title.ReplaceAll("Sum$(abs(mc_id)==13)","n^{true}_{#mu}");
  title.ReplaceAll("Sum$(genels_pt>0)", "n^{true}_{e}");
  title.ReplaceAll("Sum$(genmus_pt>0)", "n^{true}_{#mu}");
  title.ReplaceAll("Sum$(mus_sigid&&mus_miniso<0.2)","n_{#mu}^{10}");
  title.ReplaceAll("Sum$(els_sigid&&els_miniso<0.1)","n_{e}^{10}");
  title.ReplaceAll("nvmus==1&&nmus==1&&nvels==0","1 #mu");
  title.ReplaceAll("nvmus10==0&&nvels10==0", "0 leptons");  
  title.ReplaceAll("(nmus+nels)", "n_{lep}");  
  title.ReplaceAll("(nels+nmus)", "n_{lep}");  
  title.ReplaceAll("(nvmus+nvels)", "n^{veto}_{lep}");  
  title.ReplaceAll("nvmus==2&&nmus>=1","n_{#mu}#geq1, n^{veto}_{#mu}=2");
  title.ReplaceAll("nvels==2&&nels>=1","n_{e}#geq1, n^{veto}_{e}=2");
  title.ReplaceAll("(nvmus>=2||nvels>=2)","n^{veto}_{lep} #geq 2"); 
  title.ReplaceAll("(mumu_m*(mumu_m>0)+elel_m*(elel_m>0))>80&&(mumu_m*(mumu_m>0)+elel_m*(elel_m>0))<100", 
		   "80<m_{ll}<100");  
  title.ReplaceAll("mumuv_m>80&&mumuv_m<100", 
		   "80<m_{ll}<100");  
  title.ReplaceAll("elelv_m>80&&elelv_m<100", 
		   "80<m_{ll}<100");  
  title.ReplaceAll("onht>350&&onmet>100&&","");
  title.ReplaceAll("jets_islep[0]==0","");
  title.ReplaceAll("(nels==0&&nmus==1)","n_{#mu}=1");
  title.ReplaceAll("(nels==1&&nmus==0)","n_{#font[12]{e}}=1");
  title.ReplaceAll("Max$(abs(els_eta)*(els_sigid&&els_miniso<0.1&&els_pt>20))<1.479","barrel #font[12]{e}");
  title.ReplaceAll("Max$(abs(els_eta)*(els_sigid&&els_miniso<0.1&&els_pt>20))>1.479","endcap #font[12]{e}");


  title.ReplaceAll("nleps", "n_{l}");
  title.ReplaceAll("nvleps", "n_{l}");
  title.ReplaceAll("nmus", "n_{#mu}");  
  title.ReplaceAll("nels", "n_{e}");  
  title.ReplaceAll("nvmus", "n^{veto}_{#mu}");  
  title.ReplaceAll("nvels", "n^{veto}_{e}");  
  title.ReplaceAll("ntruleps", "n^{true}_{l}");
  title.ReplaceAll("_ra2b", "^{ra2b}");
  title.ReplaceAll("npv", "n_{PV}");  
  title.ReplaceAll("mumu_pt1", "p_{T}^{#mu}");  title.ReplaceAll("elel_pt1", "p_{T}^{e}");  

  title.ReplaceAll("abs(mc_id)==1000006", "stop"); title.ReplaceAll("abs(mc_id)==1000022", "LSP");

  title.ReplaceAll("onmet", "MET^{on}"); title.ReplaceAll("onht", "H_{T}^{on}");  
  title.ReplaceAll("njets30","n_{jets}^{30}"); 
  title.ReplaceAll("els_pt","p^{e}_{T}"); title.ReplaceAll("mus_pt","p^{#mu}_{T}");
  title.ReplaceAll("fjets_nconst","n_{const}^{fat jet}");
  title.ReplaceAll("fjets_30_m[0]","m(J_{1})"); title.ReplaceAll("fjets_m[0]","m(J_{1})");
  title.ReplaceAll("(fjets_pt*cosh(fjets_eta))","p_{fatjet}"); title.ReplaceAll("fjets_pt","p^{fatjet}_{T}"); title.ReplaceAll("jets_pt","p^{jet}_{T}");
  title.ReplaceAll("mus_reliso","RelIso"); title.ReplaceAll("els_reliso","RelIso");
  title.ReplaceAll("mus_miniso_tr15","MiniIso"); title.ReplaceAll("els_miniso_tr15","MiniIso");
  title.ReplaceAll("njets","n_{jets}");title.ReplaceAll("abs(lep_id)==13&&","");
  title.ReplaceAll(">=", " #geq "); title.ReplaceAll(">", " > "); 
  title.ReplaceAll("<=", " #leq "); title.ReplaceAll("<", " < "); 
  title.ReplaceAll("&&", ", "); title.ReplaceAll("==", " = "); 
  title.ReplaceAll("met", "MET"); title.ReplaceAll("ht_hlt", "H_{T}^{HLT}");  
  title.ReplaceAll("mht", "MHT");  
  title.ReplaceAll("ht", "H_{T}");  title.ReplaceAll("mt", "m_{T}"); 
  title.ReplaceAll("ntks_chg==0", " ITV");
  title.ReplaceAll("nbm","n_{b}"); 
  title.ReplaceAll("nbl","n_{b,l}");
  title.ReplaceAll("mj", " M_{J}");
  
  title.ReplaceAll("el_tks_mt", "Track m_{T}"); title.ReplaceAll("mu_tks_mt", "Track m_{T}"); title.ReplaceAll("had_tks_mt", "Track m_{T}");
  title.ReplaceAll("el_tks_pt", "Track p_{T}"); title.ReplaceAll("mu_tks_pt", "Track p_{T}"); title.ReplaceAll("had_tks_pt", "Track p_{T}");
  title.ReplaceAll("el_tks_miniso", "Track miniso"); title.ReplaceAll("mu_tks_miniso", "Track miniso"); title.ReplaceAll("had_tks_miniso", "Track miniso");
  title.ReplaceAll("el_tks_chg_miniso", "Track charged miniso"); title.ReplaceAll("mu_tks_chg_miniso", "Track charged miniso"); title.ReplaceAll("had_tks_chg_miniso", "Track charged miniso"); 
  return title;
}

TString invertcut(TString cut){ //For only one cut
  if (cut.Contains("<"))
    cut.ReplaceAll("<",">="); 
  else if (cut.Contains(">"))
    cut.ReplaceAll(">","<=");
  else if (cut.Contains("<="))
    cut.ReplaceAll("<=",">");
  else if (cut.Contains(">="))
    cut.ReplaceAll(">=","<");

  return cut;
}

pfeats::pfeats(const vector<int> &isamples, const TString &icut, const TString &itagname):
  samples(isamples),
  cut(icut),
  tagname(itagname){
  }

hfeats::hfeats(TString ivarname, int inbins, float iminx, float imaxx, vector<int> isamples,
               TString ititle, TString icuts, float icut, TString itagname,bool iskiplog, vector<double> inevents):
  title(ititle),
  varname(ivarname),
  cuts(icuts),
  nbins(inbins),
  minx(iminx),
  maxx(imaxx),
  cut(icut),
  samples(isamples),
  tagname(itagname){
  format_tag();
  unit = "";
  maxYaxis = -1.;
  maxRatio = -1.;
  skiplog=iskiplog;
  if(inevents.at(0)<0) nevents = vector<double>(isamples.size(),-1);
  else nevents = inevents;
  if(nevents.size() != samples.size() ) cout<<"hfeats samples/nevents size mismatch: "<<ititle<<endl;
  whichPlots = "0"; // Make all 4 [log_]lumi and [log_]shapes plots; For 2D: 1=linear, 2=log
  normalize=false;
  normalizeByBin=false;
  PU_reweight=false;
  moveRLegend = 0;
  addOverflow = true;

  string ctitle(title.Data()); // Needed because effing TString can't handle square brackets
  if(!(ctitle.find("GeV")==std::string::npos)) unit = "GeV";
  if(!(ctitle.find("Number")==std::string::npos)) unit = "";
  if(!(ctitle.find("phi")==std::string::npos)) unit = "rad";
  }
hfeats::hfeats(TString ivarnamex, TString ivarnamey, int inbinsx, float iminx, float imaxx, int inbinsy, float iminy, float imaxy,  vector<int> isamples,
               TString ititlex, TString ititley, TString icuts, float icutx, float icuty, TString itagname):
  titlex(ititlex),
  titley(ititley),
  varnamex(ivarnamex),
  varnamey(ivarnamey),
  cuts(icuts),
  nbinsx(inbinsx),
  nbinsy(inbinsy),
  minx(iminx),
  maxx(imaxx),
  miny(iminy),
  maxy(imaxy),
  cutx(icutx),
  cuty(icuty),
  samples(isamples),
  tagname(itagname){
  format_tag();
  unit = "";
  maxYaxis = -1.;
  maxRatio = -1.;
  PU_reweight=false;
  addOverflow = true;

  string ctitle(title.Data()); // Needed because effing TString can't handle square brackets
  if(!(ctitle.find("GeV")==std::string::npos)) unit = "GeV";
  if(!(ctitle.find("Number")==std::string::npos)) unit = "";
  if(!(ctitle.find("phi")==std::string::npos)) unit = "rad";
  }

hfeats::hfeats(TString ivarname, int inbins, float *ibinning, vector<int> isamples,
               TString ititle, TString icuts, float icut, TString itagname,bool iskiplog, vector<double> inevents):
  title(ititle),
  varname(ivarname),
  cuts(icuts),
  nbins(inbins),
  binning(ibinning),
  cut(icut),
  samples(isamples),
  tagname(itagname) {
  minx = -1; maxx = binning[nbins];
  format_tag();
  unit = "";
  maxYaxis = -1.;
  maxRatio = -1.;
  skiplog =iskiplog;
  if(inevents.at(0)<0) nevents = vector<double>(isamples.size(),-1);
  else nevents = inevents;
  if(nevents.size() != samples.size() ) cout<<"hfeats samples/nevents size mismatch: "<<ititle<<endl;
  whichPlots = "0"; // Make all 4 [log_]lumi and [log_]shapes plots; For 2D: 1=linear, 2=log
  PU_reweight=false;
  addOverflow = true;
  string ctitle(title.Data()); // Needed because effing TString can't handle square brackets
  if(!(ctitle.find("GeV")==std::string::npos)) unit = "GeV";
  if(!(ctitle.find("Number")==std::string::npos)) unit = "";
  if(!(ctitle.find("phi")==std::string::npos)) unit = "rad";
  }

void hfeats::format_tag(){
  tag = varname;
  if(varnamex!="" && varnamey!="") tag = varnamex+"_vs_"+varnamey;
  if(cuts!="1")   tag+="_"+cuts;
  if(tagname!="") tag.Prepend(tagname+"_");

  tag.ReplaceAll("1==1", "full_sample");
  tag.ReplaceAll("el_tks_chg*lep_charge<0", "OS");tag.ReplaceAll("mu_tks_chg*lep_charge<0", "OS");tag.ReplaceAll("had_tks_chg*lep_charge<0", "OS");
  tag.ReplaceAll(".","");
  tag.ReplaceAll("(",""); tag.ReplaceAll("$","");  tag.ReplaceAll(")","");
  tag.ReplaceAll("[",""); tag.ReplaceAll("]",""); tag.ReplaceAll("||","_");
  tag.ReplaceAll("/","_"); tag.ReplaceAll("*",""); tag.ReplaceAll("&&","_");
  tag.ReplaceAll(">=","ge"); tag.ReplaceAll("<=","se");
  tag.ReplaceAll(">","g"); tag.ReplaceAll("<","s"); tag.ReplaceAll("=","");
  tag.ReplaceAll("+",""); tag.ReplaceAll("&","");
  tag.ReplaceAll("!","not");
  tag.ReplaceAll("#",""); tag.ReplaceAll("{",""); tag.ReplaceAll("}","");

  tag.ReplaceAll("htg500_metg200_njetsge7_nbmge1_nmusnels1_","Baseline1B_");
  tag.ReplaceAll("htg500_metg200_njetsge7_nbmge2_nmusnels1_","Baseline_");

  tag.ReplaceAll("tks_idlep_chargeg0_nottks_is_primary_tks_idtks_id121_","os_els_");
  tag.ReplaceAll("tks_idlep_chargeg0_nottks_is_primary_tks_idtks_id169_","os_mus_");
  tag.ReplaceAll("tks_idlep_charges0_nottks_is_primary_nottks_idtks_id169_tks_idtks_id121_","os_had_");

  tag.ReplaceAll("nottks_from_w","fakes");
  tag.ReplaceAll("tks_from_w","prompt");

  tag.ReplaceAll("tks_ptmintks_mini_netks_mini_ch,tks_r02_netks_r02_ch","abs_mini_iso_chgneu");
  tag.ReplaceAll("tks_ptmintks_mini_netks_mini_ch,tks_r05_netks_r05_ch","abs_r_05_mini_iso_chgneu");
  tag.ReplaceAll("tks_pttks_mini_netks_mini_ch","abs_untruncated_mini_iso_chgneu");
  tag.ReplaceAll("mintks_mini_netks_mini_ch,tks_r02_netks_r02_ch","rel_02_mini_iso_chgneu");
  tag.ReplaceAll("mintks_mini_netks_mini_ch,tks_r05_netks_r05_ch","rel_05_mini_iso_chgneu");
  tag.ReplaceAll("tks_mini_netks_mini_ch","rel_untruncated_mini_iso_chgneu");
  
  tag.ReplaceAll("tks_ptmintks_mini_ch,tks_r02_ch","abs_mini_iso_chg");
  tag.ReplaceAll("tks_ptmintks_mini_ch,tks_r05_ch","abs_r05_mini_iso_chg");
  tag.ReplaceAll("tks_pttks_mini_ch","abs_untruncated_mini_iso_chg");
  tag.ReplaceAll("mintks_mini_ch,tks_r02_ch","rel_02_mini_iso_chg");
  tag.ReplaceAll("mintks_mini_ch,tks_r05_ch","rel_05_mini_iso_chg");
  tag.ReplaceAll("tks_mini_ch","rel_untruncated_mini_iso_chg");

 
  tag.ReplaceAll("el_tks_mt", "Track_mT"); tag.ReplaceAll("mu_tks_mt", "Track_mT"); tag.ReplaceAll("had_tks_mt", "Track_mT");
  tag.ReplaceAll("el_tks_pt", "Track_pT"); tag.ReplaceAll("mu_tks_pt", "Track_pT"); tag.ReplaceAll("had_tks_pt", "Track_pT");
  tag.ReplaceAll("el_tks_miniso", "Track_miniso"); tag.ReplaceAll("mu_tks_miniso", "Track_miniso"); tag.ReplaceAll("had_tks_miniso", "Track_miniso");
  tag.ReplaceAll("el_tks_chg_miniso", "Track_chg_miniso"); tag.ReplaceAll("mu_tks_chg_miniso", "Track_chg_miniso"); tag.ReplaceAll("had_tks_chg_miniso", "Track_chg_miniso"); 
  
  
}

TString format_tag(TString tag){

  tag.ReplaceAll(" ","");
  tag.ReplaceAll(".","");tag.ReplaceAll(",","");
  tag.ReplaceAll("(",""); tag.ReplaceAll("$","");  tag.ReplaceAll(")","");
  tag.ReplaceAll("[",""); tag.ReplaceAll("]",""); tag.ReplaceAll("||","_");
  tag.ReplaceAll("/","_"); tag.ReplaceAll("*",""); tag.ReplaceAll("&&","_");
  tag.ReplaceAll(">=","ge"); tag.ReplaceAll("<=","se");
  tag.ReplaceAll(">","g"); tag.ReplaceAll("<","s"); tag.ReplaceAll("=","");
  tag.ReplaceAll("+",""); tag.ReplaceAll("&","");
  tag.ReplaceAll("!","not");
  tag.ReplaceAll("#",""); tag.ReplaceAll("{",""); tag.ReplaceAll("}","");

  return tag;
}

sfeats::sfeats(vector<TString> ifile, TString ilabel, int icolor, int istyle, TString icut, 
               TString isamVariable){
  file = ifile; label = ilabel; cut = icut;
  color = icolor; style = istyle;
  isSig = ifile[0].Contains("T1tttt");
  samVariable = isamVariable;
  factor = "1";
  tag = label;
  tag.ReplaceAll("(",""); tag.ReplaceAll(",","_");  tag.ReplaceAll(")","");
  tag.ReplaceAll("{",""); tag.ReplaceAll("#,","");  tag.ReplaceAll("}","");
  doStack = false; isData = false; mcerr=false; doBand = false;
}

sysfeats::sysfeats(TString iname, TString ititle):
  name(iname),
  title(ititle){
  bincuts = vector<TString>();
  weights = vector<double>();
  }
void sysfeats::push_back(TString ibincut, double iweight){
  bincuts.push_back(ibincut);
  weights.push_back(iweight);
}
TString sysfeats::bincut(unsigned i){
  if (i<bincuts.size()) return bincuts[i];
  else {cout<<"ERROR: bincut out of range"<<endl; return "";}
}
double sysfeats::weight(unsigned i){
  if (i<weights.size()) return weights[i];
  else {cout<<"ERROR: weight out of range"<<endl; return -1.;}
}
unsigned sysfeats::size(){
  return weights.size(); 
}

// Function that calculates the chi2 of a histogram with respect to the flat hypothesis
void calc_chi2(TH1D *histo, float &chi2, int &ndof, float &pvalue, float &average){
  vector<double> vals[2];
  double sumx_sig2(0), sum_sig2(0);
  ndof = 0;
  for(int bin(1); bin<=histo->GetNbinsX(); bin++){
    if(histo->GetBinError(bin) > 0){
      vals[0].push_back(histo->GetBinContent(bin));
      vals[1].push_back(histo->GetBinError(bin));

      sumx_sig2 += vals[0][ndof]/pow(vals[1][ndof],2);
      sum_sig2 += 1/pow(vals[1][ndof],2);
      ndof++;
    }
  }
  if(sum_sig2<=0){cout<<"All errors in histo are zero. Exiting."<<endl; return;}
  average = sumx_sig2/sum_sig2;
  chi2 = 0; ndof--;
  for(int ival(0); ival <= ndof; ival++){
    chi2 += pow((vals[0][ival]-average)/vals[1][ival],2);
  }
  pvalue = TMath::Prob(chi2,ndof);
}

// Function that calculates the chi2 from the difference of 2 histos, after normalizing their areas
void calc_chi2_diff(TH1D *histo1, TH1D *histo2, float &chi2, int &ndof, float &pvalue, float *average){
  TH1D *histos[] = {histo1, histo2};
  vector<double> vals[2][2];
  double sumx_sig2[] = {0,0}, sum_sig2[] = {0,0};
  int ndofs[] = {0,0};
  for(int his(0); his<2; his++){
    for(int bin(1); bin<=histos[his]->GetNbinsX(); bin++){
      if(histos[his]->GetBinError(bin) > 0){
        vals[his][0].push_back(histos[his]->GetBinContent(bin));
        vals[his][1].push_back(histos[his]->GetBinError(bin));

        sumx_sig2[his] += vals[his][0][ndofs[his]];
        sum_sig2[his] += 1;
        ndofs[his]++;
      }
    }
    if(sum_sig2[his]<=0){cout<<"All errors in histo are zero. Exiting."<<endl; return;}
    average[his] = sumx_sig2[his]/sum_sig2[his];
    ndofs[his]--;
  } // Loop over histos

  // In principle, we should use just bins where both histos have entries. To be modified
  if(ndofs[0] != ndofs[1]) {cout<<"First histo has "<<ndofs[0]<<" ndof and second "<<ndofs[1]<<endl; return;}
  else ndof = ndofs[0];
  chi2 = 0;
  double Raver = average[0]/average[1];
  for(int ival(0); ival <= ndof; ival++){
    double error(sqrt(pow(vals[0][1][ival],2)+pow(vals[1][1][ival]*Raver,2)));
    chi2 += pow((vals[0][0][ival]-vals[1][0][ival]*Raver)/error,2);
  }
  pvalue = TMath::Prob(chi2,ndof);
}

long getYieldErr(TChain& tree, TString cut, double& yield, double& uncertainty){
  const TString hist_name("temp");
  TH1D temp(hist_name, "", 1, -1.0, 1.0);
  temp.Sumw2();
  long entries = tree.Project(hist_name, "0.0", cut);
  yield = temp.IntegralAndError(0,2,uncertainty);
  return entries;
}

void dump_event(small_tree_full &tree, int entry){

  tree.GetEntry(entry);

  cout<<Form("event num: %i",tree.event())<<endl;
  cout<<Form("ntruleps: %i, ntrumus: %i, ntruels: %i, ntrutaush: %i, ntrutausl: %i",tree.ntruleps(),tree.ntrumus(),tree.ntruels(),tree.ntrutaush(),tree.ntrutausl())<<endl;
  cout<<"print MC doc: "<<endl;     
  for(unsigned int igen = 0; igen<tree.mc_pt().size();igen++){
    cout<<Form("%i: ID= %i \tpT=%.1f \teta=%.1f \tphi=%.1f \tmom= %i",igen,tree.mc_id().at(igen),tree.mc_pt().at(igen),tree.mc_eta().at(igen),tree.mc_phi().at(igen),static_cast<int>(tree.mc_mom().at(igen)))<<endl;
  }

  cout<<"Dumping Tracks"<<endl;
  for(unsigned int itks = 0; itks<tree.tks_pt().size();itks++){
    cout<<Form("%i: ID= %i \tpT=%.1f \teta=%.1f \tphi=%.1f \tisPrimary= %i \tfrom W= %i \ttruID = %i",itks,tree.tks_id().at(itks),tree.tks_pt().at(itks),tree.tks_eta().at(itks),tree.tks_phi().at(itks),static_cast<int>(tree.tks_is_primary().at(itks)),static_cast<int>(tree.tks_from_w().at(itks)),tree.tks_tru_id().at(itks))<<endl;
  }
}

namespace  ra4 {
  TColor ucsb_blue(2000, 1/255.,57/255.,166/255.);
  TColor ucsb_gold(2001, 255/255.,200/255.,47/255);
  TColor penn_red(2002, 149/255.,0/255.,26/255.);
  TColor uf_orange(2003, 255/255.,74/255.,0/255.);
  TColor uo_green(2004, 0/255.,79/255.,39/255.);
  TColor tcu_purple(2005, 52/255.,42/255.,123/255.);
  TColor tar_heel_blue(2006, 86/255.,160/255.,211/255.);
  TColor sig_teal(2007, 96/255.,159/255.,128/255.);
  TColor sig_gold(2008, 215/255.,162/255.,50/255.);
  TColor seal_brown(2010, 89/255.,38/255.,11/255.);
}

namespace dps{
  TColor light_blue(2011, 153/255.,220/255.,255/255.);
  TColor med_blue(2012, 1/255.,148/255.,218/255.);
  TColor red(2015, 250/255.,96/255.,1/255.);
  TColor skype_green(2018,9/255.,186/255.,1/255.);
  // TColor purple(2019, 172/255.,46/255.,135/255.);
  TColor purple(2019, 183/255.,66/255.,176/255.);
  TColor ucsb_gold(2020, 255/255.,200/255.,47/255);

}

namespace seq{
  TColor one1(2051,239/255.,243/255.,1.);
  TColor two2(2052,189/255.,215/255.,231/255.);
  TColor three3(2053,107/255.,174/255.,214/255.);
  TColor four4(2054,49/255.,130/255.,189/255.);
  TColor five5(2055,8/255.,81/255.,156/255.);

}

double intGaus(double mean, double sigma, double minX, double maxX){
  return (TMath::Erf((maxX-mean)/sigma/sqrt(2.))-TMath::Erf((minX-mean)/sigma/sqrt(2.)))/2.;
}


// Code from http://www.hongliangjie.com/2012/12/19/how-to-generate-gamma-random-variables/
// Parameter b could be theta...
double gsl_ran_gamma(const double a, const double b, TRandom3 &rand){
  if (a < 1){
    double u = rand.Uniform(1);
    return gsl_ran_gamma(1.0 + a, b, rand) * pow (u, 1.0 / a);
  }

  double x, v, u;
  double d = a - 1.0 / 3.0;
  double c = (1.0 / 3.0) / sqrt (d);
  
  while (1) {
    do {
      x = rand.Gaus(0, 1.0);
      v = 1.0 + c * x;
    }
    while (v <= 0);
      
    v = v * v * v;
    u = rand.Uniform(1);

    if (u < 1 - 0.0331 * x * x * x * x) 
      break;

    if (log (u) < 0.5 * x * x + d * (1 - v + log (v)))
      break;
  }
    
  return b * d * v;
}


// yields[Nobs][Nsam] has the entries for each sample for each observable going into kappa
// weights[Nobs][Nsam] has the average weight of each observable for each sample
// powers[Nobs] defines kappa = Product_obs{ Sum_sam{yields[sam][obs]*weights[sam][obs]}^powers[obs] }
double calcKappa(vector<vector<float> > &entries, vector<vector<float> > &weights,
                 vector<float> &powers, float &mSigma, float &pSigma, bool do_data,
                 bool verbose, bool do_plot, int nrep){
  TRandom3 rand(1234);
  styles style("RA4"); style.setDefaultStyle();
  int nbadk(0);
  TCanvas can;
  vector<float> fKappas;
  double mean(0.), bignum(1e10);
  // Doing kappa variations
  for(int rep(0), irep(0); rep < nrep; rep++) {
    fKappas.push_back(1.);
    bool Denom_is0(false);
    for(unsigned obs(0); obs < powers.size(); obs++) {
      float observed(0.);
      for(unsigned sam(0); sam < entries[obs].size(); sam++) {
        // With a flat prior, the expected average of the Poisson with N observed is Gamma(N+1,1)
        // Rounding the expected yield for data stats
        if(do_data) observed += entries[obs][sam]*weights[obs][sam];
        else observed += gsl_ran_gamma(entries[obs][sam]+1,1,rand)*weights[obs][sam];
      } // Loop over samples
      //if(do_data) observed = gsl_ran_gamma(static_cast<int>(0.5+observed)+1,1,rand);
      if(do_data) observed = gsl_ran_gamma(observed+1,1,rand);
      if(observed <= 0 && powers[obs] < 0) Denom_is0 = true;
      else fKappas[irep] *= pow(observed, powers[obs]);
    } // Loop over number of observables going into kappa
    if(Denom_is0 && fKappas[irep]==0) {
      fKappas.pop_back();
      nbadk++;
    }else {
      if(Denom_is0) fKappas[irep] = bignum;
      else mean += fKappas[irep];
      irep++;
    }
  } // Loop over fluctuations of kappa (repetitions)
  int ntot(nrep-nbadk);
  mean /= static_cast<double>(ntot);

  sort(fKappas.begin(), fKappas.end());
  double gSigma = intGaus(0,1,0,1);
  int iMedian((nrep-nbadk+1)/2-1);
  int imSigma(iMedian-static_cast<int>(gSigma*ntot)), ipSigma(iMedian+static_cast<int>(gSigma*ntot));
  float median(fKappas[iMedian]);
  mSigma = median-fKappas[imSigma]; pSigma = fKappas[ipSigma]-median;

  // Finding standard value
  float stdval(1.);
  bool infStd(false);
  for(unsigned obs(0); obs < powers.size(); obs++) {
    float stdyield(0.);
    if(verbose) cout<<obs<<": ";
    for(unsigned sam(0); sam < entries[obs].size(); sam++) {
      if(verbose) cout<<"Yield"<<sam<<" "<<entries[obs][sam]*weights[obs][sam]
                      <<", N"<<sam<<" "<<entries[obs][sam]
                      <<", avW"<<sam<<" "<<weights[obs][sam]<<". ";
      stdyield += entries[obs][sam]*weights[obs][sam];
    }
    if(verbose) cout<<"  ==> Total yield "<<stdyield<<endl;
    if(stdyield <= 0 && powers[obs] < 0) infStd = true;
    else stdval *= pow(stdyield, powers[obs]);
  } // Loop over number of observables going into kappa
  if(infStd) stdval = median;
  else {
    int istd(0);
    for(int rep(0); rep < ntot; rep++) 
      if(fKappas[rep]>stdval) {istd = rep; break;}
    imSigma = istd-static_cast<int>(gSigma*ntot);
    ipSigma = istd+static_cast<int>(gSigma*ntot);
    if(imSigma<0){ // Adjusting the length of the interval in case imSigma has less than 1sigma
      ipSigma += (-imSigma);
      imSigma = 0;
    }
    if(ipSigma>=ntot){ // Adjusting the length of the interval in case ipSigma has less than 1sigma
      imSigma -= (ipSigma-ntot+1);
      ipSigma = ntot-1;
    }
    mSigma = stdval-fKappas[imSigma]; pSigma = fKappas[ipSigma]-stdval;
  }

  int nbins(100);
  double minH(stdval-3*mSigma), maxH(stdval+3*pSigma);
  if(minH < fKappas[0]) minH = fKappas[0];
  if(maxH > fKappas[ntot-1]) maxH = fKappas[ntot-1];
  TH1D histo("h","",nbins, minH, maxH);
  for(int rep(0); rep < ntot; rep++) 
    histo.Fill(fKappas[rep]);   
  //histo.SetBinContent(1, histo.GetBinContent(1)+nbadk);
  //histo.SetBinContent(nbins, histo.GetBinContent(nbins)+histo.GetBinContent(nbins+1));
  histo.Scale(1/histo.Integral());
  histo.SetMaximum(histo.GetMaximum()*1.2);
  histo.SetLineWidth(3);
  histo.Draw();
  histo.SetXTitle("Expected value");
  histo.SetYTitle("Probability");
  histo.Draw();
  if(do_plot) can.SaveAs("test.eps");

  double mode(histo.GetBinLowEdge(histo.GetMaximumBin()));
  if(verbose) cout<<"Std kappa = "<<stdval<<"+"<<pSigma<<"-"<<mSigma<<".   Mean = "<<mean
                  <<". Mode = "<<mode<<". Median = "<<median<<endl;

  return stdval;
}

float Efficiency(float num, float den, float &errup, float &errdown){
  if(den<=0){cout<<"Denominator is "<<den<<". Exiting"<<endl; return -1.;}

  TH1D hnum("hnum","",1,0,1);
  hnum.SetBinContent(1,num);
  TH1D hden("hden","",1,0,1);
  hden.SetBinContent(1,den);

  TEfficiency heff(hnum, hden);

  errup = heff.GetEfficiencyErrorUp(1); 
  errdown = heff.GetEfficiencyErrorLow(1);
  return num/den;
}

