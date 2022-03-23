const int leftButton = 4;
const int rightButton = 2;

void setup() {
  Serial.begin(9600);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
}

void loop() {
  int leftPressed = digitalRead(leftButton);
  int rightPressed = digitalRead(rightButton);
  int xShift = 0;
  if (leftPressed == HIGH) { xShift--; }
  if (rightPressed == HIGH) { xShift++; }
  Serial.println(xShift);
  delay(40); // ~24fps
}
