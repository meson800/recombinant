#include "FilesDataModel.h"

DataItem::DataItem(std::filesystem::path loc)
    : parent(nullptr)
    , location(loc)
{
    name = location.filename().string();
    if (is_directory(location))
    {
        for (auto& entry : std::filesystem::directory_iterator(location))
        {
            children.emplace_back(new DataItem(entry.path()));
        }
    }
}

DataItem::DataItem(std::filesystem::path loc, DataItem* parent_)
    : parent(parent_)
    , location(loc)
{
    name = location.filename().string();
    if (is_directory(location))
    {
        for (auto& entry : std::filesystem::directory_iterator(location))
        {
            children.emplace_back(new DataItem(entry.path(), this));
        }
    }
}

DataItem::operator wxDataViewItem()
{
    return wxDataViewItem(this);
}

DataItem::operator wxDataViewItem() const
{
    //ugly hacks because wxWidgets sucks
    return wxDataViewItem(
        const_cast<void*>(reinterpret_cast<const void*>(this)));
}

FilesDataModel::FilesDataModel(std::filesystem::path root_)
    : root(root_)
    , rootItem(root_)
{}

bool FilesDataModel::IsContainer(const wxDataViewItem& wxItem) const
{
    if (!wxItem.IsOk())
    {
        // The "fake root" node actually owns our root node, so it's a
        // container!
        return true;
    }

    DataItem& item = *reinterpret_cast<DataItem*>(wxItem.GetID());
    return !item.children.empty();
}

wxDataViewItem FilesDataModel::GetParent(const wxDataViewItem& wxItem) const
{
    if (!wxItem.IsOk())
    {
        return wxDataViewItem(nullptr);
    }

    return wxDataViewItem(reinterpret_cast<DataItem*>(wxItem.GetID())->parent);
}

unsigned int FilesDataModel::GetChildren(
    const wxDataViewItem& wxItem, wxDataViewItemArray& children) const
{
    if (!wxItem.IsOk())
    {
        // The root node owns a single item: our true root
        children.Add(wxDataViewItem(rootItem));
        return 1;
    }

    DataItem& item = *reinterpret_cast<DataItem*>(wxItem.GetID());
    children.Alloc(item.children.size());
    for (auto& child : item.children)
    {
        children.Add(wxDataViewItem(*child));
    }
    return static_cast<unsigned int>(item.children.size());
}

unsigned int FilesDataModel::GetColumnCount() const
{
    return 1;
}

wxString FilesDataModel::GetColumnType(unsigned int) const
{
    return "string";
}

void FilesDataModel::GetValue(
    wxVariant& val, const wxDataViewItem& wxItem, unsigned int) const
{
    if (!wxItem.IsOk())
    {
        val.Convert("Root");
        return;
    }

    DataItem& item = *reinterpret_cast<DataItem*>(wxItem.GetID());
    wxString str   = item.name.c_str();
    val            = str;
}

bool FilesDataModel::SetValue(
    const wxVariant&, const wxDataViewItem&, unsigned int)
{
    return false;
}
