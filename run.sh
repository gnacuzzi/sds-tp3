echo "Running 10 iterations of N = 30"
R=5
make

mkdir -p images

for N in 20 50 100 200 500
do
    ./bin/tp3 $N 0 "$R"
done

python3 python/interpolate.py "$R" 