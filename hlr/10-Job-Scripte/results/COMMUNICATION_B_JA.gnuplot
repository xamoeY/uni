set title "Kommunikationstest B Jacobi 200 Interlines"
set autoscale
set pointsize 2.5
set xlabel 'Prozesse'
set ylabel 'Zeit'
set terminal postscript eps
set output "COMMUNICATION_B_JA.eps"
set grid
plot "COMMUNICATION_B_JA.dat" using 1:4 smooth csplines lt rgb "black", \
     "COMMUNICATION_B_JA.dat" using 1:4 with points lt rgb "red"
