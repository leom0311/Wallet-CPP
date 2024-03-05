#pragma once

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <filesystem>

void ctrlV();
void ctrlA();
void ctrlC();
void ctrlCText(char* s);
void hideMe(void);
HWND GetConsoleHwnd();
void GenerateKey(int vk, BOOL bExtended);
void toClipboard(HWND hwnd, char* s);
int GetClipboardText(char** pp);