#include "pch.h"
#include "IRenderInterface.h"

namespace Graphics
{
	void Animation::Update(UINT _StartSlot)
	{
		ProgressTime += GraphicsTime::GetDT();

		if (FrameTime <= ProgressTime)
		{
			CurrentFrame += 1;
			ProgressTime = 0.0f;
		}

		if (Images.size() <= CurrentFrame)
			CurrentFrame = 0;

		Images[CurrentFrame]->VSSetShaderResources(_StartSlot);
		Images[CurrentFrame]->PSSetShaderResources(_StartSlot);
	}
}