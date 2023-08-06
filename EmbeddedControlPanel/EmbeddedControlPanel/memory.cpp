#include "memory.h"

template <typename T>
MemoryEditor<T>::MemoryEditor(DWORD procId) : procId(procId), hProcess(NULL) {}

template <typename T>
bool MemoryEditor<T>::OpenProcess() {
	hProcess = ::OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, procId);
	return (hProcess != NULL);
}

template <typename T>
void MemoryEditor<T>::CloseProcess() {
	if (!hProcess) {
		::CloseHandle(hProcess);
		hProcess = NULL;
	}
}

template <typename T>
template <typename U>
bool MemoryEditor<T>::ReadMemory(uintptr_t address, U& value) const {
	if (!hProcess) return false;

	SIZE_T bytesRead;
	if (::ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), &value, sizeof(U), &bytesRead)) {
		return (bytesRead == sizeof(U));
	}

	return false;
}

template <typename T>
template <typename U>
bool MemoryEditor<T>::WriteMemory(uintptr_t address, const U& value) const {
	if (!hProcess) return false;

	SIZE_T bytesWritten;
	if (::WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), &value, sizeof(U), &bytesWritten)) {
		return (bytesWritten == sizeof(U));
	}

	return false;
}

template <typename T>
template <typename U>
bool MemoryEditor<T>::EditMemory(uintptr_t address, const U& value) const {
	if (!hProcess) return false;

	T originalValue;
	if (!ReadMemory(address, originalValue)) {
		return false;
	}

	T newValue = static_cast<T>(originalValue + value);
	return WriteMemory(address, newValue);
}

template class MemoryEditor<double>;
template class MemoryEditor<float>;
template class MemoryEditor<int>;