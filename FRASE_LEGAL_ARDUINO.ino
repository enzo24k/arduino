#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
}

void loop() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);

  display.print(" Exibindo ");
  display.display();
  delay(500);

  display.print("uma frase   ");
  display.display();
  delay(500);
  
  display.print("legal");
  display.display();
  delay(500);
  display.clearDisplay();}
