#include<iostream>
using namespace std;

void elcmu(){
	/* make chain */
	TChain ch_ku("tree");
	TChain ch_ucsb("tree");

	ch_ku.Add("/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/*JetHT*");
	ch_ucsb.Add("/xrootd_user/jaehyeok/xrootd/ucsb_babies/2017_02_14/data/merged_rpvdata_st1000/*JetHT*");

	cout <<"KU entry : "<< ch_ku.GetEntries() << ", UCSB entry : " <<  ch_ucsb.GetEntries() << endl;

	TH1F *elku = new TH1F("elku","elku",5,-0.5,4.5);
	TH1F *muku = new TH1F("muku","muku",5,-0.5,4.5);
	TH1F *eluc = new TH1F("eluc","eluc",5,-0.5,4.5);
	TH1F *muuc = new TH1F("muuc","muuc",5,-0.5,4.5);
	TH1F *lepku = new TH1F("lepuc","lepuc",5,-0.5,4.5);
	TH1F *lepuc = new TH1F("lepku","lepku",5,-0.5,4.5);

	ch_ku.Draw("min(nels,4)>>elku"," ht>1200 && mj12>500 && njets>=4 && Sum$(jets_csv>0.8484 && jets_pt>30 && jets_id && !jets_islep && abs(jets_eta)<2.4)>=1 && (trig_ht900 || trig_jet450)","goff");
	cout << "KU electron finished." << endl;
	ch_ucsb.Draw("min(nels,4)>>eluc"," ht>1200 && mj12>500 && njets>=4 && nbm>=1 && (trig[54] || trig[56])","goff");
	cout << "UCSB electron finished." << endl;
	
	ch_ku.Draw("min(nmus,4)>>muku"," ht>1200 && mj12>500 && njets>=4 && Sum$(jets_csv>0.8484 && jets_pt>30 && jets_id && !jets_islep && abs(jets_eta)<2.4)>=1 && (trig_ht900 || trig_jet450)","goff");
	cout << "KU muon finished." << endl;	
	ch_ucsb.Draw("min(nmus,4)>>muuc"," ht>1200 && mj12>500 && njets>=4 && nbm>=1 && (trig[54] || trig[56])","goff");
	cout << "UCSB muon finished." << endl;

	ch_ku.Draw("min(nleps,4)>>lepku"," ht>1200 && mj12>500 && njets>=4 && Sum$(jets_csv>0.8484 && jets_pt>30 && jets_id && !jets_islep && abs(jets_eta)<2.4)>=1 && (trig_ht900 || trig_jet450)","goff");
	cout << "KU leptons finished." << endl;	
	ch_ucsb.Draw("min(nleps,4)>>lepuc"," ht>1200 && mj12>500 && njets>=4 && nbm>=1 && (trig[54] || trig[56])","goff");
	cout << "UCSB leptons finished." << endl;
	
	TCanvas *c = new TCanvas("c","c",2400,800);
	c->Divide(3,1);
	c->cd(1);
	elku->SetTitle("");
	elku->SetLineColor(kRed);
	eluc->SetLineWidth(2);
	elku->SetLineWidth(2);
	elku->SetStats(0);
	eluc->SetStats(0);
	elku->Draw("");
	eluc->Draw("same hist");
	
	TLegend *l1 = new TLegend(0.477185,0.6740231,0.8578692,0.8744133);
	l1->SetBorderSize(0);
	l1->SetNColumns(1);
	l1->AddEntry(elku, "KU ntuple electron", "l");
	l1->AddEntry(eluc, "UCSB ntuple electron", "l");
	l1->Draw("");
	
	c->cd(2);
	muku->SetTitle("");
	muku->SetLineColor(kRed);
	muuc->SetLineWidth(2);
	muku->SetLineWidth(2);
	muku->SetStats(0);
	muuc->SetStats(0);
	muku->Draw("");
	muuc->Draw("same hist");

	TLegend *l2 = new TLegend(0.477185,0.6740231,0.8578692,0.8744133);
	l2->SetBorderSize(0);
	l2->SetNColumns(1);
	l2->AddEntry(elku, "KU ntuple muon", "l");
	l2->AddEntry(eluc, "UCSB ntuple muon", "l");
	l2->Draw("");

	c->cd(3);
	lepku->SetTitle("");
	lepku->SetLineColor(kRed);
	lepuc->SetLineWidth(2);
	lepku->SetLineWidth(2);
	lepku->SetStats(0);
	lepuc->SetStats(0);
	lepku->Draw("");
	lepuc->Draw("same hist");
	
	TLegend *l3 = new TLegend(0.477185,0.6740231,0.8578692,0.8744133);
	l3->SetBorderSize(0);
	l3->SetNColumns(1);
	l3->AddEntry(elku, "KU ntuple leptons", "l");
	l3->AddEntry(eluc, "UCSB ntuple leptons", "l");
	l3->Draw("");
	
	c->Print("./Plots/el_mu_comp.pdf");
	c->Print("./Plots/el_mu_comp.C");
}
