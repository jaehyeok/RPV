for year in {2016,2017,2018}
	do echo "${year} year.."
	for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
	do echo "Gluino mass ${mass} GeV working..."
		if [ ${year} = "2016" ]; then
			./run/make_rpv_datacard_newbins.exe ${mass} mconly output_${year}.root ${year} off on
		else
			./run/make_rpv_datacard_newbins.exe ${mass} mconly output_${year}.root ${year} on on
		fi
	done

	mkdir -p datacards/nopdfoutput_${year}/

	cp datacards/*mconly_nopdfoutput_${year}.dat datacards/nopdfoutput_${year}/.

	for mass in {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200}
	do echo ${mass}
	combine -M AsymptoticLimits datacards/nopdfoutput_${year}/datacard_M${mass}_mconly_nopdfoutput_${year}.dat -n M${mass}
	done

	mv higgsCombineM*.AsymptoticLimits.mH120.root datacards/nopdfoutput_${year}/.
done
