#include "pch.h"
#include "IRenderInterface.h"

namespace Graphics
{
	void Animation::Update(UINT _StartSlot)
	{
		ProgressTime += GraphicsTime::GetDT();
		Finish = false;

		if (FrameTime <= ProgressTime)
		{
			CurrentFrame += 1;
			ProgressTime = 0.0f;

			if (Images.size() <= CurrentFrame)
			{
				CurrentFrame = 0;
				Finish = true;
			}
		}

		Images[CurrentFrame]->VSSetShaderResources(_StartSlot);
		Images[CurrentFrame]->PSSetShaderResources(_StartSlot);

		Notify();
	}
}