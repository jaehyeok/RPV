#include <iostream>
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
#include "TStyle.h"
#include "TMath.h"

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
		folder = folder_year(year).at(1);
		vector<TString> s_jetht = getRPVProcess(folder,"data");
		s_proc = s_jetht; 
	}
	if(procname == "mc"){
		folder = folder_year(year).at(0);
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
	TFile *f = new TFile("plots/trig_eff.root","recreate");
	make_te(events, f, year, procname);
	f->Close();
}

void make_te(small_tree_rpv &tree, TFile *f, TString year, TString procname){
	ioctl(0, TIOCGWINSZ, &w);
	int cols = w.ws_col;

	TH1D* h1den[4];
	TH1D* h1num[4];
	TH1D* h1eff[4];

	f->cd();

	float min[4] = {0,500,3.5,-0.5};
	float max[4] = {2000,2000,15.5,15.5};
	int nbins[4] = {20,15,12,16};

	for(int j=0;j<4;j++){
		h1den[j] = new TH1D(Form("den%d",j),Form("den%d",j),nbins[j],min[j],max[j]);
		h1num[j] = new TH1D(Form("num%d",j),Form("num%d",j),nbins[j],min[j],max[j]);
		h1eff[j] = new TH1D(Form("eff%d",j),Form("eff%d",j),nbins[j],min[j],max[j]);
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
			if(year=="2016") trig=(tree.trig_ht900()||tree.trig_jet450());
			else if(year=="2017"||year=="2018") trig=(tree.trig_ht1050());
			h1den[ibin]->Fill(var_p>max[ibin]?max[ibin]:var_p,nomweight);
			h1num[ibin]->Fill(var_p>max[ibin]?max[ibin]:var_p,nomweight*trig);
		}
	}
	
	for(unsigned int ibin=0; ibin<4; ibin++){
		h1eff[ibin] = dynamic_cast<TH1D*>(h1num[ibin]->Clone("h1_eff"));
		h1eff[ibin]->Divide(h1num[ibin],h1den[ibin],1,1,"B");
		h1den[ibin]->Write();
		h1num[ibin]->Write();
		h1eff[ibin]->Write();
	}	
}



