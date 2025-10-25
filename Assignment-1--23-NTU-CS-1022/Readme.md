ESP32 Button + OLED Project:
This little project shows how you can use buttons, LEDs, a buzzer, and an OLED display with an ESP32.
It’s split into two small challenges — one about controlling LED patterns, and the other about detecting how long you press a button.
Simple, but a good mix of hardware control and logic.

What It Does:
Task A — Multi-Mode LED Controller
One button cycles through different LED modes, and the OLED shows which mode you’re in.
A second button resets everything back to “OFF.”

Modes:

Mode Description	    Behavior
1	Both OFF	        All LEDs off
2	Alternate Blink	    LEDs blink one after the other
3	Both ON	            All LEDs stay on
4	PWM Fade	        LEDs smoothly fade in and out

Buttons:
Mode Button: changes the LED mode (goes from 0 → 3, then loops)
Reset Button: sets all LEDs to OFF and shows “OFF” on the OLED

Task B — Short vs Long Press
This one uses just a single button.
A short press toggles the LEDs, and a long press (over 1.5 seconds) plays a buzzer tone.
The OLED updates each time to tell you what just happened.

Type	        Duration	Action
Short Press	< 1.5 seconds	Toggle LEDs ON/OFF
Long Press	> 1.5 seconds	Play a buzzer tone

Hardware Setup
Part	ESP32 Pin	Use
BTN_MODE	15	Mode button
BTN_RESET	4	Reset button
LED1	13	LED output
LED2	12	LED output
LED3	14 / 21	LED output
BUZZER	5	For long-press tone
OLED SDA	21 / 23	I²C data line
OLED SCL	22	I²C clock line

Libraries You’ll Need
Install these from the Arduino Library Manager:
Adafruit GFX Library
Adafruit SSD1306
Or, if you’re using PlatformIO, drop this in your platformio.ini:

lib_deps =
    adafruit/Adafruit GFX Library
    adafruit/Adafruit SSD1306


If you get the error:
Cannot open source file “Adafruit_GFX.h”

…it just means the libraries aren’t installed correctly.
Fix it by reinstalling from Library Manager or putting them manually in
Documents/Arduino/libraries/.

🖥OLED Messages
Message	Meaning
MODE 1: OFF	LEDs are off
MODE 2: BLINK	LEDs blinking alternately
MODE 3: ON	All LEDs on
MODE 4: FADE	LEDs fading smoothly
Short Press Detected	Button pressed quickly
Long Press Detected	Button held longer than 1.5s

Notes & Tips
Some OLED displays use the address 0x3C, others 0x3D.
If your screen stays blank, run an I²C scanner to check.
Use INPUT_PULLUP for button pins to keep signals stable.
Adjust your fade speed or blink timing if you want smoother visuals.

Wokwi Link:
Task-A -----> https://wokwi.com/projects/445502265516977153
Task-B -----> https://wokwi.com/projects/445781194620551169

Images:
Task-A
All Off: 
![Task-A All Off](https://raw.githubusercontent.com/Essha-creator/ESP-32-Projects/d58697885b087fa2fef943108bafeea1f617053e/Assignment-1--23-NTU-CS-1022/AllOff.PNG)

![All On](https://github.com/Essha-creator/ESP-32-Projects/blob/b4e10ea4ac1e061e8c786e83c974907f8b4fd16b/Assignment-1--23-NTU-CS-1022/AllOn.PNG)

![Blink-1](https://github.com/Essha-creator/ESP-32-Projects/blob/b4e10ea4ac1e061e8c786e83c974907f8b4fd16b/Assignment-1--23-NTU-CS-1022/Blink-1.PNG)

![Blink-2](https://github.com/Essha-creator/ESP-32-Projects/blob/b4e10ea4ac1e061e8c786e83c974907f8b4fd16b/Assignment-1--23-NTU-CS-1022/Blink-2.PNG)

![PWM Fade](https://github.com/Essha-creator/ESP-32-Projects/blob/b4e10ea4ac1e061e8c786e83c974907f8b4fd16b/Assignment-1--23-NTU-CS-1022/PWMFade.PNG)

![Reset](https://github.com/Essha-creator/ESP-32-Projects/blob/b4e10ea4ac1e061e8c786e83c974907f8b4fd16b/Assignment-1--23-NTU-CS-1022/Reset.PNG)

