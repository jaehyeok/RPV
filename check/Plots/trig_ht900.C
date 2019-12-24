void trig_ht900()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:09:04 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.125,-200.025,1.125,1800.225);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__52 = new TH1D("hdat__52","trig_ht900",1,0,1);
   hdat__52->SetBinContent(1,762);
   hdat__52->SetBinContent(2,4319);
   hdat__52->SetEntries(5081);
   hdat__52->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__52->SetLineColor(ci);
   hdat__52->GetXaxis()->SetLabelFont(42);
   hdat__52->GetXaxis()->SetLabelSize(0.035);
   hdat__52->GetXaxis()->SetTitleSize(0.035);
   hdat__52->GetXaxis()->SetTitleFont(42);
   hdat__52->GetYaxis()->SetLabelFont(42);
   hdat__52->GetYaxis()->SetLabelSize(0.035);
   hdat__52->GetYaxis()->SetTitleSize(0.035);
   hdat__52->GetYaxis()->SetTitleOffset(0);
   hdat__52->GetYaxis()->SetTitleFont(42);
   hdat__52->GetZaxis()->SetLabelFont(42);
   hdat__52->GetZaxis()->SetLabelSize(0.035);
   hdat__52->GetZaxis()->SetTitleSize(0.035);
   hdat__52->GetZaxis()->SetTitleFont(42);
   hdat__52->Draw("");
   
   TPaveText *pt = new TPaveText(0.4404692,0.9345349,0.5595308,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("trig_ht900");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
