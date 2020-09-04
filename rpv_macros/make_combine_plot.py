import os
import sys
import ROOT
from ROOT import TCanvas, TH1, TH2, TFile

mass = sys.argv[1]
mjmin = sys.argv[2]

mjlist = [500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000]

if __name__=="__main__":
	ccpath = '/cms/ldap_home/cwjung/CMSSW_10_5_0/src/RPV/rpv_macros/'
	g = TFile.Open("result.root","read")
	hist = g.Get("hist")
	if not os.path.isfile(ccpath+'comb_comp.C'):
		os.system("cp -f comp_org.C comb_comp.C")
	with open(ccpath+'comb_comp.C','r') as f :
		lines = f.readlines()
	for line in lines :
		if 'TCanvas' in line :
			ind = lines.index(line)
	name = hist.GetTitle()
	print(str(mjlist.index(int(mjmin)))+' : '+name) 
	histring = '\th_'+str(mass)+'->SetBinContent('+str(mjlist.index(int(mjmin))+1)+','+name+');\n'
	lines.insert(ind-1,histring)
	with open(ccpath+'comb_comp.C','w') as f :
		for line in lines :
			f.write(line)


