#!/bin/sh

cd "`dirname $0`"
cp main.c.old main.c
gcc -Wall *.c ../simple_rng/*.c
rm main.c
