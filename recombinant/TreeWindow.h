#pragma once

#include "wx_headers.h"
#include <wx/dataview.h>

#include "SourceDataModel.h"
#include "../api/Source.h"

/**
 * This class visually displays a tree of possible items.
 *
 * These items are filled relative to data sources loaded through the
 * data source pane.
 */
class TreeWindow : public wxWindow
{
public:
    TreeWindow(wxWindow* parent, wxWindowID id);
    ~TreeWindow();

    /// Handles the paint event by recalculating the view state of the treeview.
    void OnPaint(wxPaintEvent& event);

private:
    /// Stores the control for the main data view
    wxDataViewCtrl* dataView;
    /// Stores the actual data model representing sequences/alignments/etc loaded
    SourceDataModel* dataModel;

    /// Stores the Source that we are temporarily using to feed data
    recombinant::api::Source* source;

    /// Gives the "add a data source" message if none are selected.
    wxStaticText* loadDataControl;
    /// This sizer centers the control inside the window
    wxGridSizer* sizer;
};
