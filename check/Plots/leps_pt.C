void leps_pt()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:58 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-39.375,-0.65625,354.375,5.90625);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__13 = new TH1D("hdat__13","leps_pt",100,0,315);
   hdat__13->SetBinContent(7,1);
   hdat__13->SetBinContent(8,5);
   hdat__13->SetBinContent(9,2);
   hdat__13->SetBinContent(11,1);
   hdat__13->SetBinContent(13,1);
   hdat__13->SetBinContent(14,1);
   hdat__13->SetBinContent(15,3);
   hdat__13->SetBinContent(17,2);
   hdat__13->SetBinContent(18,2);
   hdat__13->SetBinContent(20,1);
   hdat__13->SetBinContent(21,1);
   hdat__13->SetBinContent(22,1);
   hdat__13->SetBinContent(24,4);
   hdat__13->SetBinContent(26,2);
   hdat__13->SetBinContent(27,2);
   hdat__13->SetBinContent(31,2);
   hdat__13->SetBinContent(32,1);
   hdat__13->SetBinContent(33,3);
   hdat__13->SetBinContent(34,2);
   hdat__13->SetBinContent(37,1);
   hdat__13->SetBinContent(40,2);
   hdat__13->SetBinContent(42,1);
   hdat__13->SetBinContent(44,1);
   hdat__13->SetBinContent(45,1);
   hdat__13->SetBinContent(46,1);
   hdat__13->SetBinContent(49,1);
   hdat__13->SetBinContent(53,1);
   hdat__13->SetBinContent(57,1);
   hdat__13->SetBinContent(69,1);
   hdat__13->SetBinContent(93,1);
   hdat__13->SetEntries(49);
   hdat__13->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__13->SetLineColor(ci);
   hdat__13->GetXaxis()->SetRange(1,100);
   hdat__13->GetXaxis()->SetLabelFont(42);
   hdat__13->GetXaxis()->SetLabelSize(0.035);
   hdat__13->GetXaxis()->SetTitleSize(0.035);
   hdat__13->GetXaxis()->SetTitleFont(42);
   hdat__13->GetYaxis()->SetLabelFont(42);
   hdat__13->GetYaxis()->SetLabelSize(0.035);
   hdat__13->GetYaxis()->SetTitleSize(0.035);
   hdat__13->GetYaxis()->SetTitleOffset(0);
   hdat__13->GetYaxis()->SetTitleFont(42);
   hdat__13->GetZaxis()->SetLabelFont(42);
   hdat__13->GetZaxis()->SetLabelSize(0.035);
   hdat__13->GetZaxis()->SetTitleSize(0.035);
   hdat__13->GetZaxis()->SetTitleFont(42);
   hdat__13->Draw("");
   
   TPaveText *pt = new TPaveText(0.4537643,0.9345349,0.5462357,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("leps_pt");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
