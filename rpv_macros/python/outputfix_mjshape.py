import ROOT
from ROOT import *
import sys

if __name__=="__main__":
    year = sys.argv[1]
    if year=="2016": f_orig = TFile("variations/output_nominal_newnt_"+year+".root", "READ") #2016
    elif year=="2017" or year=="2018": f_orig = TFile("variations/output_nominal_newnt_"+year+"_20178.root", "READ") #2017,2018
    f_modi = TFile("variations/output_"+year+"_mjsyst.root","RECREATE")
    f_ttbar = TFile("plots/mjsyst/"+year+"/mjsyst_ttbar_"+year+".root","READ")
    f_wjets = TFile("plots/mjsyst/"+year+"/mjsyst_wjets_"+year+".root","READ")
    
    for i in range(22,52):
            if year == "2017" or year == "2018": year="20178"
            injets	= (i-1)%3
            inb	= int((i-22)/3+1)
            ind_njets = 10*(2*injets+4)+2*injets+5
            if ind_njets==89: ind_njets=8
            
            ttbar_r1   = f_ttbar.Get("h1_ttbar_njet"+str(ind_njets)+"_norm_r1")
            ttbar_r2   = f_ttbar.Get("h1_ttbar_njet"+str(ind_njets)+"_norm_r2")
            wjets_r1   = f_wjets.Get("h1_wjets_njet"+str(ind_njets)+"_norm_r1")
            wjets_r2   = f_wjets.Get("h1_wjets_njet"+str(ind_njets)+"_norm_r2")
            
            f_modi.cd()
            gDirectory.mkdir("bin"+str(i))
            
            h_proc_qcd = TH1F(f_orig.Get("bin"+str(i)+"/qcd"))
            h_proc_ttbar = TH1F(f_orig.Get("bin"+str(i)+"/ttbar"))
            h_proc_wjets = TH1F(f_orig.Get("bin"+str(i)+"/wjets"))
            h_mc_qcd = h_proc_qcd.Clone("h_mc_qcd")
            h_mc_ttbar = h_proc_ttbar.Clone("h_mc_ttbar")
            h_mc_wjets = h_proc_wjets.Clone("h_mc_wjets")
            
            cor_ttbar_r1	= ttbar_r1.GetBinContent(inb)
            cor_ttbar_r2	= ttbar_r2.GetBinContent(inb)
            cor_wjets_r1	= wjets_r1.GetBinContent(inb)
            cor_wjets_r2	= wjets_r2.GetBinContent(inb)
            print("bin"+str(i))
            
            qcd_mc_r1_up	    = h_proc_qcd.Clone("qcd_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Up")
            qcd_mc_r1_down    = h_proc_qcd.Clone("qcd_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Down")
            qcd_mc_r2_up	    = h_proc_qcd.Clone("qcd_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Up")
            qcd_mc_r2_down    = h_proc_qcd.Clone("qcd_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Down")
            ttbar_mc_r1_up	    = h_mc_ttbar.Clone("ttbar_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Up")
            ttbar_mc_r1_down    = h_mc_ttbar.Clone("ttbar_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Down")
            ttbar_mc_r2_up	    = h_mc_ttbar.Clone("ttbar_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Up")
            ttbar_mc_r2_down    = h_mc_ttbar.Clone("ttbar_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Down")
            wjets_mc_r1_up	    = h_mc_wjets.Clone("wjets_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Up")
            wjets_mc_r1_down    = h_mc_wjets.Clone("wjets_mjsyst_r1_njets"+str(ind_njets)+"_"+year+"Down")
            wjets_mc_r2_up    = h_mc_wjets.Clone("wjets_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Up")
            wjets_mc_r2_down    = h_mc_wjets.Clone("wjets_mjsyst_r2_njets"+str(ind_njets)+"_"+year+"Down")

            if(i>36): continue;
            else:
                ttbar_mc_r1_up.SetBinContent(2, ttbar_mc_r1_up.GetBinContent(2)+ttbar_mc_r1_up.GetBinContent(2)*(cor_ttbar_r1-1));
                ttbar_mc_r1_down.SetBinContent(2, ttbar_mc_r1_down.GetBinContent(2)+ttbar_mc_r1_down.GetBinContent(2)*(1-cor_ttbar_r1));
                ttbar_mc_r2_up.SetBinContent(3, ttbar_mc_r2_up.GetBinContent(3)+ttbar_mc_r2_up.GetBinContent(3)*(cor_ttbar_r2-1));
                ttbar_mc_r2_down.SetBinContent(3, ttbar_mc_r2_down.GetBinContent(3)+ttbar_mc_r2_down.GetBinContent(3)*(1-cor_ttbar_r2));
                wjets_mc_r1_up.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2)+wjets_mc_r1_up.GetBinContent(2)*(cor_wjets_r1-1));
                wjets_mc_r1_down.SetBinContent(2, wjets_mc_r1_down.GetBinContent(2)+wjets_mc_r1_down.GetBinContent(2)*(1-cor_wjets_r1));
                wjets_mc_r2_up.SetBinContent(3, wjets_mc_r2_up.GetBinContent(3)+wjets_mc_r2_up.GetBinContent(3)*(cor_wjets_r2-1));
                wjets_mc_r2_down.SetBinContent(3, wjets_mc_r2_down.GetBinContent(3)+wjets_mc_r2_down.GetBinContent(3)*(1-cor_wjets_r2));
                # The lines below are needed to prevent that the yields of ttbar and wjets are negative values
                if(ttbar_mc_r1_down.GetBinContent(2) < 0):
                    ttbar_mc_r1_down.SetBinContent(2, 0)
                if(ttbar_mc_r2_down.GetBinContent(3) < 0):
                    ttbar_mc_r2_down.SetBinContent(3, 0)
                if(wjets_mc_r1_down.GetBinContent(2) < 0):
                    wjets_mc_r1_down.SetBinContent(2, 0)
                if(wjets_mc_r2_down.GetBinContent(3) < 0):
                    wjets_mc_r2_down.SetBinContent(3, 0)

            print("bin "+str(i))
            print("ttbar_mc_r1_up: "+str(ttbar_mc_r1_up.GetBinContent(2)))
            print("ttbar_mc_r1_down: "+str(ttbar_mc_r1_down.GetBinContent(2)))
            print("ttbar_mc_r2_up: "+str(ttbar_mc_r2_up.GetBinContent(3)))
            print("ttbar_mc_r2_down: "+str(ttbar_mc_r2_down.GetBinContent(3)))
            print("wjets_mc_r1_up: "+str(wjets_mc_r1_up.GetBinContent(2)))
            print("wjets_mc_r1_down: "+str(wjets_mc_r1_down.GetBinContent(2)))
            print("wjets_mc_r2_up: "+str(wjets_mc_r2_up.GetBinContent(3)))
            print("wjets_mc_r2_down: "+str(wjets_mc_r2_down.GetBinContent(3)))
            '''
            if (i>=25 and i<28):
                if (cor_wjets_r1 <= 1 or cor_wjets_r2 <= 1):
                    wjets_mc_r1_down.SetBinContent(2, wjets_mc_r1_down.GetBinContent(2)*cor_wjets_r1)
                    wjets_mc_r2_down.SetBinContent(3, wjets_mc_r2_down.GetBinContent(3)*cor_wjets_r2)
                else:
                    wjets_mc_r1_up.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2)*cor_wjets_r1)
                    wjets_mc_r2_up.SetBinContent(3, wjets_mc_r2_up.GetBinContent(3)*cor_wjets_r2)
            elif (i>=28):
                if (cor_wjets_r1 <= 1 or cor_wjets_r2 <= 1):
                    wjets_mc_r1_down.SetBinContent(2, wjets_mc_r1_down.GetBinContent(2)*cor_wjets_r1)
                    wjets_mc_r2_down.SetBinContent(3, wjets_mc_r2_down.GetBinContent(3)*cor_wjets_r2)
                if (cor_ttbar_r1 <= 1 or cor_ttbar_r2 <= 1):
                    ttbar_mc_r1_down.SetBinContent(2, ttbar_mc_r1_down.GetBinContent(2)*cor_ttbar_r1)
                    ttbar_mc_r2_down.SetBinContent(3, ttbar_mc_r2_down.GetBinContent(3)*cor_ttbar_r2)
                if (cor_wjets_r1 > 1 or cor_wjets_r2 > 1):
                    wjets_mc_r1_up.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2)*cor_wjets_r1)
                    wjets_mc_r2_up.SetBinContent(3, wjets_mc_r2_up.GetBinContent(3)*cor_wjets_r2)
                if (cor_ttbar_r1 > 1 or cor_ttbar_r2 > 1):
                    ttbar_mc_r1_up.SetBinContent(2, ttbar_mc_r1_up.GetBinContent(2)*cor_ttbar_r1)
                    ttbar_mc_r2_up.SetBinContent(3, ttbar_mc_r2_up.GetBinContent(3)*cor_ttbar_r2)
            '''
            ''' 
            if cor_ttbar_r1==0 or cor_ttbar_r2==0 or cor_wjets_r1==0 or cor_wjets_r2==0
               or cor_ttbar_r1==1 or cor_ttbar_r2==1 or cor_wjets_r1==1 or cor_wjets_r2==1:
                ttbar_mc_r1_up.SetBinContent(2, ttbar_mc_r1_up.GetBinContent(2))
                ttbar_mc_r1_down.SetBinContent(2, ttbar_mc_r1_up.GetBinContent(2))
                ttbar_mc_r2_up.SetBinContent(3, ttbar_mc_r1_up.GetBinContent(3))
                ttbar_mc_r2_down.SetBinContent(3, ttbar_mc_r1_up.GetBinContent(3))
                wjets_mc_r1_up.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2))
                wjets_mc_r1_down.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2))
                wjets_mc_r2_up.SetBinContent(3, wjets_mc_r1_up.GetBinContent(3))
                wjets_mc_r2_down.SetBinContent(3, wjets_mc_r1_up.GetBinContent(3))
            
            else:
                ttbar_mc_r1_up.SetBinContent(2, ttbar_mc_r1_up.GetBinContent(2)*cor_ttbar_r1)
                ttbar_mc_r1_down.SetBinContent(2, tent(2)-ttbar_mc_r1_down.GetBinContent(2)*(1-cor_ttbar_r1))
                ttbar_mc_r2_up.SetBinContent(3, ttbar_mc_r2_up.GetBinContent(3)+ttbar_mc_r2_up.GetBinContent(3)*(1-cor_ttbar_r2))
                ttbar_mc_r2_down.SetBinContent(3, ttbar_mc_r2_down.GetBinContent(3)-ttbar_mc_r2_down.GetBinContent(3)*(1-cor_ttbar_r2))
                wjets_mc_r1_up.SetBinContent(2, wjets_mc_r1_up.GetBinContent(2)+wjets_mc_r1_up.GetBinContent(2)*(1-cor_wjets_r1))
                wjets_mc_r1_down.SetBinContent(2, wjets_mc_r1_down.GetBinContent(2)-wjets_mc_r1_down.GetBinContent(2)*(1-cor_wjets_r1))
                wjets_mc_r2_up.SetBinContent(3, wjets_mc_r2_up.GetBinContent(3)+wjets_mc_r2_up.GetBinContent(3)*(1-cor_wjets_r2))
                wjets_mc_r2_down.SetBinContent(3, wjets_mc_r2_down.GetBinContent(3)-wjets_mc_r2_down.GetBinContent(3)*(1-cor_wjets_r2))
            '''
            
            f_modi.cd()
            gDirectory.cd("bin"+str(i)+"/")
            qcd_mc_r1_up.Write()
            qcd_mc_r1_down.Write()
            qcd_mc_r2_up.Write()
            qcd_mc_r2_down.Write()
            ttbar_mc_r1_up.Write()
            ttbar_mc_r1_down.Write()
            ttbar_mc_r2_up.Write()
            ttbar_mc_r2_down.Write()
            wjets_mc_r1_up.Write()
            wjets_mc_r1_down.Write()
            wjets_mc_r2_up.Write()
            wjets_mc_r2_down.Write()
            
    
    	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
