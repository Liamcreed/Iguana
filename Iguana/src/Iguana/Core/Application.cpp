#include "pch.h"
#include "Application.h"

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
        while (m_Running)
        {
            std::cout<<Input::GetAxis("Horizontal")<<std::endl;

            m_Window->Update();
            if (m_Window->IsClosed())
                Close();
        }
    }
    void Application::Close()
    {
        m_Running = false;
    }
    Application::~Application()
    {
        delete m_Window;
    }
} // namespace Iguana
