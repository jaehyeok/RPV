void met_phi()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:06:35 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-3.926941,639.2806,3.926453,1055.474);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__6 = new TH1D("hdat__6","met_phi",6,-3.141602,3.141113);
   hdat__6->SetBinContent(1,765);
   hdat__6->SetBinContent(2,696);
   hdat__6->SetBinContent(3,789);
   hdat__6->SetBinContent(4,903);
   hdat__6->SetBinContent(5,998);
   hdat__6->SetBinContent(6,929);
   hdat__6->SetBinContent(7,1);
   hdat__6->SetEntries(5081);
   hdat__6->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__6->SetLineColor(ci);
   hdat__6->GetXaxis()->SetLabelFont(42);
   hdat__6->GetXaxis()->SetLabelSize(0.035);
   hdat__6->GetXaxis()->SetTitleSize(0.035);
   hdat__6->GetXaxis()->SetTitleFont(42);
   hdat__6->GetYaxis()->SetLabelFont(42);
   hdat__6->GetYaxis()->SetLabelSize(0.035);
   hdat__6->GetYaxis()->SetTitleSize(0.035);
   hdat__6->GetYaxis()->SetTitleOffset(0);
   hdat__6->GetYaxis()->SetTitleFont(42);
   hdat__6->GetZaxis()->SetLabelFont(42);
   hdat__6->GetZaxis()->SetLabelSize(0.035);
   hdat__6->GetZaxis()->SetTitleSize(0.035);
   hdat__6->GetZaxis()->SetTitleFont(42);
   hdat__6->Draw("");
   
   TPaveText *pt = new TPaveText(0.4506361,0.9345349,0.5493639,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("met_phi");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
