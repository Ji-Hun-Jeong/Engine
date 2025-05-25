#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"
#include "Player/PlayerController/PlayerController.h"
#include "Object/BackGround/BackGround.h"

namespace Game
{
	MyLevel::MyLevel(Graphics::IDRGenerator& _Generator)
		: Level(_Generator)
	{

	}

	MyLevel::~MyLevel()
	{
	}

	void MyLevel::InitLevel()
	{
		Super::InitLevel();

		{
			auto MeshData = Geometry::GenerateUVRect();

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh);

			auto P = CreatePlayer(Generator, Model);

			AddObject(P);
			Renderer.AddModel(eLayer::Player, Model);

			PlayerController* Controller = new PlayerController(*P);
			Controller->SetKeyInput(Input);

			AddObject(Controller);
		}

		{
			auto MeshData = Geometry::GenerateUVRect(1280.0f / 960.0f);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh);

			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = Generator.GenerateShaderResource({ "Game/resource/image/Map/MushroomStage/MushroomStage.png" });
			RenderInterface->SetImage(BackImage);
			Model->AddRenderInterface(RenderInterface);

			BackGround* Back = new BackGround;
			Back->InitalizeRerderInterface(Generator, RenderInterface);
			AddObject(Back);

			Renderer.AddModel(eLayer::BackGround, Model);
		}
		
	}

	void MyLevel::EnterLevel()
	{
		Super::EnterLevel();
	}

	void MyLevel::Update()
	{
		Super::Update();
	}

	void MyLevel::ExitLevel()
	{
		Super::ExitLevel();
	}
}