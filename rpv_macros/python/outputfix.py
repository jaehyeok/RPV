import ROOT
from ROOT import *
import sys
import ctypes

if __name__=="__main__":
    year = sys.argv[1]

    if year=="UL2016_preVFP" or year=="UL2016_postVFP": f_orig = TFile("variations/output_nominal_newnt_"+year+"_UL2016.root", "READ")
    elif year=="UL2017" or year=="UL2018": f_orig = TFile("variations/output_nominal_newnt_"+year+"_UL20178.root", "READ")
    f_modi = TFile("variations/output_"+year+"_mckappa.root","RECREATE")
    f_kapp = TFile("data/fit_kappa_summary_"+year+".root","READ")

    for i in range(22,52) :
        if year == "UL2016_preVFP" or year == "UL2016_postVFP" : year="UL2016"
        elif year == "UL2017" or year == "UL2018" : year="UL20178"
        #Get histogram profiles from fit_kappa_summary file#
        injets  = (i-1)%3
        inb     = int((i-22)/3+1)
        h1_up   = f_kapp.Get("h1_nb_fit_combined_up"+str(injets)) 
        h1_down = f_kapp.Get("h1_nb_fit_combined_down"+str(injets))
        h2_up   = f_kapp.Get("h2_nb_fit_combined_up"+str(injets))
        h2_down = f_kapp.Get("h2_nb_fit_combined_down"+str(injets))
        h1_jec_up   = f_kapp.Get("h1_nb_fit_jec_up"+str(injets)) 
        h1_jec_down = f_kapp.Get("h1_nb_fit_jec_down"+str(injets))
        h2_jec_up   = f_kapp.Get("h2_nb_fit_jec_up"+str(injets))
        h2_jec_down = f_kapp.Get("h2_nb_fit_jec_down"+str(injets))
        h1_jer_up   = f_kapp.Get("h1_nb_fit_jer_up"+str(injets)) 
        h1_jer_down = f_kapp.Get("h1_nb_fit_jer_down"+str(injets))
        h2_jer_up   = f_kapp.Get("h2_nb_fit_jer_up"+str(injets))
        h2_jer_down = f_kapp.Get("h2_nb_fit_jer_down"+str(injets))

        f_modi.cd()
        gDirectory.mkdir("bin"+str(i))
#   	for proc in ["qcd","ttbar","wjets","other"] :
        for proc in ["qcd","ttbar","wjets"] :
            h_proc = TH1F(f_orig.Get("bin"+str(i)+"/"+proc))
            #Make Combined MC Histogram#
            h_mc    = h_proc.Clone("h_mc")
            #Getting Nb correction factor from the histogram#
            kap1_cor_up   = h1_up.GetBinContent(inb)             #total
            kap1_cor_down = h1_down.GetBinContent(inb)
            kap2_cor_up   = h2_up.GetBinContent(inb)
            kap2_cor_down = h2_down.GetBinContent(inb)
            kap1_cor_jec_up   = h1_jec_up.GetBinContent(inb)     #jec
            kap1_cor_jec_down = h1_jec_down.GetBinContent(inb)
            kap2_cor_jec_up   = h2_jec_up.GetBinContent(inb)
            kap2_cor_jec_down = h2_jec_down.GetBinContent(inb)
            kap1_cor_jer_up   = h1_jer_up.GetBinContent(inb)     #jer
            kap1_cor_jer_down = h1_jer_down.GetBinContent(inb)
            kap2_cor_jer_up   = h2_jer_up.GetBinContent(inb)
            kap2_cor_jer_down = h2_jer_down.GetBinContent(inb)
            print("bin"+str(i)+" / "+str(proc))
            print("kap1_cor_up       : "+str(kap1_cor_up))
            print("kap1_cor_down     : "+str(kap1_cor_down))
            print("kap1_cor_jec_up   : "+str(kap1_cor_jec_up))
            print("kap1_cor_jec_down : "+str(kap1_cor_jec_down))

            #Making MC_kappa#
            ind_njets = 10*(2*injets+4)+2*injets+5
            if ind_njets==89 : ind_njets=8
            h_mc_kap1_up   = h_mc.Clone(proc+"_MC_kappa1_njets"+str(ind_njets)+"_"+year+"Up")  # Clone : naming?
            h_mc_kap1_down = h_mc.Clone(proc+"_MC_kappa1_njets"+str(ind_njets)+"_"+year+"Down")
            h_mc_kap2_up   = h_mc.Clone(proc+"_MC_kappa2_njets"+str(ind_njets)+"_"+year+"Up")
            h_mc_kap2_down = h_mc.Clone(proc+"_MC_kappa2_njets"+str(ind_njets)+"_"+year+"Down")
            h_mc_kap1_jec_up   = h_mc.Clone(proc+"_MC_kappa1_jec_njets"+str(ind_njets)+"_"+year+"Up")
            h_mc_kap1_jec_down = h_mc.Clone(proc+"_MC_kappa1_jec_njets"+str(ind_njets)+"_"+year+"Down")
            h_mc_kap2_jec_up   = h_mc.Clone(proc+"_MC_kappa2_jec_njets"+str(ind_njets)+"_"+year+"Up")
            h_mc_kap2_jec_down = h_mc.Clone(proc+"_MC_kappa2_jec_njets"+str(ind_njets)+"_"+year+"Down")
            h_mc_kap1_jer_up   = h_mc.Clone(proc+"_MC_kappa1_jer_njets"+str(ind_njets)+"_"+year+"Up")
            h_mc_kap1_jer_down = h_mc.Clone(proc+"_MC_kappa1_jer_njets"+str(ind_njets)+"_"+year+"Down")
            h_mc_kap2_jer_up   = h_mc.Clone(proc+"_MC_kappa2_jer_njets"+str(ind_njets)+"_"+year+"Up")
            h_mc_kap2_jer_down = h_mc.Clone(proc+"_MC_kappa2_jer_njets"+str(ind_njets)+"_"+year+"Down")

            #Applying Kappa Correction#
            h_mc_kap1_up.SetBinContent(2,h_mc_kap1_up.GetBinContent(2)*(1+kap1_cor_up))			#total
            h_mc_kap1_down.SetBinContent(2,h_mc_kap1_down.GetBinContent(2)*(1+kap1_cor_down))    # kap_cor_down is defined as negative
            h_mc_kap2_up.SetBinContent(3,h_mc_kap2_up.GetBinContent(3)*(1+kap2_cor_up))
            h_mc_kap2_down.SetBinContent(3,h_mc_kap2_down.GetBinContent(3)*(1+kap2_cor_down))
            h_mc_kap1_jec_up.SetBinContent(2,h_mc_kap1_jec_up.GetBinContent(2)*(1+kap1_cor_jec_up))		#jec
            h_mc_kap1_jec_down.SetBinContent(2,h_mc_kap1_jec_down.GetBinContent(2)*(1-kap1_cor_jec_down))    # kap_jec_down is defined as positive
            h_mc_kap2_jec_up.SetBinContent(3,h_mc_kap2_jec_up.GetBinContent(3)*(1+kap2_cor_jec_up))
            h_mc_kap2_jec_down.SetBinContent(3,h_mc_kap2_jec_down.GetBinContent(3)*(1-kap2_cor_jec_down))
            h_mc_kap1_jer_up.SetBinContent(2,h_mc_kap1_jer_up.GetBinContent(2)*(1+kap1_cor_jer_up))		#jer
            h_mc_kap1_jer_down.SetBinContent(2,h_mc_kap1_jer_down.GetBinContent(2)*(1-kap1_cor_jer_down))    # kap_jer_down is defined as positive
            h_mc_kap2_jer_up.SetBinContent(3,h_mc_kap2_jer_up.GetBinContent(3)*(1+kap2_cor_jer_up))
            h_mc_kap2_jer_down.SetBinContent(3,h_mc_kap2_jer_down.GetBinContent(3)*(1-kap2_cor_jer_down))
            f_modi.cd()
            gDirectory.cd("bin"+str(i)+"/")
            h_mc_kap1_up.Write()
            h_mc_kap1_down.Write()
            h_mc_kap2_up.Write()
            h_mc_kap2_down.Write()
            h_mc_kap1_jec_up.Write()
            h_mc_kap1_jec_down.Write()
            h_mc_kap2_jec_up.Write()
            h_mc_kap2_jec_down.Write()
            h_mc_kap1_jer_up.Write()
            h_mc_kap1_jer_down.Write()
            h_mc_kap2_jer_up.Write()
            h_mc_kap2_jer_down.Write()
