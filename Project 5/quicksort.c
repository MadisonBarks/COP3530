#include <stdio.h>
#include <time.h>
#include <stdlib.h> //For atoi && malloc

#define true 1
#define false 0

typedef int bool;

FILE * openFile(char * fileName) {
  return fopen(fileName, "rb");
}

bool checkFileSize(FILE * fp, int wantedInts) {
  int actualNumbers;
  fread(&actualNumbers, sizeof(int), 1, fp);
  return actualNumbers >= wantedInts;
}

void readInNumbers(int * array, int wantedNumbers, FILE * fp) {
  fread(array, sizeof(int), wantedNumbers, fp);
}

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

void printArrayToConsole(int array[]) {
  int i;
  int arraySize = (sizeof(array) / sizeof(int));
  printf("Array Size: %d\n", (sizeof(array) / sizeof(int)));

  for(i = 0; i < arraySize; i++) {
    printf("%d ", array[i]);
    printf("%d ", i);
  }
  printf("\n");
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
