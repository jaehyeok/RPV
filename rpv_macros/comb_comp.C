void comb_comp(){
	TH1D *h_1600 = new TH1D("1600GeV", "1600GeV", 11, 475, 1025);
	TH1D *h_1700 = new TH1D("1700GeV", "1700GeV", 11, 475, 1025);
	TH1D *h_1800 = new TH1D("1800GeV", "1800GeV", 11, 475, 1025);
	TH1D *h_1900 = new TH1D("1900GeV", "1900GeV", 11, 475, 1025);
	TH1D *h_2000 = new TH1D("2000GeV", "2000GeV", 11, 475, 1025);

	h_1600->SetBinContent(1,0.3203);
	h_1700->SetBinContent(1,0.5293);
	h_1800->SetBinContent(1,0.8320);
	h_1900->SetBinContent(1,1.4531);
	h_2000->SetBinContent(1,2.0781);
	h_1600->SetBinContent(2,0.3232);
	h_1700->SetBinContent(2,0.5215);
	h_1800->SetBinContent(2,0.8125);
	h_1900->SetBinContent(2,1.4102);
	h_2000->SetBinContent(2,1.9844);
	h_1600->SetBinContent(3,0.3271);
	h_1700->SetBinContent(3,0.5117);
	h_1800->SetBinContent(3,0.7930);
	h_1900->SetBinContent(3,1.3164);
	h_2000->SetBinContent(3,1.9062);
	h_1600->SetBinContent(4,0.3193);
	h_1700->SetBinContent(4,0.5078);
	h_1800->SetBinContent(4,0.7754);
	h_1900->SetBinContent(4,1.2656);
	h_2000->SetBinContent(4,1.8203);
	h_1600->SetBinContent(5,0.3115);
	h_1700->SetBinContent(5,0.5156);
	h_1800->SetBinContent(5,0.7734);
	h_1900->SetBinContent(5,1.2461);
	h_2000->SetBinContent(5,1.7969);
	h_1600->SetBinContent(6,0.3291);
	h_1700->SetBinContent(6,0.5312);
	h_1800->SetBinContent(6,0.7852);
	h_1900->SetBinContent(6,1.2656);
	h_2000->SetBinContent(6,1.8203);
	h_1600->SetBinContent(7,0.3154);
	h_1700->SetBinContent(7,0.5117);
	h_1800->SetBinContent(7,0.7402);
	h_1900->SetBinContent(7,1.1992);
	h_2000->SetBinContent(7,1.6641);
	h_1600->SetBinContent(8,0.3389);
	h_1700->SetBinContent(8,0.5156);
	h_1800->SetBinContent(8,0.7363);
	h_1900->SetBinContent(8,1.1680);
	h_2000->SetBinContent(8,1.6328);
	h_1600->SetBinContent(9,0.3623);
	h_1700->SetBinContent(9,0.5371);
	h_1800->SetBinContent(9,0.7578);
	h_1900->SetBinContent(9,1.1836);
	h_2000->SetBinContent(9,1.6641);
	h_1600->SetBinContent(10,0.3770);
	h_1700->SetBinContent(10,0.5488);
	h_1800->SetBinContent(10,0.7617);
	h_1900->SetBinContent(10,1.1953);
	h_2000->SetBinContent(10,1.6172);
	h_1600->SetBinContent(11,0.3701);
	h_1700->SetBinContent(11,0.5664);
	h_1800->SetBinContent(11,0.7852);
	h_1900->SetBinContent(11,1.2070);
	h_2000->SetBinContent(11,1.6172);
	
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
	legend->SetNColumns(2);
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
