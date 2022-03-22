#include <stdio.h>

const int width = 32;
const int height = 8;

void draw(char screen[]) {
  printf("\033[0;0H");
  putchar('+');
  for (int x = 0; x < width; x++) {
    putchar('-');
  }
  putchar('+');
  putchar('\n');
  for (int y = 0; y < height; y++) {
    putchar('|');
    for (int x = 0; x < width; x++) {
      putchar(screen[width * y + x]);
    }
    putchar('|');
    putchar('\n');
  }
  putchar('+');
  for (int x = 0; x < width; x++) {
    putchar('-');
  }
  putchar('+');
  putchar('\n');
}

int main() {
  char screen[width * height];
  for (int i = 0; i < width * height; i++) {
    screen[i] = 'x';
  }
  draw(screen);
  return 0;
}
