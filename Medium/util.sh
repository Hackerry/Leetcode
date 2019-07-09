#!/bin/bash

OPT=$1
FILE=$2

compile() {
	if [[ ${FILE} =~ c$ ]]; then
		echo "Compile C file: ====================================="
		gcc -g ${FILE} -o out
	elif [[ ${FILE} =~ cpp$ ]]; then
		echo "Compile CPP file: ====================================="
		g++ -g -std=c++11 ${FILE} -o out
	else
		echo "Unrecognized"
	fi
}

if [ ${OPT} == "c" ] || [ ${OPT} == "C" ]; then
	compile
elif [ ${OPT} == "r" ] || [ ${OPT} == "R" ]; then
	compile
	./out
fi
