#include <temperature_manager.hpp>
#include <sstream>
#include <iomanip>
#include <OneWire.h>
#include <DallasTemperature.h>

namespace Retrobright
{

  #define TEMP_SENSOR_PIN 27

  OneWire oneWire(TEMP_SENSOR_PIN);
  DallasTemperature temp_sensor(&oneWire);

  TemperatureManager::TemperatureManager()
  {
    temp_sensor.begin();
  }

  TemperatureManager::~TemperatureManager()
  {
  }

  void TemperatureManager::Update()
  {
    temp_sensor.requestTemperatures();
    tempC = temp_sensor.getTempCByIndex(0);
    tempString = std::to_string(tempC);
  }

  float TemperatureManager::GetTempC() const
  {
    return tempC;
  }

  std::string TemperatureManager::GetTempString() const
  {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << tempC;
    return stream.str();
  }

}
