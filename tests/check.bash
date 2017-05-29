#!/bin/bash

cd $1

make >& /dev/null

if [[ $? != 0 ]]; then
    echo "$1 - Does not compile"
    make fclean
    exit 1
fi

export GLIBCXX_FORCE_NEW=1
valgrind ./$1 run >& dump

if [[ $? != 0 ]]; then
    echo "$1 - Does not work"
    make fclean
    rm -f dump
    exit 1
fi

ALLOC=`cat dump | grep "total heap usage" | cut -d ' ' -f 7 | tr -d ','`
FREE=`cat  dump | grep "total heap usage" | cut -d ' ' -f 9 | tr -d ','`

# > 1 because of the g++ throw memory pool...
if [[ $(($ALLOC - $FREE)) > 1 ]]; then
    echo "$1 - Leaks found (Freed: $FREE / $ALLOC)"
    make fclean
    rm -f dump
    exit 1
fi

echo "$1 - Ok"
make fclean
rm -f dump
exit 0
