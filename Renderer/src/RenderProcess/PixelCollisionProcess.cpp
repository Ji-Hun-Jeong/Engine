#include "pch.h"
#include "PixelCollisionProcess.h"

namespace Graphics
{
	void PixelCollisionInterface::SetActive(bool _TF)
	{
		Processor.SetActiveInterface(Index, _TF);
	}
}