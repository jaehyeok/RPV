import re
from sys import argv, stdout, stderr, exit
import os

# import ROOT with a fix to get batch mode (http://root.cern.ch/phpBB3/viewtopic.php?t=3198)
argv.append( '-b-' )
import ROOT
ROOT.gROOT.SetBatch(True)
argv.remove( '-b-' )
from ROOT import TCanvas
from ROOT import TLine
from ROOT import TH1D
from ROOT import gStyle

if len(argv) != 2: raise RuntimeError, "Usage: plotNormsFromToys.py <dir>";

binnames=[]
pvalues=[]
bvalues=[]
svalues=[]

files = [file for file in os.listdir(argv[1]) if ".root" in file]
for ifile in files:

    file = ROOT.TFile.Open(argv[1]+ifile);
    prefit = file.Get("norm_prefit")
    fit_s = file.Get("norm_fit_s")
    fit_b = file.Get("norm_fit_b")
    status_s = file.Get("fit_s").status()
    status_b = file.Get("fit_b").status()
    if status_s!=0 or status_b!=0:
        print(ifile)
        print("status_b="+str(status_b))
        print("status_s="+str(status_s))
    if prefit == None: stderr.write("Missing fit_s in %s. Did you run MaxLikelihoodFit in a recent-enough version of combine and with --saveNorm?\n" % file);
    if fit_s  == None: raise RuntimeError, "Missing fit_s in %s. Did you run MaxLikelihoodFit with --saveNorm?" % file;
    if fit_b  == None: raise RuntimeError, "Missing fit_b in %s. Did you run MaxLikelihoodFit with --saveNorm?" % file;
    
    tmp_binnames=[]
    tmp_pvalues=[]
    tmp_bvalues=[]
    tmp_svalues=[]
    
    iter = fit_s.createIterator()
    while True:
        norm_s = iter.Next()
        if norm_s == None: break;
        if "ttbar" not in norm_s.GetName(): continue;
        norm_b = fit_b.find(norm_s.GetName())
        norm_p = prefit.find(norm_s.GetName()) if prefit else None
        m = re.match(r"(\w+)/(\w+)", norm_s.GetName());
        if m == None: m = re.match(r"n_exp_(?:final_)?(?:bin)+(\w+)_proc_(\w+)", norm_s.GetName());
        if m == None: raise RuntimeError, "Non-conforming object name %s" % norm_s.GetName()
        if norm_b == None: raise RuntimeError, "Missing normalization %s for background fit" % norm_s.GetName()

        tmp_binnames.append(norm_s.GetName().replace("/ttbar",""))
        tmp_pvalues.append(norm_p.getVal())

        tmp_bvalues.append(norm_b.getVal()) if status_b==0 else tmp_bvalues.append(-1)
        tmp_svalues.append(norm_s.getVal()) if status_s==0 else tmp_svalues.append(-1)

    binnames.append(tmp_binnames)
    pvalues.append(tmp_pvalues)
    bvalues.append(tmp_bvalues)
    svalues.append(tmp_svalues)

gStyle.SetOptStat(110001111)
#Want to fill only for some ttbar bins
h_bin5_b = TH1D('bin5','b-only ttbar norm for bin5',50,0,5); h_bin5_b.SetCanExtend(1)
h_bin11_b = TH1D('bin11','b-only ttbar norm for bin11',50,0,5); h_bin11_b.SetCanExtend(1)
h_bin20_b = TH1D('bin20','b-only ttbar norm for bin20',50,0,5); h_bin20_b.SetCanExtend(1)
h_bin21_b = TH1D('bin21','b-only ttbar norm for bin21',50,0,5); h_bin21_b.SetCanExtend(1)

h_bin5_sb = TH1D('bin5','s+b ttbar norm for bin5',50,0,5); h_bin5_sb.SetCanExtend(1); h_bin5_sb.SetLineColor(2)
h_bin11_sb = TH1D('bin11','s+b ttbar norm for bin11',50,0,5); h_bin11_sb.SetCanExtend(1); h_bin11_sb.SetLineColor(2)
h_bin20_sb = TH1D('bin20','s+b ttbar norm for bin20',50,0,5); h_bin20_sb.SetCanExtend(1); h_bin20_sb.SetLineColor(2)
h_bin21_sb = TH1D('bin21','s+b ttbar norm for bin21',50,0,5); h_bin21_sb.SetCanExtend(1); h_bin21_sb.SetLineColor(2)

lines = []

for i in range(len(binnames)):    
    for j in range(len(binnames[0])):
        #Fill Histograms
        if j not in [2,12,13,17]: continue;
        elif j == 17: 
            h_bin5_b.Fill(bvalues[i][17])
            h_bin5_sb.Fill(svalues[i][17])
        elif j == 2: 
            h_bin11_b.Fill(bvalues[i][2])
            h_bin11_sb.Fill(svalues[i][2])
        elif j == 12: 
            h_bin20_b.Fill(bvalues[i][12])
            h_bin20_sb.Fill(svalues[i][12])
        elif j == 13: 
            h_bin21_b.Fill(bvalues[i][13])
            h_bin21_sb.Fill(svalues[i][13])

h_bin5_b.SetAxisRange(0,h_bin5_b.GetXaxis().GetXmax())
h_bin11_b.SetAxisRange(0,h_bin11_b.GetXaxis().GetXmax())
h_bin20_b.SetAxisRange(0,h_bin20_b.GetXaxis().GetXmax())
h_bin21_b.SetAxisRange(0,h_bin21_b.GetXaxis().GetXmax())

h_bin5_sb.SetAxisRange(0,h_bin5_sb.GetXaxis().GetXmax())
h_bin11_sb.SetAxisRange(0,h_bin11_sb.GetXaxis().GetXmax())
h_bin20_sb.SetAxisRange(0,h_bin20_sb.GetXaxis().GetXmax())
h_bin21_sb.SetAxisRange(0,h_bin21_sb.GetXaxis().GetXmax())

line = TLine(); line.SetLineColor(1); line.SetLineWidth(6); line.SetLineStyle(2);
c1 = TCanvas()
#bonly
h_bin5_b.Draw("hist")
line.DrawLine(pvalues[0][17],0,pvalues[0][17],80)
c1.SaveAs(argv[1]+"h_bin5_b.pdf")
h_bin11_b.Draw("hist")
line.DrawLine(pvalues[0][2],0,pvalues[0][2],80)
c1.SaveAs(argv[1]+"h_bin11_b.pdf")
h_bin20_b.Draw("hist")
line.DrawLine(pvalues[0][12],0,pvalues[0][12],80)
c1.SaveAs(argv[1]+"h_bin20_b.pdf")
h_bin21_b.Draw("hist")
line.DrawLine(pvalues[0][13],0,pvalues[0][13],80)
c1.SaveAs(argv[1]+"h_bin21_b.pdf")

#s+b
h_bin5_sb.Draw("hist")
line.DrawLine(pvalues[0][17],0,pvalues[0][17],80)
c1.SaveAs(argv[1]+"h_bin5_sb.pdf")
h_bin11_sb.Draw("hist")
line.DrawLine(pvalues[0][2],0,pvalues[0][2],80)
c1.SaveAs(argv[1]+"h_bin11_sb.pdf")
h_bin20_sb.Draw("hist")
line.DrawLine(pvalues[0][12],0,pvalues[0][12],80)
c1.SaveAs(argv[1]+"h_bin20_sb.pdf")
h_bin21_sb.Draw("hist")
line.DrawLine(pvalues[0][13],0,pvalues[0][13],80)
c1.SaveAs(argv[1]+"h_bin21_sb.pdf")
