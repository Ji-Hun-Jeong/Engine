#include "pch.h"
#include "Action.h"

namespace Game
{
    Action::Action(const Str::FString& _ActionName, std::function<void()> _ActFunction)
		: ActionName(_ActionName)
		, ActFunction(_ActFunction)
		, ActionDelay(0.0f)
		, ActionDegree(0.0f)
		, AlreadyAct(false)
		, IsFinishAct(false)
	{
	}
	void Action::Act()
	{
		if (AlreadyAct == false)
		{
			ActFunction();
			AlreadyAct = true;
		}
		ActionDegree += Time::GetDT();

		if (ActionDelay <= ActionDegree)
			IsFinishAct = true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ActionPerformer::PerformActions()
	{
		Action* Action = nullptr;

		for (auto iter = BePerformedAction.begin(); iter != BePerformedAction.end(); )
		{
			Action = *iter;
			Action->Act();

			if (Action->IsFinish())
			{
				Action->ActInit();
				iter = BePerformedAction.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	ActionController::~ActionController()
	{
		for (auto iter = Actions.begin(); iter != Actions.end();)
		{
			delete iter->second;
			iter = Actions.erase(iter);
		}
	}
}