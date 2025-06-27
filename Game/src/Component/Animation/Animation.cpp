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

				// �̰� �������� ������ �� �� �����Ӹ� �ѹ� �� �׸��� �뵵�̱� ������ �� ������ �׸��� �۾� �ܿ� �ƹ��͵� ������ �ȉ�
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