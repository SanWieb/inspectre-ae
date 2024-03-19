#!/bin/bash
set -e

if [[ $EUID -ne 0 ]]; then
   echo "Please run as root"
   exit 1
fi

echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor


for option in $(seq 0 4)
do
    rm results_${1}_ibt_c${option}.txt || true
    rm results_${1}_fineibt_c${option}.txt || true
done

for i in $(seq 500)
do 
    echo "-- Iteration $i --"
    for option in $(seq 0 4)
    do
	./main ibt -c $option | tee -a results_${1}_ibt_c${option}.txt
        ./main fine_ibt -c $option | tee -a results_${1}_fineibt_c${option}.txt
    done
done