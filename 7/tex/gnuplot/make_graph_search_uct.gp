set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/search_uct.eps" 

set size 1.5, 1.5


set ytics nomirror # 第一y軸の目盛は左側のみにする
set y2tics         # 第二y軸を描画することを指定

set xlabel "Playouts"
set ylabel "Time[sec]"	# 第1y軸の見出しを指定
set y2label "Depth"		# 第2y軸の見出しを指定

unset logscale x
set grid xtics ytics mxtics mytics

set key bottom # 凡例

set boxwidth 0.0
set style fill solid border lc rgb "red"

plot "./search_uct_time.txt" w lp lw 3 title "time", \
"./search_uct_num.txt" w lp lw 3 title "depth" axes x1y2
