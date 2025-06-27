#pragma once
#include "Actor.h"
#include "Component/State/State.h"
#include "Component/Animation/Animator.h"

namespace Game
{
	class Character : public Actor
	{
		using Super = Actor;
	public:
		Character(const Str::FString& _Name) 
			: Super(_Name)
			, StateTable()
			, StateMachine(StateTable)
			, Animator(Super::RenderInterface)
		{}
		virtual ~Character() = 0
		{}

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void PostUpdate() override;
		virtual void Destory() override;

		StateVariableTable& GetStateTable() { return StateTable; }
		StateMachine& GetStateMachine() { return StateMachine; }

	protected:
		StateVariableTable StateTable;
		StateMachine StateMachine;

		Animator Animator;
	};
}


