#include <iostream>
#include <windows.h>
#include <psapi.h>
#include "memory.cpp"

DWORD GetProcessIDByName(const std::wstring& processName) {
    DWORD processIDs[1024];
    DWORD bytesReturned;

    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned))
        return 0;

    DWORD processCount = bytesReturned / sizeof(DWORD);
    for (DWORD i = 0; i < processCount; ++i) {
        if (processIDs[i] != 0) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIDs[i]);
            if (hProcess) {
                wchar_t processBuffer[MAX_PATH];
                if (GetModuleBaseName(hProcess, NULL, processBuffer, sizeof(processBuffer) / sizeof(wchar_t))) {
                    if (processName.compare(processBuffer) == 0) {
                        CloseHandle(hProcess);
                        return processIDs[i];
                    }
                }
                CloseHandle(hProcess);
            }
        }
    }

    return 0;
}

uintptr_t GetBaseAddress(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (!hProcess) {
        return 0;
    }

    HMODULE hModules[1024];
    DWORD bytesReturned;
    if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &bytesReturned)) {
        MODULEINFO moduleInfo;
        if (GetModuleInformation(hProcess, hModules[0], &moduleInfo, sizeof(moduleInfo))) {
            CloseHandle(hProcess);
            return reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
        }
    }

    CloseHandle(hProcess);
    return 0;
}

int main() {
    std::wstring sensorsApp = L"sensors.exe";
    DWORD sensorsAppid = GetProcessIDByName(sensorsApp);

    if (sensorsAppid == 0) {
        std::cerr << "Failed to find the sensors application." << std::endl;
        return 1;
    }

    MemoryEditor<double> memoryEditor(sensorsAppid);

    if (!memoryEditor.OpenProcess()) {
        std::cerr << "Failed to open the sensors application. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    uintptr_t baseAddress = GetBaseAddress(sensorsAppid);

    if (baseAddress == 0) {
        std::cerr << "Failed to get the base address." << std::endl;
        memoryEditor.CloseProcess();
        return 1;
    }

    std::cout << "Base Address: " << std::hex << baseAddress << std::endl;

    uintptr_t temperatureOffset = 0x11104;
    uintptr_t humidityOffset = 0x11221;

    
    double temperatureValue = 0.0;
    double humidityValue = 0.0;

    
    uintptr_t temperatureAddress = baseAddress + temperatureOffset;
    if (!memoryEditor.ReadMemory(temperatureAddress, temperatureValue)) {
        std::cerr << "Failed to read temperature sensor value." << std::endl;
    }

   
    uintptr_t humidityAddress = baseAddress + humidityOffset;
    if (!memoryEditor.ReadMemory(humidityAddress, humidityValue)) {
        std::cerr << "Failed to read humidity sensor value." << std::endl;
    }

    
    memoryEditor.CloseProcess();

    
    std::cout << "Temperature: " << temperatureValue << std::endl;
    std::cout << "Humidity: " << humidityValue << std::endl;
    return 0;
}