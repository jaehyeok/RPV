void nbm()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:03 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.5,-451.7625,4.5,4065.863);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__33 = new TH1D("hdat__33","nbm",4,0,4);
   hdat__33->SetBinContent(1,3442);
   hdat__33->SetBinContent(2,1251);
   hdat__33->SetBinContent(3,330);
   hdat__33->SetBinContent(4,54);
   hdat__33->SetBinContent(5,4);
   hdat__33->SetEntries(5081);
   hdat__33->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__33->SetLineColor(ci);
   hdat__33->GetXaxis()->SetLabelFont(42);
   hdat__33->GetXaxis()->SetLabelSize(0.035);
   hdat__33->GetXaxis()->SetTitleSize(0.035);
   hdat__33->GetXaxis()->SetTitleFont(42);
   hdat__33->GetYaxis()->SetLabelFont(42);
   hdat__33->GetYaxis()->SetLabelSize(0.035);
   hdat__33->GetYaxis()->SetTitleSize(0.035);
   hdat__33->GetYaxis()->SetTitleOffset(0);
   hdat__33->GetYaxis()->SetTitleFont(42);
   hdat__33->GetZaxis()->SetLabelFont(42);
   hdat__33->GetZaxis()->SetLabelSize(0.035);
   hdat__33->GetZaxis()->SetTitleSize(0.035);
   hdat__33->GetZaxis()->SetTitleFont(42);
   hdat__33->Draw("");
   
   TPaveText *pt = new TPaveText(0.4686236,0.94,0.5313764,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("nbm");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
