#pragma once
#include <string>

namespace Retrobright
{

    class TemperatureManager
    {      
        public: 
        
            explicit TemperatureManager();
            ~TemperatureManager();
            void Update();

            // Getter methods for temperature data
            float GetTempC() const;
            std::string GetTempString() const;
        
        private:
            std::string tempString; // String holding the temperature in printable format
            float tempC;            // Temperature in Centigrades

    };

}