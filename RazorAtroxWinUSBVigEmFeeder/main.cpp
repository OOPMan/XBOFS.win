#include "pch.h"

#include <stdio.h>
#include <curses.h>
#include <ViGEm/Client.h>

enum STATUS {
    DISCONNECTED,
    INIT,
    CONNECTED
};

char* statusToString(STATUS status) {
    switch (status) {
    case DISCONNECTED: return "DISCONNECTED";
    case INIT: return "INIT";
    case CONNECTED: return "CONNECTED";
    }
    return "UNKNOWN";
}

void renderUI(STATUS winUsbStatus, STATUS vigEmStatus) {
    erase();
    mvprintw(0, 0, "Razer Atrox WinUSB VigEm Feeder");
    mvprintw(2, 0, "WinUSB Status: %s", statusToString(winUsbStatus));
    mvprintw(3, 0, "VigEm Status: %s", statusToString(vigEmStatus));
    mvprintw(5, 0, "Press:");
    mvprintw(6, 0, "* W to reset WinUSB connection to Razer Atrox");
    mvprintw(7, 0, "* V to reset VigEm XB360 controller");
    mvprintw(8, 0, "* Q to exit");
    refresh();
}

LONG __cdecl _tmain(LONG Argc, LPTSTR *Argv) {
    // Variables
    WINDOW *window;
    STATUS winUsbStatus = DISCONNECTED;
    STATUS vigEmStatus = DISCONNECTED;

    // Init
    window = initscr();
    nodelay(window, TRUE);
    noecho();

    // Main loop
    while (true) {
        renderUI(winUsbStatus, vigEmStatus);
        auto key = getch();
        if (key == 'Q' || key == 'q') break;
    }
    
    endwin();
}
