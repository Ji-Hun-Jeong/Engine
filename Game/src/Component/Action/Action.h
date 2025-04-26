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

		const Str::FString& GetActionName() const 
		{ 
			return ActionName; 
		}

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
		ActionPerformer(uint8_t _NumOfPerformAction)
			: NumOfPerformAction(_NumOfPerformAction)
		{}
		~ActionPerformer() = default;

	public:
		void PerformActions();

		void AddPerformedAction(Action* _PerformedAction) 
		{
			if (BePerformedAction.size() < NumOfPerformAction)
				BePerformedAction.insert(_PerformedAction);
		}

		void ClearAction()
		{
			BePerformedAction.clear();
		}

		bool IsExistPerformedAction() { return BePerformedAction.size(); }

	private:
		std::set<Action*> BePerformedAction;

		uint8_t NumOfPerformAction;

	};

	class ActionController
	{
	public:
		ActionController() = default;
		virtual ~ActionController();

	public:
		void Update();

		void AddPerformer(const Str::FString& _ClassName, uint8_t _NumOfPerformAction)
		{
			auto Iter = ActionPerformers.find(_ClassName);
			if (Iter != ActionPerformers.end())
				assert(0);
			else
				ActionPerformers.insert(std::make_pair(_ClassName, new ActionPerformer(_NumOfPerformAction)));
		}

		void AddAction(Action* _Action)
		{
			auto Iter = Actions.find(_Action->GetActionName());
			if (Iter != Actions.end())
				assert(0);
			else
				Actions.insert(std::make_pair(_Action->GetActionName(), _Action));
		}

		void PrepareAction(const Str::FString& _ClassName, const Str::FString& _ActionName)
		{
			Action* Action = getAction(_ActionName);
			if (Action == nullptr)
				return;
			ActionPerformer* ActionPerformer = getActionPerformer(_ClassName);
			if (ActionPerformer == nullptr)
				return;

			ReadyActionQueue.push(std::make_pair(Action, _ClassName));

		}

		bool IsExistAction(const Str::FString& _ActionName)
		{
			auto Iter = Actions.find(_ActionName);
			if (Iter != Actions.end())
				return true;

			return false;
		}

	protected:
		virtual void controlAction() = 0;

		ActionPerformer* getActionPerformer(const Str::FString& _ClassName)
		{
			auto Iter = ActionPerformers.find(_ClassName);
			if (Iter == ActionPerformers.end())
				assert(0);
			return Iter->second;
		}

		Action* getAction(const Str::FString& _ActionName) const
		{
			auto Iter = Actions.find(_ActionName);
			if (Iter == Actions.end())
				assert(0);
			else
				return Iter->second;

			return nullptr;
		}

		void insertToPerformer()
		{
			std::pair<const Action*, Str::FString> Pair = { nullptr, "" };
			auto Iter = ActionPerformers.begin();
			ActionPerformer* ActionPerformer = nullptr;
			while (ReadyActionQueue.empty() == false)
			{
				Pair = std::move(ReadyActionQueue.front());
				ReadyActionQueue.pop();

				Iter = ActionPerformers.find(Pair.second);
				ActionPerformer = Iter->second;
				ActionPerformer->AddPerformedAction((Action*)Pair.first);
			}
		}

	protected:
		std::unordered_map<Str::FString, Action*> Actions;
		
		std::map<Str::FString, ActionPerformer*> ActionPerformers;

		std::queue<std::pair<const Action*, Str::FString>> ReadyActionQueue;
	};
}


