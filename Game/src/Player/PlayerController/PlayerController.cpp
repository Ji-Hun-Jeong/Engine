#include "pch.h"
#include "PlayerController.h"
#include "Player/Player.h"
#include "Object/KeyInput/KeyInput.h"

#include <Renderer/src/State/State.h>

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
		Graphics::StateVariableTable& StateTable = Player.GetStateTable();
		Graphics::StateMachine& StateMachine = Player.GetStateMachine();

		bool& MoveState = StateTable.RegistBool("Move", false);
		bool& PossibleMoveState = StateTable.RegistBool("PossibleMove", true);
		Graphics::TriggerVariable& AttackTrigger = StateTable.RegistTrigger("Attack");

		_KeyInput.AddKey("MoveLeft", Input::eKeyType::Left, Input::eButtonState::Hold, [this, &MoveState, PossibleMoveState]()->void
			{
				if (PossibleMoveState == false)
					return;
				MoveState = true;
				Player.Move(-1.0f);
			});
		_KeyInput.AddKey("MoveRight", Input::eKeyType::Right, Input::eButtonState::Hold, [this, &MoveState, PossibleMoveState]()->void
			{
				if (PossibleMoveState == false)
					return;
				MoveState = false;
				Player.Move(1.0f);
			});
		_KeyInput.AddKey("Attack", Input::eKeyType::Ctrl, Input::eButtonState::Tap, [this, &AttackTrigger, PossibleMoveState]()->void
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

		Graphics::StateCondition* Condition = new Graphics::BoolCondition(&MoveState, true);
		Graphics::AddTransition(StateMachine, Condition, Alert, Walk);

		Condition = new Graphics::BoolCondition(&MoveState, false);
		Graphics::AddTransition(StateMachine, Condition, Walk, Alert);

		Condition = new Graphics::TriggerCondition(AttackTrigger);
		Graphics::AddTransition(StateMachine, Condition, Alert, Attack);
		// Attack애니메이션 끝나면 바로 Alert로 돌아오기 위해서
		Graphics::AddTransition(StateMachine, nullptr, Attack, Alert, false);

		StateMachine.SetCurrentState(Alert);
	}
}