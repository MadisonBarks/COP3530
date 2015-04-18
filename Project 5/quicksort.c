/**
  * Sorts integers defined in a binary file
  */

#include <stdio.h>
#include <time.h>
#include <stdlib.h> //For atoi && malloc

#define true 1
#define false 0

typedef int bool;

/**
  * Opens a file for reading
  * @param fileName The name of the file to open
  * @returns A pointer to a FILE struct returned by fopen(3)
  */
FILE * openFile(char * fileName) {
  return fopen(fileName, "rb");
}

/**
  * Checks the file size and makes sure that we have enough integers to load.
  * @param fp A pointer to a FILE struct
  * @param wantedInts How many integers the user wants to sort
  * @return <code>true</code> if we have enough, <code>false</code> otherwise
  */
bool checkFileSize(FILE * fp, int wantedInts) {
  int actualNumbers;
  fread(&actualNumbers, sizeof(int), 1, fp);
  return actualNumbers >= wantedInts;
}

/**
  * Reads in the amount of numbers that the user wants to sort from the file
  * @param array A pre-allocated array of integers to load into
  * @param wantedNumbers How many numbers the user wants to load
  * @param fp A pointer to a FILE struct
  */
void readInNumbers(int * array, int wantedNumbers, FILE * fp) {
  fread(array, sizeof(int), wantedNumbers, fp);
}

/**
  * Sorts an integer array using the quicksort algorithm
  * @param array An array with integers in it
  * @param leftIndex The left-most index to look at
  * @param rightIndex The right-most index to look at
  */
void quicksort(int * array, int leftIndex, int rightIndex) {
  int pivot = array[(leftIndex + rightIndex) / 2];
  int internalLeft = leftIndex;
  int internalRight = rightIndex;
  int temp = 0;

  while(internalLeft <= internalRight) {
    while(array[internalLeft] < pivot) {
      internalLeft++;
    }
    while(array[internalRight] > pivot) {
      internalRight--;
    }
    if(internalLeft <= internalRight) {
      temp = array[internalRight];
      array[internalRight] = array[internalLeft];
      array[internalLeft] = temp;
      internalLeft++;
      internalRight--;
    }
  }

  if(leftIndex < internalLeft) {
    quicksort(array, leftIndex, internalRight);
  }

  if(rightIndex > internalRight) {
    quicksort(array, internalLeft, rightIndex);
  }
}

int main(int argc, char * argv[]) {
  clock_t start, end;
  int elapsedTime;

  if(argc < 3) {
    printf("Usage: quicksort binaryFile numberOfNumbers");
    return 0;
  }

  char * fileName = argv[1];
  int wantedNumbers = atoi(argv[2]);

  FILE * fp = openFile(fileName);
  if(fp == NULL) {
    printf("Unable to open %s", fileName);
    return 1;
  }

  if(!checkFileSize(fp, wantedNumbers)) {
    printf("Please regenerate the file - it does not contain enough ints");
    return 1;
  }

  int * array = (int *)malloc(wantedNumbers * sizeof(int));

  if(array == NULL) {
    printf("ARRAY MEMORY NOT ALLOCATED");
    return 1;
  }

  readInNumbers(array, wantedNumbers, fp);

  start = clock();

  quicksort(array, 0, wantedNumbers - 1);

  end = clock();
  elapsedTime = (end - start) / (CLOCKS_PER_SEC / 1000);

  printf("%d\t%d\n", wantedNumbers, elapsedTime);

  return 0;

}
