void ucsb_ku_comp_cuts_ht()
{
//=========Macro generated from canvas: c/c
//=========  (Fri Dec 13 17:43:04 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",20,43,800,800);
   c->Range(-625,-0.723442,5625,3.500678);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *htucsb__3 = new TH1D("htucsb__3","ht",25,0,5000);
   htucsb__3->SetBinContent(7,632);
   htucsb__3->SetBinContent(8,556);
   htucsb__3->SetBinContent(9,403);
   htucsb__3->SetBinContent(10,252);
   htucsb__3->SetBinContent(11,152);
   htucsb__3->SetBinContent(12,118);
   htucsb__3->SetBinContent(13,62);
   htucsb__3->SetBinContent(14,46);
   htucsb__3->SetBinContent(15,27);
   htucsb__3->SetBinContent(16,21);
   htucsb__3->SetBinContent(17,8);
   htucsb__3->SetBinContent(18,2);
   htucsb__3->SetBinContent(19,9);
   htucsb__3->SetBinContent(20,1);
   htucsb__3->SetBinContent(21,1);
   htucsb__3->SetBinContent(22,1);
   htucsb__3->SetBinContent(23,1);
   htucsb__3->SetBinContent(26,1);
   htucsb__3->SetEntries(2293);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("htucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2293   ");
   ptstats_LaTex = ptstats->AddText("Mean  =   1704");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  447.6");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   htucsb__3->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(htucsb__3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htucsb__3->SetLineColor(ci);
   htucsb__3->SetLineWidth(2);
   htucsb__3->GetXaxis()->SetLabelFont(42);
   htucsb__3->GetXaxis()->SetLabelSize(0.035);
   htucsb__3->GetXaxis()->SetTitleSize(0.035);
   htucsb__3->GetXaxis()->SetTitleFont(42);
   htucsb__3->GetYaxis()->SetLabelFont(42);
   htucsb__3->GetYaxis()->SetLabelSize(0.035);
   htucsb__3->GetYaxis()->SetTitleSize(0.035);
   htucsb__3->GetYaxis()->SetTitleOffset(0);
   htucsb__3->GetYaxis()->SetTitleFont(42);
   htucsb__3->GetZaxis()->SetLabelFont(42);
   htucsb__3->GetZaxis()->SetLabelSize(0.035);
   htucsb__3->GetZaxis()->SetTitleSize(0.035);
   htucsb__3->GetZaxis()->SetTitleFont(42);
   htucsb__3->Draw("");
   
   TH1D *htku__4 = new TH1D("htku__4","",25,0,5000);
   htku__4->SetBinContent(7,567);
   htku__4->SetBinContent(8,495);
   htku__4->SetBinContent(9,360);
   htku__4->SetBinContent(10,231);
   htku__4->SetBinContent(11,138);
   htku__4->SetBinContent(12,84);
   htku__4->SetBinContent(13,51);
   htku__4->SetBinContent(14,41);
   htku__4->SetBinContent(15,17);
   htku__4->SetBinContent(16,18);
   htku__4->SetBinContent(17,6);
   htku__4->SetBinContent(18,7);
   htku__4->SetBinContent(19,2);
   htku__4->SetBinContent(20,3);
   htku__4->SetBinContent(21,1);
   htku__4->SetBinContent(23,1);
   htku__4->SetBinContent(26,2);
   htku__4->SetEntries(2024);

   ci = TColor::GetColor("#ff0000");
   htku__4->SetLineColor(ci);
   htku__4->SetLineWidth(2);
   htku__4->GetXaxis()->SetLabelFont(42);
   htku__4->GetXaxis()->SetLabelSize(0.035);
   htku__4->GetXaxis()->SetTitleSize(0.035);
   htku__4->GetXaxis()->SetTitleFont(42);
   htku__4->GetYaxis()->SetLabelFont(42);
   htku__4->GetYaxis()->SetLabelSize(0.035);
   htku__4->GetYaxis()->SetTitleSize(0.035);
   htku__4->GetYaxis()->SetTitleOffset(0);
   htku__4->GetYaxis()->SetTitleFont(42);
   htku__4->GetZaxis()->SetLabelFont(42);
   htku__4->GetZaxis()->SetLabelSize(0.035);
   htku__4->GetZaxis()->SetTitleSize(0.035);
   htku__4->GetZaxis()->SetTitleFont(42);
   htku__4->Draw("same hist");
   
   TPaveText *pt = new TPaveText(0.466817,0.94,0.533183,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("ht");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
