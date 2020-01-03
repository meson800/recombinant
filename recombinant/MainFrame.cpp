#include "MainFrame.h"

#include "wx/aui/aui.h"

#include "AboutDialog.h"
#include "TreeWindow.h"
#include "ids.h"

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    manager.SetManagedWindow(this);
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(GUI_IDS::ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MainFrame::OnHello, this, GUI_IDS::ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);


    TreeWindow* tree   = new TreeWindow(this, -1);
    wxTextCtrl* text2 = new wxTextCtrl(this, -1);
    manager.AddPane(tree, wxAuiPaneInfo().CenterPane().Caption("Caption 1"));
    manager.AddPane(text2, wxAuiPaneInfo().Bottom().Caption("Caption 2"));
    manager.Update();
}

MainFrame::~MainFrame()
{
    manager.UnInit();
}

void MainFrame::OnExit(wxCommandEvent&)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent&)
{
    AboutDialog* about = new AboutDialog(this);
    about->Show();
}

void MainFrame::OnHello(wxCommandEvent&)
{
    wxLogMessage("Hello world from wxWidgets!");
}
