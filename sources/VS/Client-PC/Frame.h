// 2022/04/29 13:56:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Grid/Grid.h"
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


class DiagramPool;


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    static Frame *self;

private:

    wxToolBar    *toolBar = nullptr;

    void OnTimeScaleEvent(wxCommandEvent &);

    void OnSize(wxSizeEvent &);

    void OnCloseWindow(wxCloseEvent &);

    void OnClose();
};
