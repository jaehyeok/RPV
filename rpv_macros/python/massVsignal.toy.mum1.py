#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
import datetime
from optparse import OptionParser
import HiggsAnalysis.CombinedLimit.calculate_pulls as CP
import ROOT
import numpy as np

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
r_val_rms  =[]

TH1_1500 = ROOT.TH1F("1500 GeV", "1500 GeV",150,-5.5,9.5)
TH1_1800 = ROOT.TH1F("1800 GeV", "1800 GeV",150,-5.5,9.5)
TH1_2100 = ROOT.TH1F("2100 GeV", "2100 GeV",150,-5.5,9.5)

list_TH1 = []
for mass in list(range(1500,2300,100)):
    TH1_mass = ROOT.TH1F("h_{0}".format(mass), "h_{0}".format(mass), 150, -5.5, 9.5)
    list_TH1.append(TH1_mass)

mass_idx = -1

for mass in list(range(1500,2300,100)):

    mass_idx+=1
    central      =[]
    list_error_r =[]
    list_val_r   =[]
    n_entries=1000
    for seed in list(range(1,1001)):
        if seed%100==0 : print(str(mass)+" GeV, "+str(seed)+"th loop")
        fitresult = "out_injection_201678_full_240102/higgsCombine_M"+str(mass)+"_"+str(seed)+".FitDiagnostics.mH120."+str(seed)+".root"
        file = ROOT.TFile(fitresult)
        if file == None : raise RuntimeError, "Cannot open file %s" % fitresult
        limit_t = file.Get("limit"); 
        if limit_t == None or limit_t.ClassName() != "TTree" : raise RuntimeError, "File does not contain TTree output of the signal fit 'limit'"
        limit_t.GetEntry(4)
        value_r = limit_t.limit
        #error_r = limit_t.limitErr
        limit_t.GetEntry(3)
        error_r = limit_t.limit - value_r
        if limit_t.limit==0 : 
        #if error_r==0 : 
            print(seed)
            n_entries-=1
            continue
        list_val_r.append(value_r)
        list_error_r.append(error_r)
        central.append((value_r-1)/error_r)
        if mass==1500 : TH1_1500.Fill((value_r-1)/error_r)
        elif mass==1800 : TH1_1800.Fill((value_r-1)/error_r)
        elif mass==2100 : TH1_2100.Fill((value_r-1)/error_r)
        list_TH1[mass_idx].Fill((value_r-1)/error_r)
    central = sorted(central)
    list_error_r = sorted(list_error_r)
    print("total entries: "+str(n_entries))
    list_val_r = sorted(list_val_r)
    med_cent = central[int(n_entries/2)] 
    #r_arry.append(med_cent)
    #r_max_arry.append(rms)
    r_arry.append(list_TH1[mass_idx].GetMean())
    r_max_arry.append(list_TH1[mass_idx].GetStdDev())
    r_val_rms.append(val_rms)
    #print(mass)
    #print(list_error_r)
    #print(list_val_r)
    #print(central)
#print("M1500 Mean: "+str(TH1_1500.GetMean()))
#print("M1500 Std : "+str(TH1_1500.GetStdDev()))
#print("M1800 Mean: "+str(TH1_1800.GetMean()))
#print("M1800 Std : "+str(TH1_1800.GetStdDev()))
#print("M2100 Mean: "+str(TH1_2100.GetMean()))
#print("M2100 Std : "+str(TH1_2100.GetStdDev()))
#print("M2100 Int : "+str(TH1_2100.Integral()))

#print(list_TH1[0].GetMean())
#print(list_TH1[0].GetStdDev())
#print(list_TH1[3].GetMean())
#print(list_TH1[3].GetStdDev())
#print(list_TH1[6].GetMean())
#print(list_TH1[6].GetStdDev())

hist_mvsr = ROOT.TH1F("GvsS", "Gluino mass vs Signal Strength", 8, 1450, 2250)
for i in range(0,8) : 
    hist_mvsr.SetBinContent(i+1,r_arry[i])
    print(r_val_rms[i])
    hist_mvsr.SetBinError(i+1,r_max_arry[i])

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
hist_mvsr.GetYaxis().SetTitle("(#mu-1)/#sigma")
hist_mvsr.SetTitleSize(TitleSize)
hist_mvsr.SetStats(0)
hist_mvsr.SetMarkerStyle(42)
hist_mvsr.SetMarkerSize(0.2)
hist_mvsr.SetLineColor(ROOT.kRed)
hist_mvsr.SetMarkerColor(ROOT.kRed)
hist_mvsr.Draw()
cmslabel = "#font[62]{CMS} #scale[0.8]{#font[52]{Work In Progress}}"
lumilabel = "138 fb^{-1} (13 TeV)"
label = ROOT.TLatex()
label.SetNDC(ROOT.kTRUE)
label.SetTextSize(0.03)
label.SetTextAlign(11)
label.DrawLatex(PadLeftMargin,1-PadTopMargin+0.02,cmslabel);
label.SetTextAlign(31)
label.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,lumilabel);
b = ROOT.TBox(0,-1,9,1)
b.SetFillStyle(3003)
b.SetFillColor(ROOT.kBlue)
b.Draw("same")
hist_mvsr.Draw("same EP")
c.Print("mass_vs_r_result.pdf")
c.Print("mass_vs_r_result.C")

c2=ROOT.TCanvas()
c2.SetGrid()
TH1_1500.SetLineColor(ROOT.kBlack)
TH1_1500.SetStats(0)
TH1_1500.SetTitle("")
TH1_1500.GetXaxis().SetRangeUser(-5.5,4.5)
TH1_1500.GetYaxis().SetRangeUser(0,100)
TH1_1800.SetLineColor(ROOT.kBlue)
TH1_2100.SetLineColor(ROOT.kRed)
TH1_1500.Draw("hist")
TH1_1800.Draw("same hist")
label.SetNDC(ROOT.kTRUE)
label.SetTextSize(0.03)
label.SetTextAlign(11)
label.DrawLatex(PadLeftMargin,1-PadTopMargin+0.02,cmslabel);
label.SetTextAlign(31)
label.DrawLatex(1-PadRightMargin,1-PadTopMargin+0.02,lumilabel);
TH1_2100.Draw("same hist")
c2.Print("1800vs1500.pdf")
