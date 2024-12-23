#pragma once

#include <iostream>
#include <windows.h>

#define ASSERT(cond)					if(!(cond)) shared_assert(__FILE__, __LINE__, #cond);
#define ASSERT_MSG_VA(cond, msg, ...)	if(!(cond)) shared_assert(__FILE__, __LINE__, "%s\n\n" msg, #cond, ##__VA_ARGS__);
#define ASSERT_MSG(cond, msg)			ASSERT_MSG_VA(cond, msg);

typedef void __cdecl Dvar_SetBool_t(dvar_s* dvar, bool value);
static Dvar_SetBool_t* Dvar_SetBool = (Dvar_SetBool_t*)0x004B0C10;

static void shared_assert(const char* File, int Line, const char* Format, ...)
{
	char buffer[4096];
	char message[4096];

	va_list ap;
	va_start(ap, Format);

	_vsnprintf_s(buffer, _TRUNCATE, Format, ap);
	sprintf_s(message, "%s(%d):\n\n%s", File, Line, buffer);

	MessageBoxA(nullptr, message, "ASSERTION", MB_ICONERROR);

	if (IsDebuggerPresent())
		__debugbreak();

	ExitProcess(1);
}