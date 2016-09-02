// small_tree_full: full version of small_tree to handle reduce tree ntuples
//File generated with generate_small_tree.exe

#include "small_tree.hpp"

#include "small_tree_full.hpp"

#include <stdexcept>
#include <string>
#include <vector>

#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"

using namespace std;

small_tree_full::small_tree_full():
  small_tree(),
  dphi_neutralinos_(0),
  b_dphi_neutralinos_(tree_.Branch("dphi_neutralinos", &dphi_neutralinos_)),
  c_dphi_neutralinos_(false),
  dphi_wlep_(0),
  b_dphi_wlep_(tree_.Branch("dphi_wlep", &dphi_wlep_)),
  c_dphi_wlep_(false),
  dphi_wlep_reliso_(0),
  b_dphi_wlep_reliso_(tree_.Branch("dphi_wlep_reliso", &dphi_wlep_reliso_)),
  c_dphi_wlep_reliso_(false),
  gen_ht_(0),
  b_gen_ht_(tree_.Branch("gen_ht", &gen_ht_)),
  c_gen_ht_(false),
  gen_met_(0),
  b_gen_met_(tree_.Branch("gen_met", &gen_met_)),
  c_gen_met_(false),
  gen_met_phi_(0),
  b_gen_met_phi_(tree_.Branch("gen_met_phi", &gen_met_phi_)),
  c_gen_met_phi_(false),
  gen_mj_(0),
  b_gen_mj_(tree_.Branch("gen_mj", &gen_mj_)),
  c_gen_mj_(false),
  ht40_(0),
  b_ht40_(tree_.Branch("ht40", &ht40_)),
  c_ht40_(false),
  ht_isr_(0),
  b_ht_isr_(tree_.Branch("ht_isr", &ht_isr_)),
  c_ht_isr_(false),
  ht_isr_me_(0),
  b_ht_isr_me_(tree_.Branch("ht_isr_me", &ht_isr_me_)),
  c_ht_isr_me_(false),
  ht_isr_nonme_(0),
  b_ht_isr_nonme_(tree_.Branch("ht_isr_nonme", &ht_isr_nonme_)),
  c_ht_isr_nonme_(false),
  ht_isr_tru_(0),
  b_ht_isr_tru_(tree_.Branch("ht_isr_tru", &ht_isr_tru_)),
  c_ht_isr_tru_(false),
  ht_nonb_(0),
  b_ht_nonb_(tree_.Branch("ht_nonb", &ht_nonb_)),
  c_ht_nonb_(false),
  ht_sub_(0),
  b_ht_sub_(tree_.Branch("ht_sub", &ht_sub_)),
  c_ht_sub_(false),
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
  max_dphi_bb_(0),
  b_max_dphi_bb_(tree_.Branch("max_dphi_bb", &max_dphi_bb_)),
  c_max_dphi_bb_(false),
  max_dphi_blep_(0),
  b_max_dphi_blep_(tree_.Branch("max_dphi_blep", &max_dphi_blep_)),
  c_max_dphi_blep_(false),
  max_dphi_bmet_(0),
  b_max_dphi_bmet_(tree_.Branch("max_dphi_bmet", &max_dphi_bmet_)),
  c_max_dphi_bmet_(false),
  max_dr_bb_(0),
  b_max_dr_bb_(tree_.Branch("max_dr_bb", &max_dr_bb_)),
  c_max_dr_bb_(false),
  max_dr_blep_(0),
  b_max_dr_blep_(tree_.Branch("max_dr_blep", &max_dr_blep_)),
  c_max_dr_blep_(false),
  max_m_bb_(0),
  b_max_m_bb_(tree_.Branch("max_m_bb", &max_m_bb_)),
  c_max_m_bb_(false),
  max_m_blep_(0),
  b_max_m_blep_(tree_.Branch("max_m_blep", &max_m_blep_)),
  c_max_m_blep_(false),
  max_mt_bmet_(0),
  b_max_mt_bmet_(tree_.Branch("max_mt_bmet", &max_mt_bmet_)),
  c_max_mt_bmet_(false),
  max_pt_bb_(0),
  b_max_pt_bb_(tree_.Branch("max_pt_bb", &max_pt_bb_)),
  c_max_pt_bb_(false),
  max_pt_blep_(0),
  b_max_pt_blep_(tree_.Branch("max_pt_blep", &max_pt_blep_)),
  c_max_pt_blep_(false),
  max_pt_bmet_(0),
  b_max_pt_bmet_(tree_.Branch("max_pt_bmet", &max_pt_bmet_)),
  c_max_pt_bmet_(false),
  mht_sub_(0),
  b_mht_sub_(tree_.Branch("mht_sub", &mht_sub_)),
  c_mht_sub_(false),
  min_dphi_bb_(0),
  b_min_dphi_bb_(tree_.Branch("min_dphi_bb", &min_dphi_bb_)),
  c_min_dphi_bb_(false),
  min_dphi_blep_(0),
  b_min_dphi_blep_(tree_.Branch("min_dphi_blep", &min_dphi_blep_)),
  c_min_dphi_blep_(false),
  min_dphi_bmet_(0),
  b_min_dphi_bmet_(tree_.Branch("min_dphi_bmet", &min_dphi_bmet_)),
  c_min_dphi_bmet_(false),
  min_dr_bb_(0),
  b_min_dr_bb_(tree_.Branch("min_dr_bb", &min_dr_bb_)),
  c_min_dr_bb_(false),
  min_dr_blep_(0),
  b_min_dr_blep_(tree_.Branch("min_dr_blep", &min_dr_blep_)),
  c_min_dr_blep_(false),
  min_m_bb_(0),
  b_min_m_bb_(tree_.Branch("min_m_bb", &min_m_bb_)),
  c_min_m_bb_(false),
  min_m_blep_(0),
  b_min_m_blep_(tree_.Branch("min_m_blep", &min_m_blep_)),
  c_min_m_blep_(false),
  min_mt_bmet_(0),
  b_min_mt_bmet_(tree_.Branch("min_mt_bmet", &min_mt_bmet_)),
  c_min_mt_bmet_(false),
  min_mt_bmet_with_w_mass_(0),
  b_min_mt_bmet_with_w_mass_(tree_.Branch("min_mt_bmet_with_w_mass", &min_mt_bmet_with_w_mass_)),
  c_min_mt_bmet_with_w_mass_(false),
  min_pt_bb_(0),
  b_min_pt_bb_(tree_.Branch("min_pt_bb", &min_pt_bb_)),
  c_min_pt_bb_(false),
  min_pt_blep_(0),
  b_min_pt_blep_(tree_.Branch("min_pt_blep", &min_pt_blep_)),
  c_min_pt_blep_(false),
  min_pt_bmet_(0),
  b_min_pt_bmet_(tree_.Branch("min_pt_bmet", &min_pt_bmet_)),
  c_min_pt_bmet_(false),
  mindphin_metjet_(0),
  b_mindphin_metjet_(tree_.Branch("mindphin_metjet", &mindphin_metjet_)),
  c_mindphin_metjet_(false),
  mj15_(0),
  b_mj15_(tree_.Branch("mj15", &mj15_)),
  c_mj15_(false),
  mj_sub_(0),
  b_mj_sub_(tree_.Branch("mj_sub", &mj_sub_)),
  c_mj_sub_(false),
  mt_reliso_(0),
  b_mt_reliso_(tree_.Branch("mt_reliso", &mt_reliso_)),
  c_mt_reliso_(false),
  st_(0),
  b_st_(tree_.Branch("st", &st_)),
  c_st_(false),
  st_reliso_(0),
  b_st_reliso_(tree_.Branch("st_reliso", &st_reliso_)),
  c_st_reliso_(false),
  tru_gluglu_dphi_(0),
  b_tru_gluglu_dphi_(tree_.Branch("tru_gluglu_dphi", &tru_gluglu_dphi_)),
  c_tru_gluglu_dphi_(false),
  tru_gluglu_m_(0),
  b_tru_gluglu_m_(tree_.Branch("tru_gluglu_m", &tru_gluglu_m_)),
  c_tru_gluglu_m_(false),
  tru_gluglu_pt_(0),
  b_tru_gluglu_pt_(tree_.Branch("tru_gluglu_pt", &tru_gluglu_pt_)),
  c_tru_gluglu_pt_(false),
  tru_gluglu_ptdiff_(0),
  b_tru_gluglu_ptdiff_(tree_.Branch("tru_gluglu_ptdiff", &tru_gluglu_ptdiff_)),
  c_tru_gluglu_ptdiff_(false),
  tru_sphericity_(0),
  b_tru_sphericity_(tree_.Branch("tru_sphericity", &tru_sphericity_)),
  c_tru_sphericity_(false),
  tru_tt_dphi_(0),
  b_tru_tt_dphi_(tree_.Branch("tru_tt_dphi", &tru_tt_dphi_)),
  c_tru_tt_dphi_(false),
  tru_tt_m_(0),
  b_tru_tt_m_(tree_.Branch("tru_tt_m", &tru_tt_m_)),
  c_tru_tt_m_(false),
  tru_tt_pt_(0),
  b_tru_tt_pt_(tree_.Branch("tru_tt_pt", &tru_tt_pt_)),
  c_tru_tt_pt_(false),
  tru_tt_ptdiff_(0),
  b_tru_tt_ptdiff_(tree_.Branch("tru_tt_ptdiff", &tru_tt_ptdiff_)),
  c_tru_tt_ptdiff_(false),
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
  n_isr_me_(0),
  b_n_isr_me_(tree_.Branch("n_isr_me", &n_isr_me_)),
  c_n_isr_me_(false),
  n_isr_nonme_(0),
  b_n_isr_nonme_(tree_.Branch("n_isr_nonme", &n_isr_nonme_)),
  c_n_isr_nonme_(false),
  nbadjets_(0),
  b_nbadjets_(tree_.Branch("nbadjets", &nbadjets_)),
  c_nbadjets_(false),
  nbl40_(0),
  b_nbl40_(tree_.Branch("nbl40", &nbl40_)),
  c_nbl40_(false),
  nbl_sub_(0),
  b_nbl_sub_(tree_.Branch("nbl_sub", &nbl_sub_)),
  c_nbl_sub_(false),
  nbm40_(0),
  b_nbm40_(tree_.Branch("nbm40", &nbm40_)),
  c_nbm40_(false),
  nbm_sub_(0),
  b_nbm_sub_(tree_.Branch("nbm_sub", &nbm_sub_)),
  c_nbm_sub_(false),
  nbt40_(0),
  b_nbt40_(tree_.Branch("nbt40", &nbt40_)),
  c_nbt40_(false),
  nbt_sub_(0),
  b_nbt_sub_(tree_.Branch("nbt_sub", &nbt_sub_)),
  c_nbt_sub_(false),
  nels_reliso_(0),
  b_nels_reliso_(tree_.Branch("nels_reliso", &nels_reliso_)),
  c_nels_reliso_(false),
  nfjets15_(0),
  b_nfjets15_(tree_.Branch("nfjets15", &nfjets15_)),
  c_nfjets15_(false),
  nfsubjets_(0),
  b_nfsubjets_(tree_.Branch("nfsubjets", &nfsubjets_)),
  c_nfsubjets_(false),
  ngenfjets_(0),
  b_ngenfjets_(tree_.Branch("ngenfjets", &ngenfjets_)),
  c_ngenfjets_(false),
  ngenjets_(0),
  b_ngenjets_(tree_.Branch("ngenjets", &ngenjets_)),
  c_ngenjets_(false),
  njets40_(0),
  b_njets40_(tree_.Branch("njets40", &njets40_)),
  c_njets40_(false),
  nleps_reliso_(0),
  b_nleps_reliso_(tree_.Branch("nleps_reliso", &nleps_reliso_)),
  c_nleps_reliso_(false),
  nmus_reliso_(0),
  b_nmus_reliso_(tree_.Branch("nmus_reliso", &nmus_reliso_)),
  c_nmus_reliso_(false),
  nsubjets_(0),
  b_nsubjets_(tree_.Branch("nsubjets", &nsubjets_)),
  c_nsubjets_(false),
  ntks_(0),
  b_ntks_(tree_.Branch("ntks", &ntks_)),
  c_ntks_(false),
  ntks_chg_(0),
  b_ntks_chg_(tree_.Branch("ntks_chg", &ntks_chg_)),
  c_ntks_chg_(false),
  ntks_chg_reliso_(0),
  b_ntks_chg_reliso_(tree_.Branch("ntks_chg_reliso", &ntks_chg_reliso_)),
  c_ntks_chg_reliso_(false),
  nvels_reliso_(0),
  b_nvels_reliso_(tree_.Branch("nvels_reliso", &nvels_reliso_)),
  c_nvels_reliso_(false),
  nvmus_reliso_(0),
  b_nvmus_reliso_(tree_.Branch("nvmus_reliso", &nvmus_reliso_)),
  c_nvmus_reliso_(false),
  badjets_islep_(0),
  p_badjets_islep_(&badjets_islep_),
  b_badjets_islep_(tree_.Branch("badjets_islep", &p_badjets_islep_)),
  c_badjets_islep_(false),
  els_tru_tm_(0),
  p_els_tru_tm_(&els_tru_tm_),
  b_els_tru_tm_(tree_.Branch("els_tru_tm", &p_els_tru_tm_)),
  c_els_tru_tm_(false),
  mus_tru_tm_(0),
  p_mus_tru_tm_(&mus_tru_tm_),
  b_mus_tru_tm_(tree_.Branch("mus_tru_tm", &p_mus_tru_tm_)),
  c_mus_tru_tm_(false),
  tks_from_tau_(0),
  p_tks_from_tau_(&tks_from_tau_),
  b_tks_from_tau_(tree_.Branch("tks_from_tau", &p_tks_from_tau_)),
  c_tks_from_tau_(false),
  tks_from_tauhad_(0),
  p_tks_from_tauhad_(&tks_from_tauhad_),
  b_tks_from_tauhad_(tree_.Branch("tks_from_tauhad", &p_tks_from_tauhad_)),
  c_tks_from_tauhad_(false),
  tks_from_taulep_(0),
  p_tks_from_taulep_(&tks_from_taulep_),
  b_tks_from_taulep_(tree_.Branch("tks_from_taulep", &p_tks_from_taulep_)),
  c_tks_from_taulep_(false),
  tks_from_w_(0),
  p_tks_from_w_(&tks_from_w_),
  b_tks_from_w_(tree_.Branch("tks_from_w", &p_tks_from_w_)),
  c_tks_from_w_(false),
  tks_is_primary_(0),
  p_tks_is_primary_(&tks_is_primary_),
  b_tks_is_primary_(tree_.Branch("tks_is_primary", &p_tks_is_primary_)),
  c_tks_is_primary_(false),
  tks_is_primary_reliso_(0),
  p_tks_is_primary_reliso_(&tks_is_primary_reliso_),
  b_tks_is_primary_reliso_(tree_.Branch("tks_is_primary_reliso", &p_tks_is_primary_reliso_)),
  c_tks_is_primary_reliso_(false),
  tks_is_sig_lep_(0),
  p_tks_is_sig_lep_(&tks_is_sig_lep_),
  b_tks_is_sig_lep_(tree_.Branch("tks_is_sig_lep", &p_tks_is_sig_lep_)),
  c_tks_is_sig_lep_(false),
  badjets_eta_(0),
  p_badjets_eta_(&badjets_eta_),
  b_badjets_eta_(tree_.Branch("badjets_eta", &p_badjets_eta_)),
  c_badjets_eta_(false),
  badjets_id_(0),
  p_badjets_id_(&badjets_id_),
  b_badjets_id_(tree_.Branch("badjets_id", &p_badjets_id_)),
  c_badjets_id_(false),
  badjets_m_(0),
  p_badjets_m_(&badjets_m_),
  b_badjets_m_(tree_.Branch("badjets_m", &p_badjets_m_)),
  c_badjets_m_(false),
  badjets_phi_(0),
  p_badjets_phi_(&badjets_phi_),
  b_badjets_phi_(tree_.Branch("badjets_phi", &p_badjets_phi_)),
  c_badjets_phi_(false),
  badjets_pt_(0),
  p_badjets_pt_(&badjets_pt_),
  b_badjets_pt_(tree_.Branch("badjets_pt", &p_badjets_pt_)),
  c_badjets_pt_(false),
  els_miniso_10_(0),
  p_els_miniso_10_(&els_miniso_10_),
  b_els_miniso_10_(tree_.Branch("els_miniso_10", &p_els_miniso_10_)),
  c_els_miniso_10_(false),
  els_miniso_10_ch_(0),
  p_els_miniso_10_ch_(&els_miniso_10_ch_),
  b_els_miniso_10_ch_(tree_.Branch("els_miniso_10_ch", &p_els_miniso_10_ch_)),
  c_els_miniso_10_ch_(false),
  els_miniso_tr10_(0),
  p_els_miniso_tr10_(&els_miniso_tr10_),
  b_els_miniso_tr10_(tree_.Branch("els_miniso_tr10", &p_els_miniso_tr10_)),
  c_els_miniso_tr10_(false),
  els_miniso_tr10_ch_(0),
  p_els_miniso_tr10_ch_(&els_miniso_tr10_ch_),
  b_els_miniso_tr10_ch_(tree_.Branch("els_miniso_tr10_ch", &p_els_miniso_tr10_ch_)),
  c_els_miniso_tr10_ch_(false),
  els_mt_(0),
  p_els_mt_(&els_mt_),
  b_els_mt_(tree_.Branch("els_mt", &p_els_mt_)),
  c_els_mt_(false),
  els_reliso_(0),
  p_els_reliso_(&els_reliso_),
  b_els_reliso_(tree_.Branch("els_reliso", &p_els_reliso_)),
  c_els_reliso_(false),
  els_reliso_r01_(0),
  p_els_reliso_r01_(&els_reliso_r01_),
  b_els_reliso_r01_(tree_.Branch("els_reliso_r01", &p_els_reliso_r01_)),
  c_els_reliso_r01_(false),
  els_reliso_r015_(0),
  p_els_reliso_r015_(&els_reliso_r015_),
  b_els_reliso_r015_(tree_.Branch("els_reliso_r015", &p_els_reliso_r015_)),
  c_els_reliso_r015_(false),
  els_reliso_r02_(0),
  p_els_reliso_r02_(&els_reliso_r02_),
  b_els_reliso_r02_(tree_.Branch("els_reliso_r02", &p_els_reliso_r02_)),
  c_els_reliso_r02_(false),
  els_reliso_r03_(0),
  p_els_reliso_r03_(&els_reliso_r03_),
  b_els_reliso_r03_(tree_.Branch("els_reliso_r03", &p_els_reliso_r03_)),
  c_els_reliso_r03_(false),
  els_reliso_r04_(0),
  p_els_reliso_r04_(&els_reliso_r04_),
  b_els_reliso_r04_(tree_.Branch("els_reliso_r04", &p_els_reliso_r04_)),
  c_els_reliso_r04_(false),
  els_tru_dr_(0),
  p_els_tru_dr_(&els_tru_dr_),
  b_els_tru_dr_(tree_.Branch("els_tru_dr", &p_els_tru_dr_)),
  c_els_tru_dr_(false),
  fjets15_eta_(0),
  p_fjets15_eta_(&fjets15_eta_),
  b_fjets15_eta_(tree_.Branch("fjets15_eta", &p_fjets15_eta_)),
  c_fjets15_eta_(false),
  fjets15_m_(0),
  p_fjets15_m_(&fjets15_m_),
  b_fjets15_m_(tree_.Branch("fjets15_m", &p_fjets15_m_)),
  c_fjets15_m_(false),
  fjets15_phi_(0),
  p_fjets15_phi_(&fjets15_phi_),
  b_fjets15_phi_(tree_.Branch("fjets15_phi", &p_fjets15_phi_)),
  c_fjets15_phi_(false),
  fjets15_poscsv_(0),
  p_fjets15_poscsv_(&fjets15_poscsv_),
  b_fjets15_poscsv_(tree_.Branch("fjets15_poscsv", &p_fjets15_poscsv_)),
  c_fjets15_poscsv_(false),
  fjets15_pt_(0),
  p_fjets15_pt_(&fjets15_pt_),
  b_fjets15_pt_(tree_.Branch("fjets15_pt", &p_fjets15_pt_)),
  c_fjets15_pt_(false),
  fjets15_sumcsv_(0),
  p_fjets15_sumcsv_(&fjets15_sumcsv_),
  b_fjets15_sumcsv_(tree_.Branch("fjets15_sumcsv", &p_fjets15_sumcsv_)),
  c_fjets15_sumcsv_(false),
  fsubjets_eta_(0),
  p_fsubjets_eta_(&fsubjets_eta_),
  b_fsubjets_eta_(tree_.Branch("fsubjets_eta", &p_fsubjets_eta_)),
  c_fsubjets_eta_(false),
  fsubjets_m_(0),
  p_fsubjets_m_(&fsubjets_m_),
  b_fsubjets_m_(tree_.Branch("fsubjets_m", &p_fsubjets_m_)),
  c_fsubjets_m_(false),
  fsubjets_phi_(0),
  p_fsubjets_phi_(&fsubjets_phi_),
  b_fsubjets_phi_(tree_.Branch("fsubjets_phi", &p_fsubjets_phi_)),
  c_fsubjets_phi_(false),
  fsubjets_poscsv_(0),
  p_fsubjets_poscsv_(&fsubjets_poscsv_),
  b_fsubjets_poscsv_(tree_.Branch("fsubjets_poscsv", &p_fsubjets_poscsv_)),
  c_fsubjets_poscsv_(false),
  fsubjets_pt_(0),
  p_fsubjets_pt_(&fsubjets_pt_),
  b_fsubjets_pt_(tree_.Branch("fsubjets_pt", &p_fsubjets_pt_)),
  c_fsubjets_pt_(false),
  fsubjets_sumcsv_(0),
  p_fsubjets_sumcsv_(&fsubjets_sumcsv_),
  b_fsubjets_sumcsv_(tree_.Branch("fsubjets_sumcsv", &p_fsubjets_sumcsv_)),
  c_fsubjets_sumcsv_(false),
  genfjets_eta_(0),
  p_genfjets_eta_(&genfjets_eta_),
  b_genfjets_eta_(tree_.Branch("genfjets_eta", &p_genfjets_eta_)),
  c_genfjets_eta_(false),
  genfjets_m_(0),
  p_genfjets_m_(&genfjets_m_),
  b_genfjets_m_(tree_.Branch("genfjets_m", &p_genfjets_m_)),
  c_genfjets_m_(false),
  genfjets_phi_(0),
  p_genfjets_phi_(&genfjets_phi_),
  b_genfjets_phi_(tree_.Branch("genfjets_phi", &p_genfjets_phi_)),
  c_genfjets_phi_(false),
  genfjets_pt_(0),
  p_genfjets_pt_(&genfjets_pt_),
  b_genfjets_pt_(tree_.Branch("genfjets_pt", &p_genfjets_pt_)),
  c_genfjets_pt_(false),
  genjets_eta_(0),
  p_genjets_eta_(&genjets_eta_),
  b_genjets_eta_(tree_.Branch("genjets_eta", &p_genjets_eta_)),
  c_genjets_eta_(false),
  genjets_m_(0),
  p_genjets_m_(&genjets_m_),
  b_genjets_m_(tree_.Branch("genjets_m", &p_genjets_m_)),
  c_genjets_m_(false),
  genjets_phi_(0),
  p_genjets_phi_(&genjets_phi_),
  b_genjets_phi_(tree_.Branch("genjets_phi", &p_genjets_phi_)),
  c_genjets_phi_(false),
  genjets_pt_(0),
  p_genjets_pt_(&genjets_pt_),
  b_genjets_pt_(tree_.Branch("genjets_pt", &p_genjets_pt_)),
  c_genjets_pt_(false),
  glu_proj_frac_(0),
  p_glu_proj_frac_(&glu_proj_frac_),
  b_glu_proj_frac_(tree_.Branch("glu_proj_frac", &p_glu_proj_frac_)),
  c_glu_proj_frac_(false),
  jets_gen_pt_(0),
  p_jets_gen_pt_(&jets_gen_pt_),
  b_jets_gen_pt_(tree_.Branch("jets_gen_pt", &p_jets_gen_pt_)),
  c_jets_gen_pt_(false),
  jets_id_(0),
  p_jets_id_(&jets_id_),
  b_jets_id_(tree_.Branch("jets_id", &p_jets_id_)),
  c_jets_id_(false),
  jets_parton_pt_(0),
  p_jets_parton_pt_(&jets_parton_pt_),
  b_jets_parton_pt_(tree_.Branch("jets_parton_pt", &p_jets_parton_pt_)),
  c_jets_parton_pt_(false),
  jets_pt_from_mini_(0),
  p_jets_pt_from_mini_(&jets_pt_from_mini_),
  b_jets_pt_from_mini_(tree_.Branch("jets_pt_from_mini", &p_jets_pt_from_mini_)),
  c_jets_pt_from_mini_(false),
  mc_eta_(0),
  p_mc_eta_(&mc_eta_),
  b_mc_eta_(tree_.Branch("mc_eta", &p_mc_eta_)),
  c_mc_eta_(false),
  mc_phi_(0),
  p_mc_phi_(&mc_phi_),
  b_mc_phi_(tree_.Branch("mc_phi", &p_mc_phi_)),
  c_mc_phi_(false),
  mc_pt_(0),
  p_mc_pt_(&mc_pt_),
  b_mc_pt_(tree_.Branch("mc_pt", &p_mc_pt_)),
  c_mc_pt_(false),
  mus_miniso_10_(0),
  p_mus_miniso_10_(&mus_miniso_10_),
  b_mus_miniso_10_(tree_.Branch("mus_miniso_10", &p_mus_miniso_10_)),
  c_mus_miniso_10_(false),
  mus_miniso_10_ch_(0),
  p_mus_miniso_10_ch_(&mus_miniso_10_ch_),
  b_mus_miniso_10_ch_(tree_.Branch("mus_miniso_10_ch", &p_mus_miniso_10_ch_)),
  c_mus_miniso_10_ch_(false),
  mus_miniso_tr10_(0),
  p_mus_miniso_tr10_(&mus_miniso_tr10_),
  b_mus_miniso_tr10_(tree_.Branch("mus_miniso_tr10", &p_mus_miniso_tr10_)),
  c_mus_miniso_tr10_(false),
  mus_miniso_tr10_ch_(0),
  p_mus_miniso_tr10_ch_(&mus_miniso_tr10_ch_),
  b_mus_miniso_tr10_ch_(tree_.Branch("mus_miniso_tr10_ch", &p_mus_miniso_tr10_ch_)),
  c_mus_miniso_tr10_ch_(false),
  mus_mt_(0),
  p_mus_mt_(&mus_mt_),
  b_mus_mt_(tree_.Branch("mus_mt", &p_mus_mt_)),
  c_mus_mt_(false),
  mus_reliso_(0),
  p_mus_reliso_(&mus_reliso_),
  b_mus_reliso_(tree_.Branch("mus_reliso", &p_mus_reliso_)),
  c_mus_reliso_(false),
  mus_reliso_r01_(0),
  p_mus_reliso_r01_(&mus_reliso_r01_),
  b_mus_reliso_r01_(tree_.Branch("mus_reliso_r01", &p_mus_reliso_r01_)),
  c_mus_reliso_r01_(false),
  mus_reliso_r015_(0),
  p_mus_reliso_r015_(&mus_reliso_r015_),
  b_mus_reliso_r015_(tree_.Branch("mus_reliso_r015", &p_mus_reliso_r015_)),
  c_mus_reliso_r015_(false),
  mus_reliso_r02_(0),
  p_mus_reliso_r02_(&mus_reliso_r02_),
  b_mus_reliso_r02_(tree_.Branch("mus_reliso_r02", &p_mus_reliso_r02_)),
  c_mus_reliso_r02_(false),
  mus_reliso_r03_(0),
  p_mus_reliso_r03_(&mus_reliso_r03_),
  b_mus_reliso_r03_(tree_.Branch("mus_reliso_r03", &p_mus_reliso_r03_)),
  c_mus_reliso_r03_(false),
  mus_reliso_r04_(0),
  p_mus_reliso_r04_(&mus_reliso_r04_),
  b_mus_reliso_r04_(tree_.Branch("mus_reliso_r04", &p_mus_reliso_r04_)),
  c_mus_reliso_r04_(false),
  mus_tru_dr_(0),
  p_mus_tru_dr_(&mus_tru_dr_),
  b_mus_tru_dr_(tree_.Branch("mus_tru_dr", &p_mus_tru_dr_)),
  c_mus_tru_dr_(false),
  subjets_csv_(0),
  p_subjets_csv_(&subjets_csv_),
  b_subjets_csv_(tree_.Branch("subjets_csv", &p_subjets_csv_)),
  c_subjets_csv_(false),
  subjets_eta_(0),
  p_subjets_eta_(&subjets_eta_),
  b_subjets_eta_(tree_.Branch("subjets_eta", &p_subjets_eta_)),
  c_subjets_eta_(false),
  subjets_id_(0),
  p_subjets_id_(&subjets_id_),
  b_subjets_id_(tree_.Branch("subjets_id", &p_subjets_id_)),
  c_subjets_id_(false),
  subjets_m_(0),
  p_subjets_m_(&subjets_m_),
  b_subjets_m_(tree_.Branch("subjets_m", &p_subjets_m_)),
  c_subjets_m_(false),
  subjets_mindr_(0),
  p_subjets_mindr_(&subjets_mindr_),
  b_subjets_mindr_(tree_.Branch("subjets_mindr", &p_subjets_mindr_)),
  c_subjets_mindr_(false),
  subjets_phi_(0),
  p_subjets_phi_(&subjets_phi_),
  b_subjets_phi_(tree_.Branch("subjets_phi", &p_subjets_phi_)),
  c_subjets_phi_(false),
  subjets_pt_(0),
  p_subjets_pt_(&subjets_pt_),
  b_subjets_pt_(tree_.Branch("subjets_pt", &p_subjets_pt_)),
  c_subjets_pt_(false),
  subjets_subeta_(0),
  p_subjets_subeta_(&subjets_subeta_),
  b_subjets_subeta_(tree_.Branch("subjets_subeta", &p_subjets_subeta_)),
  c_subjets_subeta_(false),
  subjets_subm_(0),
  p_subjets_subm_(&subjets_subm_),
  b_subjets_subm_(tree_.Branch("subjets_subm", &p_subjets_subm_)),
  c_subjets_subm_(false),
  subjets_subphi_(0),
  p_subjets_subphi_(&subjets_subphi_),
  b_subjets_subphi_(tree_.Branch("subjets_subphi", &p_subjets_subphi_)),
  c_subjets_subphi_(false),
  subjets_subpt_(0),
  p_subjets_subpt_(&subjets_subpt_),
  b_subjets_subpt_(tree_.Branch("subjets_subpt", &p_subjets_subpt_)),
  c_subjets_subpt_(false),
  tks_eta_(0),
  p_tks_eta_(&tks_eta_),
  b_tks_eta_(tree_.Branch("tks_eta", &p_tks_eta_)),
  c_tks_eta_(false),
  tks_mini_ch_(0),
  p_tks_mini_ch_(&tks_mini_ch_),
  b_tks_mini_ch_(tree_.Branch("tks_mini_ch", &p_tks_mini_ch_)),
  c_tks_mini_ch_(false),
  tks_mini_ne_(0),
  p_tks_mini_ne_(&tks_mini_ne_),
  b_tks_mini_ne_(tree_.Branch("tks_mini_ne", &p_tks_mini_ne_)),
  c_tks_mini_ne_(false),
  tks_mt_(0),
  p_tks_mt_(&tks_mt_),
  b_tks_mt_(tree_.Branch("tks_mt", &p_tks_mt_)),
  c_tks_mt_(false),
  tks_phi_(0),
  p_tks_phi_(&tks_phi_),
  b_tks_phi_(tree_.Branch("tks_phi", &p_tks_phi_)),
  c_tks_phi_(false),
  tks_pt_(0),
  p_tks_pt_(&tks_pt_),
  b_tks_pt_(tree_.Branch("tks_pt", &p_tks_pt_)),
  c_tks_pt_(false),
  tks_r02_ch_(0),
  p_tks_r02_ch_(&tks_r02_ch_),
  b_tks_r02_ch_(tree_.Branch("tks_r02_ch", &p_tks_r02_ch_)),
  c_tks_r02_ch_(false),
  tks_r02_ne_(0),
  p_tks_r02_ne_(&tks_r02_ne_),
  b_tks_r02_ne_(tree_.Branch("tks_r02_ne", &p_tks_r02_ne_)),
  c_tks_r02_ne_(false),
  tks_r03_ch_(0),
  p_tks_r03_ch_(&tks_r03_ch_),
  b_tks_r03_ch_(tree_.Branch("tks_r03_ch", &p_tks_r03_ch_)),
  c_tks_r03_ch_(false),
  tks_r03_ne_(0),
  p_tks_r03_ne_(&tks_r03_ne_),
  b_tks_r03_ne_(tree_.Branch("tks_r03_ne", &p_tks_r03_ne_)),
  c_tks_r03_ne_(false),
  tks_r04_ch_(0),
  p_tks_r04_ch_(&tks_r04_ch_),
  b_tks_r04_ch_(tree_.Branch("tks_r04_ch", &p_tks_r04_ch_)),
  c_tks_r04_ch_(false),
  tks_r04_ne_(0),
  p_tks_r04_ne_(&tks_r04_ne_),
  b_tks_r04_ne_(tree_.Branch("tks_r04_ne", &p_tks_r04_ne_)),
  c_tks_r04_ne_(false),
  tks_r05_ch_(0),
  p_tks_r05_ch_(&tks_r05_ch_),
  b_tks_r05_ch_(tree_.Branch("tks_r05_ch", &p_tks_r05_ch_)),
  c_tks_r05_ch_(false),
  tks_r05_ne_(0),
  p_tks_r05_ne_(&tks_r05_ne_),
  b_tks_r05_ne_(tree_.Branch("tks_r05_ne", &p_tks_r05_ne_)),
  c_tks_r05_ne_(false),
  tks_tru_dp_(0),
  p_tks_tru_dp_(&tks_tru_dp_),
  b_tks_tru_dp_(tree_.Branch("tks_tru_dp", &p_tks_tru_dp_)),
  c_tks_tru_dp_(false),
  tks_tru_dr_(0),
  p_tks_tru_dr_(&tks_tru_dr_),
  b_tks_tru_dr_(tree_.Branch("tks_tru_dr", &p_tks_tru_dr_)),
  c_tks_tru_dr_(false),
  els_tru_id_(0),
  p_els_tru_id_(&els_tru_id_),
  b_els_tru_id_(tree_.Branch("els_tru_id", &p_els_tru_id_)),
  c_els_tru_id_(false),
  els_tru_momid_(0),
  p_els_tru_momid_(&els_tru_momid_),
  b_els_tru_momid_(tree_.Branch("els_tru_momid", &p_els_tru_momid_)),
  c_els_tru_momid_(false),
  fjets15_btags_(0),
  p_fjets15_btags_(&fjets15_btags_),
  b_fjets15_btags_(tree_.Branch("fjets15_btags", &p_fjets15_btags_)),
  c_fjets15_btags_(false),
  fjets15_nconst_(0),
  p_fjets15_nconst_(&fjets15_nconst_),
  b_fjets15_nconst_(tree_.Branch("fjets15_nconst", &p_fjets15_nconst_)),
  c_fjets15_nconst_(false),
  fsubjets_btags_(0),
  p_fsubjets_btags_(&fsubjets_btags_),
  b_fsubjets_btags_(tree_.Branch("fsubjets_btags", &p_fsubjets_btags_)),
  c_fsubjets_btags_(false),
  fsubjets_nconst_(0),
  p_fsubjets_nconst_(&fsubjets_nconst_),
  b_fsubjets_nconst_(tree_.Branch("fsubjets_nconst", &p_fsubjets_nconst_)),
  c_fsubjets_nconst_(false),
  genfjets_nconst_(0),
  p_genfjets_nconst_(&genfjets_nconst_),
  b_genfjets_nconst_(tree_.Branch("genfjets_nconst", &p_genfjets_nconst_)),
  c_genfjets_nconst_(false),
  genjets_genfjet_index_(0),
  p_genjets_genfjet_index_(&genjets_genfjet_index_),
  b_genjets_genfjet_index_(tree_.Branch("genjets_genfjet_index", &p_genjets_genfjet_index_)),
  c_genjets_genfjet_index_(false),
  genjets_isr_code_(0),
  p_genjets_isr_code_(&genjets_isr_code_),
  b_genjets_isr_code_(tree_.Branch("genjets_isr_code", &p_genjets_isr_code_)),
  c_genjets_isr_code_(false),
  jets_fjet15_index_(0),
  p_jets_fjet15_index_(&jets_fjet15_index_),
  b_jets_fjet15_index_(tree_.Branch("jets_fjet15_index", &p_jets_fjet15_index_)),
  c_jets_fjet15_index_(false),
  jets_isr_code_(0),
  p_jets_isr_code_(&jets_isr_code_),
  b_jets_isr_code_(tree_.Branch("jets_isr_code", &p_jets_isr_code_)),
  c_jets_isr_code_(false),
  mc_id_(0),
  p_mc_id_(&mc_id_),
  b_mc_id_(tree_.Branch("mc_id", &p_mc_id_)),
  c_mc_id_(false),
  mc_status_(0),
  p_mc_status_(&mc_status_),
  b_mc_status_(tree_.Branch("mc_status", &p_mc_status_)),
  c_mc_status_(false),
  mus_tru_id_(0),
  p_mus_tru_id_(&mus_tru_id_),
  b_mus_tru_id_(tree_.Branch("mus_tru_id", &p_mus_tru_id_)),
  c_mus_tru_id_(false),
  mus_tru_momid_(0),
  p_mus_tru_momid_(&mus_tru_momid_),
  b_mus_tru_momid_(tree_.Branch("mus_tru_momid", &p_mus_tru_momid_)),
  c_mus_tru_momid_(false),
  subjets_fsubjet_index_(0),
  p_subjets_fsubjet_index_(&subjets_fsubjet_index_),
  b_subjets_fsubjet_index_(tree_.Branch("subjets_fsubjet_index", &p_subjets_fsubjet_index_)),
  c_subjets_fsubjet_index_(false),
  subjets_nsub_(0),
  p_subjets_nsub_(&subjets_nsub_),
  b_subjets_nsub_(tree_.Branch("subjets_nsub", &p_subjets_nsub_)),
  c_subjets_nsub_(false),
  tks_charge_(0),
  p_tks_charge_(&tks_charge_),
  b_tks_charge_(tree_.Branch("tks_charge", &p_tks_charge_)),
  c_tks_charge_(false),
  tks_from_pv_(0),
  p_tks_from_pv_(&tks_from_pv_),
  b_tks_from_pv_(tree_.Branch("tks_from_pv", &p_tks_from_pv_)),
  c_tks_from_pv_(false),
  tks_id_(0),
  p_tks_id_(&tks_id_),
  b_tks_id_(tree_.Branch("tks_id", &p_tks_id_)),
  c_tks_id_(false),
  tks_num_prongs_(0),
  p_tks_num_prongs_(&tks_num_prongs_),
  b_tks_num_prongs_(tree_.Branch("tks_num_prongs", &p_tks_num_prongs_)),
  c_tks_num_prongs_(false),
  tks_tru_id_(0),
  p_tks_tru_id_(&tks_tru_id_),
  b_tks_tru_id_(tree_.Branch("tks_tru_id", &p_tks_tru_id_)),
  c_tks_tru_id_(false),
  mc_mom_(0),
  p_mc_mom_(&mc_mom_),
  b_mc_mom_(tree_.Branch("mc_mom", &p_mc_mom_)),
  c_mc_mom_(false),
  mc_type_(0),
  b_mc_type_(tree_.Branch("mc_type", &mc_type_)),
  c_mc_type_(false){
}

small_tree_full::small_tree_full(const string &filename):
  small_tree(filename),
  dphi_neutralinos_(0),
  b_dphi_neutralinos_(NULL),
  c_dphi_neutralinos_(false),
  dphi_wlep_(0),
  b_dphi_wlep_(NULL),
  c_dphi_wlep_(false),
  dphi_wlep_reliso_(0),
  b_dphi_wlep_reliso_(NULL),
  c_dphi_wlep_reliso_(false),
  gen_ht_(0),
  b_gen_ht_(NULL),
  c_gen_ht_(false),
  gen_met_(0),
  b_gen_met_(NULL),
  c_gen_met_(false),
  gen_met_phi_(0),
  b_gen_met_phi_(NULL),
  c_gen_met_phi_(false),
  gen_mj_(0),
  b_gen_mj_(NULL),
  c_gen_mj_(false),
  ht40_(0),
  b_ht40_(NULL),
  c_ht40_(false),
  ht_isr_(0),
  b_ht_isr_(NULL),
  c_ht_isr_(false),
  ht_isr_me_(0),
  b_ht_isr_me_(NULL),
  c_ht_isr_me_(false),
  ht_isr_nonme_(0),
  b_ht_isr_nonme_(NULL),
  c_ht_isr_nonme_(false),
  ht_isr_tru_(0),
  b_ht_isr_tru_(NULL),
  c_ht_isr_tru_(false),
  ht_nonb_(0),
  b_ht_nonb_(NULL),
  c_ht_nonb_(false),
  ht_sub_(0),
  b_ht_sub_(NULL),
  c_ht_sub_(false),
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
  max_dphi_bb_(0),
  b_max_dphi_bb_(NULL),
  c_max_dphi_bb_(false),
  max_dphi_blep_(0),
  b_max_dphi_blep_(NULL),
  c_max_dphi_blep_(false),
  max_dphi_bmet_(0),
  b_max_dphi_bmet_(NULL),
  c_max_dphi_bmet_(false),
  max_dr_bb_(0),
  b_max_dr_bb_(NULL),
  c_max_dr_bb_(false),
  max_dr_blep_(0),
  b_max_dr_blep_(NULL),
  c_max_dr_blep_(false),
  max_m_bb_(0),
  b_max_m_bb_(NULL),
  c_max_m_bb_(false),
  max_m_blep_(0),
  b_max_m_blep_(NULL),
  c_max_m_blep_(false),
  max_mt_bmet_(0),
  b_max_mt_bmet_(NULL),
  c_max_mt_bmet_(false),
  max_pt_bb_(0),
  b_max_pt_bb_(NULL),
  c_max_pt_bb_(false),
  max_pt_blep_(0),
  b_max_pt_blep_(NULL),
  c_max_pt_blep_(false),
  max_pt_bmet_(0),
  b_max_pt_bmet_(NULL),
  c_max_pt_bmet_(false),
  mht_sub_(0),
  b_mht_sub_(NULL),
  c_mht_sub_(false),
  min_dphi_bb_(0),
  b_min_dphi_bb_(NULL),
  c_min_dphi_bb_(false),
  min_dphi_blep_(0),
  b_min_dphi_blep_(NULL),
  c_min_dphi_blep_(false),
  min_dphi_bmet_(0),
  b_min_dphi_bmet_(NULL),
  c_min_dphi_bmet_(false),
  min_dr_bb_(0),
  b_min_dr_bb_(NULL),
  c_min_dr_bb_(false),
  min_dr_blep_(0),
  b_min_dr_blep_(NULL),
  c_min_dr_blep_(false),
  min_m_bb_(0),
  b_min_m_bb_(NULL),
  c_min_m_bb_(false),
  min_m_blep_(0),
  b_min_m_blep_(NULL),
  c_min_m_blep_(false),
  min_mt_bmet_(0),
  b_min_mt_bmet_(NULL),
  c_min_mt_bmet_(false),
  min_mt_bmet_with_w_mass_(0),
  b_min_mt_bmet_with_w_mass_(NULL),
  c_min_mt_bmet_with_w_mass_(false),
  min_pt_bb_(0),
  b_min_pt_bb_(NULL),
  c_min_pt_bb_(false),
  min_pt_blep_(0),
  b_min_pt_blep_(NULL),
  c_min_pt_blep_(false),
  min_pt_bmet_(0),
  b_min_pt_bmet_(NULL),
  c_min_pt_bmet_(false),
  mindphin_metjet_(0),
  b_mindphin_metjet_(NULL),
  c_mindphin_metjet_(false),
  mj15_(0),
  b_mj15_(NULL),
  c_mj15_(false),
  mj_sub_(0),
  b_mj_sub_(NULL),
  c_mj_sub_(false),
  mt_reliso_(0),
  b_mt_reliso_(NULL),
  c_mt_reliso_(false),
  st_(0),
  b_st_(NULL),
  c_st_(false),
  st_reliso_(0),
  b_st_reliso_(NULL),
  c_st_reliso_(false),
  tru_gluglu_dphi_(0),
  b_tru_gluglu_dphi_(NULL),
  c_tru_gluglu_dphi_(false),
  tru_gluglu_m_(0),
  b_tru_gluglu_m_(NULL),
  c_tru_gluglu_m_(false),
  tru_gluglu_pt_(0),
  b_tru_gluglu_pt_(NULL),
  c_tru_gluglu_pt_(false),
  tru_gluglu_ptdiff_(0),
  b_tru_gluglu_ptdiff_(NULL),
  c_tru_gluglu_ptdiff_(false),
  tru_sphericity_(0),
  b_tru_sphericity_(NULL),
  c_tru_sphericity_(false),
  tru_tt_dphi_(0),
  b_tru_tt_dphi_(NULL),
  c_tru_tt_dphi_(false),
  tru_tt_m_(0),
  b_tru_tt_m_(NULL),
  c_tru_tt_m_(false),
  tru_tt_pt_(0),
  b_tru_tt_pt_(NULL),
  c_tru_tt_pt_(false),
  tru_tt_ptdiff_(0),
  b_tru_tt_ptdiff_(NULL),
  c_tru_tt_ptdiff_(false),
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
  n_isr_me_(0),
  b_n_isr_me_(NULL),
  c_n_isr_me_(false),
  n_isr_nonme_(0),
  b_n_isr_nonme_(NULL),
  c_n_isr_nonme_(false),
  nbadjets_(0),
  b_nbadjets_(NULL),
  c_nbadjets_(false),
  nbl40_(0),
  b_nbl40_(NULL),
  c_nbl40_(false),
  nbl_sub_(0),
  b_nbl_sub_(NULL),
  c_nbl_sub_(false),
  nbm40_(0),
  b_nbm40_(NULL),
  c_nbm40_(false),
  nbm_sub_(0),
  b_nbm_sub_(NULL),
  c_nbm_sub_(false),
  nbt40_(0),
  b_nbt40_(NULL),
  c_nbt40_(false),
  nbt_sub_(0),
  b_nbt_sub_(NULL),
  c_nbt_sub_(false),
  nels_reliso_(0),
  b_nels_reliso_(NULL),
  c_nels_reliso_(false),
  nfjets15_(0),
  b_nfjets15_(NULL),
  c_nfjets15_(false),
  nfsubjets_(0),
  b_nfsubjets_(NULL),
  c_nfsubjets_(false),
  ngenfjets_(0),
  b_ngenfjets_(NULL),
  c_ngenfjets_(false),
  ngenjets_(0),
  b_ngenjets_(NULL),
  c_ngenjets_(false),
  njets40_(0),
  b_njets40_(NULL),
  c_njets40_(false),
  nleps_reliso_(0),
  b_nleps_reliso_(NULL),
  c_nleps_reliso_(false),
  nmus_reliso_(0),
  b_nmus_reliso_(NULL),
  c_nmus_reliso_(false),
  nsubjets_(0),
  b_nsubjets_(NULL),
  c_nsubjets_(false),
  ntks_(0),
  b_ntks_(NULL),
  c_ntks_(false),
  ntks_chg_(0),
  b_ntks_chg_(NULL),
  c_ntks_chg_(false),
  ntks_chg_reliso_(0),
  b_ntks_chg_reliso_(NULL),
  c_ntks_chg_reliso_(false),
  nvels_reliso_(0),
  b_nvels_reliso_(NULL),
  c_nvels_reliso_(false),
  nvmus_reliso_(0),
  b_nvmus_reliso_(NULL),
  c_nvmus_reliso_(false),
  badjets_islep_(0),
  p_badjets_islep_(&badjets_islep_),
  b_badjets_islep_(NULL),
  c_badjets_islep_(false),
  els_tru_tm_(0),
  p_els_tru_tm_(&els_tru_tm_),
  b_els_tru_tm_(NULL),
  c_els_tru_tm_(false),
  mus_tru_tm_(0),
  p_mus_tru_tm_(&mus_tru_tm_),
  b_mus_tru_tm_(NULL),
  c_mus_tru_tm_(false),
  tks_from_tau_(0),
  p_tks_from_tau_(&tks_from_tau_),
  b_tks_from_tau_(NULL),
  c_tks_from_tau_(false),
  tks_from_tauhad_(0),
  p_tks_from_tauhad_(&tks_from_tauhad_),
  b_tks_from_tauhad_(NULL),
  c_tks_from_tauhad_(false),
  tks_from_taulep_(0),
  p_tks_from_taulep_(&tks_from_taulep_),
  b_tks_from_taulep_(NULL),
  c_tks_from_taulep_(false),
  tks_from_w_(0),
  p_tks_from_w_(&tks_from_w_),
  b_tks_from_w_(NULL),
  c_tks_from_w_(false),
  tks_is_primary_(0),
  p_tks_is_primary_(&tks_is_primary_),
  b_tks_is_primary_(NULL),
  c_tks_is_primary_(false),
  tks_is_primary_reliso_(0),
  p_tks_is_primary_reliso_(&tks_is_primary_reliso_),
  b_tks_is_primary_reliso_(NULL),
  c_tks_is_primary_reliso_(false),
  tks_is_sig_lep_(0),
  p_tks_is_sig_lep_(&tks_is_sig_lep_),
  b_tks_is_sig_lep_(NULL),
  c_tks_is_sig_lep_(false),
  badjets_eta_(0),
  p_badjets_eta_(&badjets_eta_),
  b_badjets_eta_(NULL),
  c_badjets_eta_(false),
  badjets_id_(0),
  p_badjets_id_(&badjets_id_),
  b_badjets_id_(NULL),
  c_badjets_id_(false),
  badjets_m_(0),
  p_badjets_m_(&badjets_m_),
  b_badjets_m_(NULL),
  c_badjets_m_(false),
  badjets_phi_(0),
  p_badjets_phi_(&badjets_phi_),
  b_badjets_phi_(NULL),
  c_badjets_phi_(false),
  badjets_pt_(0),
  p_badjets_pt_(&badjets_pt_),
  b_badjets_pt_(NULL),
  c_badjets_pt_(false),
  els_miniso_10_(0),
  p_els_miniso_10_(&els_miniso_10_),
  b_els_miniso_10_(NULL),
  c_els_miniso_10_(false),
  els_miniso_10_ch_(0),
  p_els_miniso_10_ch_(&els_miniso_10_ch_),
  b_els_miniso_10_ch_(NULL),
  c_els_miniso_10_ch_(false),
  els_miniso_tr10_(0),
  p_els_miniso_tr10_(&els_miniso_tr10_),
  b_els_miniso_tr10_(NULL),
  c_els_miniso_tr10_(false),
  els_miniso_tr10_ch_(0),
  p_els_miniso_tr10_ch_(&els_miniso_tr10_ch_),
  b_els_miniso_tr10_ch_(NULL),
  c_els_miniso_tr10_ch_(false),
  els_mt_(0),
  p_els_mt_(&els_mt_),
  b_els_mt_(NULL),
  c_els_mt_(false),
  els_reliso_(0),
  p_els_reliso_(&els_reliso_),
  b_els_reliso_(NULL),
  c_els_reliso_(false),
  els_reliso_r01_(0),
  p_els_reliso_r01_(&els_reliso_r01_),
  b_els_reliso_r01_(NULL),
  c_els_reliso_r01_(false),
  els_reliso_r015_(0),
  p_els_reliso_r015_(&els_reliso_r015_),
  b_els_reliso_r015_(NULL),
  c_els_reliso_r015_(false),
  els_reliso_r02_(0),
  p_els_reliso_r02_(&els_reliso_r02_),
  b_els_reliso_r02_(NULL),
  c_els_reliso_r02_(false),
  els_reliso_r03_(0),
  p_els_reliso_r03_(&els_reliso_r03_),
  b_els_reliso_r03_(NULL),
  c_els_reliso_r03_(false),
  els_reliso_r04_(0),
  p_els_reliso_r04_(&els_reliso_r04_),
  b_els_reliso_r04_(NULL),
  c_els_reliso_r04_(false),
  els_tru_dr_(0),
  p_els_tru_dr_(&els_tru_dr_),
  b_els_tru_dr_(NULL),
  c_els_tru_dr_(false),
  fjets15_eta_(0),
  p_fjets15_eta_(&fjets15_eta_),
  b_fjets15_eta_(NULL),
  c_fjets15_eta_(false),
  fjets15_m_(0),
  p_fjets15_m_(&fjets15_m_),
  b_fjets15_m_(NULL),
  c_fjets15_m_(false),
  fjets15_phi_(0),
  p_fjets15_phi_(&fjets15_phi_),
  b_fjets15_phi_(NULL),
  c_fjets15_phi_(false),
  fjets15_poscsv_(0),
  p_fjets15_poscsv_(&fjets15_poscsv_),
  b_fjets15_poscsv_(NULL),
  c_fjets15_poscsv_(false),
  fjets15_pt_(0),
  p_fjets15_pt_(&fjets15_pt_),
  b_fjets15_pt_(NULL),
  c_fjets15_pt_(false),
  fjets15_sumcsv_(0),
  p_fjets15_sumcsv_(&fjets15_sumcsv_),
  b_fjets15_sumcsv_(NULL),
  c_fjets15_sumcsv_(false),
  fsubjets_eta_(0),
  p_fsubjets_eta_(&fsubjets_eta_),
  b_fsubjets_eta_(NULL),
  c_fsubjets_eta_(false),
  fsubjets_m_(0),
  p_fsubjets_m_(&fsubjets_m_),
  b_fsubjets_m_(NULL),
  c_fsubjets_m_(false),
  fsubjets_phi_(0),
  p_fsubjets_phi_(&fsubjets_phi_),
  b_fsubjets_phi_(NULL),
  c_fsubjets_phi_(false),
  fsubjets_poscsv_(0),
  p_fsubjets_poscsv_(&fsubjets_poscsv_),
  b_fsubjets_poscsv_(NULL),
  c_fsubjets_poscsv_(false),
  fsubjets_pt_(0),
  p_fsubjets_pt_(&fsubjets_pt_),
  b_fsubjets_pt_(NULL),
  c_fsubjets_pt_(false),
  fsubjets_sumcsv_(0),
  p_fsubjets_sumcsv_(&fsubjets_sumcsv_),
  b_fsubjets_sumcsv_(NULL),
  c_fsubjets_sumcsv_(false),
  genfjets_eta_(0),
  p_genfjets_eta_(&genfjets_eta_),
  b_genfjets_eta_(NULL),
  c_genfjets_eta_(false),
  genfjets_m_(0),
  p_genfjets_m_(&genfjets_m_),
  b_genfjets_m_(NULL),
  c_genfjets_m_(false),
  genfjets_phi_(0),
  p_genfjets_phi_(&genfjets_phi_),
  b_genfjets_phi_(NULL),
  c_genfjets_phi_(false),
  genfjets_pt_(0),
  p_genfjets_pt_(&genfjets_pt_),
  b_genfjets_pt_(NULL),
  c_genfjets_pt_(false),
  genjets_eta_(0),
  p_genjets_eta_(&genjets_eta_),
  b_genjets_eta_(NULL),
  c_genjets_eta_(false),
  genjets_m_(0),
  p_genjets_m_(&genjets_m_),
  b_genjets_m_(NULL),
  c_genjets_m_(false),
  genjets_phi_(0),
  p_genjets_phi_(&genjets_phi_),
  b_genjets_phi_(NULL),
  c_genjets_phi_(false),
  genjets_pt_(0),
  p_genjets_pt_(&genjets_pt_),
  b_genjets_pt_(NULL),
  c_genjets_pt_(false),
  glu_proj_frac_(0),
  p_glu_proj_frac_(&glu_proj_frac_),
  b_glu_proj_frac_(NULL),
  c_glu_proj_frac_(false),
  jets_gen_pt_(0),
  p_jets_gen_pt_(&jets_gen_pt_),
  b_jets_gen_pt_(NULL),
  c_jets_gen_pt_(false),
  jets_id_(0),
  p_jets_id_(&jets_id_),
  b_jets_id_(NULL),
  c_jets_id_(false),
  jets_parton_pt_(0),
  p_jets_parton_pt_(&jets_parton_pt_),
  b_jets_parton_pt_(NULL),
  c_jets_parton_pt_(false),
  jets_pt_from_mini_(0),
  p_jets_pt_from_mini_(&jets_pt_from_mini_),
  b_jets_pt_from_mini_(NULL),
  c_jets_pt_from_mini_(false),
  mc_eta_(0),
  p_mc_eta_(&mc_eta_),
  b_mc_eta_(NULL),
  c_mc_eta_(false),
  mc_phi_(0),
  p_mc_phi_(&mc_phi_),
  b_mc_phi_(NULL),
  c_mc_phi_(false),
  mc_pt_(0),
  p_mc_pt_(&mc_pt_),
  b_mc_pt_(NULL),
  c_mc_pt_(false),
  mus_miniso_10_(0),
  p_mus_miniso_10_(&mus_miniso_10_),
  b_mus_miniso_10_(NULL),
  c_mus_miniso_10_(false),
  mus_miniso_10_ch_(0),
  p_mus_miniso_10_ch_(&mus_miniso_10_ch_),
  b_mus_miniso_10_ch_(NULL),
  c_mus_miniso_10_ch_(false),
  mus_miniso_tr10_(0),
  p_mus_miniso_tr10_(&mus_miniso_tr10_),
  b_mus_miniso_tr10_(NULL),
  c_mus_miniso_tr10_(false),
  mus_miniso_tr10_ch_(0),
  p_mus_miniso_tr10_ch_(&mus_miniso_tr10_ch_),
  b_mus_miniso_tr10_ch_(NULL),
  c_mus_miniso_tr10_ch_(false),
  mus_mt_(0),
  p_mus_mt_(&mus_mt_),
  b_mus_mt_(NULL),
  c_mus_mt_(false),
  mus_reliso_(0),
  p_mus_reliso_(&mus_reliso_),
  b_mus_reliso_(NULL),
  c_mus_reliso_(false),
  mus_reliso_r01_(0),
  p_mus_reliso_r01_(&mus_reliso_r01_),
  b_mus_reliso_r01_(NULL),
  c_mus_reliso_r01_(false),
  mus_reliso_r015_(0),
  p_mus_reliso_r015_(&mus_reliso_r015_),
  b_mus_reliso_r015_(NULL),
  c_mus_reliso_r015_(false),
  mus_reliso_r02_(0),
  p_mus_reliso_r02_(&mus_reliso_r02_),
  b_mus_reliso_r02_(NULL),
  c_mus_reliso_r02_(false),
  mus_reliso_r03_(0),
  p_mus_reliso_r03_(&mus_reliso_r03_),
  b_mus_reliso_r03_(NULL),
  c_mus_reliso_r03_(false),
  mus_reliso_r04_(0),
  p_mus_reliso_r04_(&mus_reliso_r04_),
  b_mus_reliso_r04_(NULL),
  c_mus_reliso_r04_(false),
  mus_tru_dr_(0),
  p_mus_tru_dr_(&mus_tru_dr_),
  b_mus_tru_dr_(NULL),
  c_mus_tru_dr_(false),
  subjets_csv_(0),
  p_subjets_csv_(&subjets_csv_),
  b_subjets_csv_(NULL),
  c_subjets_csv_(false),
  subjets_eta_(0),
  p_subjets_eta_(&subjets_eta_),
  b_subjets_eta_(NULL),
  c_subjets_eta_(false),
  subjets_id_(0),
  p_subjets_id_(&subjets_id_),
  b_subjets_id_(NULL),
  c_subjets_id_(false),
  subjets_m_(0),
  p_subjets_m_(&subjets_m_),
  b_subjets_m_(NULL),
  c_subjets_m_(false),
  subjets_mindr_(0),
  p_subjets_mindr_(&subjets_mindr_),
  b_subjets_mindr_(NULL),
  c_subjets_mindr_(false),
  subjets_phi_(0),
  p_subjets_phi_(&subjets_phi_),
  b_subjets_phi_(NULL),
  c_subjets_phi_(false),
  subjets_pt_(0),
  p_subjets_pt_(&subjets_pt_),
  b_subjets_pt_(NULL),
  c_subjets_pt_(false),
  subjets_subeta_(0),
  p_subjets_subeta_(&subjets_subeta_),
  b_subjets_subeta_(NULL),
  c_subjets_subeta_(false),
  subjets_subm_(0),
  p_subjets_subm_(&subjets_subm_),
  b_subjets_subm_(NULL),
  c_subjets_subm_(false),
  subjets_subphi_(0),
  p_subjets_subphi_(&subjets_subphi_),
  b_subjets_subphi_(NULL),
  c_subjets_subphi_(false),
  subjets_subpt_(0),
  p_subjets_subpt_(&subjets_subpt_),
  b_subjets_subpt_(NULL),
  c_subjets_subpt_(false),
  tks_eta_(0),
  p_tks_eta_(&tks_eta_),
  b_tks_eta_(NULL),
  c_tks_eta_(false),
  tks_mini_ch_(0),
  p_tks_mini_ch_(&tks_mini_ch_),
  b_tks_mini_ch_(NULL),
  c_tks_mini_ch_(false),
  tks_mini_ne_(0),
  p_tks_mini_ne_(&tks_mini_ne_),
  b_tks_mini_ne_(NULL),
  c_tks_mini_ne_(false),
  tks_mt_(0),
  p_tks_mt_(&tks_mt_),
  b_tks_mt_(NULL),
  c_tks_mt_(false),
  tks_phi_(0),
  p_tks_phi_(&tks_phi_),
  b_tks_phi_(NULL),
  c_tks_phi_(false),
  tks_pt_(0),
  p_tks_pt_(&tks_pt_),
  b_tks_pt_(NULL),
  c_tks_pt_(false),
  tks_r02_ch_(0),
  p_tks_r02_ch_(&tks_r02_ch_),
  b_tks_r02_ch_(NULL),
  c_tks_r02_ch_(false),
  tks_r02_ne_(0),
  p_tks_r02_ne_(&tks_r02_ne_),
  b_tks_r02_ne_(NULL),
  c_tks_r02_ne_(false),
  tks_r03_ch_(0),
  p_tks_r03_ch_(&tks_r03_ch_),
  b_tks_r03_ch_(NULL),
  c_tks_r03_ch_(false),
  tks_r03_ne_(0),
  p_tks_r03_ne_(&tks_r03_ne_),
  b_tks_r03_ne_(NULL),
  c_tks_r03_ne_(false),
  tks_r04_ch_(0),
  p_tks_r04_ch_(&tks_r04_ch_),
  b_tks_r04_ch_(NULL),
  c_tks_r04_ch_(false),
  tks_r04_ne_(0),
  p_tks_r04_ne_(&tks_r04_ne_),
  b_tks_r04_ne_(NULL),
  c_tks_r04_ne_(false),
  tks_r05_ch_(0),
  p_tks_r05_ch_(&tks_r05_ch_),
  b_tks_r05_ch_(NULL),
  c_tks_r05_ch_(false),
  tks_r05_ne_(0),
  p_tks_r05_ne_(&tks_r05_ne_),
  b_tks_r05_ne_(NULL),
  c_tks_r05_ne_(false),
  tks_tru_dp_(0),
  p_tks_tru_dp_(&tks_tru_dp_),
  b_tks_tru_dp_(NULL),
  c_tks_tru_dp_(false),
  tks_tru_dr_(0),
  p_tks_tru_dr_(&tks_tru_dr_),
  b_tks_tru_dr_(NULL),
  c_tks_tru_dr_(false),
  els_tru_id_(0),
  p_els_tru_id_(&els_tru_id_),
  b_els_tru_id_(NULL),
  c_els_tru_id_(false),
  els_tru_momid_(0),
  p_els_tru_momid_(&els_tru_momid_),
  b_els_tru_momid_(NULL),
  c_els_tru_momid_(false),
  fjets15_btags_(0),
  p_fjets15_btags_(&fjets15_btags_),
  b_fjets15_btags_(NULL),
  c_fjets15_btags_(false),
  fjets15_nconst_(0),
  p_fjets15_nconst_(&fjets15_nconst_),
  b_fjets15_nconst_(NULL),
  c_fjets15_nconst_(false),
  fsubjets_btags_(0),
  p_fsubjets_btags_(&fsubjets_btags_),
  b_fsubjets_btags_(NULL),
  c_fsubjets_btags_(false),
  fsubjets_nconst_(0),
  p_fsubjets_nconst_(&fsubjets_nconst_),
  b_fsubjets_nconst_(NULL),
  c_fsubjets_nconst_(false),
  genfjets_nconst_(0),
  p_genfjets_nconst_(&genfjets_nconst_),
  b_genfjets_nconst_(NULL),
  c_genfjets_nconst_(false),
  genjets_genfjet_index_(0),
  p_genjets_genfjet_index_(&genjets_genfjet_index_),
  b_genjets_genfjet_index_(NULL),
  c_genjets_genfjet_index_(false),
  genjets_isr_code_(0),
  p_genjets_isr_code_(&genjets_isr_code_),
  b_genjets_isr_code_(NULL),
  c_genjets_isr_code_(false),
  jets_fjet15_index_(0),
  p_jets_fjet15_index_(&jets_fjet15_index_),
  b_jets_fjet15_index_(NULL),
  c_jets_fjet15_index_(false),
  jets_isr_code_(0),
  p_jets_isr_code_(&jets_isr_code_),
  b_jets_isr_code_(NULL),
  c_jets_isr_code_(false),
  mc_id_(0),
  p_mc_id_(&mc_id_),
  b_mc_id_(NULL),
  c_mc_id_(false),
  mc_status_(0),
  p_mc_status_(&mc_status_),
  b_mc_status_(NULL),
  c_mc_status_(false),
  mus_tru_id_(0),
  p_mus_tru_id_(&mus_tru_id_),
  b_mus_tru_id_(NULL),
  c_mus_tru_id_(false),
  mus_tru_momid_(0),
  p_mus_tru_momid_(&mus_tru_momid_),
  b_mus_tru_momid_(NULL),
  c_mus_tru_momid_(false),
  subjets_fsubjet_index_(0),
  p_subjets_fsubjet_index_(&subjets_fsubjet_index_),
  b_subjets_fsubjet_index_(NULL),
  c_subjets_fsubjet_index_(false),
  subjets_nsub_(0),
  p_subjets_nsub_(&subjets_nsub_),
  b_subjets_nsub_(NULL),
  c_subjets_nsub_(false),
  tks_charge_(0),
  p_tks_charge_(&tks_charge_),
  b_tks_charge_(NULL),
  c_tks_charge_(false),
  tks_from_pv_(0),
  p_tks_from_pv_(&tks_from_pv_),
  b_tks_from_pv_(NULL),
  c_tks_from_pv_(false),
  tks_id_(0),
  p_tks_id_(&tks_id_),
  b_tks_id_(NULL),
  c_tks_id_(false),
  tks_num_prongs_(0),
  p_tks_num_prongs_(&tks_num_prongs_),
  b_tks_num_prongs_(NULL),
  c_tks_num_prongs_(false),
  tks_tru_id_(0),
  p_tks_tru_id_(&tks_tru_id_),
  b_tks_tru_id_(NULL),
  c_tks_tru_id_(false),
  mc_mom_(0),
  p_mc_mom_(&mc_mom_),
  b_mc_mom_(NULL),
  c_mc_mom_(false),
  mc_type_(0),
  b_mc_type_(NULL),
  c_mc_type_(false){
  chain_.SetBranchAddress("dphi_neutralinos", &dphi_neutralinos_, &b_dphi_neutralinos_);
  chain_.SetBranchAddress("dphi_wlep", &dphi_wlep_, &b_dphi_wlep_);
  chain_.SetBranchAddress("dphi_wlep_reliso", &dphi_wlep_reliso_, &b_dphi_wlep_reliso_);
  chain_.SetBranchAddress("gen_ht", &gen_ht_, &b_gen_ht_);
  chain_.SetBranchAddress("gen_met", &gen_met_, &b_gen_met_);
  chain_.SetBranchAddress("gen_met_phi", &gen_met_phi_, &b_gen_met_phi_);
  chain_.SetBranchAddress("gen_mj", &gen_mj_, &b_gen_mj_);
  chain_.SetBranchAddress("ht40", &ht40_, &b_ht40_);
  chain_.SetBranchAddress("ht_isr", &ht_isr_, &b_ht_isr_);
  chain_.SetBranchAddress("ht_isr_me", &ht_isr_me_, &b_ht_isr_me_);
  chain_.SetBranchAddress("ht_isr_nonme", &ht_isr_nonme_, &b_ht_isr_nonme_);
  chain_.SetBranchAddress("ht_isr_tru", &ht_isr_tru_, &b_ht_isr_tru_);
  chain_.SetBranchAddress("ht_nonb", &ht_nonb_, &b_ht_nonb_);
  chain_.SetBranchAddress("ht_sub", &ht_sub_, &b_ht_sub_);
  chain_.SetBranchAddress("lep_eta", &lep_eta_, &b_lep_eta_);
  chain_.SetBranchAddress("lep_eta_reliso", &lep_eta_reliso_, &b_lep_eta_reliso_);
  chain_.SetBranchAddress("lep_phi", &lep_phi_, &b_lep_phi_);
  chain_.SetBranchAddress("lep_phi_reliso", &lep_phi_reliso_, &b_lep_phi_reliso_);
  chain_.SetBranchAddress("lep_pt", &lep_pt_, &b_lep_pt_);
  chain_.SetBranchAddress("lep_pt_reliso", &lep_pt_reliso_, &b_lep_pt_reliso_);
  chain_.SetBranchAddress("max_dphi_bb", &max_dphi_bb_, &b_max_dphi_bb_);
  chain_.SetBranchAddress("max_dphi_blep", &max_dphi_blep_, &b_max_dphi_blep_);
  chain_.SetBranchAddress("max_dphi_bmet", &max_dphi_bmet_, &b_max_dphi_bmet_);
  chain_.SetBranchAddress("max_dr_bb", &max_dr_bb_, &b_max_dr_bb_);
  chain_.SetBranchAddress("max_dr_blep", &max_dr_blep_, &b_max_dr_blep_);
  chain_.SetBranchAddress("max_m_bb", &max_m_bb_, &b_max_m_bb_);
  chain_.SetBranchAddress("max_m_blep", &max_m_blep_, &b_max_m_blep_);
  chain_.SetBranchAddress("max_mt_bmet", &max_mt_bmet_, &b_max_mt_bmet_);
  chain_.SetBranchAddress("max_pt_bb", &max_pt_bb_, &b_max_pt_bb_);
  chain_.SetBranchAddress("max_pt_blep", &max_pt_blep_, &b_max_pt_blep_);
  chain_.SetBranchAddress("max_pt_bmet", &max_pt_bmet_, &b_max_pt_bmet_);
  chain_.SetBranchAddress("mht_sub", &mht_sub_, &b_mht_sub_);
  chain_.SetBranchAddress("min_dphi_bb", &min_dphi_bb_, &b_min_dphi_bb_);
  chain_.SetBranchAddress("min_dphi_blep", &min_dphi_blep_, &b_min_dphi_blep_);
  chain_.SetBranchAddress("min_dphi_bmet", &min_dphi_bmet_, &b_min_dphi_bmet_);
  chain_.SetBranchAddress("min_dr_bb", &min_dr_bb_, &b_min_dr_bb_);
  chain_.SetBranchAddress("min_dr_blep", &min_dr_blep_, &b_min_dr_blep_);
  chain_.SetBranchAddress("min_m_bb", &min_m_bb_, &b_min_m_bb_);
  chain_.SetBranchAddress("min_m_blep", &min_m_blep_, &b_min_m_blep_);
  chain_.SetBranchAddress("min_mt_bmet", &min_mt_bmet_, &b_min_mt_bmet_);
  chain_.SetBranchAddress("min_mt_bmet_with_w_mass", &min_mt_bmet_with_w_mass_, &b_min_mt_bmet_with_w_mass_);
  chain_.SetBranchAddress("min_pt_bb", &min_pt_bb_, &b_min_pt_bb_);
  chain_.SetBranchAddress("min_pt_blep", &min_pt_blep_, &b_min_pt_blep_);
  chain_.SetBranchAddress("min_pt_bmet", &min_pt_bmet_, &b_min_pt_bmet_);
  chain_.SetBranchAddress("mindphin_metjet", &mindphin_metjet_, &b_mindphin_metjet_);
  chain_.SetBranchAddress("mj15", &mj15_, &b_mj15_);
  chain_.SetBranchAddress("mj_sub", &mj_sub_, &b_mj_sub_);
  chain_.SetBranchAddress("mt_reliso", &mt_reliso_, &b_mt_reliso_);
  chain_.SetBranchAddress("st", &st_, &b_st_);
  chain_.SetBranchAddress("st_reliso", &st_reliso_, &b_st_reliso_);
  chain_.SetBranchAddress("tru_gluglu_dphi", &tru_gluglu_dphi_, &b_tru_gluglu_dphi_);
  chain_.SetBranchAddress("tru_gluglu_m", &tru_gluglu_m_, &b_tru_gluglu_m_);
  chain_.SetBranchAddress("tru_gluglu_pt", &tru_gluglu_pt_, &b_tru_gluglu_pt_);
  chain_.SetBranchAddress("tru_gluglu_ptdiff", &tru_gluglu_ptdiff_, &b_tru_gluglu_ptdiff_);
  chain_.SetBranchAddress("tru_sphericity", &tru_sphericity_, &b_tru_sphericity_);
  chain_.SetBranchAddress("tru_tt_dphi", &tru_tt_dphi_, &b_tru_tt_dphi_);
  chain_.SetBranchAddress("tru_tt_m", &tru_tt_m_, &b_tru_tt_m_);
  chain_.SetBranchAddress("tru_tt_pt", &tru_tt_pt_, &b_tru_tt_pt_);
  chain_.SetBranchAddress("tru_tt_ptdiff", &tru_tt_ptdiff_, &b_tru_tt_ptdiff_);
  chain_.SetBranchAddress("trutop1_phi", &trutop1_phi_, &b_trutop1_phi_);
  chain_.SetBranchAddress("trutop1_pt", &trutop1_pt_, &b_trutop1_pt_);
  chain_.SetBranchAddress("trutop2_phi", &trutop2_phi_, &b_trutop2_phi_);
  chain_.SetBranchAddress("trutop2_pt", &trutop2_pt_, &b_trutop2_pt_);
  chain_.SetBranchAddress("lep_charge", &lep_charge_, &b_lep_charge_);
  chain_.SetBranchAddress("lep_charge_reliso", &lep_charge_reliso_, &b_lep_charge_reliso_);
  chain_.SetBranchAddress("n_isr_me", &n_isr_me_, &b_n_isr_me_);
  chain_.SetBranchAddress("n_isr_nonme", &n_isr_nonme_, &b_n_isr_nonme_);
  chain_.SetBranchAddress("nbadjets", &nbadjets_, &b_nbadjets_);
  chain_.SetBranchAddress("nbl40", &nbl40_, &b_nbl40_);
  chain_.SetBranchAddress("nbl_sub", &nbl_sub_, &b_nbl_sub_);
  chain_.SetBranchAddress("nbm40", &nbm40_, &b_nbm40_);
  chain_.SetBranchAddress("nbm_sub", &nbm_sub_, &b_nbm_sub_);
  chain_.SetBranchAddress("nbt40", &nbt40_, &b_nbt40_);
  chain_.SetBranchAddress("nbt_sub", &nbt_sub_, &b_nbt_sub_);
  chain_.SetBranchAddress("nels_reliso", &nels_reliso_, &b_nels_reliso_);
  chain_.SetBranchAddress("nfjets15", &nfjets15_, &b_nfjets15_);
  chain_.SetBranchAddress("nfsubjets", &nfsubjets_, &b_nfsubjets_);
  chain_.SetBranchAddress("ngenfjets", &ngenfjets_, &b_ngenfjets_);
  chain_.SetBranchAddress("ngenjets", &ngenjets_, &b_ngenjets_);
  chain_.SetBranchAddress("njets40", &njets40_, &b_njets40_);
  chain_.SetBranchAddress("nleps_reliso", &nleps_reliso_, &b_nleps_reliso_);
  chain_.SetBranchAddress("nmus_reliso", &nmus_reliso_, &b_nmus_reliso_);
  chain_.SetBranchAddress("nsubjets", &nsubjets_, &b_nsubjets_);
  chain_.SetBranchAddress("ntks", &ntks_, &b_ntks_);
  chain_.SetBranchAddress("ntks_chg", &ntks_chg_, &b_ntks_chg_);
  chain_.SetBranchAddress("ntks_chg_reliso", &ntks_chg_reliso_, &b_ntks_chg_reliso_);
  chain_.SetBranchAddress("nvels_reliso", &nvels_reliso_, &b_nvels_reliso_);
  chain_.SetBranchAddress("nvmus_reliso", &nvmus_reliso_, &b_nvmus_reliso_);
  chain_.SetBranchAddress("badjets_islep", &p_badjets_islep_, &b_badjets_islep_);
  chain_.SetBranchAddress("els_tru_tm", &p_els_tru_tm_, &b_els_tru_tm_);
  chain_.SetBranchAddress("mus_tru_tm", &p_mus_tru_tm_, &b_mus_tru_tm_);
  chain_.SetBranchAddress("tks_from_tau", &p_tks_from_tau_, &b_tks_from_tau_);
  chain_.SetBranchAddress("tks_from_tauhad", &p_tks_from_tauhad_, &b_tks_from_tauhad_);
  chain_.SetBranchAddress("tks_from_taulep", &p_tks_from_taulep_, &b_tks_from_taulep_);
  chain_.SetBranchAddress("tks_from_w", &p_tks_from_w_, &b_tks_from_w_);
  chain_.SetBranchAddress("tks_is_primary", &p_tks_is_primary_, &b_tks_is_primary_);
  chain_.SetBranchAddress("tks_is_primary_reliso", &p_tks_is_primary_reliso_, &b_tks_is_primary_reliso_);
  chain_.SetBranchAddress("tks_is_sig_lep", &p_tks_is_sig_lep_, &b_tks_is_sig_lep_);
  chain_.SetBranchAddress("badjets_eta", &p_badjets_eta_, &b_badjets_eta_);
  chain_.SetBranchAddress("badjets_id", &p_badjets_id_, &b_badjets_id_);
  chain_.SetBranchAddress("badjets_m", &p_badjets_m_, &b_badjets_m_);
  chain_.SetBranchAddress("badjets_phi", &p_badjets_phi_, &b_badjets_phi_);
  chain_.SetBranchAddress("badjets_pt", &p_badjets_pt_, &b_badjets_pt_);
  chain_.SetBranchAddress("els_miniso_10", &p_els_miniso_10_, &b_els_miniso_10_);
  chain_.SetBranchAddress("els_miniso_10_ch", &p_els_miniso_10_ch_, &b_els_miniso_10_ch_);
  chain_.SetBranchAddress("els_miniso_tr10", &p_els_miniso_tr10_, &b_els_miniso_tr10_);
  chain_.SetBranchAddress("els_miniso_tr10_ch", &p_els_miniso_tr10_ch_, &b_els_miniso_tr10_ch_);
  chain_.SetBranchAddress("els_mt", &p_els_mt_, &b_els_mt_);
  chain_.SetBranchAddress("els_reliso", &p_els_reliso_, &b_els_reliso_);
  chain_.SetBranchAddress("els_reliso_r01", &p_els_reliso_r01_, &b_els_reliso_r01_);
  chain_.SetBranchAddress("els_reliso_r015", &p_els_reliso_r015_, &b_els_reliso_r015_);
  chain_.SetBranchAddress("els_reliso_r02", &p_els_reliso_r02_, &b_els_reliso_r02_);
  chain_.SetBranchAddress("els_reliso_r03", &p_els_reliso_r03_, &b_els_reliso_r03_);
  chain_.SetBranchAddress("els_reliso_r04", &p_els_reliso_r04_, &b_els_reliso_r04_);
  chain_.SetBranchAddress("els_tru_dr", &p_els_tru_dr_, &b_els_tru_dr_);
  chain_.SetBranchAddress("fjets15_eta", &p_fjets15_eta_, &b_fjets15_eta_);
  chain_.SetBranchAddress("fjets15_m", &p_fjets15_m_, &b_fjets15_m_);
  chain_.SetBranchAddress("fjets15_phi", &p_fjets15_phi_, &b_fjets15_phi_);
  chain_.SetBranchAddress("fjets15_poscsv", &p_fjets15_poscsv_, &b_fjets15_poscsv_);
  chain_.SetBranchAddress("fjets15_pt", &p_fjets15_pt_, &b_fjets15_pt_);
  chain_.SetBranchAddress("fjets15_sumcsv", &p_fjets15_sumcsv_, &b_fjets15_sumcsv_);
  chain_.SetBranchAddress("fsubjets_eta", &p_fsubjets_eta_, &b_fsubjets_eta_);
  chain_.SetBranchAddress("fsubjets_m", &p_fsubjets_m_, &b_fsubjets_m_);
  chain_.SetBranchAddress("fsubjets_phi", &p_fsubjets_phi_, &b_fsubjets_phi_);
  chain_.SetBranchAddress("fsubjets_poscsv", &p_fsubjets_poscsv_, &b_fsubjets_poscsv_);
  chain_.SetBranchAddress("fsubjets_pt", &p_fsubjets_pt_, &b_fsubjets_pt_);
  chain_.SetBranchAddress("fsubjets_sumcsv", &p_fsubjets_sumcsv_, &b_fsubjets_sumcsv_);
  chain_.SetBranchAddress("genfjets_eta", &p_genfjets_eta_, &b_genfjets_eta_);
  chain_.SetBranchAddress("genfjets_m", &p_genfjets_m_, &b_genfjets_m_);
  chain_.SetBranchAddress("genfjets_phi", &p_genfjets_phi_, &b_genfjets_phi_);
  chain_.SetBranchAddress("genfjets_pt", &p_genfjets_pt_, &b_genfjets_pt_);
  chain_.SetBranchAddress("genjets_eta", &p_genjets_eta_, &b_genjets_eta_);
  chain_.SetBranchAddress("genjets_m", &p_genjets_m_, &b_genjets_m_);
  chain_.SetBranchAddress("genjets_phi", &p_genjets_phi_, &b_genjets_phi_);
  chain_.SetBranchAddress("genjets_pt", &p_genjets_pt_, &b_genjets_pt_);
  chain_.SetBranchAddress("glu_proj_frac", &p_glu_proj_frac_, &b_glu_proj_frac_);
  chain_.SetBranchAddress("jets_gen_pt", &p_jets_gen_pt_, &b_jets_gen_pt_);
  chain_.SetBranchAddress("jets_id", &p_jets_id_, &b_jets_id_);
  chain_.SetBranchAddress("jets_parton_pt", &p_jets_parton_pt_, &b_jets_parton_pt_);
  chain_.SetBranchAddress("jets_pt_from_mini", &p_jets_pt_from_mini_, &b_jets_pt_from_mini_);
  chain_.SetBranchAddress("mc_eta", &p_mc_eta_, &b_mc_eta_);
  chain_.SetBranchAddress("mc_phi", &p_mc_phi_, &b_mc_phi_);
  chain_.SetBranchAddress("mc_pt", &p_mc_pt_, &b_mc_pt_);
  chain_.SetBranchAddress("mus_miniso_10", &p_mus_miniso_10_, &b_mus_miniso_10_);
  chain_.SetBranchAddress("mus_miniso_10_ch", &p_mus_miniso_10_ch_, &b_mus_miniso_10_ch_);
  chain_.SetBranchAddress("mus_miniso_tr10", &p_mus_miniso_tr10_, &b_mus_miniso_tr10_);
  chain_.SetBranchAddress("mus_miniso_tr10_ch", &p_mus_miniso_tr10_ch_, &b_mus_miniso_tr10_ch_);
  chain_.SetBranchAddress("mus_mt", &p_mus_mt_, &b_mus_mt_);
  chain_.SetBranchAddress("mus_reliso", &p_mus_reliso_, &b_mus_reliso_);
  chain_.SetBranchAddress("mus_reliso_r01", &p_mus_reliso_r01_, &b_mus_reliso_r01_);
  chain_.SetBranchAddress("mus_reliso_r015", &p_mus_reliso_r015_, &b_mus_reliso_r015_);
  chain_.SetBranchAddress("mus_reliso_r02", &p_mus_reliso_r02_, &b_mus_reliso_r02_);
  chain_.SetBranchAddress("mus_reliso_r03", &p_mus_reliso_r03_, &b_mus_reliso_r03_);
  chain_.SetBranchAddress("mus_reliso_r04", &p_mus_reliso_r04_, &b_mus_reliso_r04_);
  chain_.SetBranchAddress("mus_tru_dr", &p_mus_tru_dr_, &b_mus_tru_dr_);
  chain_.SetBranchAddress("subjets_csv", &p_subjets_csv_, &b_subjets_csv_);
  chain_.SetBranchAddress("subjets_eta", &p_subjets_eta_, &b_subjets_eta_);
  chain_.SetBranchAddress("subjets_id", &p_subjets_id_, &b_subjets_id_);
  chain_.SetBranchAddress("subjets_m", &p_subjets_m_, &b_subjets_m_);
  chain_.SetBranchAddress("subjets_mindr", &p_subjets_mindr_, &b_subjets_mindr_);
  chain_.SetBranchAddress("subjets_phi", &p_subjets_phi_, &b_subjets_phi_);
  chain_.SetBranchAddress("subjets_pt", &p_subjets_pt_, &b_subjets_pt_);
  chain_.SetBranchAddress("subjets_subeta", &p_subjets_subeta_, &b_subjets_subeta_);
  chain_.SetBranchAddress("subjets_subm", &p_subjets_subm_, &b_subjets_subm_);
  chain_.SetBranchAddress("subjets_subphi", &p_subjets_subphi_, &b_subjets_subphi_);
  chain_.SetBranchAddress("subjets_subpt", &p_subjets_subpt_, &b_subjets_subpt_);
  chain_.SetBranchAddress("tks_eta", &p_tks_eta_, &b_tks_eta_);
  chain_.SetBranchAddress("tks_mini_ch", &p_tks_mini_ch_, &b_tks_mini_ch_);
  chain_.SetBranchAddress("tks_mini_ne", &p_tks_mini_ne_, &b_tks_mini_ne_);
  chain_.SetBranchAddress("tks_mt", &p_tks_mt_, &b_tks_mt_);
  chain_.SetBranchAddress("tks_phi", &p_tks_phi_, &b_tks_phi_);
  chain_.SetBranchAddress("tks_pt", &p_tks_pt_, &b_tks_pt_);
  chain_.SetBranchAddress("tks_r02_ch", &p_tks_r02_ch_, &b_tks_r02_ch_);
  chain_.SetBranchAddress("tks_r02_ne", &p_tks_r02_ne_, &b_tks_r02_ne_);
  chain_.SetBranchAddress("tks_r03_ch", &p_tks_r03_ch_, &b_tks_r03_ch_);
  chain_.SetBranchAddress("tks_r03_ne", &p_tks_r03_ne_, &b_tks_r03_ne_);
  chain_.SetBranchAddress("tks_r04_ch", &p_tks_r04_ch_, &b_tks_r04_ch_);
  chain_.SetBranchAddress("tks_r04_ne", &p_tks_r04_ne_, &b_tks_r04_ne_);
  chain_.SetBranchAddress("tks_r05_ch", &p_tks_r05_ch_, &b_tks_r05_ch_);
  chain_.SetBranchAddress("tks_r05_ne", &p_tks_r05_ne_, &b_tks_r05_ne_);
  chain_.SetBranchAddress("tks_tru_dp", &p_tks_tru_dp_, &b_tks_tru_dp_);
  chain_.SetBranchAddress("tks_tru_dr", &p_tks_tru_dr_, &b_tks_tru_dr_);
  chain_.SetBranchAddress("els_tru_id", &p_els_tru_id_, &b_els_tru_id_);
  chain_.SetBranchAddress("els_tru_momid", &p_els_tru_momid_, &b_els_tru_momid_);
  chain_.SetBranchAddress("fjets15_btags", &p_fjets15_btags_, &b_fjets15_btags_);
  chain_.SetBranchAddress("fjets15_nconst", &p_fjets15_nconst_, &b_fjets15_nconst_);
  chain_.SetBranchAddress("fsubjets_btags", &p_fsubjets_btags_, &b_fsubjets_btags_);
  chain_.SetBranchAddress("fsubjets_nconst", &p_fsubjets_nconst_, &b_fsubjets_nconst_);
  chain_.SetBranchAddress("genfjets_nconst", &p_genfjets_nconst_, &b_genfjets_nconst_);
  chain_.SetBranchAddress("genjets_genfjet_index", &p_genjets_genfjet_index_, &b_genjets_genfjet_index_);
  chain_.SetBranchAddress("genjets_isr_code", &p_genjets_isr_code_, &b_genjets_isr_code_);
  chain_.SetBranchAddress("jets_fjet15_index", &p_jets_fjet15_index_, &b_jets_fjet15_index_);
  chain_.SetBranchAddress("jets_isr_code", &p_jets_isr_code_, &b_jets_isr_code_);
  chain_.SetBranchAddress("mc_id", &p_mc_id_, &b_mc_id_);
  chain_.SetBranchAddress("mc_status", &p_mc_status_, &b_mc_status_);
  chain_.SetBranchAddress("mus_tru_id", &p_mus_tru_id_, &b_mus_tru_id_);
  chain_.SetBranchAddress("mus_tru_momid", &p_mus_tru_momid_, &b_mus_tru_momid_);
  chain_.SetBranchAddress("subjets_fsubjet_index", &p_subjets_fsubjet_index_, &b_subjets_fsubjet_index_);
  chain_.SetBranchAddress("subjets_nsub", &p_subjets_nsub_, &b_subjets_nsub_);
  chain_.SetBranchAddress("tks_charge", &p_tks_charge_, &b_tks_charge_);
  chain_.SetBranchAddress("tks_from_pv", &p_tks_from_pv_, &b_tks_from_pv_);
  chain_.SetBranchAddress("tks_id", &p_tks_id_, &b_tks_id_);
  chain_.SetBranchAddress("tks_num_prongs", &p_tks_num_prongs_, &b_tks_num_prongs_);
  chain_.SetBranchAddress("tks_tru_id", &p_tks_tru_id_, &b_tks_tru_id_);
  chain_.SetBranchAddress("mc_mom", &p_mc_mom_, &b_mc_mom_);
  chain_.SetBranchAddress("mc_type", &mc_type_, &b_mc_type_);
}

void small_tree_full::Fill(){
  small_tree::Fill();
  //Resetting variables
  dphi_neutralinos_ = static_cast<float >(bad_val_);
  dphi_wlep_ = static_cast<float >(bad_val_);
  dphi_wlep_reliso_ = static_cast<float >(bad_val_);
  gen_ht_ = static_cast<float >(bad_val_);
  gen_met_ = static_cast<float >(bad_val_);
  gen_met_phi_ = static_cast<float >(bad_val_);
  gen_mj_ = static_cast<float >(bad_val_);
  ht40_ = static_cast<float >(bad_val_);
  ht_isr_ = static_cast<float >(bad_val_);
  ht_isr_me_ = static_cast<float >(bad_val_);
  ht_isr_nonme_ = static_cast<float >(bad_val_);
  ht_isr_tru_ = static_cast<float >(bad_val_);
  ht_nonb_ = static_cast<float >(bad_val_);
  ht_sub_ = static_cast<float >(bad_val_);
  lep_eta_ = static_cast<float >(bad_val_);
  lep_eta_reliso_ = static_cast<float >(bad_val_);
  lep_phi_ = static_cast<float >(bad_val_);
  lep_phi_reliso_ = static_cast<float >(bad_val_);
  lep_pt_ = static_cast<float >(bad_val_);
  lep_pt_reliso_ = static_cast<float >(bad_val_);
  max_dphi_bb_ = static_cast<float >(bad_val_);
  max_dphi_blep_ = static_cast<float >(bad_val_);
  max_dphi_bmet_ = static_cast<float >(bad_val_);
  max_dr_bb_ = static_cast<float >(bad_val_);
  max_dr_blep_ = static_cast<float >(bad_val_);
  max_m_bb_ = static_cast<float >(bad_val_);
  max_m_blep_ = static_cast<float >(bad_val_);
  max_mt_bmet_ = static_cast<float >(bad_val_);
  max_pt_bb_ = static_cast<float >(bad_val_);
  max_pt_blep_ = static_cast<float >(bad_val_);
  max_pt_bmet_ = static_cast<float >(bad_val_);
  mht_sub_ = static_cast<float >(bad_val_);
  min_dphi_bb_ = static_cast<float >(bad_val_);
  min_dphi_blep_ = static_cast<float >(bad_val_);
  min_dphi_bmet_ = static_cast<float >(bad_val_);
  min_dr_bb_ = static_cast<float >(bad_val_);
  min_dr_blep_ = static_cast<float >(bad_val_);
  min_m_bb_ = static_cast<float >(bad_val_);
  min_m_blep_ = static_cast<float >(bad_val_);
  min_mt_bmet_ = static_cast<float >(bad_val_);
  min_mt_bmet_with_w_mass_ = static_cast<float >(bad_val_);
  min_pt_bb_ = static_cast<float >(bad_val_);
  min_pt_blep_ = static_cast<float >(bad_val_);
  min_pt_bmet_ = static_cast<float >(bad_val_);
  mindphin_metjet_ = static_cast<float >(bad_val_);
  mj15_ = static_cast<float >(bad_val_);
  mj_sub_ = static_cast<float >(bad_val_);
  mt_reliso_ = static_cast<float >(bad_val_);
  st_ = static_cast<float >(bad_val_);
  st_reliso_ = static_cast<float >(bad_val_);
  tru_gluglu_dphi_ = static_cast<float >(bad_val_);
  tru_gluglu_m_ = static_cast<float >(bad_val_);
  tru_gluglu_pt_ = static_cast<float >(bad_val_);
  tru_gluglu_ptdiff_ = static_cast<float >(bad_val_);
  tru_sphericity_ = static_cast<float >(bad_val_);
  tru_tt_dphi_ = static_cast<float >(bad_val_);
  tru_tt_m_ = static_cast<float >(bad_val_);
  tru_tt_pt_ = static_cast<float >(bad_val_);
  tru_tt_ptdiff_ = static_cast<float >(bad_val_);
  trutop1_phi_ = static_cast<float >(bad_val_);
  trutop1_pt_ = static_cast<float >(bad_val_);
  trutop2_phi_ = static_cast<float >(bad_val_);
  trutop2_pt_ = static_cast<float >(bad_val_);
  lep_charge_ = static_cast<int >(bad_val_);
  lep_charge_reliso_ = static_cast<int >(bad_val_);
  n_isr_me_ = static_cast<int >(bad_val_);
  n_isr_nonme_ = static_cast<int >(bad_val_);
  nbadjets_ = static_cast<int >(bad_val_);
  nbl40_ = static_cast<int >(bad_val_);
  nbl_sub_ = static_cast<int >(bad_val_);
  nbm40_ = static_cast<int >(bad_val_);
  nbm_sub_ = static_cast<int >(bad_val_);
  nbt40_ = static_cast<int >(bad_val_);
  nbt_sub_ = static_cast<int >(bad_val_);
  nels_reliso_ = static_cast<int >(bad_val_);
  nfjets15_ = static_cast<int >(bad_val_);
  nfsubjets_ = static_cast<int >(bad_val_);
  ngenfjets_ = static_cast<int >(bad_val_);
  ngenjets_ = static_cast<int >(bad_val_);
  njets40_ = static_cast<int >(bad_val_);
  nleps_reliso_ = static_cast<int >(bad_val_);
  nmus_reliso_ = static_cast<int >(bad_val_);
  nsubjets_ = static_cast<int >(bad_val_);
  ntks_ = static_cast<int >(bad_val_);
  ntks_chg_ = static_cast<int >(bad_val_);
  ntks_chg_reliso_ = static_cast<int >(bad_val_);
  nvels_reliso_ = static_cast<int >(bad_val_);
  nvmus_reliso_ = static_cast<int >(bad_val_);
  badjets_islep_.clear();
  els_tru_tm_.clear();
  mus_tru_tm_.clear();
  tks_from_tau_.clear();
  tks_from_tauhad_.clear();
  tks_from_taulep_.clear();
  tks_from_w_.clear();
  tks_is_primary_.clear();
  tks_is_primary_reliso_.clear();
  tks_is_sig_lep_.clear();
  badjets_eta_.clear();
  badjets_id_.clear();
  badjets_m_.clear();
  badjets_phi_.clear();
  badjets_pt_.clear();
  els_miniso_10_.clear();
  els_miniso_10_ch_.clear();
  els_miniso_tr10_.clear();
  els_miniso_tr10_ch_.clear();
  els_mt_.clear();
  els_reliso_.clear();
  els_reliso_r01_.clear();
  els_reliso_r015_.clear();
  els_reliso_r02_.clear();
  els_reliso_r03_.clear();
  els_reliso_r04_.clear();
  els_tru_dr_.clear();
  fjets15_eta_.clear();
  fjets15_m_.clear();
  fjets15_phi_.clear();
  fjets15_poscsv_.clear();
  fjets15_pt_.clear();
  fjets15_sumcsv_.clear();
  fsubjets_eta_.clear();
  fsubjets_m_.clear();
  fsubjets_phi_.clear();
  fsubjets_poscsv_.clear();
  fsubjets_pt_.clear();
  fsubjets_sumcsv_.clear();
  genfjets_eta_.clear();
  genfjets_m_.clear();
  genfjets_phi_.clear();
  genfjets_pt_.clear();
  genjets_eta_.clear();
  genjets_m_.clear();
  genjets_phi_.clear();
  genjets_pt_.clear();
  glu_proj_frac_.clear();
  jets_gen_pt_.clear();
  jets_id_.clear();
  jets_parton_pt_.clear();
  jets_pt_from_mini_.clear();
  mc_eta_.clear();
  mc_phi_.clear();
  mc_pt_.clear();
  mus_miniso_10_.clear();
  mus_miniso_10_ch_.clear();
  mus_miniso_tr10_.clear();
  mus_miniso_tr10_ch_.clear();
  mus_mt_.clear();
  mus_reliso_.clear();
  mus_reliso_r01_.clear();
  mus_reliso_r015_.clear();
  mus_reliso_r02_.clear();
  mus_reliso_r03_.clear();
  mus_reliso_r04_.clear();
  mus_tru_dr_.clear();
  subjets_csv_.clear();
  subjets_eta_.clear();
  subjets_id_.clear();
  subjets_m_.clear();
  subjets_mindr_.clear();
  subjets_phi_.clear();
  subjets_pt_.clear();
  subjets_subeta_.clear();
  subjets_subm_.clear();
  subjets_subphi_.clear();
  subjets_subpt_.clear();
  tks_eta_.clear();
  tks_mini_ch_.clear();
  tks_mini_ne_.clear();
  tks_mt_.clear();
  tks_phi_.clear();
  tks_pt_.clear();
  tks_r02_ch_.clear();
  tks_r02_ne_.clear();
  tks_r03_ch_.clear();
  tks_r03_ne_.clear();
  tks_r04_ch_.clear();
  tks_r04_ne_.clear();
  tks_r05_ch_.clear();
  tks_r05_ne_.clear();
  tks_tru_dp_.clear();
  tks_tru_dr_.clear();
  els_tru_id_.clear();
  els_tru_momid_.clear();
  fjets15_btags_.clear();
  fjets15_nconst_.clear();
  fsubjets_btags_.clear();
  fsubjets_nconst_.clear();
  genfjets_nconst_.clear();
  genjets_genfjet_index_.clear();
  genjets_isr_code_.clear();
  jets_fjet15_index_.clear();
  jets_isr_code_.clear();
  mc_id_.clear();
  mc_status_.clear();
  mus_tru_id_.clear();
  mus_tru_momid_.clear();
  subjets_fsubjet_index_.clear();
  subjets_nsub_.clear();
  tks_charge_.clear();
  tks_from_pv_.clear();
  tks_id_.clear();
  tks_num_prongs_.clear();
  tks_tru_id_.clear();
  mc_mom_.clear();
  mc_type_ = static_cast<unsigned >(bad_val_);
}

string small_tree_full::Type() const{
  return "full";
}

small_tree_full::~small_tree_full(){
}

void small_tree_full::GetEntry(const long entry){
  small_tree::GetEntry(entry);

  c_dphi_neutralinos_ = false;
  c_dphi_wlep_ = false;
  c_dphi_wlep_reliso_ = false;
  c_gen_ht_ = false;
  c_gen_met_ = false;
  c_gen_met_phi_ = false;
  c_gen_mj_ = false;
  c_ht40_ = false;
  c_ht_isr_ = false;
  c_ht_isr_me_ = false;
  c_ht_isr_nonme_ = false;
  c_ht_isr_tru_ = false;
  c_ht_nonb_ = false;
  c_ht_sub_ = false;
  c_lep_eta_ = false;
  c_lep_eta_reliso_ = false;
  c_lep_phi_ = false;
  c_lep_phi_reliso_ = false;
  c_lep_pt_ = false;
  c_lep_pt_reliso_ = false;
  c_max_dphi_bb_ = false;
  c_max_dphi_blep_ = false;
  c_max_dphi_bmet_ = false;
  c_max_dr_bb_ = false;
  c_max_dr_blep_ = false;
  c_max_m_bb_ = false;
  c_max_m_blep_ = false;
  c_max_mt_bmet_ = false;
  c_max_pt_bb_ = false;
  c_max_pt_blep_ = false;
  c_max_pt_bmet_ = false;
  c_mht_sub_ = false;
  c_min_dphi_bb_ = false;
  c_min_dphi_blep_ = false;
  c_min_dphi_bmet_ = false;
  c_min_dr_bb_ = false;
  c_min_dr_blep_ = false;
  c_min_m_bb_ = false;
  c_min_m_blep_ = false;
  c_min_mt_bmet_ = false;
  c_min_mt_bmet_with_w_mass_ = false;
  c_min_pt_bb_ = false;
  c_min_pt_blep_ = false;
  c_min_pt_bmet_ = false;
  c_mindphin_metjet_ = false;
  c_mj15_ = false;
  c_mj_sub_ = false;
  c_mt_reliso_ = false;
  c_st_ = false;
  c_st_reliso_ = false;
  c_tru_gluglu_dphi_ = false;
  c_tru_gluglu_m_ = false;
  c_tru_gluglu_pt_ = false;
  c_tru_gluglu_ptdiff_ = false;
  c_tru_sphericity_ = false;
  c_tru_tt_dphi_ = false;
  c_tru_tt_m_ = false;
  c_tru_tt_pt_ = false;
  c_tru_tt_ptdiff_ = false;
  c_trutop1_phi_ = false;
  c_trutop1_pt_ = false;
  c_trutop2_phi_ = false;
  c_trutop2_pt_ = false;
  c_lep_charge_ = false;
  c_lep_charge_reliso_ = false;
  c_n_isr_me_ = false;
  c_n_isr_nonme_ = false;
  c_nbadjets_ = false;
  c_nbl40_ = false;
  c_nbl_sub_ = false;
  c_nbm40_ = false;
  c_nbm_sub_ = false;
  c_nbt40_ = false;
  c_nbt_sub_ = false;
  c_nels_reliso_ = false;
  c_nfjets15_ = false;
  c_nfsubjets_ = false;
  c_ngenfjets_ = false;
  c_ngenjets_ = false;
  c_njets40_ = false;
  c_nleps_reliso_ = false;
  c_nmus_reliso_ = false;
  c_nsubjets_ = false;
  c_ntks_ = false;
  c_ntks_chg_ = false;
  c_ntks_chg_reliso_ = false;
  c_nvels_reliso_ = false;
  c_nvmus_reliso_ = false;
  c_badjets_islep_ = false;
  c_els_tru_tm_ = false;
  c_mus_tru_tm_ = false;
  c_tks_from_tau_ = false;
  c_tks_from_tauhad_ = false;
  c_tks_from_taulep_ = false;
  c_tks_from_w_ = false;
  c_tks_is_primary_ = false;
  c_tks_is_primary_reliso_ = false;
  c_tks_is_sig_lep_ = false;
  c_badjets_eta_ = false;
  c_badjets_id_ = false;
  c_badjets_m_ = false;
  c_badjets_phi_ = false;
  c_badjets_pt_ = false;
  c_els_miniso_10_ = false;
  c_els_miniso_10_ch_ = false;
  c_els_miniso_tr10_ = false;
  c_els_miniso_tr10_ch_ = false;
  c_els_mt_ = false;
  c_els_reliso_ = false;
  c_els_reliso_r01_ = false;
  c_els_reliso_r015_ = false;
  c_els_reliso_r02_ = false;
  c_els_reliso_r03_ = false;
  c_els_reliso_r04_ = false;
  c_els_tru_dr_ = false;
  c_fjets15_eta_ = false;
  c_fjets15_m_ = false;
  c_fjets15_phi_ = false;
  c_fjets15_poscsv_ = false;
  c_fjets15_pt_ = false;
  c_fjets15_sumcsv_ = false;
  c_fsubjets_eta_ = false;
  c_fsubjets_m_ = false;
  c_fsubjets_phi_ = false;
  c_fsubjets_poscsv_ = false;
  c_fsubjets_pt_ = false;
  c_fsubjets_sumcsv_ = false;
  c_genfjets_eta_ = false;
  c_genfjets_m_ = false;
  c_genfjets_phi_ = false;
  c_genfjets_pt_ = false;
  c_genjets_eta_ = false;
  c_genjets_m_ = false;
  c_genjets_phi_ = false;
  c_genjets_pt_ = false;
  c_glu_proj_frac_ = false;
  c_jets_gen_pt_ = false;
  c_jets_id_ = false;
  c_jets_parton_pt_ = false;
  c_jets_pt_from_mini_ = false;
  c_mc_eta_ = false;
  c_mc_phi_ = false;
  c_mc_pt_ = false;
  c_mus_miniso_10_ = false;
  c_mus_miniso_10_ch_ = false;
  c_mus_miniso_tr10_ = false;
  c_mus_miniso_tr10_ch_ = false;
  c_mus_mt_ = false;
  c_mus_reliso_ = false;
  c_mus_reliso_r01_ = false;
  c_mus_reliso_r015_ = false;
  c_mus_reliso_r02_ = false;
  c_mus_reliso_r03_ = false;
  c_mus_reliso_r04_ = false;
  c_mus_tru_dr_ = false;
  c_subjets_csv_ = false;
  c_subjets_eta_ = false;
  c_subjets_id_ = false;
  c_subjets_m_ = false;
  c_subjets_mindr_ = false;
  c_subjets_phi_ = false;
  c_subjets_pt_ = false;
  c_subjets_subeta_ = false;
  c_subjets_subm_ = false;
  c_subjets_subphi_ = false;
  c_subjets_subpt_ = false;
  c_tks_eta_ = false;
  c_tks_mini_ch_ = false;
  c_tks_mini_ne_ = false;
  c_tks_mt_ = false;
  c_tks_phi_ = false;
  c_tks_pt_ = false;
  c_tks_r02_ch_ = false;
  c_tks_r02_ne_ = false;
  c_tks_r03_ch_ = false;
  c_tks_r03_ne_ = false;
  c_tks_r04_ch_ = false;
  c_tks_r04_ne_ = false;
  c_tks_r05_ch_ = false;
  c_tks_r05_ne_ = false;
  c_tks_tru_dp_ = false;
  c_tks_tru_dr_ = false;
  c_els_tru_id_ = false;
  c_els_tru_momid_ = false;
  c_fjets15_btags_ = false;
  c_fjets15_nconst_ = false;
  c_fsubjets_btags_ = false;
  c_fsubjets_nconst_ = false;
  c_genfjets_nconst_ = false;
  c_genjets_genfjet_index_ = false;
  c_genjets_isr_code_ = false;
  c_jets_fjet15_index_ = false;
  c_jets_isr_code_ = false;
  c_mc_id_ = false;
  c_mc_status_ = false;
  c_mus_tru_id_ = false;
  c_mus_tru_momid_ = false;
  c_subjets_fsubjet_index_ = false;
  c_subjets_nsub_ = false;
  c_tks_charge_ = false;
  c_tks_from_pv_ = false;
  c_tks_id_ = false;
  c_tks_num_prongs_ = false;
  c_tks_tru_id_ = false;
  c_mc_mom_ = false;
  c_mc_type_ = false;
}

float  const & small_tree_full::dphi_neutralinos() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dphi_neutralinos_ && b_dphi_neutralinos_){
    b_dphi_neutralinos_->GetEntry(entry_);
    c_dphi_neutralinos_ = true;
  }
  return dphi_neutralinos_;
}

float  const & small_tree_full::dphi_wlep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dphi_wlep_ && b_dphi_wlep_){
    b_dphi_wlep_->GetEntry(entry_);
    c_dphi_wlep_ = true;
  }
  return dphi_wlep_;
}

float  const & small_tree_full::dphi_wlep_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dphi_wlep_reliso_ && b_dphi_wlep_reliso_){
    b_dphi_wlep_reliso_->GetEntry(entry_);
    c_dphi_wlep_reliso_ = true;
  }
  return dphi_wlep_reliso_;
}

float  const & small_tree_full::gen_ht() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_gen_ht_ && b_gen_ht_){
    b_gen_ht_->GetEntry(entry_);
    c_gen_ht_ = true;
  }
  return gen_ht_;
}

float  const & small_tree_full::gen_met() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_gen_met_ && b_gen_met_){
    b_gen_met_->GetEntry(entry_);
    c_gen_met_ = true;
  }
  return gen_met_;
}

float  const & small_tree_full::gen_met_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_gen_met_phi_ && b_gen_met_phi_){
    b_gen_met_phi_->GetEntry(entry_);
    c_gen_met_phi_ = true;
  }
  return gen_met_phi_;
}

float  const & small_tree_full::gen_mj() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_gen_mj_ && b_gen_mj_){
    b_gen_mj_->GetEntry(entry_);
    c_gen_mj_ = true;
  }
  return gen_mj_;
}

float  const & small_tree_full::ht40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht40_ && b_ht40_){
    b_ht40_->GetEntry(entry_);
    c_ht40_ = true;
  }
  return ht40_;
}

float  const & small_tree_full::ht_isr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_isr_ && b_ht_isr_){
    b_ht_isr_->GetEntry(entry_);
    c_ht_isr_ = true;
  }
  return ht_isr_;
}

float  const & small_tree_full::ht_isr_me() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_isr_me_ && b_ht_isr_me_){
    b_ht_isr_me_->GetEntry(entry_);
    c_ht_isr_me_ = true;
  }
  return ht_isr_me_;
}

float  const & small_tree_full::ht_isr_nonme() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_isr_nonme_ && b_ht_isr_nonme_){
    b_ht_isr_nonme_->GetEntry(entry_);
    c_ht_isr_nonme_ = true;
  }
  return ht_isr_nonme_;
}

float  const & small_tree_full::ht_isr_tru() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_isr_tru_ && b_ht_isr_tru_){
    b_ht_isr_tru_->GetEntry(entry_);
    c_ht_isr_tru_ = true;
  }
  return ht_isr_tru_;
}

float  const & small_tree_full::ht_nonb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_nonb_ && b_ht_nonb_){
    b_ht_nonb_->GetEntry(entry_);
    c_ht_nonb_ = true;
  }
  return ht_nonb_;
}

float  const & small_tree_full::ht_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ht_sub_ && b_ht_sub_){
    b_ht_sub_->GetEntry(entry_);
    c_ht_sub_ = true;
  }
  return ht_sub_;
}

float  const & small_tree_full::lep_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_eta_ && b_lep_eta_){
    b_lep_eta_->GetEntry(entry_);
    c_lep_eta_ = true;
  }
  return lep_eta_;
}

float  const & small_tree_full::lep_eta_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_eta_reliso_ && b_lep_eta_reliso_){
    b_lep_eta_reliso_->GetEntry(entry_);
    c_lep_eta_reliso_ = true;
  }
  return lep_eta_reliso_;
}

float  const & small_tree_full::lep_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_phi_ && b_lep_phi_){
    b_lep_phi_->GetEntry(entry_);
    c_lep_phi_ = true;
  }
  return lep_phi_;
}

float  const & small_tree_full::lep_phi_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_phi_reliso_ && b_lep_phi_reliso_){
    b_lep_phi_reliso_->GetEntry(entry_);
    c_lep_phi_reliso_ = true;
  }
  return lep_phi_reliso_;
}

float  const & small_tree_full::lep_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_pt_ && b_lep_pt_){
    b_lep_pt_->GetEntry(entry_);
    c_lep_pt_ = true;
  }
  return lep_pt_;
}

float  const & small_tree_full::lep_pt_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_pt_reliso_ && b_lep_pt_reliso_){
    b_lep_pt_reliso_->GetEntry(entry_);
    c_lep_pt_reliso_ = true;
  }
  return lep_pt_reliso_;
}

float  const & small_tree_full::max_dphi_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_dphi_bb_ && b_max_dphi_bb_){
    b_max_dphi_bb_->GetEntry(entry_);
    c_max_dphi_bb_ = true;
  }
  return max_dphi_bb_;
}

float  const & small_tree_full::max_dphi_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_dphi_blep_ && b_max_dphi_blep_){
    b_max_dphi_blep_->GetEntry(entry_);
    c_max_dphi_blep_ = true;
  }
  return max_dphi_blep_;
}

float  const & small_tree_full::max_dphi_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_dphi_bmet_ && b_max_dphi_bmet_){
    b_max_dphi_bmet_->GetEntry(entry_);
    c_max_dphi_bmet_ = true;
  }
  return max_dphi_bmet_;
}

float  const & small_tree_full::max_dr_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_dr_bb_ && b_max_dr_bb_){
    b_max_dr_bb_->GetEntry(entry_);
    c_max_dr_bb_ = true;
  }
  return max_dr_bb_;
}

float  const & small_tree_full::max_dr_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_dr_blep_ && b_max_dr_blep_){
    b_max_dr_blep_->GetEntry(entry_);
    c_max_dr_blep_ = true;
  }
  return max_dr_blep_;
}

float  const & small_tree_full::max_m_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_m_bb_ && b_max_m_bb_){
    b_max_m_bb_->GetEntry(entry_);
    c_max_m_bb_ = true;
  }
  return max_m_bb_;
}

float  const & small_tree_full::max_m_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_m_blep_ && b_max_m_blep_){
    b_max_m_blep_->GetEntry(entry_);
    c_max_m_blep_ = true;
  }
  return max_m_blep_;
}

float  const & small_tree_full::max_mt_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_mt_bmet_ && b_max_mt_bmet_){
    b_max_mt_bmet_->GetEntry(entry_);
    c_max_mt_bmet_ = true;
  }
  return max_mt_bmet_;
}

float  const & small_tree_full::max_pt_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_pt_bb_ && b_max_pt_bb_){
    b_max_pt_bb_->GetEntry(entry_);
    c_max_pt_bb_ = true;
  }
  return max_pt_bb_;
}

float  const & small_tree_full::max_pt_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_pt_blep_ && b_max_pt_blep_){
    b_max_pt_blep_->GetEntry(entry_);
    c_max_pt_blep_ = true;
  }
  return max_pt_blep_;
}

float  const & small_tree_full::max_pt_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_max_pt_bmet_ && b_max_pt_bmet_){
    b_max_pt_bmet_->GetEntry(entry_);
    c_max_pt_bmet_ = true;
  }
  return max_pt_bmet_;
}

float  const & small_tree_full::mht_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mht_sub_ && b_mht_sub_){
    b_mht_sub_->GetEntry(entry_);
    c_mht_sub_ = true;
  }
  return mht_sub_;
}

float  const & small_tree_full::min_dphi_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_dphi_bb_ && b_min_dphi_bb_){
    b_min_dphi_bb_->GetEntry(entry_);
    c_min_dphi_bb_ = true;
  }
  return min_dphi_bb_;
}

float  const & small_tree_full::min_dphi_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_dphi_blep_ && b_min_dphi_blep_){
    b_min_dphi_blep_->GetEntry(entry_);
    c_min_dphi_blep_ = true;
  }
  return min_dphi_blep_;
}

float  const & small_tree_full::min_dphi_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_dphi_bmet_ && b_min_dphi_bmet_){
    b_min_dphi_bmet_->GetEntry(entry_);
    c_min_dphi_bmet_ = true;
  }
  return min_dphi_bmet_;
}

float  const & small_tree_full::min_dr_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_dr_bb_ && b_min_dr_bb_){
    b_min_dr_bb_->GetEntry(entry_);
    c_min_dr_bb_ = true;
  }
  return min_dr_bb_;
}

float  const & small_tree_full::min_dr_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_dr_blep_ && b_min_dr_blep_){
    b_min_dr_blep_->GetEntry(entry_);
    c_min_dr_blep_ = true;
  }
  return min_dr_blep_;
}

float  const & small_tree_full::min_m_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_m_bb_ && b_min_m_bb_){
    b_min_m_bb_->GetEntry(entry_);
    c_min_m_bb_ = true;
  }
  return min_m_bb_;
}

float  const & small_tree_full::min_m_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_m_blep_ && b_min_m_blep_){
    b_min_m_blep_->GetEntry(entry_);
    c_min_m_blep_ = true;
  }
  return min_m_blep_;
}

float  const & small_tree_full::min_mt_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_mt_bmet_ && b_min_mt_bmet_){
    b_min_mt_bmet_->GetEntry(entry_);
    c_min_mt_bmet_ = true;
  }
  return min_mt_bmet_;
}

float  const & small_tree_full::min_mt_bmet_with_w_mass() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_mt_bmet_with_w_mass_ && b_min_mt_bmet_with_w_mass_){
    b_min_mt_bmet_with_w_mass_->GetEntry(entry_);
    c_min_mt_bmet_with_w_mass_ = true;
  }
  return min_mt_bmet_with_w_mass_;
}

float  const & small_tree_full::min_pt_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_pt_bb_ && b_min_pt_bb_){
    b_min_pt_bb_->GetEntry(entry_);
    c_min_pt_bb_ = true;
  }
  return min_pt_bb_;
}

float  const & small_tree_full::min_pt_blep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_pt_blep_ && b_min_pt_blep_){
    b_min_pt_blep_->GetEntry(entry_);
    c_min_pt_blep_ = true;
  }
  return min_pt_blep_;
}

float  const & small_tree_full::min_pt_bmet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_min_pt_bmet_ && b_min_pt_bmet_){
    b_min_pt_bmet_->GetEntry(entry_);
    c_min_pt_bmet_ = true;
  }
  return min_pt_bmet_;
}

float  const & small_tree_full::mindphin_metjet() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mindphin_metjet_ && b_mindphin_metjet_){
    b_mindphin_metjet_->GetEntry(entry_);
    c_mindphin_metjet_ = true;
  }
  return mindphin_metjet_;
}

float  const & small_tree_full::mj15() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mj15_ && b_mj15_){
    b_mj15_->GetEntry(entry_);
    c_mj15_ = true;
  }
  return mj15_;
}

float  const & small_tree_full::mj_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mj_sub_ && b_mj_sub_){
    b_mj_sub_->GetEntry(entry_);
    c_mj_sub_ = true;
  }
  return mj_sub_;
}

float  const & small_tree_full::mt_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mt_reliso_ && b_mt_reliso_){
    b_mt_reliso_->GetEntry(entry_);
    c_mt_reliso_ = true;
  }
  return mt_reliso_;
}

float  const & small_tree_full::st() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_st_ && b_st_){
    b_st_->GetEntry(entry_);
    c_st_ = true;
  }
  return st_;
}

float  const & small_tree_full::st_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_st_reliso_ && b_st_reliso_){
    b_st_reliso_->GetEntry(entry_);
    c_st_reliso_ = true;
  }
  return st_reliso_;
}

float  const & small_tree_full::tru_gluglu_dphi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_gluglu_dphi_ && b_tru_gluglu_dphi_){
    b_tru_gluglu_dphi_->GetEntry(entry_);
    c_tru_gluglu_dphi_ = true;
  }
  return tru_gluglu_dphi_;
}

float  const & small_tree_full::tru_gluglu_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_gluglu_m_ && b_tru_gluglu_m_){
    b_tru_gluglu_m_->GetEntry(entry_);
    c_tru_gluglu_m_ = true;
  }
  return tru_gluglu_m_;
}

float  const & small_tree_full::tru_gluglu_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_gluglu_pt_ && b_tru_gluglu_pt_){
    b_tru_gluglu_pt_->GetEntry(entry_);
    c_tru_gluglu_pt_ = true;
  }
  return tru_gluglu_pt_;
}

float  const & small_tree_full::tru_gluglu_ptdiff() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_gluglu_ptdiff_ && b_tru_gluglu_ptdiff_){
    b_tru_gluglu_ptdiff_->GetEntry(entry_);
    c_tru_gluglu_ptdiff_ = true;
  }
  return tru_gluglu_ptdiff_;
}

float  const & small_tree_full::tru_sphericity() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_sphericity_ && b_tru_sphericity_){
    b_tru_sphericity_->GetEntry(entry_);
    c_tru_sphericity_ = true;
  }
  return tru_sphericity_;
}

float  const & small_tree_full::tru_tt_dphi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_tt_dphi_ && b_tru_tt_dphi_){
    b_tru_tt_dphi_->GetEntry(entry_);
    c_tru_tt_dphi_ = true;
  }
  return tru_tt_dphi_;
}

float  const & small_tree_full::tru_tt_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_tt_m_ && b_tru_tt_m_){
    b_tru_tt_m_->GetEntry(entry_);
    c_tru_tt_m_ = true;
  }
  return tru_tt_m_;
}

float  const & small_tree_full::tru_tt_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_tt_pt_ && b_tru_tt_pt_){
    b_tru_tt_pt_->GetEntry(entry_);
    c_tru_tt_pt_ = true;
  }
  return tru_tt_pt_;
}

float  const & small_tree_full::tru_tt_ptdiff() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tru_tt_ptdiff_ && b_tru_tt_ptdiff_){
    b_tru_tt_ptdiff_->GetEntry(entry_);
    c_tru_tt_ptdiff_ = true;
  }
  return tru_tt_ptdiff_;
}

float  const & small_tree_full::trutop1_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop1_phi_ && b_trutop1_phi_){
    b_trutop1_phi_->GetEntry(entry_);
    c_trutop1_phi_ = true;
  }
  return trutop1_phi_;
}

float  const & small_tree_full::trutop1_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop1_pt_ && b_trutop1_pt_){
    b_trutop1_pt_->GetEntry(entry_);
    c_trutop1_pt_ = true;
  }
  return trutop1_pt_;
}

float  const & small_tree_full::trutop2_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop2_phi_ && b_trutop2_phi_){
    b_trutop2_phi_->GetEntry(entry_);
    c_trutop2_phi_ = true;
  }
  return trutop2_phi_;
}

float  const & small_tree_full::trutop2_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trutop2_pt_ && b_trutop2_pt_){
    b_trutop2_pt_->GetEntry(entry_);
    c_trutop2_pt_ = true;
  }
  return trutop2_pt_;
}

int  const & small_tree_full::lep_charge() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_charge_ && b_lep_charge_){
    b_lep_charge_->GetEntry(entry_);
    c_lep_charge_ = true;
  }
  return lep_charge_;
}

int  const & small_tree_full::lep_charge_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_lep_charge_reliso_ && b_lep_charge_reliso_){
    b_lep_charge_reliso_->GetEntry(entry_);
    c_lep_charge_reliso_ = true;
  }
  return lep_charge_reliso_;
}

int  const & small_tree_full::n_isr_me() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_n_isr_me_ && b_n_isr_me_){
    b_n_isr_me_->GetEntry(entry_);
    c_n_isr_me_ = true;
  }
  return n_isr_me_;
}

int  const & small_tree_full::n_isr_nonme() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_n_isr_nonme_ && b_n_isr_nonme_){
    b_n_isr_nonme_->GetEntry(entry_);
    c_n_isr_nonme_ = true;
  }
  return n_isr_nonme_;
}

int  const & small_tree_full::nbadjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbadjets_ && b_nbadjets_){
    b_nbadjets_->GetEntry(entry_);
    c_nbadjets_ = true;
  }
  return nbadjets_;
}

int  const & small_tree_full::nbl40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbl40_ && b_nbl40_){
    b_nbl40_->GetEntry(entry_);
    c_nbl40_ = true;
  }
  return nbl40_;
}

int  const & small_tree_full::nbl_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbl_sub_ && b_nbl_sub_){
    b_nbl_sub_->GetEntry(entry_);
    c_nbl_sub_ = true;
  }
  return nbl_sub_;
}

int  const & small_tree_full::nbm40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbm40_ && b_nbm40_){
    b_nbm40_->GetEntry(entry_);
    c_nbm40_ = true;
  }
  return nbm40_;
}

int  const & small_tree_full::nbm_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbm_sub_ && b_nbm_sub_){
    b_nbm_sub_->GetEntry(entry_);
    c_nbm_sub_ = true;
  }
  return nbm_sub_;
}

int  const & small_tree_full::nbt40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbt40_ && b_nbt40_){
    b_nbt40_->GetEntry(entry_);
    c_nbt40_ = true;
  }
  return nbt40_;
}

int  const & small_tree_full::nbt_sub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nbt_sub_ && b_nbt_sub_){
    b_nbt_sub_->GetEntry(entry_);
    c_nbt_sub_ = true;
  }
  return nbt_sub_;
}

int  const & small_tree_full::nels_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nels_reliso_ && b_nels_reliso_){
    b_nels_reliso_->GetEntry(entry_);
    c_nels_reliso_ = true;
  }
  return nels_reliso_;
}

int  const & small_tree_full::nfjets15() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nfjets15_ && b_nfjets15_){
    b_nfjets15_->GetEntry(entry_);
    c_nfjets15_ = true;
  }
  return nfjets15_;
}

int  const & small_tree_full::nfsubjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nfsubjets_ && b_nfsubjets_){
    b_nfsubjets_->GetEntry(entry_);
    c_nfsubjets_ = true;
  }
  return nfsubjets_;
}

int  const & small_tree_full::ngenfjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ngenfjets_ && b_ngenfjets_){
    b_ngenfjets_->GetEntry(entry_);
    c_ngenfjets_ = true;
  }
  return ngenfjets_;
}

int  const & small_tree_full::ngenjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ngenjets_ && b_ngenjets_){
    b_ngenjets_->GetEntry(entry_);
    c_ngenjets_ = true;
  }
  return ngenjets_;
}

int  const & small_tree_full::njets40() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_njets40_ && b_njets40_){
    b_njets40_->GetEntry(entry_);
    c_njets40_ = true;
  }
  return njets40_;
}

int  const & small_tree_full::nleps_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nleps_reliso_ && b_nleps_reliso_){
    b_nleps_reliso_->GetEntry(entry_);
    c_nleps_reliso_ = true;
  }
  return nleps_reliso_;
}

int  const & small_tree_full::nmus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nmus_reliso_ && b_nmus_reliso_){
    b_nmus_reliso_->GetEntry(entry_);
    c_nmus_reliso_ = true;
  }
  return nmus_reliso_;
}

int  const & small_tree_full::nsubjets() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nsubjets_ && b_nsubjets_){
    b_nsubjets_->GetEntry(entry_);
    c_nsubjets_ = true;
  }
  return nsubjets_;
}

int  const & small_tree_full::ntks() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntks_ && b_ntks_){
    b_ntks_->GetEntry(entry_);
    c_ntks_ = true;
  }
  return ntks_;
}

int  const & small_tree_full::ntks_chg() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntks_chg_ && b_ntks_chg_){
    b_ntks_chg_->GetEntry(entry_);
    c_ntks_chg_ = true;
  }
  return ntks_chg_;
}

int  const & small_tree_full::ntks_chg_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_ntks_chg_reliso_ && b_ntks_chg_reliso_){
    b_ntks_chg_reliso_->GetEntry(entry_);
    c_ntks_chg_reliso_ = true;
  }
  return ntks_chg_reliso_;
}

int  const & small_tree_full::nvels_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvels_reliso_ && b_nvels_reliso_){
    b_nvels_reliso_->GetEntry(entry_);
    c_nvels_reliso_ = true;
  }
  return nvels_reliso_;
}

int  const & small_tree_full::nvmus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_nvmus_reliso_ && b_nvmus_reliso_){
    b_nvmus_reliso_->GetEntry(entry_);
    c_nvmus_reliso_ = true;
  }
  return nvmus_reliso_;
}

std::vector<bool>  const & small_tree_full::badjets_islep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_islep_ && b_badjets_islep_){
    b_badjets_islep_->GetEntry(entry_);
    c_badjets_islep_ = true;
  }
  return badjets_islep_;
}

std::vector<bool>  const & small_tree_full::els_tru_tm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_tm_ && b_els_tru_tm_){
    b_els_tru_tm_->GetEntry(entry_);
    c_els_tru_tm_ = true;
  }
  return els_tru_tm_;
}

std::vector<bool>  const & small_tree_full::mus_tru_tm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_tm_ && b_mus_tru_tm_){
    b_mus_tru_tm_->GetEntry(entry_);
    c_mus_tru_tm_ = true;
  }
  return mus_tru_tm_;
}

std::vector<bool>  const & small_tree_full::tks_from_tau() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_from_tau_ && b_tks_from_tau_){
    b_tks_from_tau_->GetEntry(entry_);
    c_tks_from_tau_ = true;
  }
  return tks_from_tau_;
}

std::vector<bool>  const & small_tree_full::tks_from_tauhad() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_from_tauhad_ && b_tks_from_tauhad_){
    b_tks_from_tauhad_->GetEntry(entry_);
    c_tks_from_tauhad_ = true;
  }
  return tks_from_tauhad_;
}

std::vector<bool>  const & small_tree_full::tks_from_taulep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_from_taulep_ && b_tks_from_taulep_){
    b_tks_from_taulep_->GetEntry(entry_);
    c_tks_from_taulep_ = true;
  }
  return tks_from_taulep_;
}

std::vector<bool>  const & small_tree_full::tks_from_w() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_from_w_ && b_tks_from_w_){
    b_tks_from_w_->GetEntry(entry_);
    c_tks_from_w_ = true;
  }
  return tks_from_w_;
}

std::vector<bool>  const & small_tree_full::tks_is_primary() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_is_primary_ && b_tks_is_primary_){
    b_tks_is_primary_->GetEntry(entry_);
    c_tks_is_primary_ = true;
  }
  return tks_is_primary_;
}

std::vector<bool>  const & small_tree_full::tks_is_primary_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_is_primary_reliso_ && b_tks_is_primary_reliso_){
    b_tks_is_primary_reliso_->GetEntry(entry_);
    c_tks_is_primary_reliso_ = true;
  }
  return tks_is_primary_reliso_;
}

std::vector<bool>  const & small_tree_full::tks_is_sig_lep() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_is_sig_lep_ && b_tks_is_sig_lep_){
    b_tks_is_sig_lep_->GetEntry(entry_);
    c_tks_is_sig_lep_ = true;
  }
  return tks_is_sig_lep_;
}

std::vector<float>  const & small_tree_full::badjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_eta_ && b_badjets_eta_){
    b_badjets_eta_->GetEntry(entry_);
    c_badjets_eta_ = true;
  }
  return badjets_eta_;
}

std::vector<float>  const & small_tree_full::badjets_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_id_ && b_badjets_id_){
    b_badjets_id_->GetEntry(entry_);
    c_badjets_id_ = true;
  }
  return badjets_id_;
}

std::vector<float>  const & small_tree_full::badjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_m_ && b_badjets_m_){
    b_badjets_m_->GetEntry(entry_);
    c_badjets_m_ = true;
  }
  return badjets_m_;
}

std::vector<float>  const & small_tree_full::badjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_phi_ && b_badjets_phi_){
    b_badjets_phi_->GetEntry(entry_);
    c_badjets_phi_ = true;
  }
  return badjets_phi_;
}

std::vector<float>  const & small_tree_full::badjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_badjets_pt_ && b_badjets_pt_){
    b_badjets_pt_->GetEntry(entry_);
    c_badjets_pt_ = true;
  }
  return badjets_pt_;
}

std::vector<float>  const & small_tree_full::els_miniso_10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_miniso_10_ && b_els_miniso_10_){
    b_els_miniso_10_->GetEntry(entry_);
    c_els_miniso_10_ = true;
  }
  return els_miniso_10_;
}

std::vector<float>  const & small_tree_full::els_miniso_10_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_miniso_10_ch_ && b_els_miniso_10_ch_){
    b_els_miniso_10_ch_->GetEntry(entry_);
    c_els_miniso_10_ch_ = true;
  }
  return els_miniso_10_ch_;
}

std::vector<float>  const & small_tree_full::els_miniso_tr10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_miniso_tr10_ && b_els_miniso_tr10_){
    b_els_miniso_tr10_->GetEntry(entry_);
    c_els_miniso_tr10_ = true;
  }
  return els_miniso_tr10_;
}

std::vector<float>  const & small_tree_full::els_miniso_tr10_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_miniso_tr10_ch_ && b_els_miniso_tr10_ch_){
    b_els_miniso_tr10_ch_->GetEntry(entry_);
    c_els_miniso_tr10_ch_ = true;
  }
  return els_miniso_tr10_ch_;
}

std::vector<float>  const & small_tree_full::els_mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_mt_ && b_els_mt_){
    b_els_mt_->GetEntry(entry_);
    c_els_mt_ = true;
  }
  return els_mt_;
}

std::vector<float>  const & small_tree_full::els_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_ && b_els_reliso_){
    b_els_reliso_->GetEntry(entry_);
    c_els_reliso_ = true;
  }
  return els_reliso_;
}

std::vector<float>  const & small_tree_full::els_reliso_r01() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_r01_ && b_els_reliso_r01_){
    b_els_reliso_r01_->GetEntry(entry_);
    c_els_reliso_r01_ = true;
  }
  return els_reliso_r01_;
}

std::vector<float>  const & small_tree_full::els_reliso_r015() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_r015_ && b_els_reliso_r015_){
    b_els_reliso_r015_->GetEntry(entry_);
    c_els_reliso_r015_ = true;
  }
  return els_reliso_r015_;
}

std::vector<float>  const & small_tree_full::els_reliso_r02() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_r02_ && b_els_reliso_r02_){
    b_els_reliso_r02_->GetEntry(entry_);
    c_els_reliso_r02_ = true;
  }
  return els_reliso_r02_;
}

std::vector<float>  const & small_tree_full::els_reliso_r03() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_r03_ && b_els_reliso_r03_){
    b_els_reliso_r03_->GetEntry(entry_);
    c_els_reliso_r03_ = true;
  }
  return els_reliso_r03_;
}

std::vector<float>  const & small_tree_full::els_reliso_r04() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_reliso_r04_ && b_els_reliso_r04_){
    b_els_reliso_r04_->GetEntry(entry_);
    c_els_reliso_r04_ = true;
  }
  return els_reliso_r04_;
}

std::vector<float>  const & small_tree_full::els_tru_dr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_dr_ && b_els_tru_dr_){
    b_els_tru_dr_->GetEntry(entry_);
    c_els_tru_dr_ = true;
  }
  return els_tru_dr_;
}

std::vector<float>  const & small_tree_full::fjets15_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_eta_ && b_fjets15_eta_){
    b_fjets15_eta_->GetEntry(entry_);
    c_fjets15_eta_ = true;
  }
  return fjets15_eta_;
}

std::vector<float>  const & small_tree_full::fjets15_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_m_ && b_fjets15_m_){
    b_fjets15_m_->GetEntry(entry_);
    c_fjets15_m_ = true;
  }
  return fjets15_m_;
}

std::vector<float>  const & small_tree_full::fjets15_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_phi_ && b_fjets15_phi_){
    b_fjets15_phi_->GetEntry(entry_);
    c_fjets15_phi_ = true;
  }
  return fjets15_phi_;
}

std::vector<float>  const & small_tree_full::fjets15_poscsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_poscsv_ && b_fjets15_poscsv_){
    b_fjets15_poscsv_->GetEntry(entry_);
    c_fjets15_poscsv_ = true;
  }
  return fjets15_poscsv_;
}

std::vector<float>  const & small_tree_full::fjets15_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_pt_ && b_fjets15_pt_){
    b_fjets15_pt_->GetEntry(entry_);
    c_fjets15_pt_ = true;
  }
  return fjets15_pt_;
}

std::vector<float>  const & small_tree_full::fjets15_sumcsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_sumcsv_ && b_fjets15_sumcsv_){
    b_fjets15_sumcsv_->GetEntry(entry_);
    c_fjets15_sumcsv_ = true;
  }
  return fjets15_sumcsv_;
}

std::vector<float>  const & small_tree_full::fsubjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_eta_ && b_fsubjets_eta_){
    b_fsubjets_eta_->GetEntry(entry_);
    c_fsubjets_eta_ = true;
  }
  return fsubjets_eta_;
}

std::vector<float>  const & small_tree_full::fsubjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_m_ && b_fsubjets_m_){
    b_fsubjets_m_->GetEntry(entry_);
    c_fsubjets_m_ = true;
  }
  return fsubjets_m_;
}

std::vector<float>  const & small_tree_full::fsubjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_phi_ && b_fsubjets_phi_){
    b_fsubjets_phi_->GetEntry(entry_);
    c_fsubjets_phi_ = true;
  }
  return fsubjets_phi_;
}

std::vector<float>  const & small_tree_full::fsubjets_poscsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_poscsv_ && b_fsubjets_poscsv_){
    b_fsubjets_poscsv_->GetEntry(entry_);
    c_fsubjets_poscsv_ = true;
  }
  return fsubjets_poscsv_;
}

std::vector<float>  const & small_tree_full::fsubjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_pt_ && b_fsubjets_pt_){
    b_fsubjets_pt_->GetEntry(entry_);
    c_fsubjets_pt_ = true;
  }
  return fsubjets_pt_;
}

std::vector<float>  const & small_tree_full::fsubjets_sumcsv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_sumcsv_ && b_fsubjets_sumcsv_){
    b_fsubjets_sumcsv_->GetEntry(entry_);
    c_fsubjets_sumcsv_ = true;
  }
  return fsubjets_sumcsv_;
}

std::vector<float>  const & small_tree_full::genfjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genfjets_eta_ && b_genfjets_eta_){
    b_genfjets_eta_->GetEntry(entry_);
    c_genfjets_eta_ = true;
  }
  return genfjets_eta_;
}

std::vector<float>  const & small_tree_full::genfjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genfjets_m_ && b_genfjets_m_){
    b_genfjets_m_->GetEntry(entry_);
    c_genfjets_m_ = true;
  }
  return genfjets_m_;
}

std::vector<float>  const & small_tree_full::genfjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genfjets_phi_ && b_genfjets_phi_){
    b_genfjets_phi_->GetEntry(entry_);
    c_genfjets_phi_ = true;
  }
  return genfjets_phi_;
}

std::vector<float>  const & small_tree_full::genfjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genfjets_pt_ && b_genfjets_pt_){
    b_genfjets_pt_->GetEntry(entry_);
    c_genfjets_pt_ = true;
  }
  return genfjets_pt_;
}

std::vector<float>  const & small_tree_full::genjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_eta_ && b_genjets_eta_){
    b_genjets_eta_->GetEntry(entry_);
    c_genjets_eta_ = true;
  }
  return genjets_eta_;
}

std::vector<float>  const & small_tree_full::genjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_m_ && b_genjets_m_){
    b_genjets_m_->GetEntry(entry_);
    c_genjets_m_ = true;
  }
  return genjets_m_;
}

std::vector<float>  const & small_tree_full::genjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_phi_ && b_genjets_phi_){
    b_genjets_phi_->GetEntry(entry_);
    c_genjets_phi_ = true;
  }
  return genjets_phi_;
}

std::vector<float>  const & small_tree_full::genjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_pt_ && b_genjets_pt_){
    b_genjets_pt_->GetEntry(entry_);
    c_genjets_pt_ = true;
  }
  return genjets_pt_;
}

std::vector<float>  const & small_tree_full::glu_proj_frac() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_glu_proj_frac_ && b_glu_proj_frac_){
    b_glu_proj_frac_->GetEntry(entry_);
    c_glu_proj_frac_ = true;
  }
  return glu_proj_frac_;
}

std::vector<float>  const & small_tree_full::jets_gen_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_gen_pt_ && b_jets_gen_pt_){
    b_jets_gen_pt_->GetEntry(entry_);
    c_jets_gen_pt_ = true;
  }
  return jets_gen_pt_;
}

std::vector<float>  const & small_tree_full::jets_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_id_ && b_jets_id_){
    b_jets_id_->GetEntry(entry_);
    c_jets_id_ = true;
  }
  return jets_id_;
}

std::vector<float>  const & small_tree_full::jets_parton_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_parton_pt_ && b_jets_parton_pt_){
    b_jets_parton_pt_->GetEntry(entry_);
    c_jets_parton_pt_ = true;
  }
  return jets_parton_pt_;
}

std::vector<float>  const & small_tree_full::jets_pt_from_mini() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_pt_from_mini_ && b_jets_pt_from_mini_){
    b_jets_pt_from_mini_->GetEntry(entry_);
    c_jets_pt_from_mini_ = true;
  }
  return jets_pt_from_mini_;
}

std::vector<float>  const & small_tree_full::mc_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_eta_ && b_mc_eta_){
    b_mc_eta_->GetEntry(entry_);
    c_mc_eta_ = true;
  }
  return mc_eta_;
}

std::vector<float>  const & small_tree_full::mc_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_phi_ && b_mc_phi_){
    b_mc_phi_->GetEntry(entry_);
    c_mc_phi_ = true;
  }
  return mc_phi_;
}

std::vector<float>  const & small_tree_full::mc_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_pt_ && b_mc_pt_){
    b_mc_pt_->GetEntry(entry_);
    c_mc_pt_ = true;
  }
  return mc_pt_;
}

std::vector<float>  const & small_tree_full::mus_miniso_10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_miniso_10_ && b_mus_miniso_10_){
    b_mus_miniso_10_->GetEntry(entry_);
    c_mus_miniso_10_ = true;
  }
  return mus_miniso_10_;
}

std::vector<float>  const & small_tree_full::mus_miniso_10_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_miniso_10_ch_ && b_mus_miniso_10_ch_){
    b_mus_miniso_10_ch_->GetEntry(entry_);
    c_mus_miniso_10_ch_ = true;
  }
  return mus_miniso_10_ch_;
}

std::vector<float>  const & small_tree_full::mus_miniso_tr10() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_miniso_tr10_ && b_mus_miniso_tr10_){
    b_mus_miniso_tr10_->GetEntry(entry_);
    c_mus_miniso_tr10_ = true;
  }
  return mus_miniso_tr10_;
}

std::vector<float>  const & small_tree_full::mus_miniso_tr10_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_miniso_tr10_ch_ && b_mus_miniso_tr10_ch_){
    b_mus_miniso_tr10_ch_->GetEntry(entry_);
    c_mus_miniso_tr10_ch_ = true;
  }
  return mus_miniso_tr10_ch_;
}

std::vector<float>  const & small_tree_full::mus_mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_mt_ && b_mus_mt_){
    b_mus_mt_->GetEntry(entry_);
    c_mus_mt_ = true;
  }
  return mus_mt_;
}

std::vector<float>  const & small_tree_full::mus_reliso() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_ && b_mus_reliso_){
    b_mus_reliso_->GetEntry(entry_);
    c_mus_reliso_ = true;
  }
  return mus_reliso_;
}

std::vector<float>  const & small_tree_full::mus_reliso_r01() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_r01_ && b_mus_reliso_r01_){
    b_mus_reliso_r01_->GetEntry(entry_);
    c_mus_reliso_r01_ = true;
  }
  return mus_reliso_r01_;
}

std::vector<float>  const & small_tree_full::mus_reliso_r015() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_r015_ && b_mus_reliso_r015_){
    b_mus_reliso_r015_->GetEntry(entry_);
    c_mus_reliso_r015_ = true;
  }
  return mus_reliso_r015_;
}

std::vector<float>  const & small_tree_full::mus_reliso_r02() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_r02_ && b_mus_reliso_r02_){
    b_mus_reliso_r02_->GetEntry(entry_);
    c_mus_reliso_r02_ = true;
  }
  return mus_reliso_r02_;
}

std::vector<float>  const & small_tree_full::mus_reliso_r03() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_r03_ && b_mus_reliso_r03_){
    b_mus_reliso_r03_->GetEntry(entry_);
    c_mus_reliso_r03_ = true;
  }
  return mus_reliso_r03_;
}

std::vector<float>  const & small_tree_full::mus_reliso_r04() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_reliso_r04_ && b_mus_reliso_r04_){
    b_mus_reliso_r04_->GetEntry(entry_);
    c_mus_reliso_r04_ = true;
  }
  return mus_reliso_r04_;
}

std::vector<float>  const & small_tree_full::mus_tru_dr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_dr_ && b_mus_tru_dr_){
    b_mus_tru_dr_->GetEntry(entry_);
    c_mus_tru_dr_ = true;
  }
  return mus_tru_dr_;
}

std::vector<float>  const & small_tree_full::subjets_csv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_csv_ && b_subjets_csv_){
    b_subjets_csv_->GetEntry(entry_);
    c_subjets_csv_ = true;
  }
  return subjets_csv_;
}

std::vector<float>  const & small_tree_full::subjets_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_eta_ && b_subjets_eta_){
    b_subjets_eta_->GetEntry(entry_);
    c_subjets_eta_ = true;
  }
  return subjets_eta_;
}

std::vector<float>  const & small_tree_full::subjets_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_id_ && b_subjets_id_){
    b_subjets_id_->GetEntry(entry_);
    c_subjets_id_ = true;
  }
  return subjets_id_;
}

std::vector<float>  const & small_tree_full::subjets_m() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_m_ && b_subjets_m_){
    b_subjets_m_->GetEntry(entry_);
    c_subjets_m_ = true;
  }
  return subjets_m_;
}

std::vector<float>  const & small_tree_full::subjets_mindr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_mindr_ && b_subjets_mindr_){
    b_subjets_mindr_->GetEntry(entry_);
    c_subjets_mindr_ = true;
  }
  return subjets_mindr_;
}

std::vector<float>  const & small_tree_full::subjets_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_phi_ && b_subjets_phi_){
    b_subjets_phi_->GetEntry(entry_);
    c_subjets_phi_ = true;
  }
  return subjets_phi_;
}

std::vector<float>  const & small_tree_full::subjets_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_pt_ && b_subjets_pt_){
    b_subjets_pt_->GetEntry(entry_);
    c_subjets_pt_ = true;
  }
  return subjets_pt_;
}

std::vector<float>  const & small_tree_full::subjets_subeta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_subeta_ && b_subjets_subeta_){
    b_subjets_subeta_->GetEntry(entry_);
    c_subjets_subeta_ = true;
  }
  return subjets_subeta_;
}

std::vector<float>  const & small_tree_full::subjets_subm() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_subm_ && b_subjets_subm_){
    b_subjets_subm_->GetEntry(entry_);
    c_subjets_subm_ = true;
  }
  return subjets_subm_;
}

std::vector<float>  const & small_tree_full::subjets_subphi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_subphi_ && b_subjets_subphi_){
    b_subjets_subphi_->GetEntry(entry_);
    c_subjets_subphi_ = true;
  }
  return subjets_subphi_;
}

std::vector<float>  const & small_tree_full::subjets_subpt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_subpt_ && b_subjets_subpt_){
    b_subjets_subpt_->GetEntry(entry_);
    c_subjets_subpt_ = true;
  }
  return subjets_subpt_;
}

std::vector<float>  const & small_tree_full::tks_eta() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_eta_ && b_tks_eta_){
    b_tks_eta_->GetEntry(entry_);
    c_tks_eta_ = true;
  }
  return tks_eta_;
}

std::vector<float>  const & small_tree_full::tks_mini_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_mini_ch_ && b_tks_mini_ch_){
    b_tks_mini_ch_->GetEntry(entry_);
    c_tks_mini_ch_ = true;
  }
  return tks_mini_ch_;
}

std::vector<float>  const & small_tree_full::tks_mini_ne() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_mini_ne_ && b_tks_mini_ne_){
    b_tks_mini_ne_->GetEntry(entry_);
    c_tks_mini_ne_ = true;
  }
  return tks_mini_ne_;
}

std::vector<float>  const & small_tree_full::tks_mt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_mt_ && b_tks_mt_){
    b_tks_mt_->GetEntry(entry_);
    c_tks_mt_ = true;
  }
  return tks_mt_;
}

std::vector<float>  const & small_tree_full::tks_phi() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_phi_ && b_tks_phi_){
    b_tks_phi_->GetEntry(entry_);
    c_tks_phi_ = true;
  }
  return tks_phi_;
}

std::vector<float>  const & small_tree_full::tks_pt() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_pt_ && b_tks_pt_){
    b_tks_pt_->GetEntry(entry_);
    c_tks_pt_ = true;
  }
  return tks_pt_;
}

std::vector<float>  const & small_tree_full::tks_r02_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r02_ch_ && b_tks_r02_ch_){
    b_tks_r02_ch_->GetEntry(entry_);
    c_tks_r02_ch_ = true;
  }
  return tks_r02_ch_;
}

std::vector<float>  const & small_tree_full::tks_r02_ne() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r02_ne_ && b_tks_r02_ne_){
    b_tks_r02_ne_->GetEntry(entry_);
    c_tks_r02_ne_ = true;
  }
  return tks_r02_ne_;
}

std::vector<float>  const & small_tree_full::tks_r03_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r03_ch_ && b_tks_r03_ch_){
    b_tks_r03_ch_->GetEntry(entry_);
    c_tks_r03_ch_ = true;
  }
  return tks_r03_ch_;
}

std::vector<float>  const & small_tree_full::tks_r03_ne() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r03_ne_ && b_tks_r03_ne_){
    b_tks_r03_ne_->GetEntry(entry_);
    c_tks_r03_ne_ = true;
  }
  return tks_r03_ne_;
}

std::vector<float>  const & small_tree_full::tks_r04_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r04_ch_ && b_tks_r04_ch_){
    b_tks_r04_ch_->GetEntry(entry_);
    c_tks_r04_ch_ = true;
  }
  return tks_r04_ch_;
}

std::vector<float>  const & small_tree_full::tks_r04_ne() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r04_ne_ && b_tks_r04_ne_){
    b_tks_r04_ne_->GetEntry(entry_);
    c_tks_r04_ne_ = true;
  }
  return tks_r04_ne_;
}

std::vector<float>  const & small_tree_full::tks_r05_ch() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r05_ch_ && b_tks_r05_ch_){
    b_tks_r05_ch_->GetEntry(entry_);
    c_tks_r05_ch_ = true;
  }
  return tks_r05_ch_;
}

std::vector<float>  const & small_tree_full::tks_r05_ne() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_r05_ne_ && b_tks_r05_ne_){
    b_tks_r05_ne_->GetEntry(entry_);
    c_tks_r05_ne_ = true;
  }
  return tks_r05_ne_;
}

std::vector<float>  const & small_tree_full::tks_tru_dp() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_tru_dp_ && b_tks_tru_dp_){
    b_tks_tru_dp_->GetEntry(entry_);
    c_tks_tru_dp_ = true;
  }
  return tks_tru_dp_;
}

std::vector<float>  const & small_tree_full::tks_tru_dr() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_tru_dr_ && b_tks_tru_dr_){
    b_tks_tru_dr_->GetEntry(entry_);
    c_tks_tru_dr_ = true;
  }
  return tks_tru_dr_;
}

std::vector<int>  const & small_tree_full::els_tru_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_id_ && b_els_tru_id_){
    b_els_tru_id_->GetEntry(entry_);
    c_els_tru_id_ = true;
  }
  return els_tru_id_;
}

std::vector<int>  const & small_tree_full::els_tru_momid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_els_tru_momid_ && b_els_tru_momid_){
    b_els_tru_momid_->GetEntry(entry_);
    c_els_tru_momid_ = true;
  }
  return els_tru_momid_;
}

std::vector<int>  const & small_tree_full::fjets15_btags() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_btags_ && b_fjets15_btags_){
    b_fjets15_btags_->GetEntry(entry_);
    c_fjets15_btags_ = true;
  }
  return fjets15_btags_;
}

std::vector<int>  const & small_tree_full::fjets15_nconst() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fjets15_nconst_ && b_fjets15_nconst_){
    b_fjets15_nconst_->GetEntry(entry_);
    c_fjets15_nconst_ = true;
  }
  return fjets15_nconst_;
}

std::vector<int>  const & small_tree_full::fsubjets_btags() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_btags_ && b_fsubjets_btags_){
    b_fsubjets_btags_->GetEntry(entry_);
    c_fsubjets_btags_ = true;
  }
  return fsubjets_btags_;
}

std::vector<int>  const & small_tree_full::fsubjets_nconst() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_fsubjets_nconst_ && b_fsubjets_nconst_){
    b_fsubjets_nconst_->GetEntry(entry_);
    c_fsubjets_nconst_ = true;
  }
  return fsubjets_nconst_;
}

std::vector<int>  const & small_tree_full::genfjets_nconst() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genfjets_nconst_ && b_genfjets_nconst_){
    b_genfjets_nconst_->GetEntry(entry_);
    c_genfjets_nconst_ = true;
  }
  return genfjets_nconst_;
}

std::vector<int>  const & small_tree_full::genjets_genfjet_index() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_genfjet_index_ && b_genjets_genfjet_index_){
    b_genjets_genfjet_index_->GetEntry(entry_);
    c_genjets_genfjet_index_ = true;
  }
  return genjets_genfjet_index_;
}

std::vector<int>  const & small_tree_full::genjets_isr_code() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_genjets_isr_code_ && b_genjets_isr_code_){
    b_genjets_isr_code_->GetEntry(entry_);
    c_genjets_isr_code_ = true;
  }
  return genjets_isr_code_;
}

std::vector<int>  const & small_tree_full::jets_fjet15_index() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_fjet15_index_ && b_jets_fjet15_index_){
    b_jets_fjet15_index_->GetEntry(entry_);
    c_jets_fjet15_index_ = true;
  }
  return jets_fjet15_index_;
}

std::vector<int>  const & small_tree_full::jets_isr_code() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_jets_isr_code_ && b_jets_isr_code_){
    b_jets_isr_code_->GetEntry(entry_);
    c_jets_isr_code_ = true;
  }
  return jets_isr_code_;
}

std::vector<int>  const & small_tree_full::mc_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_id_ && b_mc_id_){
    b_mc_id_->GetEntry(entry_);
    c_mc_id_ = true;
  }
  return mc_id_;
}

std::vector<int>  const & small_tree_full::mc_status() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_status_ && b_mc_status_){
    b_mc_status_->GetEntry(entry_);
    c_mc_status_ = true;
  }
  return mc_status_;
}

std::vector<int>  const & small_tree_full::mus_tru_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_id_ && b_mus_tru_id_){
    b_mus_tru_id_->GetEntry(entry_);
    c_mus_tru_id_ = true;
  }
  return mus_tru_id_;
}

std::vector<int>  const & small_tree_full::mus_tru_momid() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mus_tru_momid_ && b_mus_tru_momid_){
    b_mus_tru_momid_->GetEntry(entry_);
    c_mus_tru_momid_ = true;
  }
  return mus_tru_momid_;
}

std::vector<int>  const & small_tree_full::subjets_fsubjet_index() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_fsubjet_index_ && b_subjets_fsubjet_index_){
    b_subjets_fsubjet_index_->GetEntry(entry_);
    c_subjets_fsubjet_index_ = true;
  }
  return subjets_fsubjet_index_;
}

std::vector<int>  const & small_tree_full::subjets_nsub() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_subjets_nsub_ && b_subjets_nsub_){
    b_subjets_nsub_->GetEntry(entry_);
    c_subjets_nsub_ = true;
  }
  return subjets_nsub_;
}

std::vector<int>  const & small_tree_full::tks_charge() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_charge_ && b_tks_charge_){
    b_tks_charge_->GetEntry(entry_);
    c_tks_charge_ = true;
  }
  return tks_charge_;
}

std::vector<int>  const & small_tree_full::tks_from_pv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_from_pv_ && b_tks_from_pv_){
    b_tks_from_pv_->GetEntry(entry_);
    c_tks_from_pv_ = true;
  }
  return tks_from_pv_;
}

std::vector<int>  const & small_tree_full::tks_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_id_ && b_tks_id_){
    b_tks_id_->GetEntry(entry_);
    c_tks_id_ = true;
  }
  return tks_id_;
}

std::vector<int>  const & small_tree_full::tks_num_prongs() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_num_prongs_ && b_tks_num_prongs_){
    b_tks_num_prongs_->GetEntry(entry_);
    c_tks_num_prongs_ = true;
  }
  return tks_num_prongs_;
}

std::vector<int>  const & small_tree_full::tks_tru_id() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_tks_tru_id_ && b_tks_tru_id_){
    b_tks_tru_id_->GetEntry(entry_);
    c_tks_tru_id_ = true;
  }
  return tks_tru_id_;
}

std::vector<size_t>  const & small_tree_full::mc_mom() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_mom_ && b_mc_mom_){
    b_mc_mom_->GetEntry(entry_);
    c_mc_mom_ = true;
  }
  return mc_mom_;
}

unsigned  const & small_tree_full::mc_type() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_mc_type_ && b_mc_type_){
    b_mc_type_->GetEntry(entry_);
    c_mc_type_ = true;
  }
  return mc_type_;
}

float  & small_tree_full::dphi_neutralinos(){
  if(read_only_ && !c_dphi_neutralinos_ && b_dphi_neutralinos_){
    b_dphi_neutralinos_->GetEntry(entry_);
    c_dphi_neutralinos_ = true;
  }
  return dphi_neutralinos_;
}

float  & small_tree_full::dphi_wlep(){
  if(read_only_ && !c_dphi_wlep_ && b_dphi_wlep_){
    b_dphi_wlep_->GetEntry(entry_);
    c_dphi_wlep_ = true;
  }
  return dphi_wlep_;
}

float  & small_tree_full::dphi_wlep_reliso(){
  if(read_only_ && !c_dphi_wlep_reliso_ && b_dphi_wlep_reliso_){
    b_dphi_wlep_reliso_->GetEntry(entry_);
    c_dphi_wlep_reliso_ = true;
  }
  return dphi_wlep_reliso_;
}

float  & small_tree_full::gen_ht(){
  if(read_only_ && !c_gen_ht_ && b_gen_ht_){
    b_gen_ht_->GetEntry(entry_);
    c_gen_ht_ = true;
  }
  return gen_ht_;
}

float  & small_tree_full::gen_met(){
  if(read_only_ && !c_gen_met_ && b_gen_met_){
    b_gen_met_->GetEntry(entry_);
    c_gen_met_ = true;
  }
  return gen_met_;
}

float  & small_tree_full::gen_met_phi(){
  if(read_only_ && !c_gen_met_phi_ && b_gen_met_phi_){
    b_gen_met_phi_->GetEntry(entry_);
    c_gen_met_phi_ = true;
  }
  return gen_met_phi_;
}

float  & small_tree_full::gen_mj(){
  if(read_only_ && !c_gen_mj_ && b_gen_mj_){
    b_gen_mj_->GetEntry(entry_);
    c_gen_mj_ = true;
  }
  return gen_mj_;
}

float  & small_tree_full::ht40(){
  if(read_only_ && !c_ht40_ && b_ht40_){
    b_ht40_->GetEntry(entry_);
    c_ht40_ = true;
  }
  return ht40_;
}

float  & small_tree_full::ht_isr(){
  if(read_only_ && !c_ht_isr_ && b_ht_isr_){
    b_ht_isr_->GetEntry(entry_);
    c_ht_isr_ = true;
  }
  return ht_isr_;
}

float  & small_tree_full::ht_isr_me(){
  if(read_only_ && !c_ht_isr_me_ && b_ht_isr_me_){
    b_ht_isr_me_->GetEntry(entry_);
    c_ht_isr_me_ = true;
  }
  return ht_isr_me_;
}

float  & small_tree_full::ht_isr_nonme(){
  if(read_only_ && !c_ht_isr_nonme_ && b_ht_isr_nonme_){
    b_ht_isr_nonme_->GetEntry(entry_);
    c_ht_isr_nonme_ = true;
  }
  return ht_isr_nonme_;
}

float  & small_tree_full::ht_isr_tru(){
  if(read_only_ && !c_ht_isr_tru_ && b_ht_isr_tru_){
    b_ht_isr_tru_->GetEntry(entry_);
    c_ht_isr_tru_ = true;
  }
  return ht_isr_tru_;
}

float  & small_tree_full::ht_nonb(){
  if(read_only_ && !c_ht_nonb_ && b_ht_nonb_){
    b_ht_nonb_->GetEntry(entry_);
    c_ht_nonb_ = true;
  }
  return ht_nonb_;
}

float  & small_tree_full::ht_sub(){
  if(read_only_ && !c_ht_sub_ && b_ht_sub_){
    b_ht_sub_->GetEntry(entry_);
    c_ht_sub_ = true;
  }
  return ht_sub_;
}

float  & small_tree_full::lep_eta(){
  if(read_only_ && !c_lep_eta_ && b_lep_eta_){
    b_lep_eta_->GetEntry(entry_);
    c_lep_eta_ = true;
  }
  return lep_eta_;
}

float  & small_tree_full::lep_eta_reliso(){
  if(read_only_ && !c_lep_eta_reliso_ && b_lep_eta_reliso_){
    b_lep_eta_reliso_->GetEntry(entry_);
    c_lep_eta_reliso_ = true;
  }
  return lep_eta_reliso_;
}

float  & small_tree_full::lep_phi(){
  if(read_only_ && !c_lep_phi_ && b_lep_phi_){
    b_lep_phi_->GetEntry(entry_);
    c_lep_phi_ = true;
  }
  return lep_phi_;
}

float  & small_tree_full::lep_phi_reliso(){
  if(read_only_ && !c_lep_phi_reliso_ && b_lep_phi_reliso_){
    b_lep_phi_reliso_->GetEntry(entry_);
    c_lep_phi_reliso_ = true;
  }
  return lep_phi_reliso_;
}

float  & small_tree_full::lep_pt(){
  if(read_only_ && !c_lep_pt_ && b_lep_pt_){
    b_lep_pt_->GetEntry(entry_);
    c_lep_pt_ = true;
  }
  return lep_pt_;
}

float  & small_tree_full::lep_pt_reliso(){
  if(read_only_ && !c_lep_pt_reliso_ && b_lep_pt_reliso_){
    b_lep_pt_reliso_->GetEntry(entry_);
    c_lep_pt_reliso_ = true;
  }
  return lep_pt_reliso_;
}

float  & small_tree_full::max_dphi_bb(){
  if(read_only_ && !c_max_dphi_bb_ && b_max_dphi_bb_){
    b_max_dphi_bb_->GetEntry(entry_);
    c_max_dphi_bb_ = true;
  }
  return max_dphi_bb_;
}

float  & small_tree_full::max_dphi_blep(){
  if(read_only_ && !c_max_dphi_blep_ && b_max_dphi_blep_){
    b_max_dphi_blep_->GetEntry(entry_);
    c_max_dphi_blep_ = true;
  }
  return max_dphi_blep_;
}

float  & small_tree_full::max_dphi_bmet(){
  if(read_only_ && !c_max_dphi_bmet_ && b_max_dphi_bmet_){
    b_max_dphi_bmet_->GetEntry(entry_);
    c_max_dphi_bmet_ = true;
  }
  return max_dphi_bmet_;
}

float  & small_tree_full::max_dr_bb(){
  if(read_only_ && !c_max_dr_bb_ && b_max_dr_bb_){
    b_max_dr_bb_->GetEntry(entry_);
    c_max_dr_bb_ = true;
  }
  return max_dr_bb_;
}

float  & small_tree_full::max_dr_blep(){
  if(read_only_ && !c_max_dr_blep_ && b_max_dr_blep_){
    b_max_dr_blep_->GetEntry(entry_);
    c_max_dr_blep_ = true;
  }
  return max_dr_blep_;
}

float  & small_tree_full::max_m_bb(){
  if(read_only_ && !c_max_m_bb_ && b_max_m_bb_){
    b_max_m_bb_->GetEntry(entry_);
    c_max_m_bb_ = true;
  }
  return max_m_bb_;
}

float  & small_tree_full::max_m_blep(){
  if(read_only_ && !c_max_m_blep_ && b_max_m_blep_){
    b_max_m_blep_->GetEntry(entry_);
    c_max_m_blep_ = true;
  }
  return max_m_blep_;
}

float  & small_tree_full::max_mt_bmet(){
  if(read_only_ && !c_max_mt_bmet_ && b_max_mt_bmet_){
    b_max_mt_bmet_->GetEntry(entry_);
    c_max_mt_bmet_ = true;
  }
  return max_mt_bmet_;
}

float  & small_tree_full::max_pt_bb(){
  if(read_only_ && !c_max_pt_bb_ && b_max_pt_bb_){
    b_max_pt_bb_->GetEntry(entry_);
    c_max_pt_bb_ = true;
  }
  return max_pt_bb_;
}

float  & small_tree_full::max_pt_blep(){
  if(read_only_ && !c_max_pt_blep_ && b_max_pt_blep_){
    b_max_pt_blep_->GetEntry(entry_);
    c_max_pt_blep_ = true;
  }
  return max_pt_blep_;
}

float  & small_tree_full::max_pt_bmet(){
  if(read_only_ && !c_max_pt_bmet_ && b_max_pt_bmet_){
    b_max_pt_bmet_->GetEntry(entry_);
    c_max_pt_bmet_ = true;
  }
  return max_pt_bmet_;
}

float  & small_tree_full::mht_sub(){
  if(read_only_ && !c_mht_sub_ && b_mht_sub_){
    b_mht_sub_->GetEntry(entry_);
    c_mht_sub_ = true;
  }
  return mht_sub_;
}

float  & small_tree_full::min_dphi_bb(){
  if(read_only_ && !c_min_dphi_bb_ && b_min_dphi_bb_){
    b_min_dphi_bb_->GetEntry(entry_);
    c_min_dphi_bb_ = true;
  }
  return min_dphi_bb_;
}

float  & small_tree_full::min_dphi_blep(){
  if(read_only_ && !c_min_dphi_blep_ && b_min_dphi_blep_){
    b_min_dphi_blep_->GetEntry(entry_);
    c_min_dphi_blep_ = true;
  }
  return min_dphi_blep_;
}

float  & small_tree_full::min_dphi_bmet(){
  if(read_only_ && !c_min_dphi_bmet_ && b_min_dphi_bmet_){
    b_min_dphi_bmet_->GetEntry(entry_);
    c_min_dphi_bmet_ = true;
  }
  return min_dphi_bmet_;
}

float  & small_tree_full::min_dr_bb(){
  if(read_only_ && !c_min_dr_bb_ && b_min_dr_bb_){
    b_min_dr_bb_->GetEntry(entry_);
    c_min_dr_bb_ = true;
  }
  return min_dr_bb_;
}

float  & small_tree_full::min_dr_blep(){
  if(read_only_ && !c_min_dr_blep_ && b_min_dr_blep_){
    b_min_dr_blep_->GetEntry(entry_);
    c_min_dr_blep_ = true;
  }
  return min_dr_blep_;
}

float  & small_tree_full::min_m_bb(){
  if(read_only_ && !c_min_m_bb_ && b_min_m_bb_){
    b_min_m_bb_->GetEntry(entry_);
    c_min_m_bb_ = true;
  }
  return min_m_bb_;
}

float  & small_tree_full::min_m_blep(){
  if(read_only_ && !c_min_m_blep_ && b_min_m_blep_){
    b_min_m_blep_->GetEntry(entry_);
    c_min_m_blep_ = true;
  }
  return min_m_blep_;
}

float  & small_tree_full::min_mt_bmet(){
  if(read_only_ && !c_min_mt_bmet_ && b_min_mt_bmet_){
    b_min_mt_bmet_->GetEntry(entry_);
    c_min_mt_bmet_ = true;
  }
  return min_mt_bmet_;
}

float  & small_tree_full::min_mt_bmet_with_w_mass(){
  if(read_only_ && !c_min_mt_bmet_with_w_mass_ && b_min_mt_bmet_with_w_mass_){
    b_min_mt_bmet_with_w_mass_->GetEntry(entry_);
    c_min_mt_bmet_with_w_mass_ = true;
  }
  return min_mt_bmet_with_w_mass_;
}

float  & small_tree_full::min_pt_bb(){
  if(read_only_ && !c_min_pt_bb_ && b_min_pt_bb_){
    b_min_pt_bb_->GetEntry(entry_);
    c_min_pt_bb_ = true;
  }
  return min_pt_bb_;
}

float  & small_tree_full::min_pt_blep(){
  if(read_only_ && !c_min_pt_blep_ && b_min_pt_blep_){
    b_min_pt_blep_->GetEntry(entry_);
    c_min_pt_blep_ = true;
  }
  return min_pt_blep_;
}

float  & small_tree_full::min_pt_bmet(){
  if(read_only_ && !c_min_pt_bmet_ && b_min_pt_bmet_){
    b_min_pt_bmet_->GetEntry(entry_);
    c_min_pt_bmet_ = true;
  }
  return min_pt_bmet_;
}

float  & small_tree_full::mindphin_metjet(){
  if(read_only_ && !c_mindphin_metjet_ && b_mindphin_metjet_){
    b_mindphin_metjet_->GetEntry(entry_);
    c_mindphin_metjet_ = true;
  }
  return mindphin_metjet_;
}

float  & small_tree_full::mj15(){
  if(read_only_ && !c_mj15_ && b_mj15_){
    b_mj15_->GetEntry(entry_);
    c_mj15_ = true;
  }
  return mj15_;
}

float  & small_tree_full::mj_sub(){
  if(read_only_ && !c_mj_sub_ && b_mj_sub_){
    b_mj_sub_->GetEntry(entry_);
    c_mj_sub_ = true;
  }
  return mj_sub_;
}

float  & small_tree_full::mt_reliso(){
  if(read_only_ && !c_mt_reliso_ && b_mt_reliso_){
    b_mt_reliso_->GetEntry(entry_);
    c_mt_reliso_ = true;
  }
  return mt_reliso_;
}

float  & small_tree_full::st(){
  if(read_only_ && !c_st_ && b_st_){
    b_st_->GetEntry(entry_);
    c_st_ = true;
  }
  return st_;
}

float  & small_tree_full::st_reliso(){
  if(read_only_ && !c_st_reliso_ && b_st_reliso_){
    b_st_reliso_->GetEntry(entry_);
    c_st_reliso_ = true;
  }
  return st_reliso_;
}

float  & small_tree_full::tru_gluglu_dphi(){
  if(read_only_ && !c_tru_gluglu_dphi_ && b_tru_gluglu_dphi_){
    b_tru_gluglu_dphi_->GetEntry(entry_);
    c_tru_gluglu_dphi_ = true;
  }
  return tru_gluglu_dphi_;
}

float  & small_tree_full::tru_gluglu_m(){
  if(read_only_ && !c_tru_gluglu_m_ && b_tru_gluglu_m_){
    b_tru_gluglu_m_->GetEntry(entry_);
    c_tru_gluglu_m_ = true;
  }
  return tru_gluglu_m_;
}

float  & small_tree_full::tru_gluglu_pt(){
  if(read_only_ && !c_tru_gluglu_pt_ && b_tru_gluglu_pt_){
    b_tru_gluglu_pt_->GetEntry(entry_);
    c_tru_gluglu_pt_ = true;
  }
  return tru_gluglu_pt_;
}

float  & small_tree_full::tru_gluglu_ptdiff(){
  if(read_only_ && !c_tru_gluglu_ptdiff_ && b_tru_gluglu_ptdiff_){
    b_tru_gluglu_ptdiff_->GetEntry(entry_);
    c_tru_gluglu_ptdiff_ = true;
  }
  return tru_gluglu_ptdiff_;
}

float  & small_tree_full::tru_sphericity(){
  if(read_only_ && !c_tru_sphericity_ && b_tru_sphericity_){
    b_tru_sphericity_->GetEntry(entry_);
    c_tru_sphericity_ = true;
  }
  return tru_sphericity_;
}

float  & small_tree_full::tru_tt_dphi(){
  if(read_only_ && !c_tru_tt_dphi_ && b_tru_tt_dphi_){
    b_tru_tt_dphi_->GetEntry(entry_);
    c_tru_tt_dphi_ = true;
  }
  return tru_tt_dphi_;
}

float  & small_tree_full::tru_tt_m(){
  if(read_only_ && !c_tru_tt_m_ && b_tru_tt_m_){
    b_tru_tt_m_->GetEntry(entry_);
    c_tru_tt_m_ = true;
  }
  return tru_tt_m_;
}

float  & small_tree_full::tru_tt_pt(){
  if(read_only_ && !c_tru_tt_pt_ && b_tru_tt_pt_){
    b_tru_tt_pt_->GetEntry(entry_);
    c_tru_tt_pt_ = true;
  }
  return tru_tt_pt_;
}

float  & small_tree_full::tru_tt_ptdiff(){
  if(read_only_ && !c_tru_tt_ptdiff_ && b_tru_tt_ptdiff_){
    b_tru_tt_ptdiff_->GetEntry(entry_);
    c_tru_tt_ptdiff_ = true;
  }
  return tru_tt_ptdiff_;
}

float  & small_tree_full::trutop1_phi(){
  if(read_only_ && !c_trutop1_phi_ && b_trutop1_phi_){
    b_trutop1_phi_->GetEntry(entry_);
    c_trutop1_phi_ = true;
  }
  return trutop1_phi_;
}

float  & small_tree_full::trutop1_pt(){
  if(read_only_ && !c_trutop1_pt_ && b_trutop1_pt_){
    b_trutop1_pt_->GetEntry(entry_);
    c_trutop1_pt_ = true;
  }
  return trutop1_pt_;
}

float  & small_tree_full::trutop2_phi(){
  if(read_only_ && !c_trutop2_phi_ && b_trutop2_phi_){
    b_trutop2_phi_->GetEntry(entry_);
    c_trutop2_phi_ = true;
  }
  return trutop2_phi_;
}

float  & small_tree_full::trutop2_pt(){
  if(read_only_ && !c_trutop2_pt_ && b_trutop2_pt_){
    b_trutop2_pt_->GetEntry(entry_);
    c_trutop2_pt_ = true;
  }
  return trutop2_pt_;
}

int  & small_tree_full::lep_charge(){
  if(read_only_ && !c_lep_charge_ && b_lep_charge_){
    b_lep_charge_->GetEntry(entry_);
    c_lep_charge_ = true;
  }
  return lep_charge_;
}

int  & small_tree_full::lep_charge_reliso(){
  if(read_only_ && !c_lep_charge_reliso_ && b_lep_charge_reliso_){
    b_lep_charge_reliso_->GetEntry(entry_);
    c_lep_charge_reliso_ = true;
  }
  return lep_charge_reliso_;
}

int  & small_tree_full::n_isr_me(){
  if(read_only_ && !c_n_isr_me_ && b_n_isr_me_){
    b_n_isr_me_->GetEntry(entry_);
    c_n_isr_me_ = true;
  }
  return n_isr_me_;
}

int  & small_tree_full::n_isr_nonme(){
  if(read_only_ && !c_n_isr_nonme_ && b_n_isr_nonme_){
    b_n_isr_nonme_->GetEntry(entry_);
    c_n_isr_nonme_ = true;
  }
  return n_isr_nonme_;
}

int  & small_tree_full::nbadjets(){
  if(read_only_ && !c_nbadjets_ && b_nbadjets_){
    b_nbadjets_->GetEntry(entry_);
    c_nbadjets_ = true;
  }
  return nbadjets_;
}

int  & small_tree_full::nbl40(){
  if(read_only_ && !c_nbl40_ && b_nbl40_){
    b_nbl40_->GetEntry(entry_);
    c_nbl40_ = true;
  }
  return nbl40_;
}

int  & small_tree_full::nbl_sub(){
  if(read_only_ && !c_nbl_sub_ && b_nbl_sub_){
    b_nbl_sub_->GetEntry(entry_);
    c_nbl_sub_ = true;
  }
  return nbl_sub_;
}

int  & small_tree_full::nbm40(){
  if(read_only_ && !c_nbm40_ && b_nbm40_){
    b_nbm40_->GetEntry(entry_);
    c_nbm40_ = true;
  }
  return nbm40_;
}

int  & small_tree_full::nbm_sub(){
  if(read_only_ && !c_nbm_sub_ && b_nbm_sub_){
    b_nbm_sub_->GetEntry(entry_);
    c_nbm_sub_ = true;
  }
  return nbm_sub_;
}

int  & small_tree_full::nbt40(){
  if(read_only_ && !c_nbt40_ && b_nbt40_){
    b_nbt40_->GetEntry(entry_);
    c_nbt40_ = true;
  }
  return nbt40_;
}

int  & small_tree_full::nbt_sub(){
  if(read_only_ && !c_nbt_sub_ && b_nbt_sub_){
    b_nbt_sub_->GetEntry(entry_);
    c_nbt_sub_ = true;
  }
  return nbt_sub_;
}

int  & small_tree_full::nels_reliso(){
  if(read_only_ && !c_nels_reliso_ && b_nels_reliso_){
    b_nels_reliso_->GetEntry(entry_);
    c_nels_reliso_ = true;
  }
  return nels_reliso_;
}

int  & small_tree_full::nfjets15(){
  if(read_only_ && !c_nfjets15_ && b_nfjets15_){
    b_nfjets15_->GetEntry(entry_);
    c_nfjets15_ = true;
  }
  return nfjets15_;
}

int  & small_tree_full::nfsubjets(){
  if(read_only_ && !c_nfsubjets_ && b_nfsubjets_){
    b_nfsubjets_->GetEntry(entry_);
    c_nfsubjets_ = true;
  }
  return nfsubjets_;
}

int  & small_tree_full::ngenfjets(){
  if(read_only_ && !c_ngenfjets_ && b_ngenfjets_){
    b_ngenfjets_->GetEntry(entry_);
    c_ngenfjets_ = true;
  }
  return ngenfjets_;
}

int  & small_tree_full::ngenjets(){
  if(read_only_ && !c_ngenjets_ && b_ngenjets_){
    b_ngenjets_->GetEntry(entry_);
    c_ngenjets_ = true;
  }
  return ngenjets_;
}

int  & small_tree_full::njets40(){
  if(read_only_ && !c_njets40_ && b_njets40_){
    b_njets40_->GetEntry(entry_);
    c_njets40_ = true;
  }
  return njets40_;
}

int  & small_tree_full::nleps_reliso(){
  if(read_only_ && !c_nleps_reliso_ && b_nleps_reliso_){
    b_nleps_reliso_->GetEntry(entry_);
    c_nleps_reliso_ = true;
  }
  return nleps_reliso_;
}

int  & small_tree_full::nmus_reliso(){
  if(read_only_ && !c_nmus_reliso_ && b_nmus_reliso_){
    b_nmus_reliso_->GetEntry(entry_);
    c_nmus_reliso_ = true;
  }
  return nmus_reliso_;
}

int  & small_tree_full::nsubjets(){
  if(read_only_ && !c_nsubjets_ && b_nsubjets_){
    b_nsubjets_->GetEntry(entry_);
    c_nsubjets_ = true;
  }
  return nsubjets_;
}

int  & small_tree_full::ntks(){
  if(read_only_ && !c_ntks_ && b_ntks_){
    b_ntks_->GetEntry(entry_);
    c_ntks_ = true;
  }
  return ntks_;
}

int  & small_tree_full::ntks_chg(){
  if(read_only_ && !c_ntks_chg_ && b_ntks_chg_){
    b_ntks_chg_->GetEntry(entry_);
    c_ntks_chg_ = true;
  }
  return ntks_chg_;
}

int  & small_tree_full::ntks_chg_reliso(){
  if(read_only_ && !c_ntks_chg_reliso_ && b_ntks_chg_reliso_){
    b_ntks_chg_reliso_->GetEntry(entry_);
    c_ntks_chg_reliso_ = true;
  }
  return ntks_chg_reliso_;
}

int  & small_tree_full::nvels_reliso(){
  if(read_only_ && !c_nvels_reliso_ && b_nvels_reliso_){
    b_nvels_reliso_->GetEntry(entry_);
    c_nvels_reliso_ = true;
  }
  return nvels_reliso_;
}

int  & small_tree_full::nvmus_reliso(){
  if(read_only_ && !c_nvmus_reliso_ && b_nvmus_reliso_){
    b_nvmus_reliso_->GetEntry(entry_);
    c_nvmus_reliso_ = true;
  }
  return nvmus_reliso_;
}

std::vector<bool>  & small_tree_full::badjets_islep(){
  if(read_only_ && !c_badjets_islep_ && b_badjets_islep_){
    b_badjets_islep_->GetEntry(entry_);
    c_badjets_islep_ = true;
  }
  return badjets_islep_;
}

std::vector<bool>  & small_tree_full::els_tru_tm(){
  if(read_only_ && !c_els_tru_tm_ && b_els_tru_tm_){
    b_els_tru_tm_->GetEntry(entry_);
    c_els_tru_tm_ = true;
  }
  return els_tru_tm_;
}

std::vector<bool>  & small_tree_full::mus_tru_tm(){
  if(read_only_ && !c_mus_tru_tm_ && b_mus_tru_tm_){
    b_mus_tru_tm_->GetEntry(entry_);
    c_mus_tru_tm_ = true;
  }
  return mus_tru_tm_;
}

std::vector<bool>  & small_tree_full::tks_from_tau(){
  if(read_only_ && !c_tks_from_tau_ && b_tks_from_tau_){
    b_tks_from_tau_->GetEntry(entry_);
    c_tks_from_tau_ = true;
  }
  return tks_from_tau_;
}

std::vector<bool>  & small_tree_full::tks_from_tauhad(){
  if(read_only_ && !c_tks_from_tauhad_ && b_tks_from_tauhad_){
    b_tks_from_tauhad_->GetEntry(entry_);
    c_tks_from_tauhad_ = true;
  }
  return tks_from_tauhad_;
}

std::vector<bool>  & small_tree_full::tks_from_taulep(){
  if(read_only_ && !c_tks_from_taulep_ && b_tks_from_taulep_){
    b_tks_from_taulep_->GetEntry(entry_);
    c_tks_from_taulep_ = true;
  }
  return tks_from_taulep_;
}

std::vector<bool>  & small_tree_full::tks_from_w(){
  if(read_only_ && !c_tks_from_w_ && b_tks_from_w_){
    b_tks_from_w_->GetEntry(entry_);
    c_tks_from_w_ = true;
  }
  return tks_from_w_;
}

std::vector<bool>  & small_tree_full::tks_is_primary(){
  if(read_only_ && !c_tks_is_primary_ && b_tks_is_primary_){
    b_tks_is_primary_->GetEntry(entry_);
    c_tks_is_primary_ = true;
  }
  return tks_is_primary_;
}

std::vector<bool>  & small_tree_full::tks_is_primary_reliso(){
  if(read_only_ && !c_tks_is_primary_reliso_ && b_tks_is_primary_reliso_){
    b_tks_is_primary_reliso_->GetEntry(entry_);
    c_tks_is_primary_reliso_ = true;
  }
  return tks_is_primary_reliso_;
}

std::vector<bool>  & small_tree_full::tks_is_sig_lep(){
  if(read_only_ && !c_tks_is_sig_lep_ && b_tks_is_sig_lep_){
    b_tks_is_sig_lep_->GetEntry(entry_);
    c_tks_is_sig_lep_ = true;
  }
  return tks_is_sig_lep_;
}

std::vector<float>  & small_tree_full::badjets_eta(){
  if(read_only_ && !c_badjets_eta_ && b_badjets_eta_){
    b_badjets_eta_->GetEntry(entry_);
    c_badjets_eta_ = true;
  }
  return badjets_eta_;
}

std::vector<float>  & small_tree_full::badjets_id(){
  if(read_only_ && !c_badjets_id_ && b_badjets_id_){
    b_badjets_id_->GetEntry(entry_);
    c_badjets_id_ = true;
  }
  return badjets_id_;
}

std::vector<float>  & small_tree_full::badjets_m(){
  if(read_only_ && !c_badjets_m_ && b_badjets_m_){
    b_badjets_m_->GetEntry(entry_);
    c_badjets_m_ = true;
  }
  return badjets_m_;
}

std::vector<float>  & small_tree_full::badjets_phi(){
  if(read_only_ && !c_badjets_phi_ && b_badjets_phi_){
    b_badjets_phi_->GetEntry(entry_);
    c_badjets_phi_ = true;
  }
  return badjets_phi_;
}

std::vector<float>  & small_tree_full::badjets_pt(){
  if(read_only_ && !c_badjets_pt_ && b_badjets_pt_){
    b_badjets_pt_->GetEntry(entry_);
    c_badjets_pt_ = true;
  }
  return badjets_pt_;
}

std::vector<float>  & small_tree_full::els_miniso_10(){
  if(read_only_ && !c_els_miniso_10_ && b_els_miniso_10_){
    b_els_miniso_10_->GetEntry(entry_);
    c_els_miniso_10_ = true;
  }
  return els_miniso_10_;
}

std::vector<float>  & small_tree_full::els_miniso_10_ch(){
  if(read_only_ && !c_els_miniso_10_ch_ && b_els_miniso_10_ch_){
    b_els_miniso_10_ch_->GetEntry(entry_);
    c_els_miniso_10_ch_ = true;
  }
  return els_miniso_10_ch_;
}

std::vector<float>  & small_tree_full::els_miniso_tr10(){
  if(read_only_ && !c_els_miniso_tr10_ && b_els_miniso_tr10_){
    b_els_miniso_tr10_->GetEntry(entry_);
    c_els_miniso_tr10_ = true;
  }
  return els_miniso_tr10_;
}

std::vector<float>  & small_tree_full::els_miniso_tr10_ch(){
  if(read_only_ && !c_els_miniso_tr10_ch_ && b_els_miniso_tr10_ch_){
    b_els_miniso_tr10_ch_->GetEntry(entry_);
    c_els_miniso_tr10_ch_ = true;
  }
  return els_miniso_tr10_ch_;
}

std::vector<float>  & small_tree_full::els_mt(){
  if(read_only_ && !c_els_mt_ && b_els_mt_){
    b_els_mt_->GetEntry(entry_);
    c_els_mt_ = true;
  }
  return els_mt_;
}

std::vector<float>  & small_tree_full::els_reliso(){
  if(read_only_ && !c_els_reliso_ && b_els_reliso_){
    b_els_reliso_->GetEntry(entry_);
    c_els_reliso_ = true;
  }
  return els_reliso_;
}

std::vector<float>  & small_tree_full::els_reliso_r01(){
  if(read_only_ && !c_els_reliso_r01_ && b_els_reliso_r01_){
    b_els_reliso_r01_->GetEntry(entry_);
    c_els_reliso_r01_ = true;
  }
  return els_reliso_r01_;
}

std::vector<float>  & small_tree_full::els_reliso_r015(){
  if(read_only_ && !c_els_reliso_r015_ && b_els_reliso_r015_){
    b_els_reliso_r015_->GetEntry(entry_);
    c_els_reliso_r015_ = true;
  }
  return els_reliso_r015_;
}

std::vector<float>  & small_tree_full::els_reliso_r02(){
  if(read_only_ && !c_els_reliso_r02_ && b_els_reliso_r02_){
    b_els_reliso_r02_->GetEntry(entry_);
    c_els_reliso_r02_ = true;
  }
  return els_reliso_r02_;
}

std::vector<float>  & small_tree_full::els_reliso_r03(){
  if(read_only_ && !c_els_reliso_r03_ && b_els_reliso_r03_){
    b_els_reliso_r03_->GetEntry(entry_);
    c_els_reliso_r03_ = true;
  }
  return els_reliso_r03_;
}

std::vector<float>  & small_tree_full::els_reliso_r04(){
  if(read_only_ && !c_els_reliso_r04_ && b_els_reliso_r04_){
    b_els_reliso_r04_->GetEntry(entry_);
    c_els_reliso_r04_ = true;
  }
  return els_reliso_r04_;
}

std::vector<float>  & small_tree_full::els_tru_dr(){
  if(read_only_ && !c_els_tru_dr_ && b_els_tru_dr_){
    b_els_tru_dr_->GetEntry(entry_);
    c_els_tru_dr_ = true;
  }
  return els_tru_dr_;
}

std::vector<float>  & small_tree_full::fjets15_eta(){
  if(read_only_ && !c_fjets15_eta_ && b_fjets15_eta_){
    b_fjets15_eta_->GetEntry(entry_);
    c_fjets15_eta_ = true;
  }
  return fjets15_eta_;
}

std::vector<float>  & small_tree_full::fjets15_m(){
  if(read_only_ && !c_fjets15_m_ && b_fjets15_m_){
    b_fjets15_m_->GetEntry(entry_);
    c_fjets15_m_ = true;
  }
  return fjets15_m_;
}

std::vector<float>  & small_tree_full::fjets15_phi(){
  if(read_only_ && !c_fjets15_phi_ && b_fjets15_phi_){
    b_fjets15_phi_->GetEntry(entry_);
    c_fjets15_phi_ = true;
  }
  return fjets15_phi_;
}

std::vector<float>  & small_tree_full::fjets15_poscsv(){
  if(read_only_ && !c_fjets15_poscsv_ && b_fjets15_poscsv_){
    b_fjets15_poscsv_->GetEntry(entry_);
    c_fjets15_poscsv_ = true;
  }
  return fjets15_poscsv_;
}

std::vector<float>  & small_tree_full::fjets15_pt(){
  if(read_only_ && !c_fjets15_pt_ && b_fjets15_pt_){
    b_fjets15_pt_->GetEntry(entry_);
    c_fjets15_pt_ = true;
  }
  return fjets15_pt_;
}

std::vector<float>  & small_tree_full::fjets15_sumcsv(){
  if(read_only_ && !c_fjets15_sumcsv_ && b_fjets15_sumcsv_){
    b_fjets15_sumcsv_->GetEntry(entry_);
    c_fjets15_sumcsv_ = true;
  }
  return fjets15_sumcsv_;
}

std::vector<float>  & small_tree_full::fsubjets_eta(){
  if(read_only_ && !c_fsubjets_eta_ && b_fsubjets_eta_){
    b_fsubjets_eta_->GetEntry(entry_);
    c_fsubjets_eta_ = true;
  }
  return fsubjets_eta_;
}

std::vector<float>  & small_tree_full::fsubjets_m(){
  if(read_only_ && !c_fsubjets_m_ && b_fsubjets_m_){
    b_fsubjets_m_->GetEntry(entry_);
    c_fsubjets_m_ = true;
  }
  return fsubjets_m_;
}

std::vector<float>  & small_tree_full::fsubjets_phi(){
  if(read_only_ && !c_fsubjets_phi_ && b_fsubjets_phi_){
    b_fsubjets_phi_->GetEntry(entry_);
    c_fsubjets_phi_ = true;
  }
  return fsubjets_phi_;
}

std::vector<float>  & small_tree_full::fsubjets_poscsv(){
  if(read_only_ && !c_fsubjets_poscsv_ && b_fsubjets_poscsv_){
    b_fsubjets_poscsv_->GetEntry(entry_);
    c_fsubjets_poscsv_ = true;
  }
  return fsubjets_poscsv_;
}

std::vector<float>  & small_tree_full::fsubjets_pt(){
  if(read_only_ && !c_fsubjets_pt_ && b_fsubjets_pt_){
    b_fsubjets_pt_->GetEntry(entry_);
    c_fsubjets_pt_ = true;
  }
  return fsubjets_pt_;
}

std::vector<float>  & small_tree_full::fsubjets_sumcsv(){
  if(read_only_ && !c_fsubjets_sumcsv_ && b_fsubjets_sumcsv_){
    b_fsubjets_sumcsv_->GetEntry(entry_);
    c_fsubjets_sumcsv_ = true;
  }
  return fsubjets_sumcsv_;
}

std::vector<float>  & small_tree_full::genfjets_eta(){
  if(read_only_ && !c_genfjets_eta_ && b_genfjets_eta_){
    b_genfjets_eta_->GetEntry(entry_);
    c_genfjets_eta_ = true;
  }
  return genfjets_eta_;
}

std::vector<float>  & small_tree_full::genfjets_m(){
  if(read_only_ && !c_genfjets_m_ && b_genfjets_m_){
    b_genfjets_m_->GetEntry(entry_);
    c_genfjets_m_ = true;
  }
  return genfjets_m_;
}

std::vector<float>  & small_tree_full::genfjets_phi(){
  if(read_only_ && !c_genfjets_phi_ && b_genfjets_phi_){
    b_genfjets_phi_->GetEntry(entry_);
    c_genfjets_phi_ = true;
  }
  return genfjets_phi_;
}

std::vector<float>  & small_tree_full::genfjets_pt(){
  if(read_only_ && !c_genfjets_pt_ && b_genfjets_pt_){
    b_genfjets_pt_->GetEntry(entry_);
    c_genfjets_pt_ = true;
  }
  return genfjets_pt_;
}

std::vector<float>  & small_tree_full::genjets_eta(){
  if(read_only_ && !c_genjets_eta_ && b_genjets_eta_){
    b_genjets_eta_->GetEntry(entry_);
    c_genjets_eta_ = true;
  }
  return genjets_eta_;
}

std::vector<float>  & small_tree_full::genjets_m(){
  if(read_only_ && !c_genjets_m_ && b_genjets_m_){
    b_genjets_m_->GetEntry(entry_);
    c_genjets_m_ = true;
  }
  return genjets_m_;
}

std::vector<float>  & small_tree_full::genjets_phi(){
  if(read_only_ && !c_genjets_phi_ && b_genjets_phi_){
    b_genjets_phi_->GetEntry(entry_);
    c_genjets_phi_ = true;
  }
  return genjets_phi_;
}

std::vector<float>  & small_tree_full::genjets_pt(){
  if(read_only_ && !c_genjets_pt_ && b_genjets_pt_){
    b_genjets_pt_->GetEntry(entry_);
    c_genjets_pt_ = true;
  }
  return genjets_pt_;
}

std::vector<float>  & small_tree_full::glu_proj_frac(){
  if(read_only_ && !c_glu_proj_frac_ && b_glu_proj_frac_){
    b_glu_proj_frac_->GetEntry(entry_);
    c_glu_proj_frac_ = true;
  }
  return glu_proj_frac_;
}

std::vector<float>  & small_tree_full::jets_gen_pt(){
  if(read_only_ && !c_jets_gen_pt_ && b_jets_gen_pt_){
    b_jets_gen_pt_->GetEntry(entry_);
    c_jets_gen_pt_ = true;
  }
  return jets_gen_pt_;
}

std::vector<float>  & small_tree_full::jets_id(){
  if(read_only_ && !c_jets_id_ && b_jets_id_){
    b_jets_id_->GetEntry(entry_);
    c_jets_id_ = true;
  }
  return jets_id_;
}

std::vector<float>  & small_tree_full::jets_parton_pt(){
  if(read_only_ && !c_jets_parton_pt_ && b_jets_parton_pt_){
    b_jets_parton_pt_->GetEntry(entry_);
    c_jets_parton_pt_ = true;
  }
  return jets_parton_pt_;
}

std::vector<float>  & small_tree_full::jets_pt_from_mini(){
  if(read_only_ && !c_jets_pt_from_mini_ && b_jets_pt_from_mini_){
    b_jets_pt_from_mini_->GetEntry(entry_);
    c_jets_pt_from_mini_ = true;
  }
  return jets_pt_from_mini_;
}

std::vector<float>  & small_tree_full::mc_eta(){
  if(read_only_ && !c_mc_eta_ && b_mc_eta_){
    b_mc_eta_->GetEntry(entry_);
    c_mc_eta_ = true;
  }
  return mc_eta_;
}

std::vector<float>  & small_tree_full::mc_phi(){
  if(read_only_ && !c_mc_phi_ && b_mc_phi_){
    b_mc_phi_->GetEntry(entry_);
    c_mc_phi_ = true;
  }
  return mc_phi_;
}

std::vector<float>  & small_tree_full::mc_pt(){
  if(read_only_ && !c_mc_pt_ && b_mc_pt_){
    b_mc_pt_->GetEntry(entry_);
    c_mc_pt_ = true;
  }
  return mc_pt_;
}

std::vector<float>  & small_tree_full::mus_miniso_10(){
  if(read_only_ && !c_mus_miniso_10_ && b_mus_miniso_10_){
    b_mus_miniso_10_->GetEntry(entry_);
    c_mus_miniso_10_ = true;
  }
  return mus_miniso_10_;
}

std::vector<float>  & small_tree_full::mus_miniso_10_ch(){
  if(read_only_ && !c_mus_miniso_10_ch_ && b_mus_miniso_10_ch_){
    b_mus_miniso_10_ch_->GetEntry(entry_);
    c_mus_miniso_10_ch_ = true;
  }
  return mus_miniso_10_ch_;
}

std::vector<float>  & small_tree_full::mus_miniso_tr10(){
  if(read_only_ && !c_mus_miniso_tr10_ && b_mus_miniso_tr10_){
    b_mus_miniso_tr10_->GetEntry(entry_);
    c_mus_miniso_tr10_ = true;
  }
  return mus_miniso_tr10_;
}

std::vector<float>  & small_tree_full::mus_miniso_tr10_ch(){
  if(read_only_ && !c_mus_miniso_tr10_ch_ && b_mus_miniso_tr10_ch_){
    b_mus_miniso_tr10_ch_->GetEntry(entry_);
    c_mus_miniso_tr10_ch_ = true;
  }
  return mus_miniso_tr10_ch_;
}

std::vector<float>  & small_tree_full::mus_mt(){
  if(read_only_ && !c_mus_mt_ && b_mus_mt_){
    b_mus_mt_->GetEntry(entry_);
    c_mus_mt_ = true;
  }
  return mus_mt_;
}

std::vector<float>  & small_tree_full::mus_reliso(){
  if(read_only_ && !c_mus_reliso_ && b_mus_reliso_){
    b_mus_reliso_->GetEntry(entry_);
    c_mus_reliso_ = true;
  }
  return mus_reliso_;
}

std::vector<float>  & small_tree_full::mus_reliso_r01(){
  if(read_only_ && !c_mus_reliso_r01_ && b_mus_reliso_r01_){
    b_mus_reliso_r01_->GetEntry(entry_);
    c_mus_reliso_r01_ = true;
  }
  return mus_reliso_r01_;
}

std::vector<float>  & small_tree_full::mus_reliso_r015(){
  if(read_only_ && !c_mus_reliso_r015_ && b_mus_reliso_r015_){
    b_mus_reliso_r015_->GetEntry(entry_);
    c_mus_reliso_r015_ = true;
  }
  return mus_reliso_r015_;
}

std::vector<float>  & small_tree_full::mus_reliso_r02(){
  if(read_only_ && !c_mus_reliso_r02_ && b_mus_reliso_r02_){
    b_mus_reliso_r02_->GetEntry(entry_);
    c_mus_reliso_r02_ = true;
  }
  return mus_reliso_r02_;
}

std::vector<float>  & small_tree_full::mus_reliso_r03(){
  if(read_only_ && !c_mus_reliso_r03_ && b_mus_reliso_r03_){
    b_mus_reliso_r03_->GetEntry(entry_);
    c_mus_reliso_r03_ = true;
  }
  return mus_reliso_r03_;
}

std::vector<float>  & small_tree_full::mus_reliso_r04(){
  if(read_only_ && !c_mus_reliso_r04_ && b_mus_reliso_r04_){
    b_mus_reliso_r04_->GetEntry(entry_);
    c_mus_reliso_r04_ = true;
  }
  return mus_reliso_r04_;
}

std::vector<float>  & small_tree_full::mus_tru_dr(){
  if(read_only_ && !c_mus_tru_dr_ && b_mus_tru_dr_){
    b_mus_tru_dr_->GetEntry(entry_);
    c_mus_tru_dr_ = true;
  }
  return mus_tru_dr_;
}

std::vector<float>  & small_tree_full::subjets_csv(){
  if(read_only_ && !c_subjets_csv_ && b_subjets_csv_){
    b_subjets_csv_->GetEntry(entry_);
    c_subjets_csv_ = true;
  }
  return subjets_csv_;
}

std::vector<float>  & small_tree_full::subjets_eta(){
  if(read_only_ && !c_subjets_eta_ && b_subjets_eta_){
    b_subjets_eta_->GetEntry(entry_);
    c_subjets_eta_ = true;
  }
  return subjets_eta_;
}

std::vector<float>  & small_tree_full::subjets_id(){
  if(read_only_ && !c_subjets_id_ && b_subjets_id_){
    b_subjets_id_->GetEntry(entry_);
    c_subjets_id_ = true;
  }
  return subjets_id_;
}

std::vector<float>  & small_tree_full::subjets_m(){
  if(read_only_ && !c_subjets_m_ && b_subjets_m_){
    b_subjets_m_->GetEntry(entry_);
    c_subjets_m_ = true;
  }
  return subjets_m_;
}

std::vector<float>  & small_tree_full::subjets_mindr(){
  if(read_only_ && !c_subjets_mindr_ && b_subjets_mindr_){
    b_subjets_mindr_->GetEntry(entry_);
    c_subjets_mindr_ = true;
  }
  return subjets_mindr_;
}

std::vector<float>  & small_tree_full::subjets_phi(){
  if(read_only_ && !c_subjets_phi_ && b_subjets_phi_){
    b_subjets_phi_->GetEntry(entry_);
    c_subjets_phi_ = true;
  }
  return subjets_phi_;
}

std::vector<float>  & small_tree_full::subjets_pt(){
  if(read_only_ && !c_subjets_pt_ && b_subjets_pt_){
    b_subjets_pt_->GetEntry(entry_);
    c_subjets_pt_ = true;
  }
  return subjets_pt_;
}

std::vector<float>  & small_tree_full::subjets_subeta(){
  if(read_only_ && !c_subjets_subeta_ && b_subjets_subeta_){
    b_subjets_subeta_->GetEntry(entry_);
    c_subjets_subeta_ = true;
  }
  return subjets_subeta_;
}

std::vector<float>  & small_tree_full::subjets_subm(){
  if(read_only_ && !c_subjets_subm_ && b_subjets_subm_){
    b_subjets_subm_->GetEntry(entry_);
    c_subjets_subm_ = true;
  }
  return subjets_subm_;
}

std::vector<float>  & small_tree_full::subjets_subphi(){
  if(read_only_ && !c_subjets_subphi_ && b_subjets_subphi_){
    b_subjets_subphi_->GetEntry(entry_);
    c_subjets_subphi_ = true;
  }
  return subjets_subphi_;
}

std::vector<float>  & small_tree_full::subjets_subpt(){
  if(read_only_ && !c_subjets_subpt_ && b_subjets_subpt_){
    b_subjets_subpt_->GetEntry(entry_);
    c_subjets_subpt_ = true;
  }
  return subjets_subpt_;
}

std::vector<float>  & small_tree_full::tks_eta(){
  if(read_only_ && !c_tks_eta_ && b_tks_eta_){
    b_tks_eta_->GetEntry(entry_);
    c_tks_eta_ = true;
  }
  return tks_eta_;
}

std::vector<float>  & small_tree_full::tks_mini_ch(){
  if(read_only_ && !c_tks_mini_ch_ && b_tks_mini_ch_){
    b_tks_mini_ch_->GetEntry(entry_);
    c_tks_mini_ch_ = true;
  }
  return tks_mini_ch_;
}

std::vector<float>  & small_tree_full::tks_mini_ne(){
  if(read_only_ && !c_tks_mini_ne_ && b_tks_mini_ne_){
    b_tks_mini_ne_->GetEntry(entry_);
    c_tks_mini_ne_ = true;
  }
  return tks_mini_ne_;
}

std::vector<float>  & small_tree_full::tks_mt(){
  if(read_only_ && !c_tks_mt_ && b_tks_mt_){
    b_tks_mt_->GetEntry(entry_);
    c_tks_mt_ = true;
  }
  return tks_mt_;
}

std::vector<float>  & small_tree_full::tks_phi(){
  if(read_only_ && !c_tks_phi_ && b_tks_phi_){
    b_tks_phi_->GetEntry(entry_);
    c_tks_phi_ = true;
  }
  return tks_phi_;
}

std::vector<float>  & small_tree_full::tks_pt(){
  if(read_only_ && !c_tks_pt_ && b_tks_pt_){
    b_tks_pt_->GetEntry(entry_);
    c_tks_pt_ = true;
  }
  return tks_pt_;
}

std::vector<float>  & small_tree_full::tks_r02_ch(){
  if(read_only_ && !c_tks_r02_ch_ && b_tks_r02_ch_){
    b_tks_r02_ch_->GetEntry(entry_);
    c_tks_r02_ch_ = true;
  }
  return tks_r02_ch_;
}

std::vector<float>  & small_tree_full::tks_r02_ne(){
  if(read_only_ && !c_tks_r02_ne_ && b_tks_r02_ne_){
    b_tks_r02_ne_->GetEntry(entry_);
    c_tks_r02_ne_ = true;
  }
  return tks_r02_ne_;
}

std::vector<float>  & small_tree_full::tks_r03_ch(){
  if(read_only_ && !c_tks_r03_ch_ && b_tks_r03_ch_){
    b_tks_r03_ch_->GetEntry(entry_);
    c_tks_r03_ch_ = true;
  }
  return tks_r03_ch_;
}

std::vector<float>  & small_tree_full::tks_r03_ne(){
  if(read_only_ && !c_tks_r03_ne_ && b_tks_r03_ne_){
    b_tks_r03_ne_->GetEntry(entry_);
    c_tks_r03_ne_ = true;
  }
  return tks_r03_ne_;
}

std::vector<float>  & small_tree_full::tks_r04_ch(){
  if(read_only_ && !c_tks_r04_ch_ && b_tks_r04_ch_){
    b_tks_r04_ch_->GetEntry(entry_);
    c_tks_r04_ch_ = true;
  }
  return tks_r04_ch_;
}

std::vector<float>  & small_tree_full::tks_r04_ne(){
  if(read_only_ && !c_tks_r04_ne_ && b_tks_r04_ne_){
    b_tks_r04_ne_->GetEntry(entry_);
    c_tks_r04_ne_ = true;
  }
  return tks_r04_ne_;
}

std::vector<float>  & small_tree_full::tks_r05_ch(){
  if(read_only_ && !c_tks_r05_ch_ && b_tks_r05_ch_){
    b_tks_r05_ch_->GetEntry(entry_);
    c_tks_r05_ch_ = true;
  }
  return tks_r05_ch_;
}

std::vector<float>  & small_tree_full::tks_r05_ne(){
  if(read_only_ && !c_tks_r05_ne_ && b_tks_r05_ne_){
    b_tks_r05_ne_->GetEntry(entry_);
    c_tks_r05_ne_ = true;
  }
  return tks_r05_ne_;
}

std::vector<float>  & small_tree_full::tks_tru_dp(){
  if(read_only_ && !c_tks_tru_dp_ && b_tks_tru_dp_){
    b_tks_tru_dp_->GetEntry(entry_);
    c_tks_tru_dp_ = true;
  }
  return tks_tru_dp_;
}

std::vector<float>  & small_tree_full::tks_tru_dr(){
  if(read_only_ && !c_tks_tru_dr_ && b_tks_tru_dr_){
    b_tks_tru_dr_->GetEntry(entry_);
    c_tks_tru_dr_ = true;
  }
  return tks_tru_dr_;
}

std::vector<int>  & small_tree_full::els_tru_id(){
  if(read_only_ && !c_els_tru_id_ && b_els_tru_id_){
    b_els_tru_id_->GetEntry(entry_);
    c_els_tru_id_ = true;
  }
  return els_tru_id_;
}

std::vector<int>  & small_tree_full::els_tru_momid(){
  if(read_only_ && !c_els_tru_momid_ && b_els_tru_momid_){
    b_els_tru_momid_->GetEntry(entry_);
    c_els_tru_momid_ = true;
  }
  return els_tru_momid_;
}

std::vector<int>  & small_tree_full::fjets15_btags(){
  if(read_only_ && !c_fjets15_btags_ && b_fjets15_btags_){
    b_fjets15_btags_->GetEntry(entry_);
    c_fjets15_btags_ = true;
  }
  return fjets15_btags_;
}

std::vector<int>  & small_tree_full::fjets15_nconst(){
  if(read_only_ && !c_fjets15_nconst_ && b_fjets15_nconst_){
    b_fjets15_nconst_->GetEntry(entry_);
    c_fjets15_nconst_ = true;
  }
  return fjets15_nconst_;
}

std::vector<int>  & small_tree_full::fsubjets_btags(){
  if(read_only_ && !c_fsubjets_btags_ && b_fsubjets_btags_){
    b_fsubjets_btags_->GetEntry(entry_);
    c_fsubjets_btags_ = true;
  }
  return fsubjets_btags_;
}

std::vector<int>  & small_tree_full::fsubjets_nconst(){
  if(read_only_ && !c_fsubjets_nconst_ && b_fsubjets_nconst_){
    b_fsubjets_nconst_->GetEntry(entry_);
    c_fsubjets_nconst_ = true;
  }
  return fsubjets_nconst_;
}

std::vector<int>  & small_tree_full::genfjets_nconst(){
  if(read_only_ && !c_genfjets_nconst_ && b_genfjets_nconst_){
    b_genfjets_nconst_->GetEntry(entry_);
    c_genfjets_nconst_ = true;
  }
  return genfjets_nconst_;
}

std::vector<int>  & small_tree_full::genjets_genfjet_index(){
  if(read_only_ && !c_genjets_genfjet_index_ && b_genjets_genfjet_index_){
    b_genjets_genfjet_index_->GetEntry(entry_);
    c_genjets_genfjet_index_ = true;
  }
  return genjets_genfjet_index_;
}

std::vector<int>  & small_tree_full::genjets_isr_code(){
  if(read_only_ && !c_genjets_isr_code_ && b_genjets_isr_code_){
    b_genjets_isr_code_->GetEntry(entry_);
    c_genjets_isr_code_ = true;
  }
  return genjets_isr_code_;
}

std::vector<int>  & small_tree_full::jets_fjet15_index(){
  if(read_only_ && !c_jets_fjet15_index_ && b_jets_fjet15_index_){
    b_jets_fjet15_index_->GetEntry(entry_);
    c_jets_fjet15_index_ = true;
  }
  return jets_fjet15_index_;
}

std::vector<int>  & small_tree_full::jets_isr_code(){
  if(read_only_ && !c_jets_isr_code_ && b_jets_isr_code_){
    b_jets_isr_code_->GetEntry(entry_);
    c_jets_isr_code_ = true;
  }
  return jets_isr_code_;
}

std::vector<int>  & small_tree_full::mc_id(){
  if(read_only_ && !c_mc_id_ && b_mc_id_){
    b_mc_id_->GetEntry(entry_);
    c_mc_id_ = true;
  }
  return mc_id_;
}

std::vector<int>  & small_tree_full::mc_status(){
  if(read_only_ && !c_mc_status_ && b_mc_status_){
    b_mc_status_->GetEntry(entry_);
    c_mc_status_ = true;
  }
  return mc_status_;
}

std::vector<int>  & small_tree_full::mus_tru_id(){
  if(read_only_ && !c_mus_tru_id_ && b_mus_tru_id_){
    b_mus_tru_id_->GetEntry(entry_);
    c_mus_tru_id_ = true;
  }
  return mus_tru_id_;
}

std::vector<int>  & small_tree_full::mus_tru_momid(){
  if(read_only_ && !c_mus_tru_momid_ && b_mus_tru_momid_){
    b_mus_tru_momid_->GetEntry(entry_);
    c_mus_tru_momid_ = true;
  }
  return mus_tru_momid_;
}

std::vector<int>  & small_tree_full::subjets_fsubjet_index(){
  if(read_only_ && !c_subjets_fsubjet_index_ && b_subjets_fsubjet_index_){
    b_subjets_fsubjet_index_->GetEntry(entry_);
    c_subjets_fsubjet_index_ = true;
  }
  return subjets_fsubjet_index_;
}

std::vector<int>  & small_tree_full::subjets_nsub(){
  if(read_only_ && !c_subjets_nsub_ && b_subjets_nsub_){
    b_subjets_nsub_->GetEntry(entry_);
    c_subjets_nsub_ = true;
  }
  return subjets_nsub_;
}

std::vector<int>  & small_tree_full::tks_charge(){
  if(read_only_ && !c_tks_charge_ && b_tks_charge_){
    b_tks_charge_->GetEntry(entry_);
    c_tks_charge_ = true;
  }
  return tks_charge_;
}

std::vector<int>  & small_tree_full::tks_from_pv(){
  if(read_only_ && !c_tks_from_pv_ && b_tks_from_pv_){
    b_tks_from_pv_->GetEntry(entry_);
    c_tks_from_pv_ = true;
  }
  return tks_from_pv_;
}

std::vector<int>  & small_tree_full::tks_id(){
  if(read_only_ && !c_tks_id_ && b_tks_id_){
    b_tks_id_->GetEntry(entry_);
    c_tks_id_ = true;
  }
  return tks_id_;
}

std::vector<int>  & small_tree_full::tks_num_prongs(){
  if(read_only_ && !c_tks_num_prongs_ && b_tks_num_prongs_){
    b_tks_num_prongs_->GetEntry(entry_);
    c_tks_num_prongs_ = true;
  }
  return tks_num_prongs_;
}

std::vector<int>  & small_tree_full::tks_tru_id(){
  if(read_only_ && !c_tks_tru_id_ && b_tks_tru_id_){
    b_tks_tru_id_->GetEntry(entry_);
    c_tks_tru_id_ = true;
  }
  return tks_tru_id_;
}

std::vector<size_t>  & small_tree_full::mc_mom(){
  if(read_only_ && !c_mc_mom_ && b_mc_mom_){
    b_mc_mom_->GetEntry(entry_);
    c_mc_mom_ = true;
  }
  return mc_mom_;
}

unsigned  & small_tree_full::mc_type(){
  if(read_only_ && !c_mc_type_ && b_mc_type_){
    b_mc_type_->GetEntry(entry_);
    c_mc_type_ = true;
  }
  return mc_type_;
}

