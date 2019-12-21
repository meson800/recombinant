#include "AboutDialog.h"

#include <algorithm>

#include "strings.h"
#include "version.h"

AboutDialog::AboutDialog(wxWindow* parent)
    : wxDialog(
        parent,
        wxID_ANY,
        localizedString(StringID::AboutDialogTitle),
        wxDefaultPosition)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Setup version information
    versionText =
        std::string(localizedString(StringID::BuildInformation))
        + VERSION_STRING;
    versionText
        .erase(std::remove(versionText.begin(), versionText.end(), '\n'),
            versionText.end());

    mainSizer->Add(new wxStaticText(this, wxID_ANY, versionText.c_str()),
        0, wxALL, 10);

    wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition,
        wxSize(400,300));
    notebook->AddPage(new wxTextCtrl
        (notebook, wxID_ANY,
            LICENSE_STRING,wxDefaultPosition,
            wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY),
        localizedString(StringID::License));
    notebook->AddPage(new wxTextCtrl
        (notebook, wxID_ANY,
            AUTHORS_STRING, wxDefaultPosition,
            wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY),
        localizedString(StringID::Authors));
    mainSizer->Add(notebook,
        wxSizerFlags(0).Expand().Border(wxALL, 10));


    SetSizerAndFit(mainSizer);

}

