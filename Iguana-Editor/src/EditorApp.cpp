#include "Iguana.h"

class IguanaEditor : public Iguana::Application
{
public:
    IguanaEditor(){}
    ~IguanaEditor(){}
};

Iguana::Application* Iguana::CreateApp()
{
    return new IguanaEditor;
}