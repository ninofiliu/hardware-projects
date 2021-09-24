#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void set_light(int on) {
  int width = 50;
  int height = 25;
  char* s = on ? "X" : "_";
  for (int line = 0; line < height; line++) {
    for (int column = 0; column < width; column++) {
      printf("%s", s);
    }
    printf("\n");
  }
  for (int line = 0; line < height; line++) {
    printf("\e[F");
  }
}

float rand_float_range(float from, float to) {
  float scale = rand() / (float)RAND_MAX;
  return from + scale * (to-from);
}

float rand_int_range(int min, int max) {
  return min + rand()%(max-min);
}

void stays_on() {
  float min_duration = 1.0;
  float max_duration = 5.0;

  float duration = rand_float_range(min_duration, max_duration);
  set_light(1);
  usleep((int)(duration*1000*1000));
}

void stays_off() {
  float min_duration = 1.0;
  float max_duration = 5.0;

  float duration = rand_float_range(min_duration, max_duration);
  set_light(0);
  usleep((int)(duration*1000*1000));
}

void flickers() {
  float total_min_duration = 0.0;
  float total_max_duration = 5.0;
  float flicker_duration = 1.0 / 20;

  float total_duration = rand_float_range(total_min_duration, total_max_duration);
  for (int i = 0; i < (int)(total_duration/flicker_duration); i++) {
    set_light(rand() % 2);
    usleep((int)(flicker_duration*1000*1000));
  }
}

void setup() {}

void loop() {
  int min_nb_flickers = 1;
  int max_nb_flickers = 5;

  int nb_flickers = rand_int_range(min_nb_flickers, max_nb_flickers);
  stays_on();
  for (int i = 0; i < nb_flickers; i++) {
    flickers();
    stays_off();
  }
}

void main() {
  setup();
  while(1) {
    loop();
  }
}
