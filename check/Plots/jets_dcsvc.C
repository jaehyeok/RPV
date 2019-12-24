void jets_dcsvc()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 24 15:08:27 2019) by ROOT version 6.12/07
   TCanvas *c1 = new TCanvas("c1", "c1",0,23,1920,800);
   c1->SetHighLightColor(2);
   c1->Range(-1.3725,-1295.438,0.9525,11658.94);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *hdat__40 = new TH1D("hdat__40","jets_dcsvc",100,-1.14,0.72);
   hdat__40->SetBinContent(8,9870);
   hdat__40->SetBinContent(62,460);
   hdat__40->SetBinContent(63,241);
   hdat__40->SetBinContent(64,203);
   hdat__40->SetBinContent(65,768);
   hdat__40->SetBinContent(66,3219);
   hdat__40->SetBinContent(67,5940);
   hdat__40->SetBinContent(68,7171);
   hdat__40->SetBinContent(69,7327);
   hdat__40->SetBinContent(70,5494);
   hdat__40->SetBinContent(71,3587);
   hdat__40->SetBinContent(72,2525);
   hdat__40->SetBinContent(73,1685);
   hdat__40->SetBinContent(74,1234);
   hdat__40->SetBinContent(75,832);
   hdat__40->SetBinContent(76,590);
   hdat__40->SetBinContent(77,424);
   hdat__40->SetBinContent(78,354);
   hdat__40->SetBinContent(79,241);
   hdat__40->SetBinContent(80,164);
   hdat__40->SetBinContent(81,142);
   hdat__40->SetBinContent(82,113);
   hdat__40->SetBinContent(83,73);
   hdat__40->SetBinContent(84,68);
   hdat__40->SetBinContent(85,58);
   hdat__40->SetBinContent(86,48);
   hdat__40->SetBinContent(87,31);
   hdat__40->SetBinContent(88,25);
   hdat__40->SetBinContent(89,23);
   hdat__40->SetBinContent(90,19);
   hdat__40->SetBinContent(91,21);
   hdat__40->SetBinContent(92,13);
   hdat__40->SetBinContent(93,12);
   hdat__40->SetBinContent(94,12);
   hdat__40->SetBinContent(95,13);
   hdat__40->SetBinContent(96,12);
   hdat__40->SetBinContent(97,8);
   hdat__40->SetBinContent(98,9);
   hdat__40->SetBinContent(99,9);
   hdat__40->SetBinContent(100,7);
   hdat__40->SetBinContent(101,18);
   hdat__40->SetEntries(53063);
   hdat__40->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hdat__40->SetLineColor(ci);
   hdat__40->GetXaxis()->SetRange(1,100);
   hdat__40->GetXaxis()->SetLabelFont(42);
   hdat__40->GetXaxis()->SetLabelSize(0.035);
   hdat__40->GetXaxis()->SetTitleSize(0.035);
   hdat__40->GetXaxis()->SetTitleFont(42);
   hdat__40->GetYaxis()->SetLabelFont(42);
   hdat__40->GetYaxis()->SetLabelSize(0.035);
   hdat__40->GetYaxis()->SetTitleSize(0.035);
   hdat__40->GetYaxis()->SetTitleOffset(0);
   hdat__40->GetYaxis()->SetTitleFont(42);
   hdat__40->GetZaxis()->SetLabelFont(42);
   hdat__40->GetZaxis()->SetLabelSize(0.035);
   hdat__40->GetZaxis()->SetTitleSize(0.035);
   hdat__40->GetZaxis()->SetTitleFont(42);
   hdat__40->Draw("");
   
   TPaveText *pt = new TPaveText(0.4368196,0.9345349,0.5631804,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("jets_dcsvc");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
