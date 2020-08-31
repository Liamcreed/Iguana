#include "pch.h"
#include "Input.h"

namespace Iguana
{
    bool Input::m_Keys[MAX_KEYS];
    bool Input::m_MouseButtons[MAX_BUTTONS];

    double Input::m_MouseX, Input::m_MouseY;
    float Input::m_ScrollX, Input::m_ScrollY;
    int Input::m_Action;

    bool Input::IsKeyPressed(KeyCode key)
    {
        if (m_Keys[key] == true)
            return true;
        return false;
    }
    /* Only returns true when key is pressed once!*/
    bool Input::IsKeyPress(KeyCode key)
    {
        static bool pressed = false;

        if (m_Keys[key] == true && pressed == false)
        {
            pressed = true;
            return true;
        }
        else if (m_Keys[key] == false)
        {
            pressed = false;
        }
        return false;
    }
    bool Input::IsKeyReleased(KeyCode key)
    {
        if (m_Keys[key] == false)
            return true;
        return false;
    }
    bool Input::IsMouseButtonPressed(int button)
    {
        if (m_MouseButtons[button] == true)
            return true;
        return false;
    }
    bool Input::IsMouseButtonReleased(int button)
    {
        if (m_MouseButtons[button] == false)
            return true;
        return false;
    }
    /* Only returns true when mouse is pressed once!*/
    bool Input::IsMouseButtonPress(int button)
    {
        static bool pressed = false;

        if (m_MouseButtons[button] == true && pressed == false)
        {
            pressed = true;
            return true;
        }
        else if (m_MouseButtons[button] == false)
        {
            pressed = false;
        }
        return false;
    }
    int Input::GetAxis(std::string axis)
    {
        if (axis == "Horizontal")
        {
            if (m_Keys[KeyCode::A] | m_Keys[KeyCode::Left])
                return -1;
            if (m_Keys[KeyCode::D] | m_Keys[KeyCode::Left])
                return 1;
        }
        else if (axis == "Vertical")
        {
            if (m_Keys[KeyCode::W] | m_Keys[KeyCode::Up])
                return 1;
            if (m_Keys[KeyCode::S] | m_Keys[KeyCode::Down])
                return -1;
        }
        else
        {
            LOG(ERROR) << axis << " is not an availible axis!\n";
        }

        return 0;
    }
    glm::vec2 Input::GetScrollWheel()
    {
        int x, y;
        float threshold = 0.1;

        if (m_ScrollX > threshold)
            x = 1;
        else if (m_ScrollX < -threshold)
            x = -1;
        else
            x = 0;

        if (m_ScrollY > threshold)
            y = 1;
        else if (m_ScrollY < -threshold)
            y = -1;
        else
            y = 0;

        return glm::vec2(x, y);
    }
    
}