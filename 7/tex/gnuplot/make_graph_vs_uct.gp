set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/vs_uct.eps" 
set size 1.3, 1.3

set autoscale
set xlabel "playouts"
set ylabel "winning rate"
set xrange [1000:50000]
set yrange [0:1.1]
unset logscale y
unset logscale x
set grid xtics ytics mxtics mytics
set key bottom # 凡例

p "./vs_uct_1000.txt" lw 3 title "1000 playouts" w lp, \
"./vs_uct_2000.txt" lw 3 title "2000 playouts" w lp, \
"./vs_uct_5000.txt" lw 3 title "5000 playouts" w lp, \
"./vs_uct_10000.txt" lw 3 title "10000 playouts" w lp, \
"./vs_uct_20000.txt" lw 3 title "20000 playouts" w lp, \
"./vs_uct_50000.txt" lt 9 lw 3 title "50000 playouts" w lp
