#pragma once
#include "Component/Action/Action.h"

namespace Game
{
	class PlayerActionController : public ActionController
	{
		using Super = ActionController;
	public:
		PlayerActionController();
		~PlayerActionController() = default;

	public:
		void controlAction() override;

	};
}


