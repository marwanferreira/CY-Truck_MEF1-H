#!/bin/bash

cut -d';' -f1,2,5 data.csv > s1.csv
tail -n +2 s1.csv > s2.csv
gcc -o exect S.c 
./exect s2.csv
head -n 50 sortie.csv > s.csv
