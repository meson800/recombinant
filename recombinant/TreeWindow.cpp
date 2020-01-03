#include "TreeWindow.h"

#include "strings.h"

TreeWindow::TreeWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    treelist = new wxTreeListCtrl(
        this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_MULTIPLE, "");
    loadDataControl = new wxStaticText(
        this, wxID_ANY, localizedString(StringID::AddDataSources));
    sizer = new wxGridSizer(1, 1, 10, 10);
    treelist->Hide();
    sizer->Add(loadDataControl, 0, wxALIGN_CENTER);
    SetSizerAndFit(sizer);
}

TreeWindow::~TreeWindow()
{}

void TreeWindow::OnPaint(wxPaintEvent&)
{}
