#!/bin/bash

INPUT_FILE="man_malloc"
REF_FILE="original_man_malloc"
THE_KEY_0="ThisIsTheKey"
THE_KEY_1="AnotherKey"
THE_KEY_2="Whatever"

function panic()
{
    echo "Files are different! :'("
    cp $REF_FILE $INPUT_FILE
    exit 1
}

./70_basic_ciphering "xor" -c $THE_KEY_0 $INPUT_FILE
./70_basic_ciphering "caesar" -c $THE_KEY_1 $INPUT_FILE
./70_basic_ciphering "shaker" -c $THE_KEY_2 $INPUT_FILE

./70_basic_ciphering "xor" -c $THE_KEY_2 $INPUT_FILE
./70_basic_ciphering "caesar" -c $THE_KEY_0 $INPUT_FILE
./70_basic_ciphering "shaker" -c $THE_KEY_1 $INPUT_FILE

#

./70_basic_ciphering "shaker" -u $THE_KEY_1 $INPUT_FILE
./70_basic_ciphering "caesar" -u $THE_KEY_0 $INPUT_FILE
./70_basic_ciphering "xor" -u $THE_KEY_2 $INPUT_FILE

./70_basic_ciphering "shaker" -u $THE_KEY_2 $INPUT_FILE
./70_basic_ciphering "caesar" -u $THE_KEY_1 $INPUT_FILE
./70_basic_ciphering "xor" -u $THE_KEY_0 $INPUT_FILE

diff $INPUT_FILE $REF_FILE >& /dev/null || panic

