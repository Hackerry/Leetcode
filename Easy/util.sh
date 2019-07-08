#!/bin/bash

OPT=$1
FILE=$2

compile() {
	if [[ ${FILE} =~ c$ ]]; then
		echo "Compile C file: ====================================="
		gcc -g ${FILE} -Wall -o out
	elif [[ ${FILE} =~ cpp$ ]]; then
		echo "Compile CPP file: ====================================="
		g++ -g ${FILE} -Wall -o out
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
