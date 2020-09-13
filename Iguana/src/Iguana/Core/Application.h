#pragma once
#include "Window.h"

namespace Iguana
{
    class Application
    {
    private:
        static Application* mInstance;
        Window* mWindow;

        bool mRunning = false;
    public:
        Application(std::string title = "Iguana Application");
        ~Application();

        void Run();
        void Close();
        
        static Application* Get(){return mInstance;}
        Window* GetWindow(){return mWindow;}
    };
    
}