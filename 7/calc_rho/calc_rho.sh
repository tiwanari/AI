#!/bin/sh


for n in `seq 9 9`
do
	touch ../tex/gnuplot/rho/$n.txt
	for i in `seq 0.1 0.1 0.9`
	do
		./aco $n $i >> ../tex/gnuplot/rho/$n.txt 2>> ../tex/gnuplot/rho/unresolved.txt
	done
done
