#include <Arduino.h>
#include "temperature_manager.hpp"
#include "ui_manager.hpp"
#include "input_manager.hpp"
#include "heating_system.hpp"

using namespace Retrobright;

TemperatureManager tempMgr;
UiManager uiMgr;
InputManager inputMgr;
HeatingSystem heatingSystem; 

void setup() 
{
    // Set up the bit rate for the serial debugging.
    Serial.begin(115200);

    // Set callbacks for button presses
    inputMgr.SetLeftCallback([&]() { uiMgr.PreviousOption(); });
    inputMgr.SetRightCallback([&]() { uiMgr.NextOption(); });
    inputMgr.SetSelectCallback([&]() { uiMgr.SelectOption(); });

    Serial.println("[DEBUG]: Setup done.");
}

void loop() 
{
    tempMgr.Update();
    inputMgr.Update();
    uiMgr.Update(tempMgr);
    heatingSystem.Update(tempMgr);
}