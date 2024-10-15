const int ledPin1 = 7;
const int ledPin2 = 6;
const int xPin = A0;
const int yPin = A1;
const int buttonPin = 2;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);}
void loop() {
  static int lastButtonState = HIGH;
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();}
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading == LOW) {
      int xValue = analogRead(xPin);
      int yValue = analogRead(yPin);
      Serial.print("X: ");
      Serial.print(xValue);
      Serial.print(" | Y: ");
      Serial.println(yValue);
      analogWrite(ledPin1, map(xValue, 0, 1023, 0, 255));
      analogWrite(ledPin2, map(yValue, 0, 1023, 0, 255));
    }else{
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);}}
  lastButtonState = reading;}

