#pragma once

#define VANILLA_DVAR(NAME, ADDRESS) static dvar_s*& NAME = *(dvar_s **)ADDRESS;
#define VANILLA_VALUE(NAME, TYPE, ADDRESS) static TYPE& NAME = *(TYPE*)ADDRESS;

#define STATIC_ASSERT_SIZE(struct, size)				static_assert(sizeof(struct) == size, "Size check")
#define STATIC_ASSERT_OFFSET(struct, member, offset)	static_assert(offsetof(struct, member) == offset, "Offset check")

#define DVAR_NOFLAG				0				// 0x0000
#define DVAR_ARCHIVE            (1 << 0)        // 0x0001
#define DVAR_USERINFO           (1 << 1)        // 0x0002
#define DVAR_SERVERINFO         (1 << 2)        // 0x0004
#define DVAR_SYSTEMINFO         (1 << 3)        // 0x0008
#define DVAR_INIT               (1 << 4)        // 0x0010
#define DVAR_LATCH              (1 << 5)        // 0x0020
#define DVAR_ROM                (1 << 6)        // 0x0040
#define DVAR_CHEAT              (1 << 7)        // 0x0080
#define DVAR_DEVELOPER          (1 << 8)        // 0x0100
#define DVAR_SAVED              (1 << 9)        // 0x0200
#define DVAR_NORESTART          (1 << 10)       // 0x0400
#define DVAR_CHANGEABLE_RESET   (1 << 12)       // 0x1000
#define DVAR_EXTERNAL           (1 << 14)       // 0x4000
#define DVAR_AUTOEXEC           (1 << 15)       // 0x8000
#define DVAR_UNRESTRICTED		(1 << 16)		// 0x10000

enum dvarType_t
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_ENUM = 0x6,
	DVAR_TYPE_STRING = 0x7,
	DVAR_TYPE_COLOR = 0x8,
	DVAR_TYPE_INT64 = 0x9,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xA,
	DVAR_TYPE_COLOR_XYZ = 0xB,
	DVAR_TYPE_COUNT = 0xC,
};

enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL = 0x0,
	DVAR_SOURCE_EXTERNAL = 0x1,
	DVAR_SOURCE_SCRIPT = 0x2,
	DVAR_SOURCE_DEVGUI = 0x3,
};

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	__int64 integer64;
	unsigned __int64 unsignedInt64;
	float value;
	float vector[4];
	const char* string;
	char color[4];
};

union DvarLimits
{
	struct
	{
		int stringCount;
		const char** strings;
	} enumeration;

	struct
	{
		int min;
		int max;
	} integer;

	struct
	{
		__int64 min;
		__int64 max;
	} integer64;

	struct
	{
		float min;
		float max;
	} value;

	struct
	{
		float min;
		float max;
	} vector;
};

struct dvar_s
{
	const char* name;
	const char* description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	bool loadedFromSaveGame;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarValue saved;
	DvarLimits domain;
	dvar_s* hashNext;
};
STATIC_ASSERT_OFFSET(dvar_s, current, 0x18);

struct GfxWindowParms
{
	HWND__* hwnd;
	int hz;
	bool fullscreen;
	int x;
	int y;
	int sceneWidth;
	int sceneHeight;
	int displayWidth;
	int displayHeight;
	int aaSamples;
};

#define ASPECT_RATIO(W, H) (((float)W) / ((float)H))

enum /*r_aspectRatio*/
{
	ASPECT_RATIO_AUTO,
	ASPECT_RATIO_STANDARD,
	ASPECT_RATIO_16_10,
	ASPECT_RATIO_16_9,
};

struct __declspec(align(4)) vidConfig_t
{
	unsigned int sceneWidth;
	unsigned int sceneHeight;
	unsigned int displayWidth;
	unsigned int displayHeight;
	unsigned __int16 outputDisplayWidth;
	unsigned __int16 outputDisplayHeight;
	unsigned int displayFrequency;
	bool isToolMode;
	int isFullscreen;
	float aspectRatioWindow;
	float aspectRatioScenePixel;
	float aspectRatioDisplayPixel;
	unsigned int maxTextureSize;
	unsigned int maxTextureMaps;
	bool deviceSupportsGamma;
};

#include <windows.h>
#include <d3d9.h>

struct DxGlobals
{
	HINSTANCE__* hinst;
	IDirect3D9* d3d9;
	IDirect3DDevice9* device;
	unsigned int adapterIndex;
	unsigned int vendorId;
	bool adapterNativeIsValid;
	int adapterNativeWidth;
	int adapterNativeHeight;
	int adapterFullscreenWidth;
	int adapterFullscreenHeight;
	bool supportsSceneNullRenderTarget;
	bool supportsIntZ;
	bool nvInitialized;
	bool nvStereoActivated;
	void* nvStereoHandle;
	void* nvDepthBufferHandle;
	void* nvFloatZBufferHandle;
	bool resizeWindow;
};

VANILLA_VALUE(vidConfig, vidConfig_t, 0x03966148);
VANILLA_VALUE(dx, DxGlobals, 0x03963440);

VANILLA_DVAR(r_aspectRatio, 0x03B1FF88);
VANILLA_DVAR(com_wideScreen, 0x024817A8);
VANILLA_DVAR(r_reflectionProbeGenerate, 0x03B35038);
VANILLA_DVAR(r_reflectionProbeGenerateExit, 0x03B3503C);
VANILLA_DVAR(r_reflectionProbeRegenerateAll, 0x03B20030);