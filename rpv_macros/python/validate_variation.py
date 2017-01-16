#!/usr/bin/env python

import sys
import math
import ROOT 

#variations_default="variations/sum_rescaled_mconly.root"
#variations_loop="variations_loop/sum_rescaled_mconly.root"
variations_default="variations/output_qcd_flavor.root"
variations_loop="variations_loop/output_qcd_flavor.root" 

variations={"qcd_flavor"}
processes={"qcd","ttbar","wjets","other","signal_M1500"}

file_default = ROOT.TFile(variations_default,"READ")
file_loop = ROOT.TFile(variations_loop,"READ")

for process in processes: 
    for variation in variations: 
        for ibin in range(0,1): 

            ############ skip bin = 6-9 ###########
            if ibin>=6 and ibin<=9: 
                break

            ############ Up variation   ###########
            print process+", "+variation+"Up"
            hist_default = file_default.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Up") 
            hist_loop = file_loop.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Up")  
            for x in range(1, 5):
                value_default=hist_default.GetBinContent(x+1)
                value_loop=hist_loop.GetBinContent(x+1)
                if value_default!=0: 
                    print "Nb=%i | %10.2f | %10.2f | %10.4f" % (x, value_default, value_loop, (value_default-value_loop)/value_default)
            
            ############ Down variation  ###########
            print process+", "+variation+"Down"
            hist_default = file_default.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Down") 
            hist_loop = file_loop.Get("bin"+str(ibin)+"/"+process+"_"+variation+"Down")  
            for x in range(1, 5):
                value_default=hist_default.GetBinContent(x+1)
                value_loop=hist_loop.GetBinContent(x+1)
                if value_default!=0: 
                    print "Nb=%i | %10.2f | %10.2f | %10.4f" % (x, value_default, value_loop, (value_default-value_loop)/value_default)
