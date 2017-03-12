import argparse
import math
from sys import argv
import os.path

#Batch mode hack
argv.append( '-b-' )
import ROOT
ROOT.gROOT.SetBatch(True)
argv.remove( '-b-' )

def getFlavorWeights(prefit, postfit):
    processes = ['other','qcd_b','qcd_c','qcd_l']

    prefit_qcdb = [prefit.find('bin1/qcd_b').getVal(), 0]
    prefit_qcdc = [prefit.find('bin1/qcd_c').getVal(), 0]
    postfit_qcdb = [postfit.find('bin1/qcd_b').getVal(), postfit.find('bin1/qcd_b').getError()]
    postfit_qcdc = [postfit.find('bin1/qcd_c').getVal(), postfit.find('bin1/qcd_c').getError()]

    prefit_norm, postfit_norm = 0, 0
    for iproc in processes:
        prefit_norm += prefit.find('bin1/'+iproc).getVal()
        postfit_norm += postfit.find('bin1/'+iproc).getVal()

    # Calculate weights and errors [qcdb/qcdc][weight/error]
    weights = [[(postfit_qcdb[0]/postfit_norm)/(prefit_qcdb[0]/prefit_norm), (postfit_qcdb[1]/postfit_norm)/(prefit_qcdb[0]/prefit_norm)]]
    weights.append([(postfit_qcdc[0]/postfit_norm)/(prefit_qcdc[0]/prefit_norm), (postfit_qcdc[1]/postfit_norm)/(prefit_qcdc[0]/prefit_norm)])

    return weights

def getTitleStrings(filename):
    filename = os.path.basename(filename)

    titles = ''
    if 'vlowmj' in filename: titles = ['csvfit_postfit_vlowmj.pdf','N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, 300 #leq M_{J} #leq 500']
    elif 'lowmj' in filename:  titles = ['csvfit_postfit_lowmj.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, 500 #leq M_{J} #leq 800']
    elif 'highmj' in filename: titles = ['csvfit_postfit_highmj.pdf','N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, M_{J} #geq 800']
    elif '45jets' in filename: titles = ['csvfit_postfit_45jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 5, M_{J} #geq 500']
    elif '67jets' in filename: titles = ['csvfit_postfit_67jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 6 #leq N_{jets}#leq 7, M_{J} #geq 500']
    elif '89jets' in filename: titles = ['csvfit_postfit_89jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 8 #leq N_{jets}#leq 9, M_{J} #geq 500']
    elif '10jets' in filename: titles = ['csvfit_postfit_10jets.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, N_{jets}#geq 10, M_{J} #geq 500']
    else:                      titles = ['csvfit_postfit.pdf', 'N_{leps} = 0, H_{T} > 1500, N_{b} #geq 2, 4 #leq N_{jets}#leq 7, M_{J} #geq 500']

    return titles

if __name__ == '__main__':
    
    parser = argparse.ArgumentParser(description='Plot the post-fit shapes from the CSV Fit')
    parser.add_argument('mlfit', help='mlfit.root file with the post-fit shapes')
    parser.add_argument('shapes', help='Pre-fit shapes file in order to get data shape')
    args = parser.parse_args()

    ROOT.TH1.SetDefaultSumw2(True);

    # Get shape histograms
    f_shapes = ROOT.TFile(args.shapes, 'READ')
    h_data = f_shapes.Get('bin1/data_obs')

    f_mlfit = ROOT.TFile(args.mlfit,'READ')
    # Histograms have non-physical binning
    h_qcdb_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_b')
    h_qcdc_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_c')
    h_qcdl_raw = f_mlfit.Get('shapes_fit_b/bin1/qcd_l')
    h_other_raw = f_mlfit.Get('shapes_fit_b/bin1/other')

    # Need TH1Ds to make plots with physical binning
    h_qcdb = ROOT.TH1D("h_qcdb","",20,0.8484,1)
    h_qcdc = ROOT.TH1D("h_qcdc","",20,0.8484,1)
    h_qcdl = ROOT.TH1D("h_qcdl","",20,0.8484,1)
    h_other = ROOT.TH1D("h_other","",20,0.8484,1)

    # Convert combine binning to physical binning
    for i in range(1,21): 
        h_qcdb.SetBinContent(i,h_qcdb_raw.GetBinContent(i))
        h_qcdb.SetBinError(i,h_qcdb_raw.GetBinError(i))

        h_qcdc.SetBinContent(i,h_qcdc_raw.GetBinContent(i))
        h_qcdc.SetBinError(i,h_qcdc_raw.GetBinError(i))

        h_qcdl.SetBinContent(i,h_qcdl_raw.GetBinContent(i))
        h_qcdl.SetBinError(i,h_qcdl_raw.GetBinError(i))
        
        h_other.SetBinContent(i,h_other_raw.GetBinContent(i))
        h_other.SetBinError(i,h_other_raw.GetBinError(i))

    # Get flavor weights and errors
    weights = getFlavorWeights(f_mlfit.Get("norm_prefit"), f_mlfit.Get("norm_fit_b"))

    ########################################
    #          Plot-Making                 #
    ########################################

    ROOT.gStyle.SetOptStat(0)
    c = ROOT.TCanvas('c','c',600,600)
    pad = ROOT.TPad('pad','pad', 0.0, 0.20, 1.0, 1.0)    
    pad.SetTopMargin(0.10)
    pad.SetBottomMargin(0.04)
    pad.SetLeftMargin(0.125)
    pad.SetRightMargin(0.04)
    pad.Draw()
    pad.cd()

    # "Stack" histograms
    h_qcdb.Add(h_qcdc)
    h_qcdb.Add(h_qcdl)
    h_qcdb.Add(h_other)

    h_qcdc.Add(h_qcdl)
    h_qcdc.Add(h_other)
    
    h_qcdl.Add(h_other)

    # Make pretty
    h_data.SetMarkerStyle(20)
    h_data.SetMarkerColor(ROOT.kBlack)
    h_data.SetLineColor(ROOT.kBlack)

    h_qcdb.SetMinimum(0)
    h_qcdb.SetLineColor(ROOT.kBlack)
    h_qcdb.SetFillColor(ROOT.kCyan+3)
    h_qcdb.SetTitle(getTitleStrings(args.shapes)[1])
    h_qcdb.GetXaxis().SetLabelSize(0)
    h_qcdb.GetYaxis().SetTitle('Entries')
    h_qcdb.GetYaxis().SetTitleSize(0.05)
    h_qcdb.GetYaxis().SetTitleOffset(1.3)
    h_qcdb.GetYaxis().SetLabelSize(0.04)
    h_qcdc.SetLineColor(ROOT.kBlack)
    h_qcdc.SetFillColor(ROOT.kRed+3)
    h_qcdl.SetLineColor(ROOT.kBlack)
    h_qcdl.SetFillColor(ROOT.kViolet+3)
    h_other.SetLineColor(ROOT.kBlack)
    h_other.SetFillColor(ROOT.kOrange-6)

    # Draw plots
    h_qcdb.DrawCopy("hist")
    # Plot again with formatting for error band
    h_qcdb.SetFillColor(ROOT.kBlack)
    h_qcdb.SetFillStyle(3002)
    h_qcdb.DrawCopy("E2 same")
    h_qcdb.SetFillColor(ROOT.kCyan+3)
    h_qcdb.SetFillStyle(1001)

    h_qcdc.Draw("hist same")
    h_qcdl.Draw("hist same")
    h_other.Draw("hist same")
    h_data.Draw('P0 same')

    # Draw legend
    ROOT.gStyle.SetLegendTextSize(0.038)
    leg = ROOT.TLegend(0.15,0.55,0.60,0.9)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)    
    leg.AddEntry(h_data, 'Data')
    leg.AddEntry(h_qcdb, 'b-quark events (w_{b} = '+str(round(weights[0][0],3))+' #pm '+str(round(weights[0][1],3))+')', 'f')
    leg.AddEntry(h_qcdc, 'c-quark events (w_{c} = '+str(round(weights[1][0],3))+' #pm '+str(round(weights[1][1],3))+')', 'f')
    leg.AddEntry(h_qcdl, 'light-quark events (Fixed)', 'f')
    leg.AddEntry(h_other, 'Non-QCD events (Fixed)', 'f')
    leg.Draw()

    # Make ratio pad
    c.cd()
    bpad = ROOT.TPad('bpad','bpad', 0.0, 0.0, 1.0, 0.22)
    bpad.Draw()
    bpad.cd()
    bpad.SetTopMargin(0.08)
    bpad.SetBottomMargin(0.3)
    bpad.SetRightMargin(0.04)
    bpad.SetLeftMargin(0.125)
    bpad.SetGridy()

    h_ratio = h_data.Clone('h_ratio')
    h_ratio.Divide(h_qcdb)

    h_ratio.SetMinimum(0.90)
    h_ratio.SetMaximum(1.10)
    h_ratio.SetTitle('')
    h_ratio.SetTitleSize(0.15,'XY')
    h_ratio.GetXaxis().SetTitle('CSV')   
    h_ratio.GetXaxis().SetTitleOffset(0.9)
    h_ratio.GetYaxis().SetTitle('Data/Fit')
    h_ratio.GetYaxis().CenterTitle()
    h_ratio.GetYaxis().SetTitleOffset(0.4)
    h_ratio.GetYaxis().SetNdivisions(3,5,0)
    h_ratio.SetLabelSize(0.15,'XY')

    h_ratio.Draw('e0')

    c.SaveAs(getTitleStrings(args.shapes)[0])
