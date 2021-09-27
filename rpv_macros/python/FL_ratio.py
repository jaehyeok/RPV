import ROOT
from ROOT import TFile, TH1, TH2D
import sys

njets_list = ["lnj", "mnj", "hnj"]

if __name__=='__main__':
	year = sys.argv[1]
	f = TFile("result_fakelepton_"+year+"_le500.root","read")
	for njets in njets_list : 
		FLR_bkg = f.Get("FLR_bkg_"+njets)
		FLR_qcd = f.Get("FLR_qcd_"+njets)
		FLR_dat = f.Get("FLR_dat_"+njets)
		FL_bkg = float(FLR_bkg.GetBinContent(1,1)+FLR_bkg.GetBinContent(1,2)+FLR_bkg.GetBinContent(2,1))
		RL_bkg = float(FLR_bkg.GetBinContent(2,2))
		FL_qcd = float(FLR_qcd.GetBinContent(1,1)+FLR_qcd.GetBinContent(1,2)+FLR_qcd.GetBinContent(2,1))
		RL_qcd = float(FLR_qcd.GetBinContent(2,2))
		FL_dat = float(FLR_dat.GetBinContent(1,1)+FLR_dat.GetBinContent(1,2)+FLR_dat.GetBinContent(2,1))
		RL_dat = float(FLR_dat.GetBinContent(2,2))
		FL_dmb = FL_dat-FL_bkg
		FL_dmb_uct = ROOT.TMath.Sqrt(FLR_bkg.GetBinError(1,1)*FLR_bkg.GetBinError(1,1)+FLR_bkg.GetBinError(1,2)*FLR_bkg.GetBinError(1,2)+FLR_bkg.GetBinError(2,1)*FLR_bkg.GetBinError(2,1)+FLR_dat.GetBinError(1,1)*FLR_dat.GetBinError(1,1)+FLR_dat.GetBinError(1,2)*FLR_dat.GetBinError(1,2)+FLR_dat.GetBinError(2,1)*FLR_dat.GetBinError(2,1))
		RL_dmb = RL_dat-RL_bkg
		RL_dmb_uct = ROOT.TMath.Sqrt(FLR_dat.GetBinError(2,2)*FLR_dat.GetBinError(2,2)+FLR_bkg.GetBinError(2,2)*FLR_bkg.GetBinError(2,2))
		FL_qcd_uct = ROOT.TMath.Sqrt(FLR_qcd.GetBinError(1,1)*FLR_bkg.GetBinError(1,1)+FLR_qcd.GetBinError(1,2)*FLR_qcd.GetBinError(1,2)+FLR_qcd.GetBinError(2,1)*FLR_qcd.GetBinError(2,1))
		RL_qcd_uct = FLR_qcd.GetBinError(2,2)
		print("===================================================================")
		print("Number of Data-Others Real Leptons in {} : {:>10.2f} +/- {:<7.2f}".format(njets,RL_dmb,RL_dmb_uct))
		print("Number of Data-Others Fake Leptons in {} : {:>10.2f} +/- {:<7.2f}".format(njets,FL_dmb,FL_dmb_uct))
		print("Number of QCD Real Leptons in {}         : {:>10.2f} +/- {:<7.2f}".format(njets,RL_qcd,RL_qcd_uct))
		print("Number of QCD Fake Leptons in {}         : {:>10.2f} +/- {:<7.2f}".format(njets,FL_qcd,FL_qcd_uct))
		FLR_dmb = RL_dmb/FL_dmb
		FLR_dmb_uct = abs(FLR_dmb)*ROOT.TMath.Sqrt((RL_dmb_uct/RL_dmb)*(RL_dmb_uct/RL_dmb)+(FL_dmb_uct/FL_dmb)*(FL_dmb_uct/FL_dmb))
		FLR_qcd = RL_qcd/FL_qcd
		FLR_qcd_uct = abs(FLR_qcd)*ROOT.TMath.Sqrt((RL_qcd_uct/RL_qcd)*(RL_qcd_uct/RL_qcd)+(FL_qcd_uct/FL_qcd)*(FL_qcd_uct/FL_qcd))
		DdQ = FLR_dmb/FLR_qcd
		DdQ_uct = abs(DdQ)*ROOT.TMath.Sqrt((FLR_dmb_uct/FLR_dmb)*(FLR_dmb_uct/FLR_dmb)+(FLR_qcd_uct/FLR_qcd)*(FLR_qcd_uct/FLR_qcd))
		print("===================================================================")
		print("Data Fake Lepton Ratio in {} : {:0.7f} +/- {:0.7f}".format(njets,FLR_dmb,FLR_dmb_uct))
		print("QCD Fake Lepton Ratio in {}  : {:0.7f} +/- {:0.7f}".format(njets,FLR_qcd,FLR_qcd_uct))
		print("===================================================================")
		print("Data/QCD Fake Lepton Ration in {} : {:0.2f} +/- {:0.2f}".format(njets,DdQ,DdQ_uct))
		print("===================================================================")
		SF = ROOT.TMath.Sqrt((1-DdQ)**2+(DdQ_uct)**2)
		print("Data/QCD Scale Factor in {}       : {:0.2f} ".format(njets, SF))
		print("===================================================================")
