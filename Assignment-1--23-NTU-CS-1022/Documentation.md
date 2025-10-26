# Task A — LED Mode Controller using ESP32 and OLED Display

##  Objective
To design a system using ESP32, where one button cycles through different LED operation modes and another button resets all LEDs to the OFF state.  
The current mode is displayed on an OLED screen.

---

##  Components Used

| Component | Quantity | Purpose |
|------------|-----------|----------|
| ESP32 | 1 | Main microcontroller |
| Push Buttons | 2 | One for changing modes, one for reset |
| LEDs | 3 | Visual indicators for mode behavior |
| OLED Display (SSD1306) | 1 | To display the current mode and status |
| Resistors | 3 | To limit LED current |

---

##  Pin Connections

| Component | ESP32 Pin | Description |
|------------|------------|--------------|
| Button 1 (Mode) | GPIO 15 | Cycles through LED modes |
| Button 2 (Reset) | GPIO 4 | Resets LEDs to OFF |
| LED1 | GPIO 13 | LED output |
| LED2 | GPIO 12 | LED output |
| LED3 | GPIO 14 | LED output |
| OLED SDA | GPIO 21 | I²C Data |
| OLED SCL | GPIO 22 | I²C Clock |

---

##  Modes Description

| Mode No. | OLED Display | Description |
|-----------|---------------|--------------|
| 1 | OFF | All LEDs are OFF |
| 2 | BLINK | LEDs blink alternately |
| 3 | ON | All LEDs are ON |
| 4 | FADE | LEDs fade in and out using PWM |

---

##  Working Principle

- **Mode Button (BTN_MODE)** — cycles through 4 LED modes in a loop.  
- **Reset Button (BTN_RESET)** — instantly resets all LEDs and returns the display to “OFF.”  
- **OLED Display** — updates dynamically to show the current mode and its name.  
- **PWM Fade** — smoothly increases and decreases LED brightness using `analogWrite()`.

---

##  Code Summary

- `mode` variable tracks the current LED behavior.  
- `millis()` is used for timing (non-blocking delay).  
- OLED is updated using `showMode()` function each time the mode changes.  
- The `setLEDs()` function simplifies controlling all three LEDs together.

---

##  Applications

- Demonstrating button-based state control.  
- Learning I²C communication with OLED.  
- Understanding PWM and timing control using ESP32.

---

# Task B — Button Press Detection with LED and Buzzer Feedback

##  Objective
To detect short and long button presses using ESP32 and perform actions:

- **Short press:** Toggle LEDs.  
- **Long press (>1.5s):** Play buzzer tone.  
- Display the event type on the OLED screen.

---

##  Components Used

| Component | Quantity | Purpose |
|------------|-----------|----------|
| ESP32 | 1 | Main controller |
| Push Button | 1 | Detect short/long presses |
| LEDs | 3 | Visual output |
| Buzzer | 1 | Sound alert on long press |
| OLED Display (SSD1306) | 1 | Display press type and status |

---

##  Pin Connections

| Component | ESP32 Pin | Description |
|------------|------------|--------------|
| Button | GPIO 4 | Input button |
| LED1 | GPIO 18 | Output |
| LED2 | GPIO 19 | Output |
| LED3 | GPIO 21 | Output |
| Buzzer | GPIO 5 | Output tone signal |
| OLED SDA | GPIO 23 | I²C Data |
| OLED SCL | GPIO 22 | I²C Clock |

---

##  Working Principle

- The button uses an internal pull-up resistor (active LOW).  
- When pressed, the time is recorded using `millis()`.  
- On release:
  - If pressed **less than 1.5s**, LEDs toggle ON/OFF.  
  - If pressed **longer than 1.5s**, a 1 kHz buzzer tone plays for 0.5 seconds.  
- OLED displays feedback such as **“Short Press Detected”** or **“Long Press Detected.”**

---

##  Code Summary

- `pressStart` records the press timestamp.  
- The difference between press and release time determines the action.  
- `tone()` and `noTone()` handle buzzer sound generation.  
- OLED provides instant user feedback for interaction clarity.

---

##  Applications

- Demonstrating input event handling.  
- Useful in embedded interfaces where a single button performs multiple actions.  
- Common in smart devices (like Bluetooth speakers or IoT gadgets).
