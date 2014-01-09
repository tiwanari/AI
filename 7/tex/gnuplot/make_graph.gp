set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/seek_C.eps" 
set size 1.0, 1.0

set autoscale
set xlabel "C"
set ylabel "winning rate"
unset logscale y
set xrange [0.1:10]
set logscale x
set grid xtics ytics mxtics mytics
set key  # 凡例

p "./seek_C_1000.txt" lw 3 title "1000 playouts" w lp, \
"./seek_C_2000.txt" lw 3 title "2000 playouts" w lp, \
"./seek_C_5000.txt" lw 3 title "5000 playouts" w lp, \
"./seek_C_10000.txt" lw 3 title "10000 playouts" w lp, \
"./seek_C_20000.txt" lw 3 title "20000 playouts" w lp, \
"./seek_C_50000.txt" lt 9 lw 3 title "50000 playouts" w lp
