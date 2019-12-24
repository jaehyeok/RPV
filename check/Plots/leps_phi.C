void leps_phi()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:08 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-4.275,-0.65625,4.475,5.90625);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__15 = new TH1D("hdat__15","leps_phi",100,-3.4,3.6);
   hdat__15->SetBinContent(9,1);
   hdat__15->SetBinContent(10,1);
   hdat__15->SetBinContent(13,2);
   hdat__15->SetBinContent(14,2);
   hdat__15->SetBinContent(17,2);
   hdat__15->SetBinContent(18,2);
   hdat__15->SetBinContent(19,1);
   hdat__15->SetBinContent(25,2);
   hdat__15->SetBinContent(30,1);
   hdat__15->SetBinContent(34,1);
   hdat__15->SetBinContent(35,3);
   hdat__15->SetBinContent(36,1);
   hdat__15->SetBinContent(40,1);
   hdat__15->SetBinContent(44,1);
   hdat__15->SetBinContent(45,1);
   hdat__15->SetBinContent(47,1);
   hdat__15->SetBinContent(48,1);
   hdat__15->SetBinContent(49,1);
   hdat__15->SetBinContent(50,1);
   hdat__15->SetBinContent(54,1);
   hdat__15->SetBinContent(56,1);
   hdat__15->SetBinContent(67,1);
   hdat__15->SetBinContent(69,1);
   hdat__15->SetBinContent(70,1);
   hdat__15->SetBinContent(75,2);
   hdat__15->SetBinContent(76,1);
   hdat__15->SetBinContent(78,1);
   hdat__15->SetBinContent(80,5);
   hdat__15->SetBinContent(81,1);
   hdat__15->SetBinContent(82,1);
   hdat__15->SetBinContent(85,2);
   hdat__15->SetBinContent(87,2);
   hdat__15->SetBinContent(89,1);
   hdat__15->SetBinContent(93,2);
   hdat__15->SetEntries(49);
   hdat__15->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__15->SetLineColor(ci);
   hdat__15->GetXaxis()->SetRange(1,100);
   hdat__15->GetXaxis()->SetLabelFont(42);
   hdat__15->GetXaxis()->SetLabelSize(0.035);
   hdat__15->GetXaxis()->SetTitleSize(0.035);
   hdat__15->GetXaxis()->SetTitleFont(42);
   hdat__15->GetYaxis()->SetLabelFont(42);
   hdat__15->GetYaxis()->SetLabelSize(0.035);
   hdat__15->GetYaxis()->SetTitleSize(0.035);
   hdat__15->GetYaxis()->SetTitleOffset(0);
   hdat__15->GetYaxis()->SetTitleFont(42);
   hdat__15->GetZaxis()->SetLabelFont(42);
   hdat__15->GetZaxis()->SetLabelSize(0.035);
   hdat__15->GetZaxis()->SetTitleSize(0.035);
   hdat__15->GetZaxis()->SetTitleFont(42);
   hdat__15->Draw("");
   
   TPaveText *pt = new TPaveText(0.4482899,0.9345349,0.5517101,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("leps_phi");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
