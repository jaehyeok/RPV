void w_pu()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:53 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-0.5,-1333.763,4.5,12003.86);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__11 = new TH1D("hdat__11","w_pu",1,0,4);
   hdat__11->SetBinContent(1,5081);
   hdat__11->SetEntries(5081);
   hdat__11->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__11->SetLineColor(ci);
   hdat__11->GetXaxis()->SetRange(1,1);
   hdat__11->GetXaxis()->SetLabelFont(42);
   hdat__11->GetXaxis()->SetLabelSize(0.035);
   hdat__11->GetXaxis()->SetTitleSize(0.035);
   hdat__11->GetXaxis()->SetTitleFont(42);
   hdat__11->GetYaxis()->SetLabelFont(42);
   hdat__11->GetYaxis()->SetLabelSize(0.035);
   hdat__11->GetYaxis()->SetTitleSize(0.035);
   hdat__11->GetYaxis()->SetTitleOffset(0);
   hdat__11->GetYaxis()->SetTitleFont(42);
   hdat__11->GetZaxis()->SetLabelFont(42);
   hdat__11->GetZaxis()->SetLabelSize(0.035);
   hdat__11->GetZaxis()->SetTitleSize(0.035);
   hdat__11->GetZaxis()->SetTitleFont(42);
   hdat__11->Draw("");
   
   TPaveText *pt = new TPaveText(0.4639312,0.94,0.5360688,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("w_pu");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
