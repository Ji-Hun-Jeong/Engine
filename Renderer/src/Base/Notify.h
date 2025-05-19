#pragma once

namespace Graphics
{
	class RENDERER_API IEventListener
	{
		friend class IEventNotifier;
	public:
		IEventListener() = default;
		virtual ~IEventListener() = default;
	
	private:
		virtual void ExecuteEvent() = 0;

	};

	class RENDERER_API IEventNotifier
	{
	public:
		IEventNotifier() = default;
		IEventNotifier(const IEventNotifier&) = delete;
		virtual ~IEventNotifier() = 0
		{
			for (auto& EventListener : EventListeners)
				delete EventListener;
		}

	public:
		void AddListener(IEventListener* _EventListener)
		{ 
			EventListeners.push_back(_EventListener);
		}
		void Notify()
		{
			for (auto& EventListener : EventListeners)
				EventListener->ExecuteEvent();
		}

	private:
		std::vector<IEventListener*> EventListeners;
	};
}


