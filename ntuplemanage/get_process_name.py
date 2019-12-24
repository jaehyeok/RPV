import os
import sys

listfile = open('process_list.txt','w')
path = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_11_07/skim_rpvfit/"
file_list = os.listdir(path)
file_list_root = [file for file in file_list if file.endswith(".root")]
process=[]

for i in range(0, len(file_list)-1):
	splited_filename = file_list_root[i].split('_')
	process.append(splited_filename[2])

process = list(set(process))

for i in range(0, len(process)-1):	
	listfile.write(process[i])
	listfile.write('\n')

listfile.close()
