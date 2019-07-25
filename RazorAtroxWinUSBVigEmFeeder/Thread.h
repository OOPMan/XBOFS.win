#pragma once
#include "pch.h"

class Thread
{
public:
    Thread() = delete;
    Thread(std::string identifier, std::string loggerName, DWORD parentThreadId, DWORD uiManagerThreadId);
    ~Thread();

    virtual DWORD run() = 0;
    DWORD getThreadId();
    DWORD getParentThreadId();
    DWORD getUiManagerThreadId();

protected:
    const std::string identifier;
    const DWORD parentThreadId;
    const DWORD uiManagerThreadId;    
    
    el::Logger* logger;
    DWORD threadId = 0;
    HANDLE threadHandle = NULL;

    static DWORD startThread(LPVOID data);
};

