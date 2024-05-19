#pragma once
#include "temperature_manager.hpp"

namespace Retrobright
{
    class HeatingSystem
    {
    public:
        HeatingSystem();
        ~HeatingSystem();

        void StartSystem();
        void StopSystem();
        void Update(const TemperatureManager& tempMgr);

        void SetTargetTemperature(float tempC);
        void SetTargetTime(int minutes);

    private:
        int relayPin;                                      // GPIO pin connected to the relay
        bool heating;                                      // Current state of the heating element
        float targetTemperature;                           // Target temperature
        int targetTime;                                    // Target time in minutes
        unsigned long startTime;                           // Time when the system was started

        void EnableHeating();
        void DisableHeating();
    };
}
