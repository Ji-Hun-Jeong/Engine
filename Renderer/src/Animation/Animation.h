#pragma once
#include "Render/IRenderInterface.h"

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
		void Update(IRenderInterface& _RenderInterface);

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

	extern void RENDERER_API AddFrameInfoToAnimation(Graphics::IDRGenerator& _Generator, Graphics::Animation* _Anim, const std::vector<Str::FString>& _ImagePath
		, std::function<void()> _FrameEvent = nullptr);
}

