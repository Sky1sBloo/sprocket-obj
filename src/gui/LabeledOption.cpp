#include "LabeledOption.hpp"
#include "wx/sizer.h"
#include <wx/wx.h>

LabeledOption::LabeledOption(wxWindow* parent, wxWindowID id, const wxString& dialog, wxWindow* item)
    : wxBoxSizer(wxHORIZONTAL)
{
    wxStaticText* label = new wxStaticText(parent, id, dialog);
    this->Add(label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    this->Add(item, 0, wxALIGN_CENTER | wxBOTTOM, 5);
}
