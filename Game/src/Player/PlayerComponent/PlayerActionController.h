#pragma once
#include "Base/Action.h"

namespace Game
{
	class PlayerActionController : public ActionController
	{
	public:
		PlayerActionController();
		~PlayerActionController() = default;

	public:
		void ControllAction() override;

	};
}


