#include <input_manager.hpp>
#include <Arduino.h>

namespace Retrobright
{
    #define LEFT_BUTTON_PIN 17
    #define RIGHT_BUTTON_PIN 0
    #define SELECT_BUTTON_PIN 35
    #define DEBOUNCE_DELAY 10

    InputManager::InputManager()
    {
        // Initialize button pins as needed
        pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP); // Example for left button
        pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP); // Example for right button
        pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP); // Example for select button
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::Update()
    {
        // Poll for inputs and handle them
        HandleButtonInput();
    }

    void InputManager::SetLeftCallback(const std::function<void()>& callback)
    {
        leftCallback = callback;
    }

    void InputManager::SetRightCallback(const std::function<void()>& callback)
    {
        rightCallback = callback;
    }

    void InputManager::SetSelectCallback(const std::function<void()>& callback)
    {
        selectCallback = callback;
    }

    void InputManager::HandleButtonInput()
    {
        static unsigned long lastPressTime = 0; 
        const unsigned long debounceDelay = DEBOUNCE_DELAY; //

        unsigned long currentTime = millis(); 

        if (currentTime - lastPressTime < debounceDelay)
        {
            return; // Ignore input if within debounce delay
        }
        if (digitalRead(LEFT_BUTTON_PIN) == LOW)
        {
            Serial.println("Left.");

            if (leftCallback)
            {
                leftCallback();
            }
        }
        else if (digitalRead(RIGHT_BUTTON_PIN) == LOW)
        {
            Serial.println("Right.");

            if (rightCallback)
            {
                rightCallback();
            }
        }
        else if (digitalRead(SELECT_BUTTON_PIN) == LOW)
        {
            Serial.println("Select.");

            if (selectCallback)
            {
                selectCallback();
            }
        }

        lastPressTime = currentTime;
    }
}
