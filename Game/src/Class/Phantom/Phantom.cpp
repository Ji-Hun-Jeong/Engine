#include "pch.h"
#include "Phantom.h"
#include "Class/Phantom/Skill/1/SwiftPhantom.h"

namespace Game
{
	void Phantom::InitClass(Player& _RefPlayer)
	{
		addSkill(1, new SwiftPhantom(_RefPlayer));
	}
	void Phantom::AddSkillToInput(KeyInput& _KeyInput)
	{
		Skill* S = SkillMgr.GetSkill(1, "SwiftPhantom");
		_KeyInput.AddKey("SwiftPhantom", Input::eKeyType::Q, Input::eButtonState::Tap, std::bind(&Skill::Cast, S));
	}
}