#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"

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

		Geometry::ColorMeshData Md = Geometry::GenerateColorTriangle();

		auto& Vertices = Md.Vertices;
		auto& Indices = Md.Indices;

		//// Renderer모듈쪽에 추가
		auto Model = std::make_shared<Graphics::Model>(Generator, Vertices.data(), sizeof(ColorVertex), Vertices.size()
			, Indices.data(), sizeof(Indices[0]), Indices.size());

		// Renderer모듈쪽에 추가
		PlayerConst* PConst = new PlayerConst;
		std::vector<Graphics::CpuConstData> Consts{ {&PConst->MVP, sizeof(*PConst)} };

		std::vector<Str::FString> Str{ "Game/resource/image/Player/Alert/0.png" };
		auto Context = std::make_shared<Graphics::StateContext>(Generator, Consts, Str);
		auto ObjData = std::make_shared<Graphics::ObjectData>();

		UINT ContextId = ObjData->AddStateContext(Context);

		UINT ObjectDataId = Model->AddObjectData(ObjData);

		UINT ModelId = ModelRegistry.AddModel(Model);

		Player* P = new Player("Test", *PConst, ModelId);


		AddActor(P);
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