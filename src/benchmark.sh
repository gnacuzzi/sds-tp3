#!/bin/bash

echo "N,time" > output/performance.csv

for N in 10 20 50 100 200 500
do
    make benchmark N=$N >> output/performance.csv
done