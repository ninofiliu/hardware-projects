void setup() {
  pinMode(8, OUTPUT);
}

// lights off
void loop() {}
/* */

// basic
/* int fps = 20;
int interval = 1000 / fps;
void loop() {
  digitalWrite(8, random(2) == 0 ? HIGH : LOW);
  delay(interval);
}
/* */

// random moods
/* int fps = 20;
int mood_s = 2;
int interval = 1000 / fps;
int mood_length = fps * mood_s;
void loop() {
  int mood_threshold = random(100);
  for (int i = 0; i < mood_length; i++) {
    digitalWrite(8, random(100) < mood_threshold ? HIGH : LOW);
    delay(interval);
  }
}
/* */

// computed moods
/* int fps = 20;
int interval = 1000 / fps;
void loop() {
  int mood_value = random(3);
  if (mood_value==0) {
    for (int i = 0; i < fps * 5; i++) {
      digitalWrite(8, random(10) < 1 ? HIGH : LOW);
      delay(interval);
    }
  }
  if (mood_value==1) {
    for (int i = 0; i < fps * 2; i++) {
      digitalWrite(8, random(10) < 5 ? HIGH : LOW);
      delay(interval);
    }
    
  }
  if (mood_value==2) {
    for (int i = 0; i < fps * 5; i++) {
      digitalWrite(8, random(10) < 10 ? HIGH : LOW);
      delay(interval);
    }
    
  }
}
/* */
