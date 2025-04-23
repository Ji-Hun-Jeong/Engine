#pragma once

namespace Game
{
	class Action
	{
	public:
		Action(const Str::FString& _ActionName, std::function<void()> _ActFunction)
			: ActionName(_ActionName)
			, ActFunction(_ActFunction)
		{}
		~Action() = default;

	public:
		void Act()
		{
			ActFunction();
		}

		const Str::FString& GetActionName() const { return ActionName; }

		// Action이 시작되는 조건 함수
		// 끝나는 조건함수?

	private:
		Str::FString ActionName;
		std::function<void()> ActFunction;

	};

	class ActionController
	{
	public:
		ActionController() = default;
		~ActionController()
		{
			for (auto iter = Actions.begin(); iter != Actions.end();)
			{
				delete iter->second;
				iter = Actions.erase(iter);
			}
		}

	public:
		void AddAction(Action* _Action)
		{
			Actions.insert(std::make_pair(_Action->GetActionName(), _Action));
		}

		void AddActionQueue(const Str::FString& _ActionName)
		{
			auto iter = Actions.find(_ActionName);
			BePerformedAction.push(iter->second);
		}

		std::queue<Action*>& GetPerformedAction() { return BePerformedAction; }

		void PerformActions()
		{
			Action* Action = nullptr;
			while (BePerformedAction.empty() == false)
			{
				Action = BePerformedAction.front();
				BePerformedAction.pop();

				Action->Act();
			}
		}

		const Action* GetAction(const Str::FString& _ActionName) const
		{
			auto iter = Actions.find(_ActionName);
			if (iter == Actions.end())
				return nullptr;
			return iter->second;
		}

	private:
		std::unordered_map<Str::FString, Action*> Actions;

		std::queue<Action*> BePerformedAction;
	};
}


