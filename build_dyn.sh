#!/bin/sh
echo "Rebuilding dyn.so"
cc -O0 -g -fPIC -shared -o dyn.so dyn.c ./libraylib.so.??? -lm
