#pragma once

#include "EventHandler.h"
#include "TimeUtil.h"

namespace Omega::Core
{
	using DebugLogEvent = Event<const std::string&>;
	extern DebugLogEvent OnDebugLog;
}

#define BEGIN_MACRO do {
#define END_MACRO } while (false)

#if defined(_DEBUG)
#define LOG(format, ...)\
	BEGIN_MACRO\
		char _buffer[4096];\
		const int _res = _snprintf_s(_buffer, std::size(_buffer), _TRUNCATE, "[%.3f]: "##format##"\n", Omega::Core::TimeUtil::GetTime(), __VA_ARGS__);\
		OutputDebugStringA(_buffer);\
		if (_res == -1)\
		{\
			OutputDebugStringA("** message truncated **\n");\
		}\
		OutputDebugStringA("\n");\
		Omega::Core::OnDebugLog(_buffer);\
	END_MACRO

#define OMEGAASSERT(condition, format, ...)\
	BEGIN_MACRO\
		if (!(condition))\
		{\
			LOG("%s(%d) "##format, __FILE__, __LINE__, __VA_ARGS__);\
			DebugBreak();\
		}\
	END_MACRO
#else
#define LOG(format, ...)
#define OMEGAASSERT(condition, format, ...) do { (void)(sizeof(condition)); } while (false)
#endif


/*
Exemple how to use log
[0.000]: App -- Starting state: EditState
[0.000]: App -- Running ...
[0.000]: App -- Registering meta types ...
[0.000]: App -- Creating window ...
[0.049]: InputSystem -- Initializing...
[0.049]: InputSystem -- System initialized.
[0.050]: GraphicsSystem -- Initializing...
[0.171]: GraphicsSystem -- System initialized.
[0.172]: VertexShader -- Initializing from file: ../../Assets/Shaders/SimpleDraw.fx
[0.181]: PixelShader -- Initializing from file: ../../Assets/Shaders/SimpleDraw.fx
[0.296]: VertexShader -- Initializing from file: ../../Assets\Shaders\Texturing.fx
[0.301]: PixelShader -- Initializing from file: ../../Assets\Shaders\Texturing.fx
[0.355]: VertexShader -- Initializing from file: ../../Assets/Shaders/Terrain.fx
[0.361]: PixelShader -- Initializing from file: ../../Assets/Shaders/Terrain.fx
[2.005]: App -- Entering main loop ...

*/