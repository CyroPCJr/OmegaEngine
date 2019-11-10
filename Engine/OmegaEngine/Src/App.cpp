#include "Precompiled.h"
#include "App.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Input;

void App::Run(AppConfig appConfig)
{
	mAppConfig = appConfig;
	// Setup our application window
	mWindow.Initialize(
		GetModuleHandle(NULL),
		appConfig.appName.c_str(),
		appConfig.windowWidth,
		appConfig.windowHeight);

	// Initialize the input system
	auto handle = mWindow.GetWindow();
	InputSystem::StaticInitialize(handle);
	
	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);

#pragma region Initialize engine system
	//OnInit

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
		//OnGameLoop
	}
	// OnCleanUp
#pragma endregion

#pragma region Terminate engine system
	
	GraphicsSystem::StaticTerminate();
	InputSystem::StaticTerminate();
	mWindow.Terminate();
	
#pragma endregion

}
