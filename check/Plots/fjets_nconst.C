void fjets_nconst()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:54 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.8750001,-792.3563,7.875,7131.206);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__49 = new TH1D("hdat__49","fjets_nconst",7,0,7);
   hdat__49->SetBinContent(2,6037);
   hdat__49->SetBinContent(3,5929);
   hdat__49->SetBinContent(4,3450);
   hdat__49->SetBinContent(5,1109);
   hdat__49->SetBinContent(6,225);
   hdat__49->SetBinContent(7,31);
   hdat__49->SetBinContent(8,1);
   hdat__49->SetEntries(16782);
   hdat__49->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__49->SetLineColor(ci);
   hdat__49->GetXaxis()->SetRange(1,100);
   hdat__49->GetXaxis()->SetLabelFont(42);
   hdat__49->GetXaxis()->SetLabelSize(0.035);
   hdat__49->GetXaxis()->SetTitleSize(0.035);
   hdat__49->GetXaxis()->SetTitleFont(42);
   hdat__49->GetYaxis()->SetLabelFont(42);
   hdat__49->GetYaxis()->SetLabelSize(0.035);
   hdat__49->GetYaxis()->SetTitleSize(0.035);
   hdat__49->GetYaxis()->SetTitleOffset(0);
   hdat__49->GetYaxis()->SetTitleFont(42);
   hdat__49->GetZaxis()->SetLabelFont(42);
   hdat__49->GetZaxis()->SetLabelSize(0.035);
   hdat__49->GetZaxis()->SetTitleSize(0.035);
   hdat__49->GetZaxis()->SetTitleFont(42);
   hdat__49->Draw("");
   
   TPaveText *pt = new TPaveText(0.4287383,0.9345349,0.5712617,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("fjets_nconst");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
