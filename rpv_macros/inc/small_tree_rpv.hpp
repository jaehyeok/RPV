// small_tree_rpv: rpv version of small_tree to handle reduce tree ntuples
// File generated with generate_small_tree.exe

#ifndef H_SMALL_TREE_RPV
#define H_SMALL_TREE_RPV

#include <vector>
#include <string>

#include "TTree.h"
#include "TChain.h"

#include "small_tree.hpp"

class small_tree_rpv : public small_tree{
public:
  small_tree_rpv(); // Constructor to create tree
  small_tree_rpv(const std::string &filename); // Constructor to read tree

  virtual void GetEntry(const long entry);

  virtual void Fill();

  virtual std::string Type() const;

  virtual ~small_tree_rpv();

  virtual bool  const & pass() const;
  virtual bool  & pass();
  virtual float  const & eff_trig() const;
  virtual float  & eff_trig();
  virtual float  const & w_pu_rpv() const;
  virtual float  & w_pu_rpv();
  virtual std::vector<bool>  const & trig() const;
  virtual std::vector<bool>  & trig();
  virtual std::vector<float>  const & dr_bb() const;
  virtual std::vector<float>  & dr_bb();
  virtual std::vector<float>  const & sys_bctag() const;
  virtual std::vector<float>  & sys_bctag();

private:
  bool  pass_;
  TBranch *b_pass_;
  mutable bool c_pass_;
  float  eff_trig_;
  TBranch *b_eff_trig_;
  mutable bool c_eff_trig_;
  float  w_pu_rpv_;
  TBranch *b_w_pu_rpv_;
  mutable bool c_w_pu_rpv_;
  std::vector<bool>  trig_;
  std::vector<bool>  *p_trig_;
  TBranch *b_trig_;
  mutable bool c_trig_;
  std::vector<float>  dr_bb_;
  std::vector<float>  *p_dr_bb_;
  TBranch *b_dr_bb_;
  mutable bool c_dr_bb_;
  std::vector<float>  sys_bctag_;
  std::vector<float>  *p_sys_bctag_;
  TBranch *b_sys_bctag_;
  mutable bool c_sys_bctag_;
};

#endif
