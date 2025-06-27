#include "pch.h"
#include "PlayerController.h"
#include "Object/Player/Player.h"
#include "Object/KeyInput/KeyInput.h"

namespace Game
{
	void PlayerController::InitObject()
	{
		Super::InitObject();
	}

	void PlayerController::Update()
	{
		Super::Update();
	}

	void PlayerController::Destory()
	{
		Super::Destory();
	}

	void PlayerController::SetKeyInput(KeyInput& _KeyInput)
	{
		StateVariableTable& StateTable = Player.GetStateTable();
		StateMachine& StateMachine = Player.GetStateMachine();
		Collision::RigidBody& RigidBody = Player.GetRigidBody();
		
		bool& MoveState = StateTable.RegistBool("Move", false);
		bool& PossibleMoveState = StateTable.RegistBool("PossibleMove", true);
		TriggerVariable& AttackTrigger = StateTable.RegistTrigger("Attack");

		_KeyInput.AddKey("PlayerMoveLeft", Input::eKeyType::Left, Input::eButtonState::Hold, [this, &MoveState, PossibleMoveState]()->void
			{
				if (PossibleMoveState == false)
					return;
				MoveState = true;
				Player.Move(Vector3(-1.0f, 0.0f, 0.0f), 1.0f);
			});
		_KeyInput.AddKey("PlayerMoveRight", Input::eKeyType::Right, Input::eButtonState::Hold, [this, &MoveState, PossibleMoveState]()->void
			{
				if (PossibleMoveState == false)
					return;
				MoveState = false;
				Player.Move(Vector3(1.0f, 0.0f, 0.0f), 1.0f);
			});
		_KeyInput.AddKey("PlayerMoveUp", Input::eKeyType::Up, Input::eButtonState::Hold, [this, &MoveState, PossibleMoveState, &RigidBody]()->void
			{
				if (PossibleMoveState == false)
					return;
				RigidBody.SetVelocity(Vector2(0.0f, 3.0f));
			});
		
		_KeyInput.AddKey("PlayerAttack", Input::eKeyType::Ctrl, Input::eButtonState::Tap, [this, &AttackTrigger, PossibleMoveState]()->void
			{
				AttackTrigger.SetTrigger();
			});

		auto Alert = StateMachine.GetState("Alert");
		Alert->SetEnterState([&PossibleMoveState]()->void
			{
				PossibleMoveState = true;
			});
		auto Walk = StateMachine.GetState("Walk");
		auto Attack = StateMachine.GetState("Attack");
		Attack->SetEnterState([&PossibleMoveState]()->void
			{
				PossibleMoveState = false;
			});

		StateCondition* Condition = new BoolCondition(&MoveState, true);
		AddTransition(StateMachine, Condition, Alert, Walk);

		Condition = new BoolCondition(&MoveState, false);
		AddTransition(StateMachine, Condition, Walk, Alert);

		Condition = new TriggerCondition(AttackTrigger);
		AddTransition(StateMachine, Condition, Alert, Attack);
		// Attack애니메이션 끝나면 바로 Alert로 돌아오기 위해서
		AddTransition(StateMachine, nullptr, Attack, Alert, false);

		StateMachine.SetCurrentState(Alert);
	}
}