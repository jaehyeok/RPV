#!/usr/bin/env python """This script plots signal systematics for the RPV analysis"""
import sys
import math
import ROOT
from array import array
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input")
parser.add_argument("-m", "--mass")
parser.add_argument("-y", "--year")
parser.add_argument("-c", "--combine_year")
args = parser.parse_args()
GLUINOMASS = 1800
Year = 2016
if (args.input):
  infile = args.input
else:
  sys.exit("Please provide an input root file")
if (args.mass):
  GLUINOMASS = args.mass
if (args.year):
  Year = args.year
if (args.combine_year):
  Comb_year = args.combine_year

one_pdf = False #put all plots in one pdf file
verbose = True  


# function to get pointers to histogram in root file
def get_hist_with_overflow(file,histname):
    if verbose:
        print(" getting "+histname)
    hist = file.Get(histname)
    nbinsX = hist.GetNbinsX()
    content = hist.GetBinContent(nbinsX) + hist.GetBinContent(nbinsX+1)
    error  = math.sqrt(math.pow(hist.GetBinError(nbinsX),2) + math.pow(hist.GetBinError(nbinsX+1),2))
    hist.SetBinContent(nbinsX,content)
    hist.SetBinContent(nbinsX+1,0) #avoid adding overflow N times for N calls to function
    hist.SetBinError(nbinsX+1,0)
    hist.SetBinError(nbinsX,error)
    return hist

#This function calculates symmetrized relative errors for a single variation in a single kinematic bin
#Return a histogram binned in Nb with the mean of the absolute value of relative errors up and down
def get_symmetrized_relative_errors(sysName,nominal,proc,sysFile,directory):


    # total hists for each variation, to include all processes
    systHistUp = ROOT.TH1F(directory+"_"+sysName+"_u","",3,500,1400)
    systHistDown = ROOT.TH1F(directory+"_"+sysName+"_d","",3,500,1400)
  
    #load hists and calculate SFs for floating component for each variation

    if sysName=='CMS_btag_fixedWP_comb_bc_uncorrelated' or sysName=='CMS_btag_fixedWP_incl_light_uncorrelated' or sysName=='CMS_res_j' or sysName=='CMS_scale_j' or sysName=='CMS_pileup' or sysName=='CMS_eff_e' or sysName=='CMS_eff_m':
        if str(Comb_year)=='2016':
            up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Up")
            down = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Down")
        elif str(Comb_year)=='1718':
            up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Up")
            down = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Down")
    elif sysName=='QCDscale_ren' or sysName=='QCDscale_fac' or sysName=='QCDscale':
        up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_t1tbsUp")
        down = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_t1tbsDown")
    elif sysName=='CMS_gs' or sysName=='CMS_btag_fixedWP_comb_bc_correlated' or sysName=='CMS_btag_fixedWP_incl_light_correlated':
        up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "Up")
        down = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "Down")
    else:
        up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Comb_year) + "Up")
        down = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Comb_year) + "Down")

#    up = get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Up")
#    down =  get_hist_with_overflow(sysFile,directory + "/" + proc + "_" + sysName + "_" + str(Year) + "Down")

    #Put yields in new histogram to avoid modifying originals
    systHistUp.Add(up)
    systHistDown.Add(down)

    #Subtract nominal histogram from varied histograms
    systHistUp.Add(nominal,-1)     
    systHistDown.Add(nominal,-1)

    for i in range(1,systHistUp.GetNbinsX()+1):
        #Find absolute value of deviation
        systHistUp.SetBinContent(i,abs(systHistUp.GetBinContent(i)))
        systHistDown.SetBinContent(i,abs(systHistDown.GetBinContent(i)))

    #Fill histUp with symmetrized error by adding histDown and dividing by 2, then divide by nominal to get relative symmetrized error    
    systHistUp.Add(systHistDown)
    systHistUp.Scale(0.5)
    systHistUp.Divide(nominal) # now systHistUp contains our relative errors
    return systHistUp

def set_palette_gray(ncontours=20):
    #stops = [0.00, 0.25, 0.50, 0.75, 1.00]
    stops = [0.00, 0.10, 0.50, 0.90, 1.00]
    red   = [1.00, 0.80, 0.65, 0.50, 0.34]
    green = [1.00, 0.80, 0.65, 0.50, 0.34]
    blue  = [1.00, 0.80, 0.65, 0.50, 0.34]
    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)
    npoints = len(s)
    fi = ROOT.TColor.CreateGradientColorTable(npoints, s, r, g, b, ncontours)
    ROOT.gStyle.SetNumberContours(ncontours)


ROOT.gROOT.SetBatch(ROOT.kTRUE) #prevent th1->Draw() from trying to open X11 window
ROOT.gStyle.SetCanvasDefW(600)
ROOT.gStyle.SetCanvasDefH(600)
ROOT.gStyle.SetTitleOffset(1.2,"x") 
#ROOT.gStyle.SetTitleOffset(1.7,"y")
ROOT.gStyle.SetTitleOffset(1.7,"z") 
#ROOT.gStyle.SetPadRightMargin(0.19) 
ROOT.gStyle.SetPadLeftMargin(0.12)
ROOT.gStyle.SetPadBottomMargin(0.12)
ROOT.gStyle.SetPadTopMargin(0.08)
ROOT.gStyle.SetPaintTextFormat("6.1f");


ROOT.gStyle.SetLabelFont(42)
ROOT.gStyle.SetLabelSize(0.05)
ROOT.gStyle.SetTitleFont(42)
ROOT.gStyle.SetTitleSize(0.07)

#set_palette()
set_palette_gray()

#make list of systematics- name, title, plot color and line style
systList=[]
systList.append(["CMS_gs","Gluon splitting",4,1])
systList.append(["CMS_pileup","Pileup",10,1])
systList.append(["CMS_btag_fixedWP_comb_bc_uncorrelated","#splitline{ Across-year uncorrelated}{                b,c jet b-tag SF}",5,1])
systList.append(["CMS_btag_fixedWP_comb_bc_correlated","#splitline{Across-year correlated}{           b,c jet b-tag SF}",5,1])
systList.append(["CMS_btag_fixedWP_incl_light_uncorrelated","#splitline{Across-year uncorrelated}{         u,d,s,g jet b-tag SF}",6,1])
systList.append(["CMS_btag_fixedWP_incl_light_correlated","#splitline{Across-year correlated}{     u,d,s,g jet b-tag SF}",6,1])
systList.append(["CMS_scale_j","Jet energy scale",7,1])
systList.append(["CMS_res_j","Jet energy resolution",7,1])
systList.append(["CMS_eff_e","Electron efficiency",9,1])
systList.append(["CMS_eff_m","Muon efficiency",9,1])
#systList.append(["isr","Initial state radiation",11,1])
systList.append(["QCDscale_ren","Renormalization scale",16,1])
systList.append(["QCDscale_fac","Factorization scale",17,1])
systList.append(["QCDscale","Renorm. and fact. scale",18,1])
systList.append(["mc_stat","MC statistics",1,2]) #must be done last!

nSyst = len(systList)
#make list of bins

binList = []
binList.append(["bin22","4 #leq n_{jets} #leq 5","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin23","6 #leq n_{jets} #leq 7","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin24","n_{jets} #geq 8","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin25","4 #leq n_{jets} #leq 5","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin26","6 #leq n_{jets} #leq 7","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin27","n_{jets} #geq 8","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin28","4 #leq n_{jets} #leq 5","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin29","6 #leq n_{jets} #leq 7","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin30","n_{jets} #geq 8","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin31","4 #leq n_{jets} #leq 5","M_{J} > 500 GeV","n_{lep} = 1"])
# signal regions
binList.append(["bin32","6 #leq n_{jets} #leq 7","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin33","n_{jets} #geq 8","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin35","6 #leq n_{jets} #leq 7","M_{J} > 500 GeV","n_{lep} = 1"])
binList.append(["bin36","n_{jets} #geq 8","M_{J} > 500 GeV","n_{lep} = 1"])


sysFile = ROOT.TFile(infile,"read")
proc = "signal_M" + str(GLUINOMASS)


for ibin in binList: 

    directory = ibin[0]
    if verbose:
        print( "directory is "+directory)
    
    nominal = get_hist_with_overflow(sysFile,(directory + "/" + proc))
    nbinsX = nominal.GetNbinsX()
    

    ROOT.gStyle.SetPadRightMargin()
    ROOT.gStyle.SetPadLeftMargin(0.12) #so it's not messed by larger table margin each iteration of the loop
    c = ROOT.TCanvas()
    leg = ROOT.TLegend(0.12,0.7,0.54,0.92)

    table = ROOT.TH2F("table_"+directory,"",nbinsX,500,1400,nSyst+1,0,nSyst+1) #nSyst"+1" for total unc.
    systHists_sym = []

    
    for isys, syst in enumerate(systList,start=1):
        sysName = syst[0]
        systHist = ROOT.TH1F(directory+"_"+sysName+"_sym","",3,500,1400) # will eventually contain errors; define now to remain in scope
        if verbose:
            print( "starting "+sysName)

        if "mc_stat" not in sysName:
            #pdf treated separately
            if "pdf" not in sysName:
                #this function does everything
                systHist = get_symmetrized_relative_errors(sysName,nominal,proc,sysFile,directory)
            
                    
            elif "pdf" in sysName:
                #This systematic is calculated from 100 variations that all represent a single source of uncertainty.
                #We want to use information from all variations without artifically inflating the total uncertainty just by sampling the same effect many times.
                #Therefore, we find symmetrized uncertainties for each pdf variation up/down, add them in quadrature and divide by sqrt(100) to normalize
                for i in range(0,100):
                    #if i == 9 : continue 
                    #Get errors for this pdf variation
                    thisvar = get_symmetrized_relative_errors("w_pdf"+str(i),nominal,proc,sysFile,directory)
                    #Add in quadrature to running total
                    for i in range(1,systHist.GetNbinsX()+1):
                        thisvar.SetBinContent(i,math.pow(thisvar.GetBinContent(i),2))
                    systHist.Add(thisvar)
                
                #take square root and normalize by sqrt(100)
                for i in range(1,systHist.GetNbinsX()+1):
                        systHist.SetBinContent(i,math.pow(systHist.GetBinContent(i),0.5)/10)
                           
            
        elif "mc_stat" in sysName:
            systHist.Add(nominal)
            for i in range(1,systHist.GetNbinsX()+1):
                #in this case, we want our relative errors to just be the MC errors
                if systHist.GetBinContent(i)>0:
                    systHist.SetBinContent(i,(systHist.GetBinError(i)/systHist.GetBinContent(i))) 

        #normalize to percentage for humans            
        for i in range(1,systHist.GetNbinsX()+1):
            if systHist.GetBinContent(i) < 0.001: 
                table.SetBinContent(i,isys,0.04)
            else: 
                table.SetBinContent(i,isys,round(100*systHist.GetBinContent(i),1))
            if verbose:
                print( "symmetrized rel error bin "+str(i)+" "+str(systHist.GetBinContent(i)))


        systHists_sym.append(systHist)


        table.GetYaxis().SetBinLabel(isys,syst[1])
        systHists_sym[isys-1].SetTitle(";M_{J};Relative Error")
        systHists_sym[isys-1].SetLineColor(syst[2])
        systHists_sym[isys-1].SetLineStyle(syst[3])
        systHists_sym[isys-1].SetLineWidth(2)
        systHists_sym[isys-1].SetMaximum(0.4)
        systHists_sym[isys-1].SetMinimum(0.)
        systHists_sym[isys-1].SetAxisRange(1,4,"X")
        systHists_sym[isys-1].SetStats(0)
        systHists_sym[isys-1].GetYaxis().SetTitleOffset(1.4)
        systHists_sym[isys-1].GetYaxis().SetTitleSize(0.04)
        systHists_sym[isys-1].GetXaxis().SetTitleSize(0.04)
        systHists_sym[isys-1].GetXaxis().SetNdivisions(505)
        leg.AddEntry(systHists_sym[isys-1],syst[1],"l")
        systHists_sym[isys-1].Draw("hist same")  


    leg.Draw()
    tla = ROOT.TLatex()
    tla.SetTextSize(0.038)
    #tla.DrawLatexNDC(0.12,0.93,"#font[62]{CMS} #scale[0.8]{#font[52]{Work In Progress}}")
    tla.DrawLatexNDC(0.20,0.93,"#font[62]{CMS} #font[52]{Preliminary}")
    tla.SetTextFont(42)
    if str(Comb_year)=='2016':
        tla.DrawLatexNDC(0.66,0.93,"36.3 fb^{-1}")
    elif str(Comb_year)=='1718':
        tla.DrawLatexNDC(0.80,0.93,"101 fb^{-1}")
#    tla.SetTextSize(0.045)
    tla.DrawLatexNDC(0.17, 0.65, ibin[3])
    tla.DrawLatexNDC(0.17, 0.6, ibin[1])
    tla.DrawLatexNDC(0.17, 0.55, ibin[2])
    if one_pdf:
        if directory == binList[0][0]:
            outname = "plots/rpv_sig_syst/" + str(Year) + "/sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf("
        elif directory == binList[len(binList)-1][0]:
            outname = "plots/rpv_sig_syst/" + str(Year) + "sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf)"
        else:
            outname = "plots/rpv_sig_syst/" + str(Year) + "/sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf"

    else:
         outname = "plots/rpv_sig_syst/" + str(Year) + "/sig_systs_" + directory + "_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf"
    print( "outname is " +outname)
    c.Print(outname)

    integral_tot_systHist = ROOT.TH1F("integral_tot_systHist","",3,500,1400)
    for i in range (1, systHist.GetNbinsX()+1):
        for j in range(1, len(systHists_sym)+1):
            integral_tot_systHist.SetBinContent(i, math.sqrt(integral_tot_systHist.GetBinContent(i)*integral_tot_systHist.GetBinContent(i)+table.GetBinContent(i,j)*table.GetBinContent(i,j)))

    # change the order of systs
    for i in range(nSyst, 0, -1):
        for j in range(1,systHist.GetNbinsX()+1):
            table.SetBinContent(j,i+1,table.GetBinContent(j,i))

    for i in range(nSyst+1, 0, -1):
        if i==1:
            table.GetYaxis().SetBinLabel(i, "Total uncertainty")
        else:
            table.GetYaxis().SetBinLabel(i, systList[i-2][1])


    # total unc
    for i in range(1, systHist.GetNbinsX()+1):
        table.SetBinContent(i, 1, integral_tot_systHist.GetBinContent(i))
#    print(table.GetBinContent(3,nSyst+1))

    ROOT.gStyle.SetPadLeftMargin(0.35)
    ROOT.gStyle.SetPadRightMargin(0.2)
    ROOT.gStyle.SetPadBottomMargin(0.1)
    #ROOT.gStyle.SetPaintTextFormat("4.5f")
    c2 = ROOT.TCanvas()
    table.GetXaxis().SetLabelSize(0.025)
    table.GetXaxis().SetNdivisions(505,1) 
    #table.GetXaxis().SetBinLabel(1,"500 \leq M_{J} \leq 800 GeV")
    #table.GetXaxis().SetBinLabel(2,"800 \leq M_{J} \leq 1100 GeV")
    #table.GetXaxis().SetBinLabel(3,"M_{J} \geq 1100 GeV")
    table.GetXaxis().SetBinLabel(1,"")
    table.GetXaxis().SetBinLabel(2,"")
    table.GetXaxis().SetBinLabel(3,"")
    table.GetXaxis().SetLabelOffset(0.01)
    table.SetMaximum(20)
    table.SetMinimum(0)
    table.SetStats(0)
    table.SetMarkerSize(1.5)
    table.SetXTitle("")
    #table.SetXTitle("M_{J} (GeV)")
    table.SetZTitle("Uncertainty [%]")
    table.GetXaxis().SetTitleOffset(0.95)
    table.GetYaxis().SetTitleOffset(1.4)
    table.GetYaxis().SetTitleSize(0.054)
    #table.GetYaxis().SetLabelSize(0.04)
    table.GetYaxis().SetLabelSize(0.03)
    table.GetXaxis().SetTitleSize(0.04)
    table.Draw("colz text")
    ROOT.gPad.SetTicks(1,0)
    table.Draw("axis y+ same")
    tla = ROOT.TLatex()
    tla.SetTextSize(0.038)
    tla.DrawLatexNDC(0.35,0.93,"#font[62]{CMS} #scale[0.9]{#font[52]{Preliminary}}")
    tla.SetTextFont(42)

    tla_mj = ROOT.TLatex()
    tla_mj.SetTextFont(42)
    tla_mj.SetTextSize(0.038)
    tla_mj.DrawLatexNDC(0.32, 0.06, "500")
    tla_mj.DrawLatexNDC(0.473, 0.06, "800")
    tla_mj.DrawLatexNDC(0.615, 0.06, "1100")
    tla_mj.DrawLatexNDC(0.76, 0.06, "1400")
    tla_mj.DrawLatexNDC(0.75, 0.02, "M_{J} (GeV)")

    if str(Year)=='2016preVFP':
        tla.DrawLatexNDC(0.63,0.93,"#scale[0.8]{19.5 fb^{-1} (13 TeV)}")
    elif str(Year)=='2016postVFP':
        tla.DrawLatexNDC(0.63,0.93,"#scale[0.8]{16.8 fb^{-1} (13 TeV)}")
    elif str(Year)=='2017':
        tla.DrawLatexNDC(0.63,0.93,"#scale[0.8]{41.5 fb^{-1} (13 TeV)}")
    elif str(Year)=='2018':
        tla.DrawLatexNDC(0.63,0.93,"#scale[0.8]{59.8 fb^{-1} (13 TeV)}")

    if one_pdf:
        if directory == binList[0][0]:
            outname = "plots/rpv_sig_syst/" + str(Year) + "/table_sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf("
        elif directory == binList[len(binList)-1][0]:
            outname = "plots/rpv_sig_syst/" + str(Year) + "/table_sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf)"
        else:
            outname = "plots/rpv_sig_syst/" + str(Year) + "/table_sig_systs_all_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf"

    else:
         outname = "plots/rpv_sig_syst/" + str(Year) + "/table_sig_systs_" + directory + "_m" + str(GLUINOMASS) + "_" + str(Year) + ".pdf"
         
    c2.Print(outname)





            
