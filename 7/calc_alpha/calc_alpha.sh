#!/bin/sh


for n in `seq 8 9`
do
	touch ../tex/gnuplot/alpha/$n.txt
	for i in `seq 1.0 0.25 2.0`
	do
		./aco $n 0.5 $i 1>> ../tex/gnuplot/alpha/$n.txt 2>> ../tex/gnuplot/alpha/unresolved.txt
	done
done
