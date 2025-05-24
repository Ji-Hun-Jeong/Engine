#pragma once
#include "Animation/Animation.h"
#include "StateCondition.h"

namespace Graphics
{
	class StateTransition;
	class RENDERER_API State
	{
	public:
		State(Animation* _Anim)
			: Anim(_Anim)
		{}
		State()
			: State(nullptr)
		{}
		~State()
		{
			if (Anim)
				delete Anim;
			
		}

	public:
		void Update(RenderInterface& _RenderInterface);
		void ExitState();
		void SetAnimation(Animation* _Anim)
		{ 
			if (Anim)
				delete Anim;
			Anim = _Anim;
		}

	private:
		Animation* Anim;

	};

	class RENDERER_API StateVariableTable
	{
	public:
		StateVariableTable() = default;
		~StateVariableTable()
		{
			
		}

	public:
		int* RegistInt(const Str::FString& _VariableName, int _InitValue = 0)
		{
			auto Iter = IntVariables.insert(std::make_pair(_VariableName, _InitValue));
			if (Iter.second == false)
				return nullptr;
			return &Iter.first->second;
		}
		float* RegistFloat(const Str::FString& _VariableName, float _InitValue = 0.0f)
		{
			auto Iter = FloatVariables.insert(std::make_pair(_VariableName, _InitValue));
			if (Iter.second == false)
				return nullptr;
			return &Iter.first->second;
		}
		double* RegistDouble(const Str::FString& _VariableName, double _InitValue = 0.0f)
		{
			auto Iter = DoubleVariables.insert(std::make_pair(_VariableName, _InitValue));
			if (Iter.second == false)
				return nullptr;
			return &Iter.first->second;
		}
		bool* RegistBool(const Str::FString& _VariableName, bool _InitValue = false)
		{
			auto Iter = BoolVariables.insert(std::make_pair(_VariableName, _InitValue));
			if (Iter.second == false)
				return nullptr;
			return &Iter.first->second;
		}

		int* GetInt(const Str::FString& _VariableName)
		{
			auto Iter = IntVariables.find(_VariableName);
			if (Iter == IntVariables.end())
				return nullptr;
			return &Iter->second;
		}
		float* GetFloat(const Str::FString& _VariableName)
		{
			auto Iter = FloatVariables.find(_VariableName);
			if (Iter == FloatVariables.end())
				return nullptr;
			return &Iter->second;
		}
		double* GetDouble(const Str::FString& _VariableName)
		{
			auto Iter = DoubleVariables.find(_VariableName);
			if (Iter == DoubleVariables.end())
				return nullptr;
			return &Iter->second;
		}
		bool* GetBool(const Str::FString& _VariableName)
		{
			auto Iter = BoolVariables.find(_VariableName);
			if (Iter == BoolVariables.end())
				return nullptr;
			return &Iter->second;
		}

	private:
		std::map<Str::FString, int> IntVariables;
		std::map<Str::FString, float> FloatVariables;
		std::map<Str::FString, double> DoubleVariables;
		std::map<Str::FString, bool> BoolVariables;
	};

	class RENDERER_API StateTransition
	{
	public:
		StateTransition(StateCondition* _Condition, State& _Tail, State& _Head, std::function<void(State*)> _ChangeStateFunc)
			: Condition(_Condition), Tail(_Tail), Head(_Head)
			, ChangeStateFunc(_ChangeStateFunc)
		{}
		~StateTransition()
		{
			delete Condition;
		}

	public:
		void TryTransition()
		{
			if (Condition->Satisfy() == false)
				return;

			ChangeStateFunc(&Head);
		}

	private:
		State& Tail;
		State& Head;

		StateCondition* Condition;

		std::function<void(State*)> ChangeStateFunc;

	};

	// StateMachine에 여러 자료형을 map으로 두고 증가감소 이런거 둔다음에
	class RENDERER_API StateMachine
	{
	public:
		StateMachine(StateVariableTable& _VariableTable)
			: VariableTable(_VariableTable)
			, CurrentState(nullptr)
		{}
		~StateMachine() 
		{
			for (auto Iter : States)
				delete Iter.second;
			for (auto Iter : Transitions)
			{
				auto& Vector = Iter.second;
				for (auto Transition : Vector)
					delete Transition;
			}
		}

	public:
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
			if (CurrentState)
				CurrentState->ExitState();

			CurrentState = Iter->second;
		}

		void SetCurrentState(State* _State)
		{
			if (CurrentState)
				CurrentState->ExitState();
			CurrentState = _State;
		}

		void UpdateCurrentState(RenderInterface& _RenderInterface)
		{
			CurrentState->Update(_RenderInterface);
			if (Transitions.find(CurrentState) == Transitions.end())
				return;

			std::vector<StateTransition*>& TransitionsVector = Transitions.find(CurrentState)->second;
			for (auto Transition : TransitionsVector)
				Transition->TryTransition();

		}

		void AddTransition(State* _State, StateTransition* _Transition)
		{
			auto [Iter, Inserted] = Transitions.insert(std::make_pair(_State, std::vector<StateTransition*>{ _Transition }));

			if (!Inserted)
			{
				Iter->second.push_back(_Transition);
			}
		}

	private:
		StateVariableTable& VariableTable;
		std::map<Str::FString, State*> States;

		std::map<State*, std::vector<StateTransition*>> Transitions;

		State* CurrentState;
	};
}
