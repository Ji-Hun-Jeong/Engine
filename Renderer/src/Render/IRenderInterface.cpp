#include "pch.h"
#include "IRenderInterface.h"

namespace Graphics
{
	//void Animation::Update(UINT _StartSlot)
	//{
	//	ProgressTime += GraphicsTime::GetDT();
	//	Finish = false;

	//	bool Reset = false;
	//	if (FrameTime <= ProgressTime)
	//	{
	//		CurrentFrame += 1;
	//		ProgressTime = 0.0f;

	//		if (FrameInfos.size() <= CurrentFrame)
	//		{
	//			CurrentFrame = FrameInfos.size() - 1;
	//			Finish = true;
	//			if (Repeat)
	//				Reset = true;

	//			// �̰� �������� ������ �� �� �����Ӹ� �ѹ� �� �׸��� �뵵�̱� ������ �� ������ �׸��� �۾� �ܿ� �ƹ��͵� ������ �ȉ�
	//		}
	//		else if (FrameInfos[CurrentFrame].FrameEvent)
	//			FrameInfos[CurrentFrame].FrameEvent();
	//	}
	//	FrameInfos[CurrentFrame].FrameImage->VSSetShaderResources(_StartSlot);
	//	FrameInfos[CurrentFrame].FrameImage->PSSetShaderResources(_StartSlot);

	//	Notify();
	//	
	//	if (Reset)
	//		ResetAnimation();
	//}
}