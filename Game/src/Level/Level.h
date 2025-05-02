#pragma once
#include "Object/Actor.h"

namespace Graphics
{
	class RenderDevice;
	class RenderContext;
}
namespace Game
{
	class Level
	{
	public:
		explicit Level();
		virtual ~Level() = 0;

	public:
		virtual void InitLevel();
		virtual void EnterLevel();
		virtual void Update();
		virtual void ExitLevel();
		virtual void Render();
		
		void AddObject(Object* _Object);
		void AddActor(Actor* _Actor);

	protected:
		std::map<Str::FString, Object*> Objects;
		std::map<Str::FString, Actor*> Actors;
	};
}