
void showArray(int *array, int size);

void showArray(int *array, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (i == 0) {
      printf("{%d, ", array[i]);
    } else if (i == size - 1) {
      printf("%d}\n", array[i]);
    } else {
      printf("%d, ", array[i]);
    }
  }
}
