#pragma once


#include <iostream>
#include <windows.h>

template <typename T>
class MemoryEditor {
public:
    MemoryEditor(DWORD procId);
    bool OpenProcess();
    void CloseProcess();

    template <typename U = T>
    bool ReadMemory(uintptr_t address, U& value) const;

    template <typename U = T>
    bool WriteMemory(uintptr_t address, const U& value) const;

    template <typename U>
    bool EditMemory(uintptr_t address, const U& value) const;

    DWORD procId;
    HANDLE hProcess;
};
