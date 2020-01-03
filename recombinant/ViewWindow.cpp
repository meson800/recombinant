#include "ViewWindow.h"

#include "strings.h"

ViewWindow::ViewWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id, wxDefaultPosition, wxSize(300, 200))
{
    Bind(wxEVT_PAINT, &ViewWindow::OnPaint, this, wxID_ANY);
    Bind(wxEVT_SIZE, &ViewWindow::OnSize, this, wxID_ANY);
}

ViewWindow::~ViewWindow()
{}

void ViewWindow::OnPaint(wxPaintEvent&)
{
    wxPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxSize dcExtent = dc.GetSize();

    wxSize textExtent =
        dc.GetTextExtent(localizedString(StringID::NoSequenceSelected));
    dc.DrawText(localizedString(StringID::NoSequenceSelected),
        (dcExtent.GetX() - textExtent.GetX()) / 2,
        (dcExtent.GetY() - textExtent.GetY()) / 2);
}

void ViewWindow::OnSize(wxSizeEvent&)
{
    Refresh();
}
