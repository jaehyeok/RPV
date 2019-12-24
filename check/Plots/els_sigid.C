void els_sigid()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:48 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-745.6313,2.25,6710.681);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__28 = new TH1D("hdat__28","els_sigid",2,0,2);
   hdat__28->SetBinContent(1,5681);
   hdat__28->SetBinContent(2,173);
   hdat__28->SetEntries(5854);
   hdat__28->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__28->SetLineColor(ci);
   hdat__28->GetXaxis()->SetRange(1,100);
   hdat__28->GetXaxis()->SetLabelFont(42);
   hdat__28->GetXaxis()->SetLabelSize(0.035);
   hdat__28->GetXaxis()->SetTitleSize(0.035);
   hdat__28->GetXaxis()->SetTitleFont(42);
   hdat__28->GetYaxis()->SetLabelFont(42);
   hdat__28->GetYaxis()->SetLabelSize(0.035);
   hdat__28->GetYaxis()->SetTitleSize(0.035);
   hdat__28->GetYaxis()->SetTitleOffset(0);
   hdat__28->GetYaxis()->SetTitleFont(42);
   hdat__28->GetZaxis()->SetLabelFont(42);
   hdat__28->GetZaxis()->SetLabelSize(0.035);
   hdat__28->GetZaxis()->SetTitleSize(0.035);
   hdat__28->GetZaxis()->SetTitleFont(42);
   hdat__28->Draw("");
   
   TPaveText *pt = new TPaveText(0.4459437,0.9345349,0.5540563,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("els_sigid");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
