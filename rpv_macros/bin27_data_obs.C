void bin27_data_obs()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Nov 15 14:21:48 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",10,32,700,500);
   c1->Range(387.5,0.3245964,1512.5,3.380824);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *data_obs__1 = new TH1F("data_obs__1","data_obs",3,500,1400);
   data_obs__1->SetBinContent(1,603);
   data_obs__1->SetBinContent(2,74);
   data_obs__1->SetBinContent(3,12);
   data_obs__1->SetBinError(1,24.55606);
   data_obs__1->SetBinError(2,8.602325);
   data_obs__1->SetBinError(3,3.464102);
   data_obs__1->SetEntries(707);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("data_obs");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 707    ");
   ptstats_LaTex = ptstats->AddText("Mean  =  651.1");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  141.8");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   data_obs__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(data_obs__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   data_obs__1->SetLineColor(ci);
   data_obs__1->GetXaxis()->SetLabelFont(42);
   data_obs__1->GetXaxis()->SetLabelSize(0.035);
   data_obs__1->GetXaxis()->SetTitleSize(0.035);
   data_obs__1->GetXaxis()->SetTitleFont(42);
   data_obs__1->GetYaxis()->SetLabelFont(42);
   data_obs__1->GetYaxis()->SetLabelSize(0.035);
   data_obs__1->GetYaxis()->SetTitleSize(0.035);
   data_obs__1->GetYaxis()->SetTitleOffset(0);
   data_obs__1->GetYaxis()->SetTitleFont(42);
   data_obs__1->GetZaxis()->SetLabelFont(42);
   data_obs__1->GetZaxis()->SetLabelSize(0.035);
   data_obs__1->GetZaxis()->SetTitleSize(0.035);
   data_obs__1->GetZaxis()->SetTitleFont(42);
   data_obs__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4147851,0.9367722,0.5852149,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("data_obs");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
