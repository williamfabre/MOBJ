#! /bin/bash
cd cells;
for ((i=0 ; 10 - $i ; i++))
do
	cd ..; ./tme6
	cd cells;bash check.sh
done

