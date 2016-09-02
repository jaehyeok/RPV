// small_tree_quick: quick version of small_tree to handle reduce tree ntuples
//File generated with generate_small_tree.exe

#include "small_tree.hpp"

#include "small_tree_quick.hpp"

#include <stdexcept>
#include <string>
#include <vector>

#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"

using namespace std;

small_tree_quick::small_tree_quick():
  small_tree(),
  dphi_wlep_(0),
  b_dphi_wlep_(tree_.Branch("dphi_wlep", &dphi_wlep_)),
  c_dphi_wlep_(false),
  dphi_wlep_reliso_(0),
  b_dphi_wlep_reliso_(tree_.Branch("dphi_wlep_reliso", &dphi_wlep_reliso_)),
  c_dphi_wlep_reliso_(false),
  ht40_(0),
  b_ht40_(tree_.Branch("ht40", &ht40_)),
  c_ht40_(false),
  ht_reliso_(0),
  b_ht_reliso_(tree_.Branch("ht_reliso", &ht_reliso_)),
  c_ht_reliso_(false),
  lep_eta_(0),
  b_lep_eta_(tree_.Branch("lep_eta", &lep_eta_)),
  c_lep_eta_(false),
  lep_eta_reliso_(0),
  b_lep_eta_reliso_(tree_.Branch("lep_eta_reliso", &lep_eta_reliso_)),
  c_lep_eta_reliso_(false),
  lep_phi_(0),
  b_lep_phi_(tree_.Branch("lep_phi", &lep_phi_)),
  c_lep_phi_(false),
  lep_phi_reliso_(0),
  b_lep_phi_reliso_(tree_.Branch("lep_phi_reliso", &lep_phi_reliso_)),
  c_lep_phi_reliso_(false),
  lep_pt_(0),
  b_lep_pt_(tree_.Branch("lep_pt", &lep_pt_)),
  c_lep_pt_(false),
  lep_pt_reliso_(0),
  b_lep_pt_reliso_(tree_.Branch("lep_pt_reliso", &lep_pt_reliso_)),
  c_lep_pt_reliso_(false),
  mindphin_metjet_(0),
  b_mindphin_metjet_(tree_.Branch("mindphin_metjet", &mindphin_metjet_)),
  c_mindphin_metjet_(false),
  mt_reliso_(0),
  b_mt_reliso_(tree_.Branch("mt_reliso", &mt_reliso_)),
  c_mt_reliso_(false),
  st_(0),
  b_st_(tree_.Branch("st", &st_)),
  c_st_(false),
  st_reliso_(0),
  b_st_reliso_(tree_.Branch("st_reliso", &st_reliso_)),
  c_st_reliso_(false),
  trutop1_phi_(0),
  b_trutop1_phi_(tree_.Branch("trutop1_phi", &trutop1_phi_)),
  c_trutop1_phi_(false),
  trutop1_pt_(0),
  b_trutop1_pt_(tree_.Branch("trutop1_pt", &trutop1_pt_)),
  c_trutop1_pt_(false),
  trutop2_phi_(0),
  b_trutop2_phi_(tree_.Branch("trutop2_phi", &trutop2_phi_)),
  c_trutop2_phi_(false),
  trutop2_pt_(0),
  b_trutop2_pt_(tree_.Branch("trutop2_pt", &trutop2_pt_)),
  c_trutop2_pt_(false),
  lep_charge_(0),
  b_lep_charge_(tree_.Branch("lep_charge", &lep_charge_)),
  c_lep_charge_(false),
  lep_charge_reliso_(0),
  b_lep_charge_reliso_(tree_.Branch("lep_charge_reliso", &lep_charge_reliso_)),
  c_lep_charge_reliso_(false),
  nbl40_(0),
  b_nbl40_(tree_.Branch("nbl40", &nbl40_)),
  c_nbl40_(false),
  nbm40_(0),
  b_nbm40_(tree_.Branch("nbm40", &nbm40_)),
  c_nbm40_(false),
  nbt40_(0),
  b_nbt40_(tree_.Branch("nbt40", &nbt40_)),
  c_nbt40_(false),
  nels_reliso_(0),
  b_nels_reliso_(tree_.Branch("nels_reliso", &nels_reliso_)),
  c_nels_reliso_(false),
  njets40_(0),
  b_njets40_(tree_.Branch("njets40", &njets40_)),
  c_njets40_(false),
  nleps_reliso_(0),
  b_nleps_reliso_(tree_.Branch("nleps_reliso", &nleps_reliso_)),
  c_nleps_reliso_(false),
  nmus_reliso_(0),
  b_nmus_reliso_(tree_.Branch("nmus_reliso", &nmus_reliso_)),
  c_nmus_reliso_(false),
  ntks_chg_(0),
  b_ntks_chg_(tree_.Branch("ntks_chg", &ntks_chg_)),
  c_ntks_chg_(false),
  ntks_chg_mini_(0),
  b_ntks_chg_mini_(tree_.Branch("ntks_chg_mini", &ntks_chg_mini_)),
  c_ntks_chg_mini_(false),
  ntrumeisr_(0),
  b_ntrumeisr_(tree_.Branch("ntrumeisr", &ntrumeisr_)),
  c_ntrumeisr_(false),
  nvels_reliso_(0),
  b_nvels_reliso_(tree_.Branch("nvels_reliso", &nvels_reliso_)),
  c_nvels_reliso_(false),
  nvmus_reliso_(0),
  b_nvmus_reliso_(tree_.Branch("nvmus_reliso", &nvmus_reliso_)),
  c_nvmus_reliso_(false),
  els_tru_tm_(0),
  p_els_tru_tm_(&els_tru_tm_),
  b_els_tru_tm_(tree_.Branch("els_tru_tm", &p_els_tru_tm_)),
  c_els_tru_tm_(false),
  mus_tru_tm_(0),
  p_mus_tru_tm_(&mus_tru_tm_),
  b_mus_tru_tm_(tree_.Branch("mus_tru_tm", &p_mus_tru_tm_)),
  c_mus_tru_tm_(false),
  els_miniso_tr10_(0),
  p_els_miniso_tr10_(&els_miniso_tr10_),
  b_els_miniso_tr10_(tree_.Branch("els_miniso_tr10", &p_els_miniso_tr10_)),
  c_els_miniso_tr10_(false),
  els_mt_(0),
  p_els_mt_(&els_mt_),
  b_els_mt_(tree_.Branch("els_mt", &p_els_mt_)),
  c_els_mt_(false),
  els_reliso_(0),
  p_els_reliso_(&els_reliso_),
  b_els_reliso_(tree_.Branch("els_reliso", &p_els_reliso_)),
  c_els_reliso_(false),
  els_tru_dr_(0),
  p_els_tru_dr_(&els_tru_dr_),
  b_els_tru_dr_(tree_.Branch("els_tru_dr", &p_els_tru_dr_)),
  c_els_tru_dr_(false),
  jets_id_(0),
  p_jets_id_(&jets_id_),
  b_jets_id_(tree_.Branch("jets_id", &p_jets_id_)),
  c_jets_id_(false),
  jets_pt_res_(0),
  p_jets_pt_res_(&jets_pt_res_),
  b_jets_pt_res_(tree_.Branch("jets_pt_res", &p_jets_pt_res_)),
  c_jets_pt_res_(false),
  mus_miniso_tr10_(0),
  p_mus_miniso_tr10_(&mus_miniso_tr10_),
  b_mus_miniso_tr10_(tree_.Branch("mus_miniso_tr10", &p_mus_miniso_tr10_)),
  c_mus_miniso_tr10_(false),
  mus_mt_(0),
  p_mus_mt_(&mus_mt_),
  b_mus_mt_(tree_.Branch("mus_mt", &p_mus_mt_)),
  c_mus_mt_(false),
  mus_reliso_(0),
  p_mus_reliso_(&mus_reliso_),
  b_mus_reliso_(tree_.Branch("mus_reliso", &p_mus_reliso_)),
  c_mus_reliso_(false),
  mus_tru_dr_(0),
  p_mus_tru_dr_(&mus_tru_dr_),
  b_mus_tru_dr_(tree_.Branch("mus_tru_dr", &p_mus_tru_dr_)),
  c_mus_tru_dr_(false),
  els_tru_id_(0),
  p_els_tru_id_(&els_tru_id_),
  b_els_tru_id_(tree_.Branch("els_tru_id", &p_els_tru_id_)),
  c_els_tru_id_(false),
  els_tru_momid_(0),
  p_els_tru_momid_(&els_tru_momid_),
  b_els_tru_momid_(tree_.Branch("els_tru_momid", &p_els_tru_momid_)),
  c_els_tru_momid_(false),
  mus_tru_id_(0),
  p_mus_tru_id_(&mus_tru_id_),
  b_mus_tru_id_(tree_.Branch("mus_tru_id", &p_mus_tru_id_)),
  c_mus_tru_id_(false),
  mus_tru_momid_(0),
  p_mus_tru_momid_(&mus_tru_momid_),
  b_mus_tru_momid_(tree_.Branch("mus_tru_momid", &p_mus_tru_momid_)),
  c_mus_tru_momid_(false){
}

small_tree_quick::small_tree_quick(const string &filename):
  small_tree(filename),
  dphi_wlep_(0),
  b_dphi_wlep_(NULL),
  c_dphi_wlep_(false),
  dphi_wlep_reliso_(0),
  b_dphi_wlep_reliso_(NULL),
  c_dphi_wlep_reliso_(false),
  ht40_(0),
  b_ht40_(NULL),
  c_ht40_(false),
  ht_reliso_(0),
  b_ht_reliso_(NULL),
  c_ht_reliso_(false),
  lep_eta_(0),
  b_lep_eta_(NULL),
  c_lep_eta_(false),
  lep_eta_reliso_(0),
  b_lep_eta_reliso_(NULL),
  c_lep_eta_reliso_(false),
  lep_phi_(0),
  b_lep_phi_(NULL),
  c_lep_phi_(false),
  lep_phi_reliso_(0),
  b_lep_phi_reliso_(NULL),
  c_lep_phi_reliso_(false),
  lep_pt_(0),
  b_lep_pt_(NULL),
  c_lep_pt_(false),
  lep_pt_reliso_(0),
  b_lep_pt_reliso_(NULL),
  c_lep_pt_reliso_(false),
  mindphin_metjet_(0),
  b_mindphin_metjet_(NULL),
  c_mindphin_metjet_(false),
  mt_reliso_(0),
  b_mt_reliso_(NULL),
  c_mt_reliso_(false),
  st_(0),
  b_st_(NULL),
  c_st_(false),
  st_reliso_(0),
  b_st_reliso_(NULL),
  c_st_reliso_(false),
  trutop1_phi_(0),
  b_trutop1_phi_(NULL),
  c_trutop1_phi_(false),
  trutop1_pt_(0),
  b_trutop1_pt_(NULL),
  c_trutop1_pt_(false),
  trutop2_phi_(0),
  b_trutop2_phi_(NULL),
  c_trutop2_phi_(false),
  trutop2_pt_(0),
  b_trutop2_pt_(NULL),
  c_trutop2_pt_(false),
  lep_charge_(0),
  b_lep_charge_(NULL),
  c_lep_charge_(false),
  lep_charge_reliso_(0),
  b_lep_charge_reliso_(NULL),
  c_lep_charge_reliso_(false),
  nbl40_(0),
  b_nbl40_(NULL),
  c_nbl40_(false),
  nbm40_(0),
  b_nbm40_(NULL),
  c_nbm40_(false),
  nbt40_(0),
  b_nbt40_(NULL),
  c_nbt40_(false),
  nels_reliso_(0),
  b_nels_reliso_(NULL),
  c_nels_reliso_(false),
  njets40_(0),
  b_njets40_(NULL),
  c_njets40_(false),
  nleps_reliso_(0),
  b_nleps_reliso_(NULL),
  c_nleps_reliso_(false),
  nmus_reliso_(0),
  b_nmus_reliso_(NULL),
  c_nmus_reliso_(false),
  ntks_chg_(0),
  b_ntks_chg_(NULL),
  c_ntks_chg_(false),
  ntks_chg_mini_(0),
  b_ntks_chg_mini_(NULL),
  c_ntks_chg_mini_(false),
  ntrumeisr_(0),
  b_ntrumeisr_(NULL),
  c_ntrumeisr_(false),
  nvels_reliso_(0),
  b_nvels_reliso_(NULL),
  c_nvels_reliso_(false),
  nvmus_reliso_(0),
  b_nvmus_reliso_(NULL),
  c_nvmus_reliso_(false),
  els_tru_tm_(0),
  p_els_tru_tm_(&els_tru_tm_),
  b_els_tru_tm_(NULL),
  c_els_tru_tm_(false),
  mus_tru_tm_(0),
  p_mus_tru_tm_(&mus_tru_tm_),
  b_mus_tru_tm_(NULL),
  c_mus_tru_tm_(false),
  els_miniso_tr10_(0),
  p_els_miniso_tr10_(&els_miniso_tr10_),
  b_els_miniso_tr10_(NULL),
  c_els_miniso_tr10_(false),
  els_mt_(0),
  p_els_mt_(&els_mt_),
  b_els_mt_(NULL),
  c_els_mt_(false),
  els_reliso_(0),
  p_els_reliso_(&els_reliso_),
  b_els_reliso_(NULL),
  c_els_reliso_(false),
  els_tru_dr_(0),
  p_els_tru_dr_(&els_tru_dr_),
  b_els_tru_dr_(NULL),
  c_els_tru_dr_(false),
  jets_id_(0),
  p_jets_id_(&jets_id_),
  b_jets_id_(NULL),
  c_jets_id_(false),
  jets_pt_res_(0),
  p_jets_pt_res_(&jets_pt_res_),
  b_jets_pt_res_(NULL),
  c_jets_pt_res_(false),
  mus_miniso_tr10_(0),
  p_mus_miniso_tr10_(&mus_miniso_tr10_),
  b_mus_miniso_tr10_(NULL),
  c_mus_miniso_tr10_(false),
  mus_mt_(0),
  p_mus_mt_(&mus_mt_),
  b_mus_mt_(NULL),
  c_mus_mt_(false),
  mus_reliso_(0),
  p_mus_reliso_(&mus_reliso_),
  b_mus_reliso_(NULL),
  c_mus_reliso_(false),
  mus_tru_dr_(0),
  p_mus_tru_dr_(&mus_tru_dr_),
  b_mus_tru_dr_(NULL),
  c_mus_tru_dr_(false),
  els_tru_id_(0),
  p_els_tru_id_(&els_tru_id_),
  b_els_tru_id_(NULL),
  c_els_tru_id_(false),
  els_tru_momid_(0),
  p_els_tru_momid_(&els_tru_momid_),
  b_els_tru_momid_(NULL),
  c_els_tru_momid_(false),
  mus_tru_id_(0),
  p_mus_tru_id_(&mus_tru_id_),
  b_mus_tru_id_(NULL),
  c_mus_tru_id_(false),
  mus_tru_momid_(0),
  p_mus_tru_momid_(&mus_tru_momid_),
  b_mus_tru_momid_(NULL),
  c_mus_tru_momid_(false){
  chain_.SetBranchAddress("dphi_wlep", &dphi_wlep_, &b_dphi_wlep_);
  chain_.SetBranchAddress("dphi_wlep_reliso", &dphi_wlep_reliso_, &b_dphi_wlep_reliso_);
  chain_.SetBranchAddress("ht40", &ht40_, &b_ht40_);
  chain_.SetBranchAddress("ht_reliso", &ht_reliso_, &b_ht_reliso_);
  chain_.SetBranchAddress("lep_eta", &lep_eta_, &b_lep_eta_);
  chain_.SetBranchAddress("lep_eta_reliso", &lep_eta_reliso_, &b_lep_eta_reliso_);
  chain_.SetBranchAddress("lep_phi", &lep_phi_, &b_lep_phi_);
  chain_.SetBranchAddress("lep_phi_reliso", &lep_phi_reliso_, &b_lep_phi_reliso_);
  chain_.SetBranchAddress("lep_pt", &lep_pt_, &b_lep_pt_);
  chain_.SetBranchAddress("lep_pt_reliso", &lep_pt_reliso_, &b_lep_pt_reliso_);
  chain_.SetBranchAddress("mindphin_metjet", &mindphin_metjet_, &b_mindphin_metjet_);
  chain_.SetBranchAddress("mt_reliso", &mt_reliso_, &b_mt_reliso_);
  chain_.SetBranchAddress("st", &st_, &b_st_);
  chain_.SetBranchAddress("st_reliso", &st_reliso_, &b_st_reliso_);
  chain_.SetBranchAddress("trutop1_phi", &trutop1_phi_, &b_trutop1_phi_);
  chain_.SetBranchAddress("trutop1_pt", &trutop1_pt_, &b_trutop1_pt_);
  chain_.SetBranchAddress("trutop2_phi", &trutop2_phi_, &b_trutop2_phi_);
  chain_.SetBranchAddress("trutop2_pt", &trutop2_pt_, &b_trutop2_pt_);
  chain_.SetBranchAddress("lep_charge", &lep_charge_, &b_lep_charge_);
  chain_.SetBranchAddress("lep_charge_reliso", &lep_charge_reliso_, &b_lep_charge_reliso_);
  chain_.SetBranchAddress("nbl40", &nbl40_, &b_nbl40_);
  chain_.SetBranchAddress("nbm40", &nbm40_, &b_nbm40_);
  chain_.SetBranchAddress("nbt40", &nbt40_, &b_nbt40_);
  chain_.SetBranchAddress("nels_reliso", &nels_reliso_, &b_nels_reliso_);
  chain_.SetBranchAddress("njets40", &njets40_, &b_njets40_);
  chain_.SetBranchAddress("nleps_reliso", &nleps_reliso_, &b_nleps_reliso_);
  chain_.SetBranchAddress("nmus_reliso", &nmus_reliso_, &b_nmus_reliso_);
  chain_.SetBranchAddress("ntks_chg", &ntks_chg_, &b_ntks_chg_);
  chain_.SetBranchAddress("ntks_chg_mini", &ntks_chg_mini_, &b_ntks_chg_mini_);
  chain_.SetBranchAddress("ntrumeisr", &ntrumeisr_, &b_ntrumeisr_);
  chain_.SetBranchAddress("nvels_reliso", &nvels_reliso_, &b_nvels_reliso_);
  chain_.SetBranchAddress("nvmus_reliso", &nvmus_reliso_, &b_nvmus_reliso_);
  chain_.SetBranchAddress("els_tru_tm", &p_els_tru_tm_, &b_els_tru_tm_);
  chain_.SetBranchAddress("mus_tru_tm", &p_mus_tru_tm_, &b_mus_tru_tm_);
  chain_.SetBranchAddress("els_miniso_tr10", &p_els_miniso_tr10_, &b_els_miniso_tr10_);
  chain_.SetBranchAddress("els_mt", &p_els_mt_, &b_els_mt_);
  chain_.SetBranchAddress("els_reliso", &p_els_reliso_, &b_els_reliso_);
  chain_.SetBranchAddress("els_tru_dr", &p_els_tru_dr_, &b_els_tru_dr_);
  chain_.SetBranchAddress("jets_id", &p_jets_id_, &b_jets_id_);
  chain_.SetBranchAddress("jets_pt_res", &p_jets_pt_res_, &b_jets_pt_res_);
  chain_.SetBranchAddress("mus_miniso_tr10", &p_mus_miniso_tr10_, &b_mus_miniso_tr10_);
  chain_.SetBranchAddress("mus_mt", &p_mus_mt_, &b_mus_mt_);
  chain_.SetBranchAddress("mus_reliso", &p_mus_reliso_, &b_mus_reliso_);
  chain_.SetBranchAddress("mus_tru_dr", &p_mus_tru_dr_, &b_mus_tru_dr_);
  chain_.SetBranchAddress("els_tru_id", &p_els_tru_id_, &b_els_tru_id_);
  chain_.SetBranchAddress("els_tru_momid", &p_els_tru_momid_, &b_els_tru_momid_);
  chain_.SetBranchAddress("mus_tru_id", &p_mus_tru_id_, &b_mus_tru_id_);
  chain_.SetBranchAddress("mus_tru_momid", &p_mus_tru_momid_, &b_mus_tru_momid_);
}

void small_tree_quick::Fill(){
  small_tree::Fill();
  //Resetting variables
  dphi_wlep_ = static_cast<float >(bad_val_);
  dphi_wlep_reliso_ = static_cast<float >(bad_val_);
  ht40_ = static_cast<float >(bad_val_);
  ht_reliso_ = static_cast<float >(bad_val_);
  lep_eta_ = static_cast<float >(bad_val_);
  lep_eta_reliso_ = static_cast<float >(bad_val_);
  lep_phi_ = static_cast<float >(bad_val_);
  lep_phi_reliso_ = static_cast<float >(bad_val_);
  lep_pt_ = static_cast<float >(bad_val_);
  lep_pt_reliso_ = static_cast<float >(bad_val_);
  mindphin_metjet_ = static_cast<float >(bad_val_);
  mt_reliso_ = static_cast<float >(bad_val_);
  st_ = static_cast<float >(bad_val_);
  st_reliso_ = static_cast<float >(bad_val_);
  trutop1_phi_ = static_cast<float >(bad_val_);
  trutop1_pt_ = static_cast<float >(bad_val_);
  trutop2_phi_ = static_cast<float >(bad_val_);
  trutop2_pt_ = static_cast<float >(bad_val_);
  lep_charge_ = static_cast<int >(bad_val_);
  lep_charge_reliso_ = static_cast<int >(bad_val_);
  nbl40_ = static_cast<int >(bad_val_);
  nbm40_ = static_cast<int >(bad_val_);
  nbt40_ = static_cast<int >(bad_val_);
  nels_reliso_ = static_cast<int >(bad_val_);
  njets40_ = static_cast<int >(bad_val_);
  nleps_reliso_ = static_cast<int >(bad_val_);
  nmus_reliso_ = static_cast<int >(bad_val_);
  ntks_chg_ = static_cast<int >(bad_val_);
  ntks_chg_mini_ = static_cast<int >(bad_val_);
  ntrumeisr_ = static_cast<int >(bad_val_);
  nvels_reliso_ = static_cast<int >(bad_val_);
  nvmus_reliso_ = static_cast<int >(bad_val_);
  els_tru_tm_.clear();
  mus_tru_tm_.clear();
  els_miniso_tr10_.clear();
  els_mt_.clear();
  els_reliso_.clear();
  els_tru_dr_.clear();
  jets_id_.clear();
  jets_pt_res_.clear();
  mus_miniso_tr10_.clear();
  mus_mt_.clear();
  mus_reliso_.clear();
  mus_tru_dr_.clear();
  els_tru_id_.clear();
  els_tru_momid_.clear();
  mus_tru_id_.clear();
  mus_tru_momid_.clear();
}

string small_tree_quick::Type() const{
  return "quick";
}

small_tree_quick::~small_tree_quick(){
}

void small_tree_quick::GetEntry(const long entry){
  small_tree::GetEntry(entry);

  c_dphi_wlep_ = false;
  c_dphi_wlep_reliso_ = false;
  c_ht40_ = false;
  c_ht_reliso_ = false;
  c_lep_eta_ = false;
  c_lep_eta_reliso_ = false;
  c_lep_phi_ = false;
  c_lep_phi_reliso_ = false;
  c_lep_pt_ = false;
  c_lep_pt_reliso_ = false;
  c_mindphin_metjet_ = false;
  c_mt_reliso_ = false;
  c_st_ = false;
  c_st_reliso_ = false;
  c_trutop1_phi_ = false;
  c_trutop1_pt_ = false;
  c_trutop2_phi_ = false;
  c_trutop2_pt_ = false;
  c_lep_charge_ = false;
  c_lep_charge_reliso_ = false;
  c_nbl40_ = false;
  c_nbm40_ = false;
  c_nbt40_ = false;
  c_nels_reliso_ = false;
  c_njets40_ = false;
  c_nleps_reliso_ = false;
  c_nmus_reliso_ = false;
  c_ntks_chg_ = false;
  c_ntks_chg_mini_ = false;
  c_ntrumeisr_ = false;
  c_nvels_reliso_ = false;
  c_nvmus_reliso_ = false;
  c_els_tru_tm_ = false;
  c_mus_tru_tm_ = false;
  c_els_miniso_tr10_ = false;
  c_els_mt_ = false;
  c_els_reliso_ = false;
  c_els_tru_dr_ = false;
  c_jets_id_ = false;
  c_jets_pt_res_ = false;
  c_mus_miniso_tr10_ = false;
  c_mus_mt_ = false;
  c_mus_reliso_ = false;
  c_mus_tru_dr_ = false;
  c_els_tru_id_ = false;
  c_els_tru_momid_ = false;
  c_mus_tru_id_ = false;
  c_mus_tru_momid_ = false;
}

float  const & small_tree_quick::dphi_wlep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dphi_wlep_ && b_dphi_wlep_){
    b_dphi_wlep_->GetEntry(entry_);
    c_dphi_wlep_ = true;
  }
  return dphi_wlep_;
}

float  const & small_tree_quick::dphi_wlep_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dphi_wlep_reliso_ && b_dphi_wlep_reliso_){
    b_dphi_wlep_reliso_->GetEntry(entry_);
    c_dphi_wlep_reliso_ = true;
  }
  return dphi_wlep_reliso_;
}

float  const & small_tree_quick::ht40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht40_ && b_ht40_){
    b_ht40_->GetEntry(entry_);
    c_ht40_ = true;
  }
  return ht40_;
}

float  const & small_tree_quick::ht_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_reliso_ && b_ht_reliso_){
    b_ht_reliso_->GetEntry(entry_);
    c_ht_reliso_ = true;
  }
  return ht_reliso_;
}

float  const & small_tree_quick::lep_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_eta_ && b_lep_eta_){
    b_lep_eta_->GetEntry(entry_);
    c_lep_eta_ = true;
  }
  return lep_eta_;
}

float  const & small_tree_quick::lep_eta_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_eta_reliso_ && b_lep_eta_reliso_){
    b_lep_eta_reliso_->GetEntry(entry_);
    c_lep_eta_reliso_ = true;
  }
  return lep_eta_reliso_;
}

float  const & small_tree_quick::lep_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_phi_ && b_lep_phi_){
    b_lep_phi_->GetEntry(entry_);
    c_lep_phi_ = true;
  }
  return lep_phi_;
}

float  const & small_tree_quick::lep_phi_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_phi_reliso_ && b_lep_phi_reliso_){
    b_lep_phi_reliso_->GetEntry(entry_);
    c_lep_phi_reliso_ = true;
  }
  return lep_phi_reliso_;
}

float  const & small_tree_quick::lep_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_pt_ && b_lep_pt_){
    b_lep_pt_->GetEntry(entry_);
    c_lep_pt_ = true;
  }
  return lep_pt_;
}

float  const & small_tree_quick::lep_pt_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_pt_reliso_ && b_lep_pt_reliso_){
    b_lep_pt_reliso_->GetEntry(entry_);
    c_lep_pt_reliso_ = true;
  }
  return lep_pt_reliso_;
}

float  const & small_tree_quick::mindphin_metjet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mindphin_metjet_ && b_mindphin_metjet_){
    b_mindphin_metjet_->GetEntry(entry_);
    c_mindphin_metjet_ = true;
  }
  return mindphin_metjet_;
}

float  const & small_tree_quick::mt_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mt_reliso_ && b_mt_reliso_){
    b_mt_reliso_->GetEntry(entry_);
    c_mt_reliso_ = true;
  }
  return mt_reliso_;
}

float  const & small_tree_quick::st() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_st_ && b_st_){
    b_st_->GetEntry(entry_);
    c_st_ = true;
  }
  return st_;
}

float  const & small_tree_quick::st_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_st_reliso_ && b_st_reliso_){
    b_st_reliso_->GetEntry(entry_);
    c_st_reliso_ = true;
  }
  return st_reliso_;
}

float  const & small_tree_quick::trutop1_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop1_phi_ && b_trutop1_phi_){
    b_trutop1_phi_->GetEntry(entry_);
    c_trutop1_phi_ = true;
  }
  return trutop1_phi_;
}

float  const & small_tree_quick::trutop1_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop1_pt_ && b_trutop1_pt_){
    b_trutop1_pt_->GetEntry(entry_);
    c_trutop1_pt_ = true;
  }
  return trutop1_pt_;
}

float  const & small_tree_quick::trutop2_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop2_phi_ && b_trutop2_phi_){
    b_trutop2_phi_->GetEntry(entry_);
    c_trutop2_phi_ = true;
  }
  return trutop2_phi_;
}

float  const & small_tree_quick::trutop2_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop2_pt_ && b_trutop2_pt_){
    b_trutop2_pt_->GetEntry(entry_);
    c_trutop2_pt_ = true;
  }
  return trutop2_pt_;
}

int  const & small_tree_quick::lep_charge() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_charge_ && b_lep_charge_){
    b_lep_charge_->GetEntry(entry_);
    c_lep_charge_ = true;
  }
  return lep_charge_;
}

int  const & small_tree_quick::lep_charge_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_charge_reliso_ && b_lep_charge_reliso_){
    b_lep_charge_reliso_->GetEntry(entry_);
    c_lep_charge_reliso_ = true;
  }
  return lep_charge_reliso_;
}

int  const & small_tree_quick::nbl40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbl40_ && b_nbl40_){
    b_nbl40_->GetEntry(entry_);
    c_nbl40_ = true;
  }
  return nbl40_;
}

int  const & small_tree_quick::nbm40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbm40_ && b_nbm40_){
    b_nbm40_->GetEntry(entry_);
    c_nbm40_ = true;
  }
  return nbm40_;
}

int  const & small_tree_quick::nbt40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbt40_ && b_nbt40_){
    b_nbt40_->GetEntry(entry_);
    c_nbt40_ = true;
  }
  return nbt40_;
}

int  const & small_tree_quick::nels_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nels_reliso_ && b_nels_reliso_){
    b_nels_reliso_->GetEntry(entry_);
    c_nels_reliso_ = true;
  }
  return nels_reliso_;
}

int  const & small_tree_quick::njets40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_njets40_ && b_njets40_){
    b_njets40_->GetEntry(entry_);
    c_njets40_ = true;
  }
  return njets40_;
}

int  const & small_tree_quick::nleps_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nleps_reliso_ && b_nleps_reliso_){
    b_nleps_reliso_->GetEntry(entry_);
    c_nleps_reliso_ = true;
  }
  return nleps_reliso_;
}

int  const & small_tree_quick::nmus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nmus_reliso_ && b_nmus_reliso_){
    b_nmus_reliso_->GetEntry(entry_);
    c_nmus_reliso_ = true;
  }
  return nmus_reliso_;
}

int  const & small_tree_quick::ntks_chg() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntks_chg_ && b_ntks_chg_){
    b_ntks_chg_->GetEntry(entry_);
    c_ntks_chg_ = true;
  }
  return ntks_chg_;
}

int  const & small_tree_quick::ntks_chg_mini() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntks_chg_mini_ && b_ntks_chg_mini_){
    b_ntks_chg_mini_->GetEntry(entry_);
    c_ntks_chg_mini_ = true;
  }
  return ntks_chg_mini_;
}

int  const & small_tree_quick::ntrumeisr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntrumeisr_ && b_ntrumeisr_){
    b_ntrumeisr_->GetEntry(entry_);
    c_ntrumeisr_ = true;
  }
  return ntrumeisr_;
}

int  const & small_tree_quick::nvels_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvels_reliso_ && b_nvels_reliso_){
    b_nvels_reliso_->GetEntry(entry_);
    c_nvels_reliso_ = true;
  }
  return nvels_reliso_;
}

int  const & small_tree_quick::nvmus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvmus_reliso_ && b_nvmus_reliso_){
    b_nvmus_reliso_->GetEntry(entry_);
    c_nvmus_reliso_ = true;
  }
  return nvmus_reliso_;
}

std::vector<bool>  const & small_tree_quick::els_tru_tm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_tm_ && b_els_tru_tm_){
    b_els_tru_tm_->GetEntry(entry_);
    c_els_tru_tm_ = true;
  }
  return els_tru_tm_;
}

std::vector<bool>  const & small_tree_quick::mus_tru_tm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_tm_ && b_mus_tru_tm_){
    b_mus_tru_tm_->GetEntry(entry_);
    c_mus_tru_tm_ = true;
  }
  return mus_tru_tm_;
}

std::vector<float>  const & small_tree_quick::els_miniso_tr10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_miniso_tr10_ && b_els_miniso_tr10_){
    b_els_miniso_tr10_->GetEntry(entry_);
    c_els_miniso_tr10_ = true;
  }
  return els_miniso_tr10_;
}

std::vector<float>  const & small_tree_quick::els_mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_mt_ && b_els_mt_){
    b_els_mt_->GetEntry(entry_);
    c_els_mt_ = true;
  }
  return els_mt_;
}

std::vector<float>  const & small_tree_quick::els_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_ && b_els_reliso_){
    b_els_reliso_->GetEntry(entry_);
    c_els_reliso_ = true;
  }
  return els_reliso_;
}

std::vector<float>  const & small_tree_quick::els_tru_dr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_dr_ && b_els_tru_dr_){
    b_els_tru_dr_->GetEntry(entry_);
    c_els_tru_dr_ = true;
  }
  return els_tru_dr_;
}

std::vector<float>  const & small_tree_quick::jets_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_id_ && b_jets_id_){
    b_jets_id_->GetEntry(entry_);
    c_jets_id_ = true;
  }
  return jets_id_;
}

std::vector<float>  const & small_tree_quick::jets_pt_res() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_pt_res_ && b_jets_pt_res_){
    b_jets_pt_res_->GetEntry(entry_);
    c_jets_pt_res_ = true;
  }
  return jets_pt_res_;
}

std::vector<float>  const & small_tree_quick::mus_miniso_tr10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_miniso_tr10_ && b_mus_miniso_tr10_){
    b_mus_miniso_tr10_->GetEntry(entry_);
    c_mus_miniso_tr10_ = true;
  }
  return mus_miniso_tr10_;
}

std::vector<float>  const & small_tree_quick::mus_mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_mt_ && b_mus_mt_){
    b_mus_mt_->GetEntry(entry_);
    c_mus_mt_ = true;
  }
  return mus_mt_;
}

std::vector<float>  const & small_tree_quick::mus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_ && b_mus_reliso_){
    b_mus_reliso_->GetEntry(entry_);
    c_mus_reliso_ = true;
  }
  return mus_reliso_;
}

std::vector<float>  const & small_tree_quick::mus_tru_dr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_dr_ && b_mus_tru_dr_){
    b_mus_tru_dr_->GetEntry(entry_);
    c_mus_tru_dr_ = true;
  }
  return mus_tru_dr_;
}

std::vector<int>  const & small_tree_quick::els_tru_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_id_ && b_els_tru_id_){
    b_els_tru_id_->GetEntry(entry_);
    c_els_tru_id_ = true;
  }
  return els_tru_id_;
}

std::vector<int>  const & small_tree_quick::els_tru_momid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_momid_ && b_els_tru_momid_){
    b_els_tru_momid_->GetEntry(entry_);
    c_els_tru_momid_ = true;
  }
  return els_tru_momid_;
}

std::vector<int>  const & small_tree_quick::mus_tru_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_id_ && b_mus_tru_id_){
    b_mus_tru_id_->GetEntry(entry_);
    c_mus_tru_id_ = true;
  }
  return mus_tru_id_;
}

std::vector<int>  const & small_tree_quick::mus_tru_momid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_momid_ && b_mus_tru_momid_){
    b_mus_tru_momid_->GetEntry(entry_);
    c_mus_tru_momid_ = true;
  }
  return mus_tru_momid_;
}

float  & small_tree_quick::dphi_wlep(){
  if(read_only_ && !c_dphi_wlep_ && b_dphi_wlep_){
    b_dphi_wlep_->GetEntry(entry_);
    c_dphi_wlep_ = true;
  }
  return dphi_wlep_;
}

float  & small_tree_quick::dphi_wlep_reliso(){
  if(read_only_ && !c_dphi_wlep_reliso_ && b_dphi_wlep_reliso_){
    b_dphi_wlep_reliso_->GetEntry(entry_);
    c_dphi_wlep_reliso_ = true;
  }
  return dphi_wlep_reliso_;
}

float  & small_tree_quick::ht40(){
  if(read_only_ && !c_ht40_ && b_ht40_){
    b_ht40_->GetEntry(entry_);
    c_ht40_ = true;
  }
  return ht40_;
}

float  & small_tree_quick::ht_reliso(){
  if(read_only_ && !c_ht_reliso_ && b_ht_reliso_){
    b_ht_reliso_->GetEntry(entry_);
    c_ht_reliso_ = true;
  }
  return ht_reliso_;
}

float  & small_tree_quick::lep_eta(){
  if(read_only_ && !c_lep_eta_ && b_lep_eta_){
    b_lep_eta_->GetEntry(entry_);
    c_lep_eta_ = true;
  }
  return lep_eta_;
}

float  & small_tree_quick::lep_eta_reliso(){
  if(read_only_ && !c_lep_eta_reliso_ && b_lep_eta_reliso_){
    b_lep_eta_reliso_->GetEntry(entry_);
    c_lep_eta_reliso_ = true;
  }
  return lep_eta_reliso_;
}

float  & small_tree_quick::lep_phi(){
  if(read_only_ && !c_lep_phi_ && b_lep_phi_){
    b_lep_phi_->GetEntry(entry_);
    c_lep_phi_ = true;
  }
  return lep_phi_;
}

float  & small_tree_quick::lep_phi_reliso(){
  if(read_only_ && !c_lep_phi_reliso_ && b_lep_phi_reliso_){
    b_lep_phi_reliso_->GetEntry(entry_);
    c_lep_phi_reliso_ = true;
  }
  return lep_phi_reliso_;
}

float  & small_tree_quick::lep_pt(){
  if(read_only_ && !c_lep_pt_ && b_lep_pt_){
    b_lep_pt_->GetEntry(entry_);
    c_lep_pt_ = true;
  }
  return lep_pt_;
}

float  & small_tree_quick::lep_pt_reliso(){
  if(read_only_ && !c_lep_pt_reliso_ && b_lep_pt_reliso_){
    b_lep_pt_reliso_->GetEntry(entry_);
    c_lep_pt_reliso_ = true;
  }
  return lep_pt_reliso_;
}

float  & small_tree_quick::mindphin_metjet(){
  if(read_only_ && !c_mindphin_metjet_ && b_mindphin_metjet_){
    b_mindphin_metjet_->GetEntry(entry_);
    c_mindphin_metjet_ = true;
  }
  return mindphin_metjet_;
}

float  & small_tree_quick::mt_reliso(){
  if(read_only_ && !c_mt_reliso_ && b_mt_reliso_){
    b_mt_reliso_->GetEntry(entry_);
    c_mt_reliso_ = true;
  }
  return mt_reliso_;
}

float  & small_tree_quick::st(){
  if(read_only_ && !c_st_ && b_st_){
    b_st_->GetEntry(entry_);
    c_st_ = true;
  }
  return st_;
}

float  & small_tree_quick::st_reliso(){
  if(read_only_ && !c_st_reliso_ && b_st_reliso_){
    b_st_reliso_->GetEntry(entry_);
    c_st_reliso_ = true;
  }
  return st_reliso_;
}

float  & small_tree_quick::trutop1_phi(){
  if(read_only_ && !c_trutop1_phi_ && b_trutop1_phi_){
    b_trutop1_phi_->GetEntry(entry_);
    c_trutop1_phi_ = true;
  }
  return trutop1_phi_;
}

float  & small_tree_quick::trutop1_pt(){
  if(read_only_ && !c_trutop1_pt_ && b_trutop1_pt_){
    b_trutop1_pt_->GetEntry(entry_);
    c_trutop1_pt_ = true;
  }
  return trutop1_pt_;
}

float  & small_tree_quick::trutop2_phi(){
  if(read_only_ && !c_trutop2_phi_ && b_trutop2_phi_){
    b_trutop2_phi_->GetEntry(entry_);
    c_trutop2_phi_ = true;
  }
  return trutop2_phi_;
}

float  & small_tree_quick::trutop2_pt(){
  if(read_only_ && !c_trutop2_pt_ && b_trutop2_pt_){
    b_trutop2_pt_->GetEntry(entry_);
    c_trutop2_pt_ = true;
  }
  return trutop2_pt_;
}

int  & small_tree_quick::lep_charge(){
  if(read_only_ && !c_lep_charge_ && b_lep_charge_){
    b_lep_charge_->GetEntry(entry_);
    c_lep_charge_ = true;
  }
  return lep_charge_;
}

int  & small_tree_quick::lep_charge_reliso(){
  if(read_only_ && !c_lep_charge_reliso_ && b_lep_charge_reliso_){
    b_lep_charge_reliso_->GetEntry(entry_);
    c_lep_charge_reliso_ = true;
  }
  return lep_charge_reliso_;
}

int  & small_tree_quick::nbl40(){
  if(read_only_ && !c_nbl40_ && b_nbl40_){
    b_nbl40_->GetEntry(entry_);
    c_nbl40_ = true;
  }
  return nbl40_;
}

int  & small_tree_quick::nbm40(){
  if(read_only_ && !c_nbm40_ && b_nbm40_){
    b_nbm40_->GetEntry(entry_);
    c_nbm40_ = true;
  }
  return nbm40_;
}

int  & small_tree_quick::nbt40(){
  if(read_only_ && !c_nbt40_ && b_nbt40_){
    b_nbt40_->GetEntry(entry_);
    c_nbt40_ = true;
  }
  return nbt40_;
}

int  & small_tree_quick::nels_reliso(){
  if(read_only_ && !c_nels_reliso_ && b_nels_reliso_){
    b_nels_reliso_->GetEntry(entry_);
    c_nels_reliso_ = true;
  }
  return nels_reliso_;
}

int  & small_tree_quick::njets40(){
  if(read_only_ && !c_njets40_ && b_njets40_){
    b_njets40_->GetEntry(entry_);
    c_njets40_ = true;
  }
  return njets40_;
}

int  & small_tree_quick::nleps_reliso(){
  if(read_only_ && !c_nleps_reliso_ && b_nleps_reliso_){
    b_nleps_reliso_->GetEntry(entry_);
    c_nleps_reliso_ = true;
  }
  return nleps_reliso_;
}

int  & small_tree_quick::nmus_reliso(){
  if(read_only_ && !c_nmus_reliso_ && b_nmus_reliso_){
    b_nmus_reliso_->GetEntry(entry_);
    c_nmus_reliso_ = true;
  }
  return nmus_reliso_;
}

int  & small_tree_quick::ntks_chg(){
  if(read_only_ && !c_ntks_chg_ && b_ntks_chg_){
    b_ntks_chg_->GetEntry(entry_);
    c_ntks_chg_ = true;
  }
  return ntks_chg_;
}

int  & small_tree_quick::ntks_chg_mini(){
  if(read_only_ && !c_ntks_chg_mini_ && b_ntks_chg_mini_){
    b_ntks_chg_mini_->GetEntry(entry_);
    c_ntks_chg_mini_ = true;
  }
  return ntks_chg_mini_;
}

int  & small_tree_quick::ntrumeisr(){
  if(read_only_ && !c_ntrumeisr_ && b_ntrumeisr_){
    b_ntrumeisr_->GetEntry(entry_);
    c_ntrumeisr_ = true;
  }
  return ntrumeisr_;
}

int  & small_tree_quick::nvels_reliso(){
  if(read_only_ && !c_nvels_reliso_ && b_nvels_reliso_){
    b_nvels_reliso_->GetEntry(entry_);
    c_nvels_reliso_ = true;
  }
  return nvels_reliso_;
}

int  & small_tree_quick::nvmus_reliso(){
  if(read_only_ && !c_nvmus_reliso_ && b_nvmus_reliso_){
    b_nvmus_reliso_->GetEntry(entry_);
    c_nvmus_reliso_ = true;
  }
  return nvmus_reliso_;
}

std::vector<bool>  & small_tree_quick::els_tru_tm(){
  if(read_only_ && !c_els_tru_tm_ && b_els_tru_tm_){
    b_els_tru_tm_->GetEntry(entry_);
    c_els_tru_tm_ = true;
  }
  return els_tru_tm_;
}

std::vector<bool>  & small_tree_quick::mus_tru_tm(){
  if(read_only_ && !c_mus_tru_tm_ && b_mus_tru_tm_){
    b_mus_tru_tm_->GetEntry(entry_);
    c_mus_tru_tm_ = true;
  }
  return mus_tru_tm_;
}

std::vector<float>  & small_tree_quick::els_miniso_tr10(){
  if(read_only_ && !c_els_miniso_tr10_ && b_els_miniso_tr10_){
    b_els_miniso_tr10_->GetEntry(entry_);
    c_els_miniso_tr10_ = true;
  }
  return els_miniso_tr10_;
}

std::vector<float>  & small_tree_quick::els_mt(){
  if(read_only_ && !c_els_mt_ && b_els_mt_){
    b_els_mt_->GetEntry(entry_);
    c_els_mt_ = true;
  }
  return els_mt_;
}

std::vector<float>  & small_tree_quick::els_reliso(){
  if(read_only_ && !c_els_reliso_ && b_els_reliso_){
    b_els_reliso_->GetEntry(entry_);
    c_els_reliso_ = true;
  }
  return els_reliso_;
}

std::vector<float>  & small_tree_quick::els_tru_dr(){
  if(read_only_ && !c_els_tru_dr_ && b_els_tru_dr_){
    b_els_tru_dr_->GetEntry(entry_);
    c_els_tru_dr_ = true;
  }
  return els_tru_dr_;
}

std::vector<float>  & small_tree_quick::jets_id(){
  if(read_only_ && !c_jets_id_ && b_jets_id_){
    b_jets_id_->GetEntry(entry_);
    c_jets_id_ = true;
  }
  return jets_id_;
}

std::vector<float>  & small_tree_quick::jets_pt_res(){
  if(read_only_ && !c_jets_pt_res_ && b_jets_pt_res_){
    b_jets_pt_res_->GetEntry(entry_);
    c_jets_pt_res_ = true;
  }
  return jets_pt_res_;
}

std::vector<float>  & small_tree_quick::mus_miniso_tr10(){
  if(read_only_ && !c_mus_miniso_tr10_ && b_mus_miniso_tr10_){
    b_mus_miniso_tr10_->GetEntry(entry_);
    c_mus_miniso_tr10_ = true;
  }
  return mus_miniso_tr10_;
}

std::vector<float>  & small_tree_quick::mus_mt(){
  if(read_only_ && !c_mus_mt_ && b_mus_mt_){
    b_mus_mt_->GetEntry(entry_);
    c_mus_mt_ = true;
  }
  return mus_mt_;
}

std::vector<float>  & small_tree_quick::mus_reliso(){
  if(read_only_ && !c_mus_reliso_ && b_mus_reliso_){
    b_mus_reliso_->GetEntry(entry_);
    c_mus_reliso_ = true;
  }
  return mus_reliso_;
}

std::vector<float>  & small_tree_quick::mus_tru_dr(){
  if(read_only_ && !c_mus_tru_dr_ && b_mus_tru_dr_){
    b_mus_tru_dr_->GetEntry(entry_);
    c_mus_tru_dr_ = true;
  }
  return mus_tru_dr_;
}

std::vector<int>  & small_tree_quick::els_tru_id(){
  if(read_only_ && !c_els_tru_id_ && b_els_tru_id_){
    b_els_tru_id_->GetEntry(entry_);
    c_els_tru_id_ = true;
  }
  return els_tru_id_;
}

std::vector<int>  & small_tree_quick::els_tru_momid(){
  if(read_only_ && !c_els_tru_momid_ && b_els_tru_momid_){
    b_els_tru_momid_->GetEntry(entry_);
    c_els_tru_momid_ = true;
  }
  return els_tru_momid_;
}

std::vector<int>  & small_tree_quick::mus_tru_id(){
  if(read_only_ && !c_mus_tru_id_ && b_mus_tru_id_){
    b_mus_tru_id_->GetEntry(entry_);
    c_mus_tru_id_ = true;
  }
  return mus_tru_id_;
}

std::vector<int>  & small_tree_quick::mus_tru_momid(){
  if(read_only_ && !c_mus_tru_momid_ && b_mus_tru_momid_){
    b_mus_tru_momid_->GetEntry(entry_);
    c_mus_tru_momid_ = true;
  }
  return mus_tru_momid_;
}

