set title "Kommunikationstest C Jacobi 200 Interlines"
set autoscale
set pointsize 2.5
set xlabel 'Prozesse und Knoten'
set ylabel 'Zeit'
set terminal postscript eps
set output "COMMUNICATION_C_JA.eps"
set grid
plot "COMMUNICATION_C_JA.dat" using 2:4 smooth csplines lt rgb "black", \
     "COMMUNICATION_C_JA.dat" using 2:4 with points lt rgb "red"
