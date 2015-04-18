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
