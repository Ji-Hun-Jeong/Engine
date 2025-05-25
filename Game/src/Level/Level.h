#pragma once
#include "Object/Actor.h"
#include "Object/KeyInput/KeyInput.h"
#include "Game/src/Geometry/Geometry.h"

namespace Game
{
	class Level
	{
	public:
		explicit Level(Graphics::IDRGenerator& _Generator);
		virtual ~Level() = 0;

	public:
		virtual void InitLevel();
		virtual void EnterLevel();
		virtual void Update();
		virtual void ExitLevel();
		virtual void Render() final;
		
		void AddObject(Object* _Object);
		void AddActor(Actor* _Actor);

	protected:
		std::map<Str::FString, Object*> Objects;
		std::map<Str::FString, Actor*> Actors;
		KeyInput Input;

		Graphics::IDRGenerator& Generator;
		Graphics::IGraphicProcess& Renderer;
		
	};
}