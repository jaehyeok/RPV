void jets_csv()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:20 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-12.625,-2200.538,3.625,19804.84);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__38 = new TH1D("hdat__38","jets_csv",100,-11,2);
   hdat__38->SetBinContent(8,7128);
   hdat__38->SetBinContent(85,53);
   hdat__38->SetBinContent(86,16766);
   hdat__38->SetBinContent(87,10666);
   hdat__38->SetBinContent(88,5626);
   hdat__38->SetBinContent(89,5810);
   hdat__38->SetBinContent(90,2463);
   hdat__38->SetBinContent(91,2092);
   hdat__38->SetBinContent(92,1658);
   hdat__38->SetBinContent(93,801);
   hdat__38->SetEntries(53063);
   hdat__38->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__38->SetLineColor(ci);
   hdat__38->GetXaxis()->SetRange(1,100);
   hdat__38->GetXaxis()->SetLabelFont(42);
   hdat__38->GetXaxis()->SetLabelSize(0.035);
   hdat__38->GetXaxis()->SetTitleSize(0.035);
   hdat__38->GetXaxis()->SetTitleFont(42);
   hdat__38->GetYaxis()->SetLabelFont(42);
   hdat__38->GetYaxis()->SetLabelSize(0.035);
   hdat__38->GetYaxis()->SetTitleSize(0.035);
   hdat__38->GetYaxis()->SetTitleOffset(0);
   hdat__38->GetYaxis()->SetTitleFont(42);
   hdat__38->GetZaxis()->SetLabelFont(42);
   hdat__38->GetZaxis()->SetLabelSize(0.035);
   hdat__38->GetZaxis()->SetTitleSize(0.035);
   hdat__38->GetZaxis()->SetTitleFont(42);
   hdat__38->Draw("");
   
   TPaveText *pt = new TPaveText(0.4488113,0.9345349,0.5511887,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_csv");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
