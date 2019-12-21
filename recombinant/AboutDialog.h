#pragma once

#include "wx_headers.h"
#include <string>

class AboutDialog : public wxDialog
{
    public:
    AboutDialog(wxWindow* parent);

    private:
    std::string versionText;

};
