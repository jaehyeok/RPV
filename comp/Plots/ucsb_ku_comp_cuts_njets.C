void ucsb_ku_comp_cuts_njets()
{
//=========Macro generated from canvas: c/c
//=========  (Fri Dec 13 17:55:04 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-3,-0.03130303,22,3.292027);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *njetsucsb__5 = new TH1D("njetsucsb__5","njets",20,-0.5,19.5);
   njetsucsb__5->SetBinContent(5,28);
   njetsucsb__5->SetBinContent(6,123);
   njetsucsb__5->SetBinContent(7,251);
   njetsucsb__5->SetBinContent(8,417);
   njetsucsb__5->SetBinContent(9,481);
   njetsucsb__5->SetBinContent(10,394);
   njetsucsb__5->SetBinContent(11,280);
   njetsucsb__5->SetBinContent(12,175);
   njetsucsb__5->SetBinContent(13,83);
   njetsucsb__5->SetBinContent(14,35);
   njetsucsb__5->SetBinContent(15,22);
   njetsucsb__5->SetBinContent(16,4);
   njetsucsb__5->SetEntries(2293);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("njetsucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2293   ");
   ptstats_LaTex = ptstats->AddText("Mean  =  8.325");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  1.983");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   njetsucsb__5->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(njetsucsb__5);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   njetsucsb__5->SetLineColor(ci);
   njetsucsb__5->SetLineWidth(2);
   njetsucsb__5->GetXaxis()->SetLabelFont(42);
   njetsucsb__5->GetXaxis()->SetLabelSize(0.035);
   njetsucsb__5->GetXaxis()->SetTitleSize(0.035);
   njetsucsb__5->GetXaxis()->SetTitleFont(42);
   njetsucsb__5->GetYaxis()->SetLabelFont(42);
   njetsucsb__5->GetYaxis()->SetLabelSize(0.035);
   njetsucsb__5->GetYaxis()->SetTitleSize(0.035);
   njetsucsb__5->GetYaxis()->SetTitleOffset(0);
   njetsucsb__5->GetYaxis()->SetTitleFont(42);
   njetsucsb__5->GetZaxis()->SetLabelFont(42);
   njetsucsb__5->GetZaxis()->SetLabelSize(0.035);
   njetsucsb__5->GetZaxis()->SetTitleSize(0.035);
   njetsucsb__5->GetZaxis()->SetTitleFont(42);
   njetsucsb__5->Draw("");
   
   TH1D *njetsku__6 = new TH1D("njetsku__6","",20,-0.5,19.5);
   njetsku__6->SetBinContent(5,24);
   njetsku__6->SetBinContent(6,102);
   njetsku__6->SetBinContent(7,210);
   njetsku__6->SetBinContent(8,388);
   njetsku__6->SetBinContent(9,401);
   njetsku__6->SetBinContent(10,379);
   njetsku__6->SetBinContent(11,250);
   njetsku__6->SetBinContent(12,148);
   njetsku__6->SetBinContent(13,71);
   njetsku__6->SetBinContent(14,28);
   njetsku__6->SetBinContent(15,20);
   njetsku__6->SetBinContent(16,2);
   njetsku__6->SetBinContent(17,1);
   njetsku__6->SetEntries(2024);

   ci = TColor::GetColor("#ff0000");
   njetsku__6->SetLineColor(ci);
   njetsku__6->SetLineWidth(2);
   njetsku__6->GetXaxis()->SetLabelFont(42);
   njetsku__6->GetXaxis()->SetLabelSize(0.035);
   njetsku__6->GetXaxis()->SetTitleSize(0.035);
   njetsku__6->GetXaxis()->SetTitleFont(42);
   njetsku__6->GetYaxis()->SetLabelFont(42);
   njetsku__6->GetYaxis()->SetLabelSize(0.035);
   njetsku__6->GetYaxis()->SetTitleSize(0.035);
   njetsku__6->GetYaxis()->SetTitleOffset(0);
   njetsku__6->GetYaxis()->SetTitleFont(42);
   njetsku__6->GetZaxis()->SetLabelFont(42);
   njetsku__6->GetZaxis()->SetLabelSize(0.035);
   njetsku__6->GetZaxis()->SetTitleSize(0.035);
   njetsku__6->GetZaxis()->SetTitleFont(42);
   njetsku__6->Draw("same hist");
   
   TPaveText *pt = new TPaveText(0.4323559,0.9345349,0.5676441,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("njets");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
