#!/bin/sh

for param in `find . -name '*.cpp'`; do
    output=`echo "$param" | cut -d '.' -f 2`
    rm -f ".$output"
done
rm -f ./*.gc*
rm -f coverage.info
rm -rf ./report/
