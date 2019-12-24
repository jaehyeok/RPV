void trig_isomu24()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:09:09 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.125,-1330.35,1.125,11973.15);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__54 = new TH1D("hdat__54","trig_isomu24",1,0,1);
   hdat__54->SetBinContent(1,5068);
   hdat__54->SetBinContent(2,13);
   hdat__54->SetEntries(5081);
   hdat__54->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__54->SetLineColor(ci);
   hdat__54->GetXaxis()->SetLabelFont(42);
   hdat__54->GetXaxis()->SetLabelSize(0.035);
   hdat__54->GetXaxis()->SetTitleSize(0.035);
   hdat__54->GetXaxis()->SetTitleFont(42);
   hdat__54->GetYaxis()->SetLabelFont(42);
   hdat__54->GetYaxis()->SetLabelSize(0.035);
   hdat__54->GetYaxis()->SetTitleSize(0.035);
   hdat__54->GetYaxis()->SetTitleOffset(0);
   hdat__54->GetYaxis()->SetTitleFont(42);
   hdat__54->GetZaxis()->SetLabelFont(42);
   hdat__54->GetZaxis()->SetLabelSize(0.035);
   hdat__54->GetZaxis()->SetTitleSize(0.035);
   hdat__54->GetZaxis()->SetTitleFont(42);
   hdat__54->Draw("");
   
   TPaveText *pt = new TPaveText(0.4253493,0.9345349,0.5746507,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("trig_isomu24");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
