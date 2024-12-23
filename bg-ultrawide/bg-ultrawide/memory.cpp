#include "pch.h"

#include "memory.hpp"

namespace memory {
	void PatchMemory(ULONG_PTR Address, PBYTE Data, SIZE_T Size)
	{
		DWORD d = 0;
		VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &d);

		for (SIZE_T i = 0; i < Size; i++)
			*(volatile BYTE*)(Address + i) = *Data++;

		VirtualProtect((LPVOID)Address, Size, d, &d);

		FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
	}

	void FixupFunction(ULONG_PTR Address, ULONG_PTR DestAddress)
	{
		DWORD data = (DestAddress - Address - 5);
		PatchMemory(Address + 0, (PBYTE)"\xE9", 1);
		PatchMemory(Address + 1, (PBYTE)&data, 4);
	}
}