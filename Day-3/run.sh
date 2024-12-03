#!/bin/bash
cd "$(dirname "$0")"

gcc -o part-one-n-two part-one-n-two.c
# valgrind ./part-one-n-two
./part-one-n-two