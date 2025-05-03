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

		// Renderer모듈쪽에 추가
		auto Mesh = Generator.GenerateModel(Vertices.data(), sizeof(ColorVertex), Vertices.size()
			, Indices.data(), sizeof(uint32_t), Indices.size());

		Graphics::Model* Model = new Graphics::Model(*Mesh.Get());

		// Renderer모듈쪽에 추가
		PlayerConst* PConst = new PlayerConst;
		std::vector<Graphics::CpuConstData> Consts{ {&PConst->MVP, sizeof(*PConst)} };
		auto Const = Generator.GenerateConstBuffer(Consts);
		
		auto ObjData = new Graphics::ObjectData;
		ObjData->AddConstBuffer(Const.Get());
		
		Model->AddObjectData(ObjData);

		UINT ModelId = ModelRegistry.AddModel(Model);

		Player* P = new Player("Test", PConst, ModelId);


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