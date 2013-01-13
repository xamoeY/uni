set title "Kommunikationstest A Jacobi 200 Interlines"
set autoscale
set pointsize 2.5
set xlabel 'Knoten'
set ylabel 'Zeit'
set terminal postscript eps
set output "COMMUNICATION_A_JA.eps"
set grid
plot "COMMUNICATION_A_JA.dat" using 2:4 smooth csplines lt rgb "black", \
     "COMMUNICATION_A_JA.dat" using 2:4 with points lt rgb "red"
