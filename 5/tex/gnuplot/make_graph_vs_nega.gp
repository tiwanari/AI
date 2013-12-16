set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/vs_negamax.eps" 
set size 1.0, 1.0

set autoscale
set xlabel "playouts"
set ylabel "winning rate"
set xrange [1000:50000]
set yrange [0:1.1]
unset logscale y
set logscale x
set grid xtics ytics mxtics mytics
set key bottom # 凡例

p "./vs_negamax_1.txt" lw 3 title "1 depth" w lp, \
"./vs_negamax_2.txt" lw 3 title "2 depth" w lp, \
"./vs_negamax_3.txt" lw 3 title "3 depth" w lp, \
"./vs_negamax_4.txt" lw 3 title "4 depth" w lp, \
"./vs_negamax_5.txt" lw 3 title "5 depth" w lp, \
"./vs_negamax_6.txt" lc 7 lw 3 title "6 depth" w lp