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

void outputWjets(std::ofstream &file, const std::vector<std::string> &bins, const std::string cardType);
void outputNormSharing(std::ofstream &file, const std::vector<std::string> &bins);
void outputFreeParameters(std::ofstream &file, const std::vector<std::string> &bins);
void outputMJConnection(std::ofstream &file, const std::vector<std::string> &bins);
void outputShapeSystematics(std::ofstream &file, const std::vector<std::string> shapeSysts);
void outputLognormalSystematics(std::ofstream &file);
void outputMCStatisticsSyst(std::ofstream &file, const std::vector<std::string> &bins, const std::string & signalBinName);
// determine if a histogram has an entry for a given nB
bool hasEntry(const std::string &sample, const std::string &bin, const int nB);

namespace {
  unsigned int nbins;
  unsigned int nprocesses;
}

using namespace std;

int main(int argc, char *argv[])
{
  bool includePDFUncert = false;
  bool includeLowMJ = false;
//  bool includeSignalRegion = true;

  // signal is added later
  std::vector<std::string> processes = { "qcd", "ttbar", "wjets", "other"};
  std::vector<std::string> shapeSysts = {"btag_bc", "btag_udsg",
					                     "gs45", "gs67", "gs89", "gs10Inf",
					                     //"jes", "jer",
					                     /*"pileup",*/"lep_eff", "ttbar_pt",
					                     "qcd_flavor",
					                     "qcd_muf", "qcd_mur", "qcd_murf", 
					                     //"isr",
					                     "ttbar_muf", "ttbar_mur", "ttbar_murf",
					                     "wjets_muf", "wjets_mur", "wjets_murf",
					                     "other_muf", "other_mur", "other_murf",
					                     /*"fs_btag_bc", "fs_btag_udsg", "fs_lep_eff"*/}; // temporarily removed

  shapeSysts={}; 

  std::string gluinoMass;
  std::string signalBinName;
  std::string cardType;
  TString inputname;
  if(argc<3) {
    std::cout << "Syntax: make_rpv_datacard.exe [gluino mass, in GeV] [default/control/mconly] [filename]" << std::endl;
    return 1;
  }
  else {
    std::stringstream ss;
    gluinoMass = argv[1];
    ss << "signal_M" << gluinoMass;
    signalBinName = ss.str();
    // this is supposed to be the first entry in the process list
    processes.insert(processes.begin(), signalBinName);

    cardType=argv[2];
    if(cardType!="control" && cardType!="default" && cardType!="mconly") {
      std::cout << "Syntax: make_rpv_datacard.exe [gluino mass, in GeV] [default/control/mconly]" << std::endl;
      return 1;
    }
    if(argc>3)
      inputname = argv[3];

//    else {
//      if(cardType=="control") includeSignalRegion=false;
//      if(cardType=="default") includeSignalRegion=true;
//      if(cardType=="mconly")  includeSignalRegion=true;
//    }
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

  std::vector<std::string> bins_cr_lowmj        = {"bin0", "bin1", "bin2"};
  std::vector<std::string> bins_cr_highmj       = {"bin3", "bin4", "bin5"};
  std::vector<std::string> bins_sr_lownj_lowmj  = {"bin16", "bin11"};
  std::vector<std::string> bins_sr_lownj_highmj = {"bin17", "bin14"};
  std::vector<std::string> bins_sr_lownj_vhighmj = {"bin18", "bin20"};
  std::vector<std::string> bins_sr_highnj_lowmj  = {"bin10", "bin12"};
  std::vector<std::string> bins_sr_highnj_highmj = {"bin13", "bin15"};
  std::vector<std::string> bins_sr_highnj_vhighmj = {"bin19", "bin21"};
  
  std::vector<std::string> bins_cr_nb1_lownjets    = {"bin40","bin25"}; 
  std::vector<std::string> bins_cr_nb2_lownjets    = {"bin43","bin28"}; 
  std::vector<std::string> bins_cr_nb3_lownjets    = {"bin46","bin31"}; 
  std::vector<std::string> bins_cr_nb4_lownjets    = {"bin49","bin34"}; 
  std::vector<std::string> bins_cr_nb1_mednjets    = {"bin41","bin26"}; 
  std::vector<std::string> bins_sr_nb2_mednjets    = {"bin44","bin29"}; 
  std::vector<std::string> bins_sr_nb3_mednjets    = {"bin47","bin32"}; 
  std::vector<std::string> bins_sr_nb4_mednjets    = {"bin50","bin35"}; 
  std::vector<std::string> bins_cr_nb1_highnjets   = {"bin42","bin27"}; 
  std::vector<std::string> bins_sr_nb2_highnjets   = {"bin45","bin30"}; 
  std::vector<std::string> bins_sr_nb3_highnjets   = {"bin48","bin33"}; 
  std::vector<std::string> bins_sr_nb4_highnjets   = {"bin51","bin36"}; 
  
  std::vector<std::string> bins_all = {"bin40","bin25","bin43","bin28","bin46","bin31","bin49","bin34","bin41","bin26","bin42","bin27"};
  if(cardType=="default" || cardType=="mconly"){
    bins_all.push_back("bin44");
    bins_all.push_back("bin29");
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
  bins.push_back(bins_cr_nb1_lownjets);
  bins.push_back(bins_cr_nb2_lownjets);
  bins.push_back(bins_cr_nb3_lownjets);
  bins.push_back(bins_cr_nb4_lownjets);
  bins.push_back(bins_cr_nb1_mednjets);
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
  std::string filename("datacard_M");
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
  if(ipair==0) filename+="_cr_nb1_lownjets";
  if(ipair==1) filename+="_cr_nb2_lownjets";
  if(ipair==2) filename+="_cr_nb3_lownjets";
  if(ipair==3) filename+="_cr_nb4_lownjets";
  if(ipair==4) filename+="_cr_nb1_mednjets";
  if(ipair==5) filename+="_cr_nb1_highnjets";

  if(cardType!="control")
  {
      if(ipair==6) filename+="_sr_nb2_mednjets";
      if(ipair==7) filename+="_sr_nb3_mednjets";
      if(ipair==8) filename+="_sr_nb4_mednjets";
      if(ipair==9) filename+="_sr_nb2_highnjets";
      if(ipair==10) filename+="_sr_nb3_highnjets";
      if(ipair==11) filename+="_sr_nb4_highnjets";
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
      file << "shapes * " << bins.at(ipair).at(ibin) << " variations/" << inputname.Data() << " " << bins.at(ipair).at(ibin);    
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

  outputFreeParameters(file, bins.at(ipair));
  //output the normalization sharing between lepton bins
  //outputNormSharing(file, bins.at(ipair));

  //output the MJ connection
  //outputMJConnection(file, bins.at(ipair));

  //output the W+jet normalization and Njets connection
  //outputWjets(file, bins.at(ipair), cardType);

  // output shape systematics
//  outputShapeSystematics(file, shapeSysts);
  
  // output lognormal lumi uncertainties for signal, wjets and other
//  outputLognormalSystematics(file);

  // output MC statistics nuisance parameters
  // FIXME: the treatment of emtpy bins should be updated
  //        right now this is done by hand basically using "hasEntry" function at the end of this code
  //        this should be done by checking the bins in the nominal shape 
//  outputMCStatisticsSyst(file, bins.at(ipair), signalBinName);

  file.close();
  }
}

void outputFreeParameters(std::ofstream &file, const std::vector<std::string> &bins){

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
    tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
    tmpLine.Prepend("normqcd_"+jbin+"                 lnU  ");
    file << tmpLine.Data() <<endl;
    }
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
    /*if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_lownjets          lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_mednjets          lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin32"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_highnjets         lnU  ");
      file << tmpLine.Data() << endl;
    }

  }
*/
  for(auto jbin:bins){
    tmpLine = line;
    tmpLine.Replace(5*(bindex[jbin]*nprocesses),4,"1.20");
    tmpLine.Prepend("normsignal_"+jbin+"              lnN  ");
    file << tmpLine.Data() << endl; 
  }
  for(auto jbin:bins){
    tmpLine = line;
    tmpLine.Replace(5*(bindex[jbin]*nprocesses+3),1,"5");
    tmpLine.Prepend("normwjets_"+jbin+"               lnU  ");
    file << tmpLine.Data() << endl; 
  }
  for(auto jbin:bins){ // ttbar 
    tmpLine = line;
    tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
    tmpLine.Prepend("normtt_"+jbin+"                  lnU  ");
    file << tmpLine.Data() << endl; 
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
    /*
    if(jbin=="bin25"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_lownjets           lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin26"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_mednjets           lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin27"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_highnjets          lnU  ");
      file << tmpLine.Data() << endl;
*/
    
  }
}



// Assumes that processes is of the format {signal, "qcd", "ttbar", ... } 
void outputNormSharing(std::ofstream &file, const std::vector<std::string> &bins){

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
    if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_lownjets          lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_mednjets          lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin32"){
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+1),1,"5");
      tmpLine.Prepend("normqcd_highnjets         lnU  ");
      file << tmpLine.Data() << endl;
    }

  }

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
    if(jbin=="bin25"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_lownjets           lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin26"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_mednjets           lnU  ");
      file << tmpLine.Data() << endl;
    }
    else if(jbin=="bin27"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex[jbin]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),1,"5");
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+2),1,"5");
      tmpLine.Prepend("normtt_highnjets          lnU  ");
      file << tmpLine.Data() << endl;
    }
  }
}

// Assumes that processes is of the format {signal, "qcd", "ttbar", ... } 
void outputMJConnection(std::ofstream &file, const std::vector<std::string> &bins){

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
    if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin40_43_bin25_28 lnN  ");
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin43"){ 
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin43_46_bin28_31 lnN  ");
      file << tmpLine.Data() << endl; 
    }
    else if(jbin=="bin46"){
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend("normqcd_bin46_49_bin31_34 lnN  ");
      file << tmpLine.Data() << endl; 
    }
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin41_44_bin26_29 lnN  ");
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin44"){
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin44_47_bin29_32 lnN  ");
      file << tmpLine.Data() << endl; 
    }  
    else if(jbin=="bin47"){
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend("normqcd_bin47_50_bin32_35 lnN  ");
      file << tmpLine.Data() << endl; 
    }  
    else if(jbin=="bin42"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin42_45_bin27_30 lnN  ");
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin45"){
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),4,"1.10");  
      tmpLine.Prepend("normqcd_bin45_48_bin30_33 lnN  ");
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin48"){
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+1),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+1),4,"1.10"); 
      tmpLine.Prepend("normqcd_bin48_51_bin33_36 lnN  ");
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
    if(jbin=="bin40"){
      tmpLine.Replace(5*(bindex["bin40"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin25"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin40_43_bin25_28  lnN  ");
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin43"){
      tmpLine.Replace(5*(bindex["bin43"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin28"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin43_46_bin28_31  lnN  ");
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin46"){
      tmpLine.Replace(5*(bindex["bin46"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin49"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin31"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin34"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend("normtt_bin46_49_bin31_34  lnN  ");
      file << tmpLine.Data() << endl; 
    }    
    else if(jbin=="bin41"){
      tmpLine.Replace(5*(bindex["bin41"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin26"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin41_44_bin26_29  lnN  ");
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin44"){
      tmpLine.Replace(5*(bindex["bin44"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin29"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin44_47_bin29_32  lnN  ");
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin47"){
      tmpLine.Replace(5*(bindex["bin47"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin50"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin32"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin35"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend("normtt_bin47_50_bin32_35  lnN  ");
      file << tmpLine.Data() << endl; 
    }   
    else if(jbin=="bin42"){
      tmpLine.Replace(5*(bindex["bin42"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin27"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin42_45_bin27_30  lnN  ");
      file << tmpLine.Data() << endl; 
    } 
    else if(jbin=="bin45"){
      tmpLine.Replace(5*(bindex["bin45"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin30"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),4,"1.10");  
      tmpLine.Prepend("normtt_bin45_48_bin30_33  lnN  ");
      file << tmpLine.Data() << endl; 
    } 
    else if(jbin=="bin48"){
      tmpLine.Replace(5*(bindex["bin48"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin51"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin33"]*nprocesses+2),4,"1.10");  
      tmpLine.Replace(5*(bindex["bin36"]*nprocesses+2),4,"1.10"); 
      tmpLine.Prepend("normtt_bin48_51_bin33_36  lnN  ");
      file << tmpLine.Data() << endl; 
    } 
  }
}

// Assumes that processes is of the format {signal, "qcd", "ttbar", "wjets", "other" } 
void outputWjets(std::ofstream &file, const std::vector<std::string> &bins, const std::string cardType){

    //create map between bin name and bin index
    map<string, int> bindex;
    for(uint ibin=0; ibin<nbins; ibin++)
        bindex[bins[ibin]]=ibin;

    // overall normalization   
    TString line_norm;
    for(uint idash=0; idash<nbins; idash++)
        line_norm+="-    -    -    2    -    ";
    line_norm.Prepend("normwjets                 lnU  ");
    file << line_norm.Data() << endl;

    if(cardType!="control")  // do not need Njets connection for CR fit
    { 
        //create template line
        TString line;
        for(uint idash=0; idash<(nprocesses*nbins); idash++)
            line+="-    ";

        TString tmpLine;
        for(auto jbin:bins){
            tmpLine = line;
            /*
            if(jbin=="bin0"){
                tmpLine.Replace(5*(bindex["bin20"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin18"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin17"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin16"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin14"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin11"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin5"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin4"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin3"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin2"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin1"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin0"]*nprocesses+3),4,"1.01");
                tmpLine.Prepend("normwjets_mednjets        lnN  ");
                file << tmpLine.Data() << endl;
            }
            if(jbin=="bin11"){
                tmpLine.Replace(5*(bindex["bin21"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin20"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin19"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin18"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin17"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin16"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin15"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin14"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin13"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin12"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin11"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin10"]*nprocesses+3),4,"1.35");
                tmpLine.Prepend("normwjets_highnjets       lnN  ");
                file << tmpLine.Data() << endl;
            }
            */
            if(jbin=="bin40"){
                tmpLine.Replace(5*(bindex["bin41"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin44"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin47"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin50"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin26"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin29"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin32"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin35"]*nprocesses+3),4,"1.50");
                tmpLine.Replace(5*(bindex["bin40"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin43"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin46"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin49"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin25"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin28"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin31"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin34"]*nprocesses+3),4,"1.01");
                tmpLine.Prepend("normwjets_mednjets        lnN  ");
                file << tmpLine.Data() << endl;
            }
            else if(jbin=="bin41"){
                tmpLine.Replace(5*(bindex["bin42"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin45"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin48"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin51"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin27"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin30"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin33"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin36"]*nprocesses+3),4,"1.35");
                tmpLine.Replace(5*(bindex["bin41"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin44"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin47"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin50"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin26"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin29"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin32"]*nprocesses+3),4,"1.01");
                tmpLine.Replace(5*(bindex["bin35"]*nprocesses+3),4,"1.01");
                tmpLine.Prepend("normwjets_highnjets       lnN  ");
                file << tmpLine.Data() << endl;
            }
        } 
    }
}

void outputLognormalSystematics(std::ofstream &file)
{
  // luminosity uncertainty is 2.6% for 2016 data
  file << "lumi  lnN  ";
  for(unsigned int ibin=0; ibin<nbins; ibin++) {
    file << "1.106 - - - 1.106 ";
  }
  file << std::endl;

}

void outputShapeSystematics(std::ofstream &file, const std::vector<std::string> shapeSysts)
{
  for(unsigned int isyst=0; isyst<shapeSysts.size(); isyst++) {
    file << shapeSysts.at(isyst) << "     shape     ";
    if(shapeSysts.at(isyst).find("pdf")!=std::string::npos) {
      // there are 100 NNPDF variations and so each needs to be scaled down by a factor 1/sqrt(100)
      for(unsigned int index=0; index<nbins; index++) file << "0.1 0.1 0.1 0.1 0.1 ";
    }
    else {
      for(unsigned int index=0; index<nbins*nprocesses; index++) file << 1.0 << " ";
    }
    file << "\n";
  }
}

// outputs MC statistical uncertainties
void outputMCStatisticsSyst(std::ofstream &file, const std::vector<std::string> &bins, const std::string & signalBinName)
{
  //  unsigned int nbins=bins.size();
  const unsigned int maxB=4;

  // only signal, qcd, and ttbar have non-negligible MC statistics uncertainties
  std::vector<std::string> samples = {signalBinName, "qcd", "ttbar"};
  for(auto isample : samples) {
      for(unsigned int ibin = 0; ibin<bins.size(); ibin++) {
          for(unsigned int ibbin=1; ibbin<maxB+1; ibbin++) {
              if(!hasEntry(isample, bins.at(ibin), ibbin)) continue;
              file << "mcstat_" << isample << "_" << bins.at(ibin) << "_nb" << ibbin << " shape ";
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
