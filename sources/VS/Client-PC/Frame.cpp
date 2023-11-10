// 2022/04/29 13:56:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Display/Diagram/Diagram.h"
#include "Display/Grid/Grid.h"
#include "Display/Diagram/Canvas.h"
#include "Settings.h"
#include "Controls/ConsoleSCPI.h"


Frame *Frame::self = nullptr;


enum
{
    FILE_QUIT = wxID_HIGHEST + 1,

    TOOL_OPEN,
    TOOL_SAVE,
    TOOL_NEW,

    TOOL_UNDO,
    TOOL_REDO,

    TOOL_VIEW_BRIEF,        // Сокращённый вид отображения
    TOOL_VIEW_FULL,         // Полный вид отображения

    TOOL_CONSOLE,

    MEAS_PRESSURE,          // Давление
    MEAS_ILLUMINATION,      // Освещённость
    MEAS_HUMIDITY,          // Влажность
    MEAS_VELOCITY,          // Скорость
    MEAS_TEMPERATURE,       // Температура

    ID_SPEED_1,
    ID_SPEED_2,
    ID_SPEED_5,
    ID_SPEED_30,
    ID_SPEED_60
};


Frame::Frame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    self = this;

    SetIcon(wxICON(MAIN_ICON));

    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(FILE_QUIT, "E&xit\tAlt-X", "Quit this program");
    menuBar->Append(menuFile, _("Файл"));

    wxMenu *menuSettings = new wxMenu();
    wxMenu *menuSpeed = new wxMenu();

    wxMenuItem *miSpeed1 = new wxMenuItem(menuSpeed, ID_SPEED_1, "1 сек", wxEmptyString, wxITEM_RADIO);
    wxMenuItem *miSpeed2 = new wxMenuItem(menuSpeed, ID_SPEED_2, "2 сек", wxEmptyString, wxITEM_RADIO);
    wxMenuItem *miSpeed5 = new wxMenuItem(menuSpeed, ID_SPEED_5, "5 сек", wxEmptyString, wxITEM_RADIO);
    wxMenuItem *miSpeed30 = new wxMenuItem(menuSpeed, ID_SPEED_30, "30 сек", wxEmptyString, wxITEM_RADIO);
    wxMenuItem *miSpeed60 = new wxMenuItem(menuSpeed, ID_SPEED_60, "60 сек", wxEmptyString, wxITEM_RADIO);

    menuSpeed->Append(miSpeed1);
    menuSpeed->Append(miSpeed2);
    menuSpeed->Append(miSpeed5);
    menuSpeed->Append(miSpeed30);
    menuSpeed->Append(miSpeed60);

    menuSettings->AppendSubMenu(menuSpeed, "Скорость обновления");

    wxMenu *menuTools = new wxMenu();
    menuTools->Append(TOOL_CONSOLE, "Open console\tCtrl-K", "Open console");

    Bind(wxEVT_MENU, &Frame::OnTimeScaleEvent, this, ID_SPEED_1);
    Bind(wxEVT_MENU, &Frame::OnTimeScaleEvent, this, ID_SPEED_2);
    Bind(wxEVT_MENU, &Frame::OnTimeScaleEvent, this, ID_SPEED_5);
    Bind(wxEVT_MENU, &Frame::OnTimeScaleEvent, this, ID_SPEED_30);
    Bind(wxEVT_MENU, &Frame::OnTimeScaleEvent, this, ID_SPEED_60);

    menuBar->Append(menuSettings, _("Настройки"));

    menuBar->Append(menuTools, _("Инструменты"));

    wxFrameBase::SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &Frame::OnQuit, this, FILE_QUIT);
    Bind(wxEVT_MENU, &Frame::OnToolConsole, this, TOOL_CONSOLE);
    Bind(wxEVT_CLOSE_WINDOW, &Frame::OnCloseWindow, this);

    Bind(wxEVT_SIZE, &Frame::OnSize, this);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(Grid::Create(this, FromDIP(wxSize((TypeMeasure::NumMeasures() + 1) * 60, 400))));

    sizer->Add(Diagram::Pool::Create(this));

    SetSizer(sizer);

    SetClientSize(1024, 600);
    wxWindowBase::SetMinClientSize({ 800, 300 });
}


void Frame::OnTimeScaleEvent(wxCommandEvent &event)
{
    static const int scales[] = { 1, 2, 5, 30, 60 };

    Set::TimeScale::Set(scales[event.GetId() - ID_SPEED_1]);
}


void Frame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    self = nullptr;

    Close(true);

    OnClose();
}


void Frame::OnCloseWindow(wxCloseEvent &event)
{
    self = nullptr;

    event.Skip();

    OnClose();
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


void Frame::OnSize(wxSizeEvent &event)
{
    Diagram::Pool::self->SetSizeArea(GetClientRect().width - Grid::self->GetSize().x, GetClientRect().height);

    wxSize size = { Grid::self->GetSize().GetWidth(), GetClientRect().height };

    Grid::self->SetMinClientSize(size);
    Grid::self->SetClientSize(size);
    Grid::self->SetSize(size);

    event.Skip();
}


void Frame::OnToolConsole(wxCommandEvent &)
{
    ConsoleSCPI::Self()->SwitchVisibility();
}
