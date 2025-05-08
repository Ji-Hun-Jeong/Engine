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
		auto Mesh = Generator.GenerateMesh(Vertices.data(), sizeof(ColorVertex), Vertices.size()
			, Indices.data(), sizeof(Indices[0]), Indices.size());
		auto Model = std::make_shared<Graphics::Model>(Mesh);

		Player* P = new Player("Test");
		P->BindRendererInterface(Generator, Model);

		ModelRegistry.AddModel(Model);

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