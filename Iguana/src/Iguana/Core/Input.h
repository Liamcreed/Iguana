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
        static bool m_Keys[MAX_KEYS];
        static bool m_MouseButtons[MAX_BUTTONS];

        static double m_MouseX, m_MouseY;
        static float m_ScrollX, m_ScrollY;
        static int m_Action;

    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsKeyReleased(KeyCode key);
        static bool IsKeyPress(KeyCode key);

        static bool IsMouseButtonPressed(int button);
        static bool IsMouseButtonReleased(int button);
        static bool IsMouseButtonPress(int button);

        static int GetAxis(std::string axis);
        static glm::vec2 GetMousePos() { return glm::vec2(m_MouseX, m_MouseY); }
        static glm::vec2 GetScrollWheel();

    private:
        friend class Window;
    };
} // namespace Iguana
