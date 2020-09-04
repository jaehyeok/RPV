void comb_comp(){
	TH1D *h_1600 = new TH1D("1600GeV", "1600GeV", 11, 475, 1025);
	TH1D *h_1700 = new TH1D("1700GeV", "1700GeV", 11, 475, 1025);
	TH1D *h_1800 = new TH1D("1800GeV", "1800GeV", 11, 475, 1025);
	TH1D *h_1900 = new TH1D("1900GeV", "1900GeV", 11, 475, 1025);
	TH1D *h_2000 = new TH1D("2000GeV", "2000GeV", 11, 475, 1025);

	
	TCanvas *c = new TCanvas("c","c",1000,800);
	h_1600->GetYaxis()->SetRangeUser(0,3.2);
	h_1600->SetTitle("Comparsion between 1600 GeV to 1900 GeV");
	h_1600->SetStats(0);
	h_1600->SetLineWidth(2);
	h_1600->SetLineColor(kBlue);
	h_1700->SetLineWidth(2);
	h_1700->SetLineColor(kGreen-6);
	h_1800->SetLineWidth(2);
	h_1800->SetLineColor(kOrange+6);
	h_1900->SetLineWidth(2);
	h_1900->SetLineColor(kRed);
	h_2000->SetLineWidth(2);
	h_2000->SetLineColor(kViolet);

	h_1600->Draw();
//	h_1700->Draw("same hist");
	h_1800->Draw("same hist");
	h_1900->Draw("same hist");
	h_2000->Draw("same hist");

	TLegend *legend = new TLegend(0.25, 0.80, 0.8, 0.88);
	TLegend->SetNColumns(2);
	legend->AddEntry(h_1600, "m_{#tilde{g}}=1600 GeV","l");
//	TlegendEntry *l2 = legend->AddEntry(h_1700, "m_{#tilde{g}}=1700 GeV","l");
	legend->AddEntry(h_1800, "m_{#tilde{g}}=1800 GeV","l");
	legend->AddEntry(h_1900, "m_{#tilde{g}}=1900 GeV","l");
	legend->AddEntry(h_2000, "m_{#tilde{g}}=2000 GeV","l");
	legend->SetBorderSize(0);
//	l1->SetTextSize(0.03);
//	l2->SetTextSize(0.03);
//	l3->SetTextSize(0.03);
//	l4->SetTextSize(0.03);
//	l5->SetTextSize(0.03);
	legend->Draw();
	
	c->Print("comparison.pdf");
}
