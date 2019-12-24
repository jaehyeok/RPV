void w_lumi()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:50 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.275,-666.8813,2.475,6001.931);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__10 = new TH1D("hdat__10","w_lumi",100,0,2.2);
   hdat__10->SetBinContent(46,5081);
   hdat__10->SetEntries(5081);
   hdat__10->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__10->SetLineColor(ci);
   hdat__10->GetXaxis()->SetRange(1,100);
   hdat__10->GetXaxis()->SetLabelFont(42);
   hdat__10->GetXaxis()->SetLabelSize(0.035);
   hdat__10->GetXaxis()->SetTitleSize(0.035);
   hdat__10->GetXaxis()->SetTitleFont(42);
   hdat__10->GetYaxis()->SetLabelFont(42);
   hdat__10->GetYaxis()->SetLabelSize(0.035);
   hdat__10->GetYaxis()->SetTitleSize(0.035);
   hdat__10->GetYaxis()->SetTitleOffset(0);
   hdat__10->GetYaxis()->SetTitleFont(42);
   hdat__10->GetZaxis()->SetLabelFont(42);
   hdat__10->GetZaxis()->SetLabelSize(0.035);
   hdat__10->GetZaxis()->SetTitleSize(0.035);
   hdat__10->GetZaxis()->SetTitleFont(42);
   hdat__10->Draw("");
   
   TPaveText *pt = new TPaveText(0.4553285,0.9345349,0.5446715,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("w_lumi");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
