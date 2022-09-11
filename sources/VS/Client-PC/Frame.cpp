// 2022/04/29 13:56:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Frame.h"
#include "Display/Display.h"
#include "Display/Diagram/Diagram.h"
#include "Display/Grid/Grid.h"
#include "Display/Diagram/Canvas.h"


Frame *Frame::self = nullptr;


enum
{
    TOOL_OPEN,
    TOOL_SAVE,
    TOOL_NEW,

    TOOL_UNDO,
    TOOL_REDO,

    TOOL_VIEW_BRIEF,        // Сокращённый вид отображения
    TOOL_VIEW_FULL,         // Полный вид отображения

    MEAS_PRESSURE,          // Давление
    MEAS_ILLUMINATION,      // Освещённость
    MEAS_HUMIDITY,          // Влажность
    MEAS_VELOCITY,          // Скорость
    MEAS_TEMPERATURE        // Температура
};


Frame::Frame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    self = this;

    SetIcon(wxICON(MAIN_ICON));

    wxMenuBar *menuBar = new wxMenuBar;

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, _("Файл"));

    wxMenu *menuSettings = new wxMenu;
    menuBar->Append(menuSettings, _("Настройки"));

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuBar->Append(menuHelp, _("Помощь"));

    wxFrameBase::SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &Frame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &Frame::OnQuit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &Frame::OnCloseWindow, this);

    Bind(wxEVT_MENU, &Frame::OnViewBrief, this, TOOL_VIEW_BRIEF);
    Bind(wxEVT_MENU, &Frame::OnViewFull, this, TOOL_VIEW_FULL);

    Bind(wxEVT_PAINT, &Frame::OnPaint, this);
    Bind(wxEVT_SIZE, &Frame::OnSize, this);

//    CreateFrameToolBar();

    grid = new Grid(this, wxID_ANY, wxPoint(0, 0), FromDIP(wxSize(500, 400)));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(grid);

    diagrams = new DiagramPool(this);

    sizer->Add(diagrams);

    SetSizer(sizer);

    SetClientSize(800, 600);
}


void Frame::CreateFrameToolBar()
{
    toolBar = CreateToolBar();

    AddTool(TOOL_VIEW_BRIEF, _T("Краткий вид"), "TOOL_VIEW_BRIEF");
    AddTool(TOOL_VIEW_FULL, _T("Полный вид"), "TOOL_VIEW_FULL");

    toolBar->AddSeparator();

    AddTool(MEAS_PRESSURE, _T("Давление"), "MEAS_PRESSURE");
    AddTool(MEAS_ILLUMINATION, _T("Освещённость"), "MEAS_ILLUMINATION");
    AddTool(MEAS_VELOCITY, _T("Скорость"), "MEAS_VELOCITY");
    AddTool(MEAS_TEMPERATURE, _T("Температура"), "MEAS_TEMPERATURE");
    AddTool(MEAS_HUMIDITY, _T("Влажность"), "MEAS_HUMIDITY");

    Bind(wxEVT_MENU, &Frame::OnMeasurePressure, this, MEAS_PRESSURE);
    Bind(wxEVT_MENU, &Frame::OnMeasureIllumination, this, MEAS_ILLUMINATION);
    Bind(wxEVT_MENU, &Frame::OnMeasureHumidity, this, MEAS_HUMIDITY);
    Bind(wxEVT_MENU, &Frame::OnMeasureVelocity, this, MEAS_VELOCITY);
    Bind(wxEVT_MENU, &Frame::OnMeasureTemperature, this, MEAS_TEMPERATURE);

    toolBar->Realize();
}


void Frame::AddTool(int id, const wxString &label, pchar nameResource, pchar nameResourceDisabled)
{
    wxBitmap bitmap(nameResource, wxBITMAP_TYPE_BMP_RESOURCE);

    wxBitmap bitmapDisabled(nameResourceDisabled ? wxBitmap(nameResourceDisabled, wxBITMAP_TYPE_BMP_RESOURCE) : bitmap);

    toolBar->AddTool(id, label, bitmap, bitmapDisabled, wxITEM_NORMAL, label, label);
}


void Frame::OnViewBrief(wxCommandEvent &)
{

}


void Frame::OnViewFull(wxCommandEvent &)
{

}


void Frame::OnMeasurePressure(wxCommandEvent &)
{
    Display::SwitchMeasure(TypeMeasure::Pressure);
}


void Frame::OnMeasureIllumination(wxCommandEvent &)
{
    Display::SwitchMeasure(TypeMeasure::Illumination);
}


void Frame::OnMeasureHumidity(wxCommandEvent &)
{
    Display::SwitchMeasure(TypeMeasure::Humidity);
}


void Frame::OnMeasureVelocity(wxCommandEvent &)
{
    Display::SwitchMeasure(TypeMeasure::Velocity);
}


void Frame::OnMeasureTemperature(wxCommandEvent &)
{
    Display::SwitchMeasure(TypeMeasure::Temperature);
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


void Frame::OnPaint(wxPaintEvent &)
{
}


void Frame::OnSize(wxSizeEvent &)
{

}


void Frame::SetID(uint id)
{
    grid->SetCellValue(0, 0, wxString::Format("%d", id));
}


void Frame::SetParameter(uint8 type, float value)
{
    grid->SetCellValue(0, type + 1, wxString::Format("%10.2f", value));
}
