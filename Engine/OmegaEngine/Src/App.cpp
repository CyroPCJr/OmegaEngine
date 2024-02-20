#include "Precompiled.h"
#include "App.h"

#include "MetaRegistration.h"

#pragma comment(lib, "FW1FontWrapper.lib")

using namespace Omega;
using namespace Omega::Core;
using namespace Omega::Graphics;
using namespace Omega::Input;

void App::ChangeState(std::string_view name)
{
	if (const auto& iter = mAppState.find(name); 
		iter != mAppState.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(const AppConfig& appConfig)
{
	LOG("App -- Running ...");
	//mAppConfig = std::move(appConfig);

	LOG("App -- Registering meta types ...");
	Core::StaticMetaRegister();
	Math::StaticMetaRegister();
	Omega::StaticMetaRegister();

	// Initialize timer
	TimeUtil::GetTime();

	// Setup our application window
	mWindow.Initialize(
		GetModuleHandle(NULL),
		std::string(appConfig.appName).c_str(),
		appConfig.windowWidth,
		appConfig.windowHeight);

	// Initialize the input system
	auto handle = mWindow.GetWindow();
	InputSystem::StaticInitialize(handle);

	// Initialize the graphics system
	GraphicsSystem::StaticInitialize(handle, false);
	GraphicsSystem::Get()->SetClearColor(Colors::Black); // default background color
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize(1024 * 1024);
	SpriteRenderer::StaticInitialize();
	TextureManager::StaticInitialize("../../Assets/Images");
	SpriteRendererManager::StaticInitialize();

#pragma region Initialize engine system
	//OnInit

	// Initialize the starting state
	mCurrentState = mAppState.begin()->second.get();
	mCurrentState->Initialize();

	mRunning = true;
	const auto& graphicsSystem = GraphicsSystem::Get();
	const auto& inputSystem = InputSystem::Get();
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
		
		inputSystem->Update();

		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		const float deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);

		graphicsSystem->BeginRender();

		mCurrentState->Render();
		SpriteRendererManager::Get()->Render();

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
	TextureManager::StaticTerminate();
	SpriteRenderer::StaticTerminate();
	SpriteRendererManager::StaticTerminate();

	mWindow.Terminate();

#pragma endregion

}

float App::GetTime()
{
	return TimeUtil::GetTime();
}
