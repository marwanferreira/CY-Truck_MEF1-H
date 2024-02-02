set terminal png size 768,768
set output 'option_l.png'

set title "Option I : Distance = f(Route)" textcolor rgb "dark-orange" font ",20"

set xlabel "ROUTE ID"
set ylabel "DISTANCE (km)"

# Set the y-range to start from 0
set yrange [0:*]

set style data histograms
set style fill solid 1.0 border -1

# Increase the boxwidth for thicker bars
set boxwidth 2 relative

set grid y
set xtics rotate by -45

plot 'output_l.txt' using 2:xtic(1) lc rgb "dark-orange" notitle
