mkdir -p log/
if [ $1 = "2016" ]; then
        ./run/make_kappa_CRfit.exe on 500 1400 $1
else
        ./run/make_kappa_CRfit.exe on 500 1400 20178
fi
