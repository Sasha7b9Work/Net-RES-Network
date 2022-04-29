// 2022/04/29 13:56:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Application.h"
#include "Frame.h"


wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // we use a PNG image in our HTML page
    wxImage::AddHandler(new wxPNGHandler);

    // create and show the main application window
    Frame *frame = new Frame(_("Метеостанция"));
    frame->Show();

    return true;
}
