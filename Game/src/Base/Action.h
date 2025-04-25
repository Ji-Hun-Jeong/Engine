#pragma once
#include <Engine/src/Time/Time.h>

namespace Game
{
	class Action
	{
	public:
		Action(const Str::FString& _ActionName, std::function<void()> _ActFunction);
		~Action() = default;

	public:
		void Act();

		bool IsFinish() const { return IsFinishAct; }

		void ActInit()
		{
			ActionDegree = 0.0f;
			AlreadyAct = false;
			IsFinishAct = false;
		}

		void SetActionDelay(float _ActionDelay) { ActionDelay = _ActionDelay; }

		const Str::FString& GetActionName() const { return ActionName; }

	private:
		Str::FString ActionName;
		std::function<void()> ActFunction;

		float ActionDelay;
		float ActionDegree;

		bool AlreadyAct;
		bool IsFinishAct;
	};

	class ActionQueue
	{
		friend class ActionController;
	private:
		ActionQueue() = default;
		~ActionQueue() = default;

	public:
		bool IsExistPreparedAction() { return PreparedActions.size() > 0; }

		std::queue<const Action*> GetPreparedActions() { return PreparedActions; }

	private:
		std::queue<const Action*> PreparedActions;

	};

	class ActionPerformer
	{
		friend class ActionController;
	private:
		ActionPerformer() = default;
		~ActionPerformer()
		{
			BePerformedAction.clear();
		}

	public:
		void PerformActions();

		void AddPerformAction(ActionQueue* _ActionQueue)
		{
			std::queue<const Action*> PreparedActions = _ActionQueue->GetPreparedActions();
			Action* PrepareAction = nullptr;
			while (PreparedActions.empty() == false)
			{
				PrepareAction = (Action*)PreparedActions.front();
				PreparedActions.pop();

				BePerformedAction.insert(PrepareAction);
			}
		}

	private:
		std::set<Action*> BePerformedAction;

	};

	class ActionController
	{
	public:
		ActionController() = default;
		virtual ~ActionController();

	public:
		virtual void ControllAction() = 0;

		void AddActionQueue(const Str::FString& _ClassName)
		{
			auto Iter = ActionQueues.find(_ClassName);
			if (Iter != ActionQueues.end())
				assert(0);
			else
				ActionQueues.insert(std::make_pair(_ClassName, new ActionQueue));
		}
		void AddAction(Action* _Action)
		{
			auto Iter = Actions.find(_Action->GetActionName());
			if (Iter == Actions.end())
				assert(0);
			else
				Actions.insert(std::make_pair(_Action->GetActionName(), _Action));
		}

		void PrepareAction(const Str::FString& _ClassName, const Str::FString& _ActionName)
		{
			const Action* Action = GetAction(_ActionName);
			if (Action)
			{
				ActionQueue* ActionQueue = getActionQueue(_ClassName);
				if (ActionQueue)
					ActionQueue->PreparedActions.push(Action);
			}			
		}

		const Action* GetAction(const Str::FString& _ActionName) const
		{
			auto Iter = Actions.find(_ActionName);
			if (Iter == Actions.end())
				assert(0);
			else
				return Iter->second;
			
			return nullptr;
		}

		ActionPerformer* GetActionPerformer() { return &ActionPerformer; }

	protected:
		ActionQueue* getActionQueue(const Str::FString& _ClassName)
		{
			auto Iter = ActionQueues.find(_ClassName);
			if (Iter == ActionQueues.end())
				assert(0);
			return Iter->second;
		}

	protected:
		std::unordered_map<Str::FString, Action*> Actions;
		std::map<Str::FString, ActionQueue*> ActionQueues;

		ActionPerformer ActionPerformer;
	};
}


