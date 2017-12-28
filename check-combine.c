#include <stdio.h>
#include <stdlib.h>

#define N 256

int main(void) {

  int i;
  for(i = 1; i <= 5; i++) {
    char s[N] = {"\0"};

    sprintf(s, "img00%d.pgm", i);

    printf("%s\n", s);
  }

  return 0;
}
