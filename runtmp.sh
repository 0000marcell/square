#!/usr/bin/bash

rm -rf a.out 
gcc -g tmp.c
gdb a.out
