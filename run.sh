echo "Running 10 iterations of N = 30"
N=5
make

./bin/tp3 50 0 "$N"

python3 python/interpolate.py "$N"