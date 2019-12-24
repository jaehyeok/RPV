void jets_dcsvb()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:23 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-2.6875,-1498.219,1.6875,13483.97);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__39 = new TH1D("hdat__39","jets_dcsvb",100,-2.25,1.25);
   hdat__39->SetBinContent(8,9870);
   hdat__39->SetBinContent(65,2423);
   hdat__39->SetBinContent(66,11415);
   hdat__39->SetBinContent(67,7794);
   hdat__39->SetBinContent(68,5023);
   hdat__39->SetBinContent(69,3591);
   hdat__39->SetBinContent(70,2491);
   hdat__39->SetBinContent(71,1707);
   hdat__39->SetBinContent(72,1241);
   hdat__39->SetBinContent(73,973);
   hdat__39->SetBinContent(74,761);
   hdat__39->SetBinContent(75,701);
   hdat__39->SetBinContent(76,546);
   hdat__39->SetBinContent(77,456);
   hdat__39->SetBinContent(78,433);
   hdat__39->SetBinContent(79,341);
   hdat__39->SetBinContent(80,297);
   hdat__39->SetBinContent(81,275);
   hdat__39->SetBinContent(82,266);
   hdat__39->SetBinContent(83,211);
   hdat__39->SetBinContent(84,199);
   hdat__39->SetBinContent(85,189);
   hdat__39->SetBinContent(86,180);
   hdat__39->SetBinContent(87,180);
   hdat__39->SetBinContent(88,160);
   hdat__39->SetBinContent(89,173);
   hdat__39->SetBinContent(90,164);
   hdat__39->SetBinContent(91,182);
   hdat__39->SetBinContent(92,213);
   hdat__39->SetBinContent(93,608);
   hdat__39->SetEntries(53063);
   hdat__39->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__39->SetLineColor(ci);
   hdat__39->GetXaxis()->SetRange(1,100);
   hdat__39->GetXaxis()->SetLabelFont(42);
   hdat__39->GetXaxis()->SetLabelSize(0.035);
   hdat__39->GetXaxis()->SetTitleSize(0.035);
   hdat__39->GetXaxis()->SetTitleFont(42);
   hdat__39->GetYaxis()->SetLabelFont(42);
   hdat__39->GetYaxis()->SetLabelSize(0.035);
   hdat__39->GetYaxis()->SetTitleSize(0.035);
   hdat__39->GetYaxis()->SetTitleOffset(0);
   hdat__39->GetYaxis()->SetTitleFont(42);
   hdat__39->GetZaxis()->SetLabelFont(42);
   hdat__39->GetZaxis()->SetLabelSize(0.035);
   hdat__39->GetZaxis()->SetTitleSize(0.035);
   hdat__39->GetZaxis()->SetTitleFont(42);
   hdat__39->Draw("");
   
   TPaveText *pt = new TPaveText(0.4362982,0.9345349,0.5637018,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_dcsvb");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
