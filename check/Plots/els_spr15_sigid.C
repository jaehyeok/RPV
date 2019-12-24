void els_spr15_sigid()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:07:52 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-2.5,-768.3376,2.5,6915.038);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__29 = new TH1D("hdat__29","els_spr15_sigid",4,-2,2);
   hdat__29->SetBinContent(3,5854);
   hdat__29->SetEntries(5854);
   hdat__29->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__29->SetLineColor(ci);
   hdat__29->GetXaxis()->SetRange(1,100);
   hdat__29->GetXaxis()->SetLabelFont(42);
   hdat__29->GetXaxis()->SetLabelSize(0.035);
   hdat__29->GetXaxis()->SetTitleSize(0.035);
   hdat__29->GetXaxis()->SetTitleFont(42);
   hdat__29->GetYaxis()->SetLabelFont(42);
   hdat__29->GetYaxis()->SetLabelSize(0.035);
   hdat__29->GetYaxis()->SetTitleSize(0.035);
   hdat__29->GetYaxis()->SetTitleOffset(0);
   hdat__29->GetYaxis()->SetTitleFont(42);
   hdat__29->GetZaxis()->SetLabelFont(42);
   hdat__29->GetZaxis()->SetLabelSize(0.035);
   hdat__29->GetZaxis()->SetTitleSize(0.035);
   hdat__29->GetZaxis()->SetTitleFont(42);
   hdat__29->Draw("");
   
   TPaveText *pt = new TPaveText(0.4123149,0.9345349,0.5876851,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("els_spr15_sigid");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
