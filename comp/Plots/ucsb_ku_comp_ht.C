void ucsb_ku_comp_ht()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec  2 13:34:25 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-625,1.128524,5625,8.386346);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *htucsb__3 = new TH1D("htucsb__3","ht",25,0,5000);
   htucsb__3->SetBinContent(6,2.415546e+07);
   htucsb__3->SetBinContent(7,8514899);
   htucsb__3->SetBinContent(8,3340529);
   htucsb__3->SetBinContent(9,1430977);
   htucsb__3->SetBinContent(10,652413);
   htucsb__3->SetBinContent(11,315994);
   htucsb__3->SetBinContent(12,158926);
   htucsb__3->SetBinContent(13,83542);
   htucsb__3->SetBinContent(14,44567);
   htucsb__3->SetBinContent(15,24956);
   htucsb__3->SetBinContent(16,14150);
   htucsb__3->SetBinContent(17,8197);
   htucsb__3->SetBinContent(18,4654);
   htucsb__3->SetBinContent(19,2824);
   htucsb__3->SetBinContent(20,1773);
   htucsb__3->SetBinContent(21,1046);
   htucsb__3->SetBinContent(22,631);
   htucsb__3->SetBinContent(23,419);
   htucsb__3->SetBinContent(24,243);
   htucsb__3->SetBinContent(25,143);
   htucsb__3->SetBinContent(26,286);
   htucsb__3->SetEntries(3.875663e+07);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("htucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries =   3.875663e+07");
   ptstats_LaTex = ptstats->AddText("Mean  =   1218");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  245.6");
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
   htku__4->SetBinContent(6,2.602007e+07);
   htku__4->SetBinContent(7,9236313);
   htku__4->SetBinContent(8,3634463);
   htku__4->SetBinContent(9,1563341);
   htku__4->SetBinContent(10,717806);
   htku__4->SetBinContent(11,348939);
   htku__4->SetBinContent(12,176628);
   htku__4->SetBinContent(13,93753);
   htku__4->SetBinContent(14,50314);
   htku__4->SetBinContent(15,28581);
   htku__4->SetBinContent(16,16368);
   htku__4->SetBinContent(17,9521);
   htku__4->SetBinContent(18,5501);
   htku__4->SetBinContent(19,3241);
   htku__4->SetBinContent(20,2103);
   htku__4->SetBinContent(21,1319);
   htku__4->SetBinContent(22,798);
   htku__4->SetBinContent(23,498);
   htku__4->SetBinContent(24,296);
   htku__4->SetBinContent(25,200);
   htku__4->SetBinContent(26,481);
   htku__4->SetEntries(4.191054e+07);

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
