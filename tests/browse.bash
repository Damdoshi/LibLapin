#!/bin/bash

for dir in *; do
    [ -d $dir ] && ./check.bash $dir
done
