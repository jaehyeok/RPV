void ucsb_ku_comp_nb()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Dec  2 14:15:50 2019) by ROOT version 6.12/07
   TCanvas *c = new TCanvas("c", "c",0,23,800,800);
   c->Range(-1.75,-1.307175,10.75,8.754272);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *nbucsb__7 = new TH1D("nbucsb__7","nb",10,-0.5,9.5);
   nbucsb__7->SetBinContent(1,2.955144e+07);
   nbucsb__7->SetBinContent(2,7699998);
   nbucsb__7->SetBinContent(3,1331027);
   nbucsb__7->SetBinContent(4,155816);
   nbucsb__7->SetBinContent(5,16143);
   nbucsb__7->SetBinContent(6,1847);
   nbucsb__7->SetBinContent(7,287);
   nbucsb__7->SetBinContent(8,57);
   nbucsb__7->SetBinContent(9,9);
   nbucsb__7->SetBinContent(10,1);
   nbucsb__7->SetEntries(3.875663e+07);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("nbucsb");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries =   3.875663e+07");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.2814");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.5489");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   nbucsb__7->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(nbucsb__7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   nbucsb__7->SetLineColor(ci);
   nbucsb__7->SetLineWidth(2);
   nbucsb__7->GetXaxis()->SetLabelFont(42);
   nbucsb__7->GetXaxis()->SetLabelSize(0.035);
   nbucsb__7->GetXaxis()->SetTitleSize(0.035);
   nbucsb__7->GetXaxis()->SetTitleFont(42);
   nbucsb__7->GetYaxis()->SetLabelFont(42);
   nbucsb__7->GetYaxis()->SetLabelSize(0.035);
   nbucsb__7->GetYaxis()->SetTitleSize(0.035);
   nbucsb__7->GetYaxis()->SetTitleOffset(0);
   nbucsb__7->GetYaxis()->SetTitleFont(42);
   nbucsb__7->GetZaxis()->SetLabelFont(42);
   nbucsb__7->GetZaxis()->SetLabelSize(0.035);
   nbucsb__7->GetZaxis()->SetTitleSize(0.035);
   nbucsb__7->GetZaxis()->SetTitleFont(42);
   nbucsb__7->Draw("");
   
   TH1D *nbku__8 = new TH1D("nbku__8","",10,-0.5,9.5);
   nbku__8->SetBinContent(1,3.282049e+07);
   nbku__8->SetBinContent(2,7655454);
   nbku__8->SetBinContent(3,1277590);
   nbku__8->SetBinContent(4,140967);
   nbku__8->SetBinContent(5,14173);
   nbku__8->SetBinContent(6,1565);
   nbku__8->SetBinContent(7,235);
   nbku__8->SetBinContent(8,54);
   nbku__8->SetBinContent(9,10);
   nbku__8->SetBinContent(10,2);
   nbku__8->SetEntries(4.191054e+07);

   ci = TColor::GetColor("#ff0000");
   nbku__8->SetLineColor(ci);
   nbku__8->SetLineWidth(2);
   nbku__8->GetXaxis()->SetLabelFont(42);
   nbku__8->GetXaxis()->SetLabelSize(0.035);
   nbku__8->GetXaxis()->SetTitleSize(0.035);
   nbku__8->GetXaxis()->SetTitleFont(42);
   nbku__8->GetYaxis()->SetLabelFont(42);
   nbku__8->GetYaxis()->SetLabelSize(0.035);
   nbku__8->GetYaxis()->SetTitleSize(0.035);
   nbku__8->GetYaxis()->SetTitleOffset(0);
   nbku__8->GetYaxis()->SetTitleFont(42);
   nbku__8->GetZaxis()->SetLabelFont(42);
   nbku__8->GetZaxis()->SetLabelSize(0.035);
   nbku__8->GetZaxis()->SetTitleSize(0.035);
   nbku__8->GetZaxis()->SetTitleFont(42);
   nbku__8->Draw("same hist");
   
   TPaveText *pt = new TPaveText(0.4599248,0.94,0.5400752,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("nb");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
