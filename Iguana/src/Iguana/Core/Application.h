#pragma once
#include "Window.h"

namespace Iguana
{
    class Application
    {
    private:
        static Application* m_Instance;
        Window* m_Window;

        bool m_Running = false;
    public:
        Application(std::string title = "Iguana Application");
        ~Application();

        void Run();
        void Close();
        
        static Application* Get(){return m_Instance;}
        Window* GetWindow(){return m_Window;}
    };
    
}