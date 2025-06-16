#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"
#include "Player/PlayerController/PlayerController.h"
#include "Object/BackGround/BackGround.h"
#include "Object/Camera/Camera.h"
#include "Object/Camera/CameraController/CameraController.h"


namespace Game
{
	MyLevel::MyLevel(Graphics::IDRGenerator& _Generator, Graphics::GraphicResourceMgr& _GRM)
		: Level(_Generator, _GRM)
		, PixelCollisionProcess(_Generator)
	{
		CollisionMgr.TypeMapping("Player");
		CollisionMgr.TypeMapping("Monster");
	}

	MyLevel::~MyLevel()
	{
	}

	void MyLevel::InitResource()
	{
		auto MeshData = Geometry::GenerateUVRect(0.5f);

		auto& Vertices = MeshData.Vertices;
		auto& Indices = MeshData.Indices;

		auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
			, Indices.data(), sizeof(Indices[0]), Indices.size());

		GRM.AddMesh("BasicRect", Mesh);

		auto BackgroundImage = Generator.GenerateShaderResource({ "Game/resource/image/Map/MushroomStage/MushroomBackground.png" });
		GRM.AddShaderResource("MushroomBackground", BackgroundImage);

		auto BackImage = Generator.GenerateShaderResource
		({
			"Game/resource/image/Map/MushroomStage/MushroomStage.png",
			"Game/resource/image/Map/MushroomStage/Floor.bmp",
			"Game/resource/image/Map/MushroomStage/Wall.bmp",
			"Game/resource/image/Map/MushroomStage/Ladder.bmp",
			"Game/resource/image/Map/MushroomStage/Rope.bmp",
			"Game/resource/image/Map/MushroomStage/MonsterWall.bmp"
		});
		BackImage->PSSetShaderResources(0);
		BackImage->CSSetShaderResources(0);
		GRM.AddShaderResource("MushroomStage", BackImage);

		const std::vector<Graphics::InputElementDesc> InputElement =
		{
			{Graphics::eSementicName::Position, Graphics::eFormat::Vector3, 0, Graphics::eInputClass::VertexData},
			{Graphics::eSementicName::UV, Graphics::eFormat::Vector2, 12, Graphics::eInputClass::VertexData}
		};

		auto ImageVS = Generator.GenerateVertexShaderAndInputLayout("./Renderer/resource/Shader/ImageVS.hlsl"
			, InputElement);
		GRM.AddVertexShader("ImageVS", ImageVS);

		auto TriangleTopology = Generator.GenerateTopology(Graphics::eTopology::Triangle);
		GRM.AddTopology("Triangle", TriangleTopology);

		auto ImagePS = Generator.GeneratePixelShader("./Renderer/resource/Shader/ImagePS.hlsl");
		GRM.AddPixelShader("ImagePS", ImagePS);

		auto BackGroundPS = Generator.GeneratePixelShader("./Renderer/resource/Shader/BackGroundPS.hlsl");
		GRM.AddPixelShader("BackGroundPS", BackGroundPS);
	}

	void MyLevel::InitCamera(UINT _ScreenWidth, UINT _ScreenHeight)
	{
		Camera* C = new Camera("sdf", _ScreenWidth, _ScreenHeight);
		auto ConstBuffer = C->InitalizeGlobalConst(Generator);
		Renderer.SetGlobalConst(ConstBuffer, 1);

		CameraController* Controller = new CameraController(*C);
		Controller->SetKeyInput(Input);
		AddObject(Controller);

		AddObject(C);
	}

	void MyLevel::InitLevel()
	{
		Super::InitLevel();

		CollisionMgr.BindCollisionWhether("Player", "Monster");

		{
			auto Model = Graphics::MakeModel(GRM, "BasicRect", "Triangle", "ImageVS", "ImagePS");

			auto P = CreatePlayer(Generator, Model, CollisionMgr);
			P->InitPixelCollision(PixelCollisionProcess);
			Collision::RigidBody* RB = new Collision::RigidBody(P->GetPositionRef());
			RB->SetMass(0.01f);
			P->SetRigidBody(RB);

			AddObject(P);
			Renderer.AddModel(eLayer::Player, Model);

			PlayerController* Controller = new PlayerController(*P);
			Controller->SetKeyInput(Input);

			AddObject(Controller);
		}

		auto TriangleToplogy = GRM.GetTopology("Triangle");
		auto ImageVS = GRM.GetVertexShader("ImageVS");
		auto ImagePS = GRM.GetPixelShader("ImagePS");
		auto BackGroundPS = GRM.GetPixelShader("BackGroundPS");

		{
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = GRM.GetShaderResource("MushroomBackground");
			Vector2 ImageSize = BackImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh, TriangleToplogy, ImageVS, ImagePS);

			RenderInterface->SetImage(BackImage);
			Model->AddRenderInterface(RenderInterface);

			BackGround* Back = new BackGround("1");
			Back->InitalizeRerderInterface(Generator, RenderInterface);
			AddObject(Back);

			Renderer.AddModel(eLayer::BackGround, Model);
		}

		{
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = GRM.GetShaderResource("MushroomStage");
			Vector2 ImageSize = BackImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			auto Model = std::make_shared<Graphics::Model>(Mesh, TriangleToplogy, ImageVS, BackGroundPS);

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

	void MyLevel::PostUpdate()
	{
		Super::PostUpdate();

	}

	void MyLevel::ExitLevel()
	{
		Super::ExitLevel();
	}

	
}