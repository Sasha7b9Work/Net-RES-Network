// 2022/04/29 13:56:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Display/Table/Table.h"


class DiagramPool;


class Frame : public wxFrame
{
public:
    Frame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    static Frame *self;

private:

    struct ModeView
    {
        enum E
        {
            Full,
            Table,
            Graph
        };
    };

    ModeView::E mode_view = ModeView::Full;

    wxToolBar *toolBar = nullptr;

    wxBoxSizer *sizer = nullptr;

    void OnSize(wxSizeEvent &);

    void OnCloseWindow(wxCloseEvent &);

    void OnMenuTool(wxCommandEvent &);

    void OnMenuSettings(wxCommandEvent &);

    void OnClose();

    void SetModeView(ModeView::E);
};
