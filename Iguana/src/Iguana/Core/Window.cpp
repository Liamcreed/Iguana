#include "pch.h"
#include "Window.h"
#include "Input.h"
#include "Application.h"
namespace Iguana
{
    Window::Window(std::string &title, uint32_t width, uint32_t height)
        : m_Title(title), m_Width(width), m_Height(height)
    {
        if (!glfwInit())
        {
            LOG(ERROR) << "Failed to initialize GLFW!" << std::endl;
            glfwTerminate();
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        m_GLFWWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (m_GLFWWindow == nullptr)
        {
            LOG(ERROR) << "Failed to create window!" << std::endl;
            glfwTerminate();
        }
        //Callbacks
        /* glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            m_Width = width;
            m_Height = height;
        }); */

        glfwSetKeyCallback(m_GLFWWindow, key_callback);
        glfwSetCursorPosCallback(m_GLFWWindow, cursor_position_callback);
        glfwSetMouseButtonCallback(m_GLFWWindow, mouse_button_callback);
        glfwSetScrollCallback(m_GLFWWindow, scroll_callback);

        glfwSetWindowMaximizeCallback(m_GLFWWindow, window_maximize_callback);
        glfwSetWindowIconifyCallback(m_GLFWWindow, window_iconify_callback);
    }
    void Window::Update()
    {
        glfwPollEvents();
        if (this->IsClosed())
                Application::Get()->Close();
    }
    Window::~Window()
    {
        glfwDestroyWindow(m_GLFWWindow);
        glfwTerminate();
    }
    bool Maximized = false;
    bool Minimized = false;

    bool Window::IsMinimized()
    {
        return Minimized;
    }

    bool Window::IsMaximized()
    {
        return Maximized;
    }
    void Window::Vsync(bool vsync)
    {
        if (vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Input::m_Action = action;
        Input::m_Keys[key] = Input::m_Action != GLFW_RELEASE;
    }
    void Window::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
        Input::m_MouseX = xpos;
        Input::m_MouseY = ypos;
    }
    void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        Input::m_MouseButtons[button] = action != GLFW_RELEASE;
    }
    void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        Input::m_ScrollX = xoffset;
        Input::m_ScrollY = yoffset;
    }

    void Window::window_iconify_callback(GLFWwindow *window, int iconified)
    {
        if (iconified)
            Minimized = true;
        else
            Minimized = false;
    }

    void Window::window_maximize_callback(GLFWwindow *window, int maximized)
    {
        if (maximized)
            Maximized = true;
        else
            Maximized = false;
    }
} // namespace Iguana
