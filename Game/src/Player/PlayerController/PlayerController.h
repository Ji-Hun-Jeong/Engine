#pragma once
#include "Object/Object.h"

namespace Game
{
	class PlayerController : public Object
	{
		using Super = Object;
		CLONE(PlayerController, Object)
	public:
		PlayerController(class Player& _Player)
			: Super("PlayerController")
			, Player(_Player)
		{}
		~PlayerController() {}

	public:
		void InitObject() override;
		void Update() override;
		void Destory() override;
		void SetKeyInput(class KeyInput& _KeyInput);

	private:
		class Player& Player;
	};
}


