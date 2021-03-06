set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/rho.eps" 

set size 0.8, 0.8

set xlabel "Rho"
set ylabel "Average Step"	# 第1y軸の見出しを指定

set logscale y
set grid xtics ytics mxtics mytics

#set key bottom # 凡例

set boxwidth 0.5
set style fill solid border lc rgb "red"


plot "./rho/5.txt" w lp lw 3 title "5Queen", \
"./rho/6.txt" w lp lw 3 title "6Queen", \
"./rho/7.txt" w lp lw 3 title "7Queen", \
"./rho/8.txt" w lp lw 3 title "8Queen", \
"./rho/9.txt" w lp lw 3 title "9Queen"

