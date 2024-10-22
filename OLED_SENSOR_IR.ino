#include <U8g2lib.h>
#define pinSensor1 7

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
    u8g2.begin();
    pinMode(pinSensor1, INPUT);
    Serial.begin(9600);}

void loop() {
    u8g2.clearBuffer();

    bool estadoSensor1 = digitalRead(pinSensor1);
    
    if (estadoSensor1) {
        Serial.println("OBSTACULO");
    } else {
        Serial.println("LIVRE");}

    u8g2.setFont(u8g2_font_helvB12_tr);

    if (estadoSensor1) {
        u8g2.setCursor(40, 40);
        u8g2.print("LIVRE");
    } else {
        u8g2.setCursor(10, 40);
        u8g2.print("OBSTACULO");}

    u8g2.sendBuffer();

    delay(500);}