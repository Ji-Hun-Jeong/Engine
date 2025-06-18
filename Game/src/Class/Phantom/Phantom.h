#pragma once
#include "Class/Class.h"

namespace Game
{
	class Phantom :	public Class
	{
		using Super = Class;
	public:
		Phantom()
			: Super("Phantom")
		{}
		~Phantom() {}

	public:
		void InitClass(Player& _RefPlayer) override;
		void AddSkillToInput(KeyInput& _KeyInput) override;

	private:
		

	};
}


