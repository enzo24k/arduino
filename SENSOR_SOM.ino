#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Fonts/FreeMono9pt7b.h>

#define OLED_RESET -1
#define SENSOR_SOM 2

Adafruit_SH1106 display(OLED_RESET);

void setup() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  pinMode(SENSOR_SOM, INPUT);
  Serial.begin(9600);
}

void loop() {
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b);
  display.setTextColor(WHITE);
  display.setTextSize(0);

  bool sensorAtivo = digitalRead(SENSOR_SOM);
  
  if (sensorAtivo) {
    exibirMensagem("Som", "Detectado");
  } else {
    exibirMensagem("Som", "Nao Detectado");
  }

  display.display();
  delay(100);
}

void exibirMensagem(const char* linha1, const char* linha2) {
  display.setCursor(0, 10);
  display.print(linha1);
  display.setCursor(0, 40);
  display.print(linha2);
}
