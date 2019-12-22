#pragma once

#include "wx_headers.h"
#include "wx/aui/framemanager.h"

class MainFrame : public wxFrame
{
    public:
    MainFrame();
    ~MainFrame();

    private:
    wxAuiManager manager;

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
