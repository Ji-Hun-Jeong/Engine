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
		bool* MoveState = StateTable.RegistBool("Move", false);

		_KeyInput.AddKey("MoveLeft", Input::eKeyType::A, Input::eButtonState::Hold, [this, MoveState]()->void
			{
				*MoveState = true;
				Player.Move(-1.0f);
			});
		_KeyInput.AddKey("MoveRight", Input::eKeyType::D, Input::eButtonState::Hold, [this, MoveState]()->void
			{
				*MoveState = false;
				Player.Move(1.0f);
			});

		auto Alert = StateMachine.GetState("Alert");
		auto Walk = StateMachine.GetState("Walk");

		Graphics::StateCondition* Condition = new Graphics::BoolCondition(MoveState, true);
		Graphics::AddTransition(StateMachine, Condition, *Alert, *Walk);

		Condition = new Graphics::BoolCondition(MoveState, false);
		Graphics::AddTransition(StateMachine, Condition, *Walk, *Alert);

		StateMachine.SetCurrentState(Alert);
	}
}