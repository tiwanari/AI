set terminal postscript eps enhanced "Courier" 20
set term postscript eps enhanced color
set output "../image/unresolved_beta.eps" 

set size 0.8, 0.8

set xlabel "Beta"
set ylabel "# of Unresolved"

set grid xtics ytics mxtics mytics

# set key bottom # 凡例

set style fill solid border lc rgb "black"
set boxwidth 1.0


plot "./beta/unresolved5.txt" using 2:xtic(1)  with histogram lw 2 lc rgb "light-pink" title "5Queen", \
"./beta/unresolved6.txt" using 2  with histogram lw 2 lc rgb "light-green" title "6Queen", \
"./beta/unresolved7.txt" using 2 with histogram lw 2 lc rgb "light-blue" title "7Queen",\
"./beta/unresolved8.txt" using 2 with histogram lw 2 lc rgb "magenta" title "8Queen",\
"./beta/unresolved9.txt" using 2 with histogram lw 2 lc rgb "khaki" title "9Queen"