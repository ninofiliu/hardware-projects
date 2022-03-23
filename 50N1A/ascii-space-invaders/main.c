#include <stdio.h>
#include <unistd.h>

const int width = 32;
const int height = 8;
const int nb_bullets = height;
const int nb_invaders = (width / 2) * (height / 2);

struct Player {
  int x;
  int lives;
};

struct Bullet {
  char firing;
  int x;
  int y;
};

struct Invader {
  char alive;
  int x;
  int y;
};

void draw(struct Player player, struct Bullet bullets[nb_bullets],
          struct Invader invaders[nb_invaders]) {
  char screen[width * height];

  for (int i = 0; i < width * height; i++) {
    screen[i] = ' ';
  }

  screen[width * (height - 1) + player.x] = '0' + player.lives;
  for (int i = 0; i < nb_bullets; i++) {
    if (bullets[i].firing) {
      screen[width * bullets[i].y + bullets[i].x] = '^';
    }
  }
  for (int i = 0; i < nb_invaders; i++) {
    if (invaders[i].alive) {
      screen[width * invaders[i].y + invaders[i].x] = 'X';
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

  struct Bullet bullets[nb_bullets];
  for (int i = 0; i < nb_bullets; i++) {
    bullets[i].firing = 0;
    bullets[i].x = 0;
    bullets[i].y = 0;
  }

  struct Invader invaders[nb_invaders];
  for (int i = 0; i < nb_invaders; i++) {
    invaders[i].alive = 1;
    invaders[i].x = 2 * (i % (width / 2));
    invaders[i].y = i / (width / 2);
  }

  for (int j = 0; j < 100; j++) {
    player.x = (player.x + 1) % width;
    bullets[j % nb_bullets].firing = 1;
    bullets[j % nb_bullets].x = player.x;
    bullets[j % nb_bullets].y = height - 1;
    for (int k = 0; k < nb_bullets; k++) {
      if (bullets[k].firing) {
        bullets[k].y--;
      }
    }
    for (int k = 0; k < nb_bullets; k++) {
      for (int l = 0; l < nb_invaders; l++) {
        if (bullets[k].firing && invaders[l].alive &&
            bullets[k].x == invaders[l].x && bullets[k].y == invaders[l].y) {
          invaders[l].alive = 0;
          bullets[k].firing = 0;
        }
      }
    }
    draw(player, bullets, invaders);
    sleep(1);
  }

  return 0;
}
