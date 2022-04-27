#define WIN32_LEAN_AND_MEAN
#include "wx/wxprec.h"
#include "wx/wx.h"
#include "wx/image.h"
#include "wx/imagpng.h"
#include "wx/wxhtml.h"
#include "wx/statline.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../../sample.xpm"
#endif


class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title);

    void OnQuit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

private:
    wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
wxEND_EVENT_TABLE()


wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // we use a PNG image in our HTML page
    wxImage::AddHandler(new wxPNGHandler);

    // create and show the main application window
    MyFrame *frame = new MyFrame(_("wxHtmlWindow testing application"));
    frame->Show();

    return true;
}


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
    wxHtmlWindow *html;
    wxDialog dlg(this, wxID_ANY, wxString(_("About")));

    topsizer = new wxBoxSizer(wxVERTICAL);

    html = new wxHtmlWindow(&dlg, wxID_ANY, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
    html->SetBorders(0);
    html->LoadPage("data/about.htm");
    html->SetHTMLBackgroundImage(wxBitmapBundle::FromSVGFile("data/bg.svg", wxSize(65, 45)));
    html->SetInitialSize(wxSize(html->GetInternalRepresentation()->GetWidth(),
        html->GetInternalRepresentation()->GetHeight()));

    topsizer->Add(html, 1, wxALL, 10);

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
