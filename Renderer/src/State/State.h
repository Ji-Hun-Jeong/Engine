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

	// StateMachine�� ���� �ڷ����� map���� �ΰ� �������� �̷��� �д����� 
	class RENDERER_API StateMachine
	{
	public:

	private:

	};
}
