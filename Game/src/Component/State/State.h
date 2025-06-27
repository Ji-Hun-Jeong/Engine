#pragma once
#include "StateCondition.h"

namespace Game
{
	class State
	{
	public:
		State(class Animation* _BaseAnimation)
			: EnterStateFunc(nullptr)
			, ExitStateFunc(nullptr)
			, BaseAnimation(_BaseAnimation)
		{
		}
		~State()
		{
		}

	public:
		void SetEnterState(std::function<void()> _EnterStateFunc) { EnterStateFunc = _EnterStateFunc; }
		void SetExitState(std::function<void()> _ExitStateFunc) { ExitStateFunc = _ExitStateFunc; }
		void EnterState();
		void ExitState();

		class Animation* GetBaseAnimation() { return BaseAnimation; }

	private:
		std::function<void()> EnterStateFunc;
		std::function<void()> ExitStateFunc;

		class Animation* BaseAnimation;
	};

	class StateTransition
	{
	public:
		StateTransition(StateCondition* _Condition, State* _Head)
			: Condition(_Condition), Head(_Head)
			, ForceExit(false)
		{
		}
		~StateTransition()
		{
			if (Condition)
				delete Condition;
		}

	public:
		State* TryTransition(State& _CurrentState)
		{
			if (ForceExit == false)
					return nullptr;

			if (Condition == nullptr)
				return Head;

			if (Condition->Satisfy() == false)
				return nullptr;

			return Head;
		}
		void SetForceExit(bool _ForceExit) { ForceExit = _ForceExit; }

	private:
		State* Head;

		StateCondition* Condition;

		bool ForceExit;

	};

	class StateMachine
	{
	public:
		StateMachine(StateVariableTable& _VariableTable)
			: VariableTable(_VariableTable)
			, CurrentState(nullptr)
			, CurrentTransitions(nullptr)
			, StateChange(false)
		{
		}
		~StateMachine()
		{
			for (auto Iter : States)
				delete Iter.second;
			for (auto Iter : Transitions)
			{
				std::vector<StateTransition*>* Vector = Iter.second;
				for (auto Transition : *Vector)
					delete Transition;
				delete Vector;
			}
		}

	public:
		void UpdateCurrentState()
		{
			StateChange = false;

			if (CurrentTransitions == nullptr)
				return;

			State* HeadState = nullptr;
			for (auto Transition : *CurrentTransitions)
			{
				HeadState = Transition->TryTransition(*CurrentState);
				if (HeadState)
					StateChange = true;
			}

			if (StateChange)
				SetCurrentState(HeadState);

			VariableTable.ResetTriggers();
		}

		void SetBaseAnimation(class Animator& _Animator);

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

			auto Iter = Transitions.find(CurrentState);
			if (Iter == Transitions.end())
				CurrentTransitions = nullptr;
			else
				CurrentTransitions = Iter->second;
		}

		void AddTransition(State* _State, StateTransition* _Transition)
		{
			auto Iter = Transitions.find(_State);
			if (Iter == Transitions.end())
			{
				std::vector<StateTransition*>* StateTransitionVector = new std::vector<StateTransition*>;
				Transitions.insert(std::make_pair(_State, StateTransitionVector));
				StateTransitionVector->push_back(_Transition);
			}
			else
			{
				std::vector<StateTransition*>* StateTransitionVector = Iter->second;
				StateTransitionVector->push_back(_Transition);
			}
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

		std::map<State*, std::vector<StateTransition*>*> Transitions;
		std::vector<StateTransition*>* CurrentTransitions;

		bool StateChange;

	};

	extern void AddTransition(StateMachine& _StateMachine, StateCondition* _Condition, State* _TailState, State* _HeadState
		, bool _ForceExit = true);
}
