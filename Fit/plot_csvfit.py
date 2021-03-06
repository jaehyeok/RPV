import argparse
from array import array
import math
from sys import argv
import os.path

# Batch mode hack
argv.append( '-b-' )
import ROOT
ROOT.gROOT.SetBatch(True)
argv.remove( '-b-' )

def main():
    ROOT.TH1.SetDefaultSumw2(True);

    # Get shape histograms
    f_shapes = ROOT.TFile(args.shapes, 'READ')
    h_data_raw = f_shapes.Get('bin1/data_obs')

    f_mlfit = ROOT.TFile(args.mlfit,'READ')
    # Histograms have non-physical binning
    h_qcdb_raw = f_mlfit.Get('shapes_fit_b/bin1/qcdb')
    h_qcdc_raw = f_mlfit.Get('shapes_fit_b/bin1/qcdc')
    h_qcdl_raw = f_mlfit.Get('shapes_fit_b/bin1/qcdl')
    h_other_raw = f_mlfit.Get('shapes_fit_b/bin1/other')

    # Need TH1Ds to make plots with physical binning
    h_data = ROOT.TH1D('h_data','',nBins,xMin,xMax)
    h_qcdb = ROOT.TH1D('h_qcdb','',nBins,xMin,xMax)
    h_qcdc = ROOT.TH1D('h_qcdc','',nBins,xMin,xMax)
    h_qcdl = ROOT.TH1D('h_qcdl','',nBins,xMin,xMax)
    h_other = ROOT.TH1D('h_other','',nBins,xMin,xMax)

    # Convert combine binning to physical binning
    for i in range(1,nBins+1):         
        h_data.SetBinContent(i,h_data_raw.GetBinContent(i))
        h_data.SetBinError(i, h_data_raw.GetBinError(i))

        h_qcdb.SetBinContent(i,h_qcdb_raw.GetBinContent(i))
        h_qcdc.SetBinContent(i,h_qcdc_raw.GetBinContent(i))
        h_qcdl.SetBinContent(i,h_qcdl_raw.GetBinContent(i))
        h_other.SetBinContent(i,h_other_raw.GetBinContent(i))

    # Get flavor weights and errors
    weights = getFlavorWeights(f_mlfit.Get('norm_prefit'), f_mlfit.Get('norm_fit_b'))
    # Get histogram with errors
    h_err, h_err_rat = getErrHists(f_mlfit.Get('norm_fit_b'), h_qcdb, h_qcdc, h_qcdl, h_other)

    ########################################
    #          Plot-Making                 #
    ########################################

    ROOT.gStyle.SetOptStat(0)
    c = ROOT.TCanvas('c','c',600,600)
    pad = ROOT.TPad('pad','pad', 0.0, 0.20, 1.0, 1.0)    
    pad.SetTopMargin(0.10); pad.SetBottomMargin(0.04)
    pad.SetLeftMargin(0.125); pad.SetRightMargin(0.04)
    pad.Draw()
    pad.cd()

    # "Stack" histograms
    h_qcdb.Add(h_qcdc); h_qcdb.Add(h_qcdl); h_qcdb.Add(h_other)
    h_qcdc.Add(h_qcdl); h_qcdc.Add(h_other)
    h_qcdl.Add(h_other)

    # Make pretty
    formatHist(h_data, markStyle=20, markColor=ROOT.kBlack, lineColor=ROOT.kBlack)
    formatHist(h_qcdb, lineColor=ROOT.kBlack, fillColor=ROOT.kCyan+3)
    formatHist(h_qcdc, lineColor=ROOT.kBlack, fillColor=ROOT.kRed+3)
    formatHist(h_qcdl, lineColor=ROOT.kBlack, fillColor=ROOT.kViolet+3)
    formatHist(h_other, lineColor=ROOT.kBlack, fillColor=ROOT.kOrange-6)
    formatHist(h_err, fillColor=ROOT.kBlack, fillStyle=3001)

    h_qcdb.SetMinimum(0)
    h_qcdb.SetTitle(getTitleStrings(args.shapes)[1])
    h_qcdb.GetXaxis().SetLabelSize(0)
    h_qcdb.GetYaxis().SetTitle('Entries')
    h_qcdb.GetYaxis().SetTitleSize(0.05)
    h_qcdb.GetYaxis().SetTitleOffset(1.3)
    h_qcdb.GetYaxis().SetLabelSize(0.04)

    # Draw plots
    h_qcdb.Draw('hist')
    h_qcdc.Draw('hist same')
    h_qcdl.Draw('hist same')
    h_other.Draw('hist same')
    h_err.Draw('E2 same')
    h_data.Draw('P0 same')

    # Draw legend
    ROOT.gStyle.SetLegendTextSize(0.038)
    leg = ROOT.TLegend(0.15,0.55,0.60,0.9)
    leg.SetFillStyle(0); leg.SetBorderSize(0)    
    leg.AddEntry(h_data, 'Data')
    leg.AddEntry(h_qcdb, 'b-quark events (w_{b} = %3.3f #pm %3.3f)' % (weights[0][0], weights[0][1]), 'f')
    leg.AddEntry(h_qcdc, 'c-quark events (w_{c} = %3.3f #pm %3.3f)' % (weights[1][0], weights[1][1]), 'f')
    leg.AddEntry(h_qcdl, 'light-quark events (Fixed)', 'f')
    leg.AddEntry(h_other, 'Non-QCD events (Fixed)', 'f')
    leg.Draw()

    # Make ratio pad
    c.cd()
    bpad = ROOT.TPad('bpad','bpad', 0.0, 0.0, 1.0, 0.22)
    bpad.Draw()
    bpad.cd()
    bpad.SetTopMargin(0.08); bpad.SetBottomMargin(0.3)
    bpad.SetRightMargin(0.04); bpad.SetLeftMargin(0.125)
    bpad.SetGridy()

    h_ratio = h_data.Clone('h_ratio')
    h_ratio.Divide(h_qcdb)

    h_err_rat.SetMinimum(0.90)
    h_err_rat.SetMaximum(1.10)
    h_err_rat.SetTitle('')
    h_err_rat.SetTitleSize(0.15,'XY')
    h_err_rat.GetXaxis().SetTitle('CSV')   
    h_err_rat.GetXaxis().SetTitleOffset(0.9)
    h_err_rat.GetYaxis().SetTitle('Data/Fit')
    h_err_rat.GetYaxis().CenterTitle()
    h_err_rat.GetYaxis().SetTitleOffset(0.4)
    h_err_rat.GetYaxis().SetNdivisions(3,5,0)
    h_err_rat.SetLabelSize(0.15,'XY')

    formatHist(h_err_rat, fillColor=ROOT.kBlack, fillStyle=3002)
    h_err_rat.Draw('E2')
    h_ratio.Draw('E0 same')

    c.SaveAs(getTitleStrings(args.shapes)[0])    

    makePullsPlot(f_mlfit.Get('fit_b'), getTitleStrings(args.shapes))

def formatHist(hist, markStyle=-1, markSize=-1, markColor=-1, lineColor=-1, lineWidth=-1, fillColor=-1, fillStyle=-1):
    if markStyle!=-1: hist.SetMarkerStyle(markStyle)
    if markSize !=-1: hist.SetMarkerSize(markSize)
    if markColor!=-1: hist.SetMarkerColor(markColor)
    if lineColor!=-1: hist.SetLineColor(lineColor)
    if lineWidth!=-1: hist.SetLineWidth(lineWidth)
    if fillColor!=-1: hist.SetFillColor(fillColor)
    if fillStyle!=-1: hist.SetFillStyle(fillStyle)

def getErrHists(postfit, h_qcdb, h_qcdc, h_qcdl, h_other):
    scale_qcdb = postfit.find('bin1/qcdb').getError()/postfit.find('bin1/qcdb').getVal()
    scale_qcdc = postfit.find('bin1/qcdc').getError()/postfit.find('bin1/qcdc').getVal()

    # Anti-correlate qcdb and qcdc uncertanties
    err = [abs(h_qcdb.GetBinContent(i)*scale_qcdb - h_qcdc.GetBinContent(i)*scale_qcdc) for i in range(1,nBins+1)] 

    h_err = h_qcdb.Clone('h_err')
    h_err.Add(h_qcdc); h_err.Add(h_qcdl); h_err.Add(h_other)
    h_err_rat = h_err.Clone('h_err_rat')

    # Add errors and make ratio band
    for i in range(1,nBins+1): h_err.SetBinError(i,err[i-1])
    h_err_rat.Divide(h_err)

    return h_err, h_err_rat

def getFlavorWeights(prefit, postfit):
    processes = ['other','qcdb','qcdc','qcdl']

    prefit_qcdb = [prefit.find('bin1/qcdb').getVal(), 0]
    prefit_qcdc = [prefit.find('bin1/qcdc').getVal(), 0]
    postfit_qcdb = [postfit.find('bin1/qcdb').getVal(), postfit.find('bin1/qcdb').getError()]
    postfit_qcdc = [postfit.find('bin1/qcdc').getVal(), postfit.find('bin1/qcdc').getError()]

    prefit_norm, postfit_norm = 0, 0
    for iproc in processes:
        prefit_norm += prefit.find('bin1/'+iproc).getVal()
        postfit_norm += postfit.find('bin1/'+iproc).getVal()

    # Calculate weights and errors [qcdb/qcdc][weight/error]
    weights = [[(postfit_qcdb[0]/postfit_norm)/(prefit_qcdb[0]/prefit_norm), (postfit_qcdb[1]/postfit_norm)/(prefit_qcdb[0]/prefit_norm)], 
               [(postfit_qcdc[0]/postfit_norm)/(prefit_qcdc[0]/prefit_norm), (postfit_qcdc[1]/postfit_norm)/(prefit_qcdc[0]/prefit_norm)]]

    return weights

def getTitleStrings(filename):
    filename = os.path.basename(filename)

    titles = ''
    if 'vlowmj' in filename: titles =   ['csvfit_postfit_vlowmj.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, 300 #leq M_{J} #leq 500']
    elif 'lowmj' in filename:  titles = ['csvfit_postfit_lowmj.png',  'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, 500 #leq M_{J} #leq 800']
    elif 'highmj' in filename: titles = ['csvfit_postfit_highmj.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, M_{J} #geq 800']
    elif '45jets' in filename: titles = ['csvfit_postfit_45jets.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 5, M_{J} #geq 500']
    elif '67jets' in filename: titles = ['csvfit_postfit_67jets.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 6 #leq N_{jets}#leq 7, M_{J} #geq 500']
    elif '89jets' in filename: titles = ['csvfit_postfit_89jets.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 8 #leq N_{jets}#leq 9, M_{J} #geq 500']
    elif '10jets' in filename: titles = ['csvfit_postfit_10jets.png', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, N_{jets}#geq 10, M_{J} #geq 500']
    else:                      titles = ['csvfit_postfit.png',        'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, M_{J} #geq 500']

    if 'noSFs' in filename: titles[0] = titles[0].replace('.png','_noSFs.png')
    if args.tag: titles[0] = titles[0].replace('.png','_'+args.tag+'.png')

    return titles

def makePullsPlot(fitb, titles):
    params = fitb.floatParsFinal()
    npulls = params.getSize()

    # Make histogram
    h_pulls = ROOT.TH1D('h_pulls',';;Post-fit pulls',npulls,0,npulls)
    formatHist(h_pulls,markStyle=20, markSize=0.6, lineColor=ROOT.kBlack, lineWidth=1)
    for i in range(npulls):
        param = params.at(i)
        h_pulls.SetBinContent(i+1,param.getVal())
        h_pulls.SetBinError(i+1,param.getError())
        # Fix bin names, so can sort labels alphabetically
        if 'bin' in param.GetName():
            name = param.GetName().split('bin')
            h_pulls.GetXaxis().SetBinLabel(i+1,name[0]+'bin'+name[1].zfill(2))
        else:
            h_pulls.GetXaxis().SetBinLabel(i+1,param.GetName())

    h_pulls.GetXaxis().LabelsOption('a')
    h_pulls.SetTitleSize(0.045,'Y'); h_pulls.SetTitleOffset(0.62,'Y')
    h_pulls.SetMinimum(-3); h_pulls.SetMaximum(3)

    # Color code nuisances
    h_qcdb, h_qcdc, h_qcdl, h_other = h_pulls.Clone('h_qcdb'), h_pulls.Clone('h_qcdc'), h_pulls.Clone('h_qcdl'), h_pulls.Clone('h_other')
    formatHist(h_qcdb,lineColor=ROOT.kCyan+3,markColor=ROOT.kCyan+3)
    formatHist(h_qcdc,lineColor=ROOT.kRed+3,markColor=ROOT.kRed+3)
    formatHist(h_qcdl,lineColor=ROOT.kViolet+3,markColor=ROOT.kViolet+3)
    formatHist(h_other,lineColor=ROOT.kOrange-6,markColor=ROOT.kOrange-6)
    for i in range(npulls):
        # Set contents off the plot if not correct nuisance
        if 'qcdb' not in h_qcdb.GetXaxis().GetBinLabel(i): h_qcdb.SetBinContent(i,100)
        if 'qcdc' not in h_qcdc.GetXaxis().GetBinLabel(i): h_qcdc.SetBinContent(i,100)
        if 'qcdl' not in h_qcdl.GetXaxis().GetBinLabel(i): h_qcdl.SetBinContent(i,100)
        if 'other' not in h_other.GetXaxis().GetBinLabel(i): h_other.SetBinContent(i,100)

    # Make box
    box = ROOT.TBox(0, -1, npulls, 1)
    formatHist(box, fillStyle=3003, fillColor=ROOT.kBlue)

    # Draw Plot
    cpulls = ROOT.TCanvas('cpulls','cpulls',800,600)
    cpulls.SetBottomMargin(0.22); 
    cpulls.SetLeftMargin(0.07); cpulls.SetRightMargin(0.02)

    h_pulls.Draw('EX0P')
    box.Draw()
    h_other.Draw('EX0P same')
    h_qcdb.Draw('EX0P same')
    h_qcdc.Draw('EX0P same')
    h_qcdl.Draw('EX0P same')

    # Add legend
    ROOT.gStyle.SetLegendTextSize(0.038)
    leg = ROOT.TLegend(0.06,0.90,0.95,1.00)
    leg.SetFillStyle(0); leg.SetBorderSize(0); leg.SetNColumns(4)
    leg.AddEntry(h_other, 'Non-QCD events', 'pe')
    leg.AddEntry(h_qcdb, 'b-quark events', 'pe')
    leg.AddEntry(h_qcdc, 'c-quark events', 'pe')
    leg.AddEntry(h_qcdl, 'light-quark events', 'pe')
    leg.Draw()

    cpulls.SaveAs(titles[0].replace('postfit','pulls'))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Plot the post-fit shapes from the CSV Fit')
    parser.add_argument('mlfit', help='mlfit file with the post-fit shapes')
    parser.add_argument('shapes', help='Pre-fit shapes file in order to get data shape')
    parser.add_argument('--tag','-t', help='Add a tag to the end of the plot titles')
    args = parser.parse_args()

    # Global values
    nBins = 20
    xMin = 0.8484
    xMax = 1
    
    # Run script
    main()
