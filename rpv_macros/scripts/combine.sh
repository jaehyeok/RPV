for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
do echo ${mass}
combineCards.py datacard_M${mass}_*.dat > total_M${mass}.dat
done
