// plot_dps: Macro that plots variables both for comissioning DPS

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

using namespace std;

TString plot_type=".pdf";
TString plot_style="CMSPaper_Preliminary";

void hem();
void l1prefire(TString year);


// data for HEM Issue
TString folder_dat_18_without_hem = "/mnt/data3/babies/241201/UL2018/merged_rpvfitnbge0_data/";
TString folder_dat_18_with_hem    = "/mnt/data3/babies/241201/UL2018/merged_rpvfitnbge0_hem_data/";
vector<TString> s_data_2018_without_hem = getRPVProcess(folder_dat_18_without_hem,"data");
vector<TString> s_data_2018_with_hem    = getRPVProcess(folder_dat_18_with_hem,   "data");

// MC for L1Prefiring Issue
TString folder_bkg_16_preVFP  = "/mnt/data3/babies/241201/UL2016_preVFP/merged_rpvfitnbge0_mc/";
TString folder_bkg_16_postVFP = "/mnt/data3/babies/241201/UL2016_postVFP/merged_rpvfitnbge0_mc/";
TString folder_bkg_17 = "/mnt/data3/babies/241201/UL2017/merged_rpvfitnbge0_mc/";
vector<TString> s_ttbar_2016_preVFP  = getRPVProcess(folder_bkg_16_preVFP, "ttbar");
vector<TString> s_ttbar_2016_postVFP = getRPVProcess(folder_bkg_16_postVFP,"ttbar");
vector<TString> s_ttbar_2017 = getRPVProcess(folder_bkg_17,"ttbar");

vector<sfeats> Samples;
vector<hfeats> vars;


void hem() {

  TString luminosity="1.";

//  Samples.push_back(sfeats(s_data_2018_with_hem, "2018 data without HEM objects", kRed,1,"pass && trig_ht1050 && run<319077 && Sum$((jets_eta>-3.0 && jets_eta<-1.3 && jets_phi>-1.57 && jets_phi <-0.87) && jets_pt>30 && abs(jets_eta)<2.4 && jets_id==1)==0")); Samples.back().isData=true;
  Samples.push_back(sfeats(s_data_2018_without_hem, "2018 data without HEM objects", kRed,1,"pass && trig_ht1050 && run<319077")); Samples.back().isData=true;
  Samples.push_back(sfeats(s_data_2018_with_hem, "2018 data with HEM objects", kBlue,1,"pass && trig_ht1050 && run<319077"));
  Samples.back().doBand = true;
  vector<int> data;
  data.push_back(0);
  data.push_back(1);

  std::vector<TString> cuts = {"nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=4&&njets<=5", // bin22
                               "nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=6&&njets<=7", // bin23
                               "nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=8",           // bin24
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=4&&njets<=5", // bin25
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=6&&njets<=7", // bin26
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=8"};          // bin27

  for(auto icut : cuts) {
    vars.push_back(hfeats("mj12", 3, 500, 1400, data, "mj12", icut,-1,"data"));
    vars.back().normalize = true;
  }

  plot_distributions(Samples, vars, luminosity, plot_type, plot_style, "dataquality/hem", true, true);
}


void l1prefire(TString year) {

  TString luminosity;
  if(year=="UL2016_preVFP") {
    luminosity="19.5";
    //Samples.push_back(sfeats(s_ttbar_2016_preVFP, "UL2016_preVFP ttbar prefired", kRed,1,cutandweight("pass","frac16/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    //Samples.push_back(sfeats(s_ttbar_2016_preVFP, "UL2016_preVFP ttbar", kBlue,1,cutandweight("pass","frac16")));
    Samples.push_back(sfeats(s_ttbar_2016_preVFP, "UL2016_preVFP ttbar prefired", kRed,1,cutandweight("pass","1/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    Samples.push_back(sfeats(s_ttbar_2016_preVFP, "UL2016_preVFP ttbar", kBlue,1,cutandweight("pass","1")));
  }
  if(year=="UL2016_postVFP") {
    luminosity="16.8";
    //Samples.push_back(sfeats(s_ttbar_2016_postVFP, "UL2016_postVFP ttbar prefired", kRed,1,cutandweight("pass","frac16/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    //Samples.push_back(sfeats(s_ttbar_2016_postVFP, "UL2016_postVFP ttbar", kBlue,1,cutandweight("pass","frac16")));
    Samples.push_back(sfeats(s_ttbar_2016_postVFP, "UL2016_postVFP ttbar prefired", kRed,1,cutandweight("pass","1/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    Samples.push_back(sfeats(s_ttbar_2016_postVFP, "UL2016_postVFP ttbar", kBlue,1,cutandweight("pass","1")));
  }
  else if(year=="2017") {
    luminosity="41.5";
    //Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar prefired", kRed,1,cutandweight("pass","frac1718/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    //Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar", kBlue,1,cutandweight("pass","frac1718")));
    Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar prefired", kRed,1,cutandweight("pass","1/l1pre_nom"))); Samples.back().mcerr=true; Samples.back().isSig=true;
    Samples.push_back(sfeats(s_ttbar_2017, "2017 ttbar", kBlue,1,cutandweight("pass","1")));
  }

  Samples.back().doBand = true;
  vector<int> ttbar;
  ttbar.push_back(0);
  ttbar.push_back(1);

  std::vector<TString> cuts = {"nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=4&&njets<=5", // bin22
                               "nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=6&&njets<=7", // bin23
                               "nleps==1&&mj12>500&&ht>1200&&nbm==0&&njets>=8",           // bin24
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=4&&njets<=5", // bin25
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=6&&njets<=7", // bin26
                               "nleps==1&&mj12>500&&ht>1200&&nbm==1&&njets>=8",           // bin27
                               "nleps==1&&mj12>500&&ht>1200&&nbm==2&&njets>=4&&njets<=5", // bin28
                               "nleps==1&&mj12>500&&ht>1200&&nbm==2&&njets>=6&&njets<=7", // bin29
                               "nleps==1&&mj12>500&&ht>1200&&nbm==2&&njets>=8",           // bin30
                               "nleps==1&&mj12>500&&ht>1200&&nbm>=3&&njets>=4&&njets<=5", // bin34
                               "nleps==1&&mj12>500&&ht>1200&&nbm==3&&njets>=6&&njets<=7", // bin32
                               "nleps==1&&mj12>500&&ht>1200&&nbm==3&&njets>=8",           // bin33
                               "nleps==1&&mj12>500&&ht>1200&&nbm>=4&&njets>=6&&njets<=7", // bin35
                               "nleps==1&&mj12>500&&ht>1200&&nbm>=4&&njets>=8"};          // bin36

  for(auto icut : cuts) {
    vars.push_back(hfeats("mj12", 3, 500, 1400, ttbar, "mj12", icut,-1,"ttbar"));
    vars.back().normalize = true;
  }

  plot_distributions(Samples, vars, luminosity, plot_type, plot_style, "dataquality/l1prefire", true, true);

}

int main(int argc, char *argv[]){
  
  TString issue = argv[1];
  TString year  = argv[2];

  // HEM
  if((issue=="hem") && (year=="2018")) {
    cout << "//////////////////////////////////////////////////" << endl;
    cout << "//////////////////// HEM Issue ///////////////////" << endl;
    cout << "//////////////////////////////////////////////////" << endl;
    cout << endl;
    cout << "!!! PLEASE fix L438 and L481 in src/utilities_macros.cpp !!!" << endl;

    hem();

    cout << "!!! PLEASE fix L438 and L481 in src/utilities_macros.cpp !!!" << endl;
  }

  // L1 Prefiring Issue
  else if((issue == "l1" || issue == "l1pre" || issue == "l1prefire") && ((year=="2016" || year=="2017"))) {
    cout << "//////////////////////////////////////////////////" << endl;
    cout << "/////////////// L1 Prefiring Issue ///////////////" << endl;
    cout << "//////////////////////////////////////////////////" << endl;
    cout << endl;
    cout << "!!! PLEASE fix L438 and L481 in src/utilities_macros.cpp !!!" << endl;

    l1prefire(year);

    cout << "!!! PLEASE fix L438 and L481 in src/utilities_macros.cpp !!!" << endl;
  }
  else {
    cout << "ERROR::Please input argument as hem/l1/l1pre/l1prefire" << endl;
    cout << "ERROR::Please input year     as 2016 or 2017 for l1prefire" << endl;
    cout << "ERROR::Please input year     as 2018 for hem" << endl;
  }


}
