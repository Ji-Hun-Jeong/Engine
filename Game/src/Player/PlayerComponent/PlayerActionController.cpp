#include "pch.h"
#include "PlayerActionController.h"

namespace Game
{
	PlayerActionController::PlayerActionController()
		: Super()
	{
		Super::AddPerformer("CantMoveAction", 1);
		Super::AddPerformer("MoveAction", 1);
		Super::AddPerformer("BasicAction", 5);
	}

	void PlayerActionController::controlAction()
	{
		ActionPerformer* BasicActionPerformer = getActionPerformer("BasicAction");
		ActionPerformer* MoveActionPerformer = getActionPerformer("MoveAction");
		ActionPerformer* CantMoveActionPerformer = getActionPerformer("CantMoveAction");

		if (CantMoveActionPerformer->IsExistPerformedAction())
		{
			MoveActionPerformer->ClearAction();
			BasicActionPerformer->ClearAction();
		}

	}
}

