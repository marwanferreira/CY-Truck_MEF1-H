set terminal png size 1000,800  
set output 'images/option_t.png'
set ylabel 'NB ROUTES'
set xlabel 'TOWN NAMES'
set title 'OPTION-T'
set style data histograms
set style histogram cluster gap 1
set style fill solid 1.0 border -1
set boxwidth 1 relative
set datafile separator ";"
set xtics rotate by -50 font ",12"
set lmargin 10
set rmargin 10
set tmargin 5
set bmargin 9
set grid y
set yrange [0:3500]
plot 'temp/output-t.txt' using 2:xticlabels(1) title 'Total Routes' lc rgb "dark-blue", '' using 3 title 'First Departure' lc rgb "dark-orange"