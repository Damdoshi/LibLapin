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

ALLOC=`cat -e dump | grep "total heap usage" | cut -d ' ' -f 7 | tr -d ','`
FREE=`cat -e dump | grep "total heap usage" | cut -d ' ' -f 9 | tr -d ','`
MARGIN=`cat margin 2> /dev/null`

if [ -z "$MARGIN" ]; then
    MARGIN=1
fi

# > 1 because of the g++ throw memory pool...
if [[ $(($ALLOC - $FREE)) > $MARGIN ]]; then
    echo "$1 - Leaks found (Freed: $FREE / $ALLOC)"
    make fclean
    rm -f dump
    exit 1
fi

echo "$1 - Ok"
make fclean
rm -f dump
exit 0
