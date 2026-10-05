#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <STM32FreeRTOS.h>

// LED pins
const int LED1 = D5;   // Red LED
const int LED2 = D6;   // Green LED

// Button pins
const int BUTTON_ON = D7;   // LCD ON button
const int BUTTON_OFF = D8;  // LCD OFF button

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Task 1: LED sequence
void TaskLEDs(void *pvParameters)
{
    while (1)
    {
        // Red LED ON
        digitalWrite(LED1, HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Red LED OFF
        digitalWrite(LED1, LOW);

        // Wait 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Green LED ON
        digitalWrite(LED2, HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Green LED OFF
        digitalWrite(LED2, LOW);

        // Wait 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 2: LCD control
void TaskLCD(void *pvParameters)
{
    while (1)
    {
        // Button 1 → Turn LCD ON
        if (digitalRead(BUTTON_ON) == LOW)
        {
            lcd.backlight();
            lcd.clear();

            lcd.setCursor(0, 0);
            lcd.print("PROJECT DONE!");

            lcd.setCursor(0, 1);
            lcd.print("GREAT JOB!");

            // Keep LCD ON for maximum 10 seconds
            // but check Button 2 every 50 ms
            for (int i = 0; i < 200; i++)
            {
                // Button 2 → Turn LCD OFF immediately
                if (digitalRead(BUTTON_OFF) == LOW)
                {
                    lcd.clear();
                    lcd.noBacklight();
                    break;
                }

                vTaskDelay(pdMS_TO_TICKS(50));
            }

            // Automatic LCD OFF after 10 seconds
            lcd.clear();
            lcd.noBacklight();

            // Wait until Button 1 is released
            while (digitalRead(BUTTON_ON) == LOW)
            {
                vTaskDelay(pdMS_TO_TICKS(50));
            }
        }

        // Button 2 → LCD OFF
        if (digitalRead(BUTTON_OFF) == LOW)
        {
            lcd.clear();
            lcd.noBacklight();

            // Wait until Button 2 is released
            while (digitalRead(BUTTON_OFF) == LOW)
            {
                vTaskDelay(pdMS_TO_TICKS(50));
            }
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    // Both buttons use internal pull-up resistors
    pinMode(BUTTON_ON, INPUT_PULLUP);
    pinMode(BUTTON_OFF, INPUT_PULLUP);

    // I2C pins for STM32 C031C6
    Wire.setSDA(PB7);
    Wire.setSCL(PB6);
    Wire.begin();

    // Initialize LCD
    lcd.init();
    lcd.noBacklight();

    // Create LED task
    xTaskCreate(
        TaskLEDs,
        "LED Sequence",
        128,
        NULL,
        1,
        NULL
    );

    // Create LCD task
    xTaskCreate(
        TaskLCD,
        "LCD Control",
        256,
        NULL,
        1,
        NULL
    );

    // Start FreeRTOS
    vTaskStartScheduler();
}

void loop()
{
}
