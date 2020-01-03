#pragma once

#include "wx_headers.h"
#include <wx/treelist.h>

/**
 * This class visually displays a tree of possible items.
 *
 * These items are filled relative to data sources loaded through the
 * data source pane.
 */
class TreeFrame : public wxWindow
{
public:
    TreeFrame(wxWindow* parent, wxWindowID id);
    ~TreeFrame();

    /// Handles the paint event by recalculating the view state of the treeview.
    void OnPaint(wxPaintEvent& event);

private:
    /// The main point of this frame. Stores a treelist of available sequences
    wxTreeListCtrl* treelist;
    /// Gives the "add a data source" message if none are selected.
    wxStaticText* loadDataControl;
    /// This sizer centers the control inside the window
    wxGridSizer* sizer;
};
