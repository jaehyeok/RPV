import argparse
import math
from sys import argv

#Batch mode hack
argv.append( '-b-' )
import ROOT
ROOT.gROOT.SetBatch(True)
argv.remove( '-b-' )

def addInQuad(x, y):
    return math.sqrt(pow(x,2)+pow(y,2))

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

    # Make the plot
    c = ROOT.TCanvas()

    ROOT.gStyle.SetOptStat(0)

    # "Stack" histograms
    h_qcdb.Add(h_qcdc)
    h_qcdb.Add(h_qcdl)
    h_qcdb.Add(h_other)

    h_qcdc.Add(h_qcdl)
    h_qcdc.Add(h_other)
    
    h_qcdl.Add(h_other)

    h_qcdb.SetMinimum(0)
    h_qcdb.SetTitle('Flavor Fit')


    #Make pretty
    h_data.SetMarkerStyle(20)
    h_data.SetMarkerColor(ROOT.kBlack)
    h_data.SetLineColor(ROOT.kBlack)

    h_qcdb.SetLineColor(ROOT.kBlack)
    h_qcdb.SetFillColor(ROOT.kCyan+3)
    h_qcdc.SetLineColor(ROOT.kBlack)
    h_qcdc.SetFillColor(ROOT.kRed+3)
    h_qcdl.SetLineColor(ROOT.kBlack)
    h_qcdl.SetFillColor(ROOT.kViolet+3)
    h_other.SetLineColor(ROOT.kBlack)
    h_other.SetFillColor(ROOT.kOrange-6)



    #Draw plots now
    h_qcdb.Draw("hist")
    #Plot again with foramtting for error band
    h_qcdb.SetFillColor(ROOT.kBlack)
    h_qcdb.SetFillStyle(3002)
    h_qcdb.DrawCopy("E2 same")
    h_qcdb.SetFillColor(ROOT.kCyan+3)
    h_qcdb.SetFillStyle(1001)

    h_qcdc.Draw("hist same")
    h_qcdl.Draw("hist same")
    h_other.Draw("hist same")
    h_data.Draw('P0 same')

    #Draw legend
    leg = ROOT.TLegend(0.15,0.6,0.48,0.85)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.AddEntry(h_data, 'Data')
    leg.AddEntry(h_qcdb, 'b-quark events', 'f')
    leg.AddEntry(h_qcdc, 'c-quark events', 'f')
    leg.AddEntry(h_qcdl, 'l-quark events', 'f')
    leg.AddEntry(h_other, 'Non-QCD events', 'f')
    leg.Draw()

    c.SaveAs('csvfit_postfit.png')
