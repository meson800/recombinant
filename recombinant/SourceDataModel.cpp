#include "SourceDataModel.h"

using recombinant::api::Entity;

SourceDataModel::SourceDataModel(recombinant::api::Source* source_)
    : source(source_)
{}

bool SourceDataModel::IsContainer(const wxDataViewItem& wxItem) const
{
    if (!wxItem.IsOk())
    {
        // The "fake root" node actually owns our root node, so it's a
        // container!
        return true;
    }

    Entity& item = *reinterpret_cast<Entity*>(wxItem.GetID());
    return !item.children.empty();
}

wxDataViewItem SourceDataModel::GetParent(const wxDataViewItem& wxItem) const
{
    if (!wxItem.IsOk())
    {
        return wxDataViewItem(nullptr);
    }

    return wxDataViewItem(reinterpret_cast<Entity*>(wxItem.GetID())->parent);
}

unsigned int SourceDataModel::GetChildren(
    const wxDataViewItem& wxItem, wxDataViewItemArray& children) const
{
    if (!wxItem.IsOk())
    {
        // The root node owns a single item: our true root
        children.Add(wxDataViewItem(source->root.get()));
        return 1;
    }

    Entity& item = *reinterpret_cast<Entity*>(wxItem.GetID());
    children.Alloc(item.children.size());
    for (auto& child : item.children)
    {
        children.Add(wxDataViewItem(child.get()));
    }
    return static_cast<unsigned int>(item.children.size());
}

unsigned int SourceDataModel::GetColumnCount() const
{
    return 1;
}

wxString SourceDataModel::GetColumnType(unsigned int) const
{
    return "string";
}

void SourceDataModel::GetValue(
    wxVariant& val, const wxDataViewItem& wxItem, unsigned int) const
{
    if (!wxItem.IsOk())
    {
        char* root_name = "Root";
        val.Convert(root_name);
        return;
    }

    Entity& item = *reinterpret_cast<Entity*>(wxItem.GetID());
    wxString str   = item.name.c_str();
    val            = str;
}

bool SourceDataModel::SetValue(
    const wxVariant&, const wxDataViewItem&, unsigned int)
{
    return false;
}
