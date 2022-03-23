#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

struct Player {
  int x;
  bool shooting;
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
int frame = 0;
Player player;

void playerDraw(void) {
  u8g.drawBitmap(player.x - 4, 56, 1, 8,
                 player.shooting ? shootingPlayerBitmap : idlePlayerBitmap);
}

void drawInvader(int x, int y) {
  u8g.drawBitmap(x, y, 1, 8, invaderBitmaps[(frame >> 2) & 1]);
}

void draw(void) {
  for (int x = 4; x < 128; x += 16) {
    for (int y = 0; y < 48; y += 16) {
      drawInvader(x, y);
    }
  }
  playerDraw();
}

void setup(void) {
  pinMode(leftButton, INPUT);
  pinMode(shootButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  player.x = width / 2;
  player.shooting = false;
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

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
    draw();
  } while (u8g.nextPage());

  frame++;
}
