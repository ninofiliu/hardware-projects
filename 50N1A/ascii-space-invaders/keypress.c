#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios termios_init;

void restore_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_init); }

int main() {
  struct termios termios_raw;
  char c;

  tcgetattr(STDIN_FILENO, &termios_init);
  termios_raw = termios_init;
  termios_raw.c_lflag &= ~(ECHO | ICANON);
  atexit(restore_raw_mode);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_raw);

  while (read(STDIN_FILENO, &c, 1) == 1) {
    printf("%d %c\n", c, c);
    if (c == 'q') {
      return 0;
    }
  }

  return 0;
}
