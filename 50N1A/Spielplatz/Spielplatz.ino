#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

struct Player {
  int x;
  bool shooting;
};

struct Invader {
  int x;
  int y;
  bool alive;
};

uint8_t invaderBitmaps[2][8] = {{
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
uint8_t idlePlayerBitmap[8] = {
    0b00011000, 0b00011000, 0b10011001, 0b10111101,
    0b11011011, 0b01011010, 0b01111110, 0b00100100,
};
uint8_t shootingPlayerBitmap[8] = {
    0b00011000, 0b01011010, 0b01011010, 0b01111110,
    0b01011010, 0b01011010, 0b01111110, 0b01100110,
};
const int width = 128;
const int height = 64;
const int leftButton = 4;
const int shootButton = 3;
const int rightButton = 2;
const int xForce = 4;
const int nbInvadersX = 6;
const int nbInvadersY = 3;
int frame = 0;
Player player;
Invader invaders[nbInvadersX * nbInvadersY];

void draw(void) {
  u8g.drawBitmap(player.x - 4, 56, 1, 8,
                 player.shooting ? shootingPlayerBitmap : idlePlayerBitmap);
  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    if (invaders[i].alive) {
      u8g.drawBitmap(invaders[i].x - 4, invaders[i].y - 4, 1, 8,
                     invaderBitmaps[frame % 2]);
    }
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

  player.x = width / 2;
  player.shooting = false;
  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    invaders[i].alive = true;
    invaders[i].x = 4 + 16 * (i % nbInvadersX);
    invaders[i].y = 4 + 16 * (i / nbInvadersX);
  }
}

void loop(void) {
  if (digitalRead(leftButton) == HIGH) {
    player.x -= xForce;
  };
  if (digitalRead(rightButton) == HIGH) {
    player.x += xForce;
  };
  player.x = min(width - 4, max(0, player.x));
  player.shooting = digitalRead(shootButton) == HIGH;

  for (int i = 0; i < nbInvadersX * nbInvadersY; i++) {
    if (invaders[i].alive) {
      if ((frame % 80) < 40) {
        invaders[i].x++;
      } else {
        invaders[i].x--;
      }
      if (frame % 40 == 0) {
        invaders[i].y++;
      }
    }
  }

  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage());

  frame++;
}
