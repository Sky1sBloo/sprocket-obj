#include "ImporterFrame.hpp"
#include <wx/app.h>

class SprocketImporterGUI : public wxApp {
public:
    bool OnInit() override
    {
        ImporterFrame* frame = new ImporterFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(SprocketImporterGUI);
