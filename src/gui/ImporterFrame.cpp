#include "ImporterFrame.hpp"
#include "Mesh.hpp"
#include "MeshToBlueprint.hpp"
#include "ObjReader.hpp"
#include <wx/wx.h>

#include "LabeledOption.hpp"

ImporterFrame::ImporterFrame()
    : wxFrame(nullptr, wxID_ANY, "Sprocket Obj Importer")
{
    wxFilePickerCtrl* filePicker = new wxFilePickerCtrl(
        this,
        wxID_ANY,
        wxEmptyString,
        "Select a file",
        "*.obj");
    LabeledOption* filePickerSizer = new LabeledOption(this, wxID_ANY, "Obj File: ", filePicker);

    wxDirPickerCtrl* outputDirPicker = new wxDirPickerCtrl(
        this,
        wxID_ANY,
        wxEmptyString,
        "Select the output directory");
    LabeledOption* outputPickerSizer = new LabeledOption(this, wxID_ANY, "Output Directory: ", outputDirPicker);

    wxTextCtrl* textCtrl = new wxTextCtrl(
        this,
        wxID_ANY);
    LabeledOption* textCtrlSizer = new LabeledOption(this, wxID_ANY, "Model name: ", textCtrl);

    wxBoxSizer* layout = new wxBoxSizer(wxVERTICAL);
    wxButton* importButton = new wxButton(
        this,
        wxID_ANY,
        "Import");

    layout->Add(filePickerSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(outputPickerSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(textCtrlSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(importButton, 0, wxALIGN_CENTER);
    this->SetSizerAndFit(layout);

    importButton->Bind(wxEVT_BUTTON, &ImporterFrame::import, this);
    filePicker->Bind(wxEVT_FILEPICKER_CHANGED, &ImporterFrame::setFileDir, this);
    outputDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &ImporterFrame::setOutputDir, this);
}

void ImporterFrame::import(wxCommandEvent& event)
{
    try {
        SprObj::Mesh mesh = readObj(mFileDir);
        if (!mModelName.empty()) {
            mesh.name = mModelName;
        }
        meshToBlueprint(mesh, mOutputDir);
        std::string logStr = "Successfully imported " + mesh.name;
        wxLogMessage(logStr.c_str());

    } catch (const std::runtime_error& ex) {
        wxLogMessage(ex.what());
    }
}

void ImporterFrame::setFileDir(wxFileDirPickerEvent& event)
{
    mFileDir = event.GetPath().c_str();
}

void ImporterFrame::setOutputDir(wxFileDirPickerEvent& event)
{
    mOutputDir = event.GetPath().c_str();
}
