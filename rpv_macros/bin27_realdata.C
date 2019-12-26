void bin27_realdata()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Nov 15 14:40:55 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",10,32,700,500);
   c1->Range(387.5,-0.06609374,1512.5,3.605143);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *mj12__1 = new TH1D("mj12__1","mj12",3,500,1400);
   mj12__1->SetBinContent(1,913);
   mj12__1->SetBinContent(2,73);
   mj12__1->SetBinContent(3,4);
   mj12__1->SetEntries(990);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("mj12");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 990    ");
   ptstats_LaTex = ptstats->AddText("Mean  =    619");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  112.4");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   mj12__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(mj12__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   mj12__1->SetLineColor(ci);
   mj12__1->GetXaxis()->SetLabelFont(42);
   mj12__1->GetXaxis()->SetLabelSize(0.035);
   mj12__1->GetXaxis()->SetTitleSize(0.035);
   mj12__1->GetXaxis()->SetTitleFont(42);
   mj12__1->GetYaxis()->SetLabelFont(42);
   mj12__1->GetYaxis()->SetLabelSize(0.035);
   mj12__1->GetYaxis()->SetTitleSize(0.035);
   mj12__1->GetYaxis()->SetTitleOffset(0);
   mj12__1->GetYaxis()->SetTitleFont(42);
   mj12__1->GetZaxis()->SetLabelFont(42);
   mj12__1->GetZaxis()->SetLabelSize(0.035);
   mj12__1->GetZaxis()->SetTitleSize(0.035);
   mj12__1->GetZaxis()->SetTitleFont(42);
   mj12__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4513181,0.9342405,0.5486819,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("mj12");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
