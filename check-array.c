#include <stdio.h>
#include <stdlib.h>

#define N 9

int isTheSameArray(int *array1, int *array2);

int main(void) {
  int array[N] = {6, 256, 11, 256, 256, 5, 256, 256, 15};

  int checkArray[N] = {6, 3, 11, 5, 1, 5, 3, 0, 11};

  printf("%d\n", isTheSameArray(array, checkArray));

  return 0;
}

int isTheSameArray(int *array1, int *array2) {
  int i;
  for(i = 0; i < 9; i++) {
    int chr = array1[i];
    int integer = array2[i];

    if (chr == 256) {
      continue;
    }

    if (integer != chr) {
      return -1;
    }
  }
  return 1;
}
