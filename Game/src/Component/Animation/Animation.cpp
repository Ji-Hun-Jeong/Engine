#include "pch.h"
#include "Animation.h"
#include <Engine/src/Time/Time.h>
#include <Renderer/src/Render/IRenderInterface.h>

namespace Game
{
	void Animation::Update(std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface)
	{
		ProgressTime += Time::GetDT();

		_RenderInterface->SetImage(FrameInfos[CurrentFrame].FrameImage);

		if (FrameTime <= ProgressTime)
		{
			CurrentFrame += 1;
			ProgressTime = 0.0f;

			if (FrameInfos.size() <= CurrentFrame)
				Finish = true;
			else
				FrameChange = true;
		}

		// 만약 프레임이 바뀌었으면 이벤트 실행시키고 Change 변수를 다시 true로 만들기전까지는 안들어오게
		if (FrameChange == false)
			return;

		if (FrameInfos[CurrentFrame].FrameEvent)
			FrameInfos[CurrentFrame].FrameEvent();

		FrameChange = false;
	}

	void AddFrameInfoToAnimation(Graphics::IDRGenerator& _Generator, Animation* _Anim, const std::vector<Str::FString>& _ImagePath, std::function<void()> _FrameEvent)
	{
		auto SRV = _Generator.GenerateShaderResource(_ImagePath);
		_Anim->AddFrameInfo(SRV, _FrameEvent);
	}
}