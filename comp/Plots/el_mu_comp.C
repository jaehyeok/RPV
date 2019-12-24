void el_mu_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Fri Dec 13 17:42:55 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,2400,800);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c_1
   TPad *c_1 = new TPad("c_1", "c_1",0.01,0.01,0.3233333,0.99);
   c_1->Draw();
   c_1->cd();
   c_1->Range(-1.125,-60354.53,5.125,543190.7);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *elku__1 = new TH1F("elku__1","",5,-0.5,4.5);
   elku__1->SetBinContent(1,459844);
   elku__1->SetBinContent(2,2866);
   elku__1->SetBinContent(3,105);
   elku__1->SetEntries(462815);
   elku__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   elku__1->SetLineColor(ci);
   elku__1->SetLineWidth(2);
   elku__1->GetXaxis()->SetLabelFont(42);
   elku__1->GetXaxis()->SetLabelSize(0.035);
   elku__1->GetXaxis()->SetTitleSize(0.035);
   elku__1->GetXaxis()->SetTitleFont(42);
   elku__1->GetYaxis()->SetLabelFont(42);
   elku__1->GetYaxis()->SetLabelSize(0.035);
   elku__1->GetYaxis()->SetTitleSize(0.035);
   elku__1->GetYaxis()->SetTitleOffset(0);
   elku__1->GetYaxis()->SetTitleFont(42);
   elku__1->GetZaxis()->SetLabelFont(42);
   elku__1->GetZaxis()->SetLabelSize(0.035);
   elku__1->GetZaxis()->SetTitleSize(0.035);
   elku__1->GetZaxis()->SetTitleFont(42);
   elku__1->Draw("");
   
   TH1F *eluc__2 = new TH1F("eluc__2","eluc",5,-0.5,4.5);
   eluc__2->SetBinContent(1,454908);
   eluc__2->SetBinContent(2,2562);
   eluc__2->SetBinContent(3,98);
   eluc__2->SetEntries(457568);
   eluc__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   eluc__2->SetLineColor(ci);
   eluc__2->SetLineWidth(2);
   eluc__2->GetXaxis()->SetLabelFont(42);
   eluc__2->GetXaxis()->SetLabelSize(0.035);
   eluc__2->GetXaxis()->SetTitleSize(0.035);
   eluc__2->GetXaxis()->SetTitleFont(42);
   eluc__2->GetYaxis()->SetLabelFont(42);
   eluc__2->GetYaxis()->SetLabelSize(0.035);
   eluc__2->GetYaxis()->SetTitleSize(0.035);
   eluc__2->GetYaxis()->SetTitleOffset(0);
   eluc__2->GetYaxis()->SetTitleFont(42);
   eluc__2->GetZaxis()->SetLabelFont(42);
   eluc__2->GetZaxis()->SetLabelSize(0.035);
   eluc__2->GetZaxis()->SetTitleSize(0.035);
   eluc__2->GetZaxis()->SetTitleFont(42);
   eluc__2->Draw("same hist");
   
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
   TPad *c_2 = new TPad("c_2", "c_2",0.3433333,0.01,0.6566667,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-60344.69,5.125,543102.1);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *muku__3 = new TH1F("muku__3","",5,-0.5,4.5);
   muku__3->SetBinContent(1,459769);
   muku__3->SetBinContent(2,2929);
   muku__3->SetBinContent(3,115);
   muku__3->SetBinContent(4,2);
   muku__3->SetEntries(462815);
   muku__3->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   muku__3->SetLineColor(ci);
   muku__3->SetLineWidth(2);
   muku__3->GetXaxis()->SetLabelFont(42);
   muku__3->GetXaxis()->SetLabelSize(0.035);
   muku__3->GetXaxis()->SetTitleSize(0.035);
   muku__3->GetXaxis()->SetTitleFont(42);
   muku__3->GetYaxis()->SetLabelFont(42);
   muku__3->GetYaxis()->SetLabelSize(0.035);
   muku__3->GetYaxis()->SetTitleSize(0.035);
   muku__3->GetYaxis()->SetTitleOffset(0);
   muku__3->GetYaxis()->SetTitleFont(42);
   muku__3->GetZaxis()->SetLabelFont(42);
   muku__3->GetZaxis()->SetLabelSize(0.035);
   muku__3->GetZaxis()->SetTitleSize(0.035);
   muku__3->GetZaxis()->SetTitleFont(42);
   muku__3->Draw("");
   
   TH1F *muuc__4 = new TH1F("muuc__4","muuc",5,-0.5,4.5);
   muuc__4->SetBinContent(1,454737);
   muuc__4->SetBinContent(2,2720);
   muuc__4->SetBinContent(3,110);
   muuc__4->SetBinContent(4,1);
   muuc__4->SetEntries(457568);
   muuc__4->SetStats(0);

   ci = TColor::GetColor("#000099");
   muuc__4->SetLineColor(ci);
   muuc__4->SetLineWidth(2);
   muuc__4->GetXaxis()->SetLabelFont(42);
   muuc__4->GetXaxis()->SetLabelSize(0.035);
   muuc__4->GetXaxis()->SetTitleSize(0.035);
   muuc__4->GetXaxis()->SetTitleFont(42);
   muuc__4->GetYaxis()->SetLabelFont(42);
   muuc__4->GetYaxis()->SetLabelSize(0.035);
   muuc__4->GetYaxis()->SetTitleSize(0.035);
   muuc__4->GetYaxis()->SetTitleOffset(0);
   muuc__4->GetYaxis()->SetTitleFont(42);
   muuc__4->GetZaxis()->SetLabelFont(42);
   muuc__4->GetZaxis()->SetLabelSize(0.035);
   muuc__4->GetZaxis()->SetTitleSize(0.035);
   muuc__4->GetZaxis()->SetTitleFont(42);
   muuc__4->Draw("same hist");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("elku","KU ntuple muon","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("eluc","UCSB ntuple muon","l");

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
  
// ------------>Primitives in pad: c_3
   TPad *c_3 = new TPad("c_3", "c_3",0.6766667,0.01,0.99,0.99);
   c_3->Draw();
   c_3->cd();
   c_3->Range(-1.125,-59344.3,5.125,534098.6);
   c_3->SetFillColor(0);
   c_3->SetBorderMode(0);
   c_3->SetBorderSize(2);
   c_3->SetFrameBorderMode(0);
   c_3->SetFrameBorderMode(0);
   
   TH1F *lepuc__5 = new TH1F("lepuc__5","",5,-0.5,4.5);
   lepuc__5->SetBinContent(1,452147);
   lepuc__5->SetBinContent(2,5143);
   lepuc__5->SetBinContent(3,276);
   lepuc__5->SetBinContent(4,2);
   lepuc__5->SetEntries(457568);
   lepuc__5->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   lepuc__5->SetLineColor(ci);
   lepuc__5->SetLineWidth(2);
   lepuc__5->GetXaxis()->SetLabelFont(42);
   lepuc__5->GetXaxis()->SetLabelSize(0.035);
   lepuc__5->GetXaxis()->SetTitleSize(0.035);
   lepuc__5->GetXaxis()->SetTitleFont(42);
   lepuc__5->GetYaxis()->SetLabelFont(42);
   lepuc__5->GetYaxis()->SetLabelSize(0.035);
   lepuc__5->GetYaxis()->SetTitleSize(0.035);
   lepuc__5->GetYaxis()->SetTitleOffset(0);
   lepuc__5->GetYaxis()->SetTitleFont(42);
   lepuc__5->GetZaxis()->SetLabelFont(42);
   lepuc__5->GetZaxis()->SetLabelSize(0.035);
   lepuc__5->GetZaxis()->SetTitleSize(0.035);
   lepuc__5->GetZaxis()->SetTitleFont(42);
   lepuc__5->Draw("");
   
   TH1F *lepku__6 = new TH1F("lepku__6","lepku",5,-0.5,4.5);
   lepku__6->SetBinContent(1,456876);
   lepku__6->SetBinContent(2,5642);
   lepku__6->SetBinContent(3,292);
   lepku__6->SetBinContent(4,5);
   lepku__6->SetEntries(462815);
   lepku__6->SetStats(0);

   ci = TColor::GetColor("#000099");
   lepku__6->SetLineColor(ci);
   lepku__6->SetLineWidth(2);
   lepku__6->GetXaxis()->SetLabelFont(42);
   lepku__6->GetXaxis()->SetLabelSize(0.035);
   lepku__6->GetXaxis()->SetTitleSize(0.035);
   lepku__6->GetXaxis()->SetTitleFont(42);
   lepku__6->GetYaxis()->SetLabelFont(42);
   lepku__6->GetYaxis()->SetLabelSize(0.035);
   lepku__6->GetYaxis()->SetTitleSize(0.035);
   lepku__6->GetYaxis()->SetTitleOffset(0);
   lepku__6->GetYaxis()->SetTitleFont(42);
   lepku__6->GetZaxis()->SetLabelFont(42);
   lepku__6->GetZaxis()->SetLabelSize(0.035);
   lepku__6->GetZaxis()->SetTitleSize(0.035);
   lepku__6->GetZaxis()->SetTitleFont(42);
   lepku__6->Draw("same hist");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("elku","KU ntuple leptons","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("eluc","UCSB ntuple leptons","l");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c_3->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
