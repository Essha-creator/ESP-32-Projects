#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==== Pin Definitions (Updated) ====
#define BTN1 4     // Push button
#define LED1 18    // LED 1
#define LED2 19    // LED 2
#define LED3 21    // LED 3
#define BUZZ 5     // Buzzer

// ==== OLED Setup ====
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// ==== Variables ====
unsigned long pressStart = 0;
bool isPressed = false;
bool ledsOn = false;

void setup() {
  pinMode(BTN1, INPUT_PULLUP);  // Button with internal pull-up
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BUZZ, LOW);

  // ==== Initialize OLED ====
  Wire.begin(23, 22); // SDA = 23, SCL = 22 (ESP32 default wiring in Wokwi)
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("Ready...");
  oled.display();
}

void loop() {
  int buttonState = digitalRead(BTN1);

  // Detect press start
  if (buttonState == LOW && !isPressed) {
    isPressed = true;
    pressStart = millis();
  }

  // Detect button release
  if (buttonState == HIGH && isPressed) {
    unsigned long duration = millis() - pressStart;
    isPressed = false;

    oled.clearDisplay();

    // Short press -> toggle LEDs
    if (duration < 1500) {
      ledsOn = !ledsOn;
      digitalWrite(LED1, ledsOn);
      digitalWrite(LED2, ledsOn);
      digitalWrite(LED3, ledsOn);

      oled.setCursor(0, 0);
      oled.println("Short Press Detected");
      oled.setCursor(0, 16);
      oled.println(ledsOn ? "LEDs: ON" : "LEDs: OFF");
      oled.display();
    } 
    // Long press -> play buzzer
    else {
      oled.setCursor(0, 0);
      oled.println("Long Press Detected");
      oled.setCursor(0, 16);
      oled.println("Playing buzzer...");
      oled.display();

      tone(BUZZ, 1000, 500); // 1kHz tone for 0.5s
      delay(500);
      noTone(BUZZ);
    }
  }
}
