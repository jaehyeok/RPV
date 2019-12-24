void pass()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:57 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.125,-7.087501,1.125,63.7875);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__50 = new TH1D("hdat__50","pass",1,0,1);
   hdat__50->SetBinContent(1,27);
   hdat__50->SetBinContent(2,5054);
   hdat__50->SetEntries(5081);
   hdat__50->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__50->SetLineColor(ci);
   hdat__50->GetXaxis()->SetLabelFont(42);
   hdat__50->GetXaxis()->SetLabelSize(0.035);
   hdat__50->GetXaxis()->SetTitleSize(0.035);
   hdat__50->GetXaxis()->SetTitleFont(42);
   hdat__50->GetYaxis()->SetLabelFont(42);
   hdat__50->GetYaxis()->SetLabelSize(0.035);
   hdat__50->GetYaxis()->SetTitleSize(0.035);
   hdat__50->GetYaxis()->SetTitleOffset(0);
   hdat__50->GetYaxis()->SetTitleFont(42);
   hdat__50->GetZaxis()->SetLabelFont(42);
   hdat__50->GetZaxis()->SetLabelSize(0.035);
   hdat__50->GetZaxis()->SetTitleSize(0.035);
   hdat__50->GetZaxis()->SetTitleFont(42);
   hdat__50->Draw("");
   
   TPaveText *pt = new TPaveText(0.4665381,0.94,0.5334619,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("pass");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
