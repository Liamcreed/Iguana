#include "pch.h"
#include "Input.h"

namespace Iguana
{
    bool Input::mKeys[MAX_KEYS];
    bool Input::mMouseButtons[MAX_BUTTONS];

    double Input::mMouseX, Input::mMouseY;
    float Input::mScrollX, Input::mScrollY;
    int Input::mAction;

    bool Input::IsKeyPressed(KeyCode key)
    {
        if (mKeys[key] == true)
            return true;
        return false;
    }
    
    /* Only returns true when key is pressed once!*/
    bool Input::IsKeyPress(KeyCode key)
    {
        static bool pressed = false;

        if (mKeys[key] == true && pressed == false)
        {
            pressed = true;
            return true;
        }
        else if (mKeys[key] == false)
        {
            pressed = false;
        }
        return false;
    }
    bool Input::IsKeyReleased(KeyCode key)
    {
        if (mKeys[key] == false)
            return true;
        return false;
    }
    bool Input::IsMouseButtonPressed(int button)
    {
        if (mMouseButtons[button] == true)
            return true;
        return false;
    }
    bool Input::IsMouseButtonReleased(int button)
    {
        if (mMouseButtons[button] == false)
            return true;
        return false;
    }
    /* Only returns true when mouse is pressed once!*/
    bool Input::IsMouseButtonPress(int button)
    {
        static bool pressed = false;

        if (mMouseButtons[button] == true && pressed == false)
        {
            pressed = true;
            return true;
        }
        else if (mMouseButtons[button] == false)
        {
            pressed = false;
        }
        return false;
    }
    int Input::GetAxis(std::string axis)
    {
        if (axis == "Horizontal")
        {
            if (mKeys[KeyCode::A] | mKeys[KeyCode::Left])
                return -1;
            if (mKeys[KeyCode::D] | mKeys[KeyCode::Left])
                return 1;
        }
        else if (axis == "Vertical")
        {
            if (mKeys[KeyCode::W] | mKeys[KeyCode::Up])
                return 1;
            if (mKeys[KeyCode::S] | mKeys[KeyCode::Down])
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

        if (mScrollX > threshold)
            x = 1;
        else if (mScrollX < -threshold)
            x = -1;
        else
            x = 0;

        if (mScrollY > threshold)
            y = 1;
        else if (mScrollY < -threshold)
            y = -1;
        else
            y = 0;

        return glm::vec2(x, y);
    }
    
}