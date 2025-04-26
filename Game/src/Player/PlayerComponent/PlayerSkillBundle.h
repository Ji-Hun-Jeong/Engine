#pragma once

namespace Game
{
	class PlayerSkillBundle
	{
	public:
		PlayerSkillBundle(class Player* _Owner);
		PlayerSkillBundle(const PlayerSkillBundle&) = delete;
		~PlayerSkillBundle() = default;

	public:
		void UltimitDrive();

	private:
		class Player* Owner;

	};
}
