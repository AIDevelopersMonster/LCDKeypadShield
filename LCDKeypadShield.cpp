#include "LCDKeypadShield.h"
#include <Arduino.h>

// Конструктор LCDKeypadShield
LCDKeypadShield::LCDKeypadShield(int rs, int enable, int d4, int d5, int d6, int d7, int contrastPin)
  : _rs(rs), _enable(enable), _d4(d4), _d5(d5), _d6(d6), _d7(d7), _contrastPin(contrastPin), 
    _lastButtonState(-1), _currentButtonState(-1) {}

void LCDKeypadShield::begin() {
  // Настройка пинов для LCD
  pinMode(_rs, OUTPUT);
  pinMode(_enable, OUTPUT);
  pinMode(_d4, OUTPUT);
  pinMode(_d5, OUTPUT);
  pinMode(_d6, OUTPUT);
  pinMode(_d7, OUTPUT);
  pinMode(_contrastPin, OUTPUT);

  // Инициализация LCD
  initializeLCD();
}

void LCDKeypadShield::initializeLCD() {
  // Инициализация в 4-битном режиме (на 16x2 экране)
  delay(15);
  sendCommand(0x33); // Инициализация
  sendCommand(0x32); // Инициализация
  sendCommand(0x28); // 4-битный режим, 2 строки
  sendCommand(0x0C); // Включаем дисплей, без курсора
  sendCommand(0x06); // Автоматическое перемещение курсора
  sendCommand(0x01); // Очистить экран
  setContrast(100);   // Устанавливаем контраст
}

void LCDKeypadShield::sendCommand(uint8_t command) {
  digitalWrite(_rs, LOW);  // Устанавливаем режим команды
  digitalWrite(_d4, (command >> 4) & 0x01);
  digitalWrite(_d5, (command >> 5) & 0x01);
  digitalWrite(_d6, (command >> 6) & 0x01);
  digitalWrite(_d7, (command >> 7) & 0x01);
  pulseEnable();

  digitalWrite(_d4, command & 0x01);
  digitalWrite(_d5, (command >> 1) & 0x01);
  digitalWrite(_d6, (command >> 2) & 0x01);
  digitalWrite(_d7, (command >> 3) & 0x01);
  pulseEnable();
}

void LCDKeypadShield::sendData(uint8_t data) {
  digitalWrite(_rs, HIGH); // Устанавливаем режим данных
  digitalWrite(_d4, (data >> 4) & 0x01);
  digitalWrite(_d5, (data >> 5) & 0x01);
  digitalWrite(_d6, (data >> 6) & 0x01);
  digitalWrite(_d7, (data >> 7) & 0x01);
  pulseEnable();

  digitalWrite(_d4, data & 0x01);
  digitalWrite(_d5, (data >> 1) & 0x01);
  digitalWrite(_d6, (data >> 2) & 0x01);
  digitalWrite(_d7, (data >> 3) & 0x01);
  pulseEnable();
}

void LCDKeypadShield::setCursor(uint8_t col, uint8_t row) {
  uint8_t address = (row == 0) ? 0x00 + col : 0x40 + col;
  sendCommand(0x80 | address);
}

void LCDKeypadShield::pulseEnable() {
  digitalWrite(_enable, LOW);
  delayMicroseconds(1);
  digitalWrite(_enable, HIGH);
  delayMicroseconds(1);
  digitalWrite(_enable, LOW);
  delayMicroseconds(100);
}

void LCDKeypadShield::setContrast(int contrastValue) {
  analogWrite(_contrastPin, contrastValue); // Устанавливаем контраст
}

void LCDKeypadShield::printMessage(const char* message) {
  clearScreen();
  for (uint8_t i = 0; i < strlen(message); i++) {
    sendData(message[i]);
  }
}

void LCDKeypadShield::clearScreen() {
  sendCommand(0x01);  // Очистить экран
  delay(2);
}

int LCDKeypadShield::readButton() {
  int adcKey = analogRead(A0); // Чтение значения с пина A0
  if (adcKey > 1000) return -1; // Нет нажатой кнопки
  if (adcKey < 50) return 0; // RIGHT
  if (adcKey < 150) return 1; // UP
  if (adcKey < 350) return 2; // DOWN
  if (adcKey < 600) return 3; // LEFT
  if (adcKey < 850) return 4; // SELECT
  return -1;
}

bool LCDKeypadShield::buttonPressed(int buttonCode) {
  int currentButton = readButton();
  if (currentButton == buttonCode && currentButton != _lastButtonState) {
    _lastButtonState = currentButton;
    return true;
  }
  return false;
}

bool LCDKeypadShield::buttonReleased(int buttonCode) {
  int currentButton = readButton();
  if (currentButton != buttonCode && currentButton == _lastButtonState) {
    _lastButtonState = -1;
    return true;
  }
  return false;
}
