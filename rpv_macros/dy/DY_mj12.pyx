import ROOT
import os
import sys
from ROOT import TLegend, TChain, TCanvas, TLorentzVector, TH1D, TH1, THStack, TColor, TPad, TGaxis, TLine, TLatex, TBox, TTree
from ROOT import kGreen, kBlue, kBlack, kAzure, kRed, kYellow, kViolet, kGray

lumi = {'2016':36.3,'2017':41.5,'2018':59.8,'Run2':138,'20178':101.3}

def totpath(year):
	ret = []
	if year=="Run2" :
		for y in ["2016","2017","2018"]:
			#ret.append("/mnt/data3/babies/210910/"+y+"/merged_norm_dy0923/") 
			ret.append("/mnt/data3/babies/231001/"+y+"/merged_norm_njets3nleps2/") 
	elif year == "20178":
		for y in ["2017","2018"]:
			#ret.append("/mnt/data3/babies/210910/"+y+"/merged_norm_dy0923/")
			ret.append("/mnt/data3/babies/231001/"+y+"/merged_norm_njets3nleps2/")
	#else : ret.append("/mnt/data3/babies/210910/"+year+"/merged_norm_dy0923/")
	else : ret.append("/mnt/data3/babies/231001/"+year+"/merged_norm_njets3nleps2/")
	print(ret)
	return ret


def Progress(entry, entry_tot):	
	progress = float(entry)/float(entry_tot)
	size = 50
	filledLength = int(progress*size)
	bar = '#'*filledLength + '-'*(size-filledLength)
	percent = "{0:.2f}".format(100*progress)
	sys.stdout.write('\r'+bar+'  '+percent+'%')
	sys.stdout.flush()

cpdef (float, float) getKappa(h1, h2):
	cdef float kappa1, kappa2
	h_div = h1.Clone("h_div")
	TH1D.Divide(h_div,h2)
	kappa1 = h_div.GetBinContent(2)/h_div.GetBinContent(1)
	kappa2 = h_div.GetBinContent(3)/h_div.GetBinContent(1)
	return kappa1, kappa2

cpdef getDYHist( ch, nbmcut, njetscut, histname, year):
	if njetscut >= 7 : njetscut_up = 9999999 #FIXME
	else : njetscut_up = njetscut+2 #FIXME
	h_ratio = TH1D("h_ratio"+histname,"h_ratio_"+histname,3,500,1400)
	h_int = TH1D("h_int_"+histname, "h_int_"+histname, 3, 500, 1400)
	h = TH1D("h_"+histname,"h_"+histname,3,500,1400)
	h2 = TH1D("h2_"+histname,"h2_"+histname,3,500,1400) #FIXME mj
	hll = TH1D("h_ll_"+histname, "h_ll_"+histname, 5, 80 ,100)
	hll = TH1D("h_ll_"+histname, "h_ll_"+histname, 5, 80 ,100)
	hll2 = TH1D("h_ll2_"+histname, "h_ll2_"+histname, 5, 80 ,100)
	cdef float mass
	cpdef mom1, mom2, momtot
	cdef float mll
	for entry in range(0,ch.GetEntries()):
		mass=0
		pas=True
		ch.GetEntry(entry)
		ch.SetAlias("pass_weight", "pass")
		if(entry%(ch.GetEntries()/10)==0) : Progress(entry, ch.GetEntries())
		if not ch.stitch_ht : continue
		if not (ch.njets>njetscut-1 and ch.njets<njetscut_up) : continue #FIXME
		if not ch.nleps==2 : continue
		if not ch.nbm<=2 : continue #FIXME
		if not ch.ht > 1200 : continue 
		if not ch.mj12 > 500 : continue
		if not ch.pass_weight==1 : continue
		if ch.leps_pdgid.at(1)*ch.leps_pdgid.at(0) == -121 : mass = 0.510*pow(10,-3) 
		elif ch.leps_pdgid.at(1)*ch.leps_pdgid.at(0) == -169 : mass = 105.66*pow(10,-3) 
		else : continue
		mom1 = TLorentzVector(0,0,0,0)
		mom2 = TLorentzVector(0,0,0,0)
		mom1.SetPtEtaPhiM(ch.leps_pt.at(0), ch.leps_eta.at(0), ch.leps_phi.at(0), mass)
		mom2.SetPtEtaPhiM(ch.leps_pt.at(1), ch.leps_eta.at(1), ch.leps_phi.at(1), mass)
		momtot = mom1+mom2
		mll = momtot.M()
		if not mll < 101 : continue
		if not mll > 81 : continue
		if "MC" in histname :
			if year=="20178" :
				h_int.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac1718*lumi[year])
				if ch.nbm==nbmcut:
					h.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac1718*lumi[year])
					hll.Fill(mll,ch.weight*ch.frac1718*lumi[year])
				elif ch.nbm==nbmcut+1:
					h2.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac1718*lumi[year])
					hll2.Fill(mll,ch.weight*ch.frac1718*lumi[year])
				else : continue
			else :
				h_int.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac16*lumi[year])
				if ch.nbm==nbmcut:
					h.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac16*lumi[year])
					hll.Fill(mll,ch.weight*ch.frac16*lumi[year])
				elif ch.nbm==nbmcut+1:
					h2.Fill(min(ch.mj12,1399.99),ch.weight*ch.frac16*lumi[year])
					hll2.Fill(mll,ch.weight*ch.frac16*lumi[year])
				else : continue
		else : 
			h_int.Fill(min(ch.mj12,1399.99),1)
			if ch.nbm==nbmcut:
				h.Fill(min(ch.mj12,1399.99),1)
				hll.Fill(mll,1)
			elif ch.nbm==nbmcut+1:
				h2.Fill(min(ch.mj12,1399.99),1)
				hll2.Fill(mll,1)
			else : continue
	return h_ratio, h, h2, hll, hll2, h_int

def MakeLegend(list_hist,Data):
	l = TLegend(0.15,0.75,0.85,0.87)
	l.SetNColumns(2)
	l.SetBorderSize(0)
	l.AddEntry(Data,"data","ep")
	lista = []
	for h in list_hist:
		if h.Integral()>0 : 
			l.AddEntry(h, h.GetTitle(), "f")
	return l

def DY(pathlist, njcut, year):
		chMC = TChain("tree")
		chData = TChain("tree")
		process_list = ['qcd','others','ttbar','wjets','dyjet']
		process_name = {'qcd':'QCD', 'others':'Others', 'ttbar':'ttbar', 'wjets':'W+jets', 'dyjet':'DY'}
		#process_list = ['dyjet']
		process_det = {'qcd':['QCD_*'],'dyjet':['DYJets*'],'others':['ttHJet*','ST_*','TTTT*','TTW*','TTZ*','WW_*','WWW*','WWZ*','WZ_*','WZZ*','ZZ_*','ZZZ*'],'ttbar':['TTJets_*'],'wjets':['WJets*']}
		#process_det = {'qcd':['*QCD_*'],'dyjet':['*DYJetsTo*'],'others':['*ST_*','*TTTT*','*TTW*','*TTZ*','WW_*','*WWW*','*WWZ*','WZ_*','*WZZ*','ZZ_*','*ZZZ*'],'ttbar':['*TTJets_*'],'wjets':['*WJetsTo*']}
		process_color = {'qcd':kBlue-4,'dyjet':kViolet-9,'ttbar':kAzure+7,'wjets':kGreen+2,'others':kGray}
		MC_Stack0 = THStack("MC_Stack0","MC_Stack0")
		MC_Stack1 = THStack("MC_Stack1","MC_Stack1")
		MC_Stack_int = THStack("MC_Stack_int"+year,"MC_Stack_int"+year)
		MC_int = TH1D("MC_int","",3,500,1400)#FIXME
		MCll_Stack0 = THStack("MC_Stack0","MC_Stack0")
		MCll_Stack1 = THStack("MC_Stack1","MC_Stack1")
		MC_Stack1p = TH1D("Stack","Stack",3,500,1400)
		list_hist0 = []
		list_hist1 = []
		for proc in process_list:
			for path in pathlist :
				for fname in process_det[proc]:
					print(fname)
					chMC.Add(path+fname)#DYJetsTo*")
			histRatio, histMC0, histMC1, histllMC0, histllMC1, h_intMC = getDYHist(chMC,0,njcut,"MC_"+proc, year)
			histMC0.SetTitle(process_name[proc])
			histMC1.SetTitle(process_name[proc])
			histllMC0.SetTitle(process_name[proc])
			histllMC1.SetTitle(process_name[proc])
			h_intMC.SetTitle(process_name[proc])
			histMC0.SetFillColor(process_color[proc])
			histMC0.SetLineColor(kBlack);
			histMC1.SetFillColor(process_color[proc])
			histMC1.SetLineColor(kBlack);
			histllMC0.SetFillColor(process_color[proc])
			histllMC0.SetLineColor(kBlack);
			histllMC1.SetFillColor(process_color[proc])
			histllMC1.SetLineColor(kBlack);
			h_intMC.SetFillColor(process_color[proc])
			h_intMC.SetLineColor(kBlack);
			list_hist0.append(histMC0)
			list_hist1.append(histMC1)
			MC_Stack0.Add(histMC0)
			MC_Stack1.Add(histMC1)
			MCll_Stack0.Add(histllMC0)
			MCll_Stack1.Add(histllMC1)
			MC_Stack1p.Add(histMC1)
			MC_Stack_int.Add(h_intMC)
			MC_int.Add(h_intMC)
			print('process_name & yield: ', process_name[proc], h_intMC.Integral())
			chMC.Reset()
		for path in pathlist :
			chData.Add(path+"JetHT*")
			#chData.Add("/mnt/data3/babies/210910/"+year+"/JetHTRun_rpvfitnbge0_step3/*")
		histRatio, histData0, histData1, histllData0, histllData1, h_intData = getDYHist(chData,0,njcut, "Data0", year)
		kappa1, kappa2 = getKappa(histData0, histMC0) 
		SF_1bin = histData1.GetBinContent(1)/MC_Stack1p.GetBinContent(1)
		h_1bin_MC = MC_Stack1p.Clone("h_1bin_MC")
		h_1bin_MC.Scale(SF_1bin)
		h_cor = h_1bin_MC.Clone("h_cor")
		h_cor.SetBinContent(2, h_1bin_MC.GetBinContent(2)*kappa1)
		h_cor.SetBinContent(3, h_1bin_MC.GetBinContent(3)*kappa2)
		c = TCanvas("c","c",3200,800)
		c.Divide(4,1)
		c.cd(1)
		MC_Stack0.SetTitle("")
		MC_Stack0.SetMinimum(0.5)
		MC_Stack0.SetMaximum(histData0.GetMaximum()*5)
		MC_Stack0.Draw("hist")
		histData0.SetMarkerStyle(20)
		histData0.SetMarkerSize(1.2)
		histData0.SetLineColor(kBlack)
		histData0.Draw("same e0 x0")
		l0 = MakeLegend(list_hist0, histData0)
		l0.Draw("same")
		c.cd(1).SetLogy()
		c.cd(2)
		MC_Stack1.SetTitle("")
		MC_Stack1.SetMinimum(0.5)
		MC_Stack1.SetMaximum(histData1.GetMaximum()*5)
		MC_Stack1.Draw("hist")
		histData1.SetMarkerStyle(20)
		histData1.SetMarkerSize(1.2)
		histData1.SetLineColor(kBlack)
		histData1.Draw("same e0 x0")
		h_1bin_MC.SetLineColor(38)
		h_1bin_MC.Draw("same hist")
		h_cor.SetLineColor(46)
		h_cor.Draw("same hist")
		l1 = MakeLegend(list_hist1, histData1)
		l1.Draw("same")
		c.cd(2).SetLogy()
		c.cd(3)
		MCll_Stack0.SetTitle("")
		MCll_Stack0.SetMaximum(histllData0.GetMaximum()*1.3)
		histllData0.SetStats(0)
		MCll_Stack0.Draw("hist")
		histllData0.SetMarkerStyle(20)
		histllData0.SetMarkerSize(1.2)
		histllData0.SetLineColor(kBlack)
		histllData0.Draw("same e0 x0")
		c.cd(4)
		MCll_Stack1.SetTitle("")
		MCll_Stack1.SetMaximum(histllData1.GetMaximum()*1.3)
		histllData1.SetStats(0)
		MCll_Stack1.Draw("hist")
		histllData1.SetMarkerStyle(20)
		histllData1.SetMarkerSize(1.2)
		histllData1.SetLineColor(kBlack)
		histllData1.Draw("same e0 x0")
		c.Print("Figure_MJ/DY_mj12"+str(njcut)+"_"+str(year)+".pdf")
		c_int = TCanvas("c_int","c_int",800,800)
		c_int.SetMargin(0.13,0.05,0.12,0.1)
		c_int.Divide(1,2)
		line = TLine()
		line.SetLineColor(1)
		line.SetLineWidth(3)
		line.SetLineStyle(2)

		lt1 = ROOT.TLatex()
		lt1.SetTextAlign(12)
		lt1.SetTextFont(42)
		lt1.SetNDC()
		lt1.SetTextAngle(90)

		lt2 = ROOT.TLatex()
		lt2.SetTextAlign(12)
		lt2.SetTextFont(42)
		lt2.SetNDC()
		lt2.SetTextSize(0.058)

		lt3 = ROOT.TLatex()
		lt3.SetTextAlign(12)
		lt3.SetTextFont(52)
		lt3.SetNDC()
		lt3.SetTextSize(0.045)

		lt4 = ROOT.TLatex()
		lt4.SetTextAlign(32)
		lt4.SetTextFont(42)
		lt4.SetNDC()
		lt4.SetTextSize(0.05)

		top_pad = c_int.cd(1)
		top_pad.SetPad(0.02,0.3,0.98,0.98)
		top_pad.SetMargin(0.1,0.05,0,0.1)#left, right, bottom, top
		top_pad.SetTicks(1,1)
		MC_Stack_int.SetTitle("")
		MC_Stack_int.SetMinimum(0.5)
		MC_Stack_int.SetMaximum(histData0.GetMaximum()*7)
		#MC_Stack_int.GetXaxis().SetNdivisions(3)
		MC_Stack_int.Print("all")
		h_intData.SetMarkerStyle(20)
		h_intData.SetMarkerSize(1.2)
		h_intData.SetLineColor(kBlack)
		h_intData.Print("all")
		MC_Stack_int.Draw("hist")
		h_intData.Draw("e0 x0 same")
		l1 = MakeLegend(list_hist0, histData0)
		lt1.DrawLatex(0.04,0.76,"Events");
		lt2.DrawLatex(0.12,0.97,"CMS");
		lt3.DrawLatex(0.12+0.095,0.97-0.007,"Preliminary");
		lt4.DrawLatex(0.95,0.97, str(year)+" #sqrt{s} = 13 TeV");
		l1.Draw("same")
		top_pad.SetLogy()

		bottom_pad = c_int.cd(2)
		c_int.SetGridx()
		bottom_pad.SetPad(0.02,0.1,0.98,0.3)
		bottom_pad.SetMargin(0.1,0.05,0.34,0)
		#bottom_pad.SetTicks(1,1)
		histRatio = h_intData.Clone("histRatio")
		histRatio.Divide(MC_int)
		#histRatio.Sumw2()
		histRatio.SetTitle("")
		histRatio.GetYaxis().SetTitle("Data / MC")
		histRatio.GetYaxis().SetTitleSize(0.16)
		histRatio.GetYaxis().SetTitleOffset(0.22)
		histRatio.GetYaxis().SetRangeUser(0.2,1.8)
		histRatio.GetYaxis().SetNdivisions(4)
		histRatio.GetYaxis().CenterTitle()
		histRatio.GetYaxis().SetLabelSize(0.14)
		histRatio.GetXaxis().SetLabelSize(0.2)
		histRatio.GetXaxis().SetLabelOffset(0.04)
		histRatio.GetXaxis().SetTitleSize(0.12)
		histRatio.GetXaxis().SetTitleOffset(1.3)
		histRatio.GetXaxis().SetBinLabel(1,"500 \leq M_{J} \leq 800 GeV")#FIXME
		histRatio.GetXaxis().SetBinLabel(2,"800 \leq M_{J} \leq 1100 GeV")#FIXME
		histRatio.GetXaxis().SetBinLabel(3,"M_{J} \geq 1100 GeV")#FIXME
		histRatio.SetStats(0)
		histRatio.Draw("e0 x0")
		line.DrawLine(500,1,1400,1)
		c_int.Print("Figure_njets/DY_mj12_intnb_njets"+str(njcut)+"_"+str(year)+".pdf")		

		print('\n')
		print SF_1bin
		print kappa1
		print kappa2

if __name__ == '__main__':
	year=sys.argv[1]
	DY(totpath(year),3,year)
	DY(totpath(year),5,year)
	DY(totpath(year),7,year)


