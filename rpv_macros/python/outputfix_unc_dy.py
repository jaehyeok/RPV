# This code is for considring the MJ shape difference between DY and W+jets MC events.

import ROOT
from ROOT import *
import sys
import ctypes

if __name__=="__main__":

    # kappa uncertainty of MJ shape difference between DY and W+jets
    # These values are from compare_shape_wjets_dy funciton in src/plot_wjets_dy.cxx
    unc_dy_UL2016_preVFP = [
            [0.21, 0.20],
            [0.20, 0.17],
            [0.20, 0.17]]
    unc_dy_UL2016_postVFP = [
            [0.23, 0.22],
            [0.21, 0.23],
            [0.21, 0.11]]
    unc_dy_UL2017 = [
            [0.21, 0.18],
            [0.23, 0.22],
            [0.23, 0.17]]
    unc_dy_UL2018 = [
            [0.21, 0.20],
            [0.22, 0.19],
            [0.21, 0.18]]

    year = sys.argv[1]

    if year=="UL2016_preVFP" or year=="UL2016_postVFP": f_orig = TFile("variations/output_nominal_newnt_"+year+"_UL2016.root", "READ")
    elif year=="UL2017" or year=="UL2018": f_orig = TFile("variations/output_nominal_newnt_"+year+"_UL20178.root", "READ")
    f_modi = TFile("variations/output_"+year+"_unc_dy.root","RECREATE")

    year_in = year
    if year == "UL2016_preVFP" or year == "UL2016_postVFP": year_in="UL2016"
    elif year == "UL2017" or year == "UL2018": year_in="UL20178"

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
        if year == "UL2016_preVFP":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_UL2016_preVFP[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_UL2016_preVFP[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_UL2016_preVFP[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_UL2016_preVFP[injets][1]))
        if year == "UL2016_postVFP":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_UL2016_postVFP[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_UL2016_postVFP[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_UL2016_postVFP[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_UL2016_postVFP[injets][1]))
        elif year == "UL2017":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_UL2017[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_UL2017[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_UL2017[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_UL2017[injets][1]))
        elif year == "UL2018":
            h_kap1_up.SetBinContent(2,   h_kap1_up.GetBinContent(2)*(1+unc_dy_UL2018[injets][0]))
            h_kap1_down.SetBinContent(2, h_kap1_down.GetBinContent(2)*(1-unc_dy_UL2018[injets][0]))
            h_kap2_up.SetBinContent(3,   h_kap2_up.GetBinContent(3)*(1+unc_dy_UL2018[injets][1]))
            h_kap2_down.SetBinContent(3, h_kap2_down.GetBinContent(3)*(1-unc_dy_UL2018[injets][1]))
        f_modi.cd()
        gDirectory.cd("/bin"+str(i))
        h_kap1_up.Write()
        h_kap1_down.Write()
        h_kap2_up.Write()
        h_kap2_down.Write()
