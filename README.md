# LCDKeypadShield Library

The `LCDKeypadShield` library is designed to work with Arduino-based LCD Keypad Shields. It simplifies interfacing with the LCD screen (16x2) and keypad (5-button), allowing easy interaction with menus and other applications on your Arduino project.

## Features

- **LCD Control**: Initialize and control a 16x2 LCD screen using a 4-bit interface.
- **Keypad Handling**: Read input from a 5-button keypad (Right, Left, Up, Down, Select).
- **Simple Menu System**: Easily integrate the keypad for navigation and control of menus on the LCD screen.

## Installation

1. Download or clone the `LCDKeypadShield` library.
2. Move the `LCDKeypadShield` folder to your Arduino libraries directory.
   - On Windows: `Documents/Arduino/libraries/`
   - On macOS/Linux: `~/Arduino/libraries/`
3. Restart the Arduino IDE to see the library in your **Sketch > Include Library** menu.

## Usage

### 1. Initialize the Library

To use the library, you need to instantiate an `LCDKeypadShield` object and initialize it with the correct pin numbers for your setup. 

```cpp
#include <LCDKeypadShield.h>

LCDKeypadShield lcd(8, 9, 4, 5, 6, 7, A1);  // Pins for LCD and contrast pin

void setup() {
  lcd.begin();
  lcd.printMessage("Hello, World!");
}

void loop() {
  int button = lcd.readButton();
  if (button >= 0) {
    lcd.printMessage("Button pressed: " + String(button));
  }
}
