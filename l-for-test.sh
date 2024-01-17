#!/bin/bash

CSV_FILE="data.csv"

if [ ! -f "$CSV_FILE" ]; then
    echo "Le fichier $CSV_FILE n'existe pas."
    exit 1
fi

start_time=$(date +%s)

awk -F ';' 'NR > 1 {gsub(",", ".", $5); sum[$1] += $5} END {for (i in sum) print sum[i], i}' "$CSV_FILE" | sort -nrk1 | head -10 

end_time=$(date +%s)
echo "Durée d'exécution: $((end_time - start_time)) secondes."
