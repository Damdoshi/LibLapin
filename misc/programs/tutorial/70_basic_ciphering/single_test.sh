#!/bin/bash

INPUT_FILE="man_malloc"
REF_FILE="original_man_malloc"
THE_KEY="ThisIsTheKey"

function panic()
{
    echo "Files are different! :'("
    cp $REF_FILE $INPUT_FILE
    exit 1
}

./70_basic_ciphering "xor" -c $THE_KEY $INPUT_FILE
./70_basic_ciphering "xor" -u $THE_KEY $INPUT_FILE

diff $INPUT_FILE $REF_FILE >& /dev/null || panic

./70_basic_ciphering "caesar" -c $THE_KEY $INPUT_FILE
./70_basic_ciphering "caesar" -u $THE_KEY $INPUT_FILE

diff $INPUT_FILE $REF_FILE >& /dev/null || panic

./70_basic_ciphering "shaker" -c $THE_KEY $INPUT_FILE
./70_basic_ciphering "shaker" -u $THE_KEY $INPUT_FILE

diff $INPUT_FILE $REF_FILE >& /dev/null || panic

