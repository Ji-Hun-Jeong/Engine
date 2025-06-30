#pragma once
#include "StateCondition.h"

namespace Game
{
	class State;
	class StateTransition
	{
	public:
		StateTransition(StateCondition* _Condition, State* _Head)
			: Condition(_Condition), Head(_Head)
		{
		}
		~StateTransition()
		{
			if (Condition)
				delete Condition;
		}

	public:
		State* TryTransition()
		{
			// 조건이 없으면 바로 헤드로
			if (Condition == nullptr)
				return Head;

			if (Condition->Satisfy() == false)
				return nullptr;

			return Head;
		}
		bool CanChange() const { Condition->Satisfy(); }
		State* GetHead() const { return Head; }

	private:
		State* Head;

		StateCondition* Condition;

	};

	class State
	{
	public:
		State(class Animation* _StateAnimation)
			: EnterStateFunc(nullptr)
			, ExitStateFunc(nullptr)
			, StateAnimation(_StateAnimation)
		{
		}
		~State();

	public:
		State* Update()
		{
			for (auto Transition : Transitions)
			{
				State* Head = Transition->TryTransition();
				if (Head)
					return Head;
			}
			return nullptr;
		}
		void SetEnterState(std::function<void()> _EnterStateFunc) { EnterStateFunc = _EnterStateFunc; }
		void SetExitState(std::function<void()> _ExitStateFunc) { ExitStateFunc = _ExitStateFunc; }
		void EnterState();
		void ExitState();

		void AddTransition(StateTransition* _Transition)
		{
			Transitions.push_back(_Transition);
		}
		bool CanChangeState(State* _State)
		{
			for (auto Transition : Transitions)
			{
				if (Transition->GetHead() == _State)
					return Transition->CanChange();
			}
			return false;
		}

		class Animation* GetStateAnimation() { return StateAnimation; }
		State* SetName(const Str::FString& _Name) { Name = _Name; return this; }
		const Str::FString& GetName() const { return Name; }
	private:
		std::function<void()> EnterStateFunc;
		std::function<void()> ExitStateFunc;

		class Animation* StateAnimation;

		std::vector<StateTransition*> Transitions;

		Str::FString Name;
	};

	class StateMachine
	{
	public:
		StateMachine(StateVariableTable& _VariableTable)
			: VariableTable(_VariableTable)
			, CurrentState(nullptr)
			, StateChanged(false)
			, UpdateWhether(true)
		{
		}
		~StateMachine()
		{
			for (auto Iter : States)
				delete Iter.second;
		}

	public:
		void UpdateCurrentState()
		{
			VariableTable.ResetTriggers();
			
			if (UpdateWhether == false)
				return;

			State* Head = CurrentState->Update();
			
			if (Head)
			{
				StateChanged = true;
				SetCurrentState(Head);
			}
		}
		void DecideUpdateWhether(class Animator& _Animator);
		void SetBaseAnimation(class Animator& _Animator);
		bool CanChangeState(State* _HeadState)
		{
			if (UpdateWhether == false)
				return false;
			return CurrentState->CanChangeState(_HeadState);
		}

		State* AddState(const Str::FString& _StateName, State* _State)
		{
			auto Iter = States.insert(std::make_pair(_StateName, _State));
			if (Iter.second == false)
			{
				std::cout << _StateName << " Is Already Exist\n";
				return nullptr;
			}
			return Iter.first->second;
		}

		void SetCurrentState(const Str::FString& _StateName)
		{
			auto Iter = States.find(_StateName);
			if (Iter == States.end())
			{
				assert(0);
				return;
			}
			SetCurrentState(Iter->second);
		}

		void SetCurrentState(State* _State)
		{
			if (CurrentState)
				CurrentState->ExitState();

			CurrentState = _State;

			if (CurrentState)
				CurrentState->EnterState();
		}

		State* GetState(const Str::FString& _StateName)
		{
			auto Iter = States.find(_StateName);
			if (Iter == States.end())
				return nullptr;
			return Iter->second;
		}

	private:
		StateVariableTable& VariableTable;

		std::map<Str::FString, State*> States;
		State* CurrentState;

		bool StateChanged;
		bool UpdateWhether;
	};
}
