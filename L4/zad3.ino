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
    static String currentText = ""; // Store the current displayed text
    lcd.setCursor(0, 0);

    if (t != currentText)
    {
        // Clear the line and print the new text only if it's different
        lcd.print("                "); // 16 spaces to clear the line
        lcd.setCursor(0, 0);
        lcd.print(t);
        currentText = t;
    }
}

void loop()
{
    int value = analogRead(POTENTIOMETER);
    float voltage = (float)value * 5.0 / 1023.0;

    const unsigned long printPeriod = 100UL;
    static unsigned long lastPrint = 0UL;

    if (millis() - lastPrint >= printPeriod)
    {
        lastPrint += printPeriod;
        printOnScreen(String(value) + " ::: " + String(voltage) + "V");
    }
}