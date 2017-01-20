#!/usr/bin/env python

import sys
import math
import ROOT 

ROOT.gStyle.SetPaintTextFormat("2.1f");
ROOT.gROOT.SetBatch(True)

############ input files ###########
variations_default="variations/sum_rescaled_mconly_beforerescale.root"
variations_loop="variations_loop/sum_rescaled_mconly_beforerescale.root" 
file_default = ROOT.TFile(variations_default,"READ")
file_loop = ROOT.TFile(variations_loop,"READ") 

variations = {'nominal','btag_bc', 'btag_udsg',
           'gs45', 'gs67', 'gs89', 'gs10Inf',
           'jes', 'jer',
           'lep_eff', 'ttbar_pt', #'pileup',
           'isr',
           'qcd_flavor',
           # the following are njet-dependent
           # versions of the previous variation
           #'qcd_flavor45', 'qcd_flavor67',
           #'qcd_flavor89', 'qcd_flavor10Inf',
           'qcd_mur', 'qcd_muf', 'qcd_murf',
           'ttbar_mur', 'ttbar_muf', 'ttbar_murf',
           'wjets_mur', 'wjets_muf', 'wjets_murf',
           'other_mur', 'other_muf', 'other_murf',
           'signal_mur', 'signal_muf', 'signal_murf'}

processes={"qcd","ttbar","wjets","other","signal_M1000","signal_M1500","signal_M2000"}

nbin=4*22;
nprocesses=len(processes);
ivariation=1;

for variation in variations: 
    hist_variation = ROOT.TH2D(variation,variation,2*nprocesses+1,0,2*nprocesses+1,nbin,0,nbin)
    iprocess=1;
    for process in processes: 
        for ibin in (0,1,2,3,4,5,10,11,12,13,14,15,16,17,18,19,20,21):  
            print "-"*43
            print "This is process %s bin %i"% (variation,ibin)
            print "-"*43
            if variation=="nominal":  # for nominal
                hist_variation.GetXaxis().SetBinLabel(iprocess,process)
                print process+":: "+variation
                hist_default = file_default.Get("bin"+str(ibin)+"/"+process) 
                hist_loop = file_loop.Get("bin"+str(ibin)+"/"+process)  
                for x in range(1, 5):
                    value_default=hist_default.GetBinContent(x+1)
                    value_loop=hist_loop.GetBinContent(x+1)
                    if value_default!=0: 
                        print "Nb=%i | %10.5f | %10.5f | %10.5f" % (x, value_default, value_loop, (value_default-value_loop)/value_default) 
                        hist_variation.SetBinContent(iprocess,ibin*4+x,(value_default-value_loop)/value_default*100)
                        hist_variation.GetYaxis().SetBinLabel(ibin*4+x,str(x))
            else: # for others
                hist_variation.GetXaxis().SetBinLabel(iprocess,process+" up")
                hist_variation.GetXaxis().SetBinLabel(iprocess+nprocesses+1,process+" down")
                ############ Up variation   ###########
                print process+":: "+variation+"Up"
                hist_default = file_default.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Up") 
                hist_loop = file_loop.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Up")  
                for x in range(1, 5):
                    value_default=hist_default.GetBinContent(x+1)
                    value_loop=hist_loop.GetBinContent(x+1)
                    if value_default!=0: 
                        print "Nb=%i | %10.4f | %10.4f | %10.4f" % (x, value_default, value_loop, (value_default-value_loop)/value_default) 
                        hist_variation.SetBinContent(iprocess,ibin*4+x,(value_default-value_loop)/value_default*100)
                        hist_variation.GetYaxis().SetBinLabel(ibin*4+x,str(x))
                ############ Down variation  ###########
                print process+":: "+variation+"Down"
                hist_default = file_default.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Down") 
                hist_loop = file_loop.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Down")  
                for x in range(1, 5):
                    value_default=hist_default.GetBinContent(x+1)
                    value_loop=hist_loop.GetBinContent(x+1)
                    if value_default!=0: 
                        print "Nb=%i | %10.4f | %10.4f | %10.4f" % (x, value_default, value_loop, (value_default-value_loop)/value_default) 
                        hist_variation.SetBinContent(iprocess+nprocesses+1,ibin*4+x,(value_default-value_loop)/value_default*100)
                        hist_variation.GetYaxis().SetBinLabel(ibin*4+x,str(x))
        print "-"*43
        iprocess=iprocess+1
    
    #### Draw summary plot ####
    c = ROOT.TCanvas("c_"+variation,"c_"+variation,500,1000)
    c.SetGrid()
    c.cd()
    hist_variation.SetMarkerSize(0.6)
    hist_variation.SetMinimum(-1)
    hist_variation.SetMaximum(1)
    hist_variation.SetStats(0)
    hist_variation.Draw("colz text")
    c.Print("plots/validate_variations/"+variation+".pdf") 
    c.Print("plots/validate_variations/"+variation+".png") 
