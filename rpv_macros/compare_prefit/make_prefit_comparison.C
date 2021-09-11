void make_prefit_comparison(){
	TFile *flist[3];
	vector<TString> fname = {"2016","2017_20178","2018_20178"}; 
	vector<TString> list_proc = {"data_obs","qcd","ttbar","wjets","other"};
	vector<TString> list_bin = {"bin22","bin23","bin24","bin25","bin26","bin27","bin28","bin29","bin30","bin31","bin32","bin33","bin35","bin36"};
	vector<int> list_color = {1, 800+10, 880+10};
	TH1F *proc[3];

	for(int i=0; i<3; i++){
		flist[i] = new TFile("../variations/output_impact_"+fname[i]+".root","READ");
	}

	float NormToShape;
	TH1F *ratio;
	bool dat_pass = true;

	for(auto ibin : list_bin){
		if(ibin=="bin30") dat_pass=false;
		for(auto iproc : list_proc){
			if(!dat_pass&&iproc=="data_obs") continue;
			TCanvas *c = new TCanvas("c_"+ibin+"/"+iproc, "c_"+ibin+"/"+iproc, 800, 800);
			/*
			   TPad *p1 = new TPad("p1_"+ibin+"/"+iproc,"p1_"+ibin+"/"+iproc,0.1,0.2,0.9,1.);
			   TPad *p2 = new TPad("p2_"+ibin+"/"+iproc,"p2_"+ibin+"/"+iproc,0.1,0.,0.9,0.2);
			   p1->Draw();
			   p2->Draw();
			   */
			for(int i=0; i<3; i++){
				proc[i] = static_cast<TH1F*>(flist[i]->Get(ibin+"/"+iproc));
				NormToShape = proc[i]->Integral();
				proc[i]->Scale(1/NormToShape);
				proc[i]->SetLineColor(list_color.at(i));
				proc[i]->SetLineWidth(2);
				proc[i]->SetStats(0);
				c->SetLogy();
				proc[i]->Draw("same e");
				/*
				   p2->cd();
				   if(i==0) ratio = static_cast<TH1F*>(proc[i]->Clone("ratio"));
				   else{
				   ratio->Divide(proc[i]);
				   ratio->SetLineColor(list_color.at(i));
				   ratio->GetYaxis()->SetRangeUser(0.5,1.5);
				   ratio->SetTitle("");
				   }
				   ratio->Draw("e");
				   */
			}
			c->Print(ibin+"."+iproc+".pdf");
			c->Print(ibin+"."+iproc+".png");
		}
	}

}
