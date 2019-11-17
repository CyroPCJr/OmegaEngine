#pragma once

#include "AppState.h"

namespace Omega
{

	struct AppConfig
	{
		std::string appName{ "Omega" };
		uint32_t windowWidth{ 1280 };
		uint32_t windowHeight{ 720 };
	};

	class App
	{
	public:

		template<class StateType, class = std::void_t<std::is_base_of<AppState, StateType>>>
		void AddState(std::string name) 
		{
			// move semantic = ownership transfer, i.e pass the temporarily values to new owner. 
			// could be represent as swallow copy
			mAppState.emplace(std::move(name), std::make_unique<StateType>());
		}

		void ChangeState(const std::string& name);

		void Run(AppConfig appConfig);
		void Quit() { mRunning = false; }
	private:
		AppConfig mAppConfig;
		Core::Window mWindow;
		bool mRunning = false;

		std::map<std::string, std::unique_ptr<AppState>> mAppState;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;
	};	

}