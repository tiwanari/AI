#!/bin/sh


for n in `seq 6 9`
do
	> ../tex/gnuplot/rho/$n.txt
	for i in `seq 0.1 0.1 0.9`
	do
		echo `./aco $n $i` >> ../tex/gnuplot/rho/$n.txt 2>> ../tex/gnuplot/unresolved/rho/unresolved.txt
	done
done