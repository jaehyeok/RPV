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

r_arr_mean = []
r_arr_med = []
r_arr_err_mean = []
r_arr_err_med = []

TH1_1500   = ROOT.TH1F("1500 GeV", "1500 GeV",150,-5.5,9.5)
TH1_1800   = ROOT.TH1F("1800 GeV", "1800 GeV",150,-5.5,9.5)
TH1_2100   = ROOT.TH1F("2100 GeV", "2100 GeV",150,-5.5,9.5)
TH1_status = ROOT.TH1F("fit_s status", "fit_s status", 7, -1., 6.)

list_TH1_dist    = []
list_TH1_mu_dist = []
for mass in list(range(1500,2300,100)):
    TH1_dist = ROOT.TH1F("h_dist_{0}".format(mass), "h_dist_{0}".format(mass), 150, -5.5, 9.5)
    TH1_mu_dist = ROOT.TH1F("h_mu_dist_{0}".format(mass), "h_mu_dist_{0}".format(mass), 150, -5.5, 9.5)
    list_TH1_dist.append(TH1_dist)
    list_TH1_mu_dist.append(TH1_mu_dist)

mass_idx = -1
nseed = 1000

for mass in list(range(1500,2300,100)):
#for mass in list(range(1500,1600,100)):

    mass_idx+=1
    central      =[]
    list_error_r =[]
    list_val_r   =[]
    n_entries = nseed
    n_fit_s_entries=nseed
    n_limit_entries=nseed
    n_status_not_0_entries=nseed
    n_exceed_entries=nseed
    list_fit_s_status=[-999 for i in range(nseed+1)]

    #for seed in list(range(1,1001)):
    for seed in list(range(1,nseed+1)):
        if seed%100==0 : print(str(mass)+" GeV, "+str(seed)+"th loop")

        fit_limit = "/mnt/data3/public/signal_injection/out_injection_201678_full_240605/higgsCombine_M"+str(mass)+"_"+str(seed)+"_201678.FitDiagnostics.mH120."+str(seed)+".root"
        fit_result = "/mnt/data3/public/signal_injection/out_injection_201678_full_240605/fitDiagnostics_M"+str(mass)+"_"+str(seed)+"_201678.root"
        file_limit = ROOT.TFile(fit_limit)
        file_result = ROOT.TFile(fit_result)

        if file_limit == None : raise RuntimeError, "Cannot open file %s" % fit_limit
        if file_result == None : raise RuntimeError, "Cannot open file %s" % fit_result

        limit_t = file_limit.Get("limit")
        result_t= file_result.Get("fit_s")

        # Get the number of events not having +1 sigma of signal strength or status of fit_s
        if result_t == None or result_t.ClassName() != "RooFitResult" :
            n_fit_s_entries-=1
        limit_t.GetEntry(3)
        if limit_t.limit==0 : 
            n_limit_entries-=1

        if result_t == None or result_t.ClassName() != "RooFitResult" :
            n_entries-=1
            continue
        if limit_t == None or limit_t.ClassName() != "TTree" : raise RuntimeError, "File does not contain TTree output of the signal fit 'limit'"
        # check whether +1 sigma of signal strength exists or not
        limit_t.GetEntry(3)
        if limit_t.limit==0 : 
            n_entries-=1
            continue

        status_t = result_t.status()
        list_fit_s_status[seed] = status_t
        TH1_status.Fill(status_t)
        # veto the case where status of fit_s is not equal to 0
        if status_t != 0 :
        #if status_t == -999 :
            n_status_not_0_entries-=1
            n_entries-=1
            continue

        limit_t.GetEntry(4)
        value_r = limit_t.limit
        limit_t.GetEntry(3)
        error_r = limit_t.limit - value_r
        list_val_r.append(value_r)
        list_error_r.append(error_r)
        if(abs((value_r-1)/error_r) > 10.) : 
            n_entries-=1
            n_exceed_entries-=1
            print("((r-1)/rErr): "+str((value_r-1)/error_r))
            continue
        central.append((value_r-1)/error_r)
        if mass==1500 : TH1_1500.Fill((value_r-1)/error_r)
        elif mass==1800 : TH1_1800.Fill((value_r-1)/error_r)
        elif mass==2100 : TH1_2100.Fill((value_r-1)/error_r)
        list_TH1_dist[mass_idx].Fill((value_r-1)/error_r)
        list_TH1_mu_dist[mass_idx].Fill(value_r)
    central = sorted(central)
    list_error_r = sorted(list_error_r)
    print("not having fit_s : "+str(nseed - n_fit_s_entries))
    print("not having limit : "+str(nseed - n_limit_entries))
    print("fit_s.status()!=0: "+str(nseed - n_status_not_0_entries))
    print("(r-1)/rErr > 10  : "+str(nseed - n_exceed_entries))
    print("total entries    : "+str(n_entries))
    list_val_r = sorted(list_val_r)
    med_cent = central[int(n_entries/2)] 

    # test
    n_nocut=0; sum_nocut = 0
    n_neg=0; sum_neg = 0
    n_pos=0; sum_pos = 0
    sum_tot = 0
    n_pos_med=0; sum_pos_med = 0
    for val in central :
        n_nocut += 1
        sum_nocut = sum_nocut + ((val-list_TH1_dist[mass_idx].GetMean())**2)
        sum_tot += val
        #if val < med_cent : continue
        if val < list_TH1_dist[mass_idx].GetMean() :
            n_neg += 1
            sum_neg = sum_neg + ((val-list_TH1_dist[mass_idx].GetMean())**2)
        if val > list_TH1_dist[mass_idx].GetMean() :
            n_pos += 1
            sum_pos = sum_pos + ((val-list_TH1_dist[mass_idx].GetMean())**2)
        if val > med_cent :
            n_pos_med += 1
            sum_pos_med = sum_pos_med + ((val-med_cent)**2)
    print("M{0} Mean                               : ".format(mass)+str(round(list_TH1_dist[mass_idx].GetMean(), 3)))
    print("[by hand] Mean                           : "+str(round(sum_tot/len(central), 3)))
    print("")
    print("M{0} StdDev                             : ".format(mass)+str(round(list_TH1_dist[mass_idx].GetStdDev(), 3)))
    print("[by hand] RMS                         : "+str(round(np.sqrt(sum_nocut/n_nocut), 3)))
    print("[by hand using half data (< Mean)] RMS: "+str(round(np.sqrt(sum_neg/n_neg), 3)))
    print("[by hand using half data (> Mean)] RMS: "+str(round(np.sqrt(sum_pos/n_pos), 3)))
    print("")

    print("M{0} Med                                : ".format(mass)+str(round(med_cent, 3)))
    print("[by hand] RMS of median               : "+str(round(np.sqrt(sum_pos_med/n_pos_med), 3)))

    c_err = ROOT.TCanvas()
    c_err.SetGrid()
    c_err.cd()
    TH1_err = ROOT.TH1F("TH1_err", "Th1_err",600,-3,3)
    for err in list_error_r:
	    TH1_err.Fill(err)
    TH1_err.Draw("hist")
    print("err_mean: "+str(TH1_err.GetMean()))
    print("err_stdD: "+str(TH1_err.GetStdDev()))

    # test end

    # mean
    r_arr_mean.append(list_TH1_dist[mass_idx].GetMean())
    r_arr_err_mean.append(list_TH1_dist[mass_idx].GetStdDev())
    # median
    r_arr_med.append(med_cent)
    r_arr_err_med.append(np.sqrt(sum_pos_med/n_pos_med))


list_mvsr = []
# define histograms
for i in range(0,2) :
    if i==0: datapoint = "mean"
    elif i==1: datapoint = "med"
    hist_mvsr = ROOT.TH1F("mass_vs_r_result_"+datapoint, "Gluino mass vs Signal Strength_"+datapoint, 8, 1450, 2250)
    list_mvsr.append(hist_mvsr)
# fill datapoints and errors
for i in range(0,8) : 
#for i in range(0,1) : 
    list_mvsr[0].SetBinContent(i+1,r_arr_mean[i])
    list_mvsr[0].SetBinError(i+1,r_arr_err_mean[i])
    list_mvsr[1].SetBinContent(i+1,r_arr_med[i])
    list_mvsr[1].SetBinError(i+1,r_arr_err_med[i])
# draw histograms
for i in range(0,2) :
    list_mvsr[i].SetTitleOffset(xTitleOffset,"x");
    list_mvsr[i].SetTitleOffset(yTitleOffset,"y");
    list_mvsr[i].SetTitleSize(TitleSize,"xyz")
    list_mvsr[i].SetLabelSize(LabelSize,"xyz")
    c = ROOT.TCanvas()
    c.SetGrid()
    list_mvsr[i].SetTitle("");
    list_mvsr[i].GetYaxis().SetRangeUser(-2, 2)
    list_mvsr[i].GetXaxis().SetRangeUser(1450,2250)
    list_mvsr[i].GetXaxis().SetTitle("m_{#tilde{g}}")
    list_mvsr[i].GetYaxis().SetTitle("(#mu-1)/#sigma")
    list_mvsr[i].SetTitleSize(TitleSize)
    list_mvsr[i].SetStats(0)
    list_mvsr[i].SetMarkerStyle(42)
    list_mvsr[i].SetMarkerSize(0.2)
    list_mvsr[i].SetLineColor(ROOT.kRed)
    list_mvsr[i].SetMarkerColor(ROOT.kRed)
    list_mvsr[i].Draw()
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
    list_mvsr[i].Draw("same EP")
    c.Print("signal_injection/{0}.pdf".format(list_mvsr[i].GetName()))
    c.Print("signal_injection/{0}.C".format(list_mvsr[i].GetName()))

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
c2.Print("signal_injection/1800vs1500.pdf")

c3=ROOT.TCanvas()
TH1_status.Draw("hist")
c3.Print("signal_injection/fit_s_status.pdf")

c4=ROOT.TCanvas()
c4.SetGrid()

for mass in range(0,8):
    list_TH1_dist[mass].SetTitle("distribution of (#mu-1)/(#mu_{+1#sigma}-#mu)")
    list_TH1_dist[mass].GetYaxis().SetRangeUser(0,200)
    list_TH1_dist[mass].GetYaxis().SetTitle("Counts")
    list_TH1_dist[mass].GetXaxis().SetTitle("(#mu-1)/(#mu_{+1#sigma}-#mu)")
    list_TH1_dist[mass].Draw("hist")
    c4.Print("signal_injection/M{0}_distribution.pdf".format(1500+100*mass))

    list_TH1_mu_dist[mass].SetTitle("distribution of signal strength")
    list_TH1_mu_dist[mass].GetYaxis().SetRangeUser(0,200)
    list_TH1_mu_dist[mass].GetYaxis().SetTitle("Counts")
    list_TH1_mu_dist[mass].GetXaxis().SetTitle("#mu")
    list_TH1_mu_dist[mass].Draw("hist")
    c4.Print("signal_injection/M{0}_mu_distribution.pdf".format(1500+100*mass))




