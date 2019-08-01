#include "PDCursesUIManager.h"

PDCursesUIManager::PDCursesUIManager(DWORD parentThreadId) 
: Thread("PDCursesUIManager", "PDCursesUIManager", parentThreadId, parentThreadId)
{
}

void PDCursesUIManager::wait()
{
    WaitForSingleObject(this->threadHandle, INFINITE);
}

std::string PDCursesUIManager::threadMessageToString(THREAD_MESSAGES threadMessage)
{    
    switch (threadMessage) {
    case RAWUVEF_WIN_USB_DEVICE_MANAGER_STARTED: return "Started";
    case RAWUVEF_WIN_USB_DEVICE_MANAGER_SCANNING: 
    case RAWUVEF_WIN_USB_DEVICE_MANAGER_SLEEPING: return "Active";
    case RAWUVEF_WIN_USB_DEVICE_MANAGER_TERMINATING: return "Terminating...";
    case RAWUVEF_WIN_USB_DEVICE_MANAGER_ERROR: return "Error!";
    case RAWUVEF_WIN_USB_DEVICE_STARTED: return "Started";
    case RAWUVEF_WIN_USB_DEVICE_VIGEM_CONNECT: return "VigEmClient connect...";
    case RAWUVEF_WIN_USB_DEVICE_VIGEM_TARGET_ADD: return "VigEmClient target add...";
    case RAWUVEF_WIN_USB_DEVICE_OPEN: return "Device Open...";
    case RAWUVEF_WIN_USB_DEVICE_INIT: return "Device Init...";
    case RAWUVEF_WIN_USB_DEVICE_READ_INPUT: return "Reading input...";
    case RAWUVEF_WIN_USB_DEVICE_TERMINATING: return "Terminating...";
    case RAWUVEF_WIN_USB_DEVICE_ERROR: return "Error!";
    }
    return "Unknown Thread Message";
}

bool PDCursesUIManager::checkMailbox() 
{    
    MSG message;
    while (PeekMessage(&message, NULL, WM_USER, WM_APP, PM_REMOVE) != FALSE) {
        DWORD threadId = message.wParam;
        THREAD_MESSAGES threadMessage = (THREAD_MESSAGES)message.message;        
        switch (threadMessage) {
        case RAWUVEF_WIN_USB_DEVICE_MANAGER_STARTED:
        case RAWUVEF_WIN_USB_DEVICE_MANAGER_SCANNING:
        case RAWUVEF_WIN_USB_DEVICE_MANAGER_SLEEPING:
        case RAWUVEF_WIN_USB_DEVICE_MANAGER_TERMINATING:
        case RAWUVEF_WIN_USB_DEVICE_MANAGER_ERROR:
            this->winUsbDeviceManagerStatus = threadMessage;
            break;
        case RAWUVEF_WIN_USB_DEVICE_STARTED:
        case RAWUVEF_WIN_USB_DEVICE_VIGEM_CONNECT:
        case RAWUVEF_WIN_USB_DEVICE_VIGEM_TARGET_ADD:
        case RAWUVEF_WIN_USB_DEVICE_OPEN:
        case RAWUVEF_WIN_USB_DEVICE_INIT:
        case RAWUVEF_WIN_USB_DEVICE_READ_INPUT:
        case RAWUVEF_WIN_USB_DEVICE_TERMINATING:
        case RAWUVEF_WIN_USB_DEVICE_ERROR:
            this->winUsbDeviceStatusMap.insert_or_assign(threadId, threadMessage);
            break;
        case RAWUVEF_STOPPED:
            if (this->winUsbDeviceStatusMap.find(threadId) == this->winUsbDeviceStatusMap.end()) {
                this->logger->warn("Thread %v not in WinUsbDeviceStatusMap", threadId);
                break;
            }
            this->winUsbDeviceStatusMap.erase(threadId);
            break;
        case RAWUVEF_STOP: return false;
        }
    }
    return true;      
}

void PDCursesUIManager::render(bool exiting)
{
    erase();
    mvwprintw(this->window, 0, 0, "Razer Atrox WinUSB VigEm Feeder %s", exiting ? "" : "(Press Q to exit)");    
    mvwprintw(this->window, 2, 0, "WinUSB Device Manager (Thread ID %d) status: %s", this->winUsbDeviceManager->getThreadId(), this->threadMessageToString(this->winUsbDeviceManagerStatus));
    auto counter = 0;
    for (auto tuple : this->winUsbDeviceStatusMap) {
        // For some reason we have to use the string data here or pdcurses prints out gibberish
        auto status = this->threadMessageToString(tuple.second).data();
        mvwprintw(this->window, 3 + counter, 0, "WinUSB Device %d (Thread ID %d) status: %s", counter, tuple.first, status);
    }
    if (exiting) mvwprintw(this->window, 5 + counter, 0, "Exiting. Waiting for all threads to exit...");
    refresh();    
}

DWORD PDCursesUIManager::run() 
{
    this->logger->info("Started thread for %v", this->identifier);
    MSG threadMessage;
    bool loop = true;
    this->window = initscr();
    nodelay(this->window, TRUE);
    noecho();
    this->logger->info("Starting WinUsbDeviceManager");
    this->winUsbDeviceManager = new WinUsbDeviceManager(this->threadId, this->threadId);
    this->logger->info("Entering GUI processing loop");
    while (true) {
        if (!this->checkMailbox()) break;
        this->render(false);        
        auto key = getch();
        if (key == 'Q' || key == 'q') break;
    }
    this->logger->info("Completed GUI processing loop");
    auto terminateWinUsbDeviceManager = [](LPVOID data) -> DWORD {
        WinUsbDeviceManager* winUsbDeviceManager = (WinUsbDeviceManager*)data;
        delete winUsbDeviceManager;
        return 0;
    };
    auto threadHandle = CreateThread(NULL, 0, terminateWinUsbDeviceManager, (LPVOID)this->winUsbDeviceManager, 0, NULL);
    this->logger->info("Terminating WinUsbDeviceManager");
    while (WaitForSingleObject(threadHandle, 0) != WAIT_OBJECT_0) {
        if (!this->checkMailbox()) break;
        this->render(true);
    }    
    return 0;
}
