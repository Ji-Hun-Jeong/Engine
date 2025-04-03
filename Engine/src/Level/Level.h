#pragma once
#include "Object/Actor.h"

namespace Graphics
{
	class RenderContext;
}
namespace Engine
{
	class Level
	{
	public:
		explicit Level(Graphics::RenderContext* _RenderContext);
		virtual ~Level() = 0;

	public:
		virtual void InitLevel();
		virtual void EnterLevel();
		virtual void Update();
		virtual void ExitLevel();
		void Render();
		
		void AddObject(Object* _Object);
		void AddActor(Actor* _Actor);

	protected:
		std::map<std::string, Object*> Objects;
		std::map<std::string, Actor*> Actors;

		Graphics::RenderContext* RenderContext;
	};
}