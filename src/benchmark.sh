#!/bin/bash

echo "N,time" > output/performance.csv

for N in 50 100 150 200 250 300 350 400 450 500 550 600 650 700 
do
    make benchmark N=$N >> output/performance.csv
done