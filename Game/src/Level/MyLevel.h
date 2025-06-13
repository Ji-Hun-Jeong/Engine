#pragma once
#include "Level/Level.h"

#include <Renderer/src/RenderProcess/PixelCollisionProcess.h>

namespace Game
{
	class MyLevel : public Level
	{
		using Super = Level;
	public:
		explicit MyLevel(Graphics::IDRGenerator& _Generator, Graphics::GraphicResourceMgr& _GRM);
		~MyLevel();

	public:
		void InitResource() override;
		void InitLevel() override;
		void EnterLevel() override;
		void Update() override;
		void PostUpdate() override;
		void ExitLevel() override;
		void InitCamera(UINT _ScreenWidth, UINT _ScreenHeight) override;

	private:
		Graphics::PixelCollisionProcess PixelCollisionProcess;

	};
}


