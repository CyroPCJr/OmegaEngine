#include "Precompiled.h"
#include "App.h"
#include "MetaRegistration.h"

#pragma comment(lib, "FW1FontWrapper.lib")

using namespace Omega;
using namespace Omega::Core;
using namespace Omega::Graphics;
using namespace Omega::Input;

namespace
{
	constexpr uint32_t MAX_VERTEX_SIZE = 1024u * 1024u;
}

void App::ChangeState(std::string_view name)
{
	if (const auto& iter = mAppState.find(std::string(name)); 
		iter != mAppState.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(const AppConfig& appConfig)
{
	LOG("App -- Running ...");

	LOG("App -- Registering meta types ...");
	Core::StaticMetaRegister();
	Math::StaticMetaRegister();
	Omega::StaticMetaRegister();

	// Setup our application window
	mWindow.Initialize(
		GetModuleHandle(NULL),
		appConfig.appName.c_str(),
		appConfig.windowWidth,
		appConfig.windowHeight);

	// Initialize the input system
	const auto& handle = mWindow.GetWindow();
	InputSystem::StaticInitialize(handle);

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);
	auto& graphicsSystem = GraphicsSystem::Get()->get();
	graphicsSystem.SetClearColor(Colors::Black); // default background color
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize(MAX_VERTEX_SIZE);
	RendererManager::StaticInitialize();

#pragma region Initialize engine system
	//OnInit

	// Initialize the starting state
	mCurrentState = mAppState.begin()->second.get();
	mCurrentState->Initialize();

	mRunning = true;
	
	auto& inputSystem = InputSystem::Get()->get();
	auto& rendererManager = RendererManager::Get()->get();
	while (mRunning)
	{
		mWindow.ProcessMessage();
		if (!mWindow.IsActive() || inputSystem.IsKeyPressed(KeyCode::ESCAPE))
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
		
		inputSystem.Update();

		mCurrentState->Update(TimeUtil::GetDeltaTime());

		graphicsSystem.BeginRender();

		mCurrentState->Render();
		rendererManager.Render();

		DebugUI::BeginRender();
		mCurrentState->DebugUI();
		DebugUI::EndRender();

		graphicsSystem.EndRender();

		//OnGameLoop
	}
	// OnCleanUp
#pragma endregion

#pragma region Terminate engine system

	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	SimpleDraw::StaticTerminate();
	RendererManager::StaticTerminate();
	
	mCurrentState->Terminate();

	mWindow.Terminate();

#pragma endregion

}

float App::GetTime()
{
	return TimeUtil::GetTime();
}
