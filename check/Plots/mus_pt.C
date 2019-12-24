void mus_pt()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:20 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-49.375,-101.325,444.375,911.925);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__19 = new TH1D("hdat__19","mus_pt",100,0,395);
   hdat__19->SetBinContent(1,500);
   hdat__19->SetBinContent(2,772);
   hdat__19->SetBinContent(3,287);
   hdat__19->SetBinContent(4,130);
   hdat__19->SetBinContent(5,79);
   hdat__19->SetBinContent(6,56);
   hdat__19->SetBinContent(7,58);
   hdat__19->SetBinContent(8,38);
   hdat__19->SetBinContent(9,25);
   hdat__19->SetBinContent(10,14);
   hdat__19->SetBinContent(11,29);
   hdat__19->SetBinContent(12,17);
   hdat__19->SetBinContent(13,10);
   hdat__19->SetBinContent(14,12);
   hdat__19->SetBinContent(15,14);
   hdat__19->SetBinContent(16,6);
   hdat__19->SetBinContent(17,6);
   hdat__19->SetBinContent(18,9);
   hdat__19->SetBinContent(19,9);
   hdat__19->SetBinContent(20,2);
   hdat__19->SetBinContent(21,6);
   hdat__19->SetBinContent(22,7);
   hdat__19->SetBinContent(23,1);
   hdat__19->SetBinContent(24,5);
   hdat__19->SetBinContent(25,5);
   hdat__19->SetBinContent(26,3);
   hdat__19->SetBinContent(27,4);
   hdat__19->SetBinContent(28,1);
   hdat__19->SetBinContent(29,2);
   hdat__19->SetBinContent(30,3);
   hdat__19->SetBinContent(31,3);
   hdat__19->SetBinContent(32,3);
   hdat__19->SetBinContent(34,1);
   hdat__19->SetBinContent(35,3);
   hdat__19->SetBinContent(38,1);
   hdat__19->SetBinContent(40,1);
   hdat__19->SetBinContent(43,1);
   hdat__19->SetBinContent(48,1);
   hdat__19->SetBinContent(53,1);
   hdat__19->SetBinContent(55,1);
   hdat__19->SetBinContent(65,2);
   hdat__19->SetBinContent(67,1);
   hdat__19->SetBinContent(92,1);
   hdat__19->SetEntries(2130);
   hdat__19->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__19->SetLineColor(ci);
   hdat__19->GetXaxis()->SetRange(1,100);
   hdat__19->GetXaxis()->SetLabelFont(42);
   hdat__19->GetXaxis()->SetLabelSize(0.035);
   hdat__19->GetXaxis()->SetTitleSize(0.035);
   hdat__19->GetXaxis()->SetTitleFont(42);
   hdat__19->GetYaxis()->SetLabelFont(42);
   hdat__19->GetYaxis()->SetLabelSize(0.035);
   hdat__19->GetYaxis()->SetTitleSize(0.035);
   hdat__19->GetYaxis()->SetTitleOffset(0);
   hdat__19->GetYaxis()->SetTitleFont(42);
   hdat__19->GetZaxis()->SetLabelFont(42);
   hdat__19->GetZaxis()->SetLabelSize(0.035);
   hdat__19->GetZaxis()->SetTitleSize(0.035);
   hdat__19->GetZaxis()->SetTitleFont(42);
   hdat__19->Draw("");
   
   TPaveText *pt = new TPaveText(0.4529823,0.9391861,0.5470177,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("mus_pt");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
