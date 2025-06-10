#pragma once
#include "Object/Camera/Camera.h"

namespace Game
{
	class CameraController : public Object
	{
		using Super = Object;
		CLONE(CameraController, Object)
	public:
		CameraController(Camera& _ControlCamera)
			: Super("CameraController")
			, ControlCamera(_ControlCamera)
		{}
		~CameraController() {}

	public:
		void SetKeyInput(class KeyInput& _KeyInput);

	private:
		Camera& ControlCamera;
	};
}

