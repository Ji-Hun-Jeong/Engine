#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"
#include "Player/PlayerController/PlayerController.h"
#include "Object/BackGround/BackGround.h"
#include "Object/Camera/Camera.h"
#include "Object/Camera/CameraController/CameraController.h"

namespace Game
{
	MyLevel::MyLevel(Graphics::IDRGenerator& _Generator)
		: Level(_Generator)
		, PixelCollisionProcess(_Generator)
	{
		CollisionMgr.TypeMapping("Player");
		CollisionMgr.TypeMapping("Monster");
	}

	MyLevel::~MyLevel()
	{
	}

	void MyLevel::InitLevel()
	{
		Super::InitLevel();

		CollisionMgr.BindCollisionWhether("Player", "Monster");

		{
			Camera* C = new Camera("sdf");
			auto ConstBuffer = C->InitalizeGlobalConst(Generator);
			Renderer.SetGlobalConst(ConstBuffer, 1);

			CameraController* Controller = new CameraController(*C);
			Controller->SetKeyInput(Input);
			AddObject(Controller);

			AddObject(C);
		}

		{
			auto MeshData = Geometry::GenerateUVRect(0.5f);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh);

			auto P = CreatePlayer(Generator, Model, CollisionMgr);
			P->InitPixelCollision(PixelCollisionProcess);

			AddObject(P);
			Renderer.AddModel(eLayer::Player, Model);

			PlayerController* Controller = new PlayerController(*P);
			Controller->SetKeyInput(Input);

			AddObject(Controller);
		}

		{
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = Generator.GenerateShaderResource({ "Game/resource/image/Map/MushroomStage/MushroomBackground.png" });
			Vector2 ImageSize = BackImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh);

			RenderInterface->SetImage(BackImage);
			Model->AddRenderInterface(RenderInterface);

			BackGround* Back = new BackGround("1");
			Back->InitalizeRerderInterface(Generator, RenderInterface);
			AddObject(Back);

			Renderer.AddModel(eLayer::BackGround, Model);
		}

		{
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = Generator.GenerateShaderResource
			({ 
				"Game/resource/image/Map/MushroomStage/MushroomStage.png",
				"Game/resource/image/Map/MushroomStage/Floor.bmp",
				"Game/resource/image/Map/MushroomStage/Wall.bmp",
				"Game/resource/image/Map/MushroomStage/Ladder.bmp",
				"Game/resource/image/Map/MushroomStage/Rope.bmp",
				"Game/resource/image/Map/MushroomStage/MonsterWall.bmp"
			});
			Vector2 ImageSize = BackImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh);

			RenderInterface->SetImage(BackImage);
			Model->AddRenderInterface(RenderInterface);

			BackGround* Back = new BackGround("2");
			Back->InitalizeRerderInterface(Generator, RenderInterface);
			auto C = CollisionMgr.GetRectCollider("Monster");
			C->SetSize(Back->GetScale());
			
			Back->SetCollider(C);
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
		PixelCollisionProcess.Progress();
	}

	void MyLevel::ExitLevel()
	{
		Super::ExitLevel();
	}
}