void leps_eta()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:04 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-3.4625,-0.65625,3.1625,5.90625);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__14 = new TH1D("hdat__14","leps_eta",100,-2.8,2.5);
   hdat__14->SetBinContent(8,1);
   hdat__14->SetBinContent(12,1);
   hdat__14->SetBinContent(22,1);
   hdat__14->SetBinContent(28,1);
   hdat__14->SetBinContent(29,2);
   hdat__14->SetBinContent(32,2);
   hdat__14->SetBinContent(35,3);
   hdat__14->SetBinContent(36,1);
   hdat__14->SetBinContent(37,1);
   hdat__14->SetBinContent(42,1);
   hdat__14->SetBinContent(45,1);
   hdat__14->SetBinContent(47,3);
   hdat__14->SetBinContent(48,1);
   hdat__14->SetBinContent(50,2);
   hdat__14->SetBinContent(53,3);
   hdat__14->SetBinContent(54,1);
   hdat__14->SetBinContent(55,1);
   hdat__14->SetBinContent(56,1);
   hdat__14->SetBinContent(57,2);
   hdat__14->SetBinContent(62,1);
   hdat__14->SetBinContent(64,1);
   hdat__14->SetBinContent(65,2);
   hdat__14->SetBinContent(66,2);
   hdat__14->SetBinContent(68,1);
   hdat__14->SetBinContent(69,1);
   hdat__14->SetBinContent(70,1);
   hdat__14->SetBinContent(72,1);
   hdat__14->SetBinContent(77,5);
   hdat__14->SetBinContent(81,1);
   hdat__14->SetBinContent(85,1);
   hdat__14->SetBinContent(89,1);
   hdat__14->SetBinContent(92,1);
   hdat__14->SetBinContent(93,1);
   hdat__14->SetEntries(49);
   hdat__14->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__14->SetLineColor(ci);
   hdat__14->GetXaxis()->SetRange(1,100);
   hdat__14->GetXaxis()->SetLabelFont(42);
   hdat__14->GetXaxis()->SetLabelSize(0.035);
   hdat__14->GetXaxis()->SetTitleSize(0.035);
   hdat__14->GetXaxis()->SetTitleFont(42);
   hdat__14->GetYaxis()->SetLabelFont(42);
   hdat__14->GetYaxis()->SetLabelSize(0.035);
   hdat__14->GetYaxis()->SetTitleSize(0.035);
   hdat__14->GetYaxis()->SetTitleOffset(0);
   hdat__14->GetYaxis()->SetTitleFont(42);
   hdat__14->GetZaxis()->SetLabelFont(42);
   hdat__14->GetZaxis()->SetLabelSize(0.035);
   hdat__14->GetZaxis()->SetTitleSize(0.035);
   hdat__14->GetZaxis()->SetTitleFont(42);
   hdat__14->Draw("");
   
   TPaveText *pt = new TPaveText(0.4482899,0.9345349,0.5517101,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("leps_eta");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
