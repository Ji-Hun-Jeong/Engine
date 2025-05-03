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
		auto Model = Generator.GenerateModel(Vertices.data(), sizeof(ColorVertex), Vertices.size()
			, Indices.data(), sizeof(uint32_t), Indices.size());

		UINT ModelId = ModelRegistry.AddModel(Model.Get());

		Player* P = new Player("Test", ModelId);

		// Renderer모듈쪽에 추가
		auto ConstData = P->GetConstData();
		std::vector<Graphics::CpuConstData> Consts{ {ConstData.first, ConstData.second} };
		auto Const = Generator.GenerateConstBuffer(Consts);
		UINT ConstId = ModelRegistry.AddConstBuffer(Const.Get());

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