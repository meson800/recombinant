#include "TreeWindow.h"

#include "strings.h"

TreeWindow::TreeWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    loadDataControl = new wxStaticText(
        this, wxID_ANY, localizedString(StringID::AddDataSources));
    sizer = new wxGridSizer(1, 1, 10, 10);
    sizer->Add(loadDataControl, 0, wxALIGN_CENTER);
    SetSizerAndFit(sizer);
}

TreeWindow::~TreeWindow()
{}

void TreeWindow::OnPaint(wxPaintEvent&)
{}
