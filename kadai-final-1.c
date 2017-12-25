#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

#define N 256

int main(void) {
  // 画像データのロード
  load_image_data();
  x_size2 = x_size1;
  y_size2 = y_size1;

  // グローバル変数 image1には画像のデータが入っている
  // 参照テーブルのためのファイルポインタ
  FILE *fp;
  char fname[] = "table.txt";

  // ファイルオープン
  fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	} else {
		printf("%s file opened!\n", fname);
	}

  // ファイル中の行数をカウントする変数
  int counter = 0;
  int chr;
  char readline[N] = {'\0'};
  while(fgets(readline, N, fp) != NULL) {
    chr = atoi(readline);

    int y_image1 = counter / x_size1;
    int x_image1 = counter % x_size1;

    int y_image2 = chr / x_size1;
    int x_image2 = chr % x_size1;

    image2[y_image2][x_image2] = image1[y_image1][x_image1];
    counter = counter + 1;
	}

  save_image_data();

  return 0;
}
