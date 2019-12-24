void ht()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:28 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(656.125,-96.46876,6095.5,868.2188);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__4 = new TH1D("hdat__4","ht",43,1200.062,5551.562);
   hdat__4->SetBinContent(1,720);
   hdat__4->SetBinContent(2,735);
   hdat__4->SetBinContent(3,681);
   hdat__4->SetBinContent(4,598);
   hdat__4->SetBinContent(5,485);
   hdat__4->SetBinContent(6,389);
   hdat__4->SetBinContent(7,321);
   hdat__4->SetBinContent(8,252);
   hdat__4->SetBinContent(9,183);
   hdat__4->SetBinContent(10,166);
   hdat__4->SetBinContent(11,141);
   hdat__4->SetBinContent(12,91);
   hdat__4->SetBinContent(13,79);
   hdat__4->SetBinContent(14,49);
   hdat__4->SetBinContent(15,32);
   hdat__4->SetBinContent(16,34);
   hdat__4->SetBinContent(17,36);
   hdat__4->SetBinContent(18,22);
   hdat__4->SetBinContent(19,13);
   hdat__4->SetBinContent(20,9);
   hdat__4->SetBinContent(21,8);
   hdat__4->SetBinContent(22,10);
   hdat__4->SetBinContent(23,3);
   hdat__4->SetBinContent(24,3);
   hdat__4->SetBinContent(25,4);
   hdat__4->SetBinContent(26,3);
   hdat__4->SetBinContent(27,4);
   hdat__4->SetBinContent(28,2);
   hdat__4->SetBinContent(29,3);
   hdat__4->SetBinContent(30,3);
   hdat__4->SetBinContent(31,1);
   hdat__4->SetBinContent(44,1);
   hdat__4->SetEntries(5081);
   hdat__4->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__4->SetLineColor(ci);
   hdat__4->GetXaxis()->SetLabelFont(42);
   hdat__4->GetXaxis()->SetLabelSize(0.035);
   hdat__4->GetXaxis()->SetTitleSize(0.035);
   hdat__4->GetXaxis()->SetTitleFont(42);
   hdat__4->GetYaxis()->SetLabelFont(42);
   hdat__4->GetYaxis()->SetLabelSize(0.035);
   hdat__4->GetYaxis()->SetTitleSize(0.035);
   hdat__4->GetYaxis()->SetTitleOffset(0);
   hdat__4->GetYaxis()->SetTitleFont(42);
   hdat__4->GetZaxis()->SetLabelFont(42);
   hdat__4->GetZaxis()->SetLabelSize(0.035);
   hdat__4->GetZaxis()->SetTitleSize(0.035);
   hdat__4->GetZaxis()->SetTitleFont(42);
   hdat__4->Draw("");
   
   TPaveText *pt = new TPaveText(0.4803545,0.94,0.5196455,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("ht");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
