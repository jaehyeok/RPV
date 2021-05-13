import sys
import ROOT
from ROOT import TFile, TH1, TF1, TChain, TCanvas, TH2D
import multiprocessing as mp
from functools import partial

##path = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_norm_noMJ/"

def eventloop(ch,TH2_FLR,year,dat,cores,itr):
        ROOT.ROOT.EnableImplicitMT(40)
        njets_list = [4,6,8]
        lep_iso = 0
        lep_id = 0
        ety_start = int((itr-1)/cores*ch.GetEntries())
        ety_end = int(itr/cores*ch.GetEntries())
	lumi=0.0
	if dat : lumi=1.0
	elif year=="2016" : lumi=35.9
	elif year=="2017" : lumi=41.5
	elif year=="2018" : lumi=59.7
        for iety in range(ety_start,ety_end):
		reg_nj=999;
		perc=""
		perc = "\r{:4.2f} % ".format(float(iety)/float(ch.GetEntries())*100.00)
		if iety%int(ch.GetEntries()/10000)==0 :
			sys.stdout.write(perc)
			sys.stdout.flush()
                ch.GetEntry(iety)
                if ch.ht<1200 :continue
                if ch.nbm!=0 :continue
                if ch.met>50 : continue

                if ch.njets==3 or ch.njets==4 : reg_nj=0;
                elif ch.njets==5 or ch.njets==6 : reg_nj=1;
                elif ch.njets>=8 : reg_nj=2;
		else : continue;
                for iels in range(0,len(ch.els_pt)) :
                        leps_iso=0
                        leps_id=0
                        if ch.els_pt.at(iels) < 20 : continue
                        if abs(ch.els_eta.at(iels)) > 2.5 : continue
                        if ch.els_miniso.at(iels) < 0.1 : leps_iso=1
                        if ch.els_sigid.at(iels) : leps_id=1
                        TH2_FLR[reg_nj].Fill(leps_iso,leps_id,lumi*ch.weight)
                for imus in range(0,len(ch.mus_pt)) :
                        leps_iso=0
                        leps_id=0
                        if ch.mus_pt.at(imus) < 20 : continue
                        if abs(ch.mus_eta.at(imus)) > 2.4 : continue
                        if ch.mus_miniso.at(imus) < 0.2 : leps_iso=1
                        if ch.mus_sigid.at(imus) : leps_id=1
                        TH2_FLR[reg_nj].Fill(leps_iso,leps_id,lumi*ch.weight)
	##	sys.stdout.write(perc+"%")
        return TH2_FLR


if __name__=='__main__':
	year = sys.argv[1]
	path = "/data2/babies/20210430/"+year+"/merged_norm/"
	path_dat = "/data2/babies/20210430/"+year+"/skim_rpvfitnbge0_nbm2/"
        ch_bkg = TChain("tree")
        ch_bkg.Add(path+"DYJets*")
        ch_bkg.Add(path+"TTJets_HT*")
        ch_bkg.Add(path+"WJetsToLNu*")
        ch_bkg.Add(path+"DYJetsToLL_M-50_HT*")
        ch_bkg.Add(path+"TTTT*")
        ch_bkg.Add(path+"TTW*")
        ch_bkg.Add(path+"TTZ*")
        ch_bkg.Add(path+"WZ_*")
        ch_bkg.Add(path+"ZZ_*")
        ch_bkg.Add(path+"WW_*")
        ch_bkg.Add(path+"WWZ_*")
        ch_bkg.Add(path+"WZZ_*")
        ch_bkg.Add(path+"ZZZ_*")
        ch_bkg.Add(path+"WWW_*")
        tot_ety = ch_bkg.GetEntries()
        TH2_FLR_bkg_lnj = TH2D("FLR_bkg_lnj","FLR_bkg_lnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_bkg_mnj = TH2D("FLR_bkg_mnj","FLR_bkg_mnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_bkg_hnj = TH2D("FLR_bkg_hnj","FLR_bkg_hnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
	TH2_FLR_bkg = [TH2_FLR_bkg_lnj, TH2_FLR_bkg_mnj, TH2_FLR_bkg_hnj]
	TH2_FLR_bkg = eventloop(ch_bkg,TH2_FLR_bkg,year,False,1,1)

	ch_qcd = TChain("tree")
	ch_qcd.Add(path+"QCD_*")
	tot_ety = ch_qcd.GetEntries()
        TH2_FLR_qcd_lnj = TH2D("FLR_qcd_lnj","FLR_qcd_lnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_qcd_mnj = TH2D("FLR_qcd_mnj","FLR_qcd_mnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_qcd_hnj = TH2D("FLR_qcd_hnj","FLR_qcd_hnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
	TH2_FLR_qcd = [TH2_FLR_qcd_lnj, TH2_FLR_qcd_mnj, TH2_FLR_qcd_hnj]
	TH2_FLR_qcd = eventloop(ch_qcd,TH2_FLR_qcd,year,False,1,1)

	ch_dat = TChain("tree")
	ch_dat.Add(path_dat+"*JetHT*")
        TH2_FLR_dat_lnj = TH2D("FLR_dat_lnj","FLR_dat_lnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_dat_mnj = TH2D("FLR_dat_mnj","FLR_dat_mnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
        TH2_FLR_dat_hnj = TH2D("FLR_dat_hnj","FLR_dat_hnj",2,0,2,2,0,2) # x axis : lep_iso, y axis = lep_id
	TH2_FLR_dat = [TH2_FLR_dat_lnj, TH2_FLR_dat_mnj, TH2_FLR_dat_hnj]
	TH2_FLR_dat = eventloop(ch_dat,TH2_FLR_dat,year,True,1,1)

	c = TCanvas("c","c",3200,2400)
	c.Divide(4,3)
	f = TFile("result_fakelepton_"+year+"_nb0.root","recreate")
	TH2_FLR_qcdat=[]
	TH2_FLR_rat=[]
	for i in range(0,3):
		c.cd(4*i+1)
		TH2_FLR_bkg[i].SetStats(0)
		TH2_FLR_bkg[i].Draw("text colz")
		TH2_FLR_bkg[i].Write()
		c.cd(4*i+2)
		TH2_FLR_qcd[i].SetStats(0)
		TH2_FLR_qcd[i].Draw("text colz")
		TH2_FLR_qcd[i].Write()
		c.cd(4*i+3)
		TH2_FLR_dat[i].SetStats(0)
		TH2_FLR_dat[i].Draw("text colz")
		TH2_FLR_dat[i].Write()
		c.cd(4*i+4)
		TH2_FLR_qcdat.append(TH2_FLR_dat[i].Clone("TH2_FLR_qcdat"+str(i)))
		TH2_FLR_qcdat[i].Add(TH2_FLR_bkg[i],-1)
		TH2_FLR_rat.append(TH2_FLR_qcdat[i].Clone("TH2_FLR_rat_"+str(i)))
		TH2_FLR_rat[i].Divide(TH2_FLR_qcd[i])
		TH2_FLR_rat[i].SetStats(0)
		TH2_FLR_rat[i].Draw("text colz")
		TH2_FLR_rat[i].Write()
	c.Print("result_fakelepton_"+year+"_nb0.pdf")
	c.Print("result_fakelepton_"+year+"_nb0.C")
'''
	for itr in range(1,cores+1):
		proc = mp.Process(target=eventloop, args=(ch_bkg,TH2_FLR,cores,itr))
		procs.append(proc)
		proc.start()
	

	for proc in procs :
		proc.join()
'''
'''
        pool = mp.Pool(cores)
        func_merged = partial(eventloop,ch_bkg,TH2_FLR,cores)
        pool.map(func_merged,[1,2,3,4])
        pool.close()
        pool.join()
'''
