void leps_nb_>=4_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec 23 14:49:44 2019) by ROOT version 6.12/07
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
   c_1->Range(-1.125,-254.2313,5.125,2288.081);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *lepku4__7 = new TH1F("lepku4__7","lepku4",5,-0.5,4.5);
   lepku4__7->SetBinContent(1,1937);
   lepku4__7->SetBinContent(2,81);
   lepku4__7->SetBinContent(3,1);
   lepku4__7->SetEntries(2019);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("lepku4");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2019   ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.04111");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.201");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepku4__7->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepku4__7);
   lepku4__7->SetFillColor(1);
   lepku4__7->SetLineWidth(2);
   lepku4__7->GetXaxis()->SetLabelFont(42);
   lepku4__7->GetXaxis()->SetLabelSize(0.035);
   lepku4__7->GetXaxis()->SetTitleSize(0.035);
   lepku4__7->GetXaxis()->SetTitleFont(42);
   lepku4__7->GetYaxis()->SetLabelFont(42);
   lepku4__7->GetYaxis()->SetLabelSize(0.035);
   lepku4__7->GetYaxis()->SetTitleSize(0.035);
   lepku4__7->GetYaxis()->SetTitleOffset(0);
   lepku4__7->GetYaxis()->SetTitleFont(42);
   lepku4__7->GetZaxis()->SetLabelFont(42);
   lepku4__7->GetZaxis()->SetLabelSize(0.035);
   lepku4__7->GetZaxis()->SetTitleSize(0.035);
   lepku4__7->GetZaxis()->SetTitleFont(42);
   lepku4__7->Draw("");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("lepku4",">=4","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4098217,0.9348829,0.5901783,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("lepku4");
   pt->Draw();
   c_1->Modified();
   c->cd();
  
// ------------>Primitives in pad: c_2
   TPad *c_2 = new TPad("c_2", "c_2",0.51,0.01,0.99,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-290.4563,5.125,2614.106);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *lepuc4__8 = new TH1F("lepuc4__8","lepuc4",5,-0.5,4.5);
   lepuc4__8->SetBinContent(1,2213);
   lepuc4__8->SetBinContent(2,77);
   lepuc4__8->SetBinContent(3,3);
   lepuc4__8->SetEntries(2293);
   
   ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("lepuc4");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2293   ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.0362");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1937");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepuc4__8->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepuc4__8);
   lepuc4__8->SetFillColor(1);
   lepuc4__8->SetLineWidth(2);
   lepuc4__8->GetXaxis()->SetLabelFont(42);
   lepuc4__8->GetXaxis()->SetLabelSize(0.035);
   lepuc4__8->GetXaxis()->SetTitleSize(0.035);
   lepuc4__8->GetXaxis()->SetTitleFont(42);
   lepuc4__8->GetYaxis()->SetLabelFont(42);
   lepuc4__8->GetYaxis()->SetLabelSize(0.035);
   lepuc4__8->GetYaxis()->SetTitleSize(0.035);
   lepuc4__8->GetYaxis()->SetTitleOffset(0);
   lepuc4__8->GetYaxis()->SetTitleFont(42);
   lepuc4__8->GetZaxis()->SetLabelFont(42);
   lepuc4__8->GetZaxis()->SetLabelSize(0.035);
   lepuc4__8->GetZaxis()->SetTitleSize(0.035);
   lepuc4__8->GetZaxis()->SetTitleFont(42);
   lepuc4__8->Draw("");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("lepuc4",">=4","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   pt = new TPaveText(0.4098217,0.9348829,0.5901783,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   pt_LaTex = pt->AddText("lepuc4");
   pt->Draw();
   c_2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
