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

	private:
		Str::FString ActionName;
		std::function<void()> ActFunction;

	};

	class ActionPerformer
	{
		friend class ActionController;
	private:
		ActionPerformer()
			: PrevedPerformAction(nullptr)
		{}
		~ActionPerformer()
		{
			while (!BePerformedAction.empty())
			{
				delete BePerformedAction.front();
				BePerformedAction.pop();
			}
		}

	public:
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
		std::queue<Action*> BePerformedAction;

		Action* PrevedPerformAction;
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
			ActionPerformer.BePerformedAction.push(iter->second);
		}

		ActionPerformer* GetActionPerformer() { return &ActionPerformer; }

		const Action* GetAction(const Str::FString& _ActionName) const
		{
			auto iter = Actions.find(_ActionName);
			if (iter == Actions.end())
				return nullptr;
			return iter->second;
		}

	private:
		std::unordered_map<Str::FString, Action*> Actions;

		ActionPerformer ActionPerformer;
	};
}


