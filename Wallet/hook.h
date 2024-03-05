#pragma once

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <shlobj.h>

#include <filesystem>


LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam);
int shift_active();
int capital_active();
