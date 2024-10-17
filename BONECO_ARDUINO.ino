#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);}

void loop() {
  display.clearDisplay();

  display.fillCircle(64, 15, 10, WHITE);

  display.drawLine(64, 25, 64, 50, WHITE);

  display.drawLine(64, 30, 50, 40, WHITE);
  display.drawLine(64, 30, 78, 40, WHITE);

  display.drawLine(64, 50, 50, 60, WHITE); // Perna esquerda
  display.drawLine(64, 50, 78, 60, WHITE); // Perna direita

  display.display();
  delay(2000);}
