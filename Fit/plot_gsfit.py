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
    h_qcd_GSbb_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_GSbb')
    h_qcd_GSb_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_GSb')
    h_qcd_noGS_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_noGS')
    h_other_raw = f_mlfit.Get('shapes_fit_b/bin1/other')

    # Need TH1Ds to make plots with physical binning
    h_data = ROOT.TH1D('h_data','',nBins,xMin,xMax)
    h_qcd_GSbb = ROOT.TH1D('h_qcd_GSbb','',nBins,xMin,xMax)
    h_qcd_GSb = ROOT.TH1D('h_qcd_GSb','',nBins,xMin,xMax)
    h_qcd_noGS = ROOT.TH1D('h_qcd_noGS','',nBins,xMin,xMax)
    h_other = ROOT.TH1D('h_other','',nBins,xMin,xMax)

    # Convert combine binning to physical binning
    for i in range(1,nBins+1):         
        h_data.SetBinContent(i,h_data_raw.GetBinContent(i))
        h_data.SetBinError(i, h_data_raw.GetBinError(i))

        h_qcd_GSbb.SetBinContent(i,h_qcd_GSbb_raw.GetBinContent(i))
        h_qcd_GSb.SetBinContent(i,h_qcd_GSb_raw.GetBinContent(i))
        h_qcd_noGS.SetBinContent(i,h_qcd_noGS_raw.GetBinContent(i))
        h_other.SetBinContent(i,h_other_raw.GetBinContent(i))

    # Get flavor weights and errors
    weights = getFlavorWeights(f_mlfit.Get('norm_prefit'), f_mlfit.Get('norm_fit_b'))
    # Get histogram with errors
    h_err, h_err_rat = getErrHists(f_mlfit.Get('norm_fit_b'), h_qcd_GSbb, h_qcd_GSb, h_qcd_noGS, h_other)

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
    h_qcd_GSbb.Add(h_qcd_GSb); h_qcd_GSbb.Add(h_qcd_noGS); h_qcd_GSbb.Add(h_other)
    h_qcd_GSb.Add(h_qcd_noGS); h_qcd_GSb.Add(h_other)
    h_qcd_noGS.Add(h_other)

    # Make pretty
    formatHist(h_data, markStyle=20, markColor=ROOT.kBlack, lineColor=ROOT.kBlack)
    formatHist(h_qcd_GSbb, lineColor=ROOT.kBlack, fillColor=ROOT.kCyan+3)
    formatHist(h_qcd_GSb, lineColor=ROOT.kBlack, fillColor=ROOT.kRed+3)
    formatHist(h_qcd_noGS, lineColor=ROOT.kBlack, fillColor=ROOT.kViolet+3)
    formatHist(h_other, lineColor=ROOT.kBlack, fillColor=ROOT.kOrange-6)
    formatHist(h_err, fillColor=ROOT.kBlack, fillStyle=3001)

    h_qcd_GSbb.SetMinimum(0)
    h_qcd_GSbb.SetMaximum(h_qcd_GSbb.GetMaximum()*1.5)
    h_qcd_GSbb.SetTitle(getTitleStrings(args.shapes)[1])
    h_qcd_GSbb.GetXaxis().SetLabelSize(0)
    h_qcd_GSbb.GetYaxis().SetTitle('Entries')
    h_qcd_GSbb.GetYaxis().SetTitleSize(0.05)
    h_qcd_GSbb.GetYaxis().SetTitleOffset(1.3)
    h_qcd_GSbb.GetYaxis().SetLabelSize(0.04)

    # Draw plots
    h_qcd_GSbb.Draw('hist')
    h_qcd_GSb.Draw('hist same')
    h_qcd_noGS.Draw('hist same')
    h_other.Draw('hist same')
    h_err.Draw('E2 same')
    h_data.Draw('P0 same')

    # Draw legend
    ROOT.gStyle.SetLegendTextSize(0.038)
    leg = ROOT.TLegend(0.15,0.65,0.65,0.90)
    leg.SetFillStyle(0); leg.SetBorderSize(0)    
    leg.AddEntry(h_data, 'Data')
    leg.AddEntry(h_qcd_GSbb, 'QCD GSbb (w = %2.2f #pm %2.2f)'  % (weights[0][0], weights[0][1]), 'f')
    leg.AddEntry(h_qcd_GSb,  'QCD GSb   (w = %2.2f #pm %2.2f)' % (weights[1][0], weights[1][1]), 'f')
    leg.AddEntry(h_qcd_noGS, 'QCD noGS (w = %2.2f #pm %2.2f)'  % (weights[2][0], weights[2][1]), 'f')
    leg.AddEntry(h_other, 'Non-QCD   (Fixed)', 'f')
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
    h_ratio.Divide(h_qcd_GSbb)

    h_err_rat.SetMinimum(0.50)
    h_err_rat.SetMaximum(1.50)
    h_err_rat.SetTitle('')
    h_err_rat.SetTitleSize(0.15,'XY')
    h_err_rat.GetXaxis().SetTitle('#DeltaR_{b#bar{b}}')   
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

def getErrHists(postfit, h_qcd_GSbb, h_qcd_GSb, h_qcd_noGS, h_other):
    #Depending on the option some errors are fully correlated
    # Option 1: All processes float -- uncertainties treated as uncorrelated
    # Option 2: GSb and noGS float together -- uncertainties treated as fully correlated
    # Option 3: GSbb and GSb float together -- uncertainties treated as fully correlated

    relerr_qcd_GSbb = postfit.find('bin1/qcd_GSbb').getError()/postfit.find('bin1/qcd_GSbb').getVal()
    relerr_qcd_GSb  = postfit.find('bin1/qcd_GSb').getError()/postfit.find('bin1/qcd_GSb').getVal()
    relerr_qcd_noGS = postfit.find('bin1/qcd_noGS').getError()/postfit.find('bin1/qcd_noGS').getVal()
    
    err = []
    if args.option=='1':
        # All uncorrelated uncertainties
        err = [h_qcd_GSbb.GetBinContent(i)*relerr_qcd_GSbb + h_qcd_GSb.GetBinContent(i)*relerr_qcd_GSb + h_qcd_noGS.GetBinContent(i)*relerr_qcd_noGS for i in range(1,nBins+1)] 
    elif args.option=='2':
        # Anti-correlate qcd_GSbb and qcd_GSb/qcd_noGS uncertainties
        err = [abs(h_qcd_GSbb.GetBinContent(i)*relerr_qcd_GSbb - (h_qcd_GSb.GetBinContent(i)*relerr_qcd_GSb+h_qcd_noGS.GetBinContent(i)*relerr_qcd_noGS)) for i in range(1,nBins+1)] 
    elif args.option=='3':
        # Anti-correlate qcd_GSbb/qcd_GSb and qcd_noGS uncertainties
        err = [abs((h_qcd_GSbb.GetBinContent(i)*relerr_qcd_GSbb+h_qcd_GSb.GetBinContent(i)*relerr_qcd_GSb) - h_qcd_noGS.GetBinContent(i)*relerr_qcd_noGS) for i in range(1,nBins+1)] 

    h_err = h_qcd_GSbb.Clone('h_err')
    h_err.Add(h_qcd_GSb); h_err.Add(h_qcd_noGS); h_err.Add(h_other)
    h_err_rat = h_err.Clone('h_err_rat')

    # Add errors and make ratio band
    for i in range(1,nBins+1): 
        h_err.SetBinError(i,err[i-1])
    h_err_rat.Divide(h_err)

    return h_err, h_err_rat

def getFlavorWeights(prefit, postfit):
    processes = ['other','qcd_noGS','qcd_GSb','qcd_GSbb']

    prefit_qcd_GSbb  = [prefit.find('bin1/qcd_GSbb').getVal(), 0]
    prefit_qcd_GSb   = [prefit.find('bin1/qcd_GSb').getVal(), 0]
    prefit_qcd_noGS  = [prefit.find('bin1/qcd_noGS').getVal(), 0]
    postfit_qcd_GSbb = [postfit.find('bin1/qcd_GSbb').getVal(), postfit.find('bin1/qcd_GSbb').getError()]
    postfit_qcd_GSb  = [postfit.find('bin1/qcd_GSb').getVal(), postfit.find('bin1/qcd_GSb').getError()]
    postfit_qcd_noGS = [postfit.find('bin1/qcd_noGS').getVal(), postfit.find('bin1/qcd_noGS').getError()]

    prefit_norm, postfit_norm = 0, 0
    for iproc in processes:
        prefit_norm += prefit.find('bin1/'+iproc).getVal()
        postfit_norm += postfit.find('bin1/'+iproc).getVal()

    # Calculate weights and errors [qcd_GSbb/qcd_GSb/qcd_noGS][weight/error]
    weights = [[(postfit_qcd_GSbb[0]/postfit_norm)/(prefit_qcd_GSbb[0]/prefit_norm), (postfit_qcd_GSbb[1]/postfit_norm)/(prefit_qcd_GSbb[0]/prefit_norm)], 
               [(postfit_qcd_GSb[0]/postfit_norm)/(prefit_qcd_GSb[0]/prefit_norm), (postfit_qcd_GSb[1]/postfit_norm)/(prefit_qcd_GSb[0]/prefit_norm)],
               [(postfit_qcd_noGS[0]/postfit_norm)/(prefit_qcd_noGS[0]/prefit_norm), (postfit_qcd_noGS[1]/postfit_norm)/(prefit_qcd_noGS[0]/prefit_norm)]]

    return weights

def getTitleStrings(filename):
    filename = os.path.basename(filename)

    titles = ''
    if 'vlowmj' in filename: titles =   ['gsfit_postfit_vlowmj.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, 4 #leq N_{jets}#leq 7, 300 #leq M_{J} #leq 500']
    elif 'lowmj' in filename:  titles = ['gsfit_postfit_lowmj.pdf',  'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, 4 #leq N_{jets}#leq 7, 500 #leq M_{J} #leq 800']
    elif 'highmj' in filename: titles = ['gsfit_postfit_highmj.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, 4 #leq N_{jets}#leq 7, M_{J} #geq 800']
    elif '45jets' in filename: titles = ['gsfit_postfit_45jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, 4 #leq N_{jets}#leq 5, M_{J} #geq 500']
    elif '67jets' in filename: titles = ['gsfit_postfit_67jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, 6 #leq N_{jets}#leq 7, M_{J} #geq 500']
    elif '8jets' in filename: titles = ['gsfit_postfit_89jets.pdf',  'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, N_{jets}#geq 8, M_{J} #geq 500']
    else:                      titles = ['gsfit_postfit.pdf',        'N_{leps} = 0, H_{T} > 1500, N_{b} = 2, N_{jets}#geq 4, M_{J} #geq 500']

    if args.option: titles[0] = titles[0].replace('.pdf','_opt'+args.option+'.pdf')
    if args.tag: titles[0] = titles[0].replace('.pdf','_'+args.tag+'.pdf')

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
    h_qcd_GSbb, h_qcd_GSb, h_qcd_noGS, h_other = h_pulls.Clone('h_qcd_GSbb'), h_pulls.Clone('h_qcd_GSb'), h_pulls.Clone('h_qcd_noGS'), h_pulls.Clone('h_other')
    formatHist(h_qcd_GSbb,lineColor=ROOT.kCyan+3,markColor=ROOT.kCyan+3)
    formatHist(h_qcd_GSb,lineColor=ROOT.kRed+3,markColor=ROOT.kRed+3)
    formatHist(h_qcd_noGS,lineColor=ROOT.kViolet+3,markColor=ROOT.kViolet+3)
    formatHist(h_other,lineColor=ROOT.kOrange-6,markColor=ROOT.kOrange-6)
    for i in range(npulls):
        # Set contents off the plot if not correct nuisance
        if 'qcd_GSbb' not in h_qcd_GSbb.GetXaxis().GetBinLabel(i): h_qcd_GSbb.SetBinContent(i,100)
        if 'qcd_GSb'  not in h_qcd_GSb.GetXaxis().GetBinLabel(i):  h_qcd_GSb.SetBinContent(i,100)
        if 'qcd_noGS' not in h_qcd_noGS.GetXaxis().GetBinLabel(i): h_qcd_noGS.SetBinContent(i,100)
        if 'other'    not in h_other.GetXaxis().GetBinLabel(i):    h_other.SetBinContent(i,100)

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
    h_qcd_GSb.Draw('EX0P same')
    h_qcd_GSbb.Draw('EX0P same')
    h_qcd_noGS.Draw('EX0P same')

    # Add legend
    ROOT.gStyle.SetLegendTextSize(0.038)
    leg = ROOT.TLegend(0.06,0.90,0.95,1.00)
    leg.SetFillStyle(0); leg.SetBorderSize(0); leg.SetNColumns(4)
    leg.AddEntry(h_other, 'Non-QCD', 'pe')
    leg.AddEntry(h_qcd_GSb,  'QCD GSb', 'pe')
    leg.AddEntry(h_qcd_GSbb, 'QCD GSbb', 'pe')
    leg.AddEntry(h_qcd_noGS, 'QCD noGS', 'pe')
    leg.Draw()

    cpulls.SaveAs(titles[0].replace('postfit','pulls'))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Plot the post-fit shapes from the CSV Fit')
    parser.add_argument('mlfit', help='mlfit file with the post-fit shapes')
    parser.add_argument('shapes', help='Pre-fit shapes file in order to get data shape')
    parser.add_argument('--option','-o',choices=['1','2','3'], default='1', help='Choose 1,2,3 to determine which processes are floated together. Default = 1')
    parser.add_argument('--tag','-t', help='Add a tag to the end of the plot titles')
    args = parser.parse_args()

    # Global values
    nBins = 4
    xMin = 0
    xMax = 4.8
    
    # Run script
    main()
