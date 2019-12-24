void leps_miniso()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:13 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.01675,-3.9375,0.15075,35.4375);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__17 = new TH1D("hdat__17","leps_miniso",100,0,0.134);
   hdat__17->SetBinContent(1,30);
   hdat__17->SetBinContent(4,2);
   hdat__17->SetBinContent(11,1);
   hdat__17->SetBinContent(15,1);
   hdat__17->SetBinContent(19,1);
   hdat__17->SetBinContent(21,1);
   hdat__17->SetBinContent(23,2);
   hdat__17->SetBinContent(24,1);
   hdat__17->SetBinContent(26,1);
   hdat__17->SetBinContent(27,1);
   hdat__17->SetBinContent(34,1);
   hdat__17->SetBinContent(36,1);
   hdat__17->SetBinContent(41,1);
   hdat__17->SetBinContent(46,1);
   hdat__17->SetBinContent(52,1);
   hdat__17->SetBinContent(72,1);
   hdat__17->SetBinContent(87,1);
   hdat__17->SetBinContent(92,1);
   hdat__17->SetEntries(49);
   hdat__17->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__17->SetLineColor(ci);
   hdat__17->GetXaxis()->SetRange(1,100);
   hdat__17->GetXaxis()->SetLabelFont(42);
   hdat__17->GetXaxis()->SetLabelSize(0.035);
   hdat__17->GetXaxis()->SetTitleSize(0.035);
   hdat__17->GetXaxis()->SetTitleFont(42);
   hdat__17->GetYaxis()->SetLabelFont(42);
   hdat__17->GetYaxis()->SetLabelSize(0.035);
   hdat__17->GetYaxis()->SetTitleSize(0.035);
   hdat__17->GetYaxis()->SetTitleOffset(0);
   hdat__17->GetYaxis()->SetTitleFont(42);
   hdat__17->GetZaxis()->SetLabelFont(42);
   hdat__17->GetZaxis()->SetLabelSize(0.035);
   hdat__17->GetZaxis()->SetTitleSize(0.035);
   hdat__17->GetZaxis()->SetTitleFont(42);
   hdat__17->Draw("");
   
   TPaveText *pt = new TPaveText(0.4300417,0.9345349,0.5699583,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("leps_miniso");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
