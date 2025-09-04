#include "ImporterFrame.hpp"
#include "Mesh.hpp"
#include "MeshToBlueprint.hpp"
#include "ObjReader.hpp"
#include <stdexcept>
#include <wx/wx.h>

#include "LabeledOption.hpp"
#include "wx/event.h"
#include "wx/gtk/textctrl.h"
#include "wx/log.h"

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

    mModelText = new wxTextCtrl(
        this,
        wxID_ANY);
    LabeledOption* modelNameSizer = new LabeledOption(this, wxID_ANY, "Model name: ", mModelText);

    mThicknessText = new wxTextCtrl(
        this,
        wxID_ANY,
        "5");
    LabeledOption* thicknessTextSizer = new LabeledOption(this, wxID_ANY, "Thickness (mm): ", mThicknessText);

    wxBoxSizer* layout = new wxBoxSizer(wxVERTICAL);
    wxButton* importButton = new wxButton(
        this,
        wxID_ANY,
        "Import");

    layout->Add(filePickerSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(outputPickerSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(modelNameSizer, 0, wxLEFT | wxRIGHT, 5);
    layout->Add(thicknessTextSizer, 0, wxLEFT | wxRIGHT, 5);
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
        if (!mModelText->GetValue().empty()) {
            mesh.name = mModelText->GetValue().ToStdString();
        }
        int thickness = 5;
        if (!mThicknessText->GetValue().empty()) {
            thickness = std::stoi(mThicknessText->GetValue().ToStdString());
        }
        mesh.thickness = thickness;
        meshToBlueprint(mesh, mOutputDir);
        std::string logStr = "Successfully imported " + mesh.name;
        wxLogMessage(logStr.c_str());

    } catch (const std::invalid_argument& ex) {
        wxLogMessage("Thickness value is not an integer");
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
