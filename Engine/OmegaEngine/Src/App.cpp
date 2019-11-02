#include "Precompiled.h"
#include "App.h"

using namespace Omega;

void App::Run(AppConfig appConfig)
{
	mAppConfig = appConfig;
	// Setup our application window
	mWindow.Initialize(
		GetModuleHandle(NULL),
		appConfig.appName.c_str(),
		appConfig.windowWidth,
		appConfig.windowHeight);

#pragma region Initialize engine system
	mRunning = true;
	while (mRunning && mWindow.IsActive())
	{
		mWindow.ProcessMessage();
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			Quit();
			break;
		}
		// Do game stuffs ....
	}

#pragma endregion

#pragma region Terminate engine system

#pragma endregion

}
