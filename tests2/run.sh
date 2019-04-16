#!/bin/sh

success_test=0
total_test=0

run_test()
{
    output=`echo "$1" | cut -d '.' -f 2`
    gcc $1 -O0 -Og -g -g3 -ggdb -W -Wall -std=gnu11 -L../ -I../include/ -llapin -lstdc++ -o .$output && \
	./$output && \
	success_test=$((success_test + 1)) && \
	echo "\033[0;32mTest $output OK\033[00m" || \
	echo "\033[0;31mTest $output KO\033[00m"
    total_test=$((total_test + 1))
}

if [ "$#" -eq "0" ]; then
    for param in `find . -name '*.c'`; do
	run_test $param
    done
else
    for param in "$@"; do
	run_test $param
    done
fi

echo "Tests passed:" $success_test "/" $total_test
if [ "$success_test" -ne "$total_test" ]; then
    exit 1
fi
exit 0
