int potX = A0;
int potY = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valorX = analogRead(potX);
  int valorY = analogRead(potY);
  
  if (valorY < 341) {
    Serial.println("Para baixo");
  } else if (valorY > 682) {
    Serial.println("Para cima");
  } else {
    Serial.println("Eixo Y neutro");
  }

  if (valorX < 341) {
    Serial.println("Para esquerda");
  } else if (valorX > 682) {
    Serial.println("Para direita");
  } else {
    Serial.println("Eixo X neutro");
  }

  delay(500);
}
