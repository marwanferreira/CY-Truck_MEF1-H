set terminal png size 800,600
set output 'Option-d1.png'

set title "Nombre de trajets par Conducteur"
set ylabel "Conducteurs"
set xlabel "Nombre de trajets"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.5
set grid y
set yrange [0:*]     # Assurez-vous que la plage est valide et suffisamment grande pour inclure toutes vos données
set auto x           # Auto-ajuste la plage de l'axe des x en fonction des données

plot 'output.txt' using 2:xticlabels(1) with boxes lc rgb"blue" notitle

