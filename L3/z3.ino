#include <LiquidCrystal_I2C.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4
#define DEBOUNCE_PERIOD 10UL

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool running = false;
unsigned long startTime = 0UL;
unsigned long previousTime = 0UL;

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

bool isGreenPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
}

bool isRedPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static unsigned long last_change_time = 0UL;
    bool isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (previous_reading != current_reading)
    {
        last_change_time = millis();
    }

    if (millis() - last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }

    previous_reading = current_reading;

    return isPressed;
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

void printOnScreen(String t)
{
    lcd.setCursor(15, 0);
    lcd.write(byte(0));
    lcd.setCursor(0, 0);
    lcd.print(t);
}


void startTimer() {
    running = true;
    startTime = millis();
}

void stopTimer() {
    running = false;
    previousTime += millis() - startTime;
}

void clearTimer() {
    running = false;
    lcd.clear();
    printOnScreen("0:0.0");
    previousTime = 0UL;
}

void loop()
{
    if (isGreenPressed())
    {
        if(running){
            stopTimer();
        } else {
            startTimer();
        }
    }

    if (isRedPressed())
    {
        clearTimer();
    }

    if (running)
    {
        unsigned long elapsedTime = (millis() - startTime) + previousTime;
        unsigned long seconds = elapsedTime / 1000;
        unsigned long minutes = seconds / 60;
        seconds = seconds % 60;

        String time = String(minutes) + ":" + String(seconds) + "." + String(elapsedTime % 1000);
        printOnScreen(time);
    }
}