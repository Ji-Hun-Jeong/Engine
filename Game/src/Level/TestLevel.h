#pragma once
#include "Level/Level.h"
#include "Renderer/src/Platform/DirectX/DXRGenerator.h"
#include "Renderer/src/Render/IRenderer.h"
namespace Game
{
	class TestLevel : public Level
	{
		using Super = Level;
	public:
		explicit TestLevel(Graphics::IDRGenerator& _Generator);
		~TestLevel();

	public:
		void InitLevel() override;
		void EnterLevel() override;
		void Update() override;
		void ExitLevel() override;
		void Render() override;

	private:
		Graphics::IDRGenerator& Generator;
		Graphics::IGraphicProcess& GraphicProcess;
	};
}


