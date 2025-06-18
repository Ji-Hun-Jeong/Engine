#pragma once
#include "Class/Skill.h"

namespace Game
{
	class SwiftPhantom : public Skill
	{
		using Super = Skill;
	public:
		SwiftPhantom(Player& _RefPlayer)
			: Super("SwiftPhantom", _RefPlayer)
		{
		}
		~SwiftPhantom() {}

	public:
		void Cast() override
		{
			std::cout << "SwiftPhantom\n";
		}

	private:
		
	};
}


