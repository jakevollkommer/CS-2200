#!/bin/bash

function run_simulations() {
	echo "Default Configuration"

	for i in `ls ./traces/`; do
		echo ""
		echo "--$i--"
			./cachesim -i ./traces/$i -r $1
	done;

	echo ""
	echo "Direct Mapped Cache"
	for i in `ls ./traces/`; do
		echo ""
		echo "--$i--"
		./cachesim -C 10 -S 0 -i ./traces/$i -r $1
	done;

	echo ""
	echo "4 Way Associative"
	for i in `ls ./traces/`; do
		echo ""
		echo "--$i--"
		./cachesim -C 12 -S 2 -B 4 -i ./traces/$i -r $1
	done;

	echo ""
	echo "4 Way Associative - Bigger Caches"
	for i in `ls ./traces/`; do
		echo ""
		echo "--$i--"
		./cachesim -C 16 -S 2 -B 4 -i ./traces/$i -r $1
	done;

	echo ""
	echo "Fully Associative"
	for i in `ls ./traces/`; do
		echo ""
		echo "--$i--"
		./cachesim -C 12 -S 8 -B 4 -i ./traces/$i -r $1
	done;
}

run_simulations "fifo"
run_simulations "lru"
