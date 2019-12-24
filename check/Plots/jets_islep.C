void jets_islep()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:34 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.25,-6958.088,2.25,62622.79);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__42 = new TH1D("hdat__42","jets_islep",2,0,2);
   hdat__42->SetBinContent(1,53014);
   hdat__42->SetBinContent(2,49);
   hdat__42->SetEntries(53063);
   hdat__42->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__42->SetLineColor(ci);
   hdat__42->GetXaxis()->SetRange(1,100);
   hdat__42->GetXaxis()->SetLabelFont(42);
   hdat__42->GetXaxis()->SetLabelSize(0.035);
   hdat__42->GetXaxis()->SetTitleSize(0.035);
   hdat__42->GetXaxis()->SetTitleFont(42);
   hdat__42->GetYaxis()->SetLabelFont(42);
   hdat__42->GetYaxis()->SetLabelSize(0.035);
   hdat__42->GetYaxis()->SetTitleSize(0.035);
   hdat__42->GetYaxis()->SetTitleOffset(0);
   hdat__42->GetYaxis()->SetTitleFont(42);
   hdat__42->GetZaxis()->SetLabelFont(42);
   hdat__42->GetZaxis()->SetLabelSize(0.035);
   hdat__42->GetZaxis()->SetTitleSize(0.035);
   hdat__42->GetZaxis()->SetTitleFont(42);
   hdat__42->Draw("");
   
   TPaveText *pt = new TPaveText(0.4428154,0.9345349,0.5571846,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_islep");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
