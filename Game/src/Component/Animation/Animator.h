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
		void Initalize(Animation* _Animation)
		{
			CurrentAnimation = _Animation;
		}

		void Update()
		{
			CurrentAnimation->Update(RenderInterface);

			if (CurrentAnimation->IsFinish() || CurrentAnimation->IsForceQuit())
			{
				CurrentAnimation->ResetAnimation();
				CurrentAnimation = AnimationQueue.top().Anim;
				AnimationQueue.pop();
			}
		}

		void ReserveNextAnimation(EAnimationPriority _Priority, Animation* _Animation)
		{
			if (CurrentAnimation == _Animation)
				return;
			AnimationQueue.push(AnimationNode(UINT(_Priority), _Animation));
		}

	private:
		Animation* CurrentAnimation;
		
		std::priority_queue<AnimationNode, std::vector<AnimationNode>> AnimationQueue;

		std::shared_ptr<Graphics::IRenderInterface>& RenderInterface;

	};
}