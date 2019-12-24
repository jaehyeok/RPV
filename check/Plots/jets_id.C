void jets_id()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:30 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-6927.376,2.25,62346.38);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__41 = new TH1D("hdat__41","jets_id",2,0,2);
   hdat__41->SetBinContent(1,283);
   hdat__41->SetBinContent(2,52780);
   hdat__41->SetEntries(53063);
   hdat__41->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__41->SetLineColor(ci);
   hdat__41->GetXaxis()->SetRange(1,100);
   hdat__41->GetXaxis()->SetLabelFont(42);
   hdat__41->GetXaxis()->SetLabelSize(0.035);
   hdat__41->GetXaxis()->SetTitleSize(0.035);
   hdat__41->GetXaxis()->SetTitleFont(42);
   hdat__41->GetYaxis()->SetLabelFont(42);
   hdat__41->GetYaxis()->SetLabelSize(0.035);
   hdat__41->GetYaxis()->SetTitleSize(0.035);
   hdat__41->GetYaxis()->SetTitleOffset(0);
   hdat__41->GetYaxis()->SetTitleFont(42);
   hdat__41->GetZaxis()->SetLabelFont(42);
   hdat__41->GetZaxis()->SetLabelSize(0.035);
   hdat__41->GetZaxis()->SetTitleSize(0.035);
   hdat__41->GetZaxis()->SetTitleFont(42);
   hdat__41->Draw("");
   
   TPaveText *pt = new TPaveText(0.457414,0.9345349,0.542586,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_id");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
