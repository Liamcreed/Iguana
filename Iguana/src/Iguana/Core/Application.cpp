#include "pch.h"
#include "Application.h"
#include "Iguana/Platform/Vulkan/Renderer.h"

namespace Iguana
{
    Application *Application::m_Instance = nullptr;
    
    Application::Application(std::string title)
    {
        m_Instance = this;

        m_Window = new Window(title, 1280, 720);
        m_Window->Vsync(true);

        m_Running = true;
    }
    void Application::Run()
    {
        Renderer::Create();

        while (m_Running)
        {
            if (!m_Window->IsMinimized())
            {
            
            }
            m_Window->Update();
        }
    }
    void Application::Close()
    {
        m_Running = false;
        Renderer::Clean();
    }
    Application::~Application()
    {
        delete m_Window;
    }
} // namespace Iguana
