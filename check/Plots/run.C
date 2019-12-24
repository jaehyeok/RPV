void run()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:05:07 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(281311,-131.25,284331,1181.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__1 = new TH1D("hdat__1","run",100,281613,284029);
   hdat__1->SetBinContent(1,27);
   hdat__1->SetBinContent(4,452);
   hdat__1->SetBinContent(5,224);
   hdat__1->SetBinContent(8,721);
   hdat__1->SetBinContent(20,436);
   hdat__1->SetBinContent(47,705);
   hdat__1->SetBinContent(69,387);
   hdat__1->SetBinContent(73,387);
   hdat__1->SetBinContent(94,258);
   hdat__1->SetBinContent(95,247);
   hdat__1->SetBinContent(97,1000);
   hdat__1->SetBinContent(101,237);
   hdat__1->SetEntries(5081);
   hdat__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__1->SetLineColor(ci);
   hdat__1->GetXaxis()->SetLabelFont(42);
   hdat__1->GetXaxis()->SetLabelSize(0.035);
   hdat__1->GetXaxis()->SetTitleSize(0.035);
   hdat__1->GetXaxis()->SetTitleFont(42);
   hdat__1->GetYaxis()->SetLabelFont(42);
   hdat__1->GetYaxis()->SetLabelSize(0.035);
   hdat__1->GetYaxis()->SetTitleSize(0.035);
   hdat__1->GetYaxis()->SetTitleOffset(0);
   hdat__1->GetYaxis()->SetTitleFont(42);
   hdat__1->GetZaxis()->SetLabelFont(42);
   hdat__1->GetZaxis()->SetLabelSize(0.035);
   hdat__1->GetZaxis()->SetTitleSize(0.035);
   hdat__1->GetZaxis()->SetTitleFont(42);
   hdat__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4738373,0.94,0.5261627,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("run");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
