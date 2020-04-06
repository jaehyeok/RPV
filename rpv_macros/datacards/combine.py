import os
import sys

mass = sys.argv[1]

if len(sys.argv) == 2:
	g = open("datacards/result.txt","w")
	dname = 'datacards/datacard_M'+str(mass)+'_mconly_'
	for nbs in {"nb1","nb2","nb3","nb4"}:
		for njets in {"low","med","high"}:
			region = "sr"
			if nbs=="nb1" or njets=="low":
				region = "cr"
			fname = dname+region+"_"+nbs+"_"+njets+"njets_nopdfoutput_nominal_newnt.dat"
			os.system("datacards/combine.sh "+fname)
			f = open("datacards/combine.txt","r")
			res = f.read()
			f.close()
			spl_res = res.split()
			exp50 = spl_res[spl_res.index("50.0%:")+3]
			pline = nbs + " / " + njets + "jets : " + exp50 + "\n"
			g.write(pline)
	g.close()
