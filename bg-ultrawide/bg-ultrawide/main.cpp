#include "pch.h"

void __cdecl R_StoreWindowSettings(GfxWindowParms* wndParms)
{
	ASSERT(r_aspectRatio);

	vidConfig.sceneWidth = wndParms->sceneWidth;
	vidConfig.sceneHeight = wndParms->sceneHeight;
	vidConfig.displayWidth = wndParms->displayWidth;
	vidConfig.displayHeight = wndParms->displayHeight;
	vidConfig.displayFrequency = wndParms->hz;
	vidConfig.isFullscreen = wndParms->fullscreen;

	switch (r_aspectRatio->current.integer)
	{
	case ASPECT_RATIO_AUTO:
	{
		int monitorWidth = vidConfig.displayWidth;
		int monitorHeight = vidConfig.displayHeight;

		if (vidConfig.isFullscreen && dx.adapterNativeIsValid)
		{
			monitorWidth = dx.adapterNativeWidth;
			monitorHeight = dx.adapterNativeHeight;
		}

#if _USE_LEGACY_ASPECT_RATIO_MODE
		// Calculate the height part of the aspect ratio and
		//  set the window's aspect ratio based on that
		int r = (int)(((float)monitorHeight * 16.0f) / (float)monitorWidth);
		if (r == 10)
			vidConfig.aspectRatioWindow = ASPECT_RATIO(16, 10);
		else if (r >= 10)
			vidConfig.aspectRatioWindow = ASPECT_RATIO(4, 3);
		else
			vidConfig.aspectRatioWindow = ASPECT_RATIO(16, 9);
#else
		vidConfig.aspectRatioWindow = (float)monitorWidth / (float)monitorHeight;
#endif

		break;
	}

	case ASPECT_RATIO_STANDARD:
		vidConfig.aspectRatioWindow = ASPECT_RATIO(4, 3);
		break;

	case ASPECT_RATIO_16_9:
		vidConfig.aspectRatioWindow = ASPECT_RATIO(16, 9);
		break;

	case ASPECT_RATIO_16_10:
		vidConfig.aspectRatioWindow = ASPECT_RATIO(16, 10);
		break;

	default:
		ASSERT_MSG_VA(false, "unhandled case, aspectRatio = %i\n", r_aspectRatio->current.integer);
		break;
	}

	ASSERT(com_wideScreen);

	bool isWidescreen = (vidConfig.aspectRatioWindow != ASPECT_RATIO(4, 3));
	Dvar_SetBool(com_wideScreen, isWidescreen);

	vidConfig.aspectRatioScenePixel = (float)vidConfig.sceneHeight * vidConfig.aspectRatioWindow / (float)vidConfig.sceneWidth;
	if (vidConfig.isFullscreen)
		vidConfig.aspectRatioDisplayPixel = ((float)dx.adapterFullscreenHeight * vidConfig.aspectRatioWindow) / (float)dx.adapterFullscreenWidth;
	else
		vidConfig.aspectRatioDisplayPixel = 1.0f;

	vidConfig.isToolMode = r_reflectionProbeGenerate && r_reflectionProbeGenerate->current.enabled;
}

void __declspec(naked) hk_R_StoreWindowSettings(void)
{
	_asm
	{
		push eax // wndParams
		call R_StoreWindowSettings
		pop eax
		retn
	}
}

extern "C" __declspec(dllexport) int Patchbgt5external(int game) {
    Detours::X86::DetourFunction((uintptr_t)0x006B68D0, (uintptr_t)&hk_R_StoreWindowSettings);
    return 1;
}