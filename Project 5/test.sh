#!/bin/bash

#First, if we don't have any of the compiled files, we want to compile them
#We should probably use make, but oh well.
if [ ! -f "genNums" ]
then
    gcc -Wall -g -o genNums genNums.c
fi

if [ ! -f "mergesort" ]
then
    gcc -Wall -g -o mergesort mergesort.c
fi

if [ ! -f "quicksort" ]
then
    gcc -Wall -g -o quicksort quicksort.c
fi

#Now we want to delete previous results, just so that we don't append to them and cause skewed results.
if [ -f "mergesort_results.txt" ]
then
    rm mergesort_results.txt
fi

if [ -f "quicksort_results.txt" ]
then
    rm quicksort_results.txt
fi

#Now we want to generate statistics
#We want to base it on 10 rounds of tests, each time generating a new set of numbers for a proper test.
ROUNDS_COUNTER=0
COUNTER=0

while [ $ROUNDS_COUNTER -lt 10 ]; do
    COUNTER=0
    while [ $COUNTER -le 18 ]; do
        ./genNums numbers.bin 1000000 > /dev/null
        ./mergesort numbers.bin $((100000 + (50000 * COUNTER))) >> mergesort_results.txt
        ((COUNTER += 1))
    done
    COUNTER=0

    while [ $COUNTER -le 18 ]; do
        ./genNums numbers.bin 1000000 > /dev/null
        ./quicksort numbers.bin $((100000 + (50000 * COUNTER))) >> quicksort_results.txt
        ((COUNTER += 1))
    done
    ((ROUNDS_COUNTER += 1))
done

echo "Results Created"
