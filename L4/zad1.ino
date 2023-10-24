#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define DEBOUNCE_PERIOD 10UL

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void setup()
{
    initButtons();

    Serial.begin(9600);
    while (!Serial)
    {
    }
}

bool GREEN_Pressed()
{
    static int GREEN_debounced_button_state = HIGH;
    static int GREEN_previous_reading = HIGH;
    static unsigned long GREEN_last_change_time = 0UL;
    bool GREEN_isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (GREEN_previous_reading != current_reading)
    {
        GREEN_last_change_time = millis();
    }

    if (millis() - GREEN_last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != GREEN_debounced_button_state)
        {
            if (GREEN_debounced_button_state == HIGH && current_reading == LOW)
            {
                GREEN_isPressed = true;
            }
            GREEN_debounced_button_state = current_reading;
        }
    }

    GREEN_previous_reading = current_reading;

    return GREEN_isPressed;
}

bool RED_Pressed()
{
    static int RED_debounced_button_state = HIGH;
    static int RED_previous_reading = HIGH;
    static unsigned long RED_last_change_time = 0UL;
    bool RED_isPressed = false;

    int current_reading = digitalRead(RED_BUTTON);

    if (RED_previous_reading != current_reading)
    {
        RED_last_change_time = millis();
    }

    if (millis() - RED_last_change_time > DEBOUNCE_PERIOD)
    {
        if (current_reading != RED_debounced_button_state)
        {
            if (RED_debounced_button_state == HIGH && current_reading == LOW)
            {
                RED_isPressed = true;
            }
            RED_debounced_button_state = current_reading;
        }
    }

    RED_previous_reading = current_reading;

    return RED_isPressed;
}

void plotSerial()
{
    int valueGreen = digitalRead(RED_BUTTON);
    int valueRed = digitalRead(GREEN_BUTTON);
    Serial.print("red:");
    Serial.print(valueRed);
    Serial.print(", ");
    Serial.print("green:");
    Serial.print(valueGreen);
    Serial.print(", ");
    Serial.println();
}

void loop()
{
    plotSerial();
}