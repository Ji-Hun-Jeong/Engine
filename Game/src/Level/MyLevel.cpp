#include "pch.h"
#include "MyLevel.h"
#include "Object/Player/Player.h"
#include "Object/Player/PlayerController/PlayerController.h"
#include "Object/BackGround/BackGround.h"
#include "Object/Camera/Camera.h"
#include "Object/Camera/CameraController/CameraController.h"


namespace Game
{
	MyLevel::MyLevel()
		: Level()
		, PixelCollisionProcess(nullptr)
	{
		CollisionMgr.TypeMapping("Player");
		CollisionMgr.TypeMapping("Monster");
	}

	MyLevel::~MyLevel()
	{
		if (PixelCollisionProcess)
			delete PixelCollisionProcess;
	}

	void MyLevel::InitCamera(UINT _ScreenWidth, UINT _ScreenHeight)
	{
		Camera* C = new Camera("sdf", _ScreenWidth, _ScreenHeight);
		auto ConstBuffer = C->InitalizeGlobalConst(*Generator);
		Renderer->SetGlobalConst(ConstBuffer, 1);

		CameraController* Controller = new CameraController(*C);
		Controller->SetKeyInput(*Input);
		AddObject(Controller);

		AddObject(C);
	}

	void MyLevel::InitRenderer(Graphics::IDRGenerator* _Generator, Graphics::GraphicResourceMgr* _GRM)
	{
		Super::InitRenderer(_Generator, _GRM);
		PixelCollisionProcess = new Graphics::PixelCollisionProcess(*Generator);

		{
			auto MeshData = Geometry::GenerateUVRect(0.5f);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator->GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());

			GRM->AddMesh("BasicRect", Mesh);
		}

		{
			auto BackgroundImage = Generator->GenerateShaderResource({ "Game/resource/image/Map/MushroomStage/MushroomBackground.png" });
			GRM->AddShaderResource("MushroomBackground", BackgroundImage);

			Vector2 ImageSize = BackgroundImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator->GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			GRM->AddMesh("MushroomBackground", Mesh);
		}

		{
			auto BackImage = Generator->GenerateShaderResource
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
			GRM->AddShaderResource("MushroomStage", BackImage);

			Vector2 ImageSize = BackImage->GetImageSize(0);

			auto MeshData = Geometry::GenerateUVRect(ImageSize.x, ImageSize.y);

			auto& Vertices = MeshData.Vertices;
			auto& Indices = MeshData.Indices;

			auto Mesh = Generator->GenerateMesh(Vertices.data(), sizeof(Vertices[0]), Vertices.size()
				, Indices.data(), sizeof(Indices[0]), Indices.size());
			GRM->AddMesh("MushroomStage", Mesh);
		}

		const std::vector<Graphics::InputElementDesc> InputElement =
		{
			{Graphics::eSementicName::Position, Graphics::eFormat::Vector3, 0, Graphics::eInputClass::VertexData},
			{Graphics::eSementicName::UV, Graphics::eFormat::Vector2, 12, Graphics::eInputClass::VertexData}
		};

		auto ImageVS = Generator->GenerateVertexShaderAndInputLayout("./Renderer/resource/Shader/ImageVS.hlsl"
			, InputElement);
		GRM->AddVertexShader("ImageVS", ImageVS);

		auto TriangleTopology = Generator->GenerateTopology(Graphics::eTopology::Triangle);
		GRM->AddTopology("Triangle", TriangleTopology);

		auto ImagePS = Generator->GeneratePixelShader("./Renderer/resource/Shader/ImagePS.hlsl");
		GRM->AddPixelShader("ImagePS", ImagePS);

		auto BackGroundPS = Generator->GeneratePixelShader("./Renderer/resource/Shader/BackGroundPS.hlsl");
		GRM->AddPixelShader("BackGroundPS", BackGroundPS);
	}

	void MyLevel::InitLevel()
	{
		Super::InitLevel();

		CollisionMgr.BindCollisionWhether("Player", "Monster");

		{
			auto Model = Graphics::MakeModel(*GRM, "BasicRect", "Triangle", "ImageVS", "ImagePS");

			auto PlayerInstance = new Player("Player");
			PlayerInstance->InitalizeRenderInterface(*Generator, Model);
			PlayerInstance->InitPixelCollision(*PixelCollisionProcess);
			PlayerInstance->InitalizeCollision(CollisionMgr);

			Collision::RigidBody* RB = new Collision::RigidBody(PlayerInstance->GetPositionRef());
			RB->SetMass(0.01f);
			RB->SetMaxSpeed(Vector2(10.0f, 0.7f));
			
			PlayerInstance->SetRigidBody(RB);

			AddObject(PlayerInstance);
			Renderer->AddModel(eLayer::Player, Model);

			PlayerController* Controller = new PlayerController(*PlayerInstance);
			Controller->SetKeyInput(*Input);

			AddObject(Controller);

			ClassMgr->AttachClassToPlayer(*PlayerInstance, "Phantom");
			ClassMgr->AddToInput(*Input);
		}

		{
			auto Model = Graphics::MakeModel(*GRM, "MushroomBackground", "Triangle", "ImageVS", "ImagePS");

			BackGround* Back = new BackGround("1");
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = GRM->GetShaderResource("MushroomBackground");
			RenderInterface->SetImage(BackImage);
			Back->SetRenderInterface(*Generator, Model, RenderInterface);
			AddObject(Back);

			Renderer->AddModel(eLayer::BackGround, Model);
		}
		{
			auto Model = Graphics::MakeModel(*GRM, "MushroomStage", "Triangle", "ImageVS", "BackGroundPS");

			BackGround* Back = new BackGround("2");
			auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			auto BackImage = GRM->GetShaderResource("MushroomStage");
			RenderInterface->SetImage(BackImage);
			Back->SetRenderInterface(*Generator, Model, RenderInterface);
			AddObject(Back);

			Renderer->AddModel(eLayer::BackGround, Model);
		}

	}

	void MyLevel::EnterLevel()
	{
		Super::EnterLevel();
	}

	void MyLevel::Update()
	{
		Super::Update();
		PixelCollisionProcess->Progress();
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