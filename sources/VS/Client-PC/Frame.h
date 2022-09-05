// 2022/04/29 13:56:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


class wxGrid;


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    static Frame *Self() { return self; }

    void OnPaint(wxPaintEvent &);

    void OnCloseWindow(wxCloseEvent &);

    void SetID(uint id);

    void SetParameter(uint8 type, float value);

private:

    static Frame *self;
    wxToolBar    *toolBar = nullptr;
    wxGrid       *grid;

    void OnViewBrief(wxCommandEvent &);
    void OnViewFull(wxCommandEvent &);

    void OnMeasurePressure(wxCommandEvent &);
    void OnMeasureIllumination(wxCommandEvent &);
    void OnMeasureHumidity(wxCommandEvent &);
    void OnMeasureVelocity(wxCommandEvent &);
    void OnMeasureTemperature(wxCommandEvent &);

    void CreateFrameToolBar();

    void AddTool(int id, const wxString &label, pchar nameResource, pchar nameResourceDisabled = nullptr);

    void OnClose();
};
