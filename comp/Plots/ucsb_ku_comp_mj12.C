void ucsb_ku_comp_mj12()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec  2 13:31:01 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-250,0.1515054,2250,8.178876);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *mj12ucsb__1 = new TH1D("mj12ucsb__1","mj12",20,0,2000);
   mj12ucsb__1->SetBinContent(1,3253157);
   mj12ucsb__1->SetBinContent(2,1.254845e+07);
   mj12ucsb__1->SetBinContent(3,1.125405e+07);
   mj12ucsb__1->SetBinContent(4,7008033);
   mj12ucsb__1->SetBinContent(5,3051189);
   mj12ucsb__1->SetBinContent(6,1080106);
   mj12ucsb__1->SetBinContent(7,355658);
   mj12ucsb__1->SetBinContent(8,123699);
   mj12ucsb__1->SetBinContent(9,47502);
   mj12ucsb__1->SetBinContent(10,19151);
   mj12ucsb__1->SetBinContent(11,8278);
   mj12ucsb__1->SetBinContent(12,3895);
   mj12ucsb__1->SetBinContent(13,1781);
   mj12ucsb__1->SetBinContent(14,769);
   mj12ucsb__1->SetBinContent(15,434);
   mj12ucsb__1->SetBinContent(16,217);
   mj12ucsb__1->SetBinContent(17,114);
   mj12ucsb__1->SetBinContent(18,67);
   mj12ucsb__1->SetBinContent(19,26);
   mj12ucsb__1->SetBinContent(20,18);
   mj12ucsb__1->SetBinContent(21,28);
   mj12ucsb__1->SetEntries(3.875663e+07);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("mj12ucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries =   3.875663e+07");
   ptstats_LaTex = ptstats->AddText("Mean  =  249.6");
   ptstats_LaTex = ptstats->AddText("Std Dev   =    128");
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
   mj12ku__2->SetBinContent(1,3514595);
   mj12ku__2->SetBinContent(2,1.350765e+07);
   mj12ku__2->SetBinContent(3,1.216798e+07);
   mj12ku__2->SetBinContent(4,7600705);
   mj12ku__2->SetBinContent(5,3322333);
   mj12ku__2->SetBinContent(6,1180624);
   mj12ku__2->SetBinContent(7,389530);
   mj12ku__2->SetBinContent(8,136053);
   mj12ku__2->SetBinContent(9,52258);
   mj12ku__2->SetBinContent(10,21313);
   mj12ku__2->SetBinContent(11,9195);
   mj12ku__2->SetBinContent(12,4317);
   mj12ku__2->SetBinContent(13,1966);
   mj12ku__2->SetBinContent(14,948);
   mj12ku__2->SetBinContent(15,469);
   mj12ku__2->SetBinContent(16,251);
   mj12ku__2->SetBinContent(17,125);
   mj12ku__2->SetBinContent(18,85);
   mj12ku__2->SetBinContent(19,33);
   mj12ku__2->SetBinContent(20,25);
   mj12ku__2->SetBinContent(21,76);
   mj12ku__2->SetEntries(4.191054e+07);

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
