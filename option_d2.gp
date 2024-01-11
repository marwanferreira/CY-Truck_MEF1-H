set terminal png size 600,800
set output 'option_d2.png'
set style data histograms
set style histogram rowstacked
set style fill solid border -1
unset key
set boxwidth 0.75 relative
set ytics nomirror
set xtics rotate by -45
set grid y
set xlabel "Distance totale parcourue (km)"
set ylabel "Conducteurs"
plot 'output_d2.txt' using 2:xticlabels(1) with boxes lc rgb "blue" notitle
