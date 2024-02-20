#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Win32 headers
#include <objbase.h>
#include <shobjidl.h> // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb776913(v=vs.85) 
#include <Windows.h>

// Standard headers
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional> 
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

// External headers
#include <RapidJSON\Inc\document.h>
#include <RapidJSON\Inc\filereadstream.h>
#include <RapidJSON\Inc\filewritestream.h>