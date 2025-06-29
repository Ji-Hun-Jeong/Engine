#include "pch.h"
#include "Character.h"

namespace Game
{
	void Character::InitObject()
	{
		Super::InitObject();
	}
	void Character::Update()
	{
		Super::Update();
		StateMachine.DecideUpdateWhether(Animator);
		StateMachine.UpdateCurrentState();
		StateMachine.SetBaseAnimation(Animator);

		Animator.Update();
	}
	void Character::PostUpdate()
	{
		Super::PostUpdate();
	}
	void Character::Destory()
	{
		Super::Destory();
	}
}