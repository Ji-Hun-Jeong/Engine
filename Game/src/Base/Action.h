#pragma once
#include <Engine/src/Time/Time.h>

namespace Game
{
	class Action
	{
	public:
		Action(const Str::FString& _ActionName, std::function<void()> _ActFunction)
			: ActionName(_ActionName)
			, ActFunction(_ActFunction)
			, ActionDelay(0.0f)
			, ActionDegree(0.0f)
			, AlreadyAct(false)
			, IsFinishAct(false)
		{}
		~Action() = default;

	public:
		void Act()
		{
			if (AlreadyAct == false)
			{
				ActFunction();
				AlreadyAct = true;
			}
			ActionDegree += Time::GetDT();
			
			if (ActionDelay <= ActionDegree)
				IsFinishAct = true;
		}

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

	class ActionPerformer
	{
		friend class ActionController;
	private:
		ActionPerformer()
		{}
		~ActionPerformer()
		{
			BePerformedAction.clear();
		}

	public:
		void PerformActions()
		{
			Action* Action = nullptr;

			for (auto iter = BePerformedAction.begin(); iter != BePerformedAction.end(); )
			{
				Action = *iter;
				if (Action->IsFinish())
				{
					Action->ActInit();
					iter = BePerformedAction.erase(iter);
				}
				else
				{
					++iter;
					Action->Act();
				}
			}
		}

		void AddPerformAction(Action* _PerformedAction)
		{
			BePerformedAction.insert(_PerformedAction);
		}

	private:
		std::set<Action*> BePerformedAction;
		
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
			ActionPerformer.AddPerformAction(iter->second);
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


