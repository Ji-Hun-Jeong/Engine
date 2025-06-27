#include "pch.h"
#include "Animation.h"
#include <Engine/src/Time/Time.h>
#include <Renderer/src/Render/IRenderInterface.h>

namespace Game
{
	void Animation::Update(std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface)
	{
		ProgressTime += Time::GetDT();

		bool Reset = false;
		if (FrameTime <= ProgressTime)
		{
			CurrentFrame += 1;
			ProgressTime = 0.0f;

			if (FrameInfos.size() <= CurrentFrame)
			{
				CurrentFrame = FrameInfos.size() - 1;
				if (Repeat)
					Reset = true;
				else
					Finish = true;

				// 이건 마지막에 종료할 때 끝 프레임만 한번 더 그리는 용도이기 때문에 이 밑으로 그리는 작업 외엔 아무것도 있으면 안됌
			}
			else if (FrameInfos[CurrentFrame].FrameEvent)
				FrameInfos[CurrentFrame].FrameEvent();
		}
		_RenderInterface->SetImage(FrameInfos[CurrentFrame].FrameImage);

		if (Reset)
			ResetAnimation();
	}

	void AddFrameInfoToAnimation(Graphics::IDRGenerator& _Generator, Animation* _Anim, const std::vector<Str::FString>& _ImagePath, std::function<void()> _FrameEvent)
	{
		auto SRV = _Generator.GenerateShaderResource(_ImagePath);
		_Anim->AddFrameInfo(SRV, _FrameEvent);
	}
}