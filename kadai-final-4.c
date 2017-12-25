#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pgm_base.h"
#include "pgm_face.h"

long checkSumDiff(int x, int y);

int main(void) {
  // 画像データのロード
  load_base_image_data();
  load_face_image_data();

  int x_pos_gacha = 0;
  int y_pos_gacha = 0;

  long tmpGraySum = LONG_MAX;

  int x, y;
  for (y = 0; y < y_base_size - 180; y++) {
    for (x = 0; x < x_base_size - 180; x++) {
      long sumDiffTmp = checkSumDiff(x, y);
      if (sumDiffTmp < tmpGraySum) {
        tmpGraySum = sumDiffTmp;
        x_pos_gacha = x;
        y_pos_gacha = y;
      }
    }
  }

  printf("見つけた！\n");
  printf("x座標: %d\n", x_pos_gacha);
  printf("y座標: %d\n", y_pos_gacha);

  return 0;
}

long checkSumDiff(int x, int y) {
  int xTmp, yTmp;
  long sumGray = 0;
  for (yTmp = y; yTmp < y + 180; yTmp++) {
    for (xTmp = x; xTmp < x + 180; xTmp++) {
      int grayFace = imageFace[yTmp - y][xTmp - x];
      int grayBase = imageBase[yTmp][xTmp];
      if (grayBase >= grayFace) {
        sumGray = sumGray + (grayBase - grayFace);
      } else {
        sumGray = sumGray + (grayFace - grayBase);
      }
    }
  }
  return sumGray;
}
