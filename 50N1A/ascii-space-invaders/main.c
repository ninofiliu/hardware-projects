#include <stdio.h>
#include <unistd.h>

const int width = 32;
const int height = 8;

struct Player {
  int x;
  int lives;
};

struct Bullet {
  char firing;
  int x;
  int y;
};

void draw(struct Player player, struct Bullet bullets[height]) {
  char screen[width * height];

  for (int i = 0; i < width * height; i++) {
    screen[i] = ' ';
  }

  screen[width * (height - 1) + player.x] = '0' + player.lives;
  for (int i = 0; i < height; i++) {
    if (bullets[i].firing) {
      screen[width * bullets[i].y + bullets[i].x] = '^';
    }
  }

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

  struct Bullet bullets[height];
  for (int i = 0; i < height; i++) {
    bullets[i].firing = 0;
    bullets[i].x = 0;
    bullets[i].y = 0;
  }

  for (int j = 0; j < 1000; j++) {
    player.x = (player.x + 1) % width;
    bullets[j % height].firing = 1;
    bullets[j % height].x = player.x;
    bullets[j % height].y = height - 1;
    for (int k = 0; k < height; k++) {
      if (bullets[k].firing) {
        bullets[k].y--;
      }
    }
    draw(player, bullets);
    sleep(1);
  }

  return 0;
}
