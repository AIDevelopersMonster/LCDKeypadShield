#ifndef LCDKEYPADSHIELD_H
#define LCDKEYPADSHIELD_H

#include <Arduino.h>  // Добавляем для использования uint8_t и других типов

class LCDKeypadShield {
  public:
    // Конструктор для инициализации пинов LCD
    LCDKeypadShield(int rs, int enable, int d4, int d5, int d6, int d7, int contrastPin);
    
    // Инициализация LCD и кнопок
    void begin();
    
    // Отображение текста на экране
    void printMessage(const char* message);
    void clearScreen();
    
    // Чтение кнопок с пина A0
    int readButton();
    
    // Функции для навигации по кнопкам
    bool buttonPressed(int buttonCode);
    bool buttonReleased(int buttonCode);

  private:
    // Пины для подключения LCD
    int _rs, _enable, _d4, _d5, _d6, _d7, _contrastPin;
    
    // Управление LCD (основные функции управления экраном)
    void sendCommand(uint8_t command);
    void sendData(uint8_t data);
    void setCursor(uint8_t col, uint8_t row);
    void pulseEnable();
    
    // Функции для настройки контраста
    void setContrast(int contrastValue);
    void initializeLCD();
    
    // Массив для отображения символов на экране
    uint8_t _lcdMemory[2][16];  // Два ряда по 16 символов (для экрана 16x2)
    
    int _lastButtonState; // Состояние кнопки для предотвращения дребезга
    int _currentButtonState; // Текущее состояние кнопки
};

#endif
