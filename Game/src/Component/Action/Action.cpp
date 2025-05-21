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
			if (ActFunction)
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
				++iter;
		}
	}
	ActionController::~ActionController()
	{
		for (auto& Pair : Actions)
		{
			delete Pair.second;
		}

		for (auto& Pair : ActionPerformers)
		{
			delete Pair.second;
		}
	}
	void ActionController::Update()
	{
		// insertToPerformer(); // 실행 대기 중인 액션을 퍼포머에 추가

		controlAction(); // 사용자 정의 액션 컨트롤
		for (auto& Performer : ActionPerformers)
			Performer.second->PerformActions(); // 실제 액션 수행
	}
}