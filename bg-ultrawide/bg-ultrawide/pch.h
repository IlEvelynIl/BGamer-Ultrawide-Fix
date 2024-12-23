// pch.h: This is a precompiled header file
#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "structs.h"
#include "functions.h"

#pragma comment(lib, "detours.lib")
#include "Detours.h"

#include "include/d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

#endif //PCH_H