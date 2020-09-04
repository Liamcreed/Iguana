#pragma once
#include "Application.h"

namespace Iguana
{
    Application *CreateApp();
} 

int main(int argc, char const *argv[])
{
    auto app = Iguana::CreateApp();

    app->Run();

    delete app;

    return 0;
}
