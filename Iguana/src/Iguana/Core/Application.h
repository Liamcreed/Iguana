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
        
        Application& Get(){return *m_Instance;}
    };
    Application* CreateApp();
    //To be defined in the Client application
}