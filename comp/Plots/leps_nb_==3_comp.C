void leps_nb_==3_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec 23 14:49:32 2019) by ROOT version 6.12/07
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
   c_1->Range(-1.125,-1794.581,5.125,16151.23);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   TH1F *lepku3__5 = new TH1F("lepku3__5","lepku3",5,-0.5,4.5);
   lepku3__5->SetBinContent(1,13673);
   lepku3__5->SetBinContent(2,333);
   lepku3__5->SetBinContent(3,11);
   lepku3__5->SetEntries(14017);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("lepku3");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 14017  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.02533");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.162");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepku3__5->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepku3__5);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   lepku3__5->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   lepku3__5->SetLineColor(ci);
   lepku3__5->SetLineWidth(2);
   lepku3__5->GetXaxis()->SetLabelFont(42);
   lepku3__5->GetXaxis()->SetLabelSize(0.035);
   lepku3__5->GetXaxis()->SetTitleSize(0.035);
   lepku3__5->GetXaxis()->SetTitleFont(42);
   lepku3__5->GetYaxis()->SetLabelFont(42);
   lepku3__5->GetYaxis()->SetLabelSize(0.035);
   lepku3__5->GetYaxis()->SetTitleSize(0.035);
   lepku3__5->GetYaxis()->SetTitleOffset(0);
   lepku3__5->GetYaxis()->SetTitleFont(42);
   lepku3__5->GetZaxis()->SetLabelFont(42);
   lepku3__5->GetZaxis()->SetLabelSize(0.035);
   lepku3__5->GetZaxis()->SetTitleSize(0.035);
   lepku3__5->GetZaxis()->SetTitleFont(42);
   lepku3__5->Draw("");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("lepku3","==3","l");

   ci = TColor::GetColor("#0000ff");
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
   TText *pt_LaTex = pt->AddText("lepku3");
   pt->Draw();
   c_1->Modified();
   c->cd();
  
// ------------>Primitives in pad: c_2
   TPad *c_2 = new TPad("c_2", "c_2",0.51,0.01,0.99,0.99);
   c_2->Draw();
   c_2->cd();
   c_2->Range(-1.125,-1940.531,5.125,17464.78);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   TH1F *lepuc3__6 = new TH1F("lepuc3__6","lepuc3",5,-0.5,4.5);
   lepuc3__6->SetBinContent(1,14785);
   lepuc3__6->SetBinContent(2,346);
   lepuc3__6->SetBinContent(3,14);
   lepuc3__6->SetEntries(15145);
   
   ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   ptstats_LaTex = ptstats->AddText("lepuc3");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 15145  ");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.02469");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  0.161");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   lepuc3__6->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(lepuc3__6);

   ci = TColor::GetColor("#0000ff");
   lepuc3__6->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   lepuc3__6->SetLineColor(ci);
   lepuc3__6->SetLineWidth(2);
   lepuc3__6->GetXaxis()->SetLabelFont(42);
   lepuc3__6->GetXaxis()->SetLabelSize(0.035);
   lepuc3__6->GetXaxis()->SetTitleSize(0.035);
   lepuc3__6->GetXaxis()->SetTitleFont(42);
   lepuc3__6->GetYaxis()->SetLabelFont(42);
   lepuc3__6->GetYaxis()->SetLabelSize(0.035);
   lepuc3__6->GetYaxis()->SetTitleSize(0.035);
   lepuc3__6->GetYaxis()->SetTitleOffset(0);
   lepuc3__6->GetYaxis()->SetTitleFont(42);
   lepuc3__6->GetZaxis()->SetLabelFont(42);
   lepuc3__6->GetZaxis()->SetLabelSize(0.035);
   lepuc3__6->GetZaxis()->SetTitleSize(0.035);
   lepuc3__6->GetZaxis()->SetTitleFont(42);
   lepuc3__6->Draw("");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("lepuc3","==3","l");

   ci = TColor::GetColor("#0000ff");
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
   pt_LaTex = pt->AddText("lepuc3");
   pt->Draw();
   c_2->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
