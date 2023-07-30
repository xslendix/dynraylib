#!/bin/sh

git clone --shallow-submodules --recursive --depth 1 https://github.com/raysan5/raylib.git

set -e

cd raylib

if test -f "./raylib/build/raylib/libraylib.so";
then
	echo "Found libraylib.so"
else
	mkdir build && cd build && cmake .. -GNinja -DBUILD_SHARED_LIBS=ON -DWITH_PIC=ON && ninja && cd ..
fi

cd ..

cp raylib/build/raylib/libraylib.so.??? .
./build_dyn.sh
cc -O0 -g -o main main.c ./libraylib.so.??? -lltdl -ldl -lm 

