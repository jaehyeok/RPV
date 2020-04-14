#include <iostream>

namespace rpv
{
  TString luminosity="35.9";
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

std::vector<TString> getRPVProcess(TString folder, TString process, bool isv5 = true){

	std::vector<TString> files;
	if(!isv5){
		if(process=="data"){
			files.push_back(folder+"*JetHT*");
		}
		else if(process.Contains("rpv")){
			if(process=="rpv_m1000") files.push_back(folder+"*mGluino*1000*");
			else if(process=="rpv_m1100") files.push_back(folder+"*mGluino*1100*");
			else if(process=="rpv_m1200") files.push_back(folder+"*mGluino*1200*");
			else if(process=="rpv_m1300") files.push_back(folder+"*mGluino*1300*");
			else if(process=="rpv_m1400") files.push_back(folder+"*mGluino*1400*");
			else if(process=="rpv_m1500") files.push_back(folder+"*mGluino*1500*");
			else if(process=="rpv_m1600") files.push_back(folder+"*mGluino*1600*");
			else if(process=="rpv_m1700") files.push_back(folder+"*mGluino*1700*");
			else if(process=="rpv_m1800") files.push_back(folder+"*mGluino*1800*");
			else if(process=="rpv_m1900") files.push_back(folder+"*mGluino*1900*");
			else if(process=="rpv_m2000") files.push_back(folder+"*mGluino*2000*");
		}
		// For 0, 1, or 2 lepton ttbar apply a ntruleps cut at the sfeat level
		else if(process=="ttbar"){
			/*
			   files.push_back(folder+"*_TTJets_DiLept_Tune*");
			   files.push_back(folder+"*_TTJets_SingleLeptFromT_Tune*");
			   files.push_back(folder+"*_TTJets_SingleLeptFromTbar_Tune*");
			   files.push_back(folder+"*_TTJets_HT*");
			   files.push_back(folder+"*_TTJets_Tune*");
			   */
			files.push_back(folder+"*_TT_*"); //v4
			//    files.push_back(folder+"TT_*"); //v5
			//std::cout<<folder+"TT_*"<<std::endl;
		}
		//Separated by ntrulep to avoid looping over samples killed by sfeat ntruleps selection
		else if(process=="ttbar_2l"){
			files.push_back(folder+"TTJets_DiLept_Tune*");
			files.push_back(folder+"TTJets_HT*");
		}
		else if(process=="ttbar_1l"){
			files.push_back(folder+"TTJets_SingleLeptFromT_Tune*");
			files.push_back(folder+"TTJets_SingleLeptFromTbar_Tune*");
			files.push_back(folder+"TTJets_HT*");
		}  
		else if(process=="ttbar_had"){
			files.push_back(folder+"TTJets_HT*");
			files.push_back(folder+"TTJets_Tune*"); //For this sample to be used in the hadronic-only selection it needs a ntruleps==0 skim
		}
		else if(process=="qcd"){
			//files.push_back(folder+"QCD_*"); //v5
			files.push_back(folder+"*_QCD_*"); //v4
		}
		// For 0 or 1 lepton wjets apply a ntruleps cut at the sfeat level
		else if(process=="wjets"){
			//    files.push_back(folder+"WJetsToLNu_*"); // v5
			files.push_back(folder+"*_WJetsToLNu_*"); // v4
			//    files.push_back(folder+"WJetsToQQ_HT-600ToInf_*");
		}
		else if(process=="singlet"){
			files.push_back(folder+"ST_*");
		}
		else if(process=="zjets"){
			files.push_back(folder+"ZJetsToQQ_HT600toInf_*");
			files.push_back(folder+"ZJetsToNuNu_HT-*");
		}
		else if(process=="other"){
			/*
			   files.push_back(folder+"DYJetsToLL_*");
			   files.push_back(folder+"TTTT_*");
			   files.push_back(folder+"TTWJetsToLNu_*");
			   files.push_back(folder+"TTZToQQ_*");
			   files.push_back(folder+"TTZToLLNuNu_*");
			   files.push_back(folder+"WZ_*"); 
			   files.push_back(folder+"ZZ_*"); 
			   files.push_back(folder+"WW_*"); 
			   files.push_back(folder+"WZZ_*"); 
			   files.push_back(folder+"WWZ_*"); 
			   files.push_back(folder+"ZZZ_*"); 
			   files.push_back(folder+"WWW_*"); //v5
			   */
			files.push_back(folder+"*_DYJetsToLL_*");
			files.push_back(folder+"*_TTTT_*");
			files.push_back(folder+"*_TTWJetsToLNu_*");
			files.push_back(folder+"*_TTZToQQ_*");
			files.push_back(folder+"*_TTZToLLNuNu_*");
			files.push_back(folder+"*_WZ_*"); 
			files.push_back(folder+"*_ZZ_*"); 
			files.push_back(folder+"*_WW_*"); 
			files.push_back(folder+"*_WZZ_*"); 
			files.push_back(folder+"*_WWZ_*"); 
			files.push_back(folder+"*_ZZZ_*"); 
			files.push_back(folder+"*_WWW_*"); // v5
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
		// For all background processes
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
			std::cout<<"Process not found. Allowed processes are \"ttbar\",\"ttbar_1l\",\"ttbar_2l\",\"ttbar_had\", \"qcd\", \"wjets\", \"singlet\", \"zjets\", \"other\" and \"other_public\" and \"all_bg\"."<<std::endl;
		}
	}
	else{
		if(process=="data"){
			files.push_back(folder+"*JetHT*");
		}
		else if(process.Contains("rpv")){
			if(process=="rpv_m1000") files.push_back(folder+"*mGluino*1000*");
			else if(process=="rpv_m1100") files.push_back(folder+"*mGluino*1100*");
			else if(process=="rpv_m1200") files.push_back(folder+"*mGluino*1200*");
			else if(process=="rpv_m1300") files.push_back(folder+"*mGluino*1300*");
			else if(process=="rpv_m1400") files.push_back(folder+"*mGluino*1400*");
			else if(process=="rpv_m1500") files.push_back(folder+"*mGluino*1500*");
			else if(process=="rpv_m1600") files.push_back(folder+"*mGluino*1600*");
			else if(process=="rpv_m1700") files.push_back(folder+"*mGluino*1700*");
			else if(process=="rpv_m1800") files.push_back(folder+"*mGluino*1800*");
			else if(process=="rpv_m1900") files.push_back(folder+"*mGluino*1900*");
			else if(process=="rpv_m2000") files.push_back(folder+"*mGluino*2000*");
		}
		// For 0, 1, or 2 lepton ttbar apply a ntruleps cut at the sfeat level
		else if(process=="ttbar"){
			/*
			   files.push_back(folder+"*_TTJets_DiLept_Tune*");
			   files.push_back(folder+"*_TTJets_SingleLeptFromT_Tune*");
			   files.push_back(folder+"*_TTJets_SingleLeptFromTbar_Tune*");
			   files.push_back(folder+"*_TTJets_HT*");
			   files.push_back(folder+"*_TTJets_Tune*");
			   */
			//			files.push_back(folder+"*_TT_*"); //v4
			//files.push_back(folder+"TT_*"); //v5 powheg
			files.push_back(folder+"TTJets_HT*"); //v5 MG
			//std::cout<<folder+"TT_*"<<std::endl;
		}
		//Separated by ntrulep to avoid looping over samples killed by sfeat ntruleps selection
		else if(process=="ttbar_2l"){
			files.push_back(folder+"TTJets_DiLept_Tune*");
			files.push_back(folder+"TTJets_HT*");
		}
		else if(process=="ttbar_1l"){
			files.push_back(folder+"TTJets_SingleLeptFromT_Tune*");
			files.push_back(folder+"TTJets_SingleLeptFromTbar_Tune*");
			files.push_back(folder+"TTJets_HT*");
		}  
		else if(process=="ttbar_had"){
			files.push_back(folder+"TTJets_HT*");
			files.push_back(folder+"TTJets_Tune*"); //For this sample to be used in the hadronic-only selection it needs a ntruleps==0 skim
		}
		else if(process=="qcd"){
			files.push_back(folder+"QCD_*"); //v5
			//files.push_back(folder+"*_QCD_*"); //v4
		}
		// For 0 or 1 lepton wjets apply a ntruleps cut at the sfeat level
		else if(process=="wjets"){
			files.push_back(folder+"WJetsToLNu_*"); // v5
			//files.push_back(folder+"*_WJetsToLNu_*"); // v4
			//    files.push_back(folder+"WJetsToQQ_HT-600ToInf_*");
		}
		else if(process=="singlet"){
			files.push_back(folder+"ST_*");
		}
		else if(process=="zjets"){
			files.push_back(folder+"ZJetsToQQ_HT600toInf_*");
			files.push_back(folder+"ZJetsToNuNu_HT-*");
		}
		else if(process=="other"){

			files.push_back(folder+"DYJetsToLL_*");
			files.push_back(folder+"TTTT_*");
			files.push_back(folder+"TTWJetsToLNu_*");
			files.push_back(folder+"TTZToQQ_*");
			files.push_back(folder+"TTZToLLNuNu_*");
			files.push_back(folder+"WZ_*"); 
			files.push_back(folder+"ZZ_*"); 
			files.push_back(folder+"WW_*"); 
			files.push_back(folder+"WZZ_*"); 
			files.push_back(folder+"WWZ_*"); 
			files.push_back(folder+"ZZZ_*"); 
			files.push_back(folder+"WWW_*");  //v5
			/*
			   files.push_back(folder+"*_DYJetsToLL_*");
			   files.push_back(folder+"*_TTTT_*");
			   files.push_back(folder+"*_TTWJetsToLNu_*");
			   files.push_back(folder+"*_TTZToQQ_*");
			   files.push_back(folder+"*_TTZToLLNuNu_*");
			   files.push_back(folder+"*_WZ_*"); 
			   files.push_back(folder+"*_ZZ_*"); 
			   files.push_back(folder+"*_WW_*"); 
			   files.push_back(folder+"*_WZZ_*"); 
			   files.push_back(folder+"*_WWZ_*"); 
			   files.push_back(folder+"*_ZZZ_*"); 
			   files.push_back(folder+"*_WWW_*"); // v5
			   */
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
		// For all background processes
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
			std::cout<<"Process not found. Allowed processes are \"ttbar\",\"ttbar_1l\",\"ttbar_2l\",\"ttbar_had\", \"qcd\", \"wjets\", \"singlet\", \"zjets\", \"other\" and \"other_public\" and \"all_bg\"."<<std::endl;
		}
	}
	return files;
}


//
//
//
bool passBinCut(int bin, int nleps_, float ht_, int njets_, float mj_, int nb_)
{
    bool pass = false;
    
    //
    int     nleps     = 99;
    float   ht        = 999999;
    int     njetsLow  = 99;
    int     njetsHigh = 99;
    float   mjLow     = 999999;
    float   mjHigh    = 999999;
    int     nbLow     = 99;
    int     nbHigh    = 99;
   
    // cut values
    const float ht0lepCut    = 1500;
    const float ht1lepCut    = 1200;

    const float mjVLowCut    = 300;
    const float mjLowCut     = 500;
    const float mjMedCut     = 800;
    const float mjHighCut    = 1000;
    const float mjInfCut     = 9999999;
    
    const float njetsVLowCut = 4;
    const float njetsLowCut  = 6;
    const float njetsMedCut  = 8;
    const float njetsHighCut = 10; 
    const float njetsInfCut  = 999; 

    const float nbVLowCut = 0;
    const float nbLowCut = 1;
    const float nbMedCut = 2;
    const float nbHighCut = 3;
    const float nbVHighCut = 4;
    const float nbInfCut = 999;
 
   // Get cut values for a given bin
    if(bin==0) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    } 
    else if(bin==1) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==2) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==3) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        mjLow       = mjMedCut;
        mjHigh      = mjInfCut;
    } 
    else if(bin==4) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjMedCut;
        mjHigh      = mjInfCut;
    }
    else if(bin==5) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        mjLow       = mjMedCut;
        mjHigh      = mjInfCut;
    }
    else if(bin==6) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        mjLow       = mjVLowCut;
        mjHigh      = mjLowCut;
    }
    else if(bin==7) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjVLowCut;
        mjHigh      = mjLowCut;
    }
    else if(bin==8) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsMedCut+1;
        mjLow       = mjVLowCut;
        mjHigh      = mjLowCut;
    }
    else if(bin==9) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsHighCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjVLowCut;
        mjHigh      = mjLowCut;
    }
    else if(bin==10) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsHighCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==11) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==12) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==13) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsHighCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjMedCut;
        mjHigh      = mjHighCut;
    }
    else if(bin==14) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjMedCut;
        mjHigh      = mjHighCut;
    }
    else if(bin==15) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjMedCut;
        mjHigh      = mjHighCut;
    }
    else if(bin==16) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsMedCut+1;
        mjLow       = mjLowCut;
        mjHigh      = mjMedCut;
    }
    else if(bin==17) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsMedCut+1;
        mjLow       = mjMedCut;
        mjHigh      = mjHighCut;
    }
    else if(bin==18) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsMedCut+1;
        mjLow       = mjHighCut;
        mjHigh      = mjInfCut;
    }
    else if(bin==19) 
    { 
        nleps       = 0;
        ht          = ht0lepCut;
        njetsLow    = njetsHighCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjHighCut;
        mjHigh      = mjInfCut;
    }
    else if(bin==20) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        mjLow       = mjHighCut;
        mjHigh      = mjInfCut;
    }
    else if(bin==21) 
    { 
        nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjHighCut;
        mjHigh      = mjInfCut;
    }
//for now, binning for mj plots in nb-njets scheme
// nb=0 binning
    else if(bin==22)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==23)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==24)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==25)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==26)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==27)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==28)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==29)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==30)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==31)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==32)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==33)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==34)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut;
        njetsHigh   = njetsVLowCut+1;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    else if(bin==35)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut;
        njetsHigh   = njetsLowCut+1;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    else if(bin==36)
    {
	nleps       = 1;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut;
        njetsHigh   = njetsInfCut;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    //nleps = 0
    else if(bin==37)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut+2;
        njetsHigh   = njetsVLowCut+3;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==38)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut+2;
        njetsHigh   = njetsLowCut+3;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==39)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut+2;
        njetsHigh   = njetsInfCut;
        nbLow       = nbVLowCut;
        nbHigh      = nbLowCut;
    }
    else if(bin==40)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut+2;
        njetsHigh   = njetsVLowCut+3;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==41)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut+2;
        njetsHigh   = njetsLowCut+3;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==42)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut+2;
        njetsHigh   = njetsInfCut;
        nbLow       = nbLowCut;
        nbHigh      = nbMedCut;
    }
    else if(bin==43)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut+2;
        njetsHigh   = njetsVLowCut+3;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==44)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut+2;
        njetsHigh   = njetsLowCut+3;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==45)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut+2;
        njetsHigh   = njetsInfCut;
        nbLow       = nbMedCut;
        nbHigh      = nbHighCut;
    }
    else if(bin==46)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut+2;
        njetsHigh   = njetsVLowCut+3;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==47)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut+2;
        njetsHigh   = njetsLowCut+3;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==48)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut+2;
        njetsHigh   = njetsInfCut;
        nbLow       = nbHighCut;
        nbHigh      = nbVHighCut;
    }
    else if(bin==49)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsVLowCut+2;
        njetsHigh   = njetsVLowCut+3;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    else if(bin==50)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsLowCut+2;
        njetsHigh   = njetsLowCut+3;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    else if(bin==51)
    {
	nleps       = 0;
        ht          = ht1lepCut;
        njetsLow    = njetsMedCut+2;
        njetsHigh   = njetsInfCut;
        nbLow       = nbVHighCut;
        nbHigh      = nbInfCut;
    }
    //lepton-0
    else  // in case of wrong bin number
    { 
        std::cout << "[Error] I don't like your bin number: " << bin << " !!" << std::endl; 
        nleps       = 99;
        ht          = 9999999;
        njetsLow    = njetsInfCut;
        njetsHigh   = njetsInfCut;
        mjLow       = mjInfCut;
        mjHigh      = mjInfCut;
    }

    if(0)  // debugging 
    { 
       std::cout << "[Debug] bin " << bin << " :: " 
                 << "htCut    : " << ht << ", "  
                 << "njetsCut : " << njetsLow << "-" << njetsHigh << ", " 
                 << "mjCut    : " << mjLow << "-" << mjHigh << " " 
                 << std::endl;
    }

    //
    // Apply cuts
    //
    bool nbormj;
    if(mjLow==999999&&mjHigh==999999){
       nbormj = nb_>=nbLow && nb_<nbHigh;
    }
    if(nbLow==99&&nbHigh==99){
       nbormj = mj_>mjLow && mj_<=mjHigh;
    }
    mj_ = mj_/1;
    if(nleps_==nleps 
       && ht_>ht
       && njets_>=njetsLow
       && njets_<=njetsHigh
       && nbormj
       ) pass = true;
    return pass;
}

