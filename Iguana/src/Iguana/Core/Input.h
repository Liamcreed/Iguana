#pragma once
#include "KeyCodes.h"
#include <glm/glm.hpp>

#define MAX_KEYS 1024
#define MAX_BUTTONS 1024

namespace Iguana
{
    class Input
    {
    private:
        static bool mKeys[MAX_KEYS];
        static bool mMouseButtons[MAX_BUTTONS];

        static double mMouseX, mMouseY;
        static float mScrollX, mScrollY;
        static int mAction;

    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsKeyReleased(KeyCode key);
        static bool IsKeyPress(KeyCode key);

        static bool IsMouseButtonPressed(int button);
        static bool IsMouseButtonReleased(int button);
        static bool IsMouseButtonPress(int button);

        static int GetAxis(std::string axis);
        static glm::vec2 GetMousePos() { return glm::vec2(mMouseX, mMouseY); }
        static glm::vec2 GetScrollWheel();

    private:
        friend class Window;
    };
} // namespace Iguana
