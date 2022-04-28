// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    static Frame *Self() { return self; };

    void OnQuit(wxCommandEvent &);
    void OnAbout(wxCommandEvent &);
    void OnPaint(wxPaintEvent &);
    void OnTimer(wxTimerEvent &);

private:
    wxDECLARE_EVENT_TABLE();

    wxTimer timer;
    static Frame *self;
};
