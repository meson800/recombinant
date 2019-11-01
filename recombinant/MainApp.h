#pragma once
//  Copyright(C) 2019. See AUTHORS file for contact information.
//  This is free software, licensed under the GPL Version 2 license (or at your option)
//  a later version. See the LICENSE file for more details.

#include "wx_headers.h"

class MainInterface : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnExit();
};
class MainFrame : public wxFrame
{
  public:
    MainFrame();

  private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
enum
{
    ID_Hello = 1
};
