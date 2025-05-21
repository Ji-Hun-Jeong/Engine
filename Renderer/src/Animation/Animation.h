#pragma once
#include "Render/IDRGenerator.h"

namespace Graphics
{
	class RENDERER_API Animation
	{
	public:
		Animation(float _FrameTime, bool _Repeat)
			: FrameTime(_FrameTime)
			, ProgressTime(FrameTime)
			, CurrentFrame(-1)
			, Repeat(_Repeat)
			, Finish(false)
		{}
		~Animation() {}

	public:
		struct FrameInfo
		{
			RefCounterPtr<class IShaderResource> FrameImage;
			std::function<void()> FrameEvent;
		};

		void ResetAnimation()
		{
			ProgressTime = FrameTime;
			CurrentFrame = -1;
		}

		void AddFrameInfo(RefCounterPtr<IShaderResource>& _Image, std::function<void()> _FrameEvent = nullptr)
		{
			FrameInfos.push_back({ _Image, _FrameEvent });
		}

		bool IsFinish() const { return Finish; }

		bool IsRepeat() const { return Repeat; }

	private:
		std::vector<FrameInfo> FrameInfos;

		float FrameTime;
		float ProgressTime;

		UINT CurrentFrame;

		bool Repeat;
		bool Finish;
	};


	/*class RENDERER_API Animator
	{
	public:
		Animator()
			: CurrentAnimation(nullptr)
		{
		}
		~Animator()
		{
			for (auto& Animation : Animations)
				delete Animation.second;
		}

	public:
		void AddAnimation(const Str::FString& _AnimationName, Animation* _Animation)
		{
			Animations.insert(std::make_pair(_AnimationName, _Animation));
		}

		void SetCurrentAnimation(const Str::FString& _AnimationName)
		{
			if (CurrentAnimation)
				CurrentAnimation->ResetAnimation();

			CurrentAnimation = Animations.find(_AnimationName)->second;
		}

		void SetCurrentAnimation(Animation* _Animation)
		{
			if (CurrentAnimation)
				CurrentAnimation->ResetAnimation();

			CurrentAnimation = _Animation;
		}

		Animation* FindAnimation(const Str::FString& _AnimationName)
		{
			auto Iter = Animations.find(_AnimationName);
			if (Iter == Animations.end())
				return nullptr;
			return Iter->second;
		}

	private:
		std::map<Str::FString, Animation*> Animations;
		Animation* CurrentAnimation;

	};*/
}

