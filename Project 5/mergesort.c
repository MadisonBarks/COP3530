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
  * Merges two parts of an array into one
  * @param array The array to merge (also acts as the return)
  * @param size The size of <code>array</code>
  * @param middle The middle of the array
  */
void merge(int * array, int size, int middle) {
  int i;
  int j;
  int k;
  int * x = malloc(size * sizeof (int));
  for (i = 0, j = middle, k = 0; k < size; k++) {
    if(j == size) {
      x[k] = array[i++];
    }
    else if(i == middle) {
      x[k] = array[j++];
    }
    else if(array[j] < array[i]) {
      x[k] = array[j++];
    }
    else {
      x[k] = array[i++];
    }
  }
  for (i = 0; i < size; i++) {
      array[i] = x[i];
  }
  free(x);
}

/**
  * Sorts an integer array using the merge sort algorithm
  * @param array An array with integers in it
  * @param leftIndex The left-most index to look at
  * @param rightIndex The right-most index to look at
  */
void merge_sort(int * array, int size) {
  if(size < 2) {
    return;
  }

  int middle = size / 2;

  merge_sort(array, middle);
  merge_sort(array + middle, size - middle);

  merge(array, size, middle);
}

int main(int argc, char * argv[]) {
  clock_t start, end;
  int elapsedTime;

  if(argc < 3) {
    printf("Usage: mergesort binaryFile numberOfNumbers");
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

  merge_sort(array, wantedNumbers);

  end = clock();
  elapsedTime = (end - start) / (CLOCKS_PER_SEC / 1000);

  printf("%d\t%d\n", wantedNumbers, elapsedTime);

  return 0;

}
