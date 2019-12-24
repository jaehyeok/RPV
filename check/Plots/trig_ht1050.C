void trig_ht1050()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:09:06 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.375,-666.8813,3.375,6001.931);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__53 = new TH1D("hdat__53","trig_ht1050",3,0,3);
   hdat__53->SetBinContent(2,5081);
   hdat__53->SetEntries(5081);
   hdat__53->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__53->SetLineColor(ci);
   hdat__53->GetXaxis()->SetRange(1,100);
   hdat__53->GetXaxis()->SetLabelFont(42);
   hdat__53->GetXaxis()->SetLabelSize(0.035);
   hdat__53->GetXaxis()->SetTitleSize(0.035);
   hdat__53->GetXaxis()->SetTitleFont(42);
   hdat__53->GetYaxis()->SetLabelFont(42);
   hdat__53->GetYaxis()->SetLabelSize(0.035);
   hdat__53->GetYaxis()->SetTitleSize(0.035);
   hdat__53->GetYaxis()->SetTitleOffset(0);
   hdat__53->GetYaxis()->SetTitleFont(42);
   hdat__53->GetZaxis()->SetLabelFont(42);
   hdat__53->GetZaxis()->SetLabelSize(0.035);
   hdat__53->GetZaxis()->SetTitleSize(0.035);
   hdat__53->GetZaxis()->SetTitleFont(42);
   hdat__53->Draw("");
   
   TPaveText *pt = new TPaveText(0.4347341,0.9345349,0.5652659,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("trig_ht1050");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
