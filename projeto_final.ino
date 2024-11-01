#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define LDR_PIN A0
#define LM35_PIN A1
#define BUZZER_PIN 3
#define RST_PIN 9
#define SS_PIN 10
#define OLED_RESET -1

// Pinos do TTP224
#define TOUCH_PIN_1 4 // TTP224 pino 1
#define TOUCH_PIN_2 5 // TTP224 pino 2
#define TOUCH_PIN_3 6 // TTP224 pino 3
#define TOUCH_PIN_4 7 // TTP224 pino 4

Adafruit_SH1106 display(OLED_RESET);
MFRC522 mfrc522(SS_PIN, RST_PIN);

byte targetUID[] = {0x66, 0x62, 0x25, 0xF8}; // UID da tag
bool accessGranted = false;
bool inSettingsMenu = false;

void setup() {
    Serial.begin(9600);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TOUCH_PIN_1, INPUT);
    pinMode(TOUCH_PIN_2, INPUT);
    pinMode(TOUCH_PIN_3, INPUT);
    pinMode(TOUCH_PIN_4, INPUT);
    
    SPI.begin();
    mfrc522.PCD_Init();
    
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
    
    Serial.println("Sistema inicializado. Aproxime um cartão RFID.");
}

void loop() {
    // Leitura de luminosidade e temperatura
    int ldrValue = analogRead(LDR_PIN);
    int rawValue = analogRead(LM35_PIN);
    float voltage = rawValue * (5.0 / 1023.0);
    float temperature = voltage * 100;

    // Alerta de luminosidade baixa
    if (ldrValue < 100) {
        tone(BUZZER_PIN, 100);
        display.clearDisplay();
        display.setCursor(0, 10);
        display.print("Luminosidade BAIXA!");
        display.display();
        delay(500);
        display.clearDisplay();
    } else {
        noTone(BUZZER_PIN);
    }

    // Leitura do cartão RFID
    if (!mfrc522.PICC_IsNewCardPresent()) {
        if (!inSettingsMenu) {
            displayData(ldrValue, temperature);
        }
        return;
    }
    
    if (!mfrc522.PICC_ReadCardSerial()) {
        if (!inSettingsMenu) {
            displayData(ldrValue, temperature);
        }
        return;
    }

    // Verificação do UID
    bool isTargetUID = true;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] != targetUID[i]) {
            isTargetUID = false;
        }
    }

    if (isTargetUID) {
        accessGranted = true;
        displayAccessGranted();
        inSettingsMenu = true; // Entra no menu de configurações
    }

    // Navegação com TTP224
    if (accessGranted && inSettingsMenu) {
        navigateSettings();
    }
}

void displayData(int ldrValue, float temperature) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.print("LDR: ");
    display.println(ldrValue);
    display.print("Temp: ");
    display.print(temperature);
    display.println(" C");
    display.display();
}

void displayAccessGranted() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Acesso Liberado");
    display.display();
    delay(2000);
}

void showMainMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Configurações:");
    display.println("Clique 1: Acessar");
    display.println("Clique 2: Voltar");
    display.display();
}

void navigateSettings() {
    if (digitalRead(TOUCH_PIN_1) == HIGH) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Menu de Opcoes:");
        display.println("Clique 3: Opcao 1");
        display.println("Clique 4: Opcao 2");
        display.display();
        
        delay(200); // Delay para evitar leituras rápidas
        
        if (digitalRead(TOUCH_PIN_3) == HIGH) {
            showOption1();
        }
        if (digitalRead(TOUCH_PIN_4) == HIGH) {
            showOption2();
        }
    }
    if (digitalRead(TOUCH_PIN_2) == HIGH) {
        accessGranted = false; // Reseta o acesso após voltar
        inSettingsMenu = false; // Volta ao modo inicial
    }
}

void showOption1() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("opcao 1");
    display.setTextSize(1);
    display.println("Temperatura em K");
    display.display();
}

void showOption2() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("opcao 2");
    display.setTextSize(1);
    display.println("Dados Adicionais");
    display.display();
}
