// 2022/09/05 08:52:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Diagram/Diagram.h"


Diagram *Diagram::Create(wxWindow *parent)
{
    return new Diagram(parent);
}


Diagram::Diagram(wxWindow *parent) : wxPanel(parent, wxID_ANY)
{

}


namespace PoolDiagram
{
    static Diagram *first = nullptr;

    Diagram *Create(wxWindow *parent)
    {
        first = Diagram::Create(parent);

        return first;
    }

    Diagram *GetFirst()
    {
        return first;
    }
}
