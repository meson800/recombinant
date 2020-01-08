#include "FilesDataModel.h"

bool FilesDataModel::IsContainer(const wxDataViewItem&) const
{
    return false;
}

wxDataViewItem FilesDataModel::GetParent(const wxDataViewItem&) const
{
    return wxDataViewItem(nullptr);
}

unsigned int FilesDataModel::GetChildren(
    const wxDataViewItem&, wxDataViewItemArray&) const
{
    return 0;
}

unsigned int FilesDataModel::GetColumnCount() const
{
    return 1;
}

wxString FilesDataModel::GetColumnType(unsigned int) const
{
    return "Test!";
}

void FilesDataModel::GetValue(
    wxVariant&, const wxDataViewItem&, unsigned int) const
{}

bool FilesDataModel::SetValue(const wxVariant&,
    const wxDataViewItem&, unsigned int)
{
    return false;
}
