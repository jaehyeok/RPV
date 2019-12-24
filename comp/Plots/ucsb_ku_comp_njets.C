void ucsb_ku_comp_njets()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec  2 13:39:06 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-3,-1.244656,22,8.191602);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *njetsucsb__5 = new TH1D("njetsucsb__5","njets",20,-0.5,19.5);
   njetsucsb__5->SetBinContent(2,1981);
   njetsucsb__5->SetBinContent(3,3402777);
   njetsucsb__5->SetBinContent(4,7584135);
   njetsucsb__5->SetBinContent(5,9341730);
   njetsucsb__5->SetBinContent(6,8051740);
   njetsucsb__5->SetBinContent(7,5355299);
   njetsucsb__5->SetBinContent(8,2905517);
   njetsucsb__5->SetBinContent(9,1325625);
   njetsucsb__5->SetBinContent(10,524580);
   njetsucsb__5->SetBinContent(11,183210);
   njetsucsb__5->SetBinContent(12,57589);
   njetsucsb__5->SetBinContent(13,16591);
   njetsucsb__5->SetBinContent(14,4371);
   njetsucsb__5->SetBinContent(15,1108);
   njetsucsb__5->SetBinContent(16,296);
   njetsucsb__5->SetBinContent(17,58);
   njetsucsb__5->SetBinContent(18,16);
   njetsucsb__5->SetBinContent(19,2);
   njetsucsb__5->SetBinContent(20,1);
   njetsucsb__5->SetBinContent(21,1);
   njetsucsb__5->SetEntries(3.875663e+07);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("njetsucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries =   3.875663e+07");
   ptstats_LaTex = ptstats->AddText("Mean  =  4.586");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  1.676");
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
   njetsku__6->SetBinContent(2,650);
   njetsku__6->SetBinContent(3,3664976);
   njetsku__6->SetBinContent(4,8156030);
   njetsku__6->SetBinContent(5,1.006534e+07);
   njetsku__6->SetBinContent(6,8700464);
   njetsku__6->SetBinContent(7,5816452);
   njetsku__6->SetBinContent(8,3170815);
   njetsku__6->SetBinContent(9,1459578);
   njetsku__6->SetBinContent(10,580659);
   njetsku__6->SetBinContent(11,205255);
   njetsku__6->SetBinContent(12,64494);
   njetsku__6->SetBinContent(13,19033);
   njetsku__6->SetBinContent(14,5052);
   njetsku__6->SetBinContent(15,1311);
   njetsku__6->SetBinContent(16,336);
   njetsku__6->SetBinContent(17,69);
   njetsku__6->SetBinContent(18,17);
   njetsku__6->SetBinContent(19,4);
   njetsku__6->SetBinContent(20,2);
   njetsku__6->SetBinContent(21,2);
   njetsku__6->SetEntries(4.191054e+07);

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
