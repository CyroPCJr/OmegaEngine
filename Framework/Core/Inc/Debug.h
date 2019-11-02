#pragma once
#define BEGIN_MACRO do {
#define END_MACRO } while (false)

#if defined(_DEBUG)
		#define LOG(format, ...)\
		BEGIN_MACRO\
			char _buffer[4096];\
			int ret = _snprintf_s(_buffer, std::size(_buffer), _TRUNCATE, "%s(%d) "##format, __FILE__, __LINE__, __VA_ARGS__);\
			OutputDebugStringA(_buffer);\
			if (ret == -1) \
				OutputDebugStringA("** message truncated **\n"); \
			OutputDebugStringA("\n");\
		END_MACRO

		#define OMEGAASSERT(condition, format, ...) \
		BEGIN_MACRO\
			if (!(condition))\
			{\
				LOG(format, __VA_ARGS__);\
				DebugBreak();\
			}\
		END_MACRO

#else
#define LOG(format,...)
#define ASSERT(condition, format, ...)
#endif // #defined(_DEBUG)