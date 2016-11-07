#! /usr/bin/env python
import os
import sys

# What module to run
makeCards = True
makeWorkspaces = True
runCombine = True
makePlots = True

# Setup directories
dirBase = "/net/top/homes/rohan/RPV/Fit/CMSSW_7_4_7_patch1/src/HiggsAnalysis/" 
dirDC = dirBase + "datacards/"
dirWS = dirBase + "workspaces/"
dirCombine = dirBase +"CombinedLimit/"

if len(sys.argv) != 2:
    print("./run/run_btaginjections.py [sum_rescaled.root]")
    print("The argument takes the original (unvaried) sum_rescaled.root file, i.e. the one used in inject_wbtag_sig.exe \n")
    sys.exit()

# Setup variables
dirname = os.path.dirname(sys.argv[1]) + '/'
filename = os.path.basename(sys.argv[1])
basename = os.path.splitext(filename)[0]
identifier = basename.replace("sum_rescaled_mconly_","")

# Make datacards from the sum_rescaled files
if makeCards:
    os.system("./compile.sh")

    # Get list of sum_rescaled files 
    files = sorted([i for i in os.listdir(dirname) if basename in i and 'sig' in i and i is not filename])

    for file in sorted(files):        
        print "Making datacard for file: " + file
        os.system("./run/make_rpv_datacard.exe 1500 mconly " + file)

    # Move cards and copy only the full datacards to combine work area
    print("\nMoving cards and corresponding sum_rescaled files to " + dirDC+"\n")
    os.system("mv *.dat ./cards/")
    os.system("find cards/ -name *" + identifier + "*.dat ! -name *_sr_* ! -name *_cr_* -exec cp {} " + dirDC +" \\;")
    # Copy sum_rescaled files to combine work area
    os.system("cp " + dirname + basename + "*sig*.root " + dirDC) 

# Make workspaces from datacards (not needed but is a precaution)
if makeWorkspaces:
    
    os.chdir(dirCombine)

    # Convert cards
    for card in sorted([i for i in os.listdir(dirDC) if identifier in i and ".dat" in i]):
        print("Making workspace for card: " + card)
        os.system("./scripts/text2workspace.py " + dirDC + card + " -o " + dirWS+ "ws_"+card.lstrip("datacard_").replace(".dat",".root"))

# Run combine to get results
if runCombine:
    
    os.chdir(dirCombine)

    # Make text files of the results
    if os.path.isfile("bctag_results.txt"): os.system("rm bctag_results.txt")
    if os.path.isfile("udsgtag_results.txt"): os.system("rm udsgtag_results.txt")

    os.system("touch bctag_results.txt")
    os.system("touch udsgtag_results.txt")

    os.system("echo ")

    # For each bctag variation, get signal strength and pulls and output to bctag_results
    for workspace in sorted([i for i in os.listdir(dirWS) if identifier in i and "bctag" in i]):
        print("Running combine for workspace: " + workspace)
        os.system("echo " + workspace + " >> bctag_results.txt")
        os.system("combine -M MaxLikelihoodFit  -n " + workspace.lstrip("ws").rstrip(".root") + " ../workspaces/"+ workspace +" --saveNorm --minimizerTolerance 0.9999999 | grep Best\\ fit >> bctag_results.txt")
        os.system("python test/diffNuisances.py --vtol=0.3 --vtol2=0.75 --stol=1000 --stol2=1000 mlfit" + workspace.lstrip("ws") + " >> bctag_results.txt")
        os.system("echo >> bctag_results.txt")

    # For each udsgtag variation, get signal strength and pulls and output to udsgtag_results
    for workspace in sorted([i for i in os.listdir(dirWS) if identifier in i and "udsgtag" in i]):
        print("Running combine for workspace: " + workspace)
        os.system("echo " + workspace + " >> udsgtag_results.txt")
        os.system("combine -M MaxLikelihoodFit  -n " + workspace.lstrip("ws").rstrip(".root") + " ../workspaces/"+ workspace +" --saveNorm --minimizerTolerance 0.9999999 | grep Best\\ fit >> udsgtag_results.txt")
        os.system("python test/diffNuisances.py --vtol=0.3 --vtol2=0.75 --stol=1000 --stol2=1000 mlfit" + workspace.lstrip("ws") + " >> udsgtag_results.txt")
        os.system("echo >> udsgtag_results.txt")

    # Move the results into a directory
    os.mkdir("M1500_" + identifier)
    os.system("mv *_results.txt M1500_" + identifier  + "/")

# Make plots using plotresult.cc
if makePlots:

    os.chdir(dirCombine)

    # Run plotresult.cc for each mlfit, then copy plots to directory
    for plot in sorted([i for i in os.listdir(dirCombine) if "mlfit_" in i]):
        print("Making plots for fit: " + plot)
        dirPlot = plot.lstrip("mlfit_").rstrip(".root")
        if not os.path.isdir("./plots/" + dirPlot):
            os.mkdir("./plots/" + dirPlot)
        os.system("cp " + plot + " mlfit.root")
        os.system("cp ../workspaces/ws_" + plot.lstrip("mlfit_") + " workspace.root")
        os.system("root -b -l -q ~/RPV/Fit/plotresult.cc")
        os.system("cp ./plots/*.pdf ./plots/" + dirPlot)
