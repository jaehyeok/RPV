#!/bin/env python
"""Script for generating condor submission files"""
import shutil
import os

def copytemplate(template, jobindex):
    """Copy template to rundir"""
    filename = template.replace('TEMPLATE', 
                                'submit_' + jobindex).replace(' ', '_')
    shutil.copy(template, filename)
    return filename
    
def replacestringinfile(filename, stringbefore, stringafter):
    """Replace placeholders in template"""
    tempstring = open(filename).read()
    tempstring = tempstring.replace(stringbefore, stringafter)
    outfile = open(filename, 'w')
    outfile.write(tempstring)
    outfile.close()

def writetemplate():
    """Output template"""
    outfile = open('TEMPLATE.cmd', 'w')

    outfile.write('Executable = PATH/run_variations.sh\n')
    outfile.write('Universe = vanilla\n')
    outfile.write('Notification = Error\n')
    outfile.write('Error = PATH/logs/VARTYPE.err\n')
    outfile.write('Output = PATH/logs/VARTYPE.out\n')
    outfile.write('Log = PATH/logs/VARTYPE.log\n')
    outfile.write('arguments = "VARTYPE"\n')
    outfile.write('request_memory = 3 GB\n')
    outfile.write('Queue\n')
    outfile.close()

def writescript():
    """Write script for condor jobs"""
    outfile = open('run_variations.sh', 'w')
    outfile.write('#!/bin/bash\n')
    # set up CMSSW environment
    outfile.write('. /cvmfs/cms.cern.ch/cmsset_default.sh\n')
    outfile.write('cd /homes/jaehyeokyoo/babymaker/CMSSW_8_0_16/src/\n')
    outfile.write('eval `scramv1 runtime -sh`\n')
    outfile.write('cd ' + PATH + '\n')
    # and then run script
    outfile.write('./run/make_variations_loop.exe $1 $2\n')
    outfile.close()

#default path should be changed
PATH = '/homes/rohan/RPV/ra4_macros'
VARLIST = ['nominal','btag_bc', 'btag_udsg',
           'gs45', 'gs67', 'gs89', 'gs10Inf',
           'jes', 'jer',
           'lep_eff', 'ttbar_pt', #'pileup',
           'isr',
           'qcd_flavor',
           # the following are njet-dependent
           # versions of the previous variation
           'qcd_flavor45', 'qcd_flavor67',
           'qcd_flavor89', 'qcd_flavor10Inf',
           'qcd_mur', 'qcd_muf', 'qcd_murf',
           'ttbar_mur', 'ttbar_muf', 'ttbar_murf',
           'wjets_mur', 'wjets_muf', 'wjets_murf',
           'other_mur', 'other_muf', 'other_murf',
           'signal_mur', 'signal_muf', 'signal_murf']

# make directory 'varscripts' to contain condor submit files
# and directory 'variations' to contain variations
PATH = os.getcwd()
if not os.path.isdir('variations'):
    os.mkdir('variations')
if not os.path.isdir('varscripts'):
    os.mkdir('varscripts')
os.chdir('varscripts')
if not os.path.isdir('logs'):
    os.mkdir('logs')

# write condor submission template file
# and script for running condor jobs
writetemplate()
writescript()


# add PDF variations
for i in range(0, 100):
    VARLIST.append('w_pdf ' + str(i))

for vartype in VARLIST:
    newfilename = copytemplate('TEMPLATE.cmd', vartype)
    replacestringinfile(newfilename, 'PATH', PATH + '/varscripts')
    replacestringinfile(newfilename, 'VARTYPE', vartype)
    replacestringinfile(newfilename, '/w_pdf ', '/w_pdf_')

# remove the TEMPLATE.cmd temporary file
os.remove('TEMPLATE.cmd') 

# change permission of run_variations.ch to 777 
os.system('chmod 777 run_variations.sh')

# dump all condor submit files to all.cmd 
os.system('cat submit_*cmd > all.cmd')
