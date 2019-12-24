void nmus()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:17 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-664.2563,2.25,5978.306);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__18 = new TH1D("hdat__18","nmus",2,0,2);
   hdat__18->SetBinContent(1,5061);
   hdat__18->SetBinContent(2,17);
   hdat__18->SetBinContent(3,3);
   hdat__18->SetEntries(5081);
   hdat__18->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__18->SetLineColor(ci);
   hdat__18->GetXaxis()->SetLabelFont(42);
   hdat__18->GetXaxis()->SetLabelSize(0.035);
   hdat__18->GetXaxis()->SetTitleSize(0.035);
   hdat__18->GetXaxis()->SetTitleFont(42);
   hdat__18->GetYaxis()->SetLabelFont(42);
   hdat__18->GetYaxis()->SetLabelSize(0.035);
   hdat__18->GetYaxis()->SetTitleSize(0.035);
   hdat__18->GetYaxis()->SetTitleOffset(0);
   hdat__18->GetYaxis()->SetTitleFont(42);
   hdat__18->GetZaxis()->SetLabelFont(42);
   hdat__18->GetZaxis()->SetLabelSize(0.035);
   hdat__18->GetZaxis()->SetTitleSize(0.035);
   hdat__18->GetZaxis()->SetTitleFont(42);
   hdat__18->Draw("");
   
   TPaveText *pt = new TPaveText(0.462367,0.94,0.537633,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("nmus");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
