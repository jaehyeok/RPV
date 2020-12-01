float AddInQuad(float a, float b)
{ 
    return TMath::Sqrt(a*a+b*b);
}

void GetPreUncert()
{ 

    TFile* infile = TFile::Open("sum_rescaled.root");
    
     // MC stats  
     // PDF
     // btag_bc 

    //float err_qcd[18][4], err_ttbar[18][4], err_wjets[18][4], err_other[18][4]; 
    float err[4][18][4];
   
    
    // loop over bins
    for(int ibin=0; ibin<18; ibin++) 
    { 
        if(ibin>=6 && ibin<=9) continue;
        if(ibin!=15) continue;

        for(int iproc=0; iproc<4; iproc++) 
        {
            std::string process; 
            if(iproc==0)  process = "qcd";
            if(iproc==1)  process = "ttbar";
            if(iproc==2)  process = "wjets";
            if(iproc==3)  process = "other"; 

            // loop over nb bins
            for(int inb=1; inb<5; inb++)  
            {  
                cout << "... " << process << endl;
                float central;
                float up; 


                if(infile->Get(Form("bin%i/%s", ibin, process.c_str()))==0x0) continue;
                central = ((TH1F*)infile->Get(Form("bin%i/%s", ibin, process.c_str())))->GetBinContent(inb+1);
                
                if(central !=0)
                {
                    up = ((TH1F*)infile->Get(Form("bin%i/%s_btag_bcUp", ibin, process.c_str())))->GetBinContent(inb+1);
                    err[iproc][ibin][inb] = TMath::Abs(up-central)/central; 

                    cout << "btag: " << ibin << " " << inb << " " << err[iproc][ibin][inb]<< endl;

                    // Stats
                    if(infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb))!=0x0)
                    {
                        up = ((TH1F*)infile->Get(Form("bin%i/%s_mcstat_%s_bin%i_nb%iUp", ibin, process.c_str(), process.c_str(),ibin,inb)))->GetBinContent(inb+1);

                        cout << "stat: " << ibin << " " << inb << " " << TMath::Abs(up-central)/central<< endl;
                        err[iproc][ibin][inb] = AddInQuad(err[iproc][ibin][inb],TMath::Abs(up-central)/central); 
                    }
                }

                cout << "both: " <<  ibin << " " << inb << " " << err[iproc][ibin][inb]<< endl;

            }
        }
    }

    infile->Close();
}
