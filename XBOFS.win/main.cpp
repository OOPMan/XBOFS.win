#include "pch.h"
#include "PDCursesUIManager.h"

#include <memory>
#include <stdio.h>
#include <curses.h>
#include <ViGEm/Client.h>

INITIALIZE_EASYLOGGINGPP

LONG __cdecl _tmain(LONG Argc, LPTSTR *Argv) {  
    el::Configurations conf("easyloggingpp.conf");
    el::Loggers::setDefaultConfigurations(conf, true);    
    el::Logger* logger  = el::Loggers::getLogger("RazerAtroxWinUSBVigEmFeeder");
    DWORD threadId      = GetCurrentThreadId();
    logger->info("Application start-up. Press enter to exit");    
    std::unique_ptr<PDCursesUIManager> manager(new PDCursesUIManager(threadId));
    manager->wait();
    logger->info("Application shut-down");        
}
