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

	//			// 이건 마지막에 종료할 때 끝 프레임만 한번 더 그리는 용도이기 때문에 이 밑으로 그리는 작업 외엔 아무것도 있으면 안됌
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