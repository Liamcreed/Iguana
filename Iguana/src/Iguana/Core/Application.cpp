#include "pch.h"
#include "Application.h"
#include "Iguana/Platform/Vulkan/Renderer.h"

namespace Iguana
{
    Application *Application::mInstance = nullptr;
    
    Application::Application(std::string title)
    {
        mInstance = this;

        mWindow = new Window(title, 1280, 720);
        mWindow->Vsync(true);

        mRunning = true;
    }
    void Application::Run()
    {
        Renderer::Create();

        while (mRunning)
        {
            if (!mWindow->IsMinimized())
            {
            
            }
            mWindow->Update();
        }
    }
    void Application::Close()
    {
        mRunning = false;
        Renderer::Clean();
    }
    Application::~Application()
    {
        delete mWindow;
    }
} // namespace Iguana
