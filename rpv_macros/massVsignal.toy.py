#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
import datetime
from optparse import OptionParser
import HiggsAnalysis.CombinedLimit.calculate_pulls as CP
import ROOT

nDivisions = 510 
xTitleOffset = 1.4
yTitleOffset = 1.5
TitleSize = 0.043
LabelSize = 0.06
LegendSize = 0.06
PadLeftMargin = 0.08
PadRightMargin = 0.05
PadTopMargin = 0.09
PadBottomMargin =0.08
nFont = 42

TitleSize=TitleSize/2
LabelSize=LabelSize/2
LegendSize=LegendSize/2

ROOT.gStyle.SetCanvasDefW(600);
ROOT.gStyle.SetCanvasDefH(600);
ROOT.gStyle.SetTextSize(LegendSize)
ROOT.gStyle.SetTitleFontSize(TitleSize)
ROOT.gStyle.SetPadLeftMargin(PadLeftMargin)
ROOT.gStyle.SetPadRightMargin(PadRightMargin)
ROOT.gStyle.SetPadTopMargin(PadTopMargin)
ROOT.gStyle.SetPadBottomMargin(PadBottomMargin)
ROOT.gStyle.SetNdivisions(nDivisions, "xyz")
ROOT.gStyle.SetTitleFont(nFont,"xyz")
ROOT.gStyle.SetLabelFont(nFont,"xyz")
ROOT.gStyle.SetTextFont(nFont)

r_arry = []
err_arry = []
r_min_arry = []
r_max_arry = []
for mass in list(range(1500,2300,100)):
	up      =[]
	down    =[]
	central =[]
	for seed in list(range(1,100)):
		fitresult = "out_injection/higgsCombine_M"+str(mass)+".FitDiagnostics.mH120."+str(seed)+".root"
		file = ROOT.TFile(fitresult)
		if file == None : raise RuntimeError, "Cannot open file %s" % fitresult
		limit_t = file.Get("limit"); 
		if limit_t == None or limit_t.ClassName() != "TTree" : raise RuntimeError, "File does not contain TTree output of the signal fit 'limit'"
		limit_t.GetEntry(2)
		down.append(limit_t.limit)
		limit_t.GetEntry(3)
		up.append(limit_t.limit)
		limit_t.GetEntry(4)
		central.append(limit_t.limit)
	up = sorted(up)
	down = sorted(down)
	central = sorted(central)
	med_up = up[50]
	med_down = down[50]
	med_cent = central[50]
	r_arry.append(med_cent)
	r_min_arry.append(med_down)
	r_max_arry.append(med_up)
hist_mvsr = ROOT.TH1F("GvsS", "Gluino mass vs Signal Strength", 8, 1450, 2250)
for i in range(0,8) : 
	hist_mvsr.SetBinContent(i+1,(r_arry[i]-1)/r_max_arry[i])
	hist_mvsr.SetBinError(i+1,1)
#err_mvsr = ROOT.TGraphAsymmErrors(hist_mvsr)
#for i in range(0,8) : 
#	err_mvsr.SetPointError(i,0,0,r_arry[i]-r_min_arry[i],r_max_arry[i]-r_arry[i])

hist_mvsr.SetTitleOffset(xTitleOffset,"x");
hist_mvsr.SetTitleOffset(yTitleOffset,"y");
hist_mvsr.SetTitleSize(TitleSize,"xyz")
hist_mvsr.SetLabelSize(LabelSize,"xyz")
c = ROOT.TCanvas()
c.SetGrid()
hist_mvsr.SetTitle("");
hist_mvsr.GetYaxis().SetRangeUser(-2, 2)
hist_mvsr.GetXaxis().SetRangeUser(1450,2250)
hist_mvsr.GetXaxis().SetTitle("m_{#tilde{g}}")
hist_mvsr.GetYaxis().SetTitle("#mu")
hist_mvsr.SetTitleSize(TitleSize)
hist_mvsr.SetStats(0)
hist_mvsr.SetMarkerStyle(42)
hist_mvsr.SetMarkerSize(0.2)
hist_mvsr.SetLineColor(ROOT.kRed)
hist_mvsr.SetMarkerColor(ROOT.kRed)
hist_mvsr.Draw()
#err_mvsr.SetMarkerStyle(42)
#err_mvsr.SetMarkerSize(0.5)
#err_mvsr.SetMarkerColor(ROOT.kRed)
#err_mvsr.SetLineColor(ROOT.kRed)
#err_mvsr.Draw("same E2 P")
cmslabel = "#font[62]{CMS} #scale[0.8]{#font[52]{Work In Progress}}"
lumilabel = "137fb^{-1} (13 TeV)"
label = ROOT.TLatex()
label.SetNDC(ROOT.kTRUE)
label.SetTextSize(0.03)
label.SetTextAlign(11)
label.DrawLatex(PadLeftMargin,1-PadTopMargin+0.02,cmslabel);
label.SetTextAlign(31)
label.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,lumilabel);
#b = ROOT.TBox(PadLeftMargin, (PadTopMargin+PadBottomMargin)/2-0.5,1-PadRightMargin, (PadTopMargin+PadBottomMargin)/2+0.5)
b = ROOT.TBox(0,-1,9,1)
b.SetFillStyle(3003)
b.SetFillColor(ROOT.kBlue)
b.Draw("same")
hist_mvsr.Draw("same EP")
c.Print("mass_vs_r_result.pdf")
