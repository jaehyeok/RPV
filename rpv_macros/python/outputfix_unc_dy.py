# This code is for considring the MJ shape difference between DY and W+jets MC events.

import ROOT
from ROOT import *
import sys
import ctypes

if __name__=="__main__":

    # kappa uncertainty of MJ shape difference between DY and W+jets
    unc_dy_2016 = [
            [0.22, 0.21],
            [0.21, 0.19],
            [0.21, 0.16]]
    unc_dy_2017 = [
            [0.21, 0.18],
            [0.23, 0.22],
            [0.22, 0.15]]
    unc_dy_2018 = [
            [0.21, 0.20],
            [0.22, 0.19],
            [0.21, 0.17]]
    unc_dy_20178 = [
            [0.21, 0.19],
            [0.22, 0.20],
            [0.21, 0.16]] # Now we don't use these 20178 uncertainty

    year = sys.argv[1]

    if year=="2016" or year=="20178": f_orig = TFile("variations/output_nominal_newnt_"+year+".root", "READ")
    elif year=="2017" or year=="2018": f_orig = TFile("variations/output_nominal_newnt_"+year+"_20178.root", "READ")
    f_modi = TFile("variations/output_"+year+"_unc_dy.root","RECREATE")

    year_in = year
    if year == "2017" or year == "2018" or year == "20178": year_in="20178"

    # bin loop
    for i in range(22,52):
        f_modi.cd()
        gDirectory.mkdir("bin"+str(i))

        injets    = (i-1)%3
        ind_njets = 10*(2*injets+4)+2*injets+5
        if ind_njets == 89 : ind_njets=8

        # Clone W+jets
        h_proc    = TH1F(f_orig.Get("bin"+str(i)+"/wjets"))
        h_wjets   = h_proc.Clone("h_wjets")

        h_kap1_up   = h_wjets.Clone("wjets_kappa1_unc_dy_njets"+str(ind_njets)+"_wjets_"+year_in+"Up")
        h_kap1_down = h_wjets.Clone("wjets_kappa1_unc_dy_njets"+str(ind_njets)+"_wjets_"+year_in+"Down")
        h_kap2_up   = h_wjets.Clone("wjets_kappa2_unc_dy_njets"+str(ind_njets)+"_wjets_"+year_in+"Up")
        h_kap2_down = h_wjets.Clone("wjets_kappa2_unc_dy_njets"+str(ind_njets)+"_wjets_"+year_in+"Down")

        # Apply kappa uncertainty
        if year == "2016":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_2016[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_2016[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_2016[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_2016[injets][1]))
        elif year == "2017":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_2017[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_2017[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_2017[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_2017[injets][1]))
        elif year == "2018":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_2018[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_2018[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_2018[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_2018[injets][1]))
        elif year == "20178":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_20178[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_20178[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_20178[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_20178[injets][1]))
        f_modi.cd()
        gDirectory.cd("/bin"+str(i))
        h_kap1_up.Write()
        h_kap1_down.Write()
        h_kap2_up.Write()
        h_kap2_down.Write()
