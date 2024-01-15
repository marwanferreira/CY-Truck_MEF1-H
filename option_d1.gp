set terminal png size 800,800
set output 'option_d1.png'
set style data histograms
set style fill solid border -1
set boxwidth 2 relative
unset key
set ytics nomirror
set xtics rotate by 90 offset 1,.2 right
set y2tics rotate by 90 offset 0,-1.5
set y2range [0:]
set grid ytics lt 0 lw 1 lc rgb "gray"  # Pour les lignes horizontales
set grid xtics lt 0 lw 1 lc rgb "gray"  # Pour les lignes verticales
set grid y
set xlabel "DRIVERS NAMES" rotate by 180
set y2label "NB ROUTES"
set ylabel "Option -d1 : Nb routes" rotate by 90 offset 3,0 tc "steelblue" font ",20"
plot 'output.txt' using 2:xticlabels(1) notitle axes x1y2 lc rgb "dark-blue"

