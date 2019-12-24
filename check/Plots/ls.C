void ls()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:05:09 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-210.625,-71.01219,1905.625,809.6097);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__2 = new TH1D("hdat__2","ls",16,1,1694);
   hdat__2->SetBinContent(1,369);
   hdat__2->SetBinContent(2,418);
   hdat__2->SetBinContent(3,358);
   hdat__2->SetBinContent(4,434);
   hdat__2->SetBinContent(5,688);
   hdat__2->SetBinContent(6,309);
   hdat__2->SetBinContent(7,513);
   hdat__2->SetBinContent(8,478);
   hdat__2->SetBinContent(9,312);
   hdat__2->SetBinContent(10,210);
   hdat__2->SetBinContent(11,168);
   hdat__2->SetBinContent(12,199);
   hdat__2->SetBinContent(13,364);
   hdat__2->SetBinContent(14,97);
   hdat__2->SetBinContent(15,49);
   hdat__2->SetBinContent(16,113);
   hdat__2->SetBinContent(17,2);
   hdat__2->SetEntries(5081);
   hdat__2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__2->SetLineColor(ci);
   hdat__2->GetXaxis()->SetLabelFont(42);
   hdat__2->GetXaxis()->SetLabelSize(0.035);
   hdat__2->GetXaxis()->SetTitleSize(0.035);
   hdat__2->GetXaxis()->SetTitleFont(42);
   hdat__2->GetYaxis()->SetLabelFont(42);
   hdat__2->GetYaxis()->SetLabelSize(0.035);
   hdat__2->GetYaxis()->SetTitleSize(0.035);
   hdat__2->GetYaxis()->SetTitleOffset(0);
   hdat__2->GetYaxis()->SetTitleFont(42);
   hdat__2->GetZaxis()->SetLabelFont(42);
   hdat__2->GetZaxis()->SetLabelSize(0.035);
   hdat__2->GetZaxis()->SetTitleSize(0.035);
   hdat__2->GetZaxis()->SetTitleFont(42);
   hdat__2->Draw("");
   
   TPaveText *pt = new TPaveText(0.481658,0.94,0.518342,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("ls");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
