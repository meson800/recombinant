#pragma once

#include "wx_headers.h"

#include <wx/dataview.h>

#include <filesystem>

/**
 * Because wxWidgets expects effectively a linked list, we need to
 * use something that also uses these fixed types of structures (e.g. with
 * _stable_ pointers). This is a limitation of wxWidgets
 * This class handles this internal state.
 */
struct DataItem
{
    /// Stores the displayed name of this DataItem
    std::string name;

    /// Stores a vector of the children of this DataItem
    std::vector<std::unique_ptr<DataItem>> children;

    /// Stores the actual location of the item
    std::filesystem::path location;

    /**
     * Stores the parent of this DataItem. If this item is the
     * root, it instead is equal to nullptr
     */
    DataItem* parent;

    /**
     * Initalizes this DataItem from a location. This recursively
     * adds children!
     *
     * No deconstructor needed because we use unique_ptr's
     * This sets parent equal to itself
     */
    DataItem(std::filesystem::path loc);

    /// Version of the constructor with a parent
    DataItem(std::filesystem::path loc, DataItem* parent_);

    /// Remove the copy constructor for safety
    DataItem(const DataItem&) = delete;

    /// Allows a DataItem to be freely converted to a DataItem
    operator wxDataViewItem();
    operator wxDataViewItem() const;
};

/**
 * This class represents files open from one of various sources.
 */
class FilesDataModel : public wxDataViewModel
{
public:
    /// Given a filesystem path, represents the files under this root.
    FilesDataModel(std::filesystem::path root_);

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
    /// Stores the root filesystem path to use
    std::filesystem::path root;

    DataItem rootItem;
};
