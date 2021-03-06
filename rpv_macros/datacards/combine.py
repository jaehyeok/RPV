import os
import sys
import ROOT
from ROOT import TH2F, TTree, TFile, TCanvas

mass = sys.argv[1]
inputname = sys.argv[2]

if len(sys.argv) == 3:
	hist = TH2F('hist','hist', 3, 4, 10, 4, 0.5, 4.5)
	g = open("datacards/result.txt","w")
	dname = 'datacards/datacard_M'+str(mass)+'_mconly_'
	nb_list = ["nb1","nb2","nb3","nb4"]
	njets_list = ["low","med","high"]
	for nbs in nb_list:
		for njets in njets_list:
			region = "sr"
			if nbs=="nb1" or njets=="low":
				region = "cr"
			fname = dname+region+"_"+nbs+"_"+njets+"njets_nopdfoutput_"+inputname+".dat"
			os.system("datacards/combine.sh "+fname)
			f = open("datacards/combine.txt","r")
			res = f.read()
			f.close()
			spl_res = res.split()
			exp50 = spl_res[spl_res.index("50.0%:")+3]
			pline = nbs + " / " + njets + "jets : " + exp50 + "\n"
			g.write(pline)
			hist.SetBinContent(njets_list.index(njets)+1,nb_list.index(nbs)+1,float(exp50))
	os.system("datacards/combine.sh "+dname+"nopdfoutput_"+inputname+".dat")
	f = open("datacards/combine.txt","r")
	res = f.read()
	f.close()
 	spl_res = res.split()
	exp50 = spl_res[spl_res.index("50.0%:")+3]
	c = TCanvas("c","c",800,800)
	c.cd()
	hist.SetTitle(exp50)
	hist.SetStats(0)
	hist.SetMarkerSize(2);
	hist.Draw("colz text")
	c.SetLogz();
	c.Print("result.pdf")
	g.close()
	h=TFile.Open('result.root','recreate')
	hist.Write()
	h.Close()
