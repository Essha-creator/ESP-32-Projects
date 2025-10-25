# ESP32 Sensor & Display Projects

This project is built around the ESP32, a powerful microcontroller that combines Wi-Fi, Bluetooth, and plenty of GPIOs.
Here I’ve explored how to connect and control components like an OLED display, LDR (Light Dependent Resistor), and DHT sensor to build small interactive systems that sense, display, and respond to their environment.

## About the ESP32

The ESP32 is a low-cost, low-power SoC (System on Chip) with built-in Wi-Fi and Bluetooth.
It’s widely used in IoT, automation, and embedded projects because it can sense, process, and communicate — all in one board.

## Key Specifications
Feature	Description
Processor	Dual-core Tensilica LX6 @ up to 240 MHz
Flash Memory	4 MB (varies by board)
SRAM	520 KB
Wi-Fi	802.11 b/g/n
Bluetooth	v4.2 BR/EDR and BLE
Operating Voltage	3.3 V
I/O Pins	30–36 GPIOs (depending on model)
ADC / DAC	12-bit ADC, 2 × 8-bit DAC
PWM	Up to 16 channels
Communication	UART, SPI, I²C, I²S, CAN
Timers / Interrupts	Multiple 64-bit hardware timers
Power Modes	Active, Sleep, Deep Sleep

The ESP32 can read sensors, control actuators, and display information all at once, making it perfect for multi-component projects like this one.

## Components Used
### OLED Display (SSD1306)

Purpose: To visually display sensor readings or system states.

How it works: Communicates with the ESP32 using I²C protocol (two wires — SDA & SCL).
Text or graphics are sent as pixel data, which the OLED renders on its small screen.

Why used: It gives real-time visual feedback — useful for debugging, monitoring sensors, or showing modes without a serial monitor.

 ### DHT Sensor (DHT11 or DHT22)

Purpose: To measure temperature and humidity.

How it works: Contains a humidity-sensing capacitor and a thermistor. It converts analog signals into digital form before sending to the ESP32.

Why used: Adds environmental sensing ability. Perfect for weather monitoring, smart home systems, or IoT dashboards.

### LDR (Light Dependent Resistor)

Purpose: To detect light intensity.

How it works: The LDR’s resistance decreases when light increases.
The ESP32 reads this change as an analog voltage using its ADC (Analog-to-Digital Converter).

Why used: It helps in automating light-based systems — for example, turning LEDs or displays on/off depending on brightness.

### Buzzer

Purpose: To give audio feedback or alerts.

How it works: The ESP32 generates a PWM signal that makes the buzzer vibrate, producing sound.

Why used: Great for alarms, mode notifications, or button-press confirmation sounds.

### LEDs & Buttons

Purpose: To create visual indicators and user interaction.

How they work:

LEDs are driven by ESP32’s GPIOs (with optional PWM for brightness control).

Buttons are read using digital inputs, sometimes with INPUT_PULLUP to keep the signal stable.

Why used: They turn a basic microcontroller setup into an interactive, user-friendly system.

### What Each Part Does Together
Component	Role	Example Use
ESP32	Core controller	Runs the logic and communicates with sensors
OLED	Display output	Shows live temperature, light level, or LED mode
LDR	Sensor input	Reads light intensity to adjust brightness or trigger LEDs
DHT	Sensor input	Reads temperature/humidity for display or control
Buttons	User input	Changes display modes or resets readings
Buzzer	Output alert	Signals a long press or threshold alert
### Example Workflow

ESP32 reads sensor data:

LDR gives analog light values.

DHT sensor gives temperature & humidity.

ESP32 processes data:

Converts readings into usable numbers.

Applies simple logic (for example: if light < threshold → turn on LEDs).

OLED shows the data:

Displays temperature, humidity, and light level clearly.

Button or buzzer interaction:

Short press toggles LEDs or display modes.

Long press triggers buzzer or resets display.

## Wiring Summary
Component	ESP32 Pin Example	Notes
OLED SDA	GPIO 21 / 23	I²C data line
OLED SCL	GPIO 22	I²C clock line
LDR	GPIO 34 (ADC)	Reads analog light value
DHT	GPIO 14	Digital data pin
LEDs	GPIO 12, 13, 14	Can use PWM
Buzzer	GPIO 5	Use tone() for sound
Buttons	GPIO 4, 15	INPUT_PULLUP mode recommended
## Libraries Used

Make sure these are installed before compiling:

Adafruit GFX Library
Adafruit SSD1306
DHT Sensor Library


Install from Arduino Library Manager or add via PlatformIO:

lib_deps =
    adafruit/Adafruit GFX Library
    adafruit/Adafruit SSD1306
    adafruit/DHT sensor library

## Why ESP32?

Unlike basic Arduino boards, the ESP32 is:

Faster (240 MHz dual-core)

Has Wi-Fi & Bluetooth built-in

Can run multiple tasks simultaneously

Supports deep sleep to save power

Reads analog and digital data with high precision

It’s essentially a bridge between sensors and the Internet, making it ideal for IoT and smart devices.
