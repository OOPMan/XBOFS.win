#include "Thread.h"

Thread::Thread(std::string identifier, std::string loggerName, DWORD parentThreadId, DWORD uiManagerThreadId)
: identifier(identifier), logger(el::Loggers::getLogger(loggerName)), parentThreadId(parentThreadId), uiManagerThreadId(uiManagerThreadId)
{       
    this->logger->info("Starting thread for %v", this->identifier);    
    this->threadHandle = CreateThread(NULL, 0, startThread, (LPVOID)this, 0, &this->threadId);
}

Thread::~Thread()
{    
    this->logger->info("Stopping thread for %v", this->identifier);
    PostThreadMessage(this->threadId, RAWUVEF_STOP, NULL, NULL);
    while (WaitForSingleObject(this->threadHandle, 10) != WAIT_OBJECT_0) {};
    CloseHandle(this->threadHandle);
    this->logger->info("Stopped thread for %v", this->identifier);
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
