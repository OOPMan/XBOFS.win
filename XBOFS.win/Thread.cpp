#include "Thread.h"

using namespace XBOFSWin;

std::string threadMessageToString(THREAD_MESSAGES threadMessage)
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

Thread::Thread(std::string identifier, std::shared_ptr<spdlog::logger> logger, DWORD parentThreadId, DWORD uiManagerThreadId)
: identifier(identifier), logger(logger), parentThreadId(parentThreadId), uiManagerThreadId(uiManagerThreadId)
{       
    this->logger->info("Starting thread for {}", this->identifier);    
    this->threadHandle = CreateThread(NULL, 0, startThread, (LPVOID)this, 0, &this->threadId);
}

Thread::~Thread()
{    
    this->logger->info("Stopping thread for {}", this->identifier);
    PostThreadMessage(this->threadId, RAWUVEF_STOP, NULL, NULL);
    while (WaitForSingleObject(this->threadHandle, INFINITE) != WAIT_OBJECT_0);
    CloseHandle(this->threadHandle);
    this->notifyUIManager(RAWUVEF_STOPPED, NULL);
    this->logger->info("Stopped thread for {}", this->identifier);
}

DWORD Thread::getThreadId() {
    return this->threadId;
}

DWORD Thread::getParentThreadId() {
    return this->parentThreadId;
}

DWORD Thread::getUiManagerThreadId() {
    return this->uiManagerThreadId;
}

DWORD Thread::startThread(LPVOID data) {    
    Thread* thread = (Thread*)data;    
    MSG threadMessage;
    PeekMessage(&threadMessage, NULL, WM_USER, WM_USER, PM_NOREMOVE);    
    return thread->run();
}

BOOL Thread::notifyUIManager(UINT messageValue, LPARAM lParam) {
    return PostThreadMessage(this->uiManagerThreadId, messageValue, this->threadId, lParam);
}
