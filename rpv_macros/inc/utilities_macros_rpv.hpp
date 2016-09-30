namespace rpv
{
  TString luminosity="12.9";
}

TString filestring(TString dataset, bool isSkimmed=true)
{
  if(isSkimmed) {
    //    TString datasetString(Form("/mnt/hadoop/local/cawest/skims/ht1200/*%s*.root", dataset.Data()));
    TString datasetString(Form("/net/cms29/cms29r0/cawest/skims/ht1200/*%s*.root", dataset.Data()));
    return datasetString;
  }
  else {
    TString datasetString(Form("/homes/cawest/links/%s/*.root", dataset.Data()));
    return datasetString;
  }

}

// this is a hack to add an additional weight
std::string cutandweight(std::string cut, std::string weight)
{
  std::string newcut("(");
  newcut+=cut;
  newcut+="))*(";
  newcut+=weight;

  return newcut;
} 

std::vector<TString> getRPVProcess(TString folder, TString process){

  std::vector<TString> files;
  
  if(process=="data"){
    files.push_back(folder+"*Run2016_HTMHT_MET_JetHT_SingleElectron_SingleMuon*");
  }
  else if(process.Contains("rpv")){
    if(process=="rpv_m1000") files.push_back(folder+"*mGluino-1000*");
    else if(process=="rpv_m1100") files.push_back(folder+"*mGluino-1100*");
    else if(process=="rpv_m1200") files.push_back(folder+"*mGluino-1200*");
    else if(process=="rpv_m1300") files.push_back(folder+"*mGluino-1300*");
    else if(process=="rpv_m1400") files.push_back(folder+"*mGluino-1400*");
    else if(process=="rpv_m1500") files.push_back(folder+"*mGluino-1500*");
  }
  // For 0, 1, or 2 lepton ttbar apply a ntruleps cut at the sfeat level
  else if(process=="ttbar"){
    files.push_back(folder+"*_TTJets_DiLept*");
    files.push_back(folder+"*_TTJets_SingleLept*");
    files.push_back(folder+"*_TTJets_HT*");
    files.push_back(folder+"*_TTJets_TuneCUETP8M1_13TeV-madgraph*"); //Skimmed so that it has only ntruleps==0 && ht_me_isr<=600
  }

  //Separated by ntrulep to avoid looping over samples killed by sfeat ntruleps selection
  else if(process=="ttbar_2l"){
    files.push_back(folder+"*_TTJets_DiLept*");
    files.push_back(folder+"*_TTJets_HT*");
  }
  else if(process=="ttbar_1l"){
    files.push_back(folder+"*_TTJets_SingleLept*");
    files.push_back(folder+"*_TTJets_HT*");
  }
  
  else if(process=="ttbar_had"){
    files.push_back(folder+"*_TTJets_HT*");
    files.push_back(folder+"*_TTJets_TuneCUETP8M1_13TeV-madgraph*"); //Skimmed so that it has only ntruleps==0 && ht_me_isr<=600
  }

  else if(process=="qcd"){
    files.push_back(folder+"*_QCD_HT1000to1500_Tune*");
    files.push_back(folder+"*_QCD_HT1500to2000_Tune*");
    files.push_back(folder+"*_QCD_HT2000toInf_Tune*");
  }
  // For 0 or 1 lepton wjets apply a ntruleps cut at the sfeat level
  else if(process=="wjets"){
    files.push_back(folder+"*_WJetsToLNu_HT*");
    files.push_back(folder+"*WJetsToQQ_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*"); //Currently do not have this sample. Update name once we do.
  }
  else if(process=="singlet"){
    files.push_back(folder+"*_ST_*");
  }
  else if(process=="zjets"){
    files.push_back(folder+"*ZJetsToQQ_HT600toInf_13TeV-madgraph*"); //Currently do no thave this sample. Update name once we do.
  }
  else if(process=="other"){
    files.push_back(folder+"*_DYJetsToLL_M-50_HT-600to800_*");
    files.push_back(folder+"*_DYJetsToLL_M-50_HT-800to1200_*");
    files.push_back(folder+"*_DYJetsToLL_M-50_HT-1200to2500_*");
    files.push_back(folder+"*_DYJetsToLL_M-50_HT-2500toInf_*");    
    files.push_back(folder+"*_ttHJetTobb_*");
    files.push_back(folder+"*_TTTT_*");
    files.push_back(folder+"*_TTWJetsToLNu_*");
    files.push_back(folder+"*_TTWJetsToQQ_*");
    files.push_back(folder+"*_TTZToQQ_*");
    files.push_back(folder+"*_TTZToLLNuNu_*");
    files.push_back(folder+"*_WZTo1L1Nu2Q_*");
  }
  //Contains all processes except for QCD, ttbar, and wjets. Typically used for public plots. Recursive so only need to change samples in one place
  else if(process=="other_public"){
    std::vector<TString> tmp_other;
    
    tmp_other = getRPVProcess(folder,"singlet");
    files.insert(files.end(),tmp_other.begin(),tmp_other.end());
    tmp_other = getRPVProcess(folder,"zjets");
    files.insert(files.end(),tmp_other.begin(),tmp_other.end());
    tmp_other = getRPVProcess(folder,"other");
    files.insert(files.end(),tmp_other.begin(),tmp_other.end());
  }
 
  
  else if(process=="all_bg"){
    std::vector<TString> tmp_allbg;
    tmp_allbg =  getRPVProcess(folder,"ttbar");
    files.insert(files.end(),tmp_allbg.begin(),tmp_allbg.end());
    tmp_allbg =  getRPVProcess(folder,"qcd");
    files.insert(files.end(),tmp_allbg.begin(),tmp_allbg.end());
    tmp_allbg =  getRPVProcess(folder,"wjets");
    files.insert(files.end(),tmp_allbg.begin(),tmp_allbg.end());
    tmp_allbg =  getRPVProcess(folder,"other_public");
    files.insert(files.end(),tmp_allbg.begin(),tmp_allbg.end());
    
  }

 else{
    std::cout<<"Process not found. Allowed processes are \"ttbar\",\"ttbar_1l\",\"ttbar_2l\",\"ttbar_had\", \"qcd\", \"wjets\", \"singlet\", \"zjets\", \"other\" and \"other_public\" and \"all_bg\" ."<<std::endl;
  }
  return files;
}
