#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Win32 headers
#include <objbase.h>
#include <Windows.h>

// Standard headers
#include <algorithm>
#include <codecvt>
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
#include <unordered_map>
#include <variant>
#include <vector>

// External headers
#include <RapidJSON\Inc\document.h>
#include <RapidJSON\Inc\filereadstream.h>
#include <RapidJSON\Inc\filewritestream.h>