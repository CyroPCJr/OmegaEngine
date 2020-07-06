#include "Precompiled.h"
#include "App.h"

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Input;

void App::ChangeState(const std::string& name)
{
	if (auto iter = mAppState.find(name); iter != mAppState.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(AppConfig appConfig)
{
	mAppConfig = std::move(appConfig);

	// Setup our application window
	mWindow.Initialize(
		GetModuleHandle(NULL),
		mAppConfig.appName.c_str(),
		mAppConfig.windowWidth,
		mAppConfig.windowHeight);

	// Initialize the input system
	auto handle = mWindow.GetWindow();
	InputSystem::StaticInitialize(handle);

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize();

#pragma region Initialize engine system
	//OnInit

	// Initialize the starting state
	mCurrentState = mAppState.begin()->second.get();
	mCurrentState->Initialize();

	mTime.Initialize();

	mRunning = true;
	while (mRunning)
	{
		mWindow.ProcessMessage();
		if (!mWindow.IsActive())
		{
			Quit();
			continue;
		}

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

		mTime.Update();
		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		float deltaTime = 1.0f / 60.0f;
		//float deltaTime = mTime.GetElapsedTime();

		mCurrentState->Update(deltaTime);

		auto graphicsSystem = GraphicsSystem::Get();
		graphicsSystem->BeginRender();
		mCurrentState->Render();

		DebugUI::BeginRender();
		mCurrentState->DebugUI();
		DebugUI::EndRender();

		graphicsSystem->EndRender();

		//OnGameLoop
	}
	// OnCleanUp
#pragma endregion

#pragma region Terminate engine system

	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	SimpleDraw::StaticTerminate();
	mWindow.Terminate();

#pragma endregion

}
