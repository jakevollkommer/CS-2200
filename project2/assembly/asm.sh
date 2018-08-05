#!/bin/bash

python assembler.py -i conte200 --hex $1.s
python assembler.py -i conte200 --sym $1.s
cat $1.hex
python conte200-sim.py $1.bin
cat ram
