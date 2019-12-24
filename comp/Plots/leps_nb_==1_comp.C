void leps_nb_==1_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec 23 14:49:09 2019) by ROOT version 6.12/07
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
   c_1->Range(-1.125,-46572.49,5.125,419152.4);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *lepku1__1 = new TH1F("lepku1__1","lepku1",5,-0.5,4.5);
   lepku1__1->SetBinContent(1,354838);
   lepku1__1->SetBinContent(2,3507);
   lepku1__1->SetBinContent(3,203);
   lepku1__1->SetBinContent(4,3);
   lepku1__1->SetEntries(358551);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("lepku1");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 358551 ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.01094");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1096");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepku1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepku1__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   lepku1__1->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   lepku1__1->SetLineColor(ci);
   lepku1__1->SetLineWidth(2);
   lepku1__1->GetXaxis()->SetLabelFont(42);
   lepku1__1->GetXaxis()->SetLabelSize(0.035);
   lepku1__1->GetXaxis()->SetTitleSize(0.035);
   lepku1__1->GetXaxis()->SetTitleFont(42);
   lepku1__1->GetYaxis()->SetLabelFont(42);
   lepku1__1->GetYaxis()->SetLabelSize(0.035);
   lepku1__1->GetYaxis()->SetTitleSize(0.035);
   lepku1__1->GetYaxis()->SetTitleOffset(0);
   lepku1__1->GetYaxis()->SetTitleFont(42);
   lepku1__1->GetZaxis()->SetLabelFont(42);
   lepku1__1->GetZaxis()->SetLabelSize(0.035);
   lepku1__1->GetZaxis()->SetTitleSize(0.035);
   lepku1__1->GetZaxis()->SetTitleFont(42);
   lepku1__1->Draw("");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("lepku1","==1","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4137328,0.9348829,0.5862672,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("lepku1");
   pt->Draw();
   c_1->Modified();
   c->cd();
  
// ------------>Primitives in pad: c_2
   TPad *c_2 = new TPad("c_2", "c_2",0.51,0.01,0.99,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-45492.96,5.125,409436.6);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *lepuc1__2 = new TH1F("lepuc1__2","lepuc1",5,-0.5,4.5);
   lepuc1__2->SetBinContent(1,346613);
   lepuc1__2->SetBinContent(2,3093);
   lepuc1__2->SetBinContent(3,191);
   lepuc1__2->SetBinContent(4,1);
   lepuc1__2->SetEntries(349898);
   
   ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("lepuc1");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 349898 ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.00994");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1046");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepuc1__2->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepuc1__2);

   ci = TColor::GetColor("#ff0000");
   lepuc1__2->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   lepuc1__2->SetLineColor(ci);
   lepuc1__2->SetLineWidth(2);
   lepuc1__2->GetXaxis()->SetLabelFont(42);
   lepuc1__2->GetXaxis()->SetLabelSize(0.035);
   lepuc1__2->GetXaxis()->SetTitleSize(0.035);
   lepuc1__2->GetXaxis()->SetTitleFont(42);
   lepuc1__2->GetYaxis()->SetLabelFont(42);
   lepuc1__2->GetYaxis()->SetLabelSize(0.035);
   lepuc1__2->GetYaxis()->SetTitleSize(0.035);
   lepuc1__2->GetYaxis()->SetTitleOffset(0);
   lepuc1__2->GetYaxis()->SetTitleFont(42);
   lepuc1__2->GetZaxis()->SetLabelFont(42);
   lepuc1__2->GetZaxis()->SetLabelSize(0.035);
   lepuc1__2->GetZaxis()->SetTitleSize(0.035);
   lepuc1__2->GetZaxis()->SetTitleFont(42);
   lepuc1__2->Draw("");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("lepuc1","==1","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   pt = new TPaveText(0.4137328,0.9348829,0.5862672,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt_LaTex = pt->AddText("lepuc1");
   pt->Draw();
   c_2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
