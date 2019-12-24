void weight()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:40 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.275,-666.8813,2.475,6001.931);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__7 = new TH1D("hdat__7","weight",100,0,2.2);
   hdat__7->SetBinContent(46,5081);
   hdat__7->SetEntries(5081);
   hdat__7->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__7->SetLineColor(ci);
   hdat__7->GetXaxis()->SetRange(1,100);
   hdat__7->GetXaxis()->SetLabelFont(42);
   hdat__7->GetXaxis()->SetLabelSize(0.035);
   hdat__7->GetXaxis()->SetTitleSize(0.035);
   hdat__7->GetXaxis()->SetTitleFont(42);
   hdat__7->GetYaxis()->SetLabelFont(42);
   hdat__7->GetYaxis()->SetLabelSize(0.035);
   hdat__7->GetYaxis()->SetTitleSize(0.035);
   hdat__7->GetYaxis()->SetTitleOffset(0);
   hdat__7->GetYaxis()->SetTitleFont(42);
   hdat__7->GetZaxis()->SetLabelFont(42);
   hdat__7->GetZaxis()->SetLabelSize(0.035);
   hdat__7->GetZaxis()->SetTitleSize(0.035);
   hdat__7->GetZaxis()->SetTitleFont(42);
   hdat__7->Draw("");
   
   TPaveText *pt = new TPaveText(0.4571533,0.9345349,0.5428467,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("weight");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
