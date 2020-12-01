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


void GetPostUncert()
{

    int TOTALTOY=100;

    // first index : qcd, ttbar, wjets, other, all bkg
    // second index: nb 
    // third index : toy
    vector<float> proc[5][18][4];

    for(int itoy=0; itoy<TOTALTOY; itoy++)
    {

        cout << " Processing toy " << itoy << endl; 
        TFile* mlfitfile = TFile::Open(Form("mlfit/mlfitM1200_seed%i.root",itoy+10000));

        if ( mlfitfile == 0x0  ) { continue; }
        RooFitResult *fit_s = (RooFitResult*) mlfitfile->Get("fit_s");
        if( fit_s == 0x0 )          { mlfitfile->Close(); continue; }
        if( fit_s->status() != 0)   { delete fit_s; mlfitfile->Close(); continue; } // fit status == 0 : requires fit quality


        // loop over bins
        for(int ibin=0; ibin<18; ibin++) 
        { 
            if(ibin>=6 && ibin<=10)  continue;

            for(int inb=1; inb<5; inb++)
            {  
                float qcd   = (static_cast<TH1D*>(mlfitfile->Get(Form("shapes_fit_s/bin%i/qcd",ibin))))->GetBinContent(inb+1);  
                float ttbar = (static_cast<TH1D*>(mlfitfile->Get(Form("shapes_fit_s/bin%i/ttbar",ibin))))->GetBinContent(inb+1);  
                float wjets = (static_cast<TH1D*>(mlfitfile->Get(Form("shapes_fit_s/bin%i/wjets",ibin))))->GetBinContent(inb+1);  
                float other = (static_cast<TH1D*>(mlfitfile->Get(Form("shapes_fit_s/bin%i/other",ibin))))->GetBinContent(inb+1);  

                proc[0][ibin][inb-1].push_back(qcd); 
                proc[1][ibin][inb-1].push_back(ttbar); 
                proc[2][ibin][inb-1].push_back(wjets); 
                proc[3][ibin][inb-1].push_back(other); 
                proc[4][ibin][inb-1].push_back(qcd+ttbar+wjets+other); 
                //cout << ibin << " " << inb << " " << GOODTOY << " :: " << proc[0][ibin][inb-1].at(GOODTOY) << endl;
            }
        }

        mlfitfile->Close();
    } 

    cout << "-------------------------- " << endl;  

    // first index : qcd, ttbar, wjets, other
    // second index: nb 
    // third index : toy
    float err[5][18][4]; 
    
    // Get mean and the width 
    for(int ibin=0; ibin<18; ibin++)
    { 
        if(ibin>=6 && ibin<=10)  continue;
        if(ibin!=16)  continue;

        for(int inb=1; inb<5; inb++)
        { 
            for(int iproc=0; iproc<5; iproc++) 
            { 
                err[iproc][ibin][inb-1] = GetRMS(proc[iproc][ibin][inb-1]);  
                cout << iproc << " ::: " << ibin << " " << inb << " :: " << err[iproc][ibin][inb-1] << endl;
            }
        }
    } 

}
