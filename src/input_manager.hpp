#pragma once
#include <functional>

namespace Retrobright
{

    class InputManager
    {
        public:

            explicit InputManager();
            ~InputManager();

            void Update(); // Method to handle input polling

            // Setters for callbacks to handle input interactions
            void SetLeftCallback(const std::function<void()>& callback);
            void SetRightCallback(const std::function<void()>& callback);
            void SetSelectCallback(const std::function<void()>& callback);

        private:
            std::function<void()> leftCallback; // Callback for left button
            std::function<void()> rightCallback; // Callback for right button
            std::function<void()> selectCallback; // Callback for select button

            void HandleButtonInput(); // Function to manage button inputs
    };

}
