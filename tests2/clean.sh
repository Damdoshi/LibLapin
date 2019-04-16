#!/bin/sh

for param in `find . -name '*.c'`; do
    output=`echo "$param" | cut -d '.' -f 2`
    rm -f ".$output"
done
