#!/bin/bash
SCRIPT=$(readlink -f "$0")
SCRIPT_DIR=$( dirname "${SCRIPT}" )
cd $SCRIPT_DIR

if [ $# -lt 1 ]; then
	echo "Usage: $0 <numjobs>"
	exit 0
fi
NUMJOBS=$1
python3 bench.py
for j in $(seq 1 $NUMJOBS); do
	python3 bench.py &
done


