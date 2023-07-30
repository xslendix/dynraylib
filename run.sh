#!/bin/sh

./recompile.sh &
KEK=$!
LD_LIBRARY_PATH=. ./main
kill -9 $KEK
