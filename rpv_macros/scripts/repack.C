#include<iostream>
#include<string.h>
#include<stdio.h>

void CopyDir(TDirectory *source){
  //source->ls();
  TDirectory *savdir = gDirectory;
  TString dirname = source->GetName();
  if(dirname.Contains("ch")) dirname.Replace(dirname.First("ch"),dirname.First("_")+1,"");
  if(dirname.Contains("ch")) dirname.Replace(dirname.First("ch"),dirname.First("_")+1,"");
  //cout<<dirname<<endl;
  TDirectory *adir;
  if(!savdir->GetDirectory(dirname)) adir = savdir->mkdir(dirname);
  else adir = savdir->GetDirectory(dirname);
  adir->cd();

  TKey *key;
  TIter nextkey(source->GetListOfKeys());
  while((key = (TKey*) nextkey())){
    const char *classname = key->GetClassName();
    TClass *cl = gROOT->GetClass(classname);
    if (!cl) continue;
    if (cl->InheritsFrom("TDirectory")) {
      source->cd(key->GetName());
      //cout<<dirname<<endl;
      TDirectory *subdir = gDirectory;
      adir->cd();
      CopyDir(subdir);
      adir->cd();
    } 
    else if (cl->InheritsFrom("TTree")) {
      TTree *T = (TTree*)source->Get(key->GetName());
      adir->cd();
      TTree *newT = T->CloneTree();
      newT->Write();
    } 
    else if (cl->InheritsFrom("TH1")) {
      TH1F *h  = (TH1F*)source->Get(key->GetName());
      TH1F *h1 = (TH1F*)source->Get(key->GetName());
      adir->cd();
      //cout<<adir->GetPath()<<endl;
      if(adir->GetListOfKeys()->Contains(key->GetName())){
	TH1F *h2 = (TH1F*)adir->Get(key->GetName());
	h->Add(h1,h2);
	TString oname(key->GetName());
	adir->Delete(oname+";1");
      }
      adir->cd();
      h->Write();
    }
    else if (cl->InheritsFrom("TGraph")){
      TGraphAsymmErrors *h1 = (TGraphAsymmErrors*)source->Get(key->GetName());
      TGraphAsymmErrors *h = (TGraphAsymmErrors*)source->Get(key->GetName());
      adir->cd();
      if((adir->FindObjectAny(key->GetName())!=NULL)){
        TGraphAsymmErrors *h2 = (TGraphAsymmErrors*)adir->Get(key->GetName());
	TObjArray *l1 = new TObjArray();
	l1->Add(h2);
	h->Merge(l1);
	h->SetName(key->GetName());
	TString oname(key->GetName());
	adir->Delete(oname+";1");
	cout<<oname+";1"<<endl;
	adir->Delete(oname);
      }
      adir->cd();
      h->Write();
    }
    else {
      source->cd();
      TObject *obj = key->ReadObj();
      adir->cd();
      obj->Write();
      delete obj;
    }
  }
  adir->SaveSelf(kTRUE);
  savdir->cd();
}

void repack(TString year="2016"){
  //TFile *input = new TFile("fitDiagnostics_cr_"+year+".root","read");
  //TFile *input = new TFile("fitDiagnostics.root","read");
  TFile *input = new TFile("fitDiagnosticsTest.root","read");
  input->cd();
  gDirectory->cd("/");
  std::vector<TString> shapes = {"shapes_prefit","shapes_fit_b","shapes_fit_s"};
  std::vector<TString> norms = {"norm_prefit","norm_fit_b","norm_fit_s"};
  std::vector<TString> fits = {"fit_b","fit_s"};

  TFile *output = new TFile("mlfit_cr_"+year+".root","recreate");
  output->cd();

  for(auto shape : shapes){
    CopyDir(input->GetDirectory(shape));
  }
  for(auto norm : norms){
    TObject *obj = input->Get(norm);
    obj->Write();
  }
  for(auto fit : fits){
    TObject *obj = input->Get(fit)->Clone(fit);
    //cout<<fit<<endl;
    obj->Write();
  }

}
