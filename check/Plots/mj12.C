void mj12()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:40 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(373.0371,-401.7563,1642.822,3615.806);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__44 = new TH1D("hdat__44","mj12",10,500.0156,1515.844);
   hdat__44->SetBinContent(1,3061);
   hdat__44->SetBinContent(2,1231);
   hdat__44->SetBinContent(3,471);
   hdat__44->SetBinContent(4,183);
   hdat__44->SetBinContent(5,68);
   hdat__44->SetBinContent(6,36);
   hdat__44->SetBinContent(7,19);
   hdat__44->SetBinContent(8,6);
   hdat__44->SetBinContent(9,3);
   hdat__44->SetBinContent(10,2);
   hdat__44->SetBinContent(11,1);
   hdat__44->SetEntries(5081);
   hdat__44->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__44->SetLineColor(ci);
   hdat__44->GetXaxis()->SetLabelFont(42);
   hdat__44->GetXaxis()->SetLabelSize(0.035);
   hdat__44->GetXaxis()->SetTitleSize(0.035);
   hdat__44->GetXaxis()->SetTitleFont(42);
   hdat__44->GetYaxis()->SetLabelFont(42);
   hdat__44->GetYaxis()->SetLabelSize(0.035);
   hdat__44->GetYaxis()->SetTitleSize(0.035);
   hdat__44->GetYaxis()->SetTitleOffset(0);
   hdat__44->GetYaxis()->SetTitleFont(42);
   hdat__44->GetZaxis()->SetLabelFont(42);
   hdat__44->GetZaxis()->SetLabelSize(0.035);
   hdat__44->GetZaxis()->SetTitleSize(0.035);
   hdat__44->GetZaxis()->SetTitleFont(42);
   hdat__44->Draw("");
   
   TPaveText *pt = new TPaveText(0.4665381,0.9345349,0.5334619,0.995,"blNDC");
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
