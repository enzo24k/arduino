const int ledPins[] = {9, 10, 11, 12}; // Pinos dos LEDs
const int touchPins[] = {2, 3, 4, 5};   // Pinos do sensor touch
int ledCount = 0;                       // Contador de LEDs acesos

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);        // Configura os pinos dos LEDs como saída
    pinMode(touchPins[i], INPUT);       // Configura os pinos do sensor touch como entrada
  }
}

void loop() {
  // Lê o estado de cada pino do sensor touch
  for (int i = 0; i < 4; i++) {
    if (digitalRead(touchPins[i]) == HIGH) { // Se o sensor for tocado
      ledCount = i + 1;                       // Define o contador com base no pino tocado
      break;                                   // Sai do loop após o primeiro toque
    }
  }

  // Atualiza os LEDs com base no contador
  for (int i = 0; i < 4; i++) {
    if (i < ledCount) {
      digitalWrite(ledPins[i], HIGH);         // Acende os LEDs de acordo com o contador
    } else {
      digitalWrite(ledPins[i], LOW);          // Apaga os LEDs que não devem estar acesos
    }
  }

  delay(200); // Aguarda um pouco antes de ler novamente
}
