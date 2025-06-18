#pragma once
#include "Skill.h"

#include "Object/KeyInput/KeyInput.h"

namespace Game
{
	class Class
	{
	public:
		Class(const Str::FString& _ClassName)
			: ClassName(_ClassName)
		{ }
		virtual ~Class() = 0
		{
		}

	public:
		virtual void InitClass(Player& _RefPlayer) = 0;
		virtual void AddSkillToInput(KeyInput& _KeyInput) = 0;

		const Str::FString& GetName() const { return ClassName; }

	protected:
		void addSkill(UINT _Degree, Skill* _Skill)
		{
			SkillMgr.AddSkill(_Degree, _Skill);
		}

	protected:
		Str::FString ClassName;
		SkillManager SkillMgr;

	};

	class ClassManager
	{
	public:
		ClassManager();
		~ClassManager()
		{
			for (auto& Pair : Classes)
				delete Pair.second;
		}

	public:
		void AttachClassToPlayer(Player& _RefPlayer, const Str::FString& _ClassName)
		{
			auto Iter = Classes.find(_ClassName);
			PlayerClass = Iter->second;

			if (PlayerClass)
				PlayerClass->InitClass(_RefPlayer);
		}
		void AddToInput(KeyInput& _KeyInput)
		{
			if (PlayerClass)
				PlayerClass->AddSkillToInput(_KeyInput);
		}

	private:
		void registClass(Class* _Class)
		{
			Classes.insert(std::make_pair(_Class->GetName(), _Class));
		}

	private:
		std::map<Str::FString, Class*> Classes;

		Class* PlayerClass;

	};
}