#pragma once

#include "wx_headers.h"

#include <wx/dataview.h>

/**
 * This class represents files open from one of various sources.
 */

class FilesDataModel : public wxDataViewModel
{
public:
    /**
     * Given a wxDataViewItem, returns true if the given item has children,
     * false if it does not.
     *
     * Specifying the special nullptr ID inside a wxDataViewItem "selects"
     * the invisible root.
     */
    virtual bool IsContainer(const wxDataViewItem& item) const override;
    /**
     * Given a wxDataViewItem, returns the parent of this item. If the item has
     * no parent (e.g. its parent is the invisible root), then we return an
     * invalid wxDataViewItem (e.g. one that has value nullptr).
     */
    virtual wxDataViewItem GetParent(const wxDataViewItem& item) const override;
    /**
     * Given an item, returns the children of this wxDataViewItem
     * by returning them as a wxDataViewItemArray. The size of this
     * array is returned with the return value.
     */
    virtual unsigned int GetChildren(const wxDataViewItem& item,
        wxDataViewItemArray& children) const override;
    /**
     * Returns the number of columns included in this control.
     */
    virtual unsigned int GetColumnCount() const override;
    /**
     * Given a column ID, returns the name of the column.
     */
    virtual wxString GetColumnType(unsigned int col) const override;
    /**
     * Given a column number and a wxDataViewItem, returns the
     * value of that item and its column.
     */
    virtual void GetValue(wxVariant& variant, const wxDataViewItem& item,
        unsigned int col) const override;

    /**
     * Given an item and a column, sets the value of the underlying
     * file. Returns false if it is not possible to set that value (e.g. if it
     * is not editable)
     */
     virtual bool SetValue(const wxVariant& variant, const wxDataViewItem& item,
        unsigned int col) override;

private:

};
