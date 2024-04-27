#pragma once

#include "AppState.h"

namespace Omega
{
	struct AppConfig
	{
		std::string appName{ "Omega" };
		uint32_t windowWidth = 1280u;
		uint32_t windowHeight = 720u;
	};

	class App final
	{
	public:
		App() noexcept = default;
		// copy ctor and assignment
		App(const App&) = delete;
		App& operator=(const App&) = delete;

		template<class StateType>
		void AddState(std::string_view name)
		{
			static_assert(std::is_base_of_v<AppState, StateType>,
				"[App] -- Cannot add type AppState which is not derived from StateType.");
			// move semantic = ownership transfer, i.e pass the temporarily values to new owner. 
			// could be represent as swallow copy
			mAppState.emplace(std::string(name), std::make_unique<StateType>());
		}

		void ChangeState(std::string_view name);

		void Run(const AppConfig& appConfig);
		void Quit() noexcept { mRunning = false; }

	private:
		void Terminate();

		Core::Window mWindow;
		std::map<std::string, std::unique_ptr<AppState>> mAppState;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;
		bool mRunning{ false };
		char mPadding[3]{};
	};

}