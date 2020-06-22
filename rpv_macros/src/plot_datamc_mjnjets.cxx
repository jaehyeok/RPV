#include <iostream>
#include <vector>

#include "TCanvas.h"
#include "TError.h"
#include "TH2D.h"
#include "TStyle.h"

#include "small_tree_rpv.hpp"
#include "utilities.hpp"
#include "utilities_macros.hpp"
#include "utilities_macros_rpv.hpp"


namespace{
  double lumi = 1.; //Need to change json bool mask as well for data

  TString outdir = "dmc_mjnjets";
  TString plot_type= ".png";

  bool do1DPlots=true;
  bool do2DPlots=false;
}
using namespace std;

void make1DPlots(TString folder_mc, TString folder_data);
void make2DPlots(TString folder_mc, TString folder_data);
void formatAndSaveHist(TH2D* hist);

int main(){
  gErrorIgnoreLevel=kError+1;

  TString mc = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_norm/";
  TString data = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/merged_norm/";

  if(do1DPlots) make1DPlots(mc, data);
  if(do2DPlots) make2DPlots(mc, data);
}

void make1DPlots(TString folder_mc, TString folder_data){

  //Get data files
  vector<TString> dats = getRPVProcess(folder_data,"data");
  small_tree_rpv data(dats[0].Data());
  for(unsigned int idat=1; idat<dats.size(); idat++)
    data.Add(dats[idat].Data());

  //Get background MC files 
  vector<TString> samples = getRPVProcess(folder_mc,"all_bg");
  small_tree_rpv bkg(samples[0].Data());
  for(unsigned int isam=1; isam<samples.size(); isam++)
    bkg.Add(samples[isam].Data());

  TH1::SetDefaultSumw2(true);
  gStyle->SetOptStat(0);

  //double xbins[] = {300, 500, 800, 1000, 1500};
  double xbins[] = {500, 800, 1100};

  // plots[data/mc][0/1 Lept][4-5/6-7 jets] --> 6-7 jets not used for 1-lepton
  vector<vector<vector<TH1D*> > > plots(2, vector<vector<TH1D*> >(2, vector<TH1D*>(2)));
  plots[0][0][0] = new TH1D("zLeptPlot_data_45j","Data;MJ [GeV]", 4, xbins);
  plots[0][0][1] = new TH1D("zLeptPlot_data_67j","Data;MJ [GeV]", 4, xbins);
  plots[0][1][0] = new TH1D("oLeptPlot_data_45j","Data;MJ [GeV]", 4, xbins);

  plots[1][0][0] = new TH1D("zLeptPlot_mc_45j"  ,"MC;MJ [GeV]"  , 4, xbins);
  plots[1][0][1] = new TH1D("zLeptPlot_mc_67j"  ,"MC;MJ [GeV]"  , 4, xbins);
  plots[1][1][0] = new TH1D("oLeptPlot_mc_45j"  ,"MC;MJ [GeV]"  , 4, xbins);

  vector<vector<vector<TH1D*> > > plots_lht(2, vector<vector<TH1D*> >(2, vector<TH1D*>(2)));
  plots_lht[0][0][0] = new TH1D("zLeptPlot_data_45j_lht","Data;MJ [GeV]", 4, xbins);
  plots_lht[0][0][1] = new TH1D("zLeptPlot_data_67j_lht","Data;MJ [GeV]", 4, xbins);
  plots_lht[0][1][0] = new TH1D("oLeptPlot_data_45j_lht","Data;MJ [GeV]", 4, xbins);

  plots_lht[1][0][0] = new TH1D("zLeptPlot_mc_45j_lht"  ,"MC;MJ [GeV]"  , 4, xbins);
  plots_lht[1][0][1] = new TH1D("zLeptPlot_mc_67j_lht"  ,"MC;MJ [GeV]"  , 4, xbins);
  plots_lht[1][1][0] = new TH1D("oLeptPlot_mc_45j_lht"  ,"MC;MJ [GeV]"  , 4, xbins);

  // Nb==1 plots
  // plots[data/mc][0/1 Lept][4-5/6-7/8-9/10 jets] --> 8-9+10 jets combined for 1-lepton
  vector<vector<vector<TH1D*> > > plots_nb1(2, vector<vector<TH1D*> >(2, vector<TH1D*>(4)));
  plots_nb1[0][0][0] = new TH1D("zLeptPlot_data_45j_nb1","Data;MJ [GeV]", 4, xbins);
  plots_nb1[0][0][1] = new TH1D("zLeptPlot_data_67j_nb1","Data;MJ [GeV]", 4, xbins);
  plots_nb1[0][0][2] = new TH1D("zLeptPlot_data_89j_nb1","Data;MJ [GeV]", 4, xbins);
  plots_nb1[0][0][3] = new TH1D("zLeptPlot_data_10j_nb1","Data;MJ [GeV]", 4, xbins);

  plots_nb1[0][1][0] = new TH1D("oLeptPlot_data_45j_nb1","Data;MJ [GeV]", 4, xbins);
  plots_nb1[0][1][1] = new TH1D("oLeptPlot_data_67j_nb1","Data;MJ [GeV]", 4, xbins);
  plots_nb1[0][1][2] = new TH1D("oLeptPlot_data_8j_nb1" ,"Data;MJ [GeV]", 4, xbins);

  plots_nb1[1][0][0] = new TH1D("zLeptPlot_data_45j_nb1","MC;MJ [GeV]", 4, xbins);
  plots_nb1[1][0][1] = new TH1D("zLeptPlot_data_67j_nb1","MC;MJ [GeV]", 4, xbins);
  plots_nb1[1][0][2] = new TH1D("zLeptPlot_data_89j_nb1","MC;MJ [GeV]", 4, xbins);
  plots_nb1[1][0][3] = new TH1D("zLeptPlot_data_10j_nb1","MC;MJ [GeV]", 4, xbins);

  plots_nb1[1][1][0] = new TH1D("oLeptPlot_data_45j_nb1","MC;MJ [GeV]", 4, xbins);
  plots_nb1[1][1][1] = new TH1D("oLeptPlot_data_67j_nb1","MC;MJ [GeV]", 4, xbins);
  plots_nb1[1][1][2] = new TH1D("oLeptPlot_data_8j_nb1" ,"MC;MJ [GeV]", 4, xbins);


  vector<vector<vector<TH1D*> > > plots_nb1_lht(2, vector<vector<TH1D*> >(2, vector<TH1D*>(4)));
  plots_nb1_lht[0][0][0] = new TH1D("zLeptPlot_data_45j_nb1_lht","Data;MJ [GeV]", 4, xbins);
  plots_nb1_lht[0][0][1] = new TH1D("zLeptPlot_data_67j_nb1_lht","Data;MJ [GeV]", 4, xbins);
  plots_nb1_lht[0][0][2] = new TH1D("zLeptPlot_data_89j_nb1_lht","Data;MJ [GeV]", 4, xbins);
  plots_nb1_lht[0][0][3] = new TH1D("zLeptPlot_data_10j_nb1_lht","Data;MJ [GeV]", 4, xbins);

  plots_nb1_lht[0][1][0] = new TH1D("oLeptPlot_data_45j_nb1_lht","Data;MJ [GeV]", 4, xbins);
  plots_nb1_lht[0][1][1] = new TH1D("oLeptPlot_data_67j_nb1_lht","Data;MJ [GeV]", 4, xbins);
  plots_nb1_lht[0][1][2] = new TH1D("oLeptPlot_data_8j_nb1_lht" ,"Data;MJ [GeV]", 4, xbins);

  plots_nb1_lht[1][0][0] = new TH1D("zLeptPlot_data_45j_nb1_lht","MC;MJ [GeV]", 4, xbins);
  plots_nb1_lht[1][0][1] = new TH1D("zLeptPlot_data_67j_nb1_lht","MC;MJ [GeV]", 4, xbins);
  plots_nb1_lht[1][0][2] = new TH1D("zLeptPlot_data_89j_nb1_lht","MC;MJ [GeV]", 4, xbins);
  plots_nb1_lht[1][0][3] = new TH1D("zLeptPlot_data_10j_nb1_lht","MC;MJ [GeV]", 4, xbins);

  plots_nb1_lht[1][1][0] = new TH1D("oLeptPlot_data_45j_nb1_lht","MC;MJ [GeV]", 4, xbins);
  plots_nb1_lht[1][1][1] = new TH1D("oLeptPlot_data_67j_nb1_lht","MC;MJ [GeV]", 4, xbins);
  plots_nb1_lht[1][1][2] = new TH1D("oLeptPlot_data_8j_nb1_lht" ,"MC;MJ [GeV]", 4, xbins);

  //Loop over Data tree
  for(unsigned int ievent=0; ievent<data.GetEntries(); ievent++){
    data.GetEntry(ievent);

    if(!(data.trig().at(12)&&data.pass())) continue;

    //Zero Lepton Selection
    if(data.nleps()==0&&data.ht()>1300&&data.nbm()>=1&&data.njets()>=4&&data.mj12()>300){
      //Low HT
      if(data.ht()<=1500){
	if(data.njets()<=5) plots_lht[0][0][0]->Fill(data.mj12());
	else if(data.njets()>=6&&data.njets()<=7) plots_lht[0][0][1]->Fill(data.mj12());
      }
      //Nom HT
      else{
	if(data.njets()<=5) plots[0][0][0]->Fill(data.mj12());
	else if(data.njets()>=6&&data.njets()<=7) plots[0][0][1]->Fill(data.mj12());
      }
      // nbm==1
      if(data.nbm()==1){
	//Low HT
	if(data.ht()<=1500){
	  if(data.njets()<=5) plots_nb1_lht[0][0][0]->Fill(data.mj12());
	  else if(data.njets()>=6&&data.njets()<=7) plots_nb1_lht[0][0][1]->Fill(data.mj12());
	  else if(data.njets()>=8&&data.njets()<=9) plots_nb1_lht[0][0][2]->Fill(data.mj12());
	  else if(data.njets()>=10) plots_nb1_lht[0][0][3]->Fill(data.mj12());
	}
	//Nom HT
	else{
	  if(data.njets()<=5) plots_nb1[0][0][0]->Fill(data.mj12());
	  else if(data.njets()>=6&&data.njets()<=7) plots_nb1[0][0][1]->Fill(data.mj12());
	  else if(data.njets()>=8&&data.njets()<=9) plots_nb1[0][0][2]->Fill(data.mj12());
	  else if(data.njets()>=10) plots_nb1[0][0][3]->Fill(data.mj12());
	}
      }
    }
    //One Lepton Selection
    else if(data.nleps()==1&&data.ht()>1000&&data.nbm()>=1&&data.njets()>=4&&data.mj12()>300){
      //Low HT
      if(data.ht()<=1200){
	if(data.njets()<=5) plots_lht[0][1][0]->Fill(data.mj12());
      }
      //Nom HT
      else{
	if(data.njets()<=5) plots[0][1][0]->Fill(data.mj12());
      }
      // nbm==1
      if(data.nbm()==1){
	//Low HT
	if(data.ht()<=1200){
	  if(data.njets()<=5) plots_nb1_lht[0][1][0]->Fill(data.mj12());
	  else if(data.njets()>=6&&data.njets()<=7) plots_nb1_lht[0][1][1]->Fill(data.mj12());
	  else if(data.njets()>=8) plots_nb1_lht[0][1][2]->Fill(data.mj12());
	}
	//Nom HT
	else{
	  if(data.njets()<=5) plots_nb1[0][1][0]->Fill(data.mj12());
	  else if(data.njets()>=6&&data.njets()<=7) plots_nb1[0][1][1]->Fill(data.mj12());
	  else if(data.njets()>=8) plots_nb1[0][1][2]->Fill(data.mj12());
	}
      }
    }
  }

  //Loop over bkg tree
  for(unsigned int ievent=0; ievent<bkg.GetEntries(); ievent++){
    bkg.GetEntry(ievent);

    if(!(bkg.stitch()&&bkg.pass())) continue;

    //Zero Lepton Selection
    if(bkg.nleps()==0&&bkg.ht()>1300&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.mj12()>300){
      //Low HT
      if(bkg.ht()<=1500){
	if(bkg.njets()<=5) plots_lht[1][0][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	else if(bkg.njets()>=6&&bkg.njets()<=7) plots_lht[1][0][1]->Fill(bkg.mj12(), lumi*bkg.weight());
      }
      //Nom HT
      else{
	if(bkg.njets()<=5) plots[1][0][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	else if(bkg.njets()>=6&&bkg.njets()<=7) plots[1][0][1]->Fill(bkg.mj12(), lumi*bkg.weight());
      }
      // nbm==1
      if(bkg.nbm()==1){
	//Low HT
	if(bkg.ht()<=1500){
	  if(bkg.njets()<=5) plots_nb1_lht[1][0][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=6&&bkg.njets()<=7) plots_nb1_lht[1][0][1]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=8&&bkg.njets()<=9) plots_nb1_lht[1][0][2]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=10) plots_nb1_lht[1][0][3]->Fill(bkg.mj12(), lumi*bkg.weight());
	}
	//Nom HT
	else{
	  if(bkg.njets()<=5) plots_nb1[1][0][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=6&&bkg.njets()<=7) plots_nb1[1][0][1]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=8&&bkg.njets()<=9) plots_nb1[1][0][2]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=10) plots_nb1[1][0][3]->Fill(bkg.mj12(), lumi*bkg.weight());
	}
      }
    }
    //One Lepton Selection
    else if(bkg.nleps()==1&&bkg.ht()>1000&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.mj12()>300){
      //Low HT
      if(bkg.ht()<=1200){
	if(bkg.njets()<=5) plots_lht[1][1][0]->Fill(bkg.mj12(), lumi*bkg.weight());
      }
      //Nom HT
      else{
	if(bkg.njets()<=5) plots[1][1][0]->Fill(bkg.mj12(), lumi*bkg.weight());
      }
      // nbm==1
      if(bkg.nbm()==1){
	//Low HT
	if(bkg.ht()<=1200){
	  if(bkg.njets()<=5) plots_nb1_lht[1][1][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=6&&bkg.njets()<=7) plots_nb1_lht[1][1][1]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=8) plots_nb1_lht[1][1][2]->Fill(bkg.mj12(), lumi*bkg.weight());
	}
	//Nom HT
	else{
	  if(bkg.njets()<=5) plots_nb1[1][1][0]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=6&&bkg.njets()<=7) plots_nb1[1][1][1]->Fill(bkg.mj12(), lumi*bkg.weight());
	  else if(bkg.njets()>=8) plots_nb1[1][1][2]->Fill(bkg.mj12(), lumi*bkg.weight());
	}
      }
    }
  }
  
  // plots[ht/lht][0/1 Lept][4-5/6-7 jets] --> 6-7 jets not used for 1-lepton
  vector<vector<vector<TH1D*> > > plots_dmc(2, vector<vector<TH1D*> >(2, vector<TH1D*>(2)));
  plots_dmc[0][0][0] = static_cast<TH1D*>(plots[0][0][0]->Clone("dmc_0l"));
  plots_dmc[0][0][1] = static_cast<TH1D*>(plots[0][0][1]->Clone("dmc_0l"));
  plots_dmc[0][1][0] = static_cast<TH1D*>(plots[0][1][0]->Clone("dmc_1l"));
  //low HT
  plots_dmc[1][0][0] = static_cast<TH1D*>(plots_lht[0][0][0]->Clone("dmc_0l_lht"));
  plots_dmc[1][0][1] = static_cast<TH1D*>(plots_lht[0][0][1]->Clone("dmc_0l_lht"));
  plots_dmc[1][1][0] = static_cast<TH1D*>(plots_lht[0][1][0]->Clone("dmc_1l_lht"));

  //Divide by MC
  plots_dmc[0][0][0]->Divide(plots[1][0][0]);
  plots_dmc[0][0][1]->Divide(plots[1][0][1]);
  plots_dmc[0][1][0]->Divide(plots[1][1][0]);
  //low HT
  plots_dmc[1][0][0]->Divide(plots_lht[1][0][0]);
  plots_dmc[1][0][1]->Divide(plots_lht[1][0][1]);
  plots_dmc[1][1][0]->Divide(plots_lht[1][1][0]);

  for(unsigned int i=0; i<plots_dmc.size(); i++){ 
    for(unsigned int j=0; j<plots_dmc[0].size(); j++){ 
      TCanvas can;	  
      for(unsigned int k=0; k<plots_dmc[0][0].size(); k++){ 
	if(j==1 && k==1) continue; //Skip higher njets CR for 1-lepton
	if(k==0){ 
	  plots_dmc[i][j][k]->SetTitle("Data/MC");
	  plots_dmc[i][j][k]->Draw("e");
	}
	else{
	  plots_dmc[i][j][k]->SetLineColor(k+1);
	  plots_dmc[i][j][k]->Draw("e same");
	}
	if(k==plots_dmc[0][0].size()-1 || (j==1&&k==plots_dmc[0][0].size()-1)) can.SaveAs("./plots/"+outdir+"/"+plots_dmc[i][j][0]->GetName()+plot_type);
      }
    }
  }

  // Nb==1 plots
  // plots[ht/lht][0/1 Lept][4-5/6-7/8-9/10 jets] --> 8-9+10 jets combined for 1-lepton
  vector<vector<vector<TH1D*> > > plots_dmc_nb1(2, vector<vector<TH1D*> >(2, vector<TH1D*>(4)));
  plots_dmc_nb1[0][0][0] = static_cast<TH1D*>(plots_nb1[0][0][0]->Clone("dmc_nb1_0l"));
  plots_dmc_nb1[0][0][1] = static_cast<TH1D*>(plots_nb1[0][0][1]->Clone("dmc_nb1_0l"));
  plots_dmc_nb1[0][0][2] = static_cast<TH1D*>(plots_nb1[0][0][2]->Clone("dmc_nb1_0l"));
  plots_dmc_nb1[0][0][3] = static_cast<TH1D*>(plots_nb1[0][0][3]->Clone("dmc_nb1_0l"));

  plots_dmc_nb1[0][1][0] = static_cast<TH1D*>(plots_nb1[0][1][0]->Clone("dmc_nb1_1l"));
  plots_dmc_nb1[0][1][1] = static_cast<TH1D*>(plots_nb1[0][1][1]->Clone("dmc_nb1_1l"));
  plots_dmc_nb1[0][1][2] = static_cast<TH1D*>(plots_nb1[0][1][2]->Clone("dmc_nb1_1l"));
  //low HT
  plots_dmc_nb1[1][0][0] = static_cast<TH1D*>(plots_nb1_lht[0][0][0]->Clone("dmc_nb1_0l_lht"));
  plots_dmc_nb1[1][0][1] = static_cast<TH1D*>(plots_nb1_lht[0][0][1]->Clone("dmc_nb1_0l_lht"));
  plots_dmc_nb1[1][0][2] = static_cast<TH1D*>(plots_nb1_lht[0][0][2]->Clone("dmc_nb1_0l_lht"));
  plots_dmc_nb1[1][0][3] = static_cast<TH1D*>(plots_nb1_lht[0][0][3]->Clone("dmc_nb1_0l_lht"));

  plots_dmc_nb1[1][1][0] = static_cast<TH1D*>(plots_nb1_lht[0][1][0]->Clone("dmc_nb1_1l_lht"));
  plots_dmc_nb1[1][1][1] = static_cast<TH1D*>(plots_nb1_lht[0][1][1]->Clone("dmc_nb1_1l_lht"));
  plots_dmc_nb1[1][1][2] = static_cast<TH1D*>(plots_nb1_lht[0][1][2]->Clone("dmc_nb1_1l_lht"));

  //Divide by MC
  plots_dmc_nb1[0][0][0]->Divide(plots_nb1[1][0][0]);
  plots_dmc_nb1[0][0][1]->Divide(plots_nb1[1][0][1]);
  plots_dmc_nb1[0][0][2]->Divide(plots_nb1[1][0][2]);
  plots_dmc_nb1[0][0][3]->Divide(plots_nb1[1][0][3]);

  plots_dmc_nb1[0][1][0]->Divide(plots_nb1[1][1][0]);
  plots_dmc_nb1[0][1][1]->Divide(plots_nb1[1][1][1]);
  plots_dmc_nb1[0][1][2]->Divide(plots_nb1[1][1][2]);
  //low HT
  plots_dmc_nb1[1][0][0]->Divide(plots_nb1_lht[1][0][0]);
  plots_dmc_nb1[1][0][1]->Divide(plots_nb1_lht[1][0][1]);
  plots_dmc_nb1[1][0][2]->Divide(plots_nb1_lht[1][0][2]);
  plots_dmc_nb1[1][0][3]->Divide(plots_nb1_lht[1][0][3]);

  plots_dmc_nb1[1][1][0]->Divide(plots_nb1_lht[1][1][0]);
  plots_dmc_nb1[1][1][1]->Divide(plots_nb1_lht[1][1][1]);
  plots_dmc_nb1[1][1][2]->Divide(plots_nb1_lht[1][1][2]);


  for(unsigned int i=0; i<plots_dmc_nb1.size(); i++){ 
    for(unsigned int j=0; j<plots_dmc_nb1[0].size(); j++){ 
      TCanvas can;	  
      for(unsigned int k=0; k<plots_dmc_nb1[0][0].size(); k++){ 
	if(j==1 && k==3) continue; //Skip higher njets CR for 1-lepton
	if(k==0){ 
	  plots_dmc_nb1[i][j][k]->SetTitle("Data/MC");
	  plots_dmc_nb1[i][j][k]->Draw("e");
	}
	else{
	  plots_dmc_nb1[i][j][k]->SetLineColor(k+1);
	  plots_dmc_nb1[i][j][k]->Draw("e same");
	}
	if(k==plots_dmc_nb1[0][0].size()-1 || (j==1&&k==plots_dmc_nb1[0][0].size()-2)) can.SaveAs("./plots/"+outdir+"/"+plots_dmc_nb1[i][j][0]->GetName()+plot_type);
      }
    }
  }
}

void make2DPlots(TString folder_mc, TString folder_data){

  //Get data files
  vector<TString> dats = getRPVProcess(folder_data,"data");
  small_tree_rpv data(dats[0].Data());
  for(unsigned int idat=1; idat<dats.size(); idat++)
    data.Add(dats[idat].Data());

  //Get background MC files 
  vector<TString> samples = getRPVProcess(folder_mc,"all_bg");
  small_tree_rpv bkg(samples[0].Data());
  for(unsigned int isam=1; isam<samples.size(); isam++)
    bkg.Add(samples[isam].Data());

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);

  TH2D* zLeptPlot_data = new TH2D("zLeptPlot_data","Data;Njets;MJ [GeV]",4,4,8,10,300,1300);
  TH2D* oLeptPlot_data = new TH2D("oLeptPlot_data","Data;Njets;MJ [GeV]",2,4,6,10,300,1300);
  TH2D* zLeptPlot_mc = new TH2D("zLeptPlot_mc","MC;Njets;MJ [GeV]",4,4,8,10,300,1300);
  TH2D* oLeptPlot_mc = new TH2D("oLeptPlot_mc","MC;Njets;MJ [GeV]",2,4,6,10,300,1300);

  TH2D* zLeptPlot_data_lowht = new TH2D("zLeptPlot_data_lowht","Data;Njets;MJ [GeV]",4,4,8,10,300,1300);
  TH2D* oLeptPlot_data_lowht = new TH2D("oLeptPlot_data_lowht","Data;Njets;MJ [GeV]",2,4,6,10,300,1300);
  TH2D* zLeptPlot_mc_lowht = new TH2D("zLeptPlot_mc_lowht","MC;Njets;MJ [GeV]",4,4,8,10,300,1300);
  TH2D* oLeptPlot_mc_lowht = new TH2D("oLeptPlot_mc_lowht","MC;Njets;MJ [GeV]",2,4,6,10,300,1300);

  //Loop over Data tree
  for(unsigned int ievent=0; ievent<data.GetEntries(); ievent++){
    data.GetEntry(ievent);

    if(!(data.trig().at(12)&&data.pass())) continue;
    //Zero Lepton Selection
    if(data.nleps()==0&&data.ht()>1200&&data.nbm()>=1&&data.njets()>=4&&data.njets()<=7&&data.mj12()>300)
      zLeptPlot_data->Fill(data.njets(),data.mj12());
    //One Lepton Selection
    if(data.nleps()==1&&data.ht()>1200&&data.nbm()>=1&&data.njets()>=4&&data.njets()<=5&&data.mj12()>300)
      oLeptPlot_data->Fill(data.njets(),data.mj12());
    // Low HT //
    //Zero Lepton Selection
    if(data.nleps()==0&&data.ht()>1300&&data.ht()<=1500&&data.nbm()>=1&&data.njets()>=4&&data.njets()<=7&&data.mj12()>300)
      zLeptPlot_data_lowht->Fill(data.njets(),data.mj12());
    //One Lepton Selection
    if(data.nleps()==1&&data.ht()>1000&&data.ht()<=1200&&data.nbm()>=1&&data.njets()>=4&&data.njets()<=5&&data.mj12()>300)
      oLeptPlot_data_lowht->Fill(data.njets(),data.mj12());
  }

  //Loop over MC tree
  for(unsigned int ievent=0; ievent<bkg.GetEntries(); ievent++){
    bkg.GetEntry(ievent);

    if(!(bkg.stitch()&&bkg.pass())) continue;
    //Zero Lepton Selection
    if(bkg.nleps()==0&&bkg.ht()>1200&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.njets()<=7&&bkg.mj12()>300)
      zLeptPlot_mc->Fill(bkg.njets(),bkg.mj12(),lumi*bkg.weight());
    //One Lepton Selection
    if(bkg.nleps()==1&&bkg.ht()>1200&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.njets()<=5&&bkg.mj12()>300)
      oLeptPlot_mc->Fill(bkg.njets(),bkg.mj12(),lumi*bkg.weight());
    // Low HT //
    //Zero Lepton Selection
    if(bkg.nleps()==0&&bkg.ht()>1200&&bkg.ht()<=1500&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.njets()<=7&&bkg.mj12()>300)
      zLeptPlot_mc_lowht->Fill(bkg.njets(),bkg.mj12(),lumi*bkg.weight());
    //One Lepton Selection
    if(bkg.nleps()==1&&bkg.ht()>1200&&bkg.ht()<=1500&&bkg.nbm()>=1&&bkg.njets()>=4&&bkg.njets()<=5&&bkg.mj12()>300)
      oLeptPlot_mc_lowht->Fill(bkg.njets(),bkg.mj12(),lumi*bkg.weight());
  } 

  //Data plots
  formatAndSaveHist(zLeptPlot_data);
  formatAndSaveHist(oLeptPlot_data);
  formatAndSaveHist(zLeptPlot_data_lowht);
  formatAndSaveHist(oLeptPlot_data_lowht);
 
  //MC plots
  formatAndSaveHist(zLeptPlot_mc);
  formatAndSaveHist(oLeptPlot_mc);
  formatAndSaveHist(zLeptPlot_mc_lowht);
  formatAndSaveHist(oLeptPlot_mc_lowht);

  //Make DataMC plots
  TH2D* zLeptPlot = static_cast<TH2D*>(zLeptPlot_data->Clone("zLeptPlot"));
  zLeptPlot->SetTitle("Data/MC Ratio");
  zLeptPlot->Divide(zLeptPlot_mc);
  TH2D* oLeptPlot = static_cast<TH2D*>(oLeptPlot_data->Clone("oLeptPlot"));
  oLeptPlot->SetTitle("Data/MC Ratio");
  oLeptPlot->Divide(oLeptPlot_mc);
  TH2D* zLeptPlot_lowht = static_cast<TH2D*>(zLeptPlot_data_lowht->Clone("zLeptPlot_lowht"));
  zLeptPlot_lowht->SetTitle("Data/MC Ratio");
  zLeptPlot_lowht->Divide(zLeptPlot_mc_lowht);
  TH2D* oLeptPlot_lowht = static_cast<TH2D*>(oLeptPlot_data_lowht->Clone("oLeptPlot_lowht"));
  oLeptPlot_lowht->SetTitle("Data/MC Ratio");
  oLeptPlot_lowht->Divide(oLeptPlot_mc_lowht);

  //Format and save DataMC plots
  formatAndSaveHist(zLeptPlot);
  formatAndSaveHist(oLeptPlot);
  formatAndSaveHist(zLeptPlot_lowht);
  formatAndSaveHist(oLeptPlot_lowht);
}

void formatAndSaveHist(TH2D* hist){
  TCanvas can;
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("8.2f");

  hist->SetMarkerSize(2);
  hist->GetXaxis()->CenterLabels(true);
  hist->GetXaxis()->SetNdivisions(205);

  hist->Draw("colz text error"); 
  can.SaveAs("./plots/"+outdir+"/"+hist->GetName()+plot_type);
}
