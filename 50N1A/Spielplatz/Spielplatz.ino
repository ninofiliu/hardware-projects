#include "U8glib.h"

const int xForce = 4;
const int bulletSpeed = 1;
const int nbFramesBetweenShots = 0;
const int moveDownEvery = 20;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

struct Player {
  int x;
  bool shooting;
};

struct Invader {
  bool alive;
  int x;
  int y;
};

struct Bullet {
  bool firing;
  int x;
  int y;
};

const uint8_t invaderBitmaps[2][8] = {{
                                          0b01011010,
                                          0b00111100,
                                          0b01111110,
                                          0b01011010,
                                          0b11011011,
                                          0b11111111,
                                          0b10100101,
                                          0b00100100,
                                      },
                                      {
                                          0b00011000,
                                          0b10111101,
                                          0b01111110,
                                          0b01011010,
                                          0b01011010,
                                          0b11111111,
                                          0b10011001,
                                          0b10011001,
                                      }};
const uint8_t idlePlayerBitmap[8] = {
    0b00011000, 0b00011000, 0b10011001, 0b10111101,
    0b11011011, 0b01011010, 0b01111110, 0b00100100,
};
const uint8_t shootingPlayerBitmap[8] = {
    0b00011000, 0b01011010, 0b01011010, 0b01111110,
    0b01011010, 0b01011010, 0b01111110, 0b01100110,
};
const int width = 128;
const int height = 64;
const int leftButton = 4;
const int shootButton = 3;
const int rightButton = 2;
const int nbInvadersX = 6;
const int nbInvadersY = 3;
const int nbBullets = 64;
int frame = 0;
int lastShootingFrame = 0;
Player player;
Invader invaders[nbInvadersX * nbInvadersY];
Bullet bullets[nbBullets];

void draw(void) {
  u8g.drawBitmap(player.x - 4, 56, 1, 8,
                 player.shooting ? shootingPlayerBitmap : idlePlayerBitmap);
  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    if (invaders[i].alive) {
      u8g.drawBitmap(invaders[i].x - 4, invaders[i].y - 4, 1, 8,
                     invaderBitmaps[frame % 2]);
    }
  }
  for (int i = 0; i < nbBullets; i++) {
    if (bullets[i].firing) {
      u8g.drawBox(bullets[i].x - 1, bullets[i].y - 1, 2, 2);
    }
  }
}

void finish(bool won) {
  u8g.firstPage();
  do {
    draw();
    u8g.drawStr(0, 0, won ? "You won!" : "You lose!");
  } while (u8g.nextPage());
  while (true) {
  }
}

void setup(void) {
  pinMode(leftButton, INPUT);
  pinMode(shootButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();

  while (digitalRead(leftButton) == LOW && digitalRead(shootButton) == LOW &&
         digitalRead(rightButton) == LOW) {
    u8g.firstPage();
    do {
      u8g.drawStr(0, 0, "Made with <3 for");
      u8g.drawStr(0, 10, "Sonia, the loveliest");
      u8g.drawStr(0, 20, "and queerest nerd in");
      u8g.drawStr(0, 30, "the whole universe");
    } while (u8g.nextPage());
  }

  player.x = width / 2;
  player.shooting = false;
  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    invaders[i].alive = true;
    invaders[i].x = 4 + 16 * (i % nbInvadersX);
    invaders[i].y = 4 + 16 * (i / nbInvadersX);
  }
  for (int i = 0; i < nbBullets; i++) {
    bullets[i].firing = false;
    bullets[i].x = 0;
    bullets[i].y = 0;
  }
}

void loop(void) {
  if (digitalRead(leftButton) == HIGH) {
    player.x -= xForce;
  };
  if (digitalRead(rightButton) == HIGH) {
    player.x += xForce;
  };
  player.x = min(width - 4, max(4, player.x));
  if (digitalRead(shootButton) == HIGH) {
    player.shooting = true;
    if (frame - lastShootingFrame >= nbFramesBetweenShots) {
      bullets[frame % nbBullets].firing = true;
      bullets[frame % nbBullets].x = player.x;
      bullets[frame % nbBullets].y = 60;
      lastShootingFrame = frame;
    }
  } else {
    player.shooting = false;
  }

  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    if (invaders[i].alive) {
      if ((frame % 80) < 40) {
        invaders[i].x++;
      } else {
        invaders[i].x--;
      }
      if (frame % moveDownEvery == 0) {
        invaders[i].y++;
      }
    }
  }

  for (int i = 0; i < nbBullets; i++) {
    if (bullets[i].firing) {
      bullets[i].y -= bulletSpeed;
      if (bullets[i].y == 0) {
        bullets[i].firing = false;
      } else {
        for (int j = 0; j < nbInvadersX * nbInvadersY; j++) {
          if (invaders[j].alive) {
            if (abs(invaders[j].x - bullets[i].x) <= 4 &&
                abs(invaders[j].y - bullets[i].y) < 4) {
              invaders[j].alive = false;
            }
          }
        }
      }
    }
  }

  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage());

  int nbInvadersAlive = 0;
  int maxInvadersY = 0;
  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    if (invaders[i].alive) {
      nbInvadersAlive++;
      maxInvadersY = max(maxInvadersY, invaders[i].y);
    }
  }
  if (nbInvadersAlive == 0) {
    finish(true);
  }
  if (maxInvadersY > 52) {
    finish(false);
  }

  frame++;
}
