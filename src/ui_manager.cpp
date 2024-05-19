#include <ui_manager.hpp>
#include <sstream>
#include <iomanip>
#include <string>
#include <SPI.h>
#include "../resources/rat.h"

namespace Retrobright
{
  #define STARTUP_SCREEN_DELAY_MS 2000


  UiManager::UiManager() : tft(), buffer(&tft), state(UiState::Startup), menuOption(MenuOption::Go), lastRenderedOption(MenuOption::Go), initialRender(true)
  {
    tft.init();
    tft.setRotation(0);
    tft.fillScreen(TFT_BLACK);

    menuOptions = { "GO", "Adjust Temperature", "Adjust Time" };
  }

  UiManager::~UiManager()
  {
  }

  void UiManager::Update(TemperatureManager tempMgr)
  {
    this->tempC = tempMgr.GetTempC();
    this->tempString = tempMgr.GetTempString();

    buffer.createSprite(TFT_HEIGHT, TFT_WIDTH);
    buffer.setRotation(1);

    DisplayHeader();
    //buffer.fillRect(0,10, TFT_WIDTH, TFT_HEIGHT-10, TFT_BLACK);

    switch (state)
    {
      case UiState::Startup:
        ShowStartupScreen();
        break;
      case UiState::Menu:
        DisplayMainMenu();
        break;
      case UiState::TempAdjust:
        DisplayTemperatureAdjust();
        break;
      case UiState::TimeAdjust:
        DisplayTimeAdjust();
        break;
    }

    buffer.pushSprite(0,0); 
    buffer.deleteSprite();
  }

  void UiManager::ShowStartupScreen()
  {
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0, 20, 135, 200, RAT);
    tft.setSwapBytes(false);
    
    delay(STARTUP_SCREEN_DELAY_MS);
    
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    buffer.setRotation(1);
    buffer.setTextColor(TFT_YELLOW, TFT_BLACK, true);

    state = UiState::Menu;
  }

  void UiManager::DisplayHeader()
  {
    buffer.fillRoundRect(0,0, TFT_HEIGHT, 25, 5, TFT_BLUE);
    buffer.setTextColor(TFT_WHITE, TFT_BLUE, true);
    buffer.setTextDatum(MR_DATUM);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << tempC << "°C";
    std::string tempString = stream.str();

    buffer.drawString(tempString.c_str(), buffer.width(), 13, 2);
  }

  void UiManager::DisplayMainMenu()
  {
    DisplayMenuOption();
  }

  void UiManager::DisplayMenuOption()
  {
    buffer.setTextDatum(MC_DATUM);
    buffer.setTextColor(TFT_YELLOW, TFT_BLACK, true);


    int optionIndex = static_cast<int>(menuOption);
    std::string currentOption = menuOptions[optionIndex];
         
    buffer.drawString(menuOptions[static_cast<int>(menuOption)].c_str(), buffer.width()/2, 80, 4);

    lastRenderedOption = menuOption;
    initialRender = false;
  }

  void UiManager::DisplayTemperatureAdjust()
  {
    buffer.setTextColor(TFT_WHITE, TFT_BLACK, true);
    buffer.setTextDatum(MC_DATUM);

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << targetTemperature << "°C";
    std::string tempString = stream.str();
    buffer.drawString(tempString.c_str(), buffer.width()/2, 80, 7);
  }
 void UiManager::DisplayTimeAdjust()
  {
    buffer.setTextColor(TFT_WHITE, TFT_BLACK, true);
    buffer.setTextDatum(MC_DATUM);

    int hours = runTimeMinutes / 60;
    int minutes = runTimeMinutes % 60;

    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << hours
           << ":" << std::setfill('0') << std::setw(2) << minutes;


    std::string timeString = stream.str();
    buffer.drawString(timeString.c_str(), buffer.width()/2, 80, 7);
  }

  void UiManager::SetTemperature(float tempC)
  {
    targetTemperature = tempC;
  }
 void UiManager::SetTime(int minutes)
  {
    runTimeMinutes = minutes;
  }
 
  void UiManager::NextOption()
  {
      if (state == UiState::Menu)
      {
          menuOption = static_cast<MenuOption>((static_cast<int>(menuOption) + 1) % 3);
          DisplayMenuOption();
      }
      else if (state == UiState::TempAdjust)
      {
          targetTemperature += 0.5f;
          DisplayTemperatureAdjust();
      }
      else if (state == UiState::TimeAdjust)
      {
          runTimeMinutes += 30;
          DisplayTimeAdjust();
      }
  }

  void UiManager::PreviousOption()
  {
    if (state == UiState::Menu)
    {
      menuOption = static_cast<MenuOption>((static_cast<int>(menuOption) + 2) % 3); // Move backward in a cyclic manner
      DisplayMenuOption();
    }
    else if (state == UiState::TempAdjust)
    {
      targetTemperature -= 0.5f;
      DisplayTemperatureAdjust();
    }
    else if (state == UiState::TimeAdjust)
    {
      runTimeMinutes -= 30;
      DisplayTimeAdjust();
    }
  }

  void UiManager::SelectOption()
  {
    if (state == UiState::Menu)
    {
      switch (menuOption)
      {
        case MenuOption::Go:
          // Start the process or other logic
          break;
        case MenuOption::TempAdjust:
          state = UiState::TempAdjust;
          DisplayTemperatureAdjust();
          break;
        case MenuOption::TimeAdjust:
          state = UiState::TimeAdjust;
          DisplayTimeAdjust();
          break;
      }
    }
    else if (state == UiState::TempAdjust || state == UiState::TimeAdjust)
    {
      state = UiState::Menu; // Return to the menu state
      DisplayMainMenu();
    }
  }

} 
