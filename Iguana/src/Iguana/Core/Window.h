#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Input.h"

namespace Iguana
{
    class Window
    {
    private:
        std::string m_Title = "Application";
        uint32_t m_Width, m_Height;

        GLFWwindow *m_GLFWWindow;

    public:
        void Update();

        Window(std::string &title, uint32_t width, uint32_t height);
        ~Window();

        bool IsClosed() { return glfwWindowShouldClose(m_GLFWWindow); }
        bool IsMinimized();
        bool IsMaximized();

        int GetWidth() { return m_Width; }
        int GetHeight() { return m_Height; }

        std::string &GetTitle() { return m_Title; }
        GLFWwindow *GetGLFWWindow() { return m_GLFWWindow; }

        void Vsync(bool vsync)
        {
            if (vsync)
                glfwSwapInterval(1);
            else
                glfwSwapInterval(0);
        }

        //--------Calbacks---------//
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        static void window_iconify_callback(GLFWwindow *window, int iconified);
        static void window_maximize_callback(GLFWwindow *window, int maximized);
    };
} // namespace Iguana
