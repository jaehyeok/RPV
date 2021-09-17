import DY_test
import sys

years=['2016','2017','2018']
#years=['2018']

for year in years :
	DY_test.DY(DY_test.totpath(year),3,year)
	DY_test.DY(DY_test.totpath(year),5,year)
	DY_test.DY(DY_test.totpath(year),7,year)
