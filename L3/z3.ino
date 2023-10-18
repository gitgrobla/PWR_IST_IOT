#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

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
}

void loop()
{
    lcd.setCursor(15, 0);
    lcd.write(byte(0));
    lcd.setCursor(0,0);
    lcd.print(millis());
    delay(1000);
}