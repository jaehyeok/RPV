void mus_sigid()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:29 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,664.6931,2.25,1466.762);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__22 = new TH1D("hdat__22","mus_sigid",2,0,2);
   hdat__22->SetBinContent(1,774);
   hdat__22->SetBinContent(2,1356);
   hdat__22->SetEntries(2130);
   hdat__22->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__22->SetLineColor(ci);
   hdat__22->GetXaxis()->SetRange(1,100);
   hdat__22->GetXaxis()->SetLabelFont(42);
   hdat__22->GetXaxis()->SetLabelSize(0.035);
   hdat__22->GetXaxis()->SetTitleSize(0.035);
   hdat__22->GetXaxis()->SetTitleFont(42);
   hdat__22->GetYaxis()->SetLabelFont(42);
   hdat__22->GetYaxis()->SetLabelSize(0.035);
   hdat__22->GetYaxis()->SetTitleSize(0.035);
   hdat__22->GetYaxis()->SetTitleOffset(0);
   hdat__22->GetYaxis()->SetTitleFont(42);
   hdat__22->GetZaxis()->SetLabelFont(42);
   hdat__22->GetZaxis()->SetLabelSize(0.035);
   hdat__22->GetZaxis()->SetTitleSize(0.035);
   hdat__22->GetZaxis()->SetTitleFont(42);
   hdat__22->Draw("");
   
   TPaveText *pt = new TPaveText(0.4389051,0.9345349,0.5610949,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("mus_sigid");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
