#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4 // Green LED pin
#define LED_R 5 // Red LED pin
#define ENDERECO  0x3F // I2C Address of the LCD
#define COLUNAS   16
#define LINHAS    2

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(ENDERECO, COLUNAS, LINHAS);

const String authorizedUIDs[] = {"A3 7B FB 1A"}; // Array of authorized UIDs

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Scan Card...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  bool authorized = false;
  
  for (const String &uid : authorizedUIDs) {
    if (content.substring(1) == uid) {
      authorized = true;
      break;
    }
  }

  if (authorized) {
    digitalWrite(LED_G, HIGH);
    Serial.println("Authorized access");
    lcd.clear();
    lcd.print("Acesso Permitido");
    delay(3000);
    digitalWrite(LED_G, LOW);
  } else {
    digitalWrite(LED_R, HIGH);
    Serial.println("Access denied");
    lcd.clear();
    lcd.print("Acesso Negado");
    delay(3000);
    digitalWrite(LED_R, LOW);
  }
}
