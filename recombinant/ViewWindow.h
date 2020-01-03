#pragma once

#include "wx_headers.h"

/**
 * This class visually displays selected sequences. This is the main
 * purpose of Recombinant!
 *
 * This is drawn manually via a wxDC, because of the relative complexiety
 * of displaying annotated sequences, sequencing traces, etc.
 */
class ViewWindow : public wxWindow
{
public:
    ViewWindow(wxWindow* parent, wxWindowID id);
    ~ViewWindow();

    /// Handles the paint event by drawing on the window itself
    void OnPaint(wxPaintEvent& event);

    /// Handles resizing events
    void OnSize(wxSizeEvent&);

private:
};
