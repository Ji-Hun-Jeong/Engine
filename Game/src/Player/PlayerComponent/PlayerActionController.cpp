#include "pch.h"
#include "PlayerActionController.h"

namespace Game
{
	PlayerActionController::PlayerActionController()
		: ActionController()
	{
		ActionController::AddActionQueue("BasicAction");
		ActionController::AddActionQueue("MoveAction");
		ActionController::AddActionQueue("CantMoveAction");
	}
	void PlayerActionController::ControllAction()
	{
		ActionQueue* CantMoveActions = getActionQueue("CantMoveAction");
		ActionQueue* MoveActions = getActionQueue("MoveAction");
		ActionQueue* BasicActions = getActionQueue("BasicAction");

		if(CantMoveActions->IsExistPreparedAction())
	}
}

