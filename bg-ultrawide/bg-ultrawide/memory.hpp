#include "pch.h"

namespace memory {
	void PatchMemory(ULONG_PTR Address, PBYTE Data, SIZE_T Size);
	void FixupFunction(ULONG_PTR Address, ULONG_PTR DestAddress);
}