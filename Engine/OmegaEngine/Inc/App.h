#pragma once

#include "AppState.h"

namespace Omega
{

	struct AppConfig
	{
		std::string appName = "Omega";
		uint32_t windowWidth = 1280;
		uint32_t windowHeight = 720;
	};

	class App
	{
	public:

		template<class StateType>
		void AddState(std::string name)
		{
			static_assert(std::is_base_of_v<AppState, StateType>,
				"[App] -- Cannot add type AppState which is not derived from StateType.");
			// move semantic = ownership transfer, i.e pass the temporarily values to new owner. 
			// could be represent as swallow copy
			mAppState.emplace(std::move(name), std::make_unique<StateType>());
		}

		void ChangeState(const std::string& name);

		void Run(AppConfig appConfig);
		void Quit() { mRunning = false; }
		
		float GetTime();

	private:
		AppConfig mAppConfig;
		Core::Window mWindow;
		bool mRunning = false;

		std::map<std::string, std::unique_ptr<AppState>> mAppState;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;

	};

}