#include "pch.h"
#include "PlayerSkillBundle.h"
#include "Player/Player.h"

namespace Game
{
	PlayerSkillBundle::PlayerSkillBundle(Player* _Owner)
		: Owner(_Owner)
	{

	}
	void PlayerSkillBundle::UltimitDrive()
	{
		std::cout << "UltimitDrive!\n";
	}
}