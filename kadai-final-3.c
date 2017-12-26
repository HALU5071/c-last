#include <stdio.h>
#include <stdlib.h>
#include "pgm_one.h"

int check(int n, int counter);

int main(void) {
  // 画像データのロード
  load_image_data();

  int array[4] = {6, 11, 5, 15};

  int i = 0;
  int max_count = x_size1 * y_size1 - 1;
  while (i <= max_count) {
    if (check(6, i) != 1) {
      i++;
      continue;
    }
    if (check(11, i + 2) != 1) {
      i++;
      continue;
    }
    if (check(5, i + 5) != 1) {
      i++;
      continue;
    }
    if (check(15, i + 8) == 1) {
      break;
    }
    i++;
  }
  if (i == max_count) {
    printf("ありませんでした\n");
    return 0;
  }
  int start_pos = i;
  printf("StartPos: %d\n", start_pos);

  return 0;
}

// n : 確認したい数
int check(int n, int counter) {
  int x_pos = counter % x_size1;
  int y_pos = counter / x_size1;
  if (image1[y_pos][x_pos] == n) {
    return 1;
  } else {
    return -1;
  }
}
