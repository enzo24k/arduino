const int ledPin = 9;
const int touchPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(touchPin, INPUT);}

void loop() {
  int touchState = digitalRead(touchPin);

  if (touchState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);}}
