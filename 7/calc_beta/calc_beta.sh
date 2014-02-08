#!/bin/sh


for n in `seq 5 9`
do
	touch ../tex/gnuplot/beta/$n.txt
	for i in `seq 1.0 0.25 2.0`
	do
		./aco $n 0.5 1.0 $i >> ../tex/gnuplot/beta/$n.txt 2>> ../tex/gnuplot/beta/unresolved.txt
	done
done