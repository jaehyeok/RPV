import ROOT
from ROOT import *
import sys

if __name__=="__main__":
    year = sys.argv[1]
    f_orig = TFile("20220211_yjeong/output_"+year+".root", "READ")
    f_modi = TFile("20220211_yjeong/output_"+year+"_mckappa.root","RECREATE")
    f_kapp = TFile("data/fit_kappa_summary_"+year+".root","READ")
    for i in range(22,52) :
        if year == "2017" or year == "2018" : year="20178"
        #Getting histogram profiles of fit_kappa_summary#
        injets  = (i-1)%3
        inb     = int((i-22)/3+1)
        h1_up   = f_kapp.Get("h1_nb_fit_combined_up"+str(injets)) 
        h1_down = f_kapp.Get("h1_nb_fit_combined_down"+str(injets))
        h2_up   = f_kapp.Get("h2_nb_fit_combined_up"+str(injets))
        h2_down = f_kapp.Get("h2_nb_fit_combined_down"+str(injets))

	f_modi.cd()
        gDirectory.mkdir("bin"+str(i))
	for proc in ["qcd","ttbar","wjets","other"] :
		h_proc = TH1F(f_orig.Get("bin"+str(i)+"/"+proc))
        	#Make Combined MC Histogram#
        	h_mc    = h_proc.Clone("h_mc")
        	#Getting Nb correction factor from the histogram#
        	kap1_cor_up   = h1_up.GetBinContent(inb)
        	kap1_cor_down = h1_down.GetBinContent(inb)
        	kap2_cor_up   = h2_up.GetBinContent(inb)
        	kap2_cor_down = h2_down.GetBinContent(inb)
		print("bin"+str(i))
		print(kap1_cor_up)
		print(kap1_cor_down)
        	#Making MC_kappa#
		ind_njets = 10*(2*injets+4)+2*injets+5
		if ind_njets==89 : ind_njets=8
        	h_mc_kap1_up   = h_mc.Clone(proc+"_MC_kappa1_njets"+str(ind_njets)+"_"+year+"Up")
        	h_mc_kap1_down = h_mc.Clone(proc+"_MC_kappa1_njets"+str(ind_njets)+"_"+year+"Down")
        	h_mc_kap2_up   = h_mc.Clone(proc+"_MC_kappa2_njets"+str(ind_njets)+"_"+year+"Up")
        	h_mc_kap2_down = h_mc.Clone(proc+"_MC_kappa2_njets"+str(ind_njets)+"_"+year+"Down")
        	#Applying Kappa Correction#
        	h_mc_kap1_up.SetBinContent(2,h_mc_kap1_up.GetBinContent(2)*(1+kap1_cor_up))
        	h_mc_kap1_down.SetBinContent(2,h_mc_kap1_up.GetBinContent(2)*(1-kap1_cor_down))
        	h_mc_kap2_up.SetBinContent(3,h_mc_kap1_up.GetBinContent(3)*(1+kap2_cor_up))
        	h_mc_kap2_down.SetBinContent(3,h_mc_kap1_up.GetBinContent(3)*(1-kap2_cor_down))
        	f_modi.cd()
        	gDirectory.cd("bin"+str(i)+"/")
        	h_mc_kap1_up.Write()
        	h_mc_kap1_down.Write()
        	h_mc_kap2_up.Write()
        	h_mc_kap2_down.Write()

