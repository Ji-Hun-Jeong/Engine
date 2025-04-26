#pragma once

namespace Game
{
	class Skill
	{
	public:
		Skill(const Str::FString& _SkillName, float _SkillDelay, std::function<void()> _SkillAction)
			: SkillName(_SkillName)
			, SkillDelay(_SkillDelay)
			, SkillAction(_SkillAction)
		{}
		Skill(const Skill&) = delete;
		~Skill() {}

	public:
		std::function<void()> GetSkillAction() { return SkillAction; }
		const Str::FString& GetSkillName() const { return SkillName; }
		float GetSkillDelay() const { return SkillDelay; }

	private:
		Str::FString SkillName;
		float SkillDelay;

		std::function<void()> SkillAction;

	};

	class SkillManagement
	{
	public:
		SkillManagement(const Str::FString& _ManagementName)
			:ManagementName(_ManagementName)
		{}
		SkillManagement(const SkillManagement&) = delete;
		~SkillManagement()
		{
			for (auto& Skill : Skills)
				delete Skill.second;
		}

	public:
		void AddSkill(Skill* _Skill)
		{
			const Str::FString& SkillName = _Skill->GetSkillName();
			auto Iter = Skills.find(SkillName);
			if (Iter != Skills.end())
				return;
			Skills.insert(std::make_pair(SkillName, _Skill));
		}

		Skill* GetSkill(const Str::FString& _SkillName)
		{
			auto Iter = Skills.find(_SkillName);
			if (Iter == Skills.end())
				return nullptr;
			return Iter->second;
		}

		const Str::FString& GetManagementName() const { return ManagementName; }

	private:
		std::map<Str::FString, Skill*> Skills;

		Str::FString ManagementName;

	};

	class SkillManager
	{
	public:
		SkillManager() {}
		SkillManager(const SkillManager&) = delete;
		~SkillManager()
		{
			for (auto& SkillManagement : SkillManagements)
				delete SkillManagement.second;
		}

	public:
		void AddManagement(const Str::FString& _ManagementName)
		{
			auto Iter = SkillManagements.find(_ManagementName);
			if (Iter != SkillManagements.end())
				return;
			SkillManagements.insert(std::make_pair(_ManagementName, new SkillManagement(_ManagementName)));
		}
		void AddSkillToManagement(const Str::FString& _ManagementName, Skill* _Skill)
		{
			auto Iter = SkillManagements.find(_ManagementName);
			if (Iter == SkillManagements.end())
				return;

			Iter->second->AddSkill(_Skill);
		}
		Skill* GetSkill(const Str::FString& _ManagementName, const Str::FString& _SkillName)
		{
			auto ManagementIter = SkillManagements.find(_ManagementName);
			if (ManagementIter == SkillManagements.end())
				return nullptr;
			Skill* FindSkill = ManagementIter->second->GetSkill(_SkillName);

			return FindSkill;
		}

	private:
		std::map<Str::FString, SkillManagement*> SkillManagements;

	};

}
