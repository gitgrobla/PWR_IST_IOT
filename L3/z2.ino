#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup()
{
    initButtons();
    initRGB();
}

void redCoroutine()
{
    const unsigned long redChangePeriod = 900UL;
    static int redState = LOW;
    static unsigned long redLastChange = 0UL;

    if (millis() - redLastChange >= redChangePeriod)
    {
        if (redState == HIGH)
        {
            redState = LOW;
        }
        else
        {
            redState = HIGH;
        }

        digitalWrite(LED_RED, redState);
        redLastChange += redChangePeriod;
    }
}

void greenCoroutine()
{
    const unsigned long greenChangePeriod = 1000UL;
    static int greenState = LOW;
    static unsigned long greenLastChange = 0UL;

    if (millis() - greenLastChange >= greenChangePeriod)
    {
        if (greenState == HIGH)
        {
            greenState = LOW;
        }
        else
        {
            greenState = HIGH;
        }

        digitalWrite(LED_GREEN, greenState);
        greenLastChange += greenChangePeriod;
    }
}

void blueCoroutine()
{
    const unsigned long blueChangePeriod = 1100UL;
    static int blueState = LOW;
    static unsigned long blueLastChange = 0UL;

    if (millis() - blueLastChange >= blueChangePeriod)
    {
        if (blueState == HIGH)
        {
            blueState = LOW;
        }
        else
        {
            blueState = HIGH;
        }

        digitalWrite(LED_BLUE, blueState);
        blueLastChange += blueChangePeriod;
    }
}

void readButtonSetLed()
{
    if (digitalRead(RED_BUTTON) == LOW)
        digitalWrite(LED_BUILTIN, HIGH);
    else
        digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
    redCoroutine();
    greenCoroutine();
    blueCoroutine();
    readButtonSetLed();
}