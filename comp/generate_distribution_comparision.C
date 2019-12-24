#include<iostream>
using namespace std;

vector<float> frame(TString var = "mj12"){
	vector<float> ret;
	if(var=="mj12"){
		ret.push_back(20);
		ret.push_back(0);
		ret.push_back(2000);
	}
	if(var=="ht"){
		ret.push_back(25);
		ret.push_back(0);
		ret.push_back(5000);
	}
	if(var=="njets"){
		ret.push_back(20);
		ret.push_back(-0.5);
		ret.push_back(19.5);
	}
	if(var=="nb"){
		ret.push_back(10);
		ret.push_back(-0.5);
		ret.push_back(9.5);
	}
	return ret;
}


void generate_distribution_comparision(){
	TChain ch_ku("tree");
	TChain ch_ucsb("tree");

	ch_ku.Add("/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/*JetHT*");
	ch_ucsb.Add("/xrootd_user/jaehyeok/xrootd/ucsb_babies/2017_02_14/data/merged_rpvdata_st1000/*JetHT*");

	cout<<ch_ku.GetEntries()<<endl;
	cout<<ch_ucsb.GetEntries()<<endl;

	vector<TString> var1;
	var1.push_back("mj12");
	var1.push_back("ht");
	var1.push_back("njets");
	var1.push_back("Sum$(jets_pt>30 && abs(jets_eta)<2.4 && !jets_islep && jets_id && jets_csv>0.8484)");
	var1.push_back("nleps");

	vector<TString> var2;
	var2.push_back("mj12");
	var2.push_back("ht");
	var2.push_back("njets");
	var2.push_back("nbm");
	var2.push_back("nleps");

	vector<TString> hist;
	hist.push_back("mj12");
	hist.push_back("ht");
	hist.push_back("njets");
	hist.push_back("nb");
	hist.push_back("nleps");

	vector<float> hfr;

	vector<TString> cuts;
	cuts.push_back("1 &&");
	cuts.push_back(" ht>1200 &&");
	cuts.push_back(" njets>=4 &&");
	cuts.push_back(" mj12>500 &&");
	cuts.push_back(" Sum$(jets_pt>30 && !jets_islep && abs(jets_eta)<2.4 && jets_csv>0.8484)>=1 &&");
	cuts.push_back(" Sum$(jets_pt>30 && !jets_islep && abs(jets_eta)<2.4 && jets_csv>0.8484)>=2 &&");
	cuts.push_back(" Sum$(jets_pt>30 && !jets_islep && abs(jets_eta)<2.4 && jets_csv>0.8484)>=3 &&");
	cuts.push_back(" Sum$(jets_pt>30 && !jets_islep && abs(jets_eta)<2.4 && jets_csv>0.8484)>=4 &&");

	int i=0;
	TString asymptcuts;
	for(i=0;i<5;i++){
		hfr = frame(hist.at(i));
		int nbins = (int) hfr.at(0);

		cout<<hist.at(i)+"ku,"<<hist.at(i)+"ku"<<","<<nbins<<","<<hfr.at(1)<<","<<hfr.at(2)<<endl;	

		TH1D *hist_ku = new TH1D(hist.at(i)+"ku",hist.at(i)+"ku",nbins,hfr.at(1),hfr.at(2));
		TH1D *hist_ucsb = new TH1D(hist.at(i)+"ucsb",hist.at(i)+"ucsb",nbins,hfr.at(1),hfr.at(2));

		cout<<var1.at(i).Data()<<","<<var2.at(i).Data()<<endl;
		for(int cts = 0 ; cts < 8 ; cts ++ ){
			asymptcuts += cuts.at(cts);
			ch_ku.Draw(Form("%s>>%sku",var1.at(i).Data(),hist.at(i).Data()), asymptcuts + "ht>1000 && (trig_ht900 || trig_jet450)","goff");
			ch_ucsb.Draw(Form("%s>>%sucsb",var2.at(i).Data(),hist.at(i).Data()), asymptcuts + "ht>1000 && (trig[54] || trig[56])","goff");

			cout<<hist_ku->Integral()<<endl;
			cout<<hist_ucsb->Integral()<<endl;	
		}		
		asymptcuts = "";
		TCanvas *c = new TCanvas("c","c",800,800);
		double maxi = max(hist_ku->GetMaximum(),hist_ucsb->GetMaximum());
		c->DrawFrame(hfr.at(1),0,hfr.at(2),maxi*1.5);
		c->SetLogy();
		hist_ucsb->SetTitle(hist.at(i));
		hist_ku->SetTitle("");
		hist_ku->SetLineColor(kRed);
		hist_ucsb->SetLineWidth(2);
		hist_ku->SetLineWidth(2);
		hist_ucsb->Draw("");
		hist_ku->Draw("same hist");				
		c->Print("./Plots/ucsb_ku_comp_cuts_"+hist.at(i)+".pdf");
		c->Print("./Plots/ucsb_ku_comp_cuts_"+hist.at(i)+".C");
	}
}


/*	TH1F *h_mj12 = new TH1F("mj12","mj12",20,0,2000);	
	TH1F *h_ht = new TH1F("ht","ht",25,0,5000);	
	TH1F *h_njets = new TH1F("njets","njets",20,0,20);	
	TH1F *h_nb = new TH1F("nb","nb",10,0,10);	
	*/
