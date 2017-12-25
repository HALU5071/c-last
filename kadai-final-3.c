#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int main(void) {
  // 画像データのロード
  load_image_data();
  x_size2 = x_size1;
  y_size2 = y_size1;


  save_image_data();

  return 0;
}
