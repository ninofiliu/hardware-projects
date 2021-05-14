#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  printf("\n");
  for (int i = 0; i < 100; i++) {
    printf("\e[F");
    int on = rand() % 2;
    printf(on ? "XXXXXXXX" : "........");
    printf("\n");
    usleep(50 * 1000);
  }
  printf("\n");
  return 0;
}
