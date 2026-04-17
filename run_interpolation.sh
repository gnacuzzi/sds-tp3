echo "Running 10 iterations of N = 20 50 100 200 and 500"
R=10
make


for N in 50 100 200 300 400 500 
do
    ./bin/tp3 $N 0 "$R"
done

python3 python/interpolate.py "$R" 