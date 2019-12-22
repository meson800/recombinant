#pragma once

#include "wx_headers.h"

class MainFrame : public wxFrame
{
   public:
    MainFrame();

   private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
