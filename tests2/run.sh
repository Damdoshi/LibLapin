#!/bin/sh

success_test=0
total_test=0

flags="-O0 -Og -g -g3 -ggdb -W -Wall -std=c++1z -fprofile-arcs -ftest-coverage --coverage"
libs="-L../ -I../include/ --whole-file -llapin -lgcov -lstdc++"

run_test()
{
    output=`echo "$1" | cut -d '.' -f 2`
    g++ $1 $libs $flags -o .$output && \
	./$output && \
	success_test=$((success_test + 1)) && \
	echo "\033[0;32mTest $output OK\033[00m" || \
	echo "\033[0;31mTest $output KO\033[00m"
    total_test=$((total_test + 1))
}

if [ "$#" -eq "0" ]; then
    for param in `find . -name '*.cpp'`; do
	run_test $param
    done
else
    for param in "$@"; do
	run_test $param
    done
fi

lcov --directory . --directory ../src2/ -c -o coverage_raw.info > /dev/null 2> /dev/null && \
    lcov --remove coverage.info '/usr/include/*' '7/*' -o coverage.info > /dev/null 2> /dev/null && \
    genhtml -o ./report/ -t "LibLapin: Coverage" coverage.info | grep "\%"
rm -f coverage_raw.info

echo "Tests passed:" $success_test "/" $total_test
if [ "$success_test" -ne "$total_test" ]; then
    exit 1
fi
exit 0
