void jets_hflavor()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:38 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-2.19675e+08,-5634.3,1.977075e+09,50708.7);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__43 = new TH1D("hdat__43","jets_hflavor",101,0,1.7574e+09);
   hdat__43->SetBinContent(0,2);
   hdat__43->SetBinContent(1,42928);
   hdat__43->SetBinContent(56,5052);
   hdat__43->SetBinContent(97,5081);
   hdat__43->SetEntries(53063);
   hdat__43->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__43->SetLineColor(ci);
   hdat__43->GetXaxis()->SetRange(1,100);
   hdat__43->GetXaxis()->SetLabelFont(42);
   hdat__43->GetXaxis()->SetLabelSize(0.035);
   hdat__43->GetXaxis()->SetTitleSize(0.035);
   hdat__43->GetXaxis()->SetTitleFont(42);
   hdat__43->GetYaxis()->SetLabelFont(42);
   hdat__43->GetYaxis()->SetLabelSize(0.035);
   hdat__43->GetYaxis()->SetTitleSize(0.035);
   hdat__43->GetYaxis()->SetTitleOffset(0);
   hdat__43->GetYaxis()->SetTitleFont(42);
   hdat__43->GetZaxis()->SetLabelFont(42);
   hdat__43->GetZaxis()->SetLabelSize(0.035);
   hdat__43->GetZaxis()->SetTitleSize(0.035);
   hdat__43->GetZaxis()->SetTitleFont(42);
   hdat__43->Draw("");
   
   TPaveText *pt = new TPaveText(0.4316058,0.9345349,0.5683942,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_hflavor");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
