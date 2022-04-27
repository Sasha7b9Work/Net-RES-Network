#define WIN32_LEAN_AND_MEAN
#include "Frame.h"
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/image.h"
#include "wx/imagpng.h"
#include "wx/statline.h"


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
wxEND_EVENT_TABLE()


MyFrame::MyFrame(const wxString &title)
    : wxFrame((wxFrame *)NULL, wxID_ANY, title)
{
    SetIcon(wxICON(sample));

    wxMenu *menuFile = new wxMenu;

    menuFile->Append(wxID_ABOUT);
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, _("&File"));

    SetMenuBar(menuBar);
}


void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
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
