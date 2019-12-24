void met()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:31 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-101.0156,-579.4688,912.6484,5215.219);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__5 = new TH1D("hdat__5","met",8,0.3508025,811.282);
   hdat__5->SetBinContent(1,4415);
   hdat__5->SetBinContent(2,598);
   hdat__5->SetBinContent(3,51);
   hdat__5->SetBinContent(4,11);
   hdat__5->SetBinContent(5,3);
   hdat__5->SetBinContent(7,1);
   hdat__5->SetBinContent(8,1);
   hdat__5->SetBinContent(9,1);
   hdat__5->SetEntries(5081);
   hdat__5->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__5->SetLineColor(ci);
   hdat__5->GetXaxis()->SetLabelFont(42);
   hdat__5->GetXaxis()->SetLabelSize(0.035);
   hdat__5->GetXaxis()->SetTitleSize(0.035);
   hdat__5->GetXaxis()->SetTitleFont(42);
   hdat__5->GetYaxis()->SetLabelFont(42);
   hdat__5->GetYaxis()->SetLabelSize(0.035);
   hdat__5->GetYaxis()->SetTitleSize(0.035);
   hdat__5->GetYaxis()->SetTitleOffset(0);
   hdat__5->GetYaxis()->SetTitleFont(42);
   hdat__5->GetZaxis()->SetLabelFont(42);
   hdat__5->GetZaxis()->SetLabelSize(0.035);
   hdat__5->GetZaxis()->SetTitleSize(0.035);
   hdat__5->GetZaxis()->SetTitleFont(42);
   hdat__5->Draw("");
   
   TPaveText *pt = new TPaveText(0.4714911,0.94,0.5285089,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("met");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
