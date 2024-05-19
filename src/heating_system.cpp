#include <Arduino.h>
#include "heating_system.hpp"

namespace Retrobright
{
    #define HEATER_RELAY_PIN 32

    HeatingSystem::HeatingSystem()
        : heating(false), targetTemperature(0.0f), targetTime(0), startTime(0)
    {
        pinMode(HEATER_RELAY_PIN, OUTPUT);
        digitalWrite(HEATER_RELAY_PIN, LOW);               // Ensure heating is off initially
    }

    HeatingSystem::~HeatingSystem()
    {
    }

    void HeatingSystem::StartSystem()
    {
        startTime = millis();
        Update(TemperatureManager());                      // Initialize with the current temperature
    }

    void HeatingSystem::StopSystem()
    {
        DisableHeating();
    }

    void HeatingSystem::Update(const TemperatureManager& tempMgr)
    {
        if ((millis() - startTime) / 60000 >= targetTime)
        {
            StopSystem();                  
            return;
        }

        float currentTemp = tempMgr.GetTempC();
        if (currentTemp < targetTemperature)
        {
            EnableHeating();
        }
        else
        {
            DisableHeating();
        }
    }

    void HeatingSystem::SetTargetTemperature(float tempC)
    {
        targetTemperature = tempC;
    }

    void HeatingSystem::SetTargetTime(int minutes)
    {
        targetTime = minutes;
    }

    void HeatingSystem::EnableHeating()
    {
        if (!heating)
        {
            digitalWrite(HEATER_RELAY_PIN, HIGH); 
            heating = true;
        }
    }

    void HeatingSystem::DisableHeating()
    {
        if (heating)
        {
            digitalWrite(HEATER_RELAY_PIN, LOW); 
            heating = false;
        }
    }
}
