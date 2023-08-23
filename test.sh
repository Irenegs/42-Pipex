#!/bin/bash

make && make clean

T=1

echo "TEST" $T && T=$((T+1))
./pipex pipex.c " wc -l pipex.c" ls pipex.h