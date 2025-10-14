
#include <Arduino.h>

// --- Buzzer setup ---
#define BUZZER_PIN  27       // GPIO connected to buzzer
#define BUZZER_CH   0        // PWM channel for buzzer
#define BUZZER_FREQ 2000     // Base frequency (Hz)
#define BUZZER_RES  10       // 10-bit resolution

// --- LED setup ---
#define LED1_PIN 18           // First LED pin
#define LED2_PIN 19           // Second LED pin
#define LED1_CH  1            // PWM channel for LED1
#define LED2_CH  2            // PWM channel for LED2
#define LED_FREQ 5000         // Frequency for LED PWM
#define LED_RES  8            // 8-bit (0–255) resolution

void setup() {
  // --- Setup for buzzer ---
  ledcSetup(BUZZER_CH, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(BUZZER_PIN, BUZZER_CH);

  // --- Setup for LEDs ---
  ledcSetup(LED1_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);

  ledcSetup(LED2_CH, LED_FREQ, LED_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);
}

void loop() {
  // --- Fade both LEDs together ---
  for (int d = 0; d <= 255; d++) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);  // opposite fade effect
    delay(5);
  }
  for (int d = 255; d >= 0; d--) {
    ledcWrite(LED1_CH, d);
    ledcWrite(LED2_CH, 255 - d);
    delay(5);
  }

  // --- Buzzer pattern (plays while LEDs glow) ---
  // 1. Simple beep pattern
  for (int i = 0; i < 3; i++) {
    ledcWriteTone(BUZZER_CH, 2000 + i * 400);
    delay(150);
    ledcWrite(BUZZER_CH, 0);
    delay(150);
  }

  // 2. Frequency sweep
  for (int f = 400; f <= 3000; f += 100) {
    ledcWriteTone(BUZZER_CH, f);
    delay(10);
  }
  ledcWrite(BUZZER_CH, 0);
  delay(200);

  // 3. Short melody
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
  for (int i = 0; i < 8; i++) {
    ledcWriteTone(BUZZER_CH, melody[i]);
    delay(200);
  }
  ledcWrite(BUZZER_CH, 0);
}
