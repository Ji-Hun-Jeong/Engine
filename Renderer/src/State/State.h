#pragma once
#include "StateCondition.h"

namespace Graphics
{
	class Animation;

	class RENDERER_API State
	{
	public:
		State(Animation* _Anim)
			: Anim(_Anim)
		{
		}
		State()
			: State(nullptr)
		{
		}
		~State()
		{
			if (Anim)
				delete Anim;
		}

	public:
		void SetAnimation(Animation* _Anim) { Anim = _Anim; }

	private:
		Animation* Anim;

	};

	class RENDERER_API StateTransition
	{
	public:

	private:

	};

	// StateMachine에 여러 자료형을 map으로 두고 증가감소 이런거 둔다음에 
	class RENDERER_API StateMachine
	{
	public:

	private:

	};
}
