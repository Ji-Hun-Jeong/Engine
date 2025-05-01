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
		explicit TestLevel(Graphics::DX::DXRGenerator& _Generator);
		~TestLevel();

	public:
		void InitLevel() override;
		void EnterLevel() override;
		void Update() override;
		void ExitLevel() override;
		void Render(Graphics::RenderContext* _RenderContext) override;

	private:
		Graphics::DX::DXRGenerator& Generator;
		Graphics::IGraphicProcess* GraphicProcess;
	};
}


