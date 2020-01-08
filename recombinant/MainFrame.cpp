#include "MainFrame.h"

#include "wx/aui/aui.h"

#include "AboutDialog.h"
#include "TreeWindow.h"
#include "ViewWindow.h"
#include "ids.h"
#include "strings.h"

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, localizedString(StringID::ProgramName),
          wxDefaultPosition, wxSize(500, 600))
{
#ifdef WIN32
    SetIcons(wxICON(aaaaaaMAIN_ICON));
#endif

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
    SetStatusText(localizedString(StringID::Welcome));
    Bind(wxEVT_MENU, &MainFrame::OnHello, this, GUI_IDS::ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

    TreeWindow* tree   = new TreeWindow(this, -1);
    ViewWindow* viewer = new ViewWindow(this, -1);
    manager.AddPane(
        tree, wxAuiPaneInfo().CenterPane().MinSize(tree->GetMinSize()));
    manager.AddPane(viewer, wxAuiPaneInfo()
                                .Bottom()
                                .Caption(localizedString(StringID::Viewer))
                                .MinSize(viewer->GetMinSize()));
    manager.Update();
    SetMinSize(wxSize(500, 600));
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
