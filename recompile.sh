#!/bin/sh

while true; do
	while inotifywait -e close_write dyn.c 2>/dev/null; do
		echo
	done
	./build_dyn.sh
done
