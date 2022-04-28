// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    static Frame *Self() { return self; };

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnPaint(wxPaintEvent &event);

private:
    wxDECLARE_EVENT_TABLE();

    static Frame *self;
};
