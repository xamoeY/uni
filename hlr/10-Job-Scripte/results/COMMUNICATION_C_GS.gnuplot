set title "Kommunikationstest C Gauss-Seidel 200 Interlines"
set autoscale
set pointsize 2.5
set xlabel 'Prozesse und Knoten'
set ylabel 'Zeit'
set terminal postscript eps
set output "COMMUNICATION_C_GS.eps"
set grid
plot "COMMUNICATION_C_GS.dat" using 2:4 smooth csplines lt rgb "black", \
     "COMMUNICATION_C_GS.dat" using 2:4 with points lt rgb "red"
