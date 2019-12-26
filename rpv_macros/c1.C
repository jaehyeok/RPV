void c1()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Nov 20 13:14:07 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",10,32,700,500);
   c1->Range(387.5,-0.2067745,1512.5,1.86097);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *qcd__1 = new TH1F("qcd__1","qcd",3,500,1400);
   qcd__1->SetBinContent(2,0.7877122);
   qcd__1->SetBinError(2,0.7877122);
   qcd__1->SetEntries(1);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("qcd");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 1      ");
   ptstats_LaTex = ptstats->AddText("Mean  =  829.4");
   ptstats_LaTex = ptstats->AddText("Std Dev   =      0");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   qcd__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(qcd__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   qcd__1->SetLineColor(ci);
   qcd__1->GetXaxis()->SetLabelFont(42);
   qcd__1->GetXaxis()->SetLabelSize(0.035);
   qcd__1->GetXaxis()->SetTitleSize(0.035);
   qcd__1->GetXaxis()->SetTitleFont(42);
   qcd__1->GetYaxis()->SetLabelFont(42);
   qcd__1->GetYaxis()->SetLabelSize(0.035);
   qcd__1->GetYaxis()->SetTitleSize(0.035);
   qcd__1->GetYaxis()->SetTitleOffset(0);
   qcd__1->GetYaxis()->SetTitleFont(42);
   qcd__1->GetZaxis()->SetLabelFont(42);
   qcd__1->GetZaxis()->SetLabelSize(0.035);
   qcd__1->GetZaxis()->SetTitleSize(0.035);
   qcd__1->GetZaxis()->SetTitleFont(42);
   qcd__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.459914,0.9342405,0.540086,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("qcd");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
