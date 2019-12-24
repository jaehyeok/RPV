void leps_nb_==2_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec 23 14:49:22 2019) by ROOT version 6.12/07
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
   c_1->Range(-1.125,-11343.68,5.125,102093.1);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *lepku2__3 = new TH1F("lepku2__3","lepku2",5,-0.5,4.5);
   lepku2__3->SetBinContent(1,86428);
   lepku2__3->SetBinContent(2,1721);
   lepku2__3->SetBinContent(3,77);
   lepku2__3->SetBinContent(4,2);
   lepku2__3->SetEntries(88228);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("lepku2");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 88228  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.02132");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1508");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepku2__3->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepku2__3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   lepku2__3->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   lepku2__3->SetLineColor(ci);
   lepku2__3->SetLineWidth(2);
   lepku2__3->GetXaxis()->SetLabelFont(42);
   lepku2__3->GetXaxis()->SetLabelSize(0.035);
   lepku2__3->GetXaxis()->SetTitleSize(0.035);
   lepku2__3->GetXaxis()->SetTitleFont(42);
   lepku2__3->GetYaxis()->SetLabelFont(42);
   lepku2__3->GetYaxis()->SetLabelSize(0.035);
   lepku2__3->GetYaxis()->SetTitleSize(0.035);
   lepku2__3->GetYaxis()->SetTitleOffset(0);
   lepku2__3->GetYaxis()->SetTitleFont(42);
   lepku2__3->GetZaxis()->SetLabelFont(42);
   lepku2__3->GetZaxis()->SetLabelSize(0.035);
   lepku2__3->GetZaxis()->SetTitleSize(0.035);
   lepku2__3->GetZaxis()->SetTitleFont(42);
   lepku2__3->Draw("");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("lepku2","==2","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4104735,0.9348829,0.5895265,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("lepku2");
   pt->Draw();
   c_1->Modified();
   c->cd();
  
// ------------>Primitives in pad: c_2
   TPad *c_2 = new TPad("c_2", "c_2",0.51,0.01,0.99,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-11620.35,5.125,104583.2);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *lepuc2__4 = new TH1F("lepuc2__4","lepuc2",5,-0.5,4.5);
   lepuc2__4->SetBinContent(1,88536);
   lepuc2__4->SetBinContent(2,1627);
   lepuc2__4->SetBinContent(3,68);
   lepuc2__4->SetBinContent(4,1);
   lepuc2__4->SetEntries(90232);
   
   ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("lepuc2");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 90232  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.01957");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1441");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepuc2__4->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepuc2__4);

   ci = TColor::GetColor("#009900");
   lepuc2__4->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   lepuc2__4->SetLineColor(ci);
   lepuc2__4->SetLineWidth(2);
   lepuc2__4->GetXaxis()->SetLabelFont(42);
   lepuc2__4->GetXaxis()->SetLabelSize(0.035);
   lepuc2__4->GetXaxis()->SetTitleSize(0.035);
   lepuc2__4->GetXaxis()->SetTitleFont(42);
   lepuc2__4->GetYaxis()->SetLabelFont(42);
   lepuc2__4->GetYaxis()->SetLabelSize(0.035);
   lepuc2__4->GetYaxis()->SetTitleSize(0.035);
   lepuc2__4->GetYaxis()->SetTitleOffset(0);
   lepuc2__4->GetYaxis()->SetTitleFont(42);
   lepuc2__4->GetZaxis()->SetLabelFont(42);
   lepuc2__4->GetZaxis()->SetLabelSize(0.035);
   lepuc2__4->GetZaxis()->SetTitleSize(0.035);
   lepuc2__4->GetZaxis()->SetTitleFont(42);
   lepuc2__4->Draw("");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("lepuc2","==2","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   pt = new TPaveText(0.4104735,0.9348829,0.5895265,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt_LaTex = pt->AddText("lepuc2");
   pt->Draw();
   c_2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
