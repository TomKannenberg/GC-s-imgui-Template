#include "gcgui.hpp"

//  uncomment to hide console
 #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {

    // Logo.png should ideally be 40x40, can ofc be changed in gcGui::FrontEnd() logosize

    bool done = false;
    gcGui gcg = gcGui("Program Name v", "1.2", &done);

    MSG msg;
    while (!done) {
        GetMessageW(&msg, nullptr, 0, 0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        gcg.Render();
        
    }

    exit(1);
}