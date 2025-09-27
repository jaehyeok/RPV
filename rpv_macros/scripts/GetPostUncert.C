float GetRMS(std::vector<float> proc) 
{ 
   // Get mean    
   float mean=0;
   for(int i=0; i<proc.size(); i++) 
   { 
        mean = mean + proc.at(i);    
   }
   mean = mean/proc.size();

   // Ger rms 
   float rms=0;
   for(int i=0; i<proc.size(); i++) 
   { 
        rms = rms + (mean - proc.at(i))*(mean - proc.at(i));    
   } 
   rms = TMath::Sqrt(rms/proc.size());
    
   return rms/mean;
}


void GetPostUncert(bool full=true, TString year="UL2016", TString step="step1")
{

    int TOTALTOY=100;

    // first index : qcd, ttbar, wjets, other, all bkg
    // second index: nb 
    // third index : toy
    vector<float> proc[5][15][3];

    for(int itoy=0; itoy<TOTALTOY; itoy++)
    {

        cout << " Processing toy " << itoy << endl; 
        //TFile* mlfitfile = TFile::Open(Form("mlfit/mlfitM1200_seed%i.root",itoy+10000));
        //TFile* mlfitfile = TFile::Open(Form("FitDiagnostics/fitDiagnostics_seed%i.root",itoy+1));
        //TFile* mlfitfile = TFile::Open(Form("postfit_uncert/fitDiagnosticsseed%i_M2200.root",itoy+1));
        //TFile* mlfitfile = TFile::Open(Form("out_injection/fitDiagnostics_M1500_%i.root",itoy+1));
        TFile* mlfitfile;
        //if(year==2016) mlfitfile = TFile::Open(Form("out_injection_%s_240606/fitDiagnostics_M1800_16_%i.root",step.Data(),itoy+1));
        //else  mlfitfile = TFile::Open(Form("out_injection_%s_240606/fitDiagnostics_M1800_78_%i.root",step.Data(),itoy+1));
        if(year=="UL2016") mlfitfile = TFile::Open(Form("out_injection_%s_250122/fitDiagnostics_M1800_16_%i.root",step.Data(),itoy+1));
        else  mlfitfile = TFile::Open(Form("out_injection_%s_250122/fitDiagnostics_M1800_78_%i.root",step.Data(),itoy+1));
        
        if ( mlfitfile == 0x0  ) { continue;}
        RooFitResult *fit_s = (RooFitResult*) mlfitfile->Get("fit_s");
        if( fit_s == 0x0 )          { mlfitfile->Close(); continue; }
        if( fit_s->status() != 0)   { delete fit_s; mlfitfile->Close(); continue; } // fit status == 0 : requires fit quality
	if( mlfitfile->GetDirectory("shapes_fit_b") == 0x0 )   { mlfitfile->Close(); continue; }


        // loop over bins
        for(int ibin=22; ibin<=36; ibin++) 
        { 
          bool flag_step=false;
          if(step=="step1"){
            if(ibin==24) flag_step=true;
            if(ibin==27) flag_step=true;
            if(ibin>=30) flag_step=true;
          }
          else if(step=="step2"){
            if(ibin>=30) flag_step=true;
          }
	  else if(step=="step3"){
	    if(ibin>=32) flag_step=true;
	    else if(ibin==30) flag_step=true;
	  }
          if(flag_step) continue;

          cout << "bin " << ibin << endl; 

          for(int imj=1; imj<4; imj++)
          {
	    float qcd, ttbar, wjets, other; 
            if(year=="UL2017")
            {
              qcd   = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/qcd",ibin))))->GetBinContent(imj);  
              ttbar = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/ttbar",ibin))))->GetBinContent(imj);  
              wjets = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/wjets",ibin))))->GetBinContent(imj);  
              other = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/other",ibin))))->GetBinContent(imj);  
            }
            else if(year=="UL2018")
            {
              qcd   = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/qcd",ibin))))->GetBinContent(imj);  
              ttbar = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/ttbar",ibin))))->GetBinContent(imj);  
              wjets = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/wjets",ibin))))->GetBinContent(imj);  
              other = (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/other",ibin))))->GetBinContent(imj);  
            }
            else
            {
	      if(year=="UL2016" && step=="step3" && ibin==31) {
		cout << "DEBUG" << endl; // because yields of qcd in bin31 and UL2016_postVFP are 0 for all MJ bins
                qcd   =   (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/qcd",ibin))))->GetBinContent(imj);
	      }
	      else {
                qcd   =   (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/qcd",ibin))))->GetBinContent(imj)  
                        + (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/qcd",ibin))))->GetBinContent(imj);  
	      }
              ttbar =   (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/ttbar",ibin))))->GetBinContent(imj)  
                      + (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/ttbar",ibin))))->GetBinContent(imj);  
              wjets =   (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/wjets",ibin))))->GetBinContent(imj)  
                      + (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/wjets",ibin))))->GetBinContent(imj);  
              other =   (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch1_bin%i/other",ibin))))->GetBinContent(imj)  
                      + (static_cast<TH1F*>(mlfitfile->Get(Form("shapes_fit_b/ch2_bin%i/other",ibin))))->GetBinContent(imj);  
            }
            proc[0][ibin-22][imj-1].push_back(qcd); 
            proc[1][ibin-22][imj-1].push_back(ttbar); 
            proc[2][ibin-22][imj-1].push_back(wjets); 
            proc[3][ibin-22][imj-1].push_back(other); 
            proc[4][ibin-22][imj-1].push_back(qcd+ttbar+wjets+other); 
            cout << ibin << " " << imj << " :: " << proc[0][ibin-22][imj-1].at(0) << endl;
          }
        }

        mlfitfile->Close();
    } 

    cout << "-------------------------- " << endl;  

    // first index : qcd, ttbar, wjets, other
    // second index: nb 
    // third index : toy
    float err[5][15][3]; 

    TFile *outputrootfile = new TFile(Form("rpv_postfit_err%s_%s_%s.root",full?"":"_control", step.Data(), year.Data()), "RECREATE");
    gROOT->cd();
    outputrootfile->cd();

    cout<<step<<endl;

    // Get mean and the width 
    //for(int ibin=22; ibin<=36; ibin++)
    for(int ibin=22; ibin<=36; ibin++)
    {
      bool flag_step=false;
      if(step=="step1"){
        if(ibin==24) flag_step=true;
        if(ibin==27) flag_step=true;
        if(ibin>=30) flag_step=true;
      }
      else if(step=="step2"){
        if(ibin>=30) flag_step=true;
      }
      if(flag_step) continue;

      TH1D* hist_qcd    = new TH1D(Form("h_bin%i_qcd", ibin), Form("h_bin%i_qcd", ibin), 4, 1, 5);
      TH1D* hist_ttbar  = new TH1D(Form("h_bin%i_ttbar", ibin), Form("h_bin%i_ttbar", ibin), 4, 1, 5);
      TH1D* hist_wjets  = new TH1D(Form("h_bin%i_wjets", ibin), Form("h_bin%i_wjets", ibin), 4, 1, 5);
      TH1D* hist_other  = new TH1D(Form("h_bin%i_other", ibin), Form("h_bin%i_other", ibin), 4, 1, 5);
      TH1D* hist_allbkg = new TH1D(Form("h_bin%i_allbkg", ibin), Form("h_bin%i_allbkg", ibin), 4, 1, 5);

      for(int imj=1; imj<4; imj++)
      { 
        hist_qcd->SetBinContent(imj, GetRMS(proc[0][ibin-22][imj-1]));
        hist_ttbar->SetBinContent(imj, GetRMS(proc[1][ibin-22][imj-1]));
        hist_wjets->SetBinContent(imj, GetRMS(proc[2][ibin-22][imj-1]));
        hist_other->SetBinContent(imj, GetRMS(proc[3][ibin-22][imj-1]));
        hist_allbkg->SetBinContent(imj, GetRMS(proc[4][ibin-22][imj-1]));

        for(int iproc=0; iproc<5; iproc++) 
        { 
          err[iproc][ibin-22][imj-1] = GetRMS(proc[iproc][ibin-22][imj-1]);  
          cout << iproc << " ::: " << ibin << " " << imj << " :: " << err[iproc][ibin-22][imj-1] << endl;
        }
      }
      hist_qcd->SetDirectory(0); hist_qcd->Write();
      hist_ttbar->SetDirectory(0); hist_ttbar->Write();
      hist_wjets->SetDirectory(0); hist_wjets->Write();
      hist_other->SetDirectory(0); hist_other->Write();
      hist_allbkg->SetDirectory(0); hist_allbkg->Write();
    } 
    outputrootfile->Close();
}
