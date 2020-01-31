#include "TreeWindow.h"

#include "strings.h"

#include "../api/LocalFileSource.h"

TreeWindow::TreeWindow(wxWindow* parent, wxWindowID id)
    : wxWindow(parent, id)
{
    dataView = new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition,
        wxSize(300, 200), wxDV_MULTIPLE | wxDV_ROW_LINES);

    // Create and associate data model with data view
    source    = new recombinant::api::LocalFileSource(".");
    dataModel = new SourceDataModel(source);
    dataView->AssociateModel(dataModel);
    dataView->AppendTextColumn("Name", 0);

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
