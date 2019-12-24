void ucsb_ku_comp_cuts_mj12()
{
//=========Macro generated from canvas: c/c
//=========  (Fri Dec 13 17:31:22 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-250,-0.7579324,2250,3.811092);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *mj12ucsb__1 = new TH1D("mj12ucsb__1","mj12",20,0,2000);
   mj12ucsb__1->SetBinContent(6,1193);
   mj12ucsb__1->SetBinContent(7,580);
   mj12ucsb__1->SetBinContent(8,279);
   mj12ucsb__1->SetBinContent(9,127);
   mj12ucsb__1->SetBinContent(10,56);
   mj12ucsb__1->SetBinContent(11,26);
   mj12ucsb__1->SetBinContent(12,13);
   mj12ucsb__1->SetBinContent(13,4);
   mj12ucsb__1->SetBinContent(14,5);
   mj12ucsb__1->SetBinContent(15,4);
   mj12ucsb__1->SetBinContent(16,2);
   mj12ucsb__1->SetBinContent(17,1);
   mj12ucsb__1->SetBinContent(18,2);
   mj12ucsb__1->SetBinContent(21,1);
   mj12ucsb__1->SetEntries(2293);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("mj12ucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 2293   ");
   ptstats_LaTex = ptstats->AddText("Mean  =  636.1");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  140.3");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   mj12ucsb__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(mj12ucsb__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   mj12ucsb__1->SetLineColor(ci);
   mj12ucsb__1->SetLineWidth(2);
   mj12ucsb__1->GetXaxis()->SetLabelFont(42);
   mj12ucsb__1->GetXaxis()->SetLabelSize(0.035);
   mj12ucsb__1->GetXaxis()->SetTitleSize(0.035);
   mj12ucsb__1->GetXaxis()->SetTitleFont(42);
   mj12ucsb__1->GetYaxis()->SetLabelFont(42);
   mj12ucsb__1->GetYaxis()->SetLabelSize(0.035);
   mj12ucsb__1->GetYaxis()->SetTitleSize(0.035);
   mj12ucsb__1->GetYaxis()->SetTitleOffset(0);
   mj12ucsb__1->GetYaxis()->SetTitleFont(42);
   mj12ucsb__1->GetZaxis()->SetLabelFont(42);
   mj12ucsb__1->GetZaxis()->SetLabelSize(0.035);
   mj12ucsb__1->GetZaxis()->SetTitleSize(0.035);
   mj12ucsb__1->GetZaxis()->SetTitleFont(42);
   mj12ucsb__1->Draw("");
   
   TH1D *mj12ku__2 = new TH1D("mj12ku__2","",20,0,2000);
   mj12ku__2->SetBinContent(6,1049);
   mj12ku__2->SetBinContent(7,553);
   mj12ku__2->SetBinContent(8,223);
   mj12ku__2->SetBinContent(9,102);
   mj12ku__2->SetBinContent(10,46);
   mj12ku__2->SetBinContent(11,25);
   mj12ku__2->SetBinContent(12,12);
   mj12ku__2->SetBinContent(13,6);
   mj12ku__2->SetBinContent(14,4);
   mj12ku__2->SetBinContent(15,2);
   mj12ku__2->SetBinContent(16,1);
   mj12ku__2->SetBinContent(21,1);
   mj12ku__2->SetEntries(2024);

   ci = TColor::GetColor("#ff0000");
   mj12ku__2->SetLineColor(ci);
   mj12ku__2->SetLineWidth(2);
   mj12ku__2->GetXaxis()->SetLabelFont(42);
   mj12ku__2->GetXaxis()->SetLabelSize(0.035);
   mj12ku__2->GetXaxis()->SetTitleSize(0.035);
   mj12ku__2->GetXaxis()->SetTitleFont(42);
   mj12ku__2->GetYaxis()->SetLabelFont(42);
   mj12ku__2->GetYaxis()->SetLabelSize(0.035);
   mj12ku__2->GetYaxis()->SetTitleSize(0.035);
   mj12ku__2->GetYaxis()->SetTitleOffset(0);
   mj12ku__2->GetYaxis()->SetTitleFont(42);
   mj12ku__2->GetZaxis()->SetLabelFont(42);
   mj12ku__2->GetZaxis()->SetLabelSize(0.035);
   mj12ku__2->GetZaxis()->SetTitleSize(0.035);
   mj12ku__2->GetZaxis()->SetTitleFont(42);
   mj12ku__2->Draw("same hist");
   
   TPaveText *pt = new TPaveText(0.433609,0.9345349,0.566391,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("mj12");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
