// 2022/04/27 11:12:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

private:
    wxDECLARE_EVENT_TABLE();
};
