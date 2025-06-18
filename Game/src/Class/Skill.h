#pragma once
#include "Object/Player/Player.h"

namespace Game
{
	class Skill
	{
	public:
		Skill(const Str::FString& _SkillName, Player& _RefPlayer)
			: SkillName(_SkillName)
			, RefPlayer(_RefPlayer)
		{}
		virtual ~Skill() {}

	public:
		virtual void Cast() = 0;

		const Str::FString& GetSkillName() const { return SkillName; }

	protected:
		Str::FString SkillName;
		Player& RefPlayer;
	};

	class SkillManager
	{
	public:
		SkillManager() {}
		~SkillManager()
		{
			for (size_t i = 0; i < 5; ++i)
			{
				for (auto& Pair : Skills[i])
					delete Pair.second;
			}
		}

	public:
		void AddSkill(UINT _Degree, Skill* _Skill)
		{
			Skills[_Degree].insert(std::make_pair(_Skill->GetSkillName(), _Skill));
		}
		Skill* GetSkill(UINT _Degree, const Str::FString& _SkillName)
		{
			auto Iter = Skills[_Degree].find(_SkillName);
			if (Iter == Skills[_Degree].end())
				return nullptr;
			return Iter->second;
		}

	private:
		std::map<Str::FString, Skill*> Skills[5];

	};
}