#pragma once
#include "Object/Actor.h"
#include "Object/KeyInput/KeyInput.h"
#include "Game/src/Geometry/Geometry.h"

#include <Renderer/src/Base/GraphicResourceMgr.h>

namespace Game
{
	class Level
	{
	public:
		explicit Level(Graphics::IDRGenerator& _Generator, Graphics::GraphicResourceMgr& _GRM);
		virtual ~Level() = 0;

	public:
		virtual void InitResource();
		virtual void InitLevel();
		virtual void EnterLevel();
		virtual void Update();
		virtual void PostUpdate();
		virtual void ExitLevel();
		virtual void Render() final;

		virtual void InitCamera(UINT _ScreenWidth, UINT _ScreenHeight) = 0;
		
		void AddObject(Object* _Object);
		void AddCamera(class Camera* _Camera);

	protected:
		std::map<Str::FString, Object*> Objects;
		std::map<Str::FString, class Camera*> Cameras;
		KeyInput Input;

		Graphics::IDRGenerator& Generator;
		Graphics::IGraphicProcess& Renderer;
		Graphics::GraphicResourceMgr& GRM;
		
		Collision::ColliderManager CollisionMgr;
		Collision::CollisionDetector CollisionDetector;

	};
}