#include "TreeWindow.h"

#include "strings.h"

TreeWindow::TreeWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    dataView = new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition,
        wxDefaultSize, wxDV_MULTIPLE | wxDV_ROW_LINES);

    // Create and associate data model with data view
    dataModel = new FilesDataModel();
    dataView->AssociateModel(dataModel);
    dataView->AppendTextColumn("Test!", 0);

    loadDataControl = new wxStaticText(
        this, wxID_ANY, localizedString(StringID::AddDataSources));
    sizer = new wxGridSizer(1, 1, 10, 10);
    //sizer->Add(loadDataControl, 0, wxALIGN_CENTER);
    sizer->Add(dataView, wxSizerFlags().Center());
    SetSizerAndFit(sizer);
}

TreeWindow::~TreeWindow()
{
    // Allow the data model to be destroyed
    dataModel->DecRef();
}

void TreeWindow::OnPaint(wxPaintEvent&)
{}
