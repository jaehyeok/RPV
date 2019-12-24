void leps_stacked_comp()
{
//=========Macro generated from canvas: c/c
//=========  (Fri Dec 13 18:50:25 2019) by ROOT version 6.12/07
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
   c_1->Range(-1.125,-59964.98,5.125,539684.8);
   c_1->SetFillColor(0);
   c_1->SetBorderMode(0);
   c_1->SetBorderSize(2);
   c_1->SetFrameBorderMode(0);
   c_1->SetFrameBorderMode(0);
   
   THStack *lepsku = new THStack();
   lepsku->SetName("lepsku");
   lepsku->SetTitle("");
   
   TH1F *lepsku_stack_1 = new TH1F("lepsku_stack_1","",5,-0.5,4.5);
   lepsku_stack_1->SetMinimum(0);
   lepsku_stack_1->SetMaximum(479719.8);
   lepsku_stack_1->SetDirectory(0);
   lepsku_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   lepsku_stack_1->SetLineColor(ci);
   lepsku_stack_1->GetXaxis()->SetLabelFont(42);
   lepsku_stack_1->GetXaxis()->SetLabelSize(0.035);
   lepsku_stack_1->GetXaxis()->SetTitleSize(0.035);
   lepsku_stack_1->GetXaxis()->SetTitleFont(42);
   lepsku_stack_1->GetYaxis()->SetLabelFont(42);
   lepsku_stack_1->GetYaxis()->SetLabelSize(0.035);
   lepsku_stack_1->GetYaxis()->SetTitleSize(0.035);
   lepsku_stack_1->GetYaxis()->SetTitleOffset(0);
   lepsku_stack_1->GetYaxis()->SetTitleFont(42);
   lepsku_stack_1->GetZaxis()->SetLabelFont(42);
   lepsku_stack_1->GetZaxis()->SetLabelSize(0.035);
   lepsku_stack_1->GetZaxis()->SetTitleSize(0.035);
   lepsku_stack_1->GetZaxis()->SetTitleFont(42);
   lepsku->SetHistogram(lepsku_stack_1);
   
   
   TH1F *lepku1_stack_1 = new TH1F("lepku1_stack_1","lepku1",5,-0.5,4.5);
   lepku1_stack_1->SetBinContent(1,354838);
   lepku1_stack_1->SetBinContent(2,3507);
   lepku1_stack_1->SetBinContent(3,203);
   lepku1_stack_1->SetBinContent(4,3);
   lepku1_stack_1->SetEntries(358551);

   ci = TColor::GetColor("#ff0000");
   lepku1_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   lepku1_stack_1->SetLineColor(ci);
   lepku1_stack_1->SetLineWidth(2);
   lepku1_stack_1->GetXaxis()->SetLabelFont(42);
   lepku1_stack_1->GetXaxis()->SetLabelSize(0.035);
   lepku1_stack_1->GetXaxis()->SetTitleSize(0.035);
   lepku1_stack_1->GetXaxis()->SetTitleFont(42);
   lepku1_stack_1->GetYaxis()->SetLabelFont(42);
   lepku1_stack_1->GetYaxis()->SetLabelSize(0.035);
   lepku1_stack_1->GetYaxis()->SetTitleSize(0.035);
   lepku1_stack_1->GetYaxis()->SetTitleOffset(0);
   lepku1_stack_1->GetYaxis()->SetTitleFont(42);
   lepku1_stack_1->GetZaxis()->SetLabelFont(42);
   lepku1_stack_1->GetZaxis()->SetLabelSize(0.035);
   lepku1_stack_1->GetZaxis()->SetTitleSize(0.035);
   lepku1_stack_1->GetZaxis()->SetTitleFont(42);
   lepsku->Add(lepku1_stack_1,"");
   
   TH1F *lepku2_stack_2 = new TH1F("lepku2_stack_2","lepku2",5,-0.5,4.5);
   lepku2_stack_2->SetBinContent(1,86428);
   lepku2_stack_2->SetBinContent(2,1721);
   lepku2_stack_2->SetBinContent(3,77);
   lepku2_stack_2->SetBinContent(4,2);
   lepku2_stack_2->SetEntries(88228);

   ci = TColor::GetColor("#009900");
   lepku2_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   lepku2_stack_2->SetLineColor(ci);
   lepku2_stack_2->SetLineWidth(2);
   lepku2_stack_2->GetXaxis()->SetLabelFont(42);
   lepku2_stack_2->GetXaxis()->SetLabelSize(0.035);
   lepku2_stack_2->GetXaxis()->SetTitleSize(0.035);
   lepku2_stack_2->GetXaxis()->SetTitleFont(42);
   lepku2_stack_2->GetYaxis()->SetLabelFont(42);
   lepku2_stack_2->GetYaxis()->SetLabelSize(0.035);
   lepku2_stack_2->GetYaxis()->SetTitleSize(0.035);
   lepku2_stack_2->GetYaxis()->SetTitleOffset(0);
   lepku2_stack_2->GetYaxis()->SetTitleFont(42);
   lepku2_stack_2->GetZaxis()->SetLabelFont(42);
   lepku2_stack_2->GetZaxis()->SetLabelSize(0.035);
   lepku2_stack_2->GetZaxis()->SetTitleSize(0.035);
   lepku2_stack_2->GetZaxis()->SetTitleFont(42);
   lepsku->Add(lepku2_stack_2,"");
   
   TH1F *lepku3_stack_3 = new TH1F("lepku3_stack_3","lepku3",5,-0.5,4.5);
   lepku3_stack_3->SetBinContent(1,13673);
   lepku3_stack_3->SetBinContent(2,333);
   lepku3_stack_3->SetBinContent(3,11);
   lepku3_stack_3->SetEntries(14017);

   ci = TColor::GetColor("#0000ff");
   lepku3_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   lepku3_stack_3->SetLineColor(ci);
   lepku3_stack_3->SetLineWidth(2);
   lepku3_stack_3->GetXaxis()->SetLabelFont(42);
   lepku3_stack_3->GetXaxis()->SetLabelSize(0.035);
   lepku3_stack_3->GetXaxis()->SetTitleSize(0.035);
   lepku3_stack_3->GetXaxis()->SetTitleFont(42);
   lepku3_stack_3->GetYaxis()->SetLabelFont(42);
   lepku3_stack_3->GetYaxis()->SetLabelSize(0.035);
   lepku3_stack_3->GetYaxis()->SetTitleSize(0.035);
   lepku3_stack_3->GetYaxis()->SetTitleOffset(0);
   lepku3_stack_3->GetYaxis()->SetTitleFont(42);
   lepku3_stack_3->GetZaxis()->SetLabelFont(42);
   lepku3_stack_3->GetZaxis()->SetLabelSize(0.035);
   lepku3_stack_3->GetZaxis()->SetTitleSize(0.035);
   lepku3_stack_3->GetZaxis()->SetTitleFont(42);
   lepsku->Add(lepku3_stack_3,"");
   
   TH1F *lepku4_stack_4 = new TH1F("lepku4_stack_4","lepku4",5,-0.5,4.5);
   lepku4_stack_4->SetBinContent(1,1937);
   lepku4_stack_4->SetBinContent(2,81);
   lepku4_stack_4->SetBinContent(3,1);
   lepku4_stack_4->SetEntries(2019);
   lepku4_stack_4->SetFillColor(1);
   lepku4_stack_4->SetLineWidth(2);
   lepku4_stack_4->GetXaxis()->SetLabelFont(42);
   lepku4_stack_4->GetXaxis()->SetLabelSize(0.035);
   lepku4_stack_4->GetXaxis()->SetTitleSize(0.035);
   lepku4_stack_4->GetXaxis()->SetTitleFont(42);
   lepku4_stack_4->GetYaxis()->SetLabelFont(42);
   lepku4_stack_4->GetYaxis()->SetLabelSize(0.035);
   lepku4_stack_4->GetYaxis()->SetTitleSize(0.035);
   lepku4_stack_4->GetYaxis()->SetTitleOffset(0);
   lepku4_stack_4->GetYaxis()->SetTitleFont(42);
   lepku4_stack_4->GetZaxis()->SetLabelFont(42);
   lepku4_stack_4->GetZaxis()->SetLabelSize(0.035);
   lepku4_stack_4->GetZaxis()->SetTitleSize(0.035);
   lepku4_stack_4->GetZaxis()->SetTitleFont(42);
   lepsku->Add(lepku4_stack_4,"");
   lepsku->Draw("");
   
   TLegend *leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("lepku1_stack_1","==1","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepku2_stack_2","==2","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepku3_stack_3","==3","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepku4_stack_4",">=4","l");
   entry->SetLineColor(1);
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
   c_2->Range(-1.125,-59344.3,5.125,534098.6);
   c_2->SetFillColor(0);
   c_2->SetBorderMode(0);
   c_2->SetBorderSize(2);
   c_2->SetFrameBorderMode(0);
   c_2->SetFrameBorderMode(0);
   
   lepsuc = new THStack();
   lepsuc->SetName("lepsuc");
   lepsuc->SetTitle("");
   
   TH1F *lepsuc_stack_2 = new TH1F("lepsuc_stack_2","",5,-0.5,4.5);
   lepsuc_stack_2->SetMinimum(0);
   lepsuc_stack_2->SetMaximum(474754.4);
   lepsuc_stack_2->SetDirectory(0);
   lepsuc_stack_2->SetStats(0);

   ci = TColor::GetColor("#000099");
   lepsuc_stack_2->SetLineColor(ci);
   lepsuc_stack_2->GetXaxis()->SetLabelFont(42);
   lepsuc_stack_2->GetXaxis()->SetLabelSize(0.035);
   lepsuc_stack_2->GetXaxis()->SetTitleSize(0.035);
   lepsuc_stack_2->GetXaxis()->SetTitleFont(42);
   lepsuc_stack_2->GetYaxis()->SetLabelFont(42);
   lepsuc_stack_2->GetYaxis()->SetLabelSize(0.035);
   lepsuc_stack_2->GetYaxis()->SetTitleSize(0.035);
   lepsuc_stack_2->GetYaxis()->SetTitleOffset(0);
   lepsuc_stack_2->GetYaxis()->SetTitleFont(42);
   lepsuc_stack_2->GetZaxis()->SetLabelFont(42);
   lepsuc_stack_2->GetZaxis()->SetLabelSize(0.035);
   lepsuc_stack_2->GetZaxis()->SetTitleSize(0.035);
   lepsuc_stack_2->GetZaxis()->SetTitleFont(42);
   lepsuc->SetHistogram(lepsuc_stack_2);
   
   
   TH1F *lepuc1_stack_1 = new TH1F("lepuc1_stack_1","lepuc1",5,-0.5,4.5);
   lepuc1_stack_1->SetBinContent(1,346613);
   lepuc1_stack_1->SetBinContent(2,3093);
   lepuc1_stack_1->SetBinContent(3,191);
   lepuc1_stack_1->SetBinContent(4,1);
   lepuc1_stack_1->SetEntries(349898);

   ci = TColor::GetColor("#ff0000");
   lepuc1_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   lepuc1_stack_1->SetLineColor(ci);
   lepuc1_stack_1->SetLineWidth(2);
   lepuc1_stack_1->GetXaxis()->SetLabelFont(42);
   lepuc1_stack_1->GetXaxis()->SetLabelSize(0.035);
   lepuc1_stack_1->GetXaxis()->SetTitleSize(0.035);
   lepuc1_stack_1->GetXaxis()->SetTitleFont(42);
   lepuc1_stack_1->GetYaxis()->SetLabelFont(42);
   lepuc1_stack_1->GetYaxis()->SetLabelSize(0.035);
   lepuc1_stack_1->GetYaxis()->SetTitleSize(0.035);
   lepuc1_stack_1->GetYaxis()->SetTitleOffset(0);
   lepuc1_stack_1->GetYaxis()->SetTitleFont(42);
   lepuc1_stack_1->GetZaxis()->SetLabelFont(42);
   lepuc1_stack_1->GetZaxis()->SetLabelSize(0.035);
   lepuc1_stack_1->GetZaxis()->SetTitleSize(0.035);
   lepuc1_stack_1->GetZaxis()->SetTitleFont(42);
   lepsuc->Add(lepuc1_stack_1,"");
   
   TH1F *lepuc2_stack_2 = new TH1F("lepuc2_stack_2","lepuc2",5,-0.5,4.5);
   lepuc2_stack_2->SetBinContent(1,88536);
   lepuc2_stack_2->SetBinContent(2,1627);
   lepuc2_stack_2->SetBinContent(3,68);
   lepuc2_stack_2->SetBinContent(4,1);
   lepuc2_stack_2->SetEntries(90232);

   ci = TColor::GetColor("#009900");
   lepuc2_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#009900");
   lepuc2_stack_2->SetLineColor(ci);
   lepuc2_stack_2->SetLineWidth(2);
   lepuc2_stack_2->GetXaxis()->SetLabelFont(42);
   lepuc2_stack_2->GetXaxis()->SetLabelSize(0.035);
   lepuc2_stack_2->GetXaxis()->SetTitleSize(0.035);
   lepuc2_stack_2->GetXaxis()->SetTitleFont(42);
   lepuc2_stack_2->GetYaxis()->SetLabelFont(42);
   lepuc2_stack_2->GetYaxis()->SetLabelSize(0.035);
   lepuc2_stack_2->GetYaxis()->SetTitleSize(0.035);
   lepuc2_stack_2->GetYaxis()->SetTitleOffset(0);
   lepuc2_stack_2->GetYaxis()->SetTitleFont(42);
   lepuc2_stack_2->GetZaxis()->SetLabelFont(42);
   lepuc2_stack_2->GetZaxis()->SetLabelSize(0.035);
   lepuc2_stack_2->GetZaxis()->SetTitleSize(0.035);
   lepuc2_stack_2->GetZaxis()->SetTitleFont(42);
   lepsuc->Add(lepuc2_stack_2,"");
   
   TH1F *lepuc3_stack_3 = new TH1F("lepuc3_stack_3","lepuc3",5,-0.5,4.5);
   lepuc3_stack_3->SetBinContent(1,14785);
   lepuc3_stack_3->SetBinContent(2,346);
   lepuc3_stack_3->SetBinContent(3,14);
   lepuc3_stack_3->SetEntries(15145);

   ci = TColor::GetColor("#0000ff");
   lepuc3_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#0000ff");
   lepuc3_stack_3->SetLineColor(ci);
   lepuc3_stack_3->SetLineWidth(2);
   lepuc3_stack_3->GetXaxis()->SetLabelFont(42);
   lepuc3_stack_3->GetXaxis()->SetLabelSize(0.035);
   lepuc3_stack_3->GetXaxis()->SetTitleSize(0.035);
   lepuc3_stack_3->GetXaxis()->SetTitleFont(42);
   lepuc3_stack_3->GetYaxis()->SetLabelFont(42);
   lepuc3_stack_3->GetYaxis()->SetLabelSize(0.035);
   lepuc3_stack_3->GetYaxis()->SetTitleSize(0.035);
   lepuc3_stack_3->GetYaxis()->SetTitleOffset(0);
   lepuc3_stack_3->GetYaxis()->SetTitleFont(42);
   lepuc3_stack_3->GetZaxis()->SetLabelFont(42);
   lepuc3_stack_3->GetZaxis()->SetLabelSize(0.035);
   lepuc3_stack_3->GetZaxis()->SetTitleSize(0.035);
   lepuc3_stack_3->GetZaxis()->SetTitleFont(42);
   lepsuc->Add(lepuc3_stack_3,"");
   
   TH1F *lepuc4_stack_4 = new TH1F("lepuc4_stack_4","lepuc4",5,-0.5,4.5);
   lepuc4_stack_4->SetBinContent(1,2213);
   lepuc4_stack_4->SetBinContent(2,77);
   lepuc4_stack_4->SetBinContent(3,3);
   lepuc4_stack_4->SetEntries(2293);
   lepuc4_stack_4->SetFillColor(1);
   lepuc4_stack_4->SetLineWidth(2);
   lepuc4_stack_4->GetXaxis()->SetLabelFont(42);
   lepuc4_stack_4->GetXaxis()->SetLabelSize(0.035);
   lepuc4_stack_4->GetXaxis()->SetTitleSize(0.035);
   lepuc4_stack_4->GetXaxis()->SetTitleFont(42);
   lepuc4_stack_4->GetYaxis()->SetLabelFont(42);
   lepuc4_stack_4->GetYaxis()->SetLabelSize(0.035);
   lepuc4_stack_4->GetYaxis()->SetTitleSize(0.035);
   lepuc4_stack_4->GetYaxis()->SetTitleOffset(0);
   lepuc4_stack_4->GetYaxis()->SetTitleFont(42);
   lepuc4_stack_4->GetZaxis()->SetLabelFont(42);
   lepuc4_stack_4->GetZaxis()->SetLabelSize(0.035);
   lepuc4_stack_4->GetZaxis()->SetTitleSize(0.035);
   lepuc4_stack_4->GetZaxis()->SetTitleFont(42);
   lepsuc->Add(lepuc4_stack_4,"");
   lepsuc->Draw("");
   
   leg = new TLegend(0.477185,0.6740231,0.8578692,0.8744133,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("lepuc1_stack_1","==1","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepuc2_stack_2","==2","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepuc3_stack_3","==3","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("lepuc4_stack_4",">=4","l");
   entry->SetLineColor(1);
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
