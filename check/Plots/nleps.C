void nleps()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:55 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-660.975,2.25,5948.775);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__12 = new TH1D("hdat__12","nleps",2,0,2);
   hdat__12->SetBinContent(1,5036);
   hdat__12->SetBinContent(2,41);
   hdat__12->SetBinContent(3,4);
   hdat__12->SetEntries(5081);
   hdat__12->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__12->SetLineColor(ci);
   hdat__12->GetXaxis()->SetLabelFont(42);
   hdat__12->GetXaxis()->SetLabelSize(0.035);
   hdat__12->GetXaxis()->SetTitleSize(0.035);
   hdat__12->GetXaxis()->SetTitleFont(42);
   hdat__12->GetYaxis()->SetLabelFont(42);
   hdat__12->GetYaxis()->SetLabelSize(0.035);
   hdat__12->GetYaxis()->SetTitleSize(0.035);
   hdat__12->GetYaxis()->SetTitleOffset(0);
   hdat__12->GetYaxis()->SetTitleFont(42);
   hdat__12->GetZaxis()->SetLabelFont(42);
   hdat__12->GetZaxis()->SetLabelSize(0.035);
   hdat__12->GetZaxis()->SetTitleSize(0.035);
   hdat__12->GetZaxis()->SetTitleFont(42);
   hdat__12->Draw("");
   
   TPaveText *pt = new TPaveText(0.4628884,0.9345349,0.5371116,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("nleps");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
