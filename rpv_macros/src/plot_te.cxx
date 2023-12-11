#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "TLatex.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMath.h"

#include "styles.hpp"
#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

using namespace std;

struct winsize w;

void make_te(small_tree_rpv &tree, TFile *f, TString year, TString procname);

int main(int argc, char *argv[])
{
	gErrorIgnoreLevel=kError+1;
	TString procname = argv[1]; 
	TString year = argv[2];
	TString folder;
	vector<TString> s_proc;
	if(procname == "data"){ 
		//folder = folder_year(year,true).at(1);
		folder = "/mnt/data3/babies/merged_231126_singlemu_data/"+year+"/";
		vector<TString> s_singlemuon = getRPVProcess(folder,"data_te");
		vector<TString> s_jetht = getRPVProcess(folder,"data");
		s_proc = s_singlemuon; 
	}
	if(procname == "mc"){
		folder = folder_year(year,true).at(0);
		vector<TString> s_qcd = getRPVProcess(folder,"qcd");
		vector<TString> s_tt = getRPVProcess(folder,"ttbar");
		vector<TString> s_wjets = getRPVProcess(folder,"wjets");
		vector<TString> s_other = getRPVProcess(folder,"other_public");
		vector<TString> s_ = s_qcd;
		s_.insert(s_.end(), s_tt.begin(), s_tt.end());
		s_.insert(s_.end(), s_wjets.begin(), s_wjets.end());
		s_.insert(s_.end(), s_other.begin(), s_other.end());
		s_proc = s_; 
	}
	for(auto str : s_proc) cout<<str<<endl;
	
	small_tree_rpv events((static_cast<std::string>(s_proc.at(0))));
	for(unsigned int iproc=1; iproc<s_proc.size(); iproc++) events.Add((static_cast<std::string>(s_proc.at(iproc))));
	TFile *f = new TFile("plots/trig_eff"+year+"_"+procname+".root","recreate");
	make_te(events, f, year, procname);
	f->Close();
}

void make_te(small_tree_rpv &tree, TFile *f, TString year, TString procname){
	ioctl(0, TIOCGWINSZ, &w);
	int cols = w.ws_col;

	styles style("CMSPaper");
	style.LegendSize=style.LegendSize*0.5;
	style.TitleSize=style.TitleSize*0.5;
	style.LabelSize=style.LabelSize*0.5;
	style.setDefaultStyle();
	gStyle->SetPadLeftMargin(0.10);
	gStyle->SetPadRightMargin(style.PadRightMargin+0.02);
	gStyle->SetPadBottomMargin(0.10);
	gStyle->SetNdivisions(10710,"xyz");
	gStyle->SetPadTickX(0);
	gStyle->SetPadTickY(0);

	TH1D* h1den[4];
	TH1D* h1num[4];
	TH1D* h1eff[4];
	TH1D* h1innum[4];
	TH1D* h1ineff[4];
	TCanvas* c[4];

	f->cd();

	float min[4] = {0,500,3.5,-0.5};
	float max[4] = {2000,2000,15.5,15.5};
	int nbins[4] = {20,15,12,16};
	TString var[4] = {"H_{T}", "M_{J}", "N_{Jets}","N_b"};
	TString varf[4] = {"HT","MJ","Njets","Nb"};

	for(int j=0;j<4;j++){
		c[j] = new TCanvas();
//		c[j] = new TCanvas(Form("c%d",j),Form("c%d",j),1600,800);
//		c[j]->Divide(2,1);
		h1den[j] = new TH1D(Form("den%d",j),Form("den%d",j),nbins[j],min[j],max[j]);
		h1num[j] = new TH1D(Form("num%d",j),Form("num%d",j),nbins[j],min[j],max[j]);
		h1innum[j] = new TH1D(Form("innum%d",j),Form("innum%d",j),nbins[j],min[j],max[j]);
		h1eff[j] = new TH1D(Form("eff%d",j),Form("eff%d",j),nbins[j],min[j],max[j]);
		h1ineff[j] = new TH1D(Form("ineff%d",j),Form("ineff%d",j),nbins[j],min[j],max[j]);
	}

	for(unsigned int ientry=0; ientry<tree.GetEntries(); ientry++)
	{
		float progress = 0.0;
		if(ientry%int(tree.GetEntries()/1000) == 0||ientry+1 == tree.GetEntries()){
			ioctl(0,TIOCGWINSZ, &w);
			cols = w.ws_col;
			//cols = 104;
			progress = float(ientry+1)/float(tree.GetEntries());
			int barWidth = cols - 78;
			TString space = "";
			for(int sp = 0 ; sp < 20-strlen(procname.Data()) ; sp++){
				space = space + " "; 
			}
			cout << "Process name      : " << procname.Data() << space.Data() <<  "[";
			int pos = barWidth*progress;
			for(int i = 0; i < barWidth;++i){
				if(i < pos) cout << "■";
				else if(i==pos) cout << "■";
				else cout << " ";
			} 
			cout<<"\033[0m]";
			TString space2 = "";
			TString space3 = "";
			for(int sp2 = 0 ; sp2 < 22-strlen(Form("%d",ientry))-strlen(Form("%d",tree.GetEntries())) ; sp2++) space2 = space2 +" ";
			cout << space2.Data() << ientry+1 << " / " << tree.GetEntries() << "   (" << space3.Data() << Form("%5.1f",progress*100.0) <<"%)\r";
			cout.flush();
		}
//		if(ientry%100==0) cout<<"A"<<endl;
		tree.GetEntry(ientry);

		float ht = tree.ht();
		float mj = tree.mj12();
		float nj = (float)tree.njets();
		float nb = (float)tree.nbm();
	
//		cout<<ht<<"||"<<mj<<"||"<<nj<<"||"<<nb<<endl;

		vector<float> var;
		var.push_back(ht);
		var.push_back(mj);
		var.push_back(nj);
		var.push_back(nb);

		for(unsigned int ibin=0;ibin<4;ibin++){
			float var_p = var.at(ibin); 
			float nomweight;
			if(procname=="mc") nomweight=tree.weight();
			else if(procname=="data") nomweight=tree.pass();
			float trig;
			float trig_mu; // I didn't apply this cut when nanoprocessing
			if(year=="2016") {
				trig=(tree.trig_ht900()||tree.trig_jet450());
				trig_mu=(tree.trig_isomu24());
			}
			else if(year=="2017"||year=="2018") {
				trig=(tree.trig_ht1050());
				trig_mu=(tree.trig_isomu27());
			}
			if(ibin==0) nomweight = nomweight;
			else nomweight = (tree.ht()>1200)*nomweight;
			h1den[ibin]->Fill(var_p>max[ibin]?max[ibin]:var_p,nomweight*trig_mu);
			h1num[ibin]->Fill(var_p>max[ibin]?max[ibin]:var_p,nomweight*trig_mu*trig);
			h1innum[ibin]->Fill(var_p>max[ibin]?max[ibin]:var_p,nomweight*trig_mu*(1-trig));
		}
	}
	for(unsigned int ibin=0; ibin<4; ibin++){

		h1eff[ibin] = dynamic_cast<TH1D*>(h1num[ibin]->Clone("h1_eff"));
		h1eff[ibin]->Divide(h1num[ibin],h1den[ibin],1,1,"B");
		h1den[ibin]->Write();
		h1num[ibin]->Write();
		h1eff[ibin]->Write();

		TString lumi;
		if(year=="2016") lumi = "36.3";
		if(year=="2017") lumi = "41.5";
		if(year=="2018") lumi = "59.8";

		TString cmslabel = "#font[62]{CMS} #scale[0.8]{#font[52]{Work In Progress}}";
		TString lumilabel = TString::Format("%1.1f", lumi.Atof())+" fb^{-1}, 13 TeV";

		h1ineff[ibin] = dynamic_cast<TH1D*>(h1num[ibin]->Clone("h1_eff"));
		h1ineff[ibin]->Divide(h1innum[ibin],h1den[ibin],1,1,"B");
		h1innum[ibin]->Write();
		h1ineff[ibin]->Write();

		double denmax = h1den[ibin]->GetMaximum();
	
//		c[ibin]->cd(1);

//		c[ibin]->cd(1)->SetGrid();
		c[ibin]->cd();
		c[ibin]->SetGrid();
				
		h1eff[ibin]->GetXaxis()->SetTitle(var[ibin]);
		h1eff[ibin]->GetYaxis()->SetTitle("Trigger Efficiency");
		h1eff[ibin]->SetStats(0);
		h1eff[ibin]->SetMaximum(1.2);
		h1eff[ibin]->SetMinimum(0);
		h1eff[ibin]->SetLineWidth(2);
		h1eff[ibin]->SetLineColor(kBlack);
		h1eff[ibin]->SetTitle("");
		h1eff[ibin]->Draw("e");

		TLatex label; label.SetNDC(kTRUE);
		label.SetTextSize(0.03);
		label.SetTextAlign(11);
		label.DrawLatex(0.10,1-style.PadTopMargin+0.02,cmslabel);
		label.SetTextAlign(31);
		label.DrawLatex(1-style.PadRightMargin-0.02,1-style.PadTopMargin+0.02,lumilabel);

		TGaxis *ax1 = new TGaxis(max[ibin],0,max[ibin],1.2,0,denmax*3,10510,"+L");
		ax1->SetLabelSize(0.03);
		ax1->SetLabelFont(40);
		ax1->SetTitle("Events");
		ax1->SetTitleSize(0.04);
		ax1->SetTitleFont(40);
		ax1->SetTitleOffset(1.3);
		ax1->SetMaxDigits(2);
		ax1->Draw("same");


		TLegend *l1 = new TLegend(style.PadLeftMargin+0.01,1-style.PadTopMargin-0.04,1-style.PadRightMargin-0.03,1-style.PadTopMargin-0.01);
		l1->AddEntry(h1eff[ibin],"Trigger Efficiency","l");
		l1->AddEntry(h1den[ibin],"Denominator","l");
		l1->AddEntry(h1num[ibin],"Numerator","f");
		l1->SetNColumns(3);
		l1->SetBorderSize(0);
		l1->Draw("same");

		TLine *h1 = new TLine(min[ibin],1,max[ibin],1);
		h1->SetLineColor(kGray);
		h1->SetLineWidth(1);
		h1->Draw("same");

		h1den[ibin]->Scale(1/(3*denmax));
		h1den[ibin]->SetLineWidth(2);
		h1den[ibin]->SetLineColor(kRed);
		h1den[ibin]->Draw("hist same");

		h1num[ibin]->Scale(1/(3*denmax));
		h1num[ibin]->SetFillStyle(3254);
		h1num[ibin]->SetFillColor(kBlue);
		h1num[ibin]->SetLineColor(kBlue);
		h1num[ibin]->SetLineWidth(2);
		h1num[ibin]->Draw("hist same");

		h1eff[ibin]->Draw("same e");
/*
		c[ibin]->cd(2);

		h1ineff[ibin]->GetXaxis()->SetTitle(var[ibin]);
		h1ineff[ibin]->GetYaxis()->SetTitle("Trigger Efficiency");
		h1ineff[ibin]->SetStats(0);
		h1ineff[ibin]->SetMaximum(1.2);
		h1ineff[ibin]->SetMinimum(0);
		h1ineff[ibin]->SetLineWidth(2);
		h1ineff[ibin]->SetLineColor(kBlack);
		h1ineff[ibin]->Draw("e");

		TGaxis *ax2 = new TGaxis(max[ibin],0,max[ibin],1.2,0,denmax*3,10510,"+L");
		ax2->SetLabelSize(0.03);
		ax2->SetLabelFont(40);
		ax2->SetTitle("Events");
		ax2->SetTitleSize(0.04);
		ax2->SetTitleFont(40);
		ax2->SetTitleOffset(1.3);
		ax2->Draw("same");

		TLine *h2 = new TLine(min[ibin],1,max[ibin],1);
		h2->SetLineColor(kGray);
		h2->SetLineWidth(1);
		h2->Draw("same");

		h1den[ibin]->Draw("hist same");

		h1innum[ibin]->Scale(1/(3*denmax));
		h1innum[ibin]->SetFillStyle(3254);
		h1innum[ibin]->SetFillColor(kBlue);
		h1innum[ibin]->SetLineColor(kBlue);
		h1innum[ibin]->SetLineWidth(2);
		h1innum[ibin]->Draw("hist same");

		h1ineff[ibin]->Draw("same e");
*/

		c[ibin]->Print(Form("plots/trig_eff_%s_%s_%s.pdf",year.Data(),procname.Data(),varf[ibin].Data()));
	}	
}



