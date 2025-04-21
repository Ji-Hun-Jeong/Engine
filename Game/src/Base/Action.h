#pragma once

namespace Game
{
	class Action
	{
	public:
		Action(const std::string& _ActionName, std::function<void()> _ActFunction)
			: ActionName(_ActionName)
			, ActFunction(_ActFunction)
		{}
		~Action() = default;

	public:
		void Act()
		{
			ActFunction();
		}
		const std::string& GetActionName() const { return ActionName; }

	private:
		std::string ActionName;
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

		void AddActionQueue(const std::string& _ActionName)
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

	private:
		std::unordered_map<std::string, Action*> Actions;

		std::queue<Action*> BePerformedAction;
	};
}


