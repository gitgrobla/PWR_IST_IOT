#include <LiquidCrystal_I2C.h>
#define POTENTIOMETER A0
#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4
#define DEBOUNCE_PERIOD 10UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void initLCD()
{
    lcd.init();
    lcd.backlight();
}

void setup()
{
    initButtons();
    initLCD();
    pinMode(POTENTIOMETER, INPUT);
}

void printOnScreen(String t)
{
    lcd.setCursor(15, 0);
    lcd.write(byte(0));
    lcd.setCursor(0, 0);
    lcd.print(t);
}

void loop()
{
    int value = analogRead(POTENTIOMETER);
    int realValue = min(max(0, value - 10), 1003);

    const unsigned long printPeriod = 100UL;
    static unsigned long lastPrint = 0UL;

    if (millis() - lastPrint >= printPeriod)
    {
        lastPrint += printPeriod;
        printOnScreen(String(value) + " : " + String(realValue));
    }
}