# Instruction on how to do the fit and extratct the fit information

This instruciton assumes that you have generated RPV datacards already.

(1) Set up combine 

cmsrel CMSSW_7_4_7_patch1
cd CMSSW_7_4_7_patch1/src
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git checkout 74x-root6

(2) Perform Maximum Likelihood fit  

(3) Extract the post-fit information  

* Pull of nuiscance parameters 
* Post-fit Nb distribution 
* Post-fit normalizations

(4) Run the limit 

(5) Signal injection test
