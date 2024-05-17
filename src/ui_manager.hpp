#pragma once
#include <vector>
#include <TFT_eSPI.h>
#include <temperature_manager.hpp>

namespace Retrobright
{

    class UiManager
    {
        public:

            explicit UiManager();
            ~UiManager();
            void Update(TemperatureManager tempMgr);

            // Functions to update displayed information
            void SetTemperature(float tempC);
            void SetTime(int minutes);

            void NextOption();                             // Move right in the menu
            void PreviousOption();                         // Move left in the menu
            void SelectOption();                           // Select the current option  

        private:
            TFT_eSPI tft;
            TFT_eSprite buffer;

            std::string tempString;                        // String holding the temperature in printable format
            std::vector<std::string> menuOptions;          // string vector with the text of all menu options
            float tempC;                                   // Temperature in Centigrades

            enum class UiState 
            { 
                Startup, 
                Menu, 
                TempAdjust, 
                TimeAdjust 
            } state;                                       // UI states
            
            enum class MenuOption 
            { 
                Go, 
                TempAdjust, 
                TimeAdjust 
            } menuOption;                                  // Menu options

            float targetTemperature = 40.0f;               // Default temperature
            int runTimeMinutes = 240;                      // Default runtime

            bool initialRender = true;                     // Flag to track initial render
            MenuOption lastRenderedOption;                 // To store the last rendered menu option

            void DisplayMenuOption();
            void DisplayHeader();
            void ShowStartupScreen();
            void DisplayMainMenu();
            void DisplayTemperatureAdjust();
            void DisplayTimeAdjust();
    };
}