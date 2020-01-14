#pragma once

namespace Omega::Graphics::DebugUI
{
	enum class Theme
	{
		Classic,
		Dark,
		Light
	};

	void StaticInitialize(HWND window, bool docking = false, bool multiViewport = false);
	void StaticTerminate();

	void SetTheme(Theme theme);

	void BeginRender();
	void EndRender();

} // namespace Omega::Graphics::DebugUI