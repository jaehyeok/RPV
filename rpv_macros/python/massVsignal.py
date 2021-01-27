#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
import datetime
from optparse import OptionParser
import HiggsAnalysis.CombinedLimit.calculate_pulls as CP
import ROOT

r_arry = []
err_arry = []
r_min_arry = []
r_max_arry = []
for mass in list(range(1000,2300,100)):
	file = ROOT.TFile("fitDiagnostics_SpB_M"+str(mass)+".root")
	if file == None : raise RuntimeError, "Cannot open file %s" % "fitDiagnostics_SpB_M"+str(mass)+".root"
	fit_s = file.Get("fit_s"); 
	if fit_s == None or fit_s.ClassName() != "RooFitResult" : raise RuntimeError, "File does not contain output of the signal fit 'fit_s'"
	fpf_s = fit_s.floatParsFinal()
	rval = fpf_s.find("r")
	print(rval.getAsymErrorHi())
	print(rval.getAsymErrorLo())
	err_arry.append(rval.getError())
	r_max_arry.append(rval.getAsymErrorHi())
	r_min_arry.append(rval.getAsymErrorLo())
	r_arry.append(rval.getVal())
hist_mvsr = ROOT.TH1F("GvsS", "Gluino mass vs Signal Strength", 13, 950, 2250)
for i in range(0,13) : 
	hist_mvsr.SetBinContent(i+1,r_arry[i])
	hist_mvsr.SetBinError(i+1,0)
err_mvsr = ROOT.TGraphAsymmErrors(hist_mvsr)
for i in range(0,13) : 
	err_mvsr.SetPointError(i+1,0,0,-1*r_min_arry[i],r_max_arry[i])
c = ROOT.TCanvas("c","c",800,800)
hist_mvsr.GetYaxis().SetRangeUser(-2.5, 6)
hist_mvsr.GetXaxis().SetRangeUser(950,2250)
hist_mvsr.SetStats(0)
hist_mvsr.SetMarkerStyle(42)
hist_mvsr.SetMarkerSize(0.05)
hist_mvsr.SetMarkerColor(ROOT.kRed)
hist_mvsr.Draw("EP")
err_mvsr.SetMarkerStyle(42)
err_mvsr.SetMarkerSize(0.2)
err_mvsr.SetMarkerColor(ROOT.kRed)
err_mvsr.SetLineColor(ROOT.kRed)
err_mvsr.Draw("same EP")
c.Print("mass.vs.r.result.pdf")
