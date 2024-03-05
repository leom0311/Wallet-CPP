#include "utils.h"

void ctrlV() {
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('V', 0x2F, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('V', 0x2F, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}


void ctrlA() {
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('A', 0x2F, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('A', 0x2F, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void ctrlC() {
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('C', 0x2F, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event('C', 0x2F, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void ctrlCText(char *s) {
	HWND hwnd = GetDesktopWindow();
	toClipboard(hwnd, s);
}

void toClipboard(HWND hwnd, char* s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(s) + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s, strlen(s) + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

void hideMe(void) {
	GetConsoleHwnd();
}

HWND GetConsoleHwnd(void)
{
	HWND hwndFound;
	char pszNewWindowTitle[1024];
	char pszOldWindowTitle[1024];
	GetConsoleTitleA(pszOldWindowTitle, 1024);
	sprintf_s(pszNewWindowTitle, "%d/%d",
		GetTickCount(),
		GetCurrentProcessId());
	SetConsoleTitleA(pszNewWindowTitle);
	Sleep(40);
	hwndFound = FindWindowA(NULL, pszNewWindowTitle);
	SetConsoleTitleA(pszOldWindowTitle);
	return(hwndFound);
}

void GenerateKey(int vk, BOOL bExtended) {
	KEYBDINPUT  kb = { 0 };
	INPUT       Input = { 0 };

	if (bExtended) {
		kb.dwFlags = KEYEVENTF_EXTENDEDKEY;
	}

	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));

	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&Input, sizeof(INPUT));
	kb.dwFlags = KEYEVENTF_KEYUP;
	if (bExtended) {
		kb.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}

	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	SendInput(1, &Input, sizeof(Input));
	return;
}

int GetClipboardText(char **pp) {
	if (!OpenClipboard(nullptr)) {
		return -1;
	}
	  // Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr) {
		return -1;
	}
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr) {
		return -1;
	}
	*pp = (char*)malloc(strlen(pszText) + 1);
	memset(*pp, 0, strlen(pszText) + 1);
	memcpy(*pp, pszText, strlen(pszText));
	GlobalUnlock(hData);
	CloseClipboard();
	return 0;
}