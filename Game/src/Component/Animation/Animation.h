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
		Animation(float _FrameTime, bool _ForceQuit)
			: FrameTime(_FrameTime)
			, ProgressTime(0.0f)
			, CurrentFrame(0)
			, Finish(false)
			, ForceQuit(_ForceQuit)
			, FrameChange(true)
		{
			// 프레임입장할 때마다 이벤트 발생시켜야하기 때문에 -1프레임부터 시작
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
			ProgressTime = 0.0f;
			CurrentFrame = 0;
			Finish = false;
			FrameChange = true;
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

		int CurrentFrame;
		bool Finish;
		bool ForceQuit;
		bool FrameChange;
	};

	extern void AddFrameInfoToAnimation(Graphics::IDRGenerator& _Generator, Animation* _Anim, const std::vector<Str::FString>& _ImagePath
		, std::function<void()> _FrameEvent = nullptr);

}


