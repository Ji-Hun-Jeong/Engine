#pragma once
#include "Animation.h"

namespace Game
{
	enum class EAnimationPriority
	{
		Base,
		Skill,
	};

	struct AnimationNode
	{
		UINT Priority;
		Animation* Anim;

		bool operator < (const AnimationNode& _AnimNode) const
		{
			return Priority < _AnimNode.Priority;
		}
	};

	class Animator
	{
	public:
		Animator(std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface)
			: RenderInterface(_RenderInterface)
			, CurrentAnimation(nullptr)
		{
		}
		~Animator() {}

	public:
		void Update()
		{
			if (CurrentAnimation->IsFinish())
				CurrentAnimation->ResetAnimation();
			CurrentAnimation->Update(RenderInterface);
		}

		void SetCurrentAnimation(Animation* _Animation)
		{
			if (CurrentAnimation)
				CurrentAnimation->ResetAnimation();
			CurrentAnimation = _Animation;
		}

		bool CurrentAnimationSkip() const
		{
			bool Skip = CurrentAnimation->IsForceQuit() || CurrentAnimation->IsFinish();
			return Skip;
		}

	private:
		Animation* CurrentAnimation;
		
		std::shared_ptr<Graphics::IRenderInterface>& RenderInterface;

	};
}