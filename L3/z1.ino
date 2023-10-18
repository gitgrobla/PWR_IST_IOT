#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

int led[] = {LED_RED, LED_GREEN, LED_BLUE};

void initRGB()
{
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

#define DEBOUNCE_PERIOD 10UL

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

bool isGreenReleased()
{
    static int g_debounced_button_state = HIGH;
    static int g_previous_reading = HIGH;
    static unsigned long g_last_change_time = 0UL;
    bool isReleased = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (g_previous_reading != current_reading)
    {
        g_last_change_time = millis();
    }

    if (millis() - g_last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != g_debounced_button_state)
        {
            if (g_debounced_button_state == LOW && current_reading == HIGH)
            {
                isReleased = true;
            }
            g_debounced_button_state = current_reading;
        }
    }

    g_previous_reading = current_reading;

    return isReleased;
}

bool isRedReleased()
{
    static int r_debounced_button_state = HIGH;
    static int r_previous_reading = HIGH;
    static unsigned long r_last_change_time = 0UL;
    bool isReleased = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (r_previous_reading != current_reading)
    {
        r_last_change_time = millis();
    }

    if (millis() - r_last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != r_debounced_button_state)
        {
            if (r_debounced_button_state == LOW && current_reading == HIGH)
            {
                isReleased = true;
            }
            r_debounced_button_state = current_reading;
        }
    }

    r_previous_reading = current_reading;

    return isReleased;
}

void setup()
{
    initRGB();
    initButtons();
}

int led_index = 0;
void loop()
{
    if (isRedReleased())
    {
        modifyLEDs();
    } else if(isGreenReleased())
    {
        modifyLEDs();
    }
}

void modifyLEDs()
{
    digitalWrite(led[led_index], LOW);
    led_index = ++led_index % 3;
    digitalWrite(led[led_index], HIGH);
}