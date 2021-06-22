#!/bin/sh

cp datacards/datacard_M1500_${1}_impact_2016.dat 2016_1.dat
cp datacards/datacard_M1500_${1}_impact_20178.dat 20178_1.dat

for i in {1..20}
do
	j=`expr $i + 1`
	echo $j
	sed -e s/ch${i}\_//g 2016_${i}.dat > 2016_${j}.dat
	sed -e s/\_ch${i}\_/\_/g 20178_${i}.dat > 20178_${j}.dat
	rm 2016_${i}.dat 20178_${i}.dat
done
cp 2016_21.dat datacards/datacard_M1500_${1}_impact_2016.dat
cp 20178_21.dat datacards/datacard_M1500_${1}_impact_20178.dat
