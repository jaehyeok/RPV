// plot_note: Macro that plots variables both lumi weighted and normalized to the same area.

#include <iostream>
#include <vector>
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"
#include "TColor.h"

#include "styles.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"

namespace {
  TString lumi = "12.9";
  TString plot_type=".pdf";
  TString plot_style="CMSPaper_Preliminary";
}

using namespace std;
using std::cout;
using std::endl;


int main(int argc, char *argv[]){
    // don't want to include RA4 trigger efficiency
    std::string extraWeight("1");

    bool showData=true;
    bool nminus1=false;
    TString outDir("rpv_base/");
    if(argc==2) {
        TString nMinus1String("nminus1");
        if(argv[1]!=nMinus1String) {
            cout << "Only valid option is 'nminus1'. If no options are specified, the default plots are generated" << endl;
            return 1;
        }
        else {
            nminus1=true;
            showData=false; // don't show data in signal region
            outDir="nminus1";
        }
    }

    TString folder_bkg = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/mc/skim_rpv_st1200/";
    TString folder_sig = "/net/cms9/cms9r0/rohan/babies/2016_07_13/T1tbs/split/renorm/";
    TString folder_dat = "/net/cms2/cms2r0/babymaker/babies/2016_08_10/data/skim_rpv_st1200/";

    vector<TString> s_jetht = getRPVProcess(folder_dat,"data");
    
    vector<TString> s_rpv_m1300 = getRPVProcess(folder_sig,"rpv_m1300");
    vector<TString> s_rpv_m1500 = getRPVProcess(folder_sig,"rpv_m1500");

    vector<TString> s_tt = getRPVProcess(folder_bkg,"ttbar");
    vector<TString> s_qcd = getRPVProcess(folder_bkg,"qcd");
    vector<TString> s_wjets = getRPVProcess(folder_bkg,"wjets");
    vector<TString> s_singlet = getRPVProcess(folder_bkg,"singlet");
    vector<TString> s_zjets = getRPVProcess(folder_bkg,"zjets");
    vector<TString> s_other = getRPVProcess(folder_bkg,"other");

    // Reading ntuples
    vector<sfeats> Samples; 
    if(showData) {
        Samples.push_back(sfeats(s_jetht, "Data",kBlack,1,"trig[12] && json12p9 && pass && (njets<10 || (nmus+nels)==0)"));
        Samples.back().isData = true;
        Samples.back().doStack = false;
    }
    //    Samples.push_back(sfeats(s_rpv_m1300, "#tilde{g}(1.3 TeV)#rightarrow tbs", ra4::c_t1tttt)); 
    //    Samples.back().doStack = false;
    //    Samples.back().isSig = true;
    //    Samples.push_back(sfeats(s_rpv_m1500, "#tilde{g}(1.5 TeV)#rightarrow tbs", ra4::c_t1tttt, 2)); 
    //    Samples.back().doStack = false;
    //    Samples.back().isSig = true;
    Samples.push_back(sfeats(s_qcd, "QCD", kYellow, 1, cutandweight("stitch&&pass",extraWeight))); 
    Samples.push_back(sfeats(s_wjets, "W+jets, 0 l", ra4::c_wjets, 1, cutandweight("stitch&&pass&&ntruleps==0",extraWeight)));
    Samples.push_back(sfeats(s_zjets, "Z+jets, 0 l", kBlack, 1, cutandweight("stitch&&pass",extraWeight)));
    Samples.push_back(sfeats(s_tt, "t#bar{t}, 1 l", ra4::c_tt_1l, 1, cutandweight("pass&&ntruleps==1", extraWeight)));
    Samples.push_back(sfeats(s_tt, "t#bar{t}, 2 l", ra4::c_tt_2l, 1, cutandweight("pass&&ntruleps==2", extraWeight)));
    Samples.push_back(sfeats(s_tt, "t#bar{t}, 0 l", kTeal, 1, cutandweight("pass&&ntruleps==0", extraWeight)));
    Samples.push_back(sfeats(s_wjets, "W+jets, 1 l", ra4::c_wjets, 1, cutandweight("stitch&&pass&&ntruleps==1",extraWeight)));
    Samples.push_back(sfeats(s_singlet, "Single t", ra4::c_singlet, 1, cutandweight("stitch&&pass",extraWeight)));
    Samples.push_back(sfeats(s_other, "Other", ra4::c_other, 1, cutandweight("stitch&&pass",extraWeight))); 


    // Adding non-skimmed samples
    vector<int> rpv_sam;
    unsigned nsam(Samples.size());
    for(unsigned sam(0); sam < nsam; sam++){
        rpv_sam.push_back(sam);
        vector<TString> sam_files = Samples[sam].file;
        Samples.push_back(sfeats(sam_files, Samples[sam].label, Samples[sam].color, Samples[sam].style,
                    Samples[sam].cut));
    } // Loop over samples

    vector<hfeats> vars;

    TString cuts("(nmus+nels)==1");

    std::vector<TString> basecut = {"(nmus+nels)==0", "(nmus+nels)==1"};
    std::vector<TString> mjcuts = {"mj12>500&&mj12<=800", "mj12>800"};
    std::vector<TString> njetcuts = {"njets>=4&&njets<=5", "njets>=6&&njets<=7"};
    TString htcut("ht>1500");
    if(!nminus1) {
        for(auto ibasecut : basecut) {
            for(auto imjcut : mjcuts) {
                for(auto ijetcut : njetcuts) {
                    // skip blinded regions
                    bool isBlind = (ibasecut.EqualTo("(nmus+nels)==0") && !ijetcut.EqualTo("njets>=4&&njets<=5") && !ijetcut.EqualTo("njets>=6&&njets<=7" )) ||
                        (ibasecut.EqualTo("(nmus+nels)==1") && !ijetcut.EqualTo("njets>=4&&njets<=5"));
                    // reenable all regions for low mj
                    if(imjcut.EqualTo("mj12>300&&mj12<=500" && !ibasecut.EqualTo("(nmus+nels)==1"))) isBlind=false;
                    if(ibasecut.EqualTo("(nmus+nels)==0") && (imjcut.EqualTo("mj12<=300") || (imjcut.EqualTo("mj12>300&&mj12<=500")))) isBlind=false;
                    if(isBlind && showData) continue;
                    if(ibasecut=="(nmus+nels)==1") {
                        ijetcut.ReplaceAll("njets>=10","njets>=8");
                        htcut="ht>1200";
                    }
                    cuts = ibasecut + "&&" + htcut + "&&" + ijetcut + "&&" + imjcut;
                    // vars.push_back(hfeats("ht",40, 0, 4000, rpv_sam, "H_{T} (GeV)", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("mj12",25, 0, 2500, rpv_sam, "M_{J} (GeV)", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("dr_bb",15, 0, 6, rpv_sam, "#DeltaR_{b#bar{b}}", cuts));
                    // vars.back().normalize = true;
                    vars.push_back(hfeats("nbm", 4, 1, 5, rpv_sam, "N_{b}", cuts));
                    vars.back().normalize = true;
                    // vars.push_back(hfeats("Sum$(jets_csv>0.605)", 4, 1, 5, rpv_sam, "N_{b,loose}", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("njets",20, 0, 20, rpv_sam, "N_{jets}", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("jets_pt[0]",30, 0, 1500, rpv_sam, "p_{T,1} (GeV)", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("jets_pt[1]",30, 0, 1500, rpv_sam, "p_{T,2} (GeV)", cuts));
                    // vars.back().normalize = true;
                    // vars.push_back(hfeats("met",30, 0, 1500, rpv_sam, "MET (GeV)", cuts));
                    // vars.back().normalize = true;
                }
            }
        }

        //Njets plots
        htcut="ht>1500";
        for(auto ibasecut : basecut) {
            for(auto imjcut : mjcuts) {
                TString ijetcut = "njets<=7"; //Blind safe
                if(!showData) ijetcut = "njets>=0";
                if(ibasecut=="(nmus+nels)==1") {
                    ijetcut.ReplaceAll("njets<=7","njets<=5");
                    htcut="ht>1200";
                }
                cuts = ibasecut + "&&" + htcut + "&&" + ijetcut + "&&" + imjcut;

		//                vars.push_back(hfeats("njets",20, 0, 20, rpv_sam, "N_{jets}", cuts));
		//                vars.back().normalize = true; vars.back().whichPlots = "1";
            }
        }
        //mj plots
        htcut="ht>1500";
        for(auto ibasecut : basecut) {     
            for(auto ijetcut : njetcuts) {
                // skip blinded regions
                bool isBlind = (ibasecut.EqualTo("(nmus+nels)==0") && !ijetcut.EqualTo("njets>=4&&njets<=5") && !ijetcut.EqualTo("njets>=6&&njets<=7" )) ||
                    (ibasecut.EqualTo("(nmus+nels)==1") && !ijetcut.EqualTo("njets>=4&&njets<=5"));
                if(isBlind && showData) continue;
                if(ibasecut=="(nmus+nels)==1") {
                    ijetcut.ReplaceAll("njets>=10","njets>=8");
                    htcut="ht>1200";
                }
                cuts = ibasecut + "&&" + htcut + "&&" + ijetcut;

		//                vars.push_back(hfeats("mj12",25, 0, 2500, rpv_sam, "M_{J} (GeV)", cuts));
		//                vars.back().normalize = true; vars.back().whichPlots = "1";
            }    
        }




    } // end if(!minus1)

    // make N-1 plots for signal regions
    else {
        std::vector<std::string> basecutsNm1 = {"(nmus+nels)==0", "(nmus+nels)==1"};
        std::vector<std::string> htcutsNm1 = {"ht>1500", "ht>1200"};
        std::vector<std::string> mjcutsNm1 = {"mj12>800", "mj12>500"};
        std::vector<std::string> njetcutsNm1 = {"njets>=10", "njets>=8"};
        std::vector<std::string> nbcutsNm1 = {"nbm>=3", "nbm>=3"};
        for(unsigned int i=0; i<basecutsNm1.size(); i++) {
            std::string cutsNm1=basecutsNm1[i]+"&&"+mjcutsNm1[i]+"&&"+njetcutsNm1[i]+"&&"+nbcutsNm1[i];
            vars.push_back(hfeats("ht",40, 0, 4000, rpv_sam, "H_{T} (GeV)", cutsNm1));
            cutsNm1=basecutsNm1[i]+"&&"+htcutsNm1[i]+"&&"+njetcutsNm1[i]+"&&"+nbcutsNm1[i];
            vars.push_back(hfeats("mj12",25, 0, 2500, rpv_sam, "M_{J} (GeV)", cutsNm1));
            cutsNm1=basecutsNm1[i]+"&&"+htcutsNm1[i]+"&&"+mjcutsNm1[i]+"&&"+nbcutsNm1[i];
            vars.push_back(hfeats("njets",20, 0, 20, rpv_sam, "N_{jets}", cutsNm1));
            cutsNm1=basecutsNm1[i]+"&&"+htcutsNm1[i]+"&&"+mjcutsNm1[i]+"&&"+njetcutsNm1[i];
            vars.push_back(hfeats("nbm",6, 0, 6, rpv_sam, "N_{b}", cutsNm1));
            cutsNm1=basecutsNm1[i]+"&&"+htcutsNm1[i]+"&&"+mjcutsNm1[i]+"&&"+njetcutsNm1[i]+"&&"+nbcutsNm1[i];
            vars.push_back(hfeats("jets_pt[0]",30, 0, 1500, rpv_sam, "p_{T,1} (GeV)", cutsNm1));
        }
    }

    plot_distributions(Samples, vars, lumi, plot_type, plot_style, outDir, showData, true); // last argument determines whether or not a ratio is drawn, and whether or not to show cuts

}

