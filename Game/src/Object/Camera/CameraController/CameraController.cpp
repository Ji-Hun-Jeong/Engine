#include "pch.h"
#include "CameraController.h"

#include "Object/KeyInput/KeyInput.h"

namespace Game
{
	void CameraController::SetKeyInput(KeyInput& _KeyInput)
	{
		_KeyInput.AddKey("CameraMoveLeft", Input::eKeyType::A, Input::eButtonState::Hold, [this]()->void
			{
				ControlCamera.Move(Vector3(-1.0f, 0.0f, 0.0f), 0.2f);
			});
		_KeyInput.AddKey("CameraMoveRight", Input::eKeyType::D, Input::eButtonState::Hold, [this]()->void
			{
				ControlCamera.Move(Vector3(1.0f, 0.0f, 0.0f), 0.2f);
			});
		_KeyInput.AddKey("CameraMoveUp", Input::eKeyType::W, Input::eButtonState::Hold, [this]()->void
			{
				ControlCamera.Move(Vector3(0.0f, 1.0f, 0.0f), 0.2f);
			});
		_KeyInput.AddKey("CameraMoveDown", Input::eKeyType::S, Input::eButtonState::Hold, [this]()->void
			{
				ControlCamera.Move(Vector3(0.0f, -1.0f, 0.0f), 0.2f);
			});
	}
}
