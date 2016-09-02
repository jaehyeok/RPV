// small_tree: base class to handle reduce tree ntuples
//File generated with generate_small_tree.exe

#include "small_tree.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include "TTreeFormula.h"

using namespace std;

bool small_tree::VectorLoader::loaded_ = false;

small_tree::VectorLoader small_tree::vl_ = small_tree::VectorLoader();

small_tree::VectorLoader::VectorLoader(){
  if(!loaded_){
    gROOT->ProcessLine("#include <vector>");
    loaded_ = true;
  }
}

const double small_tree::bad_val_ = -999.;

small_tree::small_tree():
  chain_("junk", "junk"),
  tree_("tree", "tree"),
  entry_(0),
  read_only_(false),
  ht_(0),
  b_ht_(tree_.Branch("ht", &ht_)),
  c_ht_(false),
  met_(0),
  b_met_(tree_.Branch("met", &met_)),
  c_met_(false),
  met_phi_(0),
  b_met_phi_(tree_.Branch("met_phi", &met_phi_)),
  c_met_phi_(false),
  mht_(0),
  b_mht_(tree_.Branch("mht", &mht_)),
  c_mht_(false),
  mj_(0),
  b_mj_(tree_.Branch("mj", &mj_)),
  c_mj_(false),
  mj08_(0),
  b_mj08_(tree_.Branch("mj08", &mj08_)),
  c_mj08_(false),
  mt_(0),
  b_mt_(tree_.Branch("mt", &mt_)),
  c_mt_(false),
  ntrupv_mean_(0),
  b_ntrupv_mean_(tree_.Branch("ntrupv_mean", &ntrupv_mean_)),
  c_ntrupv_mean_(false),
  weight_(0),
  b_weight_(tree_.Branch("weight", &weight_)),
  c_weight_(false),
  event_(0),
  b_event_(tree_.Branch("event", &event_)),
  c_event_(false),
  lumiblock_(0),
  b_lumiblock_(tree_.Branch("lumiblock", &lumiblock_)),
  c_lumiblock_(false),
  nbl_(0),
  b_nbl_(tree_.Branch("nbl", &nbl_)),
  c_nbl_(false),
  nbm_(0),
  b_nbm_(tree_.Branch("nbm", &nbm_)),
  c_nbm_(false),
  nbt_(0),
  b_nbt_(tree_.Branch("nbt", &nbt_)),
  c_nbt_(false),
  nels_(0),
  b_nels_(tree_.Branch("nels", &nels_)),
  c_nels_(false),
  nfjets_(0),
  b_nfjets_(tree_.Branch("nfjets", &nfjets_)),
  c_nfjets_(false),
  nfjets08_(0),
  b_nfjets08_(tree_.Branch("nfjets08", &nfjets08_)),
  c_nfjets08_(false),
  njets_(0),
  b_njets_(tree_.Branch("njets", &njets_)),
  c_njets_(false),
  nleps_(0),
  b_nleps_(tree_.Branch("nleps", &nleps_)),
  c_nleps_(false),
  nmus_(0),
  b_nmus_(tree_.Branch("nmus", &nmus_)),
  c_nmus_(false),
  npv_(0),
  b_npv_(tree_.Branch("npv", &npv_)),
  c_npv_(false),
  ntruels_(0),
  b_ntruels_(tree_.Branch("ntruels", &ntruels_)),
  c_ntruels_(false),
  ntruleps_(0),
  b_ntruleps_(tree_.Branch("ntruleps", &ntruleps_)),
  c_ntruleps_(false),
  ntrumus_(0),
  b_ntrumus_(tree_.Branch("ntrumus", &ntrumus_)),
  c_ntrumus_(false),
  ntrupv_(0),
  b_ntrupv_(tree_.Branch("ntrupv", &ntrupv_)),
  c_ntrupv_(false),
  ntrutaush_(0),
  b_ntrutaush_(tree_.Branch("ntrutaush", &ntrutaush_)),
  c_ntrutaush_(false),
  ntrutausl_(0),
  b_ntrutausl_(tree_.Branch("ntrutausl", &ntrutausl_)),
  c_ntrutausl_(false),
  nvels_(0),
  b_nvels_(tree_.Branch("nvels", &nvels_)),
  c_nvels_(false),
  nvmus_(0),
  b_nvmus_(tree_.Branch("nvmus", &nvmus_)),
  c_nvmus_(false),
  run_(0),
  b_run_(tree_.Branch("run", &run_)),
  c_run_(false),
  els_ispf_(0),
  p_els_ispf_(&els_ispf_),
  b_els_ispf_(tree_.Branch("els_ispf", &p_els_ispf_)),
  c_els_ispf_(false),
  els_sigid_(0),
  p_els_sigid_(&els_sigid_),
  b_els_sigid_(tree_.Branch("els_sigid", &p_els_sigid_)),
  c_els_sigid_(false),
  jets_islep_(0),
  p_jets_islep_(&jets_islep_),
  b_jets_islep_(tree_.Branch("jets_islep", &p_jets_islep_)),
  c_jets_islep_(false),
  mus_sigid_(0),
  p_mus_sigid_(&mus_sigid_),
  b_mus_sigid_(tree_.Branch("mus_sigid", &p_mus_sigid_)),
  c_mus_sigid_(false),
  els_d0_(0),
  p_els_d0_(&els_d0_),
  b_els_d0_(tree_.Branch("els_d0", &p_els_d0_)),
  c_els_d0_(false),
  els_dz_(0),
  p_els_dz_(&els_dz_),
  b_els_dz_(tree_.Branch("els_dz", &p_els_dz_)),
  c_els_dz_(false),
  els_eta_(0),
  p_els_eta_(&els_eta_),
  b_els_eta_(tree_.Branch("els_eta", &p_els_eta_)),
  c_els_eta_(false),
  els_phi_(0),
  p_els_phi_(&els_phi_),
  b_els_phi_(tree_.Branch("els_phi", &p_els_phi_)),
  c_els_phi_(false),
  els_pt_(0),
  p_els_pt_(&els_pt_),
  b_els_pt_(tree_.Branch("els_pt", &p_els_pt_)),
  c_els_pt_(false),
  els_sceta_(0),
  p_els_sceta_(&els_sceta_),
  b_els_sceta_(tree_.Branch("els_sceta", &p_els_sceta_)),
  c_els_sceta_(false),
  fjets08_eta_(0),
  p_fjets08_eta_(&fjets08_eta_),
  b_fjets08_eta_(tree_.Branch("fjets08_eta", &p_fjets08_eta_)),
  c_fjets08_eta_(false),
  fjets08_m_(0),
  p_fjets08_m_(&fjets08_m_),
  b_fjets08_m_(tree_.Branch("fjets08_m", &p_fjets08_m_)),
  c_fjets08_m_(false),
  fjets08_phi_(0),
  p_fjets08_phi_(&fjets08_phi_),
  b_fjets08_phi_(tree_.Branch("fjets08_phi", &p_fjets08_phi_)),
  c_fjets08_phi_(false),
  fjets08_poscsv_(0),
  p_fjets08_poscsv_(&fjets08_poscsv_),
  b_fjets08_poscsv_(tree_.Branch("fjets08_poscsv", &p_fjets08_poscsv_)),
  c_fjets08_poscsv_(false),
  fjets08_pt_(0),
  p_fjets08_pt_(&fjets08_pt_),
  b_fjets08_pt_(tree_.Branch("fjets08_pt", &p_fjets08_pt_)),
  c_fjets08_pt_(false),
  fjets08_sumcsv_(0),
  p_fjets08_sumcsv_(&fjets08_sumcsv_),
  b_fjets08_sumcsv_(tree_.Branch("fjets08_sumcsv", &p_fjets08_sumcsv_)),
  c_fjets08_sumcsv_(false),
  fjets_eta_(0),
  p_fjets_eta_(&fjets_eta_),
  b_fjets_eta_(tree_.Branch("fjets_eta", &p_fjets_eta_)),
  c_fjets_eta_(false),
  fjets_m_(0),
  p_fjets_m_(&fjets_m_),
  b_fjets_m_(tree_.Branch("fjets_m", &p_fjets_m_)),
  c_fjets_m_(false),
  fjets_phi_(0),
  p_fjets_phi_(&fjets_phi_),
  b_fjets_phi_(tree_.Branch("fjets_phi", &p_fjets_phi_)),
  c_fjets_phi_(false),
  fjets_poscsv_(0),
  p_fjets_poscsv_(&fjets_poscsv_),
  b_fjets_poscsv_(tree_.Branch("fjets_poscsv", &p_fjets_poscsv_)),
  c_fjets_poscsv_(false),
  fjets_pt_(0),
  p_fjets_pt_(&fjets_pt_),
  b_fjets_pt_(tree_.Branch("fjets_pt", &p_fjets_pt_)),
  c_fjets_pt_(false),
  fjets_sumcsv_(0),
  p_fjets_sumcsv_(&fjets_sumcsv_),
  b_fjets_sumcsv_(tree_.Branch("fjets_sumcsv", &p_fjets_sumcsv_)),
  c_fjets_sumcsv_(false),
  jets_csv_(0),
  p_jets_csv_(&jets_csv_),
  b_jets_csv_(tree_.Branch("jets_csv", &p_jets_csv_)),
  c_jets_csv_(false),
  jets_eta_(0),
  p_jets_eta_(&jets_eta_),
  b_jets_eta_(tree_.Branch("jets_eta", &p_jets_eta_)),
  c_jets_eta_(false),
  jets_m_(0),
  p_jets_m_(&jets_m_),
  b_jets_m_(tree_.Branch("jets_m", &p_jets_m_)),
  c_jets_m_(false),
  jets_phi_(0),
  p_jets_phi_(&jets_phi_),
  b_jets_phi_(tree_.Branch("jets_phi", &p_jets_phi_)),
  c_jets_phi_(false),
  jets_pt_(0),
  p_jets_pt_(&jets_pt_),
  b_jets_pt_(tree_.Branch("jets_pt", &p_jets_pt_)),
  c_jets_pt_(false),
  mus_d0_(0),
  p_mus_d0_(&mus_d0_),
  b_mus_d0_(tree_.Branch("mus_d0", &p_mus_d0_)),
  c_mus_d0_(false),
  mus_dz_(0),
  p_mus_dz_(&mus_dz_),
  b_mus_dz_(tree_.Branch("mus_dz", &p_mus_dz_)),
  c_mus_dz_(false),
  mus_eta_(0),
  p_mus_eta_(&mus_eta_),
  b_mus_eta_(tree_.Branch("mus_eta", &p_mus_eta_)),
  c_mus_eta_(false),
  mus_phi_(0),
  p_mus_phi_(&mus_phi_),
  b_mus_phi_(tree_.Branch("mus_phi", &p_mus_phi_)),
  c_mus_phi_(false),
  mus_pt_(0),
  p_mus_pt_(&mus_pt_),
  b_mus_pt_(tree_.Branch("mus_pt", &p_mus_pt_)),
  c_mus_pt_(false),
  els_charge_(0),
  p_els_charge_(&els_charge_),
  b_els_charge_(tree_.Branch("els_charge", &p_els_charge_)),
  c_els_charge_(false),
  fjets08_btags_(0),
  p_fjets08_btags_(&fjets08_btags_),
  b_fjets08_btags_(tree_.Branch("fjets08_btags", &p_fjets08_btags_)),
  c_fjets08_btags_(false),
  fjets08_nconst_(0),
  p_fjets08_nconst_(&fjets08_nconst_),
  b_fjets08_nconst_(tree_.Branch("fjets08_nconst", &p_fjets08_nconst_)),
  c_fjets08_nconst_(false),
  fjets_btags_(0),
  p_fjets_btags_(&fjets_btags_),
  b_fjets_btags_(tree_.Branch("fjets_btags", &p_fjets_btags_)),
  c_fjets_btags_(false),
  fjets_nconst_(0),
  p_fjets_nconst_(&fjets_nconst_),
  b_fjets_nconst_(tree_.Branch("fjets_nconst", &p_fjets_nconst_)),
  c_fjets_nconst_(false),
  jets_fjet08_index_(0),
  p_jets_fjet08_index_(&jets_fjet08_index_),
  b_jets_fjet08_index_(tree_.Branch("jets_fjet08_index", &p_jets_fjet08_index_)),
  c_jets_fjet08_index_(false),
  jets_fjet_index_(0),
  p_jets_fjet_index_(&jets_fjet_index_),
  b_jets_fjet_index_(tree_.Branch("jets_fjet_index", &p_jets_fjet_index_)),
  c_jets_fjet_index_(false),
  mus_charge_(0),
  b_mus_charge_(tree_.Branch("mus_charge", &mus_charge_)),
  c_mus_charge_(false){
}

small_tree::small_tree(const string &filename):
  chain_("tree","tree"),
  tree_("junk","junk"),
  entry_(0),
  read_only_(true),
  ht_(0),
  b_ht_(NULL),
  c_ht_(false),
  met_(0),
  b_met_(NULL),
  c_met_(false),
  met_phi_(0),
  b_met_phi_(NULL),
  c_met_phi_(false),
  mht_(0),
  b_mht_(NULL),
  c_mht_(false),
  mj_(0),
  b_mj_(NULL),
  c_mj_(false),
  mj08_(0),
  b_mj08_(NULL),
  c_mj08_(false),
  mt_(0),
  b_mt_(NULL),
  c_mt_(false),
  ntrupv_mean_(0),
  b_ntrupv_mean_(NULL),
  c_ntrupv_mean_(false),
  weight_(0),
  b_weight_(NULL),
  c_weight_(false),
  event_(0),
  b_event_(NULL),
  c_event_(false),
  lumiblock_(0),
  b_lumiblock_(NULL),
  c_lumiblock_(false),
  nbl_(0),
  b_nbl_(NULL),
  c_nbl_(false),
  nbm_(0),
  b_nbm_(NULL),
  c_nbm_(false),
  nbt_(0),
  b_nbt_(NULL),
  c_nbt_(false),
  nels_(0),
  b_nels_(NULL),
  c_nels_(false),
  nfjets_(0),
  b_nfjets_(NULL),
  c_nfjets_(false),
  nfjets08_(0),
  b_nfjets08_(NULL),
  c_nfjets08_(false),
  njets_(0),
  b_njets_(NULL),
  c_njets_(false),
  nleps_(0),
  b_nleps_(NULL),
  c_nleps_(false),
  nmus_(0),
  b_nmus_(NULL),
  c_nmus_(false),
  npv_(0),
  b_npv_(NULL),
  c_npv_(false),
  ntruels_(0),
  b_ntruels_(NULL),
  c_ntruels_(false),
  ntruleps_(0),
  b_ntruleps_(NULL),
  c_ntruleps_(false),
  ntrumus_(0),
  b_ntrumus_(NULL),
  c_ntrumus_(false),
  ntrupv_(0),
  b_ntrupv_(NULL),
  c_ntrupv_(false),
  ntrutaush_(0),
  b_ntrutaush_(NULL),
  c_ntrutaush_(false),
  ntrutausl_(0),
  b_ntrutausl_(NULL),
  c_ntrutausl_(false),
  nvels_(0),
  b_nvels_(NULL),
  c_nvels_(false),
  nvmus_(0),
  b_nvmus_(NULL),
  c_nvmus_(false),
  run_(0),
  b_run_(NULL),
  c_run_(false),
  els_ispf_(0),
  p_els_ispf_(&els_ispf_),
  b_els_ispf_(NULL),
  c_els_ispf_(false),
  els_sigid_(0),
  p_els_sigid_(&els_sigid_),
  b_els_sigid_(NULL),
  c_els_sigid_(false),
  jets_islep_(0),
  p_jets_islep_(&jets_islep_),
  b_jets_islep_(NULL),
  c_jets_islep_(false),
  mus_sigid_(0),
  p_mus_sigid_(&mus_sigid_),
  b_mus_sigid_(NULL),
  c_mus_sigid_(false),
  els_d0_(0),
  p_els_d0_(&els_d0_),
  b_els_d0_(NULL),
  c_els_d0_(false),
  els_dz_(0),
  p_els_dz_(&els_dz_),
  b_els_dz_(NULL),
  c_els_dz_(false),
  els_eta_(0),
  p_els_eta_(&els_eta_),
  b_els_eta_(NULL),
  c_els_eta_(false),
  els_phi_(0),
  p_els_phi_(&els_phi_),
  b_els_phi_(NULL),
  c_els_phi_(false),
  els_pt_(0),
  p_els_pt_(&els_pt_),
  b_els_pt_(NULL),
  c_els_pt_(false),
  els_sceta_(0),
  p_els_sceta_(&els_sceta_),
  b_els_sceta_(NULL),
  c_els_sceta_(false),
  fjets08_eta_(0),
  p_fjets08_eta_(&fjets08_eta_),
  b_fjets08_eta_(NULL),
  c_fjets08_eta_(false),
  fjets08_m_(0),
  p_fjets08_m_(&fjets08_m_),
  b_fjets08_m_(NULL),
  c_fjets08_m_(false),
  fjets08_phi_(0),
  p_fjets08_phi_(&fjets08_phi_),
  b_fjets08_phi_(NULL),
  c_fjets08_phi_(false),
  fjets08_poscsv_(0),
  p_fjets08_poscsv_(&fjets08_poscsv_),
  b_fjets08_poscsv_(NULL),
  c_fjets08_poscsv_(false),
  fjets08_pt_(0),
  p_fjets08_pt_(&fjets08_pt_),
  b_fjets08_pt_(NULL),
  c_fjets08_pt_(false),
  fjets08_sumcsv_(0),
  p_fjets08_sumcsv_(&fjets08_sumcsv_),
  b_fjets08_sumcsv_(NULL),
  c_fjets08_sumcsv_(false),
  fjets_eta_(0),
  p_fjets_eta_(&fjets_eta_),
  b_fjets_eta_(NULL),
  c_fjets_eta_(false),
  fjets_m_(0),
  p_fjets_m_(&fjets_m_),
  b_fjets_m_(NULL),
  c_fjets_m_(false),
  fjets_phi_(0),
  p_fjets_phi_(&fjets_phi_),
  b_fjets_phi_(NULL),
  c_fjets_phi_(false),
  fjets_poscsv_(0),
  p_fjets_poscsv_(&fjets_poscsv_),
  b_fjets_poscsv_(NULL),
  c_fjets_poscsv_(false),
  fjets_pt_(0),
  p_fjets_pt_(&fjets_pt_),
  b_fjets_pt_(NULL),
  c_fjets_pt_(false),
  fjets_sumcsv_(0),
  p_fjets_sumcsv_(&fjets_sumcsv_),
  b_fjets_sumcsv_(NULL),
  c_fjets_sumcsv_(false),
  jets_csv_(0),
  p_jets_csv_(&jets_csv_),
  b_jets_csv_(NULL),
  c_jets_csv_(false),
  jets_eta_(0),
  p_jets_eta_(&jets_eta_),
  b_jets_eta_(NULL),
  c_jets_eta_(false),
  jets_m_(0),
  p_jets_m_(&jets_m_),
  b_jets_m_(NULL),
  c_jets_m_(false),
  jets_phi_(0),
  p_jets_phi_(&jets_phi_),
  b_jets_phi_(NULL),
  c_jets_phi_(false),
  jets_pt_(0),
  p_jets_pt_(&jets_pt_),
  b_jets_pt_(NULL),
  c_jets_pt_(false),
  mus_d0_(0),
  p_mus_d0_(&mus_d0_),
  b_mus_d0_(NULL),
  c_mus_d0_(false),
  mus_dz_(0),
  p_mus_dz_(&mus_dz_),
  b_mus_dz_(NULL),
  c_mus_dz_(false),
  mus_eta_(0),
  p_mus_eta_(&mus_eta_),
  b_mus_eta_(NULL),
  c_mus_eta_(false),
  mus_phi_(0),
  p_mus_phi_(&mus_phi_),
  b_mus_phi_(NULL),
  c_mus_phi_(false),
  mus_pt_(0),
  p_mus_pt_(&mus_pt_),
  b_mus_pt_(NULL),
  c_mus_pt_(false),
  els_charge_(0),
  p_els_charge_(&els_charge_),
  b_els_charge_(NULL),
  c_els_charge_(false),
  fjets08_btags_(0),
  p_fjets08_btags_(&fjets08_btags_),
  b_fjets08_btags_(NULL),
  c_fjets08_btags_(false),
  fjets08_nconst_(0),
  p_fjets08_nconst_(&fjets08_nconst_),
  b_fjets08_nconst_(NULL),
  c_fjets08_nconst_(false),
  fjets_btags_(0),
  p_fjets_btags_(&fjets_btags_),
  b_fjets_btags_(NULL),
  c_fjets_btags_(false),
  fjets_nconst_(0),
  p_fjets_nconst_(&fjets_nconst_),
  b_fjets_nconst_(NULL),
  c_fjets_nconst_(false),
  jets_fjet08_index_(0),
  p_jets_fjet08_index_(&jets_fjet08_index_),
  b_jets_fjet08_index_(NULL),
  c_jets_fjet08_index_(false),
  jets_fjet_index_(0),
  p_jets_fjet_index_(&jets_fjet_index_),
  b_jets_fjet_index_(NULL),
  c_jets_fjet_index_(false),
  mus_charge_(0),
  p_mus_charge_(&mus_charge_),
  b_mus_charge_(NULL),
  c_mus_charge_(false){
  chain_.Add(filename.c_str());
  chain_.SetBranchAddress("ht", &ht_, &b_ht_);
  chain_.SetBranchAddress("met", &met_, &b_met_);
  chain_.SetBranchAddress("met_phi", &met_phi_, &b_met_phi_);
  chain_.SetBranchAddress("mht", &mht_, &b_mht_);
  chain_.SetBranchAddress("mj", &mj_, &b_mj_);
  chain_.SetBranchAddress("mj08", &mj08_, &b_mj08_);
  chain_.SetBranchAddress("mt", &mt_, &b_mt_);
  chain_.SetBranchAddress("ntrupv_mean", &ntrupv_mean_, &b_ntrupv_mean_);
  chain_.SetBranchAddress("weight", &weight_, &b_weight_);
  chain_.SetBranchAddress("event", &event_, &b_event_);
  chain_.SetBranchAddress("lumiblock", &lumiblock_, &b_lumiblock_);
  chain_.SetBranchAddress("nbl", &nbl_, &b_nbl_);
  chain_.SetBranchAddress("nbm", &nbm_, &b_nbm_);
  chain_.SetBranchAddress("nbt", &nbt_, &b_nbt_);
  chain_.SetBranchAddress("nels", &nels_, &b_nels_);
  chain_.SetBranchAddress("nfjets", &nfjets_, &b_nfjets_);
  chain_.SetBranchAddress("nfjets08", &nfjets08_, &b_nfjets08_);
  chain_.SetBranchAddress("njets", &njets_, &b_njets_);
  chain_.SetBranchAddress("nleps", &nleps_, &b_nleps_);
  chain_.SetBranchAddress("nmus", &nmus_, &b_nmus_);
  chain_.SetBranchAddress("npv", &npv_, &b_npv_);
  chain_.SetBranchAddress("ntruels", &ntruels_, &b_ntruels_);
  chain_.SetBranchAddress("ntruleps", &ntruleps_, &b_ntruleps_);
  chain_.SetBranchAddress("ntrumus", &ntrumus_, &b_ntrumus_);
  chain_.SetBranchAddress("ntrupv", &ntrupv_, &b_ntrupv_);
  chain_.SetBranchAddress("ntrutaush", &ntrutaush_, &b_ntrutaush_);
  chain_.SetBranchAddress("ntrutausl", &ntrutausl_, &b_ntrutausl_);
  chain_.SetBranchAddress("nvels", &nvels_, &b_nvels_);
  chain_.SetBranchAddress("nvmus", &nvmus_, &b_nvmus_);
  chain_.SetBranchAddress("run", &run_, &b_run_);
  chain_.SetBranchAddress("els_ispf", &p_els_ispf_, &b_els_ispf_);
  chain_.SetBranchAddress("els_sigid", &p_els_sigid_, &b_els_sigid_);
  chain_.SetBranchAddress("jets_islep", &p_jets_islep_, &b_jets_islep_);
  chain_.SetBranchAddress("mus_sigid", &p_mus_sigid_, &b_mus_sigid_);
  chain_.SetBranchAddress("els_d0", &p_els_d0_, &b_els_d0_);
  chain_.SetBranchAddress("els_dz", &p_els_dz_, &b_els_dz_);
  chain_.SetBranchAddress("els_eta", &p_els_eta_, &b_els_eta_);
  chain_.SetBranchAddress("els_phi", &p_els_phi_, &b_els_phi_);
  chain_.SetBranchAddress("els_pt", &p_els_pt_, &b_els_pt_);
  chain_.SetBranchAddress("els_sceta", &p_els_sceta_, &b_els_sceta_);
  chain_.SetBranchAddress("fjets08_eta", &p_fjets08_eta_, &b_fjets08_eta_);
  chain_.SetBranchAddress("fjets08_m", &p_fjets08_m_, &b_fjets08_m_);
  chain_.SetBranchAddress("fjets08_phi", &p_fjets08_phi_, &b_fjets08_phi_);
  chain_.SetBranchAddress("fjets08_poscsv", &p_fjets08_poscsv_, &b_fjets08_poscsv_);
  chain_.SetBranchAddress("fjets08_pt", &p_fjets08_pt_, &b_fjets08_pt_);
  chain_.SetBranchAddress("fjets08_sumcsv", &p_fjets08_sumcsv_, &b_fjets08_sumcsv_);
  chain_.SetBranchAddress("fjets_eta", &p_fjets_eta_, &b_fjets_eta_);
  chain_.SetBranchAddress("fjets_m", &p_fjets_m_, &b_fjets_m_);
  chain_.SetBranchAddress("fjets_phi", &p_fjets_phi_, &b_fjets_phi_);
  chain_.SetBranchAddress("fjets_poscsv", &p_fjets_poscsv_, &b_fjets_poscsv_);
  chain_.SetBranchAddress("fjets_pt", &p_fjets_pt_, &b_fjets_pt_);
  chain_.SetBranchAddress("fjets_sumcsv", &p_fjets_sumcsv_, &b_fjets_sumcsv_);
  chain_.SetBranchAddress("jets_csv", &p_jets_csv_, &b_jets_csv_);
  chain_.SetBranchAddress("jets_eta", &p_jets_eta_, &b_jets_eta_);
  chain_.SetBranchAddress("jets_m", &p_jets_m_, &b_jets_m_);
  chain_.SetBranchAddress("jets_phi", &p_jets_phi_, &b_jets_phi_);
  chain_.SetBranchAddress("jets_pt", &p_jets_pt_, &b_jets_pt_);
  chain_.SetBranchAddress("mus_d0", &p_mus_d0_, &b_mus_d0_);
  chain_.SetBranchAddress("mus_dz", &p_mus_dz_, &b_mus_dz_);
  chain_.SetBranchAddress("mus_eta", &p_mus_eta_, &b_mus_eta_);
  chain_.SetBranchAddress("mus_phi", &p_mus_phi_, &b_mus_phi_);
  chain_.SetBranchAddress("mus_pt", &p_mus_pt_, &b_mus_pt_);
  chain_.SetBranchAddress("els_charge", &p_els_charge_, &b_els_charge_);
  chain_.SetBranchAddress("fjets08_btags", &p_fjets08_btags_, &b_fjets08_btags_);
  chain_.SetBranchAddress("fjets08_nconst", &p_fjets08_nconst_, &b_fjets08_nconst_);
  chain_.SetBranchAddress("fjets_btags", &p_fjets_btags_, &b_fjets_btags_);
  chain_.SetBranchAddress("fjets_nconst", &p_fjets_nconst_, &b_fjets_nconst_);
  chain_.SetBranchAddress("jets_fjet08_index", &p_jets_fjet08_index_, &b_jets_fjet08_index_);
  chain_.SetBranchAddress("jets_fjet_index", &p_jets_fjet_index_, &b_jets_fjet_index_);
  chain_.SetBranchAddress("mus_charge", &p_mus_charge_, &b_mus_charge_);
}

void small_tree::Fill(){
  if(read_only_){
    throw std::logic_error("Trying to write to read-only tree");
  }else{
    tree_.Fill();
  }

  //Resetting variables
  ht_ = static_cast<float >(bad_val_);
  met_ = static_cast<float >(bad_val_);
  met_phi_ = static_cast<float >(bad_val_);
  mht_ = static_cast<float >(bad_val_);
  mj_ = static_cast<float >(bad_val_);
  mj08_ = static_cast<float >(bad_val_);
  mt_ = static_cast<float >(bad_val_);
  ntrupv_mean_ = static_cast<float >(bad_val_);
  weight_ = static_cast<float >(bad_val_);
  event_ = static_cast<int >(bad_val_);
  lumiblock_ = static_cast<int >(bad_val_);
  nbl_ = static_cast<int >(bad_val_);
  nbm_ = static_cast<int >(bad_val_);
  nbt_ = static_cast<int >(bad_val_);
  nels_ = static_cast<int >(bad_val_);
  nfjets_ = static_cast<int >(bad_val_);
  nfjets08_ = static_cast<int >(bad_val_);
  njets_ = static_cast<int >(bad_val_);
  nleps_ = static_cast<int >(bad_val_);
  nmus_ = static_cast<int >(bad_val_);
  npv_ = static_cast<int >(bad_val_);
  ntruels_ = static_cast<int >(bad_val_);
  ntruleps_ = static_cast<int >(bad_val_);
  ntrumus_ = static_cast<int >(bad_val_);
  ntrupv_ = static_cast<int >(bad_val_);
  ntrutaush_ = static_cast<int >(bad_val_);
  ntrutausl_ = static_cast<int >(bad_val_);
  nvels_ = static_cast<int >(bad_val_);
  nvmus_ = static_cast<int >(bad_val_);
  run_ = static_cast<int >(bad_val_);
  els_ispf_.clear();
  els_sigid_.clear();
  jets_islep_.clear();
  mus_sigid_.clear();
  els_d0_.clear();
  els_dz_.clear();
  els_eta_.clear();
  els_phi_.clear();
  els_pt_.clear();
  els_sceta_.clear();
  fjets08_eta_.clear();
  fjets08_m_.clear();
  fjets08_phi_.clear();
  fjets08_poscsv_.clear();
  fjets08_pt_.clear();
  fjets08_sumcsv_.clear();
  fjets_eta_.clear();
  fjets_m_.clear();
  fjets_phi_.clear();
  fjets_poscsv_.clear();
  fjets_pt_.clear();
  fjets_sumcsv_.clear();
  jets_csv_.clear();
  jets_eta_.clear();
  jets_m_.clear();
  jets_phi_.clear();
  jets_pt_.clear();
  mus_d0_.clear();
  mus_dz_.clear();
  mus_eta_.clear();
  mus_phi_.clear();
  mus_pt_.clear();
  els_charge_.clear();
  fjets08_btags_.clear();
  fjets08_nconst_.clear();
  fjets_btags_.clear();
  fjets_nconst_.clear();
  jets_fjet08_index_.clear();
  jets_fjet_index_.clear();
  mus_charge_.clear();
}

void small_tree::Write(){
  if(read_only_){
    throw std::logic_error("Trying to write to read-only tree.");
  }else{
    tree_.Write();
  }
}

string small_tree::Type() const{
  return "";
}

small_tree::~small_tree(){
}

int small_tree::Add(const std::string &filename){
  if(!read_only_){
    throw std::logic_error("Trying to add files to tree opened for writing.");
  }
  return chain_.Add(filename.c_str());
}

float small_tree::GetBranchValue(TString branch){
 TTreeFormula f("formula",branch, &chain_);
 float result = f.EvalInstance(0);
 return result;
}

bool small_tree::PassString(TString cut){
 TTreeFormula f("formula",cut, &chain_);
 bool result = f.EvalInstance(0);
 return result;
}

long small_tree::GetEntries() const{
  if(read_only_){
    return chain_.GetEntries();
  }else{
    return tree_.GetEntries();
  }
}

void small_tree::GetEntry(const long entry){
  if(!read_only_){
    throw std::logic_error("Trying to read from write-only tree.");
  }

  c_ht_ = false;
  c_met_ = false;
  c_met_phi_ = false;
  c_mht_ = false;
  c_mj_ = false;
  c_mj08_ = false;
  c_mt_ = false;
  c_ntrupv_mean_ = false;
  c_weight_ = false;
  c_event_ = false;
  c_lumiblock_ = false;
  c_nbl_ = false;
  c_nbm_ = false;
  c_nbt_ = false;
  c_nels_ = false;
  c_nfjets_ = false;
  c_nfjets08_ = false;
  c_njets_ = false;
  c_nleps_ = false;
  c_nmus_ = false;
  c_npv_ = false;
  c_ntruels_ = false;
  c_ntruleps_ = false;
  c_ntrumus_ = false;
  c_ntrupv_ = false;
  c_ntrutaush_ = false;
  c_ntrutausl_ = false;
  c_nvels_ = false;
  c_nvmus_ = false;
  c_run_ = false;
  c_els_ispf_ = false;
  c_els_sigid_ = false;
  c_jets_islep_ = false;
  c_mus_sigid_ = false;
  c_els_d0_ = false;
  c_els_dz_ = false;
  c_els_eta_ = false;
  c_els_phi_ = false;
  c_els_pt_ = false;
  c_els_sceta_ = false;
  c_fjets08_eta_ = false;
  c_fjets08_m_ = false;
  c_fjets08_phi_ = false;
  c_fjets08_poscsv_ = false;
  c_fjets08_pt_ = false;
  c_fjets08_sumcsv_ = false;
  c_fjets_eta_ = false;
  c_fjets_m_ = false;
  c_fjets_phi_ = false;
  c_fjets_poscsv_ = false;
  c_fjets_pt_ = false;
  c_fjets_sumcsv_ = false;
  c_jets_csv_ = false;
  c_jets_eta_ = false;
  c_jets_m_ = false;
  c_jets_phi_ = false;
  c_jets_pt_ = false;
  c_mus_d0_ = false;
  c_mus_dz_ = false;
  c_mus_eta_ = false;
  c_mus_phi_ = false;
  c_mus_pt_ = false;
  c_els_charge_ = false;
  c_fjets08_btags_ = false;
  c_fjets08_nconst_ = false;
  c_fjets_btags_ = false;
  c_fjets_nconst_ = false;
  c_jets_fjet08_index_ = false;
  c_jets_fjet_index_ = false;
  c_mus_charge_ = false;
  entry_ = chain_.LoadTree(entry);
}

float  const & small_tree::ht() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_ && b_ht_){
    b_ht_->GetEntry(entry_);
    c_ht_ = true;
  }
  return ht_;
}

float  const & small_tree::met() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_met_ && b_met_){
    b_met_->GetEntry(entry_);
    c_met_ = true;
  }
  return met_;
}

float  const & small_tree::met_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_met_phi_ && b_met_phi_){
    b_met_phi_->GetEntry(entry_);
    c_met_phi_ = true;
  }
  return met_phi_;
}

float  const & small_tree::mht() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mht_ && b_mht_){
    b_mht_->GetEntry(entry_);
    c_mht_ = true;
  }
  return mht_;
}

float  const & small_tree::mj() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mj_ && b_mj_){
    b_mj_->GetEntry(entry_);
    c_mj_ = true;
  }
  return mj_;
}

float  const & small_tree::mj08() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mj08_ && b_mj08_){
    b_mj08_->GetEntry(entry_);
    c_mj08_ = true;
  }
  return mj08_;
}

float  const & small_tree::mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mt_ && b_mt_){
    b_mt_->GetEntry(entry_);
    c_mt_ = true;
  }
  return mt_;
}

float  const & small_tree::ntrupv_mean() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrupv_mean_ && b_ntrupv_mean_){
    b_ntrupv_mean_->GetEntry(entry_);
    c_ntrupv_mean_ = true;
  }
  return ntrupv_mean_;
}

float  const & small_tree::weight() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_weight_ && b_weight_){
    b_weight_->GetEntry(entry_);
    c_weight_ = true;
  }
  return weight_;
}

int  const & small_tree::event() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_event_ && b_event_){
    b_event_->GetEntry(entry_);
    c_event_ = true;
  }
  return event_;
}

int  const & small_tree::lumiblock() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lumiblock_ && b_lumiblock_){
    b_lumiblock_->GetEntry(entry_);
    c_lumiblock_ = true;
  }
  return lumiblock_;
}

int  const & small_tree::nbl() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbl_ && b_nbl_){
    b_nbl_->GetEntry(entry_);
    c_nbl_ = true;
  }
  return nbl_;
}

int  const & small_tree::nbm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbm_ && b_nbm_){
    b_nbm_->GetEntry(entry_);
    c_nbm_ = true;
  }
  return nbm_;
}

int  const & small_tree::nbt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbt_ && b_nbt_){
    b_nbt_->GetEntry(entry_);
    c_nbt_ = true;
  }
  return nbt_;
}

int  const & small_tree::nels() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nels_ && b_nels_){
    b_nels_->GetEntry(entry_);
    c_nels_ = true;
  }
  return nels_;
}

int  const & small_tree::nfjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nfjets_ && b_nfjets_){
    b_nfjets_->GetEntry(entry_);
    c_nfjets_ = true;
  }
  return nfjets_;
}

int  const & small_tree::nfjets08() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nfjets08_ && b_nfjets08_){
    b_nfjets08_->GetEntry(entry_);
    c_nfjets08_ = true;
  }
  return nfjets08_;
}

int  const & small_tree::njets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_njets_ && b_njets_){
    b_njets_->GetEntry(entry_);
    c_njets_ = true;
  }
  return njets_;
}

int  const & small_tree::nleps() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nleps_ && b_nleps_){
    b_nleps_->GetEntry(entry_);
    c_nleps_ = true;
  }
  return nleps_;
}

int  const & small_tree::nmus() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nmus_ && b_nmus_){
    b_nmus_->GetEntry(entry_);
    c_nmus_ = true;
  }
  return nmus_;
}

int  const & small_tree::npv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_npv_ && b_npv_){
    b_npv_->GetEntry(entry_);
    c_npv_ = true;
  }
  return npv_;
}

int  const & small_tree::ntruels() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntruels_ && b_ntruels_){
    b_ntruels_->GetEntry(entry_);
    c_ntruels_ = true;
  }
  return ntruels_;
}

int  const & small_tree::ntruleps() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntruleps_ && b_ntruleps_){
    b_ntruleps_->GetEntry(entry_);
    c_ntruleps_ = true;
  }
  return ntruleps_;
}

int  const & small_tree::ntrumus() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrumus_ && b_ntrumus_){
    b_ntrumus_->GetEntry(entry_);
    c_ntrumus_ = true;
  }
  return ntrumus_;
}

int  const & small_tree::ntrupv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrupv_ && b_ntrupv_){
    b_ntrupv_->GetEntry(entry_);
    c_ntrupv_ = true;
  }
  return ntrupv_;
}

int  const & small_tree::ntrutaush() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrutaush_ && b_ntrutaush_){
    b_ntrutaush_->GetEntry(entry_);
    c_ntrutaush_ = true;
  }
  return ntrutaush_;
}

int  const & small_tree::ntrutausl() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrutausl_ && b_ntrutausl_){
    b_ntrutausl_->GetEntry(entry_);
    c_ntrutausl_ = true;
  }
  return ntrutausl_;
}

int  const & small_tree::nvels() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvels_ && b_nvels_){
    b_nvels_->GetEntry(entry_);
    c_nvels_ = true;
  }
  return nvels_;
}

int  const & small_tree::nvmus() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvmus_ && b_nvmus_){
    b_nvmus_->GetEntry(entry_);
    c_nvmus_ = true;
  }
  return nvmus_;
}

int  const & small_tree::run() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_run_ && b_run_){
    b_run_->GetEntry(entry_);
    c_run_ = true;
  }
  return run_;
}

std::vector<bool>  const & small_tree::els_ispf() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_ispf_ && b_els_ispf_){
    b_els_ispf_->GetEntry(entry_);
    c_els_ispf_ = true;
  }
  return els_ispf_;
}

std::vector<bool>  const & small_tree::els_sigid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_sigid_ && b_els_sigid_){
    b_els_sigid_->GetEntry(entry_);
    c_els_sigid_ = true;
  }
  return els_sigid_;
}

std::vector<bool>  const & small_tree::jets_islep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_islep_ && b_jets_islep_){
    b_jets_islep_->GetEntry(entry_);
    c_jets_islep_ = true;
  }
  return jets_islep_;
}

std::vector<bool>  const & small_tree::mus_sigid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_sigid_ && b_mus_sigid_){
    b_mus_sigid_->GetEntry(entry_);
    c_mus_sigid_ = true;
  }
  return mus_sigid_;
}

std::vector<float>  const & small_tree::els_d0() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_d0_ && b_els_d0_){
    b_els_d0_->GetEntry(entry_);
    c_els_d0_ = true;
  }
  return els_d0_;
}

std::vector<float>  const & small_tree::els_dz() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_dz_ && b_els_dz_){
    b_els_dz_->GetEntry(entry_);
    c_els_dz_ = true;
  }
  return els_dz_;
}

std::vector<float>  const & small_tree::els_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_eta_ && b_els_eta_){
    b_els_eta_->GetEntry(entry_);
    c_els_eta_ = true;
  }
  return els_eta_;
}

std::vector<float>  const & small_tree::els_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_phi_ && b_els_phi_){
    b_els_phi_->GetEntry(entry_);
    c_els_phi_ = true;
  }
  return els_phi_;
}

std::vector<float>  const & small_tree::els_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_pt_ && b_els_pt_){
    b_els_pt_->GetEntry(entry_);
    c_els_pt_ = true;
  }
  return els_pt_;
}

std::vector<float>  const & small_tree::els_sceta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_sceta_ && b_els_sceta_){
    b_els_sceta_->GetEntry(entry_);
    c_els_sceta_ = true;
  }
  return els_sceta_;
}

std::vector<float>  const & small_tree::fjets08_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_eta_ && b_fjets08_eta_){
    b_fjets08_eta_->GetEntry(entry_);
    c_fjets08_eta_ = true;
  }
  return fjets08_eta_;
}

std::vector<float>  const & small_tree::fjets08_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_m_ && b_fjets08_m_){
    b_fjets08_m_->GetEntry(entry_);
    c_fjets08_m_ = true;
  }
  return fjets08_m_;
}

std::vector<float>  const & small_tree::fjets08_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_phi_ && b_fjets08_phi_){
    b_fjets08_phi_->GetEntry(entry_);
    c_fjets08_phi_ = true;
  }
  return fjets08_phi_;
}

std::vector<float>  const & small_tree::fjets08_poscsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_poscsv_ && b_fjets08_poscsv_){
    b_fjets08_poscsv_->GetEntry(entry_);
    c_fjets08_poscsv_ = true;
  }
  return fjets08_poscsv_;
}

std::vector<float>  const & small_tree::fjets08_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_pt_ && b_fjets08_pt_){
    b_fjets08_pt_->GetEntry(entry_);
    c_fjets08_pt_ = true;
  }
  return fjets08_pt_;
}

std::vector<float>  const & small_tree::fjets08_sumcsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_sumcsv_ && b_fjets08_sumcsv_){
    b_fjets08_sumcsv_->GetEntry(entry_);
    c_fjets08_sumcsv_ = true;
  }
  return fjets08_sumcsv_;
}

std::vector<float>  const & small_tree::fjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_eta_ && b_fjets_eta_){
    b_fjets_eta_->GetEntry(entry_);
    c_fjets_eta_ = true;
  }
  return fjets_eta_;
}

std::vector<float>  const & small_tree::fjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_m_ && b_fjets_m_){
    b_fjets_m_->GetEntry(entry_);
    c_fjets_m_ = true;
  }
  return fjets_m_;
}

std::vector<float>  const & small_tree::fjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_phi_ && b_fjets_phi_){
    b_fjets_phi_->GetEntry(entry_);
    c_fjets_phi_ = true;
  }
  return fjets_phi_;
}

std::vector<float>  const & small_tree::fjets_poscsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_poscsv_ && b_fjets_poscsv_){
    b_fjets_poscsv_->GetEntry(entry_);
    c_fjets_poscsv_ = true;
  }
  return fjets_poscsv_;
}

std::vector<float>  const & small_tree::fjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_pt_ && b_fjets_pt_){
    b_fjets_pt_->GetEntry(entry_);
    c_fjets_pt_ = true;
  }
  return fjets_pt_;
}

std::vector<float>  const & small_tree::fjets_sumcsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_sumcsv_ && b_fjets_sumcsv_){
    b_fjets_sumcsv_->GetEntry(entry_);
    c_fjets_sumcsv_ = true;
  }
  return fjets_sumcsv_;
}

std::vector<float>  const & small_tree::jets_csv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_csv_ && b_jets_csv_){
    b_jets_csv_->GetEntry(entry_);
    c_jets_csv_ = true;
  }
  return jets_csv_;
}

std::vector<float>  const & small_tree::jets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_eta_ && b_jets_eta_){
    b_jets_eta_->GetEntry(entry_);
    c_jets_eta_ = true;
  }
  return jets_eta_;
}

std::vector<float>  const & small_tree::jets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_m_ && b_jets_m_){
    b_jets_m_->GetEntry(entry_);
    c_jets_m_ = true;
  }
  return jets_m_;
}

std::vector<float>  const & small_tree::jets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_phi_ && b_jets_phi_){
    b_jets_phi_->GetEntry(entry_);
    c_jets_phi_ = true;
  }
  return jets_phi_;
}

std::vector<float>  const & small_tree::jets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_pt_ && b_jets_pt_){
    b_jets_pt_->GetEntry(entry_);
    c_jets_pt_ = true;
  }
  return jets_pt_;
}

std::vector<float>  const & small_tree::mus_d0() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_d0_ && b_mus_d0_){
    b_mus_d0_->GetEntry(entry_);
    c_mus_d0_ = true;
  }
  return mus_d0_;
}

std::vector<float>  const & small_tree::mus_dz() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_dz_ && b_mus_dz_){
    b_mus_dz_->GetEntry(entry_);
    c_mus_dz_ = true;
  }
  return mus_dz_;
}

std::vector<float>  const & small_tree::mus_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_eta_ && b_mus_eta_){
    b_mus_eta_->GetEntry(entry_);
    c_mus_eta_ = true;
  }
  return mus_eta_;
}

std::vector<float>  const & small_tree::mus_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_phi_ && b_mus_phi_){
    b_mus_phi_->GetEntry(entry_);
    c_mus_phi_ = true;
  }
  return mus_phi_;
}

std::vector<float>  const & small_tree::mus_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_pt_ && b_mus_pt_){
    b_mus_pt_->GetEntry(entry_);
    c_mus_pt_ = true;
  }
  return mus_pt_;
}

std::vector<int>  const & small_tree::els_charge() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_charge_ && b_els_charge_){
    b_els_charge_->GetEntry(entry_);
    c_els_charge_ = true;
  }
  return els_charge_;
}

std::vector<int>  const & small_tree::fjets08_btags() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_btags_ && b_fjets08_btags_){
    b_fjets08_btags_->GetEntry(entry_);
    c_fjets08_btags_ = true;
  }
  return fjets08_btags_;
}

std::vector<int>  const & small_tree::fjets08_nconst() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets08_nconst_ && b_fjets08_nconst_){
    b_fjets08_nconst_->GetEntry(entry_);
    c_fjets08_nconst_ = true;
  }
  return fjets08_nconst_;
}

std::vector<int>  const & small_tree::fjets_btags() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_btags_ && b_fjets_btags_){
    b_fjets_btags_->GetEntry(entry_);
    c_fjets_btags_ = true;
  }
  return fjets_btags_;
}

std::vector<int>  const & small_tree::fjets_nconst() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets_nconst_ && b_fjets_nconst_){
    b_fjets_nconst_->GetEntry(entry_);
    c_fjets_nconst_ = true;
  }
  return fjets_nconst_;
}

std::vector<int>  const & small_tree::jets_fjet08_index() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_fjet08_index_ && b_jets_fjet08_index_){
    b_jets_fjet08_index_->GetEntry(entry_);
    c_jets_fjet08_index_ = true;
  }
  return jets_fjet08_index_;
}

std::vector<int>  const & small_tree::jets_fjet_index() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_fjet_index_ && b_jets_fjet_index_){
    b_jets_fjet_index_->GetEntry(entry_);
    c_jets_fjet_index_ = true;
  }
  return jets_fjet_index_;
}

std::vector<int>  const & small_tree::mus_charge() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_charge_ && b_mus_charge_){
    b_mus_charge_->GetEntry(entry_);
    c_mus_charge_ = true;
  }
  return mus_charge_;
}

float  & small_tree::ht(){
  if(read_only_ && !c_ht_ && b_ht_){
    b_ht_->GetEntry(entry_);
    c_ht_ = true;
  }
  return ht_;
}

float  & small_tree::met(){
  if(read_only_ && !c_met_ && b_met_){
    b_met_->GetEntry(entry_);
    c_met_ = true;
  }
  return met_;
}

float  & small_tree::met_phi(){
  if(read_only_ && !c_met_phi_ && b_met_phi_){
    b_met_phi_->GetEntry(entry_);
    c_met_phi_ = true;
  }
  return met_phi_;
}

float  & small_tree::mht(){
  if(read_only_ && !c_mht_ && b_mht_){
    b_mht_->GetEntry(entry_);
    c_mht_ = true;
  }
  return mht_;
}

float  & small_tree::mj(){
  if(read_only_ && !c_mj_ && b_mj_){
    b_mj_->GetEntry(entry_);
    c_mj_ = true;
  }
  return mj_;
}

float  & small_tree::mj08(){
  if(read_only_ && !c_mj08_ && b_mj08_){
    b_mj08_->GetEntry(entry_);
    c_mj08_ = true;
  }
  return mj08_;
}

float  & small_tree::mt(){
  if(read_only_ && !c_mt_ && b_mt_){
    b_mt_->GetEntry(entry_);
    c_mt_ = true;
  }
  return mt_;
}

float  & small_tree::ntrupv_mean(){
  if(read_only_ && !c_ntrupv_mean_ && b_ntrupv_mean_){
    b_ntrupv_mean_->GetEntry(entry_);
    c_ntrupv_mean_ = true;
  }
  return ntrupv_mean_;
}

float  & small_tree::weight(){
  if(read_only_ && !c_weight_ && b_weight_){
    b_weight_->GetEntry(entry_);
    c_weight_ = true;
  }
  return weight_;
}

int  & small_tree::event(){
  if(read_only_ && !c_event_ && b_event_){
    b_event_->GetEntry(entry_);
    c_event_ = true;
  }
  return event_;
}

int  & small_tree::lumiblock(){
  if(read_only_ && !c_lumiblock_ && b_lumiblock_){
    b_lumiblock_->GetEntry(entry_);
    c_lumiblock_ = true;
  }
  return lumiblock_;
}

int  & small_tree::nbl(){
  if(read_only_ && !c_nbl_ && b_nbl_){
    b_nbl_->GetEntry(entry_);
    c_nbl_ = true;
  }
  return nbl_;
}

int  & small_tree::nbm(){
  if(read_only_ && !c_nbm_ && b_nbm_){
    b_nbm_->GetEntry(entry_);
    c_nbm_ = true;
  }
  return nbm_;
}

int  & small_tree::nbt(){
  if(read_only_ && !c_nbt_ && b_nbt_){
    b_nbt_->GetEntry(entry_);
    c_nbt_ = true;
  }
  return nbt_;
}

int  & small_tree::nels(){
  if(read_only_ && !c_nels_ && b_nels_){
    b_nels_->GetEntry(entry_);
    c_nels_ = true;
  }
  return nels_;
}

int  & small_tree::nfjets(){
  if(read_only_ && !c_nfjets_ && b_nfjets_){
    b_nfjets_->GetEntry(entry_);
    c_nfjets_ = true;
  }
  return nfjets_;
}

int  & small_tree::nfjets08(){
  if(read_only_ && !c_nfjets08_ && b_nfjets08_){
    b_nfjets08_->GetEntry(entry_);
    c_nfjets08_ = true;
  }
  return nfjets08_;
}

int  & small_tree::njets(){
  if(read_only_ && !c_njets_ && b_njets_){
    b_njets_->GetEntry(entry_);
    c_njets_ = true;
  }
  return njets_;
}

int  & small_tree::nleps(){
  if(read_only_ && !c_nleps_ && b_nleps_){
    b_nleps_->GetEntry(entry_);
    c_nleps_ = true;
  }
  return nleps_;
}

int  & small_tree::nmus(){
  if(read_only_ && !c_nmus_ && b_nmus_){
    b_nmus_->GetEntry(entry_);
    c_nmus_ = true;
  }
  return nmus_;
}

int  & small_tree::npv(){
  if(read_only_ && !c_npv_ && b_npv_){
    b_npv_->GetEntry(entry_);
    c_npv_ = true;
  }
  return npv_;
}

int  & small_tree::ntruels(){
  if(read_only_ && !c_ntruels_ && b_ntruels_){
    b_ntruels_->GetEntry(entry_);
    c_ntruels_ = true;
  }
  return ntruels_;
}

int  & small_tree::ntruleps(){
  if(read_only_ && !c_ntruleps_ && b_ntruleps_){
    b_ntruleps_->GetEntry(entry_);
    c_ntruleps_ = true;
  }
  return ntruleps_;
}

int  & small_tree::ntrumus(){
  if(read_only_ && !c_ntrumus_ && b_ntrumus_){
    b_ntrumus_->GetEntry(entry_);
    c_ntrumus_ = true;
  }
  return ntrumus_;
}

int  & small_tree::ntrupv(){
  if(read_only_ && !c_ntrupv_ && b_ntrupv_){
    b_ntrupv_->GetEntry(entry_);
    c_ntrupv_ = true;
  }
  return ntrupv_;
}

int  & small_tree::ntrutaush(){
  if(read_only_ && !c_ntrutaush_ && b_ntrutaush_){
    b_ntrutaush_->GetEntry(entry_);
    c_ntrutaush_ = true;
  }
  return ntrutaush_;
}

int  & small_tree::ntrutausl(){
  if(read_only_ && !c_ntrutausl_ && b_ntrutausl_){
    b_ntrutausl_->GetEntry(entry_);
    c_ntrutausl_ = true;
  }
  return ntrutausl_;
}

int  & small_tree::nvels(){
  if(read_only_ && !c_nvels_ && b_nvels_){
    b_nvels_->GetEntry(entry_);
    c_nvels_ = true;
  }
  return nvels_;
}

int  & small_tree::nvmus(){
  if(read_only_ && !c_nvmus_ && b_nvmus_){
    b_nvmus_->GetEntry(entry_);
    c_nvmus_ = true;
  }
  return nvmus_;
}

int  & small_tree::run(){
  if(read_only_ && !c_run_ && b_run_){
    b_run_->GetEntry(entry_);
    c_run_ = true;
  }
  return run_;
}

std::vector<bool>  & small_tree::els_ispf(){
  if(read_only_ && !c_els_ispf_ && b_els_ispf_){
    b_els_ispf_->GetEntry(entry_);
    c_els_ispf_ = true;
  }
  return els_ispf_;
}

std::vector<bool>  & small_tree::els_sigid(){
  if(read_only_ && !c_els_sigid_ && b_els_sigid_){
    b_els_sigid_->GetEntry(entry_);
    c_els_sigid_ = true;
  }
  return els_sigid_;
}

std::vector<bool>  & small_tree::jets_islep(){
  if(read_only_ && !c_jets_islep_ && b_jets_islep_){
    b_jets_islep_->GetEntry(entry_);
    c_jets_islep_ = true;
  }
  return jets_islep_;
}

std::vector<bool>  & small_tree::mus_sigid(){
  if(read_only_ && !c_mus_sigid_ && b_mus_sigid_){
    b_mus_sigid_->GetEntry(entry_);
    c_mus_sigid_ = true;
  }
  return mus_sigid_;
}

std::vector<float>  & small_tree::els_d0(){
  if(read_only_ && !c_els_d0_ && b_els_d0_){
    b_els_d0_->GetEntry(entry_);
    c_els_d0_ = true;
  }
  return els_d0_;
}

std::vector<float>  & small_tree::els_dz(){
  if(read_only_ && !c_els_dz_ && b_els_dz_){
    b_els_dz_->GetEntry(entry_);
    c_els_dz_ = true;
  }
  return els_dz_;
}

std::vector<float>  & small_tree::els_eta(){
  if(read_only_ && !c_els_eta_ && b_els_eta_){
    b_els_eta_->GetEntry(entry_);
    c_els_eta_ = true;
  }
  return els_eta_;
}

std::vector<float>  & small_tree::els_phi(){
  if(read_only_ && !c_els_phi_ && b_els_phi_){
    b_els_phi_->GetEntry(entry_);
    c_els_phi_ = true;
  }
  return els_phi_;
}

std::vector<float>  & small_tree::els_pt(){
  if(read_only_ && !c_els_pt_ && b_els_pt_){
    b_els_pt_->GetEntry(entry_);
    c_els_pt_ = true;
  }
  return els_pt_;
}

std::vector<float>  & small_tree::els_sceta(){
  if(read_only_ && !c_els_sceta_ && b_els_sceta_){
    b_els_sceta_->GetEntry(entry_);
    c_els_sceta_ = true;
  }
  return els_sceta_;
}

std::vector<float>  & small_tree::fjets08_eta(){
  if(read_only_ && !c_fjets08_eta_ && b_fjets08_eta_){
    b_fjets08_eta_->GetEntry(entry_);
    c_fjets08_eta_ = true;
  }
  return fjets08_eta_;
}

std::vector<float>  & small_tree::fjets08_m(){
  if(read_only_ && !c_fjets08_m_ && b_fjets08_m_){
    b_fjets08_m_->GetEntry(entry_);
    c_fjets08_m_ = true;
  }
  return fjets08_m_;
}

std::vector<float>  & small_tree::fjets08_phi(){
  if(read_only_ && !c_fjets08_phi_ && b_fjets08_phi_){
    b_fjets08_phi_->GetEntry(entry_);
    c_fjets08_phi_ = true;
  }
  return fjets08_phi_;
}

std::vector<float>  & small_tree::fjets08_poscsv(){
  if(read_only_ && !c_fjets08_poscsv_ && b_fjets08_poscsv_){
    b_fjets08_poscsv_->GetEntry(entry_);
    c_fjets08_poscsv_ = true;
  }
  return fjets08_poscsv_;
}

std::vector<float>  & small_tree::fjets08_pt(){
  if(read_only_ && !c_fjets08_pt_ && b_fjets08_pt_){
    b_fjets08_pt_->GetEntry(entry_);
    c_fjets08_pt_ = true;
  }
  return fjets08_pt_;
}

std::vector<float>  & small_tree::fjets08_sumcsv(){
  if(read_only_ && !c_fjets08_sumcsv_ && b_fjets08_sumcsv_){
    b_fjets08_sumcsv_->GetEntry(entry_);
    c_fjets08_sumcsv_ = true;
  }
  return fjets08_sumcsv_;
}

std::vector<float>  & small_tree::fjets_eta(){
  if(read_only_ && !c_fjets_eta_ && b_fjets_eta_){
    b_fjets_eta_->GetEntry(entry_);
    c_fjets_eta_ = true;
  }
  return fjets_eta_;
}

std::vector<float>  & small_tree::fjets_m(){
  if(read_only_ && !c_fjets_m_ && b_fjets_m_){
    b_fjets_m_->GetEntry(entry_);
    c_fjets_m_ = true;
  }
  return fjets_m_;
}

std::vector<float>  & small_tree::fjets_phi(){
  if(read_only_ && !c_fjets_phi_ && b_fjets_phi_){
    b_fjets_phi_->GetEntry(entry_);
    c_fjets_phi_ = true;
  }
  return fjets_phi_;
}

std::vector<float>  & small_tree::fjets_poscsv(){
  if(read_only_ && !c_fjets_poscsv_ && b_fjets_poscsv_){
    b_fjets_poscsv_->GetEntry(entry_);
    c_fjets_poscsv_ = true;
  }
  return fjets_poscsv_;
}

std::vector<float>  & small_tree::fjets_pt(){
  if(read_only_ && !c_fjets_pt_ && b_fjets_pt_){
    b_fjets_pt_->GetEntry(entry_);
    c_fjets_pt_ = true;
  }
  return fjets_pt_;
}

std::vector<float>  & small_tree::fjets_sumcsv(){
  if(read_only_ && !c_fjets_sumcsv_ && b_fjets_sumcsv_){
    b_fjets_sumcsv_->GetEntry(entry_);
    c_fjets_sumcsv_ = true;
  }
  return fjets_sumcsv_;
}

std::vector<float>  & small_tree::jets_csv(){
  if(read_only_ && !c_jets_csv_ && b_jets_csv_){
    b_jets_csv_->GetEntry(entry_);
    c_jets_csv_ = true;
  }
  return jets_csv_;
}

std::vector<float>  & small_tree::jets_eta(){
  if(read_only_ && !c_jets_eta_ && b_jets_eta_){
    b_jets_eta_->GetEntry(entry_);
    c_jets_eta_ = true;
  }
  return jets_eta_;
}

std::vector<float>  & small_tree::jets_m(){
  if(read_only_ && !c_jets_m_ && b_jets_m_){
    b_jets_m_->GetEntry(entry_);
    c_jets_m_ = true;
  }
  return jets_m_;
}

std::vector<float>  & small_tree::jets_phi(){
  if(read_only_ && !c_jets_phi_ && b_jets_phi_){
    b_jets_phi_->GetEntry(entry_);
    c_jets_phi_ = true;
  }
  return jets_phi_;
}

std::vector<float>  & small_tree::jets_pt(){
  if(read_only_ && !c_jets_pt_ && b_jets_pt_){
    b_jets_pt_->GetEntry(entry_);
    c_jets_pt_ = true;
  }
  return jets_pt_;
}

std::vector<float>  & small_tree::mus_d0(){
  if(read_only_ && !c_mus_d0_ && b_mus_d0_){
    b_mus_d0_->GetEntry(entry_);
    c_mus_d0_ = true;
  }
  return mus_d0_;
}

std::vector<float>  & small_tree::mus_dz(){
  if(read_only_ && !c_mus_dz_ && b_mus_dz_){
    b_mus_dz_->GetEntry(entry_);
    c_mus_dz_ = true;
  }
  return mus_dz_;
}

std::vector<float>  & small_tree::mus_eta(){
  if(read_only_ && !c_mus_eta_ && b_mus_eta_){
    b_mus_eta_->GetEntry(entry_);
    c_mus_eta_ = true;
  }
  return mus_eta_;
}

std::vector<float>  & small_tree::mus_phi(){
  if(read_only_ && !c_mus_phi_ && b_mus_phi_){
    b_mus_phi_->GetEntry(entry_);
    c_mus_phi_ = true;
  }
  return mus_phi_;
}

std::vector<float>  & small_tree::mus_pt(){
  if(read_only_ && !c_mus_pt_ && b_mus_pt_){
    b_mus_pt_->GetEntry(entry_);
    c_mus_pt_ = true;
  }
  return mus_pt_;
}

std::vector<int>  & small_tree::els_charge(){
  if(read_only_ && !c_els_charge_ && b_els_charge_){
    b_els_charge_->GetEntry(entry_);
    c_els_charge_ = true;
  }
  return els_charge_;
}

std::vector<int>  & small_tree::fjets08_btags(){
  if(read_only_ && !c_fjets08_btags_ && b_fjets08_btags_){
    b_fjets08_btags_->GetEntry(entry_);
    c_fjets08_btags_ = true;
  }
  return fjets08_btags_;
}

std::vector<int>  & small_tree::fjets08_nconst(){
  if(read_only_ && !c_fjets08_nconst_ && b_fjets08_nconst_){
    b_fjets08_nconst_->GetEntry(entry_);
    c_fjets08_nconst_ = true;
  }
  return fjets08_nconst_;
}

std::vector<int>  & small_tree::fjets_btags(){
  if(read_only_ && !c_fjets_btags_ && b_fjets_btags_){
    b_fjets_btags_->GetEntry(entry_);
    c_fjets_btags_ = true;
  }
  return fjets_btags_;
}

std::vector<int>  & small_tree::fjets_nconst(){
  if(read_only_ && !c_fjets_nconst_ && b_fjets_nconst_){
    b_fjets_nconst_->GetEntry(entry_);
    c_fjets_nconst_ = true;
  }
  return fjets_nconst_;
}

std::vector<int>  & small_tree::jets_fjet08_index(){
  if(read_only_ && !c_jets_fjet08_index_ && b_jets_fjet08_index_){
    b_jets_fjet08_index_->GetEntry(entry_);
    c_jets_fjet08_index_ = true;
  }
  return jets_fjet08_index_;
}

std::vector<int>  & small_tree::jets_fjet_index(){
  if(read_only_ && !c_jets_fjet_index_ && b_jets_fjet_index_){
    b_jets_fjet_index_->GetEntry(entry_);
    c_jets_fjet_index_ = true;
  }
  return jets_fjet_index_;
}

std::vector<int>  & small_tree::mus_charge(){
  if(read_only_ && !c_mus_charge_ && b_mus_charge_){
    b_mus_charge_->GetEntry(entry_);
    c_mus_charge_ = true;
  }
  return mus_charge_;
}

bool  const & small_tree::pass() const{
  throw std::logic_error("pass does not exist in this small_tree version.");
}

float  const & small_tree::dphi_neutralinos() const{
  throw std::logic_error("dphi_neutralinos does not exist in this small_tree version.");
}

float  const & small_tree::dphi_wlep() const{
  throw std::logic_error("dphi_wlep does not exist in this small_tree version.");
}

float  const & small_tree::dphi_wlep_reliso() const{
  throw std::logic_error("dphi_wlep_reliso does not exist in this small_tree version.");
}

float  const & small_tree::eff_trig() const{
  throw std::logic_error("eff_trig does not exist in this small_tree version.");
}

float  const & small_tree::gen_ht() const{
  throw std::logic_error("gen_ht does not exist in this small_tree version.");
}

float  const & small_tree::gen_met() const{
  throw std::logic_error("gen_met does not exist in this small_tree version.");
}

float  const & small_tree::gen_met_phi() const{
  throw std::logic_error("gen_met_phi does not exist in this small_tree version.");
}

float  const & small_tree::gen_mj() const{
  throw std::logic_error("gen_mj does not exist in this small_tree version.");
}

float  const & small_tree::ht40() const{
  throw std::logic_error("ht40 does not exist in this small_tree version.");
}

float  const & small_tree::ht_isr() const{
  throw std::logic_error("ht_isr does not exist in this small_tree version.");
}

float  const & small_tree::ht_isr_me() const{
  throw std::logic_error("ht_isr_me does not exist in this small_tree version.");
}

float  const & small_tree::ht_isr_nonme() const{
  throw std::logic_error("ht_isr_nonme does not exist in this small_tree version.");
}

float  const & small_tree::ht_isr_tru() const{
  throw std::logic_error("ht_isr_tru does not exist in this small_tree version.");
}

float  const & small_tree::ht_nonb() const{
  throw std::logic_error("ht_nonb does not exist in this small_tree version.");
}

float  const & small_tree::ht_reliso() const{
  throw std::logic_error("ht_reliso does not exist in this small_tree version.");
}

float  const & small_tree::ht_sub() const{
  throw std::logic_error("ht_sub does not exist in this small_tree version.");
}

float  const & small_tree::lep_eta() const{
  throw std::logic_error("lep_eta does not exist in this small_tree version.");
}

float  const & small_tree::lep_eta_reliso() const{
  throw std::logic_error("lep_eta_reliso does not exist in this small_tree version.");
}

float  const & small_tree::lep_phi() const{
  throw std::logic_error("lep_phi does not exist in this small_tree version.");
}

float  const & small_tree::lep_phi_reliso() const{
  throw std::logic_error("lep_phi_reliso does not exist in this small_tree version.");
}

float  const & small_tree::lep_pt() const{
  throw std::logic_error("lep_pt does not exist in this small_tree version.");
}

float  const & small_tree::lep_pt_reliso() const{
  throw std::logic_error("lep_pt_reliso does not exist in this small_tree version.");
}

float  const & small_tree::max_dphi_bb() const{
  throw std::logic_error("max_dphi_bb does not exist in this small_tree version.");
}

float  const & small_tree::max_dphi_blep() const{
  throw std::logic_error("max_dphi_blep does not exist in this small_tree version.");
}

float  const & small_tree::max_dphi_bmet() const{
  throw std::logic_error("max_dphi_bmet does not exist in this small_tree version.");
}

float  const & small_tree::max_dr_bb() const{
  throw std::logic_error("max_dr_bb does not exist in this small_tree version.");
}

float  const & small_tree::max_dr_blep() const{
  throw std::logic_error("max_dr_blep does not exist in this small_tree version.");
}

float  const & small_tree::max_m_bb() const{
  throw std::logic_error("max_m_bb does not exist in this small_tree version.");
}

float  const & small_tree::max_m_blep() const{
  throw std::logic_error("max_m_blep does not exist in this small_tree version.");
}

float  const & small_tree::max_mt_bmet() const{
  throw std::logic_error("max_mt_bmet does not exist in this small_tree version.");
}

float  const & small_tree::max_pt_bb() const{
  throw std::logic_error("max_pt_bb does not exist in this small_tree version.");
}

float  const & small_tree::max_pt_blep() const{
  throw std::logic_error("max_pt_blep does not exist in this small_tree version.");
}

float  const & small_tree::max_pt_bmet() const{
  throw std::logic_error("max_pt_bmet does not exist in this small_tree version.");
}

float  const & small_tree::mht_sub() const{
  throw std::logic_error("mht_sub does not exist in this small_tree version.");
}

float  const & small_tree::min_dphi_bb() const{
  throw std::logic_error("min_dphi_bb does not exist in this small_tree version.");
}

float  const & small_tree::min_dphi_blep() const{
  throw std::logic_error("min_dphi_blep does not exist in this small_tree version.");
}

float  const & small_tree::min_dphi_bmet() const{
  throw std::logic_error("min_dphi_bmet does not exist in this small_tree version.");
}

float  const & small_tree::min_dr_bb() const{
  throw std::logic_error("min_dr_bb does not exist in this small_tree version.");
}

float  const & small_tree::min_dr_blep() const{
  throw std::logic_error("min_dr_blep does not exist in this small_tree version.");
}

float  const & small_tree::min_m_bb() const{
  throw std::logic_error("min_m_bb does not exist in this small_tree version.");
}

float  const & small_tree::min_m_blep() const{
  throw std::logic_error("min_m_blep does not exist in this small_tree version.");
}

float  const & small_tree::min_mt_bmet() const{
  throw std::logic_error("min_mt_bmet does not exist in this small_tree version.");
}

float  const & small_tree::min_mt_bmet_with_w_mass() const{
  throw std::logic_error("min_mt_bmet_with_w_mass does not exist in this small_tree version.");
}

float  const & small_tree::min_pt_bb() const{
  throw std::logic_error("min_pt_bb does not exist in this small_tree version.");
}

float  const & small_tree::min_pt_blep() const{
  throw std::logic_error("min_pt_blep does not exist in this small_tree version.");
}

float  const & small_tree::min_pt_bmet() const{
  throw std::logic_error("min_pt_bmet does not exist in this small_tree version.");
}

float  const & small_tree::mindphin_metjet() const{
  throw std::logic_error("mindphin_metjet does not exist in this small_tree version.");
}

float  const & small_tree::mj15() const{
  throw std::logic_error("mj15 does not exist in this small_tree version.");
}

float  const & small_tree::mj_sub() const{
  throw std::logic_error("mj_sub does not exist in this small_tree version.");
}

float  const & small_tree::mt_reliso() const{
  throw std::logic_error("mt_reliso does not exist in this small_tree version.");
}

float  const & small_tree::st() const{
  throw std::logic_error("st does not exist in this small_tree version.");
}

float  const & small_tree::st_reliso() const{
  throw std::logic_error("st_reliso does not exist in this small_tree version.");
}

float  const & small_tree::tru_gluglu_dphi() const{
  throw std::logic_error("tru_gluglu_dphi does not exist in this small_tree version.");
}

float  const & small_tree::tru_gluglu_m() const{
  throw std::logic_error("tru_gluglu_m does not exist in this small_tree version.");
}

float  const & small_tree::tru_gluglu_pt() const{
  throw std::logic_error("tru_gluglu_pt does not exist in this small_tree version.");
}

float  const & small_tree::tru_gluglu_ptdiff() const{
  throw std::logic_error("tru_gluglu_ptdiff does not exist in this small_tree version.");
}

float  const & small_tree::tru_sphericity() const{
  throw std::logic_error("tru_sphericity does not exist in this small_tree version.");
}

float  const & small_tree::tru_tt_dphi() const{
  throw std::logic_error("tru_tt_dphi does not exist in this small_tree version.");
}

float  const & small_tree::tru_tt_m() const{
  throw std::logic_error("tru_tt_m does not exist in this small_tree version.");
}

float  const & small_tree::tru_tt_pt() const{
  throw std::logic_error("tru_tt_pt does not exist in this small_tree version.");
}

float  const & small_tree::tru_tt_ptdiff() const{
  throw std::logic_error("tru_tt_ptdiff does not exist in this small_tree version.");
}

float  const & small_tree::trutop1_phi() const{
  throw std::logic_error("trutop1_phi does not exist in this small_tree version.");
}

float  const & small_tree::trutop1_pt() const{
  throw std::logic_error("trutop1_pt does not exist in this small_tree version.");
}

float  const & small_tree::trutop2_phi() const{
  throw std::logic_error("trutop2_phi does not exist in this small_tree version.");
}

float  const & small_tree::trutop2_pt() const{
  throw std::logic_error("trutop2_pt does not exist in this small_tree version.");
}

float  const & small_tree::w_pu_rpv() const{
  throw std::logic_error("w_pu_rpv does not exist in this small_tree version.");
}

int  const & small_tree::lep_charge() const{
  throw std::logic_error("lep_charge does not exist in this small_tree version.");
}

int  const & small_tree::lep_charge_reliso() const{
  throw std::logic_error("lep_charge_reliso does not exist in this small_tree version.");
}

int  const & small_tree::n_isr_me() const{
  throw std::logic_error("n_isr_me does not exist in this small_tree version.");
}

int  const & small_tree::n_isr_nonme() const{
  throw std::logic_error("n_isr_nonme does not exist in this small_tree version.");
}

int  const & small_tree::nbadjets() const{
  throw std::logic_error("nbadjets does not exist in this small_tree version.");
}

int  const & small_tree::nbl40() const{
  throw std::logic_error("nbl40 does not exist in this small_tree version.");
}

int  const & small_tree::nbl_sub() const{
  throw std::logic_error("nbl_sub does not exist in this small_tree version.");
}

int  const & small_tree::nbm40() const{
  throw std::logic_error("nbm40 does not exist in this small_tree version.");
}

int  const & small_tree::nbm_sub() const{
  throw std::logic_error("nbm_sub does not exist in this small_tree version.");
}

int  const & small_tree::nbt40() const{
  throw std::logic_error("nbt40 does not exist in this small_tree version.");
}

int  const & small_tree::nbt_sub() const{
  throw std::logic_error("nbt_sub does not exist in this small_tree version.");
}

int  const & small_tree::nels_reliso() const{
  throw std::logic_error("nels_reliso does not exist in this small_tree version.");
}

int  const & small_tree::nfjets15() const{
  throw std::logic_error("nfjets15 does not exist in this small_tree version.");
}

int  const & small_tree::nfsubjets() const{
  throw std::logic_error("nfsubjets does not exist in this small_tree version.");
}

int  const & small_tree::ngenfjets() const{
  throw std::logic_error("ngenfjets does not exist in this small_tree version.");
}

int  const & small_tree::ngenjets() const{
  throw std::logic_error("ngenjets does not exist in this small_tree version.");
}

int  const & small_tree::njets40() const{
  throw std::logic_error("njets40 does not exist in this small_tree version.");
}

int  const & small_tree::nleps_reliso() const{
  throw std::logic_error("nleps_reliso does not exist in this small_tree version.");
}

int  const & small_tree::nmus_reliso() const{
  throw std::logic_error("nmus_reliso does not exist in this small_tree version.");
}

int  const & small_tree::nsubjets() const{
  throw std::logic_error("nsubjets does not exist in this small_tree version.");
}

int  const & small_tree::ntks() const{
  throw std::logic_error("ntks does not exist in this small_tree version.");
}

int  const & small_tree::ntks_chg() const{
  throw std::logic_error("ntks_chg does not exist in this small_tree version.");
}

int  const & small_tree::ntks_chg_mini() const{
  throw std::logic_error("ntks_chg_mini does not exist in this small_tree version.");
}

int  const & small_tree::ntks_chg_reliso() const{
  throw std::logic_error("ntks_chg_reliso does not exist in this small_tree version.");
}

int  const & small_tree::ntrumeisr() const{
  throw std::logic_error("ntrumeisr does not exist in this small_tree version.");
}

int  const & small_tree::nvels_reliso() const{
  throw std::logic_error("nvels_reliso does not exist in this small_tree version.");
}

int  const & small_tree::nvmus_reliso() const{
  throw std::logic_error("nvmus_reliso does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::badjets_islep() const{
  throw std::logic_error("badjets_islep does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::els_tru_tm() const{
  throw std::logic_error("els_tru_tm does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::mus_tru_tm() const{
  throw std::logic_error("mus_tru_tm does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_from_tau() const{
  throw std::logic_error("tks_from_tau does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_from_tauhad() const{
  throw std::logic_error("tks_from_tauhad does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_from_taulep() const{
  throw std::logic_error("tks_from_taulep does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_from_w() const{
  throw std::logic_error("tks_from_w does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_is_primary() const{
  throw std::logic_error("tks_is_primary does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_is_primary_reliso() const{
  throw std::logic_error("tks_is_primary_reliso does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::tks_is_sig_lep() const{
  throw std::logic_error("tks_is_sig_lep does not exist in this small_tree version.");
}

std::vector<bool>  const & small_tree::trig() const{
  throw std::logic_error("trig does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::badjets_eta() const{
  throw std::logic_error("badjets_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::badjets_id() const{
  throw std::logic_error("badjets_id does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::badjets_m() const{
  throw std::logic_error("badjets_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::badjets_phi() const{
  throw std::logic_error("badjets_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::badjets_pt() const{
  throw std::logic_error("badjets_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::dr_bb() const{
  throw std::logic_error("dr_bb does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_miniso_10() const{
  throw std::logic_error("els_miniso_10 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_miniso_10_ch() const{
  throw std::logic_error("els_miniso_10_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_miniso_tr10() const{
  throw std::logic_error("els_miniso_tr10 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_miniso_tr10_ch() const{
  throw std::logic_error("els_miniso_tr10_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_mt() const{
  throw std::logic_error("els_mt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso() const{
  throw std::logic_error("els_reliso does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso_r01() const{
  throw std::logic_error("els_reliso_r01 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso_r015() const{
  throw std::logic_error("els_reliso_r015 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso_r02() const{
  throw std::logic_error("els_reliso_r02 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso_r03() const{
  throw std::logic_error("els_reliso_r03 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_reliso_r04() const{
  throw std::logic_error("els_reliso_r04 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::els_tru_dr() const{
  throw std::logic_error("els_tru_dr does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_eta() const{
  throw std::logic_error("fjets15_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_m() const{
  throw std::logic_error("fjets15_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_phi() const{
  throw std::logic_error("fjets15_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_poscsv() const{
  throw std::logic_error("fjets15_poscsv does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_pt() const{
  throw std::logic_error("fjets15_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fjets15_sumcsv() const{
  throw std::logic_error("fjets15_sumcsv does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_eta() const{
  throw std::logic_error("fsubjets_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_m() const{
  throw std::logic_error("fsubjets_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_phi() const{
  throw std::logic_error("fsubjets_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_poscsv() const{
  throw std::logic_error("fsubjets_poscsv does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_pt() const{
  throw std::logic_error("fsubjets_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::fsubjets_sumcsv() const{
  throw std::logic_error("fsubjets_sumcsv does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genfjets_eta() const{
  throw std::logic_error("genfjets_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genfjets_m() const{
  throw std::logic_error("genfjets_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genfjets_phi() const{
  throw std::logic_error("genfjets_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genfjets_pt() const{
  throw std::logic_error("genfjets_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genjets_eta() const{
  throw std::logic_error("genjets_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genjets_m() const{
  throw std::logic_error("genjets_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genjets_phi() const{
  throw std::logic_error("genjets_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::genjets_pt() const{
  throw std::logic_error("genjets_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::glu_proj_frac() const{
  throw std::logic_error("glu_proj_frac does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::jets_gen_pt() const{
  throw std::logic_error("jets_gen_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::jets_id() const{
  throw std::logic_error("jets_id does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::jets_parton_pt() const{
  throw std::logic_error("jets_parton_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::jets_pt_from_mini() const{
  throw std::logic_error("jets_pt_from_mini does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::jets_pt_res() const{
  throw std::logic_error("jets_pt_res does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mc_eta() const{
  throw std::logic_error("mc_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mc_phi() const{
  throw std::logic_error("mc_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mc_pt() const{
  throw std::logic_error("mc_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_miniso_10() const{
  throw std::logic_error("mus_miniso_10 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_miniso_10_ch() const{
  throw std::logic_error("mus_miniso_10_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_miniso_tr10() const{
  throw std::logic_error("mus_miniso_tr10 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_miniso_tr10_ch() const{
  throw std::logic_error("mus_miniso_tr10_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_mt() const{
  throw std::logic_error("mus_mt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso() const{
  throw std::logic_error("mus_reliso does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso_r01() const{
  throw std::logic_error("mus_reliso_r01 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso_r015() const{
  throw std::logic_error("mus_reliso_r015 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso_r02() const{
  throw std::logic_error("mus_reliso_r02 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso_r03() const{
  throw std::logic_error("mus_reliso_r03 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_reliso_r04() const{
  throw std::logic_error("mus_reliso_r04 does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::mus_tru_dr() const{
  throw std::logic_error("mus_tru_dr does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_csv() const{
  throw std::logic_error("subjets_csv does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_eta() const{
  throw std::logic_error("subjets_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_id() const{
  throw std::logic_error("subjets_id does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_m() const{
  throw std::logic_error("subjets_m does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_mindr() const{
  throw std::logic_error("subjets_mindr does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_phi() const{
  throw std::logic_error("subjets_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_pt() const{
  throw std::logic_error("subjets_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_subeta() const{
  throw std::logic_error("subjets_subeta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_subm() const{
  throw std::logic_error("subjets_subm does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_subphi() const{
  throw std::logic_error("subjets_subphi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::subjets_subpt() const{
  throw std::logic_error("subjets_subpt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::sys_bctag() const{
  throw std::logic_error("sys_bctag does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_eta() const{
  throw std::logic_error("tks_eta does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_mini_ch() const{
  throw std::logic_error("tks_mini_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_mini_ne() const{
  throw std::logic_error("tks_mini_ne does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_mt() const{
  throw std::logic_error("tks_mt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_phi() const{
  throw std::logic_error("tks_phi does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_pt() const{
  throw std::logic_error("tks_pt does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r02_ch() const{
  throw std::logic_error("tks_r02_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r02_ne() const{
  throw std::logic_error("tks_r02_ne does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r03_ch() const{
  throw std::logic_error("tks_r03_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r03_ne() const{
  throw std::logic_error("tks_r03_ne does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r04_ch() const{
  throw std::logic_error("tks_r04_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r04_ne() const{
  throw std::logic_error("tks_r04_ne does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r05_ch() const{
  throw std::logic_error("tks_r05_ch does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_r05_ne() const{
  throw std::logic_error("tks_r05_ne does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_tru_dp() const{
  throw std::logic_error("tks_tru_dp does not exist in this small_tree version.");
}

std::vector<float>  const & small_tree::tks_tru_dr() const{
  throw std::logic_error("tks_tru_dr does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::els_tru_id() const{
  throw std::logic_error("els_tru_id does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::els_tru_momid() const{
  throw std::logic_error("els_tru_momid does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::fjets15_btags() const{
  throw std::logic_error("fjets15_btags does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::fjets15_nconst() const{
  throw std::logic_error("fjets15_nconst does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::fsubjets_btags() const{
  throw std::logic_error("fsubjets_btags does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::fsubjets_nconst() const{
  throw std::logic_error("fsubjets_nconst does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::genfjets_nconst() const{
  throw std::logic_error("genfjets_nconst does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::genjets_genfjet_index() const{
  throw std::logic_error("genjets_genfjet_index does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::genjets_isr_code() const{
  throw std::logic_error("genjets_isr_code does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::jets_fjet15_index() const{
  throw std::logic_error("jets_fjet15_index does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::jets_isr_code() const{
  throw std::logic_error("jets_isr_code does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::mc_id() const{
  throw std::logic_error("mc_id does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::mc_status() const{
  throw std::logic_error("mc_status does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::mus_tru_id() const{
  throw std::logic_error("mus_tru_id does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::mus_tru_momid() const{
  throw std::logic_error("mus_tru_momid does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::subjets_fsubjet_index() const{
  throw std::logic_error("subjets_fsubjet_index does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::subjets_nsub() const{
  throw std::logic_error("subjets_nsub does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::tks_charge() const{
  throw std::logic_error("tks_charge does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::tks_from_pv() const{
  throw std::logic_error("tks_from_pv does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::tks_id() const{
  throw std::logic_error("tks_id does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::tks_num_prongs() const{
  throw std::logic_error("tks_num_prongs does not exist in this small_tree version.");
}

std::vector<int>  const & small_tree::tks_tru_id() const{
  throw std::logic_error("tks_tru_id does not exist in this small_tree version.");
}

std::vector<size_t>  const & small_tree::mc_mom() const{
  throw std::logic_error("mc_mom does not exist in this small_tree version.");
}

unsigned  const & small_tree::mc_type() const{
  throw std::logic_error("mc_type does not exist in this small_tree version.");
}

bool  & small_tree::pass(){
  throw std::logic_error("pass does not exist in this small_tree version.");
}

float  & small_tree::dphi_neutralinos(){
  throw std::logic_error("dphi_neutralinos does not exist in this small_tree version.");
}

float  & small_tree::dphi_wlep(){
  throw std::logic_error("dphi_wlep does not exist in this small_tree version.");
}

float  & small_tree::dphi_wlep_reliso(){
  throw std::logic_error("dphi_wlep_reliso does not exist in this small_tree version.");
}

float  & small_tree::eff_trig(){
  throw std::logic_error("eff_trig does not exist in this small_tree version.");
}

float  & small_tree::gen_ht(){
  throw std::logic_error("gen_ht does not exist in this small_tree version.");
}

float  & small_tree::gen_met(){
  throw std::logic_error("gen_met does not exist in this small_tree version.");
}

float  & small_tree::gen_met_phi(){
  throw std::logic_error("gen_met_phi does not exist in this small_tree version.");
}

float  & small_tree::gen_mj(){
  throw std::logic_error("gen_mj does not exist in this small_tree version.");
}

float  & small_tree::ht40(){
  throw std::logic_error("ht40 does not exist in this small_tree version.");
}

float  & small_tree::ht_isr(){
  throw std::logic_error("ht_isr does not exist in this small_tree version.");
}

float  & small_tree::ht_isr_me(){
  throw std::logic_error("ht_isr_me does not exist in this small_tree version.");
}

float  & small_tree::ht_isr_nonme(){
  throw std::logic_error("ht_isr_nonme does not exist in this small_tree version.");
}

float  & small_tree::ht_isr_tru(){
  throw std::logic_error("ht_isr_tru does not exist in this small_tree version.");
}

float  & small_tree::ht_nonb(){
  throw std::logic_error("ht_nonb does not exist in this small_tree version.");
}

float  & small_tree::ht_reliso(){
  throw std::logic_error("ht_reliso does not exist in this small_tree version.");
}

float  & small_tree::ht_sub(){
  throw std::logic_error("ht_sub does not exist in this small_tree version.");
}

float  & small_tree::lep_eta(){
  throw std::logic_error("lep_eta does not exist in this small_tree version.");
}

float  & small_tree::lep_eta_reliso(){
  throw std::logic_error("lep_eta_reliso does not exist in this small_tree version.");
}

float  & small_tree::lep_phi(){
  throw std::logic_error("lep_phi does not exist in this small_tree version.");
}

float  & small_tree::lep_phi_reliso(){
  throw std::logic_error("lep_phi_reliso does not exist in this small_tree version.");
}

float  & small_tree::lep_pt(){
  throw std::logic_error("lep_pt does not exist in this small_tree version.");
}

float  & small_tree::lep_pt_reliso(){
  throw std::logic_error("lep_pt_reliso does not exist in this small_tree version.");
}

float  & small_tree::max_dphi_bb(){
  throw std::logic_error("max_dphi_bb does not exist in this small_tree version.");
}

float  & small_tree::max_dphi_blep(){
  throw std::logic_error("max_dphi_blep does not exist in this small_tree version.");
}

float  & small_tree::max_dphi_bmet(){
  throw std::logic_error("max_dphi_bmet does not exist in this small_tree version.");
}

float  & small_tree::max_dr_bb(){
  throw std::logic_error("max_dr_bb does not exist in this small_tree version.");
}

float  & small_tree::max_dr_blep(){
  throw std::logic_error("max_dr_blep does not exist in this small_tree version.");
}

float  & small_tree::max_m_bb(){
  throw std::logic_error("max_m_bb does not exist in this small_tree version.");
}

float  & small_tree::max_m_blep(){
  throw std::logic_error("max_m_blep does not exist in this small_tree version.");
}

float  & small_tree::max_mt_bmet(){
  throw std::logic_error("max_mt_bmet does not exist in this small_tree version.");
}

float  & small_tree::max_pt_bb(){
  throw std::logic_error("max_pt_bb does not exist in this small_tree version.");
}

float  & small_tree::max_pt_blep(){
  throw std::logic_error("max_pt_blep does not exist in this small_tree version.");
}

float  & small_tree::max_pt_bmet(){
  throw std::logic_error("max_pt_bmet does not exist in this small_tree version.");
}

float  & small_tree::mht_sub(){
  throw std::logic_error("mht_sub does not exist in this small_tree version.");
}

float  & small_tree::min_dphi_bb(){
  throw std::logic_error("min_dphi_bb does not exist in this small_tree version.");
}

float  & small_tree::min_dphi_blep(){
  throw std::logic_error("min_dphi_blep does not exist in this small_tree version.");
}

float  & small_tree::min_dphi_bmet(){
  throw std::logic_error("min_dphi_bmet does not exist in this small_tree version.");
}

float  & small_tree::min_dr_bb(){
  throw std::logic_error("min_dr_bb does not exist in this small_tree version.");
}

float  & small_tree::min_dr_blep(){
  throw std::logic_error("min_dr_blep does not exist in this small_tree version.");
}

float  & small_tree::min_m_bb(){
  throw std::logic_error("min_m_bb does not exist in this small_tree version.");
}

float  & small_tree::min_m_blep(){
  throw std::logic_error("min_m_blep does not exist in this small_tree version.");
}

float  & small_tree::min_mt_bmet(){
  throw std::logic_error("min_mt_bmet does not exist in this small_tree version.");
}

float  & small_tree::min_mt_bmet_with_w_mass(){
  throw std::logic_error("min_mt_bmet_with_w_mass does not exist in this small_tree version.");
}

float  & small_tree::min_pt_bb(){
  throw std::logic_error("min_pt_bb does not exist in this small_tree version.");
}

float  & small_tree::min_pt_blep(){
  throw std::logic_error("min_pt_blep does not exist in this small_tree version.");
}

float  & small_tree::min_pt_bmet(){
  throw std::logic_error("min_pt_bmet does not exist in this small_tree version.");
}

float  & small_tree::mindphin_metjet(){
  throw std::logic_error("mindphin_metjet does not exist in this small_tree version.");
}

float  & small_tree::mj15(){
  throw std::logic_error("mj15 does not exist in this small_tree version.");
}

float  & small_tree::mj_sub(){
  throw std::logic_error("mj_sub does not exist in this small_tree version.");
}

float  & small_tree::mt_reliso(){
  throw std::logic_error("mt_reliso does not exist in this small_tree version.");
}

float  & small_tree::st(){
  throw std::logic_error("st does not exist in this small_tree version.");
}

float  & small_tree::st_reliso(){
  throw std::logic_error("st_reliso does not exist in this small_tree version.");
}

float  & small_tree::tru_gluglu_dphi(){
  throw std::logic_error("tru_gluglu_dphi does not exist in this small_tree version.");
}

float  & small_tree::tru_gluglu_m(){
  throw std::logic_error("tru_gluglu_m does not exist in this small_tree version.");
}

float  & small_tree::tru_gluglu_pt(){
  throw std::logic_error("tru_gluglu_pt does not exist in this small_tree version.");
}

float  & small_tree::tru_gluglu_ptdiff(){
  throw std::logic_error("tru_gluglu_ptdiff does not exist in this small_tree version.");
}

float  & small_tree::tru_sphericity(){
  throw std::logic_error("tru_sphericity does not exist in this small_tree version.");
}

float  & small_tree::tru_tt_dphi(){
  throw std::logic_error("tru_tt_dphi does not exist in this small_tree version.");
}

float  & small_tree::tru_tt_m(){
  throw std::logic_error("tru_tt_m does not exist in this small_tree version.");
}

float  & small_tree::tru_tt_pt(){
  throw std::logic_error("tru_tt_pt does not exist in this small_tree version.");
}

float  & small_tree::tru_tt_ptdiff(){
  throw std::logic_error("tru_tt_ptdiff does not exist in this small_tree version.");
}

float  & small_tree::trutop1_phi(){
  throw std::logic_error("trutop1_phi does not exist in this small_tree version.");
}

float  & small_tree::trutop1_pt(){
  throw std::logic_error("trutop1_pt does not exist in this small_tree version.");
}

float  & small_tree::trutop2_phi(){
  throw std::logic_error("trutop2_phi does not exist in this small_tree version.");
}

float  & small_tree::trutop2_pt(){
  throw std::logic_error("trutop2_pt does not exist in this small_tree version.");
}

float  & small_tree::w_pu_rpv(){
  throw std::logic_error("w_pu_rpv does not exist in this small_tree version.");
}

int  & small_tree::lep_charge(){
  throw std::logic_error("lep_charge does not exist in this small_tree version.");
}

int  & small_tree::lep_charge_reliso(){
  throw std::logic_error("lep_charge_reliso does not exist in this small_tree version.");
}

int  & small_tree::n_isr_me(){
  throw std::logic_error("n_isr_me does not exist in this small_tree version.");
}

int  & small_tree::n_isr_nonme(){
  throw std::logic_error("n_isr_nonme does not exist in this small_tree version.");
}

int  & small_tree::nbadjets(){
  throw std::logic_error("nbadjets does not exist in this small_tree version.");
}

int  & small_tree::nbl40(){
  throw std::logic_error("nbl40 does not exist in this small_tree version.");
}

int  & small_tree::nbl_sub(){
  throw std::logic_error("nbl_sub does not exist in this small_tree version.");
}

int  & small_tree::nbm40(){
  throw std::logic_error("nbm40 does not exist in this small_tree version.");
}

int  & small_tree::nbm_sub(){
  throw std::logic_error("nbm_sub does not exist in this small_tree version.");
}

int  & small_tree::nbt40(){
  throw std::logic_error("nbt40 does not exist in this small_tree version.");
}

int  & small_tree::nbt_sub(){
  throw std::logic_error("nbt_sub does not exist in this small_tree version.");
}

int  & small_tree::nels_reliso(){
  throw std::logic_error("nels_reliso does not exist in this small_tree version.");
}

int  & small_tree::nfjets15(){
  throw std::logic_error("nfjets15 does not exist in this small_tree version.");
}

int  & small_tree::nfsubjets(){
  throw std::logic_error("nfsubjets does not exist in this small_tree version.");
}

int  & small_tree::ngenfjets(){
  throw std::logic_error("ngenfjets does not exist in this small_tree version.");
}

int  & small_tree::ngenjets(){
  throw std::logic_error("ngenjets does not exist in this small_tree version.");
}

int  & small_tree::njets40(){
  throw std::logic_error("njets40 does not exist in this small_tree version.");
}

int  & small_tree::nleps_reliso(){
  throw std::logic_error("nleps_reliso does not exist in this small_tree version.");
}

int  & small_tree::nmus_reliso(){
  throw std::logic_error("nmus_reliso does not exist in this small_tree version.");
}

int  & small_tree::nsubjets(){
  throw std::logic_error("nsubjets does not exist in this small_tree version.");
}

int  & small_tree::ntks(){
  throw std::logic_error("ntks does not exist in this small_tree version.");
}

int  & small_tree::ntks_chg(){
  throw std::logic_error("ntks_chg does not exist in this small_tree version.");
}

int  & small_tree::ntks_chg_mini(){
  throw std::logic_error("ntks_chg_mini does not exist in this small_tree version.");
}

int  & small_tree::ntks_chg_reliso(){
  throw std::logic_error("ntks_chg_reliso does not exist in this small_tree version.");
}

int  & small_tree::ntrumeisr(){
  throw std::logic_error("ntrumeisr does not exist in this small_tree version.");
}

int  & small_tree::nvels_reliso(){
  throw std::logic_error("nvels_reliso does not exist in this small_tree version.");
}

int  & small_tree::nvmus_reliso(){
  throw std::logic_error("nvmus_reliso does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::badjets_islep(){
  throw std::logic_error("badjets_islep does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::els_tru_tm(){
  throw std::logic_error("els_tru_tm does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::mus_tru_tm(){
  throw std::logic_error("mus_tru_tm does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_from_tau(){
  throw std::logic_error("tks_from_tau does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_from_tauhad(){
  throw std::logic_error("tks_from_tauhad does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_from_taulep(){
  throw std::logic_error("tks_from_taulep does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_from_w(){
  throw std::logic_error("tks_from_w does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_is_primary(){
  throw std::logic_error("tks_is_primary does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_is_primary_reliso(){
  throw std::logic_error("tks_is_primary_reliso does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::tks_is_sig_lep(){
  throw std::logic_error("tks_is_sig_lep does not exist in this small_tree version.");
}

std::vector<bool>  & small_tree::trig(){
  throw std::logic_error("trig does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::badjets_eta(){
  throw std::logic_error("badjets_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::badjets_id(){
  throw std::logic_error("badjets_id does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::badjets_m(){
  throw std::logic_error("badjets_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::badjets_phi(){
  throw std::logic_error("badjets_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::badjets_pt(){
  throw std::logic_error("badjets_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::dr_bb(){
  throw std::logic_error("dr_bb does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_miniso_10(){
  throw std::logic_error("els_miniso_10 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_miniso_10_ch(){
  throw std::logic_error("els_miniso_10_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_miniso_tr10(){
  throw std::logic_error("els_miniso_tr10 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_miniso_tr10_ch(){
  throw std::logic_error("els_miniso_tr10_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_mt(){
  throw std::logic_error("els_mt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso(){
  throw std::logic_error("els_reliso does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso_r01(){
  throw std::logic_error("els_reliso_r01 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso_r015(){
  throw std::logic_error("els_reliso_r015 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso_r02(){
  throw std::logic_error("els_reliso_r02 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso_r03(){
  throw std::logic_error("els_reliso_r03 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_reliso_r04(){
  throw std::logic_error("els_reliso_r04 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::els_tru_dr(){
  throw std::logic_error("els_tru_dr does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_eta(){
  throw std::logic_error("fjets15_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_m(){
  throw std::logic_error("fjets15_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_phi(){
  throw std::logic_error("fjets15_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_poscsv(){
  throw std::logic_error("fjets15_poscsv does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_pt(){
  throw std::logic_error("fjets15_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fjets15_sumcsv(){
  throw std::logic_error("fjets15_sumcsv does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_eta(){
  throw std::logic_error("fsubjets_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_m(){
  throw std::logic_error("fsubjets_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_phi(){
  throw std::logic_error("fsubjets_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_poscsv(){
  throw std::logic_error("fsubjets_poscsv does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_pt(){
  throw std::logic_error("fsubjets_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::fsubjets_sumcsv(){
  throw std::logic_error("fsubjets_sumcsv does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genfjets_eta(){
  throw std::logic_error("genfjets_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genfjets_m(){
  throw std::logic_error("genfjets_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genfjets_phi(){
  throw std::logic_error("genfjets_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genfjets_pt(){
  throw std::logic_error("genfjets_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genjets_eta(){
  throw std::logic_error("genjets_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genjets_m(){
  throw std::logic_error("genjets_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genjets_phi(){
  throw std::logic_error("genjets_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::genjets_pt(){
  throw std::logic_error("genjets_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::glu_proj_frac(){
  throw std::logic_error("glu_proj_frac does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::jets_gen_pt(){
  throw std::logic_error("jets_gen_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::jets_id(){
  throw std::logic_error("jets_id does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::jets_parton_pt(){
  throw std::logic_error("jets_parton_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::jets_pt_from_mini(){
  throw std::logic_error("jets_pt_from_mini does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::jets_pt_res(){
  throw std::logic_error("jets_pt_res does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mc_eta(){
  throw std::logic_error("mc_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mc_phi(){
  throw std::logic_error("mc_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mc_pt(){
  throw std::logic_error("mc_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_miniso_10(){
  throw std::logic_error("mus_miniso_10 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_miniso_10_ch(){
  throw std::logic_error("mus_miniso_10_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_miniso_tr10(){
  throw std::logic_error("mus_miniso_tr10 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_miniso_tr10_ch(){
  throw std::logic_error("mus_miniso_tr10_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_mt(){
  throw std::logic_error("mus_mt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso(){
  throw std::logic_error("mus_reliso does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso_r01(){
  throw std::logic_error("mus_reliso_r01 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso_r015(){
  throw std::logic_error("mus_reliso_r015 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso_r02(){
  throw std::logic_error("mus_reliso_r02 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso_r03(){
  throw std::logic_error("mus_reliso_r03 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_reliso_r04(){
  throw std::logic_error("mus_reliso_r04 does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::mus_tru_dr(){
  throw std::logic_error("mus_tru_dr does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_csv(){
  throw std::logic_error("subjets_csv does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_eta(){
  throw std::logic_error("subjets_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_id(){
  throw std::logic_error("subjets_id does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_m(){
  throw std::logic_error("subjets_m does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_mindr(){
  throw std::logic_error("subjets_mindr does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_phi(){
  throw std::logic_error("subjets_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_pt(){
  throw std::logic_error("subjets_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_subeta(){
  throw std::logic_error("subjets_subeta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_subm(){
  throw std::logic_error("subjets_subm does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_subphi(){
  throw std::logic_error("subjets_subphi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::subjets_subpt(){
  throw std::logic_error("subjets_subpt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::sys_bctag(){
  throw std::logic_error("sys_bctag does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_eta(){
  throw std::logic_error("tks_eta does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_mini_ch(){
  throw std::logic_error("tks_mini_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_mini_ne(){
  throw std::logic_error("tks_mini_ne does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_mt(){
  throw std::logic_error("tks_mt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_phi(){
  throw std::logic_error("tks_phi does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_pt(){
  throw std::logic_error("tks_pt does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r02_ch(){
  throw std::logic_error("tks_r02_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r02_ne(){
  throw std::logic_error("tks_r02_ne does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r03_ch(){
  throw std::logic_error("tks_r03_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r03_ne(){
  throw std::logic_error("tks_r03_ne does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r04_ch(){
  throw std::logic_error("tks_r04_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r04_ne(){
  throw std::logic_error("tks_r04_ne does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r05_ch(){
  throw std::logic_error("tks_r05_ch does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_r05_ne(){
  throw std::logic_error("tks_r05_ne does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_tru_dp(){
  throw std::logic_error("tks_tru_dp does not exist in this small_tree version.");
}

std::vector<float>  & small_tree::tks_tru_dr(){
  throw std::logic_error("tks_tru_dr does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::els_tru_id(){
  throw std::logic_error("els_tru_id does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::els_tru_momid(){
  throw std::logic_error("els_tru_momid does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::fjets15_btags(){
  throw std::logic_error("fjets15_btags does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::fjets15_nconst(){
  throw std::logic_error("fjets15_nconst does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::fsubjets_btags(){
  throw std::logic_error("fsubjets_btags does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::fsubjets_nconst(){
  throw std::logic_error("fsubjets_nconst does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::genfjets_nconst(){
  throw std::logic_error("genfjets_nconst does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::genjets_genfjet_index(){
  throw std::logic_error("genjets_genfjet_index does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::genjets_isr_code(){
  throw std::logic_error("genjets_isr_code does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::jets_fjet15_index(){
  throw std::logic_error("jets_fjet15_index does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::jets_isr_code(){
  throw std::logic_error("jets_isr_code does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::mc_id(){
  throw std::logic_error("mc_id does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::mc_status(){
  throw std::logic_error("mc_status does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::mus_tru_id(){
  throw std::logic_error("mus_tru_id does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::mus_tru_momid(){
  throw std::logic_error("mus_tru_momid does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::subjets_fsubjet_index(){
  throw std::logic_error("subjets_fsubjet_index does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::subjets_nsub(){
  throw std::logic_error("subjets_nsub does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::tks_charge(){
  throw std::logic_error("tks_charge does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::tks_from_pv(){
  throw std::logic_error("tks_from_pv does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::tks_id(){
  throw std::logic_error("tks_id does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::tks_num_prongs(){
  throw std::logic_error("tks_num_prongs does not exist in this small_tree version.");
}

std::vector<int>  & small_tree::tks_tru_id(){
  throw std::logic_error("tks_tru_id does not exist in this small_tree version.");
}

std::vector<size_t>  & small_tree::mc_mom(){
  throw std::logic_error("mc_mom does not exist in this small_tree version.");
}

unsigned  & small_tree::mc_type(){
  throw std::logic_error("mc_type does not exist in this small_tree version.");
}

#include "small_tree_full.hpp"
#include "small_tree_quick.hpp"
#include "small_tree_rpv.hpp"
small_tree* NewTree(const std::type_info &type){

  if(type == typeid(small_tree)) return new small_tree;
  else if(type == typeid(small_tree_full)) return static_cast<small_tree*>(new small_tree_full);
  else if(type == typeid(small_tree_quick)) return static_cast<small_tree*>(new small_tree_quick);
  else if(type == typeid(small_tree_rpv)) return static_cast<small_tree*>(new small_tree_rpv);
  else return new small_tree;
}

