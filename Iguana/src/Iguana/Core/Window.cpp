#include "pch.h"
#include "Window.h"
#include "Input.h"
#include "Application.h"
namespace Iguana
{
    Window::Window(std::string &title, uint32_t width, uint32_t height)
        : mTitle(title), mWidth(width), mHeight(height)
    {
        if (!glfwInit())
        {
            LOG(ERROR) << "Failed to initialize GLFW!" << std::endl;
            glfwTerminate();
        }

        
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        mGLFWWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
        if (mGLFWWindow == nullptr)
        {
            LOG(ERROR) << "Failed to create window!" << std::endl;
            glfwTerminate();
        }
        //Callbacks
        /* glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            m_Width = width;
            m_Height = height;
        }); */

        glfwSetKeyCallback(mGLFWWindow, key_callback);
        glfwSetCursorPosCallback(mGLFWWindow, cursor_position_callback);
        glfwSetMouseButtonCallback(mGLFWWindow, mouse_button_callback);
        glfwSetScrollCallback(mGLFWWindow, scroll_callback);

        glfwSetWindowMaximizeCallback(mGLFWWindow, window_maximize_callback);
        glfwSetWindowIconifyCallback(mGLFWWindow, window_iconify_callback);
    }
    void Window::Update()
    {
        glfwPollEvents();
        if (this->IsClosed())
                Application::Get()->Close();
    }
    Window::~Window()
    {
        glfwDestroyWindow(mGLFWWindow);
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
        Input::mAction = action;
        Input::mKeys[key] = Input::mAction != GLFW_RELEASE;
    }
    void Window::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
        Input::mMouseX = xpos;
        Input::mMouseY = ypos;
    }
    void Window::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        Input::mMouseButtons[button] = action != GLFW_RELEASE;
    }
    void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        Input::mScrollX = xoffset;
        Input::mScrollY = yoffset;
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
