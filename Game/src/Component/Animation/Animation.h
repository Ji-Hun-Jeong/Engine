#pragma once
#include "Renderer/src/Interface/IShaderResource.h"

namespace Graphics
{
	class IRenderInterface;
	class IDRGenerator;
}

namespace Game
{
	class Animation
	{
	public:
		Animation(float _FrameTime, bool _Repeat, bool _ForceQuit)
			: FrameTime(_FrameTime)
			, ProgressTime(FrameTime)
			, CurrentFrame(-1)
			, Repeat(_Repeat)
			, Finish(false)
			, ForceQuit(_ForceQuit)
		{
		}
		~Animation() {}

	public:
		struct FrameInfo
		{
			RefCounterPtr<Graphics::IShaderResource> FrameImage;
			std::function<void()> FrameEvent;
		};
		void Update(std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface);

		void ResetAnimation()
		{
			ProgressTime = FrameTime;
			CurrentFrame = -1;
			Finish = false;
		}

		void AddFrameInfo(RefCounterPtr<Graphics::IShaderResource>& _Image, std::function<void()> _FrameEvent = nullptr)
		{
			FrameInfos.push_back({ _Image, _FrameEvent });
		}

		void SetForceQuit() { ForceQuit = true; }

		// Repeat이면 Finish로 강제로 만들어주기 전까지는 절대 true가 나오지 않음
		bool IsFinish() const { return Finish; }

		bool IsForceQuit() const { return ForceQuit; }

	private:
		std::vector<FrameInfo> FrameInfos;

		float FrameTime;
		float ProgressTime;

		UINT CurrentFrame;

		bool Repeat;
		bool Finish;
		bool ForceQuit;
	};

	extern void AddFrameInfoToAnimation(Graphics::IDRGenerator& _Generator, Animation* _Anim, const std::vector<Str::FString>& _ImagePath
		, std::function<void()> _FrameEvent = nullptr);

}


