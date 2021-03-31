#include "Precompiled.h"
#include "App.h"

#include "MetaRegistration.h"

using namespace Omega;
using namespace Omega::Core;
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
	LOG("App -- Running ...");
	mAppConfig = std::move(appConfig);

	LOG("App -- Registering meta types ...");
	Core::StaticMetaRegister();
	Math::StaticMetaRegister();
	Omega::StaticMetaRegister();
	
	// Initialize timer
	TimeUtil::GetTime();

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

	TextureManager::StaticInitialize("../Assets/Images");

#pragma region Initialize engine system
	//OnInit

	// Initialize the starting state
	mCurrentState = mAppState.begin()->second.get();
	mCurrentState->Initialize();

	mRunning = true;
	auto graphicsSystem = GraphicsSystem::Get();
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

		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		float deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);

		graphicsSystem->BeginRender();

		// --- Sprites ---
		//TODO: Continue tomorrow from here ....
		//TextureId id = 0;
		//Texture* texture = nullptr;
		//SpriteRenderer::Get()->BeginRender();
		//for (const auto& command : mySpriteCommands)
		//{
		//	if (id != command.textureId)
		//	{
		//		texture = TextureManager::Get()->GetTexture(command.textureId);
		//		id = command.textureId;
		//	}
		//	if (texture)
		//	{
		//		if (Math::IsEmpty(command.sourceRect))
		//		{
		//			SpriteRenderer::Get()->Draw(*texture, command.position, command.rotation, command.pivot, command.flip);
		//		}
		//		else
		//		{
		//			SpriteRenderer::Get()->Draw(*texture, command.sourceRect, command.position, command.rotation, command.pivot, command.flip);
		//		}
		//	}
		//}
		//mySpriteCommands.clear();
		//SpriteRenderer::Get()->EndRender();

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
	TextureManager::StaticTerminate();

	mWindow.Terminate();

#pragma endregion

}
