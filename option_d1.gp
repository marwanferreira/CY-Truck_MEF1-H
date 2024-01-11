set terminal png size 600,800
set output 'option_d1.png'
set style data histograms
set style fill solid border -1
unset key; unset xlab
set ytics nomirror
set xtics rotate by 90 offset 1,.2 right
set yrange [0:]
set y2tics -100, 20
set ytics nomirror
set grid y
set ylabel "Nombre de trajets par Conducteur"
set y2label "Option -d1 : Nb routes" rotate by 90 offset 0,2 tc "steelblue"
set xlabel "Conducteurs" rotate by 180
plot 'output.txt' using 2:xticlabels(1) notitle

