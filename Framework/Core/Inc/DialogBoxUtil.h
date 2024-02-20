#pragma once

namespace Omega::Core
{
	bool OpenFileDialog(char fileName[MAX_PATH], const char* title, const char* filter);
	bool SaveFileDialog(char fileName[MAX_PATH], const char* title, const char* filter);
}