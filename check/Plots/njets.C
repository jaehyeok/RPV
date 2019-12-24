void njets()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:00 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(2.5,-149.7563,17.5,1347.806);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__32 = new TH1D("hdat__32","njets",12,4,16);
   hdat__32->SetBinContent(1,496);
   hdat__32->SetBinContent(2,929);
   hdat__32->SetBinContent(3,1141);
   hdat__32->SetBinContent(4,1020);
   hdat__32->SetBinContent(5,718);
   hdat__32->SetBinContent(6,419);
   hdat__32->SetBinContent(7,203);
   hdat__32->SetBinContent(8,98);
   hdat__32->SetBinContent(9,38);
   hdat__32->SetBinContent(10,10);
   hdat__32->SetBinContent(11,6);
   hdat__32->SetBinContent(12,1);
   hdat__32->SetBinContent(13,2);
   hdat__32->SetEntries(5081);
   hdat__32->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__32->SetLineColor(ci);
   hdat__32->GetXaxis()->SetLabelFont(42);
   hdat__32->GetXaxis()->SetLabelSize(0.035);
   hdat__32->GetXaxis()->SetTitleSize(0.035);
   hdat__32->GetXaxis()->SetTitleFont(42);
   hdat__32->GetYaxis()->SetLabelFont(42);
   hdat__32->GetYaxis()->SetLabelSize(0.035);
   hdat__32->GetYaxis()->SetTitleSize(0.035);
   hdat__32->GetYaxis()->SetTitleOffset(0);
   hdat__32->GetYaxis()->SetTitleFont(42);
   hdat__32->GetZaxis()->SetLabelFont(42);
   hdat__32->GetZaxis()->SetLabelSize(0.035);
   hdat__32->GetZaxis()->SetTitleSize(0.035);
   hdat__32->GetZaxis()->SetTitleFont(42);
   hdat__32->Draw("");
   
   TPaveText *pt = new TPaveText(0.4660167,0.9345349,0.5339833,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("njets");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
