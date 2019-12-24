void leps_pdgid()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:11 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-18.75,-1.96875,18.75,17.71875);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__16 = new TH1D("hdat__16","leps_pdgid",30,-15,15);
   hdat__16->SetBinContent(3,13);
   hdat__16->SetBinContent(5,15);
   hdat__16->SetBinContent(27,11);
   hdat__16->SetBinContent(29,10);
   hdat__16->SetEntries(49);
   hdat__16->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__16->SetLineColor(ci);
   hdat__16->GetXaxis()->SetRange(1,100);
   hdat__16->GetXaxis()->SetLabelFont(42);
   hdat__16->GetXaxis()->SetLabelSize(0.035);
   hdat__16->GetXaxis()->SetTitleSize(0.035);
   hdat__16->GetXaxis()->SetTitleFont(42);
   hdat__16->GetYaxis()->SetLabelFont(42);
   hdat__16->GetYaxis()->SetLabelSize(0.035);
   hdat__16->GetYaxis()->SetTitleSize(0.035);
   hdat__16->GetYaxis()->SetTitleOffset(0);
   hdat__16->GetYaxis()->SetTitleFont(42);
   hdat__16->GetZaxis()->SetLabelFont(42);
   hdat__16->GetZaxis()->SetLabelSize(0.035);
   hdat__16->GetZaxis()->SetTitleSize(0.035);
   hdat__16->GetZaxis()->SetTitleFont(42);
   hdat__16->Draw("");
   
   TPaveText *pt = new TPaveText(0.4355162,0.9345349,0.5644838,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("leps_pdgid");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
