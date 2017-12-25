#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int median(int n, int *x);

int main(void) {
  // 画像データのロード
  load_image_data();
  x_size2 = x_size1;
  y_size2 = y_size1;

  // どこまでチェックするのかの座標
  int x_max_check = x_size1 - 2;
  int y_max_check = y_size1 - 2;

  int i, j;
  for (i = 0; i <= y_max_check; i++) {
    for (j = 0; j <= x_max_check; j++) {
      int x_pos_check = j + 1;
      int y_pos_check = i + 1;

      int check_array[8];
      check_array[0] = image1[i][j];
      check_array[1] = image1[i][j + 1];
      check_array[2] = image1[i][j + 2];
      check_array[3] = image1[i + 1][j + 2];
      check_array[7] = image1[i + 1][j];
      check_array[4] = image1[i + 2][j];
      check_array[5] = image1[i + 2][j + 1];
      check_array[6] = image1[i + 2][j + 2];

      int fixed = median(8, check_array);
      image2[i][j] = fixed;
    }
  }

  save_image_data();

  return 0;
}

int median(int n, int *x) {
  int temp;
  int i, j;
  // the following two loops sort the array x in ascending order
  for(i=0; i<n-1; i++) {
    for(j=i+1; j<n; j++) {
      if(x[j] < x[i]) {
        // swap elements
        temp = x[i];
        x[i] = x[j];
        x[j] = temp;
      }
    }
  }

  if(n%2==0) {
    // if there is an even number of elements, return mean of the two elements in the middle
    return((x[n/2] + x[n/2 - 1]) / 2.0);
  } else {
    // else return the element in the middle
    return x[n/2];
  }
}
