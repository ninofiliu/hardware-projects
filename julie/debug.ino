void setup() {
  Serial.begin(9600);

  Serial.println("Light should blink once a second");
  for (int i = 0; i < 10; i++) {
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
  }

  Serial.println("Should print integers between 10 and 30");
  for (int i = 0; i < 10; i++) {
    Serial.println(random(10, 30));
  }

  Serial.prinln("Should print floats between 10 and 30");
  for (int i = 0; i < 10; i++) {
    Serial.println(random(10.0, 30.0));
  }

}
void loop() {

}
