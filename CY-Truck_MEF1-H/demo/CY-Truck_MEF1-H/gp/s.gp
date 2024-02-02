set terminal png size 1400, 600
    set output 'images/option_s.png'
    set ylabel 'Distance (km)'
    set xlabel 'ROUTE ID'
    set title 'Option -s: Distance f(Route)' textcolor rgb "dark-green" font ",20"
    set xtics rotate by -90
    set key outside
    set style data lines
    set yrange [0:*]
    unset xrange
    set datafile separator ";"
    plot 'temp/s.txt' using 3:xtic(1) title 'Distance average (Km)' with lines lc rgb 'blue', \
         'temp/s.txt' using 4:xtic(1) title 'Distances Max (Km)' with lines lc rgb 'red', \
         'temp/s.txt' using 2:xtic(1) title 'Distances Min (Km)' with lines lc rgb 'green'