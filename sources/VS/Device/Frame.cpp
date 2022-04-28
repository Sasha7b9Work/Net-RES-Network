// 2022/04/27 11:11:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Display/Display.h"
#include "Modules/ST7735/ST7735.h"
#include "Application.h"
#include "wx/statline.h"


// Здесь нарисованная картинка
static wxBitmap bitmap(Display::WIDTH, Display::HEIGHT);

// Здесь будем рисовать
static wxMemoryDC memDC;

Frame *Frame::self = nullptr;

enum
{
    TIMER_ID = 111
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_MENU(wxID_ABOUT, Frame::OnAbout)
EVT_MENU(wxID_EXIT, Frame::OnQuit)
wxEND_EVENT_TABLE()


class Screen : public wxPanel
{
public:
    Screen(wxWindow *parent) : wxPanel(parent)
    {
        SetMinSize({ Display::WIDTH, Display::HEIGHT });
        SetDoubleBuffered(true);
        Bind(wxEVT_PAINT, &Screen::OnPaint, this);
    }

    void OnPaint(wxPaintEvent &)
    {
        wxPaintDC dc(this);

        wxMemoryDC memoryDC;
        memoryDC.SelectObject(bitmap);

        wxSize size = dc.GetSize();
        dc.Blit(0, 0, size.GetWidth(), size.GetHeight(), &memoryDC, 0, 0, wxCOPY);

        memoryDC.SelectObject(wxNullBitmap);
    }
};


static Screen *screen = nullptr;


Frame::Frame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    SetIcon(wxICON(sample));

    wxMenu *menuFile = new wxMenu;

    menuFile->Append(wxID_ABOUT);
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&File"));

    SetMenuBar(menuBar);

    self = this;

    screen = new Screen(this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(screen);
    SetSizer(sizer);

    Bind(wxEVT_PAINT, &Frame::OnPaint, this);
    Bind(wxEVT_TIMER, &Frame::OnTimer, this, TIMER_ID);

    timer.SetOwner(this, TIMER_ID);

    timer.Start(1);

    Show(true);
}


void Frame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

void Frame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxBoxSizer *topsizer;
    wxDialog dlg(this, wxID_ANY, wxString(_("About")));

    topsizer = new wxBoxSizer(wxVERTICAL);

#if wxUSE_STATLINE
    topsizer->Add(new wxStaticLine(&dlg, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
#endif // wxUSE_STATLINE

    wxButton *bu1 = new wxButton(&dlg, wxID_OK, _("OK"));
    bu1->SetDefault();

    topsizer->Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);

    dlg.SetSizer(topsizer);
    topsizer->Fit(&dlg);

    dlg.ShowModal();
}


void Frame::OnTimer(wxTimerEvent &)
{
    Application::Self()->Update();
}


void Frame::BeginScene()
{
    memDC.SelectObject(bitmap);
}


void Frame::EndScene()
{
    memDC.SelectObject(wxNullBitmap);

    screen->Refresh();
}


void ST7735::WriteBuffer(int x0, int y0, int width, int height)
{
    static const wxColour colors[16] =
    {
        {1.0f, 0.0f, 0.0f},
        wxColour(0.0f, 1.0f, 0.0f),
        wxColour(0.0f, 0.5f, 0.05f),
        wxColour(0.0f, 0.5f, 0.0f),
        wxColour(0.0f, 0.0f, 1.0f),
        wxColour(0.5f, 0.5f, 0.5f),
        wxColour(0.25f, 0.25f, 0.25f),
        wxColour(0.12f, 0.12f, 0.12f),
        wxColour(1.0f, 0.0f, 0.0f),
        wxColour(0.0f, 1.0f, 0.0f),
        wxColour(0.0f, 0.5f, 0.05f),
        wxColour(0.0f, 0.5f, 0.0f),
        wxColour(0.0f, 0.0f, 1.0f),
        wxColour(0.5f, 0.5f, 0.5f),
        wxColour(0.25f, 0.25f, 0.25f),
        wxColour(0.12f, 0.12f, 0.12f)
    };

    for (int y = y0; y < y0 + height; y++)
    {
        uint8 *points = Display::Buffer::GetLine(x0, y);

        uint8 value = *points;

        for (int x = x0; x < x0 + width; x += 2)
        {
            memDC.SetPen(wxPen(colors[value >> 4]));

            memDC.DrawPoint(x, y);

            memDC.SetPen(wxPen(colors[value & 0x0f]));

            memDC.DrawPoint(x + 1, y);

            value = *(++points);
        }
    }
}
