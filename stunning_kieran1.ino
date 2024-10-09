void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  int eixoX = analogRead(A0); // Lê o potenciômetro Eixo X
  int eixoY = analogRead(A1); // Lê o potenciômetro Eixo Y

  // Imprime os valores no monitor serial
  Serial.print("Eixo X: ");
  Serial.print(eixoX);
  Serial.print(" | Eixo Y: ");
  Serial.println(eixoY);

  delay(500); // Espera 500 ms antes da próxima leitura
}
