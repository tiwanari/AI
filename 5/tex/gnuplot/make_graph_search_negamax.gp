set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/search_negamax.eps" 

set size 1.5, 1.5


set ytics nomirror # 第一y軸の目盛は左側のみにする

set xlabel "Playouts"
set ylabel "Time[sec]"	# 第1y軸の見出しを指定

set logscale y
set grid xtics ytics mxtics mytics

set key bottom # 凡例

set boxwidth 0.5
set style fill solid border lc rgb "red"

plot "./search_negamax.txt" with boxes lw 2 lc rgb "red" notitle
