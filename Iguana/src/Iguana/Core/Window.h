#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Input.h"

namespace Iguana
{
    class Window
    {
    private:
        std::string mTitle = "Application";
        uint32_t mWidth, mHeight;

        GLFWwindow *mGLFWWindow;

    public:
        void Update();

        Window(std::string &title, uint32_t width, uint32_t height);
        ~Window();

        bool IsClosed() { return glfwWindowShouldClose(mGLFWWindow); }
        bool IsMinimized();
        bool IsMaximized();
        void Vsync(bool vsync);

        int GetWidth() { return mWidth; }
        int GetHeight() { return mHeight; }

        std::string &GetTitle() { return mTitle; }
        GLFWwindow *GetGLFWWindow() { return mGLFWWindow; }

        //--------Calbacks---------//
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
        static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        static void window_iconify_callback(GLFWwindow *window, int iconified);
        static void window_maximize_callback(GLFWwindow *window, int maximized);
    };
} // namespace Iguana
