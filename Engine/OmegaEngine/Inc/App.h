#pragma once

namespace Omega
{
	// foward declaration
	class AppState;

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
			mAppState.emplace(std::move(name), std::make_unique<StateType>());
		}

		void ChangeState(std::string name);

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