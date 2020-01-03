#include "ViewWindow.h"

ViewWindow::ViewWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id, wxDefaultPosition, wxSize(300, 200))
{
    Bind(wxEVT_PAINT, &ViewWindow::OnPaint, this, wxID_ANY);
}

ViewWindow::~ViewWindow()
{}

void ViewWindow::OnPaint(wxPaintEvent&)
{
    wxPaintDC dc(this);
}
