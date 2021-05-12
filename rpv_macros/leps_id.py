#!/usr/bin/python
import re
import sys

if __name__=='__main__' :
	year=sys.argv[1] 
	ratio = 0.0
	list_stats = []
	list_bin = ['njets=4,5', 'njets=6,7', 'njets=8,9', 'njets=10+']
	list_em = ['electron', '    muon']
	f = open('leps_id'+year+'.txt')
	i=0
	flag_mergedlep=False
	qcd_stats_rl_em = 0
	qcd_stats_fl_em = 0
	data_stats_rl_em = 0
	data_stats_fl_em = 0
	print('                                  QCD(RL)    Data(RL)   QCD(FL)   Data(RL)  QCD Ratio  Data Ratio   Data/QCD')
	print('-------------------------------------------------------------------------------------------------------------')
	for line in f :
		if line.startswith('Markers') :
			numbers_str = re.findall("\d+", line)
			ratio_str = numbers_str[0]+"."+numbers_str[1]
			ratio = float(ratio_str)
		if line.startswith('W+ jets') or line.startswith('QCD') or line.startswith('Data'):
			stats_str = line.split(':')[2]
			stats = float(stats_str)
			if line.startswith('W+ jets') or line.startswith('QCD') :
				ratio = 100
				stats = stats*ratio/100
			list_stats.append(stats)
		if line=='\n' and len(list_stats)!=0:
			qcd_stats_fl = list_stats[2] - list_stats[0]
			data_stats_fl = list_stats[4] - list_stats[0]
			qcd_stats_rl = list_stats[3] - list_stats[1]
			data_stats_rl = list_stats[5] - list_stats[1]
			if i%2==0 :
				qcd_stats_rl_em = qcd_stats_rl
				qcd_stats_fl_em = qcd_stats_fl
				data_stats_rl_em = data_stats_rl
				data_stats_fl_em = data_stats_fl
				flag_mergedlep = False
			elif i%2==1 :
				qcd_stats_rl_em = qcd_stats_rl_em+qcd_stats_rl
				qcd_stats_fl_em = qcd_stats_fl_em+qcd_stats_fl
				data_stats_rl_em = data_stats_rl_em+data_stats_rl
				data_stats_fl_em = data_stats_fl_em+data_stats_fl
				qcd_ratio_em = qcd_stats_rl_em/qcd_stats_fl_em
				data_ratio_em = data_stats_rl_em/data_stats_fl_em
				qcdata_em = data_ratio_em/qcd_ratio_em
				flag_mergedlep = True
			qcd_ratio = qcd_stats_rl/qcd_stats_fl
			data_ratio = data_stats_rl/data_stats_fl
			nj_str = list_bin[int(i/2)]
			em_str = list_em[i%2]
			qcdata = data_ratio/qcd_ratio
			if flag_mergedlep :
				print(f'{em_str} in {nj_str} region : {qcd_stats_rl:10.3f} {data_stats_rl:10.3f} {qcd_stats_fl:10.3f} {data_stats_fl:10.3f} {qcd_ratio:10.7f}  {data_ratio:10.7f} {qcdata_em:10.7f}\n')
			else :
				print(f'{em_str} in {nj_str} region : {qcd_stats_rl:10.3f} {data_stats_rl:10.3f} {qcd_stats_fl:10.3f} {data_stats_fl:10.3f} {qcd_ratio:10.7f}  {data_ratio:10.7f}\n')
			list_stats=[]
			i=i+1
