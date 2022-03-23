#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

uint8_t invaderBitmap[8] = {
    0b00011000, 0b00111100, 0b01111110, 0b01011010,
    0b01011010, 0b11111111, 0b10100101, 0b10100101,
};

void drawInvader(uint8_t x, uint8_t y) {
  u8g.drawBitmap(x, y, 1, 8, invaderBitmap);
}

void draw(void) {
  for (int x = 0; x < 128; x += 16) {
    for (int y = 0; y < 64; y += 16) {
      drawInvader(x, y);
    }
  }
}

void setup(void) {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop(void) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setFontPosTop();
    draw();
  } while (u8g.nextPage());
}
