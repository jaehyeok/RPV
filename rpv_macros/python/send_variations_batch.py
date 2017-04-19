#!/bin/env python
import os

VARLIST = ['nominal','btag_bc', 'btag_udsg',
           'gs',
           'jes', 'jer',
           'lep_eff', 'ttbar_pt', #'pileup',
           'isr',
           'qcd_flavor',
           'qcd_mur', 'qcd_muf', 'qcd_murf',
           'ttbar_mur', 'ttbar_muf', 'ttbar_murf',
           'wjets_mur', 'wjets_muf', 'wjets_murf',
           'other_mur', 'other_muf', 'other_murf',
           'signal_mur', 'signal_muf', 'signal_murf']

# add PDF variations
for i in range(0, 100):
    VARLIST.append('w_pdf ' + str(i))

for var in VARLIST:
    os.system('JobSubmit.csh ./varscripts/wrapper.sh ./run/make_variations.exe ' + var)
