#pragma once

#include "wx/event.h"
#include <wx/filepicker.h>
#include <wx/frame.h>

class ImporterFrame : public wxFrame {
public:
    ImporterFrame();

private:
    std::string mFileDir;
    std::string mOutputDir;

    void import(wxCommandEvent& event);

    void setFileDir(wxFileDirPickerEvent& event);
    void setOutputDir(wxFileDirPickerEvent& event);
};
