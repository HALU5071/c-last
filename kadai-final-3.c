#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_one.h"
#include "debug.h"

#define N 9

// 256階調以上は存在しないので、ワイルドカードとして扱う
int array[N] = {6, 256, 11, 256, 256, 5, 256, 256, 15};

int getGray(int n);
int isTheSameArray(int *array1, int *array2);
int checkNumber(int n, int counter);
int findMark(void);
void showResult(int position);

int main(void) {

  int i;
  for(i = 1; i <= 5; i++) {
    char *s;
    sprintf(s, "img00%d.pgm", i);

    load_image_data(s);

    int position = findMark();

    showResult(position);
  }

  return 0;
}

void showResult(int position) {
  if (position == 0) {
    printf("　　見つかりませんでした\n");
  } else {
    printf("　　見つかりました！\n");
    printf("　　スタートポジション\n");
    printf("　　x : %d\n", position % x_size1);
    printf("　　y : %d\n", position / x_size1);
  }
}

int findMark(void) {

  int checkArray[N];

  // 画像の調べたい位置を表すカウンター変数
  int i = 0;
  int start_pos = 0;
  int max_count = x_size1 * y_size1;

  while (i < max_count) {
    if (checkNumber(6, i) != 1) {
      i++;
      continue;
    }
    if (i == max_count - 1) {
      break;
    }
    // 6を発見したら、そこから9つぶんの配列を作る
    int j, k;
    k = i;
    for (j = 0; j < N; j++) {
      checkArray[j] = getGray(k);
      k++;
    }

    // showArray(checkArray, N);

    // 2つの配列を比較する
    int result = isTheSameArray(array, checkArray);

    if (result == 1) {
      start_pos = i;
      break;
    } else {
      k = i;
      if (k + 9 > max_count) {
        break;
      }
      i = i + 1;
    }
  }

  return start_pos;
}

// 与えられた場所をもとに、その位置の画素値を返す
int getGray(int n) {
  int x_pos = n % x_size1;
  int y_pos = n / x_size1;

  return image1[y_pos][x_pos];
}

int isTheSameArray(int *array1, int *array2) {
  int i;
  for(i = 0; i < N; i++) {
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

// n : 確認したい数
// counter : 画像中のどこを参照するのか
int checkNumber(int n, int counter) {
  if (n == 256) {
    return 1;
  }

  if (getGray(counter) == n) {
    return 1;
  } else {
    return -1;
  }
}
