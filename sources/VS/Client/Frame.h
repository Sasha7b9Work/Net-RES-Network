// 2022/04/29 13:56:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "defines.h"
#include <wx/wx.h>


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

private:

    wxToolBar *toolBar = nullptr;

    void OnViewBrief(wxCommandEvent &);
    void OnViewFull(wxCommandEvent &);

    void CreateFrameToolBar();

    void AddTool(int id, const wxString &label, pchar nameResource, pchar nameResourceDisabled = nullptr);
};
