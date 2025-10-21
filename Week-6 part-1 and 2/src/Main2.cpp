#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

using namespace std;

// --- Pin configuration ---
#define DHTPIN 14        // DHT22 data pin
#define DHTTYPE DHT22    // Change to DHT11 if needed
#define LDR_PIN 34       // LDR analog pin (ADC input)
#define SDA_PIN 21       // I2C SDA
#define SCL_PIN 22       // I2C SCL

// --- OLED setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- DHT sensor setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- Setup function ---
void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Sensor Display");

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20, 25);
  display.println("Initializing...");
  display.display();

  dht.begin();
  delay(1000);
}

// --- Main loop ---
void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);
  float voltage = ldrValue * (3.3 / 4095.0);  // Convert ADC reading to voltage

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT22 sensor!");
    return;
  }

  Serial.printf("Temp: %.1f °C | Humidity: %.1f %% | LDR Voltage: %.2f V\n", temperature, humidity, voltage);

  // --- OLED Display ---
  display.clearDisplay();

  // Outer rectangle
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

  // Temperature (compact format)
  display.setTextSize(1);
  display.setCursor(8, 10);
  display.print("Temp:");
  display.setTextSize(2);
  display.setCursor(60, 5);
  display.print((int)temperature);
  display.setTextSize(1);
  display.print("C");

  // Humidity
  display.setTextSize(1);
  display.setCursor(8, 30);
  display.print("Humid:");
  display.setTextSize(2);
  display.setCursor(60, 25);
  display.print((int)humidity);
  display.setTextSize(1);
  display.print("%");

  // Voltage
  display.setTextSize(1);
  display.setCursor(8, 50);
  display.print("Volt:");
  display.setTextSize(1);
  display.setCursor(50, 50);
  display.print(voltage, 2);
  display.print("V");

  display.display();

  delay(2000);
}
