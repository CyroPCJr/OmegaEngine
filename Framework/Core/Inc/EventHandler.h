//====================================================================================================
// References:
//	https://www.codeproject.com/Articles/1256352/CppEvent-How-to-Implement-Events-using-Standard-Cp
//====================================================================================================

#pragma once

#include "Common.h"

namespace Omega::Core
{
	using EventHandlerId = uint32_t;

	template <class... Args>
	class EventHandler
	{
	public:
		using EventHandlerFunc = std::function<void(Args...)>;

		explicit EventHandler(EventHandlerFunc handlerFunc)
			: mHandlerFunc(std::move(handlerFunc))
			, mHandlerId(++sNextHandlerId)
		{}

		void operator()(Args... params) const
		{
			if (mHandlerFunc)
				mHandlerFunc(params...);
		}

		EventHandlerId GetId() const
		{
			return mHandlerId;
		}

	private:
		static std::atomic_uint sNextHandlerId;

		EventHandlerFunc mHandlerFunc;
		EventHandlerId mHandlerId;
	};

	template <class... Args>
	std::atomic_uint EventHandler<Args...>::sNextHandlerId = 0;

	template <class... Args>
	class Event
	{
	public:
		using HandlerType = EventHandler<Args...>;
		using HandlerFunc = typename HandlerType::EventHandlerFunc;
		using HandlerList = std::list<HandlerType>;

		EventHandlerId Add(HandlerFunc handlerFunc)
		{
			auto& handler = mHandlerList.emplace_back(std::move(handlerFunc));
			return handler.GetId();
		}

		bool Remove(const EventHandlerId& handlerId)
		{
			auto iter = std::find_if(mHandlerList.begin(), mHandlerList.end(), [handlerId](const HandlerType& handler)
			{
				return handler.GetId() == handlerId;
			});

			if (iter == mHandlerList.end())
				return false;

			mHandlerList.erase(iter);
			return true;
		}

		void Notify(Args... params) const
		{
			for (const auto& handler : mHandlerList)
				handler(params...);
		}

		// Convenient operator overloads
		EventHandlerId operator+=(const HandlerFunc& handlerFunc) { return Add(handlerFunc); }
		bool operator-=(const EventHandlerId& handlerId) { return Remove(handlerId); }
		void operator()(Args... params) const { Notify(params...); }

	private:
		HandlerList mHandlerList;
	};
}
