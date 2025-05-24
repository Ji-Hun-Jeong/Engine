#include "pch.h"
#include "Animation.h"

namespace Graphics
{
	void Animation::Update(RenderInterface& _RenderInterface)
	{
		ProgressTime += GraphicsTime::GetDT();
		Finish = false;

		bool Reset = false;
		if (FrameTime <= ProgressTime)
		{
			CurrentFrame += 1;
			ProgressTime = 0.0f;

			if (FrameInfos.size() <= CurrentFrame)
			{
				CurrentFrame = FrameInfos.size() - 1;
				Finish = true;
				if (Repeat)
					Reset = true;

				// �̰� �������� ������ �� �� �����Ӹ� �ѹ� �� �׸��� �뵵�̱� ������ �� ������ �׸��� �۾� �ܿ� �ƹ��͵� ������ �ȉ�
			}
			else if (FrameInfos[CurrentFrame].FrameEvent)
				FrameInfos[CurrentFrame].FrameEvent();
		}
		_RenderInterface.SetImage(FrameInfos[CurrentFrame].FrameImage);

		if (Reset)
			ResetAnimation();
	}
}