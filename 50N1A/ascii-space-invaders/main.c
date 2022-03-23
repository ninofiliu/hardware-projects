#include <stdio.h>
#include <unistd.h>

const int width = 32;
const int height = 8;

struct Player {
  int x;
  int lives;
};

void draw(struct Player player) {
  char screen[width * height];

  for (int i = 0; i < width * height; i++) {
    screen[i] = ' ';
  }

  screen[width * (height - 1) + player.x] = '0' + player.lives;

  printf("\033[0;0H+");
  for (int x = 0; x < width; x++) {
    putchar('-');
  }
  printf("+\n");
  for (int y = 0; y < height; y++) {
    putchar('|');
    for (int x = 0; x < width; x++) {
      putchar(screen[width * y + x]);
    }
    printf("|\n");
  }
  putchar('+');
  for (int x = 0; x < width; x++) {
    putchar('-');
  }
  printf("+\n");
}

int main() {
  struct Player player;
  player.x = 0;
  player.lives = 5;

  for (int j = 0; j < 1000; j++) {
    player.x = (player.x + 1) % width;
    draw(player);
    usleep((int)(1000 * 1000 / 60));
  }

  return 0;
}
