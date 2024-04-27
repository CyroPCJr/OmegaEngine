#pragma once

namespace Omega::Core
{

	class FpsHelper
	{
	public:
		static int GetCurrentFps() noexcept;
	public:
		explicit FpsHelper() noexcept :
			mStartTime{ std::chrono::steady_clock::now() }
		{}
		~FpsHelper() noexcept = default;

		// copy ctor and assignment
		FpsHelper(const FpsHelper&) = delete;
		FpsHelper& operator=(const FpsHelper&) = delete;

		void BeginFrame() noexcept;
		void EndFrame() noexcept;
		void Update() noexcept;

	private:
		std::chrono::steady_clock::time_point mStartTime;
		std::chrono::steady_clock::time_point mCurrentTime;
		long long mElapsedTime{ 0 };
		unsigned int mFrameCount{ 0 };
		int mPadding{ 0 };
	};

}