Instruction on how to do the fit and extratct the fit information
=== 

This instruciton assumes that you have generated RPV datacards already.

#### Set up combine 

```
source SetupComibine/setup.sh
```

#### Perform Maximum Likelihood fit  

(1) Copy datacards   
```
mkdir datacards 
cd datacards 
cp /homes/jaehyeokyoo/cmssw/CMSSW_7_4_7_patch1/src/workspace/unblinding/datacard_M1200.dat . 
```

(2) Convert datacards to workspace  
```
for mass in {1000,1100,1200,1300,1400}; do echo $mass; text2workspace.py datacard_M${mass}.dat -o workspace_M${mass}.root -P HiggsAnalysis.CombinedLimit.RPVModel:rpvModel
```

(3) Run combine 
```
for mass in {1000,1100,1200,1300,1400}; do echo $mass; combine -M MaxLikelihoodFit  -n M${mass}  workspace_M${mass}.root --saveNorm --minimizerTolerance 0.9999999; done
```
You might need to check the convergence of the fit and change `--minimizerTolerance` to make it converge. The convergence of fit can be checked by `fit_s->status()` in `mlfitM1200.root` file. It should be 0 for a good fit. The meaning of the number is `status = 100 * hesseStatus + 10 * minosStatus +  minuit2SummaryStatus` [1-3].

#### Extract the post-fit information  

(1) Make a directory where the plots will go
```
mkdir plots
```
(2) Generate the pull of nuiscance parameters and Post-fit Nb distribution 
```
root -b -q plotresults.cc
```
(3) Print post-fit normalizations
```
python mlfitNormsToText.py mlfitM1200.root
```

#### Run the limit 

```
for mass in {1000,1100,1200,1300,1400}; do echo $mass; combine -M Asymptotic -n M${mass}  workspace_M${mass}.root; done
root -b -q limits.cc
```

#### Signal injection test


## References
[1] https://root.cern.ch/phpBB3/viewtopic.php?t=16764
[2] http://root.cern.ch/root/htmldoc/ROOT__Minuit2__Minuit2Minimizer.html#ROOT__Minuit2__Minuit2Minimizer:Hesse
[3] http://root.cern.ch/root/htmldoc/ROOT__Minuit2__Minuit2Minimizer.html#ROOT__Minuit2__Minuit2Minimizer:GetMinosError
