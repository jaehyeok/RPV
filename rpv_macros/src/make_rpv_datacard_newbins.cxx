// makes a datacard for RPV analysis with or without PDF uncertainties
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TSystem.h"

void outputWjets(std::ofstream &file, const std::vector<std::string> &bins, const std::string cardType, TString year);
void outputNormSharing(std::ofstream &file, const std::vector<std::string> &bins, TString year);
void outputOnlyNormalization(std::ofstream &file, const std::vector<std::string> &bins, TString year);
void outputMJConnection(std::ofstream &file, const std::vector<std::string> &bins, TString year);
void outputShapeSystematics(std::ofstream &file, const std::vector<std::string> shapeSysts, TString year);
void outputkappaSystematics(std::ofstream &file, const std::vector<std::string> &bins, const std::string filename, TString year);
void outputLognormalSystematics(std::ofstream &file, TString year);
void outputMCStatisticsSyst(std::ofstream &file, const std::vector<std::string> &bins, const std::string & signalBinName, TString year);
void outputautoMCStats(std::ofstream &file, const std::vector<std::string> &bins);
// determine if a histogram has an entry for a given nB
bool hasEntry(const std::string &sample, const std::string &bin, const int nB);

namespace {
  unsigned int nbins;
  unsigned int nprocesses;
}

using namespace std;

TString merge_78;

int main(int argc, char *argv[])
{
  bool includePDFUncert = false;
  bool includeLowMJ = false;
  bool nocrvr = false;
//  bool includeSignalRegion = true;
  TString year;
  TString sig_onoff;
  // signal is added later
  std::vector<std::string> processes = { "qcd", "ttbar", "wjets", "other"};
  /*std::vector<std::string> shapeSysts = {"btag_bc", "btag_udsg", //"kappa"
					                     "gs45", "gs67", "gs89", "gs10Inf",
					                     //"jes", "jer",
					                     "pileup", "lep_eff", "ttbar_pt",
					                     "qcd_flavor",
					                     "qcd_muf", "qcd_mur", "qcd_murf", 
					                     //"isr",
					                     "ttbar_muf", "ttbar_mur", "ttbar_murf",
					                     "wjets_muf", "wjets_mur", "wjets_murf",
					                     "other_muf", "other_mur", "other_murf",
					                     "fs_btag_bc", "fs_btag_udsg", "fs_lep_eff"}; // temporarily removed */
  std::vector<std::string> shapeSysts = {"JES","btag_bc","btag_udsg","muf","mur","murf","ISR","GS","lep_eff"};

  std::string gluinoMass;
  std::string signalBinName;
  std::string cardType;
  TString inputname;
  if(argc<3) {
    std::cout << "Syntax: make_rpv_datacard.exe [gluino mass, in GeV] [default/control/mconly] [filename] [year] [20178 on/off] [signal Systematics on/off]" << std::endl;
    return 1;
  }
  else {
    std::stringstream ss;
    gluinoMass = argv[1];
    year = argv[4];
    ss << "signal_M" << gluinoMass;
    //ss << "Stop_M" << gluinoMass;
    signalBinName = ss.str();
    // this is supposed to be the first entry in the process list
    processes.insert(processes.begin(), signalBinName);

    cardType=argv[2];
    if(cardType!="control" && cardType!="default" && cardType!="mconly") {
      std::cout << "Syntax: make_rpv_datacard.exe [gluino mass, in GeV] [default/control/mconly]" << std::endl;
      return 1;
    }
    inputname = argv[3];
    merge_78  = argv[5];
    sig_onoff = argv[6];
  }

  nprocesses=processes.size();

  // separate cards  
  // CR: bin 0 1 2
  // CR: bin 3 4 5 
  // low njet, low MJ  : bin 16 11
  // low njet, high MJ : bin 17 14
  // high njet, low MJ  : bin 10 12
  // high njet, high MJ : bin 13 15

  std::vector<std::vector<std::string> > bins;
/*
  std::vector<std::string> bins_cr_lowmj        = {"bin0", "bin1", "bin2"};
  std::vector<std::string> bins_cr_highmj       = {"bin3", "bin4", "bin5"};
  std::vector<std::string> bins_sr_lownj_lowmj  = {"bin16", "bin11"};
  std::vector<std::string> bins_sr_lownj_highmj = {"bin17", "bin14"};
  std::vector<std::string> bins_sr_lownj_vhighmj = {"bin18", "bin20"};
  std::vector<std::string> bins_sr_highnj_lowmj  = {"bin10", "bin12"};
  std::vector<std::string> bins_sr_highnj_highmj = {"bin13", "bin15"};
  std::vector<std::string> bins_sr_highnj_vhighmj = {"bin19", "bin21"};
  */
  std::vector<std::string> bins_cr_nb0_lownjets    = {"bin37","bin22"}; 
  std::vector<std::string> bins_cr_nb1_lownjets    = {"bin40","bin25"}; 
  std::vector<std::string> bins_cr_nb2_lownjets    = {"bin43","bin28"}; 
  std::vector<std::string> bins_cr_nb3_lownjets    = {"bin46","bin31"}; 
  //std::vector<std::string> bins_cr_nb4_lownjets    = {"bin49","bin34"}; 
  std::vector<std::string> bins_cr_nb0_mednjets    = {"bin38","bin23"}; 
  std::vector<std::string> bins_cr_nb1_mednjets    = {"bin41","bin26"}; 
  std::vector<std::string> bins_sr_nb2_mednjets    = {"bin44","bin29"}; 
  std::vector<std::string> bins_sr_nb3_mednjets    = {"bin47","bin32"}; 
  std::vector<std::string> bins_sr_nb4_mednjets    = {"bin50","bin35"}; 
  std::vector<std::string> bins_cr_nb0_highnjets   = {"bin39","bin24"}; 
  std::vector<std::string> bins_cr_nb1_highnjets   = {"bin42","bin27"}; 
  std::vector<std::string> bins_sr_nb2_highnjets   = {"bin45","bin30"}; 
  std::vector<std::string> bins_sr_nb3_highnjets   = {"bin48","bin33"}; 
  std::vector<std::string> bins_sr_nb4_highnjets   = {"bin51","bin36"}; 
  
  std::vector<std::string> bins_all = {"bin37","bin22","bin38","bin23","bin39","bin24","bin40","bin25","bin43","bin28","bin41","bin26","bin42","bin27","bin44","bin29"};
  if(nocrvr){
    bins_all = {};
  }
  if(cardType=="default" || cardType=="mconly"){
    bins_all.push_back("bin46");
    bins_all.push_back("bin31");
   // bins_all.push_back("bin49");
   // bins_all.push_back("bin34");
    bins_all.push_back("bin47");
    bins_all.push_back("bin32");
    bins_all.push_back("bin50");
    bins_all.push_back("bin35");
    bins_all.push_back("bin45");
    bins_all.push_back("bin30");
    bins_all.push_back("bin48");
    bins_all.push_back("bin33");
    bins_all.push_back("bin51");
    bins_all.push_back("bin36");
  }
  //std::vector<std::string> bins_all = {"bin0", "bin1", "bin2", "bin3", "bin4", "bin5"};
  //std::vector<std::string> bins_all = {"bin2", "bin5"};
  /*
  if(includeLowMJ) {
    bins_all.push_back("bin6");
    bins_all.push_back("bin7");
    bins_all.push_back("bin8");
    bins_all.push_back("bin9");
  }
  if(cardType=="default" || cardType=="mconly") {
    bins_all.push_back("bin10");
    bins_all.push_back("bin11");
    bins_all.push_back("bin12");
    bins_all.push_back("bin13");
    bins_all.push_back("bin14");
    bins_all.push_back("bin15");
    bins_all.push_back("bin16");
    bins_all.push_back("bin17");
    bins_all.push_back("bin18");
    bins_all.push_back("bin19");
    bins_all.push_back("bin20");
    bins_all.push_back("bin21");
  }
  */
  /*
  bins.push_back(bins_cr_lowmj);
  bins.push_back(bins_cr_highmj);
  if(cardType=="default" || cardType=="mconly") {
      bins.push_back(bins_sr_lownj_lowmj);
      bins.push_back(bins_sr_lownj_highmj);
      bins.push_back(bins_sr_lownj_vhighmj); 
      bins.push_back(bins_sr_highnj_lowmj);
      bins.push_back(bins_sr_highnj_highmj); 
      bins.push_back(bins_sr_highnj_vhighmj); 
  }
  */
  bins.push_back(bins_cr_nb0_lownjets);
  bins.push_back(bins_cr_nb1_lownjets);
  bins.push_back(bins_cr_nb2_lownjets);
  bins.push_back(bins_cr_nb3_lownjets);
  //bins.push_back(bins_cr_nb4_lownjets);
  bins.push_back(bins_cr_nb0_mednjets);
  bins.push_back(bins_cr_nb1_mednjets);
  bins.push_back(bins_cr_nb0_highnjets);
  bins.push_back(bins_cr_nb1_highnjets);

  if(cardType=="default" || cardType=="mconly"){
      bins.push_back(bins_sr_nb2_mednjets);
      bins.push_back(bins_sr_nb3_mednjets);
      bins.push_back(bins_sr_nb4_mednjets);
      bins.push_back(bins_sr_nb2_highnjets);
      bins.push_back(bins_sr_nb3_highnjets);
      bins.push_back(bins_sr_nb4_highnjets);
  }

  bins.push_back(bins_all);
 
  // include pdf syst to the shapeSysts
  if(includePDFUncert) {
    for(unsigned int i=0; i<100; i++) {
      TString pdf(Form("w_pdf%d", i));
      shapeSysts.push_back(pdf.Data());
    }
  }
   
  // loop over the first indext of the bins vector  
  for(unsigned int ipair=0; ipair<bins.size(); ipair++) 
  { 

  nbins = bins.at(ipair).size(); 

  // which variation file
  std::string dataCardPath = gSystem->pwd();
  if(argc>3) dataCardPath += "/variations/" + inputname;
  else if(cardType=="mconly") dataCardPath += "/variations/11jan2016/35/sum_rescaled_mconly.root";
  else if(cardType=="control") dataCardPath += "/variations/11jan2016/12p9/sum_rescaled_control.root";
  else dataCardPath += "/variations/sum_rescaled.root"; 
  TFile *variations = TFile::Open(dataCardPath.c_str());
  std::ofstream file;
  // card name
  std::string filename("datacards/datacard_M");
  filename+=gluinoMass;
  if(cardType=="control") filename+="_control";
  else if(cardType=="mconly") filename+="_mconly";
  /*
  if(ipair==0) filename+="_cr_lowmj";
  if(ipair==1) filename+="_cr_highmj"; 
  if(cardType!="control") 
  {
      if(ipair==2) filename+="_sr_lownj_lowmj";
      if(ipair==3) filename+="_sr_lownj_highmj";
      if(ipair==4) filename+="_sr_lownj_vhighmj";
      if(ipair==5) filename+="_sr_highnj_lowmj";
      if(ipair==6) filename+="_sr_highnj_highmj";
      if(ipair==7) filename+="_sr_highnj_vhighmj";
  }
  */

  if(ipair==0) filename+="_cr_nb0_lownjets";
  if(ipair==1) filename+="_cr_nb1_lownjets";
  if(ipair==2) filename+="_cr_nb2_lownjets";
  if(ipair==3) filename+="_cr_nb3_lownjets";
  if(ipair==4) filename+="_cr_nb4_lownjets";
  if(ipair==5) filename+="_cr_nb0_mednjets";
  if(ipair==6) filename+="_cr_nb1_mednjets";
  if(ipair==7) filename+="_cr_nb0_highnjets";
  if(ipair==8) filename+="_cr_nb1_highnjets";

  if(cardType!="control")
  {
      if(ipair==9) filename+="_sr_nb2_mednjets";
      if(ipair==10) filename+="_sr_nb3_mednjets";
      if(ipair==11) filename+="_sr_nb4_mednjets";
      if(ipair==12) filename+="_sr_nb2_highnjets";
      if(ipair==13) filename+="_sr_nb3_highnjets";
      if(ipair==14) filename+="_sr_nb4_highnjets";
  }

  if(!includePDFUncert) filename+="_nopdf";

  if(argc>3){
    TString tmpname = inputname;
    tmpname.ReplaceAll("sum_rescaled_mconly","").ReplaceAll(".root","");
    filename += tmpname;
  }

  filename+=".dat";
  file.open(filename);

  // output header
  file << "imax " << nbins << " number of bins" << std::endl;
  file << "jmax " << nprocesses-1 << std::endl;
  file << "kmax * number of nuisance parameters" << std::endl;
  file << "------------------------------------" << std::endl;

  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    if(argc>3)
      file << "shapes * " << bins.at(ipair).at(ibin) << " variations/" << inputname.Data() << " " << bins.at(ipair).at(ibin); //FIXME
    else if(cardType=="mconly")
      file << "shapes * " << bins.at(ipair).at(ibin) << " sum_rescaled_mconly.root " << bins.at(ipair).at(ibin);    
    else if(cardType=="control")
      file << "shapes * " << bins.at(ipair).at(ibin) << " sum_rescaled_control.root " << bins.at(ipair).at(ibin);
    else
      file << "shapes * " << bins.at(ipair).at(ibin) << " sum_rescaled.root " << bins.at(ipair).at(ibin);
    file << "/$PROCESS " << bins.at(ipair).at(ibin) << "/$PROCESS_$SYSTEMATIC" << std::endl;
  }
  file << "------------------------------------" << std::endl;  
  file << "bin          ";

  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    variations->cd(bins.at(ipair).at(ibin).c_str());
    file << bins.at(ipair).at(ibin) << " ";
  }
  file << "\n";
  file << "observation  ";
  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    TString binName(bins.at(ipair).at(ibin));
    TH1F *hist = static_cast<TH1F*>(variations->Get(Form("%s/data_obs",binName.Data())));
    file << hist->Integral() << " ";
    hist->Delete();
  }
  file << "\n";
  file << "------------------------------------" << std::endl;
  file << "bin  ";
  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    for(unsigned int iprocess=0; iprocess<nprocesses; iprocess++) {
      file << bins.at(ipair).at(ibin) << " ";
    }
  }
  file << "\n";
  file << "process  ";
  for(unsigned int index=0; index<nbins*nprocesses; index++) file << processes.at(index%nprocesses) << " ";
  file << "\n";
  file << "process  ";
  for(unsigned int index=0; index<nbins*nprocesses; index++) file << index%nprocesses << " ";
  file << "\n";
  file << "rate  ";
  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    for(unsigned int iprocess=0; iprocess<nprocesses; iprocess++) {
      TString histName(Form("%s/%s", bins.at(ipair).at(ibin).c_str(), processes.at(iprocess).c_str()));
      TH1F *hist = static_cast<TH1F*>(variations->Get(histName));
      file << hist->Integral() << "  ";
    }
  }
  file << "\n------------------------------------" << std::endl;

  //output the normalization sharing between lepton bins
  //outputNormSharing(file, bins.at(ipair),year);

  //output the MJ connection
//  outputMJConnection(file, bins.at(ipair)),year;
  
  //output if you want to see only normalizations between nleps
  outputOnlyNormalization(file, bins.at(ipair), year);

  //output the W+jet normalization and Njets connection
  outputWjets(file, bins.at(ipair), cardType, year);

  // output kappa systematics
  outputkappaSystematics(file, bins.at(ipair), filename, year);


  if(sig_onoff=="on"){
  // output shape systematics
    outputShapeSystematics(file, shapeSysts, year);
  
  // output lognormal lumi uncertainties for signal, wjets and other
    outputLognormalSystematics(file, year);

  // output MC statistics nuisance parameters
  // FIXME: the treatment of emtpy bins should be updated
  //        right now this is done by hand basically using "hasEntry" function at the end of this code
  //        this should be done by checking the bins in the nominal shape 
    outputMCStatisticsSyst(file, bins.at(ipair), signalBinName, year);
  
    outputautoMCStats(file, bins.at(ipair));
  
    file << "\n------------------------------------" << std::endl;
  }
  file.close();
  }
}

// Assumes that processes is of the format {signal, "qcd", "ttbar", ... } 
void outputNormSharing(std::ofstream &file, const std::vector<std::string> &bins, TString year){

  //create map between bin name and bin index
  map<string, int> bindex;
  for(uint ibin=0; ibin<nbins; ibin++)
    bindex[bins[ibin]]=ibin;

  //create template line
  TString line;
  for(uint idash=0; idash<(nprocesses*nbins); idash++)
    line+="-    ";

  TString tmpLine;
  for(auto jbin:bins){ // QCD
    tmpLine = line;
    /*
       if(jbin=="bin0"){
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin3"]*nprocesses+1),1,"5");
       tmpLine.Prepend("normqcd_vlownjets         lnU  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin1"){
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin2"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin4"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin5"]*nprocesses+1),1,"5");
       tmpLine.Prepend("normqcd_lownjets          lnU  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin18"){
       tmpLine.Replace(5*(bindex["bin11"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin16"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin20"]*nprocesses+1),1,"5");
       tmpLine.Prepend("normqcd_mednjets          lnU  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin19"){
       tmpLine.Replace(5*(bindex["bin10"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin12"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
       tmpLine.Replace(5*(bindex["bin21"]*nprocesses+1),1,"5");
       tmpLine.Prepend("normqcd_highnjets         lnU  ");
       file << tmpLine.Data() << endl;
       }    
       */
    if(jbin=="bin37"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin22"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+1),1,"5");
      tmpLine.Prepend(Form("normqcd_lownjets_%s          lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin38"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin23"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+1),1,"5");
      tmpLine.Prepend(Form("normqcd_mednjets_%s          lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin39"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin24"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+1),1,"5");
      tmpLine.Prepend(Form("normqcd_highnjets_%s         lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }

  }
  cout<<"5"<<endl;
  for(auto jbin:bins){ // ttbar 
    tmpLine = line;
    /*
       if(jbin=="bin2"){
       tmpLine.Replace(5*(bindex["bin0"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin1"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin3"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin4"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin5"]*nprocesses+2),1,"5");
       tmpLine.Prepend("normtt_lownjets           lnU  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin11"){
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin16"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin18"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin20"]*nprocesses+2),1,"5");
       tmpLine.Prepend("normtt_mednjets           lnU  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin12"){
       tmpLine.Replace(5*(bindex["bin10"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin19"]*nprocesses+2),1,"5");
       tmpLine.Replace(5*(bindex["bin21"]*nprocesses+2),1,"5");
       tmpLine.Prepend("normtt_highnjets          lnU  "); 
       file << tmpLine.Data() << endl;
       }    
       */
    if(jbin=="bin22"){
      tmpLine.Replace(5*(bindex["bin37"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+2),1,"5");
      tmpLine.Prepend(Form("normtt_lownjets_%s           lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin23"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+2),1,"5");
      tmpLine.Prepend(Form("normtt_mednjets_%s           lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin24"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+2),1,"5");
      tmpLine.Prepend(Form("normtt_highnjets_%s          lnU  ",year.Data()));
      file << tmpLine.Data() << endl;
    }
  }
}

void outputOnlyNormalization(std::ofstream &file, const std::vector<std::string> &bins, TString year){
  map<string, int> bindex;
  for(uint ibin=0; ibin<nbins; ibin++){
    bindex[bins[ibin]]=ibin;
  }

  TString line;
  for(uint idash=0; idash<(nprocesses*nbins); idash++){
    line+="-    ";
  }

  int numbin;
  TString tmpLine;  
  TString tmpbin;
  /*
     for(auto jbin:bins){ // QCD 
     tmpbin  = jbin;
     tmpbin.Replace(0,3,"");
     numbin = atoi(tmpbin);
     tmpLine = line;
     tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+1),1,"5");
     tmpLine.Prepend(Form("normqcd_bin%d             lnU  ",numbin));
     file << tmpLine.Data() << endl;
     }
     for(auto jbin:bins){ // QCD 
     tmpbin  = jbin;
     tmpbin.Replace(0,3,"");
     numbin = atoi(tmpbin);
     tmpLine = line;
     tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+2),1,"5");
     tmpLine.Prepend(Form("normttbar_bin%d           lnU  ",numbin));
     file << tmpLine.Data() << endl;
     }
     */
  for(auto jbin:bins){ // QCD 
    tmpbin  = jbin;
    tmpbin.Replace(0,3,"");
    numbin = atoi(tmpbin);
    if(numbin > 36) continue;
    tmpLine = line;
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+1),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+15)]*nprocesses+1),1,"5");
    tmpLine.Prepend(Form("normqcd_bin%d_bin%d_%s                   lnU  ",numbin,numbin+15,year.Data()));
    file << tmpLine.Data() << endl;
  }
  for(auto jbin:bins){ // QCD 
    tmpbin  = jbin;
    tmpbin.Replace(0,3,"");
    numbin = atoi(tmpbin);
    if(numbin > 36) continue;
    else if(numbin > 21 &&numbin < 25){
    tmpLine = line;
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+15)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+3)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+18)]*nprocesses+2),1,"5");
    tmpLine.Prepend(Form("normttbar_bin%d_bin%d_bin%d_bin%d_%s     lnU  ",numbin,numbin+15,numbin+3,numbin+18,year.Data()));
    file << tmpLine.Data() << endl;
    }
    else if(numbin > 24 && numbin < 28){
    tmpLine = line;
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin-3)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+12)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+15)]*nprocesses+2),1,"5");
    tmpLine.Prepend(Form("normttbar_bin%d_bin%d_bin%d_bin%d_%s     lnU  ",numbin-3,numbin+12,numbin,numbin+15,year.Data()));
    file << tmpLine.Data() << endl;
  }
    else{
    tmpLine = line;
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin)]*nprocesses+2),1,"5");
    tmpLine.Replace(5*(bindex[Form("bin%d",numbin+15)]*nprocesses+2),1,"5");
    tmpLine.Prepend(Form("normttbar_bin%d_bin%d_%s                 lnU  ",numbin,numbin+15,year.Data()));
    file << tmpLine.Data() << endl;
    }
  }
}

// Assumes that processes is of the format {signal, "qcd", "ttbar", ... } 
void outputMJConnection(std::ofstream &file, const std::vector<std::string> &bins, TString year){

  //create map between bin name and bin index
  map<string, int> bindex;
  for(uint ibin=0; ibin<nbins; ibin++)
    bindex[bins[ibin]]=ibin;

  //create template line
  TString line;
  for(uint idash=0; idash<(nprocesses*nbins); idash++)
    line+="-    ";

  TString tmpLine;
  for(auto jbin:bins){ // QCD 
    tmpLine = line;
    /*
       if(jbin=="bin0"){
       tmpLine.Replace(5*(bindex["bin3"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin0"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin0_bin3         lnN  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin1"){
       tmpLine.Replace(5*(bindex["bin5"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin4"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin2"]*nprocesses+1),4,"1.01");
       tmpLine.Replace(5*(bindex["bin1"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin1_2_bin4_5     lnN  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin11"){
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin16"]*nprocesses+1),4,"1.01");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin11"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin16_11_bin17_14 lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin14"){
       tmpLine.Replace(5*(bindex["bin20"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin18"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+1),4,"1.01");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin17_14_bin18_20 lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin15"){
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin12"]*nprocesses+1),4,"1.01");
       tmpLine.Replace(5*(bindex["bin10"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin10_12_bin13_15 lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin19"){
       tmpLine.Replace(5*(bindex["bin21"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin19"]*nprocesses+1),4,"2.00");
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+1),4,"1.01");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+1),4,"1.01");
       tmpLine.Prepend("normqcd_bin13_15_bin19_21 lnN  ");
       file << tmpLine.Data() << endl;
       */
    if(jbin=="bin37"){
      tmpLine.Replace(5*(bindex["bin37"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin22"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin37_40_bin22_25_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin40_43_bin25_28_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin43"){ 
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin43_46_bin28_31_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }
    else if(jbin=="bin46"){
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend(Form("normqcd_bin46_49_bin31_34_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }
    else if(jbin=="bin38"){
      tmpLine.Replace(5*(bindex["bin38"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin23"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin38_41_bin23_26_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin41_44_bin26_29_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin44"){
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin44_47_bin29_32_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }  
    else if(jbin=="bin47"){
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend(Form("normqcd_bin47_50_bin32_35_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }  
    else if(jbin=="bin39"){
      tmpLine.Replace(5*(bindex["bin39"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin24"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin39_42_bin24_27_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin42"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin42_45_bin27_30_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin45"){
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend(Form("normqcd_bin45_48_bin30_33_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin48"){
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend(Form("normqcd_bin48_51_bin33_36_%s lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
  }
  for(auto jbin:bins){ // ttbar 
    tmpLine = line;
    /*
       if(jbin=="bin0"){
       tmpLine.Replace(5*(bindex["bin5"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin4"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin3"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin2"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin1"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin0"]*nprocesses+2),4,"1.01");
       tmpLine.Prepend("normtt_bin0_1_2_bin3_4_5  lnN  ");
       file << tmpLine.Data() << endl;
       }
       else if(jbin=="bin11"){
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin16"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin11"]*nprocesses+2),4,"1.01");
       tmpLine.Prepend("normtt_bin16_11_bin17_14  lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin14"){
       tmpLine.Replace(5*(bindex["bin20"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin18"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin17"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin14"]*nprocesses+2),4,"1.01");
       tmpLine.Prepend("normtt_bin17_14_bin18_20  lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin15"){
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin12"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin10"]*nprocesses+2),4,"1.01");
       tmpLine.Prepend("normtt_bin10_12_bin13_15  lnN  ");
       file << tmpLine.Data() << endl;
       }    
       else if(jbin=="bin19"){
       tmpLine.Replace(5*(bindex["bin21"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin19"]*nprocesses+2),4,"2.00");
       tmpLine.Replace(5*(bindex["bin15"]*nprocesses+2),4,"1.01");
       tmpLine.Replace(5*(bindex["bin13"]*nprocesses+2),4,"1.01");
       tmpLine.Prepend("normtt_bin13_15_bin19_21  lnN  ");
       file << tmpLine.Data() << endl;
       }
       */    
    if(jbin=="bin37"){
      tmpLine.Replace(5*(bindex["bin37"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin22"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin37_40_bin22_25_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin40_43_bin25_28_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin43"){
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin43_46_bin28_31_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin46"){
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend(Form("normtt_bin46_49_bin31_34_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin38"){
      tmpLine.Replace(5*(bindex["bin38"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin23"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin38_41_bin23_26_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin41_44_bin26_29_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin44"){
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin44_47_bin29_32_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin47"){
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend(Form("normtt_bin47_50_bin32_35_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin39"){
      tmpLine.Replace(5*(bindex["bin39"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin24"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin39_42_bin24_27_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    } 
    else if(jbin=="bin42"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin42_45_bin27_30_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    } 
    else if(jbin=="bin45"){
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend(Form("normtt_bin45_48_bin30_33_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    } 
    else if(jbin=="bin48"){
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend(Form("normtt_bin48_51_bin33_36_%s  lnN  ",year.Data()));
      file << tmpLine.Data() << endl; 
    } 
  }
  }

  // Assumes that processes is of the format {signal, "qcd", "ttbar", "wjets", "other" } 
  void outputWjets(std::ofstream &file, const std::vector<std::string> &bins, const std::string cardType, TString year){

    TString mednjcon_, highnjcon_;
    if(year=="2016"){
      mednjcon_ = "1.25";
      highnjcon_ = "1.33";
    }
    if(year=="2017"){
      mednjcon_ = "1.35";
      highnjcon_ = "1.33";
    }
    if(year=="2018"){
      mednjcon_ = "1.26";
      highnjcon_ = "1.30";
    }
    //create map between bin name and bin index
    map<string, int> bindex;
    for(uint ibin=22; ibin<52; ibin++){
      bindex[Form("bin%d",ibin)]=9999;
    }
    for(uint ibin=0; ibin<nbins; ibin++){
      bindex[bins[ibin]]=ibin;
    }

    // overall normalization   
    TString line_norm;
    for(uint idash=0; idash<nbins; idash++)
      line_norm+="-    -    -    2    -    ";
    line_norm.Prepend(Form("normwjets_%s                 lnU  ",year.Data()));
    file << line_norm.Data() << endl;

    if(cardType!="control")  // do not need Njets connection for CR fit
    { 
      //create template line
      TString line;
      for(uint idash=0; idash<(nprocesses*nbins); idash++)
        line+="-    ";

      TString tmpLine;
      TString tmpbin;
      int numbin;
      vector<TString> lownj_bins, mednj_bins, highnj_bins;
      for(uint nbc=0 ; nbc<5 ; nbc++){
        lownj_bins.push_back(Form("bin%d",22+nbc*3));
        mednj_bins.push_back(Form("bin%d",22+nbc*3+1));
        highnj_bins.push_back(Form("bin%d",22+nbc*3+2));
        lownj_bins.push_back(Form("bin%d",37+nbc*3));
        mednj_bins.push_back(Form("bin%d",37+nbc*3+1));
        highnj_bins.push_back(Form("bin%d",37+nbc*3+2));
      }
      bool flag_brk(true);
      for(auto jbin:bins){
        tmpLine = line;        
        tmpbin  = jbin;
        tmpbin.Replace(0,3,"");
        numbin = atoi(tmpbin);
        

        if((numbin%3==1||numbin%3==2)&&flag_brk){
          /*
          tmpLine.Replace(5*(bindex["bin38"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin41"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin44"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin47"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin50"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin23"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin26"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin29"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin32"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin35"]*nprocesses+3),4,"1.50");
          tmpLine.Replace(5*(bindex["bin37"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin40"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin43"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin46"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin49"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin22"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin25"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin28"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin31"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin34"]*nprocesses+3),4,"1.01");
          */
          for(auto njb:lownj_bins){
            if(bindex[njb.Data()]==9999) continue;
            tmpLine.Replace(5*(bindex[njb.Data()]*nprocesses+3),4,"1.01");
          }
          for(auto njb:mednj_bins){
            if(bindex[njb.Data()]==9999) continue;
            tmpLine.Replace(5*(bindex[njb.Data()]*nprocesses+3),4, mednjcon_.Data());
          }
          tmpLine.Prepend(Form("normwjets_mednjets_%s        lnN  ",year.Data()));
          file << tmpLine.Data() << endl;
          flag_brk=false;
        }
      }
      flag_brk=true;
      for(auto jbin:bins){
        tmpLine = line;        
        tmpbin  = jbin;
        tmpbin.Replace(0,3,"");
        numbin = atoi(tmpbin);

 
        if((numbin%3==2||numbin%3==0)&&flag_brk){
          /*
          tmpLine.Replace(5*(bindex["bin39"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin42"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin45"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin48"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin51"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin24"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin27"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin30"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin33"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin36"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin38"]*nprocesses+3),4,"1.35");
          tmpLine.Replace(5*(bindex["bin41"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin44"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin47"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin50"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin23"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin26"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin29"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin32"]*nprocesses+3),4,"1.01");
          tmpLine.Replace(5*(bindex["bin35"]*nprocesses+3),4,"1.01");
          */
          for(auto njb:mednj_bins){
            if(bindex[njb.Data()]==9999) continue;
            tmpLine.Replace(5*(bindex[njb.Data()]*nprocesses+3),4,"1.01");
          }
          for(auto njb:highnj_bins){
            if(bindex[njb.Data()]==9999) continue;
            tmpLine.Replace(5*(bindex[njb.Data()]*nprocesses+3),4,highnjcon_.Data());
          }
          tmpLine.Prepend(Form("normwjets_highnjets_%s       lnN  ",year.Data()));
          file << tmpLine.Data() << endl;
          flag_brk=false;
        }
      }
    }
  }

  void outputLognormalSystematics(std::ofstream &file, TString year)
  {
    // luminosity uncertainty is 2.6% for 2016 data
    // luminosity uncertainty is 2.3% for 2017 data
    // luminosity uncertainty is 2.5% for 2018 data
    file << "lumi  lnN  ";
    for(unsigned int ibin=0; ibin<nbins; ibin++) {
      if(year == "2016") file << "1.026 - - - 1.026 ";
      if(year == "2017") file << "1.023 - - - 1.023 ";
      if(year == "2018") file << "1.025 - - - 1.025 ";
    }
    file << std::endl;

  }

  void outputShapeSystematics(std::ofstream &file, const std::vector<std::string> shapesysts, TString year)
  {
    for(unsigned int isyst=0; isyst<shapesysts.size(); isyst++) {
      file << shapesysts.at(isyst) << "_" << year << "     shape     ";
      if(shapesysts.at(isyst).find("pdf")!=std::string::npos) {
        // there are 100 nnpdf variations and so each needs to be scaled down by a factor 1/sqrt(100)
        //for(unsigned int index=0; index<nbins; index++) file << "0.1 0.1 0.1 0.1 0.1 ";
        for(unsigned int index=0; index<nbins; index++) file << " 0.1 - - - 0.1 ";//accept systematics to signal and other
      }
      else {
        //for(unsigned int index=0; index<nbins*nprocesses; index++) file << 1.0 << " ";// one sigma
        for(unsigned int index=0; index<nbins; index++) file << " 1 - - - 1 ";//accept systematics to signal and other
      }
      file << "\n";
    }
  }

  void outputkappaSystematics(std::ofstream &file, const std::vector<std::string> &bins, const std::string filename, TString year)
  {
    map<string, int> bindex;
    map<TString, int> procind;
    vector<TString> process = {"qcd","ttbar","wjets"};
    for(uint ibin=0; ibin<nbins; ibin++){
      bindex[bins[ibin]]=ibin;
    }
    for(uint iproc=0; iproc<3; iproc++){
      procind[process.at(iproc)]=iproc+1;
    }
    for(uint ibin=22; ibin<52; ibin++){
      if(bindex.find(Form("bin%d",ibin))==bindex.end()){
        bindex[Form("bin%d",ibin)]=99999;
      }
      else{
        continue;
      }
    }

    if(merge_78=="off") cout << "2017-2018 not merged" <<endl; 
    else if(merge_78=="on"){
      year = "20178";
      cout<< "2017-2018 merged : 20178"  << endl;
    }
    for(auto iproc : process){
      if(filename.find("lownjets")!=std::string::npos){
        for(int i_kap=1; i_kap<3; i_kap++){
          file << Form("kappa%d_njets45_%s_%s", i_kap, iproc.Data(), year.Data()) << "             shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",22)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",25)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",28)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",31)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",34)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";
        }
      }
      else if(filename.find("mednjets")!=std::string::npos){
        for(int i_kap=1; i_kap<3; i_kap++){
          file << Form("kappa%d_njets67_%s_%s", i_kap, iproc.Data(), year.Data()) << "             shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",23)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",26)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",29)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",32)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",35)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";
        }
      }
      else if(filename.find("highnjets")!=std::string::npos){
        for(int i_kap=1; i_kap<3; i_kap++){
          file << Form("kappa%d_njets8_%s_%s", i_kap, iproc.Data(), year.Data()) << "              shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",24)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",27)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",30)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",33)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",36)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";
        }
      }
      else{  
        for(int i_kap=1; i_kap<3; i_kap++){
          file << Form("kappa%d_njets45_%s_%s", i_kap, iproc.Data(), year.Data()) << "             shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",22)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",25)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",28)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",31)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",34)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";

          file << Form("kappa%d_njets67_%s_%s", i_kap, iproc.Data(), year.Data()) << "             shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",23)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",26)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",29)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",32)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",35)]&&int(index%5)==procind[iproc])file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";

          file << Form("kappa%d_njets8_%s_%s", i_kap, iproc.Data(), year.Data()) << "              shape     ";
          for(unsigned int index=0; index<nbins*nprocesses; index++){
            if(index%nprocesses==0) file << "-    ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",24)]&&(int(index%5)==procind[iproc]))file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",27)]&&(int(index%5)==procind[iproc]))file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",30)]&&(int(index%5)==procind[iproc]))file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",33)]&&(int(index%5)==procind[iproc]))file << "1.00" << " ";
            else if(int(index/nprocesses)==bindex[Form("bin%d",36)]&&(int(index%5)==procind[iproc]))file << "1.00" << " ";
            else file << "-    ";
          }
          file << "\n";
        }
      }
    }
}

// outputs MC statistical uncertainties
void outputMCStatisticsSyst(std::ofstream &file, const std::vector<std::string> &bins, const std::string & signalBinName, TString year)
{
  //  unsigned int nbins=bins.size();
  const unsigned int maxB=4;

  // only signal, qcd, and ttbar have non-negligible MC statistics uncertainties
  std::vector<std::string> samples = {signalBinName, "qcd", "ttbar"};
  for(auto isample : samples) {
      for(unsigned int ibin = 0; ibin<bins.size(); ibin++) {
          for(unsigned int ibbin=1; ibbin<maxB+1; ibbin++) {
              if(!hasEntry(isample, bins.at(ibin), ibbin)) continue;
              file << "mcstat_" << isample << "_" << bins.at(ibin) << "_nb" << ibbin << "_" << year << " shape ";
              for(unsigned int ientry = 0; ientry<bins.size(); ientry++) {
                  if(ientry == ibin ) {
                      if( isample.find("signal")!=std::string::npos) file << "1 - - - - ";
                      else if( isample == "qcd") file << "- 1 - - - ";
                      else if( isample == "ttbar" ) file << "- - 1 - - ";
                      else if( isample == "wjets" ) file << "- - - 1 - ";
                      else if( isample == "other" ) file << "- - - - 1 ";
                  }
                  else file << "- - - - - ";
              }
              file << "\n";
          }
      }
  }
}

void outputautoMCStats( std::ofstream &file,const std::vector<std::string> &bins){
 int threshold = 5;// Gaussian approximation threshold
 for(auto ibin : bins){
   file << ibin << " autoMCStats " << threshold << "\n";
 }
}

// exclude by hand following bins that have no entries:
// signal_mcstat_signal_bin0_nb3
// signal_mcstat_signal_bin2_nb4
// signal_mcstat_signal_bin3_nb4
// signal_mcstat_signal_bin5_nb4
// ttbar_mcstat_ttbar_bin0_nb4
// ttbar_mcstat_ttbar_bin5_nb4
// qcd_mcstat_qcd_bin5_nb3
// qcd_mcstat_qcd_bin5_nb4
// should do this from the histograms themselves!
bool hasEntry(const std::string &sample, const std::string &bin, const int nB)
{
/*
  if(sample.find("signal_M1000")!=std::string::npos) {
    if(bin=="bin2" && nB==4) return false;
    if(bin=="bin3" && nB==1) return false;
    if(bin=="bin3" && nB==3) return false;
    if(bin=="bin3" && nB==4) return false;
  }
  if(sample.find("signal_M1100")!=std::string::npos) {
    if(bin=="bin3" && nB==4) return false;
    if(bin=="bin5" && nB==4) return false;
  }
  if(sample.find("signal_M1200")!=std::string::npos) {
    if(bin=="bin0" && nB==4) return false;
    if(bin=="bin2" && nB==4) return false;
    if(bin=="bin3" && nB==4) return false;
    if(bin=="bin5" && nB==4) return false;
  }
  if(sample.find("signal_M1300")!=std::string::npos) {
    if(bin=="bin2" && nB==4) return false;
    if(bin=="bin3" && nB==1) return false;
  }
  if(sample.find("signal_M1400")!=std::string::npos) {
    if(bin=="bin0" && nB==4) return false;
  }
  //if(sample=="ttbar") {
    //if(bin=="bin0" && nB==4) return false;
    //if(bin=="bin5" && nB==4) return false;
  //}
*/
  if(sample=="qcd") {
    //if(bin=="bin5" && nB==3) return false;
    //if(bin=="bin5" && nB==4) return false;
    if(bin=="bin5" && nB==4) return true; 
    //if(bin=="bin11" && nB==4) return false;
    //if(bin=="bin14" && nB==4) return false;
    //if(bin=="bin15" && nB==4) return false;
  }

  return true;
}
