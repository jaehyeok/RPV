// small_tree_rpv: rpv version of small_tree to handle reduce tree ntuples
//File generated with generate_small_tree.exe

#include "small_tree.hpp"

#include "small_tree_rpv.hpp"

#include <stdexcept>
#include <string>
#include <vector>

#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"

using namespace std;

small_tree_rpv::small_tree_rpv():
  small_tree(),
  pass_(0),
  b_pass_(tree_.Branch("pass", &pass_)),
  c_pass_(false),
  eff_trig_(0),
  b_eff_trig_(tree_.Branch("eff_trig", &eff_trig_)),
  c_eff_trig_(false),
  w_pu_rpv_(0),
  b_w_pu_rpv_(tree_.Branch("w_pu_rpv", &w_pu_rpv_)),
  c_w_pu_rpv_(false),
  trig_(0),
  p_trig_(&trig_),
  b_trig_(tree_.Branch("trig", &p_trig_)),
  c_trig_(false),
  dr_bb_(0),
  p_dr_bb_(&dr_bb_),
  b_dr_bb_(tree_.Branch("dr_bb", &p_dr_bb_)),
  c_dr_bb_(false),
  sys_bctag_(0),
  p_sys_bctag_(&sys_bctag_),
  b_sys_bctag_(tree_.Branch("sys_bctag", &p_sys_bctag_)),
  c_sys_bctag_(false){
}

small_tree_rpv::small_tree_rpv(const string &filename):
  small_tree(filename),
  pass_(0),
  b_pass_(NULL),
  c_pass_(false),
  eff_trig_(0),
  b_eff_trig_(NULL),
  c_eff_trig_(false),
  w_pu_rpv_(0),
  b_w_pu_rpv_(NULL),
  c_w_pu_rpv_(false),
  trig_(0),
  p_trig_(&trig_),
  b_trig_(NULL),
  c_trig_(false),
  dr_bb_(0),
  p_dr_bb_(&dr_bb_),
  b_dr_bb_(NULL),
  c_dr_bb_(false),
  sys_bctag_(0),
  p_sys_bctag_(&sys_bctag_),
  b_sys_bctag_(NULL),
  c_sys_bctag_(false){
  chain_.SetBranchAddress("pass", &pass_, &b_pass_);
  chain_.SetBranchAddress("eff_trig", &eff_trig_, &b_eff_trig_);
  chain_.SetBranchAddress("w_pu_rpv", &w_pu_rpv_, &b_w_pu_rpv_);
  chain_.SetBranchAddress("trig", &p_trig_, &b_trig_);
  chain_.SetBranchAddress("dr_bb", &p_dr_bb_, &b_dr_bb_);
  chain_.SetBranchAddress("sys_bctag", &p_sys_bctag_, &b_sys_bctag_);
}

void small_tree_rpv::Fill(){
  small_tree::Fill();
  //Resetting variables
  pass_ = static_cast<bool >(bad_val_);
  eff_trig_ = static_cast<float >(bad_val_);
  w_pu_rpv_ = static_cast<float >(bad_val_);
  trig_.clear();
  dr_bb_.clear();
  sys_bctag_.clear();
}

string small_tree_rpv::Type() const{
  return "rpv";
}

small_tree_rpv::~small_tree_rpv(){
}

void small_tree_rpv::GetEntry(const long entry){
  small_tree::GetEntry(entry);

  c_pass_ = false;
  c_eff_trig_ = false;
  c_w_pu_rpv_ = false;
  c_trig_ = false;
  c_dr_bb_ = false;
  c_sys_bctag_ = false;
}

bool  const & small_tree_rpv::pass() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_pass_ && b_pass_){
    b_pass_->GetEntry(entry_);
    c_pass_ = true;
  }
  return pass_;
}

float  const & small_tree_rpv::eff_trig() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_eff_trig_ && b_eff_trig_){
    b_eff_trig_->GetEntry(entry_);
    c_eff_trig_ = true;
  }
  return eff_trig_;
}

float  const & small_tree_rpv::w_pu_rpv() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_w_pu_rpv_ && b_w_pu_rpv_){
    b_w_pu_rpv_->GetEntry(entry_);
    c_w_pu_rpv_ = true;
  }
  return w_pu_rpv_;
}

std::vector<bool>  const & small_tree_rpv::trig() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_trig_ && b_trig_){
    b_trig_->GetEntry(entry_);
    c_trig_ = true;
  }
  return trig_;
}

std::vector<float>  const & small_tree_rpv::dr_bb() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_dr_bb_ && b_dr_bb_){
    b_dr_bb_->GetEntry(entry_);
    c_dr_bb_ = true;
  }
  return dr_bb_;
}

std::vector<float>  const & small_tree_rpv::sys_bctag() const{
  if(!read_only_){
    throw std::logic_error("Trying to write to const tree.");
  }
  if(!c_sys_bctag_ && b_sys_bctag_){
    b_sys_bctag_->GetEntry(entry_);
    c_sys_bctag_ = true;
  }
  return sys_bctag_;
}

bool  & small_tree_rpv::pass(){
  if(read_only_ && !c_pass_ && b_pass_){
    b_pass_->GetEntry(entry_);
    c_pass_ = true;
  }
  return pass_;
}

float  & small_tree_rpv::eff_trig(){
  if(read_only_ && !c_eff_trig_ && b_eff_trig_){
    b_eff_trig_->GetEntry(entry_);
    c_eff_trig_ = true;
  }
  return eff_trig_;
}

float  & small_tree_rpv::w_pu_rpv(){
  if(read_only_ && !c_w_pu_rpv_ && b_w_pu_rpv_){
    b_w_pu_rpv_->GetEntry(entry_);
    c_w_pu_rpv_ = true;
  }
  return w_pu_rpv_;
}

std::vector<bool>  & small_tree_rpv::trig(){
  if(read_only_ && !c_trig_ && b_trig_){
    b_trig_->GetEntry(entry_);
    c_trig_ = true;
  }
  return trig_;
}

std::vector<float>  & small_tree_rpv::dr_bb(){
  if(read_only_ && !c_dr_bb_ && b_dr_bb_){
    b_dr_bb_->GetEntry(entry_);
    c_dr_bb_ = true;
  }
  return dr_bb_;
}

std::vector<float>  & small_tree_rpv::sys_bctag(){
  if(read_only_ && !c_sys_bctag_ && b_sys_bctag_){
    b_sys_bctag_->GetEntry(entry_);
    c_sys_bctag_ = true;
  }
  return sys_bctag_;
}

