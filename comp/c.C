void c()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec  2 20:53:59 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,1600,800);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c_1
   TPad *c_1 = new TPad("c_1", "c_1",0.01,0.01,0.49,0.99);
   c_1->Draw();
   c_1->cd();
   c_1->Range(-1.125,-60686.59,5.125,546179.3);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *elku__5 = new TH1F("elku__5","",5,-0.5,4.5);
   elku__5->SetBinContent(1,462374);
   elku__5->SetBinContent(2,1541);
   elku__5->SetBinContent(3,34);
   elku__5->SetEntries(463949);
   elku__5->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   elku__5->SetLineColor(ci);
   elku__5->SetLineWidth(2);
   elku__5->GetXaxis()->SetLabelFont(42);
   elku__5->GetXaxis()->SetLabelSize(0.035);
   elku__5->GetXaxis()->SetTitleSize(0.035);
   elku__5->GetXaxis()->SetTitleFont(42);
   elku__5->GetYaxis()->SetLabelFont(42);
   elku__5->GetYaxis()->SetLabelSize(0.035);
   elku__5->GetYaxis()->SetTitleSize(0.035);
   elku__5->GetYaxis()->SetTitleOffset(0);
   elku__5->GetYaxis()->SetTitleFont(42);
   elku__5->GetZaxis()->SetLabelFont(42);
   elku__5->GetZaxis()->SetLabelSize(0.035);
   elku__5->GetZaxis()->SetTitleSize(0.035);
   elku__5->GetZaxis()->SetTitleFont(42);
   elku__5->Draw("");
   
   TH1F *eluc__6 = new TH1F("eluc__6","eluc",5,-0.5,4.5);
   eluc__6->SetBinContent(1,454908);
   eluc__6->SetBinContent(2,2562);
   eluc__6->SetBinContent(3,98);
   eluc__6->SetEntries(457568);
   eluc__6->SetStats(0);

   ci = TColor::GetColor("#000099");
   eluc__6->SetLineColor(ci);
   eluc__6->SetLineWidth(2);
   eluc__6->GetXaxis()->SetLabelFont(42);
   eluc__6->GetXaxis()->SetLabelSize(0.035);
   eluc__6->GetXaxis()->SetTitleSize(0.035);
   eluc__6->GetXaxis()->SetTitleFont(42);
   eluc__6->GetYaxis()->SetLabelFont(42);
   eluc__6->GetYaxis()->SetLabelSize(0.035);
   eluc__6->GetYaxis()->SetTitleSize(0.035);
   eluc__6->GetYaxis()->SetTitleOffset(0);
   eluc__6->GetYaxis()->SetTitleFont(42);
   eluc__6->GetZaxis()->SetLabelFont(42);
   eluc__6->GetZaxis()->SetLabelSize(0.035);
   eluc__6->GetZaxis()->SetTitleSize(0.035);
   eluc__6->GetZaxis()->SetTitleFont(42);
   eluc__6->Draw("same hist");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("elku","KU ntuple electron","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("eluc","UCSB ntuple electron","l");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c_1->Modified();
   c->cd();
  
// ------------>Primitives in pad: c_2
   TPad *c_2 = new TPad("c_2", "c_2",0.51,0.01,0.99,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-60586.97,5.125,545282.7);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *muku__7 = new TH1F("muku__7","",5,-0.5,4.5);
   muku__7->SetBinContent(1,461615);
   muku__7->SetBinContent(2,2272);
   muku__7->SetBinContent(3,62);
   muku__7->SetEntries(463949);
   muku__7->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   muku__7->SetLineColor(ci);
   muku__7->SetLineWidth(2);
   muku__7->GetXaxis()->SetLabelFont(42);
   muku__7->GetXaxis()->SetLabelSize(0.035);
   muku__7->GetXaxis()->SetTitleSize(0.035);
   muku__7->GetXaxis()->SetTitleFont(42);
   muku__7->GetYaxis()->SetLabelFont(42);
   muku__7->GetYaxis()->SetLabelSize(0.035);
   muku__7->GetYaxis()->SetTitleSize(0.035);
   muku__7->GetYaxis()->SetTitleOffset(0);
   muku__7->GetYaxis()->SetTitleFont(42);
   muku__7->GetZaxis()->SetLabelFont(42);
   muku__7->GetZaxis()->SetLabelSize(0.035);
   muku__7->GetZaxis()->SetTitleSize(0.035);
   muku__7->GetZaxis()->SetTitleFont(42);
   muku__7->Draw("");
   
   TH1F *muuc__8 = new TH1F("muuc__8","muuc",5,-0.5,4.5);
   muuc__8->SetBinContent(1,454737);
   muuc__8->SetBinContent(2,2720);
   muuc__8->SetBinContent(3,110);
   muuc__8->SetBinContent(4,1);
   muuc__8->SetEntries(457568);
   muuc__8->SetStats(0);

   ci = TColor::GetColor("#000099");
   muuc__8->SetLineColor(ci);
   muuc__8->SetLineWidth(2);
   muuc__8->GetXaxis()->SetLabelFont(42);
   muuc__8->GetXaxis()->SetLabelSize(0.035);
   muuc__8->GetXaxis()->SetTitleSize(0.035);
   muuc__8->GetXaxis()->SetTitleFont(42);
   muuc__8->GetYaxis()->SetLabelFont(42);
   muuc__8->GetYaxis()->SetLabelSize(0.035);
   muuc__8->GetYaxis()->SetTitleSize(0.035);
   muuc__8->GetYaxis()->SetTitleOffset(0);
   muuc__8->GetYaxis()->SetTitleFont(42);
   muuc__8->GetZaxis()->SetLabelFont(42);
   muuc__8->GetZaxis()->SetLabelSize(0.035);
   muuc__8->GetZaxis()->SetTitleSize(0.035);
   muuc__8->GetZaxis()->SetTitleFont(42);
   muuc__8->Draw("same hist");
   
   leg = new TLegend(0.4810962,0.670068,0.8617804,0.8704583,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("elku","KU ntuple electron","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("eluc","UCSB ntuple electron","l");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c_2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
