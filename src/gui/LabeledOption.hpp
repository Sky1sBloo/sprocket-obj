#pragma once

#include <wx/sizer.h>
#include <wx/string.h>

class LabeledOption : public wxBoxSizer {
public:
    LabeledOption(wxWindow* parent, wxWindowID id, const wxString& dialog, wxWindow* item);
};
