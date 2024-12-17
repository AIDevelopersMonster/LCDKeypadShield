#include <LCDKeypadShield.h>

// Инициализация объекта LCDKeypadShield
LCDKeypadShield lcdKeypad(8, 9, 4, 5, 6, 7, 10); // Пины для LCD и пин для контраста

void setup() {
  lcdKeypad.begin();  // Инициализация экрана и кнопок
  lcdKeypad.printMessage("Welcome!"); // Приветственное сообщение
}

void loop() {
  // Пример обработки кнопок
  if (lcdKeypad.buttonPressed(1)) {
    lcdKeypad.printMessage("UP Pressed!");
    delay(500);
  }

  if (lcdKeypad.buttonPressed(2)) {
    lcdKeypad.printMessage("DOWN Pressed!");
    delay(500);
  }

  if (lcdKeypad.buttonPressed(4)) {
    lcdKeypad.printMessage("SELECT Pressed!");
    delay(500);
  }

  if (lcdKeypad.buttonPressed(0)) {
    lcdKeypad.printMessage("RIGHT Pressed!");
    delay(500);
  }

  if (lcdKeypad.buttonPressed(3)) {
    lcdKeypad.printMessage("LEFT Pressed!");
    delay(500);
  }
}
