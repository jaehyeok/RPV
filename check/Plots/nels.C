void nels()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:35 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-663.6,2.25,5972.4);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__24 = new TH1D("hdat__24","nels",2,0,2);
   hdat__24->SetBinContent(1,5056);
   hdat__24->SetBinContent(2,24);
   hdat__24->SetBinContent(3,1);
   hdat__24->SetEntries(5081);
   hdat__24->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__24->SetLineColor(ci);
   hdat__24->GetXaxis()->SetLabelFont(42);
   hdat__24->GetXaxis()->SetLabelSize(0.035);
   hdat__24->GetXaxis()->SetTitleSize(0.035);
   hdat__24->GetXaxis()->SetTitleFont(42);
   hdat__24->GetYaxis()->SetLabelFont(42);
   hdat__24->GetYaxis()->SetLabelSize(0.035);
   hdat__24->GetYaxis()->SetTitleSize(0.035);
   hdat__24->GetYaxis()->SetTitleOffset(0);
   hdat__24->GetYaxis()->SetTitleFont(42);
   hdat__24->GetZaxis()->SetLabelFont(42);
   hdat__24->GetZaxis()->SetLabelSize(0.035);
   hdat__24->GetZaxis()->SetTitleSize(0.035);
   hdat__24->GetZaxis()->SetTitleFont(42);
   hdat__24->Draw("");
   
   TPaveText *pt = new TPaveText(0.4694056,0.94,0.5305944,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("nels");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
